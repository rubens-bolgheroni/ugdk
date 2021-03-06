#ifndef UGDK_ACTION_3D_OGRESCENE_H_
#define UGDK_ACTION_3D_OGRESCENE_H_

#include <ugdk/action/scene.h>
#include <ugdk/action/3D/physics.h>
#include <unordered_set>
#include <forward_list>

class btVector3;

namespace Ogre {
class SceneManager;
class Viewport;
class Overlay;
class OverlaySystem;
}

namespace ugdk {
namespace action {
namespace mode3d {

class Camera;
class Element;

/**
   @class Scene3D
   @brief A 3D game scene, or screen.

   Represents a Ogre 3D scene, which contains a tree of nodes (entities) to
   render, the associated camera and viewport, and Physics manager object.
*/
class Scene3D : public ugdk::action::Scene {
//TODO: this does not allow showing at the same time multiple cameras from the same scene (splitscreen coop for example).
public:
    Scene3D(const btVector3& gravity);
    virtual ~Scene3D();
    
    /// Method called when this scene is pushed to the Engine's Scene stack.
    virtual void OnPushed(int index);
    
    void ShowFrameStats();
    bool IsFrameStatsVisible();
    void UpdateFrameStats();
    void HideFrameStats();

    /** Creates and returns a new Element in this scene. */
    const std::shared_ptr<Element>& AddElement(const std::string& name="");
    /** Marks an element to be destroyed and removed from this scene at the end of the frame. */
    void DestroyAndRemoveElement(const std::shared_ptr<Element>& element);

    const std::unique_ptr<Physics>& physics() const {
        return physics_;
    }
    Ogre::SceneManager* manager() const { return scene_mgr_; }
    Camera* camera() const { return camera_; }

protected:
    Ogre::SceneManager* scene_mgr_;
    Ogre::OverlaySystem* overlay_system_;
    Camera* camera_;
    int z_order_;
    Ogre::Viewport* viewport_;
    Ogre::Overlay* fps_stats_;

    std::unique_ptr<Physics> physics_;
    std::unordered_set<std::shared_ptr<Element>> elements_;
    std::forward_list<std::shared_ptr<Element>> to_be_removed_;
    
}; // class Scene3D.


} // namespace 3D
} /* namespace action */
} /* namespace ugdk */

#endif /* UGDK_ACTION_3D_SCENE3D_H_ */
