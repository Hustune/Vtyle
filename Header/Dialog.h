///:各种对话框
#ifndef QSSEDITOR_DIALOG_H
#define QSSEDITOR_DIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>


class RenameDialog:public QDialog{
    //重命名窗口
    Q_OBJECT
public:
    RenameDialog(QWidget* p);
    void oK();//点击确定按钮时就调用

private:
    QLineEdit* lineEdit;
};

#endif //QSSEDITOR_DIALOG_H
