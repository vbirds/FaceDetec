#include "facedetect.h"

facedetect::facedetect()
{
    this->face_cascade_file = "./haarcascade_frontalface_alt.xml";
    this->face_cascade.load((this->face_cascade_file).toStdString());
    this->faceRects.clear();
    this->faceCount = 0;
}

facedetect::~facedetect()
{

}

/********************************
 *   核心检测（真正的检测函数）
 *******************************/
std::vector<cv::Rect> facedetect::BaseDetec(Mat srcImage)
{
    int ret = 0;
    std::vector<cv::Rect> faceRects;
    if(!srcImage.data)
    {
        ret = -1;
        qDebug()<< "func facedetect::BaseDetec(Mat srcImage) error  please check !srcImage.data err: " <<ret;
    }

    Mat frame_gray;

    /*转成灰度图像*/
    cvtColor(srcImage, frame_gray, CV_BGR2GRAY);

    /*直方图均值化处理*/
    equalizeHist(frame_gray, frame_gray);

    /****************************************
     * 人脸检测 将人脸坐标存入 'faceRects'中
     ***************************************/
    this->face_cascade.detectMultiScale(frame_gray, faceRects,
                                        1.1, 2, 0|CV_HAAR_SCALE_IMAGE,
                                        Size(20, 20)
                                        );

    return faceRects;
}

/*******************************
 *   图像检测函数
 *******************************/
void facedetect::PhotoDetec(QString ImagePath)
{
    if(ImagePath.isEmpty())
    {
        qDebug()<<"func facedetect::PhotoDetec(QString ImagePath) check ImagePath.isEmpty() ";
        return;
    }
    Mat image = imread(ImagePath.toStdString());
    this->imageSrc = image;

    if(!image.data)
    {
        qDebug()<<"func facedetect::PhotoDetec(QString ImagePath) check imread error if(!image.data)";
        return;
    }

    /*调用核心检测函数*/
    this->faceRects = this->BaseDetec(image);
    return;
}

/*******************************
 *   摄像检测函数
 *******************************/
void facedetect::VideoDetec(int deviceId)
{
    std::vector<cv::Rect> faceRects;

    /*打开摄像头*/
    VideoCapture cap(deviceId);
    if(cap.isOpened())
    {
        Mat frame;
        while(true)
        {
            cap >> frame;

            if(!(this->faceRects).empty())
            {
                (this->faceRects).clear();
            }
            /*建立缩小图片,加快检测速度*/
            Mat smallImg(cvRound(frame.rows/2),cvRound(frame.cols/2),CV_8UC1);

            faceRects.clear();
            faceRects = this->BaseDetec(smallImg);

            /*Exit this loop on escape*/
            char key = (char)waitKey(20);
            if(key == 27)
            {
                break;
            }
        }

        this->videoSrc = frame;
        this->faceRects = faceRects;

    }
    else
    {
         qDebug() << "func facedetect::VideoDetec(int deviceId)  Can Open Cammer!";
         return;
    }
}

/*******************************
 *    设置分类器训练文件函数
 *******************************/
void facedetect::SetFace_cascade_file(QString filename)
{
    if(filename.isEmpty())
    {
        qDebug() << "func facedetect::SetFace_cascade_file() check filename.isEmpty()";
        return;
    }
    this->face_cascade_file = filename;
}

/*******************************
 *   设置分类器函数
 *******************************/
void facedetect::SetFace_cascade(QString filename)
{
    if(filename.isEmpty())
    {
        qDebug() << "func facedetect::SetFace_cascade() check filename.isEmpty()";
        return;
    }
    this->face_cascade.load((this->face_cascade_file).toStdString());
}

/*******************************
 *   获取人脸数函数
 *******************************/
int facedetect::GetFaceCount()
{
    this->faceCount = (this->faceRects).size();
}

/*********************************
 *   标记人脸函数 给用户提供的接口
 *********************************/
void facedetect::DrawFace()
{
   this->RealDrawFace(this->imageSrc, this->faceRects);
}

/*********************************
 *   真标记人脸函数(核心)
 *********************************/
void facedetect::RealDrawFace(Mat image, std::vector<Rect> fRects)
{
    if(!image.data || fRects.empty())
    {
        qDebug()<<"func facedetect::RealDrawFace() check if(!image.data || fRects.empty())";
        return;
    }

    /*标记人脸*/
    for(vector<Rect>::const_iterator r = fRects.begin(); r != fRects.end(); r++)
    {
        rectangle(image,
                  cvPoint(cvRound(r->x), cvRound(r->y)),
                  cvPoint(cvRound((r->x + r->width-1)), cvRound((r->y + r->height-1))),
                  Scalar(0,255,0)
                  );
    }

    cv::imshow("Result", image);
    waitKey(0);
}
