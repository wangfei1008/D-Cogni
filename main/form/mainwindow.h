#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#define OLD_GLWidget


#include <QMenu>
#include <QMdiArea>
#include "dock_window.h"
#include "menu_file.h"
#include "menu_view.h"
#include "panel_list.h"
#include "panel_data.h"


/* MainWindow */
class MainWindow : public DCDockWindow
{
    Q_OBJECT
public:
    explicit MainWindow();
    virtual ~MainWindow();
private:
    void createActions();
    void create_menu();
    void create_panel();
    void create_mdiarea();

    void createToolBar();
    void createStatusBar();
    QWidget* createMdiChild();
protected Q_SLOTS:
    void slot_createForm();
    void slot_createTree();
    void slot_createTable();
    void slot_createOpenGL();
    void slot_createThreeRows();
    void slot_createThreeColumns();
    void slot_createThreeTabs();
    void panelRequested(DockPanelRequestedArgs* args);
private Q_SLOTS:
    void slot_menu_view_triggered(QString name, bool checked);
protected:
    DockWidgetPanel* createFormPanel();
    DockWidgetPanel* createOpenGLPanel();
private:
    QMdiArea                          *m_mdiarea;                                     //中间窗口资源句柄

    //菜单
    menu_file                         *m_menu_file;                                   //文件操作菜单
    menu_view                         *m_menu_view;                                   //可视化菜单

    //面板
    panel_list                        *m_panel_list_project;                         //工程列表面板
    panel_list                        *m_panel_list_device;                          //全设备列表面板
    panel_list                        *m_panel_list_moniter_device;                 //监控设备列表面板
    panel_data                        *m_panel_data_runing;                          //运行数据面板
    panel_data                        *m_panel_data_attribute;                       //属性数据面板
    panel_data                        *m_panel_data_relationship;                    //归属关系数据面板
    QMap<QString, DockWidgetPanel*>   m_panel_map;                                    //面板名称与面板资源的map表

    //QMenu* m_fileMenu;
    QMenu* m_toolMenu;
    //QMenu* m_viewMenu;
    QMenu* m_helpMenu;

    DockToolBar* m_fileToolBar;

    QAction* m_fileNewAction;
    QAction* m_fileOpenAction;
    QAction* m_fileSaveAction;
    QAction* m_filePrintAction;
    QAction* m_editCutAction;
    QAction* m_editCopyAction;
    QAction* m_editUndoAction;
    QAction* m_editRedoAction;

    QAction* m_createFormAction;
    QAction* m_createTreeAction;
    QAction* m_createTableAction;
    QAction* m_createOpenGLAction;

    QAction* m_createThreeRowsAction;
    QAction* m_createThreeColumnsAction;
    QAction* m_createThreeTabsAction;

    int m_formCount;
    int m_openGLFormCount;
    int m_treeCount;
    int m_tableCount;
private:
    Q_DISABLE_COPY(MainWindow);
};



#endif
