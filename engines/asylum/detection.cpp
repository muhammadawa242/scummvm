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

#include "engines/advancedDetector.h"
#include "base/plugins.h"

static const PlainGameDescriptor asylumGames[] = {
	{ "sanitarium", "Sanitarium" },
	{ 0, 0 }
};

namespace Asylum {

static const ADGameDescription gameDescriptions[] = {

	// Sanitarium - English Demo
	{ "sanitarium", "Demo", {
		{"SNTRM.DAT", 0, "6a8079e0b49affc99d148624fbb584a1", 326},
		{"RES.000", 0, "57446ce089c6f9decb7f3faf41d09edf", 9022},
		AD_LISTEND},
		Common::EN_ANY, Common::kPlatformWindows, ADGF_DEMO | ADGF_UNSTABLE, GUIO0()
	},

	{ "sanitarium", "Unpatched",{
		{"SNTRM.DAT", 0, "7cfcc457c1f579fbf9878ac175d29374", 8930},
		{"RES.000", 0, "4d13f1412f9e7dd3eaf0a58f0e00e662", 272057},
		{"SCN.006", 0, "71a5f49cbda597a11e877589075e27b5", 2918330},
		AD_LISTEND},
		Common::EN_ANY, Common::kPlatformWindows, ADGF_UNSTABLE, GUIO0()
	},

	// Level 2 Lockout Bug patch was applied
	{ "sanitarium", "Patched", {
		{"SNTRM.DAT", 0, "7cfcc457c1f579fbf9878ac175d29374", 8930},
		{"RES.000", 0, "4d13f1412f9e7dd3eaf0a58f0e00e662", 272057},
		{"SCN.006", 0, "3a5b54da08198012dc0614114782d5fb", 2918330},
		 AD_LISTEND}, Common::EN_ANY, Common::kPlatformWindows, ADGF_UNSTABLE, GUIO0()
	},

	{ "sanitarium", "GOG.com", {
		{"SNTRM.DAT", 0, "7cfcc457c1f579fbf9878ac175d29374", 8930},
		{"RES.000", 0, "f58f8dc3e63663f174977d359e11132c", 272057},
		{"SCN.006", 0, "3a5b54da08198012dc0614114782d5fb", 2918330},
		AD_LISTEND},
		Common::EN_ANY, Common::kPlatformWindows, ADGF_UNSTABLE, GUIO0()
	},

	{ "sanitarium", "French Version", {
		{"SNTRM.DAT", 0, "e09a12543c6ede1727c8ecffb74e7fd2", 8930},
		{"RES.000", 0, "2a4677ee3fd7bfa3161e16cd59371238", 277931},
		{"SCN.006", 0, "3a5b54da08198012dc0614114782d5fb", 2918330},
		AD_LISTEND},
		Common::FR_FRA, Common::kPlatformWindows, ADGF_UNSTABLE, GUIO0()
	},

	{ "sanitarium", "Russian Version", {
		{"SNTRM.DAT", 0, "7cfcc457c1f579fbf9878ac175d29374", 8930},
		{"RES.000", 0, "1f8a262bf8b3035bd3cfda24068c4651", 263624},
		{"SCN.006", 0, "3a5b54da08198012dc0614114782d5fb", 2918330},
		AD_LISTEND},
		Common::RU_RUS, Common::kPlatformWindows, ADGF_UNSTABLE, GUIO0()
	},

	AD_TABLE_END_MARKER};

static const ADFileBasedFallback fileBasedFallback[] = {
	{ &Asylum::gameDescriptions[0], { "SNTRM.DAT", 0 } }, // default to english version
	{ 0, {0} } };


static const char *directoryGlobs[] = {
	"Data",
	0
};

} // End of namespace Asylum


class AsylumMetaEngineStatic : public AdvancedMetaEngineStatic {
public:
	AsylumMetaEngineStatic() : AdvancedMetaEngineStatic(Asylum::gameDescriptions, sizeof(ADGameDescription), asylumGames) {
		_md5Bytes = 0;
		_maxScanDepth = 2;
		_directoryGlobs = Asylum::directoryGlobs;
	}

	ADDetectedGame fallbackDetect(const FileMap &allFiles, const Common::FSList &fslist) const override {
		return detectGameFilebased(allFiles, Asylum::fileBasedFallback);
	}

	const char *getEngineId() const override {
		return "asylum";
	}

	const char *getName() const override {
		return "Asylum";
	}

	const char *getOriginalCopyright() const override {
		return "Sanitarium (c) ASC Games";
	}
};

REGISTER_PLUGIN_STATIC(ASYLUM_DETECTION, PLUGIN_TYPE_METAENGINE, AsylumMetaEngineStatic);
