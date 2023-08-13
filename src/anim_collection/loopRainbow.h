
/**
 * Rainbow loop animation
*/
void loopRainbow(unsigned long duration) {
    Animation* rainbow = animo.addAnimation(duration, true);
    rainbow->addVar(0, 360,
        [](const AnimationVariable var) {
            setHSV(var.value, 255, 255, true);
        },
        ANIMO_LINEAR_EASING);
    rainbow->start();
}