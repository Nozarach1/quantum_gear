#include "console.h"

Console::Console(QWidget *parent) : QWidget(parent) {
    output = new QPlainTextEdit(this);
    input = new QLineEdit(this);
    output->setReadOnly(true);
    output->setFont(QFont("Monospace", 10));

    process = new QProcess(this);

    // Connect signals
    connect(process, &QProcess::readyReadStandardOutput, this, &Console::readOutput);
    connect(process, &QProcess::readyReadStandardError, this, &Console::readError);
    connect(process, &QProcess::started, this, &Console::processStarted);
    connect(process, &QProcess::finished, this, &Console::processFinished);
    connect(process, &QProcess::errorOccurred, this, &Console::processError);
    connect(input, &QLineEdit::returnPressed, this, &Console::sendCommand);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(output);
    layout->addWidget(input);

    setLayout(layout);

    // Start the shell
    process->start("/bin/bash"); // Или другой shell
}


    void Console::keyPressEvent(QKeyEvent *event){
        if (event->key() == Qt::Key_Backspace) {
            // TODO: Обработка Backspace
            //  input->backspace(); //Просто удаляет символ из line edit. Не из эмулируемого терминала
        } else if (event->key() == Qt::Key_Up) {
            // TODO: История команд
        } else {
            // qDebug() << "Key pressed: " << event->text(); // Проверка что клавиша нажимается.
            // отправляем команду в процесс.  Нужно решить отправлять сразу или накапливать
            // в lineedit и потом по enter отправлять.
        }
    }


    void Console::readOutput() {
        QByteArray data = process->readAllStandardOutput();
        output->appendPlainText(data);
        // TODO: Парсинг ANSI escape sequences
    }

    void Console::readError() {
        QByteArray data = process->readAllStandardError();
        output->appendPlainText(data);
    }

    void Console::sendCommand() {
        QString command = input->text();
        process->write((command + "\n").toUtf8());
        input->clear();
    }

    void Console::processStarted() {
        output->appendPlainText("Process started.");
    }

    void Console::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
        output->appendPlainText(QString("Process finished with code %1 and status %2.").arg(exitCode).arg(exitStatus));
    }

    void Console::processError(QProcess::ProcessError error) {
        output->appendPlainText(QString("Process error: %1").arg(error));
    }

    Console::~Console() {
        if (process) {
            process->terminate();
            process->waitForFinished();
            delete process;
        }
    }



//#include "main.moc" // Include the moc file
