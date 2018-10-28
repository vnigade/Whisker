//==============================================================================
//
// Title:		WhiskerTime.c
// Purpose:		It implements high resolution timer functionality.
//
// Created on:	24-11-2015 at 16:54:55 by Vinod Nigade.
// Copyright:	Vrije Universiteit Amsterdam. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "WhiskerTime.h"
#include <Windows.h>
#include <ansi_c.h>

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
static LARGE_INTEGER start_counter;	/* Start performance counter */
static LARGE_INTEGER frequency;		/* CPU Frequency */
//==============================================================================
// Global functions

/*
 * Initialize performance counter.
 * TODO: It is not thread safe.
 * Design could be:
 * 1) Maintain array of start counter holders for each thread and based
 *    on indexed returned to the thread
 * 2) Caller thread should save start counter and supply every time it makes call
 *    to the timer routine.
 */
void
init_timer()
{
	QueryPerformanceCounter(&start_counter);
	QueryPerformanceFrequency(&frequency);
	return;
}

double
get_time_msec()
{
	LARGE_INTEGER	counter;
	//LARGE_INTEGER	frequency;
	double			elapsed_time = 0;
	
	/* Retrieve current counter */
	QueryPerformanceCounter(&counter);
	
	/* TODO: If frequency returned is same on multiprocessor system,
	 * Then move this frequency retrival to init_routine()
	 */
	//QueryPerformanceFrequency(&frequency);
	//printf("Frequency %d \n", frequency.QuadPart);
	
	if (frequency.QuadPart != 0) {
		elapsed_time = ((counter.QuadPart - start_counter.QuadPart) * 1000LL) / frequency.QuadPart;
	} else {
		elapsed_time = 0.0;
	}
	return elapsed_time;
}

/*
 * Populate System time structure.
 */
void
get_whisker_time(SYSTEMTIME	*dh)
{
	double			time_stamp;
	unsigned int	temp;
	
	time_stamp = get_time_msec();
	if (time_stamp == 0.0) {	/* Get local time */
		GetLocalTime(dh);
	} else {					/* Populate dh structure */
		dh->wMilliseconds = (int) time_stamp % 1000;	/* Get milli seconds */
		dh->wSecond = (int)(time_stamp / 1000.0);		/* Total number of seconds from the start of the run */
		dh->wHour = dh->wSecond / 3600;					/* Total number of hours since start of the run */
		temp = dh->wSecond % 3600;						/* Get remaning seconds */
		dh->wMinute = temp / 60;						/* Get total number of minutes */
		dh->wSecond = temp % 60;						/* Get remaining seconds */		
	}
	return;
}

