#include "../Header/TabWidget.h"
#include "../Header/MainWindow.h"

TabWidget::TabWidget(QSettings* set,MainWindow* p) {
    win=p;
    config=set;

    setObjectName("tabWidget");
    tabBar()->setObjectName("tabBar");
    setPalette(QPalette(QColor(0,0,0)));
    setAutoFillBackground(true);
    setTabShape(QTabWidget::Triangular);
    setMovable(true);
    //标签页可拖动
    setTabsClosable(true);
    //标签页可关闭
    connect(this,&TabWidget::tabCloseRequested,this,
            &TabWidget::removePage);
    //连接关闭函数
}

void TabWidget::newEditWidget(const QString &title) {
    //新建窗口
    EditWidget* widget=new EditWidget(config);
    addTab(widget,title);
    connect(widget->getTextSpace(),&QTextEdit::textChanged,
    win,&MainWindow::updateShowWidget);
    //连接新建窗口的信号  textchanged则updateShowWidget
    //应该能懂吧
    setCurrentWidget(widget);
    //将新建的窗口设置为当前活动的窗口
}

void TabWidget::addEditWidget(EditWidget *widget,const QString &title) {
    addTab(widget,title);
    connect(widget->getTextSpace(),&QTextEdit::textChanged,
            win,&MainWindow::updateShowWidget);
    setCurrentWidget(widget);
}