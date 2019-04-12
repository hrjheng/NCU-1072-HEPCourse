#include <iostream>
#include <vector>

#include "Event.h"
using namespace std;

Event::Event(std::vector<float> pt, std::vector<float> eta, std::vector<float> phi, std::vector<int> Q) {
      _pt.clear();
      _eta.clear();
      _phi.clear();
      _q.clear();
      _pt = pt;
      _eta = eta;
      _phi = phi;
      _q = Q;
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

std::vector<int> Event::charge() {
      return (_q);
}
