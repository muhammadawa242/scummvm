/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef NANCY_STATE_LOGO_H
#define NANCY_STATE_LOGO_H

#include "engines/nancy/state/state.h"

#include "common/singleton.h"

namespace Graphics {
	struct Surface;
}

namespace Nancy {

class NancyEngine;

namespace State {

class Logo : public State, public Common::Singleton<Logo> {
public:
	Logo() :
		_state(kInit),
		_runState(kBlit),
		_startTicks(0),
		_surf(nullptr) { }
		
	// State API
    virtual void process() override;
    virtual bool onStateExit() override { destroy(); return true; };

	uint MSNDchannelID; // This definitely shouldn't be here

private:
	void init();
	void startSound();
	void run();
	void stop();

	enum State {
		kInit,
		kStartSound,
		kRun,
		kStop
	};

	enum RunState {
		// First four states are related to testing mode
		kBlit = 4,
		kWait
	};

	State _state;
	RunState _runState;
	uint _startTicks;
	Graphics::Surface *_surf;
};

#define NancyLogoState Nancy::State::Logo::instance()

} // end of namespace State
} // End of namespace Nancy

#endif // NANCY_STATE_LOGO_H
