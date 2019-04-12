#include <TString.h>
#include <TRandom3.h>
#include <TObject.h>
#include "Nucleus.h"
#include "Nucleon.h"
#include "Event.h"
using namespace std;

Event::Event(Nucleus *NucA, Nucleus *NucB, float b) {
      _NucA = NucA;
      _NucB = NucB;
      _b = b;
      _random = new TRandom3();
      _Npart = 0;
      _Ncoll = 0;
      _MeanX = 0.0;
      _MeanY = 0.0;
      _MeanX2 = 0.0;
      _MeanY2 = 0.0;
      _MeanXY = 0.0;
      _VarX = 0.0;
      _VarY = 0.0;
      _VarXY = 0.0;
      _eps_RP = 0.0;
      _eps_part = 0.0;
      _HasColl = false;
}

void Event::Reset() {
      _Npart = 0;
      _Ncoll = 0;
      _MeanX = 0.0;
      _MeanY = 0.0;
      _MeanX2 = 0.0;
      _MeanY2 = 0.0;
      _MeanXY = 0.0;
      _VarX = 0.0;
      _VarY = 0.0;
      _VarXY = 0.0;
      _eps_RP = 0.0;
      _eps_part = 0.0;
}

int Event::Npart() {
      return (_Npart);
}

int Event::Ncoll() {
      return (_Ncoll);
}

float Event::b() {
      return (_b);
}

float Event::MeanX() {
      return (_MeanX);
}

float Event::MeanY() {
      return (_MeanY);
}

float Event::MeanX2() {
      return (_MeanX2);
}

float Event::MeanY2() {
      return (_MeanY2);
}

float Event::MeanXY() {
      return (_MeanXY);
}

float Event::VarX() {
      return (_VarX);
}

float Event::VarY() {
      return (_VarY);
}

float Event::VarXY() {
      return (_VarXY);
}

float Event::eps_RP() {
      return (_eps_RP);
}

float Event::eps_part() {
      return (_eps_part);
}

float Event::distance(Nucleon *eleA, Nucleon *eleB) {
      return (TMath::Sqrt(TMath::Power(eleA->x() - eleB->x(), 2) + TMath::Power(eleA->y() - eleB->y(), 2)));
}

void Event::SetEvent() {
      Reset();
      if(_HasColl == false)
      {
            cout << "No collision in this event!" << endl;
            gSystem->Exit(123);
      }

      for(int iNucA = 0; iNucA < _NucA->Z(); iNucA++)
      {
            Nucleon *nucleon_NucA = (Nucleon*)(_NucA->list_nuclei()->At(iNucA));
            if(nucleon_NucA->IsParticipant())
            {
                  _Npart++;
                  _Ncoll += nucleon_NucA->Ncollisions();
                  _MeanX += nucleon_NucA->x();
                  _MeanY += nucleon_NucA->y();
                  _MeanX2 += nucleon_NucA->x() * nucleon_NucA->x();
                  _MeanY2 += nucleon_NucA->y() * nucleon_NucA->y();
                  _MeanXY += nucleon_NucA->x() * nucleon_NucA->y();
            }
      }
      for(int iNucB = 0; iNucB < _NucB->Z(); iNucB++)
      {
            Nucleon *nucleon_NucB = (Nucleon*)(_NucB->list_nuclei()->At(iNucB));
            if(nucleon_NucB->IsParticipant())
            {
                  _Npart++;
                  _Ncoll += nucleon_NucB->Ncollisions();
                  _MeanX += nucleon_NucB->x();
                  _MeanY += nucleon_NucB->y();
                  _MeanX2 += nucleon_NucB->x() * nucleon_NucB->x();
                  _MeanY2 += nucleon_NucB->y() * nucleon_NucB->y();
                  _MeanXY += nucleon_NucB->x() * nucleon_NucB->y();
            }
      }

      _MeanX = _MeanX/float(_Npart);
      _MeanY = _MeanY/float(_Npart);
      _MeanX2 = _MeanX2/float(_Npart);
      _MeanY2 = _MeanY2/float(_Npart);
      _MeanXY = _MeanXY/float(_Npart);
      _VarX = _MeanX2 - _MeanX * _MeanX;
      _VarY = _MeanY2 - _MeanY * _MeanY;
      _VarXY = _MeanXY - _MeanX * _MeanY;
      _eps_RP = (_VarY - _VarX) / (_VarY + _VarX);
      _eps_part = TMath::Sqrt(TMath::Power(_VarY - _VarX, 2)+4.0*TMath::Power(_VarXY, 2))/(_VarY + _VarX);
}

bool Event::Make_Collision() {
      Reset();
      int count_coll = 0;
      for(int iNucA = 0; iNucA < _NucA->Z(); iNucA++)
      {
            Nucleon *nucleon_NucA = (Nucleon*)(_NucA->list_nuclei()->At(iNucA));
            for(int iNucB = 0; iNucB < _NucB->Z(); iNucB++)
            {
                  Nucleon *nucleon_NucB = (Nucleon*)(_NucB->list_nuclei()->At(iNucB));

                  if (distance(nucleon_NucA,nucleon_NucB) < 0.5*(nucleon_NucA->D()+nucleon_NucB->D()))
                  {
                        count_coll++;
                        nucleon_NucA->SetParticipant();
                        nucleon_NucB->SetParticipant();
                        nucleon_NucA->Collide();
                        nucleon_NucB->Collide();
                  }
            }
      }

      if(count_coll>0)
            _HasColl = true;

      return (_HasColl);
}
