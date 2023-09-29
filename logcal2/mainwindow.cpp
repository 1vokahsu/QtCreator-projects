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
void MainWindow:: my_funk()
{
    bool op1, op2; //операнды
    bool res; // результат (у вас должен быть bool)
    //сейчас 0 - серый, 1 - зеленый, 2 - красный, 3 - синий.
    //у вас будет false - красный, true - зеленый
    int index;

    //if (ui->CB_op1->currentIndex()==0)
        //op1 = false;
    //else
        //op1 = true;
    //Так как выше делатьб НЕ НАДО!
    op1=ui->CB_op1->currentIndex()==1;
    op2=ui->CB_op2->currentIndex()==1;
    index=ui->CB_res->currentIndex(); //код операции

    QPalette pal; // палитра
    pal=ui->centralWidget->palette();//взяли тек палитру

    switch(index)
    {
    case 0: //коньюнкция
        res = (op1 && op2);
        ui->CB_op2->show();
        break;
    case 1: //дизьюнкция
        res=op1||op2;
        ui->CB_op2->show();
        break;
    case 2: //импликация
        res=!op1||op2;
        ui->CB_op2->show();
        break;
    case 3: //строг диз
        res= !op1==op2;
        ui->CB_op2->show();
        break;
    case 4: //эквив
        res=(op1==op2);
        ui->CB_op2->show();
        break;
    case 5://отрицание
        ui->CB_op2->hide();
        res=!op1;
        break;
    }
//вы будете форм res  как результат лог функций

    //у вас вместо switch будет if тк res bool

    //вывод
    if (res==1)
        pal.setColor(QPalette::Window,Qt::green);
    else
        pal.setColor(QPalette::Window,Qt::red);


    ui->centralWidget->setAutoFillBackground(true); //включили авто зап
    ui->centralWidget->setPalette(pal); // присвоили нов палитру

}
void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    my_funk();
}

void MainWindow::on_CB_op1_currentIndexChanged(int index)
{
    my_funk();
}

void MainWindow::on_CB_op2_currentIndexChanged(int index)
{
    my_funk();
}
