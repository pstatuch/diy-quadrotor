
#include <Arduino.h>
#include "receiver.h"

void setup(){
    initReceiver();

}

void loop(){
    delay(10);
    updateChanels();

}