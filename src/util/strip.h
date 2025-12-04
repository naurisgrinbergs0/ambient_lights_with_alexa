#pragma once
#include <NeoPixelBus.h>

struct StripState {
  NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip = NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod>(NUM_LEDS);
  RgbColor colors[NUM_LEDS];
  u_int8_t brightness = 255;
  bool isTurningOn = false;
  bool isTurningOff = false;
  bool isOn = false;
};
StripState stripState = StripState();

void initStrip() {
    stripState.strip.Begin();
    stripState.strip.Show();
}

void show() {
  // scale brightness [0..255] to multiplier [0..256] and use integer math
  uint16_t scale = (uint16_t)stripState.brightness + 1; // 1..256
  for (int i = 0; i < NUM_LEDS; i++) {
    stripState.strip.SetPixelColor(i, RgbColor(
      (uint8_t)((stripState.colors[i].R * scale) >> 8),
      (uint8_t)((stripState.colors[i].G * scale) >> 8),
      (uint8_t)((stripState.colors[i].B * scale) >> 8)
    ));
  }
  stripState.strip.Show();
}


void setRGB(u_int16_t pixel, u_int8_t r, u_int8_t g, u_int8_t b, bool showIt = false) {
  stripState.colors[pixel].R = r;
  stripState.colors[pixel].G = g;
  stripState.colors[pixel].B = b;
  if (showIt) {
    show();
  }
}
void setRGB(u_int8_t r, u_int8_t g, u_int8_t b, bool showIt = false) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setRGB(i, r, g, b);
  }
  if (showIt) {
    show();
  }
}

void setR(u_int16_t pixel, u_int8_t r, bool showIt = false) {
  stripState.colors[pixel].R = r;
  if (showIt) {
    show();
  }
}
void setR(u_int8_t r, bool showIt = false) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setR(i, r);
  }
  if (showIt) {
    show();
  }
}

void setG(u_int16_t pixel, u_int8_t g, bool showIt = false) {
  stripState.colors[pixel].G = g;
  if (showIt) {
    show();
  }
}
void setG(u_int8_t g, bool showIt = false) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setG(i, g);
  }
  if (showIt) {
    show();
  }
}

void setB(u_int16_t pixel, u_int8_t b, bool showIt = false) {
  stripState.colors[pixel].B = b;
  if (showIt) {
    show();
  }
}
void setB(u_int8_t b, bool showIt = false) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setB(i, b);
  }
  if (showIt) {
    show();
  }
}


RgbColor HSVtoRGB(u_int16_t h, u_int8_t s, u_int8_t v) {
  float hue = static_cast<float>(h) / 360.0f;
  float saturation = static_cast<float>(s) / 255.0f;
  float value = static_cast<float>(v) / 255.0f;

  float C = value * saturation;
  float X = C * (1.0f - std::abs(std::fmod(hue * 6.0f, 2.0f) - 1.0f));
  float m = value - C;

  float r, g, b;

  int hueZone = static_cast<int>(hue * 6);
  float intermediateValue = X + m;

  switch (hueZone) {
      case 0:
          r = C + m;
          g = intermediateValue;
          b = m;
          break;
      case 1:
          r = intermediateValue;
          g = C + m;
          b = m;
          break;
      case 2:
          r = m;
          g = C + m;
          b = intermediateValue;
          break;
      case 3:
          r = m;
          g = intermediateValue;
          b = C + m;
          break;
      case 4:
          r = intermediateValue;
          g = m;
          b = C + m;
          break;
      default:
          r = C + m;
          g = m;
          b = intermediateValue;
          break;
  }

  return RgbColor(r * 255.0f, g * 255.0f, b * 255.0f);
}

void setHSV(u_int16_t pixel, u_int16_t h, u_int8_t s, u_int8_t v, bool showIt = false) {
    RgbColor rgb = HSVtoRGB(h, s, v);
    setRGB(pixel, rgb.R, rgb.G, rgb.B, showIt);
}
void setHSV(u_int16_t h, u_int8_t s, u_int8_t v, bool showIt = false) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setHSV(i, h, s, v);
  }
  if (showIt) {
    show();
  }
}



void clear(bool showIt = false) {
  setRGB(0, 0, 0);
  if (showIt) {
    show();
  }
}

void setBrightness(u_int8_t b, bool showIt = false) {
  stripState.brightness = b;
  if (showIt) {
    show();
  }
}

RgbColor get(u_int16_t pixel) {
  return stripState.colors[pixel];
}
