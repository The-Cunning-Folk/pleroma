TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SRCDIR = "src"

INCLUDEPATH += "SFML/include" \
    "$$SRCDIR/window" \
    "$$SRCDIR/application" \
    "$$SRCDIR/utils" \
    "$$SRCDIR/game" \
    "$$SRCDIR/game/geometry" \
    "$$SRCDIR/input" \
    "$$SRCDIR/components" \
    "$$SRCDIR/gameobject" \
    "$$SRCDIR/factories" \
    "$$SRCDIR/engines" \
    "$$SRCDIR/shapes" \
    "$$SRCDIR/logic" \
    "$$SRCDIR/logic/behaviours" \
    "$$SRCDIR/loaders" \
    "$$SRCDIR/structures"\
    "$$SRCDIR/managers"\
    "$$SRCDIR/geometry" \
    "$$SRCDIR/graphics" \
    "$$SRCDIR/environment"\
    "$$SRCDIR/data"\
    "$$SRCDIR/patterns"

HEADERS += $$SRCDIR/window/gamewindow.h \
    src/window/windowmanager.h \
    src/utils/debugutils.h \
    src/application/app.h \
    src/game/game.h \
    src/typedef/apptypes.h \
    src/utils/timeutils.h \
    src/geometry/grid.h \
    src/utils/mathsutils.h \
    src/utils/logger.h \
    src/utils/loggerfactory.h \
    src/input/inputmap.h \
    src/input/keyinput.h \
    src/gameobject/gameobject.h \
    src/components/component.h \
    src/factories/gameobjectfactory.h \
    src/components/transform.h \
    src/factories/componentfactory.h \
    src/factories/factory.h \
    src/engines/engine.h \
    src/engines/transformengine.h \
    src/shapes/crossshape.h \
    src/shapes/customshape.h \
    src/components/playerinput.h \
    src/engines/inputengine.h \
    src/engines/eventengine.h \
    src/logic/event.h \
    src/factories/eventfactory.h \
    src/input/basicinput.h \
    src/input/buttoninput.h \
    src/factories/inputfactory.h \
    src/input/controller.h \
    src/input/joystickinput.h \
    src/logic/behaviours/behaviour.h \
    src/logic/behaviours/playerbehaviours.h \
    src/components/gamelogic.h \
    src/components/collidable.h \
    src/engines/collisionengine.h \
    src/loaders/componentloader.h \
    src/structures/quadtreenode.h \
    src/structures/quadtree.h \
    src/engines/debugdisplayengine.h \
    src/structures/convexpolygon.h \
    src/structures/projection.h \
    src/loaders/resourceloader.h \
    src/structures/indexedboundingbox.h \
    src/structures/mtv.h \
    src/logic/collision.h \
    src/loaders/gameobjectloader.h \
    src/components/rigidbody.h \
    src/engines/physicsengine.h \
    src/factories/physicseventfactory.h \
    src/logic/physicalcollision.h \
    src/window/viewport.h \
    src/managers/occlusionmanager.h \
    src/engines/pathingengine.h \
    src/geometry/gridsquare.h \
    src/logic/behaviours/flowpathingbehaviours.h \
    src/engines/logicengine.h \
    src/engines/raycastingengine.h \
    src/structures/simpleray.h \
    src/structures/lineintersection.h \
    src/components/rayemitter.h \
    src/graphics/spritesheet.h \
    src/components/spriterenderer.h \
    src/engines/renderengine.h \
    src/graphics/frame.h \
    src/graphics/animation.h \
    src/environment/level.h \
    src/environment/tilemap.h \
    src/environment/tile.h \
    src/environment/tilelayer.h \
    src/graphics/sprite.h \
    src/data/datafileparser.h \
    src/patterns/gameobjectpattern.h \
    src/patterns/spriterendererpattern.h \
    src/patterns/collidablepattern.h \
    src/patterns/rigidbodypattern.h \
    src/patterns/factorypattern.h \
    src/patterns/rayemitterpattern.h \
    src/patterns/gamelogicpattern.h \
    src/environment/scene.h \
    src/gameobject/gameobjectstore.h

