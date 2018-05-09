#include "STM32F0xx.h"
#include "common.h"

/**
 * Initialize the HSI clock source and reset the PLL configuration. This
 * function is called by the startup_common.s file, just before calling the
 * main() function.
 */
void SystemInit (void) {
  // Set HSION bit
  RCC->CR |= (uint32_t)0x00000001U;

#if defined (STM32F051x8) || \
    defined (STM32F058x8)
  // Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE and MCOSEL[2:0] bits
  RCC->CFGR &= (uint32_t)0xF8FFB80CU;
#else
  // Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE, MCOSEL[2:0], MCOPRE[2:0] and PLLNODIV bits
  RCC->CFGR &= (uint32_t)0x08FFB80CU;
#endif

  // Reset HSEON, CSSON and PLLON bits
  RCC->CR &= (uint32_t)0xFEF6FFFFU;

  // Reset HSEBYP bit
  RCC->CR &= (uint32_t)0xFFFBFFFFU;

  // Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits
  RCC->CFGR &= (uint32_t)0xFFC0FFFFU;

  // Reset PREDIV[3:0] bits
  RCC->CFGR2 &= (uint32_t)0xFFFFFFF0U;

#if defined (STM32F072xB) || \
    defined (STM32F078xx)
  // Reset USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW, USBSW and ADCSW bits
  RCC->CFGR3 &= (uint32_t)0xFFFCFE2CU;

#elif defined (STM32F071xB)
  // Reset USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW and ADCSW bits
  RCC->CFGR3 &= (uint32_t)0xFFFFCEACU;

#elif defined (STM32F091xC) || \
      defined (STM32F098xx)
  // Reset USART3SW[1:0], USART2SW[1:0], USART1SW[1:0], I2C1SW, CECSW and ADCSW bits
  RCC->CFGR3 &= (uint32_t)0xFFF0FEACU;

#elif defined (STM32F030x6) || \
      defined (STM32F030x8) || \
      defined (STM32F031x6) || \
      defined (STM32F038xx) || \
      defined (STM32F030xC)
  // Reset USART1SW[1:0], I2C1SW and ADCSW bits
  RCC->CFGR3 &= (uint32_t)0xFFFFFEECU;

#elif defined (STM32F051x8) || \
      defined (STM32F058xx)
  // Reset USART1SW[1:0], I2C1SW, CECSW and ADCSW bits
  RCC->CFGR3 &= (uint32_t)0xFFFFFEACU;

#elif defined (STM32F042x6) || \
      defined (STM32F048xx)
  // Reset USART1SW[1:0], I2C1SW, CECSW, USBSW and ADCSW bits
  RCC->CFGR3 &= (uint32_t)0xFFFFFE2CU;

#elif defined (STM32F070x6) || \
      defined (STM32F070xB)
  // Reset USART1SW[1:0], I2C1SW, USBSW and ADCSW bits
  RCC->CFGR3 &= (uint32_t)0xFFFFFE6CU;
  // Set default USB clock to PLLCLK, since there is no HSI48
  RCC->CFGR3 |= (uint32_t)0x00000080U;

#else
  #warning "No target selected"
#endif

  // Reset HSI14 bit
  RCC->CR2 &= (uint32_t)0xFFFFFFFEU;

  // Disable all interrupts
  RCC->CIR = 0x00000000U;
}
