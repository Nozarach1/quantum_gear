#ifndef STARTMENU_H
#define STARTMENU_H

#include <QDialog>
#include <QLineEdit>
#include <QStandardPaths>

namespace Ui {
class startmenu;
}

class startmenu : public QDialog
{
    Q_OBJECT

public:
    explicit startmenu(QWidget *parent = nullptr);
    ~startmenu();


signals:
    void nameEntered(const QString& name , const QString& proglan);
private slots:

    void on_consolepythobutt_clicked();

    void on_CPPConsolebutton_clicked();

    void on_pushButton_clicked();

private:
    Ui::startmenu *ui;
    QString name;
    QString proglan;
};

#endif // STARTMENU_H
