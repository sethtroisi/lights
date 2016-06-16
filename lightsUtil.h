#ifndef LIGHTSUTIL_H
#define LIGHTSUTIL_H

#define DATA_PORT 14
#define CLOCK_PORT 15

#define WRITE_DELAY_US 2

#define WS2818_T0H_NS 400
#define WS2818_T0L_NS 850

#define WS2818_T1H_NS 800
#define WS2818_T1L_NS 450

void writeBit(bool bit);
void writeByte(int num);

void writeColor(int color[]);

void setupLights(void);

#endif /* LIGHTSUTIL_H */
