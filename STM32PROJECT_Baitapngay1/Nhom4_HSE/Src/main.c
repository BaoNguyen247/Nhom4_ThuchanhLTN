#include <system_stm32f4xx.h>
#define RCC_BASE_ADDR          0x40023800UL
#define RCC_CFGR_REG_OFFSET    0x08UL
#define RCC_CR_REG_OFFSET      0x00UL

#define RCC_CFGR_REG_ADDR      (RCC_BASE_ADDR + RCC_CFGR_REG_OFFSET)
#define RCC_CR_REG_ADDR        (RCC_BASE_ADDR + RCC_CR_REG_OFFSET)
#define GPIOA_BASE_ADDR        0x40020000UL

int main(void){
	uint32_t *pRccCrReg = (uint32_t*)RCC_CR_REG_ADDR;
	uint32_t *pRccCfgrReg = (uint32_t*)RCC_CFGR_REG_ADDR;

	// Kích hoạt HSE bằng cách bật bit HSEON
	*pRccCrReg |= (1 << 16);

	// Đợi cho đến khi HSE ổn định
	while (!(*pRccCrReg & (1 << 17)));

	// Chuyển hệ thống sang nguồn xung nhịp HSE
	*pRccCfgrReg |= (1 << 0);

	// Cấu hình đầu ra MCO1 để chọn HSE làm nguồn xung nhịp
	*pRccCfgrReg |= (1 << 22); // Bật bit 22, xóa bit 21

	// Cài đặt hệ số chia prescaler cho MCO1 là 4
	*pRccCfgrReg |= (1 << 25);
	*pRccCfgrReg |= (1 << 26);

	// Cấp xung clock cho PORT A
	uint32_t *pRCCAhb1Enr = (uint32_t*)(RCC_BASE_ADDR + 0x30);
	*pRCCAhb1Enr |= (1 << 0); // Enable GPIOA peripheral clock

	// Cấu hình chế độ của chân PA8 làm chức năng alternate function
	uint32_t *pGPIOAModeReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x00);
	*pGPIOAModeReg &= ~(0x3 << 16); // Xóa bit hiện tại
	*pGPIOAModeReg |= (0x2 << 16);  // Đặt chế độ alternate function

	// Cấu hình chân PA8 ở chế độ alternation function
	uint32_t *pGPIOAAltFunHighReg = (uint32_t*)(GPIOA_BASE_ADDR + 0x24);
	*pGPIOAAltFunHighReg &= ~(0x0f << 0);
}
