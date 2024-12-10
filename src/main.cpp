
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char *ssid = "YOUR-WIFI-CONNECTION-NAME";
const char *password = "WIFI-CONNECTION-PASSWORD";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setup()
{
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(19800); // +5:30 timezone in seconds
}

void loop()
{
  timeClient.update();

  // Get current time components
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();
  int currentSecond = timeClient.getSeconds();

  // Calculate date and month from epoch time
  time_t rawTime = timeClient.getEpochTime();
  struct tm *timeInfo = gmtime(&rawTime);
  int currentDay = timeInfo->tm_mday;         // Extract day
  int currentMonth = timeInfo->tm_mon + 1;    // Extract month (tm_mon is 0-based)
  int currentYear = timeInfo->tm_year + 1900; // Extract year (tm_year is years since 1900)

  // Combine into a single string variable
  char dateTime[20]; // Ensure sufficient size
  snprintf(dateTime, sizeof(dateTime), "%02d:%02d:%02d %02d:%02d:%04d",
           currentHour, currentMinute, currentSecond, currentDay, currentMonth, currentYear);

  // Print the dateTime string
  Serial.println(dateTime);

  delay(2000);
}