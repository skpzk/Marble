#include "cslider.h"

#include <QPainter>
#include <QColor>

#include <cmath>

#include <iostream>
#include <iomanip> //setw to print hex string
using namespace::std;

//to do : remove unused values knobmargin and knobradius, replace with appropriate setters and getters

CustomSlider::CustomSlider(QWidget* parent, const QString& text,
                       double knobRadius,
                       double knobMargin)
: QSlider(parent),
//   knobRadius_(knobRadius),
//   knobMargin_(knobMargin),
  text_(text)
{
    // Default range
    QSlider::setRange(-64, 63);
}

// void CustomSlider::setKnobRadius(double radius)
// {
//     knobRadius_ = radius;
// }

// double CustomSlider::getKnobRadius() const
// {
//     return knobRadius_;
// }

// void CustomSlider::setKnobMargin(double margin)
// {
//     // cout<<"SetKnobMargin called\n";
//     knobMargin_ = margin;
// }

// double CustomSlider::getKnobMargin() const
// {
//     return knobMargin_;
// }

void CustomSlider::setFixedSize(double size)
{
    // cout<<"SetFixedSize called\n";
    size_ = size;
    hasFixedSize_ = true;
}

double CustomSlider::getFixedSize() const
{
    return size_;
}

void CustomSlider::setText(const QString& text)
{
    text_ = text;
}

QString CustomSlider::getText() const
{
    return text_;
}

QColor CustomSlider::getColor(QPainter* painter){
    int c1 = 0x0079ca;   // color 1, blue
    int c2 = 0x41cd52;  // color 2, green

    // int cb = 

    int r1 = (c1 & 0xff0000) >> 16;
    int g1 = (c1 & 0x00ff00) >> 8;
    int b1 = c1 & 0x0000ff;

    // cout << "r1 = " << hex << r1;
    // cout << ", g1 = " << hex << g1;
    // cout << ", b1 = " << hex << b1 <<endl;

    int r2 = (c2 & 0xff0000) >> 16;
    int g2 = (c2 & 0x00ff00) >> 8;
    int b2 = c2 & 0x0000ff;

    int rb = painter->background().color().red();
    int gb = painter->background().color().green();
    int bb = painter->background().color().blue();

    float sliderRange = (QSlider::maximum() - QSlider::minimum());

    float interpFactor = 2 * (QSlider::value() - QSlider::minimum())/sliderRange;

    // interpFactor = 0;
    int ro, go, bo;
    if(interpFactor <= 1){
        float i = interpFactor;
        float j = (1-interpFactor); 
        ro = (j * r1 + i * rb);
        go = (j * g1 + i * gb);
        bo = (j * b1 + i * bb);
    }else{
        float i = (interpFactor - 1);
        float j = (1-i); 
        
        ro = (j * rb + i * r2);
        go = (j * gb + i * g2);
        bo = (j * bb + i * b2);
    }

    // go = 0;
    // bo = 0;

    int colorOut = ro << 16 | go << 8 | bo;

    // cout << "ro = " << hex << ro << endl;

    char hexColorOut[10];

    sprintf(hexColorOut, "#%06x", colorOut) ;

    // cout << "Color out : " << hexColorOut << endl;

    // cout << hex << setfill('0') << setw(6) << colorOut << endl;

    return QColor(hexColorOut);
}

void CustomSlider::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
    {
        this->setValue(0);
    }
}

void CustomSlider::mousePressEvent ( QMouseEvent * event )
  {
    // cout << "Custom mousePressEvent\n";
    // cout << "(event->button() == Qt::LeftButton)" << (event->button() == Qt::LeftButton) << endl;
    if (event->button() == Qt::LeftButton)
    {
        tmpValue = value();
        tmpY = event->y();
        event->accept();
    }else if ( event->button() == Qt::MiddleButton )
    {
        cout << "middle click\n";
        string name = "";
        if(param != NULL) name = param->name;
        cout << "Param name = " << name <<endl;
        StateParameter::state->ccChoosing(name);
        event->accept();
    }
    // QSlider::mousePressEvent(event);
  }

void CustomSlider::mouseMoveEvent ( QMouseEvent * event )
  {
    // cout << "Custom mouseMoveEvent\n";

    int height = 200;
    // if (event->button() == Qt::LeftButton)
    if (true)
    {
        setValue(tmpValue + (tmpY - event->y())/2) ;
        // cout << minimum() + ((maximum()-minimum()) * (height-event->y())) / height << endl;
        if(param!=NULL){
            if(param->value != this->value()) param->setValue(this->value());
        }

        event->accept();
    }
    // QSlider::mousePressEvent(event);
  }

void CustomSlider::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBackgroundMode(Qt::OpaqueMode);

    // Smooth out the circle
    painter.setRenderHint(QPainter::Antialiasing);

    // Use background color
    painter.setBrush(painter.background());

    QColor pointColor(painter.pen().color());

    // No border
    painter.setPen(QPen(Qt::NoPen));

    double height = QSlider::height();
    double width = QSlider::width();

    QSlider::setFixedWidth(30);
    QSlider::setFixedHeight(20);

    // cout << QSlider::value() <<endl;


    // draw border
    QColor borderColor = QColor("#414141");
    painter.setBrush(QBrush(borderColor));
    painter.drawRect(0, 0, width, height);

    // draw slider
    QColor color = getColor(&painter); // get color (depends on the slider value)
    painter.setBrush(QBrush(color));
    painter.drawRect(1, 1, width - 2, height - 2);

    // draw the value
    QPen pen = QPen("white");
    painter.setPen(pen);
    painter.setBackgroundMode(Qt::TransparentMode);
    QRectF textRect_ = QRectF(0, 0, width, height);
    QString text(QString::number(QSlider::value()));
    if(param!=NULL){
        if(param->value != this->value()) param->setValue(this->value());
    }

    painter.drawText(textRect_, Qt::AlignHCenter | Qt::AlignVCenter, text);
    
}