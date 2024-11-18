
// void keyInput() {
// while(1){
//   if(touchUp(btnUp)){
//     lcd.clearDisplay();
//     xKey++;
//     if(xKey > 9) xKey = 0;
//   }
//   if(touchUp(btnDown)){
//     lcd.clearDisplay();
//     xKey--;
//     if(xKey < 0) xKey = 9;
//   }

//   if(touchUp(btnMinus)){
//     lcd.clearDisplay();
//     yKey++;
//     if(yKey > 2) yKey = 0;
//   }
//   if(touchUp(btnPlus)){
//     lcd.clearDisplay();
//     yKey--;
//     if(yKey < 0) yKey = 2;
//   }

  

//   if(touchUp(btnOk)){
//     lcd.clearDisplay();
//     if((xKey == 0) && (yKey == 1) && (key == NOCAPS)){
//       key = CAPS;
//     }
//     else if((xKey == 0) && (yKey == 1) && (key == CAPS)){
//       key = NOCAPS;
//     }
//     else if((xKey == 0) && (yKey == 2) && (num == false)){
//       num = true;
//       key = NUMBERS;
//     }
//     else if((xKey == 0) && (yKey == 2) && (num == true)){
//       num = false;
//       key = NOCAPS;
         
//     }else if((yKey == 2 ) && (xKey == 9) && (num == false)){
//       PASSWORD = Input;
//       WiFi.begin(SSID , PASSWORD);
      
//       while (WiFi.status() != WL_CONNECTED) {
//         delay(1000);
//         lcd_char(1 , 1 , 1 , "Connecting..." , true , true , true );
//         lcd.clearDisplay();
//       }
      
//       lcd_char(1 , 1 , 1 , "Connected!!!" , true , true , true );
//       delay(1000);
//       lcd.clearDisplay();
      
//       // while(1){
//         checkUpdate();
//       // }
    
//     }else{
//       if(key == NOCAPS){
//       Input = Input + Letters[yKey][xKey];
//       }
//       else if(key == CAPS){
//       Input = Input + LettersCaps[yKey][xKey];     
//       }else if(key == NUMBERS){
//       Input = Input + Number[yKey][xKey];
//       }
//     }
//   }

 
  
//   if(touchUp(btnBack)){
//    lcd.clearDisplay();
//    Input.remove(Input.length() - 1);
//   }
  
//   switch(key){
//   case CAPS : displayKeyCapsLetter(); break; 
//   case NOCAPS : displayKeyNoCapsLetter(); break; 
//   case NUMBERS : displayKeyNumber(); break; 
//   }
//   displayKeyInput();
//   lcd.display();
//   }//end while 1
// }


// void displayKeyInput(){
//   lcd_char(1 , 0 , 0 , "ssid : " + SSID , true , false , false);
//   lcd_char(1 , 50 -(Input.length()*2) , 10 , Input+"_" , true , false , false);
  
// }

// void displayKeyCapsLetter(){
//   for(int i = 0 ; i < 10 ; i++){
//       for(int j = 0 ; j < 3 ; j++){
//       if((xKey == i) && (yKey == j) ){ 

//         if ((yKey == 1 ) && (xKey == 0)) lcd.fillRect(i*13 ,  (j*13)+24 , 7 , 9, SH110X_WHITE);
//         else lcd.fillRect(i*13 ,  (j*13)+24 , 7 , 9, SH110X_WHITE);
//         lcd_char(1 , i*13+1 , (j*13)+25, LettersCaps[j][i] , false , false , false ); 
//       }
//       else 
//       // lcd.fillRect(i*13 ,  (j*13)+24 , 7 , 9, SH110xKey_BLACK);
//       lcd_char(1 , i*13+1 , (j*13)+25, LettersCaps[j][i] , true ,  false ,  false);
//       }
//     }
// }


// void displayKeyNoCapsLetter(){
//   for(int i = 0 ; i < 10 ; i++){
//       for(int j = 0 ; j < 3 ; j++){
//       if((xKey == i) && (yKey == j) ){ 
//         lcd.fillRect(i*13 ,  (j*13)+24 , 7 , 9, SH110X_WHITE);
//         lcd_char(1 , i*13+1 , (j*13)+25, Letters[j][i] , false , false , false ); 
//       }
//       else 
//       // lcd.fillRect(i*13 ,  (j*13)+24 , 7 , 9, SH110xKey_BLACK);
//       lcd_char(1 , i*13+1 , (j*13)+25, Letters[j][i] , true ,  false ,  false);
//       }
//     }
// }


