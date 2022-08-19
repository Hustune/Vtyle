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
#include <QMenu>
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
#include <QResizeEvent>
#include <QSizePolicy>

#include "math.h"

class SVWheel;
class ColorPicker;
class colorGrids;
class colorGrid;

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
    QSettings* colorConfig;
    QPoint pos;
    bool isMetro;
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
    void setGrids(colorGrids* g)
    {
        grids=g;
    }
    QSettings* reConf()
    {
        return conf;
    }
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void addToG();

    colorGrids* grids;
    QSettings* colorConfig,*conf;
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
    QPushButton* addToGrids;

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

class colorGrids:public QWidget{
Q_OBJECT
public:
    colorGrids(SVWheel* wheel);
    ~colorGrids();
    void addGrid(const QColor color);
    void delGrid(QColor c);

protected:
    void paintEvent(QPaintEvent *event) override{
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
    }
private:
    QList<QColor> grids;

    QGridLayout* layout;
    SVWheel* svWheel;
    int currentRow,currentColumn;
    QSettings* colorConfig;
    bool isMetro;
};

class colorGrid:public QWidget{
    Q_OBJECT
public:
    colorGrid(const QColor& color,QSettings* conf);
    QString getColor()
    {
        return selfColor.name();
    }
signals:
    void show(QPoint pos,QColor color);
    void onDel(QColor c);
protected:
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override{
        if(event->button()==Qt::LeftButton)
        {
            emit show(event->globalPos(),selfColor);
        }
        else{
            controlMenu->move(event->globalX()+5,event->globalY()+5);
            controlMenu->show();
        }
    }
private:
    int pos;
    QColor selfColor;
    QMenu* controlMenu;
        QAction* del;
};

#endif //QSSEDITOR_HELPWIDGET_H
