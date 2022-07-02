//:该类用于创建一个提供帮助的窗口
//这些帮助类似于选色器
#ifndef QSSEDITOR_HELPWIDGET_H
#define QSSEDITOR_HELPWIDGET_H
#include <QWidget>
#include <QAction>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>
#include "qdebug.h"
#include <Windows.h>
#include <QBitmap>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QListWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScreen>
#include <QGuiApplication>
#include <QSettings>
#include <QStackedWidget>
#include <QListWidgetItem>
#include <QFontDatabase>

#include "math.h"

class SVWheel;
class ColorPicker;

class SettingWidget:public QDialog{
    Q_OBJECT
public:
    SettingWidget(QSettings* conf,QWidget* p);

private:
    //当点击确定时启用这个槽
    void callYes();
    //当listWidget里的点击项改变时启用这个
    void settingWidgetChange(QListWidgetItem* item);
    void onCENew(){
        QListWidgetItem* item=new QListWidgetItem("");
        item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsSelectable);
        cEItems->addItem(item);
        cEItems->setCurrentItem(item);
    }
    void onCEDel(){
        for(auto w:cEItems->selectedItems())
        {
            cEItems->removeItemWidget(w);
            delete w;
        }
    }

    QSettings* setting;
    QSettings* config;

    QVBoxLayout* mainLayout;
        QHBoxLayout* settingWidgetLayout;
            QListWidget* items;
            QStackedWidget* showWidget;
                QDialog* appearance;
                    QVBoxLayout * appearVLayout;
                    QComboBox* lanChoose;
                    QComboBox* themeChoose;
                    QComboBox* fontChoose;
                    QComboBox* alternateFontChoose;
                    QSpinBox* fontSizeChoose;
                QDialog* completeEditWidget;
                    QHBoxLayout* cELayout;
                    QListWidget* cEItems;
                    QVBoxLayout* cEEditButtons;
                        QPushButton* cENew;
                        QPushButton* cEDel;

        QHBoxLayout* chooseButtons;
            QPushButton* yes;
            QPushButton* cancel;
};

class HWheel:public QWidget
{
Q_OBJECT
    //明度色轮（H）

public:
    HWheel(QSettings* conf);
    SVWheel* svWheel;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event)override;
    void resizeEvent(QResizeEvent *event) override;
private:
    QPushButton* fullScreenColorPickButton;
    ColorPicker* picker;
};


class ColorPicker:public QWidget {
    Q_OBJECT
public:
    ColorPicker(QWidget* p);
    void pick();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    QWidget* wid;
    QPixmap photo;
};


class SVWheel:public QWidget{
    //S和V数值的调节
    Q_OBJECT
public:
    SVWheel(QSettings* conf);
    void svShow(QPoint pos,QColor color);

protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QVBoxLayout* vLayout;
    QLabel* colorShow;
    QHBoxLayout* sValLayout;
        QLabel* sValText;
        QSpinBox* sSpinBox;
    QHBoxLayout* vValLayout;
        QLabel* vValText;
        QSpinBox* vSpinBox;
    QHBoxLayout* rgbLayout;
        QLabel* rgbText;
        QLineEdit* rgbVal;
    QHBoxLayout* htmlLayout;
        QLabel* htmlText;
        QLineEdit* htmlVal;

    QColor selfColor;
    void setS(int val)
    {
        int h=selfColor.hue(),v=selfColor.value();
        selfColor.setHsv(h,val,v);
        qDebug()<<selfColor.name();
        colorShow->setStyleSheet
        ("QLabel{background-color:"+selfColor.name()+";}");
        colorShow->update();
        rgbVal->setText(QString::number(selfColor.red())+","+
                        QString::number(selfColor.green())+","+
                        QString::number(selfColor.blue()));
        htmlVal->setText(selfColor.name());
    }
    void setV(int val)
    {
        qDebug()<<selfColor.name();
        int h=selfColor.hsvHue(),s=selfColor.hsvSaturation();
        selfColor.setHsv(h,s,val);

        colorShow->setStyleSheet
                ("QLabel{background-color:"+selfColor.name()+";}");
        colorShow->update();
        rgbVal->setText(QString::number(selfColor.red())+","+
                        QString::number(selfColor.green())+","+
                        QString::number(selfColor.blue()));
        htmlVal->setText(selfColor.name());
    }

};

#endif //QSSEDITOR_HELPWIDGET_H
