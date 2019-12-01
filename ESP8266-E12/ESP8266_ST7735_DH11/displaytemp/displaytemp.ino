/**************************************************************************
 * 
 * ESP8266 NodeMCU interface with ST7735 color TFT (128x160 pixel) display and
 *   DHT11 digital humidity & temperature sensor.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 *
 *************************************************************************/
 
#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_ST7735.h>   // include Adafruit ST7735 TFT library
#include <DHT.h>               // include Adafruit DHT library code
 
// ST7735 TFT module connections
#define TFT_RST   D3//D4     // TFT RST pin is connected to NodeMCU pin D4 (GPIO2)
#define TFT_CS    D6//D3     // TFT CS  pin is connected to NodeMCU pin D3 (GPIO0)
#define TFT_DC    D4//D2     // TFT DC  pin is connected to N odeMCU pin D2 (GPIO4)
// initialize ST7735 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
 
#define DHTPIN  D1           // DHT11 data pin is connected to NodeMCU pin D1 (GPIO5)
#define DHTTYPE DHT11        // DHT11 sensor is used
DHT dht11(DHTPIN, DHTTYPE);  // configure DHT library
 
void setup(void)
{
  tft.initR(INITR_BLACKTAB);     // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);  // fill screen with black color
  tft.drawFastHLine(0, 50,  tft.width(), ST7735_BLUE);   // draw horizontal blue line at position (0, 50)
  tft.drawFastHLine(0, 102,  tft.width(), ST7735_BLUE);  // draw horizontal blue line at position (0, 102)
 
  tft.setTextColor(ST7735_WHITE, ST7735_BLACK);  // set text color to white with black background
  tft.setTextSize(1);                 // text size = 1
  tft.setCursor(4, 16);               // move cursor to position (4, 16) pixel
  tft.print("NODEMCU + ST7735 TFT");
  tft.setCursor(22, 33);              // move cursor to position (22, 33) pixel
  tft.print("+ DHT11 SENSOR");
  tft.setTextColor(ST7735_GREEN, ST7735_BLACK);     // set text color to green with black background
  tft.setCursor(25, 61);              // move cursor to position (25, 61) pixel
  tft.print("TEMPERATURE =");
  tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);  // set text color to yellow with black background
  tft.setCursor(34, 113);              // move cursor to position (34, 113) pixel
  tft.print("HUMIDITY =");
  tft.setTextSize(2);                     // text size = 2
  tft.drawCircle(83, 80, 2, ST7735_RED);  // print degree symbol ( ° )
  tft.setTextColor(ST7735_RED, ST7735_BLACK);  // set text color to red with black background
  tft.setCursor(89, 78);
  //tft.print("C");
  //use Farhenheit
  tft.print("F");
  // initialize DHT11 sensor
  dht11.begin();
}
 
// main loop
void loop()
{
  // read humidity in rH%
  int Humi = dht11.readHumidity() * 10;
  // read temperature in degree Celsius
  int Temp = dht11.readTemperature(true) * 10;  //pass true in to get Fahrenheit
  //convert to F
  int FTemp = (1.8 * Temp) + 32;
  // print temperature (in °C)
  tft.setTextColor(ST7735_RED, ST7735_BLACK);  // set text color to red with black background
  tft.setCursor(17, 78);
  
  if(Temp < 32)    // if temperature < 0
    tft.printf("-%02u.%1u", (abs(Temp)/10)%100, abs(Temp) % 10);
  else            // temperature >= 32
    tft.printf(" %02u.%1u", (Temp/10)%100, Temp % 10);
    
 //print F Temp
// tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
// tft.setCursor(29,130);
// tft.printf("%02u.%1u", (abs(FTemp)/10)%100, abs(FTemp) % 10);
 
  // print humidity (in %)
  tft.setTextColor(ST7735_CYAN, ST7735_BLACK);  // set text color to cyan with black background
  tft.setCursor(29, 130);
  tft.printf("%02u.%1u %%", (Humi/10)%100, Humi % 10);
 
  delay(1000);    // wait a second
}
 
// end of code.
