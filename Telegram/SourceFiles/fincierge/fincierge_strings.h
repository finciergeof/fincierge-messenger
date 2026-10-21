/*
This file is part of Fincierge Messenger,
an unofficial app based on 64Gram and Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

// Fincierge's own strings. Every new string must get all three languages.

namespace Fincierge {

struct StringEntry {
	const char *key;
	const char *en;
	const char *ru;
	const char *uk;
};

inline constexpr StringEntry kStrings[] = {
	{ "settings_title",
		"Fincierge",
		"Fincierge",
		"Fincierge" },

	// Privacy / ghost mode.
	{ "section_privacy",
		"Privacy",
		"Приватность",
		"Приватність" },
	{ "ghost_read",
		"Don't mark messages as read",
		"Не отмечать сообщения прочитанными",
		"Не позначати повідомлення прочитаними" },
	{ "ghost_typing",
		"Don't show \"typing...\"",
		"Не показывать «печатает...»",
		"Не показувати «друкує...»" },
	{ "ghost_online",
		"Always appear offline",
		"Всегда быть не в сети",
		"Завжди бути не в мережі" },
	{ "ghost_stories",
		"View stories invisibly",
		"Смотреть истории незаметно",
		"Дивитися історії непомітно" },
	{ "ghost_about",
		"Chats are marked as read only on this device. "
		"To let the sender see it, use \"Mark as read for everyone\" "
		"in the chat's menu. Sending a message in a chat marks it as read "
		"for everyone - that's how Telegram works.",
		"Чаты отмечаются прочитанными только на этом устройстве. "
		"Чтобы отправитель увидел, нажмите «Прочитать для всех» в меню "
		"чата. Если вы отправите сообщение в чат, он станет прочитанным "
		"для всех — так устроен Telegram.",
		"Чати позначаються прочитаними лише на цьому пристрої. "
		"Щоб відправник побачив, натисніть «Прочитати для всіх» у меню "
		"чату. Якщо ви надішлете повідомлення в чат, він стане "
		"прочитаним для всіх — так влаштований Telegram." },
	{ "mark_read_server",
		"Mark as read for everyone",
		"Прочитать для всех",
		"Прочитати для всіх" },
};

} // namespace Fincierge
