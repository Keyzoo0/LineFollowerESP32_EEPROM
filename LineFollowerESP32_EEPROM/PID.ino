



void program(int dataSensor, byte mode , int speed , byte pid) {
switch(mode){
  case 0://center
    switch (dataSensor) {
        // WHite LIne

        case 0b11111111111110:       error = -13;    break;
        case 0b11111111111100:       error = -12;    break;
        case 0b11111111111101:       error = -13;    break;
        case 0b11111111111001:       error = -11;    break;
        case 0b11111111111011:       error = -10;     break;
        case 0b11111111110011:       error = -8;     break;
        case 0b11111111110111:       error = -7;     break;
        case 0b11111111100111:       error = -6;     break;
        case 0b11111111101111:       error = -5;     break;
        case 0b11111111001111:       error = -4;     break;
        case 0b11111111011111:       error = -3;     break;
        case 0b11111110011111:       error = -2;     break;
        case 0b11111110111111:       error = -1;     break;
        case 0b11111100111111:       error = 0;      break;
        case 0b11111101111111:       error = 1;      break;
        case 0b11111001111111:       error = 2;      break;
        case 0b11111011111111:       error = 3;      break;
        case 0b11110011111111:       error = 4;      break;
        case 0b11110111111111:       error = 5;      break;
        case 0b11100111111111:       error = 6;      break;
        case 0b11101111111111:       error = 7;      break;
        case 0b11001111111111:       error = 8;      break;
        case 0b11011111111111:       error = 10;     break;
        case 0b10011111111111:       error = 11;     break;
        case 0b10111111111111:       error = 13;     break;
        case 0b00111111111111:       error = 12;     break;
        case 0b01111111111111:       error = 13;     break;

        // BLACK LINE

        //LEFT
        case 0b00000000000111:       error = -13;    break;
        case 0b00000000001111:       error = -12;    break;
        case 0b00000000001110:       error = -10;    break;
        case 0b00000000011110:       error = -8;    break;
        case 0b00000000011100:       error = -7;     break;
        case 0b00000000111100:       error = -6;     break;
        case 0b00000000111000:       error = -5;     break;
        case 0b00000001111000:       error = -4;     break;
        case 0b00000001110000:       error = -3;     break;
        case 0b00000011110000:       error = -2;     break;
        case 0b00000011100000:       error = -1;     break;

        //RIGHT
        case 0b00000111000000:       error = 1;      break;
        case 0b00001111000000:       error = 2;      break;
        case 0b00001110000000:       error = 3;      break;
        case 0b00011110000000:       error = 4;      break;
        case 0b00011100000000:       error = 5;      break;
        case 0b00111100000000:       error = 6;      break;
        case 0b00111000000000:       error = 7;      break;
        case 0b01111000000000:       error = 8;     break;
        case 0b01110000000000:       error = 10;     break;
        case 0b11110000000000:       error = 12;     break;
        case 0b11100000000000:       error = 13;     break;

        case 0b00000000000001:       error = -13;    break;
        case 0b00000000000011:       error = -12;    break;
        case 0b00000000000010:       error = -11;    break;
        case 0b00000000000110:       error = -10;    break;
        case 0b00000000000100:       error = -9;     break;
        case 0b00000000001100:       error = -8;     break;
        case 0b00000000001000:       error = -7;     break;
        case 0b00000000011000:       error = -6;     break;
        case 0b00000000010000:       error = -5;     break;
        case 0b00000000110000:       error = -4;     break;
        case 0b00000000100000:       error = -3;     break;
        case 0b00000001100000:       error = -2;     break;
        case 0b00000001000000:       error = -1;     break;
        case 0b00000011000000:       error = 0;      break;
        case 0b00000010000000:       error = 1;      break;
        case 0b00000110000000:       error = 2;      break;
        case 0b00000100000000:       error = 3;      break;
        case 0b00001100000000:       error = 4;      break;
        case 0b00001000000000:       error = 5;      break;
        case 0b00011000000000:       error = 6;      break;
        case 0b00010000000000:       error = 7;      break;
        case 0b00110000000000:       error = 8;      break;
        case 0b00100000000000:       error = 9;      break;
        case 0b01100000000000:       error = 10;     break;
        case 0b01000000000000:       error = 11;     break;
        case 0b11000000000000:       error = 12;     break;
        case 0b10000000000000:       error = 13;     break;

    

        
      }break;

  case 1://right
    switch (dataSensor) {
        // // WHite LIne

        // case 0b11111111111110:       error = -13;    break;
        // case 0b11111111111100:       error = -12;    break;
        // case 0b11111111111101:       error = -13;    break;
        // case 0b11111111111001:       error = -11;    break;
        // case 0b11111111111011:       error = -10;     break;
        // case 0b11111111110011:       error = -8;     break;
        // case 0b11111111110111:       error = -7;     break;
        // case 0b11111111100111:       error = -6;     break;
        // case 0b11111111101111:       error = -5;     break;
        // case 0b11111111001111:       error = -4;     break;
        // case 0b11111111011111:       error = -3;     break;
        // case 0b11111110011111:       error = -2;     break;
        // case 0b11111110111111:       error = -1;     break;
        // case 0b11111100111111:       error = 0;      break;
        // case 0b11111101111111:       error = 1;      break;
        // case 0b11111001111111:       error = 2;      break;
        // case 0b11111011111111:       error = 3;      break;
        // case 0b11110011111111:       error = 4;      break;
        // case 0b11110111111111:       error = 5;      break;
        // case 0b11100111111111:       error = 6;      break;
        // case 0b11101111111111:       error = 7;      break;
        // case 0b11001111111111:       error = 8;      break;
        // case 0b11011111111111:       error = 10;     break;
        // case 0b10011111111111:       error = 11;     break;
        // case 0b10111111111111:       error = 13;     break;
        // case 0b00111111111111:       error = 12;     break;
        // case 0b01111111111111:       error = 13;     break;

        // BLACK LINE



        case 0b00000000000001:       error = -7;    break;
        case 0b00000000000011:       error = -6;    break;
        case 0b00000000000010:       error = -5;    break;
        case 0b00000000000110:       error = -4;    break;
        case 0b00000000000100:       error = -3;     break;
        case 0b00000000001100:       error = -2;     break;
        case 0b00000000001000:       error = -1;     break;
        case 0b00000000011000:       error = 0;     break;
        case 0b00000000010000:       error = 1;     break;
        case 0b00000000110000:       error = 2;     break;
        case 0b00000000100000:       error = 3;     break;
        case 0b00000001100000:       error = 4;     break;
        case 0b00000001000000:       error = 5;     break;
        case 0b00000011000000:       error = 6;      break;
        case 0b00000010000000:       error = 7;      break;
        case 0b00000110000000:       error = 8;      break;
        case 0b00000100000000:       error = 9;      break;
        case 0b00001100000000:       error = 10;      break;
        case 0b00001000000000:       error = 11;      break;
        case 0b00011000000000:       error = 12;      break;
        case 0b00010000000000:       error = 13;      break;
        case 0b00110000000000:       error = 13;      break;
        case 0b00100000000000:       error = 13;      break;
        case 0b01100000000000:       error = 13;     break;
        case 0b01000000000000:       error = 13;     break;
        case 0b11000000000000:       error = 12;     break;
        case 0b10000000000000:       error = 13;     break;

    
      }break;

  case 2://left
    switch (dataSensor) {
        // // WHite LIne

        // case 0b11111111111110:       error = -13;    break;
        // case 0b11111111111100:       error = -12;    break;
        // case 0b11111111111101:       error = -13;    break;
        // case 0b11111111111001:       error = -11;    break;
        // case 0b11111111111011:       error = -10;     break;
        // case 0b11111111110011:       error = -8;     break;
        // case 0b11111111110111:       error = -7;     break;
        // case 0b11111111100111:       error = -6;     break;
        // case 0b11111111101111:       error = -5;     break;
        // case 0b11111111001111:       error = -4;     break;
        // case 0b11111111011111:       error = -3;     break;
        // case 0b11111110011111:       error = -2;     break;
        // case 0b11111110111111:       error = -1;     break;
        // case 0b11111100111111:       error = 0;      break;
        // case 0b11111101111111:       error = 1;      break;
        // case 0b11111001111111:       error = 2;      break;
        // case 0b11111011111111:       error = 3;      break;
        // case 0b11110011111111:       error = 4;      break;
        // case 0b11110111111111:       error = 5;      break;
        // case 0b11100111111111:       error = 6;      break;
        // case 0b11101111111111:       error = 7;      break;
        // case 0b11001111111111:       error = 8;      break;
        // case 0b11011111111111:       error = 10;     break;
        // case 0b10011111111111:       error = 11;     break;
        // case 0b10111111111111:       error = 13;     break;
        // case 0b00111111111111:       error = 12;     break;
        // case 0b01111111111111:       error = 13;     break;

        // BLACK LINE



        case 0b00000000000001:       error = -13;    break;
        case 0b00000000000011:       error = -13;    break;
        case 0b00000000000010:       error = -13;    break;
        case 0b00000000000110:       error = -13;    break;
        case 0b00000000000100:       error = -13;     break;
        case 0b00000000001100:       error = -13;     break;
        case 0b00000000001000:       error = -13;     break;
        case 0b00000000011000:       error = -12;     break;
        case 0b00000000010000:       error = -11;     break;
        case 0b00000000110000:       error = -10;     break;
        case 0b00000000100000:       error = -9;     break;
        case 0b00000001100000:       error = -8;     break;
        case 0b00000001000000:       error = -7;     break;
        case 0b00000011000000:       error = -6;      break;
        case 0b00000010000000:       error = -5;      break;
        case 0b00000110000000:       error = -4;      break;
        case 0b00000100000000:       error = -3;      break;
        case 0b00001100000000:       error = -2;      break;
        case 0b00001000000000:       error = -1;      break;
        case 0b00011000000000:       error = 0;      break;
        case 0b00010000000000:       error = 1;      break;
        case 0b00110000000000:       error = 2;      break;
        case 0b00100000000000:       error = 3;      break;
        case 0b01100000000000:       error = 4;     break;
        case 0b01000000000000:       error = 5;     break;
        case 0b11000000000000:       error = 6;     break;
        case 0b10000000000000:       error = 7;     break;

    
      }break;

}
    if (abs(error) > 1) {
      sumError +=   error;
    }
    else {
      sumError = 0;
    }

    P  = error * Kp[pid];
    I = sumError * Ki[pid] ;
    D  = (error - lastError) * Kd[pid] ;
    
    int16_t moveVal = P + I + D;
    int16_t leftW = speed - moveVal;
    int16_t rightW = speed + moveVal;
    
    leftW = constrain(leftW, -255, 255);
    rightW = constrain(rightW, -255, 255);
    
    if(dataSensor == 0b11111111111111){
    stopMotor();
    }
    else{ 
    pwmMotor(leftW, rightW); // L, R
    }
    lastError = error;

}
