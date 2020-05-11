#include "../common/stm32wrapper.h"


/* 100 MHz */
const struct rcc_clock_scale fastclock = {
  .pllm = 4, //VCOin = HSE / PLLM = 2 MHz
  .plln = 100, //VCOout = VCOin * PLLN = 200 MHz
  .pllp = 2, //PLLCLK = VCOout / PLLP = 100 MHz (max on STM32F413)
  .pllq = 6, //PLL48CLK = VCOout / PLLQ = 33.3 MHz (USB OTG FS requires exactly 48, <= 48 for RNG)
  .pllr = 0,
  .hpre = RCC_CFGR_HPRE_DIV_NONE,
  .ppre1 = RCC_CFGR_PPRE_DIV_2,
  .ppre2 = RCC_CFGR_PPRE_DIV_NONE,
  .pll_source = RCC_CFGR_PLLSRC_HSE_CLK,
  .voltage_scale = PWR_SCALE1,
  .flash_config = FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_LATENCY_3WS,
  .ahb_frequency = 100000000,
  .apb1_frequency = 50000000,
  .apb2_frequency = 100000000,
};
void clock_setup(void)
{
    rcc_clock_setup_pll(&fastclock);
    rcc_periph_clock_enable(RCC_GPIOG);
    rcc_periph_clock_enable(RCC_USART6);
    rcc_periph_clock_enable(RCC_DMA1);
}

void gpio_setup(void)
{
  gpio_mode_setup(GPIOG, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO14);
  gpio_set_af(GPIOG, GPIO_AF8, GPIO14);
}

void usart_setup(int baud)
{
  usart_set_baudrate(USART6, baud);
  usart_set_databits(USART6, 8);
  usart_set_stopbits(USART6, USART_STOPBITS_1);
  usart_set_mode(USART6, USART_MODE_TX);
  usart_set_parity(USART6, USART_PARITY_NONE);
  usart_set_flow_control(USART6, USART_FLOWCONTROL_NONE);

  usart_enable(USART6);
}

void send_USART_str(const unsigned char* in)
{
    int i;
    for(i = 0; in[i] != 0; i++) {
        usart_send_blocking(USART6, in[i]);
    }
    usart_send_blocking(USART6, '\r');
    usart_send_blocking(USART6, '\n');
}

void send_USART_bytes(const unsigned char* in, int n)
{
    int i;
    for(i = 0; i < n; i++) {
        usart_send_blocking(USART6, in[i]);
    }
}

