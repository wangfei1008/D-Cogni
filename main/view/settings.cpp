
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>

#include "settings.h"

/* SettingsWidget */
SettingsWidget::SettingsWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* l = new QVBoxLayout(this);
    l->setSizeConstraint(QLayout::SetFixedSize);
    l->setAlignment(Qt::AlignCenter);
    l->setSpacing(20);

    ColorizedStyle* style = qobject_cast<ColorizedStyle*>(qApp->style());
    if (style == Q_NULL)
        return;

    QLabel* label = new QLabel();
    label->setText(tr("Navigation Theme:"));
    QComboBox* themeComboBox = new QComboBox();
    themeComboBox->addItem(tr("Light"));
    themeComboBox->addItem(tr("Dark"));
    themeComboBox->addItem(tr("Blue"));
    themeComboBox->addItem(tr("Light Blue"));
    themeComboBox->addItem(tr("Red"));
    themeComboBox->addItem(tr("Custom"));
    connect(themeComboBox, SIGNAL(activated(int)), this, SLOT(themeActivated(int)));
    label->setBuddy(themeComboBox);
    QHBoxLayout* hl = new QHBoxLayout();
    hl->addWidget(label);
    hl->addWidget(themeComboBox);
    l->addLayout(hl);

#if 1
    label = new QLabel();
    label->setText(tr("Navigation Area:"));
    QComboBox* areComboBox = new QComboBox();
    areComboBox->addItem(tr("Top"));
    areComboBox->addItem(tr("Left"));
    areComboBox->addItem(tr("Right"));
    areComboBox->addItem(tr("Bottom"));
    connect(areComboBox, SIGNAL(activated(int)), this, SLOT(areaActivated(int)));
    label->setBuddy(areComboBox);
    hl = new QHBoxLayout(0);
    hl->addWidget(label);
    hl->addWidget(areComboBox);
    l->addLayout(hl);
