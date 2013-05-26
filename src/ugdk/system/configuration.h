#ifndef UGDK_SYSTEM_CONFIGURATION_H_
#define UGDK_SYSTEM_CONFIGURATION_H_

#include <string>
#include <ugdk/math/vector2D.h>

namespace ugdk {

typedef struct Configuration {
    std::string        base_path;
    std::string default_language;
    
    bool audio_enabled;
    
    bool graphic_enabled;
    std::string      window_icon;
    std::string     window_title;
    ugdk::math::Vector2D window_size;
    bool              fullscreen;

    bool input_enabled;

    Configuration() :
        base_path("./"),
        default_language("en_US"),

        audio_enabled(true),

        graphic_enabled(true),
        window_icon(""),
        window_title("UGDK Game"),
        window_size(800.0, 600.0),
        fullscreen(false),

        input_enabled(true) 
    {}
} Configuration;

} // namespace ugdk

#endif

