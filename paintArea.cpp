#include "paintArea.h"
#include <QPainter>

QImage paintArea::getImage() {
    QImage img = image;
    return img;
}

paintArea::paintArea(QWidget* parent) : QWidget(parent)
{
    image = QImage(800, 600, QImage::Format_RGB888);   //�����ĳ�ʼ����С��Ϊ400*300��ʹ��32λ��ɫ
    backColor = qRgb(255, 255, 255);                  //������ʼ������ɫʹ�ð�ɫ
    image.fill(backColor);
    modified = false;
    scale = 1;
    angle = 0;
    shear = 0;

    penColor = Qt::black;
    brushColor = Qt::black;
    penWidth = 15;
    penStyle = Qt::SolidLine;

    isDrawing = false;
}
void paintArea::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.scale(scale, scale);
    if (isDrawing)
    {
        painter.drawImage(0, 0, tempImage);
    }
    else
    {
        if (angle)
        {
            QImage copyImage = image;      //�½���ʱ��copyImage,������������ת����
            QPainter pp(&copyImage);
            QPointF center(copyImage.width() / 2.0, copyImage.height() / 2.0);
            painter.translate(center);
            painter.rotate(angle);
            painter.translate(-center);
            pp.drawImage(0, 0, image);
            image = copyImage;   //ֻ�Ḵ��ͼƬ�ϵ����ݣ����Ḵ������ϵͳ
            angle = 0;             //�����ת�󽫽Ƕ�ֵ������Ϊ0
        }
        if (shear)
        {
            QImage copyImage = image;
            QPainter pp(&copyImage);
            pp.shear(shear, shear);
            pp.drawImage(0, 0, image);
            image = copyImage;
            shear = 0;
        }
        painter.drawImage(0, 0, image);
    }
}

void paintArea::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)  //����������
    {
        lastPoint = event->pos();     //������ָ��ĵ�ǰ������Ϊ��ʼ����
        isDrawing = true;
    }
}

void paintArea::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)   //�������������ͬʱ�ƶ����
    {
        endPoint = event->pos();            //������ָ��ĵ�ǰ������Ϊ��ֹ����
        isDrawing = false;
        paint(image);           //����ͼ��

    }
}


void paintArea::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        endPoint = event->pos();
        isDrawing = false;
        paint(image);
    }
}


void paintArea::paint(QImage& theImage)
{
    QPainter pp(&theImage);  //��theImage�ϻ�ͼ
    QPen pen = QPen();         //���廭�ʶ���
    pen.setColor(penColor);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    QBrush brush = QBrush(brushColor);
    pp.setPen(pen);
    pp.setBrush(brush);

    int x, y, w, h;
    x = lastPoint.x() / scale;
    y = lastPoint.y() / scale;
    w = endPoint.x() / scale - x;
    h = endPoint.y() / scale - y;

    pp.drawLine(lastPoint / scale, endPoint / scale);
    lastPoint = endPoint;        //����ֹ�����Ϊ��ʼ����
    update();              //���и��½�����ʾ�������𴰿��ػ��¼����ػ洰��
    modified = true;
}



void paintArea::setImageSize(int width, int height)
{
    QImage newImage(width, height, QImage::Format_RGB32);
    image = newImage;
    update();
}


void paintArea::setImageColor(QColor color)
{
    backColor = color.rgb();  //��Ϊimage�ı���ɫҪ��QRgb���͵���ɫ���������������һ��ת��
    image.fill(backColor);
    update();
}


bool paintArea::isModified() const
{
    return modified;
}

bool paintArea::saveImage(const QString& fileName, const char* fileFormat)
{
    QImage visibleImage = image;
    if (visibleImage.save(fileName, fileFormat))  //�Ѿ�ʵ���˴洢
    {
        modified = false;
        return true;
    }
    else
    {
        return false;
    }
}


bool paintArea::openImage(const QString& fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
    {
        return false;
    }
    QSize newSize = loadedImage.size();
    setImageSize(newSize.width(), newSize.height());
    image = loadedImage;
    modified = false;
    update();
    return true;
}


QSize paintArea::getImageSize()
{
    return image.size() * scale;
}

void paintArea::clear_canvans()
{
    image = QImage(800, 600, QImage::Format_RGB32);   //�����ĳ�ʼ����С��Ϊ400*300��ʹ��32λ��ɫ
    backColor = qRgb(255, 255, 255);                  //������ʼ������ɫʹ�ð�ɫ
    image.fill(backColor);
    modified = false;
    update();
}
