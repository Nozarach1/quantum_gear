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
    keywords << "def" << "class" << "return" << "if" << "else" << "while" << "for" << "import";

    // Добавляем правила для ключевых слов
    for (const QString     void file_open(QTabWidget *tab_widget , QString file_name) {
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

        tab_widget->addTab(newTab, QFileInfo(file_name).fileName());

        file.close();
    }
};&keyword : keywords) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\\b" + keyword + "\\b");
        rule.format = keywordFormat;
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
