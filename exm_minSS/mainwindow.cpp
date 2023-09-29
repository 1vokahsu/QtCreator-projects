#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_max->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    double min = 0;
    QString val,val2;
    bool flag;

    val = ui->lineEdit_num->text();
    val.toInt(&flag,32);
    if(flag)
    {
        min=32;
        val.toInt(&flag,16);
        if(flag)
        {
            min = 16;
            val.toInt(&flag,10);
            if(flag)
            {
                min=10;
                val.toInt(&flag,8);
                if(flag)
                {
                    min = 8;
                    val.toInt(&flag,3);
                    if(flag)
                    {
                        min = 3;
                        val.toInt(&flag,2);
                        if(flag)
                            min=2;
                    }
                }
            }
        }
        ui->lineEdit_max->setText(QString::number(min));
    }
    else {
        ui->lineEdit_max->setText("Нет резульатата");
        QMessageBox::information(this,"Ошибка","Некорректное значение для записи в любой СС");
    }

}
