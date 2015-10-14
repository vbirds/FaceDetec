#ifndef FACERECOGNIZE_H
#define FACERECOGNIZE_H

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
//#include <QApplication>
#include <QString>
#include <QVector>
#include <QDebug>
#include <qdebug.h>
#include <vector>

#include "facedetect.h"

using namespace std;
using namespace cv;


class facerecognize
{
public:
    facerecognize();
    ~facerecognize();

    /*使用CSV文件去读图像和标签，主要使用stringstream和getline方法*/
    static void read_csv(const String& filename, vector<Mat>& images,
                         vector<int>& labels, char separator =';')
    {

        std::ifstream file(filename.c_str(), ifstream::in);
           if (!file) {
               string error_message ="No valid input file was given, please check the given filename.";
               CV_Error(CV_StsBadArg, error_message);
           }
           string line, path, classlabel;
           while (getline(file, line)) {
               stringstream liness(line);
               getline(liness, path, separator);
               getline(liness, classlabel);
               if(!path.empty()&&!classlabel.empty()) {
                   images.push_back(imread(path, 0));
                   labels.push_back(atoi(classlabel.c_str()));
               }
           }
    }


    /*训练函数*/
    int Learn();

    /*载入训练文件函数*/
    void LoadTrainFile();

    /*图像识别*/
    void PhotoRecognize(QString imagepath, std::vector<int> &numlist);

    /*摄像识别*/
    void VideoRecognize(int id);

    /*设置训练文件输出路径函数*/
    void SetOutputFile(QString filepath);

    /*设置训练好的xml文件的路径函数*/
    void SetTrainxmlFile(QString filepath);

    /*设置csv文件路径函数*/
    void SetCsvFile(QString filepath);

    /* 设置标准图像大小函数*/
    void SetWidthAndHeight();

    /* 设置标准图像大小函数*/
    void SetWidthAndHeight(int width, int height);

    /*清理释放内存函数*/
    void Clear();

private:

    /*初始化函数*/
    void InitFunc();

    /*核心清理释放内存函数*/
    void RealClear();

    /*核心 识别函数 返回识别出的标签号*/
    std::vector<int> Recognize(cv::Mat &image, std::vector<cv::Rect> &faces);

    /*训练文件输出路径*/
    QString output_folder;

    /*训练好的xml文件的路径*/
    QString trainxmlfile;

    /*csv文件路径*/
    QString csv_file;

    /*存储图像数据*/
    std::vector<cv::Mat> images;

    /*存储图像对应的标签*/
    std::vector<int> labels;

    /*识别类*/
    Ptr<FaceRecognizer> model;

    /*人脸检测类*/
    facedetect   *faceDetec;

    /*存放视频识别的识别信息列表*/
    std::vector<int> numlist;

    /* 标准图像大小*/
    int im_width;
    int im_height;

    /*训练文件特征数值*/
    int value;

    /*摄像头标识符*/
    int driverId;

    /*载入训练文件标识符*/
    bool loaded;

    /*readcsv 标识符*/
    bool readcsved;
};

#endif // FACERECOGNIZE_H
