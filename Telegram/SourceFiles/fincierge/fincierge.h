/*
This file is part of Fincierge Messenger,
an unofficial app based on 64Gram and Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

class History;
class PeerData;

namespace Fincierge {

// Options are stored next to 64Gram's ones in
// tdata/enhanced-settings-custom.json, with an "fc_" prefix.
[[nodiscard]] bool Option(const QString &key);
void SetOption(const QString &key, bool value);
[[nodiscard]] QString StringOption(const QString &key);
void SetStringOption(const QString &key, const QString &value);

// Bundled translations for Fincierge's own strings: en / ru / uk.
[[nodiscard]] QString Tr(const char *key);
[[nodiscard]] rpl::producer<QString> TrValue(const char *key);

// Ghost mode.
[[nodiscard]] bool GhostRead();     // don't send "read" to the server
[[nodiscard]] bool GhostTyping();   // don't send "typing..."
[[nodiscard]] bool GhostOnline();   // always appear offline
[[nodiscard]] bool GhostStories();  // view stories without a mark

// Ghost read is on, but the user explicitly asked to mark this chat.
void MarkReadOnServer(not_null<History*> history);

} // namespace Fincierge
