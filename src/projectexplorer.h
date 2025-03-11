#ifndef PROJECTEXPLORER_H
#define PROJECTEXPLORER_H

#include "pythonhighlighter.h"
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <QPushButton>

class ProjectExplorer : public QWidget
{
    Q_OBJECT
public:
    ProjectExplorer(QWidget *parent = nullptr, QTabWidget *tab_widget = nullptr, QString nameproject = nullptr);
    void file_open(QTabWidget *tab_widget, QString file_name);
    void pl_tab(QTabWidget *qtab ,QString *name);
private:


};

#endif // PROJECTEXPLORER_H
