#ifndef PROJECTEXPLORER_H
#define PROJECTEXPLORER_H

#include "pythonhighlighter.h"
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QPlainTextEdit>

class ProjectExplorer : public QWidget
{
    Q_OBJECT
public:
    ProjectExplorer(QWidget *parent = nullptr, QTabWidget *tab_widget = nullptr);

private:
    void file_open(QTabWidget *tab_widget, QString file_name);
};

#endif // PROJECTEXPLORER_H
