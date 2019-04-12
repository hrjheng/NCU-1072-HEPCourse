#include <string>
#include <TObjArray.h>
#include <TRandom3.h>
#include <TSystem.h>
#include <TF1.h>
#include <TMath.h>
using namespace std;

class Nucleus {
public:
      Nucleus(TString, float, float, float, float);

      TString name();
      float x();
      float y();
      float z();
      int Z();
      float a();
      float w();
      float R();
      float xsec_NN();
      TObjArray* list_nuclei();

      void SetNucParam();
      void SetPosition(float, float, float);
      void Fill_nuclei();
      void Refresh();
      int NumNuclei();


private:
      TString _name;
      float _x;
      float _y;
      float _z;
      int _Z;
      float _a;
      float _w;
      float _R;
      float _xsec_NN;
      TF1* _funcR;
      TObjArray* _list_nuclei;
      TRandom3* _random;

};
