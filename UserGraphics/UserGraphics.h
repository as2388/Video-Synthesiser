//
// Created by Alexander Simpson on 2016-01-26.
//

#ifndef VIDEOSYNTH_USERGRAPHICS_H
#define VIDEOSYNTH_USERGRAPHICS_H

#include <qimage.h>
#include <qdir.h>

class UserGraphics {
public:
    void loadUserGraphics(QImage** buffer, int bufferSize, int startPosition) {
        for (char i = 0; i < bufferSize; i++) {
            QString dir = QString("/Users/alexander/Documents/partii-project/code/VideoSynth/UserGraphics/");
            dir.append(QString::number(i)).append(".jpg");
            //qDebug() << dir;
            buffer[i + startPosition] = new QImage(dir);
        }
    }
};

#endif //VIDEOSYNTH_USERGRAPHICS_H
