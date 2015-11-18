#ifndef _PERFORM_TASKS_H
#define _PERFORM_TASKS_H

#include "message.h"
#include "action_enum.h"
#include "LPA_Lib_ballon.h"
#include "RP6ControlLib.h"

void performTasks(MESSAGE* _message);
void cleanMessage(MESSAGE* _message);

#endif
