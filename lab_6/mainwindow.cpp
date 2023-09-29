#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

#define PI 3.14159265

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //прячем все не нужное
    ui->eror->hide();
    ui->labpl2->hide();
    ui->labpr2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbvich_clicked()//рассчет параметров при нажатии кнопки
{
    QString stroka;//промеежуточная переменная
    double dlina, dlina2, dlina3, ug1, ug2, ug3, per, pl;//переменные для вычисления
    bool flag;
    //прячем все не нужное
    ui->eror->hide();
    ui->labpl2->hide();
    ui->labpr2->hide();
    stroka=ui->lest->text();
    dlina= stroka.toDouble(&flag);//считываем нашу сторону
    if (flag and dlina>=0 and dlina<=1e308 and not(qIsInf(dlina)) and not(qIsNaN(dlina)))//проверка длины
    {//верно
        stroka=ui->leug->text();
        ug1= stroka.toDouble(&flag);//формируем наш 1 угол
        if(flag and ug1>=0 and not(qIsInf(ug1)) and not(qIsNaN(ug1)))//проверка угла 1
        {//верно
            stroka=ui->leug2->text();
            ug2= stroka.toDouble(&flag);//формируем наш 1 угол
            if(flag and ug2>=0 and not(qIsInf(ug2)) and not(qIsNaN(ug2)))//проверка угла 2
            {//верно
                if(ug1+ug2<180)//проверка суммы 2 углов
                {
                    pl = ((dlina*dlina)*sin(ug1*PI/180)*sin(ug2*PI/180))/(2*sin((ug1+ug2)*PI/180));//считаем площадь
                    ug3 = 180 - ug1 - ug2;//выводим 3 угол
                    dlina2 = (dlina*sin(ug1*PI/180)/sin(ug3*PI/180));//счатем 2 сторону
                    dlina3 = (dlina*sin(ug2*PI/180)/sin(ug3*PI/180));//считаем 3 сторону
                    per = dlina + dlina2 + dlina3;//считаем периметр
                    if(qIsInf(pl) or qIsInf(per))//проврка на выход за одз
                    {
                        ui->eror->show();
                        ui->eror->setText("Не входит в ОДЗ");
                    }
                    else
                    {//если не вышел за одз
                        if (((ug1 == 0) and (ug2 == 0))or((ug1 == 00) and (ug2 == 0)))
                        {
                            per=per*2;
                            pl=0;
                            ui->eror->show();
                            ui->eror->setText("Вырожденный треугольник");
                            ui->labpr2->show();
                            ui->labpl2->show();
                            ui->labpr2->setNum(per);
                            ui->labpl2->setNum(pl);
                        }
                        else
                        {
                            if((ug1 == 0)or(ug2==0))
                            {
                                ui->eror->show();
                                ui->eror->setText("Такого треугольника не существует");
                            }
                            else
                            {
                                if (per>=0 and not(pl>0))//проверка на вырожденный треугольник
                                {
                                    ui->eror->show();
                                    ui->eror->setText("Вырожденный треугольник");
                                    ui->labpr2->show();
                                    ui->labpr2->setNum(per);
                                }
                                else//вывод при проверке всех ошибок
                                {
                                    ui->labpl2->setNum(pl);
                                    ui->labpr2->setNum(per);
                                    ui->labpl2->show();
                                    ui->labpr2->show();
                                    ui->eror->hide();
                                }
                            }

                        }

                    }
                }
                else
                {//ошибка в сумме 2 углов
                    ui->eror->show();
                    ui->eror->setText("Сумма 3-х углов треугольника должны быть не более 180 градусов");
                }
            }
            else
            {//ошибка в угол 2
                ui->eror->show();
                ui->eror->setText("Неправильно введены данные в угол 2");
            }
        }
        else
        {//ошибка в угол 1
            ui->eror->show();
            ui->eror->setText("Неправильно введены данные в угол 1");
        }
    }
    else
    {//ошибка в длине
        ui->eror->show();
        ui->eror->setText("Неправильно введены данные в длине");
    }
}

