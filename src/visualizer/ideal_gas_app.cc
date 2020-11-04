#include <visualizer/ideal_gas_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);
  particle_container_ = ParticleContainer(720, 480, 100, kParticleTypes);
  container_visualizer_ = ContainerVisualizer(vec2(100, 50), ci::Color8u(255, 252, 245), ci::Color(0, 0, 0));
}

void IdealGasApp::update() {
  particle_container_.Update(time_step_);
};

void IdealGasApp::draw() {
  ci::gl::clear(background_color_);
  container_visualizer_.Draw(particle_container_);
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT: {
      time_step_ += (time_step_ < kMaxTimeStep) * kTimeStepIncrement;
      break;
    }
    case ci::app::KeyEvent::KEY_LEFT: {
      time_step_ -= (time_step_ >= kTimeStepIncrement) * kTimeStepIncrement;
      break;
    }
    case ci::app::KeyEvent::KEY_SPACE: {
      time_step_ = (time_step_ == 0);
      break;
    }
  }
}

}  // namespace visualizer

}  // namespace naivebayes
