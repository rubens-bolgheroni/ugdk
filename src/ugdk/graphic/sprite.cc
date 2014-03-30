#include <ugdk/graphic/sprite.h>

#include <ugdk/resource/module.h>
#include <ugdk/graphic/spritesheet.h>
#include <ugdk/graphic/manager.h>
#include <ugdk/graphic/visualeffect.h>
#include <ugdk/graphic/drawable/functions.h>
#include <ugdk/graphic/canvas.h>
#include <ugdk/graphic/primitive.h>
#include <ugdk/graphic/opengl/shaderuse.h>
#include <ugdk/graphic/opengl/vertexbuffer.h>
#include <ugdk/graphic/opengl/Exception.h>
#include <ugdk/action/spriteanimationframe.h>
#include <ugdk/action/animationplayer.h>

namespace ugdk {
namespace graphic {

using action::SpriteAnimationPlayer;
        
void ApplyPositionOffset(VertexData& data, const math::Vector2D& offset) {
    data.CheckSizes("ApplyPositionOffset", 0, 2 * sizeof(GLfloat));

    opengl::VertexBuffer::Bind bind(*data.buffer());
    opengl::VertexBuffer::Mapper mapper(*data.buffer());

    uint8* ptr = static_cast<uint8*>(mapper.get());
    for (std::size_t i = 0; i < data.num_vertices(); ++i) {
        GLfloat* v = reinterpret_cast<GLfloat*>(ptr + i * data.vertex_size());
        v[0] += GLfloat(offset.x);
        v[1] += GLfloat(offset.y);
    }
}

void SpriteDataSetToGeometry(VertexData& data, const math::Vector2D& position, const math::Vector2D& size, const math::Vector2D& hotspot, const Geometry& geometry) {
    data.CheckSizes("SpriteDataSetToGeometry", 4, 2 * sizeof(GLfloat));

    glm::vec4 top_left(position.x - hotspot.x, position.x - hotspot.y, 0.0, 1.0);
    glm::vec4 bottom_right(top_left.x + size.x, top_left.y + size.y, 0.0, 1.0);

    const glm::mat4& mat = geometry.AsMat4();
    top_left = mat * top_left;
    bottom_right = mat * bottom_right;

    {
        opengl::VertexBuffer::Bind bind(*data.buffer());
        opengl::VertexBuffer::Mapper mapper(*data.buffer());

        uint8* ptr = static_cast<uint8*>(mapper.get());

        GLfloat* v1 = reinterpret_cast<GLfloat*>(ptr + 0 * data.vertex_size());
        v1[0] = float(top_left.x);
        v1[1] = float(top_left.y);

        GLfloat* v2 = reinterpret_cast<GLfloat*>(ptr + 1 * data.vertex_size());
        v2[0] = float(top_left.x);
        v2[1] = float(bottom_right.y);

        GLfloat* v3 = reinterpret_cast<GLfloat*>(ptr + 2 * data.vertex_size());
        v3[2 * 4 + 0] = float(bottom_right.x);
        v3[2 * 4 + 1] = float(top_left.y);

        GLfloat* v4 = reinterpret_cast<GLfloat*>(ptr + 3 * data.vertex_size());
        v4[0] = float(bottom_right.x);
        v4[1] = float(bottom_right.y);
    }
}

Sprite::Sprite(const Spritesheet *spritesheet)
: spritesheet_(spritesheet)
, owner_(nullptr)
{}

Sprite::~Sprite() {}

void Sprite::set_owner(Primitive* owner) {
    owner_ = owner;
}

void Sprite::ChangeToFrame(const action::SpriteAnimationFrame& frame) {
    const auto& spritesheet_frame = spritesheet_->frame(frame.spritesheet_frame());

    owner_->set_texture(spritesheet_frame.texture.get());
    SpriteDataSetToGeometry(*owner_->vertexdata(), position_, spritesheet_frame.size, spritesheet_frame.hotspot, frame.geometry());
}
    
void Sprite::ChangePosition(const math::Vector2D& position) {
    ApplyPositionOffset(*owner_->vertexdata(), position - position_);
    position_ = position;
}

std::shared_ptr<VertexData> CreateSpriteCompatibleVertexData() {
    return std::make_shared<VertexData>(4, 2 * 2 * sizeof(GLfloat), true);
}
std::tuple<
    std::shared_ptr<Primitive>,
    std::shared_ptr<action::SpriteAnimationPlayer>
> CreateSpritePrimitive(const Spritesheet *spritesheet, const action::SpriteAnimationTable* table) {
    std::shared_ptr<Primitive> primitive(new Primitive(spritesheet->frame(0).texture.get(), CreateSpriteCompatibleVertexData()));
    primitive->set_controller(std::unique_ptr<Sprite>(new Sprite(spritesheet)));

    return std::make_tuple(primitive, CreateSpriteAnimationPlayerForPrimitive(primitive, table));
}

std::shared_ptr<action::SpriteAnimationPlayer> CreateSpriteAnimationPlayerForPrimitive(const std::shared_ptr<Primitive>& primitive_shared, const action::SpriteAnimationTable* table) {
    std::weak_ptr<Primitive> weak_primitive(primitive_shared);

    std::shared_ptr<action::SpriteAnimationPlayer> player(new action::SpriteAnimationPlayer(table));
    player->set_frame_change_callback([weak_primitive](const action::SpriteAnimationFrame& frame) {
        if (auto primitive = weak_primitive.lock()) {
            if (Sprite* sprite = dynamic_cast<Sprite*>(primitive->controller().get())) {
                sprite->ChangeToFrame(frame);
            }
        }
    });
    return player;
}

}  // namespace graphic
}  // namespace ugdk
