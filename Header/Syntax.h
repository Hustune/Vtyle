///:此类用于代码的高亮操作

#ifndef QSSEDITOR_SYNTAX_H
#define QSSEDITOR_SYNTAX_H
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>
#include <QTextDocument>
#include <QFile>
#include <QSettings>
#include <QPair>
#include <QStack>
#include "qdebug.h"

typedef QPair<QString,int> Token;

class Syntax:public QSyntaxHighlighter{
    Q_OBJECT
public:
    Syntax(QTextDocument* d);

protected:
    void highlightBlock(const QString &text) override;

private:
    QSettings* colorConfig;
    QStack<Token> tokens;
};

#endif //QSSEDITOR_SYNTAX_H
