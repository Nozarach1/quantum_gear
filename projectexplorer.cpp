#include "projectexplorer.h"
#include "codetextedit.h"
#include <QDebug>
#include <QFile>

ProjectExplorer::ProjectExplorer(QWidget *parent, QTabWidget *tab_widget)
    : QWidget(parent)
{
    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath(QDir::homePath());
    model->setNameFilters(QStringList() << "*.txt" << "*.cpp" << "*.py" << "*.h" << "*.hpp" << "*.c");

    QTreeView *treeView = new QTreeView(this);
    treeView->setModel(model);
    treeView->setRootIndex(model->index(QDir::homePath()));  // Устанавливаем корневую директорию для отображения

    for (int i = 1; i < model->columnCount(); ++i) {
        treeView->hideColumn(i);
    }

    treeView->setFixedWidth(300);
    for (int i = 1; i < model->columnCount(); ++i) {
        treeView->hideColumn(i);
    }

    // Настраиваем соединение
    QObject::connect(treeView, &QTreeView::clicked, this, [this, model, tab_widget](const QModelIndex &index) {
        QString filePath = model->filePath(index);
        file_open(tab_widget, filePath);
    });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(treeView);
    setLayout(layout);
}

void ProjectExplorer::file_open(QTabWidget *tab_widget, QString file_name )
{
    QWidget *newTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(newTab);

    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Не удалось открыть файл:";
        return;
    }

    QTextStream in(&file);
    QString file_content = in.readAll();

    CodeTextEdit *lineEdit = new CodeTextEdit();
    lineEdit->setStyleSheet("QPlainTextEdit { color: black; background-color: #f5f5f5; }");
    lineEdit->setPlainText(file_content);
    layout->addWidget(lineEdit);
    new PythonHighlighter(lineEdit->document());

    newTab->setProperty("fileName", file_name);
    tab_widget->addTab(newTab, QFileInfo(file_name).fileName());

    file.close();
}
