target remote localhost:2331
monitor SWO EnableTarget 0 0 1 0
monitor reset
load build/ControlMI_PMIK.elf
monitor reset
monitor go
disconnect
quit
