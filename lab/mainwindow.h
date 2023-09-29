#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTableWidget>
#include <math.h>
//#define MAS_MAX_SIZE 200//макс разм массива

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_count_valueChanged(int arg1);

    void on_pushButton_randomcount_clicked();

    void on_pushButton_removeLast_clicked();

    void on_pushButton_randomValue_clicked();

    bool isCorrectValues(); //функция, проверяющая корректность введенных значений в таблицу

    bool isCorrectItem(QTableWidgetItem *item);//возвращает если значение корректное в item

    void on_pushButton_min_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_avg_clicked();

    void on_tableWidget_massive_itemChanged(QTableWidgetItem *item);

    void on_pushButton_sortcomp_clicked();

    void readMassive();//заполнение массива данными из массива

    void writeMassive();//вывести массив в таблицу

    void on_pushButton_sortbooble_clicked();

    void on_pushButton_sortfast_clicked();

    void qsortRecursive(double *mas, int size);//рекурсия

    bool isCorrect();//возвращаем значения корректности сортировки массива

    void bogoSort();

    void on_pushButton_sortmonkey_clicked();

    void on_pushButton_sortgnom_clicked();

    void on_pushButton_removeall_clicked();

    void on_pushButton_deletDoubles_clicked();

private:
    Ui::MainWindow *ui;

    //double mas[MAS_MAX_SIZE];
    double *mas = nullptr;
    int size = 0;
    bool allowChange=true;
};
#endif // MAINWINDOW_H
