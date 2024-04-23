#include "lyms.h"

#include "superwave.h"

uint8_t R_DATA1 = 0;
uint8_t R_DATA2 = 0;
uint8_t state;
uint8_t q1,q2;
float sj;



void user_usart_int()
{
    HAL_UART_Receive_IT(&huart3,&R_DATA1,1);
    HAL_UART_Receive_IT(&huart2,&R_DATA2,1);
}

void driver_off(void)
{
	M1=0;
	M2=0;
	M3=0;
	M4=0;
	Motor_Driver_Set();
}

 
void driver_forward(void)
{
	q1=0;
	q2=1;
	driver_stop();
	M1=30;
	M2=30;
	M3=-30;
	M4=-30;
	Motor_Driver_Set();
}
   
void driver_cw(void)
{
	driver_stop();
	M1=-20;
	M2=-20;
	M3=-20;
	M4=-20;
	Motor_Driver_Set();
}

void driver_left(void)
{

	driver_stop();
	M1=30;
	M2=-30;
	M3=-30;
	M4=30;
	Motor_Driver_Set();
}

void driver_right(void)
{
	driver_stop();
	M1=-30;
	M2=30;
	M3=30;
	M4=-30;
	Motor_Driver_Set();
}

void driver_back(void)
{
	q2=0;
	driver_stop();
	M1=-30;
	M2=-30;
	M3=30;
	M4=30;
	Motor_Driver_Set();
}


void driver_ccw(void)
{
	driver_stop();
	M1=20;
	M2=20;
	M3=20;
	M4=20;
	Motor_Driver_Set();

}
	
void driver_up(void)
{	
	
	if(M1<=90&&M1>=-90)
	{
		if(M1>0)
		{
			M1=M1+10;
			Motor_Driver_Set();
		}else
		{
		M1=M1-10;
		Motor_Driver_Set();	
		}
	}
	
		if(M2<=90&&M2>=-90)
		{
			if(M2>0)
		{
			M2=M2+10;
			Motor_Driver_Set();
		}else
		{
		M2=M2-10;
		Motor_Driver_Set();	
		}
	}
	
	
		if(M3<=90&&M3>=-90)
		{
			if(M3>0)
		{
			M3=M3+10;
			Motor_Driver_Set();
		}else
		{
		M3=M3-10;
		Motor_Driver_Set();	
		}
	}
		
 		if(M4<=90&&M4>=-90)
		{
			if(M4>0)
		{
			M4=M4+10;
			Motor_Driver_Set();
		}else
		{
		M4=M4-10;
		Motor_Driver_Set();	
		}
	}
		
	
	
}
void driver_down(void)
{
	if(M1>=10||M1<=-10)
	{
		if(M1>0)
		{
			M1=M1-10;
			Motor_Driver_Set();
		}else
		{
		M1=M1+10;
		Motor_Driver_Set();	
		}
	}else{
		M1=0;
		Motor_Driver_Set();	
	}
	
		if(M2>=10||M2<=-10)
		{
			if(M2>0)
		{
			M2=M2-10;
			Motor_Driver_Set();
		}else
		{
		M2=M2+10;
		Motor_Driver_Set();	
		}
	}else{
		M2=0;
		Motor_Driver_Set();	
	}
	
		if(M3>=10||M3<=-10)
		{
			if(M3>0)
		{
			M3=M3-10;
			Motor_Driver_Set();
		}else
		{
		M3=M3+10;
		Motor_Driver_Set();	
		}
	}else{
		M3=0;
		Motor_Driver_Set();	
	}
		if(M3>=10||M3<=-10)
		{
			if(M4>0)
		{
			M4=M4-10;
			Motor_Driver_Set();
		}else
		{
		M4=M4+10;
		Motor_Driver_Set();	
		}
	}else{
		M4=0;
		Motor_Driver_Set();	
	}
	
}	
void driver_stop(void)
{
	//driver_off();
	q2=0;
	Motor_Driver_Stop(1);
	Motor_Driver_Stop(2);
	Motor_Driver_Stop(3);
	Motor_Driver_Stop(4);
}


/*
R_DATA1为蓝牙接收
0为关机
1为开机
2为前进
8为后退
10为逆时针旋转
11为顺时针旋转
3为加速
9为减速
5为刹车函数
4为左走
6为右走
*/

/*
R_DATA2为传感器接收
*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart3)
    {
        if(R_DATA1==0)
        {
					driver_off();
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
					state=0;
        }
        else if (R_DATA1==1)
        {
           state=1;
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
        }
        if (state==1)
        {
            switch(R_DATA1){
                case 2:
                    driver_forward();
                    break;
                case 8:
                    driver_back();
                    break;
                case 10:
                    driver_cw();
                    break;
                case 11:
                    driver_ccw();
                    break;
                case 3:
                    driver_up();
                    break;
                case 9:
                    driver_down();
                    break;
                case 5:
                    driver_stop();
                    break;
								case 4:
										driver_left();
										break;
								case 6:
										driver_right();
									break;
                defaule:
                    driver_stop();
								
            }
        }
		R_DATA1 =100;
		user_usart_int();
    }
    else if (huart == &huart2)
    {
			sj=receive1( R_DATA2);
			if(sj!=0)
				adjust(sj,1);
			user_usart_int();	
                   
	}		
}			   