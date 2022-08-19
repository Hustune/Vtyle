#include "../Header/EditWidget.h"
#include "qdebug.h"

EditWidget::EditWidget(QSettings* config,QWidget *p): QWidget(p) {
    isSave=true;
    conf=config;
    colorConfig=new QSettings("./Data/user.ini",QSettings::IniFormat);
    layout=new QHBoxLayout();

    savePath=="";
    setObjectName("TextEdit");


    QFile qss("./Resource/Theme.qss");
    QString qssStyle;
    if(qss.open(QIODevice::ReadOnly))
    {
        qssStyle=qss.readAll();
    }
    setStyleSheet(qssStyle);
    //样式表

        //文本编辑
        editSpace=new EditSpace(config);
        editSpace->setLineWrapMode(QTextEdit::NoWrap);
        connect(editSpace,&EditSpace::textChanged,this,[&]{isSave=false;});
        //行号显示
        numberShow=new NumberShow(editSpace);
        numberShow->setAlignment(Qt::AlignTop);
        //数字从顶开始显示
        numberShow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff) ;
        numberShow->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff ) ;
        //隐藏横向和纵向的滚动条
        numberShow->setReadOnly(true);
        //不可更改

        editSpace->setVerticalScrollBar(numberShow
        ->verticalScrollBar());//将editSpace和numberShow的滚动条滚动同步
        //因为用的是numbershow的滚动条 所以样式要在numbershow里设置

        layout->addWidget(numberShow,1);
        layout->addStretch();

        connect(editSpace,&QTextEdit::textChanged
                ,numberShow, &NumberShow::updateNumber);
        //当内容发生变化时 更新行号的显示
        layout->addWidget(editSpace,13);
    setLayout(layout);

    connect(getTextSpace(),&QTextEdit::cursorPositionChanged,
            this,&EditWidget::highlighter);
    //当光标移动时 更新高亮的行
    highlighter();
    //初始化时就更新高亮
    syntax=new Syntax(editSpace->document());
    //将代码编辑区域的document传给高亮类
}

QTextEdit* EditWidget::getTextSpace() {
    return editSpace;//返回editSpace
}

void EditWidget::highlighter(){
    //高亮操作
    QTextEdit *edit = getTextSpace();
    QList<QTextEdit::ExtraSelection> extraSelection;
    QTextEdit::ExtraSelection selection;
    QColor lineColor = QColor(colorConfig->value("Color/lineLight").toString()).lighter(70);
    //高亮操作
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection,true);
    selection.cursor = edit->textCursor();
    selection.cursor.clearSelection();
    extraSelection.append(selection);
    edit->setExtraSelections(extraSelection);

    //这一段具体可以查下API看看 这部分我也是cv CSDN上大佬的demo的
}

void EditWidget::save() {
    //保存
    if(savePath=="")
    {//如果为空 代表是新建还没保存过的窗口
        savePath=QFileDialog::getSaveFileName
                (this,conf->value("lan/saveDiaTitle").toString(),".",".qss");
        //获取要保存的路径
    }
    if(savePath==NULL){
        return;
    }
    if(savePath.right(savePath.length()
                      -savePath.lastIndexOf(".")-1)=="qss")
    {

    }
    else
    {
        //如果文件名有后缀那就不添加后缀名  没有的话就加上
        savePath+=".qss";
    }
    QFile f(savePath);

    if(f.open(QIODevice::WriteOnly))
    {
        f.write(editSpace->toPlainText().toUtf8());
    }
    f.close();
    //将所有信息写入文件
    isSave= true;
}

void EditWidget::keyPressEvent(QKeyEvent *event) {
    //键盘监控 这部分不难 实在看不懂去群里问我吧 群号:822540929
    if(event->key()==Qt::Key_Control)
    {
        isCtrl=true;
    }
    if(event->key()==Qt::Key_S)
    {
        isS=true;
    }

    QWidget::keyPressEvent(event);
}

