/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2001-2005 The ScummVM project
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */


#include "stdafx.h"

#include "common/config-manager.h"

#include "scumm/actor.h"
#include "scumm/charset.h"
#include "scumm/intern.h"
#include "scumm/object.h"
#include "scumm/resource.h"
#include "scumm/resource_v7he.h"
#include "scumm/scumm.h"
#include "scumm/sound.h"

namespace Scumm {

#define OPCODE(x)	_OPCODE(ScummEngine_v90he, x)

void ScummEngine_v90he::setupOpcodes() {
	static const OpcodeEntryV90he opcodes[256] = {
		/* 00 */
		OPCODE(o6_pushByte),
		OPCODE(o6_pushWord),
		OPCODE(o72_pushDWord),
		OPCODE(o6_pushWordVar),
		/* 04 */
		OPCODE(o72_addMessageToStack),
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		OPCODE(o6_wordArrayRead),
		/* 08 */
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		OPCODE(o90_dup_n),
		OPCODE(o6_wordArrayIndexedRead),
		/* 0C */
		OPCODE(o6_dup),
		OPCODE(o6_not),
		OPCODE(o6_eq),
		OPCODE(o6_neq),
		/* 10 */
		OPCODE(o6_gt),
		OPCODE(o6_lt),
		OPCODE(o6_le),
		OPCODE(o6_ge),
		/* 14 */
		OPCODE(o6_add),
		OPCODE(o6_sub),
		OPCODE(o6_mul),
		OPCODE(o6_div),
		/* 18 */
		OPCODE(o6_land),
		OPCODE(o6_lor),
		OPCODE(o6_pop),
		OPCODE(o72_isAnyOf),
		/* 1C */
		OPCODE(o90_wizImageOps),
		OPCODE(o90_min),
		OPCODE(o90_max),
		OPCODE(o90_sin),
		/* 20 */
		OPCODE(o90_cos),
		OPCODE(o90_sqrt),
		OPCODE(o90_atan2),
		OPCODE(o90_getSegmentAngle),
		/* 24 */
		OPCODE(o90_getDistanceBetweenPoints),
		OPCODE(o90_getSpriteInfo),
		OPCODE(o90_setSpriteInfo),
		OPCODE(o90_getSpriteGroupInfo),
		/* 28 */
		OPCODE(o90_setSpriteGroupInfo),
		OPCODE(o90_getWizData),
		OPCODE(o90_getActorData),
		OPCODE(o90_startScriptUnk),
		/* 2C */
		OPCODE(o90_jumpToScriptUnk),
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		OPCODE(o90_floodState),
		/* 30 */
		OPCODE(o90_mod),
		OPCODE(o90_shl),
		OPCODE(o90_shr),
		OPCODE(o6_invalid),
		/* 34 */
		OPCODE(o90_findAllObjectsWithClassOf),
		OPCODE(o90_getPolygonOverlap),
		OPCODE(o90_cond),
		OPCODE(o90_dim2dim2Array),
		/* 38 */
		OPCODE(o90_redim2dimArray),
		OPCODE(o6_invalid),
		OPCODE(o90_sortArray),
		OPCODE(o6_invalid),
		/* 3C */
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		/* 40 */
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		OPCODE(o6_writeWordVar),
		/* 44 */
		OPCODE(o90_getObjectData),
		OPCODE(o80_loadSBNG),
		OPCODE(o80_getFileSize),
		OPCODE(o6_wordArrayWrite),
		/* 48 */
		OPCODE(o80_stringToInt),
		OPCODE(o80_getSoundVar),
		OPCODE(o80_localizeArrayToRoom),
		OPCODE(o6_wordArrayIndexedWrite),
		/* 4C */
		OPCODE(o6_invalid),
		OPCODE(o80_readConfigFile),
		OPCODE(o80_writeConfigFile),
		OPCODE(o6_wordVarInc),
		/* 50 */
		OPCODE(o72_resetCutscene),
		OPCODE(o6_invalid),
		OPCODE(o72_findObjectWithClassOf),
		OPCODE(o6_wordArrayInc),
		/* 54 */
		OPCODE(o72_getObjectImageX),
		OPCODE(o72_getObjectImageY),
		OPCODE(o72_captureWizImage),
		OPCODE(o6_wordVarDec),
		/* 58 */
		OPCODE(o72_getTimer),
		OPCODE(o72_setTimer),
		OPCODE(o72_getSoundElapsedTimeOfSound),
		OPCODE(o6_wordArrayDec),
		/* 5C */
		OPCODE(o6_if),
		OPCODE(o6_ifNot),
		OPCODE(o72_startScript),
		OPCODE(o6_startScriptQuick),
		/* 60 */
		OPCODE(o72_startObject),
		OPCODE(o72_drawObject),
		OPCODE(o72_printWizImage),
		OPCODE(o72_getArrayDimSize),
		/* 64 */
		OPCODE(o72_getNumFreeArrays),
		OPCODE(o6_stopObjectCode),
		OPCODE(o6_stopObjectCode),
		OPCODE(o6_endCutscene),
		/* 68 */
		OPCODE(o6_cutscene),
		OPCODE(o6_invalid),
		OPCODE(o6_freezeUnfreeze),
		OPCODE(o80_cursorCommand),
		/* 6C */
		OPCODE(o6_breakHere),
		OPCODE(o6_ifClassOfIs),
		OPCODE(o6_setClass),
		OPCODE(o6_getState),
		/* 70 */
		OPCODE(o80_setState),
		OPCODE(o6_setOwner),
		OPCODE(o6_getOwner),
		OPCODE(o6_jump),
		/* 74 */
		OPCODE(o70_startSound),
		OPCODE(o6_stopSound),
		OPCODE(o6_invalid),
		OPCODE(o6_stopObjectScript),
		/* 78 */
		OPCODE(o6_panCameraTo),
		OPCODE(o6_actorFollowCamera),
		OPCODE(o6_setCameraAt),
		OPCODE(o6_loadRoom),
		/* 7C */
		OPCODE(o6_stopScript),
		OPCODE(o6_walkActorToObj),
		OPCODE(o6_walkActorTo),
		OPCODE(o6_putActorAtXY),
		/* 80 */
		OPCODE(o6_putActorAtObject),
		OPCODE(o6_faceActor),
		OPCODE(o6_animateActor),
		OPCODE(o6_doSentence),
		/* 84 */
		OPCODE(o70_pickupObject),
		OPCODE(o6_loadRoomWithEgo),
		OPCODE(o6_invalid),
		OPCODE(o6_getRandomNumber),
		/* 88 */
		OPCODE(o6_getRandomNumberRange),
		OPCODE(o6_invalid),
		OPCODE(o6_getActorMoving),
		OPCODE(o6_isScriptRunning),
		/* 8C */
		OPCODE(o70_getActorRoom),
		OPCODE(o6_getObjectX),
		OPCODE(o6_getObjectY),
		OPCODE(o6_getObjectOldDir),
		/* 90 */
		OPCODE(o6_getActorWalkBox),
		OPCODE(o6_getActorCostume),
		OPCODE(o6_findInventory),
		OPCODE(o6_getInventoryCount),
		/* 94 */
		OPCODE(o90_getPaletteData),
		OPCODE(o6_beginOverride),
		OPCODE(o6_endOverride),
		OPCODE(o6_setObjectName),
		/* 98 */
		OPCODE(o6_isSoundRunning),
		OPCODE(o6_setBoxFlags),
		OPCODE(o6_invalid),
		OPCODE(o70_resourceRoutines),
		/* 9C */
		OPCODE(o72_roomOps),
		OPCODE(o72_actorOps),
		OPCODE(o90_paletteOps),
		OPCODE(o6_getActorFromXY),
		/* A0 */
		OPCODE(o70_findObject),
		OPCODE(o6_pseudoRoom),
		OPCODE(o6_getActorElevation),
		OPCODE(o6_getVerbEntrypoint),
		/* A4 */
		OPCODE(o72_arrayOps),
		OPCODE(o90_unknownA5),
		OPCODE(o80_drawBox),
		OPCODE(o6_pop),
		/* A8 */
		OPCODE(o6_getActorWidth),
		OPCODE(o60_wait),
		OPCODE(o6_getActorScaleX),
		OPCODE(o90_getActorAnimProgress),
		/* AC */
		OPCODE(o80_drawWizPolygon),
		OPCODE(o6_isAnyOf),
		OPCODE(o70_quitPauseRestart),
		OPCODE(o6_isActorInBox),
		/* B0 */
		OPCODE(o6_delay),
		OPCODE(o6_delaySeconds),
		OPCODE(o6_delayMinutes),
		OPCODE(o6_stopSentence),
		/* B4 */
		OPCODE(o6_printLine),
		OPCODE(o6_printCursor),
		OPCODE(o6_printDebug),
		OPCODE(o6_printSystem),
		/* B8 */
		OPCODE(o6_printActor),
		OPCODE(o6_printEgo),
		OPCODE(o72_talkActor),
		OPCODE(o72_talkEgo),
		/* BC */
		OPCODE(o72_dimArray),
		OPCODE(o6_stopObjectCode),
		OPCODE(o6_startObjectQuick),
		OPCODE(o6_startScriptQuick2),
		/* C0 */
		OPCODE(o72_dim2dimArray),
		OPCODE(o72_traceStatus),
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		/* C4 */
		OPCODE(o6_abs),
		OPCODE(o6_distObjectObject),
		OPCODE(o6_distObjectPt),
		OPCODE(o6_distPtPt),
		/* C8 */
		OPCODE(o72_kernelGetFunctions),
		OPCODE(o70_kernelSetFunctions),
		OPCODE(o6_delayFrames),
		OPCODE(o6_pickOneOf),
		/* CC */
		OPCODE(o6_pickOneOfDefault),
		OPCODE(o6_stampObject),
		OPCODE(o72_drawWizImage),
		OPCODE(o72_unknownCF),
		/* D0 */
		OPCODE(o6_getDateTime),
		OPCODE(o6_stopTalking),
		OPCODE(o6_getAnimateVariable),
		OPCODE(o6_invalid),
		/* D4 */
		OPCODE(o6_shuffle),
		OPCODE(o72_jumpToScript),
		OPCODE(o6_band),
		OPCODE(o6_bor),
		/* D8 */
		OPCODE(o6_isRoomScriptRunning),
		OPCODE(o60_closeFile),
		OPCODE(o72_openFile),
		OPCODE(o72_readFile),
		/* DC */
		OPCODE(o72_writeFile),
		OPCODE(o72_findAllObjects),
		OPCODE(o72_deleteFile),
		OPCODE(o60_rename),
		/* E0 */
		OPCODE(o80_unknownE0),
		OPCODE(o72_getPixel),
		OPCODE(o60_localizeArrayToScript),
		OPCODE(o80_pickVarRandom),
		/* E4 */
		OPCODE(o6_setBoxSet),
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		/* E8 */
		OPCODE(o6_invalid),
		OPCODE(o60_seekFilePos),
		OPCODE(o72_redimArray),
		OPCODE(o60_readFilePos),
		/* EC */
		OPCODE(o70_copyString),
		OPCODE(o70_getStringWidth),
		OPCODE(o70_getStringLen),
		OPCODE(o70_appendString),
		/* F0 */
		OPCODE(o70_concatString),
		OPCODE(o70_compareString),
		OPCODE(o72_checkGlobQueue),
		OPCODE(o72_readINI),
		/* F4 */
		OPCODE(o72_writeINI),
		OPCODE(o70_getStringLenForWidth),
		OPCODE(o70_getCharIndexInString),
		OPCODE(o6_invalid),
		/* F8 */
		OPCODE(o72_getResourceSize),
		OPCODE(o72_setFilePath),
		OPCODE(o72_setWindowCaption),
		OPCODE(o70_polygonOps),
		/* FC */
		OPCODE(o70_polygonHit),
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
		OPCODE(o6_invalid),
	};

	_opcodesV90he = opcodes;
}

void ScummEngine_v90he::executeOpcode(byte i) {
	OpcodeProcV90he op = _opcodesV90he[i].proc;
	(this->*op) ();
}

const char *ScummEngine_v90he::getOpcodeDesc(byte i) {
	return _opcodesV90he[i].desc;
}

void ScummEngine_v90he::o90_dup_n() {
	int num;
	int args[16];

	push(fetchScriptWord());
	num = getStackList(args, ARRAYSIZE(args));

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < num; j++)
			push(args[j]);
	}
}

