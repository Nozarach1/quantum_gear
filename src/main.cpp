#include "mainwindow.h"
#include "introwindow.h"
#include <QApplication>
#include <QTimer>
#include <QPixmap>
#include <QElapsedTimer>
#include <QThread>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Загружаем изображение для начального экрана
    QPixmap pixmap(":/images/start_frame.png"); // Укажите путь к изображению
    if (pixmap.isNull()) {
        qWarning("Не удалось загрузить изображение для начального экрана!");
        return -1;
    }

    // Создаем и показываем начальный экран
    introwindow splash(pixmap);
    splash.show();

    // Устанавливаем стили для приложения
    a.setStyleSheet("QMainWindow { background-color: #2E2E2E; }"
                    "QPushButton { background-color: #4CAF50; color: white; }"
                    "QLabel { color: white; }");

    // Создаем главное окно, но не показываем его сразу
    MainWindow w;
    w.setWindowTitle("Жесть какой текстовый редактор");
    w.setWindowState(Qt::WindowMaximized);

    // Задержка в 3 секунды
    QElapsedTimer timer;
    timer.start();
    while (timer.elapsed() < 3000) {
        a.processEvents(); // Обрабатываем события, чтобы приложение не зависло
    }

    // Закрываем начальный экран и показываем главное окно
    splash.close();
    w.show();

    return a.exec();
}
