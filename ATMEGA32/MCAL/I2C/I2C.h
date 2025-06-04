/****************************************************************************
 * @file    I2C.h
 * @author  Boles Medhat
 * @brief   I2C (TWI) Driver Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-08-06]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for the I2C (TWI) module
 * in ATmega32 microcontrollers, supporting Master and Slave operations.
 * It offers configurable initialization, start/stop conditions, address
 * transmission, data read/write (ACK/NACK), error handling, and interrupt
 * support through callback functions.
 *
 * The I2C driver includes the following functionalities:
 * - Master mode operations (start, address, write/read with ACK/NACK, stop).
 * - Slave mode operations (receive/write data based on master requests).
 * - Error handling for common I2C failure cases.
 * - Interrupt enable/disable and user-defined callback support.
 * - Real-time status checks for communication stages and modes.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `I2C_config.h` for macro-based configuration.
 * - SDA/SCL pins should be properly pulled up for reliable communication.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include "../../LIB/BIT_MATH.h"
#include "I2C_config.h"


/*
 * @brief  Initialize the I2C module based on configuration options.
 *
 * This function configures the SCL frequency using the selected prescaler and TWBR value,
 * I2C module address (7-bit), enables or disables General Call recognition,
 * internal pull-up resistors for SDA and SCL pins, enables or disables the I2C interrupt,
 * enables acknowledgment and the I2C module itself.
 * It configures the I2c registers according to the defined macros in `I2C_config.h`.
 *
 * @see `I2C_config.h` for configuration options.
 */
void I2C_Init( void );


/*
 * @brief Disable the I2C interrupt.
 *
 * This function disables I2C (TWI) interrupt by clearing the TWIE bit in the TWCR register to disable
 */
void I2C_DisableInterrupt( void );


/*
 * @brief Enable the I2C interrupt.
 *
 * This function enables I2C (TWI) interrupt by set the TWIE bit in the TWCR register.
 */
void I2C_EnableInterrupt( void );


/*
 * @brief Send an I2C start condition.
 *
 * This function initiates a start condition on the I2C bus to begin communication.
 *
 * @return (uint8) 0 if the start condition was transmitted successfully, 1 otherwise.
 */
uint8 I2C_Start( void );


/*
 * @brief Send a repeated I2C start condition.
 *
 * This function useful when changing the direction of communication or restarting
 * without sending a stop condition.
 *
 * @return (uint8) 0 if the repeated start was transmitted successfully, 1 otherwise.
 */
uint8 I2C_RepeatedStart( void );


/*
 * @brief Send the slave address with write operation.
 *
 * This function sends a 7-bit slave address followed by a write bit (0) on the I2C bus.
 *
 * @param Address: The 7-bit address of the slave device.
 *
 * @return (uint8) 0 if ACK received, 1 if NACK or error.
 */
uint8 I2C_SendSlaveAddress_Write( uint8 Address );


/*
 * @brief Send the slave address with read operation.
 *
 * This function sends a 7-bit slave address followed by a read bit (1) on the I2C bus.
 *
 * @param Address: The 7-bit address of the slave device.
 *
 * @return (uint8) 0 if ACK received, 1 if NACK or error.
 */
uint8 I2C_SendSlaveAddress_Read( uint8 Address );


/*
 * @brief Write a byte of data to the I2C bus.
 *
 * This function transmits a byte of data to the slave device currently addressed.
 *
 * @param Data: The byte of data to be transmitted.
 *
 * @return (uint8) 0 if ACK received, 1 if NACK or error.
 */
uint8 I2C_WriteData( uint8 Data );



/*
 * @brief Read a byte of data from the I2C bus and send ACK.
 *
 * This function receives a byte from the slave and sends an acknowledgment (ACK).
 *
 * @param[out] Data: Pointer to store the received byte.
 *
 * @return (uint8) 0 success, 1 otherwise.
 */
uint8 I2C_ReadData_ACK( uint8 * Data );


/*
 * @brief Read a byte of data from the I2C bus and send NACK.
 *
 * This function receives a byte from the slave and sends a not acknowledgment (NACK).
 *
 * @param[out] Data: Pointer to store the received byte.
 *
 * @return (uint8) 0 success, 1 otherwise.
 */
uint8 I2C_ReadData_NACK( uint8 * Data );


/*
 * @brief Send an I2C stop condition.
 *
 * This function Sends a stop condition to terminate communication on the I2C bus.
 */
void I2C_Stop( void );


/*
 * @brief Get the current status of the I2C bus.
 *
 * This function reads and returns the status bits from the TWSR register.
 *
 * @return (uint8) The masked status code of the current I2C operation.
 */
uint8 I2C_GetStatus(void);


/*
 * @brief Handles I2C errors by executing the appropriate error-handling routines.
 *
 * This function checks the status code of the I2C interface and performs the appropriate error-handling actions:
 * - If an arbitration loss occurs, it will send a start condition to retry the operation.
 * - For other errors such as bus errors or NACK conditions, it sends a stop condition.
 * - For certain valid conditions, it enables the acknowledge bit and clear the interrupt flag to proceed with the next operation.
 */
void I2C_ErrorHandler( void );


/*
 * @brief Checks if the I2C slave has received a request from the master to read data.
 *
 * This function checks the current status of the I2C interface to determine if the slave device
 * has been addressed for reading by the master. It returns 1 if the slave has received a read request,
 * otherwise returns 0.
 *
 * @return (uint8) 1 if the slave has received a read request, otherwise 0.
 */
uint8 I2C_IsSlaveHasRead( void );


/*
 * @brief Checks if the I2C slave has received a request from the master to write data.
 *
 * This function checks the current status of the I2C interface to determine if the slave device
 * has been addressed for writing by the master. It returns 1 if the slave has received a write request,
 * otherwise returns 0.
 *
 * @return (uint8) 1 if the slave has received a write request, otherwise 0.
 */
uint8 I2C_IsSlaveHasWrite( void );


/*
 * @brief Reads data from the master device as an I2C slave.
 *
 * This function waits until the I2C slave is addressed by the master to receive data. Once the request
 * is detected, the function reads the data byte from the data register, clear the interrupt flag to
 * allow further I2C operations, and returns the received data byte.
 *
 * @return (uint8) The data byte received from the master.
 */
uint8 I2C_SlaveRead( void );


/*
 * @brief Writes data to the master device as an I2C slave.
 *
 * This function waits until the I2C slave is addressed by the master to write data. Once the request
 * is detected, the function loads the data byte into the data register, enables the acknowledge bit,
 * clear the interrupt flag to allow further I2C operations, and sends the data byte to the master.
 *
 * @param Data: The data byte to be written to the master.
 */
void I2C_SlaveWrite( uint8 Data );


/*
 * @brief Sets a callback function for a I2C interrupt.
 *
 * This function set a user-defined callback function to be called when the I2C interrupt occurs.
 *
 * @example
 * void I2C_InterruptHandler()
 * {
 *     // code
 * }
 * ...
 * I2C_SetCallback( I2C_InterruptHandler );
 *
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 						void return type and no parameters.
 */
void I2C_SetCallback( void (*CopyFuncPtr)(void) );


#endif /* I2C_H_ */
