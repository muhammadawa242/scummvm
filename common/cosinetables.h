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

#ifndef COMMON_COSINETABLES_H
#define COMMON_COSINETABLES_H

namespace Common {

class CosineTable {
public:
	/**
	 * Construct a cosine table with the specified bit precision
	 *
	 * @param bitPrecision Precision of the table, which must be in range [4, 16]
	 */
	CosineTable(int bitPrecision);
	~CosineTable();

	/**
	 * Get pointer to table.
	 *
	 * This table contains 2^bitPrecision/2 entries.
	 * Prefer to use at()
	 * The layout of this table is as follows:
	 * - Entries 0 up to (including) 2^bitPrecision/4:
	 *           cos(0) till (including) cos(1/2*pi)
	 * - Entries (excluding) 2^bitPrecision/4 up to 2^bitPrecision/2:
	 *           (excluding) cos(3/2*pi) till (excluding) cos(2*pi)
	 */
	const float *getTable() { return _table; }

	/**
	 * Returns cos(2*pi * index / 2^bitPrecision )
	 * Index must be in range [0,2^bitPrecision-1]
	 */
	float at(int index) const;

	/**
	 * Get bit precision
	 */
	int getBitPrecision() { return _bitPrecision; }

private:
	float *_table;
	int _bitPrecision;
	double _radResolution; // Smallest radian increment
	int _refSize; // _nPoints / 4
	int _nPoints; // range of operator[]
};

} // End of namespace Common

#endif // COMMON_COSINETABLES_H
