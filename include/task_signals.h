#ifndef TASK_SIGNALS_H_
#define TASK_SIGNALS_H_

#include "SignalOutput.h"

struct signalSetting
{
    byte id;
    byte status;
};

void TaskSignals(void *pvParameters);

#endif
