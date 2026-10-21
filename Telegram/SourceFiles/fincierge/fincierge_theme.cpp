/*
This file is part of Fincierge Messenger,
an unofficial app based on 64Gram and Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "fincierge/fincierge_theme.h"

#include "fincierge/fincierge.h"
#include "window/themes/window_theme.h"
#include "window/themes/window_themes_embedded.h"

namespace Fincierge {

QColor DefaultAccent(Window::Theme::EmbeddedType type) {
	using Type = Window::Theme::EmbeddedType;
	switch (type) {
	case Type::Default:
	case Type::DayBlue:
		return QColor(0x7A, 0x5B, 0xDB); // Fincierge violet (light).
	case Type::Night:
	case Type::NightGreen:
		return QColor(0x8B, 0x6F, 0xE0); // Fincierge violet (dark).
	}
	return QColor(0x7A, 0x5B, 0xDB);
}

void ApplyFirstRunTheme() {
	if (Option(u"theme_initialized"_q)) {
		return;
	}
	using namespace Window::Theme;
	const auto background = Background();
	if (!background || !background->started()) {
		return;
	}
	SetOption(u"theme_initialized"_q, true);
	const auto &object = background->themeObject();
	if (IsNightMode()
		|| !object.pathAbsolute.isEmpty()
		|| object.cloud.id) {
		return;
	}
	ApplyDefaultWithPath(u":/gui/day-blue.tdesktop-theme"_q);
	KeepApplied();
}

} // namespace Fincierge
