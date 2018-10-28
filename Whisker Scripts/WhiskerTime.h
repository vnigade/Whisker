//==============================================================================
//
// Title:		WhiskerTime.h
// Purpose:		A short description of the interface.
//
// Created on:	24-11-2015 at 16:54:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __WhiskerTime_H__
#define __WhiskerTime_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include <Windows.h>

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

extern void init_timer();
extern double get_time_msec();
extern void get_whisker_time(SYSTEMTIME *dh);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __WhiskerTime_H__ */
