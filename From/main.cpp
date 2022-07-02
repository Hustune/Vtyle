#include <QApplication>
#include <QSettings>
#include <QScreen>
#include <QSplashScreen>
#include <time.h>
#include <QTextCodec>
#include <QProcess>
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


    MainWindow mainWindow(tr);
    mainWindow.resize(1200,800);
    mainWindow.setWindowTitle("Vtyle");
    mainWindow.setWindowIcon(QIcon("./Resource/QStyleIcon.ico"));
    mainWindow.showMaximized();


    startScreen.close();

   QString fontStr=setting.value("Appear/font").toString(),
    alternateFont=setting.value("Appear/alternateFont").toString();

   QString f1,f2;
   if(fontStr=="JetBrainsMono-Regular")
   {
       int jBMono = QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath() + "./Resource/font/JetBrainsMono-Regular.ttf");
       f1= QFontDatabase::applicationFontFamilies(jBMono).at(0);
   }
   else{
       f1=fontStr;
   }
   if(alternateFont=="SourceHanSans-Normal")
   {
       int sy = QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath() + "./Resource/font/SourceHanSans-Normal.otf");
       f2= QFontDatabase::applicationFontFamilies(sy).at(0);
   }
   else{
       f2=alternateFont;
   }
   QFont font;
   font.setPointSize(setting.value("Appear/fontSize").toInt());
   font.setFamilies({f1,f2});

    a.setFont(font);

    int re= a.exec();
    if(re==1)
    {
        mainWindow.close();
        QProcess cess;
        cess.startDetached(qApp->applicationFilePath());
        cess.waitForStarted();

    }

    return re;
}
