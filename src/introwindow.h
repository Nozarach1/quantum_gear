#ifndef INTROWINDOW_H
#define INTROWINDOW_H
#include <QApplication>
#include <QSplashScreen>
#include <QMainWindow>
#include <QTimer>
#include <QSoundEffect>

class introwindow : public QSplashScreen {
    Q_OBJECT

public:
    introwindow(const QPixmap& pixmap = QPixmap(), Qt::WindowFlags f = Qt::WindowFlags());

private:
    QSoundEffect *player;
};

#endif // INTROWINDOW_H
