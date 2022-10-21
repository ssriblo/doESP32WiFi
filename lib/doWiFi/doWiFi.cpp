#include "Arduino.h"
#include "doWiFi.h"

String wifiSsid = "";
String wifiPass = "";
bool   wifiConnected = false; 
bool   wifiInternetConnected = false;

bool wifiIsConnected(void)
{
  return WiFi.isConnected();
}

bool wifiIsInternetConnected(void)
{
  return wifiPingGoogle();
}

void wifiUnhandled_evt(WiFiEvent_t event) 
{
  Serial.printf("[WiFi-event] event: %d\n", event);

  switch (event) 
   {
    case SYSTEM_EVENT_STA_CONNECTED:
        wifiStationConnected_evt(event);
    break;
    
    case SYSTEM_EVENT_WIFI_READY: 
      Serial.println("WiFi interface ready");
      break;
    case SYSTEM_EVENT_SCAN_DONE:
      Serial.println("Completed scan for access points");
      break;
    case SYSTEM_EVENT_STA_START:
      Serial.println("WiFi client started");
      break;
    case SYSTEM_EVENT_STA_STOP:
      Serial.println("WiFi clients stopped");
      wifiConnected = false; 
      wifiInternetConnected = false;
      break;
    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
      Serial.println("Authentication mode of access point has changed");
      break;
    case SYSTEM_EVENT_STA_GOT_IP:
        wifiGotIP_evt(event);    
      break;
    case SYSTEM_EVENT_STA_LOST_IP:
      Serial.println("Lost IP address and IP address is reset to 0");
      wifiConnected = false; 
      wifiInternetConnected = false;
      break;
    case SYSTEM_EVENT_STA_WPS_ER_SUCCESS:
      Serial.println("WiFi Protected Setup (WPS): succeeded in enrollee mode");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_FAILED:
      Serial.println("WiFi Protected Setup (WPS): failed in enrollee mode");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_TIMEOUT:
      Serial.println("WiFi Protected Setup (WPS): timeout in enrollee mode");
      break;
    case SYSTEM_EVENT_STA_WPS_ER_PIN:
      Serial.println("WiFi Protected Setup (WPS): pin code in enrollee mode");
      break;
    case SYSTEM_EVENT_AP_START:
      Serial.println("WiFi access point started");
      break;
    case SYSTEM_EVENT_AP_STOP:
      Serial.println("WiFi access point  stopped");
      break;
    case SYSTEM_EVENT_AP_STACONNECTED:
      Serial.println("Client connected");
      break;
    case SYSTEM_EVENT_AP_STADISCONNECTED:
      Serial.println("Client disconnected");
      break;
    case SYSTEM_EVENT_AP_STAIPASSIGNED:
      Serial.println("Assigned IP address to client");
      break;
    case SYSTEM_EVENT_AP_PROBEREQRECVED:
      Serial.println("Received probe request");
      break;
    case SYSTEM_EVENT_GOT_IP6:
      Serial.println("IPv6 is preferred");
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      wifiStationDisconnected_evt(event);  
      break;
   
  }//switch
}

void wifiStationConnected_evt(WiFiEvent_t event)
{
  Serial.println("Connected to AP successfully!");
}

void wifiGotIP_evt(WiFiEvent_t event)
{
  Serial.println("WiFi connected. IP address: ");
  Serial.println(WiFi.localIP().toString().c_str());
  Serial.println(" SSID: ");
  Serial.println(WiFi.SSID());
  Serial.println(" RSSI: ");
  Serial.println(WiFi.RSSI());
  wifiConnected = true;
}

void wifiStationDisconnected_evt(WiFiEvent_t event)
{
  Serial.println("Disconnected from WiFi access point");
  Serial.println(String("WiFi lost connection. Trying to Reconnect: ") + wifiSsid + " " + wifiPass);  
  wifiConnected = false; 
  wifiInternetConnected = false;
   
  WiFi.begin(wifiSsid.c_str(), wifiPass.c_str());  
}


void wifiInit(String ssid, String pass)
{
   wifiSsid = ssid;
   wifiPass = pass;
     
   WiFi.disconnect(true);

   delay(100);
   WiFi.onEvent(wifiUnhandled_evt);
   WiFi.begin(wifiSsid.c_str(), wifiSsid.c_str());

}


String wifiGetString(String fileLink)
{
  HTTPClient http;

  String payload = "0";

  http.begin(fileLink);
  int httpCode = http.GET();  
  if(httpCode > 0) 
    {
      if(httpCode == HTTP_CODE_OK) 
        {       
          payload = http.getString();                 
          return payload;
        } 
      else 
        {
          Serial.println(String("wifiGetString failed, error code = ") + httpCode + " URL = " + fileLink);
          return "";
        }
    }
 return "";
}


void wifiDisconnect(void)
{
   WiFi.disconnect(true);   
}

bool wifiWaitConnection(uint32_t timeoutMs)
{
  unsigned long m = millis();

  while(millis()-m < timeoutMs)
    if (wifiIsConnected()) 
      {
        return true;
      }
  else delay(50);

  return false;
}

