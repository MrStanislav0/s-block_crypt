#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>
#include <cmath>

#include "QStandardItemModel"
#include "QStandardItem"
#include <QTimer>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windows.h"

using namespace std;

#include "fun.h" // Все остальные функции
#include "Sfiles.h"// Работа с файлами

polynom pol1; // x^49 + x^22 + 1
polynom pol2; // x^142 + x^21 + 1

int n = 0;
int m = 0;
int j = 0;

string text; // Исходный текст
string new_text; // Зашифрованный текст
string login_std; // Логин
vector <pair_text> pair2;

 vector <string> key;
 map <string, string> s_box;
 map <int, int> p_box; // Генерация p-блока (таблицы перестановки)
 vector <string> hs; // Разбиение текста на блоки
 map <string, map<string, int> > Table_analysis; //подсчет C исходя из dif
 string delta_std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Криптоанализ SPN");

    ui->progressBar->hide();
    ui->len_key->hide();
    ui->zna4_key->hide();
    ui->checkBox->hide();

    connect(ui->Generate, SIGNAL(clicked()), this, SLOT(Generate_s_p()));
    //connect(ui->import_OK, SIGNAL(clicked()), this, SLOT(Import()));
    //connect(ui->export_OK, SIGNAL(clicked()), this, SLOT(Export()));

    connect(ui->key_button, SIGNAL(clicked()), this, SLOT(Check_key()));
    connect(ui->Give_button, SIGNAL(clicked()), this, SLOT(Give_text()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(Analys()));

    connect(ui->import_OK, SIGNAL(clicked()), this, SLOT(Im2()));
    connect(ui->export_OK, SIGNAL(clicked()), this, SLOT(Ex2()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Generate_s_p()
{

    //std::string str = "Hello world";

    //QString Source_text = QString::fromStdString(str);

    //ui->textEdit->setText(Source_text);

   // ui->pushButton->setText(finalStr); // задаем имя кнопки равным финальной строке


    QString login_name = ui->login->text();
    login_std = login_name.toStdString();

    bool ok1, ok2, ok3;

    n = ui->n->text().toInt(&ok1);
    m = ui->m->text().toInt(&ok2);
    j = ui->j->text().toInt(&ok3);


    if ((!ok1) || (!ok2) || (!ok3))
    {
        ui->err_dan->setText("Введены некорректные значения!");
        n = 0;
        m = 0;
        j = 0;

        return;
    }

    if ((m <= 0) || (n <= 0) || (j <= 0) || login_name.isEmpty() || !(check_login(login_std)))
    {
        ui->err_dan->setText("Введены некорректные значения!");
        return;
    }

    ui->err_dan->setText("");
    long long int int_login = Int_login(login_std);

    srand(int_login);

    pol1 = generate_polynom(49, 22, 0); // x^49 + x^22 + 1
    pol2 = generate_polynom(142, 21, 0); // x^142 + x^21 + 1

    s_box = generate_sbox(m); // Генерация s-блока (таблицы замены)
    p_box = generate_pbox(n, m); // Генерация p-блока (таблицы перестановки)
    key = generate_key(n*m, 1); // Генерация ключа

    QString len_key = QString::number(m*n);
    ui->len_key->show();
    ui->zna4_key->show();
    ui->zna4_key->setText(len_key);


    /*
    string key_now;
    for (int i = 0; i < (int) key.size(); i++)
    {
        key_now = key_now + key[i];
    }

    QString keyy = QString::fromStdString(key_now);
    ui->label_16->setText(keyy);



    QString Source_text = QString::fromStdString(text);
    ui->textEdit->setText(Source_text);

    QString Shifr_text = QString::fromStdString(new_text);
    ui->textEdit_2->setText(Shifr_text);

    ui->tableWidget->show();

*/

    ui->pbox->setRowCount(n*m);

    int c = 0;

    map <int, int> ::iterator it;
    for (it = p_box.begin(); it != p_box.end(); it++)
    {
        QString s1 = QString::number((*it).first+1);
        QString s2 = QString::number((*it).second+1);

        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(s1);
        ui->pbox->setItem(c,0,item1);

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(s2);
        ui->pbox->setItem(c,1,item2);

        c++;
    }

    ui->pbox->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->pbox->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    int count1 = pow(2.0, m);
    ui->sbox->setRowCount(count1);

     c = 0;

    map <string, string> ::iterator it2;
    for (it2 = s_box.begin(); it2 != s_box.end(); it2++)
    {
        QString s1 = QString::fromStdString((*it2).first);
        QString s2 = QString::fromStdString((*it2).second);

        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(s1);
        ui->sbox->setItem(c,0,item1);

        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(s2);
        ui->sbox->setItem(c,1,item2);

        c++;
    }

    ui->sbox->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->sbox->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

}

void MainWindow::Analys()
{

    if ((m <= 0) || (n <= 0) || (j <= 0))
    {
        ui->err4->setText("S-блок, P-блок и ключ не были сгенерированы!");
        return;
    }

    ui->err4->setText("");

    ui->tableWidget_4->setRowCount((int) pow(2.0, (double) m));
    ui->tableWidget_4->setColumnCount((int) pow(2.0, (double) m));

    Table_analysis = Analyse_Tabl_generate(s_box, m); // Таблица анализа блока замены


    int cikl = (int)pow(2.0, (double)m);

    for (int l2 = 0; l2 < cikl; l2++)
    {
        string temp1 = Int_to_BitStr(l2, m);
        QString s1 = QString::fromStdString(temp1);
        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(s1);
         ui->tableWidget_4->setHorizontalHeaderItem(l2, item1);

        for (int l = 0; l < cikl; l++)
        {

            string temp2 = Int_to_BitStr(l, m);
            QString s2 = QString::fromStdString(temp2);
            QTableWidgetItem *item2 = new QTableWidgetItem();
            item2->setText(s2);

            ui->tableWidget_4->setVerticalHeaderItem(l, item2);


            QString s3 = QString::number(Table_analysis[temp1][temp2]);


            QTableWidgetItem *item3 = new QTableWidgetItem();
            item3->setText(s3);
            ui->tableWidget_4->setItem(l2,l,item3);

        }

    }

    for (int l2 = 0; l2 < cikl; l2++)
    {
        ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(l2, QHeaderView::Stretch);
    }

}

void MainWindow::Im2()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Выбрать"),
                                QDir::currentPath(),
                                "Text File (*.txt);;All files (*.*)");



    ui->file_import->setText(fileName);

    QString name = fileName;
    if (!(name.isEmpty()))
    {
        string name_std = name.toStdString();

        if(Is_file(name_std))
        {
            data_file data = inpute_file_full(name_std);
            m = data.m;
            n = data.n;
            j = data.j;
            login_std = data.login;

            if ((m <= 0) || (n <= 0) || (j <= 0) || !(check_login(login_std)))
            {
                ui->error1->setText("Введены некорректные значения!");
                m = 0;
                n = 0;
                j = 0;
                login_std = "";

                return;
            }

            ui->error1->setText("");

            long long int int_login = Int_login(login_std);

            srand(int_login);

            pol1 = generate_polynom(49, 22, 0); // x^49 + x^22 + 1
            pol2 = generate_polynom(142, 21, 0); // x^142 + x^21 + 1

            s_box = generate_sbox(m); // Генерация s-блока (таблицы замены)
            p_box = generate_pbox(n, m); // Генерация p-блока (таблицы перестановки)
            key = generate_key(n*m, j); // Генерация ключа


            QString Login_text = QString::fromStdString(login_std);
            ui->login->setText(Login_text);

            QString m2 = QString::number(m);
            QString n2 = QString::number(n);
            QString j2 = QString::number(j);


            ui->m->setText(m2);
            ui->n->setText(n2);
            ui->j->setText(j2);

            QString len_key = QString::number(m*n*j);
            ui->len_key->show();
            ui->zna4_key->show();
             ui->zna4_key->setText(len_key);


            // вывод s p блоков

            ui->pbox->setRowCount(n*m);

             int c = 0;

            map <int, int> ::iterator it;
            for (it = p_box.begin(); it != p_box.end(); it++)
            {
                QString s1 = QString::number((*it).first+1);
                QString s2 = QString::number((*it).second+1);

                QTableWidgetItem *item1 = new QTableWidgetItem();
                item1->setText(s1);
                ui->pbox->setItem(c,0,item1);

                QTableWidgetItem *item2 = new QTableWidgetItem();
                item2->setText(s2);
                ui->pbox->setItem(c,1,item2);

                c++;
            }

            ui->pbox->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
            ui->pbox->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

            ui->sbox->setRowCount((int) pow(2.0, (double) m));

             c = 0;

            map <string, string> ::iterator it2;
            for (it2 = s_box.begin(); it2 != s_box.end(); it2++)
            {
                QString s1 = QString::fromStdString((*it2).first);
                QString s2 = QString::fromStdString((*it2).second);

                QTableWidgetItem *item1 = new QTableWidgetItem();
                item1->setText(s1);
                ui->sbox->setItem(c,0,item1);

                QTableWidgetItem *item2 = new QTableWidgetItem();
                item2->setText(s2);
                ui->sbox->setItem(c,1,item2);

                c++;
            }

            ui->sbox->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
            ui->sbox->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

            QString err1 = QString::fromStdString("");

            ui->error1->setText(err1);
        }
        else
        {
            QString err1 = QString::fromStdString("Файл не найден!");

            ui->error1->setText(err1);
        }
    }
    else
    {
        QString err1 = QString::fromStdString("Введите полный путь к файлу!");

        ui->error1->setText(err1);
    }
}

void MainWindow::Give_text()
{

    if ((m == 0) || (n == 0) || (j ==0) || (login_std == ""))
    {
        ui->err3->setText("S-блок, P-блок и ключ не были сгенерированы!");
        return;
    }

    QString delta = ui->deltaA->text();

    bool ok;
    int kolvo_int = ui->kol_text->text().toInt(&ok);
    delta_std = delta.toStdString();

    if ((!ok) || delta.isEmpty() || !(check_delta(delta_std, m, n)))
    {
        ui->err3->setText("Введены некорректные значения!");
        return;
    }

    if (kolvo_int <= 0)
    {
        ui->err3->setText("Введены некорректные значения!");
        return;
    }

    if (kolvo_int > pow(2.0, m*n))
    {
        ui->err3->setText("Введены некорректные значения!");
        return;
    }


    ui->err3->setText("");

    pair2 = create_pair(kolvo_int, n, m, j, key, s_box, p_box, delta_std);

    //вывод
     ui->xy->setRowCount(kolvo_int);

    ui->checkBox->show();

     for (int f = 0; f < kolvo_int; f++)
     {
         QString s0 = QString::number(f+1);
         QTableWidgetItem *item0 = new QTableWidgetItem();
         item0->setText(s0);
         ui->xy->setItem(f,0,item0);

         QString s1 = QString::fromStdString(pair2[f].x);
         QString s2 = QString::fromStdString(pair2[f].y);

         QTableWidgetItem *item1 = new QTableWidgetItem();
         item1->setText(s1);
         ui->xy->setItem(f,1,item1);

         QTableWidgetItem *item2 = new QTableWidgetItem();
         item2->setText(s2);
         ui->xy->setItem(f,2,item2);


     }
     ui->xy->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
     ui->xy->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
     ui->xy->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);


     // 2 tabl
     ui->xyc->setRowCount(kolvo_int);

     for (int f = 0; f < kolvo_int; f++)
     {
         QString s0 = QString::number(f+1);
         QTableWidgetItem *item0 = new QTableWidgetItem();
         item0->setText(s0);
         ui->xyc->setItem(f,0,item0);

         QString s1 = QString::fromStdString(pair2[f].x_);
         QString s2 = QString::fromStdString(pair2[f].y_);
         QString s3 = QString::fromStdString(pair2[f].C);

         QTableWidgetItem *item1 = new QTableWidgetItem();
         item1->setText(s1);
         ui->xyc->setItem(f,1,item1);

         QTableWidgetItem *item2 = new QTableWidgetItem();
         item2->setText(s2);
         ui->xyc->setItem(f,2,item2);

         QTableWidgetItem *item3 = new QTableWidgetItem();
         item3->setText(s3);
         ui->xyc->setItem(f,3,item3);

     }

     ui->xyc->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
     ui->xyc->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
     ui->xyc->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
     ui->xyc->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

}

