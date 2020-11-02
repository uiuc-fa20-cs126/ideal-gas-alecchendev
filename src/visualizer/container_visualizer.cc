#include <visualizer/container_visualizer.h>

namespace idealgas {

namespace visualizer {

ContainerVisualizer::ContainerVisualizer(vec2 top_left_corner) {
  top_left_corner_ = top_left_corner;
}

void ContainerVisualizer::Draw(ParticleContainer particle_container) {

  vec2 bottom_right_corner = top_left_corner_ + vec2(particle_container.getWidth(), particle_container.getHeight());
  ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);

  ci::gl::color(Color(255, 250, 155));
  ci::gl::drawSolidRect(pixel_bounding_box);

  ci::gl::color(Color(0, 0, 0));
  ci::gl::drawStrokedRect(pixel_bounding_box);

};


}  // namespace visualizer

}  // namespace naivebayes
