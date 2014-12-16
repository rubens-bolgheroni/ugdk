#ifndef BULLETWORKS_COMPONENT_PHYSICSBODY_H
#define BULLETWORKS_COMPONENT_PHYSICSBODY_H

#include <bulletworks/component/body.h>

#include <LinearMath/btTransform.h>

class btCollisionShape;
class btRigidBody;

namespace bulletworks {

class Manager;

namespace component {

class PhysicsBody final : public Body {
  public:
    using Body::Move;

    struct PhysicsData {
        /// rigid body mass (must be >= 0, and 0 means static "infinite mass" object)
        double mass;
        /// flag (power of 2 bit mask) of the collision group this object belongs to
        short collision_group;
        /// flags (combination of flags - |'ed) of groups this object collides with
        short collides_with;
        /// collision shape of this object
        btCollisionShape* shape;
        /// initial position and orientation of the object
        btTransform initial;
        /// offset to center of mass
        btTransform offset;

        PhysicsData();
    };

    PhysicsBody (Manager &manager, const PhysicsData &physics_data);
    ~PhysicsBody();

    double mass() const override;
    void set_angular_factor(double x_axis, double y_axis, double z_axis) override;
    void set_restitution(double factor) override;

    void Translate(double move_x, double move_y, double move_z) override;
    void Move(double delta_x, double delta_y, double delta_z) override;
    void Rotate(double yaw, double pitch, double roll) override;
    void Scale(double factor_x, double factor_y, double factor_z) override;

  protected:

    void OnTaken() override;

  private:

    friend class ::bulletworks::Manager;

    Manager     &manager_;
    PhysicsData physics_data_;
    btRigidBody *body_;
};

inline PhysicsBody::PhysicsBody(Manager &manager, const PhysicsData &physics_data)
    : manager_(manager), physics_data_(physics_data) {}

inline double PhysicsBody::mass() const  {
    return physics_data_.mass;
}

template <>
class NullComponent<PhysicsBody> : public NullComponent<Body> {};

} // namespace component
} // namespace bulletworks

#endif // BULLETWORKS_COMPONENT_PHYSICSBODY_H
