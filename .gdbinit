file build/ControlMI_PMIK.elf
target remote localhost:2331
monitor SWO EnableTarget 0 0 1 0
monitor reset
load
monitor reset
monitor go
disconnect
quit
