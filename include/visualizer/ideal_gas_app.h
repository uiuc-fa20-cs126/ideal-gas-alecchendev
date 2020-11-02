#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

/**
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class IdealGasApp : public ci::app::App {
 public:
    IdealGasApp();

  void draw() override;

  const double kWindowWidth = 720;
  const double kWindowHeight = 480;

 private:

};

}  // namespace visualizer

}  // namespace idealgas
