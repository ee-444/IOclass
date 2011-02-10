// 
// Test implementation file
//

#include "main.h"

Cio pin1 (PIN_PB5, PINTYPE_OUTPUT);

int main (void)
{
	uint8_t tmp = 0xff;
	pin1 = 1;
	tmp = pin1;
	pin1 = 0;
	tmp = pin1;
	while(1){
		for(uint32_t i=0; i<80000; i++);
		if (pin1 == 1)
			pin1 = 0;
		else
			pin1 = 1;
	}
}
	
