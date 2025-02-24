#include "mainwindow.h"
#include "pythonhighlighter.h"



#include <QWidget>
#include <QPlainTextEdit>
#include <QString>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMenuBar>

QString * text = new QString("def hello_world():\n"
                              "    # Это комментарий\n"
                              "    print(\"Hello, world!\")\n"
                              "    return 0\n"
                          );


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QMenuBar * menubar = new QMenuBar(nullptr);
    QMenu * File = new  QMenu;

    menubar->addMenu(File);
   // File ->setActiveAction();
    QPlainTextEdit  * texed = new QPlainTextEdit (this);

    QFont font;
    font.setPointSize(12);
    texed->setFont(font);
    texed->setPlainText(*text);


    QHBoxLayout * lauoyt = new QHBoxLayout(centralWidget);
    lauoyt -> addWidget(texed);


    highlighter = new PythonHighlighter(texed->document());

}

MainWindow::~MainWindow()
{
    delete highlighter;
}


