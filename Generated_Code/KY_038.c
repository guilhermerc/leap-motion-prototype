/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : KY_038.c
**     Project     : EA076_final_proj
**     Processor   : MKL25Z128VLK4
**     Component   : ExtInt
**     Version     : Component 02.105, Driver 01.00, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-06-16, 18:30, # CodeGen: 20
**     Abstract    :
**         This component "ExtInt" implements an external 
**         interrupt, its control methods and interrupt/event 
**         handling procedure.
**         The component uses one pin which generates interrupt on 
**         selected edge.
**     Settings    :
**          Component name                                 : KY_038
**          Pin                                            : PTA5/USB_CLKIN/TPM0_CH2
**          Pin signal                                     : 
**          ExtInt_LDD                                     : ExtInt_LDD
**          Generate interrupt on                          : rising edge
**          Interrupt                                      : INT_PORTA
**          Interrupt priority                             : medium priority
**          Initialization                                 : 
**            Enabled in init. code                        : no
**     Contents    :
**         Enable - void KY_038_Enable(void);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file KY_038.c
** @version 01.00
** @brief
**         This component "ExtInt" implements an external 
**         interrupt, its control methods and interrupt/event 
**         handling procedure.
**         The component uses one pin which generates interrupt on 
**         selected edge.
*/         
/*!
**  @addtogroup KY_038_module KY_038 module documentation
**  @{
*/         

/* MODULE KY_038. */

#include "Events.h"
#include "KY_038.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Method      :  KY_038_Enable (component ExtInt)
**     Description :
**         Enable the component - the external events are accepted.
**         This method is available only if HW module allows
**         enable/disable of the interrupt.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/*
void KY_038_Enable(void)

**  This method is implemented as a macro. See KY_038.h file.  **
*/

/*
** ===================================================================
**     Method      :  KY_038_OnInterrupt (component ExtInt)
**
**     Description :
**         This event is called when an active signal edge/level has 
**         occurred. The event services the event of the inherited 
**         component and eventually invokes other events.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ExtIntLdd1_OnInterrupt(LDD_TUserData *UserDataPtr)
{
  (void)UserDataPtr;                   /* Parameter is not used, suppress unused argument warning */
  KY_038_OnInterrupt();                /* Invoke OnInterrupt event */
}

/* END KY_038. */

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
