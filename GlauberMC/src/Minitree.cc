#include <iostream>
#include <vector>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
#include "Nucleus.h"
#include "Nucleon.h"
#include "Event.h"
#include "Minitree.h"
using namespace std;

Minitree::Minitree() {
      _tree = new TTree("EventTree","EventTree");
      _tree->Branch("b",&_b);
      _tree->Branch("Npart",&_Npart);
      _tree->Branch("Ncoll",&_Ncoll);
      _tree->Branch("MeanX",&_MeanX);
      _tree->Branch("MeanY",&_MeanY);
      _tree->Branch("MeanX2",&_MeanX2);
      _tree->Branch("MeanY2",&_MeanY2);
      _tree->Branch("MeanXY",&_MeanXY);
      _tree->Branch("VarX",&_VarX);
      _tree->Branch("VarY",&_VarY);
      _tree->Branch("VarXY",&_VarXY);
      _tree->Branch("eps_RP",&_eps_RP);
      _tree->Branch("eps_part",&_eps_part);
      // _nucleon_x.clear();
      // _nucleon_y.clear();
      // _nucleon_z.clear();
      // _isparti.clear();
      // _nucleon_D.clear();
      _tree->Branch("Nucleon_x",&_nucleon_x);
      _tree->Branch("Nucleon_y",&_nucleon_y);
      _tree->Branch("Nucleon_z",&_nucleon_z);
      _tree->Branch("Nucleon_IsPart",&_isparti);
      _tree->Branch("Nucleon_D",&_nucleon_D);
}

void Minitree::FillEvent(Event *ev) {
      _b = ev->b();
      _Npart = ev->Npart();
      _Ncoll = ev->Ncoll();
      _MeanX = ev->MeanX();
      _MeanY = ev->MeanY();
      _MeanX2 = ev->MeanX2();
      _MeanY2 = ev->MeanY2();
      _MeanXY = ev->MeanXY();
      _VarX = ev->VarX();
      _VarY = ev->VarY();
      _VarXY = ev->VarXY();
      _eps_RP = ev->eps_RP();
      _eps_part = ev->eps_part();
      _nucleon_x = ev->Nucleon_x();
      _nucleon_y = ev->Nucleon_y();
      _nucleon_z = ev->Nucleon_z();
      _isparti = ev->vec_IsParti();
      _nucleon_D = ev->vec_Nuc_D();

      _tree->Fill();
}

void Minitree::SaveToFile(TString filename) {
      TFile *outfile = TFile::Open(filename.Data(), "RECREATE");
      outfile->cd();
      _tree->Write("", TObject::kOverwrite);
      outfile->Close();
}
