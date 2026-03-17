QT += core gui widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Board.cpp \
    GameController.cpp \
    MainWindow.cpp \
    main.cpp

HEADERS += \
    Board.h \
    GameController.h \
    MainWindow.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
QMAKE_PROJECT_DEPTH = 0
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
QMAKE_MOC_OPTIONS += -I"D:/Qt/6.5.3/msvc2019_64/include"
!isEmpty(target.path): INSTALLS += target
