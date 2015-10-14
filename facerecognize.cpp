#include "facerecognize.h"

facerecognize::facerecognize()
{
    /*初始化*/
    this->InitFunc();
}

facerecognize::~facerecognize()
{
    /*清理释放内存*/
    this->Clear();
}



/********************************
 *   初始化函数
 *******************************/
void facerecognize::InitFunc()
{
    this->model =  createFisherFaceRecognizer(10);
    this->faceDetec = new facedetect();

    this->output_folder = "./detection.xml";
    this->trainxmlfile = "./detection.xml";
    this->csv_file = "D:/QtProject/att_faces/at.txt";

    this->SetWidthAndHeight(112, 92);

    this->loaded = false;
    this->readcsved = false;
}

/********************************
 *   设置标准图像大小函数
 *******************************/
void facerecognize::SetWidthAndHeight()
{
    if(this->readcsved == false)
    {
        this->im_width = (this->images)[0].cols;
        this->im_height = (this->images)[0].rows;
    }
}

/********************************
 *   设置标准图像大小函数
 *******************************/
void facerecognize::SetWidthAndHeight(int width, int height)
{
    this->im_width = width;
    this->im_height = height;
}


/********************************
 *   训练函数
 *******************************/
int facerecognize::Learn()
{
    int     ret = 0;
    string csvFile = this->csv_file.toStdString();
    try{
        this->read_csv(csvFile, this->images, this->labels);
        this->readcsved = true;
    } catch(cv::Exception& e) {
        cerr << "Error opening file" << csvFile << ". Reason: "<< e.msg << endl;
        ret = -1;
        /*出现异常 退出*/
        exit(1);
    }

    /*判断有没读取到足够的数据*/
    if(this->images.size() <= 1)
    {
        ret = -2;
        QString error_message ="This demo needs at least 2 images to work.\
           Please add more images to your data set!";
        qDebug() << error_message << ret;
        return ret;
    }

    //this->SetWidthAndHeight();
    /*得到图片大小*/
    this->im_width = (this->images)[0].cols;
    this->im_height = (this->images)[0].rows;

    /*训练和保存训练文件*/
    if(this->model)
    {
        model->train(this->images, this->labels);

        model->save(this->output_folder.toStdString());

        return ret;
    }
    else
    {
        ret = -3;
        qDebug() << "func facerecognize::Learn() check if(this->model)" << ret;
        return ret;
    }
}


/********************************
 *   载入训练文件函数
 *******************************/
void facerecognize::LoadTrainFile()
{
    if(this->model && !(this->loaded))
    {
        this->model->load(this->trainxmlfile.toStdString());
        this->loaded = true;
    }
}

/********************************
 *   图像识别函数
 *******************************/
void facerecognize::PhotoRecognize(QString imagepath, std::vector<int> &numlist)
{
    std::vector<int> list;
    std::vector<cv::Rect> Rects;

    if(imagepath.isEmpty())
    {
        qDebug() << "func facerecognize::PhotoRecognize() check if(imagepath.isEmpty())";
        return;
    }
    if(!numlist.empty())
    {
        qDebug() << "func facerecognize::PhotoRecognize() check if(!numlist.empty())";
        return;
    }

    if(this->model && this->faceDetec)
    {
        this->faceDetec->PhotoDetec(imagepath);
        Rects = (this->faceDetec)->GetRects();
        Mat image = (this->faceDetec)->GetSrcMat();

        /*载入训练文件*/
        this->LoadTrainFile();
        /*调用核心识别函数*/
        list = this->Recognize(image, Rects);
        numlist = list;
    }

}

/********************************
 *  核心 识别函数 返回识别出的标签号
 *******************************/
std::vector<int> facerecognize::Recognize(Mat &image, std::vector<Rect> &faces)
{
    if(image.data && !faces.empty())
    {
        Mat original = image;
        Mat gray;
        std::vector<int>  list;

        cvtColor(original, gray, CV_BGR2GRAY);

        int scaled = this->faceDetec->GetScale();

        /*
          cvPoint(cvRound(r->x * scale), cvRound(r->y)* scale),
          cvPoint(cvRound((r->x + r->width-1)* scale), cvRound((r->y + r->height-1)* scale)),
        */
        for(std::vector<cv::Rect>::const_iterator r=faces.begin(); r != faces.end(); r++)
        {
            /*将缩放的坐标还原*/
            cv::Rect  face_i = Rect((r->x) * scaled, (r->y) * scaled,
                                    (r->width) * scaled, (r->height) *scaled
                                   );

            Mat face = gray(face_i);
            Mat face_resized;
            cv::resize(face, face_resized,
                       Size(this->im_width, this->im_height),
                       0, 0, INTER_LINEAR
                       );

            /*识别*/
            int prediction = this->model->predict(face_resized);
            /*将识别结果压入list*/
            list.push_back(prediction);
        }

        return list;
    }
}

/********************************
 *   设置训练文件输出路径函数
 *******************************/
void facerecognize::SetOutputFile(QString filepath)
{
    if(filepath.isEmpty())
    {
        qDebug()<<"func facerecognize::SetOutputFile() check if(filepath.isEmpty())";
        return;
    }

    this->output_folder = filepath;
}

/********************************
 *   设置训练好的xml文件的路径
 *******************************/
void facerecognize::SetTrainxmlFile(QString filepath)
{
    if(filepath.isEmpty())
    {
        qDebug()<<"func facerecognize::SetTrainxmlFile() check if(filepath.isEmpty())";
        return;
    }

    this->trainxmlfile = filepath;
}

/********************************
 *   设置csv文件路径函数
 *******************************/
void facerecognize::SetCsvFile(QString filepath)
{
    if(filepath.isEmpty())
    {
        qDebug()<<"func facerecognize::SetCsvFile() check if(filepath.isEmpty())";
        return;
    }

    this->csv_file = filepath;
}

/********************************
 *   清理释放内存函数
 *******************************/
void facerecognize::Clear()
{
    /*调用核心清理函数*/
    this->RealClear();
}

/********************************
 *   核心清理释放内存函数
 *******************************/
void facerecognize::RealClear()
{
    QString(this->output_folder).swap(this->output_folder);
    QString(this->trainxmlfile).swap(this->trainxmlfile);
    QString(this->csv_file).swap(this->csv_file);

    std::vector<int>(this->numlist).swap(this->numlist);

    this->im_width = 0;
    this->im_height = 0;
    this->value = 0;
    this->loaded = false;
    this->readcsved = false;
}
