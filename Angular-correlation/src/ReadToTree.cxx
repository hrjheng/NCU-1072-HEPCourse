#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Event.h"
#include "Minitree.h"

#include <TH1F.h>

using namespace std;


std::vector<float> getFloats(const std::string& s) {
    std::istringstream iss(s);
    std::string word;
    std::vector<float> result;

    size_t pos = 0;
    while (iss >> word) {
        try {
            float f = std::stof(word, &pos);
            if (pos == word.size()) {
                result.push_back(f);
            }
        }
        catch (std::invalid_argument const& ) {
            // no part of word is a float
            continue;
        }
    }

    return result;
}


int main(int argc, char *argv[]) {
      int ev = -1;
      Minitree *minitree = new Minitree();
      TH1F *hM_pt = new TH1F("hM_pt","",80,0,40);
      TH1F *hM_eta = new TH1F("hM_eta","",60,-3,3);
      TH1F *hM_phi = new TH1F("hM_phi","",70,-3.5,3.5);

      vector<float> v_pt; v_pt.clear();
      vector<float> v_eta; v_eta.clear();
      vector<float> v_phi; v_phi.clear();
      vector<int> v_q; v_q.clear();

      std::ifstream in("PbPb_5TeV_Cent40_50.txt");
      if(in.is_open()){
            std::string line;
            while (getline(in, line))
            {
                  if (line.find("Event") != string::npos) continue;
                  if (line.find("Tracks") != string::npos)
                  {
                        if(ev>-1)
                        {
                              Event *evt = new Event(v_pt,v_eta,v_phi,v_q);
                              cout << ev << " " << v_pt.size() << endl;
                              minitree->FillEvent(evt,ev);
                        }

                        ev++;

                        v_pt.clear();
                        v_eta.clear();
                        v_phi.clear();
                        v_q.clear();
                        // cout << ev << endl;
                        continue;
                  }

                  std::vector<float> result;
                  result = getFloats(line);
                  v_pt.push_back(result[0]);
                  v_eta.push_back(result[1]);
                  v_phi.push_back(result[2]);
                  v_q.push_back(result[3]);
                  hM_pt->Fill(result[0]);
                  hM_eta->Fill(result[1]);
                  hM_phi->Fill(result[2]);
            }
            Event *evt = new Event(v_pt,v_eta,v_phi,v_q);
            cout << ev << " " << v_pt.size() << endl;
            minitree->FillEvent(evt,ev);
      }
      in.close();

      system("mkdir -p ./data");
      minitree->SaveToFile("./data/data.root");
      TFile *f_hM = new TFile("./data/histogram.root","RECREATE");
      f_hM->cd();
      hM_pt->Write();
      hM_eta->Write();
      hM_phi->Write();
      f_hM->Close();

      return 0;
}
