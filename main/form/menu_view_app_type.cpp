#include "menu_view_app_type.h"
#include <QtWidgets>
#include <DevMachines/QtitanBase>
#include <DevMachines/QtitanDocking>

menu_view_app_type::menu_view_app_type(QMenu* menu, QObject *parent)
    : QObject{parent}
    , m_menu(menu)
    , m_app_style(Default)
    , m_default_style(QString())
{
    if (QProxyStyle* proxy = qobject_cast<QProxyStyle*>(qApp->style()))
        m_default_style = proxy->baseStyle()->objectName();

    add_actions();

    set_app_style(VS2019Blue);
}

void menu_view_app_type::add_actions()
{
    QMenu* menu = m_menu->addMenu(tr("Application Style..."));
    QActionGroup* style_group = new QActionGroup(this);

    m_default = new QAction(tr("Default"), this);
    m_default->setCheckable(true);
    m_default->setChecked(false);
    menu->addAction(m_default);
    style_group->addAction(m_default);

    m_fusion = new QAction(tr("Fusion"), this);
    m_fusion->setCheckable(true);
    m_fusion->setChecked(false);
    menu->addAction(m_fusion);
    style_group->addAction(m_fusion);

    menu->addSeparator();

    QAction* vs_2019 = new QAction(tr("Visual Studio 2019"), this);
    QMenu* menu_vs_2019 = new QMenu();
    m_theme_blue = new QAction(tr("Blue"), this);
    m_theme_blue->setCheckable(true);
    m_theme_blue->setChecked(false);
    menu_vs_2019->addAction(m_theme_blue);
    style_group->addAction(m_theme_blue);

    m_theme_dark = new QAction(tr("Dark"), this);
    m_theme_dark->setCheckable(true);
    m_theme_dark->setChecked(false);
    menu_vs_2019->addAction(m_theme_dark);
    style_group->addAction(m_theme_dark);

    m_theme_light = new QAction(tr("Light"), this);
    m_theme_light->setCheckable(true);
    m_theme_light->setChecked(false);
    menu_vs_2019->addAction(m_theme_light);
    style_group->addAction(m_theme_light);

    vs_2019->setMenu(menu_vs_2019);
    menu->addAction(vs_2019);

    connect(style_group, SIGNAL(triggered(QAction*)), this, SLOT(slot_style_changed(QAction*)));
}

void menu_view_app_type::set_app_style(AppStyle style)
{
    if (m_app_style == style)
        return;

    switch (style)
    {
        case Default:
        {
            qApp->setStyle(m_default_style);
            m_default->setChecked(true);
            break;
        }
        case Fusion:
        {
            qApp->setStyle(QStringLiteral("fusion"));
            m_fusion->setChecked(true);
            break;
        }
        case VS2019Blue:
        {
            VisualStudio2019Style* style = new VisualStudio2019Style();
            style->setTheme(VisualStudio2019Style::Blue);
            m_theme_blue->setChecked(true);
            qApp->setStyle(style);
            break;
        }
        case VS2019Dark:
        {
            VisualStudio2019Style* style = new VisualStudio2019Style();
            style->setTheme(VisualStudio2019Style::Dark);
            m_theme_dark->setChecked(true);
            qApp->setStyle(style);
            break;
        }
        case VS2019Light:
        {
            VisualStudio2019Style* style = new VisualStudio2019Style();
            style->setTheme(VisualStudio2019Style::Light);
            m_theme_light->setChecked(true);
            qApp->setStyle(style);
            break;
        }
    }
    m_app_style = style;
}

void menu_view_app_type::slot_style_changed(QAction *action)
{
    AppStyle style = Default;
    if (m_fusion == action)
        style = Fusion;
    else if (m_theme_blue == action)
        style = VS2019Blue;
    else if (m_theme_light == action)
        style = VS2019Light;
    else if (m_theme_dark == action)
        style = VS2019Dark;

    set_app_style(style);
}
