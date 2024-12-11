#include "Item.h"

void printState(states state) {
    switch (state)
    {
    case states::Initializing:
        Serial.print("Initializing");
        break;
    case states::Jogging:
        Serial.print("Jogging");
        break;
    case states::Escaping:
        Serial.print("Escaping");
        break;
    case states::LsHit:
        Serial.print("LsHit");
        break;
    case states::Initialized:
        Serial.print("Initialized");
        break;
    case states::Running:
        Serial.print("Running");
        break;
    case states::Finished:
        Serial.print("Finished");
        break;
    default:
        break;
    }
}

Item::Item() {
    engine = FastAccelStepperEngine();
    engine.init();    
    state = states::Initializing;

    for (int i=0; i<180; i++) {
        for (int j=0; j<10; j++) {
            animation[i][j] = 0;
        }
    }
}

void Item::setup() {
    setupLeds();
    pinMode(lsPin, INPUT_PULLUP);
    pinMode(pirPin, INPUT);
    setupSteppers();
    setupAnimation();
}

void Item::setupAnimation() {

    uint32_t size = sizeof(animConfig) / (channelWidth * sizeof(int32_t));    
    for (int i=0; i<size; i++) {
        for (int j=0; j<channelWidth; j++) {
            animation[animConfig[i][0]][j] = animConfig[i][j];
        }
        animationLength = animConfig[i][0];
    }
}

void Item::setupLeds() {
    for (int i=0; i<4; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW);
    }

    pinMode(lightPin, OUTPUT);
    digitalWrite(lightPin, LOW);

    pinMode(pwmPin, OUTPUT);
    digitalWrite(pwmPin, LOW);
}

void Item::setupSteppers() {
    rotation = engine.stepperConnectToPin(rotationPinStep);
    rotation->setDirectionPin(rotationPinDir);
    rotation->setSpeedInHz(rsr);
    rotation->setAcceleration(rsr);

    vertical = engine.stepperConnectToPin(verticalPinStep);
    vertical->setDirectionPin(verticalPinDir, false);
    vertical->setSpeedInHz(verticalSpeed); 
    vertical->setAcceleration(verticalAcc);
}

void Item::update() {

    if (checkLs(10)) {
        lsHit();
    }

    switch (state)
    {
    case states::Initializing:
        transition(states::Jogging);
        vertical->moveTo(-100000000);   
        break;
    case states::Jogging:
        break;
    case states::LsHit:
        if (vertical->getCurrentSpeedInUs() == 0) {
            transition(states::Escaping);
            escape();           
        }
        break;
    case states::Escaping:
        if (vertical->getCurrentSpeedInUs() == 0) {
            if (checkLs(10)) {
                escape();
            } else {
                transition(states::Initialized);
                vertical->forceStopAndNewPosition(0);                
            }
        }
        break;
    case states::Initialized:
        if (alwaysStart || digitalRead(pirPin) == HIGH) {
            transition(states::Running);
            startMillis = millis();
            seconds = 0;
            newSeconds = 0;        
        }
        break;
    case states::Running:
        newSeconds = (millis() - startMillis) / 1000 + 1;
        if (newSeconds > seconds) {
            seconds = newSeconds;
            Serial.println(seconds);
            if (animationLength >= seconds) {                
                if (animation[seconds][0] == seconds) {                    
                    for (byte i=1; i<5; i++) {
                        digitalWrite(ledPins[i - 1], animation[seconds][i] == 1 ? HIGH : LOW);
                    }
                    digitalWrite(lightPin, animation[seconds][8] == 1 ? HIGH : LOW);
                    digitalWrite(pwmPin, animation[seconds][9] == 1 ? HIGH : LOW);

                    if (animation[seconds][5] > 0) {
                        rotation->setSpeedInHz(animation[seconds][5]);
                        rotation->setAcceleration(animation[seconds][6]);
                        rotation->move(animation[seconds][5]);
                        rotation->keepRunning();
                    } else {
                        rotation->stopMove();
                    }

                    if (animation[seconds][10] > 0) {
                        sendFPWM(getFPWM(animation[seconds][10]));
                    }
                    vertical->moveTo(animation[seconds][7]);
                }
            } else {
                if (vertical->getCurrentSpeedInUs() == 0 && rotation->getCurrentSpeedInUs() == 0) {
                    transition(states::Finished);
                }
            }
        }
        break;
    case states::Finished:
        ESP.restart();
        break;
    default:
        break;
    }
}

String Item::getFPWM(int32_t msg) {
    if (msg < 10) {
        return String("F00") + String(msg);
    }

    if (msg < 100) {
        return String("F0") + String(msg);
    }

    if (msg < 1000) {
        return String("F") + String(msg);
    }

    if (msg < 10000) {
        msg = msg / 10;
        int32_t d = msg % 100;
        if (d < 10) {
            return String("F") + String(msg / 100) + String(".0") + String(d);
        } else {
            return String("F") + String(msg / 100) + String(".") + String(d);
        }        
    }

    if (msg < 100000) {
        msg = msg / 100;
        return String("F") + String(msg / 10) + String(".") + String(msg % 10);
    }

    if (msg <= 150000) {
        return String("F") + String(msg / 100000) + String(".") + String((msg / 10000) % 10) + String(".") + String((msg / 1000) % 10);
    }

    return String("N/A");
}

String Item::getDPWM(int msg) {
    int d = max(0, min(99, msg));
    if (d < 10) { 
        return String("D00") + String(d);
    }

    return String("D0") + String(d);
}

void Item::sendFPWM(String msg) {
    if (msg != String("N/A")) {
        Serial2.write(msg.c_str());
    } else {
        Serial.println("Invalid freq");
    }
    Serial.println(msg);
}

void Item::lsHit() {
    if (state != states::Escaping && state != states::LsHit) {
        transition(states::LsHit);
        vertical->forceStopAndNewPosition(0);
    }
}

void Item::escape() { 
    vertical->forceStopAndNewPosition(0);
    vertical->moveTo(escapePosition);
}

void Item::transition(states newState) {
    printState(state);
    Serial.print(" -> ");
    printState(newState);
    Serial.println("");
    this->state = newState;
}

bool Item::checkLs(byte n) {
    if (digitalRead(lsPin) == LOW) { 
        return false;
    }

    byte poss = 0;
    for (byte i=0; i<n; i++) {

        if (digitalRead(lsPin) == HIGH) {
        poss++;
        }
        delay(10);
    }

    if (poss > n / 2) {
        return true;
    }

    return false;
}