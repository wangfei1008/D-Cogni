#ifndef MENU_VIEW_APP_TYPE_H
#define MENU_VIEW_APP_TYPE_H

#include <QMenu>
#include <QObject>
#include <QAction>

class menu_view_app_type : public QObject
{
    Q_OBJECT
public:
    enum AppStyle
    {
        Default     = 0,
        Fusion      = 1,
        VS2019Blue  = 2,
        VS2019Dark  = 3,
        VS2019Light = 4,
    };
public:
    explicit menu_view_app_type(QMenu* menu, QObject *parent = nullptr);
private:
    void add_actions();

    //设置APP显示风格
    void set_app_style(AppStyle style);
private Q_SLOTS:
    void slot_style_changed(QAction* action);
private:
    QMenu                  *m_menu;
    AppStyle               m_app_style;
    QString                m_default_style;
    QAction                *m_default;
    QAction                *m_fusion;
    QAction                *m_theme_blue;
    QAction                *m_theme_dark;
    QAction                *m_theme_light;
};

#endif // MENU_VIEW_APP_TYPE_H
