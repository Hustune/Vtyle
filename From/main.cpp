#include <QApplication>
#include <QSettings>
#include <QScreen>
#include <QSplashScreen>
#include <time.h>
#include <QTextCodec>
#include "../Header/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QSettings setting("./Data/user.ini",QSettings::IniFormat);


    QPixmap startIma("./Resource/StartScreen.png");
    startIma=startIma.scaled(QGuiApplication::primaryScreen()->availableGeometry().width()/2.5,
                    QGuiApplication::primaryScreen()->availableGeometry().height()/2.5,
                    Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QSplashScreen startScreen(startIma);

    //读取主题信息
    startScreen.showMessage("           读取主题中...",Qt::AlignBottom|Qt::AlignLeft,Qt::white);
    QString theme=setting.value("Appear/theme").toString();
    QFile themeSet("./Resource/Theme.qss");
    if(theme=="normal")
    {
        QFile themeFile("./Data/themes/normal.qss");
        if(themeSet.open(QIODevice::WriteOnly)){
            if(themeFile.open(QIODevice::ReadOnly))
            {
                themeSet.write(themeFile.readAll());
                setting.setValue("Appear/isMetro","false");
                setting.setValue("Color/colorWheelBg","#323232");
                setting.setValue("Color/lineLight","#2C313C");
                setting.setValue("Color/colorPickerIcon","Resource/colorPicker.png");
                setting.setValue("Color/colorPickerHover","#000");
                setting.setValue("Color/svWheelFont","#FFF");

                setting.setValue("Color/value","#FFF");
                setting.setValue("Color/class","#00CFBD");
                setting.setValue("Color/bracket","#D49C9B");
                setting.setValue("Color/property","#EE3A8C");
                setting.setValue("Color/function","#00FDFF");
                setting.setValue("Color/selector","#E5C07B");
                setting.setValue("Color/bracketVal","#BBB");
            }
        }
    }
    else if(theme=="dark")
    {
        QFile themeFile("./Data/themes/dark.qss");
        if(themeSet.open(QIODevice::WriteOnly)){
            if(themeFile.open(QIODevice::ReadOnly))
            {
                themeSet.write(themeFile.readAll());
                setting.setValue("Appear/isMetro","false");
                setting.setValue("Color/colorWheelBg","#323232");
                setting.setValue("Color/lineLight","#2C313C");
                setting.setValue("Color/colorPickerIcon","Resource/colorPicker.png");
                setting.setValue("Color/colorPickerHover","#000");
                setting.setValue("Color/svWheelFont","#FFF");

                setting.setValue("Color/value","#FFF");
                setting.setValue("Color/class","#00CFBD");
                setting.setValue("Color/bracket","#D49C9B");
                setting.setValue("Color/property","#EE3A8C");
                setting.setValue("Color/function","#00FDFF");
                setting.setValue("Color/selector","#E5C07B");
                setting.setValue("Color/bracketVal","#BBB");
            }
        }
    }
    else if(theme=="light")
    {
        QFile themeFile("./Data/themes/light.qss");
        if(themeSet.open(QIODevice::WriteOnly)){
            if(themeFile.open(QIODevice::ReadOnly))
            {
                themeSet.write(themeFile.readAll());
                setting.setValue("Appear/isMetro","false");
                setting.setValue("Color/colorWheelBg","#F0F0F0");
                setting.setValue("Color/lineLight","#F0F0F0");
                setting.setValue("Color/colorPickerIcon","Resource/colorPickerLight.png");
                setting.setValue("Color/colorPickerHover","#E9E9E9");
                setting.setValue("Color/svWheelFont","#867199");

                setting.setValue("Syntax/value","#00cac4");
                setting.setValue("Syntax/class","#00949c");
                setting.setValue("Syntax/bracket","#D49C9B");
                setting.setValue("Syntax/property","#EE3A8C");
                setting.setValue("Syntax/function","#00cac4");
                setting.setValue("Syntax/selector","#E5C07B");
                setting.setValue("Syntax/bracketVal","#BBB");
            }
        }
    }
    else if(theme=="metro dark")
    {
        QFile themeFile("./Data/themes/metroDark.qss");
        if(themeSet.open(QIODevice::WriteOnly)){
            if(themeFile.open(QIODevice::ReadOnly))
            {
                themeSet.write(themeFile.readAll());
                setting.setValue("Color/centralBG","#3b4252");
                setting.setValue("Appear/isMetro","true");

                setting.setValue("Color/colorWheelBg","#282c34");
                setting.setValue("Color/lineLight","#2C313C");
                setting.setValue("Color/colorPickerIcon","Resource/colorPicker.png");
                setting.setValue("Color/colorPickerHover","#000");
                setting.setValue("Color/svWheelFont","#FFF");

                setting.setValue("Syntax/value","#00cac4");
                setting.setValue("Syntax/class","#00949c");
                setting.setValue("Syntax/bracket","#D49C9B");
                setting.setValue("Syntax/property","#EE3A8C");
                setting.setValue("Syntax/function","#00cac4");
                setting.setValue("Syntax/selector","#E5C07B");
                setting.setValue("Syntax/bracketVal","#BBB");

            }
        }
    }
    else if(theme=="metro light")
    {
        QFile themeFile("./Data/themes/metroLight.qss");
        if(themeSet.open(QIODevice::WriteOnly)){
            if(themeFile.open(QIODevice::ReadOnly))
            {
                themeSet.write(themeFile.readAll());
                setting.setValue("Color/centralBG","#f7f8fc");
                setting.setValue("Appear/isMetro","true");
                setting.setValue("Color/colorWheelBg","#f0f0f0");
                setting.setValue("Color/lineLight","#c5c5c9");
                setting.setValue("Color/colorPickerIcon","Resource/colorPickerLight.png");
                setting.setValue("Color/colorPickerHover","#E9E9E9");
                setting.setValue("Color/svWheelFont","#282c34");

                setting.setValue("Syntax/value","#00cac4");
                setting.setValue("Syntax/class","#00949c");
                setting.setValue("Syntax/bracket","#D49C9B");
                setting.setValue("Syntax/property","#EE3A8C");
                setting.setValue("Syntax/function","#00cac4");
                setting.setValue("Syntax/selector","#E5C07B");
                setting.setValue("Syntax/bracketVal","#BBB");

            }
        }
    }

    themeSet.close();

    startScreen.show();
    a.processEvents();
    //开机动画

    startScreen.showMessage("           读取语言配置中...",Qt::AlignBottom|Qt::AlignLeft,Qt::white);
    QString lan=setting.value("Appear/language").toString();
    QSettings* tr;
    if(lan=="Chinese")
    {
        tr=new QSettings("./Resource/language/ch.ini",QSettings::
        IniFormat);
        tr->setIniCodec("UTF-8");
    }else if(lan=="English")
    {
        tr=new QSettings("./Resource/language/en.ini",QSettings::
        IniFormat);
        tr->setIniCodec("UTF-8");
    }

    Vtyle mainWindow(tr);
    mainWindow.resize(1200,800);
    mainWindow.showMaximized();


    startScreen.close();

   QString fontStr=setting.value("Appear/font").toString(),
    alternateFont=setting.value("Appear/alternateFont").toString();

   QFont font;
   font.setPointSize(setting.value("Appear/fontSize").toInt());
   font.setFamilies({fontStr,alternateFont});

    a.setFont(font);

    a.exec();

    return 0;
}
