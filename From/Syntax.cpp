#include "../Header/Syntax.h"

Syntax::Syntax(QTextDocument *d): QSyntaxHighlighter(d) {

}

void Syntax::highlightBlock(const QString &text) {
    QFile propertyValLightFile("./Resource/syntax/propertyVal.txt");
    QString propertyValLight;
    if(propertyValLightFile.open(QIODevice::ReadOnly))
    {
        propertyValLight=propertyValLightFile.readAll();
    }
    //属性的值
    QFile propertyLightFile("./Resource/syntax/property.txt");
    QString propertyLight;
    if(propertyLightFile.open(QIODevice::ReadOnly))
    {
        propertyLight=propertyLightFile.readAll();
    }
    //属性
    QFile classNameLightFile("./Resource/syntax/className.txt");
    QString classNameLight;
    if(classNameLightFile.open(QIODevice::ReadOnly))
    {
        classNameLight=classNameLightFile.readAll();
    }
    //关键字之类的
    //一些配置的读取


    //一些内置函数 such as rgb,hsv....
    QFile functionNameFile("./Resource/syntax/functionName.txt");
    QString functionName;
    if(functionNameFile.open(QIODevice::ReadOnly))
    {
        functionName=functionNameFile.readAll();
    }


    QTextCharFormat format;
    QRegularExpression reg;
    QRegularExpressionMatchIterator iter;
    //采用全局的正则和格式化  减少不必要的浪费

    //一些值的高亮  类似px啊 #000这些
    format.setForeground(Qt::white);
    reg.setPattern("(:|("+propertyValLight+")|\\(|,)*\\s*(#*([0-9]*[A-Fa-f]*))");
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart()+1,match.capturedLength(),
                  format);
    }
    format.setForeground(Qt::white);
    reg.setPattern(propertyValLight);
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart()+1,match.capturedLength(),
                  format);
    }
    //属性值

    format.setForeground(QColor(0, 207, 189));
    reg.setPattern(classNameLight);
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart(),match.capturedLength(),
                  format);
    }
    //类名高亮

    format.setForeground(QColor(212, 156, 155));
    reg.setPattern("[{}\\(\\)]");
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart(),match.capturedLength(),
                  format);
    }
    //括号高亮

    format.setForeground(QColor(238,58,140));
    reg.setPattern(propertyLight);
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart(),match.capturedLength(),
                  format);
    }
    //属性


    //函数名
    format.setForeground(QColor(0,253,255));
    reg.setPattern(functionName);
    iter=reg.globalMatch(text);
    while(iter.hasNext()) {
        QRegularExpressionMatch match = iter.next();
        setFormat(match.capturedStart(), match.capturedLength(),
                  format);
    }

    //选择器
    format.setForeground(QColor(229,192,123)
    );
    reg.setPattern("#\\S*(\\s*\\S*)*{");
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart(),match.capturedLength()-1,
                  format);
    }

    //括号内的值
    format.setForeground(QColor(187,187,187)
    );
    reg.setPattern("\\(\\S*(\\s*\\S*)*\\)");
    iter=reg.globalMatch(text);
    while(iter.hasNext())
    {
        QRegularExpressionMatch match=iter.next();
        setFormat(match.capturedStart()+1,match.capturedLength()-2,
                  format);
    }
}