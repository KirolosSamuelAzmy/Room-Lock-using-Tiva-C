void solen_init(void){   //soleniod init
	 uint32_t delay;
	 SYSCTL_RCGCGPIO_R |= 0X20;   //Giving clock to port F 
	 delay=1;
	 GPIO_PORTF_LOCK_R=0x4C4F434B;
	 GPIO_PORTF_CR_R=0x08;
   GPIO_PORTF_AFSEL_R=0;    //No alternative function enabled
	 GPIO_PORTF_PCTL_R=0; 
	 GPIO_PORTF_DIR_R=0x0E;   //PF1,PF2 and PF3 ARE O/P
	 GPIO_PORTF_AMSEL_R=0;     //disable analog in portF 
	 GPIO_PORTF_DEN_R=0x0E;     
	 GPIO_PORTF_PUR_R=0;
 }