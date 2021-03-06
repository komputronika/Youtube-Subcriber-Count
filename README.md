# Subscriber Youtube dengan Youtube API dan NodeMCU

Program untuk menampilkan jumlah subscriber Youtube pada display 8 digit 7 segment Max7219 menggunakan NodeMCU. 

## Instalasi

1. Download dan buka file YoutubeAPI.ino di Arduino IDE.
3. Install library yang diperlukan (YoutubeApi dan LedControl)
3. Edit Wifi dan password, serta ketik API KEY dan CHANNEL ID Anda.
4. Upload sketch ke NodeMCU  
5. Ikuti skema di bawah ini:

![alt text](https://i.imgur.com/CyH4RfY.png)

## Cara Mendapatkan API Key Youtube

* Buka [Google Developer Dashboard](https://console.developers.google.com) dan buatlah sebuah proyek baru. Nama proyek bebas, misalnya "Youtube Subs".
* Pada bagian menu sisi kiri, buka ["Credentials"](https://console.developers.google.com/apis/credentials) dan buat sebuah API Key.
* Kemudian klik pada menu ["Library"](https://console.developers.google.com/apis/library), cari  ["YouTube Data API v3"](https://console.developers.google.com/apis/library/youtube.googleapis.com), kemudian klik "Enable" untuk proyek anda.
* Kembali ke menu ["Credentials"](https://console.developers.google.com/apis/credentials), silahkan copas API Key anda.
* Coba buka di browser dan periksa apakah anda sudah melihat data JSON (Ubah CHANNEL_ID dan API_KEY!):

`https://www.googleapis.com/youtube/v3/channels?part=statistics&id=CHANNEL_ID&key=API_KEY`


