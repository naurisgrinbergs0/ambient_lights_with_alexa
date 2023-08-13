
/**
 * Simple fade animation
*/
void fadeBrightness(unsigned long duration, u_int8_t startBrightness, u_int8_t endBrightness) {
    Animation* fadeOut = animo.addAnimation(duration);
    fadeOut->addVar(startBrightness, endBrightness,
        [](const AnimationVariable var) {
            setBrightness(var.value, true);
        },
        ANIMO_SIGMOID_EASING);
    fadeOut->start();
}