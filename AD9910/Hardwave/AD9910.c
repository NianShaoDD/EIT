#include "stm32h7xx.h"                  // Device header
#include "gpio.h"
#include "AD9910.h"


uchar cfr1[]={0x00,0x40,0x00,0x00};       //cfr1控制字
uchar cfr2[]={0x01,0x00,0x00,0x00};       //cfr2控制字
const uchar cfr3[]={0x05,0x0F,0x41,0x32};       //cfr3控制字  40M输入  25倍频  VC0=101   ICP=001;
uchar profile11[]={0x3f,0xff,0x00,0x00,0x25,0x09,0x7b,0x42};       //profile1控制字 0x25,0x09,0x7b,0x42
                  //01振幅控制 23相位控制 4567频率调谐字

uchar drgparameter[20]={0x00}; //DRG参数
uchar ramprofile0[8] = {0x00}; //ramprofile0控制字
extern const unsigned char ramdata_Square[4096];

extern uchar cfr2[4]; //cfr2控制字
extern uchar cfr1[4]; //cfr1控制字


//void AD9110_IOInit(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure ; 
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA,PB端口时钟

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9| GPIO_Pin_12; 			 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ; 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ; 
//	GPIO_Init(GPIOB ,&GPIO_InitStructure) ; 

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8; //A2，A4，A5，A6，A8
//	GPIO_Init(GPIOA ,&GPIO_InitStructure) ;

////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All^(GPIO_Pin_14| GPIO_Pin_15); //除了C14，C15，其他都选
////	GPIO_Init(GPIOC ,&GPIO_InitStructure) ;
//}

void AD9110_IOInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOJ, AD9910_SDIO_Pin|MAS_REST_Pin|SCLK_Pin|CS_Pin
                          |UP_DAT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PJPin PJPin PJPin PJPin
                           PJPin */
  GPIO_InitStruct.Pin = AD9910_SDIO_Pin|MAS_REST_Pin|SCLK_Pin|CS_Pin
                          |UP_DAT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);
}

//=====================================================================

//======================ad9910初始化程序===============================
void Init_ad9910(void)
{	
	AD9110_IOInit();//IO初始化
//	AD9910_PWR = 0;//软件拉低
	
//	PROFILE2=PROFILE1=PROFILE0=0;
//	DRCTL=0;DRHOLD=0;
//	MAS_REST=1;
	MAS_REST_HIGH();
	HAL_Delay(5);
//	delay_ms(5);  
//	MAS_REST=0; 
	MAS_REST_LOW();

	Txcfr();
}      
//=====================================================================

//======================发送8位数据程序================================
void txd_8bit(uchar txdat)
{
	uchar i,sbt;
	sbt=0x80;
//	SCLK=0;
	SCLK_LOW();
	for (i=0;i<8;i++)
	{
		if ((txdat & sbt)==0) 
//			AD9910_SDIO=0;
			AD9910_SDIO_LOW();
		else 
//			AD9910_SDIO=1;
			AD9910_SDIO_HIGH();
//		SCLK=1;
		SCLK_HIGH();
		sbt=sbt>>1;
//		SCLK=0;
		SCLK_LOW();
	}
}  
//=====================================================================

//======================ad9910发送cfrx控制字程序=======================
void Txcfr(void)
{
	uchar m,k;

//	CS=0;
	CS_LOW();
	txd_8bit(0x00);    //发送CFR1控制字地址
	for (m=0;m<4;m++)
		txd_8bit(cfr1[m]); 
//	CS=1;  
	CS_HIGH();
	for (k=0;k<10;k++);
	
//	CS=0;
	CS_LOW();
	txd_8bit(0x01);    //发送CFR2控制字地址
	for (m=0;m<4;m++)
		txd_8bit(cfr2[m]); 
//	CS=1;
	CS_HIGH();	
	for (k=0;k<10;k++);

//	CS=0;
	CS_LOW();
	txd_8bit(0x02);    //发送CFR3控制字地址
	for (m=0;m<4;m++)
		txd_8bit(cfr3[m]); 
//	CS=1;
	CS_HIGH();
	for (k=0;k<10;k++);

//	UP_DAT=1;
	UP_DAT_HIGH();
	for(k=0;k<10;k++);
//	UP_DAT=0;
	UP_DAT_LOW();
	HAL_Delay(1);
}         
//=====================================================================

//===================ad9910发送profile0控制字程序======================
void Txprofile(void)
{
	uchar m,k;

//	CS=0;
	CS_LOW();
	txd_8bit(0x0e);    //发送profile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(profile11[m]); 
//	CS=1;
	CS_HIGH();
	for(k=0;k<10;k++);

//	UP_DAT=1;
	UP_DAT_HIGH();
	for(k=0;k<10;k++);
//	UP_DAT=0;
	UP_DAT_LOW();
//	delay_ms(1);
	HAL_Delay(1);
}         
//=====================================================================

//===================计算频偏字、频率字和发送程序======================
void Freq_convert(ulong Freq)
{
	ulong Temp;
	if(Freq > 400000000)
		Freq = 400000000;
	Temp=(ulong)Freq*4.294967296; //将输入频率因子分为四个字节  4.294967296=(2^32)/1000000000 （1G 是内部时钟速度）
	profile11[7]=(uchar)Temp;
	profile11[6]=(uchar)(Temp>>8);
	profile11[5]=(uchar)(Temp>>16);
	profile11[4]=(uchar)(Temp>>24);
	Txprofile();
}
//=====================================================================

