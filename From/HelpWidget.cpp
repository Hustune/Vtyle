#include "../Header/HelpWidget.h"

SettingWidget::SettingWidget(QSettings* conf,QWidget *p):QDialog(p) {
    config=conf;
    setWindowTitle(conf->value("lan/conWidTitle").toString());
    setting=new QSettings("./Data/user.ini",QSettings::IniFormat);

    mainLayout=new QVBoxLayout();
        settingWidgetLayout=new QHBoxLayout();
            items=new QListWidget();
            items->addItem(conf->value("lan/confAppear").toString());
            items->addItem(conf->value("lan/confComplete").toString());
            connect(items,&QListWidget::itemClicked,this,&SettingWidget::settingWidgetChange);
            settingWidgetLayout->addWidget(items,1);

            showWidget=new QStackedWidget();
                appearance=new QDialog();
                    appearVLayout=new QVBoxLayout();

                        QLabel* lanChooseLabel=new QLabel(conf->value("lan/confALanChoose").toString());
                        lanChooseLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
                        appearVLayout->addWidget(lanChooseLabel);

                        lanChoose=new QComboBox();
                        lanChoose->addItem("Chinese");
                        lanChoose->addItem("English");
                        lanChoose->setCurrentText(setting->value("Appear/language").toString());
                        appearVLayout->addWidget(lanChoose);

                        QLabel* themeChooseLabel=new QLabel(conf->value("lan/confAThemeChoose").toString());
                        themeChooseLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
                        appearVLayout->addWidget(themeChooseLabel);

                        themeChoose=new QComboBox();
                        themeChoose->addItem("normal");
                        themeChoose->addItem("dark");
                        themeChoose->addItem("light");
                        themeChoose->addItem("metro dark");
                        themeChoose->addItem("metro light");

                        themeChoose->setCurrentText(setting->value("Appear/theme").toString());
                        appearVLayout->addWidget(themeChoose);

                        QLabel* fontChooseLabel=new QLabel(conf->value("lan/confAFontChoose").toString());
                        fontChooseLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
                        appearVLayout->addWidget(fontChooseLabel);

                        fontChoose=new QComboBox();
                        appearVLayout->addWidget(fontChoose);

                        QLabel* alternateFontChooseLabel=new QLabel(conf->value("lan/confAAlternateFChoose").toString());
                        alternateFontChooseLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
                        appearVLayout->addWidget(alternateFontChooseLabel);

                        alternateFontChoose=new QComboBox();
                        appearVLayout->addWidget(alternateFontChoose);

                        QFontDatabase database;

                        for(QString str:database.families()){
                            fontChoose->addItem(str);
                            alternateFontChoose->addItem(str);
                        }

                        fontChoose->setCurrentText(setting->value("Appear/font").toString());
                        alternateFontChoose->setCurrentText(setting->value("Appear/alternateFont").toString());

                        QLabel* fontSizeChooseText=new QLabel(conf->value("lan/confAFontSizeChoose").toString());
                        fontSizeChooseText->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
                        appearVLayout->addWidget(fontSizeChooseText);

                        fontSizeChoose=new QSpinBox();
                        fontSizeChoose->setMinimum(1);
                        fontSizeChoose->setMaximum(50);
                        fontSizeChoose->setValue(setting->value("Appear/fontSize").toInt());
                        appearVLayout->addWidget(fontSizeChoose);

                    appearVLayout->addStretch();
                    appearance->setLayout(appearVLayout);

                showWidget->addWidget(appearance);

                    completeEditWidget=new QDialog();
                        cELayout=new QHBoxLayout();
                            cEItems=new QListWidget();
                            cEItems->setSelectionMode(QAbstractItemView::ExtendedSelection);

                            QFile completeSentence("./Resource/complete/complete.txt");
                            if(completeSentence.open(QIODevice::ReadOnly))
                            {
                                while(!completeSentence.atEnd())
                                {
                                    auto str=QString::fromLocal8Bit(completeSentence.readLine());
                                    QListWidgetItem* item=new QListWidgetItem
                                            (str.left(str.length()-1));
                                    item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsSelectable);
                                    cEItems->addItem(item);
                                }

                            }

                            cELayout->addWidget(cEItems,7);


                            cEEditButtons=new QVBoxLayout();
                                cENew=new QPushButton(conf->value("lan/confCButtonNew").toString());
                                connect(cENew,&QPushButton::clicked,this,&SettingWidget::onCENew);
                                cEEditButtons->addWidget(cENew);

                                cEDel=new QPushButton(conf->value("lan/confCButtonDel").toString());
                                connect(cEDel,&QPushButton::clicked,this,&SettingWidget::onCEDel);
                                cEEditButtons->addWidget(cEDel);

                                cEEditButtons->addStretch();
                            cELayout->addLayout(cEEditButtons,1);

                        completeEditWidget->setLayout(cELayout);
                showWidget->addWidget(completeEditWidget);


            settingWidgetLayout->addWidget(showWidget,5);
        mainLayout->addLayout(settingWidgetLayout,10);

        chooseButtons=new QHBoxLayout();
        chooseButtons->addStretch();
        chooseButtons->addWidget(new QLabel(conf->value("lan/confTip").toString()));

            yes=new QPushButton(conf->value("lan/confYes").toString());
            connect(yes,&QPushButton::clicked,
                this,&SettingWidget::callYes);
            chooseButtons->addWidget(yes);

            cancel=new QPushButton(conf->value("lan/confCancel").toString());
            connect(cancel,&QPushButton::clicked,this,&SettingWidget::close);
            chooseButtons->addWidget(cancel);
        mainLayout->addLayout(chooseButtons,1);

    setLayout(mainLayout);

    resize(QGuiApplication::primaryScreen()->availableGeometry().width()/2,
           QGuiApplication::primaryScreen()->availableGeometry().height()/2);
}

