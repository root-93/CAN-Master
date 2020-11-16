QT       += core gui serialbus testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/CommandKey.cpp \
    src/CompositeMenu.cpp \
    src/Controler.cpp \
    src/SubMenu.cpp \
    src/TableModel.cpp \
    src/UnitTest.cpp \
    src/candump.c \
    src/cangen.c \
    src/canplayer.c \
    src/cansend.c \
    src/cansniffer.c \
    src/lib.c \
    src/main.cpp \
    src/canmaster.cpp

HEADERS += \
    inc/BaseMenu.hpp \
    inc/CanUtils.hpp \
    inc/Command.hpp \
    inc/CommandBack.hpp \
    inc/CommandDefault.hpp \
    inc/CommandKey.hpp \
    inc/CompositeMenu.hpp \
    inc/Controler.hpp \
    inc/Global.hpp \
    inc/LeafMenu.hpp \
    inc/MenuContent.hpp \
    inc/MenuItem.hpp \
    inc/SubMenu.hpp \
    inc/TableModel.hpp \
    inc/UnitTest.h \
    inc/ViewActionData.hpp \
    inc/canmaster.h \
    inc/lib.h \
    inc/linux/can.h \
    inc/terminal.h \
    inc/Qt_global.h

INCLUDEPATH += $$PWD/inc

FORMS += \
    forms/canmaster.ui

LIBS += -L/usr/lib -lncurses -lboost_unit_test_framework

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bash/configure.sh \
    bash/setvcan0.sh
