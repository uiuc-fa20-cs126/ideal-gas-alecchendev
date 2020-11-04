#pragma once

#include <core/particle_container.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "container_visualizer.h"

using ci::Color;

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  /**
   * Calls particle container function to update positions of particles
   */
  void update() override;

  /**
   * Draws the background and calls child visualizer elements to draw
   */
  void draw() override;

  /**
   * Allows user to speed up, slow down, and pause the simulation
   * @param event
   */
  void IdealGasApp::keyDown(ci::app::KeyEvent event);

 private:
  Color background_color_ = ci::Color8u(242, 239, 233);
  const double kWindowWidth = 1080;
  const double kWindowHeight = 720;
  const float kMaxTimeStep = 3.5f;
  const float kTimeStepIncrement = 0.25f;
  float time_step_ = 1;

  // Provides templates for particles to be constructed from
  const vector<Particle> kParticleTypes = vector<Particle>({
                                          Particle(5, 3, ci::Color8u(189, 137, 34), vec2(0, 0), vec2(0, 0)),
                                          Particle(3, 1, ci::Color8u(255, 170, 0), vec2(0, 0), vec2(0, 0)),
  });
  ParticleContainer particle_container_;
  ContainerVisualizer container_visualizer_;

};

}  // namespace visualizer

}  // namespace idealgas
