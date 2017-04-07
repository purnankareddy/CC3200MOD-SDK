/*
 * Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */
#include <string.h>
//#include <list.h>
/*
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#ifndef MSOCK_H
#define MSOCK_H

// this is for windows compat
#define SOCKET int

#ifdef __MINGW32__ 
#undef SOCKET
#undef socklen_t 
#define WINVER 0x0501 
#include <ws2tcpip.h> 
#define EWOULDBLOCK WSAEWOULDBLOCK
#define close closesocket
#define socklen_t int
typedef unsigned int in_addr_t;
#else
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <sys/un.h>
//#include <netinet/tcp.h>
//#include <arpa/inet.h>
#include <netdb.h>
#endif
#ifndef IPV6_ADD_MEMBERSHIP
#define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#endif
*/
#include <stdio.h>
#include <ti/sysbios/knl/Task.h>
#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"
#include "aws_iot_config.h"


#include "pin_mux_config.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "gpio.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"


#include "wificonfig.h"

//------from adc example--------///
// Standard includes
//#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Driverlib includes
#include "utils.h"
//#include "hw_memmap.h"
#include "hw_common_reg.h"
//#include "hw_types.h"
#include "hw_adc.h"
#include "hw_ints.h"
#include "hw_gprcm.h"
//#include "rom.h"
//#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "uart.h"
//#include "pinmux.h"
#include "pin.h"
#include "adc.h"

//#include "adc_userinput.h"
//#include "common/uart_if.h"
//#include "common/common.h"
/////-------------/////
#include "common/udma_if.h"
//#include "common/common.h"
#ifndef NOTERM
#include "common/uart_if.h"
#include "common/uart_if.c"
#endif

// custom headers and defines for udp socket..
#include "../../../../configure.h"
//  From SNTP

#include <time.h>

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/hal/Seconds.h>
#include <ti/net/sntp/sntp.h>

#include <simplelink.h>
#include <socket.h>

////--------added for http-------///////
////----------added for ota--------//////////
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// simplelink includes
//#include <simplelink.h>
#include <wlan.h>
//#include <nonos.h>

// driverlib includes
#include "hw_ints.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "utils.h"
#include "uart.h"

// common interface includes
//#include "udma_if.h"
//#include "common.h"
//#include "uart_if.h"
//#include "button_if.h"
//#include "net.h"

//#include "pinmux.h"
/*#include "../../../../simplelink_extlib/include/flc_api.h"
#include "../../../../simplelink_extlib/flc/flc.h"
#include "../../../../simplelink_extlib/include/ota_api.h"*/
#include "flc_api.h"
#include "flc.h"
//#include "ota.h"
#include "ota_api.h"
#include "otaconfig.h"
//#include "time.h"
//#include "task.h"
////--------------------------------//////////////

#include "jsmn.h"
void philiphsidread();
int flashFiledevice(const char *path, const unsigned char *buffer, int len);
extern void NetWiFi_init(void);
char DeviceID[20];// = "DXTRPIE1";
char philips_id[41];// = "3351225515126c7313ee321303497f3";
char philipsgetdata[1500];
int id_len;
int philips_config=0;
int philipsconfigstatus=0;
int devicestate=1;
char philips_uri[15];
char belkin_uri[10][15];
char HOST_NAME[15];
char PUT_DATA[52];
char philips_request_uri[100];
int HOST_PORT=0;
int philipsgetbulbsstatus = 0;
int updateotavariable = 0;

char dexterpistring[100];
int enddevicestatus=0;//when new ip of philips or belkin discovered it is high to send mqtt message of all ips
static int philipsidstatus=0;//if it is 0 that is there is no philips user id. if it is 1 means we have to press link button. if it is 2 we have philips user id
int philipsipstatus=0;//
int belkinipstatus=0;//
int philipsget=0;//we have to make it high to decode the json format for philips get in parse json.
int philipsbulbget=0;//it is high when individual bulb is controlled and to decode the 1st key in json decode to get the status of that bulb.
int philipssinglebulbget=0;//it is high in the json pase decode after get the 1st key. if it is high mqtt message will send to philipsbulbdetais topic.
char bulbnumber[2];//it is used to store the philips bulb id when it is controlled. 
char belkinstatus[10][2];//it is the on off status of the belkins
//belkinstatus[9]={0,0,0};

//////--------hardcoded philips user id----------///////////
//strcpy(philips_id,"3351225515126c7313ee321303497f3");
////////////////


// HTTP Client lib
//#include </home/mdubuntu/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/netapps/http/client/httpcli.h>
//#include </home/mdubuntu/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/netapps/http/client/common.h>

#include <ti/net/http/httpcli.h>
#include <ti/net/http/httpcli.c>
#include <ti/net/http/httpstd.c>
//#include</home/mdubuntu/ti/tirex-content/CC3200SDK_1.1.0/cc3200-sdk/netapps/http/client/httpcli.h>
// For SimpleLink, *********  include sssl.h add ~/ti/<tirtos_cc32xx_x_xx_xx_xx>/products/ns_1_11_00_10/packages/ti/net/http/
#include <ti/net/http/sssl.h>
//#define PUT_REQUEST_URI 	"/api/3351225515126c7313ee321303497f3/lights/1/state"
//#define PUT_DATA            "{\"on\":false}"
#define PUT_DATA1            "{\"on\":true}"
#define PUT_DATA2            "{\"on\":false}"

#define POST_REQUEST_URI 	"/upnp/control/basicevent1"
//#define POST_DATA           "{\n\"name\":\"xyz\",\n\"address\":\n{\n\"plot#\":12,\n\"street\":\"abc\",\n\"city\":\"ijk\"\n},\n\"age\":30\n}"
#define POST_DATA "<?xml version=\"1.0\" encoding=\"utf-8\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:SetBinaryState xmlns:u=\"urn:Belkin:service:basicevent:1\"><BinaryState>0</BinaryState></u:SetBinaryState></s:Body></s:Envelope>"

#define POST_DATA1 "<?xml version=\"1.0\" encoding=\"utf-8\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:SetBinaryState xmlns:u=\"urn:Belkin:service:basicevent:1\"><BinaryState>1</BinaryState></u:SetBinaryState></s:Body></s:Envelope>"


//#define GET_REQUEST_URI 	"/api/3351225515126c7313ee321303497f3/lights"

#define CONFIG_URI              "/api"
#define CONFIG_DATA		"{\"devicetype\":\"my_hue_app#iphone peter\"}"

//#define sdata  "{\"on\":true}"
//#define HOST_NAME       	"192.168.0.115" //"<host name>"for philips
//#define HOST_PORT 80 //for philips

//#define HOST_NAME       	"192.168.0.108" //"<host name>"fpr belkin
//#define HOST_PORT           49153  //for belkin

#define READ_SIZE           1450
#define MAX_BUFF_SIZE       1460

// from udp//
#define IP_ADDR            0xEFFFFFFA   /* 239.255.255.250 unsigned int ip= 4026531834; */
#define PORT_NUM           1900
#define BUF_SIZE           1400
#define UDP_PACKET_COUNT   10    // default 1000

#define REV_IP(X) ((X << 24) | (( X & 0xff00 ) << 8) | (( X >> 8) & 0xff00 ) | ( X >> 24 ))

#define HELLO_PORT 1900
#define HELLO_GROUP "239.255.255.250"
#define MSGBUFSIZE 576
//#define path "/cert/deviceid.txt"
///////added for wifi reset////////
#define WLAN_DEL_ALL_PROFILES   0xFF

#include "Board.h"
void deviceidlenread();
void deviceidread();
extern void smartConfigFxn();

void RebootMCU();

float power(int ch_no);

/////------from udp-----///////// 
//int BsdUdpClient(unsigned short usPort);
//int BsdUdpServer(unsigned short usPort);
static void InitializeAppVariables();
//////-------------///////////

// Application specific status/error codes
typedef enum{
 /* Choosing this number to avoid overlap with host-driver's error codes */
    SOCKET_CREATE_ERROR = -0x7D0,
    BIND_ERROR = SOCKET_CREATE_ERROR - 1,
    SEND_ERROR = BIND_ERROR - 1,
    RECV_ERROR = SEND_ERROR -1,
    SOCKET_CLOSE = RECV_ERROR -1,
/*  Normal */

    DEVICE_NOT_IN_STATION_MODE = -0x7D0,       
    DEVICE_START_FAILED = DEVICE_NOT_IN_STATION_MODE - 1,
    INVALID_HEX_STRING = DEVICE_START_FAILED - 1,
    TCP_RECV_ERROR = INVALID_HEX_STRING - 1,
    TCP_SEND_ERROR = TCP_RECV_ERROR - 1,
    FILE_NOT_FOUND_ERROR = TCP_SEND_ERROR - 1,
    INVALID_SERVER_RESPONSE = FILE_NOT_FOUND_ERROR - 1,
    FORMAT_NOT_SUPPORTED = INVALID_SERVER_RESPONSE - 1,
    FILE_OPEN_FAILED = FORMAT_NOT_SUPPORTED - 1,
    FILE_WRITE_ERROR = FILE_OPEN_FAILED - 1,
    INVALID_FILE = FILE_WRITE_ERROR - 1,
    SERVER_CONNECTION_FAILED = INVALID_FILE - 1,
    GET_HOST_IP_FAILED = SERVER_CONNECTION_FAILED  - 1,
    
    STATUS_CODE_MAX = -0xBB8
}e_AppStatusCodes;

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
volatile unsigned long  g_ulStatus = 0;//SimpleLink Status
unsigned long  g_ulDestinationIP;
unsigned long  g_ulDestinationIp; // IP address of destination server
unsigned long  g_ulGatewayIP = 0; //Network Gateway IP address
//unsigned char  g_ucConnectionSSID[SSID_LEN_MAX+1]; //Connection SSID
//unsigned char  g_ucConnectionBSSID[BSSID_LEN_MAX]; //Connection BSSID
unsigned char g_buff[MAX_BUFF_SIZE+1];
long bytesReceived = 0; // variable to store the file size
//From UDP//
unsigned int   g_uiPortNum = PORT_NUM;
volatile unsigned long  g_ulPacketCount = UDP_PACKET_COUNT;
unsigned char  g_ucSimplelinkstarted = 0;
unsigned long  g_ulIpAddr = 0;
char g_cBsdBuf[BUF_SIZE];
int sizeofdeviceid;

#if defined(ccs) || defined(gcc)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif  
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************

void deviceidlenread();
int UDPRECIEVER();
///////////-----from wifi audio app------------////////////

#define INVALID_CLIENT_ADDRESS            0x00000000 //Invalid clientIP 
//*****************************************************************************
//
// MultiCast Group IP Address (Any IP in Range 224.0.0.0 - 239.255.255.255)
//
//*****************************************************************************
#define ADDR_MULTICAST_GROUP 	   0xE00000FB   //"224.0.0.251" //Using mDNS IP
  
//*****************************************************************************
//
// UDP Socket Port
//
//*****************************************************************************
#define AUDIO_PORT                     (1900)  
//*****************************************************************************
//
// Define Packet Size, Rx and Tx Buffer
//
//*****************************************************************************  
#define PACKET_SIZE             1024
#define PLAY_WATERMARK			30*1024
#define RECORD_BUFFER_SIZE     	10*PACKET_SIZE
#define PLAY_BUFFER_SIZE        70*PACKET_SIZE
//*****************************************************************************
//
// UDP Socket Structure
//
//***************************************************************************** 
typedef struct UDPSocket
{
    int iSockDesc; //Socket FD
    struct sockaddr_in Server; //Address to Bind - INADDR_ANY for Local IP
    struct sockaddr_in Client; //Client Address or Multicast Group
    int iServerLength;
    int iClientLength;
}tUDPSocket;
/*int sn =0;
struct belkinips{
	int id;
	char bname[5];
	char ip[15];
};
struct node{
	struct belkinips bel;
	struct node *link;
};
struct node *head=NULL,*tail=NULL;

struct philips{
	int id;
	char pname[7];
	char ip[15];
}*philipsip;
*/
struct philips_status{
	char bid[2];
	char statuses[400];
//	char type[20];
//	char name[20];
//	char state[5];
//	char bright[4];
//	char reachable[5];
}p_bulbs;

struct philips_status *p_bulb; 
 
void deviceidlenread()
{  
    //char path[] = "/cert/deviceid.txt";
    const char* path="deviceidlen.txt";
     //unsigned char *path = "deviceid.txt";
//    unsigned char *buffer;
//int dlen = strlen(deviceID);
//flashFiledevice(path, (unsigned char *)deviceID, dlen);HIVEPIE-25614
//unsigned char buffers[30];
    int len = 2;
    int buffers;
    //int len = 13;
    long rets;
    long fileHandles = -1;
    unsigned long ulToken;
    //IOT_INFO("file is opening..........\n");
    //ret = sl_FsOpen((unsigned char *)path,FS_MODE_OPEN_CREATE(len,  _FS_FILE_PUBLIC_READ), NULL,&fileHandle);
    //ret = sl_FsOpen((unsigned char *)path, FS_MODE_OPEN_READ, NULL, &fileHandle);
    rets = sl_FsOpen((unsigned char *)path, FS_MODE_OPEN_READ, NULL, &fileHandles);
    //ret = sl_FsOpen("/cert/deviceid.txt",FS_MODE_OPEN_READ, NULL,&fileHandle);
    //IOT_INFO("sl_fsopen ret value is %d\n",rets);
    //ret = sl_FsRead(fileHandle, 0, (unsigned char  *)buffer, len);
    rets = sl_FsRead(fileHandles, 0,buffers, len);
    //buffers[len]='\0';

    ////System_printf("Data in the file is: %s\n",(unsigned char  *)buffer);
    //deviceID=(unsigned char  *)buffer;
    //strcpy(DeviceID,(unsigned char  *)buffer);
    //System_printf("Data in the file is: %s\n",buffers);
    //deviceID=(unsigned char  *)buffer;
    sizeofdeviceid=buffers;
    IOT_INFO("size of the deviceid is %d\n",sizeofdeviceid);
    //strcpy(pubtopName,DeviceID);
    //strcat(pubtopName,"/sub");
    //#ifdef AWS_IOT_MY_THING_NAME
    //#define AWS_IOT_MY_THING_NAME DeviceID
    //#endif

    //#ifdef AWS_IOT_MQTT_CLIENT_ID 
    //#define AWS_IOT_MQTT_CLIENT_ID DeviceID
    //#endif

    rets = sl_FsClose(fileHandles, NULL, NULL, 0);


}
////////////---------------////////  

