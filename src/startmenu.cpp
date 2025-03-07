#include "startmenu.h"
#include "ui_startmenu.h"
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

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
