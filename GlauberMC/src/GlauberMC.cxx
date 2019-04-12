#include "Nucleus.h"
#include "Nucleon.h"
#include "Event.h"
#include "Minitree.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <TObjString.h>

int main(int argc, char *argv[]) {

      TString NucleusType = TString(argv[1]);
      TObjArray *tx = NucleusType.Tokenize("-");
      float B = TString(argv[2]).Atof();
      TString prefix_B = (B>0.0) ? TString(argv[2]) : "Random";
      float XS_NN = TString(argv[3]).Atof();
      int Nevt = TString(argv[4]).Atoi();

      Minitree *minitree = new Minitree();

      cout << "Impact parameter B = " << B << endl
            << "Nucleon-nucleon cross-section = " << XS_NN << endl
            << "Number of events to be generated = " << Nevt << endl;

      Nucleus *NucleusA = new Nucleus(((TObjString *)(tx->At(0)))->String(),0.,0.,0.,XS_NN);
      Nucleus *NucleusB = new Nucleus(((TObjString *)(tx->At(1)))->String(),0.,0.,0.,XS_NN);
      NucleusA->SetNucParam();
      NucleusB->SetNucParam();

      TRandom3 *rand = new TRandom3();
      float bmin = 0.0;
      float bmax = 20.0;
      float b = -1.0;

      int ievt = 0;
      while (ievt < Nevt)
      {
            if ((ievt>0)&&(ievt%500)==0) cout << "Event " << ievt << " / " << Nevt << "\r" << flush;

            if (B < 0.) { b = TMath::Sqrt( (bmax*bmax-bmin*bmin) * (rand->Rndm()) + bmin*bmin ); }
            else { b = B; }

            NucleusA->SetPosition(0. + b/2, 0., 0.);
            NucleusB->SetPosition(0. - b/2, 0., 0.);
            NucleusA->Fill_nuclei();
            NucleusB->Fill_nuclei();
            Event *event = new Event(NucleusA,NucleusB,b);
            if(event->Make_Collision() == true)
            {
                  event->SetEvent();
                  ievt++;
                  minitree->FillEvent(event);
            }

            NucleusA->Refresh();
            NucleusB->Refresh();
            delete event;
      }
      system("mkdir -p ./collision-data/EventTree");
      minitree->SaveToFile("./collision-data/EventTree/"+NucleusType+"-IP"+prefix_B+"fm-XSNN"+TString(argv[3])+"mb-Nevt"+TString(argv[4])+".root");

      return 0;
}
