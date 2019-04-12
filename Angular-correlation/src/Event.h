#include <iostream>
#include <vector>

using namespace std;

class Event {
public:
      Event(std::vector<float>, std::vector<float>, std::vector<float>, std::vector<int>);

      std::vector<float> pT();
      std::vector<float> eta();
      std::vector<float> phi();
      std::vector<int> charge();


private:
      std::vector<float> _pt;
      std::vector<float> _eta;
      std::vector<float> _phi;
      std::vector<int> _q;

};
