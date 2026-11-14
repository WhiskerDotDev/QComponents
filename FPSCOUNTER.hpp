#pragma once

// #include  <QBasicTimer>
#include <QObject>
#include <QtQml/qqml.h>
#include <QDebug>
#include <QQuickWindow>

class Q_FPSCounter: public QObject{
    Q_OBJECT
    QML_ELEMENT
    QML_NAMED_ELEMENT(FPSCounter)

    // QML PROPERITES:
    Q_PROPERTY(QQuickWindow* window READ getWnd WRITE setWnd NOTIFY windowChanged REQUIRED)
    Q_PROPERTY(float fps READ getFPS NOTIFY fpsChanged FINAL)
    Q_PROPERTY(bool active READ getActive WRITE setActive NOTIFY activeChanged FINAL)
    Q_PROPERTY(int precision READ getPrecision WRITE setPrecision NOTIFY precisionChanged FINAL) // sets timer precision (e.g. Preciese, Coarse, VeryCoarse)
    Q_PROPERTY(float interval READ getInterval WRITE setInterval NOTIFY intervalChanged FINAL)
    Q_PROPERTY(bool log READ getLog WRITE setLog NOTIFY logChanged FINAL)

public:

    Q_INVOKABLE void stop(){
        // if(m_timer.isActive())m_timer.stop();
        if(m_timerID != -1){
            killTimer(m_timerID);
            m_prevID = m_timerID;
            m_timerID = -1;
        }
    }
    Q_INVOKABLE void start(const float ovr_milliseconds = -1.0f ) // ovr stands for "override", and will accordingly override the milliseconds value
    {
        qDebug() << "started!";
        if(ovr_milliseconds != -1.0f) this->m_interval = ovr_milliseconds;
        // m_timer.start( m_interval, Qt::TimerType::CoarseTimer, this);
        m_prevID = m_timerID;
        if(m_timerID != -1)stop(); // kill the current timer
        m_timerID = startTimer(m_interval, static_cast<Qt::TimerType>(m_precision) );
    }

    // WND FUNCS:
    Q_SIGNAL void windowChanged();

    QQuickWindow* getWnd(){return m_wnd;}

    void setWnd(QQuickWindow* new_wnd){
        if(m_wnd != new_wnd)m_wnd = new_wnd;
        QObject::disconnect(m_connection);
        // m_connection = QMetaObject::Connection();
        m_connection = QObject::connect(m_wnd, &QQuickWindow::frameSwapped, this, [&](){
            // m_isWriting = true;
            // m_currentFPSCOUNT++;
            // m_isWriting = false;
            _InterlockedIncrement(&m_currentFPSCOUNT);
        });
        emit windowChanged();
    }

    //FPS FUNCS:
    Q_SIGNAL void fpsChanged();
    float getFPS(){
    alignas(16) __m128 floatVector{0.0f, 0.0f, 0.0f, 0.0f};
    // floatVector = _mm_set_ps1(0.0f);
    _mm_cvt_si2ss(floatVector, m_currentFPSCOUNT);
    return (  _mm_cvtss_f32(floatVector) / ( m_interval / m_thousand ) ) ;}

    // INTERVAL FUNCS:
    Q_SIGNAL void intervalChanged();
    float getInterval(){return m_interval;}
    void setInterval(float newInterval){if(newInterval != m_interval)m_interval = newInterval; emit intervalChanged();}

    // ACTIVE_PROP FUNCS:
    Q_SIGNAL void activeChanged();
    bool getActive(){return m_timerID != -1;}
    void setActive(bool newstate){
        newstate == true? this -> start() : this -> stop();
        if(m_timerID != m_prevID) emit activeChanged();
    }

    // PRECISION FUNCS:

    Q_SIGNAL void precisionChanged();
    int getPrecision(){return m_precision;}
    void setPrecision(quint8 newPrecision){
        if(newPrecision == m_precision)return;
        if(newPrecision > 2)newPrecision = 0;
        m_precision = newPrecision;
    }

    // LOG FUNCS:

    Q_SIGNAL void logChanged();
    bool getLog(){return m_logFPS;}
    void setLog(const bool val){if(m_logFPS != val)m_logFPS = val; emit logChanged();}

    Q_FPSCounter(){
        QObject::connect(m_wnd, &QQuickWindow::frameSwapped, this, [&](){
            this ->incrementCounter();
        }, Qt::ConnectionType::DirectConnection);
    }
protected:
    void timerEvent(QTimerEvent* event) override {
        // qDebug()  <<"SOMETHING HAPPENED!";

        if(m_timerID == event->timerId()){
            m_lastFPSCOUNT = _InterlockedExchange(&m_currentFPSCOUNT, (const long)0);
            emit fpsChanged();
            if(m_logFPS == true) qDebug() << "FPS:" << m_lastFPSCOUNT << "\nWND: " << m_wnd << '\n';
        }else return;

    }

private:
    alignas(8) QQuickWindow* m_wnd = nullptr; // expects parent to be a QQuickWIndow
    /*qobject_cast<QQuickWindow*>(this->parent())*/

    alignas(8) QMetaObject::Connection m_connection = QMetaObject::Connection();

    // const float m_million = 1000000.0f; // used for conversion between nanoseconds and milliseconds
    alignas(4) const float m_thousand = 1000.0f;
    alignas(4) float m_interval = 1000.0f;
    alignas(4) volatile long m_currentFPSCOUNT = 0; // convert to float when needed
    alignas(4) volatile long m_lastFPSCOUNT = 0;

    // float m_currentFPSCount = 0.0f; // how many frames have been swapped at this instance
    // float m_lastFPSCount = 0.0f; // the last  recorded framerate
    alignas(4) int m_timerID = -1;
    alignas(4) int m_prevID = -1;

    // std::atomic_bool m_isWriting = false; // used to ensure counter isn't cleared erroneously
    alignas(1) bool m_logFPS = true;
    /*
        0 = precise (millisecond precision)
        1 = coarse (within 5% of interval)
        2 = veryCoarse (second precision)
*/
    alignas(1) quint8 m_precision = 0;


    void incrementCounter() noexcept {_InterlockedIncrement(&m_currentFPSCOUNT);}

    // alignas (8) QBasicTimer m_timer;

};
