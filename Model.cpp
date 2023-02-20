#include "Model.h"
#include <QMessageBox>
#include<iostream>
#include<fstream>
#include <qimage.h>

AIModel::AIModel() {
    engine = new ONNXEngine();
    load_label();
}

AIModel::~AIModel()
{
    delete engine;
}

std::string AIModel::infer(QImage img)
{
    std::string result;
    img = img.scaled(engine->width_, engine->height_);
    const uchar* pData = img.constBits(); // 获取图像原始数据
    for (int i = 0; i < engine->width_; i++) {
        uchar* imageScanLine = img.scanLine(i);
        for (int k = 0; k < engine->height_; k++) {
            float r = static_cast<float>(imageScanLine[k * 3 + 2]);
            float g = static_cast<float>(imageScanLine[k * 3 + 1]);
            float b = static_cast<float>(imageScanLine[k * 3]);
            float value = (255 - (r + g + b) / 3) / 255;
            engine->input_image_[i * engine->width_ + k] = value;
        }
    }
    engine->Run();
    result = "ID: " + std::to_string(engine->result_) + ", " + label_map.find(engine->result_)->second;
    return result;
}

void AIModel::load_label()
{
    std::ifstream infile;
    std::string buf;
    int i = 0;

    infile.open("model/label.txt", std::ios::in);
    if (!infile.is_open())
    {
        return;
    }
    while (std::getline(infile, buf))
    {
        int blanck_position = buf.find(' ');
        label_map.insert(std::pair<int, std::string>(i, buf.substr(blanck_position + 1)));
       ++i;
    }
}