//===================计算幅度字和发送程序==============================
void Write_Amplitude(uint Amp)
{
	ulong Temp;
	Temp = (ulong)Amp*25.20615385;	   //将输入幅度因子分为两个字节  25.20615385=(2^14)/650
	if(Temp > 0x3fff)
		Temp = 0x3fff;
	Temp &= 0x3fff;
	profile11[1]=(uchar)Temp;
	profile11[0]=(uchar)(Temp>>8);
	Txprofile();
}
//=====================================================================

//======================ad9910发送DRG参数程序==========================
void Txdrg(void)
{
	uchar m,k;

//	CS=0;
	CS_LOW();
	txd_8bit(0x0b);    //发送数字斜坡限制地址0x0b
	for (m=0;m<8;m++)
		txd_8bit(drgparameter[m]); 
//	CS=1;
	CS_HIGH();
	for(k=0;k<10;k++);
	
//	CS=0;
	CS_LOW();
	txd_8bit(0x0c);    //发送数字斜坡步长地址0x0c
	for (m=8;m<16;m++)
		txd_8bit(drgparameter[m]); 
//	CS=1;
	CS_HIGH();
	for(k=0;k<10;k++);
	
//	CS=0;
	CS_LOW();
	txd_8bit(0x0d);    //发送数字斜坡速率地址0x0d
	for (m=16;m<20;m++)
		txd_8bit(drgparameter[m]); 
//	CS=1;
	CS_HIGH();
	for(k=0;k<10;k++);
	
//	UP_DAT=1;
	UP_DAT_HIGH();
	for(k=0;k<10;k++);
//	UP_DAT=0;
	UP_DAT_LOW();
//	delay_ms(1);
	HAL_Delay(1);
}         
//=====================================================================

//=====================扫频波参数设置和发送程序========================
void SweepFre(ulong SweepMinFre, ulong SweepMaxFre, ulong SweepStepFre, ulong SweepTime)
{
	ulong Temp1, Temp2, ITemp3, DTemp3, ITemp4, DTemp4;
	Temp1 = (ulong)SweepMinFre*4.294967296;
	if(SweepMaxFre > 450000000)
		SweepMaxFre = 450000000;
	Temp2 = (ulong)SweepMaxFre*4.294967296;
	if(SweepStepFre > 450000000)
		SweepStepFre = 450000000;
	ITemp3 = (ulong)SweepStepFre*4.294967296;
	DTemp3 = ITemp3;
	ITemp4 = (ulong)SweepTime/4; //1GHz/4, 单位：ns
	if(ITemp4 > 0xffff)
		ITemp4 = 0xffff;
	DTemp4 = ITemp4;
	
	//扫频上下限
	drgparameter[7]=(uchar)Temp1;
	drgparameter[6]=(uchar)(Temp1>>8);
	drgparameter[5]=(uchar)(Temp1>>16);
	drgparameter[4]=(uchar)(Temp1>>24);
	drgparameter[3]=(uchar)Temp2;
	drgparameter[2]=(uchar)(Temp2>>8);
	drgparameter[1]=(uchar)(Temp2>>16);
	drgparameter[0]=(uchar)(Temp2>>24);
	//频率步进（单位：Hz）
	drgparameter[15]=(uchar)ITemp3;
	drgparameter[14]=(uchar)(ITemp3>>8);
	drgparameter[13]=(uchar)(ITemp3>>16);
	drgparameter[12]=(uchar)(ITemp3>>24);
	drgparameter[11]=(uchar)DTemp3;
	drgparameter[10]=(uchar)(DTemp3>>8);
	drgparameter[9]=(uchar)(DTemp3>>16);
	drgparameter[8]=(uchar)(DTemp3>>24);
	//步进时间间隔（单位：us）
	drgparameter[19]=(uchar)ITemp4;
	drgparameter[18]=(uchar)(ITemp4>>8);
	drgparameter[17]=(uchar)DTemp4;
	drgparameter[16]=(uchar)(DTemp4>>8);
	//发送DRG参数
	Txdrg();
}
//=====================================================================

//=================ad9910发送ramprofile0控制字程序=====================
void Txramprofile(void)
{
	uchar m,k;

//	CS=0;
	CS_LOW();
	txd_8bit(0x0e);    //发送ramprofile0控制字地址
	for (m=0;m<8;m++)
		txd_8bit(ramprofile0[m]); 
//	CS=1;
	CS_HIGH();
	for(k=0;k<10;k++);

//	UP_DAT=1;
	UP_DAT_HIGH();
	for(k=0;k<10;k++);
//	UP_DAT=0;
	UP_DAT_LOW();
//	delay_ms(1);
	HAL_Delay(1);
}         
//=====================================================================

//=================ad9910扫频配置函数=====================
void SW_9910(void)
{
		cfr1[0] = 0x00; //RAM 失能
		cfr2[1]=0x0e; //DRG 使能
		Txcfr();
		Write_Amplitude(650); 
		SweepFre(440000000, 450000000, 10, 5);
}