void ScummEngine_v90he::o90_min() {
	int a = pop();
	int b = pop();

	if (b < a) {
		push(b);
	} else {
		push(a);
	}
}

void ScummEngine_v90he::o90_max() {
	int a = pop();
	int b = pop();

	if (b > a) {
		push(b);
	} else {
		push(a);
	}
}

void ScummEngine_v90he::o90_sin() {
	double a = pop() * PI / 180.;
	push((int)(sin(a) * 100000));	
}

void ScummEngine_v90he::o90_cos() {
	double a = pop() * PI / 180.;
	push((int)(cos(a) * 100000));	
}

void ScummEngine_v90he::o90_sqrt() {
	int i = pop();
	if (i < 2) {
		push(i);
	} else {
		push((int)sqrt((double)(i + 1)));
	}
}

void ScummEngine_v90he::o90_atan2() {
	int y = pop();
	int x = pop();
	int a = (int)(atan2((double)y, (double)x) * 180. / PI);
	if (a < 0) {
		a += 360;
	}
	push(a);
}

void ScummEngine_v90he::o90_getSegmentAngle() {
	int y1 = pop();
	int x1 = pop();
	int dy = y1 - pop();
	int dx = x1 - pop();
	int a = (int)(atan2((double)dy, (double)dx) * 180. / PI);
	if (a < 0) {
		a += 360;
	}
	push(a);
}

