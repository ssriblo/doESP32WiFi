#include <Arduino.h>
#include "doWiFi.h"


bool wifiStart(void)
{
  unsigned long m1 = millis();
  bool wifiConnected = false;

  wifiInit(WIFI_SSID, WIFI_PASS);

  wifiConnected = wifiWaitConnection(5000);  

  if (!wifiConnected) return false;

  return true;
}


void setup()
{
  Serial.begin(115200);
  Serial.println(" REBOOT ");
  
  if (!wifiStart())
   {
    Serial.println("Wi-Fi connection error. ");
    return;
   } 
}

void loop()
{
}


