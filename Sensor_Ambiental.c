#include <xc.h>
#include "Sensor.h"

unsigned char monitoring_sensor_Ambiental(void){
    unsigned char alarm_activ=0;
    if(Temperatura==0){
        alarm_activ=1;
    }
    if(SENSOR_HALL==1){
        alarm_activ=1;
    }
    if(SENSOR_METAL==1){
        alarm_activ=1;
    }   
    return alarm_activ;
}
