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

#ifndef PRINCE_ARCHIVE_H
#define PRINCE_ARCHIVE_H

#include "common/archive.h"
#include "common/hashmap.h"
#include "common/hash-str.h"

namespace Prince {

class PtcArchive : public Common::Archive {
public:
	PtcArchive();
	~PtcArchive() override;

	bool open(const Common::Path &filename);
	bool openTranslation(const Common::Path &filename);
	void close();
	bool isOpen() const { return _stream != 0; }

	// Common::Archive API implementation
	bool hasFile(const Common::Path &path) const override;
	int listMembers(Common::ArchiveMemberList &list) const override;
	const Common::ArchiveMemberPtr getMember(const Common::Path &path) const override;
	Common::SeekableReadStream *createReadStreamForMember(const Common::Path &path) const override;

private:
	struct FileEntry {
		uint32 _offset;
		uint32 _size;
	};

	Common::SeekableReadStream *_stream;

	typedef Common::HashMap<Common::String, FileEntry, Common::IgnoreCase_Hash, Common::IgnoreCase_EqualTo> FileMap;
	FileMap _items;
};

} // End of namespace Prince

#endif
