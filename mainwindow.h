#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pythonhighlighter.h"

#include <QMainWindow>
#include <QWidget>
#include <QPlainTextEdit>
#include <QString>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMenuBar>
#include <QFileDialog>
#include <QDockWidget>

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
