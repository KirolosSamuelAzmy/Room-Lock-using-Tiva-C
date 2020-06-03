//Macros for uart
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable

// definition of CR , LF and BS
#define CR	0x0D
#define LF  0X0A
#define BS  0x08
void uart_init(void);
char uart_in_char(void);
void uart_out_char(char data);
uint32_t UART_InUDec(void);
