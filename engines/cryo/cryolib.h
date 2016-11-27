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

#ifndef CRYO_CRYOLIB_H
#define CRYO_CRYOLIB_H

#include "audio/mixer.h"
#include "common/system.h"

#include "cryo/platdefs.h"

namespace Cryo {

#define SW16(n) ( (((n) & 0xFF) << 8) | (((n) >> 8) & 0xFF) )
#define SW32(n) ( (((n) & 0xFF) << 24) | (((n) >> 24) & 0xFF) | (((n) & 0xFF00) << 8) | (((n) >> 8) & 0xFF00))
#if 0
//big-endian host
#define LE16(n) SW16(n)
#define LE32(n) SW32(n)
#define BE16(n) (n)
#define BE32(n) (n)
#else
//little-endian host
#define LE16(n) (n)
#define LE32(n) (n)
#define BE16(n) SW16(n)
#define BE32(n) SW32(n)
#endif
#define PLE16(p) ( (((byte*)(p))[1] << 8) | ((byte*)(p))[0] )
#define PLE32(p) ( (((byte*)(p))[3] << 24) | (((byte*)(p))[2] << 16) | (((byte*)(p))[1] << 8) | ((byte*)(p))[0] )

enum {
	fsFromStart = 1
};

struct BlitView{
	int     _srcLeft;
	int     _srcTop;
	int     _dstLeft;
	int     _dstTop;
	int     _width;
	int     _height;
};

struct View {
	byte    *_bufferPtr;
	int      _width;
	int      _height;
	int16    _pitch;
	bool     _doubled;
	bool     _allocated;
	BlitView _normal;
	BlitView _zoom;
};

struct color3_t {
	int16   r, g, b;
};
typedef struct color3_t color3_t;

struct color_t {
	int16   a, r, g, b;
};
typedef struct color_t color_t;

#pragma pack(push, 1)
struct HNMHeader {
	int     _signature;
	char    _unusedFlag1;
	char    _unusedFlag2;
	char    _unusedReserved;
	char    _unusedBpp;
	uint16  _width;
	uint16  _height;
	int     _unusedFileSize;
	int     _numbFrame;
	int     _unusedTableOffset;
	int16   _unusedSpeed;
	int16   _unusedMaxBuffer;
	int     _bufferSize;
	int16   _unusedUnknown;
	char    _unusedReserved2[14];
	char    _unusedCopyright[16];
};
typedef struct HNMHeader HNMHeader;
#pragma pack(pop)

struct hnm_t {
	int  _frameNum;
	int  ff_4;
	file_t  *_file;
	HNMHeader     _header;
	byte   *tmpBuffer[2];
	byte   *finalBuffer;
	byte   *_newFrameBuffer;
	byte   *_oldFrameBuffer;
	byte   *_readBuffer;
	byte   *_dataPtr;
	color_t  _palette[256];

	bool  _canLoop;
	int16 ff_896;
	int16 _chunkId;
	int   _totalRead;
};
typedef struct hnm_t hnm_t;

struct sound_t {
	char *sndHandle;
	int16 _headerLen;
	int32  _headerOffset;
	int16   ff_A;

	char    *_buffer;
	int     ff_16;
	int16   _maxLength;
	float   _rate;
	int16   _sampleSize;
	int     _length;
	int16   _mode;
	volatile int16  _locked;
	int32    _loopStart;
	int16   _loopTimes;
	bool   _reversed;
	int16   ff_32;
	int16   _volume;
};
typedef struct sound_t sound_t;

#define kCryoMaxClSounds 64

struct soundgroup_t {
	sound_t *_sounds[kCryoMaxClSounds];
	int16 _numSounds;
	int16 _soundIndex;
	int16 _playIndex;
	bool _forceWait;
};
typedef struct soundgroup_t soundgroup_t;

#define kCryoMaxChSounds 10

struct soundchannel_t {
	Audio::SoundHandle ch;
	int     xx;

	int16   _volumeLeft;
	int16   _volumeRight;
	int16   _numSounds;

	sound_t *_sounds[kCryoMaxChSounds];

