#include <visualizer/ideal_gas_app.h>
#include <visualizer/plot.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);

  particle_container_ = ParticleContainer(800, 700, 300, kParticleTypes);

  plots_.emplace_back(vec2(50, 50), 800.0f, 700.0f);
  plots_.push_back(Plot(vec2(900, 50), 250.0f, 200.0f));
  plots_.push_back(Plot(vec2(900, 300), 250.0f, 200.0f));
  plots_.push_back(Plot(vec2(900, 550), 250.0f, 200.0f));
}

void IdealGasApp::update() {
  particle_container_.Update(time_step_, vec2(mouse_location_.x - 50, 700 - (mouse_location_.y - 50)));
};

void IdealGasApp::draw() {
  ci::gl::clear(background_color_);

  for (Plot plot : plots_) {
    plot.Draw();
  }

  vector<vector<vec2>> particle_positions = particle_container_.GetParticlePositions();
  Plot container_plot(vec2(50, 50), 800.0f, 700.0f, ci::Color8u(255, 255, 255), ci::Color(0, 0, 0));
  container_plot.DrawScatter(particle_positions[0], 7.0f, ci::Color8u(52, 146, 235));
  container_plot.DrawScatter(particle_positions[1], 8.0f, ci::Color8u(235, 150, 52));
  container_plot.DrawScatter(particle_positions[2], 6.0f, ci::Color8u(130, 92, 48));

  vector<vector<float>> particle_speeds = particle_container_.GetParticleSpeeds();
  Plot plot1(vec2(900, 50), 250.0f, 200.0f, ci::Color8u(255, 255, 255), ci::Color(0, 0, 0));
  plot1.DrawHistogram(particle_speeds[0], 15, ci::Color8u(52, 146, 235));
  Plot plot2(vec2(900, 300), 250.0f, 200.0f, ci::Color8u(255, 255, 255), ci::Color(0, 0, 0));
  plot2.DrawHistogram(particle_speeds[1], 15, ci::Color8u(235, 150, 52));
  Plot plot3(vec2(900, 550), 250.0f, 200.0f, ci::Color8u(255, 255, 255), ci::Color(0, 0, 0));
  plot3.DrawHistogram(particle_speeds[2], 15, ci::Color8u(130, 92, 48));
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

void IdealGasApp::mouseMove(ci::app::MouseEvent event) {
  mouse_location_ = event.getPos();
}

}  // namespace visualizer

}  // namespace naivebayes
