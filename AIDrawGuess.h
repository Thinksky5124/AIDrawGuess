#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AIDrawGuess.h"
#include <QMainWindow>
#include "paintArea.h"
#include "Model.h"
#include <QScrollArea>
#include <QComboBox>


class AIDrawGuess : public QMainWindow
{
    Q_OBJECT

public:
    AIDrawGuess(QWidget* parent = nullptr);
    ~AIDrawGuess();

    void doNew();     //新建文件操作
    void doOpen();    //打开文件操作
    bool doFileSave();//保存文件操作
    bool doFileSaveAs();  //文件另存为操作

private slots:
    void on_action_O_triggered();

    void on_action_N_triggered();

    void on_action_S_triggered();

    void on_action_C_triggered();

    void on_action_Clear_triggered();

    void on_action_Guess_triggered();

    void on_action_Label_triggered();

    void on_action_About_triggered();

private:
    Ui::AIDrawGuessClass ui;
    AIModel* model;
    paintArea* area;
    QScrollArea* scrollArea;    //为了使画布很大时还能显示，加入滚动条

    bool isSaved;     //标志文件是否被保存过
    QString curFile;  //保存当前文件的路径
    bool maybeSave(); //是否保存文件
    bool saveFile(QString fileName);   //实现文件的存储
};

