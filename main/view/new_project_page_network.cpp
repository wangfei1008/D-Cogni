#include <QtGui>
#include <QDesktopServices>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "new_project_page_network.h"


static QPixmap get_device_model_photo(const QString &model)
{
    if(model.compare("2001"))
        return QPixmap(QStringLiteral(":res/image/device/2001.png"));
    if(model.compare("2002"))
        return QPixmap(QStringLiteral(":res/image/device/2002.png"));

    return QPixmap(QStringLiteral(":res/image/device/new_device.png"));
}

NetworkDeviceTable::NetworkDeviceTable(Qtitan::CardGrid *parent)
    :QObject(parent)
    ,m_grid(parent)
{
    m_model = new QStandardItemModel(0, DEVICE_CARD_VIEW_LABEL_NUMBER, parent);

    for(int i = 0; i < DEVICE_CARD_VIEW_LABEL_NUMBER; i++)
        m_model->setHeaderData(i, Qt::Horizontal, m_card_view_label[i]);

}

void NetworkDeviceTable::add_model_item(const QString &name, const QString &ip, const QString &model, const QString &firmware_version, const QString &describe, const QString &load_devices)
{
    int row = m_model->rowCount();
    m_model->insertRow(row);

    m_model->setData(m_model->index(row, 0), true);
    m_model->setData(m_model->index(row, 1), get_device_model_photo(model));
    m_model->setData(m_model->index(row, 2), name);
    m_model->setData(m_model->index(row, 3), ip);
    NetworkDeviceModel model_options;
    m_model->setData(m_model->index(row, 4), model_options.index(model));
    m_model->setData(m_model->index(row, 5), firmware_version);
    m_model->setData(m_model->index(row, 6), describe);
    m_model->setData(m_model->index(row, 7), load_devices);
    Qtitan::GridCardView* view = m_grid->view<Qtitan::GridCardView>();

    init_label_select(view);
    init_label_photo(view);
    init_label_model(view);
}

QStandardItemModel *NetworkDeviceTable::model()
{
    return m_model;
}

void NetworkDeviceTable::init_label_photo(Qtitan::GridCardView* view)
{
    GridCardColumn* column = static_cast<GridCardColumn *>(view->getColumnByModelColumn(1));
    if(column == NULL) return;
    column->setEditorType(GridEditor::Picture);
    column->setRowSpan(4);
    QVariant defValue = GridPictureEditorRepository::convertToVariant(QVariant::ByteArray, QPixmap(QStringLiteral(":res/image/device/new_device.png")));
    column->editorRepository()->setDefaultValue(defValue, Qt::DisplayRole);
    column->editorRepository()->setDefaultValue(defValue, Qt::EditRole);
}

void NetworkDeviceTable::init_label_model(GridCardView *view)
{
    GridCardColumn* column = static_cast<GridCardColumn *>(view->getColumnByModelColumnName(m_card_view_label[4]));
    if(column == NULL) return;
    column->setEditorType(GridEditor::ComboBox);
    QStringListModel* titleModel = new QStringListModel(column);
    NetworkDeviceModel model_options;
    titleModel->setStringList(model_options.all());
    column->dataBinding()->setRelationModel(titleModel);
}

void NetworkDeviceTable::init_label_select(GridCardView *view)
{
    GridCardColumn* column = static_cast<GridCardColumn *>(view->getColumnByModelColumn(0));
    if(column == NULL) return;
    column->setEditorType(GridEditor::CheckBox);
    column->editorRepository()->setDefaultValue(true, Qt::DisplayRole);
    column->editorRepository()->setDefaultValue(true, Qt::EditRole);
}

NetworkDevicePage::NetworkDevicePage(QWidget *parent)
    : QWidget{parent}
{
    Grid::loadTranslation();

    m_grid = new Qtitan::CardGrid();
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *layout_h = new QHBoxLayout(this);
    QToolButton* refresh = new QToolButton(this);
    refresh->setIcon(QIcon(":/res/image/refresh16x16.png"));
    refresh->setAutoRaise(true);
    connect(refresh, &QToolButton::triggered, this, &NetworkDevicePage::on_slot_refresh_triggered);

    layout_h->addWidget(refresh);
    layout_h->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum ));
    QToolButton* finish = new QToolButton(this);
    finish->setIcon(QIcon(":/res/image/finish16x16.png"));
    finish->setAutoRaise(true);
    connect(finish, &QToolButton::clicked, this, &NetworkDevicePage::on_slot_finish_triggered);
    layout_h->addWidget(finish);
    layout->addLayout(layout_h);
    layout->addWidget(m_grid);

    // Configure grid view
    m_grid->setViewType(Qtitan::CardGrid::CardView);
    Qtitan::GridCardView* view = m_grid->view<Qtitan::GridCardView>();
    view->beginUpdate();

    m_table = new NetworkDeviceTable(m_grid);

    view->options().setGroupsHeader(false);
    view->options().setNewRowPlace(Qtitan::AtEnd);

    view->options().setPreviewRowExpandStyle(GridViewOptions::PreviewExpandButton);//设置显示
    view->options().setSelectionPolicy(GridViewOptions::MultiRowSelection);//设置多行选择
    view->options().setRubberBandSelection(false);

    view->setModel(m_table->model());

    view->endUpdate();
    view->bestFit();

    m_table->add_model_item("device1", "192.168.1.2", "2001", "2024.12.1.01", "modbus device", "temp1\ntemp2\n");
    m_table->add_model_item("device2", "192.168.1.3", "2001", "2024.12.1.01", "modbus device", "temp1\ntemp2\n");
    m_table->add_model_item("device3", "192.168.1.4", "2002", "2024.12.1.01", "modbus device", "temp1\ntemp2\n");
    m_table->add_model_item("device4", "192.168.1.5", "2002", "2024.12.1.01", "modbus device", "temp1\ntemp2\n");
}


void NetworkDevicePage::setShadeColor(const QColor& color)
{
    m_grid->themeManager()->setShadeColor(color);
}

void NetworkDevicePage::on_slot_finish_triggered(bool checked)
{
    Q_EMIT signal_finish_check();
}

void NetworkDevicePage::on_slot_refresh_triggered(bool checked)
{

}
