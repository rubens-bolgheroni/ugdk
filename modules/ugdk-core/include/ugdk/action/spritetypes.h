#ifndef UGDK_ACTION_SPRITETYPES_H_
#define UGDK_ACTION_SPRITETYPES_H_

#include <ugdk/action.h>

// The following includes are necessary to use SpriteAnimationPlayer and SpriteAnimationTable.
#include <ugdk/action/spriteanimationframe.h>
#include <ugdk/action/animation.h>
#include <ugdk/action/animationplayer.h>
#include <ugdk/structure/indexabletable.h>

#include <string>

namespace ugdk {
namespace action {

using SpriteAnimationTable = ::ugdk::structure::IndexableTable<SpriteAnimation>;

SpriteAnimationTable* LoadSpriteAnimationTableFromFile(const std::string& filepath);

}  // namespace action
}  // namespace ugdk

#endif // UGDK_ACTION_SPRITETYPES_H_
