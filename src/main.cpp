
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char *ssid = "cracked 0027";
const char *password = "5FdcD9D3";

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
  // int currentSecond = timeClient.getSeconds(); (if u want seconds value then uncomment this line)

  // Calculate date and month from epoch time
  time_t rawTime = timeClient.getEpochTime();
  struct tm *timeInfo = gmtime(&rawTime);
  int currentDay = timeInfo->tm_mday;         // Extract day
  int currentMonth = timeInfo->tm_mon + 1;    // Extract month (tm_mon is 0-based)
  int currentYear = timeInfo->tm_year + 1900; // Extract year (tm_year is years since 1900)

  String dateTime = String(currentHour) + ":" +
                    String(currentMinute) + " " +
                    String(currentDay) + "-" +
                    String(currentMonth) + "-" +
                    String(currentYear);

  // Print the dateTime string
  Serial.println(dateTime);

  delay(2000);
}