#include <TTree.h>
#include <TFile.h>
#include <TObject.h>
using namespace std;

class Minitree {
public:
      Minitree();

      void FillEvent(Event*);
      void SaveToFile(TString);

private:
      TTree *_tree;

      float _b;
      int _Npart;
      int _Ncoll;
      float _MeanX;
      float _MeanY;
      float _MeanX2;
      float _MeanY2;
      float _MeanXY;
      float _VarX;
      float _VarY;
      float _VarXY;
      float _eps_RP;
      float _eps_part;
};
