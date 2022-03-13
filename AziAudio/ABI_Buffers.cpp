/****************************************************************************
*                                                                           *
* Azimer's HLE Audio Plugin for Project64 Compatible N64 Emulators          *
* http://www.apollo64.com/                                                  *
* Copyright (C) 2000-2019 Azimer. All rights reserved.                      *
*                                                                           *
* License:                                                                  *
* GNU/GPLv2 http://www.gnu.org/licenses/gpl-2.0.html                        *
*                                                                           *
****************************************************************************/
#if 0
#define FFFC_MASK 0xfffc
#else
#define FFFC_MASK 0xFFFF
#endif
/* memset() and memcpy() */
#include <string.h>

#include "audiohle.h"

void CLEARBUFF() {
	u32 addr = (u32)k0;
	u16 count = (t9 & 0xffff);
	memset(BufferSpace + addr, 0, (count) & FFFC_MASK);
}

void CLEARBUFF2() {
	u16 addr  = _SHIFTR(k0, 0, 16);
	u16 count = min(t9, sizeof(BufferSpace) - addr);
	if (count > 0)
		memset(BufferSpace + addr, 0, count);
}

void CLEARBUFF3() {
	u16 addr  = (u16)k0;
	u16 count = (u16)(t9 & 0xffff);
	memset(BufferSpace + addr + 0x4f0, 0, count);
}

void DMEMMOVE() {
	u32 v0, v1;
	u32 cnt;
	if ((t9 & 0xffff) == 0)
		return;
	v0 = (k0 & 0xFFFF);
	v1 = (t9 >> 0x10);

	u32 count = ((t9) & FFFC_MASK);

	for (cnt = 0; cnt < count; cnt += 4) {
		BufferSpace[BES(v1 + cnt + 0)] = BufferSpace[BES(v0 + cnt + 0)];
		BufferSpace[BES(v1 + cnt + 1)] = BufferSpace[BES(v0 + cnt + 1)];
		BufferSpace[BES(v1 + cnt + 2)] = BufferSpace[BES(v0 + cnt + 2)];
		BufferSpace[BES(v1 + cnt + 3)] = BufferSpace[BES(v0 + cnt + 3)];
	}
}

void DMEMMOVE2() { // Needs accuracy verification...
	u32 input, output;
	u32 cnt;
	if ((t9 & 0xffff) == 0)
		return;
	input = _SHIFTR(k0, 0, 16);
	output = _SHIFTR(t9, 16, 16);
	u32 count = _SHIFTR(t9, 0, 16);
	count	  = min(count, sizeof(BufferSpace) - output);
	count	  = min(count, sizeof(BufferSpace) - input);
	memcpy(BufferSpace + output, BufferSpace + input, count);
	//memcpy (dmem+output, dmem+input, count-1);
	/*for (cnt = 0; cnt < count; cnt += 4) {
		BufferSpace[BES(output + cnt + 0)] = BufferSpace[BES(input + cnt + 0)];
		BufferSpace[BES(output + cnt + 1)] = BufferSpace[BES(input + cnt + 1)];
		BufferSpace[BES(output + cnt + 2)] = BufferSpace[BES(input + cnt + 2)];
		BufferSpace[BES(output + cnt + 3)] = BufferSpace[BES(input + cnt + 3)];
	}*/
}

void DMEMMOVE3() { // Needs accuracy verification...
	u32 v0, v1;
	u32 cnt;
	v0 = (k0 & 0xFFFF) + 0x4f0;
	v1 = (t9 >> 0x10) + 0x4f0;
	u32 count = ((t9) & FFFC_MASK);

	//memcpy (dmem+output, dmem+input, count-1);
	for (cnt = 0; cnt < count; cnt += 4) {
		BufferSpace[BES(v1 + cnt + 0)] = BufferSpace[BES(v0 + cnt + 0)];
		BufferSpace[BES(v1 + cnt + 1)] = BufferSpace[BES(v0 + cnt + 1)];
		BufferSpace[BES(v1 + cnt + 2)] = BufferSpace[BES(v0 + cnt + 2)];
		BufferSpace[BES(v1 + cnt + 3)] = BufferSpace[BES(v0 + cnt + 3)];
	}
}

void DUPLICATE2() {
	u16 Count = _SHIFTR(k0, 16, 8);
	u16 In	  = _SHIFTR(k0, 0, 16);
	u16 Out	  = _SHIFTR(t9, 16, 16);

	u16 buff[64];

	memcpy(buff, BufferSpace + In, 128);

	while (Count) {
		memcpy(BufferSpace + Out, buff, 128);
		Out += 128;
		Count--;
	}
}

