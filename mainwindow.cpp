#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QTime"
#include "QDebug"
#include "algorithm"
#include "QInputDialog"
#include "QMessageBox"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->allTime->append("数据处理产生的卡顿，不算入算法耗时\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_creatNumber_clicked()
{
//    numberSize = QInputDialog::getInt(this,"生成数量：","数量",numberSize);
    qsrand(196003408);
    QTime time;
    time.start();
    ui->currentTime->setText("");
    ui->unsortEdit->setText("");
    if(vec.isEmpty()){
        qDebug() << "vec is empty,create new";
        vec = QVector<int>(numberSize);

    }else qDebug() << "vector is not empty,overwrite vector";

    for (int i =0;i<numberSize;i++) {
        vec[i] = rand();
        ui->unsortEdit->append(QString::number(vec[i]));
    }
    ui->currentTime->setText("生成耗时:"+QString::number(time.elapsed()));
    ui->allTime->append("生成耗时:"+QString::number(time.elapsed()));

}

void MainWindow::on_bubbleSort_clicked()
{
    if(vec.isEmpty()){
        QMessageBox::warning(this,"No data Waning","Creat data first,and then sort");
        return ;
    }

    QVector<int> bubbleVec(vec);

    QTime time;
    time.start();
    ui->currentTime->setText("");
    ui->sortedEdit->setText("");

    bubbleSort(bubbleVec);

    ui->currentTime->setText("冒泡耗时:"+QString::number(time.elapsed()));
    ui->allTime->append("冒泡耗时:"+QString::number(time.elapsed()));
    for (int i = 0;i<numberSize;i++)
        ui->sortedEdit->append(QString::number(bubbleVec[i]))  ;

}


void MainWindow::bubbleSort(QVector<int>& vec)
{

    int temp;
    for(QVector<int>::Iterator i = vec.begin();i != vec.end();i++){
        for(QVector<int>::Iterator j = i;j!=vec.end();j++){
            if(*i > *j){
                temp = *i;
                *i  = *j;
                *j = temp;
            }
        }
    }
}

void MainWindow::on_quickSort_clicked()
{
    if(vec.isEmpty()){
        QMessageBox::warning(this,"No data Waning","Creat data first,and then sort");
        return ;
    }
    QVector<int> qstVec(vec);
    QTime time;
    time.start();
    ui->currentTime->setText("");
    ui->sortedEdit->setText("");

    quickSort(&qstVec,0,qstVec.size()-1);

    ui->currentTime->setText("快排耗时:"+QString::number(time.elapsed()));
    ui->allTime->append("快排耗时:"+QString::number(time.elapsed()));
    for (int i = 0;i<numberSize;i++)
        ui->sortedEdit->append(QString::number(qstVec[i]))  ;
}

void MainWindow::quickSort(QVector<int>* s,int l,int r)
{

//    qDebug() << "quickSort:" << l << r << s->size();

    int i,j,x;
    if(l<r){
        i = l;
        j = r;
        x = s->at(i);

        while(i < j){
            while(i < j && s->at(j) > x)    j--;
            if(i<j) s->replace(i++,s->at(j));
            while(i < j && s->at(i) < x)    i++;
            if(i<j) s->replace(j--,s->at(i));
        }
        s->replace(i,x);
        quickSort(s,l,i-1);
        quickSort(s,i+1,r);

    }


}

void MainWindow::shellSort(QVector<int> &a)
{
    int gap;
    for (gap = 0; gap < a.size() / 4; gap = gap * 2 + 1); // 根据a的尺寸获得增量序列的最大值
    for (; gap > 0; gap = (gap - 1) / 2)
    {
        for (int i = gap; i < a.size(); ++i)
        {
            int tmp = a[i]; // 临时存储待寻找位置的值（因为每一趟相当于一次插入排序）
            int j = i;
            for (; j >= gap && tmp < a[j - gap]; j -= gap)
                a[j] = a[j - gap];
            a[j] = tmp;
        }
    }
}

void MainWindow::on_shellSort_clicked()
{
    if(vec.isEmpty()){
        QMessageBox::warning(this,"No data Waning","Creat data first,and then sort");
        return ;
    }
    QVector<int> shellVec(vec);
    QTime time;
    time.start();
    ui->currentTime->setText("");
    ui->sortedEdit->setText("");

    shellSort(shellVec);

    ui->currentTime->setText("希尔耗时:"+QString::number(time.elapsed()));
    ui->allTime->append("希尔耗时:"+QString::number(time.elapsed()));
    for (int i = 0;i<numberSize;i++)
        ui->sortedEdit->append(QString::number(shellVec[i]))  ;

}

void MainWindow::on_heapSort_clicked()
{
    if(vec.isEmpty()){
        QMessageBox::warning(this,"No data Waning","Creat data first,and then sort");
        return ;
    }
    QVector<int> heapVec(vec);
    QTime time;
    time.start();
    ui->currentTime->setText("");
    ui->sortedEdit->setText("");

    heapSort(heapVec);

    ui->currentTime->setText("堆排耗时:"+QString::number(time.elapsed()));
    ui->allTime->append("堆排耗时:"+QString::number(time.elapsed()));
    for (int i = 0;i<numberSize;i++)
        ui->sortedEdit->append(QString::number(heapVec[i]))  ;
}

