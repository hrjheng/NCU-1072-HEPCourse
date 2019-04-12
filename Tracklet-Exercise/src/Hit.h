#include <TObject.h>

using namespace std;

class Hit : public TObject
{
public:
      Hit();
      Hit(float);

      float Eta();

      void SetEta(float);

private:
      float _Eta;
};
