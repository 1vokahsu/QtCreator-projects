#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PB_clear->click();

    ui->LE_lastpoint->setReadOnly(true);//заперт изменений пользователей

    ui->LE_name->setMaxLength(20); //макс длина имени
    ui->LE_power->setMaxLength(2);//макс длина силы
    ui->LE_int->setMaxLength(2);//макс длина интелекта
    ui->LE_lovk->setMaxLength(2);//макс длина ловкости
    ui->LE_luck->setMaxLength(2);//макс длина удачи

    ui->LE_name->setValidator(new QRegularExpressionValidator(QRegularExpression("[а-яА-Яa-zA-Z]*")));
    ui->LE_power->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->LE_lovk->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->LE_luck->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->LE_int->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));

    //массив для силы
    mas_str[0][0]=1;//люди сила мин
    mas_str[0][1]=10;//люди сила макс
    mas_str[1][0]=1;//гномы сила мин
    mas_str[1][1]=9;//гномы сила макс
    mas_str[2][0]=1;//эльфы сила мин
    mas_str[2][1]=10;//эльфы сила макс
    mas_str[3][0]=1;//орки сила мин
    mas_str[3][1]=10;//орки сила макс
    //массив для ловкости
    mas_dex[0][0]=1;//люди ловкость мин
    mas_dex[0][1]=10;//люди ловкость макс
    mas_dex[1][0]=1;//гномы ловкость мин
    mas_dex[1][1]=7;//гномы ловкость макс
    mas_dex[2][0]=1;//эльфы ловкость мин
    mas_dex[2][1]=10;//эльфы ловкость макс
    mas_dex[3][0]=1;//орки ловкость мин
    mas_dex[3][1]=8;//орки ловкость макс
    //массив для интелекта
    mas_intel[0][0]=1;//люди интелект мин
    mas_intel[0][1]=9;//люди интелект макс
    mas_intel[1][0]=1;//гномы интелект мин
    mas_intel[1][1]=10;//гномы интелект макс
    mas_intel[2][0]=1;//эльфы интелект мин
    mas_intel[2][1]=10;//эльфы интелект макс
    mas_intel[3][0]=1;//орки интелект мин
    mas_intel[3][1]=8;//орки интелект макс
    //массив для удача
    mas_luck[0][0]=1;//люди удача мин
    mas_luck[0][1]=7;//люди удача макс
    mas_luck[1][0]=1;//гномы удача мин
    mas_luck[1][1]=10;//гномы удача макс
    mas_luck[2][0]=1;//эльфы удача мин
    mas_luck[2][1]=9;//эльфы удача макс
    mas_luck[3][0]=1;//орки удача мин
    mas_luck[3][1]=6;//орки удача макс


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PB_clear_clicked() //очистка формы
{
    ui->LE_name->clear();
    ui->LE_power->clear();
    ui->LE_int->clear();
    ui->LE_lovk->clear();
    ui->LE_luck->clear();
    ui->LAB_page->clear();

    ui->LAB_hpvalue->clear();
    ui->LAB_mpvalue->clear();
    ui->LAB_atkvalue->clear();
    ui->LAB_nicevalue->clear();
    ui->LAB_protectvalue->clear();

    ui->LE_lastpoint->setText("20");

    ui->RB_man->setChecked(true);
}

