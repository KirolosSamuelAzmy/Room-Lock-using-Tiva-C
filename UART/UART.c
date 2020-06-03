void uart_init(void){
  SYSCTL_RCGCUART_R |= 0x01;            // activate UART0
  SYSCTL_RCGCGPIO_R |= 0x01;            // activate port A
  while((SYSCTL_PRGPIO_R&0x01) == 0);
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 27;                    // IBRD = int(50,000,000 / (16 * 115,200)) = int(27.1267)
  UART0_FBRD_R = 8;                     // FBRD = int(0.1267 * 64 + 0.5) = 8
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}

char uart_in_char(void){ //function to recieve character
  while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((char)(UART0_DR_R&0xFF));
}

void uart_out_char(char data){ //function to send a char
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

void uart_outstring(char *pt){ //void to send a string 
while(*pt){
uart_out_char(*pt);
pt++;
}
}

uint32_t UART_InUDec(void){ //function to recieve an unsigned integer
uint32_t number=0, length=0;
char character;
character = uart_in_char();
while(character != CR){ // accepts until <enter> is typed
// The next line checks that the input is a digit, 0-9.
// If the character is not 0-9, it is ignored and not echoed
if((character>='0') && (character<='9')) {
number = 10*number+(character-'0');   // this line overflows if above 4294967295
length++;
uart_out_char(character);
}
// If the input is a backspace, then the return number is
// changed and a backspace is outputted to the screen
else if((character==BS) && length){
number /= 10;
length--;
uart_out_char(character);
}
character = uart_in_char();
}
return number;
}