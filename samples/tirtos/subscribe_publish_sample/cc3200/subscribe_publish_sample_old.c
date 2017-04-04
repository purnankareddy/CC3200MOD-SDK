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
//#include "uart_if.h"
/////-------------/////

//  From SNTP

#include <time.h>

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/hal/Seconds.h>
#include <ti/net/sntp/sntp.h>

#include <simplelink.h>

///--------------sntp------------///
/*
#define sNTP_PORT          123
#define sNTP_SERVERS       1
#define sNTP_SERVERS_SIZE  (sNTP_SERVERS * sizeof(struct sockaddr_in))
#define sNTP_TIMEOUT       30000

char sNTP_HOSTNAME[] = "pool.ntp.org";
char sntpServers[sNTP_SERVERS_SIZE];
static Semaphore_Handle ssemHandle = NULL;*/
char timeslap[100];


//void sstartNTP(void);

/*
 *  ======== setTime ========
 */
/*
void ssetTime(uint32_t t)
{
    SlDateTime_t dt;
    struct tm tm;
    time_t ts;

    Seconds_set(t);

    time(&ts);
    tm = *localtime(&ts);

    /// Set system clock on network processor to validate certificate 
    dt.sl_tm_day  = tm.tm_mday;
   // tm.tm_mon is the month since January, so add 1 to get the actual month 
    dt.sl_tm_mon  = tm.tm_mon + 1;
    /// tm.tm_year is the year since 1900, so add 1900 to get the actual year 
    dt.sl_tm_year = tm.tm_year + 1900;
    dt.sl_tm_hour = tm.tm_hour;
    dt.sl_tm_min  = tm.tm_min;
    dt.sl_tm_sec  = tm.tm_sec;
    sl_DevSet(SL_DEVICE_GENERAL_CONFIGURATION,
            SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME,
            sizeof(SlDateTime_t), (unsigned char *)(&dt));
}

///
 //  ======== getTime ========
 //
uint32_t sgetTime(void)
{
    return (Seconds_get());
}

///
 //  ======== timeUpdateHook ========
 //  Called after NTP time sync
 //
void stimeUpdateHook(void *p)
{
   Semaphore_post(ssemHandle);
}
*/
/*
 *  ======== startNTP ========
 */
void sstartNTP(void)
{
    //int ret;
    //unsigned long ip;
    time_t ts;
/*    struct sockaddr_in ntpAddr = {0};
    Semaphore_Params semParams;

    ret = gethostbyname((signed char *)sNTP_HOSTNAME, strlen(sNTP_HOSTNAME), &ip,
            AF_INET);
    if (ret != 0) {
        System_printf("startNTP: NTP host cannot be resolved!", ret);
    }

    ntpAddr.sin_addr.s_addr = htonl(ip);
    ntpAddr.sin_port = htons(sNTP_PORT);
    ntpAddr.sin_family = AF_INET;
    memcpy(sntpServers, &ntpAddr, sizeof(struct sockaddr_in));

    ret = SNTP_start(sgetTime, ssetTime, stimeUpdateHook,
            (struct sockaddr *)&sntpServers, sNTP_SERVERS, 0);
    if (ret == 0) {
        System_printf("startNTP: SNTP cannot be started!", -1);
    }

    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_BINARY;
    ssemHandle = Semaphore_create(0, &semParams, NULL);
    if (ssemHandle == NULL) {
        System_printf("startNTP: Cannot create semaphore!", -1);
    }

    SNTP_forceTimeSync();
    if (!Semaphore_pend(ssemHandle, sNTP_TIMEOUT)) {
        System_printf("startNTP: error, no response from NTP server\n");
    }
*/
    ts = time(NULL);
    System_printf("Current time: %s\n", ctime(&ts));
    strncpy(timeslap,ctime(&ts),strlen(ctime(&ts)));
}
//---------------------------------///



char HostAddress[255] = AWS_IOT_MQTT_HOST;
uint32_t port = AWS_IOT_MQTT_PORT;
uint32_t publishCount = 0;
unsigned int  uiChannel;
float pw=0;
int ch=0;

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
		IOT_INFO("\n\rVoltage is %f\n\r",(((float)((ulSample >> 2 ) & 0x0FFF))*1.4)/4096);
		pw=(((float)((ulSample >> 2 ) & 0x0FFF))*1.4)/4096;
	}
return pw;
}


