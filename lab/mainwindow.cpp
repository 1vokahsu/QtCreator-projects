#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_spinBox_count_valueChanged(int arg1)//функция ручного измнения кол-ва ячеек
{
    ui->tableWidget_massive->setRowCount(arg1);

}


void MainWindow::on_pushButton_randomcount_clicked()//функция, задающее рандомное кол-во ячеек
{
    int rows = 1+rand()%1000000;
    ui->spinBox_count->setValue(rows);
}


void MainWindow::on_pushButton_removeLast_clicked()//функция, которая удаляет последнюю ячейку
{
    int rows=ui->tableWidget_massive->rowCount();
    if (rows == 0)
    {
        QMessageBox::warning(this, "Ошибка", "Нельльзя удалить!");
    }
    else
    {
        ui->tableWidget_massive->removeRow(rows-1);
        ui->spinBox_count->setValue(rows-1);
    }
}


void MainWindow::on_pushButton_randomValue_clicked()//функция, которая заполняет ячейки рандомными числами
{
    int rows = ui->tableWidget_massive->rowCount();
    if(rows==0)
    {
        QMessageBox::warning(this, "Ошибка", "Нет ячеек для заполнения");
    }
    else
    {
        for (int i=0; i<rows; i++)
        {
            QTableWidgetItem*item=ui->tableWidget_massive->item(i, 0);
            if(item==nullptr)
            {
                item=new QTableWidgetItem;
                ui->tableWidget_massive->setItem(i, 0, item);
            }
            int val=rand()%2000000;
            QString text;
            text.setNum(val);
            item->setText(text);
        }
    }
}

bool MainWindow::isCorrectValues()//функция, проверяющая корректность введенных значений в таблицу
{
    int rows = ui->tableWidget_massive->rowCount();
    if(rows == 0)
    {
        //QMessageBox::warning(this, "Ошибка", "Недостаточно строк");
        return false;
    }

    QTableWidgetItem *itemWithError = nullptr;
    for (int i=0;i<rows ;i++ )
    {
        QTableWidgetItem*item = ui->tableWidget_massive->item(i, 0);
        if(item==nullptr)
        {
            item = new QTableWidgetItem;
            ui->tableWidget_massive->setItem(i, 0, item);
            item->setBackground(QBrush(QColor(255, 170, 0)));
            if(itemWithError==nullptr)
            {
                itemWithError=item;
            }
        }
        else
        {
            bool correctItem = isCorrectItem(item);
            if(!correctItem)
            {
                if(itemWithError==nullptr)
                {
                    itemWithError=item;
                }
            }
        }
    }
    if(itemWithError != nullptr)
    {
        ui->tableWidget_massive->scrollToItem(itemWithError);
        return false;
    }
    return true;
}

bool MainWindow::isCorrectItem(QTableWidgetItem*item)//возвращает если значение корректное в item
{
    if(item->text()=="")
    {
        item->setBackground(QBrush(Qt::red));
        return false;
    }
    else
    {
        bool flag = false;
        double val = item->text().toDouble(&flag);
        if(!flag || qIsInf(val) || qIsNaN(val))
        {
            item->setBackground(QBrush(Qt::red));
            return false;
        }
        else
        {
            item->setBackground(QBrush(Qt::gray));
            return true;
        }
    }
}
void MainWindow::on_pushButton_min_clicked()//считаем минимальное
{
    int rows = ui->tableWidget_massive->rowCount();
    bool correct = isCorrectValues();
    if(!correct)
    {
        ui->MinValue->clear();
        QMessageBox::warning(this, "Ошибка", "Ошибка в значение");
    }
    else
    {
        double min = ui->tableWidget_massive->item(0, 0)->text().toDouble();
        for (int i=1;i<rows ;i++ )
        {
            double val = ui->tableWidget_massive->item(i, 0)->text().toDouble();
            if (val < min)
            {
                min = val;
            }
        }
        ui->MinValue->setNum(min);
    }
}


