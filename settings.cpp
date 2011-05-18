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

void Settings::setHighlightColor(GLColor &color)
{
    _settings->setValue("view/highlight/color", color.qcolor());
}

GLColor Settings::highlightColor()
{
    return GLColor(_settings->value("view/highlight/color", GLColor(1.0f, 0.0f, 0.0f).qcolor()).value<QColor>());
}

void Settings::setHighlightObjects(int state)
{
    _settings->setValue("view/highlight/objects", state);
}

void Settings::setHighlightTime(int value)
{
    _settings->setValue("view/highlight/time", value);
}

void Settings::setHighlightRate(int value)
{
    _settings->setValue("view/highlight/rate", value);
}

int Settings::highlightObjects()
{
    return _settings->value("view/highlight/objects", 2).toInt();
}

int Settings::highlightTime()
{
    return _settings->value("view/highlight/time", 1000).toInt();
}

int Settings::highlightRate()
{
    return _settings->value("view/highlight/rate", 2).toInt();
}
