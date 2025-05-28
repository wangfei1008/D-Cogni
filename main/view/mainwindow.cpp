#include <QApplication>
#include <QScreen>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QHeaderView>
#include <QSpinBox>
#include <QLabel>
#include <QMdiArea>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QPainter>
#include <QDialog>
#include <QTreeWidget>
#include <QTableWidget>
#include <QTimer>
#include <QPaintEvent>
#include <QOpenGLFunctions>
#include <QMdiSubWindow>

#include "glwidget.h"
#include "mainwindow.h"
#include "ui_DynamicPanelsDialogForm.h"

#include "lib_handle.h"
/* MainWindow */
MainWindow::MainWindow()
    :m_formCount(0), m_openGLFormCount(0), m_treeCount(0), m_tableCount(0)
{
    connect(dockPanelManager(), SIGNAL(panelRequested(DockPanelRequestedArgs*)), this, SLOT(panelRequested(DockPanelRequestedArgs*)));

    createActions();
    create_menu();//创建菜单
    createToolBar();//创建工具栏
    create_panel();//创建面板
    createStatusBar();    
    create_mdiarea();//创建中间操作展示区句柄

    //connect(m_mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(subWindowActivated(QMdiSubWindow*)));

    QWidget* child = createMdiChild();
    //child->showMaximized();
    //child->setFocus();
    
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    const QRect availableGeometry = screen()->availableGeometry();
#else
    const QRect availableGeometry = QGuiApplication::primaryScreen()->availableGeometry();
#endif
    resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
    move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);

    read_settings();
}

MainWindow::~MainWindow()
{
    write_settings();
}

void MainWindow::createActions()
{
    m_fileNewAction = new QAction(QIcon(QStringLiteral(":/res/image/new16x16.png")), tr("&New"), this);
    m_fileNewAction->setShortcuts(QKeySequence::New);
    m_fileNewAction->setStatusTip(tr("Create a new document"));

    m_fileOpenAction = new QAction(QIcon(QStringLiteral(":/res/image/open16x16.png")), tr("&Open"), this);
    m_fileOpenAction->setShortcuts(QKeySequence::Open);
    m_fileOpenAction->setStatusTip(tr("Open an existing document"));

    m_fileSaveAction = new QAction(QIcon(QStringLiteral(":/res/image/save16x16.png")), tr("&Save..."), this);
    m_fileSaveAction->setShortcuts(QKeySequence::Save);
    m_fileSaveAction->setStatusTip(tr("Save the active document"));

    m_filePrintAction = new QAction(QIcon(QStringLiteral(":/res/image/print16x16.png")), tr("Print"), this);
    m_filePrintAction->setStatusTip(tr("Print the active document"));
    m_filePrintAction->setDisabled(true);
    m_filePrintAction->setDisabled(true);

    m_editCutAction = new QAction(QIcon(QStringLiteral(":/res/image/cut16x16.png")), tr("&Cut"), this);
    m_editCutAction->setShortcuts(QKeySequence::Cut);
    m_editCutAction->setStatusTip(tr("Cut the selection and put it on the Clipboard"));
    m_editCutAction->setDisabled(true);

    m_editCopyAction = new QAction(QIcon(QStringLiteral(":/res/image/copy16x16.png")), tr("&Copy"), this);
    m_editCopyAction->setShortcuts(QKeySequence::Copy);
    m_editCopyAction->setStatusTip(tr("Copy the selection and put it on the Clipboard"));
    m_editCopyAction->setDisabled(true);

    m_editUndoAction = new QAction(QIcon(QStringLiteral(":/res/image/undo16x16.png")), tr("Undo"), this);
    m_editUndoAction->setStatusTip(tr("Undo the last action"));
    m_editUndoAction->setDisabled(true);

    m_editRedoAction = new QAction(QIcon(QStringLiteral(":/res/image/redo16x16.png")), tr("Redo"), this);
    m_editRedoAction->setStatusTip(tr("Redo the previously undone action"));
    m_editRedoAction->setDisabled(true);

    m_createFormAction = new QAction(tr("Form"), this);
    connect(m_createFormAction, SIGNAL(triggered()), this, SLOT(slot_createForm()));
    m_createTreeAction = new QAction(tr("Tree"), this);
    connect(m_createTreeAction, SIGNAL(triggered()), this, SLOT(slot_createTree()));
    m_createTableAction = new QAction(tr("Table"), this);
    connect(m_createTableAction, SIGNAL(triggered()), this, SLOT(slot_createTable()));
    m_createOpenGLAction = new QAction(tr("OpenGL Form"), this);
    connect(m_createOpenGLAction, SIGNAL(triggered()), this, SLOT(slot_createOpenGL()));

    m_createThreeRowsAction = new QAction(tr("3(three) Rows"), this);
    connect(m_createThreeRowsAction, SIGNAL(triggered()), this, SLOT(slot_createThreeRows()));
    m_createThreeColumnsAction  = new QAction(tr("3(three) Columns"), this);
    connect(m_createThreeColumnsAction, SIGNAL(triggered()), this, SLOT(slot_createThreeColumns()));
    m_createThreeTabsAction = new QAction(tr("3(three) Tabs"), this);
    connect(m_createThreeTabsAction, SIGNAL(triggered()), this, SLOT(slot_createThreeTabs()));
}

