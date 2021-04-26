/*
 * TimerTask.c
 *
 *  Created on: 25 abr. 2021
 *      Author: ADEZ
 */


#include "TimerTask.h"

/* OSA Task Definition*/
OSA_TASK_DEFINE(My_TimerTask, gMyTaskPriority_c, 1, gMyTaskStackSize_c, FALSE );

osaEventId_t mMyEvents;
/* Global Variable to store our TimerID */
tmrTimerID_t myTimerID = gTmrInvalidTimerID_c;
/* Handler ID for task */
osaTaskId_t gMyTaskHandler_ID;
/* Local variable to store the current state of the LEDs */
static uint8_t ledsState = 0;

static uint8_t counter = 0;

/* This is the function called by the Timer each time it expires */
static void myTaskTimerCallback(void *param)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent2_c);
}



/* Main custom task */
void My_TimerTask(osaTaskParam_t argument) {
	osaEventFlags_t customEvent;
	myTimerID = TMR_AllocateTimer();

	while (1) {
		OSA_EventWait(mMyEvents, osaEventFlagsAll_c, FALSE, osaWaitForever_c,
				&customEvent);

		if (!gUseRtos_c && !customEvent) {
			break;
		}

		if(counter==200){
			counter = 0;
		}

		/* Depending on the received event */
		switch (customEvent) {
		case gMyNewTaskEvent1_c:
			TMR_StartIntervalTimer(myTimerID, /*myTimerID*/
			1000, /* Timer's Timeout */
			myTaskTimerCallback, /* pointer to myTaskTimerCallback function */
			NULL);
			TurnOffLeds(); /* Ensure all LEDs are turned off */
			break;
		case gMyNewTaskEvent2_c: /* Event called from myTaskTimerCallback */
			if (!ledsState) {
				Led_TurnOn(0x04U);
				ledsState = 1;
				counter = counter + 1;
			} else {
				TurnOffLeds();
				ledsState = 0;
				counter = counter + 1;
			}
			break;
		case gMyNewTaskEvent3_c: /* Event to stop the timer */
			ledsState = 0;
			TurnOffLeds();
			TMR_StopTimer(myTimerID);
			break;
		default:
			break;
		}
	}
}

/* Function to init the task */
void MyTimerTask_Init(void)
{
	mMyEvents = OSA_EventCreate(TRUE);
	/* The instance of the MAC is passed at task creation */
	gMyTaskHandler_ID = OSA_TaskCreate(OSA_TASK(My_TimerTask), NULL);
}

void MyTaskTimer_Start(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent1_c);
}

/* Public function to send an event to stop the timer */
void MyTaskTimer_Stop(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent3_c);
}

int GetCounter(void)
{
	return counter;
}

