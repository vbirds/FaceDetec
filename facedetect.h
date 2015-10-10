#ifndef FACEDETECT_H
#define FACEDETECT_H

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
//#include <QApplication>
#include <QString>
#include <QVector>
#include <QDebug>
#include <qdebug.h>
#include <vector>

using namespace std;
using namespace cv;

class facedetect
{
public:
    facedetect();
    ~facedetect();

    /*图像检测*/
    void PhotoDetec(QString ImagePath);

    /*摄像检测*/
    void VideoDetec(int deviceId = 0);

    /*设置分类器训练文件*/
    void SetFace_cascade_file(QString filename);

    /*设置分类器*/
    void SetFace_cascade(QString filename);

    /*获取人脸数*/
    int GetFaceCount();

    /*标记人脸 给用户提供的接口*/
    void DrawFace();

private:
    /*核心检测（真正的检测函数）*/
    std::vector<cv::Rect> BaseDetec(Mat srcImage);

    /*真标记人脸*/
    void RealDrawFace(Mat image, std::vector<cv::Rect> fRects);

    /*人脸坐标*/
    std::vector<cv::Rect> faceRects;

    /* 分类器训练文件*/
    QString           face_cascade_file;

    /*分类器*/
    CascadeClassifier face_cascade;

    /*图片位置*/
    QString imagePath;

    /*人脸数*/
    int faceCount;

    /*源图像*/
    Mat imageSrc;

};

#endif // FACEDETECT_H
