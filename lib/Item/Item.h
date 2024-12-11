#ifndef ITEM_H
#define ITEM_H

#include <FastAccelStepper.h>
#include "Config.h"


const uint32_t ticksPS = 200;


const byte lsPin = 25;

// stepper config
const byte rotationPinStep = 32;
const byte rotationPinDir = 33;

const byte verticalPinStep = 26;
const byte verticalPinDir = 27;

const byte pirPin = 22;

const float rsr = 6400.0;

const int escapePosition = 5000;


// ON-OFFs
const byte ledPins[4] = {16, 17, 5, 18};

const byte lightPin = 19;
const byte pwmPin = 21;


enum states {
    Initializing,
    Jogging,
    LsHit,
    Escaping,
    Initialized,
    Running,
    Finished
};



class Item {

    FastAccelStepperEngine engine;
    FastAccelStepper* vertical;
    FastAccelStepper* rotation;
    states state;

    uint32_t seconds = 0;
    uint32_t newSeconds = 0;
    uint32_t startMillis = 0;

    int32_t animation[180][channelWidth];
    uint32_t animationLength = 0;

    public:
        Item();
        ~Item();
        void setup();
        void update();
    private:
        void setupSteppers();
        void setupLeds();
        bool checkLs(byte n);
        void lsHit();
        void escape();
        void initialize();
        void transition(states);
        void setupAnimation();
        String getFPWM(int32_t msg);
        void sendFPWM(String msg);
        String getDPWM(int msg);
};

#endif