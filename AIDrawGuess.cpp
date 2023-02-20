#include "AIDrawGuess.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QIcon>

AIDrawGuess::AIDrawGuess(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    resize(800, 600);   //�����ڴ�С����Ϊ700*500
    area = new paintArea;
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);  //��scrollArea����ı���ɫ��ΪDark
    scrollArea->setWidget(area);     //�ǳ��ؼ�����������ӵ�scrollArea��
    scrollArea->widget()->setMinimumSize(800, 600);  //scrollArea��ʼ����С��Ϊ800*600
    setCentralWidget(scrollArea);     //��scrollArea���뵽�����ڵ�������

    isSaved = false;
    curFile = "NoName.png";
    model = new AIModel();
}

AIDrawGuess::~AIDrawGuess()
{
    delete model;
}

void AIDrawGuess::doOpen()
{
    if (maybeSave())
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath());
        if (!fileName.isEmpty())
        {
            area->openImage(fileName);
            scrollArea->widget()->resize(area->getImageSize());  //���ͼƬ�Ĵ�С��Ȼ�����scrollArea�Ĵ�С
            isSaved = true;
            curFile = fileName;
        }
    }
}

void AIDrawGuess::doNew()
{
    if (maybeSave())
    {
        area->setImageSize(800, 600);
        scrollArea->widget()->resize(800, 600);
        area->setImageColor(QPalette::Dark);
        isSaved = false;
    }
}

bool AIDrawGuess::doFileSave()
{
    if (isSaved)
    {
        return saveFile(curFile);
    }
    else  return doFileSaveAs();
}



bool AIDrawGuess::saveFile(QString fileName)
{
    if (area->saveImage(fileName, "png"))
    {
        isSaved = true;
        return true;
    }
    else return false;
}



bool AIDrawGuess::doFileSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", curFile);
    if (fileName.isEmpty())
    {
        return false;
    }
    else return saveFile(fileName);
}

bool AIDrawGuess::maybeSave()
{
    if (area->isModified())
    {
        QMessageBox::StandardButton box;
        box = QMessageBox::warning(this, "Save File", "Image is change, are you want to save?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (box == QMessageBox::Yes)
        {
            return doFileSave();
        }
        else if (box == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

void AIDrawGuess::on_action_O_triggered()
{
    doOpen();
}

void AIDrawGuess::on_action_N_triggered()
{
    doNew();
}

void AIDrawGuess::on_action_S_triggered()
{
    doFileSave();
}

void AIDrawGuess::on_action_C_triggered()
{
    doFileSaveAs();
}

void AIDrawGuess::on_action_Clear_triggered()
{
    area->clear_canvans();
}

void AIDrawGuess::on_action_Guess_triggered()
{
    QImage img = area->getImage();
    std::string result = model->infer(img);
    QMessageBox::information(this, "Result", result.c_str());
}

void AIDrawGuess::on_action_Label_triggered()
{
    std::string label_info;
    for (auto itr:model->label_map)
    {
        std::string t = "ID:" + std::to_string(itr.first) + ", " + itr.second + " ";
        label_info.append(t);
    }
    QMessageBox::information(this, "Label", label_info.c_str());
}

void AIDrawGuess::on_action_About_triggered()
{
    QMessageBox::information(this, "Version", "By ThyssenWen!");
}