///:编辑器窗口类
#ifndef QSSEDITOR_EDITWIDGET_H
#define QSSEDITOR_EDITWIDGET_H
#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QFile>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QKeyEvent>
#include <QCompleter>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QSettings>
#include <QStyledItemDelegate>

#include "../Header/Syntax.h"

class NumberShow:public QTextEdit{
    Q_OBJECT
    //此类用于显示行号
public:
    NumberShow(QTextEdit* text);

public slots:
    void updateNumber();
    //更新行号显示
private:
    QTextEdit* text;
};

class EditSpace:public QTextEdit{
    //文本编辑器类
    Q_OBJECT
public:
    EditSpace(QSettings* config);
    void completeWord(const QString& str);

protected:
    void keyPressEvent(QKeyEvent *e) override;
private:
    QString getCursorWord();//获取光标处文字
    QCompleter* completer;//补全内容显示窗口

    void showMenu();//弹出自定义的右键菜单

    QMenu* menu;
    QAction* undoAction;
    QAction* redoAction;
    QAction* copyAction;
    QAction* pasteAction;
    QAction* cutAction;
    QAction* selectAllAction;
};

class EditWidget:public QWidget{
    Q_OBJECT
public:
    EditWidget(QSettings* config,QWidget* p= nullptr);
    QTextEdit* getTextSpace();//获取内部的EditSpace
    void highlighter();//光标所在行高亮
    void setSavePath(QString& s){
        savePath=s;
    }//设置文件保存路径
    QString getSavePath(){return savePath;}//获取路径
    void rename(QString s);//重命名函数
    void save();
    //保存
    bool closeed();
    void setSaveStatus(bool b)
    {
        isSave=b;
    }
private:
    QSettings* colorConfig;
    QHBoxLayout* layout;
        EditSpace* editSpace;
        NumberShow* numberShow;
    QString savePath;//文件保存路径
    bool isCtrl,isS;//用于键盘监测Ctrl+s
    Syntax* syntax;//高亮

    bool isSave;
    QSettings* conf;
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    //用于键盘事件的监控


};

#endif //QSSEDITOR_EDITWIDGET_H
