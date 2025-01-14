/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

// Deals with sleeping and waking up
#include "common.h"
#include "sys.h"
#include "key.h"


#define BATTERY_CUTOFF	3100    //小于这个数值会自动关机 自动设置，是根据我的电池设的很水的值

typedef enum
{
	SYS_AWAKE,
	SYS_CRTANIM,
	SYS_SLEEP
} sys_t;

typedef enum
{
	USER_ACTIVE,
	USER_INACTIVE
} user_t;

static pwr_state_t active[PWR_ACTIVE_COUNT];
static sys_t systemState;
static user_t userState;

//static void batteryCutoff(void);
//static void userWake(void);
//static void userSleep(void);



//void pwrmgr_init()
//{
//	systemState = SYS_AWAKE;
//	userState = USER_ACTIVE;
////	set_sleep_mode(SLEEP_MODE_IDLE);
//}

//static void batteryCutoff()
//{
//	// If the battery voltage goes below a threshold then disable
//	// all wakeup sources apart from USB plug-in and go to power down sleep.
//	// This helps protect the battery from undervoltage and since the battery's own PCM hasn't kicked in yet the RTC will continue working.

//	uint voltage = battery_voltage();
//	if(voltage < BATTERY_CUTOFF  && voltage)
//	{
//		// Turn everything off
//		buttons_shutdown();
//		tune_stop(PRIO_MAX);
//		led_stop();
//		OLED_DisPlay_Off();
//		time_shutdown();
//		

//		// Stay in this loop until USB is plugged in or the battery voltage is above the threshold			
//		 do
//		{
//			External_interrupt_Enable();// 开启指定的外部中断
//			PWR_EnterSTOPMode(PWR_Regulator_LowPower,PWR_STOPEntry_WFE);
//      SystemInit();
//      External_interrupt_Disable();//关闭外部中断
//			// Get battery voltage
//			battery_updateNow();

//		} while(battery_voltage() < BATTERY_CUTOFF);

//		// Wake up
//		time_wake();
//		buttons_startup();
//		buttons_wake();
//		OLED_DisPlay_On();
//	}
//}

//void pwrmgr_update()
//{
//	batteryCutoff();
//	
//  bool idle=false ;// (UDADDR != 0); // if USB Configuard, no sleep
//	LOOPR(PWR_ACTIVE_COUNT, i)
//  {
// 		if(active[i] == PWR_STATE_BUSY) // Something busy, no sleep stuff
//	 		return;
//	  else if(active[i] == PWR_STATE_IDLE)
//		  idle = true;
//	}

//	bool buttonsActive = buttons_isActive();

//	if(idle || buttonsActive)
//	{
//#if COMPILE_ANIMATIONS
//		if(systemState == SYS_CRTANIM && buttonsActive) // Cancel CRT anim if a button is pressed
//		{
//			display_startCRTAnim(CRTANIM_OPEN);
//			systemState = SYS_AWAKE;
//		}
//		else // Idle sleep mode
//#endif
//		{
////      if(IS_PWR_SAVE_READY())
////				set_sleep_mode(SLEEP_MODE_PWR_SAVE); // Also disable BOD?
////			else
////				set_sleep_mode(SLEEP_MODE_IDLE);

////			debugPin_sleepIdle(HIGH);
////			sleep_mode();
////			debugPin_sleepIdle(LOW);
//		}
//	}
//	else
//	{
//#if COMPILE_ANIMATIONS
//		if(systemState == SYS_AWAKE) // Begin CRT anim
//		{
//			systemState = SYS_CRTANIM;
//			display_startCRTAnim(CRTANIM_CLOSE);

//		}
//		else if(systemState == SYS_CRTANIM)
//#endif
//		{
//			// Shutdown


//			if(userState == USER_ACTIVE)
//				userSleep();

////			systemState = SYS_SLEEP;
////			set_sleep_mode(SLEEP_MODE_PWR_DOWN);

//		 	time_sleep();

////      debugPin_sleepPowerDown(HIGH);

//			// need to make sure no interrupts fired here!
//			
//      External_interrupt_Enable();// 开启指定的外部中断
//			PWR_EnterSTOPMode(PWR_Regulator_LowPower,PWR_STOPEntry_WFE);
//      SystemInit();
//      External_interrupt_Disable();//关闭外部中断


////		 while(!buttons_isActive()){
////		  buttons_update();

////		 }

//			systemState = SYS_AWAKE;

//			if(time_wake() != RTCWAKE_SYSTEM) // Woken by button press, USB plugged in or by RTC user alarm
//				userWake();

//			//set_sleep_mode(SLEEP_MODE_IDLE);

//		}
//	}


//}

//void pwrmgr_setState(pwr_active_t thing, pwr_state_t state)
//{
//	active[thing] = state;
//}

bool pwrmgr_userActive()
{
	return userState == USER_ACTIVE;
}

//static void userWake()
//{
//	userState = USER_ACTIVE;
//	buttons_wake();
//	display_startCRTAnim(CRTANIM_OPEN);
//	OLED_DisPlay_On();
//	battery_setUpdate(3);
//}

//static void userSleep()
//{
//	userState = USER_INACTIVE;
//	OLED_DisPlay_Off();
//}