void MainWindow::on_pushButton_max_clicked()//считаем максимальное
{
    int rows = ui->tableWidget_massive->rowCount();
    bool correct = isCorrectValues();
    if(!correct)
    {
        ui->MaxValue->clear();
        QMessageBox::warning(this, "Ошибка", "Ошибка в значение");
    }
    else
    {
        double max = ui->tableWidget_massive->item(0, 0)->text().toDouble();
        for (int i=1;i<rows ;i++ )
        {
            double val = ui->tableWidget_massive->item(i, 0)->text().toDouble();
            if (val > max)
            {
                max = val;
            }
        }
        ui->MaxValue->setNum(max);
    }
}


void MainWindow::on_pushButton_avg_clicked()//считаем среднее
{
    int rows = ui->tableWidget_massive->rowCount();
    bool correct = isCorrectValues();
    if(!correct)
    {
        ui->MaxValue->clear();
        QMessageBox::warning(this, "Ошибка", "Ошибка в значение");
    }
    else
    {
        double avg = ui->tableWidget_massive->item(0, 0)->text().toDouble();
        for (int i=1;i<rows ;i++ )
        {
            double val = ui->tableWidget_massive->item(i, 0)->text().toDouble();
            avg+= val;
        }
        avg = avg/ static_cast<double>(rows);
        ui->AvgValue->setNum(avg);
    }
}


void MainWindow::on_tableWidget_massive_itemChanged(QTableWidgetItem *item)//проверка на корректность введенных значний
{
    if (allowChange)
    {
        isCorrectItem(item);
        ui->MinValue->clear();
        ui->MaxValue->clear();
        ui->AvgValue->clear();
        for (int i=0;i<ui->tableWidget_massive->rowCount() ;i++ )
        {
            QTableWidgetItem*chekItem = ui->tableWidget_massive->item(i, 0);
            if(chekItem != item && chekItem != nullptr)//нужно чтобы не вызывалась проверка самого себя, и н пустой
            {
                isCorrectItem(chekItem);
            }
        }
    }
}


void MainWindow::on_pushButton_sortcomp_clicked()//сортировка расчесткой
{
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Некоректные данные");
        return;
    }
    readMassive();
    double factor=1.2473309;//фактор уменьшения
    int step= size -1;//шаг сортировки
    //последняя итерция цикла когда step==1 эквивалнтна одному проходу сортировки пузырьком
    while (step >= 1)
    {
        for (int i=0; i+step < size; i++)
        {
            if(mas[i]>mas[i+step])
            {
                std::swap(mas[i], mas[i + step]);
            }
        }
        step /= factor;
    }
    writeMassive();
}

void MainWindow::readMassive()//заполнение массива данными из массива
{
    size=ui->tableWidget_massive->rowCount();
    if (mas != nullptr)//если память под массивом уже была выделена
    {
        delete [] mas;//удалеение старых данных
        mas = nullptr;
    }
    mas = new double[size];//динамическое выделение памяти под новый массив

    for (int i=0; i<size; i++)
    {
        mas[i]=ui->tableWidget_massive->item(i, 0)->text().toDouble();
    }
}

void MainWindow::writeMassive()//вывести массив в таблицу
{
    for (int i=0; i<size; i++)
    {
        ui->tableWidget_massive->item(i, 0)->setText(QString::number(mas[i]));
    }
}

void MainWindow::on_pushButton_sortbooble_clicked()//сортировка пузырьком
{
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Некоректные данные");
        return;
    }
    readMassive();
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size-1; j++)
        {
            if (mas[j]>mas[j+1])
            {
                double a=mas[j];//дополнительная переменная для смены местами
                mas[j]=mas[j+1];//меняем местами
                mas[j+1]=a;//значение элементов
            }
        }
    }
    writeMassive();
}

