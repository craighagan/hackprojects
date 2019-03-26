#define USE_ESP 1
#undef USE_ARDUINO

#ifdef USE_ARDUINO
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#endif

#ifdef USE_ESP
#include <ESP8266WiFi.h>
#endif

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_BME280.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <LiquidCrystal_I2C.h>
#include <DHT.h>

////////////////////////////////////////////////////
//
// set up which devices we are using
//
// wifi?
#undef USING_WIRELESS

// sensor choices
#define USING_BME 1
#define USING_BMP 2
#define USING_DHT 3

// display choices
#define USING_LCD 1
#define USING_OLED 2

// set what you're using here:
#define SENSOR USING_BME
#define MY_DISPLAY USING_OLED

////////////////////////////////////////////////////
//
// set parameters for devices, such as i2c addresses
// pins, etc
//
#define SLEEP_SECONDS 8
#define OLED_RESET 0
#define BME_ADDRESS 0x76
#define LCD_ADDRESS 0x27
#define OLED_ADDRESS 0x3C
#define DHTPIN 4
#define DHTTYPE DHT22
#define LOOP_DELAY 2000
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// connect i2c devices Vcc/Gnd to 5v, gnd.
// lcd SCL to A5 D1 on esp
// lcd SDA to A4 D2 on esp
// dht to pin 4

////////////////////////////////////////////////////
//
// initialize variables
//

#ifdef USE_ESP
// WiFi settings
const char* ssid = "ssid";
const char* password = "password";
#endif


#if MY_DISPLAY == USING_LCD
LiquidCrystal_I2C display(LCD_ADDRESS, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
#endif

#if MY_DISPLAY == USING_OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif

#if SENSOR == USING_DHT
DHT sensor(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
#endif

#if SENSOR == USING_BME
Adafruit_BME280 sensor; // I2C
#endif

#if SENSOR == USING_BMP
Adafruit_BMP085_Unified sensor = Adafruit_BMP085_Unified(10085);

sensors_event_t event;
#endif

//Variables
float humidity = 0.0;
float temperature = 0.0;
float pressure = 0.0;

// for watchdog timer
volatile int f_wdt = 1;

#ifdef USE_ARDUINO
////////////////////////////////////////////////////
//
// Watchdog Interrupt Service. This
// is executed when watchdog timed out
//
ISR(WDT_vect)
{
  if (f_wdt == 0)
  {
    f_wdt = 1;
  }
  else
  {
    Serial.println("WDT Overrun!!!");
  }
}
#endif

////////////////////////////////////////////////////
//
// celsius_to_fahrenheit convert from Celsius to
// Fahrenheit
//
float celsius_to_fahrenheit(float celsius) {
  return (celsius * 9 / 5) + 32;
}

////////////////////////////////////////////////////
//
// pascals_to_mbar convert from pascals to mbar
//
float pascals_to_mbar(float pascals) {
  return (pascals / 100.0);
}

////////////////////////////////////////////////////
//
// hpascals_to_inhg convert from pascals to inHg
//
float hpascals_to_inhg(float hpascals) {
  return (hpascals * 100 * 0.00029529983071445);
}

////////////////////////////////////////////////////
//
// setup_sensor set up the temp/humidity/pressure
// sensor
//
void setup_sensor() {

#if SENSOR == USING_BME
  Serial.println("Using BME280 I2C Sensor");
  if (!sensor.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
#endif

#if SENSOR == USING_BMP
  Serial.println("Using BMP180 I2C Sensor");
  sensor.begin();
#endif

#if SENSOR == USING_DHT
  Serial.println("Using DHT Sensor");
  sensor.begin();
#endif


}

////////////////////////////////////////////////////
//
// setup_display set up the display (oled/lcd)
//
void setup_display() {

#if MY_DISPLAY == USING_LCD
  Serial.println("Using LCD Display");

  display.init();
#endif

#if MY_DISPLAY == USING_OLED
  Serial.println("Using OLED Display");

  // SSD1306 Init
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) { // Address 0x3D for 128x64
    Serial.println("SSD1306 allocation failed");
    for (;;); // Don't proceed, loop forever
  }

#endif

}

////////////////////////////////////////////////////
//
// write information to the display
//
void write_information(float temperature,
                       float humidity,
                       float pressure) {

  Serial.print("Humidity: ");
  Serial.print(humidity, 2);
  Serial.println("%");
  Serial.print("Temp: ");
  Serial.print(celsius_to_fahrenheit(temperature), 2);
  Serial.println("F");
  Serial.print("Pressure: ");
  Serial.print(hpascals_to_inhg(pressure));
  Serial.println("inHg");

#if MY_DISPLAY == USING_LCD
  display.clear();
  display.backlight();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(celsius_to_fahrenheit(temperature), 2);
  display.println("F");
  display.setCursor(0, 1);
  display.print("Hum: ");
  display.print(humidity, 2);
  display.println("%");

#endif
#if MY_DISPLAY == USING_OLED
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text

  display.setCursor(20, 2);
  display.println("Brookline Pack 6");

  display.setCursor(18, 16);
  display.print("Temp: ");
  display.print(celsius_to_fahrenheit(temperature), 2);
  display.println("F");

  display.setCursor(24, 32);
  display.print("Hum: ");
  display.print(humidity, 2);
  display.println("%");

#if SENSOR == USING_BME
  display.setCursor(18, 48);
  display.print("Pres: ");
  display.print(hpascals_to_inhg(pressure));
  display.println("mmHg");

#endif // BME

#if SENSOR == USING_BMP
  display.setCursor(18, 48);
  display.print("Pres: ");
  display.print(hpascals_to_inhg(pressure));
  display.println("mmHg");

#endif // BMP

  display.display();
#endif // DISPLAY

}

#ifdef USE_ARDUINO
////////////////////////////////////////////////////
//
// set up watchdog timer
// stolen from http://donalmorrissey.blogspot.com/2010/04/sleeping-arduino-part-5-wake-up-via.html
//
void setup_watchdog_timer() {
  /*** Setup the WDT ***/

  /* Clear the reset flag. */
  MCUSR &= ~(1 << WDRF);

  /* In order to change WDE or the prescaler, we need to
     set WDCE (This will allow updates for 4 clock cycles).
  */
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  /* set new watchdog timeout prescaler value */
  WDTCSR = 1 << WDP0 | 1 << WDP3; /* 8.0 seconds */

  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
}

////////////////////////////////////////////////////
// enter sleep
//
void enter_sleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();

  /* Now enter sleep mode. */
  sleep_mode();

  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */

  /* Re-enable the peripherals. */
  power_all_enable();
}
#endif // USE_ARDUINO

////////////////////////////////////////////////////
//
// configure wireless
//
#ifdef USING_WIRELESS

// Client variables
char linebuf[80];
int charcount = 0;
WiFiServer server(80);

void setup_wireless() {
  Serial.println("Configuring wireless");
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());

  server.begin();
}

