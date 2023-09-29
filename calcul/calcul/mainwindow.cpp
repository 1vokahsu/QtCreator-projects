#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

#define PI 3.14159265

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->LAB_eror->setVisible(false);//прячем сообщение
    //ui->LAB_RES->hide(); //другой способ
    //Отключили тк они есть в кнопке
    ui->RB_SUM->click();//имитируем клик на кнопке сложения
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RB_SUM_clicked()//настройка интерфейса на сложение
{
    ui->LAB_op1->setText("Слагаемое 1");
    ui->LAB_op2->setText("Слагаемое 2");
    ui->PB_Vich->setText("Сумма");
    ui->LAB_eror->setVisible(false);
    ui->LAB_RES->hide();
    ui->lineEdit_op2->setVisible(true);
    ui->LAB_op2->setVisible(true);
}


void MainWindow::on_PB_Vich_clicked()
{
    double op1,op2,res; //переменные
    QString stroka; // строка для выч
    bool flag; // признак успешн конвертации
    if (ui->RB_SUM->isChecked()) //проверяем выбранго ли сложение
    {
        stroka=ui->lineEdit_op1->text(); // копируем введенное знач в стр
        op1=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
        if (flag)
        {//успешно
            stroka=ui->lineEdit_op2->text(); // копируем введенное знач в стр
            op2=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
            if (flag)//проверка успешности
            {//успешно
                res=op1+op2;//форм рез
                stroka.setNum(res);
                ui->LAB_RES->setText(stroka);//форм интерфейс
                if (qIsInf(res))
                {
                    ui->LAB_eror->show();
                    ui->LAB_eror->setText("Бесконечность");
                    ui->LAB_RES->hide();
                }
                else
                {
                    ui->LAB_RES->setVisible(true);//отображаем рез
                    ui->LAB_eror->hide();//прячем ошибку
                }
            }
            else
            {//неуспешно
                ui->LAB_eror->setText("Ошибка в слагаемом 2"); // форм ошибки
                ui->LAB_eror->show();//отображ ошибки
                ui->LAB_RES->setVisible(false);//прячем рез
            }
        }
        else
        {//не успешно
            ui->LAB_eror->setText("Ошибка в слагаемом 1"); // форм ошибки
            ui->LAB_eror->show();//отображ ошибки
            ui->LAB_RES->setVisible(false);//прячем рез
        }

    }
    if (ui->RB_SUB->isChecked()) //проверяем выбранго ли выччитание
    {
        stroka=ui->lineEdit_op1->text(); // копируем введенное знач в стр
        op1=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
        if (flag)
        {//успешно
            stroka=ui->lineEdit_op2->text(); // копируем введенное знач в стр
            op2=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
            if (flag)//проверка успешности
            {//успешно
                res=op1-op2;//форм рез
                stroka.setNum(res);
                ui->LAB_RES->setText(stroka);//форм интерфейс
                if (qIsInf(res))
                {
                    ui->LAB_eror->show();
                    ui->LAB_eror->setText("Бесконечность");
                    ui->LAB_RES->hide();
                }
                else
                {
                    ui->LAB_RES->setVisible(true);//отображаем рез
                    ui->LAB_eror->hide();//прячем ошибку
                }
            }
            else
            {//неуспешно
                ui->LAB_eror->setText("Ошибка в вычитаемом"); // форм ошибки
                ui->LAB_eror->show();//отображ ошибки
                ui->LAB_RES->setVisible(false);//прячем рез
            }
        }
        else
        {//не успешно
            ui->LAB_eror->setText("Ошибка в уменьшаемом"); // форм ошибки
            ui->LAB_eror->show();//отображ ошибки
            ui->LAB_RES->setVisible(false);//прячем рез
        }

    }
    if (ui->RB_MUL->isChecked()) //проверяем выбранго ли умножение
    {
        stroka=ui->lineEdit_op1->text(); // копируем введенное знач в стр
        op1=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
        if (flag)
        {//успешно
            stroka=ui->lineEdit_op2->text(); // копируем введенное знач в стр
            op2=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
            if (flag)//проверка успешности
            {//успешно
                res=op1*op2;//форм рез
                stroka.setNum(res);
                ui->LAB_RES->setText(stroka);//форм интерфейс
                if (qIsInf(res))
                {
                    ui->LAB_eror->show();
                    ui->LAB_eror->setText("Бесконечность");
                    ui->LAB_RES->hide();
                }
                else
                {
                    ui->LAB_RES->setVisible(true);//отображаем рез
                    ui->LAB_eror->hide();//прячем ошибку
                }
            }
            else
            {//неуспешно
                ui->LAB_eror->setText("Ошибка во множителе 2"); // форм ошибки
                ui->LAB_eror->show();//отображ ошибки
                ui->LAB_RES->setVisible(false);//прячем рез
            }
        }
        else
        {//не успешно
            ui->LAB_eror->setText("Ошибка во множителе 1"); // форм ошибки
            ui->LAB_eror->show();//отображ ошибки
            ui->LAB_RES->setVisible(false);//прячем рез
        }

    }
    if (ui->RB_DIV->isChecked()) //проверяем выбранго ли деление
    {
        stroka=ui->lineEdit_op1->text(); // копируем введенное знач в стр
        op1=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
        if (flag)
        {//успешно
            stroka=ui->lineEdit_op2->text(); // копируем введенное знач в стр
            op2=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
            if (flag)//проверка успешности
            {//успешно
                res=op1/op2;//форм рез
                stroka.setNum(res);
                ui->LAB_RES->setText(stroka);//форм интерфейс
                if (qIsInf(res)) // если ноль, то ошибку выведет
                {
                    ui->LAB_eror->setText("Нельзя делить на ноль"); // форм ошибки
                    ui->LAB_eror->show();//отображ ошибки
                    ui->LAB_RES->setVisible(false);//прячем рез
                }
                else
                {
                    ui->LAB_RES->setVisible(true);//отображаем рез
                    ui->LAB_eror->hide();//прячем ошибку
                }
            }
            else
            {//неуспешно
                ui->LAB_eror->setText("Ошибка во делителе"); // форм ошибки
                ui->LAB_eror->show();//отображ ошибки
                ui->LAB_RES->setVisible(false);//прячем рез
            }
        }
        else
        {//не успешно
            ui->LAB_eror->setText("Ошибка во делимом"); // форм ошибки
            ui->LAB_eror->show();//отображ ошибки
            ui->LAB_RES->setVisible(false);//прячем рез
        }

    }
    if (ui->RB_KVK->isChecked()) //проверяем выбран ли кв. корень
    {
        stroka=ui->lineEdit_op1->text(); // копируем введенное знач в стр
        op1=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
        if (flag)
        {//успешно
            if (op1<0)
            {
                ui->LAB_eror->show();
                ui->LAB_eror->setText("Нельзя отрицательные");
                ui->LAB_RES->hide();
            }
            else
            {
                res=sqrt(op1);//форм рез
                stroka.setNum(res);
                ui->LAB_RES->setText(stroka);//форм интерфейс
                ui->LAB_RES->setVisible(true);//отображаем рез
                ui->LAB_eror->hide();//прячем ошибку
            }

        }
        else
        {//не успешно
            ui->LAB_eror->setText("Ошибка в числе"); // форм ошибки
            ui->LAB_eror->show();//отображ ошибки
            ui->LAB_RES->setVisible(false);//прячем рез
        }

    }
    if (ui->RB_SIN->isChecked()) //проверяем выбран ли sin
    {
        stroka=ui->lineEdit_op1->text(); // копируем введенное знач в стр
        op1=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
        if (flag)
        {//успешно
            res=sin(op1*PI/180);//форм рез
            stroka.setNum(res);
            ui->LAB_RES->setText(stroka);//форм интерфейс
            if (qIsNaN(res))
            {
                ui->LAB_eror->show();
                ui->LAB_eror->setText("Не входит в ОДЗ");
                ui->LAB_RES->hide();
            }
            else
            {
                ui->LAB_RES->setVisible(true);//отображаем рез
                ui->LAB_eror->hide();//прячем ошибку
            }
        }
        else
        {//не успешно
            ui->LAB_eror->setText("Ошибка в градусах"); // форм ошибки
            ui->LAB_eror->show();//отображ ошибки
            ui->LAB_RES->setVisible(false);//прячем рез
        }

    }
    if (ui->RB_COS->isChecked()) //проверяем выбран ли cos
    {
        stroka=ui->lineEdit_op1->text(); // копируем введенное знач в стр
        op1=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
        if (flag)
        {//успешно
            res=cos(op1*PI/180);//форм рез
            stroka.setNum(res);
            ui->LAB_RES->setText(stroka);//форм интерфейс
            if (qIsNaN(res))
            {
                ui->LAB_eror->show();
                ui->LAB_eror->setText("Не входит в ОДЗ");
                ui->LAB_RES->hide();
            }
            else
            {
                ui->LAB_RES->setVisible(true);//отображаем рез
                ui->LAB_eror->hide();//прячем ошибку
            }
        }
        else
        {//не успешно
            ui->LAB_eror->setText("Ошибка в градусах"); // форм ошибки
            ui->LAB_eror->show();//отображ ошибки
            ui->LAB_RES->setVisible(false);//прячем рез
        }

    }
    if (ui->RB_ARCSIN->isChecked()) //проверяем выбран ли arcsin
    {
        stroka=ui->lineEdit_op1->text(); // копируем введенное знач в стр
        op1=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
        if (flag)
        {//успешно
            res=(asin(op1))*(180/PI);
            stroka.setNum(res);
            ui->LAB_RES->setText(stroka);//форм интерфейс
            if (qIsNaN(res))
            {
                ui->LAB_RES->hide();
                ui->LAB_eror->show();
                ui->LAB_eror->setText("-1<число>1");
            }
            else
            {
                ui->LAB_RES->setVisible(true);//отображаем рез
                ui->LAB_eror->hide();//прячем ошибку
            }
        }
        else
        {//не успешно
            ui->LAB_eror->setText("Ошибка в числе"); // форм ошибки
            ui->LAB_eror->show();//отображ ошибки
            ui->LAB_RES->setVisible(false);//прячем рез
        }

    }
    if (ui->RB_ARCCOS->isChecked()) //проверяем выбран ли arccos
    {
        stroka=ui->lineEdit_op1->text(); // копируем введенное знач в стр
        op1=stroka.toDouble(&flag); // преобразуем строку в число с формированием флага
        if (flag)
        {//успешно
            res=acos(op1)*(180/PI);
            stroka.setNum(res);
            ui->LAB_RES->setText(stroka);//форм интерфейс
            if (qIsNaN(res))
            {
                ui->LAB_RES->hide();
                ui->LAB_eror->show();
                ui->LAB_eror->setText("-1<число>1");
            }
            else
            {
                ui->LAB_RES->setVisible(true);//отображаем рез
                ui->LAB_eror->hide();//прячем ошибку
            }
        }
        else
        {//не успешно
            ui->LAB_eror->setText("Ошибка в числе"); // форм ошибки
            ui->LAB_eror->show();//отображ ошибки
            ui->LAB_RES->setVisible(false);//прячем рез
        }

    }
}

