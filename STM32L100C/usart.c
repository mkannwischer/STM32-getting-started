#include "stm32wrapper.h"
#include <stdio.h>

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup(115200);

    send_USART_str((unsigned char*)"Attack at dawn");

    return 0;
}
