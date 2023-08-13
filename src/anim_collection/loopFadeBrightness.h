
/**
 * Fades strip brightness in & out indefinitely
*/
AnimationChain* loopFadeBrightness(unsigned long fadeInDuration, unsigned long fadeOutDuration, u_int8_t startBrightness, u_int8_t endBrightness) {
    auto callback = [](const AnimationVariable var) {
        setBrightness(var.value, true);
    };

    AnimationChain* fadeChain = animo.addAnimationChain(true);
    Animation* fadeIn = fadeChain->addAnimation(fadeInDuration);
    Animation* fadeOut = fadeChain->addAnimation(fadeOutDuration);
    fadeIn->addVar(startBrightness, endBrightness, callback, ANIMO_SIGMOID_EASING);
    fadeOut->addVar(endBrightness, startBrightness, callback, ANIMO_SIGMOID_EASING);
    fadeChain->start();
    return fadeChain;
}