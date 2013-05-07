/* vim: set sw=4 ts=4 et: */
/*
 * This file is part of Other Maemo Weather(omweather) - MeeCast
 *
 * Copyright (C) 2006-2013 Vlad Vasilyeu
 * Copyright (C) 2010-2011 Tanya Makova
 *     for the code
 *
 * Copyright (C) 2008 Andrew Zhilin
 *		      az@pocketpcrussia.com 
 *	for default icon set (Glance)
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU weather-config.h General Public
 * License along with this software; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */
/*******************************************************************************/

#include <QtCore/QtGlobal>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QTranslator>
#include <QLocale>

#include <QHash>
#include <QGraphicsGridLayout>
#include <exception>
#include <iostream>

#include "core.h"
#include "dataqml.h"
#include "configqml.h"
#include "qmllayoutitem.h"
#include "dataitem.h"
#include "datamodel.h"
#include "parserqt.h"
#include "databasesqlite.h"
#include "abstractconfig.h"
#include "controller.h" 

#include <QtDebug>

#include <libintl.h>
#include <locale.h>

#include "selectmodel.h"
#include <fcntl.h>


#include <locale.h>

//#define _(String) gettext(String)

#define _(String)  QObject::trUtf8(String).toStdString().c_str()

#include <bb/cascades/QmlDocument>
#include <bb/cascades/Page>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/SceneCover>


using ::bb::cascades::Application;
using namespace bb::cascades;

//////////////////////////////////////////////////////////////////////////////
bool
update_weather_forecast(Core::Config *config){
    uint i;
    int success = 0;
    Core::Station* station;

    for (i = 0; i < config->stationsList().size(); i++){
        station = config->stationsList().at(i);
        if (station->updateData(true)){
            success ++;
        }
    }
    return true;
}
//////////////////////////////////////////////////////////////////////////////
void myMessageOutput(QtMsgType type, const char* msg){
    fprintf(stdout, "%s\n", msg);
    fflush(stdout);
}



Q_DECL_EXPORT
int main(int argc, char* argv[])
{
    std::cerr<<"Begin"<<std::endl;


    //QApplication app(argc, argv);
    Application app(argc, argv);

    /* Fo DEBUG on emulator or device */
    /*
       int fd;
       fflush( stderr );
       fd = open( "shared/documents/meego.tx", O_WRONLY|O_CREAT|O_TRUNC, 0666 );
       dup2( fd, STDERR_FILENO );
       close( fd );
       */
    qInstallMsgHandler(myMessageOutput);

    std::cerr<<"Begin"<<std::endl;
    QString str = QDir::currentPath();
    std::cerr<<str.toStdString().c_str()<<std::endl;
    QDir::setCurrent(QDir::currentPath());

    // Set up the translator.
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString("omweather_%1").arg(locale_string);
    if (translator.load(filename, "app/native/qm")) {
        std::cerr<<"Success TR"<<std::endl;
        app.installTranslator(&translator);
    }

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

 /*
    std::cerr<<"begin ssss "<<std::endl;
    Dirent *dp = 0;
    DIR *dir_fd = opendir(("./app/native"));
    if(dir_fd){
        while((dp = readdir(dir_fd))){
            std::string name = dp->d_name;
            std::cerr<<"ssss "<<std::endl;
            std::cerr<<name.c_str()<<std::endl;
        }
    }
*/
    
    //Add the QML snippet into the layout


    ConfigQml *config;
    //QString locale = QLocale::system().name();
    //std::cerr<<"locale: "<<locale.toStdString()<<std::endl;
  //  QString locale = QLocale::system().name();

   // std::cerr<<"locale: "<<locale.toStdString()<<std::endl;
    Controller *controller;

    std::cerr<<"Before controller "<<std::endl;

    controller = new Controller("asset:///qml/main.qml");

    std::cerr<<"After controller "<<std::endl;
    controller->load_data();
/*
    QTranslator translator;
    translator.load("ru.qml", "i18n");
    app.installTranslator(&translator);
*/
    
    /* Locale */
    /*
    for (unsigned int i=0; i<controller->config()->languagesList().size(); i++){
>>>>>>> 6787589fc1cb0d776a92c5fe8293cbc98f2dc76d
        if (controller->config()->languagesList().at(i).first == controller->config()->Language()){
            setlocale (LC_ALL, controller->config()->languagesList().at(i).second.c_str());
            setlocale (LC_MESSAGES, controller->config()->languagesList().at(i).second.c_str());
            QLocale::setDefault(QLocale(controller->config()->languagesList().at(i).second.c_str()));
        }
    }
    textdomain("omweather");
    bindtextdomain("omweather", "/opt/com.meecast.omweather/share/locale");
<<<<<<< HEAD

    
    */

    config = controller->config();
    //std::cerr<<"iconpath = "<<config->imagespath().toStdString() << std::endl;
 //   update_weather_forecast(config);
    
    QmlDocument *qml; 
    qml = controller->qview();

/*
    qview->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    qview->setAttribute(Qt::WA_OpaquePaintEvent);

    qview->setAttribute(Qt::WA_NoSystemBackground);

    qview->viewport()->setAttribute(Qt::WA_OpaquePaintEvent);

    qview->viewport()->setAttribute(Qt::WA_NoSystemBackground);

*/
    std::cerr << "qml path = " << Core::AbstractConfig::layoutqml << std::endl;
    //qview->setSource(QUrl::fromLocalFile(QString::fromStdString(Core::AbstractConfig::prefix +
    //                                                            Core::AbstractConfig::sharePath +
    //                                                            Core::AbstractConfig::layoutqml)));
//    qview->setSource(QUrl::fromLocalFile(QString::fromStdString("app/native/assets/usr/share/omweather/qml/WeatherPage.qml")));
  //    qview->setSource(QUrl::fromLocalFile(QString::fromStdString("app/native/assets/main.qml")));
 //   qview->setSource(QUrl::fromLocalFile(QString::fromStdString("app/native/assets/hellocascades.qml")));

    //qview->setSource(QUrl::fromLocalFile(QString::fromStdString("app/main.qml")));
    //qview->setResizeMode(QDeclarativeView::SizeRootObjectToView);


    std::cerr << "Before show"<< std::endl;
    //qview->showFullScreen();

    // Obtain a QMLDocument and load it into the qml variable, using build patterns.
  //     QmlDocument *qml = QmlDocument::create("asset:///hellocascades.qml");
    //  QmlDocument *qml = QmlDocument::create("asset:///qml/main.qml");
    //QmlDocument *qml = QmlDocument::create("asset:///qml/SettingsPage.qml");
       QObject::connect((QObject*)qml, SIGNAL(quit()), &app, SLOT(quit()));
   //    QmlDocument *qml = QmlDocument::create("asset:///Weather.qml");

       // If the QML document is valid, we process it.
       if (!qml->hasErrors()) {

           // Create the application Page from QMLDocument.
    	   config->appPage = qml->createRootObject<AbstractPane>();
    	  // Page  *appPage = qml->createRootObject<Page>();
           if (config->appPage) {
               // Set the main scene for the application to the Page.
               Application::instance()->setScene(config->appPage);
           }
       }
     QList<QDeclarativeError> errorList = qml->errors();
     foreach (const QDeclarativeError &error, errorList) {
                 qWarning() << error;
                 std::cerr << "Before show11111111 "<<error.toString().toStdString()<<	 std::endl;
             }

    app.setCover(controller->active_frame);
    std::cerr << "After show"<< std::endl;

    /*This code provides Segmantation fault
    delete dadapt;
    delete controller;
    */
    return app.exec();
   
}
