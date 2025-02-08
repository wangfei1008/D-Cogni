#include "dock_window.h"
#include <QApplication>
#include <QBuffer>
#include <QAction>
#include <QActionGroup>
#include <QFileDialog>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include "aboutdialog.h"

static const QString DockBarSetting = QStringLiteral("DockBarLayout");
static const QString DockPanelSetting = QStringLiteral("DockPanelLayout");

TitleBarCaption::TitleBarCaption(const QString& productName, const QString& version, const QString& caption)
    : QLabel()
{
    setAttribute(Qt::WA_NoSystemBackground, true);
    setOpenExternalLinks(true);
    setText(QStringLiteral("<table border=\"0\"><tr style=\"vertical-align: middle;\"> \
         <td><img src=\"res/image/logo32_32.png\"></td>\
         <td><strong>%1 %2</strong></td><td> %3").arg(productName, version, caption));
    connect(this, SIGNAL(linkHovered(const QString&)), this, SLOT(setLink(const QString&)));
}

TitleBarCaption::~TitleBarCaption()
{
}

void TitleBarCaption::mousePressEvent(QMouseEvent* event)
{
    QLabel::mousePressEvent(event);
    if (!m_link.isEmpty())
        event->accept();
}


DCDockWindow::DCDockWindow(QWidget* parent)
    : DockMainWindow(parent)
//    , m_appStyle(Default)
//    , m_defaultStyle(QString())
//    , m_styleComboBox(Q_NULL)
{
    menuBar()->setNativeMenuBar(false);

//    if (QProxyStyle* proxy = qobject_cast<QProxyStyle*>(qApp->style()))
//        m_defaultStyle = proxy->baseStyle()->objectName();

    createActions();
    
//    setCustomStyle(VS2019Blue);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS) || defined(Q_OS_LINUX)
    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(widget);
    layout->setContentsMargins(QMargins(0, 0, 0, 0));
    layout->addWidget(new TitleBarCaption(QLatin1String("D-Cogni"), QLatin1String("(Data Cognitive)"), QLatin1String()));
    titleBar()->setWidget(widget);
    titleBar()->show();
#endif
#endif

}

DCDockWindow::~DCDockWindow()
{
}

WindowTitleBar* DCDockWindow::titleBar() const
{
    WindowTitleBar* ptitlebar = WindowTitleBar::get(const_cast<DCDockWindow*>(this));
    ptitlebar->setSysButtonKind(WindowTitleBar::SysButtonHidden);
    return ptitlebar;
}

//void DCDockWindow::styleChanged(QAction* action)
//{
//    AppStyle appStyle = Default;
//    if (m_fusionStyleAction == action)
//        appStyle = Fusion;
//    else if (m_themeBlueAction == action)
//        appStyle = VS2019Blue;
//    else if (m_themeLightAction == action)
//        appStyle = VS2019Light;
//    else if (m_themeDarkAction == action)
//        appStyle = VS2019Dark;
//    setCustomStyle(appStyle);
//}

void DCDockWindow::styleIndexChanged(int index)
{
    QComboBox* comboBox = qobject_cast<QComboBox*>(sender());
    Q_ASSERT(comboBox != Q_NULL);
    QVariant var = comboBox->itemData(index);
    AppStyle appStyle = static_cast<AppStyle>(var.toInt());
    //setCustomStyle(appStyle);
}

void DCDockWindow::about()
{
    AboutDialog::show(this, tr("About Data Cognitive"), tr("QtitanDocking"), QStringLiteral(QTN_VERSION_DOCKING_STR));
}

void DCDockWindow::saveToolBarToXML()
{
    const QString path = QDir::currentPath() + QStringLiteral("/toolbar-layout");
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Save ToolBar's Layout to XML File"),  path, 
        QStringLiteral("XML (*.xml);;FastInfoset (*.fi)"));
    if (fileName.isEmpty())
        return;
    if (QFileInfo(fileName).completeSuffix().contains(QStringLiteral("xml"), Qt::CaseInsensitive))
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
            return;
        XmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        dockBarManager()->saveStateToXML(&writer);
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
            return;
        FastInfosetStreamWriter writer(&file);
        dockBarManager()->saveStateToXML(&writer);
    }
}

void DCDockWindow::loadToolBarFromXML()
{
    const QString path = QDir::currentPath() + QStringLiteral("/");
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Open ToolBar's Layout XML File"), path, 
        QStringLiteral("XML (*.xml);;FastInfoset (*.fi)"));
    if (fileName.isEmpty())
        return;
    if (QFileInfo(fileName).completeSuffix().contains(QStringLiteral("xml"), Qt::CaseInsensitive))
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
            return;
        XmlStreamReader reader(&file);
        dockBarManager()->loadStateFromXML(&reader);
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
            return;
        FastInfosetStreamReader reader(&file);
        dockBarManager()->loadStateFromXML(&reader);
    }
}

