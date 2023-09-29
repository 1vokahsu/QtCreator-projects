#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

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


void MainWindow::on_pushButton_clicked()//кнопка меняющая цвет из введенных чисел
{
    int r;
    int g;
    int b;

    bool flagG;
    bool flagR;
    bool flagB;

    QTableWidgetItem *item = ui->tableWidget->item(0, 3);
    if (item == nullptr)
    {
        item = new QTableWidgetItem;
        ui->tableWidget->setItem(0, 3, item);
    }

    item->setText(" ");

    QTableWidgetItem *itemR = ui->tableWidget->item(0, 0);
    QTableWidgetItem *itemG = ui->tableWidget->item(0, 1);
    QTableWidgetItem *itemB = ui->tableWidget->item(0, 2);

    if(itemB == nullptr || itemG == nullptr || itemR == nullptr)
    {
        item->setBackground(Qt::white);
        QMessageBox::information(this, "", "Введите значения");
        return;
    }

    r = ui->tableWidget->item(0, 0)->text().toInt(&flagR);
    g = ui->tableWidget->item(0, 1)->text().toInt(&flagG);
    b = ui->tableWidget->item(0, 2)->text().toInt(&flagB);

    if(r<0 || r>255 || g<0 || g>255 || b<0 || b>255)
    {
        item->setBackground(Qt::white);
        QMessageBox::information(this, "", "Некорректно введены значения");
        return;
    }

    item->setBackground(QColor(r, g, b));
}

