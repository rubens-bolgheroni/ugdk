#ifndef UGDK_ACTION_SCENE_H_
#define UGDK_ACTION_SCENE_H_

#include <functional>
#include <list>
#include <queue>
#include <ugdk/action.h>
#include <ugdk/audio.h>
#include <ugdk/graphic.h>
#include <ugdk/structures/types.h>
#include <ugdk/action/mediamanager.h>

namespace ugdk {
namespace action {

/**
   @class Scene
   @brief A game scene, or screen.

   Represents a scene, containing various graphical layers and sprites.
   A scene is game screen, such as a menu, or the playable part
   itself.
*/
class Scene {
  private:

    /// Auxiliar class for AddTask.
    template <typename Ret>
    struct TaskAdapter {
        template <typename T>
        static Task Adapt(T t) {
            return Task(t);
        }
    };

    // struct Scene::TaskAdapter<void>
    // Located after Scene definition.

  public:
    Scene();
      
    virtual ~Scene();

    /// Method called when this Scene arrives on the top of the Scene stack.
    virtual void Focus();

    /// Method called when this Scene leaves the top of the Scene stack.
    virtual void DeFocus();

    /// Adds an Entity to the scene.
    void AddEntity(Entity *entity);

    /// Removes the specified Entity from the scene.
    void RemoveEntity(Entity *entity) { entities_.remove(entity); }

    /// Will be added at the end of the 
    void QueuedAddEntity(Entity *entity) { queued_entities_.push(entity); }

    void RemoveAllEntities();

    /// Adds a task to the scene.
    /** All tasks are called for each Scene's Update, in order of the priorities, which
        are ordered from smaller values to bigger values.

        The task's returned value is used to destroy the task or keep it alive:
        - True keeps then for another Update.
        - False destroys then.
        - void return type implies in 'always true'.
    
        Priority values are commonly in the [0; 1] interval. */
    template <typename T>
    void AddTask(T task, double priority = 0.5) {
        AddFunctionTask(TaskAdapter<decltype(task(0.0))>::Adapt(task), priority);
    }

    /// Finishes the scene.
    void Finish() { End(); finished_ = true; }

    /// Logical update of the scene.
    /**
       @param delta_t Time in seconds since last update
    */
    void Update(double delta_t);

    /// Whether this scene stops the previous music even if wont play any music.
    void StopsPreviousMusic(bool set) { stops_previous_music_ = set; }

    void Render(const graphic::Geometry&, const graphic::VisualEffect&) const;

    /** @name Getters and Setters
    @{
    */
    bool finished() const { return finished_; }

    bool active() const { return active_; }
    void set_active(bool is_active) { active_ = is_active; }
    
    bool visible() const { return visible_; }
    void set_visible(bool is_visible) { visible_ = is_visible; }

          MediaManager& media_manager()       { return media_manager_; }
    const MediaManager& media_manager() const { return media_manager_; }

    audio::Music* background_music() const { return background_music_; }
    void set_background_music(audio::Music* music) { background_music_ = music; }
    /**@}
     */

    void set_defocus_callback(const std::function<void (Scene*)>& defocus_callback) { 
        defocus_callback_ = defocus_callback;
    }
    void set_focus_callback(const std::function<void (Scene*)>& focus_callback) { 
        focus_callback_ = focus_callback;
    }
    void set_render_function(const std::function<void (const graphic::Geometry&, const graphic::VisualEffect&)>& render_function) {
        render_function_ = render_function;
    }

  protected:
    
    /// Ends the scene activity.
    /** Note: do not release any resources in this method. */
    virtual void End();
    
    /// Tells whether the scene is currently running or not.
    bool active_;

    /// Tells whether the scene is finished or not.
    bool finished_;

    /// Tells whether the scene is visible or not.
    bool visible_;

    /// The background music when this scene is on top.
    audio::Music* background_music_;

  private:
    void AddFunctionTask(const Task& task, double priority);

    /// Whether this scene stops the previous music even if wont play any music.
    bool stops_previous_music_;

    /// A MediaManager provided for users.
    MediaManager media_manager_;

    std::list<Entity*> entities_;
    std::queue<Entity*> queued_entities_;
    std::function<void (Scene*)> defocus_callback_;
    std::function<void (Scene*)> focus_callback_;
    std::function<void (const graphic::Geometry&, const graphic::VisualEffect&)> render_function_;

    struct OrderedTask {
        OrderedTask(double p, const Task& t) : priority(p), task(t) {}

        double priority;
        Task task;

        bool operator< (const OrderedTask& other) const { 
            return priority < other.priority;
        }
    };
    std::list<OrderedTask> tasks_;
}; // class Scene.

template <>
struct Scene::TaskAdapter<void> {
    template <typename T>
    static Task Adapt(T t) {
        return Task([t](double dt) -> bool {
            t(dt);
            return true;
        });
    }
};

} /* namespace action */

} /* namespace ugdk */

#endif /* UGDK_ACTION_SCENE_H_ */
