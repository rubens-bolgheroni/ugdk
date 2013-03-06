#include <ugdk/graphic/drawable/sprite.h>

#include <ugdk/base/engine.h>
#include <ugdk/base/resourcemanager.h>
#include <ugdk/graphic/spritesheet.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/graphic/visualeffect.h>
#include <ugdk/action/spriteanimationframe.h>
#include <ugdk/action/animationplayer.h>

namespace ugdk {
namespace graphic {

using action::SpriteAnimationPlayer;

Sprite::Sprite(const Spritesheet *spritesheet, SpriteAnimationPlayer *player) 
    : spritesheet_(spritesheet), animation_player_(player) {}

Sprite::Sprite(const std::string& spritesheet_tag, SpriteAnimationPlayer* manager)
    : spritesheet_(base::ResourceManager::GetSpritesheetFromTag(spritesheet_tag)), 
      animation_player_(manager) {}

Sprite::Sprite(const std::string& spritesheet_tag, const std::string& animation_set_tag) 
    : spritesheet_(base::ResourceManager::GetSpritesheetFromTag(spritesheet_tag)),
      animation_player_(new action::AnimationTablePlayer<ugdk::action::SpriteAnimation>(
             base::ResourceManager::GetSpriteAnimationTableFromFile(animation_set_tag))) {}

Sprite::Sprite(const Spritesheet *spritesheet, const std::string& animation_set_tag)
  : spritesheet_(spritesheet), animation_player_(new action::AnimationTablePlayer<ugdk::action::SpriteAnimation>(
                  base::ResourceManager::GetSpriteAnimationTableFromFile(animation_set_tag))) {}
 
Sprite::~Sprite() {
    if (animation_player_) delete animation_player_;
}

void Sprite::Update(double delta_t) {
    if(animation_player_) animation_player_->Update(delta_t);
}

void Sprite::Draw(const Geometry& modifier, const VisualEffect& effect) const {
    if(!spritesheet_) return;
    if(animation_player_) {
        const action::SpriteAnimationFrame* animation_frame = 
            current_animation_frame();

        Geometry compose(modifier);
        compose.Compose(animation_frame->geometry());
        VisualEffect compose_effect(effect);
        compose_effect.Compose(animation_frame->effect());

        spritesheet_->Draw(animation_frame->spritesheet_frame(), hotspot_, compose, compose_effect);
    } else {
        spritesheet_->Draw(0, hotspot_, modifier, effect);
    }
}

const ugdk::math::Vector2D& Sprite::size() const {
    return spritesheet_->frame_size(current_animation_frame()->spritesheet_frame()); // TODO: requires some info from the spritesheet
}
    
const action::SpriteAnimationFrame* Sprite::current_animation_frame() const {
    return animation_player_ ? animation_player_->current_animation_frame() : NULL;
}
    
const action::SpriteAnimationPlayer* Sprite::animation_player() const { 
    return animation_player_;
}

}  // namespace graphic
}  // namespace ugdk
