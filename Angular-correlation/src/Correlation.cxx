#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Event.h"
#include "Minitree.h"

#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TString.h>
#include <TVector2.h>

using namespace std;

double deltaPhi(double phi1, double phi2) {

      double dPhi = phi1 - phi2;
      if (dPhi > TMath::Pi())
            dPhi -= 2.*TMath::Pi();
      if (dPhi < -TMath::Pi())
            dPhi += 2.*TMath::Pi();

      // Shift dPhi from [-pi,pi] to [(-1/2)*pi,(3/2)*pi]
      if(dPhi < (-1./2.)*TMath::Pi())
            dPhi += 2.*TMath::Pi();

      return dPhi;
}

double deltaEta(double eta1, double eta2) {
  return eta1 - eta2;
}

TH2F* hist_signal(TString fname, TString histname, int nbinx, float minx, float maxx, int nbiny, float miny, float maxy)
{
      TH2F *hM = new TH2F(histname.Data(),histname.Data(),nbinx,minx,maxx,nbiny,miny,maxy);

      TFile *file = new TFile(fname.Data(),"READ");
      file->cd();
      TTree *tree = (TTree*) file->Get("EventTree");
      std::vector<float> *v_pt = 0;
      std::vector<float> *v_eta = 0;
      std::vector<float> *v_phi = 0;
      std::vector<int> *v_Q = 0;
      tree->SetBranchAddress("pT",&v_pt);
      tree->SetBranchAddress("eta",&v_eta);
      tree->SetBranchAddress("phi",&v_phi);
      tree->SetBranchAddress("charge",&v_Q);

      int ntracks = 0;
      for (Int_t i = 0; i < (Int_t) tree->GetEntriesFast(); i++)
      {
            tree->GetEntry(i);
            ntracks = 0;

            // for(int itrk=0;itrk<v_eta->size()-1;itrk++)
            for(int itrk=0;itrk<v_eta->size();itrk++)
            {
                  // for(int jtrk=itrk+1;jtrk<v_eta->size();jtrk++)
                  for(int jtrk=0;jtrk<v_eta->size();jtrk++)
                  {
                        if(itrk==jtrk) continue;
                        if(fabs(v_eta->at(itrk))>1.6 || v_pt->at(itrk) < 1.) continue;
                        if(fabs(v_eta->at(jtrk))>1.6 || v_pt->at(jtrk) < 1.) continue;

                        if(fabs(deltaEta(v_eta->at(itrk),v_eta->at(jtrk))) < 1.) continue;
                        if(v_pt->at(itrk) > 2. || v_pt->at(jtrk) > 2.) continue;

                        ntracks++;

                        hM->Fill(deltaEta(v_eta->at(itrk),v_eta->at(jtrk)), deltaPhi(v_phi->at(itrk),v_phi->at(jtrk)));
                  }
            }

            // cout << "Event " << i << "; # of track pairs " << ntracks << endl;
      }
      delete tree;
      file->Close();
      delete file;

      return hM;
}

void GetTreeEntry(TString name, int ev, std::vector<float> &vpt, std::vector<float> &veta, std::vector<float> &vphi)
{
      TFile *file = new TFile(name.Data(),"READ");
      file->cd();
      TTree *tree = (TTree*) file->Get("EventTree");
      std::vector<float> *v_pt = 0;
      std::vector<float> *v_eta = 0;
      std::vector<float> *v_phi = 0;
      std::vector<int> *v_Q = 0;
      tree->SetBranchAddress("pT",&v_pt);
      tree->SetBranchAddress("eta",&v_eta);
      tree->SetBranchAddress("phi",&v_phi);
      tree->SetBranchAddress("charge",&v_Q);

      tree->GetEntry(ev);
      vpt = *v_pt;
      veta = *v_eta;
      vphi = *v_phi;

      delete tree;
      file->Close();
      delete file;
}

