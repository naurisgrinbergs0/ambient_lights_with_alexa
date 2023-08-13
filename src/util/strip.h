#include <NeoPixelBus.h>

NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(NUM_LEDS);
RgbColor colors[NUM_LEDS];
u_int8_t brightness = 255;

void initStrip() {
    strip.Begin();
    strip.Show();
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


void setRGB(u_int16_t pixel, u_int8_t r, u_int8_t g, u_int8_t b, bool showIt = false) {
  colors[pixel].R = r;
  colors[pixel].G = g;
  colors[pixel].B = b;
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
  colors[pixel].R = r;
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
  colors[pixel].G = g;
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
  colors[pixel].B = b;
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
  brightness = b;
  if (showIt) {
    show();
  }
}

RgbColor get(u_int16_t pixel) {
  return colors[pixel];
}
