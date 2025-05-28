
#include <QtGui>
#include <QMessageBox>
#include <QLabel>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QComboBox>
#include <QColorDialog>
#include <QCalendarWidget>
#include <QTableView>
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#include <QTextCodec>
#endif
#include <QApplication>
#include "new_project_window.h"


class NavigationPage : public QLabel
{
public:
    NavigationPage() : QLabel() {}
    virtual ~NavigationPage() { }
};


ProjectWindow::ProjectWindow()
    : NavigationMainWindow()
{
    setWindowTitle(tr("Create A New Project"));

    m_view = new NavigationView(this);

    m_page_attribute = new ProjectAttribute();
    m_view->addPageItem(SegoeMDL2Font::code(SegoeMDL2Font::FileExplorer), tr("Project Attribute"), m_page_attribute);
    connect(m_page_attribute, &ProjectAttribute::signal_next_check, this, &ProjectWindow::on_slot_next_check);

    m_page_device = new NetworkDevicePage();
    m_view->addPageItem(SegoeMDL2Font::code(SegoeMDL2Font::World), tr("Network Device"), m_page_device);
    connect(m_page_device, &NetworkDevicePage::signal_finish_check, this, &ProjectWindow::on_slot_finish_check);

//    m_view->settingsItem()->setPage(new SettingsWidget(this));
//    m_view->settingsItem()->setTransition(Qtitan::Entrance);

    //setContentsMargins(3, 3, 3, 3);
    setCentralWidget(m_view);

    titleBar()->setSysButtonKind(WindowTitleBar::SysButtonHidden);
    titleBar()->setBlurBehindWindowEnabled(true);
    titleBar()->setExtendViewIntoTitleBar(true);
    //titleBar()->setStyledFrame(false);
    titleBar()->setVisible(true);

    m_view->frame()->navigateTo(m_page_attribute);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    const QRect availableGeometry = screen()->availableGeometry();
#else
    QRect availableGeometry = QGuiApplication::primaryScreen()->availableGeometry();
#endif
    resize(QSize(2 * availableGeometry.width() / 3, 2 * availableGeometry.height() / 3));
    move(QPoint((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2));
}

void ProjectWindow::paintEvent(QPaintEvent* event)
{
    NavigationMainWindow::paintEvent(event);
}

void ProjectWindow::on_slot_finish_check()
{
    this->close();
}

void ProjectWindow::on_slot_next_check()
{
    m_view->frame()->navigateTo(m_page_device);
}
