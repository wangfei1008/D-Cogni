QT += gui

TEMPLATE = lib
DEFINES += EXPORT_LIBRARY

CONFIG += c++17 staticlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#######################################################
#程序版本信息定义
#######################################################
#程序版本
VERSION = 2024.12.16.01
#公司名称
QMAKE_TARGET_COMPANY = "orient"
#产品名称
QMAKE_TARGET_PRODUCT = TARGET
#版权所有
QMAKE_TARGET_COPYRIGHT = "orient LTD. All rights reserved."
#文件说明
QMAKE_TARGET_DESCRIPTION = "based on Component"
DEFINES += SDK_VERSION=$$VERSION


HEADERS += \
    abstract_component.h \
    data_base.h \
    export_global.h


INCLUDEPATH += \
           $$PWD/../base

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#应用程序输出路径
Debug::DESTDIR    += $$PWD/../bin/debug
Release::DESTDIR  += $$PWD/../bin/release

