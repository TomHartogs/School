#include "MessageQueue.h"
#include <cstdlib> 
#include <stdio.h>
#include <errno.h>
#include <mqueue.h>

mqd_t CreateMessageQueue(std::string queueName)
{
    struct mq_attr attr;

	/* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; 					//******perhaps change??******
    attr.mq_msgsize = MAX_MESSAGE_SIZE;
    attr.mq_curmsgs = 0;
    mode_t mode  = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    
    mqd_t mq = mq_open(queueName.c_str(), O_CREAT | O_RDWR, mode, &attr);
    if(errno == EEXIST)
    {
		DeleteMessageQueue(queueName);
		printf("Deleted old message queue");
		mq = mq_open(queueName.c_str(), O_CREAT | O_RDWR, (S_IRWXU | S_IRWXG | S_IRWXO), &attr);
	}
    else if(mq == -1)
    {
		perror("Creating message queue failed");
		return (mqd_t)NULL;
	}
	printf("Message queue created\n");
	return mq;
}

mqd_t OpenMessageQueue(std::string queueName)
{
    mqd_t mq = mq_open(queueName.c_str(), O_RDWR);
    if(mq == -1)
    {
		perror("Opening message queue failed");
		return (mqd_t)NULL;
	}
	else
	{
		printf("Message queue opened\n");
		return mq;
	}
}

void DeleteMessageQueue(std::string queueName)
{
	printf("Unlinking message queue: ");
	if(mq_unlink(queueName.c_str()) != 0)
		perror("Unlinking message queue failed");
	
}
