#pragma once

#include <core/particle_container.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using ci::Color;

namespace idealgas {

namespace visualizer {

/**
 * Draws necessary elements of particle container given appropriate visual characteristics
 */
class ContainerVisualizer {
 public:
  ContainerVisualizer(){};

  /**
   * Constructs container visualizer with necessary visual information
   * @param top_left_corner vec2 origin denoting top left corner to draw container from
   * @param container_background_ color of background within container
   * @param container_stroke color of container outline
   */
  ContainerVisualizer(vec2 top_left_corner, Color container_background_, Color container_stroke);

  /**
   * Draws the particle container and all particles inside
   * @param particle_container particle container to draw
   */
  void Draw(const ParticleContainer& particle_container);

 private:
  vec2 top_left_corner_;
  Color container_background_;
  Color container_stroke_;
};

}  // namespace visualizer

}  // namespace idealgas
