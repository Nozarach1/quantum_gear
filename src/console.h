#ifndef CONSOLE_H
#define CONSOLE_H

#include <QApplication>
#include <QPlainTextEdit>
#include <QProcess>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QStandardPaths>
#include <QFile>

class Console : public QWidget {
    Q_OBJECT

public:
    Console(QWidget *parent = nullptr , QString  name = nullptr);
    ~Console();
    void Run();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void readOutput();

    void readError();

    void sendCommand();

    void processStarted();

    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void processError(QProcess::ProcessError error);

private:
    QPlainTextEdit *output;
    QLineEdit *input;
    QProcess *process;
};


#endif // CONSOLE_H
