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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "common/config-manager.h"

#include "agi/agi.h"
#include "agi/sprite.h"
#include "agi/graphics.h"
#include "agi/inv.h"
#include "agi/text.h"
#include "agi/keyboard.h"
#include "agi/menu.h"
#include "agi/systemui.h"

namespace Agi {

/**
 * Set up new room.
 * This function is called when ego enters a new room.
 * @param n room number
 */
void AgiEngine::newRoom(int16 newRoomNr) {
	ScreenObjEntry *screenObj;
	ScreenObjEntry *screenObjEgo = &_game.screenObjTable[SCREENOBJECTS_EGO_ENTRY];
	int i;

	// Loading trigger
	loadingTrigger_NewRoom(newRoomNr);

	debugC(4, kDebugLevelMain, "*** room %d ***", newRoomNr);
	_sound->stopSound();

	i = 0;
	for (screenObj = _game.screenObjTable; screenObj < &_game.screenObjTable[SCREENOBJECTS_MAX]; screenObj++) {
		screenObj->objectNr = i++;
		screenObj->flags &= ~(fAnimated | fDrawn);
		screenObj->flags |= fUpdate;
		screenObj->stepTime = 1;
		screenObj->stepTimeCount = 1;
		screenObj->cycleTime = 1;
		screenObj->cycleTimeCount = 1;
		screenObj->stepSize = 1;
	}
	agiUnloadResources();

	_game.playerControl = true;
	_game.block.active = false;
	_game.horizon = 36;
	_game.vars[VM_VAR_PREVIOUS_ROOM] = _game.vars[VM_VAR_CURRENT_ROOM];
	_game.vars[VM_VAR_CURRENT_ROOM] = newRoomNr;
	_game.vars[VM_VAR_BORDER_TOUCH_OBJECT] = 0;
	_game.vars[VM_VAR_BORDER_CODE] = 0;
	_game.vars[VM_VAR_EGO_VIEW_RESOURCE] = screenObjEgo->currentViewNr;

	agiLoadResource(RESOURCETYPE_LOGIC, newRoomNr);

	// Reposition ego in the new room
	switch (_game.vars[VM_VAR_BORDER_TOUCH_EGO]) {
	case 1:
		screenObjEgo->yPos = SCRIPT_HEIGHT - 1;
		break;
	case 2:
		screenObjEgo->xPos = 0;
		break;
	case 3:
		screenObjEgo->yPos = _game.horizon + 1;
		break;
	case 4:
		screenObjEgo->xPos = SCRIPT_WIDTH - screenObjEgo->xSize;
		break;
	}

	if (getVersion() < 0x2000) {
		warning("STUB: NewRoom(%d)", newRoomNr);

		screenObjEgo->flags &= ~fDidntMove;
		// animateObject(0);
		agiLoadResource(RESOURCETYPE_VIEW, screenObjEgo->currentViewNr);
		setView(screenObjEgo, screenObjEgo->currentViewNr);

	} else {
		if (screenObjEgo->motionType == kMotionEgo) {
			screenObjEgo->motionType = kMotionNormal;
			_game.vars[VM_VAR_EGO_DIRECTION] = 0;
		}

		_game.vars[VM_VAR_BORDER_TOUCH_EGO] = 0;
		setflag(VM_FLAG_NEW_ROOM_EXEC, true);

		_game.exitAllLogics = true;

		_game._vm->_text->statusDraw();
		_game._vm->_text->promptRedraw();
	}
}

void AgiEngine::resetControllers() {
	int i;

	for (i = 0; i < MAX_CONTROLLERS; i++) {
		_game.controllerOccured[i] = false;
	}
}

void AgiEngine::interpretCycle() {
	ScreenObjEntry *screenObjEgo = &_game.screenObjTable[SCREENOBJECTS_EGO_ENTRY];
	int oldSound, oldScore;

	if (_game.playerControl)
		_game.vars[VM_VAR_EGO_DIRECTION] = screenObjEgo->direction;
	else
		screenObjEgo->direction = _game.vars[VM_VAR_EGO_DIRECTION];

	checkAllMotions();

	oldScore = _game.vars[VM_VAR_SCORE];
	oldSound = getflag(VM_FLAG_SOUND_ON);

	_game.exitAllLogics = false;
	while (runLogic(0) == 0 && !(shouldQuit() || _restartGame)) {
		_game.vars[VM_VAR_WORD_NOT_FOUND] = 0;
		_game.vars[VM_VAR_BORDER_TOUCH_OBJECT] = 0;
		_game.vars[VM_VAR_BORDER_CODE] = 0;
		oldScore = _game.vars[VM_VAR_SCORE];
		setflag(VM_FLAG_ENTERED_CLI, false);
		_game.exitAllLogics = false;
		nonBlockingText_CycleDone();
		resetControllers();
	}
	nonBlockingText_CycleDone();
	resetControllers();

	screenObjEgo->direction = _game.vars[VM_VAR_EGO_DIRECTION];

	if (_game.vars[VM_VAR_SCORE] != oldScore || getflag(VM_FLAG_SOUND_ON) != oldSound)
		_game._vm->_text->statusDraw();

	_game.vars[VM_VAR_BORDER_TOUCH_OBJECT] = 0;
	_game.vars[VM_VAR_BORDER_CODE] = 0;
	setflag(VM_FLAG_NEW_ROOM_EXEC, false);
	setflag(VM_FLAG_RESTART_GAME, false);
	setflag(VM_FLAG_RESTORE_JUST_RAN, false);

	if (_game.gfxMode) {
		updateScreenObjTable();
	}
	_gfx->updateScreen();
	//_gfx->doUpdate();
}

/**
 * Update AGI interpreter timer.
 */
void AgiEngine::updateTimer() {
	_clockCount++;
	if (_clockCount <= TICK_SECONDS)
		return;

	_clockCount -= TICK_SECONDS;

	if (!_game.clockEnabled)
		return;

	setVar(VM_VAR_SECONDS, getVar(VM_VAR_SECONDS) + 1);
	if (getVar(VM_VAR_SECONDS) < 60)
		return;

	setVar(VM_VAR_SECONDS, 0);
	setVar(VM_VAR_MINUTES, getVar(VM_VAR_MINUTES) + 1);
	if (getVar(VM_VAR_MINUTES) < 60)
		return;

	setVar(VM_VAR_MINUTES, 0);
	setVar(VM_VAR_HOURS, getVar(VM_VAR_HOURS) + 1);
	if (getVar(VM_VAR_HOURS) < 24)
		return;

	setVar(VM_VAR_HOURS, 0);
	setVar(VM_VAR_DAYS, getVar(VM_VAR_DAYS) + 1);
}

void AgiEngine::newInputMode(InputMode mode) {
	//if (mode == INPUTMODE_MENU && !getflag(VM_FLAG_MENUS_WORK) && !(getFeatures() & GF_MENUS))
	//	return;

	_oldMode = _game.inputMode;
	_game.inputMode = mode;
}

void AgiEngine::oldInputMode() {
	_game.inputMode = _oldMode;
}

// If main_cycle returns false, don't process more events!
int AgiEngine::mainCycle(bool onlyCheckForEvents) {
	uint16 key;
	byte   keyAscii;
	ScreenObjEntry *screenObjEgo = &_game.screenObjTable[SCREENOBJECTS_EGO_ENTRY];

	if (!onlyCheckForEvents) {
		pollTimer();
		updateTimer();
	}

	if (_menu->delayedExecuteActive()) {
		_menu->execute();
	}

	key = doPollKeyboard();

	// In AGI Mouse emulation mode we must update the mouse-related
	// vars in every interpreter cycle.
	//
	// We run AGIMOUSE always as a side effect
	//if (getFeatures() & GF_AGIMOUSE) {
		_game.vars[28] = _mouse.x / 2;
		_game.vars[29] = _mouse.y;
	//}

	switch (_game.inputMode) {
	case INPUTMODE_NORMAL:
	case INPUTMODE_NONE:
		// Click-to-walk mouse interface
		if (_game.playerControl && (screenObjEgo->flags & fAdjEgoXY)) {
			int toX = screenObjEgo->move_x;
			int toY = screenObjEgo->move_y;

			// AGI Mouse games use ego's sprite's bottom left corner for mouse walking target.
			// Amiga games use ego's sprite's bottom center for mouse walking target.
			// Atari ST and Apple II GS seem to use the bottom left
			if (getPlatform() == Common::kPlatformAmiga)
				toX -= (screenObjEgo->xSize / 2); // Center ego's sprite horizontally

			// Adjust ego's sprite's mouse walking target position (These parameters are
			// controlled with the adj.ego.move.to.x.y-command). Note that these values rely
			// on the horizontal centering of the ego's sprite at least on the Amiga platform.
			toX += _game.adjMouseX;
			toY += _game.adjMouseY;

			screenObjEgo->direction = getDirection(screenObjEgo->xPos, screenObjEgo->yPos, toX, toY, screenObjEgo->stepSize);

			if (screenObjEgo->direction == 0)
				inDestination(screenObjEgo);
		}
		break;
	default:
		break;
	}

	keyAscii = key & 0xFF;
	if (keyAscii) {
		setVar(VM_VAR_KEY, keyAscii);
	}

	if (!cycleInnerLoopIsActive()) {
		// no inner loop active at the moment, regular processing
		switch (_game.inputMode) {
		case INPUTMODE_NORMAL:
			if (!handleController(key)) {
				if (key == 0 || (!_text->promptIsEnabled()))
					break;

				_text->promptCharPress(key);
			}
			break;
		case INPUTMODE_NONE:
			handleController(key);
			if (key)
				_game.keypress = key;
			break;
		default:
			break;
		}

	} else {
		// inner loop active
		// call specific workers
		setVar(VM_VAR_KEY, 0);	// clear keys, they must not be passed to the scripts
		_game.keypress = 0;

		switch (_game.cycleInnerLoopType) {
		case CYCLE_INNERLOOP_GETSTRING: // loop called from TextMgr::stringEdit()
		case CYCLE_INNERLOOP_GETNUMBER:
			//handleController(key);
			if (key) {
				_text->stringCharPress(key);
			}
			break;

		case CYCLE_INNERLOOP_INVENTORY: // loop called from InventoryMgr::show()
			if (key) {
				_inventory->charPress(key);
			}
			break;

		case CYCLE_INNERLOOP_MENU:
			if (key) {
				_menu->charPress(key);
			}
			return false;

		case CYCLE_INNERLOOP_SYSTEMUI_SELECTSAVEDGAMESLOT:
			if (key) {
				_systemUI->savedGameSlot_CharPress(key);
			}
			break;

		default:
			break;
		}
	}

	if (!onlyCheckForEvents) {
		if (_game.msgBoxTicks > 0)
			_game.msgBoxTicks--;
	}

	_gfx->updateScreen();

	return true;
}

int AgiEngine::playGame() {
	int ec = errOK;

	debugC(2, kDebugLevelMain, "initializing...");
	debugC(2, kDebugLevelMain, "game version = 0x%x", getVersion());

	_sound->stopSound();

	// We need to do this accurately and reset the AGI priorityscreen to 4
	// otherwise at least the fan game Nick's Quest will go into an endless
	// loop, because the game draws views before it draws the first background picture.
	// For further study see bug #3451122
	_gfx->clear(0, 4);

	_game.horizon = 36;
	_game.playerControl = false;

	setflag(VM_FLAG_LOGIC_ZERO_FIRST_TIME, true);	// not in 2.917
	setflag(VM_FLAG_NEW_ROOM_EXEC, true);	// needed for MUMG and SQ2!
	setflag(VM_FLAG_SOUND_ON, true);	// enable sound
	setVar(VM_VAR_TIME_DELAY, 2);	// "normal" speed

	_game.gfxMode = true;
	_game.clockEnabled = true;
	_text->promptRow_Set(22);

	// We run AGIMOUSE always as a side effect
	//if (getFeatures() & GF_AGIMOUSE)
		debug(1, "Using AGI Mouse 1.0 protocol");

	if (getFeatures() & GF_AGIPAL)
		debug(1, "Running AGIPAL game");

	debug(0, "Running AGI script.\n");

	setflag(VM_FLAG_ENTERED_CLI, false);
	setflag(VM_FLAG_SAID_ACCEPTED_INPUT, false);
	_game.vars[VM_VAR_WORD_NOT_FOUND] = 0;
	_game.vars[VM_VAR_KEY] = 0;

	debugC(2, kDebugLevelMain, "Entering main loop");
	bool firstLoop = !getflag(VM_FLAG_RESTART_GAME); // Do not restore on game restart

	if (firstLoop) {
		if (ConfMan.hasKey("save_slot")) {
			// quick restore enabled
			_game.automaticRestoreGame = true;
		}
	}

	nonBlockingText_Forget();

	do {

		if (!mainCycle())
			continue;

		if (getVar(VM_VAR_TIME_DELAY) == 0 || (1 + _clockCount) % getVar(VM_VAR_TIME_DELAY) == 0) {
			if (!_game.hasPrompt && _game.inputMode == INPUTMODE_NORMAL) {
				_text->promptRedraw();
				_game.hasPrompt = 1;
			} else if (_game.hasPrompt && _game.inputMode == INPUTMODE_NONE) {
				_text->promptRedraw();
				_game.hasPrompt = 0;
			}

			interpretCycle();

			// Check if the user has asked to load a game from the command line
			// or the launcher
			if (_game.automaticRestoreGame) {
				_game.automaticRestoreGame = false;
				checkQuickLoad();
			}

			setflag(VM_FLAG_ENTERED_CLI, false);
			setflag(VM_FLAG_SAID_ACCEPTED_INPUT, false);
			_game.vars[VM_VAR_WORD_NOT_FOUND] = 0;
			_game.vars[VM_VAR_KEY] = 0;
		}

		if (shouldPerformAutoSave(_lastSaveTime)) {
			saveGame(getSavegameFilename(0), "Autosave");
		}

	} while (!(shouldQuit() || _restartGame));

	_sound->stopSound();

	return ec;
}

int AgiEngine::runGame() {
	int ec = errOK;

	// figure out the expected menu trigger for the current platform
	// need to trigger the menu via mouse and via keyboard for platforms except PC
	if (!(getFeatures() & GF_ESCPAUSE)) {
		switch (getPlatform()) {
		case Common::kPlatformAmiga:
		case Common::kPlatformApple2GS:
			_game.specialMenuTriggerKey = AGI_MENU_TRIGGER_APPLE2GS;
			break;
		case Common::kPlatformAtariST:
			_game.specialMenuTriggerKey = AGI_MENU_TRIGGER_ATARIST;
			break;
		// Macintosh games seem to use ESC key just like PC versions do
		default:
			break;
		}
	}

	// Execute the game
	do {
		debugC(2, kDebugLevelMain, "game loop");
		debugC(2, kDebugLevelMain, "game version = 0x%x", getVersion());

		if (agiInit() != errOK)
			break;

		if (_restartGame) {
			setflag(VM_FLAG_RESTART_GAME, true);
			setVar(VM_VAR_TIME_DELAY, 2);	// "normal" speed
			_restartGame = false;
		}

		// Set computer type (v20 i.e. vComputer) and sound type
		switch (getPlatform()) {
		case Common::kPlatformAtariST:
			setVar(VM_VAR_COMPUTER, kAgiComputerAtariST);
			setVar(VM_VAR_SOUNDGENERATOR, kAgiSoundPC);
			break;
		case Common::kPlatformAmiga:
			if (getFeatures() & GF_OLDAMIGAV20)
				setVar(VM_VAR_COMPUTER, kAgiComputerAmigaOld);
			else
				setVar(VM_VAR_COMPUTER, kAgiComputerAmiga);
			setVar(VM_VAR_SOUNDGENERATOR, kAgiSoundTandy);
			break;
		case Common::kPlatformApple2GS:
			setVar(VM_VAR_COMPUTER, kAgiComputerApple2GS);
			if (getFeatures() & GF_2GSOLDSOUND)
				setVar(VM_VAR_SOUNDGENERATOR, kAgiSound2GSOld);
			else
				setVar(VM_VAR_SOUNDGENERATOR, kAgiSoundTandy);
			break;
		case Common::kPlatformDOS:
		default:
			setVar(VM_VAR_COMPUTER, kAgiComputerPC);
			setVar(VM_VAR_SOUNDGENERATOR, kAgiSoundPC);
			break;
		}

		// Set monitor type (v26 i.e. vMonitor)
		switch (_renderMode) {
		case RENDERMODE_CGA:
			setVar(VM_VAR_MONITOR, kAgiMonitorCga);
			break;
		case RENDERMODE_HERCULES:
			setVar(VM_VAR_MONITOR, kAgiMonitorHercules);
			break;
		// Don't know if Amiga AGI games use a different value than kAgiMonitorEga
		// for vMonitor so I just use kAgiMonitorEga for them (As was done before too).
		case RENDERMODE_AMIGA:
		case RENDERMODE_APPLE_II_GS:
		case RENDERMODE_ATARI_ST:
		case RENDERMODE_EGA:
		case RENDERMODE_VGA:
		default:
			setVar(VM_VAR_MONITOR, kAgiMonitorEga);
			break;
		}

		setVar(VM_VAR_FREE_PAGES, 180); // Set amount of free memory to realistic value
		setVar(VM_VAR_MAX_INPUT_CHARACTERS, 38);
		_game.inputMode = INPUTMODE_NONE;
		_text->promptDisable();
		_game.hasPrompt = 0;

		_game.state = STATE_RUNNING;
		ec = playGame();
		_game.state = STATE_LOADED;
		agiDeinit();
	} while (_restartGame);

	delete _menu;
	_menu = NULL;

	releaseImageStack();

	return ec;
}

} // End of namespace Agi
