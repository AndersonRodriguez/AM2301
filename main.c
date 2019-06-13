#include <18f4550.h>
#device adc=10
#include <string.h>
#use delay(crystal=4MHz)

#fuses XT
#fuses NOPROTECT
#fuses NOPUT
#fuses NOWDT
#fuses MCLR

#include "LCD.h"        //Importa Los pines y la libreria de la ldc
#include "AM2301.c"     //Importa uso de AM2301

// Programa principal
void main()
{
   unsigned char state = 0;
   lcd_init ();
   lcd_putc ('\f');
   WHILE (TRUE)
   {
      state = get_data ();
      
      SWITCH (state)
      {
         CASE 1:
         {
            lcd_putc ('\f');
            lcd_gotoxy (5, 1);
            lcd_putc ("Time out ! ");
            break;
         }

         CASE 2:
         {
            lcd_putc('\f');                              
            lcd_gotoxy(3, 1);                             
            lcd_putc("No response");
            lcd_gotoxy(1, 2);                              
            lcd_putc("from the sensor");
            break;
         }

         CASE 3:
         {
            lcd_putc('\f');                       
            lcd_gotoxy(1, 1);                          
            lcd_putc("Checksum Error!");
            break;
         }

         DEFAULT:
         {
            lcd_gotoxy (1, 1);
            printf (lcd_putc, message1);
            lcd_gotoxy (1, 2);
            printf (lcd_putc, message2);
            break;
         }
      }

      delay_ms (1000);
   }
}

