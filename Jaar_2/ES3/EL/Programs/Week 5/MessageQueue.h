#pragma once

#include <mqueue.h>
#include <string>

#define MAX_MESSAGE_SIZE 	2000
#define MAX_NAME_SIZE		100

void Unlink();

mqd_t CreateMessageQueue(std::string);

mqd_t OpenMessageQueue(std::string);

void DeleteMessageQueue(std::string);
