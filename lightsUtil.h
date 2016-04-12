#define DATA_PORT 9
#define CLOCK_PORT 8

#define WRITE_DELAY_US 4

void writeBit(bool bit);
void writeByte(int num);

void writeColor(int color[]);

void setupLights(void);
