#include <LiquidCrystal.h>

#define END_SENSOR A1
#define START_SENSOR A2
#define SENSOR_LOW 0
#define SENSOR_HIGH 250

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int LastKeyPressed = -1;
bool DebugMode = false;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(START_SENSOR, INPUT);
  pinMode(END_SENSOR, INPUT);
  Serial.begin(9600);      // open the serial port at 9600 bps:   
}

int sensor_tripped(int sensor_id, int low_value, int high_value) {
  int sensor_value = 0;
  char *sensor_string = 0;
  sensor_value = analogRead(sensor_id); // The keys pass a unique value to A0
  if (sensor_value > low_value && sensor_value < high_value) {
    return true;
  }
  return false;
}

void loop() {
  char *DisplayString = "";
  bool started = false;
  bool finished = false;
  unsigned long starttime = 0;
  unsigned long endtime = 0;
  unsigned long elapsed_time = 0;

  while (true) {
    started = false;
    finished = false;
    DisplayString = "";
    starttime = 0;
    endtime = 0;
    elapsed_time = 0;
    
    ClearLine(0);
    DisplayText(0, 0, "Ready");
    Serial.print("Ready\n");
    
    while (!started) {
      started = sensor_tripped(START_SENSOR, SENSOR_LOW, SENSOR_HIGH);
    }
    starttime = millis();
    Serial.print("sense start at ");
    Serial.print(starttime);
    Serial.print("\n");
    ClearLine(0);

    // debounce the start timer; more useful
    // when testing with buttons, however a legal
    // car must past start before finishing
    while (started) {
      started = sensor_tripped(START_SENSOR, SENSOR_LOW, SENSOR_HIGH);
    }
    
    ClearLine(1);
    DisplayText(0, 0, "Start");
    while (!finished) {
      finished = sensor_tripped(END_SENSOR, SENSOR_LOW, SENSOR_HIGH);
    }
    endtime = millis();
    elapsed_time = endtime - starttime;

    // debounce finished sensor
    while (finished) {
      finished = sensor_tripped(END_SENSOR, SENSOR_LOW, SENSOR_HIGH);
    }
    sprintf(DisplayString, "Elapsed %lu ms", elapsed_time);
    Serial.print(DisplayString);
    Serial.print("\n");
    ClearLine(0);
    ClearLine(1);
    DisplayText(0, 0, "Finished:");
    DisplayText(1, 0, DisplayString);
    delay(2500);
  }
}

void ClearLine(int LineToClear) {
  lcd.setCursor(0, LineToClear); //0 is the first and 1 is the second line, x=0
  lcd.print("                "); //Add 16 spaces to clear the line (there may be better ways to do this)
}
void DisplayText(int Line, int CursorPos, char *TextToDisplay) {
  lcd.setCursor(CursorPos, Line); //0 is the first line and 1 is the second line
  lcd.print(TextToDisplay);
}

