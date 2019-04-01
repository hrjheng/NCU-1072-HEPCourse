#include <TObjArray.h>
#include <TString.h>
#include <TF1.h>
#include <TMath.h>
#include <TSystem.h>
#include "Nucleus.h"
#include "Nucleon.h"
using namespace std;

Nucleus::Nucleus(TString name, float x, float y, float z, float xsec_NN) {
    _name = name;
    _x = x;
    _y = y;
    _z = z;
    _Z = 0;
    _R = 0.0;
    _a = 0.0;
    _w = 0.0;
    _xsec_NN = xsec_NN;
    _list_nuclei = new TObjArray();
    _random = new TRandom3();
}

float Nucleus::x() {
      return (_x);
}

float Nucleus::y() {
      return (_y);
}

float Nucleus::z() {
      return (_z);
}

int Nucleus::Z() {
      return (_Z);
}

float Nucleus::a() {
      return (_a);
}

float Nucleus::w() {
      return (_w);
}

float Nucleus::xsec_NN() {
      return (_xsec_NN);
}

float Nucleus::R() {
      return (_R);
}

TObjArray* Nucleus::list_nuclei() {
      return (_list_nuclei);
}

TString Nucleus::name() {
      return (_name);
}

void Nucleus::SetNucParam() {
      if (_name == "Si") { _Z = 28; _a = 0.580; _w = -0.233;}
      else if (_name == "S") { _Z = 32; _a = 2.191; _w = 0.16;}
      else if (_name == "Ca") { _Z = 40; _a = 0.586; _w = -0.161;}
      else if (_name == "Ni") { _Z = 58; _a = 0.517; _w = -0.1308;}
      else if (_name == "Cu") { _Z = 62; _a = 0.596; _w = 0.0;}
      else if (_name == "Au") { _Z = 197; _a = 0.535; _w = 0.0;}
      else if (_name == "Pb") { _Z = 207; _a = 0.546; _w = 0.0;}
      else
      {
            std::cout << "Could not find nucleus " << _name << "!!" << endl;
            gSystem->Exit(123);
      }

      _R = 1.2*TMath::Power(_Z,1./3.);
      _funcR = new TF1("Fermi_dist","x*x*(1+[2]*(x/[0])**2)/(1+exp((x-[0])/[1]))",0,14);
      _funcR->SetParameters(_R,_a,_w);
}

void Nucleus::SetPosition(float x, float y, float z) {
      _x = x;
      _y = y;
      _z = z;
}

void Nucleus::Fill_nuclei() {
      for(int iNuc = 0; iNuc < _Z; iNuc++)
      {
            float r = _funcR->GetRandom(0,_R);
            float ctheta = (2.0 * _random->Rndm()) - 1.0;
            float stheta = TMath::Sqrt(1.0 - ctheta*ctheta);
            float phi = 2.0 * _random->Rndm() * TMath::Pi();
            Nucleon *nucleon = new Nucleon(_x+r*stheta*TMath::Cos(phi), _y+r*stheta*TMath::Sin(phi),_z+ctheta);
            nucleon->SetXSNN(_xsec_NN);
            _list_nuclei->Add(nucleon);
      }
      _list_nuclei->SetOwner();
}

void Nucleus::Refresh() {
      _list_nuclei->Clear();
}

int Nucleus::NumNuclei() {
      return _list_nuclei->GetEntries();
}
