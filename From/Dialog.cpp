#include "../Header/Dialog.h"
#include "../Header/MainWindow.h"

RenameDialog::RenameDialog(QWidget *p): QDialog(p) {
    setWindowTitle("Rename");

    QVBoxLayout* v=new QVBoxLayout();
    QHBoxLayout* h=new QHBoxLayout();

    h->addWidget(new QLabel("文件名:"));

    lineEdit=new QLineEdit;
    lineEdit->setStyleSheet("QLineEdit{color:white;}");

    h->addWidget(lineEdit);
    v->addLayout(h);

    QPushButton* button=new QPushButton("确定");
    button->setStyleSheet("color:white;");

    v->addWidget(button);

    connect(button,&QPushButton::clicked,
            this,&RenameDialog::oK);
    //点击确定按钮就调用oK函数
    setLayout(v);

}

void RenameDialog::oK() {
    ((MainWindow*)parentWidget())->renameStr=lineEdit->text();
    //设置renameStr 你现在应该知道为什么要有这个public method了吧
    close();
    //关闭窗口
}