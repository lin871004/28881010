#include "time_utils.h"
#include <Arduino.h>  // 為了使用 Serial.print 等
#include <time.h>

void printTimeFields(struct tm timeinfo) {
  Serial.println("----- Parsed Time Info -----");
  Serial.print("Year: ");
  Serial.println(timeinfo.tm_year + 1900);

  Serial.print("Month: ");
  Serial.println(timeinfo.tm_mon + 1);

  Serial.print("Day: ");
  Serial.println(timeinfo.tm_mday);

  Serial.print("Hour: ");
  Serial.println(timeinfo.tm_hour);

  Serial.print("Minute: ");
  Serial.println(timeinfo.tm_min);

  Serial.print("Second: ");
  Serial.println(timeinfo.tm_sec);
  Serial.println("-----------------------------");
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Connection Err");
    return;
  }

  Serial.print("Time: ");
  Serial.println(&timeinfo, "%H:%M:%S");

  Serial.print("Date: ");
  Serial.println(&timeinfo, "%d/%m/%Y   %Z");

  printTimeFields(timeinfo);
}
