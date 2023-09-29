#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    no_auto_change=true;
    ui->spinBox_Row->setMaximum(MAS_MAX_SIZE);//меняем максимум спинбокса строк
    ui->spinBox_column->setMaximum(MAS_MAX_SIZE);//меняем максимум спинбокса столбцов
    mas_table1=nullptr;
    mas_table2=nullptr;
    mas_exist=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PBaddrow_clicked()//добавить строку
{
    ui->spinBox_Row->setValue(ui->spinBox_Row->value()+1);
}


void MainWindow::on_PBdelrow_clicked()//убрать строку
{
    ui->spinBox_Row->setValue(ui->spinBox_Row->value()-1);
}


void MainWindow::on_PBaddcolumn_clicked()//добавить столбец
{
    ui->spinBox_column->setValue(ui->spinBox_column->value()+1);
}


void MainWindow::on_PBdelcolumn_clicked()//удалить столбец
{
    ui->spinBox_column->setValue(ui->spinBox_column->value()-1);
}


void MainWindow::on_spinBox_Row_valueChanged(int arg1)//изменение спинбокса строки
{
    ui->tableWidget->setRowCount(arg1);
}


void MainWindow::on_spinBox_column_valueChanged(int arg1)//изменения спинбокса стобца
{
    ui->tableWidget->setColumnCount(arg1);
}


void MainWindow::on_pushButton_sum_clicked()//считаем сумму
{
    no_auto_change=false;
    int row=ui->tableWidget->rowCount();
    int column=ui->tableWidget->columnCount();
    int sum=0;
    bool flag;

    for (int i=0;i<row;i++)
        for (int j=0;j<column;j++)
            if (ui->tableWidget->item(i,j)!=nullptr)//проверка на существование ячейки
            { //сущствует
                sum+=ui->tableWidget->item(i,j)->text().toInt(&flag);
                if (flag)
                    ui->tableWidget->item(i,j)->setBackground(Qt::white);
                else
                    ui->tableWidget->item(i,j)->setBackground(Qt::red);
            }
            else
            {//не существут
                //создаем
                QTableWidgetItem * ti;//создаем указатель
                ti = new QTableWidgetItem;//выделяем память
                ui->tableWidget->setItem(i,j,ti);//заносим в ячейку в таблицу
                ui->tableWidget->item(i,j)->setBackground(Qt::blue);
                QBrush br;
                br.setColor(Qt::blue);
                br.setStyle(Qt::DiagCrossPattern);
                ui->tableWidget->item(i,j)->setBackground(br);
            }

    ui->label_sum->setNum(sum);
    no_auto_change=true;
}


void MainWindow::on_pushButton_random_clicked()//заполнение случайными числами
{
    no_auto_change=false;
    int row=ui->tableWidget->rowCount();
    int column=ui->tableWidget->columnCount();

    int val;
    for (int i=0;i<row;i++)
        for (int j=0;j<column;j++)
        {
            if (ui->tableWidget->item(i,j)==nullptr)//провеерка на существование ячейки таблицы
            {
                //создаем
                QTableWidgetItem * ti;//создаем указатель
                ti = new QTableWidgetItem;//выделяем память
                ui->tableWidget->setItem(i,j,ti);//заносим в ячейку в таблицу
            }
            val=rand()%201-100; //от -100 до 100
            ui->tableWidget->item(i,j)->setBackground(Qt::white);
            ui->tableWidget->item(i,j)->setText(QString::number(val));
        }
    no_auto_change=true;
}
void MainWindow::on_tableWidget_cellChanged(int row, int column)//изменили ячейку
{
    if (no_auto_change)
    {
        bool flag;
        ui->tableWidget->item(row, column)->text().toInt(&flag);
        if (flag)
            ui->tableWidget->item(row,column)->setBackground(Qt::white);
        else
            ui->tableWidget->item(row,column)->setBackground(Qt::yellow);
    }
}


