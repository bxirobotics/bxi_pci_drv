#ifndef _BXI_PCI_DRV_H
#define _BXI_PCI_DRV_H

#include <linux/can.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define CANFD_DEVICE_NUM 5

typedef struct
{
    unsigned int bus;
    struct canfd_frame frame;
}canfd_packet __attribute__((__aligned__(8)));

typedef int (*canfd_rx_call)(void *arg, canfd_packet *msg);
typedef int (*canfd_event_call)(void *arg, int event); //TODO:event call(e.g.:tx failed)

/**
 * @brief bxi_pci_init
 * 
 * @param func canfd recv call func
 * @param arg user args
 * @param cpu [0...ncores], CPU affinity settings for the CANFD receiver function, -1 disable
 * @return -1 failed
 */
int bxi_pci_init(canfd_rx_call func, void *arg, int cpu);
int canfd_send_packet(canfd_packet *packet, unsigned int num);
int bxi_pci_exit();

#define LED_R (1<<0)
#define LED_G (1<<1)
#define LED_B (1<<2)

int motor_pwr_set(unsigned int pwr);
int motor_pwr_get();
int fan_pwr_set(unsigned int pwr);
int led_rgb_set(unsigned int rgb);

#ifdef __cplusplus
}
#endif

#endif