# define row1  ( GPIO_PORTB_DATA_R & 0x01 ) //PB0 INPUTS
# define row2  ( GPIO_PORTB_DATA_R & 0x02 ) //PB1
# define row3  ( GPIO_PORTB_DATA_R & 0x04 ) //PB2
# define row4  ( GPIO_PORTB_DATA_R & 0x08 ) //PB3
	
#define  col1 *((volatile uint32_t *)0x40005040) //PB4 OUTPUTS
#define  col2 *((volatile uint32_t *)0x40005080) //PB5
#define  col3 *((volatile uint32_t *)0x40005100) //PB6
#define  col4 *((volatile uint32_t *)0x40005200) //PB7
void keypad_ports_init(void);
unsigned char scan_keypad;