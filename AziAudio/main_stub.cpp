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

#include "common.h"
#include "my_types.h"
#include "AudioSpec.h"


void AiDacrateChanged(int SystemType)
{
	return;
}

void AiLenChanged(void)
{
	return;
}


u32 AiReadLength(void)
{
	return 0;
}


void AiUpdate(Boolean Wait)
{
	return;
}


void CloseDLL(void)
{
	return;
}


void DllAbout(HWND hParent)
{
	return;
}

void DllConfig(HWND hParent)
{
	return;
}

void DllTest(HWND hParent)
{
	return;
}


void GetDllInfo(PLUGIN_INFO * PluginInfo)
{
	return;
}

Boolean InitiateAudio(AUDIO_INFO Audio_Info)
{
	return true;
}



void ProcessAList(void)
{
	return;
}


void  RomClosed(void)
{
	return;
}

void  RomOpen(void)
{
	return;
}

void  PluginLoaded(void)
{
	return;
}


void AiCallBack(void)
{
	return;
}


extern AUDIO_INFO AudioInfo;


void HLEStart(AZI_OSTask* task)
{
	return;
}

void ChangeABI (int type)
{
	return;
}
