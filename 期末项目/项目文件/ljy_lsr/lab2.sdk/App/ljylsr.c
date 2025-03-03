#include "xparameters.h"
#include "xgpio.h"
#include "xutil.h"

//====================================================

// 定义一个延时xms毫秒的延时函数
void delay(unsigned int xms)  // xms代表需要延时的毫秒数
{
    unsigned int x,y;
    for(x=xms;x>0;x--)
        for(y=110;y>0;y--);
}

int main (void)
{

	//led灯，按钮和开关的设备号
    XGpio led,push,dip;
    int i,j,k,x,psb_check,pss_check;
	//计数器
	int count=0,beep=0;

    xil_printf("-- Start of the Program --\r\n");

    //初始化设备
    XGpio_Initialize(&led, XPAR_LED_DEVICE_ID);
	//将通道设置为输出
    XGpio_SetDataDirection(&led, 1, 0x00000000);

	XGpio_Initialize(&push, XPAR_BTNS_4BIT_DEVICE_ID);
	XGpio_SetDataDirection(&push, 1, 0xffffffff);

	XGpio_Initialize(&dip, XPAR_SW_4BIT_DEVICE_ID);
	XGpio_SetDataDirection(&dip, 1, 0xffffffff);


	while (1)
	{

		//读取按钮的值
	    psb_check = XGpio_DiscreteRead(&push, 1);
	    xil_printf("Push Buttons Status %x\r\n", psb_check);
	    //读取开关的值
	    pss_check = XGpio_DiscreteRead(&dip, 1);
	    xil_printf("Dip Switches Status %x\r\n", pss_check);

	  //在第一个开关打开时，流水灯
	  if (pss_check == 1){
		  if (count%3==0) {
			  //向插着led灯的gpio口写数据
			  XGpio_DiscreteWrite(&led, 1,2);
		  }
		  else if (count%3==1) {
			  XGpio_DiscreteWrite(&led, 1,4);
		  }
		  else if (count%3==2) {
			  XGpio_DiscreteWrite(&led, 1,8);
		  }
		  //延时1000ms
		  delay(100000);
		  //更新计数器
		  count++;
	  }
	  //第二个开关打开时，亮SOS
	  else if (pss_check == 2) {
		  for (x=0; x<3; x++) {
			  XGpio_DiscreteWrite(&led, 1,2);
			  delay(150000);
			  XGpio_DiscreteWrite(&led, 1,0);
			  delay(100000);
		  }
		  delay(10000);
		  for (x=0; x<3; x++) {
			  XGpio_DiscreteWrite(&led, 1,2);
			  delay(400000);
			  XGpio_DiscreteWrite(&led, 1,0);
			  delay(100000);
		  }
		  delay(10000);
		  for (x=0; x<3; x++) {
			  XGpio_DiscreteWrite(&led, 1,2);
			  delay(150000);
			  XGpio_DiscreteWrite(&led, 1,0);
			  delay(100000);
		  }
		  delay(1000000);
	  }
	  else if (pss_check == 4) {
			  if(beep==1){
			  	  XGpio_DiscreteWrite(&led, 1,1);
			  }
			  if(beep==0){
			  	  XGpio_DiscreteWrite(&led, 1,0);
			  }
			  for(i=0; i<1000; i++);
			  beep=1-beep;
	  }
	  else {
		  XGpio_DiscreteWrite(&led, 1,0);
	  }
	}
}


