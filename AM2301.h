/*
Variables Usadas en el sensor AM2301
Usa el pin C0 como comunicacion, si se quiere cambiar se pone el pin en la definicion
se imprime en dos variables donde solo se  modifica el dato para mostrar en pantalla.
Este programa esta diseñado para un cristal de 4MHz

Para usar esta importacion se usa 
#include "AM2301.c"

void main()
{
   unsigned char state = 0;
   WHILE (TRUE)
   {
      state = get_data ();
      
      SWITCH (state)
      {
         CASE 1:
         {
            //Time out!
            break;
         }

         CASE 2:
         {
            //No response from the sensor
            break;
         }

         CASE 3:
         {
            //Checksum Error!
            break;
         }

         DEFAULT:
         {
            // imprimir message1 y message2
            break;
         }
      }

      delay_ms (1000);
   }
}


*/

#define DHT11_PIN PIN_C0                     // Pin de comunicacion

char message1[] = "Temp = 00.0 C  ";         // Dato de temperatura
char message2[] = "RH   = 00.0 %  ";         // Dato de humedad

unsigned char get_data();                    // Funcion de lectura
