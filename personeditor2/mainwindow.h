#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox> //подключили библиотеку

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PB_clear_clicked();

    void on_PB_creat_clicked();

    void on_LE_name_textChanged(const QString &arg1);

    void on_LE_power_textChanged(const QString &arg1);

    void score_calc(void); //читаем очки

    void on_LE_lovk_textChanged(const QString &arg1);

    void on_LE_int_textChanged(const QString &arg1);

    void on_LE_luck_textChanged(const QString &arg1);

    void on_CB_race_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    int mas_str[4][2]; //4 рассы, значение для мин(0) и макс(1) силы
    int mas_dex[4][2]; //4 рассы, значение для мин(0) и макс(1) ловкости
    int mas_intel[4][2]; //4 рассы, значение для мин(0) и макс(1) интелекта
    int mas_luck[4][2]; //4 рассы, значение для мин(0) и макс(1) удачи
};

#endif // MAINWINDOW_H