void ScummEngine_v90he::o90_getActorData() {
	Actor *a;

	int subOp = pop();
	int val = pop();
	int act = pop();

	a = derefActorSafe(act, "o90_getActorData");

	switch (subOp) {
	case 1:
		push(a->isUserConditionSet(val));
		break;
	case 2:
		// Get actor limb?
		checkRange(15, 0, val, "Limb %d out of range");
		push(0);
		break;
	case 3:
		push(a->getAnimSpeed());
		break;
	case 4:
		push(a->_shadowMode);
		break;
	case 5:
		push(a->_layer);
		break;
	case 6:
		push(a->_hePaletteNum);
		break;
	default:
		error("o90_getActorData: Unknown actor property %d", subOp);
	}
}

void ScummEngine_v90he::o90_startScriptUnk() {
	int args[25];
	int script, cycle;
	byte flags;

	getStackList(args, ARRAYSIZE(args));
	cycle = pop();
	script = pop();
	flags = fetchScriptByte();
	runScript(script, (flags == 199 || flags == 200), (flags == 195 || flags == 200), args, cycle);
}

void ScummEngine_v90he::o90_jumpToScriptUnk() {
	int args[25];
	int script, cycle;
	byte flags;

	getStackList(args, ARRAYSIZE(args));
	cycle = pop();
	script = pop();
	flags = fetchScriptByte();
	stopObjectCode();
	runScript(script, (flags == 199 || flags == 200), (flags == 195 || flags == 200), args, cycle);
}

void ScummEngine_v90he::o90_wizImageOps() {
	int a, b;
	int subOp = fetchScriptByte();
	subOp -= 46;

	switch (subOp) {
	case -14: // HE99+
		_wizParams.processFlags |= kWPFUseDefImgWidth;
		_wizParams.resDefImgW = pop();
		break;
	case -13: // HE99+
		_wizParams.processFlags |= kWPFUseDefImgHeight;
		_wizParams.resDefImgH = pop();
		break;
	case 0:
		// Dummy case
		pop();
		break;
	case 1:
		_wizParams.box.bottom = pop();
		_wizParams.box.right = pop();
		_wizParams.box.top = pop();
		_wizParams.box.left = pop();
		break;
	case 2:
		_wizParams.processMode = 1;
		break;
	case 3:
		_wizParams.processFlags |= kWPFUseFile;
		_wizParams.processMode = 3;
		copyScriptString(_wizParams.filename);
		break;
	case 4:
		_wizParams.processFlags |= kWPFUseFile;
		_wizParams.processMode = 4;
		copyScriptString(_wizParams.filename);
		_wizParams.unk_14C = pop();
		break;
	case 5:
		_wizParams.processFlags |= 0x300;
		_wizParams.processMode = 2;
		_wizParams.box.bottom = pop();
		_wizParams.box.right = pop();
		_wizParams.box.top = pop();
		_wizParams.box.left = pop();
		_wizParams.compType = pop();
		break;
	case 6:
		_wizParams.processFlags |= kWPFNewState;
		_wizParams.img.state = pop();
		break;
	case 7:
		_wizParams.processFlags |= kWPFRotate;
		_wizParams.angle = pop();
		break;
	case 8:
		_wizParams.processFlags |= kWPFNewFlags;
		_wizParams.img.flags = pop();
		break;
	case 10:
		_wizParams.img.flags = pop();
		_wizParams.img.state = pop();
		_wizParams.img.y1 = pop();
		_wizParams.img.x1 = pop();
		_wizParams.img.resNum = pop();
		displayWizImage(&_wizParams.img);
		break;
	case 11:
		_wizParams.img.resNum = pop();
		_wizParams.processMode = 0;
		_wizParams.processFlags = 0;
		_wizParams.remapNum = 0;
		_wizParams.img.flags = 0;
		break;
	case 16: // HE99+
		_wizParams.processFlags |= 0x80000;
		_wizParams.unk_178  = pop();
		break;
	case 19:
		_wizParams.processFlags |= 1;
		_wizParams.img.y1 = pop();
		_wizParams.img.x1 = pop();
		break;
	case 20:
	case 203: // HE98+
		b = pop();
		a = pop();
		_wizParams.processFlags |= 0x40;
		_wizParams.processMode = 6;
		if (_wizParams.remapNum == 0) {
			memset(_wizParams.remapIndex, 0, sizeof(_wizParams.remapIndex));
		} else {
			assert(_wizParams.remapNum < ARRAYSIZE(_wizParams.remapIndex));
			_wizParams.remapIndex[_wizParams.remapNum] = a;
			_wizParams.remapColor[a] = b;
			++_wizParams.remapNum;
		}
		break;
	case 21:
		_wizParams.processFlags |= kWPFClipBox;
		_wizParams.box.bottom = pop();
		_wizParams.box.right = pop();
		_wizParams.box.top = pop();
		_wizParams.box.left = pop();
		break;
	case 40: // HE99+
		_wizParams.processFlags |= 0x8000;
		_wizParams.unk_174 = pop();
		break;
	case 46:
		_wizParams.processFlags |= kWPFZoom;
		_wizParams.zoom = pop();
		break;
	case 52:
		_wizParams.processFlags |= 4;
		_wizParams.unk_15C = pop();
		break;
	case 85: // HE99+
		_wizParams.processFlags |= 0x1102;
		_wizParams.processMode = 7;
		_wizParams.unk_164 = pop();
		_wizParams.unk_160 = pop();
		_wizParams.compType = pop();
		break;
	case 87: // HE99+
		_wizParams.processFlags |= 0x60000;
		_wizParams.processMode = 9;
		_wizParams.fillColor = pop();
		_wizParams.box2.bottom = pop();
		_wizParams.box2.right = pop();
		_wizParams.box2.top = pop();
		_wizParams.box2.left = pop();
		break;
	case 88: // HE99+
		_wizParams.processFlags |= 0x60000;
		_wizParams.processMode = 10;
		_wizParams.fillColor = pop();
		_wizParams.box2.bottom = pop();
		_wizParams.box2.right = pop();
		_wizParams.box2.top = pop();
		_wizParams.box2.left = pop();
		break;
	case 89: // HE99+
		_wizParams.processFlags |= 0x60000;
		_wizParams.processMode = 11;
		_wizParams.fillColor = pop();
		_wizParams.box2.top = _wizParams.box2.bottom = pop();
		_wizParams.box2.left = _wizParams.box2.right = pop();
		break;
	case 90: // HE99+
		_wizParams.processFlags |= 0x60000;
		_wizParams.processMode = 12;
		_wizParams.fillColor = pop();
		_wizParams.box2.top = _wizParams.box2.bottom = pop();
		_wizParams.box2.left = _wizParams.box2.right = pop();
		break;
	case 91: // HE99+
		_wizParams.processFlags |= 0x10000;
		_wizParams.unk_380 = pop();
		break;
	case 108:
		_wizParams.processFlags |= kWPFSetPos;
		_wizParams.img.y1 = pop();
		_wizParams.img.x1 = pop();
		break;
	case 171: // HE99+
		_wizParams.processMode = 8;
		break;
	case 200:
		_wizParams.processFlags |= kWPFNewFlags | kWPFSetPos | 2;
		_wizParams.img.flags |= kWIFIsPolygon;
		_wizParams.unk_160 = _wizParams.img.y1 = _wizParams.img.x1 = pop();
		break;
	case 209:
		if (_wizParams.img.resNum)
			processWizImage(&_wizParams);
		break;
	default:
		error("o90_wizImageOps: unhandled case %d", subOp);
	}

	debug(1,"o90_wizImageOps stub (%d)", subOp);
}