void MainWindow::Check_key()
{
    QString key_2 = ui->key->text();
    if (!(key_2.isEmpty()))
    {
        if ((int) key.size() == 0)
        {
            ui->label_key->setText("Ключ не был сгенерирован!");
            return;
        }

        QString err1 = QString::fromStdString("");

        ui->label_key->setText(err1);

        ui->progressBar->show();

        int ms = 300;


        ui->key_button->hide();

        for (int i = 0; i < 100; i++)
        {
            QEventLoop loop;
            QTimer::singleShot(ms, &loop, SLOT(quit()));
            loop.exec();
            loop.exit();
            ui->progressBar->setValue(i+1);
        }

         ui->progressBar->hide();
        ui->progressBar->setValue(0);

        string key_check = key_2.toStdString();

        string key_now;



        for (int i = 0; i < (int) key.size(); i++)
        {
            key_now = key_now + key[i];
        }


        if (key_check == key_now)
        {
            QString err1 = QString::fromStdString("Ключ введен правильный!");

            ui->label_key->setText(err1);
        }
        else
        {
            QString err1 = QString::fromStdString("Ключ введен неверный!");

            ui->label_key->setText(err1);
        }
        ui->key_button->show();
    }
    else
    {
        QString err1 = QString::fromStdString("Поле не заполнено");

        ui->label_key->setText(err1);
    }
}

void MainWindow::Ex2()
{

        if (!((m == 0) || (n == 0) || (j ==0) || (login_std == "")))
        {

            QString fileName = QFileDialog::getSaveFileName(this,
                                        QString::fromUtf8("Выбрать"),
                                        QDir::currentPath(),
                                        "Text File (*.txt);;All files (*.*)");

            QString name = fileName;
            if (!(name.isEmpty()))
            {

                string name_std = name.toStdString();

                outpute_file_full(name_std, login_std, m, n, j, s_box, p_box);

                if(ui->checkBox->isChecked())
                {
                    outpute_deltaA(name_std, pair2, delta_std, 2);
                }

                QString err1 = QString::fromStdString("Данные успешно сохранены в файл!");

                ui->error1->setText(err1);

            }

            ui->file_export->setText(fileName);
        }
        else
        {
            QString err1 = QString::fromStdString("Выводить в файл нечего");

            ui->error1->setText(err1);
        }

}
