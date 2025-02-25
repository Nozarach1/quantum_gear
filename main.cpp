#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    a.setStyleSheet("QMainWindow { background-color: #2E2E2E; }"
                    "QPushButton { background-color: #4CAF50; color: white; }"
                    "QLabel { color: white; }");

    MainWindow w;
    w.setWindowTitle("Жесть какой текстовый редактор");
    w.setWindowState(Qt::WindowMaximized);


    w.show();
    return a.exec();
}
