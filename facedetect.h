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

    /*图像检测*/
    void PhotoDetec(Mat image, std::vector<cv::Rect> &rect);

    /*摄像检测*/
    void VideoDetec(int deviceId = 0);

    /*设置分类器训练文件*/
    void SetFace_cascade_file(QString filename);

    /*设置分类器*/
    void SetFace_cascade(QString filename);

    /*获取人脸数*/
    int GetFaceCount();

    /*设置缩放比(初始化时默认已经赋值1.2)*/
    void SetScale(int value);

    /*获取缩放比值*/
    int GetScale();

    /*获取人脸坐标函数*/
    std::vector<cv::Rect> GetRects();

    /*获取源图像函数*/
    cv::Mat GetSrcMat();

    /*标记人脸(照片图像) 给用户提供的接口*/
    void DrawFace();

    /*标记人脸(摄像头) 给用户提供的接口*/
    void VideoDrawFace(Mat &image, std::vector<Rect> &fRects);

    /*清理释放内存函数*/
    void Clear();



private:
    /*核心检测（真正的检测函数）*/
    std::vector<cv::Rect> BaseDetec(Mat srcImage);

    /*真标记人脸(照片图像)*/
    void RealDrawFace(Mat image, std::vector<cv::Rect> fRects);


    /*初始化函数*/
    void InitFunc();

    /*核心清理释放内存函数*/
    void RealClear();

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

    /*缩放比*/
    int scale;

    /*摄像停止标识*/
    bool stop;

};

#endif // FACEDETECT_H
