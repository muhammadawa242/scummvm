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

#ifndef CRAB_REPLYMENU_H
#define CRAB_REPLYMENU_H

#include "GameEventInfo.h"
#include "ImageData.h"
#include "PersonHandler.h"
#include "ReplyButton.h"
#include "common_header.h"
#include "conversationdata.h"
#include "emotion.h"
#include "eventstore.h"
#include "menu.h"

namespace pyrodactyl {
namespace ui {
class ReplyMenu : public Menu<ReplyButton> {
	// Data about the background image
	ImageData bg;

	// The minimum spacing between two reply choices
	int spacing;

	// The emotion indicator used to indicate the type of reply selected
	EmotionIndicator tone;

public:
	ReplyMenu() { spacing = 20; }
	~ReplyMenu() {}

	void Load(const std::string &filename);
	int HandleEvents(pyrodactyl::event::Info &info, pyrodactyl::event::ConversationData &dat,
					 const std::string &cur_id, PersonHandler &oh, const SDL_Event &Event);

	void Draw();
	void Cache(pyrodactyl::event::Info &info, pyrodactyl::event::ConversationData &dat);

	void SetUI();
};
} // End of namespace ui
} // End of namespace pyrodactyl

#endif // CRAB_REPLYMENU_H