void MainWindow::on_pushButton_magic_clicked()//демо для массива нечет*2 чет+3
{
    no_auto_change=false;
    int row=ui->tableWidget->rowCount();
    int column=ui->tableWidget->columnCount();
    bool flag;//признак успешного преобразования ячейки
    bool gl_flag=true;//признак успешности преобразования таблицы в массиве

    //выделение памяти
    try
    {
        mas_table1=new int[row];
    }
    catch (std::bad_alloc&)
    {
        QMessageBox::information(this, "Ошибка", "Не могу выделить память", QMessageBox::Ok);
        //  return;
        gl_flag=false;
    }
    if (gl_flag)
    {
        try
        {
            mas_table2=new int*[row];
            for (int i=0;i<row;i++)
                mas_table2[i]=nullptr;
            //цикл выше бессмысленного в случае норм работы
            //он только на аварийную ситуацию.
            for (int i=0;i<row;i++)
                mas_table2[i]=new int[column];
        }
        catch (std::bad_alloc&)
        {
            QMessageBox::information(this, "Ошибка", "Не могу выделить память", QMessageBox::Ok);
            //return;
            gl_flag=false;
        }
    }

    //формируем массив
    for (int i=0;i<row;i++)
    {
        for (int j=0;j<column;j++)
        {
            if (ui->tableWidget->item(i,j)==nullptr)
            {
                gl_flag=false;//нашли не существующую ячейку
                //создаем
                QTableWidgetItem * ti;//создаем указатель
                ti = new QTableWidgetItem;//выделяем память
                ui->tableWidget->setItem(i,j,ti);//заносим в ячейку в таблицу
                ui->tableWidget->item(i,j)->setBackground(Qt::darkGray);
            }
            else
            {
                mas_table2[i][j] +=ui->tableWidget->item(i,j)->text().toInt(&flag);
                if (flag)
                    ui->tableWidget->item(i,j)->setBackground(Qt::white);
                else
                {
                    ui->tableWidget->item(i,j)->setBackground(Qt::magenta);
                    gl_flag=false;//нашли ячейку с ошибкой
                }
            }
        }
        mas_table1[i]=mas_table2[i][0];

    }

    if(gl_flag)//если массив сформирован без ошибок(то есть сформирован правильно)
    {
        //расчеты
        for (int i=0;i<row;i++)
            for (int j=0;j<column;j++)
                if (mas_table2[i][j]%2==0)
                    mas_table2[i][j]+=3;//четные+3
                else
                    mas_table2[i][j]*=2;//нечет *2

        //вывод в таблицу (проверок нет, тк по условию gl_flag все уж проврено)
        for (int i=0;i<row;i++)
            for (int j=0;j<column;j++)
                ui->tableWidget->item(i,j)->setText(QString::number(mas_table2[i][j]));
    }
    //освобождение памяти
    delete [] mas_table1;
    mas_table1=nullptr;

    if(mas_table2!=nullptr)//нужно, тк при мас табл2 равном nullptr
    {//будет крашиться люб обращение к мас табл2
        for (int i=0;i<row;i++)
            delete [] mas_table2[i];
        delete [] mas_table2;
        mas_table2=nullptr;
    }
    no_auto_change=true;
}


