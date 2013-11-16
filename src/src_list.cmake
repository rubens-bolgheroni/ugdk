SET(UGDK_SRC 
    src/pyramidworks/collision.h 
    src/pyramidworks/collision/collisionclass.cc 
    src/pyramidworks/collision/collisionclass.h 
    src/pyramidworks/collision/collisionmanager.cc 
    src/pyramidworks/collision/collisionmanager.h 
    src/pyramidworks/collision/collisionobject.cc 
    src/pyramidworks/collision/collisionobject.h 
    src/pyramidworks/geometry.h 
    src/pyramidworks/geometry/circle.cc 
    src/pyramidworks/geometry/circle.h 
    src/pyramidworks/geometry/convexpolygon.cc 
    src/pyramidworks/geometry/convexpolygon.h 
    src/pyramidworks/geometry/geometricshape.h 
    src/pyramidworks/geometry/rect.cc 
    src/pyramidworks/geometry/rect.h 
    src/ugdk/action.h 
    src/ugdk/action/animationplayer.h 
    src/ugdk/action/entity.h 
    src/ugdk/action/mediamanager.h 
    src/ugdk/action/mediaplayer.cc 
    src/ugdk/action/mediaplayer.h 
    src/ugdk/action/observer.h 
    src/ugdk/action/scene.cc 
    src/ugdk/action/scene.h 
    src/ugdk/action/spriteanimationframe.h 
    src/ugdk/action/spritetypes.cc 
    src/ugdk/action/spritetypes.h 
    src/ugdk/audio.h 
    src/ugdk/audio/manager.cc 
    src/ugdk/audio/manager.h 
    src/ugdk/audio/module.cc 
    src/ugdk/audio/module.h 
    src/ugdk/audio/music.cc 
    src/ugdk/audio/music.h 
    src/ugdk/audio/sample.cc 
    src/ugdk/audio/sample.h 
    src/ugdk/desktop.h 
    src/ugdk/desktop/manager.cc 
    src/ugdk/desktop/manager.h 
    src/ugdk/desktop/module.cc 
    src/ugdk/desktop/module.h 
    src/ugdk/desktop/window.cc 
    src/ugdk/desktop/window.h 
    src/ugdk/desktop/windowsettings.cc 
    src/ugdk/desktop/windowsettings.h 
    src/ugdk/graphic.h 
    src/ugdk/graphic/defaultshaders.cc 
    src/ugdk/graphic/defaultshaders.h 
    src/ugdk/graphic/drawable.h 
    src/ugdk/graphic/drawable/functions.cc 
    src/ugdk/graphic/drawable/functions.h 
    src/ugdk/graphic/drawable/label.cc 
    src/ugdk/graphic/drawable/label.h 
    src/ugdk/graphic/drawable/sprite.cc 
    src/ugdk/graphic/drawable/sprite.h 
    src/ugdk/graphic/drawable/textbox.cc 
    src/ugdk/graphic/drawable/textbox.h 
    src/ugdk/graphic/drawable/texturedrectangle.cc 
    src/ugdk/graphic/drawable/texturedrectangle.h 
    src/ugdk/graphic/font.cc 
    src/ugdk/graphic/font.h 
    src/ugdk/graphic/geometry.h 
    src/ugdk/graphic/light.cc 
    src/ugdk/graphic/light.h 
    src/ugdk/graphic/manager.cc 
    src/ugdk/graphic/manager.h 
    src/ugdk/graphic/module.cc 
    src/ugdk/graphic/module.h 
    src/ugdk/graphic/node.cc 
    src/ugdk/graphic/node.h 
    src/ugdk/graphic/opengl/Exception.cc 
    src/ugdk/graphic/opengl/Exception.h 
    src/ugdk/graphic/opengl/shader.cc 
    src/ugdk/graphic/opengl/shader.h 
    src/ugdk/graphic/opengl/shaderprogram.cc 
    src/ugdk/graphic/opengl/shaderprogram.h 
    src/ugdk/graphic/opengl/vertexbuffer.cc 
    src/ugdk/graphic/opengl/vertexbuffer.h 
    src/ugdk/graphic/pixelsurface.h 
    src/ugdk/graphic/spritesheet.cc 
    src/ugdk/graphic/spritesheet.h 
    src/ugdk/graphic/spritesheetdata.cc 
    src/ugdk/graphic/spritesheetdata.h 
    src/ugdk/graphic/textmanager.cc 
    src/ugdk/graphic/textmanager.h 
    src/ugdk/graphic/texture.cc 
    src/ugdk/graphic/texture.h 
    src/ugdk/graphic/visualeffect.h 
    src/ugdk/input.h 
    src/ugdk/input/events.h 
    src/ugdk/input/keyboard.cc 
    src/ugdk/input/keyboard.h 
    src/ugdk/input/keycode.cc 
    src/ugdk/input/keycode.h 
    src/ugdk/input/manager.cc 
    src/ugdk/input/manager.h 
    src/ugdk/input/module.cc 
    src/ugdk/input/module.h 
    src/ugdk/input/mouse.cc 
    src/ugdk/input/mouse.h 
    src/ugdk/input/mousebutton.h 
    src/ugdk/input/scancode.h 
    src/ugdk/internal.h 
    src/ugdk/internal/sdleventdelegatorhandler.h 
    src/ugdk/internal/sdleventhandler.h 
    src/ugdk/math.h 
    src/ugdk/math/frame.cc 
    src/ugdk/math/frame.h 
    src/ugdk/math/integer2D.cc 
    src/ugdk/math/integer2D.h 
    src/ugdk/math/vector2D.cc 
    src/ugdk/math/vector2D.h 
    src/ugdk/resource.h 
    src/ugdk/resource/genericcontainer.h 
    src/ugdk/resource/manager.cc 
    src/ugdk/resource/manager.h 
    src/ugdk/resource/module.cc 
    src/ugdk/resource/module.h 
    src/ugdk/resource/resourcecontainer.h 
    src/ugdk/script.h 
    src/ugdk/script/baseproxy.h 
    src/ugdk/script/defs.h 
    src/ugdk/script/initscripts.cc 
    src/ugdk/script/langwrapper.h 
    src/ugdk/script/module.h 
    src/ugdk/script/scriptmanager.cc 
    src/ugdk/script/scriptmanager.h 
    src/ugdk/script/type.h 
    src/ugdk/script/virtualdata.h 
    src/ugdk/script/virtualobj.cc 
    src/ugdk/script/virtualobj.h 
    src/ugdk/script/virtualprimitive.h 
    src/ugdk/structure.h 
    src/ugdk/structure/box.h 
    src/ugdk/structure/indexabletable.h 
    src/ugdk/structure/intervalkdtree.h 
    src/ugdk/structure/types.h 
    src/ugdk/system.h 
    src/ugdk/system/configuration.cc 
    src/ugdk/system/configuration.h 
    src/ugdk/system/engine.cc 
    src/ugdk/system/engine.h 
    src/ugdk/system/eventhandler.h 
    src/ugdk/system/task.h 
    src/ugdk/system/taskplayer.cc 
    src/ugdk/system/taskplayer.h 
    src/ugdk/time.h 
    src/ugdk/time/manager.cc 
    src/ugdk/time/manager.h 
    src/ugdk/time/module.cc 
    src/ugdk/time/module.h 
    src/ugdk/time/timeaccumulator.cc 
    src/ugdk/time/timeaccumulator.h 
    src/ugdk/ui.h 
    src/ugdk/ui/button.cc 
    src/ugdk/ui/button.h 
    src/ugdk/ui/menu.cc 
    src/ugdk/ui/menu.h 
    src/ugdk/ui/uielement.cc 
    src/ugdk/ui/uielement.h 
    src/ugdk/util.h 
    src/ugdk/util/animationprotocol.cc 
    src/ugdk/util/animationprotocol.h 
    src/ugdk/util/gdd/descriptionprotocol.h 
    src/ugdk/util/gdd/descriptionprotocolbase.cc 
    src/ugdk/util/gdd/descriptionprotocolbase.h 
    src/ugdk/util/gdd/loader.h 
    src/ugdk/util/gdd/parser.cc 
    src/ugdk/util/gdd/parser.h 
    src/ugdk/util/gdd/parserutility.h 
    src/ugdk/util/gdd/reader.cc 
    src/ugdk/util/gdd/reader.h 
    src/ugdk/util/gdd/typeconverter.h 
    src/ugdk/util/gdd/typedargsconverter.h 
    src/ugdk/util/gdd/types.h 
    src/ugdk/util/idgenerator.cc 
    src/ugdk/util/idgenerator.h 
    src/ugdk/util/language.cc 
    src/ugdk/util/language.h 
    src/ugdk/util/languagemanager.cc 
    src/ugdk/util/languagemanager.h 
    src/ugdk/util/languageword.cc 
    src/ugdk/util/languageword.h 
    src/ugdk/util/uncopyable.h 
    src/ugdk/util/utf8.cc 
    src/ugdk/util/utf8.h 
)
