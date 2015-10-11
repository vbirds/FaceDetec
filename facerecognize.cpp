#include "facerecognize.h"

facerecognize::facerecognize()
{
}

facerecognize::~facerecognize()
{

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
