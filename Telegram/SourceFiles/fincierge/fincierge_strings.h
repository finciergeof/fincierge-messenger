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

	// Reminders.
	{ "remind_me",
		"Remind me...",
		"Напомнить...",
		"Нагадати..." },
	{ "remind_title",
		"Remind me about this message",
		"Напомнить об этом сообщении",
		"Нагадати про це повідомлення" },
	{ "remind_button",
		"Remind",
		"Напомнить",
		"Нагадати" },
	{ "remind_about",
		"At this time the message will arrive in your Saved Messages "
		"with a notification - even if this app is closed.",
		"В это время сообщение придёт в «Избранное» с уведомлением — "
		"даже если приложение закрыто.",
		"У цей час повідомлення прийде в «Збережене» зі сповіщенням — "
		"навіть якщо застосунок закрито." },
	{ "remind_done",
		"Reminder set. It will arrive in Saved Messages.",
		"Напоминание создано. Оно придёт в «Избранное».",
		"Нагадування створено. Воно прийде в «Збережене»." },

	// Chat notes.
	{ "note_add",
		"Add note",
		"Добавить заметку",
		"Додати нотатку" },
	{ "note_edit",
		"Edit note",
		"Изменить заметку",
		"Змінити нотатку" },
	{ "note_title",
		"Note",
		"Заметка",
		"Нотатка" },
	{ "note_placeholder",
		"Only you can see it, on this device",
		"Видна только вам, на этом устройстве",
		"Бачите лише ви, на цьому пристрої" },
	{ "note_label",
		"Your note",
		"Ваша заметка",
		"Ваша нотатка" },
};

} // namespace Fincierge
