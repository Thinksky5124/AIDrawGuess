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
    void paintEvent(QPaintEvent*);  //重绘事件

    void mousePressEvent(QMouseEvent*);  //鼠标按下事件
    void mouseMoveEvent(QMouseEvent*);   //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent*);//鼠标释放事件

    void paint(QImage& theImage);

private:
    QImage image;            //QImage类对象，用于在其上绘图
    QRgb backColor;          //存储11景颜色
    QPoint lastPoint, endPoint;   //定义两个坐标对象存放鼠标指针的前后两个坐标

    bool modified;           //标志画布是否被更改过

    qreal scale;             //缩放量
    int angle;               //角度
    qreal shear;             //拉伸量

    QColor penColor;         //画笔颜色
    QColor brushColor;       //填充颜色
    int penWidth;            //画笔宽度
    Qt::PenStyle penStyle;   //画笔风格

    QImage tempImage;   //临时绘图区
    bool isDrawing;     //是否在绘制特殊 图形
};

