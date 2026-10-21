/*
This file is part of Fincierge Messenger,
an unofficial app based on 64Gram and Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

class PeerData;

namespace Window {
class SessionController;
} // namespace Window

namespace Fincierge {

// Chats protected with a local code. The code is asked when the chat is
// opened; chat list previews and notification texts are hidden.
[[nodiscard]] bool IsChatLocked(not_null<PeerData*> peer);
[[nodiscard]] bool IsChatLocked(PeerId peerId);

// Returns true if the chat may be opened right now. Otherwise asks for the
// code and calls `open` after a correct one.
[[nodiscard]] bool CheckChatUnlocked(
	not_null<Window::SessionController*> controller,
	PeerId peerId,
	Fn<void()> open);

// Chat menu: lock / remove lock (asks the code or creates one).
void ToggleChatLock(
	not_null<Window::SessionController*> controller,
	not_null<PeerData*> peer);

// Settings: change the code.
void ChangeChatLockCode(not_null<Window::SessionController*> controller);
[[nodiscard]] bool HasChatLockCode();

} // namespace Fincierge
