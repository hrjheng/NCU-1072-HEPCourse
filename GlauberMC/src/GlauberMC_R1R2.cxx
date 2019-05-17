#include "Nucleus.h"
#include "Nucleon.h"
#include "Event.h"
#include "Minitree.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <TObjString.h>
#include <TH2F.h>
#include <TMath.h>
#include <TEllipse.h>
#include <TRandom.h>
#include <TLine.h>

std::vector<int> Setup_ellipse(std::vector<int> *Nucleon_IsPart)
{
      std::vector<int> vec_idxpart;
      for(int i=0;i<Nucleon_IsPart->size();i++)
      {
            if(Nucleon_IsPart->at(i)==1) vec_idxpart.push_back(i);
      }

    return vec_idxpart;
}

void Coordinate_transform(float &x, float &y, float angle)
{
      float xprime = x*TMath::Cos(angle)+y*TMath::Sin(angle);
      float yprime = -x*TMath::Sin(angle)+y*TMath::Cos(angle);
      x = xprime;
      y = yprime;
}

void R1R2(float &R1, float &R2, vector<float> *Nuc_x, vector<float> *Nuc_y, vector<float> *Nuc_D, vector<int> list_idxpart, TEllipse *RefNuc, float angle)
{
      vector<float> list_R_positive;
      vector<float> list_R_negative;
      for(int ipart=0; ipart<list_idxpart.size(); ipart++)
      {
            // std::cout << angle << endl;
            if(Nuc_x->at(list_idxpart[ipart]) == RefNuc->GetX1() || Nuc_y->at(list_idxpart[ipart]) == RefNuc->GetY1()) continue;

            float x = Nuc_x->at(list_idxpart[ipart]) - RefNuc->GetX1();
            float y = Nuc_y->at(list_idxpart[ipart]) - RefNuc->GetY1();
            // std::cout << "x0, y0 " << x << " " << y << endl;
            Coordinate_transform(x,y,angle);
            // std::cout << "(transformed) x, y " << x << " " << y << endl;
            if(fabs(y)<0.5*Nuc_D->at(list_idxpart[ipart]))
            {
                  if(x>0.)
                  {
                        list_R_positive.push_back(x+TMath::Sqrt(TMath::Power(Nuc_D->at(list_idxpart[ipart])/2.,2)-TMath::Power(y,2)));
                  }
                  else if(x<0.)
                  {
                        list_R_negative.push_back(fabs(x-TMath::Sqrt(TMath::Power(Nuc_D->at(list_idxpart[ipart])/2.,2)-TMath::Power(y,2))));
                  }
                  else
                        continue;
            }
            else
                  continue;
      }

      if(list_R_positive.size()<1)
      {
            list_R_positive.push_back(Nuc_D->at(list_idxpart[0])/2.);
      }

      if(list_R_negative.size()<1)
      {
            list_R_negative.push_back(Nuc_D->at(list_idxpart[0])/2.);
      }

      R1 = *max_element(list_R_positive.begin(), list_R_positive.end());
      R2 = *max_element(list_R_negative.begin(), list_R_negative.end());
      if(R1 < Nuc_D->at(list_idxpart[0])/2.) R1 = Nuc_D->at(list_idxpart[0])/2.;
      if(R2 < Nuc_D->at(list_idxpart[0])/2.) R2 = Nuc_D->at(list_idxpart[0])/2.;
}

int main(int argc, char *argv[]) {
      TString NucleusType = TString(argv[1]);
      float XS_NN = TString(argv[2]).Atof();

      TH2F *hM_R1R2 = new TH2F("hM_R1R2","",200,0,20,200,0,20);

      std::vector<int> list_idxpart; list_idxpart.clear();

      TFile *fin = new TFile("./collision-data/EventTree/Pb-Pb-IPless3.5fm-XSNN72.0mb-Nevt10000.root","READ");
      TTree* tree = (TTree*) fin->Get("EventTree");
      std::vector<float> *Nucleon_x=0;
      std::vector<float> *Nucleon_y=0;
      std::vector<float> *Nucleon_z=0;
      std::vector<int> *Nucleon_IsPart=0;
      std::vector<float> *Nucleon_D=0;
      tree->SetBranchAddress("Nucleon_x", &Nucleon_x);
      tree->SetBranchAddress("Nucleon_y", &Nucleon_y);
      tree->SetBranchAddress("Nucleon_z", &Nucleon_z);
      tree->SetBranchAddress("Nucleon_IsPart", &Nucleon_IsPart);
      tree->SetBranchAddress("Nucleon_D", &Nucleon_D);
      for(int i=0;i<tree->GetEntriesFast();i++)
      {
            tree->GetEntry(i);

            TRandom *random = new TRandom3();
            list_idxpart.clear();
            list_idxpart = Setup_ellipse(Nucleon_IsPart);
            // std::cout << list_idxpart.size() << std::endl;
            int rand_idx = list_idxpart[random->Integer(list_idxpart.size())];
            TEllipse *RefNuc = new TEllipse(Nucleon_x->at(rand_idx),Nucleon_y->at(rand_idx),Nucleon_D->at(rand_idx)/2.,Nucleon_D->at(rand_idx)/2.);

            for(int iran=0;iran<100;iran++)
            {
                  float phi = 2.*TMath::Pi()*random->Rndm();
                  TLine *l1 = new TLine(Nucleon_x->at(rand_idx)+13*TMath::Cos(TMath::Pi()+phi),Nucleon_y->at(rand_idx)+13*TMath::Sin(TMath::Pi()+phi),Nucleon_x->at(rand_idx)+13*TMath::Cos(phi),Nucleon_y->at(rand_idx)+13*TMath::Sin(phi));

                  float R1 = 0;
                  float R2 = 0;
                  R1R2(R1, R2, Nucleon_x, Nucleon_y, Nucleon_D, list_idxpart, RefNuc, phi);

                  if(i % 1000 == 0 and iran == 0)
                  {
                        std::cout << i << " " << R1 << " " << R2 << endl;
                  }

                  hM_R1R2->Fill(R1,R2);
            }
      }

      fin->Close();

      TFile *fout = new TFile("./plots/histogram-R1R2.root","RECREATE");
      fout->cd();
      hM_R1R2->Write();
      fout->Close();

      return 0;
}
