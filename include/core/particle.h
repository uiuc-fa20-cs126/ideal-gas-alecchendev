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
  Particle(float radius, float mass, Color color, vec2 position, vec2 velocity) {
    this->radius = radius;
    this->mass = mass;
    this->color = color;
    this->position = position;
    this->velocity = velocity;
  }

  float radius;
  float mass;
  Color color;
  vec2 position;
  vec2 velocity;
};

}  // namespace idealgas