//
void deviceidread()
{  
    //char path[] = "/cert/deviceid.txt";
    const char* path="deviceid.txt";
     //unsigned char *path = "deviceid.txt";
//    unsigned char *buffer;
//int dlen = strlen(deviceID);
//flashFiledevice(path, (unsigned char *)deviceID, dlen);HIVEPIE-25614
unsigned char buffers[30];
    int len = SIZEOFID;
    //int len = sizeofdeviceid;
    long rets;
    long fileHandles = -1;
    unsigned long ulToken;
    IOT_INFO("file is opening..........\n");
    //ret = sl_FsOpen((unsigned char *)path,FS_MODE_OPEN_CREATE(len,  _FS_FILE_PUBLIC_READ), NULL,&fileHandle);
    //ret = sl_FsOpen((unsigned char *)path, FS_MODE_OPEN_READ, NULL, &fileHandle);
    rets = sl_FsOpen((unsigned char *)path, FS_MODE_OPEN_READ, NULL, &fileHandles);
    //ret = sl_FsOpen("/cert/deviceid.txt",FS_MODE_OPEN_READ, NULL,&fileHandle);
    IOT_INFO("sl_fsopen ret value is %d\n",rets);
    //ret = sl_FsRead(fileHandle, 0, (unsigned char  *)buffer, len);
    rets = sl_FsRead(fileHandles, 0,buffers, len);
    buffers[len]='\0';

    //System_printf("Data in the file is: %s\n",(unsigned char  *)buffer);
    //deviceID=(unsigned char  *)buffer;
    //strcpy(DeviceID,(unsigned char  *)buffer);
    System_printf("Data in the file is: %s\n",buffers);
    //deviceID=(unsigned char  *)buffer;
    strcpy(DeviceID,buffers);
    strcpy(pubtopName,DeviceID);
    strcat(pubtopName,"/sub");
    #ifdef AWS_IOT_MY_THING_NAME
    #define AWS_IOT_MY_THING_NAME DeviceID
    #endif

    #ifdef AWS_IOT_MQTT_CLIENT_ID 
    #define AWS_IOT_MQTT_CLIENT_ID DeviceID
    #endif

    rets = sl_FsClose(fileHandles, NULL, NULL, 0);

 /*      const char DeviceFileName[] = "MyFile.txt";
       unsigned long   MaxSize = 63; //62.5K is max file size
       long            DeviceFileHandle = -1;
       long            RetVal;        //negative retval is an error
       unsigned long   Offset = 0;
       unsigned char   InputBuffer[100];
       IOT_INFO("file is opening. the path of the file is %s\n",(unsigned char *)DeviceFileName);
       // Create a file and write data. The file in this example is secured, without signature and with a fail safe commit
       RetVal = sl_FsOpen((unsigned char *)DeviceFileName,
                                        FS_MODE_OPEN_CREATE(MaxSize , _FS_FILE_OPEN_FLAG_NO_SIGNATURE_TEST | _FS_FILE_OPEN_FLAG_COMMIT ),
                                        NULL, &DeviceFileHandle);
       IOT_INFO("file is opened\n");

       Offset = 0;
       //Preferred in secure file that the Offset and the length will be aligned to 16 bytes.
       RetVal = sl_FsWrite( DeviceFileHandle, Offset, (unsigned char *)"HelloWorld", strlen("HelloWorld"));

       RetVal = sl_FsClose(DeviceFileHandle, NULL, NULL , 0);

       // open the same file for read, using the Token we got from the creation procedure above
       RetVal = sl_FsOpen((unsigned char *)DeviceFileName,
                                        FS_MODE_OPEN_READ,
                                        NULL, &DeviceFileHandle);

       Offset = 0;
       RetVal = sl_FsRead( DeviceFileHandle, Offset, (unsigned char *)InputBuffer, strlen("HelloWorld"));

       RetVal = sl_FsClose(DeviceFileHandle, NULL, NULL , 0);
      IOT_INFO("data in file is %s\n",(unsigned char *)InputBuffer);*/

/*
char sentence[1000];
   FILE *fptr;
  char c[1000];
   fptr = fopen("program.txt", "w");
   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }
   
   printf("Enter a sentence:\n");
   //gets(sentence);
   strcpy(sentence,"this is a trail program\n");
   fprintf(fptr,"%s", sentence);
   fclose(fptr);


if ((fptr = fopen("program.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        exit(1);         
    }

    // reads text until newline 
    fscanf(fptr,"%[^\n]", c);

    printf("Data from the file:\n%s", c);
    fclose(fptr);
*/
}
////////////---------------////////       

int flashFiledevice(const char *path, const unsigned char *buffer, int len)
{
    long ret;
    long fileHandle;

    if (!path || !buffer) {
        System_printf("flashfile: Error invalid input params\n");
        ret = -1;
        goto flashdone;
    }

    ret = sl_FsOpen((unsigned char *)path,
            FS_MODE_OPEN_CREATE(len, _FS_FILE_OPEN_FLAG_NO_SIGNATURE_TEST | _FS_FILE_OPEN_FLAG_COMMIT), NULL,
            &fileHandle);
    if (ret < 0) {
        System_printf("flashfile: Error couldn't open the file %s"
                ", error code = %d\n", path, ret);
        ret = -1;
        goto flashdone;
    }

    ret = sl_FsWrite(fileHandle, 0, (unsigned char *)buffer, len);
    if (ret < 0) {
        sl_FsClose(fileHandle, NULL, NULL, 0);

        System_printf("flashfile: Error couldn't write to the file %s"
                ", error code = %d\n", path, ret);
        ret = -1;
        goto flashdone;
    }

    ret = sl_FsClose(fileHandle, NULL, NULL, 0);
    if (ret < 0) {
        System_printf("flashfile: Error couldn't close to the file %s"
                ", error code = %d\n", path, ret);
        ret = -1;
        goto flashdone;
    }

    ret = 0;

flashdone:
    return (ret);
}

void philiphsidread()
{
    const char* path="philipsid.txt";
    unsigned char buffers[41];
    int len = 41;
    long rets;
    long fileHandles = -1;
    unsigned long ulToken;
    IOT_INFO("file is opening..........\n");
    rets = sl_FsOpen((unsigned char *)path, FS_MODE_OPEN_READ, NULL, &fileHandles);
    if (rets < 0){
		IOT_INFO("philipsid.txt file is not created");
		philipsidstatus = 0;	
		}
    else{
    	IOT_INFO("sl_fsopen ret value is %d\n",rets);
    	rets = sl_FsRead(fileHandles, 0, buffers, len);
    	buffers[len]="\0";
    	System_printf("Data in the file is: %s\n",buffers);
    	if (buffers[0] != "\0"){
    		strcpy(philips_id,buffers);
		philips_id[len]="\0";
    		philipsidstatus = 2;
		}
    	rets = sl_FsClose(fileHandles, NULL, NULL, 0);
	}
}


  

char timeslap[100];
char userid[10];//user id from app or ui in gpio command

///////-------------///////
void sstartNTP(void)
{
    //int ret;
    //unsigned long ip;
    time_t ts;
    ts = time(NULL);
    System_printf("Current time: %s\n", ctime(&ts));
    strncpy(timeslap,ctime(&ts),strlen(ctime(&ts))); 
    
}
//---------------------------------///
static void InitializeAppVariables()
{
    g_ulStatus = 0;
    g_ulGatewayIP = 0;
  //  memset(g_ucConnectionSSID,0,sizeof(g_ucConnectionSSID));
  //  memset(g_ucConnectionBSSID,0,sizeof(g_ucConnectionBSSID));
    g_ulDestinationIp = IP_ADDR;
    g_uiPortNum = PORT_NUM;
    g_ulPacketCount = UDP_PACKET_COUNT;
}

int PWR1=0,PWR2=0,PWR3=0,PWR4=0;
float Power1[10],Power2[10],Power3[10],Power4[10];
int i1=0,j1=0,k1=0,l1=0;
int Phantom_var1=0,Phantom_var2=0,Phantom_var3=0,Phantom_var4=0;
int Phantom_buff=0;
int variable=1;
int max1=0,max2=0,max3=0,max4=0;
////    Power Storing ////

void dynamic_power_1(void)
{
int i=0,temp=0;

while(1)
{
	Phantom_buff=0;
	IOT_INFO("....Dynamic Power-1....\n");

        if(i1==10)
               i1=0;
        if(j1==10)
               j1=0;
        if(k1==10)
               k1=0;
        if(l1==10)
               l1=0;
               
        if(PWR1==1){
		IOT_INFO("....Dynamic Power-1  --- socket- 1....\n");
                Power1[i1++]=power(1);
        }
        if(PWR2==1){
		IOT_INFO("....Dynamic Power-1  --- socket- 2....\n");
                Power2[j1++]=power(2);
        }
        if(PWR3==1){
		IOT_INFO("....Dynamic Power-1  --- socket- 3....\n");
                Power3[k1++]=power(3);
        }
        if(PWR4==1){
		IOT_INFO("....Dynamic Power-1  --- socket- 4....\n");
                Power4[l1++]=power(4);
        }
	

	//first power array veryvifing...
	IOT_INFO("....Dynamic Power-2....\n");
	if(PWR1==1){
	IOT_INFO("....Dynamic Power-2  --- socket- 1....\n");
	for(i=0;i<i1;i++){
	        if(max1 < Power1[i]){
	                max1 = Power1[i];
	        }
	}
	for(i=0;i<i1;i++){
	        if((max1/4) >= Power1[i]){
	                Phantom_var1=1;
	                Phantom_buff=1;
			i1--;
	                }else
	                Phantom_var1=0;
	}
	}
	//Second power array veryvifing...
	if(PWR2==1){
	IOT_INFO("....Dynamic Power-2  --- socket- 2....\n");
	for(i=0;i<j1;i++){
        if(max2 < Power2[i]){
	                max2 = Power2[i];
	        }
	}
	for(i=0;i<j1;i++){
	        if((max2/4) >= Power2[i]){
	                Phantom_var2=1;
	                Phantom_buff=1;
			j1--;
	                }else
	                Phantom_var2=0;
	}
	}
	//third power array veryvifing...
	if(PWR3==1){
	IOT_INFO("....Dynamic Power-2  --- socket- 3....\n");
	for(i=0;i<k1;i++){
	        if(max3 < Power3[i]){
	                max3 = Power3[i];
	        }
	}
	for(i=0;i<k1;i++){
	        if((max3/4) >= Power3[i]){
	                Phantom_var3=1;
	                Phantom_buff=1;
			k1--;
	                }else
	                Phantom_var3=0;
	}
	}
	//fourth power array veryvifing...
	if(PWR4==1){
	IOT_INFO("....Dynamic Power-2  --- socket- 4....\n");
	for(i=0;i<l1;i++){
	        if(max4 < Power4[i]){
	                max4 = Power4[i];
	        }
		}
	for(i=0;i<l1;i++){
	        if((max4/4) >= Power4[i]){
	                Phantom_var4=1;
	                Phantom_buff=1;
			l1--;
	                }else
	                Phantom_var4=0;
		}
	}
/*
	for(temp=0;((temp<l1)||(temp<k1)||(temp<j1)||(temp<i1));temp++)
	{
		IOT_INFO("Dynamic power ...\n\tSocket-1: %f \n\tSocket-2: %f \n\tSocket-3: %f \n\tSocket-4: %f \n",Power1[temp],Power2[temp],Power3[temp],Power4[temp]);
	}
*/
	int i2=i1,j2=j1,k2=k1,l2=l1;
	IOT_INFO("\nDynamic Power Calculations in Array: \n");	
	for(temp=0;((temp<l1)||(temp<k1)||(temp<j1)||(temp<i1));temp++)
	{
		if(temp<i2){
			IOT_INFO("Socket-1: %f \n",Power1[temp]);
		}
		if(temp<j2){
			IOT_INFO("Socket-2: %f \n",Power2[temp]);
		}
		if(temp<k2){
			IOT_INFO("Socket-3: %f \n",Power2[temp]);
		}
		if(temp<l2){
			IOT_INFO("Socket-4: %f \n",Power2[temp]);
		}
	}


/*
if(variable==1)
	Task_sleep(1000);
else if(variable == 0)
	Task_sleep(5000);
else 
	Task_sleep(1000);
*/
	if(PWR1==1 || PWR2 == 1 || PWR3 == 1 || PWR4 ==1){
		if(Phantom_buff==1)
			Task_sleep(20000);
		else
			Task_sleep(2000);//300000);
		} //300000
	else
		Task_sleep(1000);

}
}


/////  Dynamic Power Detection ////
void dynamic_power_2(void)
{
int i=0,max=0;
while(1){

//first power array veryvifing...
IOT_INFO("....Dynamic Power-2....\n");
if(PWR1==1){
IOT_INFO("....Dynamic Power-2  --- socket- 1....\n");
for(i=0;i<i1;i++){
        if(max < Power1[i]){
                max = Power1[i];
        }
}
for(i=0;i<i1;i++){
        if((max/4) <= Power1[i]){
                Phantom_var1=1;
                Phantom_buff=1;
                }else
                Phantom_var1=0;
}
}
//Second power array veryvifing...
if(PWR2==1){
IOT_INFO("....Dynamic Power-2  --- socket- 2....\n");
for(i=0;i<j1;i++){
        if(max < Power2[i]){
                max = Power2[i];
        }
}
for(i=0;i<j1;i++){
        if((max/4) <= Power2[i]){
                Phantom_var2=1;
                Phantom_buff=1;
                }else
                Phantom_var2=0;
}
}
//third power array veryvifing...
if(PWR3==1){
IOT_INFO("....Dynamic Power-2  --- socket- 3....\n");
for(i=0;i<k1;i++){
        if(max < Power3[i]){
                max = Power3[i];
        }
}
for(i=0;i<k1;i++){
        if((max/4) <= Power3[i]){
                Phantom_var3=1;
                Phantom_buff=1;
                }else
                Phantom_var3=0;
}
}
//fourth power array veryvifing...
if(PWR4==1){
IOT_INFO("....Dynamic Power-2  --- socket- 4....\n");
for(i=0;i<l1;i++){
        if(max < Power4[i]){
                max = Power4[i];
        }
}
for(i=0;i<l1;i++){
        if((max/4) <= Power4[i]){
                Phantom_var4=1;
                Phantom_buff=1;
                }else
                Phantom_var4=0;
}
}
        Task_sleep(1000);
}
}
///vinay ota////////
static OtaOptServerInfo_t g_otaOptServerInfo;
static void *pvOtaApp;
long OptionLen;
unsigned char OptionVal;
int SetCommitInt = 1;
unsigned char ucVendorStr[20];
void NetMACAddressGet(unsigned char *pMACAddress)
{
    unsigned char macAddressLen = SL_MAC_ADDR_LEN;

    //
    // Get the MAC address
    //
    sl_NetCfgGet(SL_MAC_ADDRESS_GET, NULL, &macAddressLen, pMACAddress);

}
int OTAServerInfoSet(void **pvOtaApp, char *vendorStr)
{

    unsigned char macAddressLen = SL_MAC_ADDR_LEN;
    //
    // Set OTA server info
    //
    g_otaOptServerInfo.ip_address = OTA_SERVER_IP_ADDRESS;
    g_otaOptServerInfo.secured_connection = OTA_SERVER_SECURED;
    strcpy((char *)g_otaOptServerInfo.server_domain, OTA_SERVER_NAME);
    strcpy((char *)g_otaOptServerInfo.rest_update_chk, OTA_SERVER_REST_UPDATE_CHK);
    strcpy((char *)g_otaOptServerInfo.rest_rsrc_metadata, OTA_SERVER_REST_RSRC_METADATA);
    strcpy((char *)g_otaOptServerInfo.rest_hdr, OTA_SERVER_REST_HDR);
    strcpy((char *)g_otaOptServerInfo.rest_hdr_val, OTA_SERVER_REST_HDR_VAL);
    strcpy((char *)g_otaOptServerInfo.log_server_name, LOG_SERVER_NAME);
    strcpy((char *)g_otaOptServerInfo.rest_files_put, OTA_SERVER_REST_FILES_PUT);
    NetMACAddressGet((_u8 *)g_otaOptServerInfo.log_mac_address); 
    //sl_NetCfgGet(SL_MAC_ADDRESS_GET, NULL, &macAddressLen,(_u8 *)g_otaOptServerInfo.log_mac_address);
   IOT_INFO("mac id is %x.....",(_u8 *)g_otaOptServerInfo.log_mac_address);


    //
    // Set OTA server Info
    //
    sl_extLib_OtaSet(*pvOtaApp, EXTLIB_OTA_SET_OPT_SERVER_INFO,
                     sizeof(g_otaOptServerInfo), (_u8 *)&g_otaOptServerInfo);

    //
    // Set vendor ID.
    //
    sl_extLib_OtaSet(*pvOtaApp, EXTLIB_OTA_SET_OPT_VENDOR_ID, strlen(vendorStr),
                     (_u8 *)vendorStr);

    //
    // Return ok status
    //
    return RUN_STAT_OK;
}
//static void RebootMCU()
void RebootMCU()
{

  //
  // Configure hibernate RTC wakeup
  //
  PRCMHibernateWakeupSourceEnable(PRCM_HIB_SLOW_CLK_CTR);

  //
  // Delay loop
  //
  MAP_UtilsDelay(8000000);

  //
  // Set wake up time
  //
  PRCMHibernateIntervalSet(330);

  //
  // Request hibernate
  //
  PRCMHibernateEnter();

  //
  // Control should never reach here
  //
  while(1)
  {

  }
}

