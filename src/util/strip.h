#include <NeoPixelBus.h>

NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(NUM_LEDS);
RgbColor colors[NUM_LEDS];
u_int8_t brightness = 255;

void initStrip() {
    strip.Begin();
    strip.Show();
}

void set(u_int16_t pixel, u_int8_t r, u_int8_t g, u_int8_t b) {
  colors[pixel].R = r;
  colors[pixel].G = g;
  colors[pixel].B = b;
}

void set(u_int8_t r, u_int8_t g, u_int8_t b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    colors[i].R = r;
    colors[i].G = g;
    colors[i].B = b;
  }
}

void setBrightness(u_int8_t b) {
  brightness = b;
}

void clear() {
  set(0, 0, 0);
}

void show() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.SetPixelColor(i, RgbColor(
      u_int8_t(float(colors[i].R) * (float(brightness) / 255.0)), 
      u_int8_t(float(colors[i].G) * (float(brightness) / 255.0)), 
      u_int8_t(float(colors[i].B) * (float(brightness) / 255.0))
      ));
  }
  strip.Show();
}

RgbColor hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
  if (s == 0) {
    return RgbColor(v, v, v);
  }
  uint8_t region = h / 4369; // h / 60 degrees
  uint16_t remainder = (h - (region * 4369)) * 6;

  uint8_t p = (v * (255 - s)) >> 8;
  uint8_t q = (v * (255 - ((s * remainder) >> 16))) >> 8;
  uint8_t t = (v * (255 - ((s * (65535 - remainder)) >> 16))) >> 8;

  switch (region) {
    case 0: return RgbColor(v, t, p);
    case 1: return RgbColor(q, v, p);
    case 2: return RgbColor(p, v, t);
    case 3: return RgbColor(p, q, v);
    case 4: return RgbColor(t, p, v);
    default: return RgbColor(v, p, q);
  }
}

void setHSV(u_int16_t pixel, uint16_t hue, uint8_t saturation, uint8_t value) {
  colors[pixel] = hsvToRgb(hue, saturation, value);
}