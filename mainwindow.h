#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <vector>

#include "facedetect.h"
#include "facerecognize.h"

using namespace std;

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
    void PhotoDetec();
    void VideoDetec();

    void Train();
    void PhotoRecognize();

private:
    Ui::MainWindow *ui;
    facedetect   *faceDet;
    facerecognize *recognize;




};

#endif // MAINWINDOW_H
