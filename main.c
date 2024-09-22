#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
void init (void);
void Interrupt_Handler(void);
void init(void)
{

    SYSCTL_RCGCGPIO_R |= 0x020;
                   GPIO_PORTF_LOCK_R = 0x4C4F434B;

                   GPIO_PORTF_CR_R |= 0x10;          // allow changes to Port F4

                       // Configure PF1 as output  LED

                       GPIO_PORTF_DIR_R = 0x02;
                       GPIO_PORTF_DEN_R = 0x12;

                       GPIO_PORTF_PUR_R = 0x10;


                      GPIO_PORTF_IS_R = 0x00;            //  edge sensitive
                      GPIO_PORTF_IBE_R = 0x00;           // Interrupt controlled by IEV
                      GPIO_PORTF_IEV_R = 0x00;          // Falling edge trigger
                      GPIO_PORTF_ICR_R = 0x10;          // removing prior interrupt
                      GPIO_PORTF_IM_R = 0x10;            // Unmask interrupt for Port F4


                      NVIC_EN0_R = 0x40000000;

}



int main()
{
    init();
    GPIO_PORTF_DATA_R = 0x00; //Making red led to be off initially
               while(1)
               {
                  // do nothing
               }
}
void Interrupt_Handler(void)
{
    if(GPIO_PORTF_RIS_R & 0x10)
    {

            GPIO_PORTF_DATA_R ^= 0x02;

            // Clear the interrupt
            GPIO_PORTF_ICR_R = 0x10;

    }
}
