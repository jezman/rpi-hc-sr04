#define BEEP 27
#define TRIG_X 1
#define ECHO_X 3
#define TRIG_Y 0
#define ECHO_Y 2
#define TRIG_Z 4
#define ECHO_Z 5

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>


int buzzer() {
	pinMode(BEEP, OUTPUT);
	int timer = 200;
	while(timer != 0) {
      		digitalWrite(BEEP, HIGH);
      		delayMicroseconds(200);
      		digitalWrite(BEEP, LOW);
      		delayMicroseconds(200);
      		timer--;
	  }
return 0;
}

static int ping(TRIG, ECHO) {
	long ping      = 0;
	long pong      = 0;
	float distance = 0;
 	long timeout   = 500000; // 0.5 sec ~ 171 m
	
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	
	// Ensure trigger is low.
	digitalWrite(TRIG, LOW);
	delay(50);
	
	// Trigger the ping.
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10); 
	digitalWrite(TRIG, LOW);
	
	// Wait for ping response, or timeout.
	while (digitalRead(ECHO) == LOW && micros() < timeout) {
	}
	
	// Cancel on timeout.
	if (micros() > timeout) {
		printf("Out of range.\n");
		buzzer();
		return 0;
	}
	
	ping = micros();
	
	// Wait for pong response, or timeout.
	while (digitalRead(ECHO) == HIGH && micros() < timeout) {
	}
	
	// Cancel on timeout.
	if (micros() > timeout) {
		printf("Out of range.\n");
		buzzer();		
		return 0;
	}
	
	pong = micros();
	
	// Convert ping duration to distance.
	distance = (float) (pong - ping) * 0.017150;
	
	printf("Distance: %.2f cm.\n", distance);
	
	return 1;
}

int main (int argc, char *argv[]) {
	printf ("Raspberry Pi wiringPi HC-SR04 Sonar test program.\n");

	if (wiringPiSetup () == -1) {
		exit(EXIT_FAILURE);
	        buzzer();
        }
		
	if (setuid(getuid()) < 0) {
		perror("Dropping privileges failed.\n");
	        buzzer();
		exit(EXIT_FAILURE);
	}
	
	ping(TRIG_X, ECHO_X);
	ping(TRIG_Y, ECHO_Y);
	ping(TRIG_Z, ECHO_Z);
	buzzer();
	
	return 0;
}
