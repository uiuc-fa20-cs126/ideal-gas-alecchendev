#include <visualizer/ideal_gas_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
  particle_container_ = ParticleContainer(720, 480, );
  container_visualizer_ = ContainerVisualizer();
}

void IdealGasApp::draw() {
    ci::Color8u background_color(255, 246, 148);  // light yellow
    ci::gl::clear(background_color);
    container_visualizer_.Draw(particle_container_);
}

}  // namespace visualizer

}  // namespace naivebayes