////////////
/////vinay udp/////////
int r=0;
char enddevicemname[8];
char enddeviceip[15];
void vinayudp(void)
{
      sockaddr_in addr;
     int fd, nbytes,addrlen;
     //ip_mreq mreq;
     SlSockIpMreq mreq;
	//struct_sl_sock_ip_mreq mreq;
     char msgbuf[MSGBUFSIZE];

char sendmessage[70]; int cnt;

     unsigned int yes=1;            /*** MODIFICATION TO ORIGINAL */

     /* create what looks like an ordinary UDP socket */
     if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
	  //perror("socket");
	  //exit(1);
	 IOT_INFO("....socket creation failed....\n");
     }


/**** MODIFICATION TO ORIGINAL */
    /* allow multiple sockets to use the same PORT number */
   /* if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
       //perror("Reusing ADDR failed");
       //exit(1);
	IOT_INFO(".....setsockopt failed.....\n");
       }*/
/*** END OF MODIFICATION TO ORIGINAL */

     /* set up destination address */
     memset(&addr,0,sizeof(addr));
     addr.sin_family=AF_INET;
     //addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
     addr.sin_port=htons(HELLO_PORT);


addr.sin_addr.s_addr=htonl(HELLO_GROUP);

sprintf(sendmessage,"Hiveypie is online. device id is %s",DeviceID);
IOT_INFO(".......sending message...........%s\n",sendmessage);
cnt = sendto(fd,sendmessage,sizeof(sendmessage),0,(struct sockaddr *) &addr,sizeof(addr));
if (cnt < 0){
IOT_INFO(".........sending failed........\n");
}
//if(cnt >= 0){
//IOT_INFO(".......sending message...........%s\n",sendmessage);
//}


addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */

     
     /* bind to receive address */
     if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
	 // perror("bind");
	 // exit(1);
	IOT_INFO("....bind failed....\n");
     }
     
     /* use setsockopt() to request that the kernel join a multicast group */
     //mreq.imr_multiaddr.s_addr=inet_addr(HELLO_GROUP);
	//mreq.imr_multiaddr.s_addr=htonl(HELLO_GROUP);
       mreq.imr_multiaddr.s_addr=sl_Htonl((unsigned int)IP_ADDR);
     mreq.imr_interface.s_addr=htonl(INADDR_ANY);
     if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
	  //perror("setsockopt");
	  //exit(1);
	  IOT_INFO("......setsockopt failed.....\n");
     }
	int udppackets=0,a=0,b=0;
     /* now just enter a read-print loop */
     while (1) {
	  addrlen=sizeof(addr);
	  if ((nbytes=recvfrom(fd,msgbuf,MSGBUFSIZE,0,
			       (struct sockaddr *) &addr,&addrlen)) < 0) {
	       //perror("recvfrom");
	       //exit(1);
		IOT_INFO(".....recvfrom failed.....\n");
	  }
	 // puts(message);
		//IOT_INFO("....%s.....",msgbuf);
		IOT_INFO("....%d.....",(unsigned int)addr.sin_addr.s_addr);
		IOT_INFO("....%x.....",addr.sin_addr.s_addr);
		IOT_INFO("....%x.....",REV_IP(addr.sin_addr.s_addr));
		unsigned int val = REV_IP(addr.sin_addr.s_addr);

			

		IOT_INFO("%d.%d.%d.%d",(val & 0xFF000000) >> 24,(val & 0x00FF0000) >> 16,(val & 0x0000FF00) >> 8,val & 0x000000FF);
		udppackets++;
		IOT_INFO("---udppackets received  %d-----\n",udppackets);
		if(a==0 || b<=10)
		{
			if(a==0)
			{
				if( strstr(msgbuf,"IpBridge"))
				{
					IOT_INFO("philips bridge ip is ---%d.%d.%d.%d",(val & 0xFF000000) >> 24,(val & 0x00FF0000) >> 16,(val & 0x0000FF00) >> 8,val & 0x000000FF);
			
					sprintf(philips_uri,"%d.%d.%d.%d",(val & 0xFF000000) >> 24,(val & 0x00FF0000) >> 16,(val & 0x0000FF00) >> 8,val & 0x000000FF);
					IOT_INFO("-------%s------\n",philips_uri);
					//*philipsip->id=a++;
					//strcpy(*philipsip->ip,philips_uri);
					//strcpy(*philipsip->pname,"Philips");
					a=1;
					philipsipstatus=1;
					enddevicestatus=1;
					if (philipsidstatus == 2){
						//Task_sleep(6000);
						//strncpy(dexterpistring,"get philips ",12);
						//strcat(dexterpistring,"\0");
                                         philipsgetbulbsstatus = 1;
					}
				}
			}
			if(b<10)
			{
				if(strstr(msgbuf,"NOTIFY") && strstr(msgbuf,"Belkin") && strstr(msgbuf,"http://schemas.upnp.org/upnp/1/0/")&& !strstr(msgbuf,"IpBridge"))
				{
					int find=0;
					IOT_INFO("belkin ip is ---%d.%d.%d.%d\n",(val & 0xFF000000) >> 24,(val & 0x00FF0000) >> 16,(val & 0x0000FF00) >> 8,val & 0x000000FF);
					char uri[15],Bel[5]="Bel";
					int i=0;
					sprintf(uri,"%d.%d.%d.%d",(val & 0xFF000000) >> 24,(val & 0x00FF0000) >> 16,(val & 0x0000FF00) >> 8,val & 0x000000FF);
					IOT_INFO("uri is : %s",uri);
					/*
					if(head == NULL){
					struct node *n1=(struct node *)malloc(sizeof(struct node));
					n1->bel.id=sn++;
					strcpy(n1->bel.ip,uri);
					strcat(Bel,sn);
					strcpy(n1->bel.bname,Bel);
					n1->link=NULL;
					head=n1;
					tail=n1;
					}else if(head != NULL){
						struct node *temp=head;
						while(temp->link != NULL){
							if(strcmp(temp->bel.ip,uri))
								temp = temp->link;}
						struct node *new=(struct node *)malloc(sizeof(struct node));
						new->Bel.id=sn++;
						strcpy(new->bel.ip,uri);
						strcat(Bel,sn);
						strcpy(new->bel.bname,Bel);
						new->link=NULL;
						tail = new;
					}*/
					for(i=0;i<10;i++)
					{
						if(!strcmp(belkin_uri[i],uri))
						{
							IOT_INFO("belkin_uri[%d]: {%s} is same as uri{%s}",i,belkin_uri[i],uri);
							find=1;
							break;
						}
					}
					if(find == 1){
						continue;
					}
					else{ 
						strcpy(belkin_uri[r++],uri);
						IOT_INFO("belkin_uri[%d] is : %s",i,belkin_uri[i]);
					}


					/*
					for (i=0;i<10;i++)
					{
						if(!strcmp(belkin_uri[i],uri))
						{
							IOT_INFO("belkin_uri[%d]{%s} is same as uri{%s}",i,belkin_uri[i],uri);
							i=10;
						}
				
						else if(belkin_uri[i][0]=="\0")
						{
							sprintf(belkin_uri[i],"%d.%d.%d.%d",(val & 0xFF000000) >> 24,(val & 0x00FF0000) >> 16,(val & 0x0000FF00) >> 8,val & 0x000000FF);
							IOT_INFO("belkin_uri[%d] is : %s",i,belkin_uri[i]);
							b++;
							i=10;
							enddevicestatus=1;
						}
					}
			
			
			
					//IOT_INFO("-------%s------\n",belkin_uri[0]);
					//b=1;
					belkinipstatus=1;
					*/
					enddevicestatus=1;
				}
			}
		}
		else;
     }
}

static int ConnectToHTTPServer(HTTPCli_Handle httpClient)
{
    long lRetVal = -1;
    struct sockaddr_in addr;
  
  
    /* Resolve HOST NAME/IP */
    /*lRetVal = sl_NetAppDnsGetHostByName((signed char *)HOST_NAME,
                                          strlen((const char *)HOST_NAME),
                                          &g_ulDestinationIP,SL_AF_INET);  */

	lRetVal = sl_NetAppDnsGetHostByName((signed char *)HOST_NAME,
                                          strlen((const char *)HOST_NAME),
                                          &g_ulDestinationIP,SL_AF_INET);
    if(lRetVal < 0)
    {
       // ASSERT_ON_ERROR(GET_HOST_IP_FAILED);
    }

    /* Set up the input parameters for HTTP Connection */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(HOST_PORT);
    addr.sin_addr.s_addr = sl_Htonl(g_ulDestinationIP);

    /* Testing HTTPCli open call: handle, address params only */
    HTTPCli_construct(httpClient);
    lRetVal = HTTPCli_connect(httpClient, (struct sockaddr *)&addr, 0, NULL);
    if (lRetVal < 0)
    {
        IOT_INFO("Connection to server failed. error(%d)\n\r", lRetVal);
       // ASSERT_ON_ERROR(SERVER_CONNECTION_FAILED);
    }    
    else
    {
        IOT_INFO("Connection to server created successfully\r\n");
    }

    return 0;
}

static void BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs) || defined(gcc)
    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}


//*****************************************************************************
//
//! \brief Flush response body.
//!
//! \param[in]  httpClient - Pointer to HTTP Client instance
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
static int FlushHTTPResponse(HTTPCli_Handle httpClient)
{
    const char *ids[2] = {
                            HTTPStd_FIELD_NAME_CONNECTION, /* App will get connection header value. all others will skip by lib */
                            NULL
                         };
    char buf[128];
    int id;
    int len = 1;
    bool moreFlag = 0;
    char ** prevRespFilelds = NULL;


    /* Store previosly store array if any */
    prevRespFilelds = HTTPCli_setResponseFields(httpClient, ids);

    /* Read response headers */
    while ((id = HTTPCli_getResponseField(httpClient, buf, sizeof(buf), &moreFlag))
            != HTTPCli_FIELD_ID_END)
    {

        if(id == 0)
        {
            if(!strncmp(buf, "close", sizeof("close")))
            {
                IOT_INFO("Connection terminated by server\n\r");
            }
        }

    }

    /* Restore previosuly store array if any */
    HTTPCli_setResponseFields(httpClient, (const char **)prevRespFilelds);

    while(1)
    {
        /* Read response data/body */
        /* Note:
                moreFlag will be set to 1 by HTTPCli_readResponseBody() call, if more
                data is available Or in other words content length > length of buffer.
                The remaining data will be read in subsequent call to HTTPCli_readResponseBody().
                Please refer HTTP Client Libary API documenation @ref HTTPCli_readResponseBody
                for more information.
        */
        HTTPCli_readResponseBody(httpClient, buf, sizeof(buf) - 1, &moreFlag);
        //ASSERT_ON_ERROR(len);

        if ((len - 2) >= 0 && buf[len - 2] == '\r' && buf [len - 1] == '\n'){
            break;
        }

        if(!moreFlag)
        {
            /* There no more data. break the loop. */
            break;
        }
    }
    return 0;
}


//*****************************************************************************
//
//! \brief Handler for parsing JSON data
//!
//! \param[in]  ptr - Pointer to http response body data
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
jsmntok_t   *tokenList;
int noOfToken;
char philipsbulbid[2];
char philipsbulbstatus[400];
int philipsgetstatus=0;
int ParseJSONData(char *ptr)
{
    long lRetVal = 0;
    
    jsmn_parser parser;
    


    /* Initialize JSON PArser */
    jsmn_init(&parser);

    /* Get number of JSON token in stream as we we dont know how many tokens need to pass */
    noOfToken = jsmn_parse(&parser, (const char *)ptr, strlen((const char *)ptr), NULL, 10);
    if(noOfToken <= 0)
    {
    	IOT_INFO("Failed to initialize JSON parser\n\r");
    	return -1;

    }

    /* Allocate memory to store token */
    tokenList = (jsmntok_t *) malloc(noOfToken*sizeof(jsmntok_t));
    if(tokenList == NULL)
    {
        IOT_INFO("Failed to allocate memory\n\r");
        return -1;
    }

    /* Initialize JSON Parser again */
    jsmn_init(&parser);
    noOfToken = jsmn_parse(&parser, (const char *)ptr, strlen((const char *)ptr), tokenList, noOfToken);
    if(noOfToken < 0)
    {
    	IOT_INFO("Failed to parse JSON tokens\n\r");
    	lRetVal = noOfToken;
    }
    else
    {
    	IOT_INFO("Successfully parsed %ld JSON tokens\n\r", noOfToken);
	int i=0;
		
	for(i=0;i<noOfToken;i++){	
	//IOT_INFO("----token[%d] = ",i);
	//IOT_INFO("----%s------\n",tokenList[i]);}
	//IOT_INFO("parser------%s-------\n",&parser);
		jsmntok_t key = tokenList[i];
		unsigned int length = key.end - key.start;
		char keyString[length + 1];    
		memcpy(keyString, &((const char *)ptr)[key.start], length);
		keyString[length] = '\0';
		//if(i == noOfToken){
		  //id_len=sizeof(keyString);
		  //strncpy(keyString,philips_id,id_len);
		  IOT_INFO("i=%d\n",i);
		  IOT_INFO("Key: %s\n", keyString);
		  //IOT_INFO("my Key: %s\n", keyString[1]);
		//}
		if(philipsbulbget==1)
		{
			if(i==0)
			{
				id_len=sizeof(keyString);
				strncpy(philipsbulbstatus,keyString,id_len);
				IOT_INFO("philips bulb status: %s---\n", philipsbulbstatus);
				philipssinglebulbget=1;
			}
			philipsbulbget=0;

		}
		if (philips_config==1){
		if(i == noOfToken-1){
			
			IOT_INFO("philips config---\n");
			if((strcmp(keyString,"link button not pressed"))==0)
			{
				philipsidstatus=1;
				enddevicestatus=1;
			}
			else
			{
				id_len=sizeof(keyString);
				strncpy(philips_id,keyString,id_len);
				IOT_INFO("philips id: %s---\n", philips_id);
                                if (flashFiledevice("philipsid.txt",philips_id,id_len) == -1){
					IOT_INFO("error in file writing of philips id\n");
				}
                                 
				philipsidstatus=2;
				enddevicestatus=1;
			}
			philips_config=0;
		}	
		}
		if(philipsget==1)
		{
			/*if(i/22==0){
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);			
			}*//*
			if(i==0)
			{
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);	
			}*/
			for(i=1;i<noOfToken;i+=24)
			{
				jsmntok_t key = tokenList[i];
				unsigned int length = key.end - key.start;
				//IOT_INFO("length of the string is %d\n",length);
				char keyString[length + 1];
				//keyString[length] = '\0';    
				memcpy(keyString, &((const char *)ptr)[key.start], length);
				keyString[length] = '\0';
		
				IOT_INFO("i=%d\n",i);
				//if(i/21==0){
				//p_bulb = (struct philips_status *)malloc(sizeof(struct philips_status));
				//strcpy(p_bulb->bid,keyString);
				//IOT_INFO("Key: %s\n", p_bulb->bid);
				//strncpy(p_bulbs.bid,keyString,strlen(keyString));
				strncpy(philipsbulbid,keyString,strlen(keyString));
				//IOT_INFO("Key: %s\n", p_bulbs.bid);
				//IOT_INFO("Key: %s\n", p_bulbs.bid);
				
				IOT_INFO("Key: %s\n", philipsbulbid);	
				//}else if(i/22==0){
			 	key = tokenList[i+1];
				length = key.end - key.start;
				//IOT_INFO("length of the string is %d\n",length);
				char keyString1[length + 1];    
				memcpy(keyString1, &((const char *)ptr)[key.start], length);
				keyString1[length] = '\0';
		
				//IOT_INFO("i=%d\n",i+1);
				//strncpy(p_bulb->statuses,keyString,length);
				//IOT_INFO("Key: %s\n", p_bulb->statuses);
				//strncpy(p_bulbs.statuses,keyString,length);
				//IOT_INFO("Key: %s\n", p_bulbs.statuses);
				strncpy(philipsbulbstatus,keyString1,length);
				//IOT_INFO("Key: %s\n", philipsbulbstatus);
				IOT_INFO("Key: %s\n", philipsbulbstatus);
				//}
//				IOT_INFO("Key: %s\n", keyString);
//				IOT_INFO("my Key: %s\n", keyString[1]);
				philipsgetstatus=1;
				Task_sleep(1500);
			}
			philipsget=0;
		}
		
		
	}
    }

    free(tokenList);

    return lRetVal;
}

