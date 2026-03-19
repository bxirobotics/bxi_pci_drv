#include <stdio.h>
#include <unistd.h>

#include "bxi_pci_drv.h"

int can_rx_call_test(void *arg, canfd_packet *msg){
    printf("can[%d] recv, id:%d, dlc:%d, data:", msg->bus, msg->frame.can_id, msg->frame.len);

    // for (size_t i = 0; i < msg->can_dlc; i++){
    //     printf("0x%x ", msg->data[i]);
    // }
    printf("\n");

    return 0;
}

int main(){

    if (-1 == bxi_pci_init(can_rx_call_test, NULL, -1)){
        return -1;
    }

    //RGB test
    led_rgb_set(LED_R);
    printf("led red on\n");
    sleep(1);
    led_rgb_set(LED_G);
    printf("led green on\n");
    sleep(1);
    led_rgb_set(LED_B);
    printf("led blue on\n");
    sleep(1);
    led_rgb_set(LED_R|LED_G|LED_B);
    printf("led rgb on\n");
    sleep(1);
    led_rgb_set(0);
    printf("led off\n");
    sleep(1);
    
    //FAN test
    fan_pwr_set(1);
    printf("fan power on\n");
    sleep(1);
    fan_pwr_set(0);
    printf("fan power off\n");
    sleep(1);

    //motor test
    motor_pwr_set(1);
    printf("motor power on\n");
    sleep(1); //wait for soft start

    //remote emergency stop test
    for (size_t i = 10; i > 0; i--)
    {
        printf("Please press the remote emergency stop, wait %ld s.\n", i);
        if (0 == motor_pwr_get())
        {
            printf("successful\n");
            break;
        }
        sleep(1);
    }
    
    motor_pwr_set(0);
    printf("motor power off\n");

    //connect can0 to canXX
    //can test
    for (size_t i = 0; i < 1000; i++)
    {
        #define MSG_NUM 5
        canfd_packet msg[MSG_NUM];
        for (size_t i = 0; i < MSG_NUM; i++){
            msg[i].bus = 0;
            msg[i].frame.can_id = i;
            msg[i].frame.len = 8;
            for (size_t j = 0; j < 8; j++){
                msg[i].frame.data[j] = j;
            }
        }
        canfd_send_packet(msg, MSG_NUM);
        sleep(1);
    }
    
    bxi_pci_exit();

    return 0;
}