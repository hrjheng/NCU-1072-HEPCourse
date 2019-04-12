#include <TObject.h>
#include <TObjArray.h>
#include <TString.h>
#include <TF1.h>
#include <TMath.h>
#include <TSystem.h>
#include "Event.h"
#include "Layer.h"
#include "Hit.h"

using namespace std;

Event::Event(Layer *L1, Layer *L2) {
      _L1 = L1;
      _L2 = L2;
}

void Tracklet::Refresh() {
      _L1->SetOwner();
      _L1->Clear();
      _L2->SetOwner();
      _L2->Clear();
}
