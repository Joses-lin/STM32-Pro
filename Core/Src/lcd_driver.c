#include "main.h"
#include "lcd_driver.h"

uint16_t DeviceCode= 0; //0x9328;

 
static void delay(uint32_t nCount)
{
  volatile uint32_t index = 0; 
  for(index = (100000 * nCount); index != 0; index--)
  {
  }
}

static void Lcd_Shortdelay(void)
{
  volatile uint32_t index = 0; 
  for(index = 10; index != 0; index--)
  {
  }
}



/*******************************************************************************
* Function Name  : LCD_DB_AS_InPut
* Description    : config MCU LCD_DB pins AS InPut
* Input          : None
* Output         : None
* Return         : None.
*******************************************************************************/
void LCD_DB_AS_InPut(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // DB15--0
  GPIO_InitStruct.Pin = GPIO_PIN_All;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

/*******************************************************************************
* Function Name  : LCD_DB_AS_OutPut
* Description    : config MCU LCD_DB pins AS OutPut
* Input          : None
* Output         : None
* Return         : None.
*******************************************************************************/
void LCD_DB_AS_OutPut(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // DB15--0
  GPIO_InitStruct.Pin = GPIO_PIN_All;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

/**
  * @brief  Prepare to write to the LCD RAM.
  * @param  None
  * @retval None
  */
void LCD_WriteRAM_Prepare(void)
{
  /* Write 16-bit Index, then Write Reg */
  Clr_Cs
  Clr_Rs
  Clr_nWr
  LCD_Write(0x22);
  Set_nWr
  Set_Rs
}

/**
  * @brief  Writes to the LCD RAM.
  * @param  RGB_Code: the pixel color in RGB mode (5-6-5).
  * @retval None
  */
void LCD_WriteRAM(uint16_t RGB_Code)
{
  Clr_nWr
  LCD_Write(RGB_Code);
  Set_nWr
}

/**
  * @brief  Sets the cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position. 
  * @retval None
  */
void LCD_SetCursor(uint8_t Xpos, uint16_t Ypos)
{
	if(DeviceCode==0x8989)
	{
	 	ili9320_WriteRegister(0x004e,Xpos);        //ÐÐ
    	ili9320_WriteRegister(0x004f,Ypos);  //ÁÐ
	}
	else if((DeviceCode==0x9320))
	{
  		ili9320_WriteRegister(0x0020,Xpos); // ÐÐ
  		ili9320_WriteRegister(0x0021,0x13f-Ypos); // ÁÐ
	}
	else if((DeviceCode==0x9919))
	{
		ili9320_WriteRegister(0x004e,Xpos); // ÐÐ
  		ili9320_WriteRegister(0x004f,Ypos); // ÁÐ	
	}
	else
	{
  		ili9320_WriteRegister(0x0020,Ypos); // ÐÐ
  		ili9320_WriteRegister(0x0021,0x13f-Xpos); // ÁÐ
	}
}

/**
  * @brief  Draws a chinacharacter on LCD.
  * @param  Xpos: the Line where to display the character shape.
  * @param  Ypos: start column address.
  * @param  c: pointer to the character data.
  * @retval None
  */
void LCD_DrawChinaChar(u8 Xpos, u16 Ypos, const u8 *c)
{
  u32 index = 0, i = 0, j = 0;
  u8 Xaddress = 0;
   
  Xaddress = Xpos;
  
  //ili9320_SetCursor(Xaddress, Ypos);
  ili9320_SetCursor(Ypos, Xaddress);

  for(index = 0; index < 24; index++)
  {
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    for(j = 0; j < 3; j++)
    {
        for(i = 0; i < 8; i++)
        {
          if((c[3*index + j] & (0x80 >> i)) == 0x00)
          {
              LCD_WriteRAM(0xF800);
          }
          else
          {
            LCD_WriteRAM(0xFFE0);
          }
        }   
     }
    Set_Cs
    Xaddress++;
    //LCD_SetCursor(Xaddress, Ypos);
    ili9320_SetCursor(Ypos, Xaddress);
  }
}

void LCD_DisplayWelcomeStr(u8 Line)
{
  // u16 num = 0;

  // /* Send the string character by character on LCD */
  // for(num=0; num<13; num++)
  // {
  //   /* Display one China character on LCD */
  //   LCD_DrawChinaChar(Line, num*24+4, (u8 *)WelcomeStr[num]);
  // }
}

/****************************************************************************
* Ãû    ³Æ£ºvoid ili9320_Initializtion()
* ¹¦    ÄÜ£º³õÊ¼»¯ ILI9320 ¿ØÖÆÆ÷
* Èë¿Ú²ÎÊý£ºÎÞ
* ³ö¿Ú²ÎÊý£ºÎÞ
* Ëµ    Ã÷£º
* µ÷ÓÃ·½·¨£ºili9320_Initializtion();
****************************************************************************/
void ili9320_Initializtion()
{ 
  
  delay(1); /* delay 50 ms */
  ili9320_WriteRegister(0x0000,0x0001);          //start internal osc
  delay(1); /* delay 50 ms */			
  LCD_DB_AS_InPut();
  delay(1); /* delay 50 ms */
  DeviceCode = ili9320_ReadRegister(0x0000);
  if(( 0 == DeviceCode) || (1 == DeviceCode))
  {
  	DeviceCode = ili9320_ReadRegister(0x0000);
  }
  //printf("\n\r ###### www.armjishu.com DeviceCode = 0x%x ###### ", DeviceCode);
  //printf("\n\r ###### DeviceCode = LCD_ReadReg(0x0000) = 0x%x ###### ", LCD_ReadReg(0x0000));
  //printf("\n\r ###### DeviceCode = LCD_ReadSta(0x0000) = 0x%x ###### ", LCD_ReadSta());
//
//  Devicestr[15] = ((DeviceCode >> 12) & 0xF) + 0x30;
//  Devicestr[16] = ((DeviceCode >> 8) & 0xF) + 0x30;
//  Devicestr[17] = ((DeviceCode >> 4) & 0xF) + 0x30;
//  Devicestr[18] = ((DeviceCode >> 0) & 0xF) + 0x30;
  
  LCD_DB_AS_OutPut();
  delay(1); /* delay 50 ms */			//start internal osc

  if(DeviceCode == 0)
  {
    DeviceCode = 0x9320;
  }

  if(DeviceCode == 0x8989)
  {
      // printf("\n\r This LCD is SSD1289 ");
  }
 
  if(DeviceCode == 0x9325)
  {
      // printf("\n\r This LCD is ili9325 ");
  }
  
	if(DeviceCode==0x9325||DeviceCode==0x9328)
	{
    	ili9320_WriteRegister(0x00e3,0x3008);
    	ili9320_WriteRegister(0x00e7,0x0012);
    	ili9320_WriteRegister(0x00ef,0x1231);//Set the internal vcore voltage
        // ili9320_WriteRegister(0x00e7,0x0010);      
        ili9320_WriteRegister(0x0000,0x0001);  			//start internal osc
        ili9320_WriteRegister(0x0001,0x0100);     
        ili9320_WriteRegister(0x0002,0x0700); 				//power on sequence                     
        ili9320_WriteRegister(0x0003,(1<<12)|(1<<5)|(1<<4) ); 	//65K 
        ili9320_WriteRegister(0x0004,0x0000);                                   
        ili9320_WriteRegister(0x0008,0x0207);	           
        ili9320_WriteRegister(0x0009,0x0000);         
        ili9320_WriteRegister(0x000a,0x0000); 				//display setting         
        ili9320_WriteRegister(0x000c,0x0001);				//display setting          
        ili9320_WriteRegister(0x000d,0x0000); 				//0f3c          
        ili9320_WriteRegister(0x000f,0x0000);
        //Power On sequence //
        ili9320_WriteRegister(0x0010,0x0000);   
        ili9320_WriteRegister(0x0011,0x0007);
        ili9320_WriteRegister(0x0012,0x0000);                                                                 
        ili9320_WriteRegister(0x0013,0x0000);                 
        delay(5);
		delay(5);
        ili9320_WriteRegister(0x0010,0x1590);   
        ili9320_WriteRegister(0x0011,0x0227);
        delay(5);
		delay(5);
        ili9320_WriteRegister(0x0012,0x009c);                  
        delay(5);
		delay(5);
        ili9320_WriteRegister(0x0013,0x1900);   
        ili9320_WriteRegister(0x0029,0x0023);
        ili9320_WriteRegister(0x002b,0x000e);
        delay(5);
		delay(5);
        ili9320_WriteRegister(0x0020,0x0000);                                                            
        ili9320_WriteRegister(0x0021,0x0000);           
        ///////////////////////////////////////////////////////      
        delay(5);
		delay(5);
        ili9320_WriteRegister(0x0030,0x0007); 
        ili9320_WriteRegister(0x0031,0x0707);   
        ili9320_WriteRegister(0x0032,0x0006);
        ili9320_WriteRegister(0x0035,0x0704);
        ili9320_WriteRegister(0x0036,0x1f04); 
        ili9320_WriteRegister(0x0037,0x0004);
        ili9320_WriteRegister(0x0038,0x0000);        
        ili9320_WriteRegister(0x0039,0x0706);     
        ili9320_WriteRegister(0x003c,0x0701);
        ili9320_WriteRegister(0x003d,0x000f);
        delay(5);
		delay(5);
        ili9320_WriteRegister(0x0050,0x0000);        
        ili9320_WriteRegister(0x0051,0x00ef);   
        ili9320_WriteRegister(0x0052,0x0000);     
        ili9320_WriteRegister(0x0053,0x013f);
        ili9320_WriteRegister(0x0060,0xa700);        
        ili9320_WriteRegister(0x0061,0x0001); 
        ili9320_WriteRegister(0x006a,0x0000);
        ili9320_WriteRegister(0x0080,0x0000);
        ili9320_WriteRegister(0x0081,0x0000);
        ili9320_WriteRegister(0x0082,0x0000);
        ili9320_WriteRegister(0x0083,0x0000);
        ili9320_WriteRegister(0x0084,0x0000);
        ili9320_WriteRegister(0x0085,0x0000);
      
        ili9320_WriteRegister(0x0090,0x0010);     
        ili9320_WriteRegister(0x0092,0x0600);  
    	if(DeviceCode==0x9328)
        {   
            ili9320_WriteRegister(0x0093,0x0003);
            ili9320_WriteRegister(0x0095,0x0110);
            ili9320_WriteRegister(0x0097,0x0000);        
            ili9320_WriteRegister(0x0098,0x0000);  
         }
         //display on sequence     
        ili9320_WriteRegister(0x0007,0x0133);
    
        ili9320_WriteRegister(0x0020,0x0000);                                                            
        ili9320_WriteRegister(0x0021,0x0000);
	}
	else if(DeviceCode==0x9320||DeviceCode==0x9300)
	{
     //   printf("\n\r This LCD is ili%x.", DeviceCode);
    ili9320_WriteRegister(0x00,0x0001);
		ili9320_WriteRegister(0x01,0x0100);	//Driver Output Contral. 0x0100
		ili9320_WriteRegister(0x02,0x0700);	//LCD Driver Waveform Contral.
		ili9320_WriteRegister(0x03,0x1018);	//Entry Mode Set. 0x1018 0x1030
		//ili9320_WriteRegister(0x03,0x1018);	//Entry Mode Set.
		delay(5);
	
		ili9320_WriteRegister(0x04,0x0000);	//Scalling Contral.
		ili9320_WriteRegister(0x08,0x0202);	//Display Contral 2.(0x0207)
		ili9320_WriteRegister(0x09,0x0000);	//Display Contral 3.(0x0000)
		ili9320_WriteRegister(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		ili9320_WriteRegister(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		ili9320_WriteRegister(0x0d,0x0000);	//Frame Maker Position.
		ili9320_WriteRegister(0x0f,0x0000);	//Extern Display Interface Contral 2.
	
		delay(5);
		ili9320_WriteRegister(0x07,0x0101);	//Display Contral.
		delay(5);
	
		ili9320_WriteRegister(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		ili9320_WriteRegister(0x11,0x0007);								//Power Control 2.(0x0001)
		ili9320_WriteRegister(0x12,(1<<8)|(1<<4)|(0<<0));					//Power Control 3.(0x0138)
		ili9320_WriteRegister(0x13,0x0b00);								//Power Control 4.
		ili9320_WriteRegister(0x29,0x0000);								//Power Control 7.
		ili9320_WriteRegister(0x2b,(1<<14)|(1<<4));
		
		ili9320_WriteRegister(0x50,0);		//Set X Start.
		ili9320_WriteRegister(0x51,239);	//Set X End.
		ili9320_WriteRegister(0x52,0);		//Set Y Start.
		ili9320_WriteRegister(0x53,319);	//Set Y End.
	
		ili9320_WriteRegister(0x60,0x2700);	//Driver Output Control.
		ili9320_WriteRegister(0x61,0x0001);	//Driver Output Control.
		ili9320_WriteRegister(0x6a,0x0000);	//Vertical Srcoll Control.
	
		ili9320_WriteRegister(0x80,0x0000);	//Display Position? Partial Display 1.
		ili9320_WriteRegister(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		ili9320_WriteRegister(0x82,0x0000);	//RAM Address End-Partial Display 1.
		ili9320_WriteRegister(0x83,0x0000);	//Displsy Position? Partial Display 2.
		ili9320_WriteRegister(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		ili9320_WriteRegister(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		ili9320_WriteRegister(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		ili9320_WriteRegister(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		ili9320_WriteRegister(0x93,0x0001);	//Panel Interface Contral 3.
		ili9320_WriteRegister(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		ili9320_WriteRegister(0x97,(0<<8));	//
		ili9320_WriteRegister(0x98,0x0000);	//Frame Cycle Contral.
        delay(5);
		ili9320_WriteRegister(0x07,0x0173);	//(0x0173)
		delay(5);
	}
	else if(DeviceCode==0x9331)
	{
		ili9320_WriteRegister(0x00E7, 0x1014);
		ili9320_WriteRegister(0x0001, 0x0100); // set SS and SM bit   0x0100
		ili9320_WriteRegister(0x0002, 0x0200); // set 1 line inversion
		ili9320_WriteRegister(0x0003, 0x1030); // set GRAM write direction and BGR=1.     0x1030
		ili9320_WriteRegister(0x0008, 0x0202); // set the back porch and front porch
		ili9320_WriteRegister(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		ili9320_WriteRegister(0x000A, 0x0000); // FMARK function
		ili9320_WriteRegister(0x000C, 0x0000); // RGB interface setting
		ili9320_WriteRegister(0x000D, 0x0000); // Frame marker Position
		ili9320_WriteRegister(0x000F, 0x0000); // RGB interface polarity
		//*************Power On sequence ****************//
		ili9320_WriteRegister(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		ili9320_WriteRegister(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
		ili9320_WriteRegister(0x0012, 0x0000); // VREG1OUT voltage
		ili9320_WriteRegister(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
		delay(5); // Dis-charge capacitor power voltage
		ili9320_WriteRegister(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
		ili9320_WriteRegister(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		delay(2); // Delay 50ms
		ili9320_WriteRegister(0x0012, 0x000C); // Internal reference voltage= Vci;
		delay(2); // Delay 50ms
		ili9320_WriteRegister(0x0013, 0x0800); // Set VDV[4:0] for VCOM amplitude
		ili9320_WriteRegister(0x0029, 0x0011); // Set VCM[5:0] for VCOMH
		ili9320_WriteRegister(0x002B, 0x000B); // Set Frame Rate
		delay(2); // Delay 50ms
		ili9320_WriteRegister(0x0020, 0x0000); // GRAM horizontal Address
		ili9320_WriteRegister(0x0021, 0x0000); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		ili9320_WriteRegister(0x0030, 0x0000);
		ili9320_WriteRegister(0x0031, 0x0106);
		ili9320_WriteRegister(0x0032, 0x0000);
		ili9320_WriteRegister(0x0035, 0x0204);
		ili9320_WriteRegister(0x0036, 0x160A);
		ili9320_WriteRegister(0x0037, 0x0707);
		ili9320_WriteRegister(0x0038, 0x0106);
		ili9320_WriteRegister(0x0039, 0x0707);
		ili9320_WriteRegister(0x003C, 0x0402);
		ili9320_WriteRegister(0x003D, 0x0C0F);
		//------------------ Set GRAM area ---------------//
		ili9320_WriteRegister(0x0050, 0x0000); // Horizontal GRAM Start Address
		ili9320_WriteRegister(0x0051, 0x00EF); // Horizontal GRAM End Address
		ili9320_WriteRegister(0x0052, 0x0000); // Vertical GRAM Start Address
		ili9320_WriteRegister(0x0053, 0x013F); // Vertical GRAM Start Address
		ili9320_WriteRegister(0x0060, 0x2700); // Gate Scan Line
		ili9320_WriteRegister(0x0061, 0x0001); // NDL,VLE, REV
		ili9320_WriteRegister(0x006A, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		ili9320_WriteRegister(0x0080, 0x0000);
		ili9320_WriteRegister(0x0081, 0x0000);
		ili9320_WriteRegister(0x0082, 0x0000);
		ili9320_WriteRegister(0x0083, 0x0000);
		ili9320_WriteRegister(0x0084, 0x0000);
		ili9320_WriteRegister(0x0085, 0x0000);
		//-------------- Panel Control -------------------//
		ili9320_WriteRegister(0x0090, 0x0010);
		ili9320_WriteRegister(0x0092, 0x0600);
		ili9320_WriteRegister(0x0007,0x0021);		
		delay(2);
		ili9320_WriteRegister(0x0007,0x0061);
		delay(2);
		ili9320_WriteRegister(0x0007,0x0133);  // 262K color and display ON
		delay(2);
	}
	else if(DeviceCode==0x9919)
	{
		//*********POWER ON &RESET DISPLAY OFF
		 ili9320_WriteRegister(0x28,0x0006);
		 ili9320_WriteRegister(0x00,0x0001);
		 ili9320_WriteRegister(0x10,0x0000);
		 ili9320_WriteRegister(0x01,0x72ef);
		 ili9320_WriteRegister(0x02,0x0600);
		 ili9320_WriteRegister(0x03,0x6a38);
		 ili9320_WriteRegister(0x11,0x6874);//70
		 
		 //  RAM WRITE DATA MASK
		 ili9320_WriteRegister(0x0f,0x0000); 
		 //  RAM WRITE DATA MASK
		 ili9320_WriteRegister(0x0b,0x5308); 
		 ili9320_WriteRegister(0x0c,0x0003);
		 ili9320_WriteRegister(0x0d,0x000a);
		 ili9320_WriteRegister(0x0e,0x2e00);  //0030
		 ili9320_WriteRegister(0x1e,0x00be);
		 ili9320_WriteRegister(0x25,0x8000);
		 ili9320_WriteRegister(0x26,0x7800);
		 ili9320_WriteRegister(0x27,0x0078);
		 ili9320_WriteRegister(0x4e,0x0000);
		 ili9320_WriteRegister(0x4f,0x0000);
		 ili9320_WriteRegister(0x12,0x08d9);
		 // -----------------Adjust the Gamma Curve----//
		 ili9320_WriteRegister(0x30,0x0000);	 //0007
		 ili9320_WriteRegister(0x31,0x0104);	   //0203
		 ili9320_WriteRegister(0x32,0x0100);		//0001
		 ili9320_WriteRegister(0x33,0x0305);	  //0007
		 ili9320_WriteRegister(0x34,0x0505);	  //0007
		 ili9320_WriteRegister(0x35,0x0305);		 //0407
		 ili9320_WriteRegister(0x36,0x0707);		 //0407
		 ili9320_WriteRegister(0x37,0x0300);		  //0607
		 ili9320_WriteRegister(0x3a,0x1200);		 //0106
		 ili9320_WriteRegister(0x3b,0x0800);		 
		 ili9320_WriteRegister(0x07,0x0033);
	}
	else if(DeviceCode==0x1505)
	{
        // second release on 3/5  ,luminance is acceptable,water wave appear during camera preview
        ili9320_WriteRegister(0x0007,0x0000);
        delay(2);
        ili9320_WriteRegister(0x0012,0x011C);//0x011A   why need to set several times?
        ili9320_WriteRegister(0x00A4,0x0001);//NVM
        ili9320_WriteRegister(0x0008,0x000F);
        ili9320_WriteRegister(0x000A,0x0008);
        ili9320_WriteRegister(0x000D,0x0008);
       
        //GAMMA CONTROL/
        ili9320_WriteRegister(0x0030,0x0707);
        ili9320_WriteRegister(0x0031,0x0007); //0x0707
        ili9320_WriteRegister(0x0032,0x0603); 
        ili9320_WriteRegister(0x0033,0x0700); 
        ili9320_WriteRegister(0x0034,0x0202); 
        ili9320_WriteRegister(0x0035,0x0002); //?0x0606
        ili9320_WriteRegister(0x0036,0x1F0F);
        ili9320_WriteRegister(0x0037,0x0707); //0x0f0f  0x0105
        ili9320_WriteRegister(0x0038,0x0000); 
        ili9320_WriteRegister(0x0039,0x0000); 
        ili9320_WriteRegister(0x003A,0x0707); 
        ili9320_WriteRegister(0x003B,0x0000); //0x0303
        ili9320_WriteRegister(0x003C,0x0007); //?0x0707
        ili9320_WriteRegister(0x003D,0x0000); //0x1313//0x1f08
        delay(2);
        ili9320_WriteRegister(0x0007,0x0001);
        ili9320_WriteRegister(0x0017,0x0001);   //Power supply startup enable
        delay(2);
  
        //power control//
        ili9320_WriteRegister(0x0010,0x17A0); 
        ili9320_WriteRegister(0x0011,0x0217); //reference voltage VC[2:0]   Vciout = 1.00*Vcivl
        ili9320_WriteRegister(0x0012,0x011E);//0x011c  //Vreg1out = Vcilvl*1.80   is it the same as Vgama1out ?
        ili9320_WriteRegister(0x0013,0x0F00); //VDV[4:0]-->VCOM Amplitude VcomL = VcomH - Vcom Ampl
        ili9320_WriteRegister(0x002A,0x0000);  
        ili9320_WriteRegister(0x0029,0x000A); //0x0001F  Vcomh = VCM1[4:0]*Vreg1out    gate source voltage??
        ili9320_WriteRegister(0x0012,0x013E); // 0x013C  power supply on
           //Coordinates Control//
        ili9320_WriteRegister(0x0050,0x0000);//0x0e00
        ili9320_WriteRegister(0x0051,0x00EF); 
        ili9320_WriteRegister(0x0052,0x0000); 
        ili9320_WriteRegister(0x0053,0x013F); 
        //Pannel Image Control//
        ili9320_WriteRegister(0x0060,0x2700); 
        ili9320_WriteRegister(0x0061,0x0001); 
        ili9320_WriteRegister(0x006A,0x0000); 
        ili9320_WriteRegister(0x0080,0x0000); 
        //Partial Image Control//
        ili9320_WriteRegister(0x0081,0x0000); 
        ili9320_WriteRegister(0x0082,0x0000); 
        ili9320_WriteRegister(0x0083,0x0000); 
        ili9320_WriteRegister(0x0084,0x0000); 
        ili9320_WriteRegister(0x0085,0x0000); 
        //Panel Interface Control//
        ili9320_WriteRegister(0x0090,0x0013); //0x0010 frenqucy
        ili9320_WriteRegister(0x0092,0x0300); 
        ili9320_WriteRegister(0x0093,0x0005); 
        ili9320_WriteRegister(0x0095,0x0000); 
        ili9320_WriteRegister(0x0097,0x0000); 
        ili9320_WriteRegister(0x0098,0x0000); 
  
        ili9320_WriteRegister(0x0001,0x0100); 
        ili9320_WriteRegister(0x0002,0x0700); 
        ili9320_WriteRegister(0x0003,0x1030); 
        ili9320_WriteRegister(0x0004,0x0000); 
        ili9320_WriteRegister(0x000C,0x0000); 
        ili9320_WriteRegister(0x000F,0x0000); 
        ili9320_WriteRegister(0x0020,0x0000); 
        ili9320_WriteRegister(0x0021,0x0000); 
        ili9320_WriteRegister(0x0007,0x0021); 
        delay(2);
        ili9320_WriteRegister(0x0007,0x0061); 
        delay(2);
        ili9320_WriteRegister(0x0007,0x0173); 
        delay(2);
	}							 
	else if(DeviceCode==0x8989)
	{
	    ili9320_WriteRegister(0x0000,0x0001);		//´ò¿ª¾§Õñ
	    ili9320_WriteRegister(0x0003,0xA8A4);		//0xA8A4
	    ili9320_WriteRegister(0x000C,0x0000);        
	    ili9320_WriteRegister(0x000D,0x080C);        
	    ili9320_WriteRegister(0x000E,0x2B00);        
	    ili9320_WriteRegister(0x001E,0x00B0);        
	    ili9320_WriteRegister(0x0001,0x293F);		//Çý¶¯Êä³ö¿ØÖÆ320*240  0x693F  0x2B3F 0x293F
	    ili9320_WriteRegister(0x0002,0x0600);     	//LCD Driving Waveform control
	    ili9320_WriteRegister(0x0010,0x0000);     
	    ili9320_WriteRegister(0x0011,0x6078);		//0x4030	//¶¨ÒåÊý¾Ý¸ñÊ½  16Î»É« 0x6070	ºáÆÁ 0x6058
	    ili9320_WriteRegister(0x0005,0x0000);     
	    ili9320_WriteRegister(0x0006,0x0000);     
	    ili9320_WriteRegister(0x0016,0xEF1C);     
	    ili9320_WriteRegister(0x0017,0x0003);     
	    ili9320_WriteRegister(0x0007,0x0233);		//0x0233       
	    ili9320_WriteRegister(0x000B,0x0000);     
	    ili9320_WriteRegister(0x000F,0x0000);		//É¨Ãè¿ªÊ¼µØÖ·
	    ili9320_WriteRegister(0x0041,0x0000);     
	    ili9320_WriteRegister(0x0042,0x0000);     
	    ili9320_WriteRegister(0x0048,0x0000);     
	    ili9320_WriteRegister(0x0049,0x013F);     
	    ili9320_WriteRegister(0x004A,0x0000);     
	    ili9320_WriteRegister(0x004B,0x0000);     
	    ili9320_WriteRegister(0x0044,0xEF00);     
	    ili9320_WriteRegister(0x0045,0x0000);     
	    ili9320_WriteRegister(0x0046,0x013F);     
	    ili9320_WriteRegister(0x0030,0x0707);     
	    ili9320_WriteRegister(0x0031,0x0204);     
	    ili9320_WriteRegister(0x0032,0x0204);     
	    ili9320_WriteRegister(0x0033,0x0502);     
	    ili9320_WriteRegister(0x0034,0x0507);     
	    ili9320_WriteRegister(0x0035,0x0204);     
	    ili9320_WriteRegister(0x0036,0x0204);     
	    ili9320_WriteRegister(0x0037,0x0502);     
	    ili9320_WriteRegister(0x003A,0x0302);     
	    ili9320_WriteRegister(0x003B,0x0302);     
	    ili9320_WriteRegister(0x0023,0x0000);     
	    ili9320_WriteRegister(0x0024,0x0000);     
	    ili9320_WriteRegister(0x0025,0x8000);     
	    ili9320_WriteRegister(0x004e,0);        //ÁÐ(X)Ê×Ö·0
	    ili9320_WriteRegister(0x004f,0);        //ÐÐ(Y)Ê×Ö·0
	}
    else
    {
     //  printf("\n\r ###### Err: Unknow DeviceCode 0x%x ###### ", DeviceCode);
    }


	if(DeviceCode!=0x1505)
	{
    //     ili9320_Clear(0x07e0);
    // 	LCD_DisplayWelcomeStr(0x60);
		// delay(400);
    }

/*
    for (i=0;i<len;i++)
    {
        LCD_DisplayChar(LCD_LINE_1, 100,str[i]);
    }
*/
    
    //ili9320_Clear(0x001F);
 
}

__inline void ili9320_SetCursor(u16 x,u16 y)
{
	if(DeviceCode==0x8989)
	{
	 	ili9320_WriteRegister(0x004e,y);        
    	ili9320_WriteRegister(0x004f,x);  
	}
	else if(DeviceCode==0x9320)
	{
		ili9320_WriteRegister(0x0020,y); 
  		ili9320_WriteRegister(0x0021,0x13f-x); 	
	}
	else if(DeviceCode==0x9919)
	{
		ili9320_WriteRegister(0x004e,x); 
  		ili9320_WriteRegister(0x004f,y); 	
	}
	else
	{
  		ili9320_WriteRegister(0x0020,y); 
  		ili9320_WriteRegister(0x0021,0x13f-x); 
	}
}

__inline void ili9320_SetWindows(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
{
  ili9320_SetCursor(StartX,StartY);
  ili9320_WriteRegister(0x0050, StartX);
  ili9320_WriteRegister(0x0052, StartY);
  ili9320_WriteRegister(0x0051, EndX);
  ili9320_WriteRegister(0x0053, EndY);
}


void ili9320_Clear(u16 Color)
{
  u32 index = 0;

  LCD_SetCursor(0,0); 
  LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

  Clr_Cs
  Set_Rs
  for(index=0;index<76800;index++)
   {
      Clr_nWr
      LCD_WriteRAM(Color);
      Set_nWr
   }
  Set_Cs
}

/****************************************************************************
* Ãû    ³Æ£ºu16 ili9320_GetPoint(u16 x,u16 y)
* ¹¦    ÄÜ£º»ñÈ¡Ö¸¶¨×ù±êµÄÑÕÉ«Öµ
* Èë¿Ú²ÎÊý£ºx      ÐÐ×ù±ê
*           y      ÁÐ×ù±ê
* ³ö¿Ú²ÎÊý£ºµ±Ç°×ù±êÑÕÉ«Öµ
* Ëµ    Ã÷£º
* µ÷ÓÃ·½·¨£ºi=ili9320_GetPoint(10,10);
****************************************************************************/
//u16 ili9320_GetPoint(u16 x,u16 y)
//{
//  ili9320_SetCursor(x,y);
//  return (ili9320_BGR2RGB(ili9320_ReadRegister(0x0022)));
//}


u16 ili9320_GetPoint(u16 x,u16 y)
{
  u16 temp;
  ili9320_SetCursor(x,y);
  Clr_Cs;
  ili9320_WriteIndex(0x0022);  
	temp = ili9320_ReadData(); 
	temp = ili9320_ReadData(); 	
   Set_Cs;
   if((DeviceCode!=0x7783) && (DeviceCode!=0x8989))
   	  temp=ili9320_BGR2RGB(temp);
   return (temp);
}


void ili9320_SetPoint(u16 x,u16 y,u16 point)
{
  if ( (x>320)||(y>240) ) return;
  ili9320_SetCursor(x,y);

  Clr_Cs;
  ili9320_WriteIndex(0x0022);
  ili9320_WriteData(point);
  Set_Cs;
}

void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
{
  u16  i;
  ili9320_SetWindows(StartX,StartY,EndX,EndY);
  ili9320_SetCursor(StartX,StartY);
  
  Clr_Cs;

  ili9320_WriteIndex(0x0022);
  for (i=0;i<(EndX*EndY);i++)
  {
      ili9320_WriteData(*pic++);
  }     
  Set_Cs;
}

void ili9320_PutChar(u16 x,u16 y,u8 c,u16 charColor,u16 bkColor)
{
  // u16 i=0;
  // u16 j=0;
  
  // u8 tmp_char=0;

  // for (i=0;i<16;i++)
  // {
  //   tmp_char=ascii_8x16[((c-0x20)*16)+i];
  //   for (j=0;j<8;j++)
  //   {
  //     if ( (tmp_char >> 7-j) & 0x01 == 0x01)
  //       {
  //         ili9320_SetPoint(x+j,y+i,charColor); // ×Ö·ûÑÕÉ«
  //       }
  //       else
  //       {
  //         ili9320_SetPoint(x+j,y+i,bkColor); // ±³¾°ÑÕÉ«
  //       }
  //   }
  // }
}

void ili9320_Test()
{
  u8  R_data,G_data,B_data,i,j;

	ili9320_SetCursor(0x00, 0x0000);
	ili9320_WriteRegister(0x0050,0x00);
	ili9320_WriteRegister(0x0051,239);
	ili9320_WriteRegister(0x0052,0);
	ili9320_WriteRegister(0x0053,319);  
	Clr_Cs; 
	ili9320_WriteIndex(0x0022);
    R_data=0;G_data=0;B_data=0;     
    for(j=0;j<50;j++)
    {
        for(i=0;i<240;i++)
            {R_data=i/8;ili9320_WriteData(R_data<<11|G_data<<5|B_data);
		}
    }
    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<50;j++)
    {
        for(i=0;i<240;i++)
            {
            G_data=0x3f-(i/4);
            B_data=0x1f-(i/8);
            ili9320_WriteData(R_data<<11|G_data<<5|B_data);
			}
    }
//----------------------------------
    R_data=0;G_data=0;B_data=0;
    for(j=0;j<50;j++)
    {
        for(i=0;i<240;i++)
            {G_data=i/4;
			ili9320_WriteData(R_data<<11|G_data<<5|B_data);
}
    }

    R_data=0x1f;G_data=0x3f;B_data=0x1f;
    for(j=0;j<50;j++)
    {
        for(i=0;i<240;i++)
            {
            R_data=0x1f-(i/8);
            B_data=0x1f-(i/8);
            ili9320_WriteData(R_data<<11|G_data<<5|B_data);
		}
    }
//----------------------------------
 
    R_data=0;G_data=0;B_data=0;
    for(j=0;j<60;j++)
    {
        for(i=0;i<240;i++)
            {B_data=i/8;ili9320_WriteData(R_data<<11|G_data<<5|B_data);
			}
    } 

    B_data=0; 
    R_data=0x1f;G_data=0x3f;B_data=0x1f;

    for(j=0;j<60;j++)
    {
        for(i=0;i<240;i++)
            {
            G_data=0x3f-(i/4);
            R_data=0x1f-(i/8);
            ili9320_WriteData(R_data<<11|G_data<<5|B_data);
		}
    }	  
	Set_Cs;
}

u16 ili9320_BGR2RGB(u16 c)
{
  u16  r, g, b, rgb;

  b = (c>>0)  & 0x1f;
  g = (c>>5)  & 0x3f;
  r = (c>>11) & 0x1f;
  
  rgb =  (b<<11) + (g<<5) + (r<<0);

  return( rgb );
}

__inline void ili9320_WriteIndex(u16 idx)
{
  Clr_Rs;
	Set_nRd;
	GPIOE->ODR = idx;
	Clr_nWr;
	Set_nWr;
}

void ili9320_WriteData(u16 data)
{
	Set_Rs;
	Set_nRd;
  	GPIOE->ODR = data;
	Clr_nWr;
	Set_nWr;
}


__inline u16 ili9320_ReadData(void)
{
//========================================================================
// **                                                                    **
// ** nCS       ----\__________________________________________/-------  **
// ** RS        ------\____________/-----------------------------------  **
// ** nRD       -------------------------\_____/---------------------  **
// ** nWR       --------\_______/--------------------------------------  **
// ** DB[0:15]  ---------[index]----------[data]-----------------------  **
// **                                                                    **
//========================================================================
	unsigned short val = 0;
	Set_Rs;
	Set_nWr;
	Clr_nRd;
    GPIOE->CRH = 0x44444444;
	GPIOE->CRL = 0x44444444;
	Lcd_Shortdelay();
	val = GPIOE->IDR;
	val = GPIOE->IDR;
	GPIOE->CRH = 0x33333333;
	GPIOE->CRL = 0x33333333;
	Set_nRd;
	return val;
}

__inline u16 ili9320_ReadRegister(u16 index)
{ 
  	Clr_Cs;
	ili9320_WriteIndex(index);     
	index = ili9320_ReadData();      	
	Set_Cs;
	return index;
}

__inline void ili9320_WriteRegister(u16 index,u16 dat)
{
 /************************************************************************
  **                                                                    **
  ** nCS       ----\__________________________________________/-------  **
  ** RS        ------\____________/-----------------------------------  **
  ** nRD       -------------------------------------------------------  **
  ** nWR       --------\_______/--------\_____/-----------------------  **
  ** DB[0:15]  ---------[index]----------[data]-----------------------  **
  **                                                                    **
  ************************************************************************/
    Clr_Cs;
	ili9320_WriteIndex(index);      
	ili9320_WriteData(dat);    
	Set_Cs; 
}

void ili9320_Delay(u32 nCount)
{
  for(; nCount != 0; nCount--);
}
