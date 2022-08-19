///:分页窗口类
#ifndef QSSEDITOR_TABWIDGET_H
#define QSSEDITOR_TABWIDGET_H
#include <QTabWidget>
#include <QFile>
#include "../Header/EditWidget.h"

class MainWindow;

class TabWidget:public QTabWidget {
Q_OBJECT
public:
    TabWidget(QSettings* set,MainWindow* p=nullptr);
    void newEditWidget(const QString& title="*");
    //新建 title参数自己体会
    void addEditWidget(EditWidget* widget,const QString& title="*");
    //添加现有的窗口
    bool removePage(int index)
        {
            if((dynamic_cast<EditWidget*>(widget(index)))
               == nullptr)
            {
                removeTab(index);
                return true;
            }
            bool r=((EditWidget*) widget(index))->closeed();
            if(r)
            {
                removeTab(index);
            }
            return r;
        }
private:
    MainWindow* win;
    //父窗口
    QSettings* config;
};


#endif //QSSEDITOR_TABWIDGET_H
