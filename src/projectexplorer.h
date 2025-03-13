#ifndef PROJECTEXPLORER_H
#define PROJECTEXPLORER_H

#include "codetextedit.h"
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
    ProjectExplorer(QWidget *parent = nullptr, QTabWidget *tab_widget = nullptr, QString nameproject = nullptr , QString lang = nullptr);
    void file_open(QTabWidget *tab_widget, QString file_name);
    void pl_tab(QTabWidget *qtab ,QString *name);
    void save_global(QTabWidget * tab_widget , QWidget *centralWidget);
    void save_file (CodeTextEdit *textEdit, const QString &file_name);
private:


};

#endif // PROJECTEXPLORER_H
