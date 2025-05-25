#include "codehighlighter.h"

CodeHighlighter::CodeHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent), currentLanguage("python")
{
    initializePythonRules();
}

void CodeHighlighter::setLanguage(const QString &lang)
{
    if (lang == currentLanguage) return;

    currentLanguage = lang;
    highlightingRules.clear();

    if (lang == "PYTHON") {
        initializePythonRules();
    } else if (lang == "CPP") {
        initializeCppRules();
    }

    rehighlight();
}

void CodeHighlighter::initializePythonRules()
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

void CodeHighlighter::initializeCppRules()
{
    // 1. Ключевые слова C++
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList cppKeywords = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
        "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
        "class", "compl", "concept", "const", "consteval", "constexpr", "const_cast",
        "continue", "co_await", "co_return", "co_yield", "decltype", "default", "delete",
        "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
        "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
        "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator",
        "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast",
        "requires", "return", "short", "signed", "sizeof", "static", "static_assert",
        "static_cast", "struct", "switch", "template", "this", "thread_local", "throw",
        "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
        "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
    };

    for (const QString &keyword : cppKeywords) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\\b" + keyword + "\\b");
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // 2. Препроцессорные директивы
    QTextCharFormat preprocessorFormat;
    preprocessorFormat.setForeground(Qt::darkMagenta);

    HighlightingRule preprocessorRule;
    preprocessorRule.pattern = QRegularExpression("^\\s*#\\s*\\w+");
    preprocessorRule.format = preprocessorFormat;
    highlightingRules.append(preprocessorRule);

    // 3. Типы данных (дополнительно)
    QTextCharFormat typeFormat;
    typeFormat.setForeground(Qt::darkCyan);
    typeFormat.setFontWeight(QFont::Bold);

    QStringList cppTypes = {
        "int", "float", "double", "char", "void", "bool", "short", "long",
        "signed", "unsigned", "size_t", "ssize_t", "int8_t", "int16_t",
        "int32_t", "int64_t", "uint8_t", "uint16_t", "uint32_t", "uint64_t"
    };

    for (const QString &type : cppTypes) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression("\\b" + type + "\\b");
        rule.format = typeFormat;
        highlightingRules.append(rule);
    }

    // 4. Строки
    QTextCharFormat stringFormat;
    stringFormat.setForeground(Qt::darkRed);

    HighlightingRule stringRule;
    stringRule.pattern = QRegularExpression(R"("(?:\\.|[^"\\])*")");
    stringRule.format = stringFormat;
    highlightingRules.append(stringRule);

    // 5. Символьные литералы
    HighlightingRule charRule;
    charRule.pattern = QRegularExpression(R"('(?:\\.|[^'\\])')");
    charRule.format = stringFormat;
    highlightingRules.append(charRule);

    // 6. Комментарии (однострочные)
    QTextCharFormat singleLineCommentFormat;
    singleLineCommentFormat.setForeground(Qt::darkGreen);
    singleLineCommentFormat.setFontItalic(true);

    HighlightingRule singleLineCommentRule;
    singleLineCommentRule.pattern = QRegularExpression("//[^\n]*");
    singleLineCommentRule.format = singleLineCommentFormat;
    highlightingRules.append(singleLineCommentRule);

    // 7. Многострочные комментарии (особая обработка)
    QTextCharFormat multiLineCommentFormat;
    multiLineCommentFormat.setForeground(Qt::darkGreen);
    multiLineCommentFormat.setFontItalic(true);

    HighlightingRule multiLineCommentStartRule;
    multiLineCommentStartRule.pattern = QRegularExpression("/\\*");
    multiLineCommentStartRule.format = multiLineCommentFormat;
    highlightingRules.append(multiLineCommentStartRule);

    HighlightingRule multiLineCommentEndRule;
    multiLineCommentEndRule.pattern = QRegularExpression("\\*/");
    multiLineCommentEndRule.format = multiLineCommentFormat;
    highlightingRules.append(multiLineCommentEndRule);

    // 8. Числовые литералы
    QTextCharFormat numberFormat;
    numberFormat.setForeground(Qt::blue);

    HighlightingRule numberRule;
    numberRule.pattern = QRegularExpression("\\b\\d+(\\.\\d+)?([eE][+-]?\\d+)?[fFlL]?\\b");
    numberRule.format = numberFormat;
    highlightingRules.append(numberRule);
}

void CodeHighlighter::highlightBlock(const QString &text)
{
    // Обработка многострочных комментариев (особый случай)
    setCurrentBlockState(previousBlockState());

    int startIndex = 0;
    if (previousBlockState() != 1) {
        startIndex = text.indexOf(QRegularExpression("/\\*"));
    }

    while (startIndex >= 0) {
        QRegularExpressionMatch endMatch;
        int endIndex = text.indexOf(QRegularExpression("\\*/"), startIndex, &endMatch);
        int commentLength;

        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + endMatch.capturedLength();
        }

        QTextCharFormat multiLineCommentFormat;
        multiLineCommentFormat.setForeground(Qt::darkGreen);
        multiLineCommentFormat.setFontItalic(true);

        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(QRegularExpression("/\\*"), startIndex + commentLength);
    }

    // Обработка всех остальных правил
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
