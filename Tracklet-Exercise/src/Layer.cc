#include <TObject.h>
#include <TObjArray.h>
#include <TString.h>
#include <TF1.h>
#include <TMath.h>
#include <TSystem.h>
#include "Layer.h"
#include "Hit.h"

using namespace std;

Layer::Layer() {
      _list_hits = new TObjArray();
}

int Layer::Nhits() {
      return (_list_hits->GetEntries());
}

TObjArray* Layer::list_hits() {
      return (_list_hits);
}

void Layer::AddHit(float hit_eta) {
      Hit *hit = new Hit(hit_eta);
      _list_hits->Add(hit);
}

void Layer::Refresh() {
      _list_hits->SetOwner();
      _list_hits->Clear();
}
