#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()//кнопка считающая кол-во рус символов из вводимых данных в таблице
{
    bool flag=true;
    QString stroka=ui->lineEdit->text();
    int size=stroka.size();
    int count = 0;

    for (int i=0; i<size; i++)
    {
        if((stroka[i] >= "А" and stroka[i] <= "Я") or (stroka[i]>="а" and stroka[i]<="я"))
        {
            count++;
        }
    }
    if(size==0)
    {
        QMessageBox::warning(this, "Ошибка", "Введите значения");
        return;
    }
    else
    {
        QMessageBox::information(this, "", "Кол-во символов: "+QString::number(count));
        return;
    }
}
