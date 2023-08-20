#include <stdint.h>

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

void light_state_machine(int event);
void change_Light(int Pin, int intensity);

void setup(){
    Serial.begin(115200);
    Serial.println("Finite State Machine Mealy");
    Serial.println("Light Control Application");
    Serial.println("----------------------------");
    Serial.println("Send 'x' or 'o'");
    pinMode(Pin_Light,OUTPUT);
}

void loop(){
    char buff;
    event_t event;
    if(Serial.available()>0){
        buff = Serial.read();
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

void light_state_machine(int event)
{
    switch(current_state)
    {
        case LIGHT_OFF:{

            switch(event){
                case ON:{
                    change_Light(Pin_Light,LOW_LIGHT);
                    Serial.println("Evento ON ocorrido");
                    Serial.println("Esatdo antererior: ");
                    Serial.println(current_state);
                    current_state = LIGHT_DIM;
                    Serial.println("Estado atual: ");
                    Serial.println(current_state);
                    break;
                }
                case OFF:{
                    change_Light(Pin_Light,OFF_LIGHT);
                    Serial.println("Evento OFF ocorrido");
                    Serial.println("Esatdo antererior: ");
                    Serial.println(current_state);
                    current_state = LIGHT_OFF;
                    Serial.println("Estado atual: ");
                    Serial.println(current_state);
                    break;
                }
            }

            break;
        }

        case LIGHT_DIM:{

             switch(event){
                case ON:{
                    change_Light(Pin_Light,MEDIUM_LIGHT);
                    Serial.println("Evento ON ocorrido");
                    Serial.println("Esatdo antererior: ");
                    Serial.println(current_state);
                    current_state = LIGHT_MEDIUM;
                    Serial.println("Estado atual: ");
                    Serial.println(current_state);
                    break;
                }
                case OFF:{
                    change_Light(Pin_Light,OFF_LIGHT);
                    Serial.println("Evento OFF ocorrido");
                    Serial.println("Esatdo antererior: ");
                    Serial.println(current_state);
                    current_state = LIGHT_OFF;
                    Serial.println("Estado atual: ");
                    Serial.println(current_state);
                    break;
                }
            }
            break;
        }

        case LIGHT_MEDIUM:{

            switch(event){
                case ON:{
                    change_Light(Pin_Light,FULL_LIGHT);
                    Serial.println("Evento ON ocorrido");
                    Serial.println("Esatdo antererior: ");
                    Serial.println(current_state);
                    current_state = LIGHT_FULL;
                    Serial.println("Estado atual: ");
                    Serial.println(current_state);
                    break;
                }
                case OFF:{
                    change_Light(Pin_Light,OFF_LIGHT);
                    Serial.println("Evento OFF ocorrido");
                    Serial.println("Esatdo antererior: ");
                    Serial.println(current_state);
                    current_state = LIGHT_OFF;
                    Serial.println("Estado atual: ");
                    Serial.println(current_state);
                    break;
                }
            }
            break;
        }
        
        case LIGHT_FULL:{

            switch(event){
                case ON:{
                    change_Light(Pin_Light,LIGHT_DIM);
                    Serial.println("Evento ON ocorrido");
                    Serial.println("Esatdo antererior: ");
                    Serial.println(current_state);
                    current_state = LIGHT_DIM;
                    Serial.println("Estado atual: ");
                    Serial.println(current_state);
                    break;
                }
                case OFF:{
                    change_Light(Pin_Light,OFF_LIGHT);
                    Serial.println("Evento OFF ocorrido");
                    Serial.println("Esatdo antererior: ");
                    Serial.println(current_state);
                    current_state = LIGHT_OFF;
                    Serial.println("Estado atual: ");
                    Serial.println(current_state);
                    break;
                }
            }
            break;
        }
    }
}

void change_Light(int Pin, int intensity){
    analogWrite(Pin, intensity);
}