// void displayKeyNumber(){
//   for(int i = 0 ; i < 10 ; i++){
//       for(int j = 0 ; j < 3 ; j++){
//       if((xKey == i) && (yKey == j) ){ 
//         lcd.fillRect(i*13 ,  (j*13)+24 , 7 , 9, SH110X_WHITE);
//         lcd_char(1 , i*13+1 , (j*13)+25, Number[j][i] , false , false , false ); 
//       }
//       else 
//       // lcd.fillRect(i*13 ,  (j*13)+24 , 7 , 9, SH110xKey_BLACK);
//       lcd_char(1 , i*13+1 , (j*13)+25, Number[j][i] , true ,  false ,  false);
//       }
//     }
// }

// void scanWifi(){

// while(1){
// int  n = WiFi.scanNetworks();
// String ssid[n];
// String rssi[n];
    
   
//     if (n == 0) {
//         lcd_char(1 , 0 , 15 , "no networks found" , true , false  , true );
//     } else {
//       while(1){
//         lcd_char(1 , 10 , 0 , "Wi-Fi Available :" , true , false  , true); 
//         if(touchUp(Button_DOWN)){
//           lcd.clearDisplay();
//           idxWifi++;
//           if(idxWifi >= n) idxWifi = 0;
//         }
//         if(touchUp(Button_UP)){
//           lcd.clearDisplay();
//           idxWifi--;
//           if(idxWifi <= 0 ) idxWifi = n;
//         }
//         if(touchUp(Button_RUN)){
//           lcd.clearDisplay();
//           ESP.restart();
//         } 
//         if(touchUp(Button_OK)){
//           lcd.clearDisplay();
//           SSID = ssid[idxWifi];
//           keyInput();
//         }
//         Serial.print(n);
//         Serial.println(" networks found");
//         for (int i = 0; i < n; ++i) {
//             // Print SSID and RSSI for each network found
//             ssid[i] = WiFi.SSID(i);
//             rssi[i] = WiFi.RSSI(i);
//         }


//       for (int i = 0; i < n; ++i) {
//             String ssid2 = ssid[i]  + "\n" ;
//             if(i == idxWifi ) lcd_char(1 , 0 , 14*(i+1) , ">" , true , false  , false);        
//             else lcd_char(1 , 0 , 14*(i+1) , " " , true , false , false);        
//             lcd_char(1 , 0 , 14*(i+1) , " " + ssid2 , true , false  , false );
//         }

//         lcd.display();
//       }//end while(1)

//     }
//   }//end while 1
// }




// void checkUpdate() {
//   if ((WiFi.status() == WL_CONNECTED)) {
//     Serial.println("Checking Update!");
//     HTTPClient http;
//     String response;
//     String url = UPDATE_URL;
//     http.begin(url);
//     int httpCode = http.GET();  // Get HTTP response code

//     if (httpCode == HTTP_CODE_OK) {  // Make sure the request is successful
//       response = http.getString();
//       Serial.println(response);

//       StaticJsonDocument<1024> doc;
//       deserializeJson(doc, response);
//       JsonObject obj = doc.as<JsonObject>();
//       String version = obj[String("version")];
//       String url_update = obj[String("url")];

//       if (version.toDouble() > FIRMWARE_VERSION) {
//         Serial.println("Update Tersedia!");
//         lcd.clearDisplay();
//         while(1){
//           lcd_char(1 , 2 , 2 , "Update Tersedia v" + version , true , false , true);
//           lcd_char(1 , 2 , 12 , "Ingin Update?", true , false , true);
//           lcd_char(2 , 10 , 25 , "Yes | No", true , false , true);
          
//           if(touchUp(Button_UP)){
//             for (byte x = 0; x < 100; x++) {
//               lcd_char(1, 0, 0, "Downloading v"+version, true, true, false);
//               lcd_char(3, 29, 10, "EEOS", true, false, false);
//               lcd_loading(8, 42, x, true, false, true);
//             }
//             lcd.clearDisplay();
           
//             break;
//           }

//           if(touchUp(Button_PLUS )){
//             ESP.restart();
//           }

//         } 
//           lcd_char(1, 0, 0, "Installing v"+version, true, false, true);
//           lcd_char(3, 10, 15, "EEOTA", true, false, true);
         
//         while(1){
//           if (updateFirmware(url_update) == HTTP_UPDATE_OK) {
//             WiFi.disconnect(true);
//             WiFi.mode(WIFI_OFF);
//             ESP.restart();  // Restart ESP32 after successful update
//           }
//         }
//       } else {
//           lcd.clearDisplay();
//           lcd_char(1 , 2 , 2 , "Versi OS Anda v" + version , true , false , true);
//           lcd_char(1 , 2 , 15 , "Adalah Versi Terbaru !!" , true , false , true);
//           delay(3000);
//           ESP.restart();
//       }
//     } else {
//       Serial.printf("Failed to get update info, HTTP code: %d\n", httpCode);
//     }

//     http.end();  // Close the connection
//   }
// }
