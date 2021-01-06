/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_TOUCH_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/
#include "GUI.h"
//#include "GUI_X.h"
#include "main.h"
#include "stdio.h"

extern SPI_HandleTypeDef hspi3;

unsigned char SPI3_WriteByte(unsigned char data);
unsigned short TPReadX(void);
unsigned short TPReadY(void);

unsigned char SPI3_WriteByte(unsigned char data) 
{ 
	unsigned char Data = 0; 
	HAL_SPI_Transmit(&hspi3,&data,1,3000);
	//HAL_SPI_Receive(&hspi3,&Data,1,3000);
  	return Data; 													 // Return the shifted data 	 
}


void SpiDelay(unsigned int DelayCnt)
{
 	unsigned int i;
 	for(i=0;i<DelayCnt;i++);
}

unsigned short TPReadX(void)
{ 
   unsigned short x=0;
   unsigned char data[2];
   TP_CS();
   SpiDelay(10);
   SPI3_WriteByte(0xd0);
   SpiDelay(10);
   HAL_SPI_Receive(&hspi3,data,2,3000);
   TP_DCS(); 
   x = data[0];
   x = (x << 8) + data[1];
   x = x >> 3;
   return (x);
}

unsigned short TPReadY(void)
{
 	unsigned short y=0;
	unsigned char data[2];
  	TP_CS();
  	SpiDelay(10);
	SPI3_WriteByte(0x90);
	SpiDelay(10);
	HAL_SPI_Receive(&hspi3,data,2,3000);
	TP_DCS();
	y = data[0];
	y = (y << 8) + data[1]; 
	y = y >> 3;
	return (y);
}


void GUI_TOUCH_X_ActivateX(void) 
{
}

void GUI_TOUCH_X_ActivateY(void) 
{
}

int  GUI_TOUCH_X_MeasureX(void) 
{
	unsigned char t=0,t1,count=0;
	unsigned short int databuffer[10]={5,7,9,3,2,6,4,0,3,1};
	unsigned short temp=0,X=0;	
 	
	while(count<10)
	{	   	  
		databuffer[count]=TPReadX();
		count++; 
	}       
	if(count==10)
	{  
	    do  
		{	
			t1=0;		  
			for(t=0;t<count-1;t++)
			{
				if(databuffer[t]>databuffer[t+1])
				{
					temp=databuffer[t+1];
					databuffer[t+1]=databuffer[t];
					databuffer[t]=temp;
					t1=1; 
				}  
			}
		}while(t1); 	    		 	 		  
		X=(databuffer[3]+databuffer[4]+databuffer[5])/3;	  
	} 	  
	return(X);  
}

int  GUI_TOUCH_X_MeasureY(void) 
{
  	unsigned char t=0,t1,count=0;
	unsigned short int databuffer[10]={5,7,9,3,2,6,4,0,3,1};//������
	unsigned short temp=0,Y=0;	
 
    while(count<10)	
	{	   	  
		databuffer[count]=TPReadY();
		count++;  
	}  
	if(count==10)
	{  
	    do
		{	
			t1=0;		  
			for(t=0;t<count-1;t++)
			{
				if(databuffer[t]>databuffer[t+1])
				{
					temp=databuffer[t+1];
					databuffer[t+1]=databuffer[t];
					databuffer[t]=temp;
					t1=1; 
				}  
			}
		}while(t1); 
	    		 	 		  
		Y=(databuffer[3]+databuffer[4]+databuffer[5])/3;
			  
	}
	return(Y); 
}  
