#ifndef WINDOW_H
#define WINDOW_H

#include <QCheckBox>
#include <QPushButton>
#include <QTimer>
#include <QLCDNumber>
#include <DevMachines/QtitanNavigationDesignUI>

class ColorPickerButton;

class ProjectWindow : public NavigationMainWindow
{
    Q_OBJECT
public:
    ProjectWindow();
    QWidget* createSettingsWidget();
    void updateSettings();
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
protected Q_SLOTS:
    void showTime();
    void blendChecked(bool);
    void extendViewChecked(bool);
    void materialOpacityChanged(int value);
private:
    void createContent();
    MaterialWidget* m_materialWidget;
    QLCDNumber* m_clockWidget;
    QTimer m_timer;
};


#endif