#endif

    label = new QLabel();
    label->setText(tr("Window Color:"));
    m_windowColorPicker = new ColorPickerButton();
    connect(m_windowColorPicker, SIGNAL(colorSelected(const QColor&)),
        style, SLOT(setWindowColor(const QColor&)));
    label->setBuddy(m_windowColorPicker);
    hl = new QHBoxLayout(0);
    hl->addWidget(label);
    hl->addWidget(m_windowColorPicker);
    l->addLayout(hl);

    label = new QLabel();
    label->setText(tr("Window Text Color:"));
    m_windowTextColorPicker = new ColorPickerButton();
    connect(m_windowTextColorPicker, SIGNAL(colorSelected(const QColor&)),
        style, SLOT(setWindowTextColor(const QColor&)));
    label->setBuddy(m_windowTextColorPicker);
    hl = new QHBoxLayout(0);
    hl->addWidget(label);
    hl->addWidget(m_windowTextColorPicker);
    l->addLayout(hl);

    label = new QLabel();
    label->setText(tr("Material Color:"));
    m_materialColorColorPicker = new ColorPickerButton();
    connect(m_materialColorColorPicker, SIGNAL(colorSelected(const QColor&)),
        style, SLOT(setMaterialColor(const QColor&)));
    label->setBuddy(m_materialColorColorPicker);
    hl = new QHBoxLayout(0);
    hl->addWidget(label);
    hl->addWidget(m_materialColorColorPicker);
    l->addLayout(hl);

    label = new QLabel();
    label->setText(tr("Tile Menu Color:"));
    m_tileMenuColorPicker = new ColorPickerButton();
    connect(m_tileMenuColorPicker, SIGNAL(colorSelected(const QColor&)), style, SLOT(setTileMenuColor(const QColor&)));
    label->setBuddy(m_tileMenuColorPicker);
    hl = new QHBoxLayout(0);
    hl->addWidget(label);
    hl->addWidget(m_tileMenuColorPicker);
    l->addLayout(hl);

    label = new QLabel();
    label->setText(tr("Menu Color:"));
    m_menuColorPicker = new ColorPickerButton();
    connect(m_menuColorPicker, SIGNAL(colorSelected(const QColor&)), style, SLOT(setMenuColor(const QColor&)));
    label->setBuddy(m_menuColorPicker);
    hl = new QHBoxLayout(0);
    hl->addWidget(label);
    hl->addWidget(m_menuColorPicker);
    l->addLayout(hl);

    label = new QLabel();
    label->setText(tr("Link Color:"));
    m_linkColorPicker = new ColorPickerButton();
    connect(m_linkColorPicker, SIGNAL(colorSelected(const QColor&)), style, SLOT(setLinkColor(const QColor&)));
    label->setBuddy(m_linkColorPicker);
    hl = new QHBoxLayout(0);
    hl->addWidget(label);
    hl->addWidget(m_linkColorPicker);
    l->addLayout(hl);

    label = new QLabel();
    label->setText(tr("Item Color:"));
    m_itemColorPicker = new ColorPickerButton();
    connect(m_itemColorPicker, SIGNAL(colorSelected(const QColor&)), style, SLOT(setItemColor(const QColor&)));
    label->setBuddy(m_itemColorPicker);
    hl = new QHBoxLayout(0);
    hl->addWidget(label);
    hl->addWidget(m_itemColorPicker);
    l->addLayout(hl);

    label = new QLabel();
    label->setText(tr("Item Text Color:"));
    m_itemTextColorPicker = new ColorPickerButton();
    connect(m_itemTextColorPicker, SIGNAL(colorSelected(const QColor&)), style, SLOT(setItemTextColor(const QColor&)));
    label->setBuddy(m_itemTextColorPicker);
    hl = new QHBoxLayout(0);
    hl->addWidget(label);
    hl->addWidget(m_itemTextColorPicker);
    l->addLayout(hl);

    label = new QLabel();
    label->setText(tr("Caption Color:"));
    m_captionColorPicker = new ColorPickerButton();
    connect(m_captionColorPicker, SIGNAL(colorSelected(const QColor&)), style, SLOT(setCaptionColor(const QColor&)));
    label->setBuddy(m_captionColorPicker);
    hl = new QHBoxLayout(0);
    hl->addWidget(label);
    hl->addWidget(m_captionColorPicker);
    l->addLayout(hl);

    updateSettings();
}

void SettingsWidget::updateSettings()
{
    ColorizedStyle* style = qobject_cast<ColorizedStyle*>(qApp->style());
    if (style == Q_NULL)
        return;
    m_windowColorPicker->setColor(style->windowColor());
    m_windowTextColorPicker->setColor(style->windowTextColor());
    m_materialColorColorPicker->setColor(style->materialColor());
    m_tileMenuColorPicker->setColor(style->tileMenuColor());
    m_menuColorPicker->setColor(style->menuColor());
    m_linkColorPicker->setColor(style->linkColor());
    m_itemColorPicker->setColor(style->itemColor());
    m_itemTextColorPicker->setColor(style->itemTextColor());
    m_captionColorPicker->setColor(style->captionColor());
}

void SettingsWidget::areaActivated(int index)
{
    NavigationMainWindow* w = qobject_cast<NavigationMainWindow*>(window());
    if (w == Q_NULL)
        return;

    if (index == 0)
    {
        w->setNavigationBarArea(Qtitan::TopArea);
    }
    else if (index == 1)
        w->setNavigationBarArea(Qtitan::LeftArea);
    else if (index == 2)
        w->setNavigationBarArea(Qtitan::RightArea);
    else
        w->setNavigationBarArea(Qtitan::BottomArea);
}

void SettingsWidget::themeActivated(int index)
{
    ColorizedStyle* style = qobject_cast<ColorizedStyle*>(qApp->style());
    if (style == Q_NULL)
        return;
    style->setTheme((ColorizedStyle::Theme)index);
    updateSettings();
}