/////////////get json

int getParseJSONData(char *ptr)
{
    long lRetVal = 0;
    int noOfToken;
    jsmn_parser parser;
    jsmntok_t   *tokenList;


    /* Initialize JSON PArser */
    jsmn_init(&parser);

    /* Get number of JSON token in stream as we we dont know how many tokens need to pass */
    noOfToken = jsmn_parse(&parser, (const char *)ptr, strlen((const char *)ptr), NULL, 10);
    if(noOfToken <= 0)
    {
    	IOT_INFO("Failed to initialize JSON parser\n\r");
    	return -1;

    }

    /* Allocate memory to store token */
    tokenList = (jsmntok_t *) malloc(noOfToken*sizeof(jsmntok_t));
    if(tokenList == NULL)
    {
        IOT_INFO("Failed to allocate memory\n\r");
        return -1;
    }

    /* Initialize JSON Parser again */
    jsmn_init(&parser);
    noOfToken = jsmn_parse(&parser, (const char *)ptr, strlen((const char *)ptr), tokenList, noOfToken);
    if(noOfToken < 0)
    {
    	IOT_INFO("Failed to parse JSON tokens\n\r");
    	lRetVal = noOfToken;
    }
    else
    {
    	IOT_INFO("Successfully parsed %ld JSON tokens\n\r", noOfToken);
	int i=1;
	
		
	for(i=1;i<noOfToken;i+=42)
	{
		jsmntok_t key = tokenList[i];
		unsigned int length = key.end - key.start;
		char keyString[length + 1];    
		memcpy(keyString, &((const char *)ptr)[key.start], length);
		keyString[length] = '\0';
		
		IOT_INFO("i=%d\n",i);
		//if(i/21==0){
				strncpy(p_bulb->bid,keyString,length+1);
				IOT_INFO("Key: %s\n", p_bulb->bid);
				IOT_INFO("Key: %s\n", keyString);	
		//}else if(i/22==0){
			 key = tokenList[i+1];
		 length = key.end - key.start;
		//char keyString1[length + 1];    
		memcpy(keyString, &((const char *)ptr)[key.start], length);
		keyString[length] = '\0';
		
		IOT_INFO("i=%d\n",i+1);
			strncpy(p_bulb->statuses,keyString,length+1);
			IOT_INFO("Key: %s\n", p_bulb->statuses);
			IOT_INFO("Key: %s\n", keyString);
		//}
//		IOT_INFO("Key: %s\n", keyString);
//		IOT_INFO("my Key: %s\n", keyString[1]);
		
	}
    }

    free(tokenList);

    return lRetVal;
}



/*!
    \brief This function read respose from server and dump on console

    \param[in]      httpClient - HTTP Client object

    \return         0 on success else -ve

    \note

    \warning
*/
static int readResponse(HTTPCli_Handle httpClient)
{
	long lRetVal = 0;
	int bytesRead = 0;
	int id = 0;
	unsigned long len = 0;
	int json = 0;
	char *dataBuffer=NULL;
	bool moreFlags = 1;
	const char *ids[4] = {
					HTTPStd_FIELD_NAME_CONTENT_LENGTH,
			                HTTPStd_FIELD_NAME_CONNECTION,
			                HTTPStd_FIELD_NAME_CONTENT_TYPE,
			                NULL
	                     };

	/* Read HTTP POST request status code */
	lRetVal = HTTPCli_getResponseStatus(httpClient);
	if(lRetVal > 0)
	{
		switch(lRetVal)
		{
		case 200:
		{
			IOT_INFO("HTTP Status 200\n\r");
			/*
                 Set response header fields to filter response headers. All
                  other than set by this call we be skipped by library.
			 */
			HTTPCli_setResponseFields(httpClient, (const char **)ids);

			/* Read filter response header and take appropriate action. */
			/* Note:
                    1. id will be same as index of fileds in filter array setted
                    in previous HTTPCli_setResponseFields() call.

                    2. moreFlags will be set to 1 by HTTPCli_getResponseField(), if  field
                    value could not be completely read. A subsequent call to
                    HTTPCli_getResponseField() will read remaining field value and will
                    return HTTPCli_FIELD_ID_DUMMY. Please refer HTTP Client Libary API
                    documenation @ref HTTPCli_getResponseField for more information.
			 */
			while((id = HTTPCli_getResponseField(httpClient, (char *)g_buff, sizeof(g_buff), &moreFlags))
					!= HTTPCli_FIELD_ID_END)
			{

				
				IOT_INFO("data in while---%s--%d--\n",(const char *)g_buff,sizeof(g_buff));
				IOT_INFO("Switch Case...%d..\n",id);
				len = strtoul((char *)g_buff, NULL, 0);
				IOT_INFO("len in outside of switch case is %d \n",len);
				//IOT_INFO("len in case0 -----%d-----\n",len);
				//IOT_INFO();
				len = sizeof(g_buff);
                                IOT_INFO("len in outside of switch case ater size of g_buff is %d \n",len);
				switch(id)
				{
				case 0: /* HTTPCli_FIELD_NAME_CONTENT_LENGTH */
				{
					len = strtoul((char *)g_buff, NULL, 0);
					IOT_INFO("len in case0 -----%d-----\n",len);
				}
				break;
				case 1: /* HTTPCli_FIELD_NAME_CONNECTION */
				{
					IOT_INFO(" CASE 1 ");
				}
				break;
				case 2: /* HTTPCli_FIELD_NAME_CONTENT_TYPE */
				{
					IOT_INFO(" CASE 2 ");
					//len = strtoul((char *)g_buff, NULL, 10);
					//IOT_INFO("len in case2 -----%d-----\n",len);
					IOT_INFO("vinay---%s---\n",(const char *)g_buff);
					if(!strncmp((const char *)g_buff, "application/json",
							sizeof("application/json")))
					{
						json = 1;
						IOT_INFO("it is in json format");
					}
					else
					{
						/* Note:
                                Developers are advised to use appropriate
                                content handler. In this example all content
                                type other than json are treated as plain text.
						 */
						json = 0;
					}
					IOT_INFO(HTTPStd_FIELD_NAME_CONTENT_TYPE);
					IOT_INFO(" : ");
					IOT_INFO("application/json\n\r");
					
				}
				break;
				default:
				{
					IOT_INFO("Wrong filter id\n\r");
					lRetVal = -1;
					goto end;
				}
				}
			}
			IOT_INFO("1. Struck at application/json\n\r");
			bytesRead = 0;
			if(len > sizeof(g_buff))
			//if(len < sizeof(g_buff))
			{
				IOT_INFO("2. Struck at application/json\n\r");
				dataBuffer = (char *) malloc(len);
				if(dataBuffer)
				{
					IOT_INFO("3. Struck at application/json\n\r");
					IOT_INFO("Failed to allocate memory\n\r");
					lRetVal = -1;
					goto end;
				}
			}
			else
			{
				IOT_INFO("4. Struck at application/json\n\r");
				dataBuffer = (char *)g_buff;
			}

			/* Read response data/body */
			/* Note:
                    moreFlag will be set to 1 by HTTPCli_readResponseBody() call, if more
		            data is available Or in other words content length > length of buffer.
		            The remaining data will be read in subsequent call to HTTPCli_readResponseBody().
		            Please refer HTTP Client Libary API documenation @ref HTTPCli_readResponseBody
		            for more information

			 */
			//bytesRead = HTTPCli_readResponseBody(httpClient, (char *)dataBuffer, len, &moreFlags);
			IOT_INFO(" %s... \n",(char *)dataBuffer);
			IOT_INFO(" %d... \n",len);
			bytesRead = HTTPCli_readRawResponseBody(httpClient, (char *)dataBuffer, len);
			IOT_INFO(" %d... \n",bytesRead);
			/*if(bytesRead < 0)
			{
				IOT_INFO("Failed to received response body\n\r");
				lRetVal = bytesRead;
				goto end;
			}
			else if( bytesRead < len || moreFlags)
			{
				IOT_INFO("Mismatch in content length and received data length\n\r");
				goto end;
			}*/
			dataBuffer[bytesRead] = '\0';
			IOT_INFO("5. Struck at application/json\n\r");

			if(json)
			{
				IOT_INFO("----%s-----\n",dataBuffer);
				/* Parse JSON data */
				//char *dummydata = "{\"on\":false}";
				//IOT_INFO("------%s----\n",dummydata);
				//lRetVal = ParseJSONData(dummydata);
				//if(lRetVal < 0)
				//{
				//	goto end;
				//}
				lRetVal = ParseJSONData(dataBuffer);
				//lRetVal = getParseJSONData(dataBuffer);
				if(lRetVal < 0)
				{
					goto end;
				}
			}
			else
			{
				/* treating data as a plain text */
				//IOT_INFO("The plain text is:----%s-----\n",dataBuffer);
				IOT_INFO("The plain text is not a JSON formate-----\n");
			}

		}
		break;

		case 404:
			IOT_INFO("File not found. \r\n");
			break;
		default:
			IOT_INFO("IN DEFAULT STATE.... \r\n");
			FlushHTTPResponse(httpClient);
			break;
		}
	}
	else
	{
		IOT_INFO("Failed to receive data from server.\r\n");
		goto end;
	}

	lRetVal = 0;

end:
    if(len > sizeof(g_buff) && (dataBuffer != NULL))
    //if(len > sizeof(g_buff) || (dataBuffer != NULL))
	{
	    free(dataBuffer);
    }
  else {
	for(int i=0;dataBuffer[i]!='\0';i++){
        	strcpy(&dataBuffer[i],"\0") ;
	}
}
    return lRetVal;
}

/////-------for philips config--------////////

static int philipsconfig(HTTPCli_Handle httpClient)
{
    bool moreFlags = 1;
    bool lastFlag = 1;
    char tmpBuf[4];
    long lRetVal = 0;
    HTTPCli_Field fields[4] = {
				{HTTPStd_FIELD_NAME_HOST, HOST_NAME},
                                {HTTPStd_FIELD_NAME_ACCEPT, "*/*"},
                                {HTTPStd_FIELD_NAME_CONTENT_TYPE, "text/html"},
                                {NULL, NULL}	
			      };
//{"SOAPACTION", "urn:Belkin:service:basicevent:1#SetBinaryState"},
//{NULL, NULL}	
   // ; charset=utf-8
//{NULL, NULL}
    /* Set request header fields to be send for HTTP request. */
    HTTPCli_setRequestFields(httpClient, fields);

    /* Send POST method request. */
    /* Here we are setting moreFlags = 1 as there are some more header fields need to send
       other than setted in previous call HTTPCli_setRequestFields() at later stage.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendRequest for more information.
    */
    moreFlags = 1;
    char *vinayuri;
    vinayuri = "/api";
    lRetVal = HTTPCli_sendRequest(httpClient, HTTPStd_POST, vinayuri, moreFlags);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP POST request header.\n\r");
        return lRetVal;
    }

    sprintf((char *)tmpBuf, "%d", (sizeof(CONFIG_DATA)-1));

    /* Here we are setting lastFlag = 1 as it is last header field.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendField for more information.
    */
    lastFlag = 1;
    lRetVal = HTTPCli_sendField(httpClient, HTTPStd_FIELD_NAME_CONTENT_LENGTH, (const char *)tmpBuf, lastFlag);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP POST request header.\n\r");
        return lRetVal;
    }


    /* Send POST data/body */
    lRetVal = HTTPCli_sendRequestBody(httpClient, CONFIG_DATA, (sizeof(CONFIG_DATA)-1));
    IOT_INFO(CONFIG_DATA);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP POST request body.\n\r");
        return lRetVal;
    }


    lRetVal = readResponse(httpClient);

    return lRetVal;
}

/////////////////// 
/////----for philips off-----/////
static int HTTPPutMethod(HTTPCli_Handle httpClient)
{
  
    long lRetVal = 0;
    HTTPCli_Field fields[4] = {
                                {HTTPStd_FIELD_NAME_HOST, HOST_NAME},
                                {HTTPStd_FIELD_NAME_ACCEPT, "*/*"},
                                {HTTPStd_FIELD_NAME_CONTENT_TYPE, "text/html"},
                                {NULL, NULL}
                            };
    bool        moreFlags = 1;
    bool        lastFlag = 1;
    char        tmpBuf[4];
    
    
    /* Set request header fields to be send for HTTP request. */
    HTTPCli_setRequestFields(httpClient, fields);

    /* Send PUT method request. */
    /* Here we are setting moreFlags = 1 as there are some more header fields need to send
       other than setted in previous call HTTPCli_setRequestFields() at later stage.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendRequest for more information.
    */
    moreFlags = 1;
    lRetVal = HTTPCli_sendRequest(httpClient, HTTPStd_PUT, philips_request_uri, moreFlags);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP PUT request header.\n\r");
        return lRetVal;
    }
    sprintf((char *)tmpBuf, "%d", (sizeof(PUT_DATA)-1));

    /* Here we are setting lastFlag = 1 as it is last header field.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendField for more information.
    */
    lastFlag = 1;
    lRetVal = HTTPCli_sendField(httpClient, HTTPStd_FIELD_NAME_CONTENT_LENGTH, (char *)tmpBuf, lastFlag);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP PUT request header.\n\r");
        return lRetVal;
    }

    /* Send PUT data/body */
    lRetVal = HTTPCli_sendRequestBody(httpClient, PUT_DATA, (sizeof(PUT_DATA)-1));
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP PUT request body.\n\r");
        return lRetVal;
    }

    lRetVal = readResponse(httpClient);

    return lRetVal;
}

