#pragma once
#include "cinder/gl/gl.h"
#include <map>
#include <string>
#include <vector>

using glm::vec2;
using std::vector;
using ci::Color;

namespace idealgas {

struct Particle {
  Particle(float radius, float mass, vec2 position, vec2 velocity) {
    this->radius = radius;
    if (mass <= 0.0f)
      throw std::invalid_argument("Mass cannot be 0 or less.");
    this->mass = mass;
    this->position = position;
    this->velocity = velocity;
  }

  float radius;
  float mass;
  vec2 position;
  vec2 velocity;
};

}  // namespace idealgas