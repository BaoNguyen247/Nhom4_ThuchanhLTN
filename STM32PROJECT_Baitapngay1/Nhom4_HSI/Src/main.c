#include <system_stm32f4xx.h>
#define RCC_BASE_ADDR         0x40023800UL
#define RCC_CFGR_REG_OFFSET   0x08UL

#define RCC_CFGR_REG_ADDR     (RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)
#define GPIOA_BASE_ADDR       0x40020000UL
int main(void){
uint32_t *pRccCfgrReg =  (uint32_t*) RCC_CFGR_REG_ADDR;

// Cấu hình trường bit MCO1 của thanh ghi RCC_CFGR để lựa chọn HSI làm nguồn clock
*pRccCfgrReg &= ~(0x3 << 21); // Xóa bit 21 và 22

// Cài đặt hệ số chia prescaler cho đầu ra MCO1 là 4
*pRccCfgrReg |= (1 << 25);
*pRccCfgrReg |= (1 << 26);

// Cấp xung clock cho PORT A
uint32_t *pRCCAhb1Enr = (uint32_t*)(RCC_BASE_ADDR + 0x30);
*pRCCAhb1Enr |= (1 << 0); // Kích hoạt clock cho GPIOA

// Cài đặt chế độ của chân PA8 làm chức năng alternate function
uint32_t *pGPIOAModeReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
*pGPIOAModeReg &= ~(0x3 << 16); // Xóa
*pGPIOAModeReg |= (0x2 << 16);  // Cấu hình chế độ alternate function

// Cài đặt thanh ghi alternation function ở chế độ 0 cho chân PA8
uint32_t *pGPIOAAltFunHighReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x24);
*pGPIOAAltFunHighReg &= ~(0x0f << 0);

}
