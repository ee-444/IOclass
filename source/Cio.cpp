// $Id$  

/**  

  * @file Cio.cpp  
  * The source file for class Cio.  This is a class to handle digital input
  * and output pins for Atmel atmega MCU's
  *  
  * @brief This file contains the class member functions for Cio - digital input and output control.  
  *  
  * @author sgrove   
  *
  * @version 1.01   
  *
  */ 

// $Log$ 

#include "Cio.h"

namespace ArduinoLibrary{

Cio::Cio(PinName name, PinType type, BuiltInPullUp pullup)
{
	// setup the PORTA pins (PB_BASE-1)
	if (name < PB_BASE){
		#ifdef PINA
		// register map = PINA -> DDRA -> PORTA
		_base_peripheral_address = PINA;
		// only 8 bit device
		_shift_amt = (name & 0x7);
		#endif
	}
	// setup the PORTB pins (PC_BASE-1)
	else if (name < PC_BASE){
		#ifdef PINB
		// register map = PINB -> DDRB -> PORTB
		_base_peripheral_address = (uint8_t*)&PINB;
		// only 8 bit device
		_shift_amt = (name & 0x7);
		#endif
	}
	// setup the PORTC pins (PD_BASE-1)
	else if (name < PD_BASE){
		#ifdef PINC
		// register map = PINB -> DDRB -> PORTB
		_base_peripheral_address = (uint8_t*)&PINC;
		// only 8 bit device
		_shift_amt = (name & 0x7);
		#endif
	}
	// setup the PORTD pins (Px_BASE-1)
	else if (name < Px_BASE){
		#ifdef PIND
		// register map = PINB -> DDRB -> PORTB
		_base_peripheral_address = (uint8_t*)&PIND;
		// only 8 bit device
		_shift_amt = (name & 0x7);
		#endif
	}
	// set up the pin according to the parameters
	PinState(type);
	// set the pullup if necessary
	PullUp(pullup);
}

Cio::~Cio()
{

}

void Cio::PinState(PinType type)
{
	// change the state to input or output
	*(uint8_t*)(_base_peripheral_address+1) &= ~(type << _shift_amt);
	*(uint8_t*)(_base_peripheral_address+1) |= (type << _shift_amt);
}

void Cio::PullUp(BuiltInPullUp pullup)
{
	// only can be done to input pins (0 = input, 1 = output)
	if ((*(uint8_t*)(_base_peripheral_address+1) & (1 << _shift_amt)) != (1 << _shift_amt)){
		// set the bit of the associated pin
		*(uint8_t*)(_base_peripheral_address+2) &= ~(pullup << _shift_amt);
		*(uint8_t*)(_base_peripheral_address+2) |= (pullup << _shift_amt);	
	}
}

void Cio::SetPin()
{
	// only can be done to output pins (0 = input, 1 = output)
	if((*(uint8_t*)(_base_peripheral_address+1) & (1 << _shift_amt)) == (1 << _shift_amt)){
		// write to the bit location in the register associated with this object
		*(uint8_t*)(_base_peripheral_address+2) |= (1 << _shift_amt);
	} 
}

void Cio::ClrPin()
{
	// only can be done to output pins (0 = input, 1 = output)
	if((*(uint8_t*)(_base_peripheral_address+1) & (1 << _shift_amt)) == (1 << _shift_amt)){
		// write to the bit location in the register associated with this object
		*(uint8_t*)(_base_peripheral_address+2) &= ~(1 << _shift_amt);
	} 
}

uint8_t Cio::Read()
{
	uint8_t result = (*(uint8_t*)(_base_peripheral_address) & (1 << _shift_amt));
	return (result >> _shift_amt);
}

void Cio::Write(uint8_t value)
{
	if (value){
		SetPin();
	}
	else{
		ClrPin();
	}
}

};	// end of namespace
