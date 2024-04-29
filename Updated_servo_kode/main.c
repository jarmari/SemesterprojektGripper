//Define constants for uart recieve
#define F_CPU 8000000UL				//Defining the frequency of the CPU.
#define GRIPPER_NUMBER_BIT 0b01100000
#define ROT_BIT 0b00010000
#define OPEN_BIT 0b00001000
#define CHECK_BIT 0b10000001

//Includes 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

//Setup constants:
uint8_t m; 
uint8_t error; 
uint8_t gripper_number;
uint8_t rot; 
uint8_t open; 

//Duty
uint16_t gripper_rot[4] = {1000, 1000, 1000, 1000};
uint16_t gripper_open[4] = {1000, 1000, 1000, 1000};
uint8_t servo_rot_pin [4] = {PIND3, PIND4, PIND5, PIND7};
uint8_t servo_open_pin [4] = {PINA1,PINA3 ,PINA5, PINA7};

//UART setup, setting recieve and transmit 
void setup_uart() {
	// Set baud rate
	UBRRH =  0;								//Used for calculating F_CPU/16(baud rate)-1 = 51
	UBRRL =  51;							//Therefor its under 255 and we only have to use the low part not the high part.
	UCSRB |= (1 << TXEN) | (1 << RXEN);
	UCSRB |= (1 << RXCIE);
}

//UART transmit for sending back to robot 
void uart_transmit(uint8_t data) {
	// Wait for empty transmit buffer
	while (!(UCSRA & (1 << UDRE)));

	// Put data into buffer, sends the data
	UDR = data;
}

void uart_transmit_16(uint16_t data) {
	// Wait for empty transmit buffer
	uint8_t MSB = data >> 8; 
	uint8_t LSB = (data<<8) >> 8;
	uint8_t data2[2] = {MSB, LSB};
		
	for (int i= 0; i<2; i++ ){
		while (!(UCSRA & (1 << UDRE)));
		UDR = data2[i];
		}
}

//Timer interrupt for PWN 
ISR(TIMER1_COMPA_vect){
	PORTD = 0xFF;
	PORTA = 0xFF;
}

//SETUP PWM 
void set_timer_pwm(){
	DDRD = 0xFF; //Port D som output
	DDRA = 0xFF; 
	
	TCCR1A |= 1<<WGM11;   // | 1<<COM1A1 | 1<<COM1A0 | 1<<COM1B1 | 1<<COM1B0 | 1<<FOC1A | 1<<FOC1B; //configuration af TC1 "Fast PWM mode, non-inverted output on OC1A.
	TCCR1B |= 1<<WGM12 | 1<<WGM13  | 1<<CS11; //Sets TC1 for a prescaler of 8 (no prescaling) and Fast PWM mode.
	TIMSK  |= 1<<OCIE1A; //Enables the output compare interrupt for OC1A.
	
	ICR1 = 19999; // maksimale værdi for counter fra databladet beregnes duty cycle.

	sei(); // Enables global interrupts. som gør at kalde interrupt service routine (ISR), som sætter PORTD to 0xFF (all pins high).
	
	DDRD |= (1 << PORTD5) | (1 << PORTD4) | (1 << PORTD3) | (1 << PORTD7); // PD5,4,3,7 som output-pins.
	DDRA |= (1 << PORTA1) | (1 << PORTA3) | (1 << PORTA5) | (1 << PORTA7); // PA1,2,4,6 som output-pins.

}

void rot_servo(uint8_t gripper_number, uint8_t rot){
	uint16_t angle;
	if (rot == 1){
		angle = 2300;
	}
	else {
		angle = 1000;
	}
	
	gripper_rot[gripper_number] = angle;
	
	
}

void open_serv(uint8_t gripper_number, uint8_t open){
	uint16_t angle;
	if (open == 1){
		angle = 2000;		//2650 var en stabil 
	}
	else {
		angle = 600;
	}

gripper_open[gripper_number] = angle;
//uart_transmit_16(servo_open[gripper_number]); 
}

ISR(USART_RXC_vect){			//UART Receive interrupt
	m = UDR;
	if ((m & CHECK_BIT)==CHECK_BIT){
		rot = (m & ROT_BIT) >> 4;
		gripper_number = (m & GRIPPER_NUMBER_BIT)>>5;
		open = (m & OPEN_BIT) >> 3;
		rot_servo(gripper_number, rot);
		open_serv(gripper_number, open);
	}
	else {
		error = 1;
		uart_transmit(error);
	}
}


int main(void) {
	
	set_timer_pwm(); 
	setup_uart();


	while(1){
		for (int i=0; i < 4; i++) {
			if (TCNT1 >= 500 && TCNT1 <= 2500){
				if (TCNT1 >= gripper_rot[i] && bit_is_set(PORTD , servo_rot_pin[i])) PORTD &= ~(1 << servo_rot_pin[i]);
				
				if (TCNT1 > gripper_open[i]&& bit_is_set(PORTA , servo_open_pin[i])) PORTA &= ~(1 << servo_open_pin[i]);
				}
		}
		
	}
	
	return 0;
}