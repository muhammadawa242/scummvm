/*
Copyright (C) 2004-2007 The Pentagram team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "ultima/ultima8/misc/pent_include.h"

#include "ultima/ultima8/games/u8_game.h"

#include "ultima/ultima8/graphics/palette_manager.h"
#include "ultima/ultima8/filesys/idata_source.h"
#include "ultima/ultima8/filesys/file_system.h"
#include "ultima/ultima8/games/game_data.h"
#include "ultima/ultima8/graphics/xform_blend.h"
#include "ultima/ultima8/filesys/u8_save_file.h"
#include "ultima/ultima8/world/world.h"
#include "ultima/ultima8/world/actors/main_actor.h"
#include "ultima/ultima8/world/item_factory.h"
#include "ultima/ultima8/kernel/object_manager.h"
#include "ultima/ultima8/ultima8.h"
#include "ultima/ultima8/conf/setting_manager.h"
#include "ultima/ultima8/gumps/movie_gump.h"
#include "ultima/ultima8/filesys/raw_archive.h"
#include "ultima/ultima8/gumps/credits_gump.h"
#include "ultima/ultima8/kernel/kernel.h"
#include "ultima/ultima8/audio/music_process.h"
#include "ultima/ultima8/games/start_u8_process.h"
#include "ultima/ultima8/world/get_object.h"

namespace Ultima {
namespace Ultima8 {

U8Game::U8Game() : Game() {
	// Set some defaults for gameplay-related settings
	SettingManager *settingman = SettingManager::get_instance();
	settingman->setDefault("skipstart", false);
	settingman->setDefault("endgame", false);
	settingman->setDefault("quotes", false);
	settingman->setDefault("footsteps", true);
	settingman->setDefault("targetedjump", true);

	GameInfo *info = Ultima8Engine::get_instance()->getGameInfo();
	if (info->_language == GameInfo::GAMELANG_JAPANESE) {
		settingman->setDefault("textdelay", 20);
	} else {
		settingman->setDefault("textdelay", 8);
	}
}

U8Game::~U8Game() {
}

bool U8Game::loadFiles() {
	// Load palette
	pout << "Load Palette" << Std::endl;
	IDataSource *pf = FileSystem::get_instance()->ReadFile("@game/static/u8pal.pal");
	if (!pf) {
		perr << "Unabl-e to load static/u8pal.pal." << Std::endl;
		return false;
	}
	pf->seek(4); // seek past header

	IBufferDataSource xfds(U8XFormPal, 1024);
	PaletteManager::get_instance()->load(PaletteManager::Pal_Game, *pf, xfds);
	delete pf;

	pout << "Load GameData" << Std::endl;
	GameData::get_instance()->loadU8Data();

	return true;
}

bool U8Game::startGame() {
	// NOTE: assumes the entire engine has been reset!

	pout << "Starting new Ultima 8 game." << Std::endl;

	ObjectManager *objman = ObjectManager::get_instance();

	// reserve a number of objids just in case we'll need them sometime
	for (uint16 i = 384; i < 512; ++i)
		objman->reserveObjId(i);

	// reserve ObjId 666 for the Guardian Bark hack
	objman->reserveObjId(666);

	IDataSource *saveds = FileSystem::get_instance()->ReadFile("@game/savegame/u8save.000");
	if (!saveds) {
		perr << "Unable to load savegame/u8save.000." << Std::endl;
		return false;
	}
	U8SaveFile *u8save = new U8SaveFile(saveds);

	IDataSource *nfd = u8save->getDataSource("NONFIXED.DAT");
	if (!nfd) {
		perr << "Unable to load savegame/u8save.000/NONFIXED.DAT." << Std::endl;
		return false;
	}
	World::get_instance()->loadNonFixed(nfd); // deletes nfd

	IDataSource *icd = u8save->getDataSource("ITEMCACH.DAT");
	if (!icd) {
		perr << "Unable to load savegame/u8save.000/ITEMCACH.DAT." << Std::endl;
		return false;
	}
	IDataSource *npcd = u8save->getDataSource("NPCDATA.DAT");
	if (!npcd) {
		perr << "Unable to load savegame/u8save.000/NPCDATA.DAT." << Std::endl;
		return false;
	}

	World::get_instance()->loadItemCachNPCData(icd, npcd); // deletes icd, npcd
	delete u8save;

	MainActor *av = getMainActor();
	assert(av);

	av->setName("Avatar"); // default name

	// avatar needs a backpack ... CONSTANTs and all that
	Item *backpack = ItemFactory::createItem(529, 0, 0, 0, 0, 0, 0, true);
	backpack->moveToContainer(av);

	World::get_instance()->switchMap(av->getMapNum());

	Ultima8Engine::get_instance()->setAvatarInStasis(true);

	return true;
}

bool U8Game::startInitialUsecode(int saveSlot) {
	Process *proc = new StartU8Process(saveSlot);
	Kernel::get_instance()->addProcess(proc);

	return true;
}


ProcId U8Game::playIntroMovie() {
	GameInfo *gameinfo = CoreApp::get_instance()->getGameInfo();
	char langletter = gameinfo->getLanguageFileLetter();
	if (!langletter) {
		perr << "U8Game::playIntro: Unknown language." << Std::endl;
		return 0;
	}

	Std::string filename = "@game/static/";
	filename += langletter;
	filename += "intro.skf";

	FileSystem *filesys = FileSystem::get_instance();
	IDataSource *skf = filesys->ReadFile(filename);
	if (!skf) {
		pout << "U8Game::playIntro: movie not found." << Std::endl;
		return 0;
	}

	RawArchive *flex = new RawArchive(skf);
	return MovieGump::U8MovieViewer(flex, true);
}

ProcId U8Game::playEndgameMovie() {
	Std::string filename = "@game/static/endgame.skf";
	FileSystem *filesys = FileSystem::get_instance();
	IDataSource *skf = filesys->ReadFile(filename);
	if (!skf) {
		pout << "U8Game::playEndgame: movie not found." << Std::endl;
		return 0;
	}

	RawArchive *flex = new RawArchive(skf);
	return MovieGump::U8MovieViewer(flex);
}

void U8Game::playCredits() {
	GameInfo *gameinfo = CoreApp::get_instance()->getGameInfo();
	char langletter = gameinfo->getLanguageFileLetter();
	if (!langletter) {
		perr << "U8Game::playCredits: Unknown language." << Std::endl;
		return;
	}
	Std::string filename = "@game/static/";
	filename += langletter;
	filename += "credits.dat";

	IDataSource *ids = FileSystem::get_instance()->ReadFile(filename);
	if (!ids) {
		perr << "U8Game::playCredits: error opening credits file: "
		     << filename << Std::endl;
		return;
	}
	Std::string text = getCreditText(ids);
	delete ids;

	MusicProcess *musicproc = MusicProcess::get_instance();
	if (musicproc) musicproc->playMusic(51); // CONSTANT!

	CreditsGump *gump = new CreditsGump(text);
	gump->InitGump(0);
	gump->SetFlagWhenFinished("quotes");
	gump->setRelativePosition(Gump::CENTER);
}

void U8Game::playQuotes() {
	Std::string filename = "@game/static/quotes.dat";

	IDataSource *ids = FileSystem::get_instance()->ReadFile(filename);
	if (!ids) {
		perr << "U8Game::playCredits: error opening credits file: "
		     << filename << Std::endl;
		return;
	}
	Std::string text = getCreditText(ids);
	delete ids;

	MusicProcess *musicproc = MusicProcess::get_instance();
	if (musicproc) musicproc->playMusic(113); // CONSTANT!

	Gump *gump = new CreditsGump(text, 80);
	gump->InitGump(0);
	gump->setRelativePosition(Gump::CENTER);
}


void U8Game::writeSaveInfo(ODataSource *ods) {
	MainActor *av = getMainActor();
	int32 x, y, z;

	const Std::string &avname = av->getName();
	const uint8 namelength = static_cast<uint8>(avname.size());
	ods->write1(namelength);
	for (unsigned int i = 0; i < namelength; ++i)
		ods->write1(static_cast<uint8>(avname[i]));

	av->getLocation(x, y, z);
	ods->write2(av->getMapNum());
	ods->write4(static_cast<uint32>(x));
	ods->write4(static_cast<uint32>(y));
	ods->write4(static_cast<uint32>(z));

	ods->write2(av->getStr());
	ods->write2(av->getInt());
	ods->write2(av->getDex());
	ods->write2(av->getHP());
	ods->write2(av->getMaxHP());
	ods->write2(av->getMana());
	ods->write2(av->getMaxMana());
	ods->write2(av->getArmourClass());
	ods->write2(av->getTotalWeight());

	for (unsigned int i = 1; i <= 6; i++) {
		uint16 objid = av->getEquip(i);
		Item *item = getItem(objid);
		if (item) {
			ods->write4(item->getShape());
			ods->write4(item->getFrame());
		} else {
			ods->write4(0);
			ods->write4(0);
		}
	}
}

Std::string U8Game::getCreditText(IDataSource *ids) {
	Std::string text;
	unsigned int size = ids->getSize();
	text.resize(size);
	for (unsigned int i = 0; i < size; ++i) {
		uint8 c = ids->read1();
		int x;
		switch (i) {
		case 0:
		case 1:
			x = 0;
			break;
		case 2:
			x = 0xE1;
			break;
		default:
			x = 0x20 * (i + 1) + (i >> 1);
			x += (i % 0x40) * ((i & 0xC0) >> 6) * 0x40;
			break;
		}
		char d = (c ^ x) & 0xFF;
		if (d == 0) d = '\n';
		text[i] = d;
	}

	return text;
}

} // End of namespace Ultima8
} // End of namespace Ultima
