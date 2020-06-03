struct room
	{

  char password[4];
	uint32_t room_n; 
	int status; // 0--->reserved
		          //1--->cleaning
	            //2---->free
	int door_condition;  //0--->closed
		                   //1--->opened
};
	
//function to return the index of the room based on its number assuming that the number of the rooms is 9
uint32_t findIndex(uint32_t target, struct room* array)
{
	int i = 0;
	while (( i < 10) && (array[i].room_n != target)) i++;
	return (i < 10) ? (i) : (-1);
}

//global varibales to be used
char room_pass[4]; //room password to be entered by the client using keypad
char pass_check; 
uint32_t setup_number; //no of rooms to be in setup
struct room room_list[9]; //room list
//variables to be used in the loops
int i;
int j;
uint32_t scenario;   //scnario to be entered
uint32_t room_number; //room number to be used by recept.
uint32_t r_index; //to hold the index
   


int main(){
//initalizing the devices connected to tiva c
keypad_ports_init();
uart_init();
solen_init();
//setup mode
uart_outstring("Please enter the number of rooms");
setup_number=UART_InUDec();  //get the number of the rooms to be in setup (must be less than 9 rooms)
//intializing the rooms by getting their numbers and making all of them closed by default and free.
for(i=0;i<setup_number;i++){
  room_list[i].room_n=UART_InUDec(); //enter the number of each room
	for(j=0;j<4;j++){       
	room_list[i].password[j]=uart_in_char();       	//entering the password of the room using uart
	}
  room_list[i].door_condition=0;       
  GPIO_PORTF_DIR_R=red;  //the door is closed
  room_list[i].status=2;	 //free
}
while(1){
 uart_outstring("Enter the scnartio you want");
 scenario= UART_InUDec();//get scenario
	//start of the code
	//check in
	if(scenario==0){
			uart_outstring("Please enter the room number");
			room_number=UART_InUDec(); //now i hold the room number
			r_index=findIndex(room_number,room_list); // now i hold the index of the room
		  if(room_list[r_index].status==0){ //if the room is already reserved
			uart_outstring("The room is already reserved");
			}
			else{ //The room is free
			room_list[r_index].status = 0; //The room is now reserved
			uart_outstring("Enter the password of the room");
			for(i=0;i<4;i++){
			room_list[r_index].password[i]=uart_in_char();
			}
			i=0;
			//the user will enter the password by using keypad
		 while(i!=4){
		 pass_check=scan_keypad();
	  	if(pass_check!='z'){
		 room_pass[i]=pass_check;
		 i++;
		 }
		 }
	   if(room_pass[0]==room_list[r_index].password[0]&&room_pass[1]==room_list[r_index].password[1]&&room_pass[2]==room_list[r_index].password[2]&&room_pass[3]==room_list[r_index].password[3]){
		 room_list[r_index].door_condition=1;
		 GPIO_PORTF_DIR_R=green; //door opened
		}
	}
		}
	else if(scenario==1) //cleaning
	{
	uart_outstring("Please enter the room number");
	room_number=UART_InUDec(); //now i hold the room number
	r_index=findIndex(room_number,room_list); // now i hold the index of the room
	room_list[r_index].status=1; //cleaning
	room_list[r_index].door_condition=1; //door opened
	GPIO_PORTF_DIR_R=green;
	}
	else if(scenario==2){ //check out
	uart_outstring("Please enter the room number");
	room_number=UART_InUDec(); //now i hold the room number
	r_index=findIndex(room_number,room_list); // now i hold the index of the room
	if(room_list[r_index].status==2){  //room is already free
	uart_outstring("The room is already free");
	}
	else if(room_list[r_index].status==0) //room is reserved
		{
	room_list[r_index].status=2; //room is free
	room_list[r_index].door_condition=0; //door is closed
	GPIO_PORTF_DIR_R=red; //door is closed
		}
	}

}
}