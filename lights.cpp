#include <iostream>
#include <cstdlib>
#include <ctime>
#include <wiringPi.h>

using namespace std;

#define dataPort 9
#define clockPort 8

void writeBit(bool bit) {
	cout << bit;
	digitalWrite (dataPort, bit);     // data

	digitalWrite (clockPort, 1);       // CLK up
	digitalWrite (clockPort, 0);       // CLK down

}

void writeByte(char num) {
	cout << (int) num << " : ";
	for (int bit = 1; bit <= 255; bit <<= 1) {
		writeBit((num & bit) > 0);
	}
	cout << endl;
}

void writeColor(char color[]) {
	writeByte(color[0]);
	writeByte(color[1]);
	writeByte(color[2]);
	cout << endl;
}

 
int main (void)
{

  if (wiringPiSetup () == -1) {
		cout << "wiringPiSetup failed" << endl;
    return 1;
	}

	cout << "Hello world!" << endl;

  pinMode (clockPort, OUTPUT);
  pinMode (dataPort, OUTPUT);

	srand(time(0));
	int major = rand() % 3;

	cout << "major: " << major << endl;
	cout << endl;

	char colors[100][3] = {};
	for (int ci = 0; ci < 6; ci++) {
		colors[ci][major] = 255 - 10 * ci;

		writeColor(colors[ci]);
	}



	cout << "program finished" << endl;
 
  return 0;
}
