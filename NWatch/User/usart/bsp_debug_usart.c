#include "bsp_debug_usart.h"

UART_HandleTypeDef UartHandle;

/**
 * @brief  DEBUG_USART GPIO ����,����ģʽ���á�115200 8-N-1
 * @param  ��
 * @retval ��
 */
void DEBUG_USART_Config(void)
{

    UartHandle.Instance          = DEBUG_USART;

    UartHandle.Init.BaudRate     = DEBUG_USART_BAUDRATE;
    UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits     = UART_STOPBITS_1;
    UartHandle.Init.Parity       = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode         = UART_MODE_TX_RX;

    HAL_UART_Init(&UartHandle);
    /*ʹ�ܴ��ڽ��ն� */
    __HAL_UART_ENABLE_IT(&UartHandle, UART_IT_RXNE);
}


/**
  * @brief UART MSP ��ʼ��
  * @param huart: UART handle
  * @retval ��
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    DEBUG_USART_CLK_ENABLE();

    DEBUG_USART_RX_GPIO_CLK_ENABLE();
    DEBUG_USART_TX_GPIO_CLK_ENABLE();

    /**USART1 GPIO Configuration
      PA9     ------> USART1_TX
      PA10    ------> USART1_RX
      */
    /* ����Tx����Ϊ���ù���  */
    GPIO_InitStruct.Pin = DEBUG_USART_TX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStruct);

    /* ����Rx����Ϊ���ù��� */
    GPIO_InitStruct.Pin = DEBUG_USART_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_INPUT;	//ģʽҪ����Ϊ��������ģʽ��
    HAL_GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStruct);

    //��ռ���ȼ�0�������ȼ�1
    HAL_NVIC_SetPriority(DEBUG_USART_IRQ, 2, 0);
    //ʹ��USART1�ж�ͨ��
    HAL_NVIC_EnableIRQ(DEBUG_USART_IRQ );
}

void  DEBUG_USART_IRQHandler(void)
{
    uint8_t ch = 0;

    if(__HAL_UART_GET_FLAG( &UartHandle, UART_FLAG_RXNE ) != RESET)
    {
        ch = ( uint16_t)READ_REG(UartHandle.Instance->DR);
        WRITE_REG(UartHandle.Instance->DR, ch);
    }
}


/*****************  �����ַ��� **********************/
void Usart_SendString(uint8_t *str)
{
    unsigned int k = 0;

    do
    {
        HAL_UART_Transmit(&UartHandle, (uint8_t *)(str + k), 1, 1000);
        k++;
    }
    while(*(str + k) != '\0');

}
//�ض���c�⺯��printf������DEBUG_USART���ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
    /* ����һ���ֽ����ݵ�����DEBUG_USART */
    HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 1000);

    return (ch);
}

//�ض���c�⺯��scanf������DEBUG_USART����д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
    int ch;
    HAL_UART_Receive(&UartHandle, (uint8_t *)&ch, 1, 1000);
    return (ch);
}

/*********************************************END OF FILE**********************/