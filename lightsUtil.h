#ifndef LIGHTSUTIL_H
#define LIGHTSUTIL_H

#define DATA_PORT 14
#define CLOCK_PORT 15

#define WRITE_DELAY_US 5

void writeBit(bool bit);
void writeByte(int num);

void writeColor(int color[]);

void setupLights(void);

#endif /* LIGHTSUTIL_H */
