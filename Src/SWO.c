#include <SWO.h>
#include <stm32f303xe.h>

uint8_t SWO_PrintChar(char c) {
    while (ITM->PORT[0].u32 == 0);
    ITM->PORT[0].u8 = (uint8_t) c;
}

void SWO_PrintString(const char* s) {
    while (*s) {
        while (ITM->PORT[0].u32 == 0);
        ITM->PORT[0].u8 = (uint8_t) *s;
        s++;
    }
}