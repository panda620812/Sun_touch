; Generated by holtek-gcc v3.17, Sat Dec 16 15:02:24 2017
; 
; Configuration:
;       without long instruction
;       Single ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use ret-const
;       
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.17" "build 20130711"
; Rebuild 307

ir equ [2]
mp equ [3]
sbp equ [7]
acc equ [5]
bp equ [4]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
intc equ [11]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @HCCINIT, @HCCINIT0

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
public _LEDX4_V16_INITIAL
_LEDX4_V16_INITIAL .section 'code'
_LEDX4_V16_INITIAL proc
	ret
_LEDX4_V16_INITIAL endp
public _LEDX4_V16
_LEDX4_V16 .section 'code'
_LEDX4_V16 proc
	ret
_LEDX4_V16 endp

; 
; Generated by holtek-gcc v3.17, Sat Dec 16 15:02:24 2017
; Rebuild 307
; end of file