void ScummEngine_v90he::o90_getDistanceBetweenPoints() {
	byte subOp = fetchScriptByte();
	int x1, y1, z1, x2, y2, z2, dx, dy, dz, d;

	switch (subOp) {
	case 23: // HE100
	case 28:
		y2 = pop();
		x2 = pop();
		y1 = pop();
		x1 = pop();
		dx = x2 - x1;
		dy = y2 - y1;
		d = dx * dx + dy * dy;
		if (d < 2) {
			push(d);
		} else {
			push((int)sqrt((double)(d + 1)));
		}
		break;
	case 24: // HE100
	case 29:
		z2 = pop();
		y2 = pop();
		x2 = pop();
		z1 = pop();
		y1 = pop();
		x1 = pop();
		dx = x2 - x1;
		dy = y2 - y1;
		dz = z2 - z1;
		d = dx * dx + dy * dy + dz * dz;
		if (d < 2) {
			push(d);
		} else {
			push((int)sqrt((double)(d + 1)));
		}		
		break;
	default:
		error("o90_getDistanceBetweenPoints: Unknown case %d", subOp);
	}
}

void ScummEngine_v90he::o90_getSpriteInfo() {
	int args[16];
	int spriteId, flags, c, d, e, f;
	int32 a, b;

	byte subOp = fetchScriptByte();
	subOp -= 30;

	debug(0,"o90_getSpriteInfo (%d)", subOp);
	switch (subOp) {
	case 0:
		spriteId = pop();
		if (spriteId) {
			spriteInfoGet_tx_ty(spriteId, a, b);
			push(a);
		} else {
			push(0);
		}
		break;
	case 1:
		spriteId = pop();
		if (spriteId) {
			spriteInfoGet_tx_ty(spriteId, a, b);
			push(b);
		} else {
			push(0);
		}
		break;
	case 2:
		spriteId = pop();
		if (spriteId) {
			getSpriteImageDim(spriteId, a, b);
			push(a);
		} else {
			push(0);
		}
		break;
	case 3:
		spriteId = pop();
		if (spriteId) {
			getSpriteImageDim(spriteId, a, b);
			push(b);
		} else {
			push(0);
		}
		break;
	case 4:
		spriteId = pop();
		if (spriteId) {
			spriteInfoGet_dx_dy(spriteId, a, b);
			push(a);
		} else {
			push(0);
		}
		break;
	case 5:
		spriteId = pop();
		if (spriteId) {
			spriteInfoGet_dx_dy(spriteId, a, b);
			push(b);
		} else {
			push(0);
		}
		break;
	case 6:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_wizSize(spriteId));
		else
			push(0);
		break;
	case 7:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_groupNum(spriteId));
		else
			push(0);
		break;
	case 8:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_grp_tx(spriteId));
		else
			push(0);
		break;
	case 9:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_grp_ty(spriteId));
		else
			push(0);
		break;
	case 12:
		flags = pop();
		spriteId = pop();
		if (spriteId) {
			switch(flags) {
			case 0:
				push(spriteInfoGet_flagXFlipped(spriteId));
				break;
			case 1:
				push(spriteInfoGet_flagYFlipped(spriteId));
				break;
			case 2:
				push(spriteInfoGet_flagActive(spriteId));
				break;
			case 3:
				push(spriteInfoGet_flags_13(spriteId));
				break;
			case 4:
				push(spriteInfoGet_flags_20(spriteId));
				break;
			default:
				push(0);
			}
		} else {
			push(0);
		}
		break;
	case 13:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_zorderPriority(spriteId));
		else
			push(0);
		break;
	case 15:
		if (_heversion == 99) {
			flags = getStackList(args, ARRAYSIZE(args));
			c = pop();
			d = pop();
			e = pop();
			f = pop();
			push(findSpriteWithClassOf(f, e, d, c, flags, args));
		} else if (_heversion == 98) {
			c = pop();
			d = pop();
			e = pop();
			f = pop();
			push(findSpriteWithClassOf(f, e, d, c, 0, 0));
		} else {
			d = pop();
			e = pop();
			f = pop();
			push(findSpriteWithClassOf(f, e, d, 0, 0, 0));
		}
		break;
	case 22:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_resState(spriteId));
		else
			push(0);
		break;
	case 32:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_field_7C(spriteId));
		else
			push(0);
		break;
	case 33:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_resId(spriteId));
		else
			push(0);
		break;
	case 38:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_flagHasImage(spriteId));
		else
			push(1);
		break;
	case 52:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_flags_22(spriteId));
		else
			push(0);
		break;
	case 56:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_field_14(spriteId));
		else
			push(0);
		break;
	case 62:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_zoom(spriteId));
		else
			push(0);
		break;
	case 67:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_delayAmount(spriteId));
		else
			push(1);
		break;
	case 68:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_field_54(spriteId));
		else
			push(0);
		break;
	case 94:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_flags_23(spriteId));
		else
			push(0);
		break;
	case 95:
		flags = getStackList(args, ARRAYSIZE(args));
		spriteId = pop();
		if (spriteId) {
			if (flags)
				push(spriteInfoGet_classFlagsAnd(spriteId, flags, args));
			else
				push(spriteInfoGet_classFlags(spriteId, -1));
		} else {
			push(0);
		}
		break;
	case 109:
		flags = pop();
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_field_88(spriteId, flags));
		else
			push(0);
		break;
	case 110:
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_field_80(spriteId));
		else
			push(0);
		break;
	case 168:
		pop();
		spriteId = pop();
		if (spriteId)
			push(spriteInfoGet_field_44(spriteId));
		else
			push(0);
		break;
	default:
		error("o90_getSpriteInfo: Unknown case %d", subOp);
	}
}

