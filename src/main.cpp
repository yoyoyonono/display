#include <ch32v10x.h>
#include <debug.h>

#include "util.hpp"

#define PIN_1_PORT GPIOC
#define PIN_1_PIN 8
#define PIN_2_PORT GPIOC
#define PIN_2_PIN 7
#define PIN_3_PORT GPIOC
#define PIN_3_PIN 6
#define PIN_4_PORT GPIOB
#define PIN_4_PIN 15
#define PIN_5_PORT GPIOB
#define PIN_5_PIN 0
#define PIN_6_PORT GPIOC
#define PIN_6_PIN 5
#define PIN_7_PORT GPIOC
#define PIN_7_PIN 4
#define PIN_8_PORT GPIOA
#define PIN_8_PIN 7

GPIO_TypeDef* ports[] = {PIN_1_PORT, PIN_2_PORT, PIN_3_PORT, PIN_4_PORT, PIN_5_PORT, PIN_6_PORT, PIN_7_PORT, PIN_8_PORT};
uint8_t pins[] = {PIN_1_PIN, PIN_2_PIN, PIN_3_PIN, PIN_4_PIN, PIN_5_PIN, PIN_6_PIN, PIN_7_PIN, PIN_8_PIN};

void all_input() {
    for (int i = 0; i < 8; i++) {
        pinMode(ports[i], pins[i], INPUT);
    }
}

int main() {
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf(__TIMESTAMP__ "\r\n");
    printf("SystemCoreClock: %d Hz\r\n", SystemCoreClock);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    while (true)
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (i == j) {
                    continue;
                }
                all_input();
                pinMode(ports[i], pins[i], OUTPUT);
                pinMode(ports[j], pins[j], OUTPUT);
                digitalWrite(ports[i], pins[i], HIGH);
                digitalWrite(ports[j], pins[j], LOW);
                printf("%d high\t%d low\r\n", i, j);
                printf("\r\n");
                digitalWrite(ports[i], pins[i], LOW);
                digitalWrite(ports[j], pins[j], HIGH);
                printf("%d high\t%d low\r\n", j, i);
                printf("\r\n");
            }
        }
}