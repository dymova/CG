QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
TARGET = CircleDrawer

HEADERS += ./Circle.h \
    ./ConfigParser.h \
    ./Configuration.h \
    ./ConsoleModeController.h \
    ./JsonParserException.h \
    ./Serializer.h \
    ./Panel.h \
    ./Drawer.h \
    ./DrawPanel.h \
    ./MainWindow.h \
    ./GuiModeController.h \
    ./ControlPanel.h
SOURCES += ./Circle.cpp \
    ./ConsoleModeController.cpp \
    ./Drawer.cpp \
    ./ConfigParser.cpp \
    ./Configuration.cpp \
    ./ControlPanel.cpp \
    ./DrawPanel.cpp \
    ./GuiModeController.cpp \
    ./JsonParserException.cpp \
    ./main.cpp \
    ./MainWindow.cpp \
    ./Panel.cpp \
    ./Serializer.cpp

