///:主窗口

#ifndef QSSEDITOR_MAINWINDOW_H
#define QSSEDITOR_MAINWINDOW_H
#include <QMainWindow>
#include <QFile>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QComboBox>
#include <QDockWidget>
#include <QLabel>
#include <QUiLoader>
#include <QListView>
#include <QFileDialog>
#include <QStyleFactory>
#include <QToolButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QCommandLinkButton>
#include <QSlider>
#include <QSpinBox>
#include <QListWidget>
#include <QTreeWidget>
#include <QProcess>
#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QLCDNumber>
#include <QProgressBar>
#include <QToolBox>
#include <QCalendarWidget>
#include <QColumnView>
#include <QStandardItemModel>
#include <QSplitter>
#include <QMessageBox>
#include <QPalette>
#include <windowsx.h>
#include <cmath>

#include "./TabWidget.h"
#include "./EditWidget.h"
#include "Dialog.h"
#include "HelpWidget.h"

#define boundaryWidth 10

class MainWindow;
class TitleWid;

class Vtyle:public QWidget {
Q_OBJECT
public:
    Vtyle(QSettings *tr, QWidget *p = nullptr);

    QVBoxLayout *layout;
    MainWindow *mainWid;
    TitleWid *titleWid;
    bool isMax;
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
};
class TitleWid:public QMainWindow{
    Q_OBJECT
public:
    TitleWid(MainWindow* wid,Vtyle* v);

private:
    QWidget* cen;
    QHBoxLayout* layout;
        QLabel* windowIcon;
        QLabel* windowTitleText;

    int wid;
    QPoint pos;
protected:
   void mousePressEvent(QMouseEvent* event){
       pos=event->localPos().toPoint();
       wid=mainWid->width();
   }
   void mouseMoveEvent(QMouseEvent *e)
   {
       mainWid->isMax=false;
       mainWid->showNormal();

       max->setIcon(QIcon("./Resource/max.png"));
       mainWid->move(e->globalX()-double(pos.x())/wid*width(),e->globalY()-pos.y());
   }

    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        mainWid->showMaximized();
    }
public:
        QPushButton* min,*max,*close;
        Vtyle* mainWid;
};

class MainWindow:public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QSettings* tr,QWidget* p= nullptr,Vtyle* v=nullptr);
    bool Close();
protected:
    void closeEvent(QCloseEvent* event)override;
private:
    QSettings* config;
        QWidget* centralWidget;//中心窗口
            QHBoxLayout* layout;
                TabWidget* tab;//分页的窗口
    Vtyle* parent;

public:
        QMenuBar* mainMenuBar;//窗口的菜单栏

        QMenu* fileMenu;//文件菜单
        QAction* openAction;//打开
        QAction* importUiFileAct;//导入ui文件
        QAction* newAction;//新建
        QAction* saveAction;//保存
        QAction* saveAsAction;//另存为
        QAction* restartAction;

        QMenu* editMenu;//编辑菜单
        QAction* renameFileAction;//重命名

        QAction* undoAction;
        QAction* redoAction;
        QAction* copyAction;
        QAction* pasteAction;
        QAction* cutAction;
        QAction* selectAllAction;

        QAction* about;

        QAction* setting;
private:
        QToolBar* controlMenu;//控制工具栏
        QComboBox* replaceControl;//更换控件栏


        QDockWidget* previewWidget;//预览窗口
        QDockWidget* colorWheel;//色轮
public:
    QString renameStr;//用于实现重命名操作
    //这样设计是因为重命名窗口的值比较难获取
    //所以初始化时直接传入主窗口指针  dialog完毕后会设置这个值
    void updateShowWidget();//更新预览窗口显示
    void changeShowWidget(const QString& s);//更换预览窗口的控件
    void open();//打开文件
    void newFile();//新建文件
    void save();//保存
    void saveAs();//另存为
    void rename();//重命名

    void importUiFile();

    void undo();
    void redo();
    void copy();
    void paste();
    void cut();
    void selectAll();

    void aboutFunc();
    void settings();

    void restart();
};

#endif //QSSEDITOR_MAINWINDOW_H
