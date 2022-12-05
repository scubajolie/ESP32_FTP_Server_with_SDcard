#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "ESP32FtpServer.h"
#include "files.h"

FtpServer ftpSrv;

void setup()
{
  Serial.begin(115200);
  while(!Serial); // Wait for the Serial port to open
  SPIFFS.begin();
  SD_card_status(); /* Status of SD card*/
  Auth_decode();    /* Decoding auth file from SD card for WIFI and FTP config*/
  WiFi.begin(wifi_name, wifi_pass);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

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
}

void loop()
{
  ftpSrv.handleFTP();
}
