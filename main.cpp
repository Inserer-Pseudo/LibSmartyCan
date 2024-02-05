
#if !DEVICE_CAN

#error [NOT_SUPPORTED] CAN not supported for this target

#endif
 
#include "mbed.h"
 
CAN can1(PA_11, PA_12, 20000);
 
char counter = 0;
 
int main()

{

    CANMessage msg;

    while (1) {

        printf("loop()\n");

        if (can1.read(msg,0)) {

            printf("Message received: %d\n", msg.data[0]);

        }

        ThisThread::sleep_for(200);
 
}

}