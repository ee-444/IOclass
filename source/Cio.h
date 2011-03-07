// $Id$  

/**  

  * @file Cio.h  
  * The header file for class Cio.  This is a class to handle digital input
  * and output pins for Atmel atmega MCU's
  *  
  * @brief This file contains the class definition for Cio - digital input and output control.  
  *  
  * @author sgrove   
  *
  * @version 1.01   
  *
  */ 

// $Log$ 

#ifndef CIO_H
#define CIO_H

#include "ArduinoLib.h"

//! scope for peripheral driver software
namespace ArduinoLibrary{

//! Digital Input and Output class definition
class Cio{

private:
	// stored base address for object relating it to the proper
	// peripheral associated registers
	volatile uint8_t* _base_peripheral_address;
	// the amount of shifting to get to the pins bit location
	uint8_t _shift_amt;
	// Write operation only used by the overloaded operators 
	void write(uint8_t);

public:
 	
	/**  
    	This is the default constructor for the Cio class.  It builds the object as an output or input.

    	@param[in]  name - An enumerated member of PinName.  This is the MCU pin that will be
							tied to the specific object  
    	@param[in]  type - An enumerated member of PinType.  This will make the object an 
							input or output.  This can later be changed in the program
    	@param[in] 	pullup - An enumerated member of BuildInPullUp.  If the pin is an 
								input the internal pullup can be enabled.  It is always 
								disabled for outputs.

  	*/ 
	Cio(PinName name, PinType type, BuiltInPullUp pullup = PULLUP_DISABLE);

	/**  
    	This is the default deconstructor for the Cio class.
  	*/ 
	~Cio();
 	
	/**  
    	Used to change a pin from input to output or output to input 

    	@param[in]  type - An enumerated member of PinType.  This will make the object an 
							input or output.  This can later be changed in the program

  	*/ 
	void pinState(PinType type);
	
	/**  
    	Used to enable or disable the internal pullup resistor on an input pin (INPUT PIN ONLY).
		Has no functionallity if the object is an output

    	@param[in] 	pullup - An enumerated member of BuildInPullUp.  If the pin is an 
								input the internal pullup can be enabled.  It is always 
								disabled for outputs

  	*/ 
	void pullUp(BuiltInPullUp pullup);

	/**  
    	Used to make the output of an output pin a logic 1 (OUTPUT PIN ONLY).  Has no functionallity
		if the object is an input
  	*/
	void setPin();

	/**  
    	Used to make the output of an output pin a logic 0 (OUTPUT PIN ONLY).  Has no functionallity
		if the object is an input
  	*/
	void clrPin();

	/**  
    	Used to read the logic level of a digital input or output pin

		@return		The logic level pf the pin ( 1 or 0 )

  	*/
	uint8_t read();

	/**  
    	Overloaded overator for "=".  Changes only occur if the object is an OUTPUT.
		Used for shorthand notation while coding.
  	*/
	Cio& operator= (uint8_t in){ 
		write(in); 
		return *this; 
	}

	/**  
    	Overloaded overator for "=".  This allows the logic level of one object to be assigned
		to another object of the same type.  The object that is being assigned a value must be an
		output or no change will occur while the value of the object that is the operand can be an
		input or an output.
  	*/
	Cio& operator= (Cio& rhs){
		write(rhs.read()); 
		return *this; 
	}

	/**  
    	Overloaded overator for "=".  This variant is used to read the state on an input
		or output into a variable of any type.
  	*/
	operator uint8_t(){
		return read(); 
	}
};

};	// end of namespace

#endif
