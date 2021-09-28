#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL

#define RS232 Serial1
#define RS232Baud 11500

void RS232Setup();
void userDataToController();
void readRS232();
void setCurrentLimit();
void readMotorStats();

#endif