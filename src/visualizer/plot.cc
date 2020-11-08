#include <visualizer/plot.h>

namespace idealgas {

namespace visualizer {

Plot::Plot(vec2 top_left_corner, float width, float height, Color background_color, Color outline_color) {
  top_left_corner_ = top_left_corner;
  width_ = width;
  height_ = height;
  background_color_ = background_color;
  outline_color_ = outline_color;
}

void Plot::Draw() {
  vec2 bottom_right_corner = top_left_corner_ + vec2(width_, height_);
  ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);

  ci::gl::color(background_color_);
  ci::gl::drawSolidRect(pixel_bounding_box);

  ci::gl::color(outline_color_);
  ci::gl::drawStrokedRect(pixel_bounding_box);
};

void Plot::DrawHistogram(const vector<float>& values, const int& n_bins, const Color& color) {

  float max_frequency = 0;
  float max_value = *max_element(values.begin(), values.end());
  vector<float> frequencies = vector<float>(n_bins, 0.0f);
  for (float value : values) {
    int bin = static_cast<int>(floor(value * (n_bins - 1) / max_value));
    frequencies[bin]++;
    max_frequency = max(max_frequency, frequencies[bin]);
  }
  max_frequency *= 1.1f;

  vec2 origin = top_left_corner_ + vec2(0, height_);
  vec2 x_increment = vec2(width_ / n_bins, 0);
  for (int bin = 0; bin < n_bins; bin++) {
    vec2 bottom_left = origin + static_cast<float>(bin) * x_increment;
    float frequency = frequencies[bin];
    float bar_height = frequency / max_frequency * height_;
    vec2 top_right = bottom_left + x_increment - vec2(0, bar_height);
    ci::Rectf bar(bottom_left, top_right);
    ci::gl::color(color);
    ci::gl::drawSolidRect(bar);
  }

}

void Plot::DrawScatter(const vector<vec2>& positions, const float& radius, const Color& color) {
  vec2 origin = top_left_corner_ + vec2(0, height_);
  for (vec2 position : positions) {
    ci::gl::color(color);
    ci::gl::drawSolidCircle(origin + vec2(position.x, -position.y), radius);
  }
}

}  // namespace visualizer

}  // namespace naivebayes
