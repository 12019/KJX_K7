/**********************************************************************************
*Filename:     kjx_main_oldman.h
*
*Description:  
*
*Author:        caoweijie
*
*Datetime:    2014/01/13
*
***********************************************************************************/
#if !defined(KJX_MAIN_OLDMAN_H)
#define KJX_MAIN_OLDMAN_H


#if defined(CUSTOMER_NAME_OLDMAN)

#define HEART_BEAT_TIME   1000*60*5    /*5����*/
#define GPS_DATA_TIME   1000*60*60   /*10����*/
         
#define KJX_PROJECT "OLDMAN\0"
#define KJX_VERSION "V1.0\0"
 
#define KJX_DOMAIN	"bb.kejiaxun.com" 
#define KJX_PORT	6600

#define MAIN_OLDMAIN_DEBUG

typedef enum
{
  SEND_OLDMAN_TYPE_NONE,
  SEND_OLDMAN_TYPE_SMS,
  SEND_OLDMAN_TYPE_SERVER,
  SEND_OLDMAN_TYPE_ALL
}kjx_oldman_send_type;

typedef enum
{
  SERVER_OLDMAN_TYPE_0001,/*����*/
  SERVER_OLDMAN_TYPE_9955,/*��λ����*/
  SERVER_OLDMAN_TYPE_9958,/*��ǰλ��*/
  SERVER_OLDMAN_TYPE_4101,/*��λ����*/
  SERVER_OLDMAN_TYPE_4102,/*��λ����*/
  SERVER_OLDMAN_TYPE_4103,/*SOS*/
  SERVER_OLDMAN_TYPE_4104,/*ʱ����*/
  SERVER_OLDMAN_TYPE_4130,/*����*/
  SERVER_OLDMAN_TYPE_4132,/*ʱ��*/
  SERVER_OLDMAN_TYPE_8701,/*����������*/
  SERVER_OLDMAN_TYPE_8501,/*����������*/
  SERVER_OLDMAN_TYPE_8601,/*����������*/
  SERVER_OLDMAN_TYPE_8602,/*���ٱ���*/
  SERVER_OLDMAN_TYPE_8805,
  SERVER_OLDMAN_TYPE_6105,/*��ȡSOS����*/
  SERVER_OLDMAN_TYPE_6106,/*��ȡ��������*/
}kjx_oldman_socket_type;


typedef enum
{
	GPRS_OLDMAN_TYPE_INTERVAL_INFO,
	GPRS_OLDMAN_TYPE_SOS_NUM,
	GPRS_OLDMAN_TYPE_LISTEN_NUM,
	GPRS_OLDMAN_TYPE_PARSE_FLAG,
}kjx_oldman_gprs_get_type;

typedef struct 
{
	char psw[10];/*����*/
	char sosNum[SOS_NUM_MAX][20];/*SOS����*/
	char listenNum[20];/*��������*/
	char superNum[20]; /* +8613800138000 */
	char currLang[6];	  /*����*/
	char sosString[512];	 /*SOS������������*/
	char deviceNumber[10];	/*�豸��*/
	char writeImei[20];	/*д���IMEI��*/
	U16 interval; /*�ϴ�ʱ��*/
	U16 sleepStatus;/*����״̬*/
	U16 listenStatus;/*����״̬*/
	U16 moveStatus; /*����Χ��״̬*/
	U16 moveValue; /*����Χ������*/
	double latitude; /*����Χ��γ��*/
	double longitude; /*����Χ������*/
	S8 latitudeDir; /*N/S*/
	S8 longitudeDir; /*E/W*/
}kjx_oldman_struct;


typedef struct 
{
     BOOL gps_status;            /*  GPS����״̬*/    
}kjx_oldman_tem_status;

#define NVRAM_EF_OLDMAN_TOTAL_SIZE            sizeof(kjx_oldman_struct)
#define NVRAM_EF_OLDMAN_TOTAL           1


/***********************************************************************************/
//extern
extern U16 useDataLen;
extern U8  useData[512*4];
extern U8  crcPack[1024*4];
extern U8  unpack_data[1024*4];
extern U8	monitor_out_state;
extern kjxNetInfo g_kjxNetInfo;
#ifdef __KJX_FUN_GPS__
extern kjx_gps_data g_kjx_gps_data;
extern kjx_gps_func g_kjx_gps_func;
extern kjx_gps_info_string  gps_info_string;
extern kjx_pos_gps_info_string g_kjx_gps_info_string;
#endif
extern kjx_gprs_data g_kjx_gprs_data;
#if !defined(KJX_FORMAT_ACSSII)
extern kjx_pack_struct g_kjx_pack_struct;
#endif
extern kjx_lbs_info_struct g_kjx_lbs_info_struct;
extern kjx_socket_context g_kjx_socket_context;
extern kjx_socket_notify_func g_socket_notify_func;
extern kjx_socket_event_func g_kjx_socket_event_func;
extern kjx_main_func g_kjx_main_func;
extern nvram_ef_kjx_nvram_struct g_kjx_nvram_struct;

extern void kjx_func_main_oldman(void);
extern void kjx_oldman_check_do_somthing(void);
extern void kjx_oldman_socket_send_heartbeat(void);
extern void kjx_oldman_socket_send_gps_data(void);
extern void kjx_oldman_move_timeout(BOOL timeout);
extern int kjx_acc_data_initialize(void);
extern void kjx_oldman_trace_to_service(kjx_socket_type socket_type);

extern void kjx_oldman_send_call_area_alarm(void);
extern void kjx_oldman_send_sms_out_area_alarm(void);
extern void kjx_oldman_send_sms_in_area_alarm(void);
extern void kjx_set_status_icon(void);
extern void kjx_handle_position(void);
#endif
#endif/*KJX_MAIN_OLDMAN_H*/

