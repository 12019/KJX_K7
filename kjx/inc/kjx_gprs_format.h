/**********************************************************************************
*Filename:     kjx_net_format.h
*
*Description:  
*
*Author:        caoweijie
*
*Datetime:    2014/01/07
*
***********************************************************************************/
#ifndef __KJX_NET_FORMAT_H__
#define __KJX_NET_FORMAT_H__

#if defined(__KJX_FUN__)

/****************************************************************************
* Include Files                   		����ͷ�ļ�
****************************************************************************/
#include "kjx_type_define.h"

/*****************************************************************************
 *  Define					�궨��
 *****************************************************************************/
#define KJX_FORMAT_ACSSII
#define GPRS_FORMAT_DEBUG

/*****************************************************************************
*	Enum				ö�����Ͷ���
*****************************************************************************/
typedef enum
{
	LED_FLASH_MEGE2_TYPE_CALL,
	LED_FLASH_MEGE2_TYPE_GPS,
	LED_FLASH_MEGE2_TYPE_GPRS,
	LED_FLASH_MEGE2_TYPE_LIGHT,
	LED_FLASH_MEGE2_TYPE_EMPTY,
	LED_FLASH_MEGE2_TYPE_END
}led_flash_type;

/*****************************************************************************
 *  Struct					���ݽṹ����
*****************************************************************************/
typedef struct 
{
	 U16 tracer_to_service;   //���з��ز�������		 
	 U16 service_to_tracer;   //���в�������	 
}kjx_subTotal;


#if !defined(KJX_FORMAT_ACSSII)
typedef struct
{
	kal_uint16 header;	/*$$ 2byte*/
	kal_uint16 packLen;  /*L 2byte*/
	kal_uint16 imei[4];	 /*ID 7byte,ʵ�ʶ���8byte*/
	kal_uint16 project[2];/*project 4byte*/
	kal_uint16 version;	 /*version 2byte*/
	kal_uint8 total;		  /*total 1byte*/
	kal_uint16 checksum;/*checksum 2byte*/
	kal_uint16 ender; 	  /*\r\n 2byte*/
}kjx_pack_struct;
#endif

typedef U16 (*user_data) (U16);

typedef struct
{
    user_data get_user_data;//U16 kjx_gprs_get_user_data(U16 command);
    user_data get_unpack_data;//U16 kjx_gprs_get_unpack_data(U16 command);
} kjx_gprs_data;

#ifdef __KJX_WEATHER_SUPPORT__
typedef struct
{
	double latitude;
	double longitude; 
	U8 cityname[50];
	U8 date[50];
	U8 weather[128];
	U8 wind[128];
	U8 temperatrue[50];
	U8 DayPictureUrl[128];
	U8 NightPictureUrl[128];
	U8 DayPicName[50];
	U8 NightPicName[50];
}kjx_weather_struct;
#endif

#ifdef __KJX_FENCE_SUPPORT__
typedef struct
{
	U8 alarm_status;//����״̬ 1��������Χ������ 2��������Χ������
	U8 alarm_mode;//��ʾ��ʽ 0������ʾ1������ʾ2��������ʾ3����+������ʾ
	U8 alarm_str[256];//������ʾ��
}kjx_fence_struct;
#endif
/****************************************************************************
* Global Variable - Extern	ȫ�ֱ���
*****************************************************************************/
extern nvram_ef_kjx_nvram_struct g_kjx_nvram_struct;

/*****************************************************************************
 *  Local Functions			���غ���
******************************************************************************/

/*****************************************************************************
 *  Local Functions			ȫ�ֺ���
 *****************************************************************************/
extern void kjx_nvram_init(void);
extern void kjx_set_domain_infos(void);
extern void kjx_set_apn_infos(void);
extern void kjx_gprs_recvbuf_parse(kal_int32 len);
extern void kjx_reset_gps_data_send_func(void);
extern void kjx_sos_send_gps_data(void);
extern void kjx_sos_get_address(void);
extern U16 mmi_get_gps_status(void);
extern U16 kjx_sensor_is_sleep(void);
extern BOOL kjx_gprs_is_connect_check(void);
extern void kjx_set_language(void);
extern void kjx_set_timezone(void);
extern void us5182_set_power_mode( char bOn );
extern char us5182_get_power_mode( void );
extern void kjx_send_address_to_sos(void);

#endif/*__KJX_FUN__*/

#endif/*__KJX_NET_FORMAT_H__*/