void MainWindow::create_menu()
{
    m_menu_file = new menu_file(menuBar()->addMenu(tr("&File")));
    m_menu_view = new menu_view(menuBar()->addMenu(tr("&View")));
    connect(m_menu_view, &menu_view::signal_triggered, this, &MainWindow::slot_menu_view_triggered);
//    m_fileMenu = menuBar()->addMenu(tr("&File"));
//    m_fileMenu->addAction(m_createFormAction);
//    m_fileMenu->addAction(m_createTreeAction);
//    m_fileMenu->addAction(m_createTableAction);
//    m_fileMenu->addAction(m_createOpenGLAction);
//    m_fileMenu->addSeparator();
//    m_fileMenu->addAction(m_createThreeRowsAction);
//    m_fileMenu->addAction(m_createThreeColumnsAction);
//    m_fileMenu->addAction(m_createThreeTabsAction);

//    m_viewMenu = menuBar()->addMenu(tr("&View"));

    m_toolMenu = menuBar()->addMenu(tr("&Tools"));


 //   addSaveLoadMenu(m_viewMenu);
 //   m_viewMenu->addSeparator();
 //   addStyleMenu(m_viewMenu);

    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_helpMenu->addAction(m_aboutAction);
}

void MainWindow::create_panel()
{
    //list
    m_panel_list_project = new panel_list("Project", this);
    m_panel_map.insert("Project", m_panel_list_project->panel());
    m_panel_list_device = new panel_list("Device", this);
    m_panel_map.insert("Device", m_panel_list_device->panel());
    m_panel_list_moniter_device = new panel_list("Moniter device", this);
    m_panel_map.insert("Moniter device", m_panel_list_moniter_device->panel());
    dockPanelManager()->insertDockPanel(m_panel_list_project->panel(), QSize(250, 200), Qtitan::LeftDockPanelArea);
    dockPanelManager()->insertDockPanel(m_panel_list_device->panel(), QSize(250, 200), Qtitan::InsideDockPanelArea, m_panel_list_project->panel());
    dockPanelManager()->insertDockPanel(m_panel_list_moniter_device->panel(), QSize(250, 200), Qtitan::InsideDockPanelArea, m_panel_list_project->panel());

    //data
    m_panel_data_runing = new panel_data("Runing", this);                          //运行数据面板
    m_panel_map.insert("Runing", m_panel_data_runing->panel());
    m_panel_data_attribute = new panel_data("Attribute", this);                       //属性数据面板
    m_panel_map.insert("Attribute", m_panel_data_attribute->panel());
    m_panel_data_relationship = new panel_data("Relationship", this);                    //归属关系数据面板
    m_panel_map.insert("Relationship", m_panel_data_relationship->panel());
    dockPanelManager()->insertDockPanel(m_panel_data_runing->panel(), Qtitan::BottomDockPanelArea);
    dockPanelManager()->insertDockPanel(m_panel_data_attribute->panel(), Qtitan::InsideDockPanelArea, m_panel_data_runing->panel());
    dockPanelManager()->insertDockPanel(m_panel_data_relationship->panel(), Qtitan::InsideDockPanelArea, m_panel_data_runing->panel());

    //set
}

