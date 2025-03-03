#include "pythonhighlighter.h"

// Конструктор
PythonHighlighter::PythonHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    initializeHighlightingRules();  // Инициализация правил подсветки
}

// Метод для инициализации правил подсветки
void PythonHighlighter::initializeHighlightingRules()
{
    // Формат для ключевых слов
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    // Список ключевых слов
    QStringList keywords;
    keywords << "def" << "class" << "return" << "w" << "else" << "while" << "for" << "import";

    // Добавляем правила для ключевых слов
    for (const QString &keyword : keywords) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\\b" + keyword + "\\b");
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }


    QTextCharFormat printFormat;
    printFormat.setForeground(Qt::darkYellow); // Устанавливаем цвет (оранжевый)

    QStringList keywordsprint;
    keywordsprint <<  "print"; // Используем keywordsprint, а не keywords

    // Добавляем правила для ключевых слов
    for (const QString &keyword : keywordsprint) { // Используем keyword, а не keywords
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\\b" + keyword + "\\b");
        rule.format = printFormat;
        highlightingRules.append(rule);
    }

    // Формат для однострочных комментариев
    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::darkGreen);
    commentFormat.setFontItalic(true);

    // Правило для однострочных комментариев
    HighlightingRule commentRule;
    commentRule.pattern = QRegularExpression("#[^\n]*");
    commentRule.format = commentFormat;
    highlightingRules.append(commentRule);

    // Формат для строк
    QTextCharFormat stringFormat;
    stringFormat.setForeground(Qt::darkRed);

    // Правило для строк в кавычках
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

// Переопределенный метод для подсветки текста
void PythonHighlighter::highlightBlock(const QString &text)
{
    // Применяем правила подсветки
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
