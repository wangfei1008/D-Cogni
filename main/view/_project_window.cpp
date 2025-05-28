
#include <QtGui>
#include <QMessageBox>
#include <QLabel>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QComboBox>
#include <QColorDialog>
#include <QResizeEvent>

#include "project_window.h"

ProjectWindow::ProjectWindow()
    : NavigationMainWindow(), m_timer(this)
{
    setWindowTitle(tr("Create A New Project"));
 
    titleBar()->setBlurBehindWindowEnabled(true);
    titleBar()->setSysButtonKind(WindowTitleBar::BackButton);
    titleBar()->show();

    m_materialWidget = new MaterialWidget(this);
    m_materialWidget->setBlendType(MaterialWidget::BackgroundBlend);
    m_materialWidget->setTintColor(Qt::white);
    setCentralWidget(m_materialWidget);

    createContent();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(showTime()));
    m_timer.start(1000);
    showTime();

#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    const QRect availableGeometry = screen()->availableGeometry();
#else
    QRect availableGeometry = QGuiApplication::primaryScreen()->availableGeometry();
#endif
    resize(QSize(2 * availableGeometry.width() / 3, 2 * availableGeometry.height() / 3));
    move(QPoint((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2));
}

QWidget* ProjectWindow::createSettingsWidget()
{
    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(widget);

    QCheckBox* blendBox = new QCheckBox(widget);
    blendBox->setText(tr("In-App material brush blending"));
    connect(blendBox, SIGNAL(toggled(bool)), this, SLOT(blendChecked(bool)));
    layout->addWidget(blendBox);

    QCheckBox* extendViewBox = new QCheckBox(widget);
    extendViewBox->setText(tr("Extend view into Title Bar (new)"));
    connect(extendViewBox, SIGNAL(toggled(bool)), this, SLOT(extendViewChecked(bool)));
    extendViewBox->toggle();
    layout->addWidget(extendViewBox);

    QSlider* materialOpacitySlider = new QSlider(Qt::Horizontal, widget);
    materialOpacitySlider->setMinimum(0);
    materialOpacitySlider->setMaximum(100);
    connect(materialOpacitySlider, SIGNAL(valueChanged(int)), this, SLOT(materialOpacityChanged(int)));
    materialOpacitySlider->setValue(75);
    layout->addWidget(materialOpacitySlider);

    return widget;
}

void ProjectWindow::paintEvent(QPaintEvent* event)
{
    if (m_materialWidget->blendType() != MaterialWidget::BackgroundBlend)
    {
        static QPixmap background(QStringLiteral(":res/natural-image.jpg"));
        QPainter painter(this);
        painter.setClipRegion(event->region());
        painter.drawPixmap(0, 0, /*width(), height(), */background);
    }
}

void ProjectWindow::mousePressEvent(QMouseEvent *event)
{
    titleBar()->startDrag(this, event->globalPos());
    event->accept();
}

void ProjectWindow::mouseMoveEvent(QMouseEvent *event)
{
    NavigationMainWindow::mouseMoveEvent(event);
}

void ProjectWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString(QStringLiteral("hh:mm"));
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    m_clockWidget->display(text);
}

void ProjectWindow::blendChecked(bool checked)
{
    m_materialWidget->setBlendType(checked ? MaterialWidget::InAppBlend : MaterialWidget::BackgroundBlend);
}

void ProjectWindow::extendViewChecked(bool checked)
{
    titleBar()->setExtendViewIntoTitleBar(checked);
}

void ProjectWindow::materialOpacityChanged(int value)
{
    m_materialWidget->setTintOpacity(qreal(value) / 100);
}

void ProjectWindow::createContent()
{
    m_clockWidget = new QLCDNumber;
    m_clockWidget->setFrameShape(QFrame::NoFrame);
    m_clockWidget->setSegmentStyle(QLCDNumber::Filled);

    QGridLayout *layout = new QGridLayout;
    m_clockWidget->setFixedHeight(100);
    layout->addWidget(m_clockWidget, 0, 0, Qt::AlignBottom);
    layout->addWidget(createSettingsWidget(), 1, 0, Qt::AlignCenter);
    centralWidget()->setLayout(layout);
}
