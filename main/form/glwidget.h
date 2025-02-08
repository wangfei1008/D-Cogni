#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QPen>

#ifdef OLD_GLWidget
#include <QGLWidget>
#endif
#include <QOpenGLWidget>


#ifdef OLD_GLWidget
class GLWidget : public QGLWidget
#else
class GLWidget : public QOpenGLWidget
#endif
{
    Q_OBJECT
public:
    class Helper
    {
    public:
        Helper(int num);
    public:
        void paint(QPainter* painter, QPaintEvent* event, int elapsed);
    private:
        QBrush m_background;
        QBrush m_circleBrush;
        QFont m_textFont;
        QPen m_circlePen;
        QPen m_textPen;
        int m_number;
    };
public:
    GLWidget(int num, QWidget* parent = NULL);
    virtual ~GLWidget();
public Q_SLOTS:
    void animate();
protected:
    virtual void paintEvent(QPaintEvent* event) override;
private:
    Helper* m_helper;
    int m_elapsed;
};


#endif // GLWIDGET_H
