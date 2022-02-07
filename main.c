#include "STC15Fxxxx.h"
#include "button.h" 
#include "LCD1602.h"
//#include "fuzzy_pid.h"
#define uchar unsigned char	
//#define OSC           18432000L
//#define BAUD          9600
//#define URMD          0
#define ADC_POWER     0x80
#define ADC_FLAG      0x10
#define ADC_START     0x08
#define ADC_SPEEDLL   0x00
#define ADC_SPEEDL    0x20
#define ADC_SPEEDH    0x40
#define ADC_SPEEDHH   0x60
#define TIMS 65236
int   TK=50;						//����?��2��?��?��?����?��?,//2��?��?��?����?TK*10ms
int   TC;	

bit flag=0;

unsigned int intr2;
unsigned char intr;
bit adc_flag;
uchar state=1;		//��ʼ��С�Ŀ���״̬
#define da_cs P15
#define led P17
bit key_flag;
float Err=0,D_Err=0;	
float Last_Err=0,Prev_Err=0;
int limit=0;
float vol_set,vol_sample=0,temp_sample,dac=0;
int temp_set=60; 
uchar key_table[]={0,0,0};
float uk0=0;
 uint ad_data=0;  
//bit adc_rd=0;


static double error;
static double error_1=0;
static double error_2=0;
static double u_1=0;
static double u_2=0;
static double u_out;




void timer_0() interrupt 1
{
	if(++intr == 10)  //1ms?��DD��?��?
	{
     intr = 0;
		 key_flag = 1;  //10ms�м�
   
	 }
	if(++intr2 == 500)  //1ms?��DD��?��?
	{
    //P47=!P47;
		intr2 = 0;
		adc_flag=1;  //1s adc2��?��??��������????		    
  }
//display(temp_set,temp_sample);
}

void adc_int() interrupt 5
{
	ADC_CONTR &=!ADC_FLAG;
    //if (adc_rd==1){
	ad_data=ADC_RES*4+ADC_RESL;  
    // } if (adc_rd==0) {adc_rd=1;}
}
float  zuixiaopai_Calculate() 
{ 	  

 
u_out =error*22.22-error_1*27.553+error_2*7.016+0.322*u_1+0.678*u_2;


error_2=error_1; 
error_1=error;
u_2=u_1;
u_1=u_out;

return(u_1);
			
			
   } 

void main()
{
   	unsigned char key_temp;
	unsigned char ch=0;  //AD2��?�������̨�
        uchar i=0;
        P4=0;
        P0M0 = 0x00;
        P0M1 = 0x00;
        P1M0 = 0x01;
        P1M1 = 0x01;
        P2M0 = 0x00;
        P2M1 = 0x00;
        P3M0 = 0x00;
        P3M1 = 0x00;
        P4M0 = 0x00;
        P4M1 = 0x00;
        P5M0 = 0x00;
        P5M1 = 0x00;
        P6M0 = 0x00;
        P6M1 = 0x00;
        P7M0 = 0x00;
        P7M1 = 0x00;
        CLK_DIV=0x03;
        lcd_init(); 
        display_init(); 
        led=1;
	TL0=TIMS;
	TH0=TIMS>>8;
	AUXR&=0x3F;
	AUXR1=0X08;
	TMOD=0x00;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
	EADC=1;
	P1ASF=0xFF;
	ADC_RES=0;
    
        temp_sample=vol_sample*16+20;    //���û����¶ȳ�ʼֵ����Ӧ0-5V�������¶ȷ�Χ20-100��C
	ADC_CONTR =ADC_POWER  |ADC_SPEEDLL  | ADC_START | ch;
	//for(i=0;i<10000;i++);
  //ADC_CONTR &=!ADC_FLAG;
    da_cs=0;  //D/A��ʼֵ
    while(1)
    { 
		if(key_flag)			//10msɨ�����1��
		{
                key_flag = 0;
                key_temp = read_key();
		}
		switch (state)			   //״̬�л�
		{
			case 1:					//��С�Ŀ���
				
				
			if (adc_flag==1)
			{   
					
			ADC_CONTR=ADC_POWER |ADC_SPEEDLL | ADC_START | ch;
					// ad_data=0
                	adc_flag=0;
				
			vol_set=(temp_set-20)/16.0;   //�¿��趨��Χ20-100�ȣ�AD  0-5V
                        vol_sample=(float)(ad_data)*5/1024;   //����������0-1023����ɵ�ѹֵ0-5V
			temp_sample=vol_sample*16+20;    //������¶�
			error = vol_set - vol_sample;
			u_out=zuixiaopai_Calculate();     //����PID
			dac=(u_out/5*256*5/12);    
			limit=round(dac);
			if(limit<0) limit=0;
			if(limit>255) limit=255;		   
			P4=limit;

                   
                   }
                  
			display(temp_set,temp_sample);
			 if  (key_temp==10)       //���ü�����
			{
				state=2;
                                led=0;				//����ָʾ����
			}
			break;
			
			case 2:					     //���ø����¶�
			if (key_temp>=0&&key_temp<=9)       //���ּ�����
                               {key_table[i++]=key_temp;               //��λ��¼�����趨ֵ
                                if (i==3) i=0;}
				else if  (key_temp==11) 
				{	
					led=1;
					Err=0;
					D_Err=0;
                                        state=1;
					break;
				}
				//led=0;
				temp_set=key_table[0]*100+key_table[1]*10+key_table[2];  //��ϳ��¶��趨ֵ
				display(temp_set,temp_sample);

				break; 
				 
		}	
		
		
    }
	
	
}