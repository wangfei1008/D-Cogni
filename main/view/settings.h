#ifndef SETTINGS_H
#define SETTINGS_H

#include <DevMachines/QtitanStyle>
#include <DevMachines/QtitanNavigationDesignUI>

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    SettingsWidget(QWidget* parent);
    void updateSettings();
protected Q_SLOTS:
    void areaActivated(int index);
    void themeActivated(int index);
private:
    ColorPickerButton* m_windowColorPicker;
    ColorPickerButton* m_windowTextColorPicker;
    ColorPickerButton* m_materialColorColorPicker;
    ColorPickerButton* m_tileMenuColorPicker;
    ColorPickerButton* m_menuColorPicker;
    ColorPickerButton* m_linkColorPicker;
    ColorPickerButton* m_itemColorPicker;
    ColorPickerButton* m_itemTextColorPicker;
    ColorPickerButton* m_captionColorPicker;
};

#endif //SETTINGS_H


