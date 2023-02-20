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

    void doNew();     //�½��ļ�����
    void doOpen();    //���ļ�����
    bool doFileSave();//�����ļ�����
    bool doFileSaveAs();  //�ļ����Ϊ����

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
    QScrollArea* scrollArea;    //Ϊ��ʹ�����ܴ�ʱ������ʾ�����������

    bool isSaved;     //��־�ļ��Ƿ񱻱����
    QString curFile;  //���浱ǰ�ļ���·��
    bool maybeSave(); //�Ƿ񱣴��ļ�
    bool saveFile(QString fileName);   //ʵ���ļ��Ĵ洢
};