// TODO: This comment has me wondering if there's a problem.  10+ year old comments are hard to remember. -Azimer
void LOADBUFF() { // memcpy causes static... endianess issue :(
	u32 v0;
	if (AudioCount == 0)
		return;
	v0 = t9; // TODO FIX (t9 & 0xfffffc);// + SEGMENTS[(t9>>24)&0xf];
	memcpy(BufferSpace + (AudioInBuffer & FFFC_MASK), (void*)v0, (AudioCount) & FFFC_MASK);
}

void LOADBUFF2()
{ // Needs accuracy verification...
	auto src = (void*)t9;
	u16 dmem = _SHIFTR(k0, 0, 16);
	u32 cnt	 = min(_SHIFTR(k0, 16, 8) << 4, sizeof(BufferSpace) - dmem);

	memcpy(BufferSpace + dmem, src, cnt);
}

void LOADBUFF3() {
	u32 v0;
	u32 cnt = (((k0 >> 0xC) + 3) & 0xFFC);
	v0 = t9; // TODO FIX (t9 & 0xfffffc);
	u32 src = (k0 & 0xffc) + 0x4f0;
	memcpy(BufferSpace + src, DRAM + v0, cnt);
}

// TODO: This comment has me wondering if there's a problem.  10+ year old comments are hard to remember. -Azimer
void SAVEBUFF() { // memcpy causes static... endianess issue :(
	u32 v0;
	if (AudioCount == 0)
		return;
	v0 = t9; // TODO FIX (t9 & 0xfffffc);// + SEGMENTS[(t9>>24)&0xf];
	memcpy(DRAM + v0, BufferSpace + (AudioOutBuffer & FFFC_MASK), (AudioCount) & FFFC_MASK);
}

void SAVEBUFF2() { // Needs accuracy verification...
	u32 cnt = _SHIFTR(k0, 16, 8) << 4;

	if(cnt >= 0xFF)
	{
		int x = 0;
	}
	//v0 = t9; // TODO FIX (t9 & 0xfffffc);// + SEGMENTS[(t9>>24)&0xf];
	memcpy((void*)t9, BufferSpace + (k0 & FFFC_MASK), (cnt) & FFFC_MASK);
}

void SAVEBUFF3() {
	u32 v0;
	u32 cnt = (((k0 >> 0xC) + 3) & 0xFFC);
	v0 = t9; // TODO FIX (t9 & 0xfffffc);
	u32 src = (k0 & 0xffc) + 0x4f0;
	memcpy(DRAM + v0, BufferSpace + src, cnt);
}

void SEGMENT() { // Should work
	SEGMENTS[(t9 >> 24) & 0xf] = t9;
}

void SEGMENT2() {
	if (isZeldaABI) {
		FILTER2();
		return;
	}
	if ((k0 & 0xffffff) == 0) {
		isMKABI = true;
		//SEGMENTS[(t9>>24)&0xf] = (t9 & 0xffffff);
	}
	else {
		isMKABI = false;
		isZeldaABI = true;
		FILTER2();
	}
}

void SETBUFF() { // Should work ;-)
	if ((k0 >> 0x10) & 0x8) { // A_AUX - Auxillary Sound Buffer Settings
		AudioAuxA = (u16)(k0 & 0xFFFF);
		AudioAuxC = (u16)((t9 >> 0x10));
		AudioAuxE = (u16)(t9 & 0xFFFF);
	}
	else {		// A_MAIN - Main Sound Buffer Settings
		AudioInBuffer = (u16)(k0 & 0xFFFF);           // 0x00
		AudioOutBuffer = (u16)((t9 >> 0x10)); // 0x02
		AudioCount = (u16)(t9 & 0xFFFF);           // 0x04
	}
}

void SETBUFF2() {
	AudioInBuffer  = (u16)_SHIFTR(k0, 0, 16);       // 0x00
	AudioOutBuffer = (u16)_SHIFTR(t9, 16, 16); // 0x02
	AudioCount     = (u16)_SHIFTR(t9, 0, 16);	// 0x04
}

void SETLOOP() {
	loopval = t9;// + SEGMENTS[(t9>>24)&0xf];
	//VolTrg_Left  = (s16)(loopval>>16);		// m_LeftVol
	//VolRamp_Left = (s16)(loopval);	// m_LeftVolTarget
}

void SETLOOP2() {
	loopval = t9;
}

void SETLOOP3() {
	loopval = t9;
}
