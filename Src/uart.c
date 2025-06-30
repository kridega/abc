/*
 * uart.c
 *
 *  Created on: Jun 26, 2025
 *      Author: singh
 */

#include "uart.h"
#include "pins.h"
#include "drive.h"



// =========================
// Bit Definitions
// =========================
// RCC
#define RCC_APB2ENR_IOPAEN    (1 << 2)
#define RCC_APB1ENR_USART2EN  (1 << 17)

// USART SR
#define USART_SR_TXE          (1 << 7)
#define USART_SR_RXNE         (1 << 5)

// USART CR1
#define USART_CR1_UE          (1 << 13)
#define USART_CR1_TE          (1 << 3)
#define USART_CR1_RE          (1 << 2)
#define USART_CR1_RXNEIE      (1 << 5)

// NVIC
#define USART2_IRQ_NUM        38
#define NVIC_ISER_USART2      (1 << (USART2_IRQ_NUM - 32)) // ISER1 handles IRQ 32–63

// =========================
// UART2 Initialization
// =========================
void UART2_Init(uint32_t baud)
{
    // 1. Enable Clocks
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC_APB1ENR |= RCC_APB1ENR_USART2EN;

    // 2. Configure GPIO
    // PA2 = TX (Alternate Function Push-Pull, 50 MHz)
    GPIOA_CRL &= ~(0xF << (2 * 4));   // Clear CNF+MODE for PA2
    GPIOA_CRL |=  (0xB << (2 * 4));   // MODE=11 (50MHz), CNF=10 (AF_PP)

    // PA3 = RX (Floating Input)
    GPIOA_CRL &= ~(0xF << (3 * 4));
    GPIOA_CRL |=  (0x4 << (3 * 4));   // MODE=00, CNF=01 (Floating input)

    // 3. Configure Baud Rate
    uint32_t uartdiv = 36000000 / (16 * baud);
    uint32_t mantissa = uartdiv;
    uint32_t fraction = ((36000000 % (16 * baud)) * 16) / baud;
    USART2_BRR = (mantissa << 4) | (fraction & 0xF);

    // 4. Enable USART, TX, RX, and RX Interrupt
    USART2_CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;

    // 5. Enable USART2 interrupt in NVIC (IRQ38 is on NVIC_ISER1 bit 6)
    NVIC_ISER1 |= NVIC_ISER_USART2;
}

// =========================
// Send One Character
// =========================
void UART2_SendChar(char c)
{
    while (!(USART2_SR & USART_SR_TXE)); // Wait for TX empty
    USART2_DR = c;
}

// =========================
// Send String
// =========================
void UART2_SendString(const char* str)
{
    while (*str)
    {
        UART2_SendChar(*str++);
    }
}

// =========================
// USART2 IRQ Handler
// =========================
void USART2_IRQHandler(void)
{
    if (USART2_SR & USART_SR_RXNE)
    {
        uint8_t data = USART2_DR;   // Reading DR clears RXNE
        UART2_StoreData(data);
    }
    int delimiterPos = inputBuffer.indexOf(';');
    if (delimiterPos <= 0) {
        // Serial.println("Packet missing delimiter, skipping.");
        return;
      }
      else{

        char axesStr[] = inputBuffer.substring(0, delimiterPos);
        char buttonsStr[] = inputBuffer.substring(delimiterPos + 1);

        parseAxes(axesStr, axes, MAX_AXES);
        parseButtons(buttonsStr, buttons, MAX_BUTTONS);

      // Print button 9 for debug:
      // Serial.print("Button9: ");
      // Serial.println(buttons[9]);

      // Execute robot control
      controlMotors(axes[0], axes[1], axes[4], axes[5]);
      }
}

int parseAxes(char *axesStr, float *axes, int maxAxes) {
    int axisIndex = 0;
    char *token = strtok(axesStr, ",");

    while (token != NULL && axisIndex < maxAxes) {
        axes[axisIndex++] = atof(token);
        token = strtok(NULL, ",");
    }

    return axisIndex;
}

int parseButtons(char *buttonsStr, int *buttons, int maxButtons) {
    int buttonIndex = 0;
    char *token = strtok(buttonsStr, ",");

    while (token != NULL && buttonIndex < maxButtons) {
        buttons[buttonIndex++] = atoi(token);
        token = strtok(NULL, ",");
    }

    return buttonIndex;
}






