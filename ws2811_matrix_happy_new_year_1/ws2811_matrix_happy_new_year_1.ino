// Adafruit_NeoMatrix example for ws2811 LED series.
// Scrolls 'HAPPYNEWYEAR2022' across the matrix.

#include <Adafruit_GFX.h>
#include <FastLED.h>
#include <FastLED_NeoMatrix.h>

#define LED_PIN 7

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
#define mw 7
#define mh 7
#define NUMMATRIX (mw*mh)

CRGB matrixleds[NUMMATRIX];

/*
 * Code works with below given LED Matrix layout.
 * 48 47 46 45 44 43 42
 * 35 36 37 38 39 40 41
 * 34 33 32 31 30 29 28
 * 21 22 23 24 25 26 27
 * 20 19 18 17 16 15 14
 *  7  8  9 10 11 12 13
 *  6  5  4  3  2  1  0
 */
FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, mw, mh, mw/7, 1, 
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG );

const uint16_t colors[] = {
  matrix->Color(255, 0, 0),
  matrix->Color(255, 127, 0),
  matrix->Color(255, 255, 0),
  matrix->Color(127, 255, 0),
  matrix->Color(0, 255, 0),
  matrix->Color(0, 255, 127),
  matrix->Color(0, 255, 255),
  matrix->Color(0, 127, 255),
  matrix->Color(0, 0, 255),
  matrix->Color(127, 0, 255),
  matrix->Color(255, 0, 255),
  matrix->Color(255, 0, 127),
  matrix->Color(255, 0, 0)
};

int pos  = 0;
int pass = 0;
char *disp_string;

#define TEXT_WIDTH 6
#define COUNT_OF(x) (sizeof(x)/sizeof(x[0]))

void setup() {
  FastLED.addLeds<WS2811, LED_PIN, RGB>(matrixleds, NUMMATRIX); 
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(24);
  matrix->setTextColor(CRGB(0,0,0));
  disp_string = "HAPPYNEWYEAR2022";
}

void loop() {
  matrix->fillScreen(0);
  int i;
  int x;
  for (i = 0, x = pos; i < strlen(disp_string); i++, x += 6) {
      matrix->setCursor(x, 0);
      matrix->print(disp_string[i]);

      matrix->setTextColor(colors[i % COUNT_OF(colors)]);
  }

  if(--pos < -96) {
    pos = matrix->width();
  }

  matrix->show();
  delay(150);
}
