#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>

#include "bxi_pci_drv.h"

uint64_t timebase64_get(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000ULL + (uint64_t)tv.tv_usec;
}

uint64_t timebase64_diff_us(uint64_t timeBase)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((uint64_t)tv.tv_sec * 1000000ULL + (uint64_t)tv.tv_usec) - timeBase;
}

uint64_t time_send = 0;

int can_rx_call_test(void *arg, canfd_packet *msg){
    // printf("can[%d] recv, id:%d, dlc:%d, data:", msg->bus, msg->frame.can_id, msg->frame.len);

    if (msg->frame.can_id == 0x11) //motor reply id
    {
        printf("time diff:%ld us\n", timebase64_diff_us(time_send));
    }
    

    return 0;
}

int main(){

    if (-1 == bxi_pci_init(can_rx_call_test, NULL, -1)){
        return -1;
    }

    //motor test
    motor_pwr_set(1);
    printf("motor power on\n");
    sleep(2); //wait for soft start

    //can test
    for (size_t i = 0; i < 10; i++)
    {
        #define MSG_NUM 1
        canfd_packet msg[MSG_NUM];

        //send to bus 0, id 1
        msg[0].bus = 0;
        msg[0].frame.can_id = 1;
        msg[0].frame.len = 8;

        //MIT protocol: exit motor mode
        msg[0].frame.data[0] = 0xFF;
        msg[0].frame.data[1] = 0xFF;
        msg[0].frame.data[2] = 0xFF;
        msg[0].frame.data[3] = 0xFF;
        msg[0].frame.data[4] = 0xFF;
        msg[0].frame.data[5] = 0xFF;
        msg[0].frame.data[6] = 0xFF;
        msg[0].frame.data[7] = 0xFD;

        printf("send msg\n");
        time_send = timebase64_get();

        canfd_send_packet(msg, 1);
        sleep(1);
    }
    
    motor_pwr_set(0);
    printf("motor power off\n");

    bxi_pci_exit();

    return 0;
}