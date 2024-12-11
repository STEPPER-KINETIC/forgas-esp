#include <Arduino.h>
#include "Item.h"


Item *item = new Item();

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 13, 12);
  delay(3000);
  item->setup();
}

void loop() {
  item->update();
  delay(1000 / ticksPS);
}