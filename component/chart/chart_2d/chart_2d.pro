
QT += core gui widgets opengl printsupport

TEMPLATE = lib

CONFIG += \
         c++11\
         skip_target_version_ext                  #避免在dll文件的名字里面自动加数字

# 作为编译器C预处理器宏(-D选项)
# QT_DEPRECATED_WARNINGS表示当Qt的某些功能被标记为过时的，那么编译器会发出警告。
DEFINES += QT_DEPRECATED_WARNINGS\
           EXPORT_LIBRARY

#应用程序图表
#RC_ICONS          = $$PWD/res/image/logo.ico

#应用程序名称
#TARGET            = chart_2d

#######################################################
#程序版本信息定义
#######################################################
#程序版本
VERSION                  = 2024.12.16.01
#公司名称
QMAKE_TARGET_COMPANY     = "orient"
#产品名称
QMAKE_TARGET_PRODUCT     = $$TARGET
#版权所有
QMAKE_TARGET_COPYRIGHT   = "orient ltd. All rights reserved."
#文件说明
QMAKE_TARGET_DESCRIPTION = "base on QCustomPlot Chart Component"
DEFINES += SDK_VERSION=$$VERSION

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
Debug::DESTDIR    += $$PWD/../../bin/debug
Release::DESTDIR  += $$PWD/../../bin/release

include( $$PWD/../../../../cf/base/base.pri )

#依赖文件夹
INCLUDEPATH   += \
                $$PWD/../../../base\
                $$PWD/data\
                $$PWD/view\
                $$PWD/business\
                $$PWD/third

HEADERS       += \
                business/concrete_mediator.h \
                business/mediator.h \
                business/plot_business_data.h \
                business/property_json.h \
                chart_2d.h\
                component_lib.h\
                data/chart_constants.h \
                data/chart_macros.h \
                data/chart_typedef.h \
                data/property_data.h \
                third/qcustomplot.h \
                view/channel_map.h \
                view/plot_widget.h \
                view/property_widget.h

SOURCES       += \
                business/concrete_mediator.cpp \
                business/mediator.cpp \
                business/plot_business_data.cpp \
                business/property_json.cpp \
                chart_2d.cpp\
                component_lib.cpp\
                data/chart_constants.cpp \
                data/property_data.cpp \
                third/qcustomplot.cpp \
                view/channel_map.cpp \
                view/plot_widget.cpp \
                view/property_widget.cpp


#FORMS         += \
#                ui/property.ui


RESOURCES     += \
                chart_2d.qrc

DISTFILES      += \
                 readme.json\
                 readme.md

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
