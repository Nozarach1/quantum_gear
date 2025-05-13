#include "introwindow.h"

    introwindow::introwindow(const QPixmap& pixmap, Qt::WindowFlags f)
        : QSplashScreen(pixmap, f) {

        player = new QSoundEffect(this);
        player->setSource(QUrl::fromLocalFile(":/sound/LOBOTOMY.wav"));


        showMessage("Загрузка приложения...", Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
        player->play();
    }
