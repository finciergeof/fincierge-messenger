/*
This file is part of Fincierge Messenger,
an unofficial app based on 64Gram and Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "fincierge/fincierge_lock.h"

#include "fincierge/fincierge.h"
#include "base/random.h"
#include "data/data_peer.h"
#include "lang/lang_keys.h"
#include "ui/layers/generic_box.h"
#include "ui/widgets/fields/password_input.h"
#include "ui/widgets/labels.h"
#include "window/window_session_controller.h"
#include "styles/style_layers.h"
#include "styles/style_widgets.h"

#include <QtCore/QCryptographicHash>

namespace Fincierge {
namespace {

constexpr auto kUnlockedFor = crl::time(10 * 60 * 1000);

[[nodiscard]] base::flat_map<PeerId, crl::time> &Unlocked() {
	static auto result = base::flat_map<PeerId, crl::time>();
	return result;
}

[[nodiscard]] QStringList LockedList() {
	return StringOption(u"locked_chats"_q).split(
		',',
		Qt::SkipEmptyParts);
}

void SetLockedList(const QStringList &list) {
	SetStringOption(u"locked_chats"_q, list.join(','));
}

[[nodiscard]] QString HashCode(const QString &code, const QString &salt) {
	return QString::fromLatin1(QCryptographicHash::hash(
		(salt + code).toUtf8(),
		QCryptographicHash::Sha256).toHex());
}

[[nodiscard]] bool CodeMatches(const QString &code) {
	const auto salt = StringOption(u"lock_salt"_q);
	const auto hash = StringOption(u"lock_hash"_q);
	return !hash.isEmpty() && (HashCode(code, salt) == hash);
}

void SaveCode(const QString &code) {
	auto bytes = QByteArray(16, Qt::Uninitialized);
	base::RandomFill(bytes.data(), bytes.size());
	const auto salt = QString::fromLatin1(bytes.toHex());
	SetStringOption(u"lock_salt"_q, salt);
	SetStringOption(u"lock_hash"_q, HashCode(code, salt));
}

// Generic "enter code" box. `check` returns false on a wrong code.
void ShowCodeBox(
		not_null<Window::SessionController*> controller,
		const char *title,
		const char *about,
		bool confirmTwice,
		Fn<bool(QString)> check) {
	controller->show(Box([=](not_null<Ui::GenericBox*> box) {
		box->setTitle(TrValue(title));
		box->addRow(object_ptr<Ui::FlatLabel>(
			box,
			TrValue(about),
			st::boxLabel));
		const auto &fieldSt = st::defaultInputField;
		const auto addField = [&](const char *placeholder) {
			const auto row = box->addRow(object_ptr<Ui::RpWidget>(box));
			row->resize(row->width(), fieldSt.heightMin);
			const auto field = Ui::CreateChild<Ui::PasswordInput>(
				row,
				fieldSt,
				TrValue(placeholder));
			row->sizeValue() | rpl::on_next([=](QSize size) {
				field->resize(size.width(), field->height());
			}, row->lifetime());
			return field;
		};
		const auto first = addField("lock_code_placeholder");
		const auto second = confirmTwice
			? addField("lock_code_repeat")
			: nullptr;
		box->setFocusCallback([=] { first->setFocusFast(); });
		const auto confirm = [=] {
			const auto code = first->getLastText();
			if (code.isEmpty()) {
				first->setFocus();
				first->showError();
				return;
			} else if (second && second->getLastText() != code) {
				second->setFocus();
				second->showError();
				return;
			}
			const auto weak = base::make_weak(box);
			if (!check(code)) {
				first->setFocus();
				first->showError();
				return;
			}
			if (weak) {
				box->closeBox();
			}
		};
		QObject::connect(first, &Ui::MaskedInputField::submitted, confirm);
		if (second) {
			QObject::connect(
				second,
				&Ui::MaskedInputField::submitted,
				confirm);
		}
		box->addButton(TrValue("lock_confirm"), confirm);
		box->addButton(tr::lng_cancel(), [=] { box->closeBox(); });
	}));
}

} // namespace

bool HasChatLockCode() {
	return !StringOption(u"lock_hash"_q).isEmpty();
}

bool IsChatLocked(PeerId peerId) {
	return LockedList().contains(QString::number(peerId.value));
}

bool IsChatLocked(not_null<PeerData*> peer) {
	return IsChatLocked(peer->id);
}

bool CheckChatUnlocked(
		not_null<Window::SessionController*> controller,
		PeerId peerId,
		Fn<void()> open) {
	if (!IsChatLocked(peerId) || !HasChatLockCode()) {
		return true;
	}
	const auto i = Unlocked().find(peerId);
	if (i != Unlocked().end() && crl::now() < i->second + kUnlockedFor) {
		return true;
	}
	ShowCodeBox(
		controller,
		"lock_enter_title",
		"lock_enter_about",
		false,
		[=](QString code) {
			if (!CodeMatches(code)) {
				return false;
			}
			Unlocked()[peerId] = crl::now();
			crl::on_main([=] {
				open();
			});
			return true;
		});
	return false;
}

void ToggleChatLock(
		not_null<Window::SessionController*> controller,
		not_null<PeerData*> peer) {
	const auto id = QString::number(peer->id.value);
	const auto peerId = peer->id;
	if (IsChatLocked(peer)) {
		ShowCodeBox(
			controller,
			"lock_remove_title",
			"lock_enter_about",
			false,
			[=](QString code) {
				if (!CodeMatches(code)) {
					return false;
				}
				auto list = LockedList();
				list.removeAll(id);
				SetLockedList(list);
				Unlocked().erase(peerId);
				controller->showToast(Tr("lock_removed"));
				return true;
			});
		return;
	}
	const auto lock = [=] {
		auto list = LockedList();
		if (!list.contains(id)) {
			list.push_back(id);
		}
		SetLockedList(list);
		Unlocked()[peerId] = crl::now();
		controller->showToast(Tr("lock_added"));
	};
	if (HasChatLockCode()) {
		lock();
		return;
	}
	ShowCodeBox(
		controller,
		"lock_create_title",
		"lock_create_about",
		true,
		[=](QString code) {
			SaveCode(code);
			lock();
			return true;
		});
}

void ChangeChatLockCode(not_null<Window::SessionController*> controller) {
	const auto create = [=] {
		ShowCodeBox(
			controller,
			"lock_create_title",
			"lock_create_about",
			true,
			[=](QString code) {
				SaveCode(code);
				controller->showToast(Tr("lock_code_saved"));
				return true;
			});
	};
	if (!HasChatLockCode()) {
		create();
		return;
	}
	ShowCodeBox(
		controller,
		"lock_change_title",
		"lock_enter_about",
		false,
		[=](QString code) {
			if (!CodeMatches(code)) {
				return false;
			}
			crl::on_main([=] {
				create();
			});
			return true;
		});
}

} // namespace Fincierge
