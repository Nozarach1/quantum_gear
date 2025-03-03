#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pythonhighlighter.h"
#include "projectexplorer.h"
#include "codetextedit.h"
#include "console.h"

#include <QMainWindow>
#include <QWidget>
//#include <QPlainTextEdit>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMenuBar>
#include <QFileDialog>
#include <QDockWidget>
#include <QPushButton>
#include <QSpacerItem>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:



    void file_open(QTabWidget *qtab, const QString &file_name);

    void pl_tab(QTabWidget *qtab);

    void save_file (CodeTextEdit *textEdit, const QString &file_name);

    void save_global(QTabWidget * tab_widget , QWidget *centralWidget);

    void open_project_exp(ProjectExplorer * projectexplorer);

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    PythonHighlighter *highlighter;
};
#endif // MAINWINDOW_H
