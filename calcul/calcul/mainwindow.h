#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_RB_SUM_clicked();

    void on_PB_Vich_clicked();

    void on_RB_SUB_clicked();

    void on_RB_MUL_clicked();

    void on_RB_DIV_clicked();

    void on_RB_KVK_clicked();

    void on_RB_SIN_clicked();

    void on_RB_COS_clicked();

    void on_RB_ARCSIN_clicked();

    void on_RB_ARCCOS_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
