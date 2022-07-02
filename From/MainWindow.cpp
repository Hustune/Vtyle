#include "../Header/MainWindow.h"

MainWindow::MainWindow(QSettings* tr,QWidget* p): QMainWindow(p)
{
    config=tr;
    //加载qss样式文件 并将值赋给QString qssStyle
    QFile qss("./Resource/Theme.qss");
    QString qssStyle;
    if(qss.open(QIODevice::ReadOnly))
    {
        qssStyle=qss.readAll();
    }

    setStyleSheet(qssStyle);//设置样式

    mainMenuBar=menuBar();//获得窗口菜单栏的指针
    mainMenuBar->setObjectName("mainMenuBar");
    //设置对象名 防止样式覆盖
    mainMenuBar->setStyleSheet(qssStyle);
    //文件菜单
        fileMenu=new QMenu(tr->value("lan/fileMenu").toString());
        fileMenu->setObjectName("windowMenu");
        fileMenu->setStyleSheet(qssStyle);//样式设置
        //
            openAction=new QAction(
                    QIcon("./Resource/open.png")
                    ,tr->value("lan/openAction").toString());
            fileMenu->addAction(openAction);
            openAction->setShortcut(QKeySequence::Open);
            connect(openAction,&QAction::triggered
            ,this,&MainWindow::open);

        //
            newAction=new QAction(QIcon("./Resource/new.png"),tr->value("lan/newAction").toString());
            newAction->setShortcut(QKeySequence::New);
            connect(newAction,&QAction::triggered
            ,this,&MainWindow::newFile);
            fileMenu->addAction(newAction);
        //
            saveAction=new QAction(QIcon("./Resource/save.png"),tr->value("lan/saveAction").toString());
            saveAction->setShortcut(QKeySequence::Save);
            connect(saveAction,&QAction::triggered,
                    this,&MainWindow::save);
            fileMenu->addAction(saveAction);
        //
            saveAsAction=new QAction(tr->value("lan/saveAsAction").toString());
            saveAsAction->setShortcut(QKeySequence::SaveAs);
            connect(saveAsAction,&QAction::triggered,
                    this,&MainWindow::saveAs);
            fileMenu->addAction(saveAsAction);
        //
            restartAction=new QAction(tr->value("lan/restartAction").toString());
            connect(restartAction,&QAction::triggered,this,&MainWindow::restart);
            fileMenu->addAction(restartAction);
        //

        mainMenuBar->addMenu(fileMenu);//添加
    //编辑
        editMenu=new QMenu(tr->value("lan/editMenu").toString());
        editMenu->setObjectName("windowMenu");
        editMenu->setStyleSheet(qssStyle);
        //
            renameFileAction=new QAction(tr->value("lan/renameFileAction").toString());
            connect(renameFileAction,&QAction::triggered,
                    this,&MainWindow::rename);
            renameFileAction->setShortcut(
                    QKeySequence("ctrl+r"));//快捷键设置
            editMenu->addAction(renameFileAction);
        //
            undoAction=new QAction(QIcon("./Resource/undo.png"),tr->value("lan/undoAction").toString());
            undoAction->setShortcut(QKeySequence::Undo);
            connect(undoAction,&QAction::triggered,
                    this,&MainWindow::undo);

            redoAction=new QAction(QIcon("./Resource/redo.png"),tr->value("lan/redoAction").toString());
            redoAction->setShortcut(QKeySequence::Redo);
            connect(redoAction,&QAction::triggered,
                    this,&MainWindow::redo);

            copyAction=new QAction(tr->value("lan/copyAction").toString());
            copyAction->setShortcut(QKeySequence::Copy);
            connect(copyAction,&QAction::triggered,
                    this,&MainWindow::copy);

            pasteAction=new QAction(tr->value("lan/pasteAction").toString());
            pasteAction->setShortcut(QKeySequence::Paste);
            connect(pasteAction,&QAction::triggered,
                  this,&MainWindow::paste);

            cutAction=new QAction(tr->value("lan/cutAction").toString());
            cutAction->setShortcut(QKeySequence::Cut);
            connect(cutAction,&QAction::triggered,
                 this,&MainWindow::cut);


            selectAllAction=new QAction(tr->value("lan/selectAllAction").toString());
            selectAllAction->setShortcut(QKeySequence::SelectAll);
            connect(selectAllAction,&QAction::triggered,
                  this,&MainWindow::selectAll);
        //
            editMenu->addAction(undoAction);
            editMenu->addAction(redoAction);
            editMenu->addAction(copyAction);
            editMenu->addAction(cutAction);
            editMenu->addAction(pasteAction);
            editMenu->addAction(selectAllAction);
    mainMenuBar->addMenu(editMenu);


    setting=new QAction(tr->value("lan/settingAction").toString());
    connect(setting,&QAction::triggered,this,&MainWindow::settings);
    mainMenuBar->addAction(setting);

    about=new QAction(tr->value("lan/aboutAction").toString());
    connect(about,&QAction::triggered,this,&MainWindow::aboutFunc);
    mainMenuBar->addAction(about);


//主窗口
    centralWidget=new QWidget();
    centralWidget->setObjectName("centralWidget");
    centralWidget->setStyleSheet(qssStyle);
        layout=new QHBoxLayout();
        layout->setMargin(0);
            tab=new TabWidget(config,this);
            tab->setStyleSheet(qssStyle);
            //打开时会加载开始页面
            //开始页面
            QWidget* w=new QWidget;
            QHBoxLayout* wl=new QHBoxLayout;
            QLabel* introduce=new QLabel("Ctrl + n        <"+tr->value("lan/introduceNew").toString()+">\n"
                                         "Ctrl + s        <"+tr->value("lan/introduceSave").toString()+">\n"
                                         "Ctrl + o        <"+tr->value("lan/introduceOpen").toString()+">\n"
                                         "Ctrl + r       <"+tr->value("lan/introduceRename").toString()+">"
                    );
            introduce->setAlignment(Qt::Alignment::enum_type::AlignCenter);
            introduce->setObjectName("introduceLabel");
            introduce->setStyleSheet(qssStyle);
            wl->addWidget(introduce);
            w->setLayout(wl);

            tab->addTab(w,tr->value("lan/startPage").toString());
            //添加分页窗口
            layout->addWidget(tab);
        centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    //控件更改工具栏
    controlMenu=new QToolBar();
    QWidget *spacer1 = new QWidget(this);
    spacer1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    controlMenu->addWidget(spacer1);
    controlMenu->setObjectName("windowToolBar");
//    controlMenu->addAction(openAction);
//    controlMenu->addAction(saveAction);
//    controlMenu->addAction(newAction);

        replaceControl=new QComboBox();
        replaceControl->setObjectName("replaceBox");
        replaceControl->view()->verticalScrollBar()->setObjectName("ScrollBar");
        replaceControl->view()->verticalScrollBar()->setStyleSheet(qssStyle);
        replaceControl->setStyleSheet(qssStyle);

        replaceControl->addItem("QWidget");
        replaceControl->addItem("QMainWindow");
        replaceControl->addItem("QLabel");
        replaceControl->addItem("QLineEdit");
        replaceControl->addItem("QTextEdit");
        replaceControl->addItem("QComboBox");
        replaceControl->addItem("QTabWidget");
        replaceControl->addItem("QToolBox");
        replaceControl->addItem("QButton");
        replaceControl->addItem("QSlider");
        replaceControl->addItem("QSpinBox");
        replaceControl->addItem("QSplitter");
        replaceControl->addItem("QListWidget");
        replaceControl->addItem("QTreeWidget");
        replaceControl->addItem("QColumnView");
        replaceControl->addItem("QGroupBox");
        replaceControl->addItem("QCalendarWidget");
        replaceControl->addItem("QProgressBar");
        replaceControl->addItem("QLCDNumber");

        replaceControl->setView(new QListView());

        void (QComboBox::* currentChanged)(const QString&)=&QComboBox::currentTextChanged;
        connect(replaceControl,currentChanged,
        this,&MainWindow::changeShowWidget);
        //当更改了控件时触发这个函数用于控件的更新
        controlMenu->addWidget(replaceControl);
    controlMenu->addAction(undoAction);
    controlMenu->addAction(redoAction);
    QWidget *spacer2 = new QWidget(this);
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    controlMenu->addWidget(spacer2);
    controlMenu->setMovable(false);//不可移动
    controlMenu->setStyleSheet(qssStyle);
    addToolBar(Qt::ToolBarArea::TopToolBarArea,controlMenu);
    //初始化在上面

    //帮助窗口
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(
            50, 50, 50));
    helpWidget=new QDockWidget();
    helpWidget->setPalette(palette);
    helpWidget->setAutoFillBackground(true);
    helpWidget->setWidget(new HWheel(config));
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,helpWidget);
    helpWidget->setFeatures(QDockWidget::DockWidgetFeatures::
                          enum_type::NoDockWidgetFeatures);
    //预览窗口
    showWidget=new QDockWidget();
    showWidget->setObjectName("dockWidget");
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea,showWidget);
    showWidget->setFeatures(QDockWidget::DockWidgetFeatures::
    enum_type::NoDockWidgetFeatures);//无任何特征
    showWidget->setWindowTitle(config->value("lan/previewWidget").toString()+"QWidget");
    showWidget->setStyleSheet(qssStyle);
    showWidget->setWidget(new QWidget);
}

