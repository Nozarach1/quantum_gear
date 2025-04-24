#include "mainwindow.h"
#include "introwindow.h"
#include "startmenu.h"
#include <QApplication>
#include <QTimer>
#include <QPixmap>
#include <QElapsedTimer>
#include <QThread>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QPixmap pixmap(":/images/start_frame.png");
    if (pixmap.isNull()) {
        qWarning("Не удалось загрузить изображение для начального экрана!");
        return -1;
    }


    introwindow splash(pixmap);
    splash.show();


    a.setStyleSheet("QMainWindow { background-color: #2E2E2E; }"
                    "QPushButton { background-color: #4CAF50; color: white; }"
                    "QLabel { color: white; }");


            QElapsedTimer timer;
            timer.start();
            while (timer.elapsed() < 3000) {
                a.processEvents();
            }

        splash.close();

    QString name;
    QString proglan;
    startmenu * menu = new startmenu;

    QObject::connect(menu, &startmenu::nameEntered,[&name , &proglan](const QString& enteredName , const QString& enteredProglan) {
        name = enteredName;
        proglan = enteredProglan;
    });
    menu->exec();

    MainWindow w(nullptr , name, proglan);
   // w.setProjectName(name);
    w.setWindowTitle("Жесть какой текстовый редактор");
    w.setWindowState(Qt::WindowMaximized);

    w.show();

    return a.exec();
}
