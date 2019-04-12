#include <TObject.h>
#include <TObjArray.h>
#include <TString.h>
#include <TMath.h>

using namespace std;

class Layer : public TObject
{
public:
      Layer();

      int Nhits();
      TObjArray* list_hits();

      void AddHit(float);
      void Refresh();

private:
      TObjArray* _list_hits;
};
