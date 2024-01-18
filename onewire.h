#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__
void Delay1(int num);
unsigned char onewire_start();
void onewire_sendbit(unsigned char wei);
unsigned char onewire_receive();
void send_byte(unsigned char zijie);
unsigned char receive_byte();

#endif