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
        if(! node)node = new QSGNode();
        node ->removeAllChildNodes();
        // Q_ImageNode* texnode = static_cast<Q_ImageNode*>(node);
        auto texnode = new Q_ImageNode(m_src_ptr->requestFrame(-1), this);
        // QSGTexture *texture = window()->createTextureFromImage(m_src_ptr->requestFrame(-1));
        // texnode->setOwnsTexture(true);
        // texnode->setRect(boundingRect());
        // node->set
        // texnode->setTexture(texture);
        node ->appendChildNode(texnode);
        texnode->markDirty(QSGNode::DirtyForceUpdate);
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