#ifndef NETWORKDEVICEPAGE_H
#define NETWORKDEVICEPAGE_H

#include <QWidget>
#include <DevMachines/QtitanGrid>
#include <QCheckBox>
#include <QStandardItemModel>

#define DEVICE_CARD_VIEW_LABEL_NUMBER  8

class NetworkDeviceModel
{
public:
    NetworkDeviceModel(){
        models << "2001" << "2002";
    }
    QStringList all(){
        return models;
    }
    int index(const QString& m)
    {
        return models.indexOf(m, 0);
    }
private:
    QStringList models;
};
class NetworkDeviceTable:public QObject
{
    Q_OBJECT
public:
    NetworkDeviceTable(Qtitan::CardGrid *parent = nullptr);
    void add_model_item(const QString& name, const QString& ip, const QString& model, \
                     const QString& firmware_version, const QString& describe, const QString& load_devices);
    QStandardItemModel* model();
    void init_label_photo(Qtitan::GridCardView* view);
    void init_label_model(Qtitan::GridCardView* view);
    void init_label_select(Qtitan::GridCardView* view);
private:
    QAbstractItemModel* create_model(QObject *parent);


private:
    Qtitan::CardGrid* m_grid;
    QStandardItemModel* m_model;
    const QString m_card_view_label[DEVICE_CARD_VIEW_LABEL_NUMBER] = {"Select", "Photo", "Name","IP","Model","Firmware Version","Describe", "Load Devices"};

};

class NetworkDevicePage : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkDevicePage(QWidget *parent = nullptr);

private Q_SLOTS:
    void setShadeColor(const QColor& color);
    void on_slot_finish_triggered(bool checked);
    void on_slot_refresh_triggered(bool checked);
Q_SIGNALS:
    void signal_finish_check();

private:
    Qtitan::CardGrid* m_grid;
    NetworkDeviceTable* m_table;
};

#endif // NETWORKDEVICEPAGE_H
