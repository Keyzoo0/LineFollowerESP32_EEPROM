// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <ArduinoJson.h>
// #include <ESP32httpUpdate.h>
// #include <SPI.h>


// #define FIRMWARE_VERSION 1.3
// #define UPDATE_URL "https://keyzoo0.github.io/firmware.json" 


// enum key_type {
//   CAPS,
//   NOCAPS,
//   NUMBERS
// };

// int idxWifi = 0;
 

// String SSID = "";
// String PASSWORD = "";



// int key = NOCAPS ;
// bool num = false;
// String Input = "Akubagas18999";

// int xKey = 0 , yKey = 0 ;


// char* Letters[3][10]={
//             {"q","w","e","r","t","y","u","i","o","p"},
//             {"^","a","s","d","f","g","h","j","k","l"},
//             {"&","z","x","c"," ","v","b","n","m",">"}
//                     };
// char* LettersCaps[3][10]={
//             {"Q","W","E","R","T","Y","U","I","O","P"},
//             {"^","A","S","D","F","G","H","J","K","L"},
//             {"&","Z","X","C"," ","V","B","N","M",">"}
//                     };
// char* Number[3][10]={
//             {"1","2","3","4","5","6","7","8","9","0"},
//             {"@","#","$","_","-","+","(",")","/","|"},
//             {"&",",",".","=","[","]",":",";","!","?"}
//                     };


// t_httpUpdate_return updateFirmware(String url_update) {
//   if (WiFi.status() == WL_CONNECTED) {
//     Serial.printf("Starting firmware update from: %s\n", url_update.c_str());

//     // Perform the firmware update
//     t_httpUpdate_return ret = ESPhttpUpdate.update(url_update);
    
//     // Handle the update result
//     switch (ret) {
//       case HTTP_UPDATE_FAILED:
//         Serial.printf("[Update] Update Gagal! Error (%d): %s\n",
//                       ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
//         break;

//       case HTTP_UPDATE_NO_UPDATES:
//         Serial.println("[Update] Update Tidak Tersedia!");
//         break;

//       case HTTP_UPDATE_OK:
//         Serial.println("[Update] Update Berhasil!");
//         break;
//     }

//     return ret;
//   }

//   return HTTP_UPDATE_FAILED;  // Return failed status if not connected to WiFi
// }




