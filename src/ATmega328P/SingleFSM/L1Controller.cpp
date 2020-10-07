#include "L1Controller.h"

L1State L1Controller::currentState = AWAKE;

L1Controller::L1Controller()
{

}

void L1Controller::processMAIN()
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

void L1Controller::processPCINT0()
{
    // In this case, unique behavior for any L1 state because it's been used as a peripheral device to FSM task 
}

void L1Controller::processTMR0OVF()
{
    // In this case, unique behavior for any L1 state because it's been used as a peripheral device to FSM task
}
