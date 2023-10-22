#pragma once

#include "Math.hpp"

#include "UClass.hpp"

namespace sdk {
class UCameraComponent;
class USceneComponent;

class AActor : public UObject {
public:
    static UClass* static_class();

    // it takes a hit result as out param but we dont care.
    bool set_actor_location(const glm::vec3& location, bool sweep, bool teleport);
    glm::vec3 get_actor_location();

    bool set_actor_rotation(const glm::vec3& rotation, bool teleport);

    USceneComponent* get_component_by_class(UClass* uclass);
    UCameraComponent* get_camera_component();

    USceneComponent* add_component_by_class(UClass* uclass);
    void finish_add_component(sdk::UObject* component);

protected:
};
}