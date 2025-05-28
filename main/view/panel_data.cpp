#include "panel_data.h"
#include <QTableWidget>
#include <QHeaderView>

panel_data::panel_data(const QString& name,  DCDockWindow* dock, QObject *parent)
    : panel_base(name, dock, parent)
{
    create(name);
}

int panel_data::create(const QString &name)
{
    QTableWidget* tableWidget = new QTableWidget;
    tableWidget->setAlternatingRowColors(true);
    tableWidget->setColumnCount(11);
    tableWidget->setRowCount(6);
    tableWidget->setShowGrid(false);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Name")));
    tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Path")));
    tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Optimized")));
    tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("User Code")));
    tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem(tr("Symbol Status")));
    tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem(tr("Symbol File")));
    tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem(tr("Order")));
    tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem(tr("Version")));
    tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem(tr("Timestamp")));
    tableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem(tr("Addresswewe")));
    tableWidget->setHorizontalHeaderItem(10, new QTableWidgetItem(tr("Process")));

    int height = tableWidget->horizontalHeader()->sizeHint().height();

    tableWidget->setRowHeight(0, height);
    tableWidget->setVerticalHeaderItem(0, new QTableWidgetItem(QIcon(QStringLiteral(":/res/modules.png")),tr("")));
    tableWidget->setItem(0, 0, new QTableWidgetItem(tr("ntdll.dll")));
    tableWidget->setItem(0, 1, new QTableWidgetItem(tr("C:/Windows/System32/ntdll.dll")));
    tableWidget->setItem(0, 2, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(0, 3, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(0, 4, new QTableWidgetItem(tr("Symbols loaded.")));
    tableWidget->setItem(0, 5, new QTableWidgetItem(tr("C:/Qtitan/customstyles.pdb")));
    tableWidget->setItem(0, 6, new QTableWidgetItem(tr("1")));
    tableWidget->setItem(0, 7, new QTableWidgetItem(tr("6.1.7600.16385 (win7_rtm.090713-1255)")));
    tableWidget->setItem(0, 8, new QTableWidgetItem(tr("27.10.2010 8:32")));
    tableWidget->setItem(0, 9, new QTableWidgetItem(tr("773A0000-774DD000")));
    tableWidget->setItem(0, 10, new QTableWidgetItem(tr("[3376] customstyles.exe: Native")));

    tableWidget->setRowHeight(1, height);
    tableWidget->setVerticalHeaderItem(1, new QTableWidgetItem(QIcon(QStringLiteral(":/res/modules.png")),tr("")));
    tableWidget->setItem(1, 0, new QTableWidgetItem(tr("ntdll.dll")));
    tableWidget->setItem(1, 1, new QTableWidgetItem(tr("C:/Windows/System32/kernel32.dll")));
    tableWidget->setItem(1, 2, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(1, 3, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(1, 4, new QTableWidgetItem(tr("No symbols loaded.")));
    tableWidget->setItem(1, 5, new QTableWidgetItem(tr("")));
    tableWidget->setItem(1, 6, new QTableWidgetItem(tr("2")));
    tableWidget->setItem(1, 7, new QTableWidgetItem(tr("6.1.7600.16385 (win7_rtm.090713-1255)")));
    tableWidget->setItem(1, 8, new QTableWidgetItem(tr("27.10.2010 8:32")));
    tableWidget->setItem(1, 9, new QTableWidgetItem(tr("872A0000-766DD000")));
    tableWidget->setItem(1, 10, new QTableWidgetItem(tr("[3376] customstyles.exe: Native")));

    tableWidget->setRowHeight(2, height);
    tableWidget->setVerticalHeaderItem(2, new QTableWidgetItem(QIcon(QStringLiteral(":/res/modules.png")),tr("")));
    tableWidget->setItem(2, 0, new QTableWidgetItem(tr("kernelBase.dll")));
    tableWidget->setItem(2, 1, new QTableWidgetItem(tr("C:/Windows/System32/kernelBase.dll")));
    tableWidget->setItem(2, 2, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(2, 3, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(2, 4, new QTableWidgetItem(tr("No symbols loaded.")));
    tableWidget->setItem(2, 5, new QTableWidgetItem(tr("")));
    tableWidget->setItem(2, 6, new QTableWidgetItem(tr("3")));
    tableWidget->setItem(2, 7, new QTableWidgetItem(tr("6.1.7600.16385 (win7_rtm.090713-1255)")));
    tableWidget->setItem(2, 8, new QTableWidgetItem(tr("08.10.2010 8:32")));
    tableWidget->setItem(2, 9, new QTableWidgetItem(tr("772A0000-566DD000")));
    tableWidget->setItem(2, 10, new QTableWidgetItem(tr("[3376] customstyles.exe: Native")));

    tableWidget->setRowHeight(3, height);
    tableWidget->setVerticalHeaderItem(3, new QTableWidgetItem(QIcon(QStringLiteral(":/res/modules.png")),tr("")));
    tableWidget->setItem(3, 0, new QTableWidgetItem(tr("QtCoreed4.dll")));
    tableWidget->setItem(3, 1, new QTableWidgetItem(tr("C:/Qt/4.6.2/Bin/QtCored4.dll")));
    tableWidget->setItem(3, 2, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(3, 3, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(3, 4, new QTableWidgetItem(tr("Symbols loaded.")));
    tableWidget->setItem(3, 5, new QTableWidgetItem(tr("C:/Qt/4.6.2/lib/QtCored4.pdb")));
    tableWidget->setItem(3, 6, new QTableWidgetItem(tr("4")));
    tableWidget->setItem(3, 7, new QTableWidgetItem(tr("6.1.7600.16385 (win7_rtm.090713-1255)")));
    tableWidget->setItem(3, 8, new QTableWidgetItem(tr("08.10.2010 8:32")));
    tableWidget->setItem(3, 9, new QTableWidgetItem(tr("772A0000-566DD000")));
    tableWidget->setItem(3, 10, new QTableWidgetItem(tr("[3376] customstyles.exe: Native")));

    tableWidget->setRowHeight(4, height);
    tableWidget->setVerticalHeaderItem(4, new QTableWidgetItem(QIcon(QStringLiteral(":/res/modules.png")),tr("")));
    tableWidget->setItem(4, 0, new QTableWidgetItem(tr("user32.dll")));
    tableWidget->setItem(4, 1, new QTableWidgetItem(tr("C:/Windows/System32/user32.dll")));
    tableWidget->setItem(4, 2, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(4, 3, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(4, 4, new QTableWidgetItem(tr("No symbols loaded.")));
    tableWidget->setItem(4, 5, new QTableWidgetItem(tr("")));
    tableWidget->setItem(4, 6, new QTableWidgetItem(tr("3")));
    tableWidget->setItem(4, 7, new QTableWidgetItem(tr("6.1.7600.16385 (win7_rtm.090713-1255)")));
    tableWidget->setItem(4, 8, new QTableWidgetItem(tr("08.10.2010 8:32")));
    tableWidget->setItem(4, 9, new QTableWidgetItem(tr("552A0000-544AD000")));
    tableWidget->setItem(4, 10, new QTableWidgetItem(tr("[3376] customstyles.exe: Native")));

    tableWidget->setRowHeight(5, height);
    tableWidget->setVerticalHeaderItem(5, new QTableWidgetItem(QIcon(QStringLiteral(":/res/modules.png")),tr("")));
    tableWidget->setItem(5, 0, new QTableWidgetItem(tr("usp10.dll")));
    tableWidget->setItem(5, 1, new QTableWidgetItem(tr("C:/Windows/System32/usp10.dll")));
    tableWidget->setItem(5, 2, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(5, 3, new QTableWidgetItem(tr("N/A")));
    tableWidget->setItem(5, 4, new QTableWidgetItem(tr("No symbols loaded.")));
    tableWidget->setItem(5, 5, new QTableWidgetItem(tr("")));
    tableWidget->setItem(5, 6, new QTableWidgetItem(tr("3")));
    tableWidget->setItem(5, 7, new QTableWidgetItem(tr("6.1.7600.16385 (win7_rtm.090713-1255)")));
    tableWidget->setItem(5, 8, new QTableWidgetItem(tr("08.10.2010 8:32")));
    tableWidget->setItem(5, 9, new QTableWidgetItem(tr("552A0000-544AD000")));
    tableWidget->setItem(5, 10, new QTableWidgetItem(tr("[3376] customstyles.exe: Native")));

    set_widget(tableWidget);
    return 0;
}
