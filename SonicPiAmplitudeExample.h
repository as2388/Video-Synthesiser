//
// Created by Alexander Simpson on 2016-02-04.
//

#ifndef VIDEOSYNTH_SONICPIAMPLITUDEEXAMPLE_H
#define VIDEOSYNTH_SONICPIAMPLITUDEEXAMPLE_H


#include <qthread.h>

class SonicPiAmplitudeExample: public QObject {
    Q_OBJECT
public:
    SonicPiAmplitudeExample();
public slots:
    void run();
    void nextRandomAmplitude();
signals:
    void amplitudeUpdate(float x);
};


#endif //VIDEOSYNTH_SONICPIAMPLITUDEEXAMPLE_H
