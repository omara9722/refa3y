#include <FastLED.h>

#define LED_PIN     25
#define NUM_LEDS    16
#define MIC_PIN     34  // Analog pin connected to MAX9814 OUT
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
uint8_t gHue = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  Serial.begin(115200);
}

void loop() {
  int micValue = analogRead(MIC_PIN); // Read microphone analog value
  Serial.println(micValue);           // Optional: view raw sound input

  // Map mic value to number of LEDs to light
  int level = map(micValue, 2000, 3200, 0, NUM_LEDS);
  level = constrain(level, 0, NUM_LEDS);

  // Show rainbow with brightness based on sound
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < level) {
      leds[i] = CHSV(gHue + (i * 10), 255, 255);  // Rainbow effect
    } else {
      leds[i] = CRGB::Black;
    }
  }

  FastLED.show();
  gHue++;  // Cycle through rainbow colors slowly
  delay(30);
}
