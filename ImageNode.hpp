#ifndef IMAGENODE_HPP
#define IMAGENODE_HPP
#include <QSGSimpleTextureNode>
#include <QQuickItem>
#include <QSGTexture>
#include <QPointer>
#include<QRect>

class Q_ImageNode : public QSGSimpleTextureNode{
public:
    inline void setTextureFromImage(const QImage& img){
        if(m_itemptr != nullptr){
            m_texptr = m_itemptr->window()->createTextureFromImage(img);
            this->setTexture(m_texptr.data());
        }
    }
    Q_ImageNode(QQuickItem* contextItem =nullptr, QSGTexture* tex =nullptr, QRect override_rect = QRect(-1, -1, -1, -1) ){
        m_itemptr = contextItem;
        if( override_rect == QRect(-1,-1,-1,-1) ) {
            this ->setRect( m_itemptr->boundingRect().toRect() ); }
        else
            this->setRect(override_rect);
        m_texptr = tex;
        this->setTexture(m_texptr.data());
    }
    Q_ImageNode(const QImage& img, QQuickItem* contextItem =nullptr,const QRect override_rect = QRect(-1, -1, -1, -1) ){
        m_itemptr = contextItem;
        if( override_rect == QRect(-1,-1,-1,-1) ) {
            this ->setRect( m_itemptr->boundingRect().toRect() ); }
        else
            this->setRect(override_rect);
        this->setTextureFromImage(img);
    }
private:
    QPointer<QQuickItem> m_itemptr = nullptr;
    QPointer<QSGTexture> m_texptr = nullptr;
};

#endif // IMAGENODE_HPP
