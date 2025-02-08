#QtitanComponents2023.1.0环境设置
QT_VERSION = $$[QT_VERSION]
QT_VERSION = $$split(QT_VERSION, ".")
QT_VER_MAJ = $$member(QT_VERSION, 0)
QT_VER_MIN = $$member(QT_VERSION, 1)

QTN_OPENGL_DISABLED=1

!qtitan_no_private {
  greaterThan(QT_MAJOR_VERSION, 4):CONFIG+=private_headers
}

private_headers {
  DEFINES += QTN_PRIVATE_HEADERS
}

equals(QTN_OPENGL_DISABLED, 1) {
  CONFIG+=opengl_disabled
}

!opengl_disabled {
  DEFINES += QTN_OPENGL_ENABLED
}

defineReplace(toNativeSeparators) {
    return($$replace(1, /, $$QMAKE_DIR_SEP))
}
defineReplace(fromNativeSeparators) {
    return($$replace(1, \\\\, /))
}

defineReplace(cleanPath) {
    win32:1 ~= s|\\\\|/|g
    contains(1, ^/.*):pfx = /
    else:pfx =
    segs = $$split(1, /)
    out =
    for(seg, segs) {
        equals(seg, ..):out = $$member(out, 0, -2)
        else:!equals(seg, .):out += $$seg
    }
    return($$join(out, /, $$pfx))
}

RCC = $$toNativeSeparators($$cleanPath($$[QT_INSTALL_BINS]/rcc))
LRELEASE = $$toNativeSeparators($$cleanPath($$[QT_INSTALL_BINS]/lrelease))
LUPDATE = $$toNativeSeparators($$cleanPath($$[QT_INSTALL_BINS]/lupdate))
LCONVERT = $$toNativeSeparators($$cleanPath($$[QT_INSTALL_BINS]/lconvert))
QMAKE_BINARY = $$toNativeSeparators($$cleanPath($$[QT_INSTALL_BINS]/qmake))

win32 {
    RCC = $${RCC}.exe
    LRELEASE = $${LRELEASE}.exe
    LUPDATE = $${LUPDATE}.exe
    LCONVERT = $${LCONVERT}.exe
    QMAKE_BINARY = $${QMAKE_BINARY}.exe
}

win32 {
    DEFINES += _WINDOWS
}

!no_mp {
    unix|win32-g++ {
        #QMAKE_CXXFLAGS += -j8
    } else {
        QMAKE_CXXFLAGS += -MP
    }
}

DEFINES += QTN_NAMESPACE

unix|win32-g++ {
    #QMAKE_CXXFLAGS += -Wsuggest-override
    QMAKE_CXXFLAGS += -Wno-inconsistent-missing-override
}

python {
    include($$PWD/python.pri)
    python_debug:QTN_OUTPUT_DIR=$$PYSIDE_DIR/../DevMachines
    else:QTN_OUTPUT_DIR=$$PWD/../../site-packages/DevMachines
} else {
    QTN_OUTPUT_DIR=$$PWD/../../bin$$QTITAN_LIB_PREFIX
}

remove_rpath {
    linux {
        #QMAKE_RPATHDIR = $ORIGIN
        QMAKE_LFLAGS_RPATH=
        QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\'"
    }
    macx {
        QMAKE_LFLAGS_RPATH=
        QMAKE_LFLAGS += "-Wl,-rpath,@loader_path"
        QMAKE_LFLAGS_SONAME = -Wl,-install_name,@rpath/
    }
}

designer_rpath {
    linux {
        #QMAKE_RPATHDIR = $ORIGIN../../lib
        QMAKE_LFLAGS_RPATH=
        QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN/../../lib\'"
    }
    macx {
        QMAKE_LFLAGS_RPATH=
        QMAKE_LFLAGS += "-Wl,-rpath,@executable_path/Frameworks"
        QMAKE_LFLAGS += "-Wl,-rpath,@loader_path/../../lib"
    }
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

############################################################################################################
#
#
#
############################################################################################################
#qt工程设置

QT += core gui
CONFIG += c++17

# 作为编译器C预处理器宏(-D选项)
# QT_DEPRECATED_WARNINGS表示当Qt的某些功能被标记为过时的，那么编译器会发出警告。
DEFINES += QT_DEPRECATED_WARNINGS

#应用程序图表
RC_ICONS          = $$PWD/res/image/logo.ico

#应用程序名称
TARGET            = D-Cogni

#指定包含用户界面翻译文本的翻译(.ts)文件列表。
#TRANSLATIONS += $$PWD/res/myapp_zh.ts \
#                $$PWD/res/myapp_en.ts

#moc,rcc,ui,obj编译文件的输出路径
#CONFIG            -= debug_and_release
#MOC_DIR           += $$PWD/tmp/moc
#RCC_DIR           += $$PWD/tmp/res
#UI_DIR            += $$PWD/tmp/ui
#OBJECTS_DIR       += $$PWD/tmp/obj

#应用程序输出路径
Debug::DESTDIR    += $$PWD/../bin/debug
Release::DESTDIR  += $$PWD/../bin/release

#基础依赖文件
include( $$PWD/../../cf/base/base.pri )
#依赖文件夹
INCLUDEPATH   += \
                $$PWD/../base\
                $$PWD/business

#动态库的依赖
INCLUDEPATH   += \
                $$PWD/../thrid/QtitanComponents2023.1.0/include
LIBPATH       += \
                $$PWD/../thrid/QtitanComponents2023.1.0/lib
CONFIG(debug, debug|release)
{
    LIBS      += \
                 -lQtitanBased2\
                 -lQtitanChartd6\
                 -lQtitanChartDesignerd6\
                 -lQtitanDockingd4\
                 -lQtitanFastInfosetd2\
                 -lQtitanGridd7\
                 -lQtitanStyled2\
                 -lQtitanRibbond6\
                 -lQtitanRibbonDesignerd6
}
CONFIG(release, debug|release)
{
    LIBS      += \
                 -lQtitanBase2\
                 -lQtitanChart6\
                 -lQtitanDockingd4\
                 -lQtitanFastInfoset2\
                 -lQtitanGrid7\
                 -lQtitanStyle2\
                 -lQtitanRibbon6
}
win32
{
    CONFIG(debug, debug|release)
    {
    }
    CONFIG(release, debug|release)
    {
    }
}
unix
{
    CONFIG(debug, debug|release)
    {
    }
    CONFIG(release, debug|release)
    {
    }
}


#依赖文件夹
INCLUDEPATH   += \
                $$PWD/form

HEADERS       = business/lib_handle.h\
                form/mainwindow.h\
                form/aboutdialog.h \
                form/dock_window.h \
                form/glwidget.h \
                form/menu_file.h \
                form/menu_view.h \
                form/menu_view_app_type.h \
                form/panel_base.h \
                form/panel_data.h \
                form/panel_list.h

SOURCES       = business/lib_handle.cpp\
                src/main.cpp \
                form/dock_window.cpp \
                form/glwidget.cpp \
                form/mainwindow.cpp\
                form/aboutdialog.cpp \
                form/menu_file.cpp \
                form/menu_view.cpp \
                form/menu_view_app_type.cpp \
                form/panel_base.cpp \
                form/panel_data.cpp \
                form/panel_list.cpp

FORMS         += \
                res/mainwindow.ui\
                res/DynamicPanelsDialogForm.ui

RESOURCES     += \
                main.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
