#include "startmenu.h"
#include "ui_startmenu.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>

startmenu::startmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::startmenu)
{
    ui->setupUi(this);
}

startmenu::~startmenu()
{
    delete ui;
}

void startmenu::on_consolepythobutt_clicked()
{

    QLineEdit *nameprogect = new QLineEdit(this);
    QPushButton *Create = new QPushButton("Создать", this);

    QWidget *currentTab = ui->tabWidget->widget(0);

    QHBoxLayout *layout = new QHBoxLayout(currentTab);
    currentTab->setLayout(layout);


    currentTab->layout()->addWidget(nameprogect);
    currentTab->layout()->addWidget(Create);


    QObject::connect(Create , &QPushButton::clicked, this, [ nameprogect , this](){
        this->name = nameprogect->text();
        emit nameEntered(name);
        this->close();

    });
}

void startmenu::on_CPPConsolebutton_clicked()
{

    QLineEdit *nameprogect = new QLineEdit(this);
    QPushButton *Create = new QPushButton("Создать", this);

    QWidget *currentTab = ui->tabWidget->widget(1);


    QHBoxLayout *layout = new QHBoxLayout(currentTab);
    currentTab->setLayout(layout);


    currentTab->layout()->addWidget(nameprogect);
    currentTab->layout()->addWidget(Create);

    QObject::connect(Create , &QPushButton::clicked, this, [ nameprogect , this](){
        this->name = nameprogect->text();
        emit nameEntered(name);
        this->close();
    });

}

void startmenu::on_pushButton_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Project"), "/home/deck/Documents/", QFileDialog::ShowDirsOnly);
    QDir selectedDir(dir);

    name = selectedDir.dirName();
    emit nameEntered(name);
    this->close();

}

