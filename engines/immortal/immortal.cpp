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

#include "immortal/immortal.h"
#include "immortal/detection.h"
#include "immortal/disk.h"

#include "common/scummsys.h"
#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "common/events.h"
#include "common/system.h"
#include "common/debug.h"
#include "common/debug-channels.h"
#include "common/error.h"
#include "common/file.h"

#include "engines/util.h"
#include "audio/mixer.h"

#include "graphics/palette.h"
#include "graphics/surface.h"

namespace Immortal {

ImmortalEngine *g_engine;

ImmortalEngine::ImmortalEngine(OSystem *syst, const ADGameDescription *gameDesc)
	: Engine(syst)
	, _gameDescription(gameDesc)
	, _randomSource("Immortal") {
	g_engine = this;

	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "game");

	debug("ImmortalEngine::ImmortalEngine");
}

ImmortalEngine::~ImmortalEngine() {
	debug("ImmortalEngine::~ImmortalEngine");
}

uint32 ImmortalEngine::getFeatures() const {
	return _gameDescription->flags;
}

Common::String ImmortalEngine::getGameId() const {
	return _gameDescription->gameId;
}

Common::Error ImmortalEngine::run() {
	initGraphics(320, 200);

	if (SearchMan.hasFile("IMMORTAL.dsk")) {
		ProDosDisk *diskBoot  = new ProDosDisk("IMMORTAL.dsk");
		if (diskBoot) {
			debug("Boot disk found");
			SearchMan.add("IMMORTAL.dsk", diskBoot, 0, true);
		}
	}

	if (SearchMan.hasFile("IMMORTAL_GFX.dsk")) {
		ProDosDisk *diskGFX  = new ProDosDisk("IMMORTAL_GFX.dsk");
		if (diskGFX) {
			debug("Gfx disk found");
			SearchMan.add("IMMORTAL_GFX.dsk", diskGFX, 0, true);
		}
	}

	Common::File f;
	if (!f.open("LOAD.OBJ")) {
		debug("oh no :(");
	}

	debug("first file loaded");
	f.close();

	Common::File f2;
	if (!f2.open("GOBLIN.SPR")) {
		debug("oh no :((");
	}

	debug("second file loaded");
	f2.close();


	while (!shouldQuit()) {
	
		int64 loopStart = g_system->getMillis();
		Common::Event event;
		g_system->getEventManager()->pollEvent(event);

		int64 loopEnd = 16 - (g_system->getMillis() - loopStart);
		if (loopEnd > 0)
			g_system->delayMillis(loopEnd);
	}

	return Common::kNoError;

}

Common::Error ImmortalEngine::syncGame(Common::Serializer &s) {
	// The Serializer has methods isLoading() and isSaving()
	// if you need to specific steps; for example setting
	// an array size after reading it's length, whereas
	// for saving it would write the existing array's length
	int dummy = 0;
	s.syncAsUint32LE(dummy);

	return Common::kNoError;
}

} // namespace Immortal
