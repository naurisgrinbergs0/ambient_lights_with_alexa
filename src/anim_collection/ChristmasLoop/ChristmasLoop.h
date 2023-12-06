/**
 * Christmas loop animation
*/
#pragma once
#include "../lib/Animo/src/animo.h"
#include "../anim.h"
#include "../FadeColor.h"
#include "ModeChase.h"
#include "ModeBlink.h"

class ChristmasLoop : public Anim {
private:
    enum class Mode {
        CHASE,
        BLINK,
        NONE,
    };

    Mode mode = Mode::NONE;

    ModeChase* modeChase;
    ModeBlink* modeBlink;

    FadeColor* transition;

    RgbColor* colors;

public:
    ChristmasLoop(RgbColor* colors): colors(colors){};

    void changeMode(Mode mode = Mode::NONE) {
        this->mode = mode == Mode::NONE ? (Mode)random(0, 1) : mode;
        
        delete modeChase;
        delete modeBlink;
        
        switch (this->mode)
        {
            case Mode::CHASE:
                modeChase = new ModeChase();
                break;
            case Mode::BLINK:
                modeBlink = new ModeBlink();
                break;
            default:
                break;
        }
    }

    void start() override {
        // transition = new FadeColor(colors);
        // transition->setDuration(400);
        // transition->setTargetRGB(255, 0, 0);
        // transition->onFinished([this]() {
        //     // this->anim->start();
        //     this->changeMode();
        //     delete transition;
        //     transition = nullptr;
        // });
        // transition->start();
        this->changeMode(Mode::BLINK);
        this->isAnimPlaying = true;
    }

    void onAdvance() {
        if (this->isAnimPlaying) {
            switch(mode) {
                case Mode::CHASE: {
                    modeChase->advance();
                    break;
                }
                case Mode::BLINK: {
                    modeBlink->advance();
                    break;
                }
                default:
                    break;
            }
        }
    }
};