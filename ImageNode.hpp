#ifndef IMAGENODE_HPP
#define IMAGENODE_HPP
#include <QSGSimpleTextureNode>
#include <QQuickItem>
#include <QSGTexture>
#include <QPointer>
#include<QRect>

class Q_ImageNode : public QSGSimpleTextureNode{
public:
    inline void setTextureFromImage(const QImage& img, QQuickItem* contextItem){
        if(contextItem != nullptr){
            QSGTexture* tex = contextItem->window()->createTextureFromImage(img);
            this->setTexture(tex);
        }
    }
    Q_ImageNode(QQuickItem* contextItem =nullptr, QSGTexture* tex =nullptr, QRect override_rect = QRect(-1, -1, -1, -1) ){
        // contextItem = contextItem;
        if( override_rect == QRect(-1,-1,-1,-1) ) {
            this ->setRect( contextItem->boundingRect().toRect() ); }
        else
            this->setRect(override_rect);
        // tex = tex;
        this->setTexture(tex);
    }
    Q_ImageNode(const QImage& img, QQuickItem* contextItem =nullptr,const QRect override_rect = QRect(-1, -1, -1, -1) ){
        contextItem = contextItem;
        if( override_rect == QRect(-1,-1,-1,-1) ) {
            this ->setRect( contextItem->boundingRect().toRect() ); }
        else
            this->setRect(override_rect);
        this->setTextureFromImage(img, contextItem);
    }
private:
    // QPointer<QQuickItem> contextItem = nullptr;
    // QPointer<QSGTexture> tex = nullptr;
};

#endif // IMAGENODE_HPP
