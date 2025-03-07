#ifndef DIALOGFILENAME_H
#define DIALOGFILENAME_H

#include <QDialog>

namespace Ui {
class dialogfilename;
}

class dialogfilename : public QDialog
{
    Q_OBJECT

public:
    explicit dialogfilename(QWidget *parent = nullptr);
    ~dialogfilename();

private:
    Ui::dialogfilename *ui;
};

#endif // DIALOGFILENAME_H
