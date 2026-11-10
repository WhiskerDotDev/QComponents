#pragma once
#include "intrin.h"
#include <QtQml/qqml.h>
// #include <QObject>
#include <QQuickPaintedItem>
#include <ImageSource.hpp>
#include <QElapsedTimer>
// #include <QQUickItem>
#include <QImage>
#include <QPainter>

class Q_CPURenderedImage  : public QQuickPaintedItem{
    Q_OBJECT
    // QML_ELEMENT
    Q_PROPERTY(Q_ImageSource* imgsrc READ getImgSrc WRITE setImgSrc NOTIFY imgSrcChanged FINAL)
    QML_NAMED_ELEMENT(CPUImage)

public:
    Q_CPURenderedImage(QQuickItem* parent = nullptr){
        QObject::connect(this, &QQuickItem::xChanged, [this](){
            this ->update(this->boundingrect);
        });
        QObject::connect(this, &QQuickItem::widthChanged, [this](){
            boundingrect = boundingRect().toRect();
        });
        QObject::connect(this, &QQuickItem::heightChanged, [this](){
            boundingrect = boundingRect().toRect();
        });
    }

    Q_SIGNAL void imgSrcChanged();
    Q_ImageSource* getImgSrc(){return m_src_ptr;}
    void setImgSrc(Q_ImageSource* ptr = nullptr){
        // qDebug() <<ptr;
        // Q_ImageSource* ptr_converted = qobject_cast<Q_ImageSource*>(ptr);
        if(m_src_ptr != ptr){m_src_ptr = ptr; emit imgSrcChanged();}
        img_cpy = m_src_ptr->requestFrame(-1);
    }


protected:

    void paint(QPainter* painter)override{
        // __rdtscp(&rdtsc_init);
        tmr.restart();
        if(painter == nullptr || painter ->isActive() == false) [[unlikely]] goto _end;
        // painter->setRenderHint(QPainter::RenderHint::LosslessImageRendering, false);
        // qDebug()<<painter ->testRenderHint(QPainter::RenderHint::VerticalSubpixelPositioning);
        painter->drawImage( this ->boundingRect(), img_cpy);
        qDebug() << tmr.nsecsElapsed();
        // tmr.invalidate();
        // tmr.restart();
        _end:
        return;

    }

private:
    QImage img_cpy;
    QRect boundingrect = this ->boundingRect().toRect();
    Q_ImageSource* m_src_ptr = nullptr;
    QElapsedTimer tmr;

};
