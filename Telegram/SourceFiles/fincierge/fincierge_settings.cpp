/*
This file is part of Fincierge Messenger,
an unofficial app based on 64Gram and Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "fincierge/fincierge_settings.h"

#include "fincierge/fincierge.h"
#include "fincierge/fincierge_actions.h"
#include "fincierge/fincierge_lock.h"
#include "settings/settings_common.h"
#include "ui/vertical_list.h"
#include "ui/wrap/vertical_layout.h"
#include "ui/widgets/buttons.h"
#include "window/window_session_controller.h"
#include "styles/style_settings.h"

namespace Fincierge {
namespace {

void AddToggle(
		not_null<Ui::VerticalLayout*> container,
		const char *title,
		const QString &key) {
	Settings::AddButtonWithIcon(
		container,
		TrValue(title),
		st::settingsButtonNoIcon
	)->toggleOn(
		rpl::single(Option(key))
	)->toggledValue(
	) | rpl::filter([=](bool enabled) {
		return (enabled != Option(key));
	}) | rpl::on_next([=](bool enabled) {
		SetOption(key, enabled);
	}, container->lifetime());
}

} // namespace

void SetupSettings(
		not_null<Window::SessionController*> controller,
		not_null<Ui::VerticalLayout*> container) {
	Ui::AddSkip(container);
	Ui::AddSubsectionTitle(container, TrValue("section_privacy"));
	AddToggle(container, "ghost_read", u"ghost_read"_q);
	AddToggle(container, "ghost_typing", u"ghost_typing"_q);
	AddToggle(container, "ghost_online", u"ghost_online"_q);
	AddToggle(container, "ghost_stories", u"ghost_stories"_q);
	Ui::AddSkip(container);
	Ui::AddDividerText(container, TrValue("ghost_about"));

	Ui::AddSkip(container);
	Ui::AddSubsectionTitle(container, TrValue("section_lock"));
	Settings::AddButtonWithIcon(
		container,
		TrValue("lock_change_code"),
		st::settingsButtonNoIcon
	)->addClickHandler([=] {
		ChangeChatLockCode(controller);
	});
	Ui::AddSkip(container);
	Ui::AddDividerText(container, TrValue("lock_settings_about"));

	Ui::AddSkip(container);
	Ui::AddSubsectionTitle(container, TrValue("section_messages"));
	Settings::AddButtonWithIcon(
		container,
		TrValue("templates_title"),
		st::settingsButtonNoIcon
	)->addClickHandler([=] {
		EditTemplates(controller);
	});
	AddToggle(container, "keep_deleted", u"keep_deleted"_q);
	Ui::AddSkip(container);
	Ui::AddDividerText(container, TrValue("messages_about"));
}

} // namespace Fincierge
