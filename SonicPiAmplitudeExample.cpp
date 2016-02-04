//
// Created by Alexander Simpson on 2016-02-04.
//

#include <qtimer.h>
#include "SonicPiAmplitudeExample.h"


float randf(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

SonicPiAmplitudeExample::SonicPiAmplitudeExample() {

}

void SonicPiAmplitudeExample::run() {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextRandomAmplitude()));
    timer->start(50);
}

float x = 0;
void SonicPiAmplitudeExample::nextRandomAmplitude() {
    emit amplitudeUpdate(randf(0, 1));
}
