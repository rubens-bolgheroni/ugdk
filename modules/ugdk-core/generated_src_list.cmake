SET(GENERATED_SRC
modules/ugdk-core/src/action/mediaplayer.cc
modules/ugdk-core/src/action/scene.cc
modules/ugdk-core/src/audio/manager.cc
modules/ugdk-core/src/audio/module.cc
modules/ugdk-core/src/audio/music.cc
modules/ugdk-core/src/audio/sample.cc
modules/ugdk-core/src/debug/log.cc
modules/ugdk-core/src/debug/profiler.cc
modules/ugdk-core/src/desktop/manager.cc
modules/ugdk-core/src/desktop/module.cc
modules/ugdk-core/src/desktop/windowsettings.cc
modules/ugdk-core/src/input/keyboard.cc
modules/ugdk-core/src/input/keycode.cc
modules/ugdk-core/src/input/manager.cc
modules/ugdk-core/src/input/module.cc
modules/ugdk-core/src/input/mouse.cc
modules/ugdk-core/src/input/textinput.cc
modules/ugdk-core/src/math/frame.cc
modules/ugdk-core/src/math/integer2D.cc
modules/ugdk-core/src/math/vector2D.cc
modules/ugdk-core/src/pyramidworks/collision/collisionclass.cc
modules/ugdk-core/src/pyramidworks/collision/collisionmanager.cc
modules/ugdk-core/src/pyramidworks/collision/collisionobject.cc
modules/ugdk-core/src/pyramidworks/geometry/circle.cc
modules/ugdk-core/src/pyramidworks/geometry/convexpolygon.cc
modules/ugdk-core/src/pyramidworks/geometry/rect.cc
modules/ugdk-core/src/resource/manager.cc
modules/ugdk-core/src/resource/module.cc
modules/ugdk-core/src/system/configuration.cc
modules/ugdk-core/src/system/engine.cc
modules/ugdk-core/src/system/LoveException.cc
modules/ugdk-core/src/system/sdleventhandler.h
modules/ugdk-core/src/system/taskplayer.cc
modules/ugdk-core/src/time/manager.cc
modules/ugdk-core/src/time/module.cc
modules/ugdk-core/src/time/timeaccumulator.cc
modules/ugdk-core/src/util/idgenerator.cc
modules/ugdk-core/src/util/utf8.cc
)
SET(GENERATED_HEADERS
modules/ugdk-core/include/pyramidworks/collision.h
modules/ugdk-core/include/pyramidworks/collision/collisionclass.h
modules/ugdk-core/include/pyramidworks/collision/collisiondata.h
modules/ugdk-core/include/pyramidworks/collision/collisionmanager.h
modules/ugdk-core/include/pyramidworks/collision/collisionobject.h
modules/ugdk-core/include/pyramidworks/geometry.h
modules/ugdk-core/include/pyramidworks/geometry/circle.h
modules/ugdk-core/include/pyramidworks/geometry/convexpolygon.h
modules/ugdk-core/include/pyramidworks/geometry/geometricshape.h
modules/ugdk-core/include/pyramidworks/geometry/rect.h
modules/ugdk-core/include/ugdk/action.h
modules/ugdk-core/include/ugdk/action/animationplayer.h
modules/ugdk-core/include/ugdk/action/events.h
modules/ugdk-core/include/ugdk/action/mediamanager.h
modules/ugdk-core/include/ugdk/action/mediaplayer.h
modules/ugdk-core/include/ugdk/action/observer.h
modules/ugdk-core/include/ugdk/action/scene.h
modules/ugdk-core/include/ugdk/audio.h
modules/ugdk-core/include/ugdk/audio/manager.h
modules/ugdk-core/include/ugdk/audio/module.h
modules/ugdk-core/include/ugdk/audio/music.h
modules/ugdk-core/include/ugdk/audio/sample.h
modules/ugdk-core/include/ugdk/debug.h
modules/ugdk-core/include/ugdk/debug/log.h
modules/ugdk-core/include/ugdk/debug/profiler.h
modules/ugdk-core/include/ugdk/desktop.h
modules/ugdk-core/include/ugdk/desktop/manager.h
modules/ugdk-core/include/ugdk/desktop/module.h
modules/ugdk-core/include/ugdk/desktop/window.h
modules/ugdk-core/include/ugdk/desktop/windowsettings.h
modules/ugdk-core/include/ugdk/graphic.h
modules/ugdk-core/include/ugdk/input.h
modules/ugdk-core/include/ugdk/input/events.h
modules/ugdk-core/include/ugdk/input/keyboard.h
modules/ugdk-core/include/ugdk/input/keycode.h
modules/ugdk-core/include/ugdk/input/manager.h
modules/ugdk-core/include/ugdk/input/module.h
modules/ugdk-core/include/ugdk/input/mouse.h
modules/ugdk-core/include/ugdk/input/mousebutton.h
modules/ugdk-core/include/ugdk/input/scancode.h
modules/ugdk-core/include/ugdk/input/textinput.h
modules/ugdk-core/include/ugdk/internal.h
modules/ugdk-core/include/ugdk/math.h
modules/ugdk-core/include/ugdk/math/frame.h
modules/ugdk-core/include/ugdk/math/integer2D.h
modules/ugdk-core/include/ugdk/math/vector2D.h
modules/ugdk-core/include/ugdk/resource.h
modules/ugdk-core/include/ugdk/resource/genericcontainer.h
modules/ugdk-core/include/ugdk/resource/manager.h
modules/ugdk-core/include/ugdk/resource/module.h
modules/ugdk-core/include/ugdk/resource/resourcecontainer.h
modules/ugdk-core/include/ugdk/script.h
modules/ugdk-core/include/ugdk/structure.h
modules/ugdk-core/include/ugdk/structure/box.h
modules/ugdk-core/include/ugdk/structure/indexabletable.h
modules/ugdk-core/include/ugdk/structure/intervalkdtree.h
modules/ugdk-core/include/ugdk/structure/types.h
modules/ugdk-core/include/ugdk/system.h
modules/ugdk-core/include/ugdk/system/compatibility.h
modules/ugdk-core/include/ugdk/system/configuration.h
modules/ugdk-core/include/ugdk/system/engine.h
modules/ugdk-core/include/ugdk/system/eventhandler.h
modules/ugdk-core/include/ugdk/system/exceptions.h
modules/ugdk-core/include/ugdk/system/LoveException.h
modules/ugdk-core/include/ugdk/system/task.h
modules/ugdk-core/include/ugdk/system/taskplayer.h
modules/ugdk-core/include/ugdk/text.h
modules/ugdk-core/include/ugdk/time.h
modules/ugdk-core/include/ugdk/time/manager.h
modules/ugdk-core/include/ugdk/time/module.h
modules/ugdk-core/include/ugdk/time/timeaccumulator.h
modules/ugdk-core/include/ugdk/ui.h
modules/ugdk-core/include/ugdk/util.h
modules/ugdk-core/include/ugdk/util/idgenerator.h
modules/ugdk-core/include/ugdk/util/uncopyable.h
modules/ugdk-core/include/ugdk/util/utf8.h
)