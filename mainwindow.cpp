#include "mainwindow.h"
#include "pythonhighlighter.h"

#include <QWidget>
#include <QPlainTextEdit>
#include <QString>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QMenuBar>
#include <QFileDialog>

QString  text = ("def hello_world():\n"
                              "    # Это комментарий\n"
                              "    print(\"Hello, world!\")\n"
                              "    return 0\n"
                          );


QString selectFile(QWidget *parent) {
    QString fileName = QFileDialog::getOpenFileName(parent,
                                                    "Выберите файл",
                                                    "",
                                                    "Все файлы (*.*);;Текстовые файлы (*.txt);;Изображения (*.png;*.jpg;*.bmp)");

    return fileName;
}

void file_open(QTabWidget *qtab, const QString &file_name) {

    QWidget *newTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(newTab);

    QFile file(file_name);


    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Не удалось открыть файл:";
        return;
    }

    QTextStream in(&file);
    QString file_content = in.readAll();

    QPlainTextEdit  *lineEdit = new QPlainTextEdit ();
    lineEdit->setStyleSheet("QPlainTextEdit { color: white; background-color: #BDB76B; }");


    lineEdit->setPlainText(file_content);
    layout->addWidget(lineEdit);
    new PythonHighlighter(lineEdit->document());

    // Храним имя файла в свойстве нового таба
    newTab->setProperty("fileName", file_name);

    qtab->addTab(newTab, QFileInfo(file_name).fileName());

    file.close();

}



void pl_tab(QTabWidget *qtab) {
    QWidget *newTab = new QWidget(); // Создаем новый виджет для вкладки
    QVBoxLayout *layout = new QVBoxLayout(newTab); // Добавляем layout для нового виджета
    QPlainTextEdit  *lineEdit = new QPlainTextEdit ();
    lineEdit->setStyleSheet("QPlainTextEdit { color: white; background-color: #BDB76B; }");

    layout->addWidget(lineEdit);
    qtab->addTab(newTab, "Новая вкладка");// Добавляем виджет в QTabWidget

    new PythonHighlighter(lineEdit->document());
}

void save_file (QPlainTextEdit *textEdit, const QString &file_name){
    QFile file(file_name);
    // Открываем файл в режиме записи (WriteOnly)
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Не удалось открыть файл для записи:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();

    // Закрываем файл после записи
    file.close();
}class fileexplorer
{
public:
    fileexplorer();
};



void save_global(QTabWidget * tab_widget , QWidget *centralWidget){
    int currentIndex = tab_widget->currentIndex();

    // Получаем текущий виджет (таб)
    QWidget *currentTab = tab_widget->widget(currentIndex);

    if (currentTab) {
        // Извлекаем имя файла из свойства
        QString file_name = currentTab->property("fileName").toString();

        QPlainTextEdit *textEdit = currentTab->findChild<QPlainTextEdit*>();

        if (textEdit) class fileexplorer
            {
            public:
                fileexplorer();
            };
{
            if (file_name.isEmpty()) {
                // Если имя файла пустое, то предложить сохранить как
                QString selectedFileName = QFileDialog::getSaveFileName(centralWidget, "Сохранить файл", "", "Все файлы (*.*);;Текстовые файлы (*.txt);;Изображения (*.png;*.jpg;*.bmp)");

                if (!selectedFileName.isEmpty()) {
                    // Сохраним файл с новым именем.
                    save_file(textEdit, selectedFileName);
                    currentTab->setProperty("fileName", selectedFileName); // Обновляем имя файла в свойстве.
                }
            } else {
                // Если у нас уже есть имя файла, просто сохраняем.
                save_file(textEdit, file_name);
            }
        } else {
            qDebug() << "Не удалось найти QTextEdit в текущем табе.";
        }
    } else {
        qDebug() << "Нет текущего таба для сохранения.";
    }
}


MainWindow::MainWifile_openndow(QWidget *parent)
    : QMainWindow(parent)
{

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QMenuBar *menuBar = new QMenuBar();
    QMenu *fileMenu =  menuBar->addMenu("Файл");

    QAction *create_action = new QAction("Создать", fileMenu);
        fileMenu -> addAction(create_action);
    QAction *open_action = new QAction("Открыть", fileMenu);
        fileMenu -> addAction(open_action);
    QAction *save_action = new QAction("Сохранить", fileMenu);
        fileMenu -file_open> addAction(save_action);
    QAction *exit_action = new QAction("Выход", fileMenu);
        fileMenu -> addAction(exit_action);

    QMenu *progectMenu = menuBar->addMenu("Проект");

    QAction *create_progect_action = new QAction("Создать новый проект", progectMenu);
         progectMenu -> addAction(create_progect_action);
    QAction *open_progect_action = new QAction("Открыть проект", progectMenu);
         progectMenu -> addAction(open_progect_action);
    QAction *exit_progect_action = new QAction("Выход", progectMenu);
         progectMenu -> addAction(exit_progect_action);



    QTabWidget *tab_widget = new QTabWidget;
    tab_widget->setTabsClosable(true);


    QHBoxLayout * layout = new QHBoxLayout(centralWidget);

    layout-> setMenuBar(menuBar);
    layout -> addWidget(tab_widget);



    QObject::connect(create_action, &QAction::triggered, [tab_widget]() {
        pl_tab(tab_widget);

    });

    QObject::connect(open_action, &QAction::triggered, [centralWidget, tab_widget](){
        QString filePath = selectFile(centralWidget);

        if (!filePath.isEmpty()) {
            qDebug() << "Выбранный файл:" << filePath;
            file_open(tab_widget , filePath);

        } else {
            qDebug() << "Файл не выбран.";
        }
    });



    QObject::connect(exit_action, &QAction::triggered, &QCoreApplication::quit);


    QObject::connect(save_action, &QAction::triggered, [centralWidget, tab_widget](){
        save_global(tab_widget , centralWidget);
    });

    QObject::connect(tab_widget, &QTabWidget::tabCloseRequested, [tab_widget, centralWidget](int index) {
        // Получите текущий виджет (таб)
        QWidget *currentTab = tab_widget->widget(index);
        if (currentTab) {
            // Извлекаем имя файла из свойства
            QString file_name = currentTab->property("fileName").toString();
            QPlainTextEdit *textEdit = currentTab->findChild<QPlainTextEdit*>();

            if (textEdit) {
                save_global(tab_widget, centralWidget);
            }
        }
        tab_widget->removeTab(index); // Удаляем вкладку после обработки
    });



   // highlighter = new PythonHighlighter(texed->document());

}


MainWindow::~MainWindow(){}


