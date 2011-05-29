/***************************************************************************
 *   Copyright (C) 2011 by Christian Ernst & Kai Wellmann                  *
 *   info@skynet-gfx.de                                                    *
 ***************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include "xml.h"

//#define OUTPUT

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName  ("FH-SWF");
    QCoreApplication::setOrganizationDomain("fh-swf.de");
    QCoreApplication::setApplicationName   ("3D Vector Viewer");

    _settings    = new Settings();

    _view        = new GLWidget(_settings->backgroundColor(),
                                _settings->showObjectIds(),
                                _settings->showCoordinates(),
                                _settings->showVectors(),
                                this);

    _view->setObjects(&_objects);

    _navigation  = new Navigation(this);
    _preferences = new Preferences(this);

    QObject::connect(_preferences, SIGNAL(changeBackgroundColor(GLColor)), this, SLOT(changeBackgroundColor(GLColor)));
    QObject::connect(_preferences, SIGNAL(showCoordinates(int)),           this, SLOT(showCoordinates(int)));
    QObject::connect(_preferences, SIGNAL(showObjectIds(int)),             this, SLOT(showObjectIds(int)));
    QObject::connect(_preferences, SIGNAL(showVectors(int)),               this, SLOT(showVectors(int)));

    QObject::connect(_preferences, SIGNAL(showHighlightObjects(int)),      this, SLOT(showHighlightObjects(int)));
    QObject::connect(_preferences, SIGNAL(changeHighlightColor(GLColor)),  this, SLOT(changeHighlightColor(GLColor)));
    QObject::connect(_preferences, SIGNAL(changeHighlightTime(int)),       this, SLOT(changeHighlightTime(int)));
    QObject::connect(_preferences, SIGNAL(changeHighlightRate(int)),       this, SLOT(changeHighlightRate(int)));

    QObject::connect(_navigation,  SIGNAL(play(bool)),                     this, SLOT(play(bool)));
    QObject::connect(_navigation,  SIGNAL(positionChanged(int)),           this, SLOT(setTime(int)));
    QObject::connect(_navigation,  SIGNAL(step(int)),                      this, SLOT(step(int)));

    _navigationLabel = new NavigationLabel(this);
    QObject::connect(_navigationLabel, SIGNAL(pressed(bool)), this, SLOT(openNavigation(bool)));

    ui->statusBar->addPermanentWidget(_navigationLabel);

    setCentralWidget(_view);
    ui->mainToolBar->addWidget(_navigation);
    ui->mainToolBar->setVisible(false);

    _timeMax   = _time    = 0;
    _objectPos = _timeID  = -1;

    GLObject::setHighlightColor(_settings->highlightColor());
    _highlightObjects = _settings->highlightObjects();
    _highlightTime    = _settings->highlightTime();
    _highlightRate    = _settings->highlightRate();

    _navigation->setSliderMaximum(time());

    restoreGeometry(_settings->restoreGeometry());
}

MainWindow::~MainWindow()
{
    _settings->storeGeometry(saveGeometry());

    delete ui;
    delete _view;
    delete _navigation;
    delete _preferences;
    delete _settings;
    delete _navigationLabel;
}

void MainWindow::step(int value)
{
    if(_objectPos + value >= 0 && _objectPos + value < _objects.size())
    {
        _view->setObjectIndex(_objectPos += value);
        _view->repaint();
        _navigation->setSliderPosition(_time = _objects.at(_objectPos)->time());
        updateStatusBar();
    }
}

void MainWindow::setTime(int time)
{
    _time = time;
    updateIndex();
}

void MainWindow::updateIndex()
{
    _objectPosSave = _objectPos;
    for(_objectPos = 0; _objectPos < _objects.size(); _objectPos++)
    {
        if(_time < _objects.at(_objectPos)->time())
        {
            break;
        }

        if(_highlightObjects)
        {
            int  highlightTime = _time - _objects.at(_objectPos)->time();
            bool highlightStep = (int)(highlightTime / (_highlightTime / (_highlightRate*2))) % 2;

            if(highlightTime <= _highlightTime && highlightStep)
            {
                _objects.at(_objectPos)->setHighlight(true);
            }
            else if(!highlightStep)
            {
                _objects.at(_objectPos)->setHighlight(false);
            }
        }
        else
        {
            _objects.at(_objectPos)->setHighlight(false);
        }

#ifdef OUTPUT
        if(_objects.at(_objectPos)->type() == GLObject::VECTOR_OBJECT)
        {
            GLVector * vec = (GLVector *)(_objects.at(_objectPos));

            qDebug("<object type=\"vector\" id=\"%s\">", qPrintable(vec->id()));
                    qDebug("\t<point x=\"%f\" y=\"%f\" z=\"%f\"/>", vec->sX(), vec->sY(), vec->sZ());
                    qDebug("\t<point x=\"%f\" y=\"%f\" z=\"%f\"/>", vec->eX(), vec->eY(), vec->eZ());
                    qDebug("\t<color r=\"%x\" g=\"%x\" b=\"%x\" a=\"%x\"/>", vec->color().redDez(), vec->color().greenDez(), vec->color().blueDez(), vec->color().alphaDez());
                    qDebug("\t<time>%i</time>", vec->time());
            qDebug("</object>");
        }
        else
        if(_objects.at(_objectPos)->type() == GLObject::ANGLE_OBJECT)
        {
            GLAngle * vec = (GLAngle *)(_objects.at(_objectPos));

            qDebug("<object type=\"angle\" id=\"%s\">", qPrintable(vec->id()));
                    qDebug("\t<object id=\"%s\"/>", qPrintable(vec->vectorA().id()));
                    qDebug("\t<object id=\"%s\"/>", qPrintable(vec->vectorB().id()));
                    qDebug("\t<color r=\"%x\" g=\"%x\" b=\"%x\" a=\"%x\"/>", vec->color().redDez(), vec->color().greenDez(), vec->color().blueDez(), vec->color().alphaDez());
                    qDebug("\t<time>%i</time>", vec->time());
            qDebug("</object>");
        }
        else
        if(_objects.at(_objectPos)->type() == GLObject::DELETE_OBJECT)
        {
            GLDelete * vec = (GLDelete *)(_objects.at(_objectPos));

            qDebug("<object type=\"delete\" id=\"%s\">", qPrintable(vec->id()));
                    if(!vec->objects().isEmpty())
                    {
                        foreach(GLObject * o,vec->objects())
                            qDebug("\t<object id=\"%s\"/>", qPrintable(o->id()));
                    }
                    qDebug("\t<time>%i</time>", vec->time());
            qDebug("</object>");
        }
        else
        if(_objects.at(_objectPos)->type() == GLObject::POINT_OBJECT)
        {
            GLPoint * vec = (GLPoint *)(_objects.at(_objectPos));

            qDebug("<object type=\"point\" id=\"%s\">", qPrintable(vec->id()));
                    qDebug("\t<point x=\"%f\" y=\"%f\" z=\"%f\"/>", vec->x(), vec->y(), vec->z());
                    qDebug("\t<color r=\"%x\" g=\"%x\" b=\"%x\" a=\"%x\"/>", vec->color().redDez(), vec->color().greenDez(), vec->color().blueDez(), vec->color().alphaDez());
                    qDebug("\t<time>%i</time>", vec->time());
            qDebug("</object>");
        }
        else
        if(_objects.at(_objectPos)->type() == GLObject::PLANE_OBJECT)
        {
            GLPlane * vec = (GLPlane *)(_objects.at(_objectPos));

            qDebug("<object type=\"plane\" id=\"%s\">", qPrintable(vec->id()));
                    qDebug("\t<point x=\"%f\" y=\"%f\" z=\"%f\"/>", vec->point().x(), vec->point().y(), vec->point().z());
                    qDebug("\t<normal x=\"%f\" y=\"%f\" z=\"%f\"/>", vec->normal().x(), vec->normal().y(), vec->normal().z());
                    qDebug("\t<color r=\"%x\" g=\"%x\" b=\"%x\" a=\"%x\"/>", vec->color().redDez(), vec->color().greenDez(), vec->color().blueDez(), vec->color().alphaDez());
                    qDebug("\t<time>%i</time>", vec->time());
            qDebug("</object>");
        }
        else
        if(_objects.at(_objectPos)->type() == GLObject::LINE_OBJECT)
        {
            GLLine * vec = (GLLine *)(_objects.at(_objectPos));

            qDebug("<object type=\"line\" id=\"%s\">", qPrintable(vec->id()));
                    qDebug("\t<point x=\"%f\" y=\"%f\" z=\"%f\"/>", vec->line().sX(), vec->line().sY(), vec->line().sZ());
                    qDebug("\t<point x=\"%f\" y=\"%f\" z=\"%f\"/>", vec->line().eX(), vec->line().eY(), vec->line().eZ());
                    qDebug("\t<color r=\"%x\" g=\"%x\" b=\"%x\" a=\"%x\"/>", vec->color().redDez(), vec->color().greenDez(), vec->color().blueDez(), vec->color().alphaDez());
                    qDebug("\t<time>%i</time>", vec->time());
            qDebug("</object>");
        }
#endif
    }

    _objectPos--;

    if(_objectPosSave != _objectPos)
    {
        _view->setObjectIndex(_objectPos);
    }

    _view->repaint();
    updateStatusBar();
}

void MainWindow::timerEvent(QTimerEvent *)
{
    _time += TIMERANGE;

    updateIndex();

    _navigation->setSliderPosition(_time);

    if(_time >= time())
    {
        killTimer(_timeID);
        _timeID = -1;
        _navigation->pause();
    }
}

void MainWindow::on_actionScript_start_triggered()
{
    _time = 0;
    updateIndex();
    _navigation->setSliderPosition(_time);
}

void MainWindow::on_actionScript_end_triggered()
{
    _time = time();
    updateIndex();
    _navigation->setSliderPosition(_time);
}

void MainWindow::openNavigation(bool open)
{
    ui->mainToolBar->setVisible(open);
    ui->actionNavigation->setChecked(open);
}

void MainWindow::on_actionOpen_object_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("File open"), QApplication::applicationDirPath(), "XML files (*.xml);;All files (*)");
    if(fileName.isEmpty())
        return;

    play(false);
    _timeMax = _time = _objectPos = 0;

    qDeleteAll(_objects);
    _objects = XML::readXML(fileName);

    if(XML::error())
    {
        QMessageBox::critical(this, "XML-Error", XML::errorText());
    }

    //qSort(_objects.begin(), _objects.end(), caseInsensitiveLessThanTime);

    bool shift = false;
    int last   = 0;
    GLObject * temp;

    for(int i = 0; i < _objects.size(); i++)
    {
        for(int j = 1; j < _objects.size() - last; j++)
        {
            if(_objects[j-1]->time() > _objects[j]->time())
            {
                temp          = _objects[j-1];
                _objects[j-1] = _objects[j];
                _objects[j]   = temp;

                shift         = true;
            }
        }

        if(!shift)
            break;

        shift = false;

        last++;
    }

    foreach (GLObject *object, _objects)
    {
        if(_timeMax < object->time())
            _timeMax = object->time();
    }

    _navigation->setSliderPosition(_time);
    _navigation->setSliderMaximum(time());

    updateIndex();
}

void MainWindow::updateStatusBar()
{
    int t = _time;
    if(t > time())
        t= time();

    ui->statusBar->showMessage(QString::number(_objectPos+1) + "/" + QString::number(_objects.count()) + " Objects, " +
                               QString::number(t) + "/" + QString::number(time()) + "msec Playtime");
}

/*bool MainWindow::caseInsensitiveLessThanTime(const GLObject * objectA, const GLObject * objectB)
{
    return objectA->time() < objectB->time();
}*/