void SettingWidget::callYes() {
    setting->setValue("Appear/language",lanChoose->currentText());
    setting->setValue("Appear/theme",themeChoose->currentText());
    setting->setValue("Appear/font",fontChoose->currentText());
    setting->setValue("Appear/alternateFont",alternateFontChoose->currentText());
    setting->setValue("Appear/fontSize",fontSizeChoose->value());
    QFile f("./Resource/complete/complete.txt");
    if(f.open(QIODevice::WriteOnly))
    {
        for(int i=0;i<cEItems->count();i++)
        {
            f.write(cEItems->item(i)->text().toLocal8Bit()+"\n");
        }
    }
    close();
}

void SettingWidget::settingWidgetChange(QListWidgetItem* item) {
    if(item->text()==config->value("lan/confAppear").toString())
    {
        showWidget->setCurrentWidget(appearance);
    }
    else if(item->text()==config->value("lan/confComplete").toString())
    {
        showWidget->setCurrentWidget(completeEditWidget);
    }
}


HWheel::HWheel(QSettings* conf): QWidget() {

    QSettings setting("./Data/user.ini",QSettings::IniFormat);
    isMetro=setting.value("Appear/isMetro").toBool();

    pos.setX(-1);
    pos.setY(-1);
    //本质就是在窗口上绘制一个色轮（包含HSV颜色空间中所有色相）
    // 监测点击事件  然后如果点击事件在窗口里面就响应取色工作
    // 并弹出颜色调节窗口
    colorConfig=new QSettings("./Data/user.ini",QSettings::IniFormat);
    svWheel=new SVWheel(conf);
    setStyleSheet("QWidget{background:"+colorConfig->value("Color/colorWheelBg").toString()+";}");
    //全屏拾色激发按钮
    fullScreenColorPickButton=new
            QPushButton(this);

    QPixmap pixmap = QPixmap(colorConfig->value("Color/colorPickerIcon").toString());
    fullScreenColorPickButton->setIcon(pixmap);
    //透明背景
    fullScreenColorPickButton->setStyleSheet(
            "QPushButton{border:none;background:transparent;}"
            "QPushButton:hover{background:"+colorConfig->value("Color/colorPickerHover").toString()+";}");

    picker=new ColorPicker(this);
    connect(fullScreenColorPickButton,&QPushButton::clicked,picker,&ColorPicker::pick);
}

