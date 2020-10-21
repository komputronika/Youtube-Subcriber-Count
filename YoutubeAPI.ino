/*****************************************************\

    Mambaca Statistik Channel YouTube menggunakan
    NodeMCU atau board ESP8266 sejenis dan menampilkan pada
    8 Digit 7 segment display berbasis MAX7219

    Hardware utama:
    1. NodeMCU (atau board ESP8266 lainnya)
       (http://bit.ly/beli-nodemcu)
    2. 8 digit 7 segment display Max7219
    
    Dibuat oleh: Komputronika
    Tanggal: 20 Oktober 2016
    
    Youtube Channel: https://www.youtube.com/channel/UCcmgpnfQrljrXDoa6Go4mGg
    Blog: https://arduino-elektro.blogspot.com  

\*****************************************************/

//-------------------------
// Library standar untuk ESP8266
//-------------------------

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//-------------------------
// Library tambahan
//-------------------------

#include <YoutubeApi.h>
#include <ArduinoJson.h>
#include "LedControl.h"

// https://github.com/witnessmenow/arduino-youtube-api
// https://github.com/bblanchon/ArduinoJson

//-------------- Ubah di sini -------------------

// Your WIFI name (SSID) and password
char ssid[]        = "Wifi"; 
char password[]    = "password"; 

// Your google apps API Token and channel's URL
#define API_KEY    "api-key-youtube-anda"
#define CHANNEL_ID "channel-id-anda"

// Cara mendapatkan API Key Youtube:
// https://www.slickremix.com/docs/get-api-key-for-youtube/

//---------------------------------------------

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

// Pin dari NodeMCU ke Display Max7219
// D8 = DIN
// D7 = CS
// D6 = CLK
//                         DIN,CLK,CS
LedControl lc = LedControl(D8, D6, D7, 1);

unsigned long waktuBaca = 45000; // Dalam satuan millidetik
unsigned long waktuMulai;

//-------------------------
// Fungsi setup
//-------------------------
void setup() {

    Serial.begin(115200);

    lc.shutdown(0, false);  // Enable display
    lc.setIntensity(0, 15); // Set brightness (0 is min, 15 is max)
    lc.clearDisplay(0);     // Clear display register

    // Set WiFi ke mode station
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // Menghubungkan ke Wifi
    Serial.print("Menghubungkan ke Wifi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi terhubung");
    Serial.print("IP address: ");
    IPAddress ip = WiFi.localIP();
    Serial.println(ip);

}

//-------------------------
// Fungsi untuk menampilkan digit per digit di display
//-------------------------
void printNumber(int n) {
    byte i;
    byte digit[8] = {'xxxxxxxx'};
    byte pos = 7;
    bool dot;

    while (n > 0) {
        i = n % 10;
        digit[pos--] = i;
        n = n / 10;
    }

    for (int x = 0; x < 8; x++) {
        dot = ((x + 1) % 3 == 1 and x != 0);
        lc.setDigit(0, x, digit[7 - x], dot);
    }
}

//-------------------------
// Fungsi loop utama
//-------------------------
void loop() {
    if (millis() > waktuMulai) {
        if (api.getChannelStatistics(CHANNEL_ID)) {
            Serial.print("Jumlah subscriber: ");
            Serial.println(api.channelStats.subscriberCount);
            printNumber(api.channelStats.subscriberCount);
        }
        waktuMulai = millis() + waktuBaca;
    }
}
