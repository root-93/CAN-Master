QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CommandKey.cpp \
    CompositeMenu.cpp \
    Controler.cpp \
    SubMenu.cpp \
    candump.c \
    cangen.c \
    canplayer.c \
    cansend.c \
    cansniffer.c \
    lib.c \
    main.cpp \
    canmaster.cpp

HEADERS += \
    BaseMenu.hpp \
    CanUtils.hpp \
    Command.hpp \
    CommandBack.hpp \
    CommandDefault.hpp \
    CommandKey.hpp \
    CompositeMenu.hpp \
    Controler.hpp \
    Global.hpp \
    LeafMenu.hpp \
    MenuContent.hpp \
    MenuItem.hpp \
    SubMenu.hpp \
    ViewActionData.hpp \
    canmaster.h \
    lib.h \
    terminal.h

FORMS += \
    canmaster.ui

LIBS += -L/usr/lib -lncurses

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bash/configure.sh \
    bash/setvcan0.sh
