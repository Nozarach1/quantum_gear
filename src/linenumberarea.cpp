#include "linenumberarea.h"
#include "codetextedit.h"
#include <QPainter>

LineNumberArea::LineNumberArea(CodeTextEdit *editor) : QWidget(editor), codeEditor(editor)
{}

QSize LineNumberArea::sizeHint() const
{
    return QSize(codeEditor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event)
{
    codeEditor->lineNumberAreaPaintEvent(event);
}
