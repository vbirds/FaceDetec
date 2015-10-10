#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->faceDet = new facedetect();

    QObject::connect(ui->PhotoDet_action, SIGNAL(triggered()), this, SLOT(PhotoDetec()));
    QObject::connect(ui->Video_action, SIGNAL(triggered()), this, SLOT(VideoDetec()));
}

MainWindow::~MainWindow()
{
    delete ui;

    if(this->faceDet)
    {
        delete this->faceDet;
    }


}

void MainWindow::PhotoDetec()
{
    QString filepath = QFileDialog::getOpenFileName(this,tr("Open File"),
                                                    QDir::currentPath(),
                                                    tr("Image Files (*.png *.jpg *.bmp)")
                                                    );
    if(this->faceDet)
    {
        faceDet->PhotoDetec(filepath);
        this->faceDet->DrawFace();
    }
}

void MainWindow::VideoDetec()
{
    facedetect *fac = new facedetect();

    if(fac)
    {
        fac->VideoDetec(0);
    }

    delete fac;
    fac = NULL;
}
