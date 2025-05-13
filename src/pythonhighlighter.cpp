#include "pythonhighlighter.h"

// Конструктор
PythonHighlighter::PythonHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    initializeHighlightingRules();
}


void PythonHighlighter::initializeHighlightingRules()
{

    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);


    QStringList keywords;
    keywords << "def" << "class" << "return" << "w" << "else" << "while" << "for" << "import";


    for (const QString &keyword : keywords) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\\b" + keyword + "\\b");
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }


    QTextCharFormat printFormat;
    printFormat.setForeground(Qt::darkYellow);

    QStringList keywordsprint;
    keywordsprint <<  "print";


    for (const QString &keyword : keywordsprint) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\\b" + keyword + "\\b");
        rule.format = printFormat;
        highlightingRules.append(rule);
    }


    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::darkGreen);
    commentFormat.setFontItalic(true);


    HighlightingRule commentRule;
    commentRule.pattern = QRegularExpression("#[^\n]*");
    commentRule.format = commentFormat;
    highlightingRules.append(commentRule);


    QTextCharFormat stringFormat;
    stringFormat.setForeground(Qt::darkRed);


    HighlightingRule stringRule;
    stringRule.pattern = QRegularExpression("\".*\"");
    stringRule.format = stringFormat;
    highlightingRules.append(stringRule);


    // QTextCharFormat defaultFormat;
    // defaultFormat.setForeground(Qt::black);

    // HighlightingRule defaultRule;
    // defaultRule.pattern = QRegularExpression("[^\\s]");
    // defaultRule.format = defaultFormat;
    // highlightingRules.append(defaultRule);

}


void PythonHighlighter::highlightBlock(const QString &text)
{

    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
