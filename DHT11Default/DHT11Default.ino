#include <WiFi.h>
#include <ThingSpeak.h>
#include <SimpleDHT.h>   // 引入 SimpleDHT 庫

// 替換成你的Wi-Fi名稱和密碼
const char* ssid = "labor";  // Wi-Fi 名稱
const char* password = "98668800";  // Wi-Fi 密碼

// ThingSpeak 的頻道設定
unsigned long channelID = 2957957;  // 替換成你的 ThingSpeak 頻道 ID
const char* writeAPIKey = "XNUPYCIRN01Y7W0T";  // 替換成你的 API Key

// DHT11 感測器設定
#define DHTPIN 4  // DHT 資料腳位接到 GPIO4
SimpleDHT11 dht11(DHTPIN);  // 初始化 SimpleDHT11 物件

WiFiClient client;

void setup() {
  // 開啟序列埠以便進行調試
  Serial.begin(115200);

  // 連接 WiFi
  connectWiFi();

  // 初始化 ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // 儲存溫度和濕度
  byte temperature = 0;
  byte humidity = 0;
  byte pdata[40];  // 用來儲存其他的資料

  // 讀取溫度和濕度數據
  int ret = dht11.read(&temperature, &humidity, pdata);

  if (ret != SimpleDHTErrSuccess) {
    Serial.print("DHT11 讀取失敗，錯誤代碼: ");
    Serial.println(ret);  // 顯示錯誤代碼
    return;
  }

  // 顯示讀取到的數據
  Serial.print("濕度: ");
  Serial.print(humidity);
  Serial.print("%  溫度: ");
  Serial.print(temperature);
  Serial.println("°C");

  // 將數據傳送到 ThingSpeak
  sendToThingSpeak(humidity, temperature);

  // 每 15 秒更新一次
  delay(15000);  // 15秒
}

void connectWiFi() {
  Serial.print("連接 WiFi 中...");
  WiFi.begin(ssid, password);

  // 等待 Wi-Fi 連接成功
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("成功連接到 WiFi");
}

void sendToThingSpeak(int humidity, int temperature) {
  // 將濕度數據寫入 Field 1，將溫度數據寫入 Field 2
  ThingSpeak.setField(1, humidity);   // Field 1 -> 濕度
  ThingSpeak.setField(2, temperature); // Field 2 -> 溫度

  // 發送請求到 ThingSpeak
  int httpCode = ThingSpeak.writeFields(channelID, writeAPIKey);
  
  if (httpCode == 200) {
    // 請求成功
    Serial.println("數據已成功傳送到 ThingSpeak");
  } else {
    // 請求失敗
    Serial.println("傳送數據到 ThingSpeak 失敗");
  }
}
