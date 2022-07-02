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

#include "./TabWidget.h"
#include "./EditWidget.h"
#include "Dialog.h"
#include "HelpWidget.h"

class MainWindow:public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QSettings* tr,QWidget* p= nullptr);
protected:
    void closeEvent(QCloseEvent* event)override;
private:
    QSettings* config;
    QWidget* centralWidget;//中心窗口
        QHBoxLayout* layout;
            TabWidget* tab;//分页的窗口


    QMenuBar* mainMenuBar;//窗口的菜单栏

    QMenu* fileMenu;//文件菜单
    QAction* openAction;//打开
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

    QToolBar* controlMenu;//控制工具栏
    QComboBox* replaceControl;//更换控件栏


    QDockWidget* showWidget;//预览窗口
    QDockWidget* helpWidget;//帮助窗口
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
