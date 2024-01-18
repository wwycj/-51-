#include <STC89C5xRC.H>
#include "onewire.h"

	
#define DS18B20_SKIP_ROM			0xCC
#define DS18B20_CONVERT_T			0x44
#define DS18B20_READ_SCRATCHPAD 	0xBE

//void temp_convert()
//{
//	onewire_start();
//	send_byte(DS18B20_SKIP_ROM);
//	send_byte(DS18B20_CONVERT_T);
//}

float Readtemp_convert()
{
	unsigned char TMSB,TLSB;
	int temp;
	float temperture;
	onewire_start();
	send_byte(DS18B20_SKIP_ROM);
	send_byte(DS18B20_CONVERT_T);

	onewire_start();
	send_byte(DS18B20_SKIP_ROM);
	send_byte(DS18B20_READ_SCRATCHPAD);
	TLSB=receive_byte();
	TMSB=receive_byte();
	temp=(TMSB<<8)|TLSB;
	temperture=temp/16.0;
	return temperture;

}
	
	