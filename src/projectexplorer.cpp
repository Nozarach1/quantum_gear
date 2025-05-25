#include "projectexplorer.h"
#include "codetextedit.h"
#include "dialogfilename.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

ProjectExplorer::ProjectExplorer(QWidget *parent, QTabWidget *tab_widget , QString stringname , QString lang)
    : QWidget(parent)
{
    QString cmake_base_content =
        "cmake_minimum_required(VERSION 3.5)\n"
        "project(" + stringname +")\n\n"
        "set(CMAKE_CXX_STANDARD 17)\n"
        "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n"
        "add_executable(+" + stringname + "+\n";

    QPushButton * plusFile =  new QPushButton("+Файл",this);
    QPushButton * plusDir =  new QPushButton("+Папка",this);
    QPushButton * deleteB =  new QPushButton("Удалить",this);



    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath(QDir::homePath());
    model->setNameFilters(QStringList() << "*.txt" << "*.cpp" << "*.py" << "*.h" << "*.hpp" << "*.c" << "CMakeListsd.txt" << ".png" << ".ui" <<".qss" << ".qrc");

    model->setNameFilterDisables(false);
    model->setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);



    treeView = new QTreeView(this);
    treeView->setModel(model);
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);
    treeView->setUniformRowHeights(true);
    treeView->setAnimated(false);



    if(QDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/"+ stringname).exists()){
        treeView->setRootIndex(model->index(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" + stringname));
    }else{
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +"/"+ stringname);
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +"/"+ stringname +"/.q_conf");


        QString filePath =QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +"/" + stringname +"/.q_conf/conf.gson";

        QFile file(filePath);
        QTextStream out(&file);
        out << "program_lang = " + lang + ';';
        file.close();


        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            qDebug() << "Не удалось открыть файл для записи:" << file.errorString();
        }
        file.close();
        treeView->setRootIndex(model->index(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +"/" + stringname));

        if(lang == "PYTHON"){

            QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +"/"+ stringname + '/' + "main.py";
            QFile mainfile(filePath);
            mainfile.open(QIODevice::WriteOnly);
            mainfile.close();

        }else if (lang == "CPP"){
            QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +"/"+ stringname + '/' + "main.cpp";
            QFile mainfile(filePath);
            mainfile.open(QIODevice::WriteOnly);
            mainfile.close();

            QString filemake = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +"/"+ stringname + '/' + "CMakeLists.txt";
            QFile  mainfilemake (filemake);
            mainfilemake.open(QIODevice::WriteOnly);
            mainfilemake.write(cmake_base_content.toUtf8());
            mainfilemake.write("main.cpp \n )");
        }
    }


    for (int i = 1; i < model->columnCount(); ++i) {
        treeView->hideColumn(i);
    }

    treeView->setFixedWidth(300);
    for (int i = 1; i < model->columnCount(); ++i) {
        treeView->hideColumn(i);
    }

    QObject::connect(treeView, &QTreeView::doubleClicked, this, [this, model, tab_widget](const QModelIndex &index) {
        QString filePath = model->filePath(index);

        if (model->isDir(index)) {

            qDebug() << "Это папка:" << filePath;

            treeView->setExpanded(index, !treeView->isExpanded(index));
        } else {

            qDebug() << "Это файл:" << filePath;
            file_open(tab_widget, filePath, nullptr);
        }
    });


    QObject::connect(plusFile, &QPushButton::clicked, this, [this, stringname, tab_widget]() {

        QString name = "";
        dialogfilename * dil = new dialogfilename;
        QObject::connect(dil, &dialogfilename::nameEntered,[&name](const QString& enteredName) {
            name = enteredName;
        });
        dil->exec();

        QString adres = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +"/"+ stringname + '/';
        QString filePath = name;

        if(!filePath.contains(adres)){
            filePath.prepend(adres);
        }

        QFile file(filePath);


        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            qDebug() << "Не удалось создать файл для записи:" << file.errorString();
            return;
        }
        file.close();
    });

    QObject::connect(plusDir, &QPushButton::clicked, this, [this, stringname, tab_widget]() {

        QString name = "";
        dialogfilename * dil = new dialogfilename;
        QObject::connect(dil, &dialogfilename::nameEntered,[&name](const QString& enteredName) {
            name = enteredName;
        });
        dil->exec();


        QString adres = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +"/"+ stringname + '/';
        QString dirPath = name;


        if(!dirPath.contains(adres)){
            dirPath.prepend(adres);
        }
        QDir().mkdir(dirPath);

        if (!QDir(dirPath).exists()) {
            qDebug() << "Не удалось создать   каталог:" <<Qt::endl;
            return;
        }

    });

    QObject::connect(deleteB, &QPushButton::clicked, this, [this , model]() {
        QModelIndex currentIndex = treeView->currentIndex();
        if (currentIndex.isValid()) {
            delete_file_dir(currentIndex, model);
        }
    });



    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(plusFile);
    layout->addWidget(plusDir);
    layout->addWidget(deleteB);
    layout->addWidget(treeView);
    setLayout(layout);
    QObject::connect(plusFile, &QPushButton::clicked , this , [](){

    });

}

