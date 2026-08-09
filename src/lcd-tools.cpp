// SPDX-FileCopyrightText: 2022-2026 Florent Revest <revestflo@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later
#include "catfish-tools.h"
#include "rubyfish-tools.h"
#include "koi-tools.h"
#include "medaka-tools.h"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <QSettings>

const char* CONFIG_FILE = "/etc/asteroid/machine.conf";
CLI::App IWatch::app{"lcd-tools: Various controls for watches with a secondary display"};

int main( int argc, char** argv ) {
	QSettings m_settings(CONFIG_FILE, QSettings::IniFormat);
	const std::string machineCodename = m_settings.value("Identity/MACHINE", "unknown").toString().toStdString();

	using Creator = std::function<std::unique_ptr<IWatch>()>;
	using Watchlist = std::unordered_map<std::string_view, Creator>;

	static Watchlist watches = {
		{ "catfish",  []{ return std::make_unique<Catfish>(); } },
		{ "rubyfish", []{ return std::make_unique<Rubyfish>(); } },
		{ "koi",      []{ return std::make_unique<Koi>(); } },
		{ "medaka",   []{ return std::make_unique<Medaka>(); } },
	};
	try {
		auto a = watches.at(machineCodename)();
		a->run(argc, argv);
	} catch (std::out_of_range&) {
		// not in the list of watches, so do nothing
	}
}
