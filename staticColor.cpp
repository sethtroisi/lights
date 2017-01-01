#include <cassert>
#include <cmath>
#include <iostream>

#include "staticColor.h"

using namespace std;

int hexValue(char hex) {
  if (hex >= '0' && hex <= '9') {
    return hex - '0';
  } else if (hex >= 'A' && hex <= 'F') {
    return hex - 'A' + 10;
  } else if (hex >= 'a' && hex <= 'f') {
    return hex - 'f' + 10;
  } else {
    cout << "UNKNOWN HEX: " << hex << endl;
    return 0;
  }
}

int readHex(string hex) {
  if (hex.size() == 0) {
    return 0;
  }
  return 16 * readHex(hex.substr(1)) + hexValue(hex.back());
}


void StaticColor::setupEffect() {
  /////////// CONFIG STARTS HERE ///////////

  brightness = 0.8;

  // These defines how the color sparkles.
  deriv = 0.01;

  if (parameters.find("color") != parameters.end()) {
    string color = parameters["color"];
    cout << "\t" << "parameter color: " << color << endl;

    if (color.front() == '#') {
      color = color.substr(1);
    }

    if (color.size() == 3) {
      color = color.substr(0, 1) + color.substr(0, 1) +
              color.substr(1, 1) + color.substr(1, 1) +
              color.substr(2, 1) + color.substr(2, 1);
    }
    staticColor[0] = readHex(color.substr(0, 2));
    staticColor[1] = readHex(color.substr(2, 2));
    staticColor[2] = readHex(color.substr(4, 2));
  } else { 
    staticColor[0] = randomInt(140,255);
    staticColor[1] = randomInt(10,40);
    staticColor[2] = randomInt(0,20);

    // shuffle
    swap(staticColor[2], staticColor[randomInt(0,2)]);
    swap(staticColor[1], staticColor[randomInt(0,1)]);
    cout << "\t" << "random static color: " << staticColor[0] << ", " <<
                                               staticColor[1] << ", " <<
                                               staticColor[2] << endl;
  }

  //////////// CONFIG ENDS HERE ////////////
};  

void StaticColor::iterate() {
  iter++;

//  if (oneInX(cyclesPerColor)) {
//    setupEffect();
//  }

  brightness += deriv;
  if (brightness < 0 || brightness > 1) {
    deriv *= -1;
  }

  brightness = clamp(brightness, 0.0, 1.0);


  for (int ci = 0; ci < n; ci++) {
    for (int part = 0; part < 3; part++) {
      float c = staticColor[part];
      (*colors)[ci][part] = c * brightness;
    }
  }
}
