#include "L2Controller.h"

L2State L2Controller::currentState = AWAKE;

L2Controller::L2Controller()
{

}

void L2Controller::processACTIVEMAIN()
{
    // Transition Logic
    switch(currentState)
    {
        case AWAKE:
            break;

        case SLEEP:
            break;

        case DEEPSLEEP
            break;
    }

    // Output Logic
    switch(currentState)
    {
        case AWAKE:
            break;

        case SLEEP:
            break;

        case DEEPSLEEP
            break;
    }
}

void L2Controller::processACTIVEPCINT0()
{
    // In this case, unique behavior for any L2 state
}

void L2Controller::processACTIVETMR0OVF()
{
    // In this case, unique behavior for any L2 state
}


void L2Controller::processINACTIVEMAIN()
{
    // Transition Logic
    switch(currentState)
    {
        case AWAKE:
            break;

        case SLEEP:
            break;

        case DEEPSLEEP
            break;
    }

    // Output Logic
    switch(currentState)
    {
        case AWAKE:
            break;

        case SLEEP:
            break;

        case DEEPSLEEP
            break;
    }
}

void L2Controller::processINACTIVEPCINT0()
{
    // In this case, unique behavior for any L2 state
}

void L2Controller::processINACTIVETMR0OVF()
{
    // In this case, unique behavior for any L2 state
}
