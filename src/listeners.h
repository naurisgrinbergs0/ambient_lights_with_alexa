void onDevice00Change()  {
    if (!Animator::getInstance()->getIsActive()) {
        loopPulseBrigtness();
    } else {
        Animator::getInstance()->forceStopAnimations();
        clear();
        show();
    }
}
