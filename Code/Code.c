 

#include<reg51.h> // Including header file for 8051 microcontroller
#include <stdio.h> // Standard input-output library for C
#include <math.h> // Math library for C

#define sound_velocity 34300  	/* Defining the velocity of sound in cm/s */
#define period_in_us pow(10,-6) // Defining the period for microsecond time delay
#define Clock_period 1.085*period_in_us /* Defining the period of the clock cycle of 8051 microcontroller */

sbit rightIR = P3^3; // Defining the right IR sensor pin
sbit leftIR = P3^4; // Defining the left IR sensor pin

// Defining the LED pins
sbit ledS = P1^4; // Sound-sensor LED
sbit ledI = P1^6; // IR sensor LED

sbit SW = P1^5; // Defining the switch pin

// Defining the motor control pins
sbit M1A = P2^0; // Motor 1 forward
sbit M1B = P2^1; // Motor 1 backward
sbit M2A = P2^2; // Motor 2 forward
sbit M2B = P2^3; // Motor 2 backward
sbit M3A = P1^0; // Motor 3 forward
sbit M3B = P1^1; // Motor 3 backward
sbit M4A = P1^2; // Motor 4 forward
sbit M4B = P1^3; // Motor 4 backward

// Defining the Ultrasonic sensor pins
sbit Trigger_pin1 = P2^4; // Trigger pin for sensor 1
sbit Echo_pin1 = P2^5;    // Echo pin for sensor 1
sbit Trigger_pin2 = P2^6; // Trigger pin for sensor 2
sbit Echo_pin2 = P2^7;    // Echo pin for sensor 2
sbit Trigger_pin3 = P0^6; // Trigger pin for sensor 3
sbit Echo_pin3 = P0^7;    // Echo pin for sensor 3

void Delay_us()
{
	TL0=0xF5; // Load the lower byte of the timer
	TH0=0xFF; // Load the higher byte of the timer
	TR0=1; // Start the timer
	while (TF0==0); // Wait until the timer overflows
	TR0=0; // Stop the timer
	TF0=0; // Clear the timer overflow flag
}

void init_timer(){
	TMOD=0x01; /* Initialize Timer 0 in mode 1 (16-bit timer mode) */
	TF0=0; // Clear the timer overflow flag
	TR0 = 0; // Stop the timer
}

void GoForward(void) // Function to drive the robot forward
{
    M1A = 0; // Motor 1 forward control OFF
    M1B = 1; // Motor 1 backward control ON
    M2A = 0; // Motor 2 forward control OFF
    M2B = 1; // Motor 2 backward control ON
    M3A = 0; // Motor 3 forward control OFF
    M3B = 1; // Motor 3 backward control ON
    M4A = 0; // Motor 4 forward control OFF
    M4B = 1; // Motor 4 backward control ON
}

void GoLeft(void) // Function to turn the robot to the left
{   
    M1A = 1; // Motor 1 forward control ON
    M1B = 0; // Motor 1 backward control OFF
    M2A = 1; // Motor 2 forward control ON
    M2B = 0; // Motor 2 backward control OFF
    M3A = 0; // Motor 3 forward control OFF
    M3B = 1; // Motor 3 backward control ON
    M4A = 0; // Motor 4 forward control OFF
    M4B = 1; // Motor 4 backward control ON
}

void GoRight(void) // Function to turn the robot to the right
{   
    M1A = 0; // Motor 1 forward control OFF
    M1B = 1; // Motor 1 backward control ON
    M2A = 0; // Motor 2 forward control OFF
    M2B = 1; // Motor 2 backward control ON
    M3A = 1; // Motor 3 forward control ON
    M3B = 0; // Motor 3 backward control OFF
    M4A = 1; // Motor 4 forward control ON
    M4B = 0; // Motor 4 backward control OFF
}

void Stop(void) // Function to stop the robot
{   
    M1A = 0; // Motor 1 forward control OFF
    M1B = 0; // Motor 1 backward control OFF
    M2A = 0; // Motor 2 forward control OFF
    M2B = 0; // Motor 2 backward control OFF
    M3A = 0; // Motor 3 forward control OFF
    M3B = 0; // Motor 3 backward control OFF
    M4A = 0; // Motor 4 forward control OFF
    M4B = 0; // Motor 4 backward control OFF
}

float measureDistance1() {
    float distance_measurement, value;
	
    init_timer();			/* Initialize Timer */
    Trigger_pin1= 1;           	/* Pull trigger pin HIGH */
	Delay_us();               	/* Provide 10uS Delay*/
	Trigger_pin1 = 0; 			/* Send trigger pulse of 10us */
    
    while(!Echo_pin1);           		/* Waiting for Echo */
    TR0 = 1;                    		/* Timer Starts */
    while(Echo_pin1 && !TF0);    		/* Waiting for Echo goes LOW */
    TR0 = 0;                    		/* Stop the timer */
	  
    /* calculate distance using timer */
    value = Clock_period * sound_velocity; 
    distance_measurement = (TL0|(TH0<<8));	/* Read timer register for time count */
    distance_measurement = (distance_measurement*value)/2.0;  /* Calculate distance(in cm) */
    
    return distance_measurement; // Return the calculated distance
}

/* Repeat the measureDistance1() function for the other two sensors */
float measureDistance2() {
    // Similar to measureDistance1() but with Trigger_pin2 and Echo_pin2
}

float measureDistance3() {
    // Similar to measureDistance1() but with Trigger_pin3 and Echo_pin3
}

void SoundControl(void)
{
for(;;){ // Infinite loop
float leftDistance,centerDistance,rightDistance ;	 

		  leftDistance = measureDistance1(); // Measure left distance
        centerDistance = measureDistance2(); // Measure center distance
                rightDistance = measureDistance3();    /* Measure right distance */
        
        if (centerDistance > 40 && leftDistance > 20 && rightDistance > 20) {
     		GoForward(); // If all distances are clear, go forward
   		 } else if (leftDistance > rightDistance && leftDistance > 20  ) {
    		   
    		     GoLeft(); // If left is clearer than right, go left
     		    
    		  }   else if (rightDistance>leftDistance  ) {
   	    
   	     GoRight(); // If right is clearer than left, go right
   	    
   	   	} else{
   	   	 // Both left and right have obstacles, so turn around
   	   	GoRight();Delay_us();Delay_us();Delay_us(); // Additional delay to make a complete turn around
   	   	}
   	   	}
}

void main() {	
	 	 
    ledS = 0; // Initialize Ultrasound  LED as OFF
    ledI = 0;  // Initialize IR LED as OFF
    SW = 1; // Initialize Switch as ON
     
    while(1) {   // Main infinite loop
    
    if(SW == 1){
    SoundControl(); // Call SoundControl function if switch is ON
    ledS = 1; // Turn on Ultrasound  LED
        	  }
         
         else
         {
	  ledI =1; // Turn on IR LED
          if(rightIR && leftIR) // If both IR sensors are activated
          {
          GoForward(); // Go forward
          }else if (!rightIR && leftIR) // If only left IR sensor is activated
          {
          GoLeft(); // Turn left
          }else if (rightIR  && !leftIR) { // If only right IR sensor is activated
          GoRight(); // Turn right
          }else{ // If none of the IR sensors are activated
          Stop(); // Stop
          }

		
        }
        }Delay_us(); // Delay before next iteration of the loop
    }


