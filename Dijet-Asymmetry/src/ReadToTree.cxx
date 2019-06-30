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

      vector<float> v_pt; v_pt.clear();
      vector<float> v_eta; v_eta.clear();
      vector<float> v_phi; v_phi.clear();

      std::ifstream in("jet_data_pp_v2.txt");
      if(in.is_open()){
            std::string line;
            while (getline(in, line))
            {
                  std::vector<float> vtmp;
                  vtmp = getFloats(line);
                  if (vtmp.size() < 2)
                  {
                        if(ev>-1)
                        {
                              Event *evt = new Event(v_pt,v_eta,v_phi);
                              // if (v_pt.size()!=2) cout << ev << " " << v_pt.size() << endl;
                              minitree->FillEvent(evt,ev);
                        }

                        ev++;

                        v_pt.clear();
                        v_eta.clear();
                        v_phi.clear();
                        // cout << ev << endl;
                        continue;
                  }

                  std::vector<float> result;
                  result = getFloats(line);
                  v_eta.push_back(result[0]);
                  v_pt.push_back(result[1]);
                  v_phi.push_back(result[2]);
            }
            Event *evt = new Event(v_pt,v_eta,v_phi);
            // if (v_pt.size()!=2) cout << ev << " " << v_pt.size() << endl;
            minitree->FillEvent(evt,ev);
      }
      in.close();

      system("mkdir -p ./data");
      minitree->SaveToFile("./data/dijet_events_v2.root");

      return 0;
}