void MainWindow::qsortRecursive(double *mas, int size)//рекурсия
{
    //указатель в начало и в конец массива
    int i =0;
    int j=size-1;
    //центральный элемент массива
    double mid = mas[size/2];
    //делим массив
    do
    {
        //пробеегаем массив и ищем элементы которые нужно перекинуть в другую часть

        //в леевой части массива пропускаем(оставляем на месте) элемнты, которые меньше центрального
        while (mas[i] < mid)
        {
            i++;
        }
        //в правой части попускаем элмнты кот больше центрального
        while(mas[j] > mid)
        {
            j--;
        }
        //меняем местами
        if(i <= j)
        {
            double tmp=mas[i];
            mas[i]=mas[j];
            mas[j]=tmp;

            i++;
            j--;
        }
    }
    while(i <= j);

    //рекурсивные вызовы если осталось что сортировать
    if (j>0)
    {
        //левый
        qsortRecursive(mas, j+1);
    }
    if(i < size)
    {
        //правый
        qsortRecursive(&mas[i], size-i);
    }
}

bool MainWindow::isCorrect()//возвращаем значения корректности сортировки массива
{
    for (int i=0; i<size-1; i++)
    {
        if(mas[i] > mas[i+1])
        {
            return false;
        }
    }
    return true;
}

void MainWindow::on_pushButton_sortfast_clicked()//сортировка быстрая
{
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Некоректные данные");
        return;
    }
    readMassive();
    qsortRecursive(mas, size);
    writeMassive();
}

void MainWindow::bogoSort()//сортировка для обзъяньей сортировки
{
    int count = 0;
    while(!isCorrect())
    {
        if(count == 1000)
        {
            break;
        }
        for (int i=0; i<size; i++)
        {
            std::swap(mas[i], mas[(rand()%size)]);
        }
    }
}
void MainWindow::on_pushButton_sortmonkey_clicked()//обезъянья сортировка
{
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Некоректные данные");
        return;
    }
    readMassive();
    if(size>5)
    {
        QMessageBox::warning(this, "Ошибка", "Обеезъянья сортировка может быть использована для массива, состоящего не более, чем из 5 элеементов!");
        return;
    }
    bogoSort();
    bool masCorrect = isCorrect();//корректность массива
    if(!masCorrect)
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось остортировать");
    }
    else
    {
        writeMassive();
    }
}


void MainWindow::on_pushButton_sortgnom_clicked()//гномья сортировка
{
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Некоректные данные");
        return;
    }
    readMassive();
    int i =1;//счетчик
    while(i<size)
    {
        if(i==0)
        {
            i=1;
        }
        if(mas[i-1]<mas[i]||(abs(mas[i-1]-mas[i]) < pow(10, -15)))//реализация mas[i-1] <= mas[i] в типе дабл
        {
            ++i;//идем вперед
        }
        else
        {//меням местами
            double tmp=mas[i];
            mas[i]=mas[i-1];
            mas[i-1]=tmp;
            //идем назад
            --i;
        }
    }
    writeMassive();
}


void MainWindow::on_pushButton_removeall_clicked()//очистить форму
{
    ui->spinBox_count->setValue(0);
}




void MainWindow::on_pushButton_deletDoubles_clicked()// удалеение дубликатов
{
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Некоректные данные!");
        return;
    }
    readMassive();//считываем массив из таблицы и потом его провряем
    if (size <= 0)
    {
        QMessageBox::warning(this, "Ошибка", "В таблице нет элементов!");
        return;
    }

    double *temp_mas = new double [size];//создаем временный массив для хранния бз повторов
    int noPovtorCount = 0; //кол-во элемнтов в массивее без повторов
    for (int i=0; i<size; i++)
    {
        bool contains = false;//флаг отвечающий за нахождение повтора эл в массиве
        for (int j=0; j<i; j++)
        {
              if(mas[i]==mas[j])
            if(abs(mas[i]-mas[j])<pow(10, -15))
            {
                contains = true;
            }
        }
        if(!contains)//если нет повтора
        {
            temp_mas[noPovtorCount]=mas[i];//запис элемент
            noPovtorCount++;//увеличиваем на 1 тк элемеент был добавлен
        }
    }


    delete [] mas;
    mas=nullptr;

    mas= new double[noPovtorCount];
    size=noPovtorCount;
    for (int i=0; i<noPovtorCount; i++)
    {
        mas[i]=temp_mas[i];
    }


    delete [] temp_mas;
    temp_mas=nullptr;

    ui->spinBox_count->setValue(noPovtorCount);
    writeMassive();
}

