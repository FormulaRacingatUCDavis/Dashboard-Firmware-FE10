# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\leoja\Documents\GitHub\Dashboard-Firmware-FE10\Dashboard-Firmware-FE9\Dashboard.cydsn\Dashboard.cyprj
# Date: Fri, 29 Sep 2023 03:50:16 GMT
#set_units -time ns
create_clock -name {ADC_GLV_V_intClock(FFB)} -period 208.33333333333331 -waveform {0 104.166666666667} [list [get_pins {ClockBlock/ff_div_10}]]
create_clock -name {CyRouted1} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {ADC_GLV_V_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 5 11} -nominal_period 208.33333333333331 [list]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 5} [list [get_pins {ClockBlock/udb_div_1}]]
create_generated_clock -name {timer_clock_3} -source [get_pins {ClockBlock/hfclk}] -edges {1 961 1921} [list [get_pins {ClockBlock/udb_div_3}]]


# Component constraints for C:\Users\leoja\Documents\GitHub\Dashboard-Firmware-FE10\Dashboard-Firmware-FE9\Dashboard.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\leoja\Documents\GitHub\Dashboard-Firmware-FE10\Dashboard-Firmware-FE9\Dashboard.cydsn\Dashboard.cyprj
# Date: Fri, 29 Sep 2023 03:50:07 GMT
# GraphicLCDIntf
# False paths present for both 8 and 16 bits Graphic LCD Interface configurations 
expr {(8) == 8 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd8:Lsb\/p_out_0}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_0}]] : \
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Lsb\/p_out_0}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_0}]]} 
   
expr {(8) == 8 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd8:Lsb\/p_out_1}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_1}]] : \
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Lsb\/p_out_1}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_1}]]} 
   
expr {(8) == 8 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd8:Lsb\/p_out_2}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_2}]] : \
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Lsb\/p_out_2}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_2}]]} 
   
expr {(8) == 8 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd8:Lsb\/p_out_3}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_3}]] : \
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Lsb\/p_out_3}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_3}]]} 
   
expr {(8) == 8 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd8:Lsb\/p_out_4}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_4}]] : \
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Lsb\/p_out_4}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_4}]]} 
   
expr {(8) == 8 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd8:Lsb\/p_out_5}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_5}]] : \
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Lsb\/p_out_5}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_5}]]} 
   
expr {(8) == 8 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd8:Lsb\/p_out_6}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_6}]] : \
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Lsb\/p_out_6}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_6}]]} 
 
expr {(8) == 8 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd8:Lsb\/p_out_7}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_7}]] : \
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Lsb\/p_out_7}] -to [get_pins {\GraphicLCDIntf:LsbReg\/status_7}]]} 
   
# False paths present only for 16 bits Graphic LCD Interface configuration
expr {(8) == 16 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Msb\/p_out_0}] -to [get_pins {\GraphicLCDIntf:GraphLcd16:MsbReg\/status_0}]] : {}}
   
expr {(8) == 16 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Msb\/p_out_1}] -to [get_pins {\GraphicLCDIntf:GraphLcd16:MsbReg\/status_1}]] : {}}
   
expr {(8) == 16 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Msb\/p_out_2}] -to [get_pins {\GraphicLCDIntf:GraphLcd16:MsbReg\/status_2}]] : {}}

expr {(8) == 16 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Msb\/p_out_3}] -to [get_pins {\GraphicLCDIntf:GraphLcd16:MsbReg\/status_3}]] : {}}
   
expr {(8) == 16 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Msb\/p_out_4}] -to [get_pins {\GraphicLCDIntf:GraphLcd16:MsbReg\/status_4}]] : {}}
   
expr {(8) == 16 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Msb\/p_out_5}] -to [get_pins {\GraphicLCDIntf:GraphLcd16:MsbReg\/status_5}]] : {}}
   
expr {(8) == 16 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Msb\/p_out_6}] -to [get_pins {\GraphicLCDIntf:GraphLcd16:MsbReg\/status_6}]] : {}}
   
expr {(8) == 16 ?
   [set_false_path -from [get_pins {\GraphicLCDIntf:GraphLcd16:Msb\/p_out_7}] -to [get_pins {\GraphicLCDIntf:GraphLcd16:MsbReg\/status_7}]] : {}}