void EditWidget::keyReleaseEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_Control)
    {
        isCtrl=false;
    }
    if(event->key()==Qt::Key_S)
    {
        if(isS&&isCtrl)
        {
            save();
        }
        isS=false;
    }

    QWidget::keyReleaseEvent(event);
}

void EditWidget::rename(QString s) {
    //重命名函数
    QFile f(savePath);
    //创建一个文件对象
    QString path;
    if(s.right(s.length()
                      -s.lastIndexOf(".")-1)=="qss")
    {
        path=savePath.left(savePath.length()-savePath.lastIndexOf("/")+1)+s;
    }
    else
    {
        path=savePath.left(savePath.length()-savePath.lastIndexOf("/")+1)+s+".qss";
    }
    //文件名处理

    f.rename(path);
    //调用文件对象的rename
    savePath=path;
    //更新path
}
bool EditWidget::closeed() {
    if(isSave)
    {
        close();
        return true;
    }
    else{
        auto button=QMessageBox::question(this,conf->value("lan/isSaveDoc").toString(),conf->value("lan/isSaveDoc").toString()
        ,QMessageBox::Save|QMessageBox::No|QMessageBox::Cancel);
        if(button==QMessageBox::Save)
        {
            save();
            return true;
        }
        else if(button==QMessageBox::No){
            close();
            return true;
        }
        else{
            return false;
        }
    }
}


NumberShow::NumberShow(QTextEdit* text): QTextEdit("1") {
    this->text=text;
    setObjectName("TextEdit");
    setMinimumWidth(70);
    verticalScrollBar()->setObjectName("ScrollBar");
}

void NumberShow::updateNumber() {
    //行号更新
    //原理介绍 本质上就是把editSpace和numberShow的行数保持同步
    //editSpace有几行 numberShow就添加对应的数字
    int enterVal=1;//默认有一行
    QString numberStr=text->toPlainText();

    for(int i=0;i<numberStr.length();i++)
    {
        if(numberStr[i]=='\n')
        {
            enterVal+=1;
        }
    }//遍历editSpace的文字 如果有换行符就将enterVal加1

    numberStr="";
    for(int i=1;i<=enterVal;i++)
    {
        numberStr+=QString::number(i)+='\n';
    }//添加enterVal次的数字
    //然后设置numberShow的文字
    setText(numberStr);
}




EditSpace::EditSpace(QSettings* config): QTextEdit() {
    horizontalScrollBar()->setObjectName("ScrollBar");

    QStringList completeWord;
    setObjectName("TextEdit");
    QFile completeFile("./Resource/complete/complete.txt");
    //读取补全信息文件
    if(completeFile.open(QIODevice::ReadOnly))
    {
        QString tempStr=completeFile.readLine().simplified();
        completeWord<<tempStr;
        while(tempStr!=NULL)
        {
            tempStr=completeFile.readLine().simplified();
            completeWord<<tempStr;
        }
    }

    QString qssStyle;
    QFile cQss("./Resource/Theme.qss");
    if(cQss.open(QIODevice::ReadOnly))
    {
        qssStyle=cQss.readAll();
    }
    verticalScrollBar()->setStyleSheet(qssStyle);

   completer = new QCompleter(completeWord,this);
    QStyledItemDelegate* d = new QStyledItemDelegate;//必须 否则部分style不生效
    completer->popup()->setItemDelegate(d);//必须

    completer->popup()->setObjectName("completer");
    completer->popup()->verticalScrollBar()->setObjectName("ScrollBar");
    completer->popup()->verticalScrollBar()->setStyleSheet(qssStyle);
    completer->popup()->setStyleSheet(qssStyle);

   completer->setWidget(this);

   completer->setCompletionMode(QCompleter::PopupCompletion);
   //显示模式
   completer->setCaseSensitivity(Qt::CaseInsensitive);
   //检索模式
    connect(completer,QOverload<const QString &>::of(&QCompleter::activated),
            this,&EditSpace::completeWord);



    //右键菜单
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &EditSpace::customContextMenuRequested,
            this, &EditSpace::showMenu);


    undoAction=new QAction(config->value("lan/undoAction").toString());
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction,&QAction::triggered,
            this,&EditSpace::undo);

    redoAction=new QAction(config->value("lan/redoAction").toString());
    redoAction->setShortcut(QKeySequence::Redo);
    connect(redoAction,&QAction::triggered,
            this,&EditSpace::redo);

    copyAction=new QAction(config->value("lan/copyAction").toString());
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction,&QAction::triggered,
            this,&EditSpace::copy);

    pasteAction=new QAction(config->value("lan/pasteAction").toString());
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction,&QAction::triggered,
            this,&EditSpace::paste);

    cutAction=new QAction(config->value("lan/cutAction").toString());
    cutAction->setShortcut(QKeySequence::Cut);
    connect(cutAction,&QAction::triggered,
            this,&EditSpace::cut);


    selectAllAction=new QAction(config->value("lan/selectAllAction").toString());
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    connect(selectAllAction,&QAction::triggered,
            this,&EditSpace::selectAll);

    menu=new QMenu();
    menu->setObjectName("windowMenu");
    menu->addAction(undoAction);
    menu->addAction(redoAction);
    menu->addAction(copyAction);
    menu->addAction(cutAction);
    menu->addAction(pasteAction);
    menu->addAction(selectAllAction);

    //各种new
    menu->setStyleSheet(qssStyle);
}

