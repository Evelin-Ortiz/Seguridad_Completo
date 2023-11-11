#include <xc.h>
#include "Sensor.h"

unsigned char monitoring_sensor(void) {
    // Variables locales para el estado de la alarma y el sensor magnético
    unsigned char alarm_activ = 0;
    unsigned char alarm_mt = 1;

    // Verifica el estado del sensor de infrarrojos (SENSOR_IR)
    if (SENSOR_IR == 0) {
        alarm_activ = 1;  // Activa la alarma si el sensor de infrarrojos está activado
    }

    // Verifica el estado del sensor Hall (SENSOR_HALL)
    if (SENSOR_HALL == 0) {
        alarm_activ = 1;  // Activa la alarma si el sensor Hall está activado
    }

    // Verifica el estado del sensor de metal (SENSOR_METAL)
    if (SENSOR_METAL == 1) {
        alarm_activ = 0;  // Desactiva la alarma si el sensor de metal está activado
    }

    // Retorna el estado de activación de la alarma
    return alarm_activ;
    
    // Este bloque nunca se ejecutará, ya que la función ya ha devuelto un valor
    return alarm_mt;
}