void DCDockWindow::savePanelToXML()
{
    const QString path = QDir::currentPath() + QStringLiteral("/panel-layout");
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Save Panel's Layout to XML File"), path, 
        QStringLiteral("XML (*.xml);;FastInfoset (*.fi)"));
    if (fileName.isEmpty())
        return;
    if (QFileInfo(fileName).completeSuffix().contains(QStringLiteral("xml"), Qt::CaseInsensitive))
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
            return;
        XmlStreamWriter writer(&file);
        writer.setAutoFormatting(true);
        dockPanelManager()->saveStateToXML(&writer);
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
            return;
        FastInfosetStreamWriter writer(&file);
        dockPanelManager()->saveStateToXML(&writer);
    }
}

void DCDockWindow::loadPanelFromXML()
{
    const QString path = QDir::currentPath() + QStringLiteral("/");
    const QString fileName = QFileDialog::getOpenFileName(this, tr("Open Panel's Layout XML File"), path, 
        QStringLiteral("XML (*.xml);;FastInfoset (*.fi)"));
    if (fileName.isEmpty())
        return;
    if (QFileInfo(fileName).completeSuffix().contains(QStringLiteral("xml"), Qt::CaseInsensitive))
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
            return;
        XmlStreamReader reader(&file);
        dockPanelManager()->loadStateFromXML(&reader);
    }
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
            return;
        FastInfosetStreamReader reader(&file);
        dockPanelManager()->loadStateFromXML(&reader);
    }
}

void DCDockWindow::createActions()
{
    // Save DockToolBar layout to XML...
    m_saveToolBarAction = new QAction(tr("&Save ToolBar's Layout to XML/FastInfoset"), this);
    connect(m_saveToolBarAction, SIGNAL(triggered()), this, SLOT(saveToolBarToXML()));
    m_loadToolBarAction = new QAction(tr("&Load ToolBar's Layout from XML/FastInfoset"), this);
    connect(m_loadToolBarAction, SIGNAL(triggered()), this, SLOT(loadToolBarFromXML()));

    // Save DockToolBar layout to XML...
    m_savePanelAction = new QAction(tr("&Save Panel's Layout to XML/FastInfoset"), this);
    connect(m_savePanelAction, SIGNAL(triggered()), this, SLOT(savePanelToXML()));
    m_loadPanelAction = new QAction(tr("&Load Panel's Layout from XML/FastInfoset"), this);
    connect(m_loadPanelAction, SIGNAL(triggered()), this, SLOT(loadPanelFromXML()));

    //Auto Save to XML/FastInfoset
    m_autoSaveAction = new QAction(tr("&Auto Save (new)"), this);
    m_autoSaveAction->setCheckable(true);
    m_autoSaveAction->setChecked(false);

    m_aboutAction = new QAction(QIcon(QStringLiteral(":res/about.png")), tr("About D-Cogni..."), this);
    m_aboutAction->setStatusTip(tr("Display program information, version number and copyright"));
    connect(m_aboutAction, SIGNAL(triggered()), this, SLOT(about()));

//    m_defaultStyleAction = new QAction(tr("Default"), this);
//    m_defaultStyleAction->setCheckable(true);
//    m_defaultStyleAction->setChecked(false);
//    m_fusionStyleAction = new QAction(tr("Fusion"), this);
//    m_fusionStyleAction->setCheckable(true);
//    m_fusionStyleAction->setChecked(false);
//    m_themeBlueAction = new QAction(tr("Blue"), this);
//    m_themeBlueAction->setCheckable(true);
//    m_themeBlueAction->setChecked(false);
//    m_themeLightAction = new QAction(tr("Light"), this);
//    m_themeLightAction->setCheckable(true);
//    m_themeLightAction->setChecked(false);
//    m_themeDarkAction = new QAction(tr("Dark"), this);
//    m_themeDarkAction->setCheckable(true);
//    m_themeDarkAction->setChecked(false);
}

//QComboBox* DCDockWindow::createComboBoxStyle()
//{
//    m_styleComboBox = new QComboBox(this);
//    m_styleComboBox->addItem(m_defaultStyleAction->text(), Default);
//    m_styleComboBox->addItem(m_fusionStyleAction->text(), Fusion);
//    m_styleComboBox->addItem(QStringLiteral("VisualStudio2019 ") + m_themeBlueAction->text(),  VS2019Blue);
//    m_styleComboBox->addItem(QStringLiteral("VisualStudio2019 ") + m_themeDarkAction->text(),  VS2019Dark);
//    m_styleComboBox->addItem(QStringLiteral("VisualStudio2019 ") + m_themeLightAction->text(), VS2019Light);
//    m_styleComboBox->setCurrentIndex(static_cast<int>(m_appStyle));
//    connect(m_styleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(styleIndexChanged(int)));
//    return m_styleComboBox;
//}