void ScummEngine_v90he::o90_setSpriteInfo() {
	int args[16];
	int spriteId;
	int32 tmp[2];
	static int storedFields[2];
	int n;

	byte subOp = fetchScriptByte();
	subOp -= 34;

	debug(0,"o90_setSpriteInfo (%d)", subOp);
	switch (subOp) {
	case 0:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++) {
			spriteInfoGet_dx_dy(spriteId, tmp[0], tmp[1]);
			storedFields[0] = tmp[0];
			spriteInfoSet_dx_dy(spriteId, args[0], tmp[1]);
		}
		break;
	case 1:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++) {
			spriteInfoGet_dx_dy(spriteId, tmp[0], tmp[1]);
			storedFields[1] = tmp[1];
			spriteInfoSet_dx_dy(spriteId, tmp[0], args[0]);
		}
		break;
	case 3:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_groupNum(spriteId, args[0]);
		break;
	case 8:
		args[1] = pop();
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			switch(args[1]) {
			case 0:
				spriteInfoSet_flagXFlipped(spriteId, args[0]);
				break;
			case 1:
				spriteInfoSet_flagYFlipped(spriteId, args[0]);
				break;
			case 2:
				spriteInfoSet_flagActive(spriteId, args[0]);
				break;
			case 3:
				spriteInfoSet_flag13(spriteId, args[0]);
				break;
			case 4:
				spriteInfoSet_flag20(spriteId, args[0]);
				break;
			default:
				break;
			}
		break;
	case 9:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_zorderPriority(spriteId, args[0]);
		break;
	case 10:
		args[1] = pop();
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_Inc_tx_ty(spriteId, args[0], args[1]);
		break;
	case 18:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_resState(spriteId, args[0]);
		break;
	case 19:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_rotAngle(spriteId, args[0]);
		break;
	case 23:
		if (_gameId == GID_FREDDI4 || _heversion >= 99) {
			_curMaxSpriteId = pop();
			_curSpriteId = pop();
			
			if (_curSpriteId > _curMaxSpriteId)
				SWAP(_curSpriteId, _curMaxSpriteId);
		} else {
			_curSpriteId = pop();
			_curMaxSpriteId = _curSpriteId; // to make all functions happy
		}
		break;
	case 28: // HE99+
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_field_7C(spriteId, args[0]);
		break;
	case 29:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteAddImageToList(spriteId, 1, &args[0]);
		break;
	case 31:
		args[1] = pop();
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_tx_ty(spriteId, args[0], args[1]);
		break;
	case 34:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_flagHasImage(spriteId, args[0]);
		break;
	case 43:
		args[1] = pop();
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_dx_dy(spriteId, args[0], args[1]);
		break;
	case 48:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_flag22(spriteId, args[0]);
		break;
	case 52: // HE 98+
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_field_14(spriteId, args[0]);
		break;
	case 58: // HE 99+
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_zoom(spriteId, args[0]);
		break;
	case 63: // HE 98+
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_delay(spriteId, args[0]);
		break;
	case 64:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_field_54(spriteId, args[0]);
		break;
	case 90:
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_flag23(spriteId, args[0]);
		break;
	case 91:
		n = getStackList(args, ARRAYSIZE(args));
		if (_curSpriteId != 0 && _curMaxSpriteId != 0 && n != 0) {
			int *p = &args[n - 1];
			do {
				int code = *p;
				if (code == 0) {
					for (int i = _curSpriteId; i <= _curMaxSpriteId; ++i) {
						spriteInfoSet_resetClassFlags(i);					
					}
				} else if (code & 0x80) {
					for (int i = _curSpriteId; i <= _curMaxSpriteId; ++i) {
						spriteInfoSet_setClassFlag(i, code & 0x7F, 1);
					}
				} else {
					for (int i = _curSpriteId; i <= _curMaxSpriteId; ++i) {
						spriteInfoSet_setClassFlag(i, code & 0x7F, 0);
					}
				}
				--p;
			} while (--n);
		}
		break;
	case 105: // HE 99+
		args[1] = pop();
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_field_88(spriteId, args[0], args[1]);
		break;
	case 106: // HE 99+
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_field_80(spriteId, args[0]);
		break;
	case 124:
		spritesResetTables(true);
		break;
	case 164:
		args[1] = pop();
		args[0] = pop();
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_field_44(spriteId, args[0], args[1]);
		break;
	case 183:
		if (_curSpriteId > _curMaxSpriteId)
			break;
		spriteId = _curSpriteId;
		if (!spriteId)
			spriteId++;

		for (; spriteId <= _curMaxSpriteId; spriteId++)
			spriteInfoSet_resetSprite(spriteId);
		break;
	default:
		error("o90_setSpriteInfo: Unknown case %d", subOp);
	}
}

void ScummEngine_v90he::o90_getSpriteGroupInfo() {
	int32 tx, ty;
	int spriteGroupId, type;

	byte subOp = fetchScriptByte();

	debug(0,"o90_getSpriteGroupInfo (%d)", subOp);
	switch (subOp) {
	case 8: // HE 99+
		spriteGroupId = pop();
		if (spriteGroupId)
			push(spriteGroupGet_allocateGroupSpritesList(spriteGroupId));
		else
			push(0);
		break;
	case 30:
		spriteGroupId = pop();
		if (spriteGroupId) {
			spriteGroupGet_tx_ty(spriteGroupId, tx, ty);
			push(tx);
		} else {
			push(0);
		}
		break;
	case 31:
		spriteGroupId = pop();
		if (spriteGroupId) {
			spriteGroupGet_tx_ty(spriteGroupId, tx, ty);
			push(ty);
		} else {
			push(0);
		}
		break;
	case 42: // HE 99+
		type = pop();
		spriteGroupId = pop();
		if (spriteGroupId) {
			switch(type) {
			case 0:
				push(spriteGroupGet_scale_x_ratio_mul(spriteGroupId));
				break;
			case 1:
				push(spriteGroupGet_scale_x_ratio_div(spriteGroupId));
				break;
			case 2:
				push(spriteGroupGet_scale_y_ratio_mul(spriteGroupId));
				break;
			case 3:
				push(spriteGroupGet_scale_y_ratio_div(spriteGroupId));
				break;
			default:
				push(0);
			}
		} else {
			push(0);
		}
		break;
	case 43:
		spriteGroupId = pop();
		if (spriteGroupId)
			push(spriteGroupGet_zorderPriority(spriteGroupId));
		else
			push(0);
		break;
	case 63: // HE 99+
		spriteGroupId = pop();
		if (spriteGroupId)
			push(spriteGroupGet_field_20(spriteGroupId));
		else
			push(0);
		break;
	case 139: // HE 99+
		// dummy case
		pop();
		pop();
		push(0);
		break;
	default:
		error("o90_getSpriteGroupInfo: Unknown case %d", subOp);
	}
}

