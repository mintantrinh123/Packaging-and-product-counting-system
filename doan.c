#include "AT89X51.h"
const char ma7doan[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
#define p_led P0
sbit led1 = P2^7;
sbit led2 = P2^6;
sbit led3 = P2^5;
sbit led4 = P2^4;
sbit LED = P2^3;
unsigned char lan_quet=0;
unsigned char dem_ton_tof=0;
unsigned int so_sp;
unsigned int i,j;
sbit cb_hn = P1^0; // Cam bien hong ngoai
bit ncb_hn=0; // Ngan cam bien hong ngoai
sbit tang = P2^2; // Nut tang
sbit giam = P2^1; // Nut giam
sbit reset = P2^0; // Nut reset
bit NN = 0;
sbit coibao = P3^2;
void quet_nut();
void cam_bien();
//======================================== 
#define t_on 4
#define t_of 4
void quet_led(so_sp) // Ham quet led
{
	dem_ton_tof++;	
	 if(dem_ton_tof==t_on)
	{
			lan_quet++;
			if(lan_quet==1)
			{
					p_led=(ma7doan[so_sp/1000%10]);
					led1=0;
			}
			if(lan_quet==2)
			{
					p_led=(ma7doan[so_sp/100%10]);
					led2=0;
			}
			if(lan_quet==3)
			{
					p_led=(ma7doan[so_sp/10%10]);
					led3=0;
			}
			if(lan_quet==4)
			{
					p_led=(ma7doan[so_sp/1%10]);
					led4=0;
					lan_quet=0;
			}
	}
	else
	{
		if(dem_ton_tof==t_on+t_of)
		{
				led1=led2=led3=led4=1;
				p_led=0xff;
				dem_ton_tof=0; 
		}
	}
}
//======================================== 
void delay_ms(unsigned int t) // Ham delay
{
	for(i=0;i<t;i++)//Ham tre 1ms
	    {
	       for(j=0;j<50;j++);
				 LED=0;
				 coibao=0;
				 quet_led(so_sp);
				 quet_nut();
				 cam_bien();
			}
			LED=1;
			coibao=1;
}
void cam_bien() //Ham cam bien
{
	quet_led(so_sp);
	if(cb_hn==1)
	{
		ncb_hn=1; // Bao co vat can chan ngan
	}
	if(cb_hn==0&&ncb_hn==1)
	{
		ncb_hn=0; // Bao vat da di ngan qua
		so_sp++;
		if(so_sp>9999)
		{
			so_sp=0;
			
			delay_ms(5000);
		}
	}
}
//======================================== 
void main()  //chuong trinh chinh
{
	while(1) // Vong lap vo han
	{
		cam_bien();
		quet_nut();
	}
}
//======================================== 
void quet_nut() //Ham quet nut
{
	quet_led(so_sp);
	if(NN==1) // Kiem tra nut nhan nn = 1
	{
		if(tang==0)//Nut tang
		{
			NN=0; // Bao da nhan nut
			so_sp++;
			if(so_sp>9999)
			{
				so_sp=0;
	      delay_ms(5000);
			}
		}
		if(giam==0) // Nut giam
		{
			NN=0; // Bao da nhan nut
			so_sp--;
			if(so_sp>9999)
			{
				so_sp=0;
			}
		}
		if(reset==0)//Nut reset
		{
			NN=0; // Bao da nhan nut
			so_sp=0;
		}
	}
	else 
	{
		if(tang==1&&giam==1&&reset==1)
		{
			NN=1;
		}
	}
}
