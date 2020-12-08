/**********************************************************************************
*Filename:     kjx_main_tour.h
*
*Description:  
*
*Author:        caoweijie
*
*Datetime:    2014/01/13
*
***********************************************************************************/
#if !defined(KJX_MAIN_TOUR_H)
#define KJX_MAIN_TOUR_H

#if defined(CUSTOMER_NAME_TOUR)
/****************************************************************************
* Include Files                   		����ͷ�ļ�
****************************************************************************/
#include "common_nvram_editor_data_item.h"
#include "Kjx_rfid.h"

/*****************************************************************************
 *  Define					�궨��
*****************************************************************************/
#define HEART_BEAT_TIME   1000*60*3    //xb add 2016-09-24 /*5����*/
#define HEART_BEAT_WAIT_CB_TIME   1000*60*2    //�������ظ��ȴ�ʱ��
#define GPS_DATA_TIME   1000*60*30   /*30����*/
          
#define KJX_PROJECT "TOUR\0"
#define KJX_VERSION "V1.0\0"
#ifdef __BLE_MODULE_SUPPORT__
#define BLE_UUID_HEAD	"757488A2"	//KJX A2 (16������)
#endif

#define MAIN_TOUR_DEBUG

#define KJX_DOMAIN	"tcp.youbaowlw.com"	//"device.bdontour.com"	//"device.zhihuiquanyu.com"	//"16uy302334.51mypc.cn"	//"device.zhihuiquanyu.com"	//"device.zhihuiquanyu.com"	//"61.189.189.186"	//"service.jezetrip.com"	//"service.jezetrip.com"   //"120.132.37.82"   //"bb.kejiaxun.com" 
#define KJX_PORT	8556	//8556	//8556	//6600

#if defined(__KJX_POSITION_TRIGGER_IN_LOCAL__)
#define PIAD 3.1415926
#define GPS_LON_MAX_LEN	20
#define GPS_LAT_MAX_LEN	20
#define GPS_DISTANCE_MAX_LEN	10
#define POSITIONPLAYINFO	L"PosInfos"
#endif

/*****************************************************************************
*   Enum					ö�����Ͷ���
*****************************************************************************/
#if defined(__KJX_BAT_STATUS_LED_SHOW__)
typedef enum
{
	BAT_LED_BEGIN,
	BAT_LED_RED = BAT_LED_BEGIN,
	BAT_LED_GREEN,
	BAT_LED_MAX
}kjx_bat_led;

typedef enum
{
	BATTERY_TURN_ON_RED,
	BATTERY_TURN_ON_GREEN,
	BATTERY_LOW_STATUS,
	BATTERY_NORMAL_STATUS,
	BATTERY_CHARGING_STATUS,
	BATTERY_FULL_STATUS,
	BATTERY_ALL_OFF,
	BATTERY_MAX
}kjx_bat_status;
#endif
	
typedef enum
{
	SEND_TOUR_TYPE_NONE,
	SEND_TOUR_TYPE_SMS,
	SEND_TOUR_TYPE_SERVER,
	SEND_TOUR_TYPE_ALL
}kjx_tour_send_type;

typedef enum
{
	SERVER_TOUR_TYPE_0001,/*����*/
	SERVER_TOUR_TYPE_9955,/*��λ����*/
	SERVER_TOUR_TYPE_9958,/*��ǰλ��*/
	SERVER_TOUR_TYPE_4101,/*��λ����*/
	SERVER_TOUR_TYPE_4102,/*��λ����*/
	SERVER_TOUR_TYPE_4103,/*SOS*/
	SERVER_TOUR_TYPE_4104,/*ʱ����*/
	SERVER_TOUR_TYPE_4130,/*����*/
	SERVER_TOUR_TYPE_4132,/*ʱ��*/
	SERVER_TOUR_TYPE_8701,/*����������*/
	SERVER_TOUR_TYPE_8501,/*����������*/
	SERVER_TOUR_TYPE_8601,/*����������*/
	SERVER_TOUR_TYPE_8602,/*���ٱ���*/
	SERVER_TOUR_TYPE_8805,
	SERVER_TOUR_TYPE_6105,/*��ȡSOS����*/
	SERVER_TOUR_TYPE_6106,/*��ȡ��������*/
}kjx_tour_socket_type;