void MainWindow::on_PB_creat_clicked()//расчет параметров персонажа
{
    QString name;//имя
    int dlina;//длина имени
    int str, dex, intel, luck; //параметры
    int w = ui->LAB_page->width();//длина для подгона фоток
    int h = ui->LAB_page->height();//ширина для подгона фоток
    bool flag; //признак успеваемости генерации персонажа

    int race_indx;//код (индекс расы)

    //Раса
    race_indx=ui->CB_race->currentIndex();

    //имя
    name=ui->LE_name->text();
    dlina=name.length();//определили длину

    if ((dlina<3)||(dlina>20))//заперерта длина от 3 до 20
    {
        flag=false;
        QMessageBox::information(this, "Ошибка", "Длина имени должна быть от 3 до 20 символов", QMessageBox::Ok);
    }
    else
        flag=true;

    //сила
    str=0;
    if (flag) //вместо вложенных условий
    {
        str=ui->LE_power->text().toInt(&flag); //форм значение силы с
        //проверяем успешность преобразование флагом
        if (flag)
        {
            if ((str<mas_str[race_indx][0])||(str>mas_str[race_indx][1]))
            {
                flag=false;
                QMessageBox::information(this, "Ошибка", "\"Сила\"должна быть от "+ QString::number(mas_str[race_indx][0])+" до "+
                        QString::number(mas_str[race_indx][1])+" . ", QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка", "Неверное значение параметра\"Сила\".", QMessageBox::Ok);
    }
    //ввод и проверка Ловкости
    dex=0;
    if (flag) //вместо вложенных условий
    {
        dex=ui->LE_lovk->text().toInt(&flag); //форм значение ловкости с
        //проверяем успешность преобразование флагом
        if (flag)
        {
            if ((dex<mas_dex[race_indx][0])||(dex>mas_dex[race_indx][1]))
            {
                flag=false;
                QMessageBox::information(this, "Ошибка", "\"Ловкость\"должна быть от "+ QString::number(mas_dex[race_indx][0])+" до "+
                        QString::number(mas_dex[race_indx][1])+" . ", QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка", "Неверное значение параметра\"Ловкость\".", QMessageBox::Ok);
    }
    //ввод и проверка интелекта
    intel=0;
    if (flag) //вместо вложенных условий
    {
        intel=ui->LE_int->text().toInt(&flag); //форм значение интелекта с
        //проверяем успешность преобразование флагом
        if (flag)
        {
            if ((intel<mas_intel[race_indx][0])||(intel>mas_intel[race_indx][1]))
            {
                flag=false;
                QMessageBox::information(this, "Ошибка", "\"Интелект\"должен быть от "+ QString::number(mas_intel[race_indx][0])+" до "+
                        QString::number(mas_intel[race_indx][1])+" . ", QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка", "Неверное значение параметра\"Сила\".", QMessageBox::Ok);
    }
    luck=0;//ввод и проверка удачи
    if (flag) //вместо вложенных условий
    {
        luck=ui->LE_luck->text().toInt(&flag); //форм значение удачи с
        //проверяем успешность преобразование флагом
        if (flag)
        {
            if ((luck<mas_luck[race_indx][0])||(luck>mas_luck[race_indx][1]))
            {
                flag=false;
                QMessageBox::information(this, "Ошибка", "\"Удача\"должна быть от "+ QString::number(mas_str[race_indx][0])+" до "+
                        QString::number(mas_luck[race_indx][1])+" . ", QMessageBox::Ok);
            }
        }
        else
            QMessageBox::information(this,"Ошибка", "Неверное значение параметра\"Удача\".", QMessageBox::Ok);
    }




    //проверяем сумму очков
    if (flag)
    {
        int score_left=20-str-dex-intel-luck;
        ui->LE_lastpoint->setText(QString::number(score_left));
        if(score_left!=0)
        {
            flag=false;
            if (score_left<0)
            {
                QMessageBox::information(this,"Ошибка", "Нельзя тратить больше 20 очков.", QMessageBox::Ok);
            }
            else
            {
                QMessageBox::information(this,"Ошибка", "Нужно потратить все очки.", QMessageBox::Ok);
            }
        }

    }
    //расчет параметров и вывод реза
    if (flag)
    {
        int hp, mp, atk, def;
        if (ui->RB_man->isChecked())//проверка на мужской пол
        {//расчеет пар-ов если м
            hp = 8*str+2*dex;
            mp=8*intel+dex+luck;
            atk=6*str+2*dex+2*luck;
            def=7*dex+3*luck;
            if (race_indx==0)//если человек
            {
                if((intel>7))//условия для мага
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Маг");
                    QPixmap mag(":/res/picture/mag.jpg");
                    ui->LAB_page->setPixmap(mag.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((dex>7))//условия для ловкача ловкого dexy
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Ловкач");
                    QPixmap squire(":/res/picture/chvor.jpg");
                    ui->LAB_page->setPixmap(squire.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str>7))//условия для силача
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Силач");
                    QPixmap chr(":/res/picture/chr.jpg");
                    ui->LAB_page->setPixmap(chr.scaled(w, h, Qt::KeepAspectRatio));
                }
                if ((str<8) and (intel<8) and (dex<8) and (luck<8))//нейтральный
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Нейтральный");
                    QPixmap chn(":/res/picture/chn.png");
                    ui->LAB_page->setPixmap(chn.scaled(w, h, Qt::KeepAspectRatio));
                }

            }
            if (race_indx==1)//гномы
            {
                if((luck>7))//условия для lucky
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Самый удачливый гном");
                    QPixmap gplut(":/res/picture/gplut.jpg");
                    ui->LAB_page->setPixmap(gplut.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str>7))//условия silach'a
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Силач");
                    QPixmap voin(":/res/picture/voin.jpg");
                    ui->LAB_page->setPixmap(voin.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((intel>7))//условия для мага
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Маг");
                    QPixmap mag(":/res/picture/gmag.jpg");
                    ui->LAB_page->setPixmap(mag.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((def<8)and(luck<8)and (intel<8)and(str<8))//условия для нейтрального
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Нейтральный");
                    QPixmap gn(":/res/picture/Gnome.webp");
                    ui->LAB_page->setPixmap(gn.scaled(w, h, Qt::KeepAspectRatio));
                }

            }
            if (race_indx==2)//эльфы
            {
                if((intel>7))//условия для мага
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Маг");
                    QPixmap emag(":/res/picture/emag.webp");
                    ui->LAB_page->setPixmap(emag.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str>7))//условия silacha
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Силач");
                    QPixmap eric(":/res/picture/eric.jpg");
                    ui->LAB_page->setPixmap(eric.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((luck>7))//условия для удачливого
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Самый удачливый эльф");
                    QPixmap eluck(":/res/picture/eluk.webp");
                    ui->LAB_page->setPixmap(eluck.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((dex>7))//условия для ловкач
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Ловкач");
                    QPixmap evor(":/res/picture/evor.jpg");
                    ui->LAB_page->setPixmap(evor.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str<8) and (intel<8)and(dex<8)and(luck<8))//условия для нейтрального
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Нейтральный");
                    QPixmap en(":/res/picture/en.jpg");
                    ui->LAB_page->setPixmap(en.scaled(w, h, Qt::KeepAspectRatio));
                }
            }
            if (race_indx==3)//орки
            {
                if((str>7))//условия для силача
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Силач");
                    QPixmap ovoin(":/res/picture/ovoin.jpg");
                    ui->LAB_page->setPixmap(ovoin.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((intel>7))//условия для мага
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Маг");
                    QPixmap omag(":/res/picture/omag.jpg");
                    ui->LAB_page->setPixmap(omag.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str<8) and (intel<8)and(dex<8)and(luck<8))//условия для нейтрального
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Нейтральный");
                    QPixmap orug(":/res/picture/oorug.jpg");
                    ui->LAB_page->setPixmap(orug.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((dex>7))//условия для ловкач
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Ловкач");
                    QPixmap ovor(":/res/picture/ovor.jpg");
                    ui->LAB_page->setPixmap(ovor.scaled(w, h, Qt::KeepAspectRatio));
                }
            }
        }
        else
        {//расчеет пар-ов если ж
            hp= 6*str+3*dex;
            mp=8*intel+dex+luck;
            atk=4*str+3*dex+3*luck;
            def=6*dex+4*luck;

            if (race_indx==0)//если человек
            {
                if((intel>7))//условия колдуньи
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Колдунья");
                    QPixmap cmagg(":/res/picture/cmagg.jpg");
                    ui->LAB_page->setPixmap(cmagg.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str>7))//условия для силачки
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Силачка");
                    QPixmap cvoing(":/res/picture/cvoing.jpg");
                    ui->LAB_page->setPixmap(cvoing.scaled(w, h, Qt::KeepAspectRatio));
                }
                if(dex>7)//условия для Ловкачки
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Ловкачка");
                    QPixmap cbmagg(":/res/picture/cbmagg.jpg");
                    ui->LAB_page->setPixmap(cbmagg.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str<8) and (intel<8) and (dex<8) and (luck<8))//нейтральная
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Нейтральная");
                    QPixmap chnp(":/res/picture/chsobg.jpg");
                    ui->LAB_page->setPixmap(chnp.scaled(w, h, Qt::KeepAspectRatio));
                }
            }
            if (race_indx==1)//гномы
            {
                if((str>7))//условия силачки
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Силачка");
                    QPixmap gvoing(":/res/picture/gvoing.jpg");
                    ui->LAB_page->setPixmap(gvoing.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((luck>7))//условия Самая удачливая гномиха
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Самая удачливая девочка-гном");
                    QPixmap grg(":/res/picture/grg.jpg");
                    ui->LAB_page->setPixmap(grg.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((intel>7))//условия для кольдуньи
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Кольдунья");
                    QPixmap gmagg(":/res/picture/gmagg.jpg");
                    ui->LAB_page->setPixmap(gmagg.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str<8) and (intel<8) and (dex<8) and (luck<8))//условия для нейтральной
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Нейтральная");
                    QPixmap gng(":/res/picture/gsobg.png");
                    ui->LAB_page->setPixmap(gng.scaled(w, h, Qt::KeepAspectRatio));
                }
            }
            if (race_indx==2)//эльфы
            {
                if((dex>7))//условия для ловкачки
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Ловкачка");
                    QPixmap evorg(":/res/picture/evorg.jpg");
                    ui->LAB_page->setPixmap(evorg.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str<8) and (intel<8) and (dex<8) and (luck<8))//условия для нейтральной
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Нейтральная");
                    QPixmap eng(":/res/picture/eng.jpg");
                    ui->LAB_page->setPixmap(eng.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((intel>7))//условия колдуньи
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Колдунья");
                    QPixmap emagg(":/res/picture/emagg.webp");
                    ui->LAB_page->setPixmap(emagg.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str>7))//условия для силачка
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Силачка");
                    QPixmap evoing(":/res/picture/ericg.jpg");
                    ui->LAB_page->setPixmap(evoing.scaled(w, h, Qt::KeepAspectRatio));
                }
                if(luck>7)//условия для боевой колдуньи
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Самая удачливая женщина-эльф");
                    QPixmap ebmagg(":/res/picture/ebmagg.jpg");
                    ui->LAB_page->setPixmap(ebmagg.scaled(w, h, Qt::KeepAspectRatio));
                }
            }
            if (race_indx==3)//орки
            {
                if((dex>7))//условия для ловкачка
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Ловкачка");
                    QPixmap osobg(":/res/picture/ovorg.jpg");
                    ui->LAB_page->setPixmap(osobg.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str<8) and (intel<8) and (dex<8) and (luck<8))//условия для нейтральной
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Нейтральная");
                    QPixmap ong(":/res/picture/ong.jpg");
                    ui->LAB_page->setPixmap(ong.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((str>7))//условия силачка
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Силачка");
                    QPixmap ovoing(":/res/picture/ovoing.jpg");
                    ui->LAB_page->setPixmap(ovoing.scaled(w, h, Qt::KeepAspectRatio));
                }
                if((intel>7))//условия для кольдуньи
                {
                    ui->LAB_hpvalue->setNum(hp);
                    ui->LAB_mpvalue->setNum(mp);
                    ui->LAB_atkvalue->setNum(atk);
                    ui->LAB_protectvalue->setNum(def);
                    ui->LAB_nicevalue->setText("Колдунья");
                    QPixmap omagg(":/res/picture/omagg.jpg");
                    ui->LAB_page->setPixmap(omagg.scaled(w, h, Qt::KeepAspectRatio));
                }
            }
        }
    }
    else
    { //очищаем предыдущие результаты
        ui->LAB_hpvalue->clear();
        ui->LAB_mpvalue->clear();
        ui->LAB_atkvalue->clear();
        ui->LAB_nicevalue->clear();
        ui->LAB_protectvalue->clear();
        ui->LAB_page->clear();
    }
}

