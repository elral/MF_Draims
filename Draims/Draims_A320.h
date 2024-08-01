#pragma once

#include "Arduino.h"
#include <TFT_eSPI.h>

// Use these when printing or drawing text in GLCD and high rendering speed fonts
// Call up the font using tft.setTextFont()
#define GFXFF 1
#define GLCD  0
#define FONT2 2
#define FONT4 4
#define FONT6 6
#define FONT7 7
#define FONT8 8

class draims_a320
{
public:
    draims_a320();
    void begin();
    void attach();
    void detach();
    void set(int16_t messageID, char *setPoint);
    void update();

private:
    bool      _initialised;
    TFT_eSPI *draims_tft;
};