void HWheel::resizeEvent(QResizeEvent *event) {
    //每次大小改变时 都保持按钮的位置和图标大小正常
    fullScreenColorPickButton->resize(width()/8,width()/8);
    fullScreenColorPickButton->move(width()-fullScreenColorPickButton->width(),0);
    fullScreenColorPickButton->setIconSize(QSize(width()/8,width()/8 ));
}

void HWheel::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    const int r = width()/2;

    painter.setPen(Qt::NoPen);



    if(isMetro){
        painter.setBrush(QColor(colorConfig->value("Color/centralBg").toString()));
        painter.drawRect(this->rect());

        painter.setBrush(QColor(colorConfig->value("Color/colorWheelBg").toString()));
        QRect rect = this->rect();
        // rect: 绘制区域  15：圆角弧度
        painter.drawRoundedRect(rect, 20, 20);
    }
    else{
        painter.setBrush(QColor(colorConfig->value("Color/colorWheelBg").toString()));
        painter.drawRect(this->rect());
    }



//    //背景圆
//    painter.setBrush(QBrush(QColor(80,80,80)));
//    painter.drawEllipse(QPoint(r,r),r,r);



    QConicalGradient conicalGradient(0,0,0);
    QColor color;
    //这些绘图算法自己看吧
    color.setHsv(0,255,255);
    conicalGradient.setColorAt(0.0,color);
    color.setHsv(60,255,255);
    conicalGradient.setColorAt(1.0/6,color);
    color.setHsv(120,255,255);
    conicalGradient.setColorAt(2.0/6,color);
    color.setHsv(180,255,255);
    conicalGradient.setColorAt(3.0/6,color);
    color.setHsv(240,255,255);
    conicalGradient.setColorAt(4.0/6,color);
    color.setHsv(300,255,255);
    conicalGradient.setColorAt(5.0/6,color);
    color.setHsv(360,255,255);
    conicalGradient.setColorAt(6.0/6,color);

    painter.translate(r,r);

    painter.setBrush(QBrush(conicalGradient));

    painter.drawEllipse(QPoint(0,0),r/*/20*19*/,r/*/20*19*/);
    //画中间的小=[圆 形成圆环
    painter.setBrush(QBrush(QColor(colorConfig->value("Color/colorWheelBg").toString())));
    painter.drawEllipse(QPoint(0,0),r/2/*/20*19*/,r/2/*/20*19*/);

    if(pos.x()>0 && pos.y()>0)
    {
        QColor color(255,255,255);
        color.setAlpha(200);
        painter.setBrush(QBrush(color));
        painter.translate(-r,-r);
        painter.drawEllipse(pos,r/25,r/25);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(QBrush(Qt::white),2));
        painter.drawEllipse(pos,r/20,r/20);
    }


}

void HWheel::mousePressEvent(QMouseEvent *event)
{
    const int r = width()/2;
    int distance = sqrt(pow(event->x()-r,2)
            +pow(event->y()-r,2));
    //计算鼠标点击位置到圆心的距离
    //如果小于圆的半径 并大于圆半径的二分之一（中间的小圆） 则进行取色操作
    if(distance<r&&distance>r/2)
    {
        HDC dc = GetDC(0);
        int BGR = GetPixel(dc,event->globalX(),event->globalY());
        int red = BGR & 255;
        int green = BGR >> 8 & 255;
        int blue = BGR >> 16 & 255;
        //获取鼠标所在点颜色
        qDebug()<<QColor(red,green,blue).name();
        pos=event->localPos().toPoint();
        update();
        svWheel->svShow(event->globalPos(),QColor(red,green,blue));
    }

}

