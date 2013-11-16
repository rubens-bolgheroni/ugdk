#ifndef UGDK_DESKTOP_WINDOW_H_
#define UGDK_DESKTOP_WINDOW_H_

#include <string>
#include <ugdk/math/integer2D.h>
#include <ugdk/desktop.h>

struct SDL_Window;

namespace ugdk {
namespace desktop {

class Window {
  private:
    Window(SDL_Window* sdl_window, const std::string& title, const math::Integer2D& size, bool fullscreen);

  public:
    ~Window();

    /// Presents the current canvas in the screen.
    void Present();

    /// Updates the settings and applies the changes.
    /** Warning: some fullscreen/resolution combinations may be unsupported by the display, resulting
        in unoperable windows. */
    void ChangeSettings(const math::Integer2D& size, bool fullscreen);

    const std::string& title() const { return title_; }
    const math::Integer2D& size() const { return size_; }
    bool fullscreen() const { return fullscreen_; }

  private:
    SDL_Window* sdl_window_;
    std::string title_;
    math::Integer2D size_;
    bool fullscreen_;

    friend class ::ugdk::desktop::Manager;
};

}  // namespace desktop
}  // namespace ugdk

#endif // UGDK_DESKTOP_WINDOW_H_
