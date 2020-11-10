#pragma once

#include <core/particle_container.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "plot.h"

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

  /**
   * Keeps track of location of the mouse anytime it moves
   * @param event
   */
  void IdealGasApp::mouseMove(ci::app::MouseEvent event);

 private:
  const float kMaxTimeStep = 3.5f;
  const float kTimeStepIncrement = 0.25f;
  const int kParticles = 250;
  const int kBins = 15;

  Color kBackgroundColor = ci::Color8u(242, 239, 233);
  const float kWindowWidth = 1200.0f;
  const float kWindowHeight = 800.0f;

  const float kMargin = 50.0f;
  const float kContainerWidth = 800.0f;
  const float kContainerHeight = 700.0f;
  const float kContainerHistMargin = 50.0f;
  const float kHistMargin = 50.0f;

  const float kPlotTitleMargin = 15.0f;
  const float kPlotXLabelMargin = 5.0f;
  const float kPlotYLabelMargin = 15.0f;

  float time_step_ = 1;
  // Provides templates for particles to be constructed from
  const vector<Particle> kParticleTypes = vector<Particle>({
                                          Particle("Small", 5, 5, ci::Color8u(130, 92, 48), vec2(0, 0), vec2(0, 0)),
                                          Particle("Medium", 8, 5, ci::Color8u(235, 150, 52), vec2(0, 0), vec2(0, 0)),
                                          Particle("Large", 10, 10, ci::Color8u(52, 146, 235), vec2(0, 0), vec2(0, 0)),
                                          Particle("Larger", 10, 20, ci::Color8u(0, 0, 0), vec2(0, 0), vec2(0, 0)),
  });
  ParticleContainer particle_container_;
  vector<Plot> plots_;

  vec2 mouse_location_;

};

}  // namespace visualizer

}  // namespace idealgas
