#include <TString.h>
#include <TMath.h>
#include <TRandom3.h>
#include "Nucleon.h"
using namespace std;

Nucleon::Nucleon() {
    _x = 0.0;
    _y = 0.0;
    _z = 0.0;
    _D = 0.0;
    _xsec_NN = 0.0;
    _Ncollisions = 0.0;
    _IsParticipant = false;
}

Nucleon::Nucleon(float x, float y, float z) {
    _x = x;
    _y = y;
    _z = z;
    _D = 0.0;
    _xsec_NN = 0.0;
    _Ncollisions = 0.0;
    _IsParticipant = false;
}

Nucleon::Nucleon(float x, float y, float z, float xsec_NN) {
    _x = x;
    _y = y;
    _z = z;
    _D = TMath::Sqrt(0.1 * xsec_NN / TMath::Pi());
    _xsec_NN = xsec_NN;
    _Ncollisions = 0.0;
    _IsParticipant = false;
}

float Nucleon::x() {
      return (_x);
}

float Nucleon::y() {
      return (_y);
}

float Nucleon::z() {
      return (_z);
}

float Nucleon::D() {
      return (_D);
}

int Nucleon::Ncollisions() {
      return (_Ncollisions);
}

bool Nucleon::IsParticipant() {
      return (_IsParticipant);
}

void Nucleon::SetParticipant() {
      _IsParticipant = true;
}

void Nucleon::SetSpectator() {
      _IsParticipant = false;
}

void Nucleon::SetPosition(float x, float y, float z) {
      _x = x;
      _y = y;
      _z = z;
}

void Nucleon::SetXSNN(float xsec_NN) {
      _xsec_NN = xsec_NN;
      _D = TMath::Sqrt(0.1 * xsec_NN / TMath::Pi()); // D is automatically set as long as xsec_NN is set
}

void Nucleon::Collide() {
      _Ncollisions++;
}
