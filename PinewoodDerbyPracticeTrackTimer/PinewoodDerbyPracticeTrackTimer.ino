#include <LiquidCrystal.h>

#define END_SENSOR A1 // sensor at start gate
#define START_SENSOR A2 // sensor at finish line
#define SENSOR_LOW 0

// sensor pct is used
// as a multiplier against the ambient
// light
#define SENSOR_PCT 0.8
#define SENSOR_SAMPLES 1000

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int LastKeyPressed = -1;
bool DebugMode = false;
int ambient_light_value_start = 0;
int ambient_light_value_end = 0;
int sensor_high_start = 0;
int sensor_high_end = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(START_SENSOR, INPUT);
  pinMode(END_SENSOR, INPUT);
  Serial.begin(9600);      // open the serial port at 9600 bps:
  ambient_light_value_start = guess_ambient_light(START_SENSOR);
  ambient_light_value_end = guess_ambient_light(END_SENSOR);
  sensor_high_start = int(ambient_light_value_start * SENSOR_PCT);
  sensor_high_end = int(ambient_light_value_end * SENSOR_PCT);
  Serial.print("Detected ambient light value for start to be ");
  Serial.println(ambient_light_value_start);
  Serial.print("Detected ambient light value for end to be ");
  Serial.println(ambient_light_value_end);
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

int guess_ambient_light(int sensor_id) {
  unsigned long sensor_data = 0;
  for(int i=0;i<SENSOR_SAMPLES;i++) {
    sensor_data += analogRead(sensor_id);
  }
  return int(sensor_data / SENSOR_SAMPLES);
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
    DisplayText(0, 0, "Ready           ");
    Serial.println("Ready");

    // blinkdisplay
    BlinkDisplay(500);

    while (!started) {
      started = sensor_tripped(START_SENSOR, SENSOR_LOW, sensor_high_start);
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
      started = sensor_tripped(START_SENSOR, SENSOR_LOW, sensor_high_start);
    }

    lcd.clear();
    DisplayText(0, 0, "Car started   ");
    while (!finished) {
      finished = sensor_tripped(END_SENSOR, SENSOR_LOW, sensor_high_end);
    }
    endtime = millis();
    elapsed_time = endtime - starttime;

    // debounce finished sensor
    // probably not strictly necessary
    while (finished) {
      finished = sensor_tripped(END_SENSOR, SENSOR_LOW, sensor_high_end);
    }
    sprintf(DisplayString, "Elapsed %lu ms", elapsed_time);
    Serial.print(DisplayString);
    Serial.print("\n");
    lcd.clear();
    DisplayText(0, 0, "Finished:       ");
    DisplayText(1, 0, DisplayString);
    delay(2500);
  }
}


void BlinkDisplay(int blink_delay) {
    lcd.noDisplay();
    delay(blink_delay);
    lcd.display();
}
void ClearLine(int LineToClear) {
  lcd.setCursor(0, LineToClear); //0 is the first and 1 is the second line, x=0
  lcd.print("                "); //Add 16 spaces to clear the line (there may be better ways to do this)
}
void DisplayText(int Line, int CursorPos, char *TextToDisplay) {
  lcd.setCursor(CursorPos, Line); //0 is the first line and 1 is the second line
  lcd.print(TextToDisplay);
}
