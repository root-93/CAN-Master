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
    src/FilterDump.cpp \
    src/FilterSniff.cpp \
    src/Stack.cpp \
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
    inc/Filter.hpp \
    inc/FilterDump.hpp \
    inc/FilterSniff.hpp \
    inc/MenuCli/BaseMenu.hpp \
    inc/CanUtils.hpp \
    inc/MenuCli/Command.hpp \
    inc/MenuCli/CommandBack.hpp \
    inc/MenuCli/CommandDefault.hpp \
    inc/MenuCli/CommandKey.hpp \
    inc/MenuCli/CompositeMenu.hpp \
    inc/MenuCli/Controler.hpp \
    inc/Global.hpp \
    inc/MenuCli/LeafMenu.hpp \
    inc/MenuCli/MenuContent.hpp \
    inc/MenuCli/MenuItem.hpp \
    inc/MenuCli/SubMenu.hpp \
    inc/Stack.hpp \
    inc/TableModel.hpp \
    inc/UnitTest.h \
    inc/MenuCli/ViewActionData.hpp \
    inc/canmaster.h \
    inc/lib.h \
    inc/linux/can.h \
    inc/terminal.h \
    inc/Qt_global.h

FORMS += \
    forms/canmaster.ui

INCLUDEPATH += $$PWD/inc/MenuCli $$PWD/inc

LIBS += -L/usr/lib -lncurses -lboost_unit_test_framework

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bash/configure.sh \
    bash/setvcan0.sh
