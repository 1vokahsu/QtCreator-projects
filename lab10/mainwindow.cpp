#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar_loading->hide();
    mas=nullptr;
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
    int rows = 1+rand()%200;
    ui->spinBox_count->setValue(rows);
}

void MainWindow::on_pushButton_removeLast_clicked()//функция, которая удаляет последнюю ячейку
{
    int rows=ui->tableWidget_massive->rowCount();
    if (rows == 0)
    {
        QMessageBox::warning(this, "Ошибка", "Нельзя удалить!");
    }
    else
    {
        ui->tableWidget_massive->removeRow(rows-1);
        ui->spinBox_count->setValue(rows-1);
    }
}

void MainWindow::on_pushButton_randomValue_clicked()//функция, которая заполняет ячейки рандомными числами
{
    flag_hand=false;
    int rows = ui->tableWidget_massive->rowCount();
    if(rows==0)
    {
        QMessageBox::warning(this, "Ошибка", "Нет ячеек для заполнения");
        return;
    }
    if(rows>5000)
    {
        QMessageBox::warning(this, "Ошибка", "Процесс может занять больше времени, чем обычно!");
    }
    int val;
    for (int i=0; i<rows; i++)
    {

        if(ui->tableWidget_massive->item(i, 0)==nullptr)
        {
            QTableWidgetItem*it;
            it=new QTableWidgetItem;
            ui->tableWidget_massive->setItem(i, 0, it);
        }
        val=rand()-150;
        ui->tableWidget_massive->item(i, 0)->setBackground(Qt::gray);
        ui->tableWidget_massive->item(i, 0)->setText(QString::number(val));
    }

    flag_hand=true;
}

