#include <WiFi.h>
#include "time_utils.h"  // 引入你剛才寫的副程式檔案

#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     28800
#define UTC_OFFSET_DST 0

void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdb";
  Serial.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to WiFi... ");
  WiFi.begin("labor", "98668800", 6);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    spinner();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Online");
  Serial.println("Updating time...");

  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}

void loop() {
  printLocalTime();  // 呼叫副程式（來自 time_utils.cpp）
  delay(1000);
}