TH2F* hist_bkg(TString fname, TString histname, int nbinx, float minx, float maxx, int nbiny, float miny, float maxy)
{
      cout << "Run event mixing!" << endl;

      int nentries = 0;
      TFile *file = new TFile(fname.Data(),"READ");
      file->cd();
      TTree *tree = (TTree*) file->Get("EventTree");
      nentries = tree->GetEntriesFast();
      file->Close();
      delete file;

      TH2F *hM = new TH2F(histname.Data(),histname.Data(),nbinx,minx,maxx,nbiny,miny,maxy);
      // TH2F *hM_check_eta = new TH2F("hM_check_eta","",64,-1.6,1.6,64,-1.6,1.6);
      // TH2F *hM_check_phi = new TH2F("hM_check_phi","",70,-3.5,3.5,70,-3.5,3.5);

      std::vector<float> v_pt_ev1;
      std::vector<float> v_pt_ev2;
      std::vector<float> v_eta_ev1;
      std::vector<float> v_eta_ev2;
      std::vector<float> v_phi_ev1;
      std::vector<float> v_phi_ev2;

      int ev = 0;
      while (ev < nentries-1)
      {
            GetTreeEntry(fname, ev, v_pt_ev1, v_eta_ev1, v_phi_ev1);
            GetTreeEntry(fname, ev+1, v_pt_ev2, v_eta_ev2, v_phi_ev2);

            for(int itrk=0;itrk<v_eta_ev1.size();itrk++)
            {
                  for(int jtrk=0;jtrk<v_eta_ev2.size();jtrk++)
                  {
                        if(fabs(v_eta_ev1[itrk])>1.6 || v_pt_ev1[itrk] < 1.) continue;
                        if(fabs(v_eta_ev2[jtrk])>1.6 || v_pt_ev2[jtrk] < 1.) continue;

                        if(fabs(deltaEta(v_eta_ev1[itrk],v_eta_ev2[jtrk])) < 1.) continue;
                        if(v_pt_ev1[itrk] > 2. || v_pt_ev2[jtrk] > 2.) continue;

                        hM->Fill(deltaEta(v_eta_ev1[itrk],v_eta_ev2[jtrk]), deltaPhi(v_phi_ev1[itrk],v_phi_ev2[jtrk]));

                        // if(deltaEta(v_eta_ev1[itrk],v_eta_ev2[jtrk]) < -3. && (deltaPhi(v_phi_ev1[itrk],v_phi_ev2[jtrk])>2.8 && deltaPhi(v_phi_ev1[itrk],v_phi_ev2[jtrk])<2.9))
                        // {
                        //       // cout << v_eta_ev1[itrk] << " " << v_eta_ev2[jtrk] << " " << v_phi_ev1[itrk] << " " << v_phi_ev2[jtrk] << endl;
                        //       hM_check_eta->Fill(v_eta_ev1[itrk],v_eta_ev2[jtrk]);
                        //       hM_check_phi->Fill(v_phi_ev1[itrk],v_phi_ev2[jtrk]);
                        // }
                  }
            }

            ev++;
            v_pt_ev1.clear();
            v_eta_ev1.clear();
            v_phi_ev1.clear();
            v_pt_ev2.clear();
            v_eta_ev2.clear();
            v_phi_ev2.clear();
      }

      // TFile *ftmp = new TFile("check-hist.root","RECREATE");
      // ftmp->cd();
      // hM_check_eta->Write();
      // hM_check_phi->Write();
      // ftmp->Close();

      return hM;
}

int main(int argc, char *argv[]) {

      TH2F *hM_sig = hist_signal("./data/data_20k.root","hM_sig",20,-4,4,35,-2,5);
      // TH2F *hM_sig_2 = hist_signal("./data/data_20k.root","hM_sig_zoom1",25,-3.5,-2.5,20,2.8,3.2);
      TH2F *hM_bkg = hist_bkg("./data/data_20k.root","hM_bkg",20,-4,4,35,-2,5);
      // TH2F *hM_bkg_2 = hist_bkg("./data/data_20k.root","hM_bkg_zoom1",25,-3.5,-2.5,20,2.8,3.2);


      system("mkdir -p ./plots");
      TFile *fout = new TFile("./plots/hist_corr_20k.root","RECREATE");
      fout->cd();
      hM_sig->Write();
      // hM_sig_2->Write();
      hM_bkg->Write();
      // hM_bkg_2->Write();
      fout->Close();

      return 0;
}
