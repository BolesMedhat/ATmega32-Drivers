/****************************************************************************
 * @file    I2C_def.h
 * @author  Boles Medhat
 * @brief   I2C (TWI) Driver Definitions Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-08-06]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all the necessary register definitions, bit positions,
 * status codes, and mode macros required for configuring and interacting
 * with the I2C (TWI) module on the ATmega32 microcontroller.
 *
 * These definitions are intended to be used by the `I2C` driver and other
 * components that require interaction with the I2C (TWI) module.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef I2C_DEF_H_
#define I2C_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*---------------------------------------    Registers    ---------------------------------------*/

/*I2C Address Register*/
#define TWAR								*((volatile uint8 *)0x22)	/*TWI (Slave) Address Register*/

/*I2C Data Register*/
#define TWDR								*((volatile uint8 *)0x23)	/*TWI Data Register*/

/*I2C Control Registers*/
#define TWBR								*((volatile uint8 *)0x20)	/*TWI Bit Rate Register*/
#define TWCR								*((volatile uint8 *)0x56)	/*TWI Control Register*/
#define TWSR								*((volatile uint8 *)0x21)	/*TWI Status Register*/

/*Global Interrupt Register*/
#define SREG								*((volatile uint8 *)0x5F)	/*status register*/

/*I2C Pins Data Register*/
#define PORTC								*((volatile uint8 *)0x35)	/*Port C Data Register (for SDA, SCL pins)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*TWAR Register*/
#define TWGCE								0	/*TWI General Call Recognition Enable Bit*/

/*TWCR Register*/
#define TWIE								0	/*TWI Interrupt Enable*/
#define TWEN								2	/*TWI Enable Bit*/
#define TWWC								3	/*TWI Write Collision Flag*/
#define TWSTO								4	/*TWI STOP Condition Bit*/
#define TWSTA								5	/*TWI START Condition Bit*/
#define TWEA								6	/*TWI Enable Acknowledge Bit*/
#define TWINT								7	/*TWI Interrupt Flag*/

/*TWSR Register*/
#define TWPS0								0	/*TWI Prescaler Bit 0*/
#define TWPS1								1	/*TWI Prescaler Bit 1*/

/*SREG Register*/
#define	I									7	/*Global Interrupt Enable*/

/*PORTC Register*/
#define SCL_PIN								0	/*Two-wire Serial Bus Clock Line pin from pinout*/
#define SDA_PIN								1	/*Two-wire Serial Bus Data Input/Output Line pin from pinout*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*I2C operations*/
#define I2C_WRITE							0		/*Write operation: Master sends data to the slave*/
#define I2C_READ							1		/*Read operation: Master receives data from the slave*/

/*I2C Status Code*/

/*Master Transmitter/Receiver Mode*/
#define I2C_START_TRANSMITTED_SC            0x08    /*Status Code $08: A START condition has been transmitted successfully*/
#define I2C_REPEATED_START_SC               0x10    /*Status Code $10: A repeated START condition has been transmitted successfully*/
#define I2C_ARBITRATION_LOST_SC             0x38    /*Status Code $38: Arbitration lost in SLA+R/W or data bytes*/

/*Master Transmitter Mode*/
#define I2C_SLAW_ACK_SC                     0x18    /*Status Code $18: SLA+W has been transmitted, ACK received*/
#define I2C_SLAW_NACK_SC                    0x20    /*Status Code $20: SLA+W has been transmitted, NACK received*/
#define I2C_DATA_TRANSMITTED_ACK_SC         0x28    /*Status Code $28: Data byte has been transmitted, ACK received*/
#define I2C_DATA_TRANSMITTED_NACK_SC        0x30    /*Status Code $30: Data byte has been transmitted, NACK received*/

/*Master Receiver Mode*/
#define I2C_SLAR_ACK_SC                     0x40    /*Status Code $40: SLA+R has been transmitted, ACK received*/
#define I2C_SLAR_NACK_SC                    0x48    /*Status Code $48: SLA+R has been transmitted, NACK received*/
#define I2C_DATA_RECEIVED_ACK_SC            0x50    /*Status Code $50: Data byte has been received, ACK transmitted*/
#define I2C_DATA_RECEIVED_NACK_SC           0x58    /*Status Code $58: Data byte has been received, NACK transmitted*/