inline void swap(QVector<int>& vec,int idx1,int idx2){
    int t = vec[idx1];
    vec[idx1] = vec[idx2];
    vec[idx2] = t;

}
void heapMake(QVector<int> &vec,int len,int index){
    int left = 2*index + 1;
    int right= 2*index + 2;
    int maxIdx = index;
    if(left < len && vec.at(left) > vec.at(maxIdx))
        maxIdx = left ;
    if(right < len && vec.at(right) > vec.at(maxIdx))
        maxIdx = right ;
    if(maxIdx != index){
        swap(vec,maxIdx,index);
        heapMake(vec,len,maxIdx);
    }

}
void MainWindow::heapSort(QVector<int> &heapVec)
{

    for (int i = heapVec.size()/2 - 1;i>=0;i--) {
        heapMake(heapVec,heapVec.size(),i);
    }
    for (int i = heapVec.size()-1;i >=1;i--) {
        swap(heapVec,0,i);
        heapMake(heapVec,i,0);
    }
}
 //辅助函数，求数据的最大位数
int maxBit(QVector<int> vec){
    int max = vec[0];
    for(int i = 1;i<vec.size();i++){
        max = max<vec[i] ? vec[i] : max;
    }
    int d = 1;
    int p = 10;
    while(max >= p){
        max/=10;
        ++d;
    }
    return d;
}
void MainWindow::radixSort(QVector<int> &radixVec)
{
    int d = maxBit(radixVec);
    QVector<int> tmp(radixVec.size());
    QVector<int> count(10,0);
    int k ;
    int radix = 1;
    for (int i =1;i<d;i++) {
        for(int j =0 ;j<10;j++){
            count[j] = 0;
        }
        for(int j =0;j<radixVec.size();j++){
           k = (radixVec[j] / radix) % 10;
           count[k] ++;
        }
        for(int j =1;j<10;j++){
            count[j] = count[j-1] + count[j];
        }
        for(int j = radixVec.size()-1;j >=0;j--){
            k = (radixVec[j]/radix)%10;
            tmp[count[k]-1] = radixVec[j];
            count[k] --;
        }
        for(int j = 0;j<radixVec.size();j++){
            radixVec[j] = tmp[j];
        }
        radix = radix*10;
    }
}

void MainWindow::on_radixSort_clicked()
{
    if(vec.isEmpty()){
        QMessageBox::warning(this,"No data Waning","Creat data first,and then sort");
        return ;
    }
    QVector<int> radixVec(vec);
    QTime time;
    time.start();
    ui->currentTime->setText("");
    ui->sortedEdit->setText("");

    radixSort(radixVec);

    ui->currentTime->setText("基数耗时:"+QString::number(time.elapsed()));
    ui->allTime->append("基数耗时:"+QString::number(time.elapsed()));
    for (int i = 0;i<numberSize;i++)
        ui->sortedEdit->append(QString::number(radixVec[i]))  ;
}

void MainWindow::on_allSort_clicked()
{
    if(vec.isEmpty()){
        QMessageBox::warning(this,"No data Waning","Creat data first,and then sort");
        return ;
    }
    QVector<QVector<int> > allSortVecs(5,QVector<int>(vec));


    ui->currentTime->setText("");
    ui->sortedEdit->setText("");

    QTime time;
    time.start();

    QTime timeLite;
    timeLite.start();

    bubbleSort(allSortVecs[0]);
    ui->currentTime->setText("冒泡耗时:"+QString::number(timeLite.elapsed()));
    ui->allTime->append("冒泡耗时:"+QString::number(timeLite.elapsed()));

    timeLite.restart();
    quickSort(&allSortVecs[1],0,allSortVecs[1].size()-1);
    ui->currentTime->setText("快排耗时:"+QString::number(timeLite.elapsed()));
    ui->allTime->append("快排耗时:"+QString::number(timeLite.elapsed()));

    timeLite.restart();
    shellSort(allSortVecs[2]);
    ui->currentTime->setText("希尔耗时:"+QString::number(timeLite.elapsed()));
    ui->allTime->append("希尔耗时:"+QString::number(timeLite.elapsed()));

    timeLite.restart();
    heapSort(allSortVecs[3]);
    ui->currentTime->setText("堆排耗时:"+QString::number(timeLite.elapsed()));
    ui->allTime->append("堆排耗时:"+QString::number(timeLite.elapsed()));
    timeLite.restart();
    radixSort(allSortVecs[4]);
    ui->currentTime->setText("基数耗时:"+QString::number(timeLite.elapsed()));
    ui->allTime->append("基数耗时:"+QString::number(timeLite.elapsed()));

    ui->currentTime->setText("总耗时:"+QString::number(time.elapsed()));
    ui->allTime->append("总耗时:"+QString::number(time.elapsed()));
}
