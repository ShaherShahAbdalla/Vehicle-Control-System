/*******************************************************************************************/
/*******************************************************************************************/
/*	Project Name:	Mini Project 1_C Programming	****************************************/
/*	Author		:	Shaher Shah Abdalla Kamal		****************************************/
/*	Date		:	11 / 08 / 2023					****************************************/
/*******************************************************************************************/

#include <stdio.h>

/*	Determine whether to activate any function or data related to the "Engine Temperature Controller */
/*	You could put its value either as 1 or 0 */
/*	1 enable anything related to the engine temperature controller and 0 disable them*/
#define	WITH_ENGINE_TEMP_CONTROLLER		1


#define ON								1
#define	OFF								0

/********************************		Global Variables	********************************/
char main_action, set_menu_action, traffic_light_sensor;
char engine_state = ON;
char AC_state = OFF;
int vehicle_speed;
float room_temp = 25;
#if WITH_ENGINE_TEMP_CONTROLLER
	char engine_temp_controller_state = OFF;
	float engine_temp = 110;
#endif

char Turn_on_no_matter_what = 0;

/*******************************************	Function Declarations	*******************************************/
void what_to_do(void);
void sensors_set_menu(void);
void set_traffic_light(void);
void set_room_temp(void);
#if WITH_ENGINE_TEMP_CONTROLLER
void set_engine_temp(void);
#endif
void print_vehicle_state(void);

/***************************************		main Function		***************************************/
int main ()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	what_to_do();

	/* If the user turned the engine off Ask him again what does he/she want */
	while (main_action == 'b')
	{
		what_to_do();
	}
	if (main_action == 'c')
	{
		return 0;
	}

	/* If the user turned the engine off then decided to turn it off, Ask him again what does he/she want */
	if (set_menu_action == 'a' && main_action == 'b')
	{
		while (main_action == 'b')
			{
				what_to_do();
			}
		if (main_action == 'c')
			{
				return 0;
			}
	}
}

/*******************************************	Function Definitions	*******************************************/

/********************************	"Primary menu"	********************************/
void what_to_do(void)
{
	printf("a: Turn on the vehicle engine\n");
	printf("b: Turn off the vehicle engine\n");
	printf("c: Quit the system\n\n");
	scanf(" %c",&main_action);
	switch (main_action)
	{
	case 'a':
		printf("Engine starts...\n");
		sensors_set_menu();
		break;
	case 'b':
		printf("Engine is turned off\n");
		break;
	case 'c':
		printf("Quitting the system...\n");
		return;
	default:
		printf("Wrong input\nPlease enter 'a' or 'b' or 'c' :)\n");
		what_to_do();
	}
}

/********************************	"Secondary Menu"	********************************/
void sensors_set_menu(void)
{
	printf("a: Turn off the engine\n");
	printf("b: Set the traffic light color\n");
	printf("c: Set the room temperature\n");
#if WITH_ENGINE_TEMP_CONTROLLER
	printf("d: Set the engine temperature\n\n");
#endif
	scanf(" %c",&set_menu_action);
	switch (set_menu_action)
	{
	case 'a':
		printf("Engine is turned off\n");
		what_to_do();
		break;
	case 'b':
		printf("Setting the traffic light\n");
		set_traffic_light();
		break;
	case 'c':
		printf("Setting the room temperature\n");
		Turn_on_no_matter_what = 1;
		set_room_temp();
		break;
	case 'd':
#if WITH_ENGINE_TEMP_CONTROLLER
		printf("Setting the engine temperature\n");
		Turn_on_no_matter_what = 1;
		set_engine_temp();
#endif
		break;
	default:
#if WITH_ENGINE_TEMP_CONTROLLER
		printf("Wrong input\nPlease enter 'a' or 'b' or 'c' or 'd':)\n\n");
		sensors_set_menu();
#else
		printf("Wrong input\nPlease enter 'a' or 'b' or 'c' :)\n\n");
		sensors_set_menu();
#endif
	}
}

/********************************	"Setting the speed according to input of Light sensor"	********************************/
void set_traffic_light(void)
{
	printf("G: Set the vehicle speed to 100 km/hr\n");
	printf("O: Set the vehicle speed to 30 km/hr\n");
	printf("R: Set the vehicle speed to 0 km/hr\n");
	scanf(" %c",&traffic_light_sensor);
	switch(traffic_light_sensor)
	{
	case 'G':
		vehicle_speed = 100;
		break;
	case 'O':
		vehicle_speed = 30;
		Turn_on_no_matter_what = 0;
		set_room_temp();
#if WITH_ENGINE_TEMP_CONTROLLER
		set_engine_temp();
#endif
		break;
	case 'R':
		vehicle_speed = 0;
		break;
	default:
		printf("Wrong input\nPlease enter 'G' or 'O' or 'R' :)\n\n");
		set_traffic_light();
	}
	print_vehicle_state();
	sensors_set_menu();
}

/********************************	"Turning on AC"	********************************/
void set_room_temp(void)
{
	if (Turn_on_no_matter_what == 1)
	{
		printf("Enter the room temperature\n");
		scanf("%f",&room_temp);
		if (room_temp < 10 || room_temp > 30)
		{
			AC_state = ON;
			room_temp = 20;
		}
		else
		{
			AC_state = OFF;
		}
		print_vehicle_state();
		sensors_set_menu();
	}
	else
	{
		if (AC_state == OFF)
		{
			AC_state = ON;
			room_temp = room_temp * (1.25) + 1;
		}
		else
		{
			room_temp = room_temp * (1.25) + 1;
		}
	}
	Turn_on_no_matter_what = 0;
}

/********************************	"Turning on Engine Temperature Controller"	********************************/
#if WITH_ENGINE_TEMP_CONTROLLER
void set_engine_temp(void)
{
	if (Turn_on_no_matter_what == 1)
	{
		printf("Enter the engine temperature\n");
		scanf("%f",&engine_temp);
		if (engine_temp < 100 || engine_temp > 150)
		{
			engine_temp_controller_state = ON;
			engine_temp = 125;
		}
		else
		{
			engine_temp_controller_state = OFF;
		}
		print_vehicle_state();
		sensors_set_menu();
	}
	else
	{
		if (engine_temp_controller_state == OFF)
		{
			engine_temp_controller_state = ON;
			engine_temp = engine_temp * (1.25) + 1;
		}
		else
		{
			engine_temp = engine_temp * (1.25) + 1;
		}
	}
	Turn_on_no_matter_what = 0;
}
#endif

/********************************	"Printing Vehicle States"	********************************/
void print_vehicle_state(void)
{
	printf("\nEngine state: ON\n");
	if (AC_state)
	{
		printf("AC state: ON\n");
	}
	else
	{
		printf("AC state: OFF\n");
	}
	printf("Vehicle speed: %d\n", vehicle_speed);
	printf("Room temperature: %f\n", room_temp);
#if WITH_ENGINE_TEMP_CONTROLLER
	if (engine_temp_controller_state)
	{
		printf("Engine temperature controller state: ON\n");
	}
	else
	{
		printf("Engine temperature controller state: OFF\n");
	}
	printf("Engine temperature: %f\n",engine_temp);
#endif
}