void MainWindow::on_LE_name_textChanged(const QString &arg1)//закрепление длины имени
{
    int dlina=arg1.length();
    QPalette pal;
    pal=ui->LE_name->palette();
    if ((dlina < 3)||(dlina>20))
        pal.setColor(QPalette::Text, Qt::red);
    else
        pal.setColor(QPalette::Text, Qt::green);

    ui->LE_name->setPalette(pal);
}

void MainWindow::on_LE_power_textChanged(const QString &)//расцветка силы в LE и LAB (done)
{
    int race_indx=ui->CB_race->currentIndex();
    int val=ui->LE_power->text().toInt();
    //флаг не нужен тк при ошибке в val будет 0
    QPalette pal, lap;
    pal=ui->LE_power->palette();
    lap=ui->LAB_power->palette();
    if ((val < mas_str[race_indx][0])||(val > mas_str[race_indx][1]))
    {
        pal.setColor(QPalette::Text, Qt::red);
        lap.setColor(QPalette::WindowText, Qt::black);
    }
    else
    {
        pal.setColor(QPalette::Text, Qt::green);
        if ((val >= 1) and (val <= 3))
        {
            lap.setColor(QPalette::WindowText, Qt::red);
        }
        if ((val >= 4)and(val<= 7))
        {
            lap.setColor(QPalette::WindowText, Qt::yellow);
        }
        if ((val >= 8)and(val <= 10))
        {
            lap.setColor(QPalette::WindowText, Qt::green);
        }
    }
    ui->LE_power->setPalette(pal);
    ui->LAB_power->setPalette(lap);
    score_calc();
}
void MainWindow::score_calc(void)//расчет и расцветка остатка очков
{
    int str, dex, intel, luck;
    str=ui->LE_power->text().toInt();
    dex=ui->LE_lovk->text().toInt();
    intel=ui->LE_int->text().toInt();
    luck=ui->LE_luck->text().toInt();

    int score_left=20-str-dex-intel-luck;
    QPalette pal;
    pal=ui->LE_lastpoint->palette();
    if (score_left!=0)
        pal.setColor(QPalette::Text, Qt::black);
    else
        pal.setColor(QPalette::Text, Qt::green);

    ui->LE_lastpoint->setPalette(pal);
    ui->LE_lastpoint->setText(QString::number(score_left));
}