void MainWindow::on_RB_SUB_clicked()//настройка интерфейса на вычитание
{
    ui->LAB_op1->setText("Уменьшаемое");
    ui->LAB_op2->setText("Вычитаемое");
    ui->PB_Vich->setText("Разность");
    ui->LAB_eror->setVisible(false);
    ui->LAB_RES->hide();
    ui->lineEdit_op2->setVisible(true);
    ui->LAB_op2->setVisible(true);
}

void MainWindow::on_RB_MUL_clicked()//настройка интерфейса на умножение
{
    ui->LAB_op1->setText("Множитель 1");
    ui->LAB_op2->setText("Множитель 2");
    ui->PB_Vich->setText("Произведение");
    ui->LAB_eror->setVisible(false);
    ui->LAB_RES->hide();
    ui->lineEdit_op2->setVisible(true);
    ui->LAB_op2->setVisible(true);
}

void MainWindow::on_RB_DIV_clicked()//настройка интерфейса на деление
{
    ui->LAB_op1->setText("Делимое");
    ui->LAB_op2->setText("Делитель");
    ui->PB_Vich->setText("Частное");
    ui->LAB_eror->setVisible(false);
    ui->LAB_RES->hide();
    ui->lineEdit_op2->setVisible(true);
    ui->LAB_op2->setVisible(true);
}

