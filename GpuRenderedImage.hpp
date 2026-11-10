// THIS CLASS IS MOSTLY FOR TESTING PURPOSES.

#pragma once
#include <qqml.h>
#include <QObject>
#include <QQuickItem>
// #include <QSGImageNode>
#include <QElapsedTimer>
#include <QImage>
#include <QSGTexture>
#include <QSGSimpleTextureNode>
#include "ImageSource.hpp"

class Q_GPURenderedImage : public QQuickItem{
    Q_OBJECT
    // QML_ELEMENT
    Q_PROPERTY(Q_ImageSource* imgsrc READ getImgSrc WRITE setImgSrc NOTIFY imgSrcChanged FINAL)
    QML_NAMED_ELEMENT(GPUImage)

public:
    Q_GPURenderedImage(QQuickItem* parent = nullptr){
        this -> setFlag(ItemHasContents, true);
        QObject::connect(this, &QQuickItem::xChanged, [this](){
            this ->update(/*this->boundingRect().toRect()*/);
        });
        // QObject::connect(this, &QQuickItem::widthChanged, [this](){
        //     boundingrect = boundingRect().toRect();
        // });
        // QObject::connect(this, &QQuickItem::heightChanged, [this](){
        //     boundingrect = boundingRect().toRect();
        // });
    }

    Q_SIGNAL void imgSrcChanged();
    Q_ImageSource* getImgSrc(){return m_src_ptr;}
    void setImgSrc(Q_ImageSource* ptr = nullptr){
        // qDebug() <<ptr;
        // Q_ImageSource* ptr_converted = qobject_cast<Q_ImageSource*>(ptr);
        if(m_src_ptr != ptr){m_src_ptr = ptr; emit imgSrcChanged();}
        img_cpy = m_src_ptr->requestFrame(0);
    }
protected:
    QSGNode* updatePaintNode(QSGNode* node, UpdatePaintNodeData *updatePaintNodeData )override{
        tmr.start();
        // if(! node)node = new QSGNode();
        // node ->removeAllChildNodes();
        QSGSimpleTextureNode* texnode = static_cast<QSGSimpleTextureNode*>(node);
        if(!texnode) texnode = new QSGSimpleTextureNode;
        QSGTexture *texture = window()->createTextureFromImage(m_src_ptr->requestFrame(0), QQuickWindow::TextureHasAlphaChannel);
        texnode->setOwnsTexture(true);
        texnode->setRect(boundingRect());
        // node->set
        texnode->markDirty(QSGNode::DirtyForceUpdate);
        texnode->setTexture(texture);
        // node ->appendChildNode(texnode);
        qDebug()<< tmr.nsecsElapsed();
        tmr.invalidate();

        return texnode;
    }


private:
    QImage img_cpy;
    // QSGTexture* tex;
    // QRect boundingrect = this ->boundingRect().toRect();
    Q_ImageSource* m_src_ptr = nullptr;
    QElapsedTimer tmr;
};