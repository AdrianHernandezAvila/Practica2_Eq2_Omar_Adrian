/*
 * TimerTask.h
 *
 *  Created on: 25 abr. 2021
 *      Author: ADEZ
 */

#ifndef TIMERTASK_H_
#define TIMERTASK_H_

/* Fwk*/
#include"TimersManager.h"
#include"FunctionLib.h"
#include"LED.h"
/* KSDK */
#include"fsl_common.h"
#include"EmbeddedTypes.h"
#include"fsl_os_abstraction.h"

/* Define the available Task's Events */
#define	gMyNewTaskEvent1_c (1 << 0)
#define	gMyNewTaskEvent2_c (1 << 1)
#define	gMyNewTaskEvent3_c (1 << 2)

#define	gMyTaskPriority_c 3
#define	gMyTaskStackSize_c 400

void MyTaskTimer_Start(void);
void MyTaskTimer_Stop(void);
void MyTimerTask_Init(void);
int GetCounter(void);

void My_TimerTask(osaTaskParam_t argument);

#endif /* TIMERTASK_H_ */
