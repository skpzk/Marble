#include "cdial.h"

#include <QPainter>
#include <QColor>

#include <cmath>

#include <iostream>
#include <QMouseEvent>
using namespace::std;

//to do : remove unused values knobmargin and knobradius, replace with appropriate setters and getters

CustomDial::CustomDial(QWidget* parent, const QString& text,
                       double knobRadius,
                       double knobMargin)
: QDial(parent),
  knobRadius_(knobRadius),
  knobMargin_(knobMargin),
  text_(text)
{
    // Default range
    QDial::setRange(0,127);
}

void CustomDial::setKnobRadius(double radius)
{
    knobRadius_ = radius;
}

double CustomDial::getKnobRadius() const
{
    return knobRadius_;
}

void CustomDial::setKnobMargin(double margin)
{
    // cout<<"SetKnobMargin called\n";
    knobMargin_ = margin;
}

double CustomDial::getKnobMargin() const
{
    return knobMargin_;
}

void CustomDial::setFixedSize(double size)
{
    // cout<<"SetFixedSize called\n";
    size_ = size;
    hasFixedSize_ = true;
}

double CustomDial::getFixedSize() const
{
    return size_;
}

void CustomDial::setText(const QString& text)
{
    text_ = text;
}

QString CustomDial::getText() const
{
    return text_;
}

void CustomDial::mousePressEvent(QMouseEvent *e){
    if ( e->button() == Qt::MiddleButton )
    {
        cout << "middle click\n";
        string name = "";
        if(param != NULL) name = param->name;
        cout << "Param name = " << name <<endl;
        StateParameter::state->ccChoosing(name);
        e->accept();
    }
    
    else{
        QDial::mousePressEvent(e);
    }
}

void CustomDial::paintEvent(QPaintEvent*)
{
    static const double degree270 = 1.5 * M_PI;

    static const double degree225 = 1.25 * M_PI;

    QPainter painter(this);

    // So that we can use the background color
    painter.setBackgroundMode(Qt::OpaqueMode);

    // Smooth out the circle
    painter.setRenderHint(QPainter::Antialiasing);

    // Use background color
    painter.setBrush(painter.background());
    // painter.setBrush(QBrush(QColor::fromRgbF(1, 0, 0, 1)));

    // Store color from stylesheet, pen will be overriden
    QColor pointColor(painter.pen().color());

    // No border
    painter.setPen(QPen(Qt::NoPen));

    double center_x, center_y;
    
    center_x = QDial::width() / 2.0;
    center_y = QDial::height() / 2.0;

    double radius;
    if(!hasFixedSize_){
        radius = fmin(QDial::width()/2. - knobMargin_, QDial::height()/2. - knobMargin_);
    }else{
        radius = size_/2.;
    }

    // Draw outer circle(ring)
    painter.setBrush(QBrush(pointColor));
    painter.drawEllipse(QPointF(center_x, center_y), 
        radius, radius);

    
    // Reset color to pointColor from stylesheet
    
    float ringSize = 0.94;
    
    // Draw inner circle
    painter.setBrush(painter.background());

    painter.drawEllipse(QPointF(center_x, center_y), 
    radius * ringSize, radius * ringSize);
    

    // Get ratio between current value and maximum to calculate angle
    if(param!=NULL){
        // if(param->value != this->value()) *param = this->value();
        if(param->value != this->value()) param->setValue(this->value());
    }
    double ratio = static_cast<double> (QDial::value()) / QDial::maximum();

    // The maximum amount of degrees is 270, offset by 225
    double angle = ratio * degree270 - degree225;

    // Draw the indicator
    painter.setBrush(QBrush(pointColor));
   
    double linewidth = (1 - ringSize) *radius;

    double a_y = center_y + sin(angle) * (radius - linewidth);
    double a_x = center_x + cos(angle) * (radius - linewidth);

    QPen pen = QPen(pointColor, linewidth);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);

    painter.drawLine(a_x, a_y, center_x, center_y);

    QRectF textRect_ = QRectF(0, QDial::height()/2 + radius, QDial::width(), 100);

    painter.drawText(textRect_, Qt::AlignHCenter | Qt::AlignTop, text_);
}