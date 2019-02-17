#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QDir>
#include<QFileDialog>
#include<QDebug>
#include<QGraphicsPixmapItem>
#include<QDebug>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QProcess>
#include<QMessageBox>
#include <QKeyEvent>
#include "keypress.h"
int a=0;
QString file,uzanti,translated,returned,original;
 QStringList images;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


   file = QFileDialog::getExistingDirectory(this, "Open file");


    fotodegis(a);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnnext_clicked()
{

    if(a>images.length()-1)
    {
        QMessageBox *msgBox = new QMessageBox(this);
            msgBox->setText("Sona Ulasildi");
            a--;
    }
    else
    {
        a++;
        fotodegis(a);
    }


}
void MainWindow::fotodegis(int index){

    QDir directory(file);

     images = directory.entryList(QStringList() << "*.jpg" << "*.JPG"<< "*.PNG"<< "*.png",QDir::Files);
    uzanti=file+"\\"+images.at(index);

    QPixmap pic(uzanti);
    qDebug()<<uzanti;
    ui->photo->setPixmap(pic);
    ui->photo->setScaledContents(true);
}

void MainWindow::on_btnprev_clicked()
{
    if(a==0){
        fotodegis(0);
    }
    else{
        a--;
     fotodegis(a);
    }

}

void MainWindow::on_btnfolder_clicked()
{
    file = QFileDialog::getExistingDirectory(this, "Open file");
    a=0;
    fotodegis(a);
}

void MainWindow::on_pushButton_clicked()
{

    QProcess process;
    QString scriptFile =  "C:\\Users\\Kerem\\Documents\\PhotoViewer\\metin.py";

    QString pythonCommand = "python " + scriptFile + " --r " + uzanti;





    process.start(pythonCommand);
    process.execute(pythonCommand);



    process.waitForFinished();
   // returned=process.readAllStandardOutput();
    returned=process.readAll();
    returned.trimmed();
    QStringList pieces = returned.split("*****" );
    original=pieces[0];
    translated=pieces[1];

    ui->translate_original->setText(original);
    ui->translate_translated->setText(translated);


}
