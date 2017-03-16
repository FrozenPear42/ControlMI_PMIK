target remote localhost:2331
monitor reset
load build/ControlMI_PMIK.elf
monitor reset
monitor go
disconnect
