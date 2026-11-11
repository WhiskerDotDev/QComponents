// THIS CLASS IS MOSTLY FOR TESTING PURPOSES.

#define EXPERIMENTAL_USAGE
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
#include "ImageNode.hpp"

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
    QSGNode* updatePaintNode(QSGNode* node, UpdatePaintNodeData *updatePaintNodeData )override{
        tmr.start();

#ifdef EXPERIMENTAL_USAGE
        if(! node)node = new QSGNode();
        node ->removeAllChildNodes();
        Q_ImageNode* texnode = new Q_ImageNode(m_src_ptr->requestFrame(-1), this, true);
        texnode->markDirty(QSGNode::DirtyForceUpdate);
        node ->appendChildNode(texnode);
        // node->markDirty(QSGNode::DirtyStateBit::DirtyNodeAdded);
#else
        QSGSimpleTextureNode* texnode = static_cast<QSGSimpleTextureNode*>(node);
        if(!texnode) texnode = new QSGSimpleTextureNode;
        QSGTexture *texture = window()->createTextureFromImage(m_src_ptr->requestFrame(-1), QQuickWindow::TextureHasAlphaChannel);
        texnode->setOwnsTexture(true);
        // texnode->setSourceRect(QRectF(0,0,2,2));
        texnode->setRect(boundingRect().toRect());
        texnode->markDirty(QSGNode::DirtyStateBit::DirtyMaterial);
        texnode->setTexture(texture);
#endif

        // Q_ImageNode* texnode = static_cast<Q_ImageNode*>(node);
        // node->set

        qDebug()<< tmr.nsecsElapsed();
        tmr.invalidate();
#ifdef EXPERIMENTAL_USAGE
        return node;
#else
        return texnode;
#endif

    }


private:
    QImage img_cpy;
    // QSGTexture* tex;
    // QRect boundingrect = this ->boundingRect().toRect();
    Q_ImageSource*m_src_ptr;
    QElapsedTimer tmr;
};