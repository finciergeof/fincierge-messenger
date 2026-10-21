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

	// Templates.
	{ "section_messages",
		"Messages",
		"Сообщения",
		"Повідомлення" },
	{ "templates_title",
		"Quick reply templates",
		"Шаблоны ответов",
		"Шаблони відповідей" },
	{ "templates_placeholder",
		"One template per line",
		"Один шаблон на строку",
		"Один шаблон на рядок" },
	{ "messages_about",
		"Templates appear when you right-click the message field. "
		"\"Remind me...\" is in the message menu, chat notes are in the "
		"chat menu in the chat list. Deleted messages are kept only "
		"while the app is running.",
		"Шаблоны появляются по правому клику в поле ввода. "
		"«Напомнить...» — в меню сообщения, заметки — в меню чата "
		"в списке чатов. Удалённые сообщения хранятся, пока "
		"приложение открыто.",
		"Шаблони з'являються за правим кліком у полі введення. "
		"«Нагадати...» — у меню повідомлення, нотатки — у меню чату "
		"в списку чатів. Видалені повідомлення зберігаються, поки "
		"застосунок відкритий." },

	// Deleted messages.
	{ "keep_deleted",
		"Keep deleted messages",
		"Сохранять удалённые сообщения",
		"Зберігати видалені повідомлення" },
	{ "deleted_mark",
		"deleted",
		"удалено",
		"видалено" },

	// Chat lock.
	{ "section_lock",
		"Locked chats",
		"Чаты под кодом",
		"Чати під кодом" },
	{ "lock_add",
		"Lock with code",
		"Закрыть кодом",
		"Закрити кодом" },
	{ "lock_remove",
		"Remove code",
		"Убрать код",
		"Прибрати код" },
	{ "lock_added",
		"The chat is locked with your code.",
		"Чат закрыт кодом.",
		"Чат закрито кодом." },
	{ "lock_removed",
		"The code is removed from this chat.",
		"Код с чата снят.",
		"Код з чату знято." },
	{ "lock_preview",
		"Locked chat",
		"Чат под кодом",
		"Чат під кодом" },
	{ "lock_enter_title",
		"Enter the code",
		"Введите код",
		"Введіть код" },
	{ "lock_enter_about",
		"This chat is protected with your code.",
		"Этот чат защищён вашим кодом.",
		"Цей чат захищено вашим кодом." },
	{ "lock_remove_title",
		"Remove the code",
		"Убрать код",
		"Прибрати код" },
	{ "lock_create_title",
		"Create a code",
		"Придумайте код",
		"Придумайте код" },
	{ "lock_create_about",
		"It will be asked when you open locked chats on this device. "
		"Telegram doesn't know it and can't restore it.",
		"Его будут спрашивать при открытии закрытых чатов на этом "
		"устройстве. Telegram его не знает и восстановить не сможет.",
		"Його питатимуть під час відкриття закритих чатів на цьому "
		"пристрої. Telegram його не знає і не зможе відновити." },
	{ "lock_change_title",
		"Current code",
		"Текущий код",
		"Поточний код" },
	{ "lock_change_code",
		"Code for locked chats",
		"Код для закрытых чатов",
		"Код для закритих чатів" },
	{ "lock_code_placeholder",
		"Code",
		"Код",
		"Код" },
	{ "lock_code_repeat",
		"Repeat the code",
		"Повторите код",
		"Повторіть код" },
	{ "lock_confirm",
		"OK",
		"Готово",
		"Готово" },
	{ "lock_code_saved",
		"The code is saved.",
		"Код сохранён.",
		"Код збережено." },
	{ "lock_settings_about",
		"Lock a chat from its menu in the chat list. The code is asked "
		"when the chat is opened (then the chat stays open for 10 "
		"minutes), its messages are hidden in the chat list and in "
		"notifications. This protects from people at your computer, "
		"the chat itself stays a normal Telegram chat.",
		"Закрыть чат можно в его меню в списке чатов. Код спрашивается "
		"при открытии (потом чат открыт 10 минут), сообщения скрыты в "
		"списке чатов и в уведомлениях. Это защита от тех, кто сядет за "
		"ваш компьютер, сам чат остаётся обычным чатом Telegram.",
		"Закрити чат можна в його меню в списку чатів. Код питається під "
		"час відкриття (потім чат відкритий 10 хвилин), повідомлення "
		"приховані в списку чатів і в сповіщеннях. Це захист від тих, хто "
		"сяде за ваш комп'ютер, сам чат залишається звичайним чатом "
		"Telegram." },
};

} // namespace Fincierge
