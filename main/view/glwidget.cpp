#include "glwidget.h"
#include <QPainter>
#include <QTimer>
#include <QPaintEvent>

/* Helper */
GLWidget::Helper::Helper(int num)
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, QColor(0xFF, 0x00, 0x00));
    gradient.setColorAt(1.0, QColor(0x73, 0x20, 0x1B));

    m_background = QBrush(QColor(46, 46, 46));
    m_circleBrush = QBrush(gradient);
    m_circlePen = QPen(Qt::black);
    m_circlePen.setWidth(1);
    m_textPen = QPen(Qt::white);
    m_textFont.setPixelSize(50);
    m_number = num;
}

void GLWidget::Helper::paint(QPainter* painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(event->rect(), m_background);
    painter->translate(event->rect().width()/2, event->rect().height()/2);
    painter->save();
    painter->setBrush(m_circleBrush);
    painter->setPen(m_circlePen);
    painter->rotate(elapsed * 0.030);

    qreal r = elapsed / 1000.0;
    int n = 40;
    for (int i = 0; i < n; ++i)
    {
        painter->rotate(30);
        qreal factor = (i + r) / n;
        qreal radius = 0 + 180.0 * factor;
        qreal circleRadius = 1 + factor * 20;
        painter->drawEllipse(QRectF(radius, -circleRadius, circleRadius * 2, circleRadius * 2));
    }
    painter->restore();
    painter->setPen(m_textPen);
    painter->setFont(m_textFont);
    painter->drawText(QRect(-90, -50, 190, 100), Qt::AlignCenter, QStringLiteral("Qtitan %1").arg(m_number));
}

/* GLWidget */
GLWidget::GLWidget(int num, QWidget *parent)
#ifdef OLD_GLWidget
    : QGLWidget(parent)
#else
    : QOpenGLWidget(parent)
#endif
    , m_helper(new Helper(num))
    , m_elapsed(0)
{
//    makeCurrent();
    setAutoFillBackground(false);
}

GLWidget::~GLWidget()
{
    delete m_helper;
}

void GLWidget::animate()
{
    m_elapsed = (m_elapsed + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}

void GLWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    m_helper->paint(&painter, event, m_elapsed);
    painter.end();
}
