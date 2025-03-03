#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include <QSize>
#include <QPaintEvent>

class CodeTextEdit;  // Forward declaration (объявление класса, который будет определен позже)

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeTextEdit *editor);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    CodeTextEdit *codeEditor;
};

#endif // LINENUMBERAREA_H
