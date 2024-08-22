#include "Draims_A320.h"
#include "allocateMem.h"
#include "commandmessenger.h"

/* **********************************************************************************
    This is just the basic code to set up your custom device.
    Change/add your code as needed.
********************************************************************************** */

draims_a320::draims_a320()
{
    _initialised = false;
}

void draims_a320::attach()
{
    if (!FitInMemory(sizeof(TFT_eSPI))) {
        // Error Message to Connector
        cmdMessenger.sendCmd(kStatus, F("Custom Device does not fit in Memory"));
        return;
    }
    draims_tft = new (allocateMemory(sizeof(TFT_eSPI))) TFT_eSPI();
    _initialised = true;
}

void draims_a320::begin()
{
    if (!_initialised)
        return;

    uint32_t millis_start, millis_end;
    draims_tft->init();
    //draims_tft->initDMA();
    millis_start = millis();
    draims_tft->fillScreen(TFT_BLACK);
    millis_end = millis();
    draims_tft->setRotation(3);

    draims_tft->setTextColor(TFT_WHITE);
    draims_tft->setTextDatum(TC_DATUM); // Centre middle justified
    draims_tft->setFreeFont(&FreeSerifBold24pt7b);
    draims_tft->drawString("First 5inch Display Test!", TFT_HEIGHT / 2, (TFT_WIDTH / 2)  - 24, 1);
    draims_tft->setTextFont(GLCD);     // Select the orginal small GLCD font by using NULL or GLCD
    draims_tft->setTextColor(TFT_YELLOW);
    draims_tft->drawString("running on Raspberry Pico using the second core", TFT_HEIGHT / 2, (TFT_WIDTH / 2) + 30, 1);

    draims_tft->setTextColor(TFT_RED);
    char message[40];                                                    // buffer for message
    sprintf(message, "Erasing display needs: %5d ms", millis_end - millis_start); // create message
    draims_tft->drawString(message, TFT_HEIGHT / 2, (TFT_WIDTH / 2) + 50, 1);

}

void draims_a320::detach()
{
    if (!_initialised)
        return;
    _initialised = false;
}

void draims_a320::set(int16_t messageID, char *setPoint)
{
    /* **********************************************************************************
        Each messageID has it's own value
        check for the messageID and define what to do.
        Important Remark!
        MessageID == -2 will be send from the board when PowerSavingMode is set
            Message will be "0" for leaving and "1" for entering PowerSavingMode
        MessageID == -1 will be send from the connector when Connector stops running
        Put in your code to enter this mode (e.g. clear a display)

    ********************************************************************************** */
    int32_t  data = atoi(setPoint);
    uint16_t output;

    // do something according your messageID
    switch (messageID) {
    case -1:
        // tbd., get's called when Mobiflight shuts down
    case -2:
        // tbd., get's called when PowerSavingMode is entered
    case 0:
        output = (uint16_t)data;
        data   = output;
        break;
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;
    default:
        break;
    }
}

void draims_a320::update()
{
    // Do something which is required regulary
}
