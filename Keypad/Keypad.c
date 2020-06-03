void keypad_ports_init(void){
	  uint32_t delay;
		SYSCTL_RCGCGPIO_R|=0x02; //give clock to port B
		delay=1; //dummy var
		GPIO_PORTB_LOCK_R =0X4C4F434B; //unlock port B
		GPIO_PORTB_CR_R=0xff;
		GPIO_PORTB_AFSEL_R=0;
		GPIO_PORTB_PCTL_R=0;
		GPIO_PORTB_AMSEL_R=0;
		GPIO_PORTB_DEN_R=0xff;
		GPIO_PORTB_PUR_R=0;
		GPIO_PORTB_DIR_R=0x0f;
}

unsigned char scan_keypad(){
 int i,column,key=0;
const unsigned char key_val [4][4] =
{ // col0 , col1 , col2 , col3
{'1', '2', '3', 'A'}, // row0
{'4', '5', '6', 'B'}, // row1
{'7', '8', '9', 'C'}, // row2
{'*', '0', '#', 'D'} // row3
};
for(i=0;i<4;i++){
  column=0x01 << i; //0x01---->first loop
	                  //0x10---->second loop
	                  //0x40---->third loop
	                  //0x08---->fourth loop
	col1=column << 4; // column 1 will be high in first loop
	col2=column << 4; // column 2 will be high in second loop
	col3=column << 4; // column 4 will be high in 3rd loop
	col4=column << 4; // column 3 will be high in 4th loop 
if(row1 & 0x01){
while(row1 & 0x01);
return key_val[key][i];
}
if(row2 & 0x02){
key+=1;
while(row1 & 0x02);
return key_val[key][i];
}
if(row3 & 0x04){
key+=2;
while(row3 & 0x04);
return key_val[key][i];
}
if(row4 & 0x08){
key+=3;
while(row4 & 0x08);
return key_val[key][i];
}
key=0;
}
return 'z';  //return z in case of not pressing any key
}