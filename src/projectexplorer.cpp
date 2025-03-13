#include "projectexplorer.h"
#include "codetextedit.h"
#include "dialogfilename.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>

ProjectExplorer::ProjectExplorer(QWidget *parent, QTabWidget *tab_widget , QString stringname , QString lang)
    : QWidget(parent)
{
    QPushButton * plusFile =  new QPushButton("+Файл",this);
    QPushButton * plusDir =  new QPushButton("+Папка",this);

    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath(QDir::homePath());
    model->setNameFilters(QStringList() << "*.txt" << "*.cpp" << "*.py" << "*.h" << "*.hpp" << "*.c");

    QTreeView *treeView = new QTreeView(this);
    treeView->setModel(model);
    if(QDir(stringname).exists()){
        treeView->setRootIndex(model->index("/home/deck/Documents/" + stringname));
    }else{
        QDir().mkdir("/home/deck/Documents/" + stringname);
        QDir().mkdir("/home/deck/Documents/" + stringname +"/.q_conf");

        QString filePath ="/home/deck/Documents/" + stringname +"/.q_conf/conf.gson";

        QFile file(filePath);
        QTextStream out(&file);
        out << "program_lang = " + lang;
        file.close();


        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            qDebug() << "Не удалось открыть файл для записи:" << file.errorString();
            return;
        }
        file.close();
        treeView->setRootIndex(model->index("/home/deck/Documents/" + stringname));
    }

    for (int i = 1; i < model->columnCount(); ++i) {
        treeView->hideColumn(i);
    }

    treeView->setFixedWidth(300);
    for (int i = 1; i < model->columnCount(); ++i) {
        treeView->hideColumn(i);
    }

    // Настраиваем соединение
    QObject::connect(treeView, &QTreeView::clicked, this, [this, model, tab_widget](const QModelIndex &index) {
        QString filePath = model->filePath(index);
        file_open(tab_widget, filePath);
    });


    QObject::connect(plusFile, &QPushButton::clicked, this, [this, stringname, tab_widget]() {

        QString name = "";
        dialogfilename * dil = new dialogfilename;
        QObject::connect(dil, &dialogfilename::nameEntered,[&name](const QString& enteredName) {
            name = enteredName;
        });
        dil->exec();


        QString filePath = "/home/deck/Documents/" + stringname + '/' + name;
        QFile file(filePath);


        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            qDebug() << "Не удалось открыть файл для записи:" << file.errorString();
            return;
        }
        file.close();
    });



    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(plusFile);
    layout->addWidget(plusDir);
    layout->addWidget(treeView);
    setLayout(layout);
    QObject::connect(plusFile, &QPushButton::clicked , this , [](){

    });

}

void ProjectExplorer::file_open(QTabWidget *tab_widget, QString file_name )
{
    QWidget *newTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(newTab);

    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Не удалось открыть файл:";
        return;
    }

    QTextStream in(&file);
    QString file_content = in.readAll();

    CodeTextEdit *lineEdit = new CodeTextEdit();
    lineEdit->setStyleSheet("QPlainTextEdit { color: black; background-color: #f5f5f5; }");

    lineEdit->setPlainText(file_content);

    layout->addWidget(lineEdit);

    new PythonHighlighter(lineEdit->document());

    newTab->setProperty("fileName", file_name);
    tab_widget->addTab(newTab, QFileInfo(file_name).fileName());

    file.close();
}

void ProjectExplorer::pl_tab(QTabWidget *qtab , QString  *name) {

    QWidget *newTab = new QWidget(); // Создаем новый виджет для вкладки
    QVBoxLayout *layout = new QVBoxLayout(newTab); // Добавляем layout для нового виджета
    CodeTextEdit  *lineEdit = new CodeTextEdit ();
    lineEdit->setStyleSheet("QPlainTextEdit { color: black41; background-color: #f5f5f5; }");

    layout->addWidget(lineEdit);
    qtab->addTab(newTab, *name);

    new PythonHighlighter(lineEdit->document());

}



