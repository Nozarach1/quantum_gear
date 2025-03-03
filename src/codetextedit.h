#ifndef CODETEXTEDIT_H
#define CODETEXTEDIT_H

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>

class CodeTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeTextEdit(QWidget *parent = nullptr);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea;
};

#endif // CODETEXTEDIT_H
