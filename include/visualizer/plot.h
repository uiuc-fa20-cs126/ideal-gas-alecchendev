#pragma once

#include <algorithm>
#include <core/particle_container.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using ci::Color;
using std::max;

namespace idealgas {

namespace visualizer {

/**
 * Draws necessary elements of particle container given appropriate visual characteristics
 */
class Plot {
 public:
  Plot(){};

  Plot(vec2 top_left_corner, float width, float height, Color background_color, Color outline_color);

  /**
   * Draws the basic plot elements
   */
  void Draw();

  void DrawHistogram(const vector<float>& values = vector<float>{}, const int& n_bins = 10, const Color& color = Color(0, 0, 0));

  void DrawScatter(const vector<vec2>& positions, const float& radius, const Color& color = Color(0, 0, 0));

 private:
  vec2 top_left_corner_;
  float width_;
  float height_;
  Color background_color_;
  Color outline_color_;
};

}  // namespace visualizer

}  // namespace idealgas
