#include <string>
#include <TMath.h>
#include <TObject.h>
using namespace std;

class Nucleon : public TObject
{
public:
      Nucleon();
      Nucleon(float, float, float);
      Nucleon(float, float, float, float);

      float D();
      float x();
      float y();
      float z();
      int Ncollisions();
      bool IsParticipant();

      void SetParticipant();
      void SetSpectator();
      void SetPosition(float, float, float);
      void SetXSNN(float);
      void Collide();


private:
      float _xsec_NN;
      float _D;
      float _x;
      float _y;
      float _z;
      int _Ncollisions;
      bool _IsParticipant;
};
