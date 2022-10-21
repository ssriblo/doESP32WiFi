#ifndef __GINSTR_WIFI__
#define __GINSTR_WIFI__

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <WiFiUdp.h>  

#define WIFI_GOOGLE_PING_INTERVAL_MS    30000
#define WIFI_TIME_SYNC_INTERVAL_MS      120000
#define WIFI_MAX_TIME_SYNC_ATTEMPTS     3

#define WIFI_DEF_NTP1_ADDR   "0.pool.ntp.org"
#define WIFI_DEF_NTP2_ADDR   "1.pool.ntp.org"
#define WIFI_DEF_NTP3_ADDR   "2.pool.ntp.org"

#define WIFI_PING_LINK "google.com"
#define WIFI_PING_TEXT "connected"


void wifiStationConnected_evt(WiFiEvent_t event);
void wifiGotIP_evt(WiFiEvent_t event);
void wifiStationDisconnected_evt(WiFiEvent_t event);


void wifiInit(String ssid, String pass);
bool wifiIsInternetConnected(void);
bool wifiIsConnected(void);
bool wifiPingGoogle(void);
String wifiGetString(String fileLink);

//bool wifiSyncTime(String sNtp1 = WIFI_DEF_NTP1_ADDR, String sNtp2 = WIFI_DEF_NTP2_ADDR, String sNtp3 = WIFI_DEF_NTP3_ADDR);

int8_t wifiGetRSSI(void);
uint8_t wifiGetSSPercents(void);
void wifiDisconnect(void);
bool wifiWaitConnection(uint32_t timeoutMs = 30000);

String wifiGetTimeString(String url);
time_t wifiGetGinstrTime(String url);
bool   wifiSyncTime(String url);

#endif
