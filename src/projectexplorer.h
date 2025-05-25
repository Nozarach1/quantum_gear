#ifndef PROJECTEXPLORER_H
#define PROJECTEXPLORER_H

#include "codetextedit.h"
#include "codehighlighter.h"
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStandardPaths>
class ProjectExplorer : public QWidget
{
    Q_OBJECT
public:
    ProjectExplorer(QWidget *parent = nullptr, QTabWidget *tab_widget = nullptr, QString nameproject = nullptr , QString lang = nullptr);
    void file_open(QTabWidget *tab_widget, QString file_name, QString lang);
    void pl_tab(QTabWidget *qtab ,QString *name, QString lang);
    void save_global(QTabWidget * tab_widget , QWidget *centralWidget);
    void save_file (CodeTextEdit *textEdit, const QString &file_name);
    bool delete_file_dir(const QModelIndex &index, QFileSystemModel *model);
    QString detectLanguageByExtension(const QString &fileName);
    ~ProjectExplorer(){};
    //QFile * mainfilemake;
private:
    CodeHighlighter *syntaxHighlighter = nullptr;
    QTreeView *treeView = nullptr;

};

#endif // PROJECTEXPLORER_H
