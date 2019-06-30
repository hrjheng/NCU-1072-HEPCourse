#include "Hit.h"
#include "Layer.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include <TObjString.h>
#include <TH1F.h>
#include <TFile.h>

int main(int argc, char *argv[]) {
      TObjArray *list_layers = new TObjArray();
      Layer *layer = new Layer();

      std::ifstream in;
      in.open("tracklet_data.txt");

      float x = -1.;
      int LayerIdx = 0;
      while(1)
      {
            in >> x;

            if(!in.good())
            {
                  Layer *temp = new Layer();
                  temp = layer;
                  list_layers->Add(temp);

                  break;
            }

            if (x > 10.0)
            {
                  if(LayerIdx>0)
                  {
                        Layer *temp = new Layer();
                        temp = layer;
                        list_layers->Add(temp);

                        layer = new Layer();
                  }
                  LayerIdx++;
            }
            else
            {
                  layer->AddHit(x);
            }

      }


      TH1F *hM = new TH1F("hM","",80,-0.02,0.02);
      TH1F *hM_eta = new TH1F("hM_eta","",40,-1.1,1.1);
      float deta_tmp = 99.;
      float eta2_tmp = 99.;
      for(int iL = 0; iL<list_layers->GetEntries()/2; iL++)
      // for(int iL = 0; iL<1; iL++)
      {
            Layer *Layer1 = (Layer*) list_layers->At(2*iL);
            Layer *Layer2 = (Layer*) list_layers->At(2*iL + 1);

            deta_tmp = 99.;
            eta2_tmp = 99.;
            for(int iHit_L1 = 0; iHit_L1 < Layer1->list_hits()->GetEntries(); iHit_L1++)
            {
                  Hit *tmpHit1 = (Hit*) Layer1->list_hits()->At(iHit_L1);
                  for(int iHit_L2 = 0; iHit_L2 < Layer2->list_hits()->GetEntries(); iHit_L2++)
                  {
                        Hit *tmpHit2 = (Hit*) Layer2->list_hits()->At(iHit_L2);
                        hM->Fill(tmpHit1->Eta() - tmpHit2->Eta());

                        if(fabs(tmpHit1->Eta() - tmpHit2->Eta()) < deta_tmp)
                        {
                              deta_tmp = fabs(tmpHit1->Eta() - tmpHit2->Eta());
                              eta2_tmp = tmpHit2->Eta();
                        }
                  }
                  hM_eta->Fill((tmpHit1->Eta()+eta2_tmp)/2.);
            }
      }
      
      TFile *fout = new TFile("histogram.root","RECREATE");
      fout->cd();
      hM->Write();
      hM_eta->Write();
      fout->Close();

      return 0;
}
