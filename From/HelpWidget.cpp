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

                        fontChoose->addItem("JetBrainsMono-Regular");
                        alternateFontChoose->addItem("JetBrainsMono-Regular");
                        fontChoose->addItem("SourceHanSans-Normal");
                        alternateFontChoose->addItem("SourceHanSans-Normal");

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
    //本质就是在窗口上绘制一个色轮（包含HSV颜色空间中所有色相）
    // 监测点击事件  然后如果点击事件在窗口里面就响应取色工作
    // 并弹出颜色调节窗口
    svWheel=new SVWheel(conf);
    setStyleSheet("QWidget{background:#000;}");
    //全屏拾色激发按钮
    fullScreenColorPickButton=new
            QPushButton(this);

    QPixmap pixmap = QPixmap("Resource/colorPicker.png");
    fullScreenColorPickButton->setIcon(pixmap);
    //透明背景
    fullScreenColorPickButton->setStyleSheet(
            "QPushButton{border:none;background:transparent;}"
            "QPushButton:hover{background:black;}");

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
    resize(width(),width());

    painter.setPen(Qt::NoPen);

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

    painter.drawEllipse(QPoint(0,0),r,r);
    //画中间的小圆 形成圆环
    painter.setBrush(QBrush(QColor(50,50,50)));
    painter.drawEllipse(QPoint(0,0),r/2,r/2);

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
        svWheel->svShow(event->globalPos(),QColor(red,green,blue));
    }

}

SVWheel::SVWheel(QSettings* conf) {
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    //不在任务栏显示  无标题栏  无阴影

    //下面这些看结构应该就能明白吧
    vLayout=new QVBoxLayout();
    vLayout->setMargin(30);
        colorShow=new QLabel();
        vLayout->addWidget(colorShow);

        sValLayout=new QHBoxLayout();
            sValText=new QLabel("H("+conf->value("lan/wheelHText").toString()+"):");
            sValLayout->addWidget(sValText);

            sSpinBox=new QSpinBox;
            sSpinBox->setMaximum(255);
            connect(sSpinBox,qOverload<int>(&QSpinBox::valueChanged),
                this,&SVWheel::setS);
            sValLayout->addWidget(sSpinBox);

        vLayout->addLayout(sValLayout);

        vValLayout=new QHBoxLayout();
            vValText=new QLabel("V("+conf->value("lan/wheelVText").toString()+"):");
            vValLayout->addWidget(vValText);

            vSpinBox=new QSpinBox;
            vSpinBox->setMaximum(255);
            connect(vSpinBox,
                    qOverload<int>(&QSpinBox::valueChanged),
                        this,&SVWheel::setV);
            vValLayout->addWidget(vSpinBox);
        vLayout->addLayout(vValLayout);

        rgbLayout=new QHBoxLayout();
            rgbText=new QLabel("RBG");
            rgbLayout->addWidget(rgbText);
            rgbVal=new QLineEdit();
            rgbVal->setReadOnly(true);
            rgbLayout->addWidget(rgbVal);
        vLayout->addLayout(rgbLayout);

        htmlLayout=new QHBoxLayout();
            htmlText=new QLabel("Html");
            htmlLayout->addWidget(htmlText);
            htmlVal=new QLineEdit();
            htmlVal->setReadOnly(true);
            htmlLayout->addWidget(htmlVal);
        vLayout->addLayout(htmlLayout);

    setLayout(vLayout);
}

void SVWheel::svShow(QPoint pos,QColor color) {
    setStyleSheet("QWidget{background:rgb(50,50,50);color:white;}");
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
