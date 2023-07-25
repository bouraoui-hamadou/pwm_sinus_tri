

/*
 * main.c
 *
 *  Created on: 2023 Mar 13 14:29:51
 *  Author: rybsk
 */



#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "lcd-routines.h"
#include "math.h" 			// for sin and pi

/*

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
// create sin table from 0 to 2pi,  0 to 4096-1 values -> good enought?
double sin_table[256];
double U_1;
double f_1;
double f_diff;
uint16_t led_freq;
uint8_t x = 0;
uint8_t y = 1;
uint32_t time;
double time_sample;
XMC_VADC_RESULT_SIZE_t result;
double U_u;
double U_v;
double U_w;
char str_dc[15] = "DC-Bremsen    ";
char str_cl[15] = "Beschleunigung";
char str_aus[15] = "Stop/Auslaufen";
char str_wechsel[15] = "Drehwechsel   ";
char str_dreh[9] = "   Dreh:";
char str_p[4] = "(+)";
char str_m[4] = "(-)";
uint8_t index_count_1 = 0;
uint8_t index_count_2 = 171;
uint8_t index_count_3 = 85;

double f_aktuell = 0;

double U_N = 120;
double f_N = 50;
char str2[6];
char str4[7] = {"   f:"};
char str5[5];
char str6[4] = {" / "};
char str7[5];

// Variable für die PinInterrupts
  bool pin_status1 = false; // Abschalten
  bool pin_status2 = false; // DC_Bremsen
  uint32_t d = 5000;
  uint32_t f = 1000;
  uint32_t d1 = 5000;
  uint32_t d2 = 5000;
  uint32_t d3 = 5000;
  uint32_t d2_DC = 8500; //24/60
  uint32_t d3_DC = 8500;

  bool pin_status_bremsen = false;
  bool current_index_status = false;

void write_display()
{
	 char str1[40] = {"U:"};
	 snprintf(str2, 6,"%f", U_1);
	 strcat(str1,str2);


	 snprintf(str5, 5, "%f", f_1);
	 snprintf(str7, 5, "%f", f_aktuell);
	 strcat(str1,str4);
	 strcat(str1,str7);
	 strcat(str1,str6);
	 strcat(str1,str5);
	 strcat(str1,str_dreh);
	 if(!current_index_status)
	 {
		 strcat(str1,str_p);
	 }
	 else
	 {
		 strcat(str1,str_m);
	 }

	 //strcat(str1,str5);

	 lcd_home(); // cursor in die 1. Zeile
	 lcd_string(str1);

}
void change_frequency()
{
	 f_diff = f_aktuell-f_1;
	 if ((f_diff >= -1) && (f_diff <= 1))
	 {
		 time_sample = 1/f_1 * 1000000 * 100; // frequenz vom sinus * anzahl an werte
		 time_sample = time_sample/256;
		 f_aktuell = f_1;
	 }
	 else
	 {
		if(f_diff > 0)
		{
			f_aktuell = f_aktuell - 1;
		}
		else 	// (f_diff < 0)
		{
			f_aktuell = f_aktuell + 1;
		}
		time_sample = (1/f_aktuell) * 1000000 * 100; // wenn frequenz änderung zu hoch ist wird nur um 1Hz erhöht 1/(f*1)*100*0.0000001*anzahl_sin_werte
		time_sample = time_sample/256;
	  }
	  TIMER_Stop(&TIMER_1);
	  TIMER_SetTimeInterval(&TIMER_1, (uint32_t) time_sample);
	  TIMER_Start(&TIMER_1);

	  if(pin_status_bremsen && f_1 == f_aktuell)
	  {
		  //TIMER_Stop(&TIMER_0);
		  current_index_status = !current_index_status;
		  if(current_index_status)
		  {
			  index_count_2 = index_count_2 - 86;
			  index_count_3 = index_count_3 + 86;
		  }
		  else
		  {
			  index_count_2 = index_count_2 + 86;
			  index_count_3 = index_count_3 - 86;
		  }
		  pin_status_bremsen = false;
		  //Timer_Start(&TIMER_0);
	  }

	  if (f_aktuell < 50)
	  {
	  	U_1 = (U_N*0.9/50)*(f_aktuell) + U_N*0.1;
	  }
	  else
	  {
		U_1 = 120;
	  }

	  //write_display();
}

void Adc_Measurement_Handler()
{
#if(UC_SERIES != XMC11)

  result = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_A);
#else
  result = ADC_MEASUREMENT_GetGlobalResult();
#endif
  	 //result = 100;
  	 if(pin_status1)
  	 {
  		 f_1 = (99.5/1024) * result + 0.5;  // frequenz start bei 0.5Hz
  	 }
  	 else
  	 {
  		 f_1 = 0.5;
  	 }

  	 if(pin_status_bremsen)
  	 {
  		 f_1 = 0.5;
  	 }
     change_frequency();
}

double p1 = 0;
double p2 = 0;
double p3 = 0;

void sinus_dreieck_vergleich()
{
	p1 = ((U_u*U_1)/120 + 1)*10000/2;
	p2 = ((U_v*U_1)/120 + 1)*10000/2;
	p3 = ((U_w*U_1)/120 + 1)*10000/2;

	//PWM_CCU8_STATUS(&PWM_CCU8_0);

	//DC_Bremsen
	  if (!pin_status2)
	  {
		  // ganz normaler Betrieb
		PWM_CCU8_SetDutyCycleSymmetric(&PWM_CCU8_0, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, (uint32_t) p1);
		PWM_CCU8_SetDutyCycleSymmetric(&PWM_CCU8_1, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, (uint32_t) p2);
		PWM_CCU8_SetDutyCycleSymmetric(&PWM_CCU8_2, XMC_CCU8_SLICE_COMPARE_CHANNEL_1, (uint32_t) p3);
		 /* PWM_CCU8_Start(&PWM_CCU8_0);
		  PWM_CCU8_SetFreqAndDutyCycleSymmetric(&PWM_CCU8_0, f, d1,0);
		  PWM_CCU8_Start(&PWM_CCU8_1);
		  PWM_CCU8_SetFreqAndDutyCycleSymmetric(&PWM_CCU8_1, f, d2,0);
		  PWM_CCU8_Start(&PWM_CCU8_2);
		  PWM_CCU8_SetFreqAndDutyCycleSymmetric(&PWM_CCU8_2, f, d3,0);
		  */
	  }
	  else
	  {
		//DC_Bremsen
		  //PWM_Start(&PWM_CCU8_0);
		  PWM_CCU8_SetFreqAndDutyCycleSymmetric(&PWM_CCU8_0, f, 10000,0);
		  //PWM_Start(&PWM_CCU8_1);
		  PWM_CCU8_SetFreqAndDutyCycleSymmetric(&PWM_CCU8_1, f, d2_DC,0);
		 // PWM_Start(&PWM_CCU8_2);
		  PWM_CCU8_SetFreqAndDutyCycleSymmetric(&PWM_CCU8_2, f, d3_DC,0);

		  f_aktuell = 0;

	  }



	/*PWM_CCU8_Start(&PWM_CCU8_0);
	PWM_CCU8_Start(&PWM_CCU8_1);
	PWM_CCU8_Start(&PWM_CCU8_2);
*/
}


