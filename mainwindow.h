#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QVector"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<int> vec;
    int numberSize = 50000;

private slots:
    void on_creatNumber_clicked();

    void on_quickSort_clicked();

    void on_bubbleSort_clicked();

    void on_shellSort_clicked();

    void on_heapSort_clicked();

    void on_radixSort_clicked();

    void on_allSort_clicked();

private:
    void bubbleSort(QVector<int>& bubbleVec );
    void quickSort(QVector<int>* ,int ,int );
    void shellSort  (QVector<int>& shellVec);
    void heapSort   (QVector<int>& heapVec);
    void radixSort  (QVector<int>& radixVec);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
