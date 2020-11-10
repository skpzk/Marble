#ifndef CSLIDER_H_
#define CSLIDER_H_

#include <QSlider>
#include <QColor>
#include <QMouseEvent>

class CustomSlider;
#include "state.h"

class CustomSlider : public QSlider
{
    Q_OBJECT

    // Q_PROPERTY(double knobRadius READ getKnobRadius WRITE setKnobRadius) 
    // //permits access via stylesheet

    // Q_PROPERTY(double knobMargin READ getKnobMargin WRITE setKnobMargin)
    // Q_PROPERTY(double fixedSize READ getFixedSize WRITE setFixedSize)

public:

    CustomSlider(QWidget * parent = nullptr,
               const QString& text = "",
               double knobRadius = 5,
               double knobMargin = 5);

    // void setKnobRadius(double radius);

    // double getKnobRadius() const;

    // void setKnobMargin(double margin);

    // double getKnobMargin() const;

    void setFixedSize(double size);

    double getFixedSize() const;

    void setText(const QString& text);
    
    QString getText() const;


    StateParameter* param=NULL;

private:

    virtual void paintEvent(QPaintEvent*) override;
    QColor getColor(QPainter* painter);

    void mouseDoubleClickEvent( QMouseEvent * e );
    void mousePressEvent( QMouseEvent * e ) override;
    void mouseMoveEvent( QMouseEvent * e ) override;
    int tmpValue, tmpY;

    // double knobRadius_;

    // double knobMargin_;

    double size_;
    bool hasFixedSize_ = false;

    QString text_;

};

#endif