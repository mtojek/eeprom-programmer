#define SHIFT_CLK 2
#define SHIFT_LATCH 3
#define SHIFT_DATA 4

#define EEPROM_D0 5
#define EEPROM_D7 12

#define WRITE_EN 13

#define OPCODE_BRK 0

void setAddress(unsigned int address, bool outputEnable) {
  digitalWrite(SHIFT_LATCH, LOW);
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, (address >> 8) | (outputEnable ? 0 : 0x80));
  shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, address);
  digitalWrite(SHIFT_LATCH, HIGH);
  digitalWrite(SHIFT_LATCH, LOW);
}

byte readEEPROM(unsigned int address) {
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    pinMode(pin, INPUT);
  }

  setAddress(address, true);
  byte data = 0;
  for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin -= 1) {
    data = (data << 1) + digitalRead(pin);
  }
  return data;
}

byte writeEEPROM(unsigned int address, byte data) {
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    pinMode(pin, OUTPUT);
  }

  setAddress(address, false);
  for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin += 1) {
    digitalWrite(pin, data & 1);
    data = data >> 1;
  }
  digitalWrite(WRITE_EN, LOW);
  delayMicroseconds(1);
  digitalWrite(WRITE_EN, HIGH);
  delay(10);
}

void printContents(unsigned int offset, unsigned int len) {
  for (unsigned int base = offset; base <= offset + len; base += 16) {
    byte data[16];
    for (unsigned int offset = 0; offset < 16; offset += 1) {
      data[offset] = readEEPROM(base + offset);
    }

    char buf[80];
    sprintf(buf, "%04x: %02x %02x %02x %02x %02x %02x %02x %02x    %02x %02x %02x %02x %02x %02x %02x %02x    %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c",
            base,
            data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15],
            data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
    Serial.println(buf);
  }
}

void setup() {
  pinMode(SHIFT_CLK, OUTPUT);
  pinMode(SHIFT_LATCH, OUTPUT);
  pinMode(SHIFT_DATA, OUTPUT);

  digitalWrite(WRITE_EN, HIGH);
  pinMode(WRITE_EN, OUTPUT);

  Serial.begin(57600);

  Serial.println("Reset");
  delay(2000);
  Serial.println("Run!");

  unsigned int offset = 0;
  char program[] = {
0xa9, 0xff, 0x8d, 0x03, 0x60, 0xa9, 0x00, 0x8d, 0x01, 0x60, 0x85, 0x04, 0x20, 0x27, 0x80, 0x38,
0xa5, 0x00, 0xe5, 0x04, 0xc9, 0x19, 0x90, 0xf7, 0xa9, 0x01, 0x4d, 0x01, 0x60, 0x8d, 0x01, 0x60,
0xa5, 0x00, 0x85, 0x04, 0x4c, 0x0f, 0x80, 0xa9, 0x00, 0x85, 0x00, 0x85, 0x01, 0x85, 0x02, 0x85,
0x03, 0xa9, 0x40, 0x8d, 0x0b, 0x60, 0xa9, 0x80, 0x8d, 0x04, 0x60, 0xa9, 0x00, 0x8d, 0x05, 0x60,
0xa9, 0xc0, 0x8d, 0x0e, 0x60, 0x58, 0x60, 0x2c, 0x04, 0x60, 0xe6, 0x00, 0xd0, 0x0a, 0xe6, 0x01,
0xd0, 0x06, 0xe6, 0x02, 0xd0, 0x02, 0xe6, 0x03, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  const int programLen = 16 * 6;

  for (offset = 0; offset <= programLen; offset++) {
    writeEEPROM(offset, program[offset]);
  }

  // Fill empty bytes
  /*for (offset = 0x7f00; offset < 0x7ffc; offset++) {
    writeEEPROM(offset, OPCODE_BRK);
    }*/

  // Write vector
  /*writeEEPROM(0x7ffa, 0x00);
  writeEEPROM(0x7ffb, 0x00);

  writeEEPROM(0x7ffc, 0x00);
  writeEEPROM(0x7ffd, 0x80);

  writeEEPROM(0x7ffe, 0x47);
  writeEEPROM(0x7fff, 0x80);*/

  printContents(0, 0x130);
  printContents(0x7f00, 0xff);
}


void loop() {
  // put your main code here, to run repeatedly:

}