bool ProjectExplorer::delete_file_dir(const QModelIndex &index, QFileSystemModel *model){
    if (!index.isValid()) return false;

    QString path = model->filePath(index);
    QFileInfo fileInfo(path);

    // Диалог подтверждения
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "Подтверждение",
        QString("Удалить %1?").arg(fileInfo.fileName()),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply != QMessageBox::Yes) return false;

    bool success = fileInfo.isDir() ? QDir(path).removeRecursively() : QFile::remove(path);

    if (success) {
        QString path = model->filePath(index.parent());
        model->setRootPath("");  // Сброс
        model->setRootPath(path);
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось удалить!");
    }

    return success;
}

QString ProjectExplorer::detectLanguageByExtension(const QString &fileName) {
    QFileInfo fileInfo(fileName);
    QString ext = fileInfo.suffix().toLower();

    if (ext == "py") return "PYTHON";
    if (ext == "cpp" || ext == "cxx" || ext == "cc" || ext == "c++" || ext == "h" || ext == "hpp") return "CPP";
    if (ext == "qml") return "qml";
    if (ext == "js") return "javascript";
    if (ext == "html" || ext == "htm") return "html";
    if (ext == "css") return "css";
    if (ext == "json") return "json";
    if (ext == "xml") return "xml";

    return "plain";
}


void ProjectExplorer::file_open(QTabWidget *tab_widget, QString file_name, QString lang) {
    QWidget *newTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(newTab);

    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Не удалось открыть файл:" << file_name;
        delete newTab;
        return;
    }

    QTextStream in(&file);
    QString file_content = in.readAll();
    file.close();

    CodeTextEdit *textEdit = new CodeTextEdit();
    textEdit->setPlainText(file_content);
    layout->addWidget(textEdit);

    // Определяем язык (если не задан явно)
    QString language = lang.isEmpty() ? detectLanguageByExtension(file_name) : lang;

    // Создаем подсветку синтаксиса
    syntaxHighlighter = new CodeHighlighter(textEdit->document());
    syntaxHighlighter->setLanguage(language);

    newTab->setProperty("fileName", file_name);
    tab_widget->addTab(newTab, QFileInfo(file_name).fileName());
}

// void ProjectExplorer::pl_tab(QTabWidget *qtab , QString  *name, QString lang) {

//     QWidget *newTab = new QWidget();
//     QVBoxLayout *layout = new QVBoxLayout(newTab);
//     CodeTextEdit  *lineEdit = new CodeTextEdit ();
//     //lineEdit->setStyleSheet("QPlainTextEdit { color: black41; background-color: #f5f5f5; }");

//     layout->addWidget(lineEdit);
//     qtab->addTab(newTab, *name);

//     //new CodeHighlighter(lineEdit->document());
//     syntaxHighlighter = new CodeHighlighter (lineEdit->document());
//     syntaxHighlighter->setLanguage((lang).toUtf8());

// }





