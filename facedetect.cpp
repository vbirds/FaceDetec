#include "facedetect.h"

facedetect::facedetect()
{
    /*初始化*/
    this->InitFunc();
}

facedetect::~facedetect()
{
    /*清理释放内存*/
    this->Clear();
}


/********************************
 *   初始化函数
 *******************************/
void facedetect::InitFunc()
{
    this->face_cascade_file = "./haarcascade_frontalface_alt.xml";
    this->face_cascade.load((this->face_cascade_file).toStdString());
    this->faceRects.clear();
    this->faceCount = 0;
    /*设置缩放比*/
    this->scale = 1.2;
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
    /*建立缩小图片,加快检测速度*/
    Mat smallImg(cvRound(srcImage.rows/(this->scale)), cvRound(srcImage.cols/(this->scale)),CV_8UC1);

    /*转成灰度图像*/
    cvtColor(srcImage, frame_gray, CV_BGR2GRAY);

    /*改变图像大小*/
    cv::resize(frame_gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);

    /*直方图均值化处理*/
    equalizeHist(smallImg, smallImg);

    /****************************************
     * 人脸检测 将人脸坐标存入 'faceRects'中
     ***************************************/
    this->face_cascade.detectMultiScale(smallImg, faceRects,
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
    this->imageSrc.release();
    this->imageSrc = image;

    if(!image.data)
    {
        qDebug()<<"func facedetect::PhotoDetec(QString ImagePath) check imread error if(!image.data)";
        return;
    }

    /*调用核心检测函数*/
    this->faceRects.clear();
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
            /*清理缓存*/
            faceRects.clear();
            /*调用核心检测函数*/
            faceRects = this->BaseDetec(frame);

            /*Exit this loop on escape*/
            char key = (char)waitKey(20);
            if(key == 27)
            {
                break;
            }
        }

        /*在清理以前的缓存后再赋值*/
        this->imageSrc.release();
        this->imageSrc = frame;
        this->faceRects.clear();
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
    return this->faceCount;
}

/*******************************
 *   设置缩放比函数(初始化时默认已经赋值1.2)
 *******************************/
void facedetect::SetScale(int value)
{
    if(value <= 0)
    {
        qDebug()<<" func SetScale(int value) please check if(value > 0)";
        return;
    }

    this->scale = value;
}

/*********************************************
 *   获取缩放比值函数(初始化时默认已经赋值1.2)
 *********************************************/
int facedetect::GetScale()
{
    return this->scale;
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
                  cvPoint(cvRound(r->x * (this->scale)), cvRound(r->y)* (this->scale)),
                  cvPoint(cvRound((r->x + r->width-1)* (this->scale)), cvRound((r->y + r->height-1)* (this->scale))),
                  Scalar(0,255,0)
                  );
    }

    cv::imshow("Result", image);
    waitKey(0);
}

/*********************************
 *   清理释放内存函数
 *********************************/
void facedetect::Clear()
{
    /*调用核心内存释放函数*/
    this->RealClear();
}

/*********************************
 *   核心清理释放内存函数
 *********************************/
void facedetect::RealClear()
{

    std::vector<cv::Rect>(this->faceRects).swap(this->faceRects);
    QString(this->face_cascade_file).swap(this->face_cascade_file);
    QString(this->face_cascade_file).swap(this->face_cascade_file);

    this->imageSrc.release();
    this->scale = 0;
    this->faceCount = 0;

}
