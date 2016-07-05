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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void Generate_s_p();

    void Give_text();
    void Analys();
    void Check_key();

    void Im2();
    void Ex2();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
