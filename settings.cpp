#include "settings.h"
#include <QVector>

Settings::Settings(QString organization, QString application)
{
    _settings = new QSettings(organization, application);
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