bool MainWindow::isCorrectValues()//функция, проверяющая корректность введенных значений в таблицу
{
    int rows = ui->tableWidget_massive->rowCount();
    if(rows == 0)
    {
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
    if(rows == 0)
    {
        ui->MinValue->clear();
        QMessageBox::warning(this, "Ошибка", "Недостаточно строк!");
        return;
    }
    else
    {
        if(!correct)
        {
            ui->MinValue->clear();
            QMessageBox::warning(this, "Ошибка", "Ошибка в значении");

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
}

void MainWindow::on_pushButton_max_clicked()//считаем максимальное
{
    int rows = ui->tableWidget_massive->rowCount();
    bool correct = isCorrectValues();
    if (rows == 0)
    {
        ui->MaxValue->clear();
        QMessageBox::warning(this, "Ошибка", "Недостаточно строк!");
        return;
    }
    else
    {
        if(!correct)
        {
            ui->MaxValue->clear();
            QMessageBox::warning(this, "Ошибка", "Ошибка в значении");
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

}

void MainWindow::on_pushButton_avg_clicked()//считаем среднее
{
    int rows = ui->tableWidget_massive->rowCount();
    bool correct = isCorrectValues();
    if (rows == 0)
    {
        ui->AvgValue->clear();
        QMessageBox::warning(this, "Ошибка", "Недостаточно строк!");
        return;
    }
    else
    {
        if(!correct)
        {
            ui->AvgValue->clear();
            QMessageBox::warning(this, "Ошибка", "Ошибка в значении");
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
}

void MainWindow::on_tableWidget_massive_itemChanged(QTableWidgetItem *item)//проверка на корректность введенных значний
{
    if (allowChange)
    {
        isCorrectItem(item);
        ui->MinValue->clear();
        ui->MaxValue->clear();
        ui->AvgValue->clear();
        if(flag_hand)
        {
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
}

void MainWindow::on_pushButton_sortcomp_clicked()//сортировка расчесткой
{
    flag_hand=false;
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка в значении");
        return;
    }
    readMassive();
    if(size>400000)
    {
        QMessageBox::warning(this, "Ошибка", "Процесс может занять больше времени, чем обычно!");
    }
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
    flag_hand=true;
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
    flag_hand=false;
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка в значении");
        return;
    }
    readMassive();
    if(size>400000)
    {
        QMessageBox::warning(this, "Ошибка", "Процесс может занять больше времени, чем обычно!");
    }
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
    flag_hand=true;
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

bool MainWindow::isCorrect()//возвращаем значения корректности если массив отсортирован
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
    flag_hand=false;
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка в значении");
        return;
    }
    readMassive();
    if(size>400000)
    {
        QMessageBox::warning(this, "Ошибка", "Процесс может занять больше времени, чем обычно!");
    }
    qsortRecursive(mas, size);
    writeMassive();
    flag_hand=true;
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
    flag_hand=false;
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка в значении");
        return;
    }
    readMassive();
    if(size>400000)
    {
        QMessageBox::warning(this, "Ошибка", "Процесс может занять больше времени, чем обычно!");
    }
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
    flag_hand=true;
}

void MainWindow::on_pushButton_sortgnom_clicked()//гномья сортировка
{
    flag_hand=false;
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка в значении");
        return;
    }
    readMassive();
    if(size>400000)
    {
        QMessageBox::warning(this, "Ошибка", "Процесс может занять больше времени, чем обычно!");
    }
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
    flag_hand=true;
}

void MainWindow::on_pushButton_removeall_clicked()//очистить форму
{
    int rows=ui->tableWidget_massive->rowCount();
    if (rows == 0)
    {
        QMessageBox::warning(this, "Ошибка", "Нельзя удалить!");
    }
    else
    {
        ui->spinBox_count->setValue(0);
    }
}

void MainWindow::on_pushButton_clicked()//поиск
{
    bool flag=false;
    double searchValue = ui->lineEdit->text().toDouble(&flag);
    if(!flag)
    {
        ui->lab_searchCountValue->setText("Некоректное значение!");
        ui->textEdit->clear();
        return;
    }
    bool correct = isCorrectValues();
    if(!correct)
    {
        ui->lab_searchCountValue->setText("Некорректные данные!");
        ui->textEdit->clear();
        QMessageBox::warning(this, "Ошибка", "Некорректные данные!");
        return;
    }
    readMassive();
    if(size>400000)
    {
        QMessageBox::warning(this, "Ошибка", "Процесс может занять больше времени, чем обычно!");
    }
    if(size==0)
    {
        ui->lab_searchCountValue->setText("Заполните массив!");
        ui->textEdit->clear();
        QMessageBox::warning(this, "Ошибка", "Заполните массив!");
        return;
    }
    for (int i=0; i<size; i++)
    {
        ui->tableWidget_massive->item(i, 0)->setBackground(Qt::gray);
    }
    bool masSorted = isCorrect();
    int searchCount = 0;//применяем для хранения кол-ва найденных элементов
    QString searchItemNumbers = "";//переменная кот будет хранить в себе номера строки для вывода
    allowChange=false;
    if(!masSorted)//не отсортирован
    {
        for (int i=0; i<size; i++)
        {
            if(abs(mas[i]-searchValue)<pow(10, -5))//сравнение чисеел в дабл
            {//если число в массиве совпадает с искомым
                searchCount++;
                ui->tableWidget_massive->item(i, 0)->setBackground(Qt::yellow);
                if(searchItemNumbers != "")
                {
                    searchItemNumbers.append(", ");
                }
                searchItemNumbers.append(QString::number(i+1));
            }
        }
    }
    else//если массив остортирован, используем бинарный
    {
        int mid = size/2;//центральный
        int left = 0;//самый левый
        int right = size-1;//самый правый
        //кладем -1, чтобы не было проблеем при 1 запуске цикла
        int lastleft = -1;
        int lastright = -1;
        while (abs(mas[mid]-searchValue)>pow(10, -5)
               && (abs(mas[mid+1]-searchValue)>pow(10, -5)))//mas[mid]!=searchValue
        {
            //проверка на бесконечность
            if((left == lastleft)&&(right == lastright))
            {
                break;//значений не найдено-выход из цикла
            }
            //сохр ласт значение границ
            lastleft=left;
            lastright=right;
            //сдвигаем границы
            if(searchValue<mas[mid])
            {//если искомое значние меньше выбраного центра
                right=mid;//сдвиг правой границы влево
            }
            else
            {//если искомое значние больше выбраного центра
                left=mid;//сдвиг левой границы вправо
            }
            mid=(left+right)/2;//задаем новый центр
        }
        //цикл закончился
        if (abs(mas[mid]-searchValue)<pow(10, -5))
        {
            //если центр совпал то менять ничего не нужно
        }
        else if(abs(mas[mid+1]-searchValue)<pow(10, -5))
        {//если искомое справа, то мы сдвигаем центр вправо
            mid++;//сдвиг на 1 элемент
        }
        else
        {//ничего не было найдено
            mid=-1;//ставим заведомо невозмножное значение номера ячйки
        }
        if(mid != -1)
        {//если значения было найдено в массив
            //идем влево пока пока слева будут совпадения
            if (mid>0)//проверка на не самый левый элемент
            {
                int index=mid-1;//элемент кот стоит слева
                while (abs(mas[index]-searchValue)<pow(10, -5))
                {//пока mas[index]==searchValue
                    if(index==0)
                    {//если дошли до 0, выходиим
                        index--;
                        break;
                    }
                    index--;//сдвиг влево
                    //также выход из цикла произойдет как только мы наткнемся на эл кот не равен искомому
                }
                //тк мы сдвинулись на неправильныц эл-сдвиг инд вправо
                index++;
                //если мы попали на эту строку -> нашли крайний левый кот совпадает с искомым
                for (int i=index; i<mid; i++)
                {//если число в массиве совпадает с искомым
                    searchCount++;
                    ui->tableWidget_massive->item(i, 0)->setBackground(Qt::yellow);
                    if (searchItemNumbers != "")
                    {//если в строке уже есть значения
                        searchItemNumbers.append(", ");
                    }
                    searchItemNumbers.append(QString::number(i+1));
                }
            }
            //доб центр, если число в массиве совпадает с искомым
            searchCount++;
            ui->tableWidget_massive->item(mid, 0)->setBackground(Qt::yellow);
            if(searchItemNumbers != "")
            {
                searchItemNumbers.append(", ");
            }
            searchItemNumbers.append(QString::number(mid+1));
            if(mid< size-1)
            {
                int index = mid+1;
                while (abs(mas[index]-searchValue)<pow(10, -5))
                {
                    if(index==size-1)
                    {
                        index++;
                        break;
                    }
                    index++;
                }
                index--;
                //если мы попали на эту строку -> мы нашли крайний левый кот совпад с искомым
                for (int i=mid+1; i<=index; i++)
                {//если число в массиве совпало с искомым
                    searchCount++;
                    ui->tableWidget_massive->item(i, 0)->setBackground(Qt::yellow);
                    if(searchItemNumbers != "")
                    {
                        searchItemNumbers.append(", ");
                    }
                    searchItemNumbers.append(QString::number(i+1));
                }
            }
        }
        else
        {
            searchItemNumbers = "Не найдено!";
        }
    }
    allowChange=true;
    ui->lab_searchCountValue->setNum(searchCount);
    ui->textEdit->setText(searchItemNumbers);
}

void MainWindow::on_pushButton_removeall_deleteDouble_clicked()//удаление дубликатов
{
    flag_hand=false;
    bool correct = isCorrectValues();
    if(!correct)
    {
        QMessageBox::warning(this, "Ошибка", "Некоректные данные!");
        return;
    }
    readMassive();//считываем массив из таблицы и потом его провряем
    if (size == 0)
    {
        QMessageBox::warning(this, "Ошибка", "В таблице нет элементов!");
        return;
    }

    double *temp_mas = new double [size];//создаем временный массив для хранния бз повторов
    int noPovtorCount = 0; //кол-во элемнтов в массивее без повторов
    bool sorted = isCorrect();
    if(sorted)
    {

        temp_mas[0]=mas[0];
        noPovtorCount++;
        for(int i=1; i<size; i++)
        {

            if(abs(mas[i-1]-mas[i])> pow(10, -5))
            {
                temp_mas[noPovtorCount]=mas[i];
                noPovtorCount++;
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Массив нее отсортирован!");
        delete [] temp_mas;
        temp_mas=nullptr;
        return;
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
    flag_hand=true;
}

void MainWindow::on_pushButton_const_clicked()//заполнить массив одним числом
{
    flag_hand=false;
    bool flag=true;
    int rows = ui->tableWidget_massive->rowCount();
    if(rows==0)
    {
        QMessageBox::warning(this, "Ошибка", "Нет ячеек для заполнения");
        return;
    }
    if(rows>400000)
    {
        QMessageBox::warning(this, "Ошибка", "Процесс может занять больше времени, чем обычно!");
    }
    if(flag)
    {
        {
            int val;
            for (int i=0; i<rows; i++)
            {

                if(ui->tableWidget_massive->item(i, 0)==nullptr)
                {
                    QTableWidgetItem*it;
                    it=new QTableWidgetItem;
                    ui->tableWidget_massive->setItem(i, 0, it);
                }
                val=ui->spinBox_const->text().toDouble();;
                ui->tableWidget_massive->item(i, 0)->setBackground(Qt::gray);
                ui->tableWidget_massive->item(i, 0)->setText(QString::number(val));
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Некоректные данные!");
        return;
    }
    flag_hand=true;
}

