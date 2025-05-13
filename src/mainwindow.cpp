#include "mainwindow.h"

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

void MainWindow::file_open(QTabWidget *qtab, const QString &file_name) {

    QWidget *newTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(newTab);

    QFile file(file_name);


    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Не удалось открыть файл:";
        return;
    }

    QTextStream in(&file);
    QString file_content = in.readAll();

    CodeTextEdit  *lineEdit = new CodeTextEdit ();
    lineEdit->setStyleSheet("QPlainTextEdit { color: black; background-color: #f5f5f5; }");


    lineEdit->setPlainText(file_content);
    layout->addWidget(lineEdit);
    new PythonHighlighter(lineEdit->document());


    newTab->setProperty("fileName", file_name);

    qtab->addTab(newTab, QFileInfo(file_name).fileName());

    file.close();
}

void MainWindow::pl_tab(QTabWidget *qtab) {
    QWidget *newTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(newTab);
    CodeTextEdit  *lineEdit = new CodeTextEdit ();
    lineEdit->setStyleSheet("QPlainTextEdit { color: black41; background-color: #f5f5f5; }");

    layout->addWidget(lineEdit);
    qtab->addTab(newTab, "Новая вкладка");

    new PythonHighlighter(lineEdit->document());
}

void MainWindow::save_file (CodeTextEdit *textEdit, const QString &file_name){
    QFile file(file_name);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Не удалось открыть файл для записи:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();


    file.close();
}

void MainWindow::save_global(QTabWidget * tab_widget , QWidget *centralWidget){
    int currentIndex = tab_widget->currentIndex();

    QWidget *currentTab = tab_widget->widget(currentIndex);

    if (currentTab) {

        QString file_name = currentTab->property("fileName").toString();

        CodeTextEdit *textEdit = currentTab->findChild<CodeTextEdit*>();

        if (textEdit) {
            if (file_name.isEmpty()) {

                QString selectedFileName = QFileDialog::getSaveFileName
                    (centralWidget, "Сохранить файл",
                        "", "Все файлы (*.*);;Текстовые файлы (*.txt);;Изображения (*.png;*.jpg;*.bmp)");

                if (!selectedFileName.isEmpty()) {

                    save_file(textEdit, selectedFileName);
                    currentTab->setProperty("fileName", selectedFileName); // Обновляем имя файла в свойстве.
                }
            } else {

                save_file(textEdit, file_name);
            }
        } else {
            qDebug() << "Не удалось найти QTextEdit в текущем табе.";
        }
    } else {
        qDebug() << "Нет текущего таба для сохранения.";
    }
}

void MainWindow::open_project_exp(ProjectExplorer * projectexplorer , QString name){

    QDockWidget *dockWidget = new QDockWidget(tr(name.toUtf8()), this);
    dockWidget->setWidget(projectexplorer);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}

void MainWindow::open_console(Console * console){

    QDockWidget *dockWidget0 = new QDockWidget(this);
    dockWidget0->setWidget(console);
    dockWidget0->setAllowedAreas(Qt::BottomDockWidgetArea | Qt::TopDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, dockWidget0);
}



void handleCommand(const QString& command) {
    qDebug() << "Command entered: " << command;

}


MainWindow::MainWindow(QWidget *parent , QString nameprogect , QString program_lang) : QMainWindow(parent) {
    if(nameprogect == ""){
        QMetaObject::invokeMethod(this,"close",Qt::QueuedConnection);
    }

    QPushButton *run = new QPushButton("&Run");
    QPushButton *run_debug = new QPushButton("&Run Debug");

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);
    QHBoxLayout *layouth = new QHBoxLayout(centralWidget);
    layout -> addLayout(layouth);

    QSpacerItem * spase = new QSpacerItem(0, 0, QSizePolicy::Expanding);

    Console *console = new Console( nullptr , nameprogect);
    open_console(console);

    layouth -> addWidget(run);
    layouth -> addWidget(run_debug);
    layouth ->addSpacerItem(spase);


    QMenuBar *menuBar = this->menuBar();

    QMenu *fileMenu =  menuBar->addMenu("Файл");
    QMenu *progectMenu = menuBar->addMenu("Проект");

    QAction *create_action = new QAction("Создать", fileMenu);
        fileMenu -> addAction(create_action);
    QAction *open_action = new QAction("Открыть", fileMenu);
        fileMenu -> addAction(open_action);
    QAction *save_action = new QAction("Сохранить", fileMenu);
        fileMenu -> addAction(save_action);
    QAction *exit_action = new QAction("Выход", fileMenu);
        fileMenu -> addAction(exit_action);

    QAction *create_progect_action = new QAction("Создать новый проект", progectMenu);
        progectMenu -> addAction(create_progect_action);
    QAction *open_progect_action = new QAction("Открыть проект", progectMenu);
        progectMenu -> addAction(open_progect_action);
    QAction *  open_project_explorer = new QAction("Обозреватель проекта", progectMenu);
        progectMenu -> addAction(open_project_explorer);
    QAction *  open_console = new QAction("Терминал", progectMenu);
    QAction *exit_progect_action = new QAction("Выход", progectMenu);

        progectMenu -> addAction(exit_progect_action);

    QTabWidget *tab_widget = new QTabWidget;
        tab_widget->setMovable(true);
        tab_widget->setTabsClosable(true);



    layout -> addWidget(tab_widget);

//?
    ProjectExplorer * projectexplorer = new ProjectExplorer(centralWidget , tab_widget, nameprogect ,program_lang);

    open_project_exp(projectexplorer , nameprogect);
//?
    QObject::connect(create_action, &QAction::triggered, [tab_widget, this]() {
        pl_tab(tab_widget);

    });

    QObject::connect(open_action, &QAction::triggered, [centralWidget, tab_widget, this](){
        QString filePath = selectFile(centralWidget);

        if (!filePath.isEmpty()) {
            qDebug() << "Выбранный файл:" << filePath;
            file_open(tab_widget , filePath);

        } else {
            qDebug() << "Файл не выбран.";
        }
    });

    QObject::connect(exit_action, &QAction::triggered, &QCoreApplication::quit);


    QObject::connect(save_action, &QAction::triggered, [centralWidget, tab_widget, this](){
        save_global(tab_widget , centralWidget);
    });

    QObject::connect(tab_widget, &QTabWidget::tabCloseRequested, [tab_widget, centralWidget, this](int index) {

        QWidget *currentTab = tab_widget->widget(index);
        if (currentTab) {

            QString file_name = currentTab->property("fileName").toString();
            CodeTextEdit *textEdit = currentTab->findChild<CodeTextEdit*>();

            if (textEdit) {
                save_global(tab_widget, centralWidget);
            }
        }
        tab_widget->removeTab(index);
    });


    QObject::connect(open_project_explorer, &QAction::triggered, [projectexplorer,nameprogect, this]() {
        open_project_exp(projectexplorer, nameprogect);
    });


    QObject::connect(run, &QPushButton::clicked, [console, this]() {
            console->Run();
    });


    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this);


    QObject::connect(shortcut,    &QShortcut::activated, [tab_widget , centralWidget , this]{
        int currentIndex = tab_widget->currentIndex();
        QWidget *currentTab = tab_widget->widget(currentIndex);
        QString file_name = currentTab->property("fileName").toString();
        CodeTextEdit *textEdit = currentTab->findChild<CodeTextEdit*>();

        save_file(textEdit, file_name);
    });




}


MainWindow::~MainWindow(){}