void MainWindow::on_actionAbout_3DVV_triggered()
{
    QMessageBox::about(this, tr("About 3DVV"),
            tr("<b>3D Vector Viewer</b><br/>"
               "Copyright &copy; 2011 Fachhochschule S&uuml;dwestfalen<br/>"
               "Written by Christian Ernst and Kai Wellmann"));
}

void MainWindow::on_actionAboutQt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_actionPreferences_triggered()
{
    _preferences->setBackgroundColorButtonColor(_settings->backgroundColor());
    _preferences->setShowObjectIds             (_settings->showObjectIds());
    _preferences->setShowCoordinates           (_settings->showCoordinates());
    _preferences->setShowVectors               (_settings->showVectors());

    _preferences->setHighlightColorButtonColor (_settings->highlightColor());
    _preferences->setHighlightObjects          (_settings->highlightObjects());
    _preferences->setHighlightTime             (_settings->highlightTime());
    _preferences->setHighlightRate             (_settings->highlightRate());
    _preferences->exec();
}

void MainWindow::changeBackgroundColor(GLColor color)
{
    _settings->setBackgroundColor(color);
    _view->setBackgroundColor(color);
}

void MainWindow::showObjectIds(int state)
{
    _settings->setShowObjectIds(state);
    _view->setShowObjectIds(state);
}

void MainWindow::showCoordinates(int state)
{
    _settings->setShowCoordinates(state);
    _view->setShowCoordinates(state);
}

void MainWindow::showVectors(int state)
{
    _settings->setShowVectors(state);
    _view->setShowVectors(state);
}

void MainWindow::showHighlightObjects(int state)
{
    _settings->setHighlightObjects(state);
    _highlightObjects = state;
}

void MainWindow::changeHighlightColor(GLColor color)
{
    _settings->setHighlightColor(color);
    GLObject::setHighlightColor(color);
}

void MainWindow::changeHighlightTime(int value)
{
    _settings->setHighlightTime(value);
    _highlightTime = value;
    _navigation->setSliderMaximum(time());
    updateStatusBar();
}

void MainWindow::changeHighlightRate(int value)
{
    _settings->setHighlightRate(value);
    _highlightRate = value;
}

void MainWindow::play(bool value)
{
    if(value && _timeID == -1)
    {
        _timeID = startTimer(TIMERANGE);
    }
    else if(!value && _timeID != -1)
    {
        killTimer(_timeID);
        _timeID = -1;
    }
}
