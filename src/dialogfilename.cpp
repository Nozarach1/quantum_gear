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

void dialogfilename::on_pushButton_clicked()
{
    this->name = ui->lineEdit->text();
    this->name.prepend(addres);
    emit nameEntered(name);

    this->close();
}

QString selectDir(QWidget *parent) {
    QString fileName = QFileDialog::getExistingDirectory(parent,
                                                    "Каталог",
                                                    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));

    return fileName;
}

void dialogfilename::on_dirButton_clicked()
{

    this->addres.append(selectDir(this));
    this->addres.append("/");

}

