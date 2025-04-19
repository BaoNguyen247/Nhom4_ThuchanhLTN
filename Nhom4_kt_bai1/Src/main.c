#include "STM32F401RE_H"
static void delay(int x)
{
	for(uint32_t i =0; i < x * 1000000; i++);
}

int dk = 0 ;
int main(void){
	//Bat clock
	RCC->AHB1ENR |= 0x01 << 0;
	RCC->AHB1ENR |= 0x01 << 2;
	//PC13-Nut bam
	GPIOC->MODER |= ~(0x03 << 26);//input
	GPIOC->PUPDR |= 0x01 <<26;
	//PA5-led
	GPIOA->MODER |= 0x01 <<10;//output
	GPIOA->OTYPER |= 0x00 << 5;// pp
//	GPIOA->OTYPER |= 0x01 << 5;// od
//	GPIOA->OSPEEDR |= 0x01 << 10; // medium

	 while (1) {

	        if ((GPIOC->IDR & (0x01 << 13)) == 0) {
	        	dk = !dk;
	        	delay(2);
	        }
	        if (dk) {
	            GPIOA->ODR |= (0x01 << 5);  // A5 cao
	        } else {
	            GPIOA->ODR &= ~(0x01 << 5); // A5 thap
	        }
	 }
}