/*Slave Receiver Mode*/
#define I2C_SLA_W_RECEIVED_SC               0x60    /*Status Code $60: SLA+W has been received, ACK transmitted*/
#define I2C_ARBITRATION_LOST_SLA_W_SC       0x68    /*Status Code $68: Arbitration lost in SLA+R/W, SLA+W received, ACK transmitted*/
#define I2C_GENERAL_CALL_ACK_SC             0x70    /*Status Code $70: General call address has been received, ACK transmitted*/
#define I2C_ARBITRATION_LOST_GCALL_ACK_SC   0x78    /*Status Code $78: Arbitration lost in SLA+R/W, general call received, ACK transmitted*/
#define I2C_PREVIOUS_ACK_SC                 0x80    /*Status Code $80: Previously addressed with own SLA+W; data received, ACK transmitted*/
#define I2C_PREVIOUS_NACK_SC                0x88    /*Status Code $88: Previously addressed with own SLA+W; data received, NACK transmitted*/
#define I2C_GENERAL_CALL_DATA_ACK_SC        0x90    /*Status Code $90: General call address received, data received, ACK transmitted*/
#define I2C_GENERAL_CALL_DATA_NACK_SC       0x98    /*Status Code $98: General call address received, data received, NACK transmitted*/
#define I2C_STOP_OR_REPEATED_START_SC       0xA0    /*Status Code $A0: A STOP condition or repeated START condition has been received while still addressed as a slave*/

/*Slave Transmitter Mode*/
#define I2C_SLA_R_RECEIVED_SC               0xA8    /*Status Code $A8: Own SLA+R has been received, ACK transmitted*/
#define I2C_ARBITRATION_LOST_SLA_R_SC       0xB0    /*Status Code $B0: Arbitration lost in SLA+R/W, SLA+R received, ACK transmitted*/
#define I2C_DATA_TRANSMITTED_ACK_SLAVE_SC   0xB8    /*Status Code $B8: Data byte has been transmitted, ACK received (slave)*/
#define I2C_DATA_TRANSMITTED_NACK_SLAVE_SC  0xC0    /*Status Code $C0: Data byte has been transmitted, NACK received (slave)*/
#define I2C_LAST_DATA_TRANSMITTED_ACK_SC    0xC8    /*Status Code $C8: Last data byte has been transmitted (slave), ACK received*/

/*Miscellaneous States*/
#define I2C_NO_RELEVANT_STATE_SC            0xF8    /*Status Code $F8: No relevant state information available (TWINT=0)*/
#define I2C_BUS_ERROR_SC                    0x00    /*Status Code $00: Bus error due to an illegal START or STOP condition*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*I2C Interrupt Status*/
#define I2C_INT_DISABLE						0	/*I2C Interrupt disable*/
#define I2C_INT_ENABLE						1	/*I2C Interrupt enable*/

/*I2C general call Status*/
#define I2C_GENERAL_CALL_DISABLE			0	/*The I2C module will ignore 	 the General Call address (0x00)*/
#define I2C_GENERAL_CALL_ENABLE				1	/*The I2C module will respond to the General Call address (0x00)*/

/*I2C Internal pull-up Status*/
#define I2C_INTERNAL_PULLUP_DISABLE			0	/*the internal pull-up disable by clearing the PORT bits corresponding to the SCL and SDA pins*/
#define I2C_INTERNAL_PULLUP_ENABLE			1	/*the internal pull-up enable  by setting  the PORT bits corresponding to the SCL and SDA pins*/

/*I2C Prescaler*/
#define I2C_PRESCALER_1						0	/*SCL = F_CPU / (16 + 2   * TWBR)*/
#define I2C_PRESCALER_4						1	/*SCL = F_CPU / (16 + 8   * TWBR)*/
#define I2C_PRESCALER_16					2	/*SCL = F_CPU / (16 + 32  * TWBR)*/
#define I2C_PRESCALER_64					3	/*SCL = F_CPU / (16 + 128 * TWBR)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   masks    -----------------------------------------*/

#define I2C_STATUS_msk						0xF8	/*I2C prescaler clear mask (0B11111000)*/

#define RESERVED_ADDRESS_MASK				0x78	/*Mask for addresses of the format 1111xxx*/
/*_______________________________________________________________________________________________*/


#endif /* I2C_DEF_H_ */
