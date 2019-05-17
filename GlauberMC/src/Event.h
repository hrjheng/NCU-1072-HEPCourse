#include <iostream>
#include <vector>
#include <string>
#include <TRandom3.h>
using namespace std;

class Event {
public:
      Event(Nucleus*, Nucleus*, float);

      float b();
      int Npart();
      int Ncoll();
      float MeanX();
      float MeanY();
      float MeanX2();
      float MeanY2();
      float MeanXY();
      float VarX();
      float VarY();
      float VarXY();
      float eps_RP();
      float eps_part();
      std::vector<float> Nucleon_x();
      std::vector<float> Nucleon_y();
      std::vector<float> Nucleon_z();
      std::vector<int> vec_IsParti();
      std::vector<float> vec_Nuc_D();
      bool Make_Collision();
      void SetEvent(bool);


private:
      Nucleus *_NucA;
      Nucleus *_NucB;
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
      std::vector<float> _Nucleon_x;
      std::vector<float> _Nucleon_y;
      std::vector<float> _Nucleon_z;
      std::vector<int> _IsParti;
      std::vector<float> _Nuc_D;

      TRandom3 *_random;

      float distance(Nucleon *eleA, Nucleon *eleB);
      void Reset();
      bool _HasColl;
};