SOURCES += src/main.cpp \
    $$SRCDIR/window/gamewindow.cpp \
    src/window/windowmanager.cpp \
    src/utils/debugutils.cpp \
    src/application/app.cpp \
    src/game/game.cpp \
    src/utils/timeutils.cpp \
    src/geometry/grid.cpp \
    src/utils/mathsutils.cpp \
    src/utils/logger.cpp \
    src/utils/loggerfactory.cpp \
    src/input/inputmap.cpp \
    src/input/keyinput.cpp \
    src/gameobject/gameobject.cpp \
    src/components/component.cpp \
    src/factories/gameobjectfactory.cpp \
    src/components/transform.cpp \
    src/factories/componentfactory.cpp \
    src/factories/factory.cpp \
    src/engines/engine.cpp \
    src/engines/transformengine.cpp \
    src/shapes/crossshape.cpp \
    src/shapes/customshape.cpp \
    src/components/playerinput.cpp \
    src/engines/inputengine.cpp \
    src/engines/eventengine.cpp \
    src/logic/event.cpp \
    src/factories/eventfactory.cpp \
    src/input/basicinput.cpp \
    src/input/buttoninput.cpp \
    src/factories/inputfactory.cpp \
    src/input/controller.cpp \
    src/input/joystickinput.cpp \
    src/logic/behaviours/behaviour.cpp \
    src/logic/behaviours/playerbehaviours.cpp \
    src/components/gamelogic.cpp \
    src/components/collidable.cpp \
    src/engines/collisionengine.cpp \
    src/loaders/componentloader.cpp \
    src/structures/quadtreenode.cpp \
    src/structures/quadtree.cpp \
    src/engines/debugdisplayengine.cpp \
    src/structures/convexpolygon.cpp \
    src/structures/projection.cpp \
    src/loaders/resourceloader.cpp \
    src/structures/indexedboundingbox.cpp \
    src/structures/mtv.cpp \
    src/logic/collision.cpp \
    src/loaders/gameobjectloader.cpp \
    src/components/rigidbody.cpp \
    src/engines/physicsengine.cpp \
    src/factories/physicseventfactory.cpp \
    src/logic/physicalcollision.cpp \
    src/window/viewport.cpp \
    src/managers/occlusionmanager.cpp \
    src/engines/pathingengine.cpp \
    src/geometry/gridsquare.cpp \
    src/logic/behaviours/flowpathingbehaviours.cpp \
    src/engines/logicengine.cpp \
    src/engines/raycastingengine.cpp \
    src/structures/simpleray.cpp \
    src/structures/lineintersection.cpp \
    src/components/rayemitter.cpp \
    src/graphics/spritesheet.cpp \
    src/components/spriterenderer.cpp \
    src/engines/renderengine.cpp \
    src/graphics/frame.cpp \
    src/graphics/animation.cpp \
    src/environment/level.cpp \
    src/environment/tilemap.cpp \
    src/environment/tile.cpp \
    src/environment/tilelayer.cpp \
    src/graphics/sprite.cpp \
    src/data/datafileparser.cpp \
    src/patterns/gameobjectpattern.cpp \
    src/patterns/spriterendererpattern.cpp \
    src/patterns/collidablepattern.cpp \
    src/patterns/rigidbodypattern.cpp \
    src/patterns/factorypattern.cpp \
    src/patterns/rayemitterpattern.cpp \
    src/patterns/gamelogicpattern.cpp \
    src/environment/scene.cpp \
    src/gameobject/gameobjectstore.cpp

LIBS += -L"$$PWD/SFML/lib"


unix {
# Copies the given files to the destination directory
copydata.commands = $(COPY_DIR) $$PWD/var $$OUT_PWD
}

win32 {
# Copies the given files to the destination directory
PWD_WIN = $${PWD}
PWD_WIN ~= s,/,\\,g

OUT_WIN = $${OUT_PWD}
OUT_WIN ~= s,/,\\,g
copydata.commands = $(COPY_DIR) $$PWD_WIN\var $$OUT_WIN\var
}

first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

OBJECTS_DIR=obj #Intermediate object files directory
MOC_DIR=moc #Intermediate moc files directory


CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "SFML/include"
DEPENDPATH += "SFML/include"
INCLUDEPATH += "include"
DEPENDPATH += "include"