typedef enum
{
	GPRS_TOUR_TYPE_INTERVAL_INFO,
	GPRS_TOUR_TYPE_SOS_NUM,
	GPRS_TOUR_TYPE_LISTEN_NUM,
	GPRS_TOUR_TYPE_PARSE_FLAG,
}kjx_tour_gprs_get_type;

/*****************************************************************************
 *  Struct					���ݽṹ����
******************************************************************************/
typedef struct 
{
	char psw[10];/*����*/
	char sosNum[SOS_NUM_MAX][20];/*SOS����*/
	char listenNum[20];/*��������*/
	char superNum[20]; /* +8613800138000 */
	char currLang[6];	  /*����*/
	char sosString[512];	 /*SOS������������*/
	char deviceNumber[10];	/*�豸��*/
	char writeImei[20]; /*д���IMEI��*/
	U16 interval; /*�ϴ�ʱ��*/
	U16 sleepStatus;/*����״̬*/
	U16 listenStatus;/*����״̬*/
	U16 moveStatus; /*����Χ��״̬*/
	U16 moveValue; /*����Χ������*/
	double latitude; /*����Χ��γ��*/
	double longitude; /*����Χ������*/
	S8 latitudeDir; /*N/S*/
	S8 longitudeDir; /*E/W*/
}kjx_tour_struct;

typedef struct 
{
	BOOL gps_status;			 /*  GPS����״̬*/	  
}kjx_tour_tem_status;

#if defined(__KJX_POSITION_TRIGGER_IN_LOCAL__)
struct kjxPositionInfo
{
	double lat;
	double lon;
	U32 distance;
	char rfid_id[MAX_RFID_LEN+1];		
	struct kjxPositionInfo *next;
};

typedef struct
{
	int maxID;
	struct kjxPositionInfo *positioninfo;
}kjxPositionPlayInfo;

typedef struct kjxPositionInfo KJXPOSITIONINFO;
#endif

/*****************************************************************************
* Local variable				�ֲ�����
*****************************************************************************/
static void kjx_position_trigger_process_in_local(S8 longitude_dir, double longitude, S8 latitude_dir, double latitude);

/****************************************************************************
* Global Variable - Extern          ȫ�ֱ���
*****************************************************************************/

/****************************************************************************
* Global Variable - Extern          ����ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
 *  Global Functions		ȫ�ֺ���
******************************************************************************/
#ifdef __KJX_FUN_GPS__
void kjx_open_gps(void);
void kjx_close_gps(void);
#endif

/*****************************************************************************
 *  Global Functions	- Extern		�����ⲿ����
******************************************************************************/
extern void kjx_func_main_tour(void);
extern void kjx_tour_check_do_somthing(void);
extern void kjx_tour_socket_send_heartbeat(void);
extern void kjx_tour_socket_send_gps_data(void);
extern void kjx_tour_move_timeout(BOOL timeout);
extern int kjx_acc_data_initialize(void);
extern void kjx_tour_trace_to_service(kjx_socket_type socket_type);
extern void kjx_factory_g_sensor_test_end(int result);
extern void kjx_tour_send_call_area_alarm(void);
extern void kjx_tour_send_sms_out_area_alarm(void);
extern void kjx_tour_send_sms_in_area_alarm(void);
extern void kjx_set_status_icon(void);
extern BOOL kjx_rfid_will_stop_work(void);
#ifdef __KJX_FUN_GPS__
extern BOOL kjx_gps_is_valid(void);
#endif
#if defined(__KJX_BAT_STATUS_LED_SHOW__)
extern void kjx_tour_battery_status_led(kjx_bat_status bat_status);
#endif/*__KJX_BAT_STATUS_LED_SHOW__*/
extern void kjx_tour_socket_timeout(void);
#endif/*CUSTOMER_NAME_TOUR*/
#endif/*KJX_MAIN_TOUR_H*/

