#include "console.h"


Console::Console(QWidget * parent , QString  name) : QWidget(parent) {
    output = new QPlainTextEdit(this);
    input = new QLineEdit(this);
    output->setReadOnly(true);
    output->setFont(QFont("Monospace", 10));

    progname = name;

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
    process->start("/bin/bash");

    process->write(("cd " + QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" +  name + "\n").toUtf8());


    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" +  name + "/.q_conf/conf.gson");



    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        const size_t linenum = 1;

        for (size_t i = 0; i < linenum - 1; i++)
            file.readLine();
        QByteArray rawline = file.readLine();
        file.close();
        proglang = QString::fromUtf8(rawline);
    }

}



    void Console::keyPressEvent(QKeyEvent *event){
        if (event->key() == Qt::Key_Backspace) {

        } else if (event->key() == Qt::Key_Up) {

        } else {

        }
    }


    void Console::readOutput() {
        QByteArray data = process->readAllStandardOutput();
        output->appendPlainText(data);

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
    void Console::Run() {

        QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" +  progname + "/.q_conf/conf.gson");


        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            const size_t linenum = 1;

            for (size_t i = 0; i < linenum - 1; i++)
                file.readLine();
            QByteArray rawline = file.readLine();
            file.close();
            proglang = QString::fromUtf8(rawline);
        }

        if(proglang.contains("PYTHON")){
            process->write(("python3 main.py\n"));
        }
        else if (proglang.contains("CPP")) {

            if(!QDir("build").exists()){
                process->write("mkdir build\n");
                process->write("cd build\n");
            }else{
                process->write("cd build\n");
            }
            process->write("cmake ..\n");
            process->write("make\n");
            process->write(("./" + progname +"\n").toUtf8());
            process->write("cd ..\n");
            //process->write( ("./" + QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/" +  progname + "/build/MyAppp").toUtf8());
        }

    }
