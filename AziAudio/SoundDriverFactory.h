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
#pragma once
#include "common.h"
#include "SoundDriverInterface.h"

class SoundDriverFactory
{
private:
	typedef SoundDriverInterface* (*SoundDriverCreationFunction)();
	struct FactoryDriversStruct
	{
		SoundDriverType DriverType;
		SoundDriverCreationFunction CreateFunction;
		int Priority;
		char Description[100];
	};

private:
	SoundDriverFactory() {};
	static int FactoryNextSlot;
	static const int MAX_FACTORY_DRIVERS = 20;
	static FactoryDriversStruct FactoryDrivers[MAX_FACTORY_DRIVERS];
public:
	~SoundDriverFactory() {};

	static SoundDriverInterface* CreateSoundDriver(SoundDriverType DriverID);
	static bool RegisterSoundDriver(SoundDriverType DriverType, SoundDriverCreationFunction CreateFunction, const char *Description, int Priority);
	static SoundDriverType DefaultDriver();
	static int EnumDrivers(SoundDriverType *drivers, int max_entries);
	static int InitDrivers();
	static const char* GetDriverDescription(SoundDriverType driver);
	static bool DriverExists(SoundDriverType driver);
};