void ScummEngine_v90he::o90_setSpriteGroupInfo() {
	int type, value1, value2, value3, value4;

	byte subOp = fetchScriptByte();
	subOp -= 37;

	debug(0,"o90_setSpriteGroupInfo (%d)", subOp);
	switch (subOp) {
	case 0:
		type = pop() - 1;
		switch (type) {
		case 0:
			value2 = pop();
			value1 = pop();
			if (!_curSpriteGroupId)
				break;

			spriteGroupSet_case0_0(_curSpriteGroupId, value1, value2);
			break;
		case 1:
			value1 = pop();
			if (!_curSpriteGroupId)
				break;

			spriteGroupSet_case0_1(_curSpriteGroupId, value1);
			break;
		case 2:
			value1 = pop();
			if (!_curSpriteGroupId)
				break;

			spriteGroupSet_case0_2(_curSpriteGroupId, value1);
			break;
		case 3:
			value1 = pop();
			if (!_curSpriteGroupId)
				break;

			spriteGroupSet_case0_3(_curSpriteGroupId, value1);
			break;
		case 4:
			if (!_curSpriteGroupId)
				break;

			spriteGroupSet_case0_4(_curSpriteGroupId);
			break;
		case 5:
			value1 = pop();
			if (!_curSpriteGroupId)
				break;

			spriteGroupSet_case0_5(_curSpriteGroupId, value1);
			break;
		case 6:
			value1 = pop();
			if (!_curSpriteGroupId)
				break;

			spriteGroupSet_case0_6(_curSpriteGroupId, value1);
			break;
		case 7:
			value1 = pop();
			if (!_curSpriteGroupId)
				break;

			spriteGroupSet_case0_7(_curSpriteGroupId, value1);
			break;
		default:
			error("o90_setSpriteGroupInfo subOp 0: Unknown case %d", subOp);
		}
		break;
	case 5:
		type = pop();
		value1 = pop();
		if (!_curSpriteGroupId)
			break;

		switch (type) {
		case 0:
			spriteGroupSet_scale_x_ratio_mul(_curSpriteGroupId, value1);
			break;
		case 1:
			spriteGroupSet_scale_x_ratio_div(_curSpriteGroupId, value1);
			break;
		case 2:
			spriteGroupSet_scale_y_ratio_mul(_curSpriteGroupId, value1);
			break;
		case 3:
			spriteGroupSet_scale_y_ratio_div(_curSpriteGroupId, value1);
			break;
		default:
			error("o90_setSpriteGroupInfo subOp 5: Unknown case %d", subOp);
		}
		break;
	case 6:
		value1 = pop();
		if (!_curSpriteGroupId)
			break;

		spriteGroupSet_zorderPriority(_curSpriteGroupId, value1);
		break;
	case 7:
		value2 = pop();
		value1 = pop();
		if (!_curSpriteGroupId)
			break;

		spriteGroupSet_inc_tx_ty(_curSpriteGroupId, value1, value2);
		break;
	case 20:
		_curSpriteGroupId = pop();
		break;
	case 26:
		value1 = pop();
		if (!_curSpriteGroupId)
			break;

		spriteGroupSet_field_20(_curSpriteGroupId, value1);
		break;
	case 28:
		value2 = pop();
		value1 = pop();
		if (!_curSpriteGroupId)
			break;

		spriteGroupSet_tx_ty(_curSpriteGroupId, value1, value2);
		break;
	case 30:
		value4 = pop();
		value3 = pop();
		value2 = pop();
		value1 = pop();
		if (!_curSpriteGroupId)
			break;

		spriteGroupSet_bbox(_curSpriteGroupId, value1, value2, value3, value4);
		break;
	case 56:
		if (!_curSpriteGroupId)
			break;

		spriteGroupSet_flagClipBoxAnd(_curSpriteGroupId);
		break;
	case 180:
		if (!_curSpriteGroupId)
			break;

		spritesResetGroup(_curSpriteGroupId);
		break;
	default:
		error("o90_setSpriteGroupInfo: Unknown case %d", subOp);
	}
}

void ScummEngine_v90he::o90_getWizData() {
	int state, resId;
	int32 w, h;
	int16 x, y;

	byte subOp = fetchScriptByte();
	subOp -= 30;

	switch (subOp) {
	case 0:
		state = pop();
		resId = pop();
		loadImgSpot(resId, state, x, y);
		push(x);
		break;
	case 1:
		state = pop();
		resId = pop();
		loadImgSpot(resId, state, x, y);
		push(y);
		break;
	case 2:
		state = pop();
		resId = pop();
		getWizImageDim(resId, state, w, h);
		push(w);
		break;
	case 3:
		state = pop();
		resId = pop();
		getWizImageDim(resId, state, w, h);
		push(h);
		break;
	case 6:
		resId = pop();
		push(getWizImageStates(resId));
		break;
	case 15:
		y = pop();
		x = pop();
		state = pop();
		resId = pop();
		push(isWizPixelNonTransparent(rtImage, resId, state, x, y, 0));
		break;
	case 36:
		y = pop();
		x = pop();
		state = pop();
		resId = pop();
		push(getWizPixelColor(rtImage, resId, state, x, y, 0));
		break;
	case 100:
		h = pop();
		w = pop();
		y = pop();
		x = pop();
		state = pop();
		resId = pop();
		if (x == -1 && y == -1 && w == -1 && h == -1) {
			getWizImageDim(resId, state, w, h);
			x = 0;
			y = 0;
		}		
		push(computeWizHistogram(resId, state, x, y, w, h));		
		break;
	case 109:
		pop();
		pop();
		push(0);
		break;		
	default:
		error("o90_getWizData: Unknown case %d", subOp);
	}
}

void ScummEngine_v90he::o90_floodState() {
	byte subOp = fetchScriptByte();
	subOp -= 54;

	switch (subOp) {
	case 0:
		_floodStateParams.field_1C = pop();
		break;
	case 3:
		memset(&_floodStateParams, 0, sizeof(_floodStateParams));
		_floodStateParams.box.left = 0;
		_floodStateParams.box.top = 0;
		_floodStateParams.box.right = 640;
		_floodStateParams.box.bottom = 480;
		break;
	case 11:
		_floodStateParams.field_14 = pop();
		_floodStateParams.field_10 = pop();
		break;
	case 12:
		_floodStateParams.field_18 = pop();
		break;
	case 13:
		_floodStateParams.box.bottom = pop();
		_floodStateParams.box.right = pop();
		_floodStateParams.box.top = pop();
		_floodStateParams.box.left = pop();
		break;
	case 201:
		//floodState(_floodStateParams);
		break;
	default:
		error("o90_floodState: Unknown case %d", subOp);
	}
	debug(1,"o90_floodState stub (%d)", subOp);
}

void ScummEngine_v90he::o90_shl() {
	int a = pop();
	push(pop() << a);
}

void ScummEngine_v90he::o90_shr() {
	int a = pop();
	push(pop() >> a);
}

void ScummEngine_v90he::o90_mod() {
	int a = pop();
	if (a == 0)
		error("modulus by zero");
	push(pop() % a);
}

