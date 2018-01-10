; ========================================================================================================================
; * Created by: Holtek Touch MCU Workshop, Version 3.5.0.0
; MAIN_PROGRAM_V104.inc
; 03:02:23 PM Saturday, December 16, 2017
; ========================================================================================================================
#include "..\TKS_GLOBE_VARIES.inc" 
#include "MAIN_PROGRAM_20170905.MCU" 
#include "..\BS84B08A_LIBV413\BS84B08A_LIBV413.aex" 
#define                                
#define EXTEND_FUNCTION_1A_INITIAL     _BS84B08A_LIBV413_INITIAL
#define EXTEND_FUNCTION_1A             _BS84B08A_LIBV413
#include "..\USER_PROGRAM\USER_PROGRAM.aex" 
#define                                
#define EXTEND_FUNCTION_1B_INITIAL     _USER_PROGRAM_INITIAL
#define EXTEND_FUNCTION_1B             _USER_PROGRAM
#include "..\LEDX4_V16\LEDX4_V16.aex" 
#define                                
#define EXTEND_FUNCTION_1C_INITIAL     _LEDX4_V16_INITIAL
#define EXTEND_FUNCTION_1C             _LEDX4_V16
