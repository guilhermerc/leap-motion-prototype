/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
**
** @author Guilherme R C <guilherme.riciolic@gmail.com
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include <comm.h>
#include <console.h>
#include <DEBOUNCING.h>
#include <event_buff.h>
#include <PE_Types.h>
#include <PORT_PDD.h>
#include <stdint.h>
#include <stdlib.h>
#include <TI1.h>
#include <UART0.h>
#include <UART2.h>
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* User includes (#include below this line is not maintained by Processor Expert) */

#define	TIMEOUT	10 // 600 ms of timeout. TODO: Check if this is a good value.
#define DEBOUNCING_TIMEOUT	100

/* A static variable that counts how many 100 ms timer interruptions have
 * occurred
 */
static uint8_t timeout_counter = 0;

/* A static variable that counts the number of snapping in a given period
 * (namely "timeout")
 */
static uint8_t snapping_counter = 0;

/*
** ===================================================================
**     Event       :  CPU_OnNMIINT (module Events)
**
**     Component   :  CPU [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void CPU_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  CPU [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}


/*
** ===================================================================
**     Event       :  UART0_OnError (module Events)
**
**     Component   :  UART0 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART0_OnError(void)
{
  /* Write your code here ... */
}

/*! @brief A handler that echoes the received char and also insert an
 * event in the event ring buffer if a complete message was received
**
** 	Follows the description generated by ProcessorExpert.
** ===================================================================
**     Event       :  UART0_OnRxChar (module UART0Events)
**
**     Component   :  UART0 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART0_OnRxChar(void)
{
	/*!
	 * Echoes the just received char
	 * Using the LOG function ensures that the next handling of an
	 * event will wait this echoing to be done. This is important as
	 * during this handling a LOG function can also be used and this
	 * message would be overwritten.
	 */
	console_write(NULL, UART0_GetPtrToLastRecvChar());

	if(UART0_HasACompleteMessage())
		event_buff_insert_event(NEW_MESSAGE_FROM_TERMINAL);
}

/*! @brief A function that indicates that a character was sent into the
 * TX channel of UART0. This handler is used to trigger chained calls
 * to send a message.
**
** 	Follows the description generated by ProcessorExpert.
** ===================================================================
**     Event       :  UART0_OnTxChar (module UART0Events)
**
**     Component   :  UART0 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART0_OnTxChar(void)
{
	static uint8_t curr_idx = 0;

	UART0_TComData curr_char = console_info.buffer[curr_idx++];
	if(curr_char != '\0')
	{
		UART0_SendChar(curr_char);
	}
	else
	{
		curr_idx = 0;

		console_info.status = DONE;
	}
}

/*
** ===================================================================
**     Event       :  UART2_OnError (module Events)
**
**     Component   :  UART2 [AsynchroSerial]
**     Description :
**         This event is called when a channel error (not the error
**         returned by a given method) occurs. The errors can be read
**         using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART2_OnError(void)
{
  /* Write your code here ... */
}

/*! @brief A handler that checks if a complete message has been
 * received. If so, it inserts a new event in the event ring buffer.
**
** 	Follows the description generated by ProcessorExpert.
** ===================================================================
**     Event       :  UART0_OnRxChar (module UART0Events)
**
**     Component   :  UART0 [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART2_OnRxChar(void)
{
	if(UART2_HasACompleteMessage())
		event_buff_insert_event(NEW_MESSAGE_FROM_BROKER);
}

/*! @brief A handler that indicates that a character was sent into the
 * TX channel of UART2. This handler is used to trigger chained calls
 * until a complete message is sent.
**
** 	Follows the description generated by ProcessorExpert.
** ===================================================================
**     Event       :  UART2_OnTxChar (module UART2Events)
**
**     Component   :  UART2 [AsynchroSerial]
**     Description :
**         This event is called after a character is transmitted.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART2_OnTxChar(void)
{
	static uint8_t curr_idx = 0;

	UART2_TComData curr_char = comm_info.message_out[curr_idx++];
	if(curr_char != '\0')
	{
		UART2_SendChar(curr_char);
	}
	else
	{
		curr_idx = 0;
		comm_info.sending_status = DONE;
	}
}

/*
** ===================================================================
**     Event       :  KY_038_OnInterrupt (module Events)
**
**     Component   :  KY_038 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void KY_038_OnInterrupt(void)
{
	/* If this is the first snapping since the last timeout, starts a new
	 * timeout counting process.
	 */

    EnterCritical();                   /* Disable global interrupts */

    DEBOUNCING_Waitms(DEBOUNCING_TIMEOUT);

	if(snapping_counter == 0)
	{
		timeout_counter = 0;
		TI1_EnableEvent();
	}

	snapping_counter++;	// And increment the number of snappings

    ExitCritical();                    /* Enable global interrupts */

	PORT_PDD_ClearPinInterruptFlag(PORTA_BASE_PTR, 5);
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
  	timeout_counter++;

  	/* If the timeout was achieved, inserts the proper event into the event
  	 * buffer.
  	 * NOTE: If 3 or more snappings occurred, it is not considered an event.
  	 */
  	if(timeout_counter == TIMEOUT)
  	{
  		if(snapping_counter == 2)
  			event_buff_insert_event(SINGLE_FINGER_SNAPPING);
  		else if(snapping_counter == 4)
  			event_buff_insert_event(DOUBLE_FINGER_SNAPPING);

  		snapping_counter = 0;

  		TI1_DisableEvent();
  	}
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
