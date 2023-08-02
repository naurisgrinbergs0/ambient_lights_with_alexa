#include "animation/animationVariable.h"
#include "util/strip.h"

void pulseStripBrightnessCallback(const AnimationVariable variables[]) {
    setBrightness(variables[0].value);
    show();
}

void pulsePixelPositionCallback(const AnimationVariable variables[]) {
    set(0, 0, 0);
    set(variables[0].value-1, 255, 255, 0);
    set(variables[0].value, 0, 255, 255);
    set(variables[0].value+1, 255, 0, 255);
    show();
}

void colorfulPulseBrightnessCallback(const AnimationVariable variables[]) {
    setBrightness(variables[0].value);
    show();
}
void colorfulPulsePixelMovementCallback(const AnimationVariable variables[]) {
    int position = variables[0].value;
    set(0, 0, 0);
    set(position - 1, 255, 255, 0);
    set(position, 0, 255, 255);
    set(position + 1, 255, 0, 255);
    show();
}

void colorSpectrumAnimationCallback(const AnimationVariable variables[]) {
    float t = float(millis() - variables[0].startTime) / variables[0].duration;
    t = constrain(t, 0.0, 1.0); // Ensure t is within the range [0, 1]
    
    // Calculate the hue value based on t and the full hue range (0 to 65535)
    int hueValue = int(t * 65535.0);
    
    // Set the LED strip color based on the calculated hue value
    for (int i = 0; i < 20; i++) {
        setHSV(i, hueValue, 255, 255); // Set the color in HSV format
    }
    
    show();
}

// void twinkleAnimationCallback(const AnimationVariable variables[]) {
//     // TODO: Should create some kind of new animation class - "Random" or smtn (basically with no duration - happens instantly)
//     set(random(0, variables[0].endValue), random(256), random(256), random(256));
//     show();
// }