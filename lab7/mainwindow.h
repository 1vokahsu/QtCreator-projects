#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#define MAS_MAX_SIZE 2000000//макс разм массива
#define MAS_BUF_SIZE 4000000//больше чм этот (байт) выделить нее будлем потому что не хотим

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

    void on_PBaddrow_clicked();

    void on_PBdelrow_clicked();

    void on_PBaddcolumn_clicked();

    void on_PBdelcolumn_clicked();

    void on_pushButton_sum_clicked();

    void on_spinBox_Row_valueChanged(int arg1);

    void on_spinBox_column_valueChanged(int arg1);

    void on_pushButton_random_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_magic_clicked();

    void on_pushButton_crash_clicked();

    bool creat_mas(void);

    void on_pushButton_magic_2_clicked();

    bool give_memo(int*&mas, int size);

private:
    Ui::MainWindow *ui;
    bool no_auto_change;//признак НЕ автоматической работы с таблицей(ручная работы)
    //int mas_table[MAS_MAX_SIZE][MAS_MAX_SIZE];//в 8й практике у вас одномерная таблица и массив надо будет делать одномерный
    int* mas_table1;//указатель на одномерный массив
    int**mas_table2;//указатель на двумерный массив
    bool mas_changed;
    bool mas_exist;
};
#endif // MAINWINDOW_H
