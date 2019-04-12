#include <TObject.h>
#include <TObjArray.h>
#include <TString.h>
#include <TF1.h>
#include <TMath.h>
#include <TSystem.h>
using namespace std;

class Event {
public:
      Event(Layer*, Layer*);

      void Refresh();

private:
      Layer* _L1;
      Layer* _L2;
};
