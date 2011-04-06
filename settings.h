#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include "glcolor.h"

class Settings
{
public:
    Settings(QString organization, QString application);
    ~Settings();

    void setBackgroundColor(GLColor &color);
    GLColor backgroundColor();

private:
    QSettings * _settings;
};

#endif // SETTINGS_H
