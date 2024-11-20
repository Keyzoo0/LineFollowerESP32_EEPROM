



void program(int dataSensor, byte mode) {
    switch (dataSensor) {
    // WHite LIne

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

    //LEFT
    case 0b00000000000111:       error = -13;    break;
    case 0b00000000001110:       error = -10;    break;
    case 0b00000000011100:       error = -8;     break;
    case 0b00000000111000:       error = -6;     break;
    case 0b00000001110000:       error = -4;     break;
    case 0b00000011100000:       error = -2;     break;

    //RIGHT
    case 0b00000111000000:       error = 2;      break;
    case 0b00001110000000:       error = 4;      break;
    case 0b00011100000000:       error = 6;      break;
    case 0b00111000000000:       error = 8;      break;
    case 0b01110000000000:       error = 10;     break;
    case 0b11100000000000:       error = 13;     break;

    case 0b00000000000001:       error = -13;    break;
    case 0b00000000000011:       error = -12;    break;
    case 0b00000000000010:       error = -13;    break;
    case 0b00000000000110:       error = -11;    break;
    case 0b00000000000100:       error = -10;     break;
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
    case 0b00100000000000:       error = 10;      break;
    case 0b01100000000000:       error = 11;     break;
    case 0b01000000000000:       error = 13;     break;
    case 0b11000000000000:       error = 12;     break;
    case 0b10000000000000:       error = 13;     break;

    case 0b00000111111111:       error = 2;   break;
    case 0b00000011111111:       error = 1;   break;
    case 0b00000001111111:       error = 0;   break;
    case 0b00000000111111:       error = -1;  break;
    case 0b00000000011111:       error = -2;  break;
    case 0b11111000000000:       error = 2;   break;
    case 0b11111100000000:       error = 1;   break;
    case 0b11111110000000:       error = 0;   break;
    case 0b11111111000000:       error = -1;  break;
    case 0b11111111100000:       error = -2;  break;

    case 0b01111000011110:       error = 0;  break;
    case 0b00111000011110:       error = 0;  break;
    case 0b00000111100000:       error = 0;  break;
    case 0b00001111110000:       error = 0;  break;
    case 0b00011111111000:       error = 0;  break;
    case 0b00111111111100:       error = 0;  break;

    }

    if (abs(error) > 1) {
      sumError +=   error;
    }
    else {
      sumError = 0;
    }

    P  = error * Kp[selectPresetPIDPlay];
    I = sumError * Ki[selectPresetPIDPlay] ;
    D  = (error - lastError) * Kd[selectPresetPIDPlay] ;
    
    int16_t moveVal = P + I + D;
    int16_t leftW = maxS - moveVal;
    int16_t rightW = maxS + moveVal;
    
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
