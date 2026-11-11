#ifndef IMAGENODE_HPP
#define IMAGENODE_HPP
#include <QSGSimpleTextureNode>
#include <QQuickItem>
#include <QSGTexture>
#include <QPointer>
#include<QRect>

class Q_ImageNode : public QSGSimpleTextureNode{
public:
    void setTextureFromImage(const QImage& img, QQuickItem* contextItem){
        if(contextItem != nullptr){
            // qDebug() <<"proceeding!";
            QSGTexture* tex = contextItem->window()->createTextureFromImage(img, QQuickWindow::CreateTextureOption::TextureHasAlphaChannel);
            this->setTexture(tex);
            // qDebug()<<tex;
        }
    }
    Q_ImageNode(QQuickItem* contextItem =nullptr, QSGTexture* tex =nullptr, const bool ownsTexture = false, QRect override_rect = QRect(-1, -1, -1, -1) ) {
        this ->setOwnsTexture(ownsTexture);
        if( override_rect == QRect(-1,-1,-1,-1) ) {
            this ->setRect( contextItem->boundingRect().toRect() ); }
        else
            this->setRect(override_rect);
        // tex = tex;
        this->setTexture(tex);
    }
    Q_ImageNode(const QImage& img, QQuickItem* contextItem =nullptr, const bool ownsTexture = false, const QRect override_rect = QRect(-1, -1, -1, -1) ){
        this ->setOwnsTexture(ownsTexture);
        // this->setSourceRect(QRectF(0.0, 0.0, 1.0,1.0));
        // qDebug()<<this->sourceRect();
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