void MainWindow::on_pushButton_crash_clicked()//ломательная кнопка
{
    int*bad_mas;
    bad_mas=(int*)0xad554432;//мусорный указатеель
    //    bad_mas=nullptr; //если включить эту строку, то авариия отменяется
    delete [] bad_mas; //будет аварийное завершеение
}
bool MainWindow::creat_mas()
{
    no_auto_change=false;
    int row=ui->tableWidget->rowCount();
    int column=ui->tableWidget->columnCount();
    bool flag;//признак успешного преобразования ячейки
    bool gl_flag=true;//признак успешности преобразования таблицы в массиве

    if(mas_table2!=nullptr)//нужно, тк при мас табл2 равном nullptr
    {//будет крашиться люб обращение к мас табл2
        for (int i=0;i<row;i++)
            delete [] mas_table2[i];
        delete [] mas_table2;
        mas_table2=nullptr;
    }
    //выделение памяти
    try
    {
        mas_table1=new int[row];
    }
    catch (std::bad_alloc&)
    {
        QMessageBox::information(this, "Ошибка", "Не могу выделить память", QMessageBox::Ok);
        //  return;
        gl_flag=false;
    }
    if (gl_flag)
    {
        try
        {
            mas_table2=new int*[row];
            for (int i=0;i<row;i++)
                mas_table2[i]=nullptr;
            //цикл выше бессмысленного в случае норм работы
            //он только на аварийную ситуацию.
            for (int i=0;i<row;i++)
                mas_table2[i]=new int[column];
        }
        catch (std::bad_alloc&)
        {
            QMessageBox::information(this, "Ошибка", "Не могу выделить память", QMessageBox::Ok);
            //return;
            gl_flag=false;
        }
    }

    //формируем массив
    for (int i=0;i<row;i++)
    {
        for (int j=0;j<column;j++)
        {
            if (ui->tableWidget->item(i,j)==nullptr)
            {
                gl_flag=false;//нашли не существующую ячейку
                //создаем
                QTableWidgetItem * ti;//создаем указатель
                ti = new QTableWidgetItem;//выделяем память
                ui->tableWidget->setItem(i,j,ti);//заносим в ячейку в таблицу
                ui->tableWidget->item(i,j)->setBackground(Qt::darkGray);
            }
            else
            {
                mas_table2[i][j] +=ui->tableWidget->item(i,j)->text().toInt(&flag);
                if (flag)
                    ui->tableWidget->item(i,j)->setBackground(Qt::white);
                else
                {
                    ui->tableWidget->item(i,j)->setBackground(Qt::magenta);
                    gl_flag=false;//нашли ячейку с ошибкой
                }
            }
        }
        mas_table1[i]=mas_table2[i][0];

    }

    if(gl_flag)//если массив сформирован без ошибок(то есть сформирован правильно)
    {
        //расчеты
        for (int i=0;i<row;i++)
            for (int j=0;j<column;j++)
                if (mas_table2[i][j]%2==0)
                    mas_table2[i][j]+=3;//четные+3
                else
                    mas_table2[i][j]*=2;//нечет *2

        //вывод в таблицу (проверок нет, тк по условию gl_flag все уж проврено)
        for (int i=0;i<row;i++)
            for (int j=0;j<column;j++)
                ui->tableWidget->item(i,j)->setText(QString::number(mas_table2[i][j]));
    }
    //освобождение памяти
    delete [] mas_table1;
    mas_table1=nullptr;

    if(mas_table2!=nullptr)//нужно, тк при мас табл2 равном nullptr
    {//будет крашиться люб обращение к мас табл2
        for (int i=0;i<row;i++)
            delete [] mas_table2[i];
        delete [] mas_table2;
        mas_table2=nullptr;
    }
    mas_exist=gl_flag;
    no_auto_change=true;
    return (gl_flag);

}

void MainWindow::on_pushButton_magic_2_clicked()
{

    int row=ui->tableWidget->rowCount();
    int column=ui->tableWidget->columnCount();
    bool gl_flag=true;//признак успешности преобразования таблицы в массиве

    if (mas_changed||(!mas_exist))
    {
        gl_flag=creat_mas();
    }
    no_auto_change=false;
    if(gl_flag)//если массив сформирован без ошибок(то есть сформирован правильно)
    {
        //расчеты
        for (int i=0;i<row;i++)
            for (int j=0;j<column;j++)
                if (mas_table2[i][j]%2==0)
                    mas_table2[i][j]+=3;//четные+3
                else
                    mas_table2[i][j]*=2;//нечет *2

        //вывод в таблицу (проверок нет, тк по условию gl_flag все уж проврено)
        for (int i=0;i<row;i++)
            for (int j=0;j<column;j++)
                ui->tableWidget->item(i,j)->setText(QString::number(mas_table2[i][j]));
    }
    no_auto_change=true;
}

bool MainWindow::give_memo(int*&mas, int size)
{
    bool fl;
    if ((size>0)&&(size*size_int))

}
