#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->faceDet = new facedetect();
    this->recognize = new facerecognize();

    QObject::connect(ui->PhotoDet_action, SIGNAL(triggered()), this, SLOT(PhotoDetec()));
    QObject::connect(ui->Video_action, SIGNAL(triggered()), this, SLOT(VideoDetec()));
    QObject::connect(ui->Train_action, SIGNAL(triggered()), this, SLOT(Train()));
    QObject::connect(ui->Recog_action, SIGNAL(triggered()), this, SLOT(PhotoRecognize()));
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
                                                    tr("Image Files (*.png *.jpg *.bmp *.pgm)")
                                                    );
    if(this->faceDet)
    {
        faceDet->PhotoDetec(filepath);
        qDebug() <<"People nums: "<< this->faceDet->GetFaceCount();
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

void MainWindow::Train()
{
    int ret;
    ret = this->recognize->Learn();

    if(ret == 0)
    {
        QMessageBox::information(NULL,"Informaition", "Train Succcess");
    }
    else
    {
        QMessageBox::information(NULL,"Informaition", "Train failed");
    }
}

void MainWindow::PhotoRecognize()
{
    QString photopath = QFileDialog::getOpenFileName(this,tr("Open File"),
                                                     QDir::currentPath(),
                                                     tr("Image Files (*.png *.jpg *.bmp *.pgm)")
                                                     );
    std::vector<int>  nums;

    this->recognize->PhotoRecognize(photopath, nums);
}
