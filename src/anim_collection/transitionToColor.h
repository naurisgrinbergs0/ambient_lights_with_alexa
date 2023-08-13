
/**
 * Simple transition from color to other color
*/
void transitionToColor(unsigned long duration, 
    u_int8_t rFrom, u_int8_t gFrom, u_int8_t bFrom, u_int8_t rTo, u_int8_t gTo, u_int8_t bTo) {
    Animation* fadeRed = animo.addAnimation(duration);
    Animation* fadeGreen = animo.addAnimation(duration);
    Animation* fadeBlue = animo.addAnimation(duration);
    fadeRed->addVar(rFrom, rTo,
        [](const AnimationVariable var) {
            setR(var.value);
        },
        ANIMO_SIGMOID_EASING);
    fadeGreen->addVar(gFrom, gTo,
        [](const AnimationVariable var) {
            setG(var.value);
        },
        ANIMO_SIGMOID_EASING);
    fadeBlue->addVar(bFrom, bTo,
        [](const AnimationVariable var) {
            setB(var.value);
        },
        ANIMO_SIGMOID_EASING);
    fadeRed->start();
    fadeGreen->start();
    fadeBlue->start();
}