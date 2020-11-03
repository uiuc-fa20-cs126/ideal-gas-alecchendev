#pragma once

#include <core/particle_container.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "container_visualizer.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void update() override;
  void draw() override;

  const double kWindowWidth = 1080;
  const double kWindowHeight = 720;

 private:
  ParticleContainer particle_container_;
  ContainerVisualizer container_visualizer_;

};

}  // namespace visualizer

}  // namespace idealgas
