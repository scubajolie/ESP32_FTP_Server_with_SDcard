#ifndef __FILES_H__
#define __FILES_H__

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <SPIFFS.h>

#define FSPI_SCLK_PIN   37
#define FSPI_MISO_PIN   36
#define FSPI_MOSI_PIN   35
#define FSPI_CS_PIN     38

#define SETUP_FAIL_NO_WIFI        -1
#define SETUP_FAIL_NO_SDCARD      -2
#define SETUP_FAIL_NO_SDCARD_TYPE -3

extern SPIClass SD_SPI;

extern char wifi_name[20];
extern char wifi_pass[20];
extern char ftp_name[20];
extern char ftp_pass[20];

extern char auth_data[200];
int SD_card_status();
void Auth_decode();
bool ESP32_readFile(fs::FS &fs, const char * path);


#endif //__FILES_H__