SVWheel::SVWheel(QSettings* conf) {
    this->conf=conf;
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    //不在任务栏显示  无标题栏  无阴影

    QFile qss("./Resource/Theme.qss");
    QString qssStyle;
    if(qss.open(QIODevice::ReadOnly))
    {
        qssStyle=qss.readAll();
    }

    colorConfig=new QSettings("./Data/user.ini",QSettings::IniFormat);
    //下面这些看结构应该就能明白吧
    vLayout=new QVBoxLayout();
    vLayout->setMargin(30);
        colorShow=new QLabel();
//        colorShow->setStyleSheet("QLabel{border-color:black;border:5px;}");
        vLayout->addWidget(colorShow);

        sValLayout=new QHBoxLayout();
            sValText=new QLabel("H("+conf->value("lan/wheelHText").toString()+"):");
            sValText->setStyleSheet("QLabel{color:"+colorConfig->value("Color/svWheelFont").toString()+";}");
            sValLayout->addWidget(sValText);

            sSpinBox=new QSpinBox;
            sSpinBox->setStyleSheet("QSpinBox{color:"+colorConfig->value("Color/svWheelFont").toString()+";}");
            sSpinBox->setMaximum(255);
            connect(sSpinBox,qOverload<int>(&QSpinBox::valueChanged),
                this,&SVWheel::setS);
            sValLayout->addWidget(sSpinBox);

        vLayout->addLayout(sValLayout);

        vValLayout=new QHBoxLayout();
            vValText=new QLabel("V("+conf->value("lan/wheelVText").toString()+"):");
            vValText->setStyleSheet("QLabel{color:"+colorConfig->value("Color/svWheelFont").toString()+";}");
            vValLayout->addWidget(vValText);

            vSpinBox=new QSpinBox;
            vSpinBox->setStyleSheet("QSpinBox{color:"+colorConfig->value("Color/svWheelFont").toString()+";}");
            vSpinBox->setMaximum(255);
            connect(vSpinBox,
                    qOverload<int>(&QSpinBox::valueChanged),
                        this,&SVWheel::setV);
            vValLayout->addWidget(vSpinBox);
        vLayout->addLayout(vValLayout);

        rgbLayout=new QHBoxLayout();
            rgbText=new QLabel("RBG");
            rgbText->setStyleSheet("QLabel{color:"+colorConfig->value("Color/svWheelFont").toString()+";}");
            rgbLayout->addWidget(rgbText);
            rgbVal=new QLineEdit();
            rgbVal->setStyleSheet("QLineEdit{color:"+colorConfig->value("Color/svWheelFont").toString()+";}");
            rgbVal->setReadOnly(true);
            rgbLayout->addWidget(rgbVal);
        vLayout->addLayout(rgbLayout);

        htmlLayout=new QHBoxLayout();
            htmlText=new QLabel("Html");
            htmlText->setStyleSheet("QLabel{color:"+colorConfig->value("Color/svWheelFont").toString()+";}");
            htmlLayout->addWidget(htmlText);
            htmlVal=new QLineEdit();
            htmlVal->setStyleSheet("QLineEdit{color:"+colorConfig->value("Color/svWheelFont").toString()+";}");
            htmlVal->setReadOnly(true);
            htmlLayout->addWidget(htmlVal);
        vLayout->addLayout(htmlLayout);

        addToGrids=new QPushButton(conf->value("lan/addToGrid").toString());
        addToGrids->setObjectName("addButton");
        addToGrids->setStyleSheet(qssStyle);
        connect(addToGrids,&QPushButton::clicked,this,&SVWheel::addToG);
        vLayout->addWidget(addToGrids);

    setLayout(vLayout);
}

void SVWheel::addToG() {
    grids->addGrid(QColor(htmlVal->text()));
}

void SVWheel::svShow(QPoint pos,QColor color) {
    setStyleSheet("QWidget{background:rgb"+colorConfig->value("Color/colorWheelBg").toString()+";color:white;}");
    selfColor=color;
    int h,s,v;
    color.getHsv(&h,&s,&v);
    vSpinBox->setValue(v);
    sSpinBox->setValue(s);

    colorShow->setStyleSheet("QLabel{background:"+color.name()+";}");
    colorShow->update();

    rgbVal->setText(QString::number(color.red())+","+
    QString::number(color.green())+","+
    QString::number(color.blue()));

    htmlVal->setText(color.name());
    //设置好一些参数后 将窗口移动到鼠标所在位置并弹出窗口
    move(pos);
    show();
}

