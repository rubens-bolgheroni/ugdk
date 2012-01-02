#include <SDL/SDL_opengl.h>

#include <ugdk/graphic/drawable/solidrectangle.h>

#include <ugdk/base/engine.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/graphic/modifier.h>

namespace ugdk {

SolidRectangle::SolidRectangle(const Vector2D& size) : size_(size) {}

SolidRectangle::~SolidRectangle() {}

void SolidRectangle::Draw() {
    const Modifier& mod = VIDEO_MANAGER()->CurrentModifier();

    Vector2D origin, target(size_);

    if(mod.mirror() & MIRROR_HFLIP) { // Horizontal flip
        origin.x = target.x;
        target.x = 0.0f;
    }
    if(mod.mirror() & MIRROR_VFLIP) { // Vertical flip
        origin.y = target.y;
        target.y = 0.0f;
	}

    glColor4f(mod.color().r * color_.r, mod.color().g * color_.g, mod.color().b * color_.b, mod.alpha());

    glDisable(GL_TEXTURE_2D);
	glBegin( GL_QUADS ); { //Start quad
        glVertex2fv( origin.val );
        glVertex2f(  target.x, origin.y );
        glVertex2fv( target.val );
        glVertex2f(  origin.x, target.y );
    } glEnd();
}

}  // namespace ugdk
