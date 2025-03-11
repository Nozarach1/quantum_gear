#ifndef DIALOGFILENAME_H
#define DIALOGFILENAME_H

#include <QDialog>
#include <QString>

namespace Ui {
class dialogfilename;
}

class dialogfilename : public QDialog
{
    Q_OBJECT

public:
    explicit dialogfilename(QWidget *parent = nullptr);
    ~dialogfilename();

signals:
    void nameEntered(const QString& name);

private slots:
    void on_pushButton_clicked();

private:
    Ui::dialogfilename *ui;
    QString name;
};

#endif // DIALOGFILENAME_H
