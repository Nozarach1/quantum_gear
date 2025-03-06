#ifndef STARTMENU_H
#define STARTMENU_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class startmenu;
}

class startmenu : public QDialog
{
    Q_OBJECT

public:
    explicit startmenu(QWidget *parent = nullptr);
    ~startmenu();
    QString name;

private slots:

    void on_consolepythobutt_clicked();

    void on_CPPConsolebutton_clicked();

private:
    Ui::startmenu *ui;

};

#endif // STARTMENU_H
