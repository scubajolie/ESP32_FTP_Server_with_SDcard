#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "ESP32FtpServer.h"
#include "ESP32_files.h"

FtpServer ftpSrv;

// Before you call this function, the serial port needs to be open.
// Opens the SD card and defines pinouts. 
int ESP32_setup()
{

  SPIFFS.begin();
  Auth_decode();    /* Decoding auth file from SD card for WIFI and FTP config*/
  WiFi.begin(wifi_name, wifi_pass);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // TODO:  Add a timeout
  /*
  if (WiFiTimedOut) {
    return SETUP_FAIL_NO_WIFI;
  }*/

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(wifi_name);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  SD_SPI.begin(FSPI_SCLK_PIN, FSPI_MISO_PIN, FSPI_MOSI_PIN, FSPI_CS_PIN);
  if (SD.begin(14, SD_SPI))
  {
    Serial.println("SD opened!");
    /* username, password for ftp.  
    set ports in ESP32FtpServer.h  (default 21 for FTP, 50009 for passive data port)*/
    ftpSrv.begin(ftp_name, ftp_pass);
  }
  else {
    Serial.println("SD card failed to initialize");
    return SETUP_FAIL_NO_SDCARD;
  }

  int status = SD_card_status(); /* Status of SD card*/
  if (status != 0) {
    return status;
  }

  return 0;
}

void ESP32_loop()
{
  ftpSrv.handleFTP();
}
