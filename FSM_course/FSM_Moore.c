#include <stdint.h>
#include <stdio.h>

typedef enum{
    ON,
    OFF
}event_t;

typedef enum{
    LIGHT_OFF,
    LIGHT_DIM,
    LIGHT_MEDIUM,
    LIGHT_FULL
}light_state_t;

#define OFF_LIGHT 0
#define LOW_LIGHT 63
#define MEDIUM_LIGHT 127
#define FULL_LIGHT 255
#define Pin_Light 9

light_state_t current_state = LIGHT_OFF;

void light_state_machine(uint8_t event);
void change_Light(uint8_t Pin, uint8_t intensity);
void run_entry_action(light_state_t state);

void main(){
    printf("Finite State Machine Moore\n");
    printf("Light Control Application\n");
    printf("----------------------------\n");
    


    while(1){
        char buff;
        event_t event;
        printf("Send 'x' or 'o'\n");
        scanf("%c", &buff);
        if(buff == 'o')
        {
            event = ON;
            light_state_machine(event);
        }
        else if(buff == 'x')
        {
            event = OFF;
            light_state_machine(event);
        }

    }
}

void light_state_machine(uint8_t event)
{
    light_state_t prev_state;

    switch(current_state)
    {
        case LIGHT_OFF:{

            switch(event){
                case ON:{
                    
                    printf("Evento ON ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_DIM;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
                case OFF:{
                    
                    printf("Evento OFF ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_OFF;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
            }

            break;
        }

        case LIGHT_DIM:{

             switch(event){
                case ON:{
                    
                    printf("Evento ON ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_MEDIUM;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
                case OFF:{
                    
                    printf("Evento OFF ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_OFF;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
            }
            break;
        }

        case LIGHT_MEDIUM:{

            switch(event){
                case ON:{
                    
                    printf("Evento ON ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_FULL;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
                case OFF:{
                    
                    printf("Evento OFF ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_OFF;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
            }
            break;
        }
        
        case LIGHT_FULL:{

            switch(event){
                case ON:{
                    
                    printf("Evento ON ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_DIM;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
                case OFF:{
                    printf("Evento OFF ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_OFF;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
            }
            break;
        }
    }

    if(current_state!=prev_state){
        run_entry_action(current_state);
    }
}

void Light_changeIntensity(uint8_t Pin, uint8_t intensity){
    printf("Intensidade do PWM");
    printf("%i\n",intensity);
}

void run_entry_action(light_state_t state)
{
    switch(state){
        case LIGHT_OFF:{
            Light_changeIntensity(Pin_Light, OFF_LIGHT);
            break;
        }

        case LIGHT_DIM:{
            Light_changeIntensity(Pin_Light, LOW_LIGHT);
            break;
        }

        case LIGHT_MEDIUM:{
            Light_changeIntensity(Pin_Light, MEDIUM_LIGHT);
            break;
        }

        case LIGHT_FULL:{
            Light_changeIntensity(Pin_Light, FULL_LIGHT);
            break;
        }
    }
}