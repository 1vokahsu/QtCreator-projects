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
    void on_comboBox_2_currentIndexChanged(int index);

    void on_CB_op1_currentIndexChanged(int index);

    void on_CB_op2_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void my_funk(void);
};

#endif // MAINWINDOW_H
