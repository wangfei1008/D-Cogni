#ifndef RIBBONWINDOW_H
#define RIBBONWINDOW_H

#include <QSettings>
#include <QComboBox>
#include <QLabel>

#include <DevMachines/QtitanBase>
#include <DevMachines/QtitanDocking>
#include <DevMachines/QtitanFastInfoset>

class TitleBarCaption : public QLabel
{
    Q_OBJECT
public:
    explicit TitleBarCaption(const QString& productName, const QString& version, const QString& caption);
    ~TitleBarCaption() override;
protected:
    void mousePressEvent(QMouseEvent* event) override;
protected Q_SLOTS:
    void setLink(const QString& link)
    {
        m_link = link;
    }
private:
    QString m_link;
private:
    Q_DISABLE_COPY(TitleBarCaption)
};

class DCDockWindow: public DockMainWindow
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
    explicit DCDockWindow(QWidget* parent = Q_NULL);
    virtual ~DCDockWindow();
    WindowTitleBar* titleBar() const;
private Q_SLOTS:
    void saveToolBarToXML();
    void loadToolBarFromXML();
    void savePanelToXML();
    void loadPanelFromXML();
protected:
    void createActions();
 //   QComboBox* createComboBoxStyle();
//    void addStyleMenu(QMenu* menu);
    void addSaveLoadMenu(QMenu* menu);

//    void setCustomStyle(AppStyle appStyle);

    void loadDockToolBarSettings(const QSettings& settings);
    void saveDockToolBarSettings(QSettings& settings);

    void loadDockPanelSettings(const QSettings& settings);
    void saveDockPanelSettings(QSettings& settings);

    void read_settings();                                                //读取注册文件本执行程序配置
    void write_settings();                                               //对注册文件写本执行程序配置
protected Q_SLOTS:
    //void styleChanged(QAction* action);
    void styleIndexChanged(int index);
    void about();
protected:
//    AppStyle m_appStyle;
//    QString m_defaultStyle;
//    QComboBox* m_styleComboBox;

    QAction* m_saveToolBarAction;
    QAction* m_loadToolBarAction;
    QAction* m_savePanelAction;
    QAction* m_loadPanelAction;
    QAction* m_autoSaveAction;

    QAction* m_aboutAction;

//    QAction* m_defaultStyleAction;
//    QAction* m_fusionStyleAction;
//    QAction* m_themeBlueAction;
//    QAction* m_themeDarkAction;
//    QAction* m_themeLightAction;
private:
    Q_DISABLE_COPY(DCDockWindow)
};

#endif // RIBBONWINDOW_H