///////      ----------- ///////////


/// -------------FOR PHILIPS ON ----------///////////

static int HTTPPutMethodon(HTTPCli_Handle httpClient)
{
  
    long lRetVal = 0;
    HTTPCli_Field fields[4] = {
                                {HTTPStd_FIELD_NAME_HOST, HOST_NAME},
                                {HTTPStd_FIELD_NAME_ACCEPT, "*/*"},
                                {HTTPStd_FIELD_NAME_CONTENT_TYPE, "text/html"},
                                {NULL, NULL}
                            };
    bool        moreFlags = 1;
    bool        lastFlag = 1;
    char        tmpBuf[4];
    
    
    /* Set request header fields to be send for HTTP request. */
    HTTPCli_setRequestFields(httpClient, fields);

    /* Send PUT method request. */
    /* Here we are setting moreFlags = 1 as there are some more header fields need to send
       other than setted in previous call HTTPCli_setRequestFields() at later stage.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendRequest for more information.
    */
    moreFlags = 1;
    lRetVal = HTTPCli_sendRequest(httpClient, HTTPStd_PUT, philips_request_uri, moreFlags);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP PUT request header.\n\r");
        return lRetVal;
    }
    sprintf((char *)tmpBuf, "%d", (sizeof(PUT_DATA1)-1));



    /* Here we are setting lastFlag = 1 as it is last header field.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendField for more information.
    */
    lastFlag = 1;
    lRetVal = HTTPCli_sendField(httpClient, HTTPStd_FIELD_NAME_CONTENT_LENGTH, (char *)tmpBuf, lastFlag);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP PUT request header.\n\r");
        return lRetVal;
    }

    /* Send PUT data/body */
    lRetVal = HTTPCli_sendRequestBody(httpClient, PUT_DATA1, (sizeof(PUT_DATA1)-1));
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP PUT request body.\n\r");
        return lRetVal;

    }

    lRetVal = readResponse(httpClient);

    return lRetVal;
}
//*****************************************************************************
//
//! \brief HTTP POST Demonstration
//!
//! \param[in]  httpClient - Pointer to http client
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
static int HTTPPostMethod(HTTPCli_Handle httpClient)
{
    bool moreFlags = 1;
    bool lastFlag = 1;
    char tmpBuf[4];
    long lRetVal = 0;
    HTTPCli_Field fields[5] = {
                                {HTTPStd_FIELD_NAME_HOST, HOST_NAME},
                                {HTTPStd_FIELD_NAME_ACCEPT, "*/*"},
                                {HTTPStd_FIELD_NAME_CONTENT_TYPE, "text/xml; charset=utf-8"},
				//{HTTPStd_FIELD_NAME_SOAPACTION, "\"urn:Belkin:service:basicevent:1#SetBinaryState\""},
				{"SOAPACTION", "\"urn:Belkin:service:basicevent:1#SetBinaryState\""},
				{NULL, NULL}	
			      };
//{"SOAPACTION", "urn:Belkin:service:basicevent:1#SetBinaryState"},
//{NULL, NULL}	
   // ; charset=utf-8
//{NULL, NULL}
    /* Set request header fields to be send for HTTP request. */
    HTTPCli_setRequestFields(httpClient, fields);

    /* Send POST method request. */
    /* Here we are setting moreFlags = 1 as there are some more header fields need to send
       other than setted in previous call HTTPCli_setRequestFields() at later stage.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendRequest for more information.
    */
    moreFlags = 1;
    lRetVal = HTTPCli_sendRequest(httpClient, HTTPStd_POST, POST_REQUEST_URI, moreFlags);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP POST request header.\n\r");
        return lRetVal;
    }

    sprintf((char *)tmpBuf, "%d", (sizeof(POST_DATA)-1));

    /* Here we are setting lastFlag = 1 as it is last header field.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendField for more information.
    */
    lastFlag = 1;
    lRetVal = HTTPCli_sendField(httpClient, HTTPStd_FIELD_NAME_CONTENT_LENGTH, (const char *)tmpBuf, lastFlag);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP POST request header.\n\r");
        return lRetVal;
    }


    /* Send POST data/body */
    lRetVal = HTTPCli_sendRequestBody(httpClient, POST_DATA, (sizeof(POST_DATA)-1));
    IOT_INFO(POST_DATA);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP POST request body.\n\r");
        return lRetVal;
    }


    lRetVal = readResponse(httpClient);

    return lRetVal;
}

static int HTTPPostMethodon(HTTPCli_Handle httpClient)
{
    bool moreFlags = 1;
    bool lastFlag = 1;
    char tmpBuf[4];
    long lRetVal = 0;
    HTTPCli_Field fields[5] = {
                                {HTTPStd_FIELD_NAME_HOST, HOST_NAME},
                                {HTTPStd_FIELD_NAME_ACCEPT, "*/*"},
                                {HTTPStd_FIELD_NAME_CONTENT_TYPE, "text/xml; charset=utf-8"},
				//{HTTPStd_FIELD_NAME_SOAPACTION, "\"urn:Belkin:service:basicevent:1#SetBinaryState\""},
				{"SOAPACTION", "\"urn:Belkin:service:basicevent:1#SetBinaryState\""},
				{NULL, NULL}	
			      };
			      
//{"SOAPACTION", "urn:Belkin:service:basicevent:1#SetBinaryState"},
//{NULL, NULL}	
   // ; charset=utf-8
//{NULL, NULL}
    /* Set request header fields to be send for HTTP request. */
    HTTPCli_setRequestFields(httpClient, fields);

    /* Send POST method request. */
    /* Here we are setting moreFlags = 1 as there are some more header fields need to send
       other than setted in previous call HTTPCli_setRequestFields() at later stage.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendRequest for more information.
    */
    moreFlags = 1;
    lRetVal = HTTPCli_sendRequest(httpClient, HTTPStd_POST, POST_REQUEST_URI, moreFlags);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP POST request header.\n\r");
        return lRetVal;
    }

    sprintf((char *)tmpBuf, "%d", (sizeof(POST_DATA1)-1));

    /* Here we are setting lastFlag = 1 as it is last header field.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendField for more information.
    */
    lastFlag = 1;
    lRetVal = HTTPCli_sendField(httpClient, HTTPStd_FIELD_NAME_CONTENT_LENGTH, (const char *)tmpBuf, lastFlag);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP POST request header.\n\r");
        return lRetVal;
    }


    /* Send POST data/body */
    lRetVal = HTTPCli_sendRequestBody(httpClient, POST_DATA1, (sizeof(POST_DATA1)-1));
    IOT_INFO(POST_DATA);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP POST request body.\n\r");
        return lRetVal;
    }


    lRetVal = readResponse(httpClient);

    return lRetVal;
}


//*****************************************************************************
//
//! \brief HTTP GET Demonstration
//!
//! \param[in]  httpClient - Pointer to http client
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
static int HTTPGetMethod(HTTPCli_Handle httpClient)
{
  
    long lRetVal = 0;
    HTTPCli_Field fields[4] = {
                                //{HTTPStd_FIELD_NAME_HOST, HOST_NAME},
				{HTTPStd_FIELD_NAME_HOST, HOST_NAME},
                                {HTTPStd_FIELD_NAME_ACCEPT, "*/*"},
                                {HTTPStd_FIELD_NAME_CONTENT_LENGTH, "0"},
				 //{HTTPStd_FIELD_NAME_CONTENT_TYPE, "application/json"},
                                {NULL, NULL}
                            };
    bool        moreFlags;
    
    
    /* Set request header fields to be send for HTTP request. */
    HTTPCli_setRequestFields(httpClient, fields);

    /* Send GET method request. */
    /* Here we are setting moreFlags = 0 as there are no more header fields need to send
       at later stage. Please refer HTTP Library API documentaion @ HTTPCli_sendRequest
       for more information.
    */
    moreFlags = 0;
    lRetVal = HTTPCli_sendRequest(httpClient, HTTPStd_GET, philips_request_uri, moreFlags);
    if(lRetVal < 0)
    {
        IOT_INFO("Failed to send HTTP GET request.\n\r");
        return lRetVal;
    }

    //lRetval = HTTPCli_readRawResponseBody()
    lRetVal = readResponse(httpClient);

    return lRetVal;
}



////////------------//////////

char HostAddress[255] = AWS_IOT_MQTT_HOST;
uint32_t port = AWS_IOT_MQTT_PORT;
uint32_t publishCount = 0;
unsigned int  uiChannel;
float pw=0;
int ch=0;
int status=0;


float power(int ch_no){
if (ch_no == 1)
	uiChannel = ADC_CH_0;
else if (ch_no == 2)
	uiChannel = ADC_CH_1;
else if (ch_no == 3)
	uiChannel = ADC_CH_2;
else if (ch_no == 4)
	uiChannel = ADC_CH_3;

#ifdef CC3200_ES_1_2_1
        //
        // Enable ADC clocks.###IMPORTANT###Need to be removed for PG 1.32
        //
        HWREG(GPRCM_BASE + GPRCM_O_ADC_CLK_CONFIG) = 0x00000043;
        HWREG(ADC_BASE + ADC_O_ADC_CTRL) = 0x00000004;
        HWREG(ADC_BASE + ADC_O_ADC_SPARE0) = 0x00000100;
        HWREG(ADC_BASE + ADC_O_ADC_SPARE1) = 0x0355AA00;
#endif

        //
        // Configure ADC timer which is used to timestamp the ADC data samples
        //
        MAP_ADCTimerConfig(ADC_BASE,2^17);

	//PinTypeADC(PIN_59, 0xFF);

        //
        // Enable ADC timer which is used to timestamp the ADC data samples
        //
        MAP_ADCTimerEnable(ADC_BASE);

        //
        // Enable ADC module
        //
        MAP_ADCEnable(ADC_BASE);

        //
        // Enable ADC channel
        //

        MAP_ADCChannelEnable(ADC_BASE, uiChannel);
	//MAP_UtilsDelay(800000);

	if(MAP_ADCFIFOLvlGet(ADC_BASE, uiChannel)){

	        unsigned long ulSample = MAP_ADCFIFORead(ADC_BASE, uiChannel);
		IOT_INFO("%lu\n",ulSample);
		IOT_INFO("%f...\n",(float)((ulSample >> 2 ) & 0x0FFF));
		IOT_INFO("\n\rVoltage is %f\n\r",(((float)((ulSample >> 2 ) & 0x0FFF))*1.467)/4096);
		pw=(((float)((ulSample >> 2 ) & 0x0FFF))*1.467)/4096;
		//VinOpAmp=pw/91; I=V/R=VinOpAmp/Sensing resister; Irms=I/sqrtof(2); Vrms=77 for 120Volts AC; pw=Vrms*Irms;
		pw=(((((pw*2)/91)/0.005)/1.4142)*77);	
	}
return pw;
}



int size;
void MQTTcallbackHandler(AWS_IoT_Client *pClient, char *topicName,
        uint16_t topicNameLen, IoT_Publish_Message_Params *params, void *pData)
{
	//int status=0;
    IOT_INFO("Subscribe callback");
    IOT_INFO("%.*s\t%.*s",topicNameLen, topicName, (int)params->payloadLen,
            (char *)params->payload);
	strncpy(dexterpistring,(char *)params->payload,(int)params->payloadLen);
	IOT_INFO("dexterpistring in mqtt handler is : %s\n",dexterpistring);
	size = (int)params->payloadLen;
}

    //IOT_INFO("%d",(int)params->payloadLen);
   // IOT_INFO("%s",(char *)params->payload);

    //size = (int)params->payloadLen;
   // IOT_INFO("--------%d------\n",size);
    //const char *string = ((char *)params->payload);
