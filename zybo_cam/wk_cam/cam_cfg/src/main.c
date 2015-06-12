/************************************************************************/
/*																		*/
/*	main.c	--	ZYBO_CAMERA						*/
/*																		*/
/************************************************************************/

/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include "xparameters.h"
#include "xuartps.h"
#include "xiicps.h"
#include "OV9655_camera.h"
#include "xiicps_hw.h"
#include "stdio.h"

/* ------------------------------------------------------------ */
/*				Global Variables								*/
/* ------------------------------------------------------------ */

/*
 * XPAR redefines
 */

#define SSM2603_BASEADDR 			0b0011010
#define SSM2603_NUMBER_REGISTER		38

#define IIC_DEVICE_ID		XPAR_XIICPS_0_DEVICE_ID
#define I2C0_BASEADDR  		XPAR_PS7_I2C_0_BASEADDR
#define IIC_SCLK_RATE		100000

#define UART_DEVICE_ID		XPAR_XUARTPS_0_DEVICE_ID
#define UART_BASEADDR		XPAR_PS7_UART_1_BASEADDR
#define UART_BAUDRATE		115200

int LireClavier();
void init_I2C0();

XIicPs Iic;

/* ------------------------------------------------------------ */
/*				Procedure Definitions							*/
/* ------------------------------------------------------------ */

int main(void)
{
	u8 ReadValue = 0;
	char userInput = 0;
	char YesNo[2];
	int addrReg, valReg;

	xil_printf("\x1B[2J"); // Clear terminal

	/* Initialisation I2C0 du PS */
	init_I2C0();

	/* Configuration camera */
	init_OV9655(&Iic);

	xil_printf("\x1B[H");  // Set cursor to top left of terminal
	xil_printf("\x1B[2J"); // Clear terminal
	xil_printf("**************************************************\n\r");
	xil_printf("**************************************************\n\r");
	xil_printf("*         Configuration camera OV9655            *\n\r");
	xil_printf("**************************************************\n\r");
	xil_printf("**************************************************\n\r");
	xil_printf("\n\r");
	xil_printf("w - Modifier registre\n\r");
	xil_printf("r - Lire registre\n\r");
	xil_printf("q - Quitter\n\r");
	xil_printf("\n\r");
	xil_printf("S��lectionnez votre action:\n\r");

	/* Vide FIFO */
	while (XUartPs_IsReceiveData(UART_BASEADDR))
	{
		XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
	}

	while (userInput != 'q')
	{
		/* Attente donn��es UART */
		while (!XUartPs_IsReceiveData(UART_BASEADDR));

		/* Lit caractere UART et l'affiche */
		userInput = XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);
		xil_printf("%c\n\r", userInput);

		switch (userInput)
		{
			case 'w':
				xil_printf("Entrez l'addresse du registre �� modifier\n\r");
				addrReg = LireClavier();
				xil_printf("Entrez la nouvelle valeur du registre\r\n");
				valReg = LireClavier();
				xil_printf("Confirmation valeur 0x%2x du registre d'addresse 0x%2x ? (y/n)\r\n", valReg, addrReg);
				scanf("%2s", YesNo);
				if (YesNo[0] == 'y')
				{
					OV9655_WriteRegister(&Iic, addrReg, valReg);
					xil_printf("Registre modifi��\r\n");
				}
				else
				{
					xil_printf("Abandon\r\n");
				}
				break;
			case 'r':
				xil_printf("Entrez l'addresse du registre a lire\n\r");
				addrReg = LireClavier();
				ReadValue = OV9655_ReadRegister(&Iic, addrReg);
				xil_printf("Valeur lue 0x%2x du registre d'adresse 0x%2x\n\r", ReadValue, addrReg);
				break;
			case 'q':
				break;
			default :
				xil_printf("S��lectionnez votre action\n\r");
		}
	}

	xil_printf("END_CONFIGURATION_CAMERA\n\r");

	return 0;
}

int LireClavier()
{
	char Buffer[2];
	int reg;

	scanf("%2s", Buffer);
	sscanf(Buffer, "%x", &reg);
	xil_printf("%x\n\r", reg);

	return reg;
}

void init_I2C0()
{
	XIicPs_Config *Config;
	int Status;

	xil_printf("INIT_I2C\n\r");
	Config = XIicPs_LookupConfig(IIC_DEVICE_ID);
	if (NULL == Config){
		xil_printf("LOOKUP_FAIL_I2C\n\r");
	}

	Status = XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress); /* I2C0_BASEADDR */
	if (Status != XST_SUCCESS){
		xil_printf("INIT_INSTANCE_FAIL_I2C\n\r");
	}

	Status = XIicPs_SelfTest(&Iic);
	if (Status != XST_SUCCESS){
		xil_printf("SELF_TEST_FAIL_I2C\n\r");
	}

	Status = XIicPs_SetOptions(&Iic, XIICPS_7_BIT_ADDR_OPTION);
	if (Status != XST_SUCCESS){
		xil_printf("SET_OPTION_FAIL_I2C\n\r");
	}

	XIicPs_SetSClk(&Iic, IIC_SCLK_RATE); /* 100kHz */

}

