#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include "glcolor.h"

class Settings
{
public:
    Settings();
    ~Settings();

    void setBackgroundColor(GLColor &color);
    GLColor backgroundColor();

    void setShowObjectIds(int state);
    void setShowCoordinates(int state);
    void setShowVectors(int state);
    int showObjectIds();
    int showCoordinates();
    int showVectors();

private:
    QSettings * _settings;
};

#endif // SETTINGS_H
