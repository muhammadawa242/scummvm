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

#ifndef SCUMM_COSTUME_H
#define SCUMM_COSTUME_H

#include "scumm/base-costume.h"

namespace Scumm {
class ClassicCostumeLoader : public BaseCostumeLoader {
public:
	int _id;
	const byte *_baseptr;
	const byte *_animCmds;
	const byte *_dataOffsets;
	const byte *_palette;
	const byte *_frameOffsets;
	byte _numColors;
	byte _numAnim;
	byte _format;
	bool _mirror;

	ClassicCostumeLoader(ScummEngine *vm) :
		BaseCostumeLoader(vm),
		_id(-1), _baseptr(0), _animCmds(0), _dataOffsets(0), _palette(0),
		_frameOffsets(0), _numColors(0), _numAnim(0), _format(0), _mirror(false) {}

	void loadCostume(int id) override;
	void costumeDecodeData(Actor *a, int frame, uint usemask) override;
	bool increaseAnims(Actor *a) override;

protected:
	bool increaseAnim(Actor *a, int slot);
};

class NESCostumeLoader : public BaseCostumeLoader {
public:
	int _id;
	const byte *_baseptr;
	const byte *_dataOffsets;
	byte _numAnim;

	NESCostumeLoader(ScummEngine *vm) : BaseCostumeLoader(vm), _id(0), _baseptr(nullptr), _dataOffsets(nullptr), _numAnim(0) {}
	void loadCostume(int id) override;
	void costumeDecodeData(Actor *a, int frame, uint usemask) override;
	bool increaseAnims(Actor *a) override;

protected:
	bool increaseAnim(Actor *a, int slot);
};

class V0CostumeLoader : public ClassicCostumeLoader {
public:
	V0CostumeLoader(ScummEngine *vm) : ClassicCostumeLoader(vm) {}
	void loadCostume(int id) override;
	void costumeDecodeData(Actor *a, int frame, uint usemask) override;
	bool increaseAnims(Actor *a) override;
	byte getFrame(Actor *a, int limb);

protected:
	bool increaseAnim(Actor *a, int limb);
};

class ClassicCostumeRenderer : public BaseCostumeRenderer {
protected:
	ClassicCostumeLoader _loaded;

	byte _scaleIndexX;						/* must wrap at 256 */
	byte _scaleIndexY;
	uint16 _palette[32];

public:
	ClassicCostumeRenderer(ScummEngine *vm) : BaseCostumeRenderer(vm), _loaded(vm), _scaleIndexX(0), _scaleIndexY(0) {
		memset(_palette, 0, sizeof(_palette));
	}

	void setPalette(uint16 *palette) override;
	void setFacing(const Actor *a) override;
	void setCostume(int costume, int shadow) override;

protected:
	byte drawLimb(const Actor *a, int limb) override;

	void proc3(ByleRLEData &v1);
	void proc3_ami(ByleRLEData &v1);

	void procC64(ByleRLEData &v1, int actor);

	void procPCEngine(ByleRLEData &v1);

	byte mainRoutine(int xmoveCur, int ymoveCur);
};

class NESCostumeRenderer : public BaseCostumeRenderer {
protected:
	NESCostumeLoader _loaded;

public:
	NESCostumeRenderer(ScummEngine *vm) : BaseCostumeRenderer(vm), _loaded(vm) {}

	void setPalette(uint16 *palette) override;
	void setFacing(const Actor *a) override;
	void setCostume(int costume, int shadow) override;

protected:
	byte drawLimb(const Actor *a, int limb) override;
};

#ifdef USE_RGB_COLOR
class PCEngineCostumeRenderer : public ClassicCostumeRenderer {
public:
	PCEngineCostumeRenderer(ScummEngine *vm) : ClassicCostumeRenderer(vm) {}

	void setPalette(uint16 *palette) override;
};
#endif

class V0CostumeRenderer : public BaseCostumeRenderer {
protected:
	V0CostumeLoader _loaded;

public:
	V0CostumeRenderer(ScummEngine *vm) : BaseCostumeRenderer(vm), _loaded(vm) {}

	void setPalette(uint16 *palette) override {}
	void setFacing(const Actor *a) override {}
	void setCostume(int costume, int shadow) override;

protected:
	byte drawLimb(const Actor *a, int limb) override;
};

} // End of namespace Scumm

#endif
