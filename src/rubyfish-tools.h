// SPDX-FileCopyrightText: 2022-2026 Florent Revest <revestflo@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef ASTEROIDOS_RUBYFISH_TOOLS_H
#define ASTEROIDOS_RUBYFISH_TOOLS_H
#include "featurelist.h"
#include <cstdint>

class Rubyfish : public IWatch {
public:
	Rubyfish();
	~Rubyfish();
	AsteroidOS::LCD_Tools::Feature::SyncTime st;
	AsteroidOS::LCD_Tools::Feature::PrepareTimepiece pt;
	AsteroidOS::LCD_Tools::Feature::DisableStepcounter ds;
	AsteroidOS::LCD_Tools::Feature::EnableStepcounter es;
	AsteroidOS::LCD_Tools::Feature::DisableHeartrate dh;
	AsteroidOS::LCD_Tools::Feature::EnableHeartrate eh;
	AsteroidOS::LCD_Tools::Feature::DisableMotion dm;
	AsteroidOS::LCD_Tools::Feature::EnableMotion em;
private:
	int SyncTime();
	int PrepareTimepiece();
	int DisableStepCounter();
	int EnableStepCounter();
	int DisableHeartRate();
	int EnableHeartRate();
	int DisableMotion();
	int EnableMotion();
	void* OpenLibrary();
	void LoadSymbols();
	void* LoadSymbol(const char *symbol_string);
	int CloseLibrary(void* lib_mcutool);
	void* mcutool_handle;

	typedef struct nativeFunctions_t {
		int (*autoLowPowerScreen)(int32_t, int32_t, int32_t enable);
		int (*bandMode)();
		int (*cutOffScreen)();
		int (*enableHeartRate)(int32_t, int32_t, int32_t enable);
		int (*enableLowPowerScreen)(int32_t, int32_t, int32_t enable);
		int (*enableMotion)(int32_t, int32_t, int32_t enable);
		int (*enableStepCounter)(int32_t, int32_t, int32_t enable);
		int (*getBandModeData)();
		int (*getDataVersion)();
		int (*syncSteps)(int32_t, int32_t, int32_t steps);
		int (*syncTime)();
		int (*updateFitnessState)(int32_t, int32_t, int32_t type, int32_t state, int32_t heartRate, int64_t duration, int32_t calorie, float distance, int32_t speed, int32_t gpsStatus, uint8_t isKilometer);
		int (*wipeBandModeData)();
	} nativeFunctions_t;

	nativeFunctions_t nativeFunctions;
};

#endif //ASTEROIDOS_RUBYFISH_TOOLS_H
