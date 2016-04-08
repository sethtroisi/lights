#include <cmath>
#include <cstdlib>

using namespace std;


void tracer(int round, int colors[][3]) {
  colors[ci][0] = max(0, colors[ci][0] - 1);
  colors[ci][1] = max(0, colors[ci][1] - 1);
  colors[ci][2] = max(0, colors[ci][2] - 1);
}