//void DCDockWindow::addStyleMenu(QMenu* menu)
//{
//    // styles...
//    QMenu* menuStyles = menu->addMenu(tr("Application Style..."));
//    QActionGroup* styleActionGroup = new QActionGroup(this);
//    menuStyles->addAction(m_defaultStyleAction);
//    styleActionGroup->addAction(m_defaultStyleAction);
//    menuStyles->addAction(m_fusionStyleAction);
//    styleActionGroup->addAction(m_fusionStyleAction);
//    menuStyles->addSeparator();
//    QAction* vs2019StyleAction = new QAction(tr("Visual Studio 2019"), this);
//    QMenu* menuVS2019Styles = new QMenu(this);
//    menuVS2019Styles->addAction(m_themeBlueAction);
//    styleActionGroup->addAction(m_themeBlueAction);
//    menuVS2019Styles->addAction(m_themeDarkAction);
//    styleActionGroup->addAction(m_themeDarkAction);
//    menuVS2019Styles->addAction(m_themeLightAction);
//    styleActionGroup->addAction(m_themeLightAction);
//    vs2019StyleAction->setMenu(menuVS2019Styles);
//    menuStyles->addAction(vs2019StyleAction);
//    connect(styleActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(styleChanged(QAction*)));
//}

void DCDockWindow::addSaveLoadMenu(QMenu* menu)
{
    menu->addAction(m_saveToolBarAction);
    menu->addAction(m_loadToolBarAction);
    menu->addSeparator();
    menu->addAction(m_savePanelAction);
    menu->addAction(m_loadPanelAction);
    menu->addSeparator();
    menu->addAction(m_autoSaveAction);
}

//void DCDockWindow::setCustomStyle(AppStyle appStyle)
//{
//    if (m_appStyle == appStyle)
//        return;

//    switch (appStyle)
//    {
//        case Default:
//        {
//            qApp->setStyle(m_defaultStyle);
//            m_defaultStyleAction->setChecked(true);
//            break;
//        }
//        case Fusion:
//        {
//            qApp->setStyle(QStringLiteral("fusion"));
//            m_fusionStyleAction->setChecked(true);
//            break;
//        }
//        case VS2019Blue:
//        {
//            VisualStudio2019Style* style = new VisualStudio2019Style();
//            style->setTheme(VisualStudio2019Style::Blue);
//            m_themeBlueAction->setChecked(true);
//            qApp->setStyle(style);
//            break;
//        }
//        case VS2019Dark:
//        {
//            VisualStudio2019Style* style = new VisualStudio2019Style();
//            style->setTheme(VisualStudio2019Style::Dark);
//            m_themeDarkAction->setChecked(true);
//            qApp->setStyle(style);
//            break;
//        }
//        case VS2019Light:
//        {
//            VisualStudio2019Style* style = new VisualStudio2019Style();
//            style->setTheme(VisualStudio2019Style::Light);
//            m_themeLightAction->setChecked(true);
//            qApp->setStyle(style);
//            break;
//        }
//    }
//    m_appStyle = appStyle;

//    if (m_styleComboBox != Q_NULL)
//        m_styleComboBox->setCurrentIndex(static_cast<int>(m_appStyle));
//}

void DCDockWindow::loadDockToolBarSettings(const QSettings& settings)
{
    QByteArray data = settings.value(DockBarSetting).toByteArray();
    if (!data.isEmpty())
    {
        QBuffer buffer(&data);
        if (!buffer.open(QIODevice::ReadOnly))
            Q_ASSERT(false);
        loadStateFromDevice(&buffer, Q_NULL);
    }
}

void DCDockWindow::saveDockToolBarSettings(QSettings& settings)
{
    QByteArray data;
    QBuffer buffer(&data);
    if (!buffer.open(QIODevice::WriteOnly))
        Q_ASSERT(false);

    saveStateToDevice(&buffer, Q_NULL);
    settings.setValue(DockBarSetting, QVariant(data));
}

void DCDockWindow::loadDockPanelSettings(const QSettings& settings)
{
    QByteArray data = settings.value(DockPanelSetting).toByteArray();
    if (!data.isEmpty())
    {
        QBuffer buffer(&data);
        if (!buffer.open(QIODevice::ReadOnly))
            Q_ASSERT(false);
        loadStateFromDevice(Q_NULL, &buffer);
    }
}

void DCDockWindow::saveDockPanelSettings(QSettings& settings)
{
    QByteArray data;
    QBuffer buffer(&data);
    if (!buffer.open(QIODevice::WriteOnly))
        Q_ASSERT(false);
    saveStateToDevice(Q_NULL, &buffer);
    settings.setValue(DockPanelSetting, QVariant(data));
}

void DCDockWindow::read_settings()
{
    QSettings settings(this);
    AppStyle appStyle = static_cast<AppStyle>(settings.value(QStringLiteral("style"), static_cast<int>(Default)).toInt());
    //setCustomStyle(appStyle);

    QByteArray byte = settings.value(QStringLiteral("geometry")).toByteArray();
    if (!byte.isEmpty())
        restoreGeometry(byte);

    loadDockToolBarSettings(settings);
    loadDockPanelSettings(settings);
}

void DCDockWindow::write_settings()
{
    QSettings settings(this);

    settings.setValue(QStringLiteral("style"), QString::number(static_cast<int>(0)));
    QByteArray byte = saveGeometry();
    settings.setValue(QStringLiteral("geometry"), byte);
    saveDockToolBarSettings(settings);
    saveDockPanelSettings(settings);
}
