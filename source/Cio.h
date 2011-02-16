//
// 	Author: 	sgrove
//	Target: 	Arduino (328p for now)
// 	Project:	EE-444
//

#ifndef CIO_H
#define CIO_H

#include "ArduinoLib.h"

// Memory locations for this peripheral class: assumes that the peripheral map is 
//	PINx
//  DDx
//  PORTx
//#define PINB *(volatile uint8_t *)0x23
//#define PINC *(volatile uint8_t *)0x26
//#define PIND *(volatile uint8_t *)0x29

// namespace used for Library variables and privacy
namespace ArduinoLibrary{

// declaration of the class
class Cio{

private:
	// base address for the peripheral associated registers
	volatile uint8_t* _base_peripheral_address;
	// the amount of shifting to get to the pins bit location
	uint8_t _shift_amt;
	void Write(uint8_t);

public:
	// constructor for the object
	Cio(PinName, PinType, BuiltInPullUp = PULLUP_DISABLE);
	void PinState(PinType);
	void PullUp(BuiltInPullUp);
	void SetPin();
	void ClrPin();
	uint8_t Read();
	// operator overloading for easy coding :-)
	//  = as in write to the objest
	Cio& operator= (uint8_t value){ 
		Write(value); 
		return *this; 
	}
	//  = as in equals another object of the same type
	Cio& operator= (Cio& rhs){
		Write(rhs.Read()); 
		return *this; 
	}
	//  = as in read contents to a variable
	operator uint8_t(){
		return Read(); 
	}
};	// end of class

};	// end of namespace

#endif
