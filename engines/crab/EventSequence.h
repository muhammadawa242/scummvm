/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * This code is based on the CRAB engine
 *
 * Copyright (c) Arvind Raja Yadav
 *
 * Licensed under MIT
 *
 */

#ifndef CRAB_EVENTSEQUENCE_H
#define CRAB_EVENTSEQUENCE_H
#include "common_header.h"

#include "GameEventInfo.h"
#include "ImageManager.h"
#include "Inventory.h"
#include "gameevent.h"
#include "journal.h"

namespace pyrodactyl {
namespace event {
class EventSequence {
	std::vector<GameEvent> events;
	bool event_in_progress;

	// The event currently in execution - updated only when all trigger conditions are met in InternalEvents
	unsigned int cur;

	// The events that can happen next - these are updated when the cur event is over
	// This means cur and next operate in an alternating way
	// scan next until find event, make it cur, end cur and update next, repeat
	std::vector<unsigned int> next;

public:
	EventSequence() {
		event_in_progress = false;
		next.push_back(0);
		cur = 0;
	}
	~EventSequence() {}

	GameEvent *CurrentEvent() { return &events[cur]; }

	// See if we should trigger any event
	void InternalEvents(pyrodactyl::event::Info &info);
	void NextEvent(Info &info, const std::string &player_id, std::vector<EventResult> &result,
				   std::vector<EventSeqInfo> &end_seq, int NextEventChoice = -1);

	bool EventInProgress() { return event_in_progress; }
	void EventInProgress(bool val) { event_in_progress = val; }

	// Load and save
	void Load(const std::string &filename);

	void SaveState(rapidxml::xml_document<char> &doc, rapidxml::xml_node<char> *root, const char *name);
	void LoadState(rapidxml::xml_node<char> *node);
};
} // End of namespace event
} // End of namespace pyrodactyl

#endif // CRAB_EVENTSEQUENCE_H