void ScummEngine_v90he::o90_findAllObjectsWithClassOf() {
	int args[16];
	int cond, num, cls, tmp;
	bool b;

	num = getStackList(args, ARRAYSIZE(args));
	int room = pop();
	int j = 1;

	if (room != _currentRoom)
		warning("o90_findAllObjectsWithClassOf: current room is not %d", room);

	writeVar(0, 0);
	defineArray(0, kDwordArray, 0, 0, 0, _numLocalObjects + 1);
	for (int i = 1; i < _numLocalObjects; i++) {
		cond = 1;
		tmp = num;
		while (--tmp >= 0) {
			cls = args[tmp];
			b = getClass(i, cls);
			if ((cls & 0x80 && !b) || (!(cls & 0x80) && b))
				cond = 0;
		}

		if (cond)
			writeArray(0, 0, j++, _objs[i].obj_nr);
	}
	writeArray(0, 0, 0, j);
	
	push(readVar(0));
}

void ScummEngine_v90he::o90_getPolygonOverlap() {
	int args1[32];
	int args2[32];

	int n1 = getStackList(args1, ARRAYSIZE(args1));
	getStackList(args2, ARRAYSIZE(args2));

	int subOp = pop();

	switch (subOp) {
	case 1:
		{
			Common::Rect r(args1[0], args1[1], args1[2] + 1, args1[3] + 1);
			Common::Point p(args2[0], args2[1]);
			push(r.contains(p) ? 1 : 0);
		}
		break;
	case 2:
		{
			int dx = args2[0] - args1[0];
			int dy = args2[1] - args1[1];
			int dist = dx * dx + dy * dy;
			if (dist >= 2) {
				dist = (int)sqrt((double)(dist + 1));
			}
			push((dist > args1[2]) ? 1 : 0);
		}
		break;
	case 3:
		{
			Common::Rect r1(args1[0], args1[1], args1[2] + 1, args1[3] + 1);
			Common::Rect r2(args2[0], args2[1], args2[2] + 1, args2[3] + 1);
			push(r2.intersects(r1) ? 1 : 0);			
		}
		break;
	case 4:
		{
			int dx = args2[0] - args1[0];
			int dy = args2[1] - args1[1];
			int dist = dx * dx + dy * dy;
			if (dist >= 2) {
				dist = (int)sqrt((double)(dist + 1));
			}
			push((dist < args1[2] && dist < args2[2]) ? 1 : 0);
		}
		break;
	case 5:
		{
			assert((n1 & 1) == 0);
			n1 /= 2;
			if (n1 == 0) {
				push(0);
			} else {
				WizPolygon wp;
				memset(&wp, 0, sizeof(wp));
				wp.numVerts = n1;
				assert(n1 < ARRAYSIZE(wp.vert));
				for (int i = 0; i < n1; ++i) {
					wp.vert[i].x = args1[i * 2 + 0];
					wp.vert[i].y = args1[i * 2 + 1];
				}
				push(_wiz.polygonContains(wp, args2[0], args2[1]) ? 1 : 0);
			}
		}
		break;
	// HE 98+
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		push(0);
		break;
	default:
		error("o90_getPolygonOverlap: default case %d", subOp);
	}
}

void ScummEngine_v90he::o90_cond() {
	int a = pop();
	int b = pop();
	int c = pop();

	if (!c)
		b = a;
	push(b);
}

void ScummEngine_v90he::o90_dim2dim2Array() {
	int data, dim1start, dim1end, dim2start, dim2end;
	int type = fetchScriptByte();

	switch (type) {
	case 2:		// SO_BIT_ARRAY
		data = kBitArray;
		break;
	case 3:		// SO_NIBBLE_ARRAY
		data = kNibbleArray;
		break;
	case 4:		// SO_BYTE_ARRAY
		data = kByteArray;
		break;
	case 5:		// SO_INT_ARRAY
		data = kIntArray;
		break;
	case 6:
		data = kDwordArray;
		break;
	case 7:		// SO_STRING_ARRAY
		data = kStringArray;
		break;
	default:
		error("o90_dim2dim2Array: default case %d", type);
	}

	if (pop() == 2) {
		dim1end = pop();
		dim1start = pop();
		dim2end = pop();
		dim2start = pop();
	} else {
		dim2end = pop();
		dim2start = pop();
		dim1end = pop();
		dim1start = pop();
	}

	defineArray(fetchScriptWord(), data, dim2start, dim2end, dim1start, dim1end);
}

void ScummEngine_v90he::o90_redim2dimArray() {
	int a, b, c, d;
	d = pop();
	c = pop();
	b = pop();
	a = pop();

	byte subOp = fetchScriptByte();

	switch (subOp) {
	case 4:
		redimArray(fetchScriptWord(), a, b, c, d, kByteArray);
		break;
	case 5:
		redimArray(fetchScriptWord(), a, b, c, d, kIntArray);
		break;
	case 6:
		redimArray(fetchScriptWord(), a, b, c, d, kDwordArray);
		break;
	default:
		error("o90_redim2dimArray: default type %d", subOp);
	}
}

void ScummEngine_v90he::o90_sortArray() {
	// Sorts array via qsort
	byte subOp = fetchScriptByte();

	switch (subOp) {
	case 129:
	case 134: // HE100
		fetchScriptWord();
		pop();
		pop();
		pop();
		pop();
		pop();
		break;
	default:
		error("o90_sortArray: Unknown case %d", subOp);
	}
	debug(1,"o90_sortArray stub (%d)", subOp);
}

void ScummEngine_v90he::o90_getObjectData() {
	// Object releated
	byte subOp = fetchScriptByte();
	subOp -= 32;

	switch (subOp) {
	case 0:
		if (_heObjectNum == -1)
			push(0);
		else
			push(_objs[_heObjectNum].width);
		break;
	case 1:
		if (_heObjectNum == -1)
			push(0);
		else
			push(_objs[_heObjectNum].height);
		break;
	case 4:
		push(getObjectImageCount(_heObject));
		break;
	case 6:
		if (_heObjectNum == -1)
			push(0);
		else
			push(_objs[_heObjectNum].x_pos);
		break;
	case 7:
		if (_heObjectNum == -1)
			push(0);
		else
			push(_objs[_heObjectNum].y_pos);
		break;
	case 20:
		push(getState(_heObject));
		break;
	case 25:
		_heObject = pop();
		_heObjectNum = getObjectIndex(_heObject);
		break;
	case 107:
		// Dummy case
		pop();
		push(0);
		break;
	default:
		error("o90_getObjectData: Unknown case %d", subOp);
	}
	debug(1,"o90_getObjectData stub (%d)", subOp);
}

uint8 *ScummEngine_v90he::getHEPalette(int palSlot) {
	assert(palSlot >= 1 && palSlot <= _numPalettes);
	if (palSlot == 1) {
		return _currentPalette; // XXX won't work, as size == 768
	} else {
		return _hePalettes + (palSlot - 2) * 1024;
	}
}