void MainWindow::on_LE_lovk_textChanged(const QString &)//расцветка ловкости в LE and LAB (done)
{
    int race_indx=ui->CB_race->currentIndex();
    int val=ui->LE_lovk->text().toInt();

    //флаг не нужен тк при ошибке в val будет 0
    QPalette pal,lap;
    pal=ui->LE_lovk->palette();
    lap=ui->LAB_lovk->palette();
    if ((val<mas_dex[race_indx][0]) || (val>mas_dex[race_indx][1]))
    {
        pal.setColor(QPalette::Text, Qt::red);
        lap.setColor(QPalette::WindowText, Qt::black);
    }
    else
    {
        pal.setColor(QPalette::Text, Qt::green);
        if ((val>=1)and(val<=3))
        {
            lap.setColor(QPalette::WindowText, Qt::red);
        }
        if ((val>=4)and(val<=7))
        {
            lap.setColor(QPalette::WindowText, Qt::yellow);
        }
        if ((val>=8) and (val<=10))
        {
            lap.setColor(QPalette::WindowText, Qt::green);
        }
    }
    ui->LE_lovk->setPalette(pal);
    ui->LAB_lovk->setPalette(lap);
    score_calc();
}

void MainWindow::on_LE_int_textChanged(const QString &)//расцветка интелекта в LE and LAB (done)
{
    int race_indx=ui->CB_race->currentIndex();
    int val=ui->LE_int->text().toInt();
    //флаг не нужен тк при ошибке в val будет 0
    QPalette pal,lap;
    pal=ui->LE_int->palette();
    lap=ui->LAB_int->palette();
    if ((val<mas_intel[race_indx][0])||(val>mas_intel[race_indx][1]))
    {
        pal.setColor(QPalette::Text, Qt::red);
        lap.setColor(QPalette::WindowText, Qt::black);
    }
    else
    {
        pal.setColor(QPalette::Text, Qt::green);
        if ((val>=1)and(val<=3))
        {
            lap.setColor(QPalette::WindowText, Qt::red);
        }
        if ((val>=4)and(val<=7))
        {
            lap.setColor(QPalette::WindowText, Qt::yellow);
        }
        if ((val>=8)and(val<=10))
        {
            lap.setColor(QPalette::WindowText, Qt::green);
        }
    }
    ui->LE_int->setPalette(pal);
    ui->LAB_int->setPalette(lap);
    score_calc();
}