	int16   ff_536;
};
typedef struct soundchannel_t soundchannel_t;

extern volatile int32 TimerTicks;
extern View ScreenView;


soundgroup_t *CLSoundGroup_New(int16 numSounds, int16 length, int16 sampleSize, float rate, int16 mode);
void CLSoundGroup_Free(soundgroup_t *sg);
void CLSoundGroup_Reverse16All(soundgroup_t *sg);
void *CLSoundGroup_GetNextBuffer(soundgroup_t *sg);
bool CLSoundGroup_AssignDatas(soundgroup_t *sg, void *buffer, int length, bool isSigned);
bool CLSoundGroup_SetDatas(soundgroup_t *sg, void *data, int length, bool isSigned);
void CLSoundGroup_PlayNextSample(soundgroup_t *sg, soundchannel_t *ch);

sound_t *CLSoundRaw_New(int16 length, float rate, int16 sampleSize, int16 mode);
void CLSoundRaw_Free(sound_t *sound);
void CLSoundRaw_AssignBuffer(sound_t *sound, void *buffer, int bufferOffs, int length);

void SysBeep(int x);
int32 TickCount();
void FlushEvents(int16 arg1, int16 arg2);

void CLBlitter_CopyViewRect(View *view1, View *view2, Common::Rect *rect1, Common::Rect *rect2);
void CLBlitter_Send2ScreenNextCopy(color_t *palette, uint16 first, uint16 count);
void CLBlitter_OneBlackFlash();
void CLBlitter_CopyView2ViewSimpleSize(byte *src, int16 srcw, int16 srcp, int16 srch,
                                       byte *dst, int16 dstw, int16 dstp, int16 dsth);
void CLBlitter_CopyView2ScreenCUSTOM(View *view);
void CLBlitter_CopyView2Screen(View *view);
void CLBlitter_UpdateScreen();
void CLBlitter_FillView(View *view, unsigned int fill);
void CLBlitter_FillScreenView(unsigned int fill);

void CLPalette_Init();
void CLPalette_SetLastPalette(color_t *palette, int16 first, int16 count);
void CLPalette_GetLastPalette(color_t *palette);
void CLPalette_SetRGBColor(color_t *palette, uint16 index, color3_t *rgb);
void CLPalette_Macintize(int16 macintize);
void CLPalette_SetInterval(uint16 first, uint16 last);
void CLPalette_DeactivateInterval();
void CLPalette_Send2Screen(struct color_t *palette, uint16 first, uint16 count);
void CLPalette_BeSystem();

void CLFile_Write(file_t &handle, void *buffer, int32 *size);

void CLSound_PrepareSample(sound_t *sound, int16 mode);
void CLSound_SetWantsDesigned(int16 designed);
void CLSound_SetLength(sound_t *sound, int length);

soundchannel_t *CLSoundChannel_New(int arg1);
void CLSoundChannel_Free(soundchannel_t *ch);
void CLSoundChannel_Stop(soundchannel_t *ch);
void CLSoundChannel_Play(soundchannel_t *ch, sound_t *sound);
int16 CLSoundChannel_GetVolume(soundchannel_t *ch);
void CLSoundChannel_SetVolume(soundchannel_t *ch, int16 volume);
void CLSoundChannel_SetVolumeRight(soundchannel_t *ch, int16 volume);
void CLSoundChannel_SetVolumeLeft(soundchannel_t *ch, int16 volume);

int16 CLKeyboard_HasCmdDown();
void CLKeyboard_Read();
byte CLKeyboard_GetLastASCII();
int16 CLKeyboard_IsScanCodeDown(int16 scancode);

void CLMouse_Hide();
void CLMouse_Show();
void CLMouse_GetPosition(int16 *x, int16 *y);
void CLMouse_SetPosition(int16 x, int16 y);
uint16 CLMouse_IsDown();

void CLView_SetSrcZoomValues(View *view, int x, int y);
void CLView_SetDisplayZoomValues(View *view, int w, int h);
void CLView_Free(View *view);
void CLView_InitDatas(View *view, int w, int h, void *buffer);
View *CLView_New(int w, int h);
void CLView_CenterIn(View *parent, View *child);

void CLScreenView_CenterIn(View *view);

void CRYOLib_ManagersInit();
void CRYOLib_ManagersDone();

void CLHNM_DecompLempelZiv(byte *buffer, byte *output);
void CLHNM_DecompUBA(byte *output, byte *curr_buffer, byte *prev_buffer,
                     byte *input, int width, char flags);
void CLHNM_Done();
hnm_t *CLHNM_New(int preload_size);
void CLHNM_Dispose(hnm_t *hnm);
void CLHNM_SetFile(hnm_t *hnm, file_t *file);
void CLHNM_SetFinalBuffer(hnm_t *hnm, byte *buffer);
void CLHNM_AllocMemory(hnm_t *hnm);
void CLHNM_DeallocMemory(hnm_t *hnm);
void CLHNM_CanLoop(hnm_t *hnm, bool canLoop);
void CLHNM_SelectBuffers(hnm_t *hnm);
void CLHNM_ChangePalette(hnm_t *hnm);
void CLHNM_Desentrelace(hnm_t *hnm);
bool CLHNM_LoadFrame(hnm_t *hnm);
void CLHNM_WantsSound(int16 sound);
void CLHNM_SoundMono(int16 is_mono);
void CLHNM_ReadHeader(hnm_t *hnm);
int16 CLHNM_GetVersion(hnm_t *hnm);
int CLHNM_GetFrameNum(hnm_t *hnm);
void CLHNM_Desentrelace320(byte *frame_buffer, byte *final_buffer, uint16 height);


} // End of namespace Cryo

#endif
