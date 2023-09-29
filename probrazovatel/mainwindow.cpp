#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()//выполнить преобразование
{
    int number,cc;//переменная для числа
    QString stroka,ss;//строка для преобразования
    bool flag,flag2; //признак (флаг) успешности преобразования
    stroka=ui->lineEdit->text();// считали введенное значение в строку
    ss=ui->lineEdit_2->text();//считали введенное значение в строку
    number=stroka.toInt(&flag,10);// поменяли
    cc=ss.toInt(&flag2);//поменяли
    if (flag) //проверка
    {
        if (flag2)//проверка
        {
            if ((cc>1) and (cc<33))//проверка си
            {
                if (number>0)//проверка числа
                {
                    stroka.setNum(number,cc); //установили полученное число
                    ui->label->setText(stroka);//вывели полученное число
                }
                else//отриц число
                {
                    ui->label->setText("отрицательное число");
                }
            }
            else//не успешно
            {
                ui->label->setText("ошибка в втором поле");
            }
        }
        else//не успешно
        {
            ui->label->setText("ошибка в втором поле");
        }
    }
    else//не успешно
    {
        ui->label->setText("ошибка во первом поле");

    }



}
