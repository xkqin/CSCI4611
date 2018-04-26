/** CSci-4611 Assignment 2:  Car Soccer
 */

#ifndef CAR_H_
#define CAR_H_

#include <mingfx.h>

/// Small data structure for a car
class Car {
public:

    /// The constructor sets the static properties of the car, like its size,
    /// and then calls Reset() to reset the position, velocity, and any other
    /// dynamic variables that change during game play.
    Car() : size_(3,2,4), collision_radius_(2.5) {
        Reset();
    }

    /// Nothing special needed in the constructor
    virtual ~Car() {}

    /// Resets all the dynamic variables, so if you call this after a goal, the
    /// car will go back to its starting position.
    void Reset() {
        position_ = Point3(0, size_[1]/2, 45);
    }

    float collision_radius() { return collision_radius_; }
    Vector3 velocity(){return velocity_;}
    Vector3 size() { return size_; }
    float angle(){return angle_;}
    Point3 position() { return position_; }
    void set_position(const Point3 &p) { position_ = p; }
    void set_velocity(const Vector3 &v) { velocity_ = v; }
    void set_angle(const float &f) { angle_ = f; }
private:
    // You will probably need to store some additional data here, e.g., speed.
    Vector3 velocity_;
    Vector3 size_;
    float collision_radius_;
    Point3 position_;
    float angle_;
};

#endif