void init_OV9655(XIicPs *IIcPtr)
{
	u8 ReadValue = 0;
	volatile int cpt = 0;
	xil_printf("Coucou config \n\r");
	//////////////////////////////////////////////////////////////
	/* Boucle d'attente avant configuration pour pb d'affichage */
	OV9655_WriteRegister(IIcPtr, OV9655_COM15, RGB_565_OUT_FULL);
	while(cpt < 25000000)
	{
		cpt++;
	}
	cpt = 0;
	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_COM15);
	OV9655_WriteRegister(IIcPtr, OV9655_COM15, RGB_OUT_FULL);
	while(cpt < 25000000)
	{
		cpt++;
	}
	//////////////////////////////////////////////////////////////

	/* Definition Href pour 640x480 */
	xil_printf("Href_Config\n\r");
	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_HREF);
	OV9655_WriteRegister(IIcPtr, OV9655_HREF, 0xBF); // Href LSB

	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_HSTART);
	OV9655_WriteRegister(IIcPtr, OV9655_HSTART, 0x1D); // Hstart = 239

	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_HSTOP);
	OV9655_WriteRegister(IIcPtr, OV9655_HSTOP, 0x6D); // Hstop = 879

	/* Definition Vref pour 640x480 */
	xil_printf("Vref_Config\n\r");
	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_VREF);
	OV9655_WriteRegister(IIcPtr, OV9655_VREF, 0x12); // Vref LSB

	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_VSTART);
	OV9655_WriteRegister(IIcPtr, OV9655_VSTART, 0x01); // Vstart = 10

	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_VSTOP);
	OV9655_WriteRegister(IIcPtr, OV9655_VSTOP, 0x3D); // Vstop = 490

	/* Configuration format de sortie */
	xil_printf("Mode_RGB\n\r");
	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_COM7);
	OV9655_WriteRegister(IIcPtr, OV9655_COM7, (ReadValue & 0b11011111) | OUTPUT_FORMAT_RGB); // Mode RGB
	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_COM7);
	OV9655_WriteRegister(IIcPtr, OV9655_COM7, ReadValue | FORMAT_CTRL_15fpsVGA); // 15fps

	xil_printf("RGB_565\n\r");
	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_COM15);
	OV9655_WriteRegister(IIcPtr, OV9655_COM15, (ReadValue & 0b11011111)| RGB_565_OUT_FULL); // RGB 565 et output full range

	/* Configuration Gain */
	xil_printf("Config_Gain_Image\n\r");
	ReadValue = OV9655_ReadRegister(IIcPtr, OV9655_COM9);
	OV9655_WriteRegister(IIcPtr, OV9655_COM9, (ReadValue & 0b10001111) | GAIN_4x); // Max AGC x4
}

void OV9655_WriteRegister(XIicPs *IIcPtr, u8 RegAddr, u8 RegisterValue)
{
	int Status;
	u8 SendBuffer[2];

	SendBuffer[0] = RegAddr;
	SendBuffer[1] = RegisterValue;

	Status = XIicPs_MasterSendPolled(IIcPtr, SendBuffer, 2, OV9655_DEVICE_WRITE_ADDRESS);
	if (Status != XST_SUCCESS){
		xil_printf("IIC_SEND_FAIL\n\r");
	}

	/* Attente fin communication I2C */
	while (XIicPs_BusIsBusy(IIcPtr)) {}
}

u8 OV9655_ReadRegister(XIicPs *IIcPtr, u8 RegAddr)
{
	int Status;
	u8 RecvBuffer[1]={0};
	u8 SendBuffer[1];

	SendBuffer[0]=RegAddr;

	Status = XIicPs_MasterSendPolled(IIcPtr, SendBuffer, 1, OV9655_DEVICE_WRITE_ADDRESS);
	if (Status != XST_SUCCESS){
		xil_printf("IIC_SEND_FAIL\n\r");
	}

	/* Attente fin communication I2C */
	while (XIicPs_BusIsBusy(IIcPtr)) {}

	Status = XIicPs_MasterRecvPolled(IIcPtr, RecvBuffer, 1, OV9655_DEVICE_READ_ADDRESS);
	if (Status != XST_SUCCESS){
		xil_printf("IIC_RECEIVE_FAIL\n\r");
	}

	/* Attente fin communication I2C */
	while (XIicPs_BusIsBusy(IIcPtr)) {}

	return RecvBuffer[0];
}

