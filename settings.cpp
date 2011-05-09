#include "settings.h"
#include <QVector>

Settings::Settings()
{
    _settings = new QSettings();
}

Settings::~Settings()
{
    _settings->sync();
    delete _settings;
}

void Settings::setBackgroundColor(GLColor &color)
{
    _settings->setValue("view/backgroundColor", color.qcolor());
}

GLColor Settings::backgroundColor()
{
    return GLColor(_settings->value("view/backgroundColor", GLColor().qcolor()).value<QColor>());
}

void Settings::setShowObjectIds(int state)
{
    _settings->setValue("view/objectIds", state);
}

void Settings::setShowCoordinates(int state)
{
    _settings->setValue("view/coordinates", state);
}

void Settings::setShowVectors(int state)
{
    _settings->setValue("view/vectors", state);
}

int Settings::showObjectIds()
{
    return _settings->value("view/objectIds", 2).toInt();
}

int Settings::showCoordinates()
{
    return _settings->value("view/coordinates", 2).toInt();
}

int Settings::showVectors()
{
    return _settings->value("view/vectors", 2).toInt();
}
