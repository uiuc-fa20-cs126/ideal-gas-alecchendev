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

  Plot(vec2 top_left_corner, float width, float height, Color background_color = Color(1, 1, 1), Color outline_color = Color(0, 0, 0));

  /**
   * Draws the basic plot elements - the frame, background, position, etc
   */
  void Draw();

  /**
   * Draws the histogram corresponding to the given values
   * @param values vector of float values to be converted into frequencies
   * @param n_bins number of bins for the histogram
   * @param color color of the bars in the histogram
   */
  void DrawHistogram(const vector<float>& values, const int& n_bins = 10, const Color& color = Color(0, 0, 0));

  /**
   * Draws the points of a scatter plot
   * @param positions vec2 positions of points to draw
   * @param radius float size of the points
   * @param color color of the points
   */
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
