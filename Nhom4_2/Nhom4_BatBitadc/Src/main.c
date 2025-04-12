#include<stdio.h>
#include<stdint.h>
#define RCC_BASE_ADDR 0x40023800UL
#define RCC_APB2ENR_ADDR (RCC_BASE_ADDR + 0x44UL)
#define RCC_CR_ADDR (RCC_BASE_ADDR + 0x00UL)
#define ADC_CR1_ADDR  (0x40012000UL + 0x04UL)


int main(){
uint32_t *papb2enr = (uint32_t*) RCC_APB2ENR_ADDR;
uint32_t *parcccr = (uint32_t*) RCC_CR_ADDR;
uint32_t *paadc = (uint32_t*) ADC_CR1_ADDR;
*papb2enr |= 0x100;//Bat clock cho adc1
*parcccr   |= 1;// bat hsi
*paadc |= 1<<8;
}