void MainWindow::on_LE_luck_textChanged(const QString &)//расцветка удачи в LE and LAB
{
    int race_indx=ui->CB_race->currentIndex();
    int val=ui->LE_luck->text().toInt();
    //флаг не нужен тк при ошибке в val будет 0
    QPalette pal,lap;
    pal=ui->LE_luck->palette();
    lap=ui->LAB_luck->palette();
    if ((val<mas_luck[race_indx][0])||(val>mas_luck[race_indx][1]))
    {
        pal.setColor(QPalette::Text, Qt::red);
        lap.setColor(QPalette::WindowText, Qt::black);
    }
    else
    {
        pal.setColor(QPalette::Text, Qt::green);
        if ((val>=1)and(val<=3))
        {
            lap.setColor(QPalette::WindowText, Qt::red);
        }
        if ((val>=4)and(val<=7))
        {
            lap.setColor(QPalette::WindowText, Qt::yellow);
        }
        if ((val>=8)and(val<=10))
        {
            lap.setColor(QPalette::WindowText, Qt::green);
        }
    }
    ui->LE_luck->setPalette(pal);
    ui->LAB_luck->setPalette(lap);
    score_calc();
}


void MainWindow::on_CB_race_currentTextChanged(const QString &arg1)//проверка и окрашивание вводимых параметров при смене расы
{
    on_LE_int_textChanged(arg1);
    on_LE_lovk_textChanged(arg1);
    on_LE_power_textChanged(arg1);
    on_LE_luck_textChanged(arg1);
    ui->LAB_atkvalue->clear();
    ui->LAB_mpvalue->clear();
    ui->LAB_hpvalue->clear();
    ui->LAB_nicevalue->clear();
    ui->LAB_protectvalue->clear();
    ui->LAB_page->clear();
}