void MainWindow::create_mdiarea()
{
    m_mdiarea = new QMdiArea(this);
    m_mdiarea->setLineWidth(0);
    m_mdiarea->setViewMode(QMdiArea::SubWindowView);
    m_mdiarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_mdiarea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(m_mdiarea);
}

void MainWindow::createToolBar()
{
    m_fileToolBar = addToolBar(tr("Standard"), Qtitan::DockBarTop);
    m_fileToolBar->addAction(m_fileNewAction); 
    m_fileToolBar->addAction(m_fileOpenAction); 
    m_fileToolBar->addAction(m_fileSaveAction); 
    m_fileToolBar->addSeparator(); 
    m_fileToolBar->addAction(m_editCutAction);
    m_fileToolBar->addAction(m_editCopyAction);
    m_fileToolBar->addSeparator(); 
    m_fileToolBar->addAction(m_editUndoAction);
    m_fileToolBar->addAction(m_editRedoAction);
    m_fileToolBar->addSeparator(); 
    m_fileToolBar->addAction(m_filePrintAction);

    m_fileToolBar->addWidget(new QLabel(tr("   Style:")));
    //QAction* stylesAction = m_fileToolBar->addWidget(createComboBoxStyle());
    //stylesAction->setToolTip(tr("Styles switcher"));

    m_fileToolBar->addSeparator(); 
    m_fileToolBar->addAction(m_aboutAction);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

QWidget* MainWindow::createMdiChild()
{
    QWidget* child = NULL;
    lib_handle lib("chart_2d");
    for(int i = 0; i < 3; i++)
    {
        abstract_component* p = lib.create();
        QWidget* child = p->plot();

        QVector<double> x, y;
        x << 1 << 2 << 3;
        y << 20 << 30 << 50;
        p->set_data("www", x,y);

        y.clear();
        y << 2 << 4 << 2;
        p->set_data("ccc", x,y);

        y.clear();
        y << 8 << 6 << 4;
        p->set_data("aaaa", x,y);

        QMdiSubWindow* w = m_mdiarea->addSubWindow(child);
        w->setVisible(true);
    }
    return child;
}

void MainWindow::slot_createForm()
{
    DockWidgetPanel* form = createFormPanel();
    insertDockPanel(form, QSize(220, 200), Qtitan::RightDockPanelArea);
}

void MainWindow::slot_createTree()
{
//    DockWidgetPanel* tree = createTreePanel();
//    insertDockPanel(tree, QSize(220, 200), Qtitan::LeftDockPanelArea);
}

void MainWindow::slot_createTable()
{
//    DockWidgetPanel* table = createTablePanel();
//    insertDockPanel(table, QSize(220, 200), Qtitan::BottomDockPanelArea);
}

void MainWindow::slot_createOpenGL()
{
    DockWidgetPanel* openGL = createOpenGLPanel();
    insertDockPanel(openGL, QSize(220, 200), Qtitan::LeftDockPanelArea);
}

void MainWindow::slot_createThreeRows()
{
//    DockWidgetPanel* form = createFormPanel();
//    DockWidgetPanel* tree = createTreePanel();
//    DockWidgetPanel* table = createTablePanel();

//    insertDockPanel(form, QSize(220, 200), Qtitan::BottomDockPanelArea);
//    insertDockPanel(tree, QSize(220, 200), Qtitan::RightDockPanelArea, form);
//    insertDockPanel(table, QSize(220, 200), Qtitan::RightDockPanelArea, form);
}

void MainWindow::slot_createThreeColumns()
{
//    DockWidgetPanel* form = createFormPanel();
//    DockWidgetPanel* tree = createTreePanel();
//    DockWidgetPanel* table = createTablePanel();

//    insertDockPanel(form, QSize(220, 200), Qtitan::LeftDockPanelArea);
//    insertDockPanel(tree, QSize(220, 200), Qtitan::BottomDockPanelArea, form);
//    insertDockPanel(table, QSize(220, 200), Qtitan::BottomDockPanelArea, form);
}

void MainWindow::slot_createThreeTabs()
{
//    DockWidgetPanel* form = createFormPanel();
//    DockWidgetPanel* tree = createTreePanel();
//    DockWidgetPanel* table = createTablePanel();

//    insertDockPanel(form, QSize(220, 200), Qtitan::RightDockPanelArea);
//    insertDockPanel(tree, QSize(220, 200), Qtitan::InsideDockPanelArea, form);
//    insertDockPanel(table, QSize(220, 200), Qtitan::InsideDockPanelArea, form);
}

void MainWindow::panelRequested(DockPanelRequestedArgs* args)
{
    DockWidgetPanel* panel = Q_NULL;
    QString id = args->id();
    if (id.contains("form"))
        panel = createFormPanel();
//    else if (id.contains("tree"))
//        panel = createTreePanel();
//    else if (id.contains("table"))
//        panel = createTablePanel();
    else if (id.contains("opengl"))
        panel = createOpenGLPanel();
    else
        panel = new DockWidgetPanel(dockPanelManager()); //Default empty panel.
    
    if (panel != Q_NULL)
    {
        panel->setId(args->id());
        args->setPanel(panel);
        args->setHandled(true);
    }
}

void MainWindow::slot_menu_view_triggered(QString name, bool checked)
{
    auto panel = m_panel_map.find(name);
    if(panel == m_panel_map.end()) return;
    if(checked)
    {

    }
    else
    {
        dockPanelManager()->setDockPanelAutoHide(panel.value(), true);
    }
}

class DialogForm : public QDialog
{
public:
    DialogForm() { m_uiDialog.setupUi(this); }
    Ui::DialogForm m_uiDialog;
};

DockWidgetPanel* MainWindow::createFormPanel()
{
    DockWidgetPanel* panel = new DockWidgetPanel(tr("Form %1").arg(++m_formCount), dockPanelManager());
    DialogForm* dialog = new DialogForm();
    panel->setWidget(dialog);
    return panel;
}

DockWidgetPanel* MainWindow::createOpenGLPanel()
{
    DockWidgetPanel* panel = new DockWidgetPanel(tr("OpenGL %1").arg(++m_openGLFormCount), dockPanelManager());

    GLWidget* glWidget = new GLWidget(m_openGLFormCount, this);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, glWidget, &GLWidget::animate);
    timer->start(50);
    panel->setWidget(glWidget);
    return panel;
}

void MainWindow::read_settings()
{
    QSettings settings(this);
    menu_view_app_type::AppStyle app_style = static_cast<menu_view_app_type::AppStyle>(settings.value(QStringLiteral("style"), static_cast<int>(menu_view_app_type::AppStyle::Default)).toInt());
    m_menu_view->menu_view_app_stype()->set_app_style(app_style);

    QByteArray byte = settings.value(QStringLiteral("geometry")).toByteArray();
    if (!byte.isEmpty()) restoreGeometry(byte);

    loadDockToolBarSettings(settings);
    loadDockPanelSettings(settings);
}

void MainWindow::write_settings()
{
    QSettings settings(this);

    settings.setValue(QStringLiteral("style"), QString::number(static_cast<int>( m_menu_view->menu_view_app_stype()->app_type())));
    QByteArray byte = saveGeometry();
    settings.setValue(QStringLiteral("geometry"), byte);
    saveDockToolBarSettings(settings);
    saveDockPanelSettings(settings);
}
