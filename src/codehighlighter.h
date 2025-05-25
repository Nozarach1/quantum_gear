#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class CodeHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    CodeHighlighter(QTextDocument *parent = nullptr);
    void setLanguage(const QString &lang);  // "python" или "cpp"

protected:
    void highlightBlock(const QString &text) override;

private:
    void initializePythonRules();
    void initializeCppRules();

    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;
    QString currentLanguage;
};
#endif // HIGHLIGHTER_H
