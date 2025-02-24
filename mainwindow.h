#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pythonhighlighter.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    PythonHighlighter *highlighter;
};
#endif // MAINWINDOW_H
