#ifndef _BXI_PCI_DRV_H
#define _BXI_PCI_DRV_H

#define CAN_MAX_DLC     8

typedef struct
{
    unsigned int can_id;
    unsigned int can_dlc;
    unsigned char data[CAN_MAX_DLC];
}can_frame  __attribute__((__aligned__(1)));

typedef struct
{
    unsigned int bus;
    can_frame frame;
}can_packet __attribute__((__aligned__(1)));

typedef int (*can_rx_call)(unsigned bus, void *arg, can_frame *msg);

int bxi_pci_init(can_rx_call func, void *arg, int cpu);
int can_send_pack(can_packet *pack, unsigned int num);
int bxi_pci_exit();

int motor_pwr_set(unsigned int pwr);
int motor_pwr_get();
int fan_pwr_set(unsigned int pwr);
int led_rgb_set(unsigned int rgb);

#endif