///added for ota////////////
int updateota(void)
{
//while(1){
//if(updateotavariable == 1){
long lRetVal = -1;
	pvOtaApp = sl_extLib_OtaInit(RUN_MODE_NONE_OS | RUN_MODE_BLOCKING,0);
	strcpy((char *)ucVendorStr,OTA_VENDOR_STRING);
        OTAServerInfoSet(&pvOtaApp,(char *)ucVendorStr);

//SetCommitInt = OTA_ACTION_IMAGE_NOT_COMMITED;
//sl_extLib_OtaSet(pvOtaApp, EXTLIB_OTA_SET_OPT_IMAGE_COMMIT,sizeof(int), (_u8 *)&SetCommitInt);

	sl_extLib_OtaGet(pvOtaApp,EXTLIB_OTA_GET_OPT_IS_PENDING_COMMIT,
                         &OptionLen,&OptionVal);
	IOT_INFO("EXTLIB_OTA_GET_OPT_IS_PENDING_COMMIT? %d \n\r",OptionVal);
	if(OptionVal == true)
		{
		IOT_INFO("ota: pending comit & wlan ok ==> perform comit \n\r");
		SetCommitInt = OTA_ACTION_IMAGE_COMMITED;
		sl_extLib_OtaSet(pvOtaApp, EXTLIB_OTA_SET_OPT_IMAGE_COMMIT,
                             sizeof(int), (_u8 *)&SetCommitInt);
		
		}
	else
		{
		IOT_INFO("starting ota\n\r");
		lRetVal = 0;
		while(!lRetVal)
			{
			lRetVal = sl_extLib_OtaRun(pvOtaApp);
			}
		IOT_INFO("ota run = %d\n\r", lRetVal);
		if(lRetVal < 0)
			{
			IOT_INFO("ota: error with ota server\n\r");
			return 0;
			}
		else if (lRetVal == RUN_STAT_NO_UPDATES)
			{
			IOT_INFO("ota: run stat no updates\n\r");
			return 0;
			}
		else if ((lRetVal & RUN_STAT_DOWNLOAD_DONE))
			{
			lRetVal = sl_extLib_OtaSet(pvOtaApp, EXTLIB_OTA_SET_OPT_IMAGE_TEST,
                                    sizeof(int), (_u8 *)&SetCommitInt);
			IOT_INFO("ota: new image download complete\n\r");
			IOT_INFO("rebooting...");
			RebootMCU();
			}
		}
//}
//updateotavariable = 0;
}
void dexterpicontroller(void)
{
while(1)
{
if (dexterpistring[0] != "\0")
{
IOT_INFO(". : %s\n",dexterpistring);
//int size = (int)sizeof(dexterpistring);
    char string[size];
    //char string1[size];
    //char *string1;
    //string1 = malloc(size);
    int dummy = 0;
    //memset(string, '\0', sizeof(string));
    strcpy(string,dexterpistring);
    strncat(string, " ", size+1);
    //IOT_INFO("vinay----%s------\n",string);
if(!strncmp(dexterpistring ,"gpio", 4)){

	  if(11 >= size >= 50){
		continue;
	  }	

 const char s[2] = " ";
   char *token;
   
   /* get the first token */
   token = strtok(string, s);
   char *word[5];
   int dummy2 = 0;
   
   /* walk through other tokens */
   while( token != NULL ) 
   {
      printf( " %s\n", token );
      word[dummy2] = token;
      dummy2++;
    
      token = strtok(NULL, s);
   }
   IOT_INFO("---%s-----\n",word[4]);
   //for(dummy=0;dummy<=dummy2;dummy++){
	//if(word[dummy] == "from"){
         strcpy(userid,word[4]);//}}
   IOT_INFO("userid---%s-----\n",userid);

 if(!strncmp(dexterpistring ,"gpio 1 on", 9)){
	GPIOPinWrite(GPIOA1_BASE, 0x10, 0x10);
	PWR1=1;
	ch = 1;
	status=1;//variable=0;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);

 }

 if(!strncmp(dexterpistring ,"gpio 2 on", 9)){
	GPIOPinWrite(GPIOA1_BASE, 0x8, 0x8);
	PWR2=1;
	ch =2;//variable=0;
	status = 1;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
}

 if(!strncmp(dexterpistring ,"gpio 3 on", 9)){
        GPIOPinWrite(GPIOA1_BASE, 0x80, 0x80);
        PWR3=1;
	ch =3;//variable=0;
	status = 1;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 }

 if(!strncmp(dexterpistring ,"gpio 4 on", 9)){
        GPIOPinWrite(GPIOA3_BASE, 0x10, 0x10);
        PWR4=1;
	ch=4;//variable=0;
	status = 1;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 } 

 if(!strncmp(dexterpistring ,"gpio 1 off", 10)){
	GPIOPinWrite(GPIOA1_BASE, 0x10, 0x0);
        PWR1=0;
        ch =1;//variable=1;
	status = 0;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 }

 if(!strncmp(dexterpistring ,"gpio 2 off", 10)){
	GPIOPinWrite(GPIOA1_BASE, 0x8, 0x0);
        PWR2=0;
        ch=2;//variable=1;
	status = 0;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 }

 if(!strncmp(dexterpistring ,"gpio 3 off", 10)){
        GPIOPinWrite(GPIOA1_BASE, 0x80, 0x0);
        PWR3=0;
        ch=3;//variable=1;
	status = 0;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 }

 if(!strncmp(dexterpistring ,"gpio 4 off", 10)){
        GPIOPinWrite(GPIOA3_BASE, 0x10, 0x0);
        PWR4=0;
        ch=4;//variable=1;
	status = 0;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 }

}

if(!strncmp(dexterpistring ,"philips", 7)){
 const char s[2] = " ";
   char *token;
   
   /* get the first token */
   token = strtok(string, s);
   char *word[3];
   int dummy2 = 0;
   
   /* walk through other tokens */
   while( token != NULL ) 
   {
      printf( " %s\n", token );
      word[dummy2] = token;
      dummy2++;
    
      token = strtok(NULL, s);
   }
   IOT_INFO("---%s-----\n",word[2]);
   //for(dummy=0;dummy<=dummy2;dummy++){  {\"on\":true,\"sat\":254,"\bri\":254,\"hue\":10000}
	//if(word[dummy] == "from"){
	char philipsmessage[52];
	char id[2];
         strcpy(philipsmessage,word[2]);//}}
	 strcpy(id,word[1]);
	strcpy(bulbnumber,word[1]);
   IOT_INFO("philips bulb id---%s-----\n",id);
   IOT_INFO("philipsmessage---%s-----\n",philipsmessage);

strcpy(HOST_NAME,philips_uri);
HOST_PORT = 80;
sprintf(philips_request_uri,"/api/%s/lights/%s/state",philips_id,id);
long lRetVal = -1;
sprintf(PUT_DATA,"%s",philipsmessage);
IOT_INFO("put data is %s\n",PUT_DATA);
    HTTPCli_Struct httpClient1;


    //
    // Board Initialization
    //
    //BoardInit();
 lRetVal = ConnectToHTTPServer(&httpClient1);
    /*if(lRetVal < 0)
    {
        LOOP_FOREVER();
    }
*/
    IOT_INFO("\n\r");

 IOT_INFO("HTTP Put Begin:\n\r");

    lRetVal = HTTPPutMethod(&httpClient1);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Put failed.\n\r");
    }
    IOT_INFO("HTTP Put End:\n\r");
    HTTPCli_disconnect(&httpClient1);
/*/////////added for get//////
philipsget=1;
sprintf(philips_request_uri,"/api/%s/lights",philips_id);
lRetVal = ConnectToHTTPServer(&httpClient);

IOT_INFO("HTTP Get Begin:\n\r");
    lRetVal = HTTPGetMethod(&httpClient);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Post Get failed.\n\r");
    }
    IOT_INFO("HTTP Get End:\n\r");

//////////*/
//Task_sleep(1000);
philipsbulbget=1;
HTTPCli_Struct httpClient10;
sprintf(philips_request_uri,"/api/%s/lights/%s",philips_id,id);
lRetVal = ConnectToHTTPServer(&httpClient10);

IOT_INFO("HTTP Get Begin:\n\r");
    lRetVal = HTTPGetMethod(&httpClient10);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Post Get failed.\n\r");
    }
    IOT_INFO("HTTP Get End:\n\r");
   HTTPCli_disconnect(&httpClient10);

}

if(!strncmp(dexterpistring ,"Belkin", 6)){
 const char s[2] = " ";
   char *token;
	int belkin_number;
   
   /* get the first token */
   token = strtok(string, s);
   char *word[5];
   int dummy2 = 0;
   
   /* walk through other tokens */
   while( token != NULL ) 
   {
      printf( " %s\n", token );
      word[dummy2] = token;
      dummy2++;
    
      token = strtok(NULL, s);
   }
   //IOT_INFO("---%s-----\n",word[4]);
   //for(dummy=0;dummy<=dummy2;dummy++){
	//if(word[dummy] == "from"){
        // strcpy(userid,word[4]);//}}
   //IOT_INFO("userid---%s-----\n",userid);

belkin_number=atoi(word[1]);
IOT_INFO("belkin number=%d\n",belkin_number);
IOT_INFO("Belkin Function Call...\n");
long lRetVal = -1;
strcpy(HOST_NAME,belkin_uri[belkin_number-1]);
HOST_PORT = 49153;
    HTTPCli_Struct httpClient2;


    //
    // Board Initialization
    //
    //BoardInit();
 lRetVal = ConnectToHTTPServer(&httpClient2);
    /*if(lRetVal < 0)
    {

        LOOP_FOREVER();

    }

*/
    IOT_INFO("\n\r");
     IOT_INFO("HTTP Post Begin:\n\r");
    if(!strcmp(word[2],"on")){
    strcpy(belkinstatus[belkin_number-1],"1");
    lRetVal = HTTPPostMethodon(&httpClient2);}
    else if(!strcmp(word[2],"off")){
    strcpy(belkinstatus[belkin_number-1],"0");
    lRetVal = HTTPPostMethod(&httpClient2);}
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Post failed.\n\r");
    }
    IOT_INFO("HTTP Post End:\n\r");
    HTTPCli_disconnect(&httpClient2);
    enddevicestatus=1;
}
/*
 if(!strncmp(dexterpistring ,"gpio 1 on", 9)){
	GPIOPinWrite(GPIOA1_BASE, 0x10, 0x10);
	PWR1=1;
	ch = 1;
	status=1;//variable=0;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);

 }

 if(!strncmp(dexterpistring ,"gpio 2 on", 9)){
	GPIOPinWrite(GPIOA1_BASE, 0x8, 0x8);
	PWR2=1;
	ch =2;//variable=0;
	status = 1;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
}

 if(!strncmp(dexterpistring ,"gpio 3 on", 9)){
        GPIOPinWrite(GPIOA1_BASE, 0x80, 0x80);
        PWR3=1;
	ch =3;//variable=0;
	status = 1;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 }

 if(!strncmp(dexterpistring ,"gpio 4 on", 9)){
        GPIOPinWrite(GPIOA3_BASE, 0x10, 0x10);
        PWR4=1;
	ch=4;//variable=0;
	status = 1;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 } 

 if(!strncmp(dexterpistring ,"gpio 1 off", 10)){
	GPIOPinWrite(GPIOA1_BASE, 0x10, 0x0);
        PWR1=0;
        ch =1;//variable=1;
	status = 0;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 }

 if(!strncmp(dexterpistring ,"gpio 2 off", 10)){
	GPIOPinWrite(GPIOA1_BASE, 0x8, 0x0);
        PWR2=0;
        ch=2;//variable=1;
	status = 0;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 }

 if(!strncmp(dexterpistring ,"gpio 3 off ", 10)){
        GPIOPinWrite(GPIOA1_BASE, 0x80, 0x0);
        PWR3=0;
        ch=3;//variable=1;
	status = 0;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 }

 if(!strncmp(dexterpistring ,"gpio 4 off", 10)){
        GPIOPinWrite(GPIOA3_BASE, 0x10, 0x0);
        PWR4=0;
        ch=4;//variable=1;
	status = 0;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 } 
*/
 if(!strncmp(dexterpistring ,"discover", 8)){
	IOT_INFO("----Discover-----");
	//sri_recev();	
	//discover();
	//vinayudp();
	enddevicestatus=1;

	        
 }
 if(!strncmp(dexterpistring ,"multicast", 9)){
	IOT_INFO("----SENDMULTICAST-----");
	//SendMulticast();
 }
/* if(!strncmp((char *)params->payload ,"multi", 5)){
	IOT_INFO("----SENDRevice-----");
recievepack();
}*/
 if(!strncmp(dexterpistring ,"demouser", 8)){
	IOT_INFO("----SENDRevice-----");
//recievepack();
}

if((!strncmp(dexterpistring ,"get philips", 11)) || philipsgetbulbsstatus == 1){
HTTPCli_Struct httpClient3;
long lRetVal = -1;
philipsget=1;
//enddevicestatus=1;
IOT_INFO("philips Function Call...\n");
//getip();
strcpy(HOST_NAME,philips_uri);
HOST_PORT = 80;
IOT_INFO("philips get uri before :  %s\n",philips_request_uri);
sprintf(philips_request_uri,"/api/%s/lights",philips_id);
IOT_INFO("philips get uri after :  %s\n",philips_request_uri);
//IOT_INFO("philips get uri after ...");
    //
    // Board Initialization
    //
    //BoardInit();
lRetVal = ConnectToHTTPServer(&httpClient3);
    /*if(lRetVal < 0)
    {
        LOOP_FOREVER();
    }
*/
    IOT_INFO("\n\r");

/* IOT_INFO("HTTP Put Begin:\n\r");

    lRetVal = HTTPPutMethod(&httpClient);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Put failed.\n\r");
    }
    IOT_INFO("HTTP Put End:\n\r");
*/
IOT_INFO("HTTP Get Begin:\n\r");
    lRetVal = HTTPGetMethod(&httpClient3);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Post Get failed.\n\r");
    }
    IOT_INFO("HTTP Get End:\n\r");
    HTTPCli_disconnect(&httpClient3);
philipsgetbulbsstatus = 0;
}

    if(!strncmp(dexterpistring ,"philps off", 10)){
IOT_INFO("philips Function Call...\n");
//getip();
strcpy(HOST_NAME,philips_uri);
HOST_PORT = 80;
sprintf(philips_request_uri,"/api/%s/lights/1/state",philips_id);
long lRetVal = -1;
    HTTPCli_Struct httpClient4;


    //
    // Board Initialization
    //
    //BoardInit();
 lRetVal = ConnectToHTTPServer(&httpClient4);
    /*if(lRetVal < 0)
    {
        LOOP_FOREVER();
    }
*/
    IOT_INFO("\n\r");

 IOT_INFO("HTTP Put Begin:\n\r");

    lRetVal = HTTPPutMethod(&httpClient4);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Put failed.\n\r");
    }
    IOT_INFO("HTTP Put End:\n\r");


}

    if(!strncmp(dexterpistring ,"philps on", 9)){
IOT_INFO("philips Function Call...\n");
//getip();
strcpy(HOST_NAME,philips_uri);
HOST_PORT = 80;
sprintf(philips_request_uri,"/api/%s/lights/1/state",philips_id);
long lRetVal = -1;
    HTTPCli_Struct httpClient5;


    //
    // Board Initialization
    //
    //BoardInit();
 lRetVal = ConnectToHTTPServer(&httpClient5);
    /*if(lRetVal < 0)
    {

        LOOP_FOREVER();

    }

*/
    IOT_INFO("\n\r");

 IOT_INFO("HTTP Put Begin:\n\r");

    lRetVal = HTTPPutMethodon(&httpClient5);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Put failed.\n\r");
    }
    IOT_INFO("HTTP Put End:\n\r"); 
}

    if(!strncmp(dexterpistring ,"config philips", 14)){
IOT_INFO("philips config Call...\n");
//enddevicestatus=1;
philips_config=1;
long lRetVal = -1;
strcpy(HOST_NAME,philips_uri);
HOST_PORT = 80;
sprintf(philips_request_uri,"/api");
    HTTPCli_Struct httpClient6;


    //
    // Board Initialization
    //
    //BoardInit();
 lRetVal = ConnectToHTTPServer(&httpClient6);
    /*if(lRetVal < 0)
    {

        LOOP_FOREVER();

    }

*/
    IOT_INFO("\n\r");
     IOT_INFO("HTTP Post Begin:\n\r");
    lRetVal = philipsconfig(&httpClient6);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Post failed.\n\r");
    }
    IOT_INFO("HTTP Post End:\n\r");
    HTTPCli_disconnect(&httpClient6);
philipsconfigstatus=1;
if (philipsidstatus==2)
{
Task_sleep(500);
philipsget=1;
HTTPCli_Struct httpClient7;
sprintf(philips_request_uri,"/api/%s/lights",philips_id);
lRetVal = ConnectToHTTPServer(&httpClient7);

IOT_INFO("HTTP Get Begin:\n\r");
    lRetVal = HTTPGetMethod(&httpClient7);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Post Get failed.\n\r");
    }
    IOT_INFO("HTTP Get End:\n\r");
   HTTPCli_disconnect(&httpClient7);
}

}

    if(!strncmp(dexterpistring ,"belkin on", 9)){
IOT_INFO("Belkin Function Call...\n");
long lRetVal = -1;
strcpy(HOST_NAME,belkin_uri[0]);
HOST_PORT = 49153;
    HTTPCli_Struct httpClient8;


    //
    // Board Initialization
    //
    //BoardInit();
 lRetVal = ConnectToHTTPServer(&httpClient8);
    /*if(lRetVal < 0)
    {

        LOOP_FOREVER();

    }

*/
    IOT_INFO("\n\r");
     IOT_INFO("HTTP Post Begin:\n\r");
    lRetVal = HTTPPostMethodon(&httpClient8);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Post failed.\n\r");
    }
    IOT_INFO("HTTP Post End:\n\r");
}

if(!strncmp(dexterpistring ,"belkin off", 10)){
IOT_INFO("Belkin Function Call...\n");
long lRetVal = -1;
strcpy(HOST_NAME,belkin_uri[0]);
HOST_PORT = 49153;
    HTTPCli_Struct httpClient9;


    //
    // Board Initialization
    //
    //BoardInit();
 lRetVal = ConnectToHTTPServer(&httpClient9);
    /*if(lRetVal < 0)
    {

        LOOP_FOREVER();

    }

*/
    IOT_INFO("\n\r");
     IOT_INFO("HTTP Post Begin:\n\r");
    lRetVal = HTTPPostMethod(&httpClient9);
    if(lRetVal < 0)
    {
    	IOT_INFO("HTTP Post failed.\n\r");
    }
    IOT_INFO("HTTP Post End:\n\r");
}