void find_3phase_index()
{
	index_count_1++;
	index_count_2++;
	index_count_3++;

	// bool status = PIN_INTERRUPT_STATUS(&PIN_INTERRUPT_0);
	// if(taster1 == 1)
	U_u = sin_table[index_count_1];
	U_v = sin_table[index_count_2]; // aufrunden oder abrunden ?
	U_w = sin_table[index_count_3];
	// else {U_v = sin_table[index_count_1];
	//U_u = sin_table[index_count_2]; // aufrunden oder abrunden ?
	//U_w = sin_table[index_count_3];}
	sinus_dreieck_vergleich();
}
//bool current_status = false;
void start()
{
	 pin_status1=!pin_status1;
	 if(pin_status1)
	 {
		 lcd_setcursor(0,2);
		 lcd_string(str_cl);
		 TIMER_Start(&TIMER_0);
		 TIMER_Start(&TIMER_1);
		 PWM_CCU8_Start(&PWM_CCU8_0);
		 PWM_CCU8_Start(&PWM_CCU8_1);
		 PWM_CCU8_Start(&PWM_CCU8_2);
	 }
	 else
	 {
	     lcd_setcursor(0,2);
		 lcd_string(str_aus);
		 PWM_CCU8_Stop(&PWM_CCU8_0);
		 PWM_CCU8_Stop(&PWM_CCU8_1);
		 PWM_CCU8_Stop(&PWM_CCU8_2);
		 TIMER_Stop(&TIMER_1);
		 TIMER_Stop(&TIMER_0);
		 delay_ms(70000000);
		 f_aktuell = 0;
	 }
}

