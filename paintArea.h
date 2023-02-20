#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

class paintArea : public QWidget
{
    Q_OBJECT
public:
    explicit paintArea(QWidget* parent = nullptr);

    void setImageSize(int width, int heightg);
    void setImageColor(QColor color);

    bool isModified() const;
    bool saveImage(const QString& fileName, const char* fileFormat);
    bool openImage(const QString& fileName);

    QSize getImageSize();

    void clear_canvans();
    QImage getImage();

signals:

public slots:
protected:
    void paintEvent(QPaintEvent*);  //�ػ��¼�

    void mousePressEvent(QMouseEvent*);  //��갴���¼�
    void mouseMoveEvent(QMouseEvent*);   //����ƶ��¼�
    void mouseReleaseEvent(QMouseEvent*);//����ͷ��¼�

    void paint(QImage& theImage);

private:
    QImage image;            //QImage��������������ϻ�ͼ
    QRgb backColor;          //�洢11����ɫ
    QPoint lastPoint, endPoint;   //��������������������ָ���ǰ����������

    bool modified;           //��־�����Ƿ񱻸��Ĺ�

    qreal scale;             //������
    int angle;               //�Ƕ�
    qreal shear;             //������

    QColor penColor;         //������ɫ
    QColor brushColor;       //�����ɫ
    int penWidth;            //���ʿ��
    Qt::PenStyle penStyle;   //���ʷ��

    QImage tempImage;   //��ʱ��ͼ��
    bool isDrawing;     //�Ƿ��ڻ������� ͼ��
};

