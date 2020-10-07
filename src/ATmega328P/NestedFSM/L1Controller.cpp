#include "L1Controller.h"

L1State L1Controller::currentState = ACTIVE;

L1Controller::L1Controller()
{

}

void L1Controller::processMAIN()
{
    // Transition Logic
    switch(currentState)
    {
        case ACTIVE:
            break;

        case INACTIVE:
            break;
    }

    // Output Logic
    switch(currentState)
    {
        case ACTIVE:
            L2Controller::processACTIVEMAIN();
            break;

        case INACTIVE:
            L2Controller::processINACTIVEMAIN();
            break;
    }
}

void L1Controller::processPCINT0()
{
    // Transition Logic
    switch(currentState)
    {
        case ACTIVE:
            break;

        case INACTIVE:
            break;
    }

    // Output Logic
    switch(currentState)
    {
        case ACTIVE:
            L2Controller::processACTIVEPCINT0();
            break;

        case INACTIVE:
            L2Controller::processINACTIVEPCINT0();
            break;
    }
}

void L1Controller::processTMR0OVF()
{
    // Transition Logic
    switch(currentState)
    {
        case ACTIVE:
            break;

        case INACTIVE:
            break;
    }

    // Output Logic
    switch(currentState)
    {
        case ACTIVE:
            L2Controller::processACTIVETMR0OVF();
            break;

        case INACTIVE:
            L2Controller::processINACTIVETMR0OVF();
            break;
    }
}