void ScummEngine_v90he::setHEPaletteColor(int palSlot, uint8 color, uint8 r, uint8 g, uint8 b) {
	assert(palSlot >= 1 && palSlot <= _numPalettes);
	uint8 *p = _hePalettes + palSlot * 1024 + color * 3;
	*(p + 0) = r;
	*(p + 1) = g;
	*(p + 2) = b;
	*(_hePalettes + palSlot * 1024 + 768 + color) = color;
}

void ScummEngine_v90he::setHEPaletteFromPtr(int palSlot, const uint8 *palData) {
	assert(palSlot >= 1 && palSlot <= _numPalettes);
	uint8 *pc = _hePalettes + palSlot * 1024;
	uint8 *pi = pc + 768;
	for (int i = 0; i < 256; ++i) {
		*pc++ = *palData++;
		*pc++ = *palData++;
		*pc++ = *palData++;
		*pi++ = i;
	}
}

void ScummEngine_v90he::setHEPaletteFromCostume(int palSlot, int resId) {
	assert(palSlot >= 1 && palSlot <= _numPalettes);
	const uint8 *data = getResourceAddress(rtCostume, resId);
	assert(data);
	const uint8 *rgbs = findResourceData(MKID('RGBS'), data);
	assert(rgbs);
	setHEPaletteFromPtr(palSlot, rgbs);
}

void ScummEngine_v90he::setHEPaletteFromImage(int palSlot, int resId, int state) {
	assert(palSlot >= 1 && palSlot <= _numPalettes);
	uint8 *data = getResourceAddress(rtImage, resId);
	assert(data);
	uint8 *rgbs = findWrappedBlock(MKID('RGBS'), data, state, 0);
	assert(rgbs);
	setHEPaletteFromPtr(palSlot, rgbs);
}

void ScummEngine_v90he::setHEPaletteFromRoom(int palSlot, int resId, int state) {
	assert(palSlot >= 1 && palSlot <= _numPalettes);
	uint8 *data = getResourceAddress(rtRoom, resId);
	assert(data);
	uint8 *rgbs = findWrappedBlock(MKID('PALS'), data, state, 0);
	assert(rgbs);
	setHEPaletteFromPtr(palSlot, rgbs);
}

void ScummEngine_v90he::restoreHEPalette(int palSlot) {
	assert(palSlot >= 1 && palSlot <= _numPalettes);
	if (palSlot != 1) {
		memcpy(_hePalettes + palSlot * 1024, _hePalettes + 1024, 1024);
	}
}

void ScummEngine_v90he::copyHEPalette(int dstPalSlot, int srcPalSlot) {
	assert(dstPalSlot >= 1 && dstPalSlot <= _numPalettes);
	assert(srcPalSlot >= 1 && srcPalSlot <= _numPalettes);
	if (dstPalSlot != srcPalSlot) {
		memcpy(_hePalettes + srcPalSlot * 1024, _hePalettes + dstPalSlot * 1024, 1024);
	}
}

void ScummEngine_v90he::copyHEPaletteColor(int palSlot, uint8 dstColor, uint8 srcColor) {
	assert(palSlot >= 1 && palSlot <= _numPalettes);
	uint8 *dstPal = _hePalettes + palSlot * 1024 + dstColor * 3;
	uint8 *srcPal = _hePalettes + (palSlot + 1) * 1024 + srcColor * 3;
	memcpy(dstPal, srcPal, 3);
	*(_hePalettes + palSlot * 1024 + 768 + dstColor) = srcColor;
}

void ScummEngine_v90he::o90_getPaletteData() {
	byte subOp = fetchScriptByte();
	subOp -= 45;

	switch (subOp) {
	case 0:
		break;
	case 7:
		pop();
		pop();
		pop();
		break;
	case 21:
		pop();
		pop();
		break;
	case 87:
		pop();
		pop();
		break;
	case 172:
		pop();
		pop();
		pop();
		break;
	default:
		error("o90_getPaletteData: Unknown case %d", subOp);
	}
	push(0);
	debug(1,"o90_getPaletteData stub (%d)", subOp);
}

void ScummEngine_v90he::o90_paletteOps() {
	int a, b, c, d, e;

	byte subOp = fetchScriptByte();
	subOp -= 57;

	switch (subOp) {
	case 0:
		_hePaletteNum = pop();
		break;
	case 6:
		b = pop();
		a = pop();
		if (_hePaletteNum != 0) {
			setHEPaletteFromImage(_hePaletteNum, a, b);
		}
		break;
	case 9:
		e = pop();
		d = pop();
		c = pop();
		b = pop();
		a = pop();
		if (_hePaletteNum != 0) {
			for (; a <= b; ++a) {
				setHEPaletteColor(_hePaletteNum, a, c, d, e);
			}
		}
		break;
	case 13:
		c = pop();
		b = pop();
		a = pop();
		if (_hePaletteNum) {
			for (; a <= b; ++a) {
				copyHEPaletteColor(_hePaletteNum, a, c);
			}
		}
		break;
	case 19: //HE99+
		a = pop();
		if (_hePaletteNum != 0) {
			setHEPaletteFromCostume(_hePaletteNum, a);
		}
		break;
	case 29:
		a = pop();
		if (_hePaletteNum != 0) {
			copyHEPalette(_hePaletteNum, a);
		}
		break;
	case 118:
		b = pop();
		a = pop();
		if (_hePaletteNum != 0) {
			setHEPaletteFromRoom(_hePaletteNum, a, b);
		}
		break;
	case 160:
		if (_hePaletteNum != 0) {
			restoreHEPalette(_hePaletteNum);
		}
		break;
	case 198:
		_hePaletteNum = 0;
		break;
	default:
		error("o90_paletteOps: Unknown case %d", subOp);
	}
	debug(1,"o90_paletteOps stub (%d)", subOp);
}



void ScummEngine_v90he::o90_unknownA5() {
	// Font related
	byte string[80];
	int a;

	byte subOp = fetchScriptByte();

	switch (subOp) {
	case 42:
		a = pop();
		if (a == 2) {
			copyScriptString(string);
			push(-1);
		} else if (a == 1) {
			pop();
			writeVar(0, 0);
			defineArray(0, kStringArray, 0, 0, 0, 0);
			writeArray(0, 0, 0, 0);
			push(readVar(0));
		}
		break;
	case 57:
		push(1);
		break;
	default:
		error("o90_unknownA5: Unknown case %d", subOp);
	}

	debug(1,"o90_unknownA5 stub (%d)", subOp);
}

void ScummEngine_v90he::o90_getActorAnimProgress() {
	Actor *a = derefActor(pop(), "o90_getActorAnimProgress");
	push(a->getAnimProgress());
}

} // End of namespace Scumm
