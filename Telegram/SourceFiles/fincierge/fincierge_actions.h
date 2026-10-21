/*
This file is part of Fincierge Messenger,
an unofficial app based on 64Gram and Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

class HistoryItem;
class PeerData;

namespace Ui {
class PopupMenu;
} // namespace Ui

namespace Window {
class SessionController;
} // namespace Window

namespace Fincierge {

// "Remind me..." for a single message in the chat context menu.
void AddMessageActions(
	not_null<Ui::PopupMenu*> menu,
	not_null<Window::SessionController*> controller,
	not_null<HistoryItem*> item);

// Private notes for chats, visible only to the user on this device.
[[nodiscard]] QString ChatNote(not_null<PeerData*> peer);
void SetChatNote(not_null<PeerData*> peer, const QString &note);
[[nodiscard]] rpl::producer<TextWithEntities> ChatNoteValue(
	not_null<PeerData*> peer);
void EditChatNote(
	not_null<Window::SessionController*> controller,
	not_null<PeerData*> peer);

} // namespace Fincierge
