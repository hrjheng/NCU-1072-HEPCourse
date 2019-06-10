#include <iostream>
#include <vector>

#include "Event.h"
using namespace std;

Event::Event(std::vector<float> pt, std::vector<float> eta, std::vector<float> phi) {
      _pt.clear();
      _eta.clear();
      _phi.clear();
      _pt = pt;
      _eta = eta;
      _phi = phi;
}

std::vector<float> Event::pT() {
      return (_pt);
}

std::vector<float> Event::eta() {
      return (_eta);
}

std::vector<float> Event::phi() {
      return (_phi);
}
