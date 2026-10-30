// SPDX-FileCopyrightText: 2022-2026 AsteroidOS contributors
// SPDX-License-Identifier: GPL-3.0-only
#ifndef ASTEROIDOS_KOI_TOOLS_H
#define ASTEROIDOS_KOI_TOOLS_H
#include "featurelist.h"

class Koi : public IWatch {
public:
	Koi();
	AsteroidOS::LCD_Tools::Feature::SyncTime syncTime;
	AsteroidOS::LCD_Tools::Feature::PrepareTimepiece prepareTimepiece;
	AsteroidOS::LCD_Tools::Feature::SessionRestart sessionRestart;
	AsteroidOS::LCD_Tools::Feature::WhiteBackground whiteBackground;
	AsteroidOS::LCD_Tools::Feature::BlackBackground blackBackground;
};
#endif //ASTEROIDOS_KOI_TOOLS_H
