#include "STC15Fxxxx.h" 
bit key_re;
unsigned char key_press;


   //��ȡ��ֵ
unsigned char read_key(void)  //key_press �ظ�5�Σ�������ʱ������
{
	
    unsigned char key_temp;
    unsigned char key_value;
	 P0=0xF0;
	 key_temp =P0;
    if(key_temp != 0xF0) //�а�������
        key_press++;
	else
		key_press = 0;  //����
    
    if(key_press ==2)
    {
		      key_press = 0;
	      	key_re = 1;
		  		P0=0xFE;   //��һ�и�0
	        //IO_KeyDelay();
		      key_temp=P0;	 
		      switch (key_temp)                
		       {
			     case 0xee:  key_value=0;  break;
			     case 0xde:  key_value=4;  break;
			     case 0xbe:  key_value=8;  break;
			     case 0x7e:  key_value=12;  break;

                // case 0xee:  key_value=1;  break;
			     //case 0xde:  key_value=2;  break;
			     //case 0xbe:  key_value=3;  break;
			    // case 0x7e:  key_value=12;  break; //����
			     default  : ; 
		       }
		      P0=0xFD;
	        //IO_KeyDelay();
		      key_temp=P0;	 	 
		      switch (key_temp)
	      	 {
				 case 0xed: key_value=1; break;
			     case 0xdd: key_value=5; break;
			    case 0xbd: key_value=9; break;
			    case 0x7d: key_value=13; break; 

			     //case 0xed: key_value=4; break;
			    // case 0xdd: key_value=5; break;
			    // case 0xbd: key_value=6; break;
			     //case 0x7d: key_value=13; break; //�˺�
			     default  : ; 
		       }
					P0=0xFB;
	        //IO_KeyDelay();
		      key_temp=P0;	  
		      switch (key_temp)
		     {
			    case 0xeb: key_value=2; break;
			    case 0xdb: key_value=6; break;
			    case 0xbb: key_value=10; break;
			    case 0x7b: key_value=14; break; 

                //case 0xeb: key_value=7; break;
			    //case 0xdb: key_value=8; break;
			    //case 0xbb: key_value=9; break;
			    //case 0x7b: key_value=14; break; //����
			    default  : ; 
		     }
				 P0=0xF7;
	       // IO_KeyDelay();
		      key_temp=P0;	 
		 		  switch (key_temp)
		     {
			     case 0xe7: key_value=3; break;
			     case 0xd7: key_value=7; break;
			     case 0xb7: key_value=11;break;
			     case 0x77: key_value=15; break; 
                 

                // case 0xe7: key_value=10; break;    //���
			     //case 0xd7: key_value=0; break;
			     //case 0xb7: key_value=11;break;  //�Ⱥ�
			     //case 0x77: key_value=15; break;//�Ӻ�
			     default  : ; 
		     }	
				
				
				
				
    }
    //������μ�⵽���������£����Ҹð����Ѿ��ͷ�
    if((key_re == 1) && (key_temp == 0xF0))
    {
        key_re = 0;
        return key_value;
    }
    
    return 0xff;  //�ް������»򱻰��µİ���δ���ͷ�    
}