void EditSpace::keyPressEvent(QKeyEvent *e) {
    QTextCursor cursor=textCursor();
    switch (e->key()) {
        case Qt::Key_BraceLeft:
            cursor.insertText("{\n    \n}");
            moveCursor(QTextCursor::Up);
            moveCursor(QTextCursor::Right);
            moveCursor(QTextCursor::Right);
            moveCursor(QTextCursor::Right);
            moveCursor(QTextCursor::Right);
            completer->popup()->setVisible(false);
            return;
        case Qt::Key_ParenLeft:
            cursor.insertText("()");
            moveCursor(QTextCursor::Left);
            completer->popup()->setVisible(false);
            return;
    }
    if (completer) {
        if (completer->popup()->isVisible()) {
            //如果提示窗口激活了 那么将把以下几个事件忽略掉
            switch (e->key()) {
                case Qt::Key_Escape:
                case Qt::Key_Enter:
                case Qt::Key_Return:
                case Qt::Key_Tab:
                    e->ignore();
                    return;
                default:
                    break;
            }
        }
        //如果没有
        QTextEdit::keyPressEvent(e);
        completer->setCompletionPrefix(getCursorWord());
        // 通过设置QCompleter的前缀，来让Completer寻找关键词
        QRect cr = cursorRect();
        cr.setWidth((completer->popup()->sizeHintForColumn(0)
                    + completer->popup()->verticalScrollBar()->sizeHint().width())*2);
        completer->popup()->setVisible(true);
        completer->complete(cr);
        //QRect表示位置
    }
}

void EditSpace::completeWord(const QString &completion) {
    //补全字符
    //这一段cv的 自己理解一下算法
        QString completionPrefix = getCursorWord(),
                shouldInertText = completion;
        QTextCursor cursor = this->textCursor();
        if (!completion.contains(completionPrefix)) {// delete the previously typed.
            cursor.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,
                                completionPrefix.size());
            cursor.clearSelection();
        } else {
            // 补全相应的字符
            shouldInertText = shouldInertText.replace(
                    shouldInertText.indexOf(completionPrefix), completionPrefix.size(), "");
        }
        cursor.insertText(shouldInertText);
}

QString EditSpace::getCursorWord() {
    QTextDocument* doc=document();//获取自身的document
    QTextCursor cursor=textCursor();//获取光标

    int row,column;//光标所在的行和列
    row=cursor.blockNumber();
    column=cursor.columnNumber();

    QString rowText=doc->findBlockByLineNumber(row).text();
    rowText=rowText.left(column);
    rowText=rowText.
            right(rowText.length()-1-rowText.lastIndexOf(QRegExp("(\\s)|(:)")));
    return rowText;
}

void EditSpace::showMenu() {

    //移到适合的位置并显示
    menu->move (cursor().pos());
    menu->show();
}