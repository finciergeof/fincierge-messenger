/*
This file is part of Fincierge Messenger,
an unofficial app based on 64Gram and Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "fincierge/fincierge_actions.h"

#include "fincierge/fincierge.h"
#include "api/api_common.h"
#include "apiwrap.h"
#include "base/unixtime.h"
#include "data/data_peer.h"
#include "data/data_session.h"
#include "data/data_types.h"
#include "history/history.h"
#include "history/history_item.h"
#include "lang/lang_keys.h"
#include "main/main_session.h"
#include "ui/boxes/choose_date_time.h"
#include "ui/layers/generic_box.h"
#include "ui/widgets/fields/input_field.h"
#include "ui/widgets/popup_menu.h"
#include "window/window_session_controller.h"
#include "styles/style_layers.h"
#include "styles/style_menu_icons.h"
#include "styles/style_widgets.h"

namespace Fincierge {
namespace {

constexpr auto kDefaultRemindIn = TimeId(60 * 60);

rpl::event_stream<PeerId> &NoteChanges() {
	static auto result = rpl::event_stream<PeerId>();
	return result;
}

[[nodiscard]] QString NoteKey(not_null<PeerData*> peer) {
	return u"note_"_q + QString::number(peer->id.value);
}

void RemindAbout(
		not_null<Window::SessionController*> controller,
		FullMsgId itemId,
		TimeId when) {
	const auto session = &controller->session();
	const auto item = session->data().message(itemId);
	if (!item) {
		return;
	}
	auto options = Api::SendOptions();
	options.scheduled = when;
	auto action = Api::SendAction(
		session->data().history(session->user()),
		options);
	action.clearDraft = false;
	auto draft = Data::ResolvedForwardDraft{
		.items = HistoryItemsList{ item },
	};
	const auto weak = base::make_weak(controller);
	session->api().forwardMessages(std::move(draft), action, [=] {
		if (const auto strong = weak.get()) {
			strong->showToast(Tr("remind_done"));
		}
	});
}

} // namespace

void AddMessageActions(
		not_null<Ui::PopupMenu*> menu,
		not_null<Window::SessionController*> controller,
		not_null<HistoryItem*> item) {
	if (!item->isRegular() || !item->allowsForward()) {
		return;
	}
	const auto itemId = item->fullId();
	menu->addAction(Tr("remind_me"), [=] {
		controller->show(Box([=](not_null<Ui::GenericBox*> box) {
			Ui::ChooseDateTimeBox(box, {
				.title = TrValue("remind_title"),
				.submit = TrValue("remind_button"),
				.done = [=](TimeId when) {
					RemindAbout(controller, itemId, when);
					box->closeBox();
				},
				.time = base::unixtime::now() + kDefaultRemindIn,
				.description = TrValue("remind_about"),
			});
		}));
	}, &st::menuIconSchedule);
}

QString ChatNote(not_null<PeerData*> peer) {
	return StringOption(NoteKey(peer));
}

void SetChatNote(not_null<PeerData*> peer, const QString &note) {
	SetStringOption(NoteKey(peer), note.trimmed());
	NoteChanges().fire_copy(peer->id);
}

rpl::producer<TextWithEntities> ChatNoteValue(not_null<PeerData*> peer) {
	const auto id = peer->id;
	return rpl::single(
		id
	) | rpl::then(NoteChanges().events(
	) | rpl::filter([=](PeerId changed) {
		return (changed == id);
	})) | rpl::map([=](PeerId) {
		return TextWithEntities{ ChatNote(peer) };
	});
}

void EditChatNote(
		not_null<Window::SessionController*> controller,
		not_null<PeerData*> peer) {
	controller->show(Box([=](not_null<Ui::GenericBox*> box) {
		box->setTitle(TrValue("note_title"));
		const auto field = box->addRow(object_ptr<Ui::InputField>(
			box,
			st::defaultInputField,
			Ui::InputField::Mode::MultiLine,
			TrValue("note_placeholder"),
			ChatNote(peer)));
		const auto save = [=] {
			SetChatNote(peer, field->getLastText());
			box->closeBox();
		};
		box->addButton(tr::lng_settings_save(), save);
		box->addButton(tr::lng_cancel(), [=] { box->closeBox(); });
		box->setFocusCallback([=] { field->setFocusFast(); });
	}));
}

} // namespace Fincierge
