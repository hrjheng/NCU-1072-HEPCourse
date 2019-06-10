#include <iostream>
#include <vector>

#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
using namespace std;

class Minitree {
public:
      Minitree();

      void FillEvent(Event*,int);
      void SaveToFile(TString);

private:
      TTree *_tree;

      int _ev;
      vector<float> _pt;
      vector<float> _eta;
      vector<float> _phi;
};
