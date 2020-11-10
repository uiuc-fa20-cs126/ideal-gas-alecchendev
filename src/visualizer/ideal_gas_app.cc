#include <visualizer/ideal_gas_app.h>
#include <visualizer/plot.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() {
  ci::app::setWindowSize((int) kWindowWidth, (int) kWindowHeight);

  particle_container_ = ParticleContainer(kContainerWidth, kContainerHeight, kParticles, kParticleTypes);

  // container plot
  plots_.emplace_back(vec2(kMargin, kMargin), kContainerWidth, kContainerHeight);

  // histogram plots
  float height = (kContainerHeight - (kHistMargin * (kParticleTypes.size() - 1))) / kParticleTypes.size();
  float width = kWindowWidth - (kMargin + kContainerWidth + kContainerHistMargin) - kMargin;
  for (size_t idx = 0; idx < kParticleTypes.size(); idx++) {
    vec2 top_left_corner = vec2(kMargin + kContainerWidth + kContainerHistMargin, kMargin + idx * (height + kHistMargin));
    plots_.emplace_back(top_left_corner, width, height);
  }
}

void IdealGasApp::update() {
  particle_container_.Update(time_step_, vec2(mouse_location_.x - 50, 700 - (mouse_location_.y - 50)));
};

void IdealGasApp::draw() {
  // draw canvas and particle container
  ci::gl::clear(kBackgroundColor);
  plots_[0].Draw();

  // loop through each type of particle
  std::map<string, vector<Particle>> particles_by_type = particle_container_.GetParticlesByType();
  for (size_t idx = 0; idx < kParticleTypes.size(); idx++) {
    // getting values necessary for drawing
    Particle particle_type = kParticleTypes[idx];
    vector<Particle> particles = particles_by_type[particle_type.type];
    vector<vec2> positions;
    vector<float> speeds;
    for (Particle particle : particles) {
      positions.push_back(particle.position);
      speeds.push_back(length(particle.velocity));
    }

    // drawing the particles
    plots_[0].DrawScatter(positions, particle_type.radius, particle_type.color);

    // drawing the histogram
    size_t plot_idx = idx + 1;
    plots_[plot_idx].Draw();
    plots_[plot_idx].DrawHistogram(speeds, kBins, particle_type.color);
    plots_[plot_idx].LabelTitle(particle_type.type + " Particle Speed Distribution", kPlotTitleMargin);
    plots_[plot_idx].LabelXAxis("Speed", kPlotXLabelMargin);
    plots_[plot_idx].LabelYAxis("# Particles", kPlotYLabelMargin);
  }
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