if (!strncmp(dexterpistring , "gpio all on", 11)){
    IOT_INFO("\n GPIO OFF using COPY..  \n");
    GPIOPinWrite(GPIOA1_BASE, 0x10, 0x10);
    GPIOPinWrite(GPIOA1_BASE, 0x8, 0x8);
    GPIOPinWrite(GPIOA1_BASE, 0x80, 0x80);
    GPIOPinWrite(GPIOA3_BASE, 0x10, 0x10);
}
if (!strncmp(dexterpistring , "gpio all off", 12)){
    IOT_INFO("\n GPIO OFF using COPY..  \n");
    GPIOPinWrite(GPIOA1_BASE, 0x10, 0);
    GPIOPinWrite(GPIOA1_BASE, 0x8, 0);
    GPIOPinWrite(GPIOA1_BASE, 0x80, 0);
    GPIOPinWrite(GPIOA3_BASE, 0x10, 0);
}
if(!strncmp(dexterpistring , "update", 6)){
updateotavariable = 1;
/*
	long lRetVal = -1;
	pvOtaApp = sl_extLib_OtaInit(RUN_MODE_NONE_OS | RUN_MODE_BLOCKING,0);
	strcpy((char *)ucVendorStr,OTA_VENDOR_STRING);
        OTAServerInfoSet(&pvOtaApp,(char *)ucVendorStr);

//SetCommitInt = OTA_ACTION_IMAGE_NOT_COMMITED;
//sl_extLib_OtaSet(pvOtaApp, EXTLIB_OTA_SET_OPT_IMAGE_COMMIT,sizeof(int), (_u8 *)&SetCommitInt);

	sl_extLib_OtaGet(pvOtaApp,EXTLIB_OTA_GET_OPT_IS_PENDING_COMMIT,
                         &OptionLen,&OptionVal);
	IOT_INFO("EXTLIB_OTA_GET_OPT_IS_PENDING_COMMIT? %d \n\r",OptionVal);
	if(OptionVal == true)
		{
		IOT_INFO("ota: pending comit & wlan ok ==> perform comit \n\r");
		SetCommitInt = OTA_ACTION_IMAGE_COMMITED;
		sl_extLib_OtaSet(pvOtaApp, EXTLIB_OTA_SET_OPT_IMAGE_COMMIT,
                             sizeof(int), (_u8 *)&SetCommitInt);
		
		}
	else
		{
		IOT_INFO("starting ota\n\r");
		lRetVal = 0;
		while(!lRetVal)
			{
			lRetVal = sl_extLib_OtaRun(pvOtaApp);
			}
		IOT_INFO("ota run = %d\n\r", lRetVal);
		if(lRetVal < 0)
			{
			IOT_INFO("ota: error with ota server\n\r");
			}
		else if (lRetVal == RUN_STAT_NO_UPDATES)
			{
			IOT_INFO("ota: run stat no updates\n\r");
			}
		else if ((lRetVal & RUN_STAT_DOWNLOAD_DONE))
			{
			lRetVal = sl_extLib_OtaSet(pvOtaApp, EXTLIB_OTA_SET_OPT_IMAGE_TEST,
                                    sizeof(int), (_u8 *)&SetCommitInt);
			IOT_INFO("ota: new image download complete\n\r");
			IOT_INFO("rebooting...");
			RebootMCU();
			}
		}/*
IOT_INFO("starting ota\n\r");
		lRetVal = 0;
		while(!lRetVal)
			{
			lRetVal = sl_extLib_OtaRun(pvOtaApp);
			}
		IOT_INFO("ota run = %d\n\r", lRetVal);
		if(lRetVal < 0)
			{
			IOT_INFO("ota: error with ota server\n\r");
			}
		else if (lRetVal == RUN_STAT_NO_UPDATES)
			{
			IOT_INFO("ota: run stat no updates\n\r");
			}
		else if ((lRetVal & RUN_STAT_DOWNLOAD_DONE))
			{
			lRetVal = sl_extLib_OtaSet(pvOtaApp, EXTLIB_OTA_SET_OPT_IMAGE_TEST,
                                    sizeof(int), (_u8 *)&SetCommitInt);
			IOT_INFO("ota: new image download complete\n\r");
			IOT_INFO("rebooting...");
			RebootMCU();
			}*/
}
if(!strncmp(dexterpistring , "reboot", 6)){
RebootMCU();
}

if(!strncmp(dexterpistring , "reset", 5)){
sBootInfo_t sBootInfo;
  long lFileHandle;
  unsigned long ulToken;
if( 0 == sl_FsOpen((unsigned char *)IMG_BOOT_INFO, FS_MODE_OPEN_READ,
                       &ulToken, &lFileHandle) )
    {
        if( 0 > sl_FsRead(lFileHandle, 0, (unsigned char *)&sBootInfo,
                         sizeof(sBootInfo_t)) )
        {
          //return TASK_RET_DONE;
        }
        sl_FsClose(lFileHandle, 0, 0, 0);
    }

    //
    // Set the factory default
    //
    sBootInfo.ucActiveImg = IMG_ACT_FACTORY;
    sBootInfo.ulImgStatus = IMG_STATUS_NOTEST;

    //
    // Save the new configuration
    //
    if( 0 == sl_FsOpen((unsigned char *)IMG_BOOT_INFO, FS_MODE_OPEN_WRITE,
                       &ulToken, &lFileHandle) )
    {
        sl_FsWrite(lFileHandle, 0, (unsigned char *)&sBootInfo,
                   sizeof(sBootInfo_t));
        sl_FsClose(lFileHandle, 0, 0, 0);
    }
    RebootMCU();
    //
    // Force reboot
    //
    //g_ulSysState  = SYS_STATE_REBOOT;

    //
    // Return done.
    //
    //return TASK_RET_DONE;

}

//static uint32_t currButton, prevButton;
////////added for wifi reset///////////
//currButton = GPIO_read(Board_BUTTON0);
        //if (currButton == 1) {
if (!GPIOPinRead(GPIOA2_BASE, 0x2)) {
		System_printf("16\n");
            //smartConfigFxn();
	    sl_WlanProfileDel(WLAN_DEL_ALL_PROFILES);
            RebootMCU();
        }
        //prevButton = currButton;


////////////////



