#if !DEVICE_CAN
#error [NOT_SUPPORTED] CAN not supported for this target
#endif

#include "mbed.h"

#include "CANSmartyCoffre.hpp"

CAN can1(MBED_CONF_APP_CAN1_RD, MBED_CONF_APP_CAN1_TD,20000);

int main()
{
    // Constructeur prend l'objet CAN et l'identifiant du noeud (int) exemple 5 pour empreinte
    CANSmartyCoffre noeud(can1,2);

    noeud.StartPinging();

    while (1) {
        
         if (true) {
             noeud.SendDetectionSignal();
        }

        // if (true){
        //     noeud.SendDisarmedSignal();
        // }

        ThisThread::sleep_for(2s);
    }
}