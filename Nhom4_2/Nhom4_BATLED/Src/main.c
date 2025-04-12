#include "STM32F401RE_H"

int main(void) {
    // Bật đồng hồ cho GPIOA và GPIOC
    RCC->AHB1ENR |= (1 << 0);  // Bật đồng hồ cho GPIOA
    RCC->AHB1ENR |= (1 << 2);  // Bật đồng hồ cho GPIOC

    // Cấu hình GPIOC pin 13 làm đầu vào với pull-up
    GPIOC->MODER &= ~(3 << 26);  // Đặt chế độ là đầu vào (00)
    GPIOC->PUPDR &= ~(3 << 26);  // Xóa cấu hình pull-up/pull-down
    GPIOC->PUPDR |= (1 << 26);   // Đặt pull-up (01)

    // Cấu hình GPIOA pin 5 làm đầu ra
    GPIOA->MODER |= (1 << 10);    // Đặt chế độ là đầu ra (01)

    while (1) {
        // Kiểm tra nếu nút bấm tại chân C13 được nhấn (trạng thái thấp)
        if ((GPIOC->IDR & (1 << 13)) == 0) {
            // Nút bấm được nhấn, bật LED tại chân A5
            GPIOA->ODR |= (1 << 5);  // Đặt chân A5 lên cao (bật LED)
        } else {
            // Nút bấm không được nhấn, tắt LED tại chân A5
            GPIOA->ODR &= ~(1 << 5); // Đặt chân A5 xuống thấp (tắt LED)
        }
    }
}