for(int i=0;dexterpistring[i]!='\0';i++)
        strcpy(&dexterpistring[i],"\0") ;
}
Task_sleep(1000);
}
}
void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data)
{
    IOT_WARN("MQTT Disconnect");
    IoT_Error_t rc = SUCCESS;

    if (NULL == data) {
        return;
    }

    AWS_IoT_Client *client = (AWS_IoT_Client *)data;
    if (aws_iot_is_autoreconnect_enabled(client)) {
        IOT_INFO("Auto Reconnect is enabled, Reconnecting attempt will start now");
        RebootMCU();
	//myawstask_status = true;
    }
    else {
        IOT_WARN("Auto Reconnect not enabled. Starting manual reconnect...");
        rc = aws_iot_mqtt_attempt_reconnect(client);
        if (NETWORK_RECONNECTED == rc) {
            IOT_WARN("Manual Reconnect Successful");
            IOT_WARN("Manual Reconnect Failed - %d", rc);
        }
        else {
            IOT_WARN("Manual Reconnect Failed - %d", rc);
        }
    }
}
bool myawstask_status;
static int livestatus=0;
void runAWSClient(void)
{
int awsloop = 0;
//deviceidread();
//philiphsidread();
IOT_INFO(".....The thing name is %s...\n",AWS_IOT_MY_THING_NAME);
for(awsloop = 0;awsloop <= 1000;awsloop++){
myawstask_status = false;

while(!myawstask_status){
IOT_INFO("\n....RUNNING....AWS_IOT...\n");
    IoT_Error_t rc = SUCCESS;
    int32_t i = 0;
    bool infinitePublishFlag = true;
    char *topicName; // = "sdkTest/sub";
    topicName = pubtopName;
    int topicNameLen = strlen(topicName);
    char *pubtopicName = "sdkTest/pub";
    int pubtopicNameLen = strlen(pubtopicName);

    AWS_IoT_Client client;
    IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
    IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;

    IoT_Publish_Message_Params paramsQOS0;
    IoT_Publish_Message_Params paramsQOS1;

    IOT_INFO("\nAWS IoT SDK Version %d.%d.%d-%s\n", VERSION_MAJOR, VERSION_MINOR,
            VERSION_PATCH, VERSION_TAG);


    mqttInitParams.enableAutoReconnect = false; // We enable this later below
    mqttInitParams.pHostURL = HostAddress;
    mqttInitParams.port = port;
    /*
     *  The following cert file variables are not used in this release. All
     *  cert files must exist in the "/certs" directory and be named "ca.der",
     *  "cert.der" and "key.der", as shown in the certflasher application. The
     *  ability to change this will be added in a future release.
     */
    mqttInitParams.pRootCALocation = AWS_IOT_ROOT_CA_FILENAME;
    mqttInitParams.pDeviceCertLocation = AWS_IOT_CERTIFICATE_FILENAME;
    mqttInitParams.pDevicePrivateKeyLocation = AWS_IOT_PRIVATE_KEY_FILENAME;
    mqttInitParams.mqttCommandTimeout_ms = 20000;
    mqttInitParams.tlsHandshakeTimeout_ms = 5000;
    mqttInitParams.isSSLHostnameVerify = true;
    mqttInitParams.disconnectHandler = disconnectCallbackHandler;
    mqttInitParams.disconnectHandlerData = (void *)&client;

    rc = aws_iot_mqtt_init(&client, &mqttInitParams);
    if (SUCCESS != rc) {
        IOT_ERROR("aws_iot_mqtt_init returned error : %d ", rc);
    }

    connectParams.keepAliveIntervalInSec = 10;
    connectParams.isCleanSession = true;
    connectParams.MQTTVersion = MQTT_3_1_1;
    connectParams.pClientID = AWS_IOT_MQTT_CLIENT_ID;
    connectParams.clientIDLen = (uint16_t)strlen(AWS_IOT_MQTT_CLIENT_ID);
    IOT_INFO(".....CLIENT ID IS ...%s...\n",AWS_IOT_MQTT_CLIENT_ID);
    connectParams.isWillMsgPresent = false;

    IOT_INFO("Connecting...");
    rc = aws_iot_mqtt_connect(&client, &connectParams);
    if (SUCCESS != rc) {
        IOT_ERROR("Error(%d) connecting to %s:%d", rc, mqttInitParams.pHostURL,
                mqttInitParams.port);
    }

    /*
     *  Enable Auto Reconnect functionality. Minimum and Maximum time of
     *  exponential backoff are set in aws_iot_config.h:
     *  #AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL
     *  #AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL
     */
    rc = aws_iot_mqtt_autoreconnect_set_status(&client, true);
    if (SUCCESS != rc) {
        IOT_ERROR("Unable to set Auto Reconnect to true - %d", rc);
    }

    IOT_INFO("Subscribing...");
    rc = aws_iot_mqtt_subscribe(&client, topicName, topicNameLen, QOS0,
            MQTTcallbackHandler, NULL);
    if (SUCCESS != rc) {
        IOT_ERROR("Error subscribing (%d)", rc);
    }

    char cPayload[512];
    sprintf(cPayload, "%s : %d ", "hello from SDK", i);

    paramsQOS0.qos = QOS0;
    paramsQOS0.payload = (void *)cPayload;
    paramsQOS0.isRetained = 0;

    paramsQOS1.qos = QOS1;
    paramsQOS1.payload = (void *)cPayload;
    paramsQOS1.isRetained = 0;

    if (publishCount != 0) {
       infinitePublishFlag = false;
    }

    while ((NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc ||
            SUCCESS == rc) && (publishCount > 0 || infinitePublishFlag)) {
        rc = aws_iot_mqtt_yield(&client, 150);

        if (NETWORK_ATTEMPTING_RECONNECT == rc) {
            /* If the client is attempting to reconnect, skip rest of loop */
            continue;
        }
	
//	if(livestatus++%2==0){
//	GPIOPinWrite(GPIOA3_BASE, 0x40, 0x0);
        if (GPIOPinRead(GPIOA3_BASE, 0x40))
	{ 
        	GPIOPinWrite(GPIOA3_BASE, 0x40, 0x0);
	}
        else {
		GPIOPinWrite(GPIOA3_BASE, 0x40, 0x40);
	}
//	}

        GPIOPinWrite(GPIOA2_BASE, 0x40, 0x40);
        IOT_INFO("-->sleep");
        Task_sleep(1000);
        if (publishCount > 0) {
           publishCount--;
        }
        if(((++livestatus)%30) == 0){

        sprintf(cPayload, "{ \n\"dexterpi_id\" : \"%s\",\n\"state\" : \"1\",\n\"version\" : \"%d\"\n}",DeviceID,APP_VER_BUILD);
        		paramsQOS1.payloadLen = strlen(cPayload);

			 char *pubtopicNames = "Devicelogstatus";
    			 int pubtopicNamesLen = strlen(pubtopicNames);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));


         }
	if(Phantom_buff==1){
		char *pubtopicName1 = "Phantompower";//"enddevices/status";
    		int pubtopicNameLen1 = strlen(pubtopicName1);
	        int socket=0;
	        if(Phantom_var1==1){
	                socket=1;PWR1=0;
	        //sprintf(cPayload, "{ \n \"Phantom Power Decteted at Channel-1 and socket-1\"\n}");
	        }else if(Phantom_var2==1){
	                socket=2;PWR2=0;
	        //sprintf(cPayload, "{ \n \"Phantom Power Decteted at Channel-2 and socket-2\"\n}");
	        }else if(Phantom_var3==1){
	                socket=3;PWR3=0;
	        //sprintf(cPayload, "{ \n \"Phantom Power Decteted at Channel-3 and socket-3\"\n}");
	        }else if(Phantom_var4==1){
	                socket=4;PWR4=0;
	        //sprintf(cPayload, "{ \n \"Phantom Power Decteted at Channel-4 and socket-4\"\n}");
	        }
	sprintf(cPayload, "{ \n \"Dynamic_Power_socketId\" : \"%d\",\n\"status\" : \"%d\",\n\"power\" : \"%f\",\n\"dexterpi_id\" : \"%s\",\n\"userId\" : \"%s\"\n}",socket,status,power(ch),DeviceID,userid);
        /* Recalculate string len to avoid truncation in subscribe callback */
        paramsQOS1.payloadLen = strlen(cPayload);
        do {
            rc = aws_iot_mqtt_publish(&client, pubtopicName1, pubtopicNameLen1,
                    &paramsQOS1);
            if (publishCount > 0) {
                publishCount--;
            }
        } while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                (publishCount > 0 || infinitePublishFlag));

	Phantom_buff=0;
	}
	
	if(ch!=0){
        //sprintf(cPayload, "%s : %f ", "Power = ", power(ch));
	//sprintf(cPayload, "Power of socket %d = %f -----at time %s",ch , power(ch),timeslap);
	sprintf(cPayload, "{ \n \"socketId\" : \"%d\",\n\"status\" : \"%d\",\n\"power\" : \"%f\",\n\"dexterpi_id\" : \"%s\",\n\"userId\" : \"%s\"\n}",ch,status,power(ch),DeviceID,userid);
	
        /* Recalculate string len to avoid truncation in subscribe callback */
        paramsQOS1.payloadLen = strlen(cPayload);
        do {
            rc = aws_iot_mqtt_publish(&client, pubtopicName, pubtopicNameLen,
                    &paramsQOS1);
            if (publishCount > 0) {
                publishCount--;
            }
        } while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                (publishCount > 0 || infinitePublishFlag));
   
        ch =0;
	}
	if(devicestate==1)
	{
		///////added for sending to app////////
			IOT_INFO("dexter pi is connected to cloud\n");
			/*char *pubtopicNames = "sdkTest/sub";//"enddevices/status";
    			int pubtopicNamesLen = strlen(pubtopicNames);
			

			sprintf(cPayload, "HiveyPIE is online with version %d",APP_VER_BUILD);
	

        		paramsQOS1.payloadLen = strlen(cPayload);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));*/

// Log purpose
			//MAP_UtilsDelay(800);
        //Task_sleep(1000);
			sprintf(cPayload, "{ \n\"dexterpi_id\" : \"%s\",\n\"state\" : \"1\",\n\"version\" : \"%d\"\n}",DeviceID,APP_VER_BUILD);
        		paramsQOS1.payloadLen = strlen(cPayload);

			 char *pubtopicNames = "Devicelog";
    			 int pubtopicNamesLen = strlen(pubtopicNames);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));
		devicestate=0;
	}

	if(enddevicestatus==1)
	{
		IOT_INFO("discover is called\n");
		char *pubtopicNames = "enddeviceipdetails";//"enddevices/status";
    		int pubtopicNamesLen = strlen(pubtopicNames);
		
		if(philipsidstatus==0)
		{
			/*sprintf(cPayload, "{ \n \"PhilipsIPStatus\" : \"%s\",\n\"PhilipsIDStatus\" : \"no\",\n\"Belkin1IPStatus\" : \"%s\",\n\"Belkin2IPStatus\" : \"%s\",\n\"Belkin3IPStatus\" : \"%s\",\n\"Belkin4IPStatus\" : \"%s\",\n\"Belkin5IPStatus\" : \"%s\",\n\"Belkin6IPStatus\" : \"%s\",\n\"Belkin7IPStatus\" : \"%s\",\n\"Belkin8IPStatus\" : \"%s\",\n\"Belkin9IPStatus\" : \"%s\",\n\"Belkin10IPStatus\" : \"%s\",\n\"dexterpi_id\" : \"%s\"\n}",philips_uri,belkin_uri[0],belkin_uri[1],belkin_uri[2],belkin_uri[3],belkin_uri[4],belkin_uri[5],belkin_uri[6],belkin_uri[7],belkin_uri[8],belkin_uri[9],deviceID);*/
			sprintf(cPayload, "{ \n \"PhilipsIPStatus\" : \"%s\",\n\"PhilipsIDStatus\" : \"no\",\n\"B1IP\" : \"%s\",\n\"B2IP\" : \"%s\",\n\"B3IP\" : \"%s\",\n\"B4IP\" : \"%s\",\n\"B5IP\" : \"%s\",\n\"B6IP\" : \"%s\",\n\"B7IP\" : \"%s\",\n\"B8IP\" : \"%s\",\n\"B9IP\" : \"%s\",\n\"B10IP\" : \"%s\",\n\"B1S\" : \"%s\",\n\"B2S\" : \"%s\",\n\"B3S\" : \"%s\",\n\"B4S\" : \"%s\",\n\"B5S\" : \"%s\",\n\"B6S\" : \"%s\",\n\"B7S\" : \"%s\",\n\"B8S\" : \"%s\",\n\"B9S\" : \"%s\",\n\"B10S\" : \"%s\",\n\"dexterpi_id\" : \"%s\"\n}",philips_uri,belkin_uri[0],belkin_uri[1],belkin_uri[2],belkin_uri[3],belkin_uri[4],belkin_uri[5],belkin_uri[6],belkin_uri[7],belkin_uri[8],belkin_uri[9],belkinstatus[0],belkinstatus[1],belkinstatus[2],belkinstatus[3],belkinstatus[4],belkinstatus[5],belkinstatus[6],belkinstatus[7],belkinstatus[8],belkinstatus[9],DeviceID);			
		}
		else if(philipsidstatus==1)
		{
			/*///////added for sending to app////////
			IOT_INFO("philips config  is called\n");
			char *pubtopicNames = "sdkTest/sub";//"enddevices/status";
    			int pubtopicNamesLen = strlen(pubtopicNames);
			/*if(i/22==0){
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);			
			}*//*
			if(i==0)
			{
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);	
			}*//*

			sprintf(cPayload, "please press link button on hue bridge");
	
        		/* Recalculate string len to avoid truncation in subscribe callback *//*
        		paramsQOS1.payloadLen = strlen(cPayload);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));*/
   
			//////////////

			sprintf(cPayload, "{ \n \"PhilipsIPStatus\" : \"%s\",\n\"PhilipsIDStatus\" : \"no\",\n\"B1IP\" : \"%s\",\n\"B2IP\" : \"%s\",\n\"B3IP\" : \"%s\",\n\"B4IP\" : \"%s\",\n\"B5IP\" : \"%s\",\n\"B6IP\" : \"%s\",\n\"B7IP\" : \"%s\",\n\"B8IP\" : \"%s\",\n\"B9IP\" : \"%s\",\n\"B10IP\" : \"%s\",\n\"B1S\" : \"%s\",\n\"B2S\" : \"%s\",\n\"B3S\" : \"%s\",\n\"B4S\" : \"%s\",\n\"B5S\" : \"%s\",\n\"B6S\" : \"%s\",\n\"B7S\" : \"%s\",\n\"B8S\" : \"%s\",\n\"B9S\" : \"%s\",\n\"B10S\" : \"%s\",\n\"dexterpi_id\" : \"%s\"\n}",philips_uri,belkin_uri[0],belkin_uri[1],belkin_uri[2],belkin_uri[3],belkin_uri[4],belkin_uri[5],belkin_uri[6],belkin_uri[7],belkin_uri[8],belkin_uri[9],belkinstatus[0],belkinstatus[1],belkinstatus[2],belkinstatus[3],belkinstatus[4],belkinstatus[5],belkinstatus[6],belkinstatus[7],belkinstatus[8],belkinstatus[9],DeviceID);				
//sprintf(cPayload, "{ \n \"PhilipsIPStatus\" : \"%d\",\n\"BelkinIPStatus\" : \"%d\",\n\"PhilipsUserIDStatus\" : \"please press link button on hue bridge\",\n\"dexterpi_id\" : \"DEXT01\"\n}",philipsipstatus,belkinipstatus);
		}
		else if(philipsidstatus==2)
		{
			/*///////////added for app////////////
			IOT_INFO("philips config  is called\n");
			char *pubtopicNames = "sdkTest/sub";//"enddevices/status";
    			int pubtopicNamesLen = strlen(pubtopicNames);
			/*if(i/22==0){
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);			
			}*//*
			if(i==0)
			{
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);	
			}*//*

			sprintf(cPayload, "pl 1");
	
        		/* Recalculate string len to avoid truncation in subscribe callback *//*
        		paramsQOS1.payloadLen = strlen(cPayload);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));*/
			///////////////

			/*sprintf(cPayload, "{ \n \"PhilipsIPStatus\" : \"%s\",\n\"PhilipsIDStatus\" : \"yes\",\n\"Belkin1IPStatus\" : \"%s\",\n\"Belkin2IPStatus\" : \"%s\",\n\"Belkin3IPStatus\" : \"%s\",\n\"Belkin4IPStatus\" : \"%s\",\n\"Belkin5IPStatus\" : \"%s\",\n\"Belkin6IPStatus\" : \"%s\",\n\"Belkin7IPStatus\" : \"%s\",\n\"Belkin8IPStatus\" : \"%s\",\n\"Belkin9IPStatus\" : \"%s\",\n\"Belkin10IPStatus\" : \"%s\",\n\"dexterpi_id\" : \"%s\"\n}",philips_uri,belkin_uri[0],belkin_uri[1],belkin_uri[2],belkin_uri[3],belkin_uri[4],belkin_uri[5],belkin_uri[6],belkin_uri[7],belkin_uri[8],belkin_uri[9],deviceID);*/
			sprintf(cPayload, "{ \n \"PhilipsIPStatus\" : \"%s\",\n\"PhilipsIDStatus\" : \"yes\",\n\"B1IP\" : \"%s\",\n\"B2IP\" : \"%s\",\n\"B3IP\" : \"%s\",\n\"B4IP\" : \"%s\",\n\"B5IP\" : \"%s\",\n\"B6IP\" : \"%s\",\n\"B7IP\" : \"%s\",\n\"B8IP\" : \"%s\",\n\"B9IP\" : \"%s\",\n\"B10IP\" : \"%s\",\n\"B1S\" : \"%s\",\n\"B2S\" : \"%s\",\n\"B3S\" : \"%s\",\n\"B4S\" : \"%s\",\n\"B5S\" : \"%s\",\n\"B6S\" : \"%s\",\n\"B7S\" : \"%s\",\n\"B8S\" : \"%s\",\n\"B9S\" : \"%s\",\n\"B10S\" : \"%s\",\n\"dexterpi_id\" : \"%s\"\n}",philips_uri,belkin_uri[0],belkin_uri[1],belkin_uri[2],belkin_uri[3],belkin_uri[4],belkin_uri[5],belkin_uri[6],belkin_uri[7],belkin_uri[8],belkin_uri[9],belkinstatus[0],belkinstatus[1],belkinstatus[2],belkinstatus[3],belkinstatus[4],belkinstatus[5],belkinstatus[6],belkinstatus[7],belkinstatus[8],belkinstatus[9],DeviceID);		
			//sprintf(cPayload, "{ \n \"PhilipsIPStatus\" : \"%d\",\n\"BelkinIPStatus\" : \"%d\",\n\"PhilipsUserIDStatus\" : \"have an new userid\",\n\"dexterpi_id\" : \"DEXT01\"\n}",philipsipstatus,belkinipstatus);
		}
		/*
		else if(philipsget==1)
		{
			sprintf(cPayload,"%s",philipsgetdata);
			philipsget=0;
		}*/
		else
		{
			sprintf(cPayload,"discover");
		}
		IOT_INFO("cpayload---%s----",cPayload);
        	/* Recalculate string len to avoid truncation in subscribe callback */
        	paramsQOS1.payloadLen = strlen(cPayload);
        	do {
			
            		rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    	&paramsQOS1);
			IOT_INFO("discover is called to publish\n");
            		if (publishCount > 0) {
                		publishCount--;
            		}
        	} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                (publishCount > 0 || infinitePublishFlag));
		enddevicestatus=0;
	}
    if(philipsconfigstatus==1)
	{
		if(philipsidstatus==1)
		{
			///////added for sending to app////////
			IOT_INFO("philips config  is called\n");
			char *pubtopicNames; // = "sdkTest/sub";//"enddevices/status";
			pubtopicNames = pubtopName;
    			int pubtopicNamesLen = strlen(pubtopicNames);
			/*if(i/22==0){
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);			
			}*//*
			if(i==0)
			{
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);	
			}*/

			sprintf(cPayload, "please press link button on hue bridge");
	
        		/* Recalculate string len to avoid truncation in subscribe callback */
        		paramsQOS1.payloadLen = strlen(cPayload);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));
		}
		else if(philipsidstatus==2)
		{
			///////////added for app////////////
			IOT_INFO("philips config  is called\n");
			char *pubtopicNames; // = "sdkTest/sub";//"enddevices/status";
			pubtopicNames = pubtopName;
    			int pubtopicNamesLen = strlen(pubtopicNames);
			/*if(i/22==0){
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);			
			}*//*
			if(i==0)
			{
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);	
			}*/

			sprintf(cPayload, "pl 1");
	
        		/* Recalculate string len to avoid truncation in subscribe callback */
        		paramsQOS1.payloadLen = strlen(cPayload);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));
		}
		
   		philipsconfigstatus=0;
	}
	/*if(philipsidstatus==1)
        {
		IOT_INFO("philips config  is called\n");
			char *pubtopicNames = "sdkTest/sub";//"enddevices/status";
    			int pubtopicNamesLen = strlen(pubtopicNames);
			/*if(i/22==0){
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);			
			}*//*
			if(i==0)
			{
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);	
			}*//*

			sprintf(cPayload, "please press link button on hue bridge");
	
        		/* Recalculate string len to avoid truncation in subscribe callback *//*
        		paramsQOS1.payloadLen = strlen(cPayload);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));
   
        		philipsidstatus =3;
		}

	if(philipsidstatus==2)
        {
		IOT_INFO("philips config  is called\n");
			char *pubtopicNames = "sdkTest/sub";//"enddevices/status";
    			int pubtopicNamesLen = strlen(pubtopicNames);
			/*if(i/22==0){
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);			
			}*//*
			if(i==0)
			{
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);	
			}*//*

			sprintf(cPayload, "pl 1");
	
        		/* Recalculate string len to avoid truncation in subscribe callback *//*
        		paramsQOS1.payloadLen = strlen(cPayload);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));
   
        		philipsidstatus =3;
		}*/	



        //}
/////////added for philips get///////
//philipssinglebulbget
		if(philipssinglebulbget==1)
		{
			IOT_INFO("philips single bulb get  is called\n");
			char *pubtopicNames = "philipsbulbsdetails";
			int pubtopicNamesLen = strlen(pubtopicNames);

			sprintf(cPayload, "{ \n \"philipsbulbId\" : \"%s\",\n\"philipsbulbStatus\" : %s,\n\"dexterpi_id\" : \"%s\",\n\"philipsip\" : \"%s\"\n}",bulbnumber,philipsbulbstatus,DeviceID,philips_uri);
	
        		/* Recalculate string len to avoid truncation in subscribe callback */
        		paramsQOS1.payloadLen = strlen(cPayload);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));
   
        		philipssinglebulbget =0;
		}	

		if(philipsgetstatus==1)
		{
			IOT_INFO("philips get  is called\n");
			char *pubtopicNames = "philipsbulbsdetails";//"enddevices/status";
    			int pubtopicNamesLen = strlen(pubtopicNames);
			/*if(i/22==0){
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);			
			}*//*
			if(i==0)
			{
				id_len=sizeof(keyString);
				IOT_INFO("philips get data length: %d\n",id_len);
				strncpy(philipsgetdata,keyString,id_len);
				IOT_INFO("philips get data : %s---\n", philipsgetdata);	
			}*/

			sprintf(cPayload, "{ \n \"philipsbulbId\" : \"%s\",\n\"philipsbulbStatus\" : %s,\n\"dexterpi_id\" : \"%s\",\n\"philipsip\" : \"%s\"\n}",philipsbulbid,philipsbulbstatus,DeviceID,philips_uri);
	
        		/* Recalculate string len to avoid truncation in subscribe callback */
        		paramsQOS1.payloadLen = strlen(cPayload);
        		do {
            			rc = aws_iot_mqtt_publish(&client, pubtopicNames, pubtopicNamesLen,
                    		&paramsQOS1);
            			if (publishCount > 0) {
                			publishCount--;
            			}
        		} while (MQTT_REQUEST_TIMEOUT_ERROR == rc &&
                		(publishCount > 0 || infinitePublishFlag));
   
        		philipsgetstatus =0;
		}	
////////////////////////////

	else{
        sprintf(cPayload, "%s : %d ", "hello from SDK QOS1", i++);
	}
 }
    if((NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc ||
            SUCCESS == rc)){
		NetWiFi_init();
    }

    if (SUCCESS != rc) {
        IOT_ERROR("An error occurred in the loop. Error code = %d\n", rc);
        myawstask_status = true;
	//runAWSClient();
    }
    else {
        IOT_INFO("Publish done\n");
    }
}}
if(awsloop >= 1000){
RebootMCU();
}
}