void MainWindow::restart() {
     qApp->exit(1);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    int c=tab->count();
    for(int i=0;i<c;i++)
    {
        tab->removePage(tab->count()-1);
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::updateShowWidget() {
    if((dynamic_cast<EditWidget*>(tab->currentWidget()))
       == nullptr)
    {
        return;
    }
    //这串代码是精髓所在
    //首先 我们知道 dynamic_cast可以用于不同类型指针间的转换
    //不可转换时就返回nullptr
    //然后分页窗口会有两种窗口被添加
    // EditWidget(继承自QWidget)和搭载了控件的QWidget
    //QWidget无法转换成EditWidget
    //所以在当分页窗口当前的窗口不是可以执行update的类型时就会返回
    EditWidget* e=(EditWidget*)tab->currentWidget();
    //获取当前窗口并转型
    showWidget->widget()->setStyleSheet(e->getTextSpace()
    ->toPlainText());
    //将预览窗口的样式设置为当前编辑器窗口里的文字
}

void MainWindow::settings() {
    SettingWidget widget(config,this);
    widget.exec();
}

void MainWindow::changeShowWidget(const QString &s) {
    //当更换控件时即触发
    if(s=="QMainWindow")
    {
        QMainWindow* mainWindow=new QMainWindow;
        QMenu* tempMenu=mainWindow->menuBar()->addMenu(config->value("lan/fileMenu").toString());
        QMenu* tempMenu2=tempMenu->addMenu(config->value("lan/saveAction").toString());
        tempMenu2->addAction(new QAction(config->value("lan/saveAction").toString()));
        QToolBar* tempToolBar=mainWindow->addToolBar(config->value("lan/fileMenu").toString());
        tempToolBar->addAction(new QAction(config->value("lan/saveAction").toString()));
        showWidget->setWidget(mainWindow);
    }
    else if(s=="QWidget"){
        showWidget->setWidget(new QWidget);
    }
    else if(s=="QLabel")
    {
        QWidget* wid=new QWidget();
        wid->setLayout(new QVBoxLayout);
        wid->layout()->addWidget(new QLabel(config->value("lan/previewWidget").toString()));
        QLabel* pic=new QLabel();
        pic->setPixmap(QPixmap("./Resource/QStyleIcon.ico"));
        wid->layout()->addWidget(pic);
        showWidget->setWidget(wid);
    }
    else if(s=="QLineEdit"){
        showWidget->setWidget(new QLineEdit);
    }
    else if(s=="QTextEdit")
    {
        QTextEdit* edit=new QTextEdit();
        edit->setLineWrapMode(QTextEdit::NoWrap);
        showWidget->setWidget(edit);
    }
    else if(s=="QComboBox"){
        QComboBox* comboBox=new QComboBox;
        comboBox->addItem("1");
        comboBox->addItem("2");
        comboBox->addItem("3");
        showWidget->setWidget(comboBox);
    }
    else if(s=="QTabWidget")
    {
        QTabWidget* tabwidget=new QTabWidget;
        tabwidget->addTab(new QWidget,"1");
        tabwidget->addTab(new QWidget,"2");
        tabwidget->addTab(new QWidget,"3");
        tabwidget->setMovable(true);
        tabwidget->setTabsClosable(true);
        showWidget->setWidget(tabwidget);
    }
    else if(s=="QToolBox"){
        QToolBox* box=new QToolBox();
        box->addItem(new QLabel("QLabel"),config->value("lan/toolBoxLabel").toString());
        box->addItem(new QTextEdit,config->value("lan/toolBoxEditor").toString());
        box->addItem(new QPushButton(config->value("lan/toolBoxButton").toString()),config->value("lan/toolBoxButton").toString());
        showWidget->setWidget(box);
    }
    else if(s=="QButton")
    {
        QWidget* wid=new QWidget;
        wid->setLayout(new QVBoxLayout);
        QPushButton* pushButton=new QPushButton(config->value("lan/toolBoxButton").toString());
        wid->layout()->addWidget(pushButton);

        QToolButton*toolButton=new QToolButton();
        toolButton->setPopupMode(QToolButton::MenuButtonPopup);
        toolButton->setArrowType(Qt::DownArrow);
        toolButton->addAction(new QAction(config->value("lan/copyAction").toString()));
        toolButton->addAction(new QAction(config->value("lan/cutAction").toString()));
        toolButton->addAction(new QAction(config->value("lan/pasteAction").toString()));
        wid->layout()->addWidget(toolButton);

        wid->layout()->addWidget(new QRadioButton(config->value("lan/radioButton").toString()));
        QCheckBox* checkBox=new QCheckBox(config->value("lan/checkBox").toString());
        checkBox->setTristate(true);
        wid->layout()->addWidget(checkBox);

        wid->layout()->addWidget(new QCommandLinkButton(config->value("lan/commandButton").toString()
                               ,config->value("lan/cmdButtonDesc").toString()));


        showWidget->setWidget(wid);

    }
    else if(s=="QSlider")
    {
        QWidget* wid=new QWidget();
        wid->setLayout(new QHBoxLayout);
        QSlider* v=new QSlider();
        v->setOrientation(Qt::Vertical);
        wid->layout()->addWidget(v);
        QSlider* h=new QSlider();
        h->setOrientation(Qt::Horizontal);
        wid->layout()->addWidget(h);
        showWidget->setWidget(wid);
    }
    else if(s=="QSpinBox")
    {
        QWidget* wid=new QWidget();
        wid->setLayout(new QVBoxLayout);
        wid->layout()->addWidget(new QLabel("QSpinBox"));
        wid->layout()->addWidget(new QSpinBox);
        wid->layout()->addWidget(new QLabel("QDoubleSpiBox"));
        wid->layout()->addWidget(new QDoubleSpinBox);
        wid->layout()->addWidget(new QLabel("QDateEdit"));
        wid->layout()->addWidget(new QDateEdit);
        wid->layout()->addWidget(new QLabel("QTimeEdit"));
        wid->layout()->addWidget(new QTimeEdit);
        wid->layout()->addWidget(new QLabel("QDateTimeEdit"));
        wid->layout()->addWidget(new QDateTimeEdit);
        showWidget->setWidget(wid);
    }
    else if(s=="QSplitter")
    {
        QSplitter* sw1=new QSplitter();
        sw1->setOrientation(Qt::Horizontal);
        sw1->addWidget(new QTextEdit);

        QSplitter* sw2=new QSplitter();
        sw2->setOrientation(Qt::Vertical);
        sw2->addWidget(new QLabel("QSplitter"));

        QLCDNumber* num=new QLCDNumber();
        num->display("15:33");
        sw2->addWidget(num);

        sw1->addWidget(sw2);

        showWidget->setWidget(sw1);
    }
    else if(s=="QListWidget")
    {
        QListWidget* lw=new QListWidget();
        lw->addItems(QStringList{"Li","st","Wid","get"});
        showWidget->setWidget(lw);
    }
    else if(s=="QTreeWidget"){
        QTreeWidget* tw=new QTreeWidget();
        tw->setColumnCount(3);
        tw->addTopLevelItem(new QTreeWidgetItem(QStringList{"pare","nt","node"}));
        tw->topLevelItem(0)->addChild(new QTreeWidgetItem(
                QStringList{"child","node","1"}));
        QTreeWidgetItem* item=new QTreeWidgetItem(QStringList{"child","node2"});
        item->setCheckState(1,Qt::Checked);
        tw->topLevelItem(0)->addChild(item);

        showWidget->setWidget(tw);
    }
    else if(s=="QColumnView"){
        QStandardItemModel* model=new QStandardItemModel();

        QStandardItem* cpp=new QStandardItem("C++");
        cpp->appendRow(new QStandardItem("Map"));
        cpp->appendRow(new QStandardItem("Set"));

        QStandardItem* py=new QStandardItem("Python");
        py->appendRow(new QStandardItem("List"));
        py->appendRow(new QStandardItem("Tuple"));

        QStandardItem* java=new QStandardItem("Java");
        java->appendRow(new QStandardItem("HashMap"));
        java->appendRow(new QStandardItem("HashSet"));

        model->appendRow(cpp);
        model->appendRow(py);
        model->appendRow(java);

        QColumnView* view=new QColumnView();
        view->setModel(model);

        showWidget->setWidget(view);
    }
    else if(s=="QCalendarWidget")
    {
        QCalendarWidget* widget=new QCalendarWidget();
        widget->setLocale(QLocale::English);
        showWidget->setWidget(widget);
    }
    else if(s=="QGroupBox")
    {
        QGroupBox* groupBox =new QGroupBox("QGroupBox");

        QRadioButton* radio1 =new QRadioButton(config->value("lan/radioButton").toString()+"1");
        QRadioButton* radio2 =new QRadioButton(config->value("lan/radioButton").toString()+"2");
        QRadioButton* radio3 =new QRadioButton(config->value("lan/radioButton").toString()+"3");

        radio1->setChecked(true);


        QVBoxLayout* v =new QVBoxLayout();
        v->addWidget(radio1);
        v->addWidget(radio2);
        v->addWidget(radio3);
        v->addStretch(1);
        groupBox->setLayout(v);

        showWidget->setWidget(groupBox);
    }
    else if(s=="QProgressBar"){
        QWidget* wid1=new QWidget();
        wid1->setLayout(new QVBoxLayout);
        QProgressBar *h1=new QProgressBar();
        h1->setMinimum(0);
        h1->setMaximum(100);
        h1->setValue(65);
        h1->setOrientation(Qt::Horizontal);

        QProgressBar *h2=new QProgressBar();
        h2->setMinimum(0);
        h2->setMaximum(0);
        h2->setOrientation(Qt::Horizontal);
        wid1->layout()->addWidget(h1);
        wid1->layout()->addWidget(h2);

        QWidget* wid2=new QWidget();
        wid2->setLayout(new QHBoxLayout);

        QProgressBar *v1=new QProgressBar();
        v1->setMinimum(0);
        v1->setMaximum(100);
        v1->setValue(65);
        v1->setOrientation(Qt::Vertical);

        QProgressBar *v2=new QProgressBar();
        v2->setMinimum(0);
        v2->setMaximum(0);
        v2->setOrientation(Qt::Vertical);

        wid2->layout()->addWidget(v1);
        wid2->layout()->addWidget(v2);

        wid1->layout()->addWidget(wid2);

        showWidget->setWidget(wid1);
    }
    else if(s=="QLCDNumber"){
        QLCDNumber* num=new QLCDNumber();
        num->display("6:50");
        showWidget->setWidget(num);
    }
    showWidget->setWindowTitle(config->value("lan/previewWidget").toString()+s);
    //更新标题
    updateShowWidget();
    //更新样式
}

void MainWindow::open() {
    //打开
    QString fileName =QFileDialog::getOpenFileName
            (NULL,config->value("lan/openFDiaTitle").toString(),".","*.qss");
    //获取文件的路径
    if(fileName==NULL)
    {
        //如果没有获取到任何信息 那么返回
        return;
    }


    QFile file(fileName);
    EditWidget* widget=new EditWidget(config);
    //根据路径创造文件对象和新的编辑器窗口
    if(file.open(QIODevice::ReadOnly))
    {
        widget->getTextSpace()->setText(file.readAll());
    }
    else{
        //读取所有信息并设置 如果打开失败就返回
        return;
    }

    widget->setSavePath(fileName);//更新编辑器内部保存的文件路径
    widget->setSaveStatus(true);
    tab->addEditWidget(widget,fileName.right(fileName.length()-
    fileName.lastIndexOf('/')-1));//设置标题（截取路径里的文件名）
    updateShowWidget();//更新样式
}

void MainWindow::newFile() {
    tab->newEditWidget();
    //新建
}

void MainWindow::save() {
    if((dynamic_cast<EditWidget*>(tab->currentWidget()))
       == nullptr)
    {
        return;
    }
    //懂得都懂
    ((EditWidget*)tab->currentWidget())->save();
    //调用编辑器内部的save函数  由于编辑器内部还要监控键盘事件
}

void MainWindow::saveAs() {
    if((dynamic_cast<EditWidget*>(tab->currentWidget()))
       == nullptr)
    {
        return;
    }
    //
    QString savePath=QFileDialog::getSaveFileName
            (this,config->value("lan/saveDiaTitle").toString(),".",".qss");
    //获取另存的路径
    if(savePath==NULL){
        return;
    }
    if(savePath.right(savePath.length()
                      -savePath.lastIndexOf(".")-1)=="qss")
    {}
    else
    {
        //如果
        //文件名里面没有包含扩展名 则添加
        savePath+=".qss";
    }

    ((EditWidget*)tab->currentWidget())->setSavePath(savePath);
    //更新编辑器内部保存的文件路径
    tab->setTabText(tab->currentIndex(),
                    savePath.right(savePath.length()-
                    savePath.lastIndexOf('/')-1));

    ((EditWidget*)tab->currentWidget())->save();
    //更新后调用save
}

void MainWindow::rename() {
    if((dynamic_cast<EditWidget*>(tab->currentWidget()))
       == nullptr)
    {
        return;
    }

    renameStr="";
    //设置初值 后面要用到
    QString savePath=((EditWidget*)tab->currentWidget())
            ->getSavePath();
    //获得编辑器的文件路径
    if(savePath=="")
    {
        //如果路径为空 证明连文件都没 那就保存之后返回吧
        save();
        return;
    }

    RenameDialog* widget=new RenameDialog(this);
    //重命名窗口  可以跳去看一下源码  下面要说到
    widget->exec();
    //模态显示

    delete widget;
    //窗口关闭后释放内存
    if(renameStr!="")
    {
        //如果为空 说明不想重命名了
        //如果不为空 那么
        ((EditWidget*)tab->currentWidget())->rename(renameStr);
        //调用编辑器类内部的重命名函数 并传入文件名参数
        QString savePath= ((EditWidget*)tab->currentWidget())->getSavePath();
        tab->setTabText(tab->currentIndex(),
                        savePath.right(savePath.length()-
                                       savePath.lastIndexOf('/')-1));
        //获得文件路径 更新标题
    }
}

void MainWindow::undo() {
    if((dynamic_cast<EditWidget*>(tab->currentWidget()))
       == nullptr)
    {
        return;
    }
    dynamic_cast<EditWidget*>(tab->currentWidget())->getTextSpace()->undo();
}

void MainWindow::redo() {
    if((dynamic_cast<EditWidget*>(tab->currentWidget()))
       == nullptr)
    {
        return;
    }
    dynamic_cast<EditWidget*>(tab->currentWidget())->
    getTextSpace()->redo();
}

void MainWindow::copy() {
    if((dynamic_cast<EditWidget*>(tab->currentWidget()))
       == nullptr)
    {
        return;
    }
    dynamic_cast<EditWidget*>(tab->currentWidget())->
            getTextSpace()->copy();
}

void MainWindow::paste() {
    if((dynamic_cast<EditWidget*>(tab->currentWidget()))
       == nullptr)
    {
        return;
    }
    dynamic_cast<EditWidget*>(tab->currentWidget())->
            getTextSpace()->paste();
}

void MainWindow::cut() {
    if((dynamic_cast<EditWidget*>(tab->currentWidget()))
       == nullptr)
    {
        return;
    }
    dynamic_cast<EditWidget*>(tab->currentWidget())->
            getTextSpace()->cut();
}

void MainWindow::selectAll() {
    if((dynamic_cast<EditWidget*>(tab->currentWidget()))
       == nullptr)
    {
        return;
    }
    dynamic_cast<EditWidget*>(tab->currentWidget())->
            getTextSpace()->selectAll();
}

void MainWindow::aboutFunc() {
    QMessageBox::information(this,config->value("lan/aboutDiaTitle").toString(),config->value("lan/information").toString());
}
