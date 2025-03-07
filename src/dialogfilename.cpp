#include "dialogfilename.h"
#include "ui_dialogfilename.h"

dialogfilename::dialogfilename(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dialogfilename)
{
    ui->setupUi(this);
}

dialogfilename::~dialogfilename()
{
    delete ui;
}
