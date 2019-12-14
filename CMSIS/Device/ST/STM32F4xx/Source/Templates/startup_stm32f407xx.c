/******************************************************************************
 * @file     startup_Device.c
 * @brief    CMSIS-Core(M) Device Startup File for <Device>
 * @version  V2.0.0
 * @date     20. May 2019
 ******************************************************************************/
/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bsp.h"

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void( *pFunc )( void );

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;
extern uint32_t __STACK_LIMIT;

extern __NO_RETURN void __PROGRAM_START(void);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
__NO_RETURN void Default_Handler        (void);
__NO_RETURN void Reset_Handler          (void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
__NO_RETURN void NMI_Handler            (void);
__NO_RETURN void HardFault_Handler      (void) __attribute__ ((naked));
__NO_RETURN void MemManage_Handler      (void);
__NO_RETURN void BusFault_Handler       (void);
__NO_RETURN void UsageFault_Handler     (void);

__NO_RETURN void SVC_Handler            (void) __attribute__ ((weak, alias("Unused_Handler")));
__NO_RETURN void DebugMon_Handler       (void) __attribute__ ((weak, alias("Unused_Handler")));
__NO_RETURN void PendSV_Handler         (void) __attribute__ ((weak, alias("Unused_Handler")));
__NO_RETURN void SysTick_Handler        (void) __attribute__ ((weak, alias("Unused_Handler")));

__NO_RETURN void Interrupt0_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void Interrupt1_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void Interrupt2_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void Interrupt3_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void Interrupt4_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void Interrupt5_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void Interrupt6_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void Interrupt7_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void Interrupt8_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));
__NO_RETURN void Interrupt9_Handler     (void) __attribute__ ((weak, alias("Default_Handler")));


/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
extern const pFunc __VECTOR_TABLE[240];
       const pFunc __VECTOR_TABLE[240] __VECTOR_TABLE_ATTRIBUTE = {
  (pFunc)(&__INITIAL_SP),                   /*     Initial Stack Pointer */
  Reset_Handler,                            /*     Reset Handler */
  NMI_Handler,                              /* -14 NMI Handler */
  HardFault_Handler,                        /* -13 Hard Fault Handler */
  MemManage_Handler,                        /* -12 MPU Fault Handler */
  BusFault_Handler,                         /* -11 Bus Fault Handler */
  UsageFault_Handler,                       /* -10 Usage Fault Handler */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  0,                                        /*     Reserved */
  SVC_Handler,                              /*  -5 SVCall Handler */
  DebugMon_Handler,                         /*  -4 Debug Monitor Handler */
  0,                                        /*     Reserved */
  PendSV_Handler,                           /*  -2 PendSV Handler */
  SysTick_Handler,                          /*  -1 SysTick Handler */

  /* Interrupts */
  Interrupt0_Handler,                       /*   0 Interrupt 0 */
  Interrupt1_Handler,                       /*   1 Interrupt 1 */
  Interrupt2_Handler,                       /*   2 Interrupt 2 */
  Interrupt3_Handler,                       /*   3 Interrupt 3 */
  Interrupt4_Handler,                       /*   4 Interrupt 4 */
  Interrupt5_Handler,                       /*   5 Interrupt 5 */
  Interrupt6_Handler,                       /*   6 Interrupt 6 */
  Interrupt7_Handler,                       /*   7 Interrupt 7 */
  Interrupt8_Handler,                       /*   8 Interrupt 8 */
  Interrupt9_Handler                        /*   9 Interrupt 9 */
                                            /* Interrupts 10 .. 223 are left out */
};

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
  SystemInit();                             /* CMSIS System Initialization */
  __PROGRAM_START();                        /* Enter PreMain (C library entry point) */
}

/*----------------------------------------------------------------------------
  NMI Handler 
 *----------------------------------------------------------------------------*/
void NMI_Handler(void) {
    assert_failed("NMI_Handler", __LINE__);
}

/*----------------------------------------------------------------------------
  HardFault Handler 
 *----------------------------------------------------------------------------*/
void HardFault_Handler(void) {
    __ASM volatile (
       "    mov r0,sp\n\t" /* Put value of stack pointer in r0 */
       "    ldr r1,=__StackLimit\n\t"  /* Load initial SP into r1 */
       "    cmp r0,r1\n\t" /* Perform r0 - r1 */
       "    bcs stack_ok\n\t"
       "    ldr r0,=__StackTop\n\t"
       "    mov sp,r0\n\t"
       "    ldr r0,=str_overflow\n\t"
       "    mov r1,#1\n\t"
       "    b assert_failed\n\t"
       "stack_ok:\n\t"
       "    ldr r0,=str_hardfault\n\t"
       "    mov r1,#2\n\t"
       "    b assert_failed\n\t"
       "str_overflow:   .asciz \"StackOverflow\"\n\t"
       "str_hardfault:  .asciz \"HardFault\"\n\t"
    );
}

/*----------------------------------------------------------------------------
  MemManage Handler 
 *----------------------------------------------------------------------------*/
void MemManage_Handler(void) {
    assert_failed("MemManage_Handler", __LINE__);
}

/*----------------------------------------------------------------------------
  BusFault Handler 
 *----------------------------------------------------------------------------*/
void BusFault_Handler(void) {
    assert_failed("BusFault_Handler", __LINE__);
}

/*----------------------------------------------------------------------------
  UsageFault Handler 
 *----------------------------------------------------------------------------*/
void UsageFault_Handler(void) {
    assert_failed("UsageFault_Handler", __LINE__);
}

/*----------------------------------------------------------------------------
  Unused Handler for Exceptions
 *----------------------------------------------------------------------------*/
void Unused_Handler(void) {
    assert_failed("Unused_Handler", __LINE__);
}

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
  while(1);
}