void DC_Bremsen (void)
{
	pin_status2=!pin_status2;
	TIMER_Stop(&TIMER_1);
	TIMER_Stop(&TIMER_0);
	if(pin_status2)
	{
		sinus_dreieck_vergleich();
		lcd_setcursor(0,2);
		lcd_string(str_dc);
		delay_ms(50000000);
	}
	else
	{
		lcd_setcursor(0,2);
		lcd_string(str_cl);
		TIMER_Start(&TIMER_0);
		TIMER_Start(&TIMER_1);
	}
}

void PWM_Drehrichtung()
{
	pin_status_bremsen =!pin_status_bremsen;
	lcd_setcursor(0,2);
	lcd_string(str_wechsel);
}


int main(void)
{
	// create values for sin_table
	for (int i = 0; i<=255; i++)
	  {
	    sin_table[i] = sin(2*M_PI/255 * i);
	  }
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if (status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }
  //bool status_Brems_ADC;
 // status_Brems_ADC = PWM_CCU4_GetInterruptStatus(&PWM_CCU4_0,XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);


  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  //led_freq = 20;
  //CLOCK_XMC4_Init();

  //time = PWM_CCU4_GetTimerValue(&PWM_CCU4_0);
	 // PWM_SetFreq(&PWM_0,led_freq);

  lcd_init(); // erste haupt initialisierung
  lcd_clear();

  //TIMER_Start(&TIMER_0);

  //time = PWM_CCU4_GetTimerValue(&PWM_CCU4_0);
  //while(1U)
  // {
	//  result = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_A);
  // }
  // Calculate components

  //double U_1 = 70;
  // ab 20 hz R = 0?


  ADC_MEASUREMENT_StartConversion(&ADC_MEASUREMENT_0);

  //double f_1 = sqrt((U_1*f_N/U_N)*(U_1*f_N/U_N)); // R abouve 20Hz is 0  - (R_1*f_N)/X_1
 // double f_2 = sqrt((U_1*f_N/U_N)*(U_1*f_N/U_N)- (R_1*f_N)/X_1); // R abouve 20Hz is 0  - (R_1*f_N)/X_1

  //DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1); // test led
 // PWM_Start(&PWM_0);
  while(1U)
  {

	  	  //timer 1 (ccu4) for checking ADC changes every 100ms, interrupt ?
	  	  //

	     // DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1); // test led
		  //lcd_clear();
		  //result = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_A);
		  //lcd_home(); // cursor in die 1. Zeile
		  //const char str1[] = "Hello World!";
		  //lcd_string(str1);
		  //snprintf(str, sizeof str, "%lu", (unsigned long)n); /* Method 1 */
		 //DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		  //delay_ms(50000000);
		  //char result[];
		  //ADC_MEASUREMENT_StartConversion(&ADC_MEASUREMENT_0);

		  //Adc_Measurement_Handler();
		  //time = PWM_CCU4_GetTimerValue(&PWM_CCU4_0);
	  	  write_display();

		  /*status_Brems_ADC = PWM_CCU4_GetInterruptStatus(&PWM_CCU4_0,XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH); // check if 10hz are over 100ms (Bremsen Interrup und adc lesen)
		  if (status_Brems_ADC == true)
		  {
			  //delay_ms(50000000);
			  //PWM_Stop(&PWM_0);
			  //DIGITAL_IO_SetOutputLow(&DIGITAL_IO_1);
			  PWM_CCU4_ClearTrap(&PWM_CCU4_0); // setzt Brems und ADC status als gecheckt und lässt neue 100ms laufen

			  ADC_MEASUREMENT_StartConversion(&ADC_MEASUREMENT_0); // schaue nach was adc ausgibt
			  Adc_Measurement_Handler(); // rufe handler für display auf der display refreshed
			  //DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1);
			  //PWM_Start(&PWM_0);
		  }
	  	  */
		  /*x = 11;
		  y = 2;

		  char str2[] = "  ";
		  snprintf(str2, sizeof str2, "%lu", (unsigned long)result); // Method 1
		  lcd_setcursor(x,y);
		  lcd_string(result);
		  lcd_clear();
		  */
		  //DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);

	  /*

	   if()
	   {
	   	   f_1 = 0;
	   	   i
	   }
	   */

  }
}
