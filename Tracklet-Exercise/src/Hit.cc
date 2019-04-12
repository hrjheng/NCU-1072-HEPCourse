#include <TObject.h>

#include "Hit.h"

using namespace std;

Hit::Hit() {
      _Eta = 0.0;
}

Hit::Hit(float eta) {
      _Eta = eta;
}

float Hit::Eta() {
      return (_Eta);
}

void Hit::SetEta(float eta) {
      _Eta = eta;
}
