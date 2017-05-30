// LED Characters
// Author: Jan Van Bruggen
//
// For the 7x5 LED Matrix I used,
// an LED will only light up if
// its row is HIGH and its column is LOW.


// GLOBAL VARIABLES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int COLUMN_OFF = HIGH;
int COLUMN_ON = LOW;
int ROW_OFF = LOW;
int ROW_ON = HIGH;


// SETUP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void setup() {
  Serial.println("Running setup() ...");
  setupPins();
  setupSerial();
}

void setupPins() {
  Serial.println("Running setupPins() ...");
  for (int outputPin = 2; outputPin <= 13; outputPin += 1) {
    pinMode(outputPin, OUTPUT);
    if (outputPin <= 8) {
      // Pins 2-8 are used for rows.
      // This guarantees no LEDs on this row are lit up.
      digitalWrite(outputPin, ROW_OFF);
    } else {
      // Pins 9-13 are used for columns.
      // This guarantees no LEDs on this column are lit up.
      digitalWrite(outputPin, COLUMN_OFF);
    }
  }
}

void setupSerial() {
  Serial.println("Running setupSerial() ...");
  Serial.begin(9600);
}


// LOOP ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void loop() {
  Serial.println("Running loop() ...");
  // Draw each character as many times as it takes to achieve the desired duration.
  // The drawing speed varies with each character's number of "on" LEDs.
  drawJ(1000);
  drawPlus(700);
  drawL(1500);
  drawEquals(600);
  drawHeart(2000);
}

void drawJ(int numberOfTimesToDraw) {
  int jMatrix[7][5] = {
    {0,0,0,0,0},
    {1,1,1,1,1},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {1,0,1,0,0},
    {1,1,1,0,0},
    {0,0,0,0,0}
  };
  draw(jMatrix, numberOfTimesToDraw);
}

void drawPlus(int numberOfTimesToDraw) {
  int plusMatrix[7][5] = {
    {0,0,0,0,0},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {1,1,1,1,1},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,0,0,0}
  };
  draw(plusMatrix, numberOfTimesToDraw);
}

void drawL(int numberOfTimesToDraw) {
  int lMatrix[7][5] = {
    {0,0,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,1,0,0,0},
    {0,1,1,1,0},
    {0,0,0,0,0}
  };
  draw(lMatrix, numberOfTimesToDraw);
}

void drawEquals(int numberOfTimesToDraw) {
  int equalsMatrix[7][5] = {
    {0,0,0,0,0},
    {0,0,0,0,0},
    {1,1,1,1,1},
    {0,0,0,0,0},
    {1,1,1,1,1},
    {0,0,0,0,0},
    {0,0,0,0,0}
  };
  draw(equalsMatrix, numberOfTimesToDraw);
}

void drawHeart(int numberOfTimesToDraw) {
  int heartMatrix[7][5] = {
    {0,0,0,0,0},
    {0,1,0,1,0},
    {1,0,1,0,1},
    {1,0,0,0,1},
    {0,1,0,1,0},
    {0,0,1,0,0},
    {0,0,0,0,0}
  };
  draw(heartMatrix, numberOfTimesToDraw);
}

void draw(int matrix[7][5], int numberOfTimesToDraw) {
  for (int drawCount = 0; drawCount < numberOfTimesToDraw; drawCount += 1) {
    // Draw each LED separately (very fast).
    for (int row = 1; row <= 7; row += 1) {
      // Arrays are indexed starting at 0,
      // and "matrix" is a 2-dimensional Array.
      int rowIndex = row - 1;
      for (int column = 1; column <= 5; column += 1) {
        int columnIndex = column - 1;
        if (matrix[rowIndex][columnIndex] == 1) {
          turnOnLed(row, column);
        }
      }
      turnAllLedsOff();
    }
  }
}

void turnOnLed(int row, int column) {
  setRow(row, ROW_ON);
  for (int otherRow = 1; otherRow <= 7; otherRow += 1) {
    if (otherRow != row) {
      setRow(otherRow, ROW_OFF);
    }
  }
  setColumn(column, COLUMN_ON);
  for (int otherColumn = 1; otherColumn <= 5; otherColumn += 1) {
    if (otherColumn != column) {
      setColumn(otherColumn, COLUMN_OFF);
    }
  }
}

void turnAllLedsOff() {
  for (int row = 1; row <= 7; row += 1) {
    setRow(row, ROW_OFF);
  }
  for (int column = 1; column <= 5; column += 1) {
    setColumn(column, COLUMN_OFF);
  }
}

void setRow(int row, int value) {
  // Pins 2-8 correspond to rows 1-7.
  digitalWrite(row + 1, value);
}

void setColumn(int column, int value) {
  // Pins 9-13 correspond to columns 1-5.
  digitalWrite(column + 8, value);
}
