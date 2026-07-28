#include "koi-tools.h"

#include <array>
#include <iostream>
#include <MDConfItem>

#include <QTime>
#include <QDate>
#include <QFile>

using SpiMsg = std::array<uint8_t, 7>;

static void Write(const SpiMsg& data) {
	QFile multiSensorFile("/dev/MultiSensors_CD_01");
	if(!multiSensorFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		qCritical("Unable to open file for write. Check permissions");
		return;
	}
	multiSensorFile.write((const char *)data.data(), data.size());
	multiSensorFile.close();
}

static void KoiSet12H(bool value) {
	Write({0xFE,0x01,0x01,value,0x00,0x00,0x00});
}


namespace AsteroidOS::LCD_Tools::Koi {

static void SyncTime() {
	KoiSet12H(!MDConfItem("/org/asteroidos/settings/use-12h-format").value().toBool());
	QDate dateNow = QDate::currentDate();
	QTime timeNow = QTime::currentTime();
	Write({
	(uint8_t) 0x50,
	(uint8_t) 0,
	(uint8_t) ((((dateNow.year() - 2000) & 0xEF) << 1) | ((dateNow.month() & 0x08) >> 3)),
	(uint8_t) ((dateNow.month() << 5) | (dateNow.day() & 0x1F)),
	(uint8_t) (((dateNow.dayOfWeek() % 7) << 5) | (timeNow.hour() & 0x1F)), //weeks are counted from sunday, sunday encoded as zero.
	(uint8_t) (timeNow.minute() & 0xFF),
	(uint8_t) ((timeNow.second() + 1) & 0xFF) //the original casio code seems to add one second here to compensate for an update delay in the subcpu
	});
}

static void SetDisplayColor(bool value, bool persist) {
	if (persist) {
		MDConfItem("/org/asteroidos/lcd-tools/koi/display-color").set(value);
	}
	Write({0xFE,0x01,0x05,value,0x00,0x00,0x00});
}

static void SyncSettings() {
	SetDisplayColor(MDConfItem("/org/asteroidos/lcd-tools/koi/display-color").value().toInt(),false);
}

static void PrepareTimepiece() {
	Write({0x02,0xC1,0xBE,0x78,0x3F,0x91,0xC7});
}
} // end of namespace AsteroidOS::LCD_Tools::Koi

Koi::Koi()
        : st([]{ AsteroidOS::LCD_Tools::Koi::SyncTime(); })
        , pt([]{ AsteroidOS::LCD_Tools::Koi::PrepareTimepiece(); })
        , sr([]{ AsteroidOS::LCD_Tools::Koi::SyncSettings(); })
        , wb([]{ AsteroidOS::LCD_Tools::Koi::SetDisplayColor(true, true); })
        , bb([]{ AsteroidOS::LCD_Tools::Koi::SetDisplayColor(false, true); })
{}
