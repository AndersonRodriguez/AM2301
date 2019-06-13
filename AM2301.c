/*
Funciones usadas para el funcionamiento del AM2301
Este sensor usa la logica del sensor DHT21
se puede modificar para funcionar por el DHT11 y el DH22
*/

#include "AM2301.h"                    //Importa las variables globales del archivo .h

// Definicion de variables globales 
short Time_out ;
unsigned int8 T_byte1, T_byte2, RH_byte1, RH_byte2, CheckSum ;
unsigned int16 Temp, RH;

// Esta funcion envia un pulso bajo de 1ms y alto de 20 us para 
//inicializar el sensor
void start_signal(){
  output_drive(DHT11_PIN);                            
  output_low(DHT11_PIN);                                             
  delay_ms(1);
  output_high(DHT11_PIN);                                                  
  delay_us(20);
  output_float(DHT11_PIN);                                 
}

//Esta funcion verifica que la comunicacion sea correcta entre el pic 
//el sensor, puede variar segun el sensor usado
short check_response(){
  delay_us(40);
  if(!input(DHT11_PIN)){                     
    delay_us(80);
    if(input(DHT11_PIN)){                    
      delay_us(50);
      return 1;}
    }
}

//Lee el dato de entrada del sensor 
unsigned int8 Read_Data(){
  unsigned int8 i, k, _data = 0;     
  if(Time_out)
    break;
  for(i = 0; i < 8; i++){
    k = 0;
    while(!input(DHT11_PIN)){                          
      k++;
      if (k > 100) {Time_out = 1; break;}
      delay_us(1);}
    delay_us(30);
    if(!input(DHT11_PIN))
      bit_clear(_data, (7 - i));               
    else{
      bit_set(_data, (7 - i));                 
      while(input(DHT11_PIN)){                         
      k++;
      if (k > 100) {Time_out = 1; break;}
      delay_us(1);}
    }
  }
  return _data;
}

//Funcion principal donde: se inicializa, se verifica la comunicacion
//y se decodifican los datos que son digitales.
//0. Para entrar al defauld donde se imprimen los datos 
//1. Error en la comunicacion un "Time out"
//2. No hay comunicacion con el sensor un "No response from the sensor"
//3. Error en la decodificacion de datos un "Checksum Error"
unsigned char get_data() {

   delay_ms(2000);
   Time_out = 0;
   Start_signal();                  // Inicializa el sensor para la lectura
   
   if(check_response()){            // Mira la comunicacion 
   
      //Inicio de lectura
      RH_byte1 = Read_Data();                
      RH_byte2 = Read_Data();                 
      T_byte1 = Read_Data();                  
      T_byte2 = Read_Data();    
      //Fin de lectura
      Checksum = Read_Data();       //Verifica el bit de paridad                
      if(Time_out){                 //Timeout                 
        return 1;
      }
      else{
         if(CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF)){
            RH = RH_byte1;
            RH = (RH << 8) | RH_byte2;
            Temp = T_byte1;
            Temp = (Temp << 8) | T_byte2;
            if (Temp > 0X8000){
               message1[6] = '-';
               Temp = Temp & 0X7FFF; 
            }
            else{
               message1[7] = (Temp / 100) % 10  + 48;
               message1[8] = (Temp / 10) % 10  + 48;
               message1[10] = Temp % 10  + 48;
               message2[7] = (RH / 100) % 10 + 48;
               message2[8] = (RH / 10) % 10 + 48;
               message2[10] = RH % 10 + 48;             
               return 0;                              //Impresion de los datos
            }
          }
          else {
            return 3;                                 //Error en los datos
          }
      }
    }
    else {
      return 2;                                       //No hay comunicacion
    }
}
