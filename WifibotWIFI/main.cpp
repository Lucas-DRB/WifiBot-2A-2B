#include <stdio.h>
#include <stdlib.h>

#include "WifibotClient.h"

#define SPEED 50
#define PORT	15020


int SharpLUT[]={150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,103,102,101,100,99,
          96,95,90,88,87,86,85,84,83,82,81,80,79,77,75,74,73,72,71,70,69,68,67,66,65,65,64,64,63,62,61,61,60,60,59,59,58,58,57,57,56,56,56,55,55,55,54,54,54,53,
          53,53,52,52,51,51,50,50,49,49,49,48,48,47,47,46,46,46,45,45,44,44,43,43,42,42,41,41,41,40,40,40,39,39,39,39,39,38,38,
                  38,38,37,37,37,37,36,36,36,36,35,35,35,35,34,34,34,34,34,34,33,33,33,33,32,32,32,32,32,31,31,31,31,30,30,30,30,30,30,30,
          30,29,29,29,29,29,29,29,28,28,28,28,28,28,27,27,27,27,27,27,27,26,26,26,26,25,25,25,25,25,25,24,24,24,24,24,23,23,23,
          23,23,23,22,22,22,22,22,21,21,21,21,21,21,20,20,20,20,19,19,19,19,19,19,18,18,18,18,18,18,17,17,17,16,16,15,15};

void main(void)
{

	WifibotClient robot;

	/*.........................*/
	/* Connection to the robot */
	/*.........................*/

	char ip_adr[50] = "10.3.141.1";

	printf("Trying to connect to %s...\n", ip_adr);
	bool rep = robot.ConnectToRobot(ip_adr, PORT);
	if( rep )
	{
		printf("Connection failed...\n");
		getchar();
		return;
	}
	else
	{
		printf("Connection established...\n");
	}


	/*..............*/
	/* Main program */
	/*..............*/
	
	SensorData sensors_data;

	while (1)
	{
		unsigned char flags = 128 + 32 + 64 + 16 + 1;
		robot.GetSensorData(&sensors_data);	//Get every sensor data from robot for loop init
		system("CLS");
		printf("IR Left  : %d cm\n", SharpLUT[sensors_data.IRLeft]);
		printf("IR Right : %d cm\n", SharpLUT[sensors_data.IRRight]);
		printf("Battery : %d \n", sensors_data.BatVoltage);
		Sleep(50);
		robot.Avancer(0, 0);	//1st command is mandatory to be able to read data again + is iddle state for bot
		
		//while no obstacle in range of IR threshold
		while ((robot.FiltrageCapteurIR_Left(SharpLUT[sensors_data.IRLeft]) > 35) && (robot.FiltrageCapteurIR_Right(SharpLUT[sensors_data.IRRight]) > 35))
		{
			
			robot.GetSensorData(&sensors_data);	//Get every sensor data from robot
			robot.Avancer(SPEED, SPEED);
			system("CLS");
			printf("IR Left  : %d cm\n", robot.FiltrageCapteurIR_Left(SharpLUT[sensors_data.IRLeft]));
			printf("IR Right : %d cm\n", robot.FiltrageCapteurIR_Right(SharpLUT[sensors_data.IRRight]));
			printf("Battery : %d \n", sensors_data.BatVoltage);
			Sleep(50);
			
		}
	}	
}