void MainWindow::on_RB_KVK_clicked()//настройка интерфейса на кв. корень
{
    ui->LAB_op1->setText("Число");
    ui->LAB_op2->hide();
    ui->PB_Vich->setText("Корень из числа");
    ui->LAB_RES->hide();
    ui->LAB_eror->hide();
    ui->lineEdit_op2->setVisible(false);
}


void MainWindow::on_RB_SIN_clicked()//настройка интерфейса на sin
{
    ui->LAB_op1->setText("SIN Градусы");
    ui->LAB_op2->hide();
    ui->PB_Vich->setText("Результат");
    ui->LAB_RES->hide();
    ui->LAB_eror->hide();
    ui->lineEdit_op2->setVisible(false);
}


void MainWindow::on_RB_COS_clicked()//настройка интерфейса на cos
{
    ui->LAB_op1->setText("COS Градусы");
    ui->LAB_op2->hide();
    ui->PB_Vich->setText("Результат");
    ui->LAB_RES->hide();
    ui->LAB_eror->hide();
    ui->lineEdit_op2->setVisible(false);
}


void MainWindow::on_RB_ARCSIN_clicked()//настройка интерфейса на arcsin
{
    ui->LAB_op1->setText("Число");
    ui->LAB_op2->hide();
    ui->PB_Vich->setText("Результат в Градусах");
    ui->LAB_RES->hide();
    ui->LAB_eror->hide();
    ui->lineEdit_op2->setVisible(false);
}


void MainWindow::on_RB_ARCCOS_clicked()//настройка интерфейса на arccos
{
    ui->LAB_op1->setText("Число");
    ui->LAB_op2->hide();
    ui->PB_Vich->setText("Результат в градусах");
    ui->LAB_RES->hide();
    ui->LAB_eror->hide();
    ui->lineEdit_op2->setVisible(false);
}

