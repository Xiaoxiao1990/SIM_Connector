# SIM_Connector
This is a test for STM8S003K3 to read the SIM card. 
Before to connect with the SIM card,we should confirm that the MCU physically connected to the SIM PINs.The connect pin map below:
 ========================
|   SIM CARD    |  MCU   |
 ------------------------
|   GND         |  GND   |
 ------------------------
|   VCC         |  VCC   |
 ------------------------
|   VPP         |  NC    |
 ------------------------
|   RST         |  PD4   |
 ------------------------
|   IO          |  PD5/6 |
 ------------------------
|   CLK         |  PC4   |
 ------------------------
 Note: 
 1. VPP is not use,thus none connet.
 2. IO is is connect to the UART,Rx & Tx.
 3. CLK is supply by CLK_COO,output by MCU fcpu/4 (2Mhz).

About protocal. Ref. ISO-7816-1,2,3,4

OK,Let's go!
