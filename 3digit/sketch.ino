int segmentPins[] = {23, 22, 21, 19, 18, 17, 16};  // ขา Segment a-g
int digitPins[] = {2, 0, 4};  // ขา Digit Control (Common Cathode)

// รูปแบบ segment สำหรับตัวเลข 0-9
byte digitPatterns[10][7] = {
  {1,1,1,1,1,1,0},  // 0
  {0,1,1,0,0,0,0},  // 1
  {1,1,0,1,1,0,1},  // 2
  {1,1,1,1,0,0,1},  // 3
  {0,1,1,0,0,1,1},  // 4
  {1,0,1,1,0,1,1},  // 5
  {1,0,1,1,1,1,1},  // 6
  {1,1,1,0,0,0,0},  // 7
  {1,1,1,1,1,1,1},  // 8
  {1,1,1,1,0,1,1}   // 9
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
}

void loop() {
  for (int num = 0; num <= 99; num++) {
    // แยกหลักร้อย หลักสิบ หลักหน่วย
    int hundreds = num / 100;            // หลักร้อย (ที่นี่จะเป็น 0 ตลอด)
    int tens = (num / 10) % 10;          // หลักสิบ
    int ones = num % 10;                 // หลักหน่วย

    // แสดงเลขนี้เป็นเวลา ~1 วินาที (ทำ multiplexing หลายรอบเพื่อความสว่างคงที่)
    for (int i = 0; i < 200; i++) {  // แสดง 200 รอบ (ประมาณ 1 วินาที)
      displayNumber(hundreds, tens, ones);
    }
  }
}

// ฟังก์ชันแสดงตัวเลข 3 หลัก (Multiplexing)
void displayNumber(int d1, int d2, int d3) {
  int digits[3] = {d1, d2, d3};
  for (int digit = 0; digit < 3; digit++) {
    setSegments(digits[digit]);
    digitalWrite(digitPins[digit], LOW);  // เปิด Digit นี้ (Common Cathode)
    delay(3);  // หน่วงเพื่อให้มองเห็น (~3ms ต่อหลัก)
    digitalWrite(digitPins[digit], HIGH);  // ปิด Digit นี้
  }
}

// ฟังก์ชันเปิด segment ตามตัวเลข
void setSegments(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], digitPatterns[num][i]);
  }
}
