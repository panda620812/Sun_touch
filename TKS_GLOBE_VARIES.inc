; ========================================================================================================================
; * Created by: Holtek Touch MCU Workshop, Version 3.5.0.0
; TKS_GLOBE_VARIES.inc
; 03:02:23 PM Saturday, December 16, 2017
; ========================================================================================================================
#include "BS84B08A-3.inc"
#define _BS84B08A_
#define _V413_
#define SystemClock     0
#define IO              0
#define KEY             1
; Keys' attribute & settings ...
#define KEY1            KEY
#define Key1Threshold   16
#define KEY2            IO
#define Key2Threshold   16
#define KEY3            IO
#define Key3Threshold   16
#define KEY4            KEY
#define Key4Threshold   16
#define KEY5            KEY
#define Key5Threshold   25
#define KEY6            IO
#define Key6Threshold   16
#define KEY7            IO
#define Key7Threshold   16
#define KEY8            IO
#define Key8Threshold   16
#define IO_TOUCH_ATTR   00000000000000000000000000011001b
#define IO_TOUCH_ATTR2  0000b
; Components' settings ...
; Global options' settings ...
#define DebounceTimes   1 	; 180mS
#define AutoCalibrationPeriod 15 	; x 8 (640mS)
#define HighSensitive   0 	; check
#define MaximumKeyHoldTime 0	; Disable
#define FastResponse    0 	; uncheck
#define AutoFrequencyHopping 0 	; uncheck
#define OneKeyActive    1 	; check
#define PowerSave       0 	; uncheck
#define NoiseProtect    1 	; check
#define MovingCalibration 0 	; uncheck
#define GlobeOptionA    (DebounceTimes | (AutoCalibrationPeriod << 4))
#define GlobeOptionB    (HighSensitive | (MaximumKeyHoldTime << 4))
#define GlobeOptionC    ((FastResponse << 2) | (AutoFrequencyHopping << 3) | (OneKeyActive << 5) | (PowerSave << 6) | (NoiseProtect << 4) | (MovingCalibration << 7))
