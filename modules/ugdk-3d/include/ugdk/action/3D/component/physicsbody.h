#ifndef UGDK_ACTION_3D_COMPONENT_PHYSICSBODY_H
#define UGDK_ACTION_3D_COMPONENT_PHYSICSBODY_H

#include <ugdk/action/3D/component/body.h>
#include <LinearMath/btTransform.h>
#include <unordered_map>

class btCollisionShape;
class btRigidBody;

namespace ugdk {
namespace action {
namespace mode3d {

class Physics;

namespace component {

class PhysicsBody final : public Body {
  public:
    using Body::ApplyImpulse;

    struct PhysicsData {
        /** rigid body mass (must be >= 0, and 0 means static "infinite mass" object) */
        double mass;
        /** flag (power of 2 bit mask) of the collision group this object belongs to */
        short collision_group;
        /**  flags (combination of flags - |'ed) of groups this object collides with */
        short collides_with;
        /**  collision shape of this object */
        btCollisionShape* shape;
        /** initial position and orientation of the object */
        btTransform initial;
        /** offset to center of mass */
        btTransform offset;
        /** wheter orientation is applied to Ogre's node or not */
        bool apply_orientation;
        PhysicsData();
    };

    PhysicsBody(Physics &physics, const PhysicsData &physics_data);
    ~PhysicsBody();

    double mass() const override;
    short collision_group() const override;
    short collides_with() const override;
    void set_angular_factor(double x_axis, double y_axis, double z_axis) override;
    void set_restitution(double factor) override;
    void set_friction(double frict) override;
    void set_damping(double linear, double angular) override;
    void SetRespondsOnContact(bool has_response) override;
    void SetContinuousCollisionDetection(double speed_threshold, double sphere_radius) override;

    Ogre::Vector3 position() const override;
    Ogre::Quaternion orientation() const override;
    void set_orientation(const Ogre::Vector3& dir) override;
    Ogre::Vector3 linear_velocity() const override;
    void set_linear_velocity(const Ogre::Vector3& velocity) override;
    Ogre::Vector3 angular_velocity() const override;
    Ogre::Vector3 GetVelocityInPoint(const Ogre::Vector3& point) const override;

    void Translate(double move_x, double move_y, double move_z) override;
    void ApplyImpulse(double imp_x, double imp_y, double imp_z) override;
    void ApplyImpulse(const Ogre::Vector3& imp, const Ogre::Vector3& relative_pos) override;
    void Rotate(double yaw, double pitch, double roll) override;
    void Scale(double factor_x, double factor_y, double factor_z) override;

    void AddCollisionAction(short target_mask, const CollisionAction& action) override;

  protected:
    void OnTaken() override;

  private:
    friend class ::ugdk::action::mode3d::Physics;

    Physics     &physics_;
    PhysicsData physics_data_;
    btRigidBody *body_;
    std::unordered_map<short, CollisionAction> action_map_;
};

inline PhysicsBody::PhysicsBody(Physics &physics, const PhysicsData &physics_data)
    : physics_(physics), physics_data_(physics_data) {}

inline double PhysicsBody::mass() const  {
    return physics_data_.mass;
}

inline short PhysicsBody::collision_group() const  {
    return physics_data_.collision_group;
}
inline short PhysicsBody::collides_with() const  {
    return physics_data_.collides_with;
}

template <>
class NullComponent<PhysicsBody> : public NullComponent<Body> {};

} // namespace component
} // namespace mode3d
} // namespace action
} // namespace ugdk

#endif // BULLETWORKS_COMPONENT_PHYSICSBODY_H
