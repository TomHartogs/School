#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "RP6uart.h"
#include <stdbool.h>
#include <stdio.h>
#include "action_enum.h"

typedef struct
{
    char 	action;
    int 	data;
} MESSAGE;


int Read(MESSAGE* _message);
void Write(MESSAGE _message);

#endif
