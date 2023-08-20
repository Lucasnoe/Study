#include "Parser.h"
#include "MK20DX256.h"

#ifndef NULL
#define NULL 0
#endif

#ifndef TEST
#define STATIC static
#else
#define STATIC
#endif

#define PARSER_BUFFER_LENGTH_MAX (23)

static char buffer[PARSER_BUFFER_LENGTH_MAX];

STATIC PARSER_STATE_T state = PARSER_LOOKING_FOR_START;

static int len;

char* Parser_AddChar(char NewChar)
{
    if(NewChar == '[')
    {
        state = PARSER_LOOKING_FOR_CMD;
        buffer[0] = NewChar;
        return 0;
    }

    if((NewChar == ']') && (state == PARSER_LOOKING_FOR_END)){
        state = PARSER_LOOKING_FOR_START;
        buffer[3] = NewChar;
        buffer[4] = 0;
        return buffer;
    }

    switch(state){

        case PARSER_LOOKING_FOR_CMD:
        {
            if((NewChar >= 'A')&&(NewChar<='Z'))
            {
                state = PARSER_LOOKING_FOR_LEN;
                buffer[1] = NewChar;
            }
            else
            {
                state = PARSER_LOOKING_FOR_START;
            }
            break;
            
        }
        case PARSER_LOOKING_FOR_LEN:
        {
            if((NewChar>'0')&&((NewChar)<='9'))
            {
                state = PARSER_LOOKING_FOR_DATA;
                buffer[2] = NewChar;
                
                len = (int)NewChar;
            }

            else if (NewChar == 0)
            {
                state = PARSER_LOOKING_FOR_END;
                buffer[2] = NewChar;
            }

            else if(NewChar == '[')
            {
                state = PARSER_LOOKING_FOR_CMD;
            }

            else{
                state = PARSER_LOOKING_FOR_START;
            } 
            break;
        }

        case(PARSER_LOOKING_FOR_DATA)
        {
            if ()
        }

        default: break;
    }
    return 0;
}
