/*
This file is part of Fincierge Messenger,
an unofficial app based on 64Gram and Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

namespace Window::Theme {
enum class EmbeddedType;
} // namespace Window::Theme

namespace Fincierge {

// Fincierge brand accent for the built-in themes, used when the user
// didn't pick an accent color of their own.
[[nodiscard]] QColor DefaultAccent(Window::Theme::EmbeddedType type);

// On the very first launch switch to the light "Day" theme, which is
// colorized with the Fincierge accent (violet bubbles, violet controls).
void ApplyFirstRunTheme();

} // namespace Fincierge
