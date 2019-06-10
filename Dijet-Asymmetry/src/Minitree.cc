#include <iostream>
#include <vector>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include "Event.h"
#include "Minitree.h"
using namespace std;

Minitree::Minitree() {
      _tree = new TTree("EventTree","EventTree");
      _pt.clear();
      _eta.clear();
       _phi.clear();
      _tree->Branch("ev",&_ev);
      _tree->Branch("pT",&_pt);
      _tree->Branch("eta",&_eta);
      _tree->Branch("phi",&_phi);
}

void Minitree::FillEvent(Event *evt, int ev) {
      _ev = ev;
      _pt = evt->pT();
      _eta = evt->eta();
      _phi = evt->phi();

      _tree->Fill();
}

void Minitree::SaveToFile(TString filename) {
      TFile *outfile = TFile::Open(filename.Data(), "RECREATE");
      outfile->cd();
      _tree->Write("", TObject::kOverwrite);
      outfile->Close();
}
