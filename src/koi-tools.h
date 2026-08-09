// SPDX-FileCopyrightText: 2022-2026 Florent Revest <revestflo@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef ASTEROIDOS_KOI_TOOLS_H
#define ASTEROIDOS_KOI_TOOLS_H
#include "featurelist.h"

class Koi : public IWatch {
public:
	Koi();
	AsteroidOS::LCD_Tools::Feature::SyncTime st;
	AsteroidOS::LCD_Tools::Feature::PrepareTimepiece pt;
	AsteroidOS::LCD_Tools::Feature::SessionRestart sr;
	AsteroidOS::LCD_Tools::Feature::WhiteBackground wb;
	AsteroidOS::LCD_Tools::Feature::BlackBackground bb;
};
#endif //ASTEROIDOS_KOI_TOOLS_H
