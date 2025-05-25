#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "codehighlighter.h"
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

#include <QShortcut>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:




    void file_open(QTabWidget *qtab, const QString &file_name, QString program_lang);

    void pl_tab(QTabWidget *qtab, QString program_lang);

    void save_file (CodeTextEdit *textEdit, const QString &file_name);

    void save_global(QTabWidget * tab_widget , QWidget *centralWidget);

    void open_project_exp(ProjectExplorer * projectexplorer,  QString name);
    void open_console(Console * console);

    MainWindow(QWidget *parent = nullptr , QString nameprogect = nullptr , QString program_lang = nullptr);
    ~MainWindow();

    //void setProjectName(const QString &name );
private:
    CodeHighlighter *highlighter;
    //QString nameprogect;
};
#endif // MAINWINDOW_H
