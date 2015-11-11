TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SRCDIR = "src"

INCLUDEPATH += "$$SRCDIR/window" \
    "$$SRCDIR/application" \
    "$$SRCDIR/utils" \
    "$$SRCDIR/game"

HEADERS += $$SRCDIR/window/gamewindow.h \
    src/window/windowmanager.h \
    src/utils/debugutils.h \
    src/application/app.h \
    src/game/game.h \
    src/typedef/apptypes.h \
    src/utils/timeutils.h

SOURCES += src/main.cpp $$SRCDIR/window/gamewindow.cpp \
    src/window/windowmanager.cpp \
    src/utils/debugutils.cpp \
    src/application/app.cpp \
    src/game/game.cpp \
    src/utils/timeutils.cpp

LIBS += -L"$$PWD/SFML/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "SFML/include"
DEPENDPATH += "SFML/include"
