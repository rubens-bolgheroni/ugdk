#ifndef UGDK_RESOURCE_MODULE_H_
#define UGDK_RESOURCE_MODULE_H_

#include <ugdk/resource/manager.h>

#include <ugdk/system/config.h>

#include <ugdk/graphic.h>
#include <ugdk/internal.h>
#include <ugdk/text.h>

namespace ugdk {
namespace resource {

/// Initializes the module with the given Manager.
bool Initialize(Manager* manager);

/// Releases the module, disabling it.
void Release();

/// Getter for the manager of the module.
Manager* manager();

#ifndef UGDK_3D_ENABLED
graphic::SpriteAnimationTable*    GetSpriteAnimationTableFromFile(const std::string& file);
internal::GLTexture*             GetTextureFromTag(const std::string& tag);
internal::GLTexture*             GetTextureFromFile(const std::string& file);
graphic::TextureAtlas*           GetTextureAtlasFromTag(const std::string& tag);
graphic::TextureAtlas*           GetTextureAtlasFromFile(const std::string& file);
text::LanguageWord*              GetLanguageWord(const std::string& tag);
#endif // UGDK_3D_ENABLED

} // namespace resource
} // namespace ugdk

#endif // UGDK_RESOURCE_MODULE_H_