////////////////////////////////////////////////////
//
// respond to clients
//
void respond_network_clients() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    memset(linebuf, 0, sizeof(linebuf));
    charcount = 0;
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        //read char by char HTTP request
        linebuf[charcount] = c;
        if (charcount < sizeof(linebuf) - 1) charcount++;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<meta http-equiv=\"refresh\" content=\"30\"></head>");
          client.println("<body><div style=\"font-size: 3.5rem;\"><p>ESP32 - DHT</p><p>");
          if (temperature >= 25 ) {
            client.println("<div style=\"color: #930000;\">");
          }
          else if (temperature < 25 && temperature >= 5 ) {
            client.println("<div style=\"color: #006601;\">");
          }
          else if (temperature < 5) {
            client.println("<div style=\"color: #009191;\">");
          }
          client.println(temperature, 2);
          client.println("*C</p><p>");
          client.println(celsius_to_fahrenheit(temperature), 2);
          client.println("*F</p></div><p>");
          client.println(humidity, 2);
          client.println("%</p></div>");
          client.println("</body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          memset(linebuf, 0, sizeof(linebuf));
          charcount = 0;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
#endif // USING_WIRELESS

///////////////////////////////////////////////////////////////////////////////////////
//
// mandatory arduino stuff
//

////////////////////////////////////////////////////
//
// setup
//
void setup()
{

#ifdef USE_ARDUINO
  setup_watchdog_timer();
#endif

  Wire.begin();
  Serial.begin(9600);

#ifdef USING_WIRELESS
  setup_wireless();
#endif // USING_WIRELESS

  setup_sensor();

  setup_display();
}


////////////////////////////////////////////////////
//
// loop
//
void loop()
{
  // wait for everything to start up
#ifdef USING_WIRELESS
  respond_network_clients();
#endif

  if (f_wdt == 1) {
#if SENSOR == USING_DHT

    humidity = sensor.readHumidity();
    temperature = sensor.readTemperature();
    // don't have pressure
    pressure = 101325; // 1 atm, 30mmHg

#endif
#if SENSOR == USING_BME
    humidity = sensor.readHumidity();
    temperature = sensor.readTemperature();
    pressure = sensor.readPressure();
#endif

#if SENSOR == USING_BMP
    sensor.getEvent(&event);
    pressure = event.pressure;
    sensor.getTemperature(&temperature);
    humidity = 0.0;
#endif


    write_information(temperature, humidity, pressure);
    // let everything write
    delay(100);
    // clear watchdog and go back to sleep

#ifdef USE_ARDIONO
    if_wdt = 0;
    enter_sleep();
#endif

#ifdef USE_ESP
#ifdef USING_WIRELESS
    delay(100);
#else
    display.ssd1306_command(0x81);
    display.ssd1306_command(10); //max 157
    display.ssd1306_command(0xD9);
    display.ssd1306_command(17);  //max 34

    Serial.println("going to sleep");
    ESP.deepSleep(SLEEP_SECONDS * 1000000);
    delay(100); // sometimes a few more instructions happen
    // making the non dead code not quite dead
#endif // USING_WIRELESS
#endif // USE_ESP


  }
}