void MQTTcallbackHandler(AWS_IoT_Client *pClient, char *topicName,
        uint16_t topicNameLen, IoT_Publish_Message_Params *params, void *pData)
{
    IOT_INFO("Subscribe callback");
    IOT_INFO("%.*s\t%.*s",topicNameLen, topicName, (int)params->payloadLen,
            (char *)params->payload);

    IOT_INFO("%d",(int)params->payloadLen);
    IOT_INFO("%s",(char *)params->payload);
    //ch = (char *)params->payload;
    //IOT_INFO("----%s----\n",ch);

     /*if(!strncmp((char *)params->payload ,"gpio", 4)){
	IOT_INFO("GPIO FUNCTION CALL...\n");
	GPIOPinWrite(GPIOA3_BASE, 0x10, 0x10);
	GPIOPinWrite(GPIOA1_BASE, 0x80, 0x80);
        GPIOPinWrite(GPIOA1_BASE, 0x40, 0x40);
        GPIOPinWrite(GPIOA1_BASE, 0x10, 0x10);
 }*/

 if(!strncmp((char *)params->payload ,"gpio 1 on", 9)){
	GPIOPinWrite(GPIOA3_BASE, 0x10, 0x10);
	ch = 1;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);


 }

 if(!strncmp((char *)params->payload ,"gpio 2 on", 9)){
	GPIOPinWrite(GPIOA1_BASE, 0x80, 0x80);
	ch =2;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);
 
}

 if(!strncmp((char *)params->payload ,"gpio 3 on", 9)){
        GPIOPinWrite(GPIOA1_BASE, 0x40, 0x40);
	ch =3;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);

 }

 if(!strncmp((char *)params->payload ,"gpio 4 on", 9)){
        GPIOPinWrite(GPIOA1_BASE, 0x10, 0x10);

	ch=4;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);

 } 

 if(!strncmp((char *)params->payload ,"gpio 1 off", 10)){
	GPIOPinWrite(GPIOA3_BASE, 0x10, 0x0);
ch =1;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);

 }

 if(!strncmp((char *)params->payload ,"gpio 2 off", 10)){
	GPIOPinWrite(GPIOA1_BASE, 0x80, 0x0);
ch=2;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);

 }

 if(!strncmp((char *)params->payload ,"gpio 3 off ", 10)){
        GPIOPinWrite(GPIOA1_BASE, 0x40, 0x0);
ch=3;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);

 }

 if(!strncmp((char *)params->payload ,"gpio 4 off", 10)){
        GPIOPinWrite(GPIOA1_BASE, 0x10, 0x0);
 ch=4;
	sstartNTP();
	IOT_INFO("----current time = %s-----",timeslap);

 } 

    if(!strncmp((char *)params->payload ,"philps", 6)){
IOT_INFO("philips Function Call...\n");


}

    if(!strncmp((char *)params->payload ,"belkin", 6)){
IOT_INFO("Belkin Function Call...\n");
}

/*
    if (!strncmp((char *)params->payload , "copy", 4)){
    IOT_INFO("\n GPIO OFF using COPY..  \n");
    GPIOPinWrite(GPIOA3_BASE, 0x10, 0);
    GPIOPinWrite(GPIOA1_BASE, 0x80, 0);
    GPIOPinWrite(GPIOA1_BASE, 0x40, 0);
    GPIOPinWrite(GPIOA1_BASE, 0x10, 0);
}*/
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

void runAWSClient(void)
{
    IoT_Error_t rc = SUCCESS;
    int32_t i = 0;
    bool infinitePublishFlag = true;
    char *topicName = "sdkTest/sub";
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

    char cPayload[100];
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
        rc = aws_iot_mqtt_yield(&client, 100);

        if (NETWORK_ATTEMPTING_RECONNECT == rc) {
            /* If the client is attempting to reconnect, skip rest of loop */
            continue;
        }
	
        IOT_INFO("-->sleep");
        Task_sleep(1000);
       /* sprintf(cPayload, "%s : %d ", "hello from SDK QOS0", i++);
        // Recalculate string len to avoid truncation in subscribe callback 
        paramsQOS0.payloadLen = strlen(cPayload);
        rc = aws_iot_mqtt_publish(&client, pubtopicName, pubtopicNameLen,
                &paramsQOS0);*/
        if (publishCount > 0) {
           publishCount--;
        }

	if(ch!=0){
        //sprintf(cPayload, "%s : %f ", "Power = ", power(ch));
	sprintf(cPayload, "Power of socket %d = %f -----at time %s",ch , power(ch),timeslap);
	
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
	else{
        sprintf(cPayload, "%s : %d ", "hello from SDK QOS1", i++);
	}
 }

    if (SUCCESS != rc) {
        IOT_ERROR("An error occurred in the loop. Error code = %d\n", rc);
    }
    else {
        IOT_INFO("Publish done\n");
    }
}
