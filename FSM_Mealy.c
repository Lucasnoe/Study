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

void main(){
    printf("Finite State Machine Mealy\n");
    printf("Light Control Application\n");
    printf("----------------------------\n");
    


while(1){
    char buff;
    event_t event;
    printf("Send 'x' or 'o'\n");
    scanf("%c", &buff);
    if(buff == 'o'){
        event = ON;
        light_state_machine(event);
    }
    else if(buff == 'x'){
        event = OFF;
        light_state_machine(event);
    }

}
}

void light_state_machine(uint8_t event)
{
    switch(current_state)
    {
        case LIGHT_OFF:{

            switch(event){
                case ON:{
                    change_Light(Pin_Light,LOW_LIGHT);
                    printf("Evento ON ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_DIM;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
                case OFF:{
                    change_Light(Pin_Light,OFF_LIGHT);
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
                    change_Light(Pin_Light,MEDIUM_LIGHT);
                    printf("Evento ON ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_MEDIUM;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
                case OFF:{
                    change_Light(Pin_Light,OFF_LIGHT);
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
                    change_Light(Pin_Light,FULL_LIGHT);
                    printf("Evento ON ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_FULL;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
                case OFF:{
                    change_Light(Pin_Light,OFF_LIGHT);
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
                    change_Light(Pin_Light,LIGHT_DIM);
                    printf("Evento ON ocorrido\n");
                    printf("Esatdo anterior: \n");
                    printf("%i\n",current_state);
                    current_state = LIGHT_DIM;
                    printf("Estado atual: \n");
                    printf("%i\n",current_state);
                    break;
                }
                case OFF:{
                    change_Light(Pin_Light,OFF_LIGHT);
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
}

void change_Light(uint8_t Pin, uint8_t intensity){
    printf("Intensidade do PWM");
    printf("%i\n",intensity);
}

