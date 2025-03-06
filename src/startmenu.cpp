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

    QLineEdit *nameprogect = new QLineEdit("Название проекта",this);
    QPushButton *Create = new QPushButton("Создать", this);

    QWidget *currentTab = ui->tabWidget->widget(0);

    if (!currentTab->layout()) {
        QHBoxLayout *layout = new QHBoxLayout(currentTab);
        currentTab->setLayout(layout);
    }

    currentTab->layout()->addWidget(nameprogect);
    currentTab->layout()->addWidget(Create);
    this->name = nameprogect->text();
}

void startmenu::on_CPPConsolebutton_clicked()
{

    QLineEdit *nameprogect = new QLineEdit("Название проекта",this);
    QPushButton *Create = new QPushButton("Создать", this);

    QWidget *currentTab = ui->tabWidget->widget(0);

    if (!currentTab->layout()) {
        QHBoxLayout *layout = new QHBoxLayout(currentTab);
        currentTab->setLayout(layout);
    }

    currentTab->layout()->addWidget(nameprogect);
    currentTab->layout()->addWidget(Create);
    this->name = nameprogect->text();
}
