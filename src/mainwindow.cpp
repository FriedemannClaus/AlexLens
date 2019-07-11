#include "../includes/mainwindow.h"
#include "../includes/ui_mainwindow.h"
#include<iostream>
#include<unistd.h>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    /*QString imagePath = QFileDialog::getOpenFileName(
                        this,
                        tr("Choose"),
                        "",
                        tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
                        );

    QImage imageObject;
    imageObject.load(imagePath);
    imageObject = imageObject.scaledToWidth(ui->myLabel->width());
    image = QPixmap::fromImage(imageObject);
    ui->myLabel->setPixmap(image);*/

    std::cout << "im here";
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    //ui->graphicsView->setScene(scene);

}