void SVWheel::paintEvent(QPaintEvent *event) {
    //为了实现圆角窗口
    QBitmap bmp(this->size());

    bmp.fill();
    QPainter p(&bmp);
    p.setRenderHint(QPainter::Antialiasing,true);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),50,50);
    setMask(bmp);
}

ColorPicker::ColorPicker(QWidget* p): QWidget() {
    wid=p;
    setWindowFlag(Qt::FramelessWindowHint);
    photo.load("Resource/colorPicker.png");
}

void ColorPicker::pick() {
    photo=QGuiApplication::primaryScreen()->grabWindow(0);
    //获取整个屏幕的截图

    update();
    showMaximized();
    //最大化
    setCursor(Qt::CrossCursor);
}

void ColorPicker::mousePressEvent(QMouseEvent *event) {
    if(event->button()==Qt::LeftButton)
    {
        //左键
        QColor color=photo.toImage().pixelColor(event->globalPos());
        //获取鼠标所在点颜色
        ((HWheel*)wid)->svWheel->svShow(
                QPoint(wid->x()+wid->width()/2,
                       wid->y()+wid->width()/2),color);
        close();

    }
    else
    {
        //右键
        close();
    }
}

void ColorPicker::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, photo);
}

colorGrids::colorGrids(SVWheel* sv) {
    QSettings* setting=new QSettings("./Data/user.ini",QSettings::IniFormat);
    colorConfig=setting;
    isMetro=setting->value("Appear/isMetro").toBool();

    currentRow=0;
    currentColumn=0;
    layout=new QGridLayout();
    svWheel=sv;
    sv->setGrids(this);
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<6;j++)
            {
                layout->addWidget(new QWidget,j,i);
            }
        }
    layout->setMargin(50);
    layout->setSpacing(40);

    QFile file("./Data/grids.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            QString s = file.readLine();
            addGrid(QColor(s.left(s.length()-1)));
        }
        file.close();
    }
    setLayout(layout);

}

void colorGrids::addGrid(const QColor color)
{

    colorGrid* grid=new colorGrid(color,svWheel->reConf());
    connect(grid,&colorGrid::show,svWheel,&SVWheel::svShow);
    connect(grid,&colorGrid::onDel,this, &colorGrids::delGrid);
    grids.append(QColor(grid->getColor()));
    layout->addWidget(grid,currentRow,currentColumn);
    if(currentColumn<3)
    {
        currentColumn++;

    }else{
        currentColumn=0;
        currentRow++;
    }
}

void clearLayout(QLayout *layout)
{
    //cv别人的 这个函数是
    QLayoutItem *item;
    while((item = layout->takeAt(0)) != 0){
        //删除widget
        if(item->widget()){
            delete item->widget();
        }
        //删除子布局
        QLayout *childLayout = item->layout();
        if(childLayout){
            clearLayout(childLayout);
        }
        delete item;
    }
}

void colorGrids::delGrid(QColor c) {
    currentRow=0;
    currentColumn=0;

    clearLayout(layout);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<6;j++)
        {
            layout->addWidget(new QWidget,j,i);
        }
    }

    QList<QColor> copy(grids);
    copy.removeOne(c);

    grids.clear();
    for (int i = 0; i < copy.size(); ++i) {
        addGrid( copy.at(i) );
    }
}

colorGrids::~colorGrids() {
    QFile f("./Data/grids.txt");
    if(f.open(QIODevice::WriteOnly))
    {
        for(QColor g:grids)
        {
            f.write(g.name().toLocal8Bit()+"\n");
        }
    }
}

colorGrid::colorGrid(const QColor &color,QSettings* conf): QWidget() {
    QFile qss("./Resource/Theme.qss");
    QString qssStyle;
    if(qss.open(QIODevice::ReadOnly))
    {
        qssStyle=qss.readAll();
    }

    selfColor=color;
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, color);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    controlMenu=new QMenu();
    controlMenu->setObjectName("windowMenu");
    controlMenu->setStyleSheet(qssStyle);
        del=new QAction(conf->value("lan/confCButtonDel").toString());
        connect(del,&QAction::triggered,this,[&]{emit onDel(selfColor);});
        controlMenu->addAction(del);
}

void colorGrid::resizeEvent(QResizeEvent *event) {

}
