/*
  USART.c
  2017/12/14
  written by kokubo
*/

#include "stdio.h"
#include "string.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "USART.h"

extern UART_HandleTypeDef huart2;

//USART2　初期化
void USART2_Init(void)
{
  
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}


//1文字取得
char uart_getc(){
  char ch;
  while(HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, 1000) == HAL_TIMEOUT);
  return ch;
}


//1文字出力
void uart_putc(char ch){
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 1000);
}


//文字列を出力
void uart_puts(char *str){
  HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000);
  }


//変数の値を文字列として出力
void uart_putv(int32_t value){
  char str[20] = {'\0'};
  sprintf(str, "%d", value);  
  HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000);
  }