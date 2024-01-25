# Projet CANSmartyCoffre

Voici un exemple d'implémentation de la classe CANSmartyCoffre dans un programme mbed.:

```cpp
#if !DEVICE_CAN
#error [NOT_SUPPORTED] CAN not supported for this target
#endif

#include "mbed.h"

#include "CANSmartyCoffre.hpp"

CAN can1(MBED_CONF_APP_CAN1_RD, MBED_CONF_APP_CAN1_TD,120);

int main()
{
    // Constructeur prend l'objet CAN et l'identifiant du noeud (int) exemple 5 pour empreinte
    CANSmartyCoffre noeud(can1,1);

    noeud.StartPinging();

    while (1) {
        
        if (detection > seuil_min) {
            noeud.SendDetectionSignal();
        }

        if (deverouillage_OK){
            noeud.SendDisarmedSignal();
        }
    }
}
```