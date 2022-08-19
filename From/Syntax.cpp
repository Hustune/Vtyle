#include "../Header/Syntax.h"

Syntax::Syntax(QTextDocument *d): QSyntaxHighlighter(d) {
    colorConfig=new QSettings("./Data/user.ini",QSettings::IniFormat);
}

void Syntax::highlightBlock(const QString &text) {
    QRegExp isLetter("[A-Za-z]");
    QRegExp isSpace("[:\n\\s;\\{\\}]");
    bool isId=false,isClass=false;
    bool haveSign=false;
    bool haveString=false;
    int begin=0;
    QString temp="";
    QTextCharFormat format;

    format.setForeground(Qt::darkRed);
    //分解成Token
    for(int i=0;i<text.length();i++)
    {
        if(haveString)
        {
            temp.append(text[i]);
        }
        else if(text[i]>='a'&&text[i]<='z'||text[i]>='A'&&text[i]<='Z'){
            begin=i;
            temp.append(text[i]);
            haveString=true;
        }
        else if(text[i]==":"||text[i]==";"||text[i]=="{"||
        text[i]=="}"||text[i]=="\n"||text[i]==" ")
        {
            tokens.push(Token(temp,begin));
            temp.clear();
            begin=0;
            haveString=false;
            tokens.push(Token(text[i],i));
        }
        else{
            setFormat(i,1,format);
            haveString=false;
        }
    }

    qDebug()<<"------------------------------------------------------------------";
    while(!tokens.isEmpty())
    {
        qDebug()<<tokens.pop();
    }


//    QFile propertyValLightFile("./Resource/syntax/propertyVal.txt");
//    QString propertyValLight;
//    if(propertyValLightFile.open(QIODevice::ReadOnly))
//    {
//        propertyValLight=propertyValLightFile.readAll();
//    }
//    //属性的值
//    QFile propertyLightFile("./Resource/syntax/property.txt");
//    QString propertyLight;
//    if(propertyLightFile.open(QIODevice::ReadOnly))
//    {
//        propertyLight=propertyLightFile.readAll();
//    }
//    //属性
//    QFile classNameLightFile("./Resource/syntax/className.txt");
//    QString classNameLight;
//    if(classNameLightFile.open(QIODevice::ReadOnly))
//    {
//        classNameLight=classNameLightFile.readAll();
//    }
//    //关键字之类的
//    //一些配置的读取
//
//
//    //一些内置函数 such as rgb,hsv....
//    QFile functionNameFile("./Resource/syntax/functionName.txt");
//    QString functionName;
//    if(functionNameFile.open(QIODevice::ReadOnly))
//    {
//        functionName=functionNameFile.readAll();
//    }
//
//
//    QTextCharFormat format;
//    QRegularExpression reg;
//    QRegularExpressionMatchIterator iter;
//    //采用全局的正则和格式化  减少不必要的浪费
//
//    //一些值的高亮  类似px啊 #000这些
//    format.setForeground(QColor(colorConfig->value("Syntax/value").toString()));
//    reg.setPattern("(:|("+propertyValLight+")|\\(|,)*\\s*(#*([0-9]*[A-Fa-f]*))");
//    iter=reg.globalMatch(text);
//    while(iter.hasNext())
//    {
//        QRegularExpressionMatch match=iter.next();
//        setFormat(match.capturedStart()+1,match.capturedLength(),
//                  format);
//    }
//    format.setForeground(QColor(colorConfig->value("Syntax/value").toString()));
//    reg.setPattern(propertyValLight);
//    iter=reg.globalMatch(text);
//    while(iter.hasNext())
//    {
//        QRegularExpressionMatch match=iter.next();
//        setFormat(match.capturedStart()+1,match.capturedLength(),
//                  format);
//    }
//    //属性值
//
//
//    format.setForeground(QColor(colorConfig->value("Syntax/class").toString()));
//    reg.setPattern(classNameLight);
//    iter=reg.globalMatch(text);
//    while(iter.hasNext())
//    {
//        QRegularExpressionMatch match=iter.next();
//        setFormat(match.capturedStart(),match.capturedLength(),
//                  format);
//    }
//    //类名高亮
//
//
//    format.setForeground(QColor(colorConfig->value("Syntax/bracket").toString()));
//    reg.setPattern("[{}\\(\\)]");
//    iter=reg.globalMatch(text);
//    while(iter.hasNext())
//    {
//        QRegularExpressionMatch match=iter.next();
//        setFormat(match.capturedStart(),match.capturedLength(),
//                  format);
//    }
//    //括号高亮
//
//    format.setForeground(QColor(colorConfig->value("Syntax/property").toString()));
//    reg.setPattern(propertyLight);
//    iter=reg.globalMatch(text);
//    while(iter.hasNext())
//    {
//        QRegularExpressionMatch match=iter.next();
//        setFormat(match.capturedStart(),match.capturedLength(),
//                  format);
//    }
//    //属性
//
//
//    //函数名
//    format.setForeground(QColor(colorConfig->value("Syntax/function").toString()));
//    reg.setPattern(functionName);
//    iter=reg.globalMatch(text);
//    while(iter.hasNext()) {
//        QRegularExpressionMatch match = iter.next();
//        setFormat(match.capturedStart(), match.capturedLength(),
//                  format);
//    }
//
//    //选择器
//    format.setForeground(QColor(colorConfig->value("Syntax/selector").toString()));
//    reg.setPattern("#\\S*(\\s*\\S*)*{");
//    iter=reg.globalMatch(text);
//    while(iter.hasNext())
//    {
//        QRegularExpressionMatch match=iter.next();
//        setFormat(match.capturedStart(),match.capturedLength()-1,
//                  format);
//    }
//
//    //括号内的值
//    format.setForeground(QColor(colorConfig->value("Syntax/bracketVal").toString())
//    );
//    reg.setPattern("\\(\\S*(\\s*\\S*)*\\)");
//    iter=reg.globalMatch(text);
//    while(iter.hasNext())
//    {
//        QRegularExpressionMatch match=iter.next();
//        setFormat(match.capturedStart()+1,match.capturedLength()-2,
//                  format);
//    }
}