#pragma once

#include <core/particle_container.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class ContainerVisualizer {
 public:
  ContainerVisualizer() {
    top_left_corner_ = vec2(50, 50);
  }
  ContainerVisualizer(vec2 top_left_corner);

  void Draw(ParticleContainer particle_container);

 private:
  vec2 top_left_corner_;

};

}  // namespace visualizer

}  // namespace idealgas
