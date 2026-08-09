// SPDX-FileCopyrightText: 2022-2026 Florent Revest <revestflo@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later
#ifndef FEATURELIST_H
#define FEATURELIST_H
#include "feature.h"
/*
 * This is a list of the possible features.
 *
 * To add a new feature, choose a string for the feature flag
 * and then a string for the description.
 *
 * Implementation of the features is done per watch.
 */
namespace AsteroidOS::LCD_Tools::Feature {
using SyncTime = NamedFeature<
    fixed_string{"--sync-time"},
    fixed_string{"Sync lcd time with linux time"}
>;

using WhiteBackground = NamedFeature<
    fixed_string{"--white-background"},
    fixed_string{"set display background to white"}
>;

using BlackBackground = NamedFeature<
    fixed_string{"--black-background"},
    fixed_string{"set display background to black"}
>;

using PrepareTimepiece = NamedFeature<
    fixed_string{"--prepare-timepiece"},
    fixed_string{"prepare watch for power off into timekeeping mode. You will then need to shut it down manually"}
>;

using SessionRestart = NamedFeature<
    fixed_string{"--session-restart"},
    fixed_string{"Initialise LCD for user session restart"}
>;

using EnableStepcounter = NamedFeature<
    fixed_string{"--enable-stepcounter"},
    fixed_string{"Enable the step counter"}
>;

using DisableStepcounter = NamedFeature<
    fixed_string{"--disable-stepcounter"},
    fixed_string{"Disable the step counter"}
>;

using EnableHeartrate = NamedFeature<
    fixed_string{"--enable-heartrate"},
    fixed_string{"Enable the heart rate sensor"}
>;

using DisableHeartrate = NamedFeature<
    fixed_string{"--disable-heartrate"},
    fixed_string{"Disable the heart rate sensor"}
>;

using EnableMotion = NamedFeature<
    fixed_string{"--enable-motion"},
    fixed_string{"Enable motion"}
>;

using DisableMotion = NamedFeature<
    fixed_string{"--disable-motion"},
    fixed_string{"Disable motion"}
>;
} // end of namespace Feature
#endif /* FEATURELIST_H */
