#pragma once
#include <QtQml/qqml.h>
// #include "qqmlintegration.h"
#include <QObject>
#include <QDebug>
#include <QImage>
#include <QImageReader>
#include <QString>
#include <QVarLengthArray>
// #include <QRgb>
#include <QColor>
#include <qquickitem.h>
#include "Windows.h"
// #include <libloaderapi.h>

class Q_ImageSource : public QObject{
    Q_OBJECT
    // QML_ELEMENT
    QML_NAMED_ELEMENT(ImageSource)

public:
    Q_ImageSource(QQuickItem* parent){

        QObject::connect(this, &Q_ImageSource::pathReady, this, [&](){
            QString* old = this ->m_resourcePathptr;
            m_resourcePathptr = nullptr;
            delete old;
            m_resourcePathptr = new QString(path);
            m_resourcePath = m_resourcePathptr->right( m_resourcePathptr->length() - m_resourcePathptr->lastIndexOf("\\") );
            m_resourcePathptr ->clear();
        });

        GetModuleFileNameW(NULL, path, MAX_PATH);
        emit this->pathReady();

    }

    const QImage requestFrame(qint64 idx){
        if(m_frames.length() < idx || idx < 0){
            err_img.setColor(1, m_errclr1.rgb());
            err_img.setColor(2, m_errclr2.rgb());
            return err_img;
        }
        return static_cast<const QImage>(m_frames[idx]);
        // return QImage();
    }

    void readFrames(){
        if(m_filename.isEmpty() || m_filename.isNull()) {
            qDebug() << "Null file!";
            return;}
        m_reader.setFileName(m_filename);
        qDebug() <<"FILENAME: " << m_reader.fileName();

        if(m_reader.canRead() == false || m_reader.imageCount() == -1)  [[unlikely]] {
            qDebug()<< m_reader.errorString();
            return;
        }

        m_frames.clear();
        if(m_reader.supportsAnimation() == false) [[unlikely]] {
            m_frames.append(m_reader.read());
            return;
        }

        if(m_frames.capacity() < m_reader.imageCount()) m_frames.reserve(m_reader.imageCount() - m_frames.capacity());
        QImage current = m_reader.read();
        while(current.isNull() == false){
            m_frames.append(current);
            current = m_reader.read();
        }
    }

    Q_ImageSource(QObject* parent = nullptr){
        this ->readFrames();
    }

    void setFileName(const QString& other){
        m_filename.clear();
        m_filename = other;
    }


private:
    Q_SIGNAL void pathReady();
    wchar_t path[MAX_PATH];

    QString m_filename = "C:/Projects/myBrowser/ico/magnifyingGlass001.png";
    QString m_resourcePath;
    QString* m_resourcePathptr = nullptr;
    QVarLengthArray<QImage, 1> m_frames;
    QImageReader m_reader;
    QColor m_errclr1 = QColor(0,0,0,255);
    QColor m_errclr2 = QColor(255, 60, 255, 255);
    uchar m_errData[6] =  {2, 1, 2,1,1,2}; // Why did this combination work..?
    QImage err_img = QImage(m_errData, 2,  2,  QImage::Format::Format_Indexed8);


};
