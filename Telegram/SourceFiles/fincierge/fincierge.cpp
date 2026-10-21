/*
This file is part of Fincierge Messenger,
an unofficial app based on 64Gram and Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "fincierge/fincierge.h"

#include "fincierge/fincierge_strings.h"

#include <cstring>
#include "core/enhanced_settings.h"
#include "lang/lang_instance.h"
#include "history/history.h"
#include "history/history_item.h"
#include "data/data_peer.h"
#include "data/data_channel.h"
#include "main/main_session.h"
#include "apiwrap.h"
#include "data/data_session.h"
#include "settings.h"

namespace Fincierge {
namespace {

[[nodiscard]] QString Key(const QString &key) {
	return u"fc_"_q + key;
}

[[nodiscard]] int LanguageIndex() {
	const auto id = Lang::GetInstance().id().toLower();
	if (id.startsWith(u"uk"_q)) {
		return 2;
	} else if (id.startsWith(u"ru"_q) || id.startsWith(u"be"_q)) {
		return 1;
	}
	return 0;
}

[[nodiscard]] base::flat_set<FullMsgId> &KeptDeleted() {
	static auto result = base::flat_set<FullMsgId>();
	return result;
}

} // namespace

bool Option(const QString &key) {
	return GetEnhancedBool(Key(key));
}

void SetOption(const QString &key, bool value) {
	SetEnhancedValue(Key(key), value);
	EnhancedSettings::Write();
}

QString StringOption(const QString &key) {
	return GetEnhancedString(Key(key));
}

void SetStringOption(const QString &key, const QString &value) {
	SetEnhancedValue(Key(key), value);
	EnhancedSettings::Write();
}

QString Tr(const char *key) {
	for (const auto &entry : kStrings) {
		if (!strcmp(entry.key, key)) {
			const auto index = LanguageIndex();
			const auto text = (index == 2)
				? entry.uk
				: (index == 1)
				? entry.ru
				: entry.en;
			return QString::fromUtf8(text);
		}
	}
	return QString::fromUtf8(key);
}

rpl::producer<QString> TrValue(const char *key) {
	return rpl::single(Tr(key));
}

bool GhostRead() {
	return Option(u"ghost_read"_q);
}

bool GhostTyping() {
	return Option(u"ghost_typing"_q);
}

bool GhostOnline() {
	return Option(u"ghost_online"_q);
}

bool GhostStories() {
	return Option(u"ghost_stories"_q);
}

void MarkReadOnServer(not_null<History*> history) {
	const auto last = history->lastServerMessage();
	const auto tillId = last ? last->id : history->maxMsgId();
	if (!tillId) {
		return;
	}
	const auto peer = history->peer;
	auto &api = peer->session().api();
	if (const auto channel = peer->asChannel()) {
		api.request(MTPchannels_ReadHistory(
			channel->inputChannel(),
			MTP_int(tillId)
		)).send();
	} else {
		api.request(MTPmessages_ReadHistory(
			peer->input(),
			MTP_int(tillId)
		)).done([=](const MTPmessages_AffectedMessages &result) {
			peer->session().api().applyAffectedMessages(peer, result);
		}).send();
	}
}

bool KeepDeleted() {
	return Option(u"keep_deleted"_q);
}

bool IsKeptDeleted(not_null<const HistoryItem*> item) {
	const auto &kept = KeptDeleted();
	return !kept.empty() && kept.contains(item->fullId());
}

std::vector<not_null<HistoryItem*>> KeepDeletedItems(
		std::vector<not_null<HistoryItem*>> items) {
	if (!KeepDeleted()) {
		return items;
	}
	auto result = std::vector<not_null<HistoryItem*>>();
	for (const auto &item : items) {
		if (item->isRegular() && !item->isService()) {
			KeptDeleted().emplace(item->fullId());
			item->history()->owner().requestItemViewRefresh(item);
		} else {
			result.push_back(item);
		}
	}
	return result;
}

} // namespace Fincierge
