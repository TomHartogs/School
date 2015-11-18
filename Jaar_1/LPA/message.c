#include "message.h" 

#define MIN_REQUEST_SIZE	5
#define MAX_REQUEST_SIZE	8
#define BEGIN_MARK '{'
#define END_MARK '}'

int Read(MESSAGE* _message)
{	
	char request_buffer[MAX_REQUEST_SIZE];
	int buffer_pos = 0;
	if(getBufferLength() > MIN_REQUEST_SIZE)
	{
		request_buffer[buffer_pos] = readChar();	
		if(request_buffer[buffer_pos] == BEGIN_MARK)
        {
			writeChar(request_buffer[buffer_pos]);
			buffer_pos++;
			request_buffer[buffer_pos] = readChar();
			if(request_buffer[buffer_pos] == BEGIN_MARK);
			{
				writeChar(request_buffer[buffer_pos]);
				while(request_buffer[buffer_pos - 1] != END_MARK && 
				      buffer_pos <= (MAX_REQUEST_SIZE - 1))
				{
					buffer_pos++;
					request_buffer[buffer_pos] = readChar();
					writeChar(request_buffer[buffer_pos]);
				}
				if(request_buffer[0] == BEGIN_MARK &&
				   request_buffer[1] == BEGIN_MARK &&
				   request_buffer[buffer_pos] == END_MARK &&
				   request_buffer[buffer_pos - 1] == END_MARK)
				{
					_message->action = request_buffer[2];
					
					int data = 0;
					if(buffer_pos == 7 &&
					   _message->action == SET_HEIGHT)
					{
						data = (request_buffer[3] - '0') * 100;
						data += (request_buffer[4] - '0') * 10;
						data += request_buffer[5] - '0';
						_message->data = data;
						writeChar('\n');
						writeChar(_message->action);
						writeInteger(data, DEC);
						return 1;
					}
					else if(buffer_pos == (MIN_REQUEST_SIZE - 1) && _message->action != SET_HEIGHT)
					{
						writeChar('\n');
						writeChar(_message->action);
						return 1;	
					}
					return 0;
				}	
			}
		}
		buffer_pos = 0;
	}
	return 0;
}

//--------------------Write-the-message-through-I2C---------------------
void Write(MESSAGE _message)
{
	writeChar(BEGIN_MARK);
	writeChar(BEGIN_MARK);
	writeChar(_message.action);
	if(_message.action == GET_HEIGHT)
	{
		writeInteger(_message.data, DEC);
	}
	writeChar(END_MARK);
	writeChar(END_MARK);
}
