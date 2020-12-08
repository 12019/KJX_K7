/**********************************************************************************
*Filename:     kjx_main.h
*
*Description:  
*
*Author:        caoweijie
*
*Datetime:    2013/12/17
*
***********************************************************************************/
#ifndef __KJX_MAIN_H__
#define __KJX_MAIN_H__

#if defined(__KJX_FUN__)
/****************************************************************************
* Include Files 						����ͷ�ļ�
*****************************************************************************/
#include "kjx_type_define.h"
#include "kjx_socket.h"

/*****************************************************************************
 *	Define					�궨��
 *****************************************************************************/
#if !defined(MAX_LANGUAGES)
#define MAX_LANGUAGES 30
#endif

#if defined(__KJX_NBR_CELL__)
#define KJX_CELL_NBR_MAX	6
#endif

#define __FAST_TEST_FACTORY__

#ifdef __BLE_MODULE_SUPPORT__
extern const char gpio_bt_power_pin;
#define FUN_BT_PWR_PIN		gpio_bt_power_pin
#endif

#define MAIN_DEBUG

#ifdef __KJX_MULTI_LANGUAGE__
#define KJX_LANGUAGE_MAX	41

#define AUDIODIR_LANG_ENGLISH		L"ENGLISH\\"	//Ӣ
#define AUDIODIR_LANG_FRENCH		L"FRENCH\\"		//��
#define AUDIODIR_LANG_GERMAN		L"GERMAN\\"		//��
#define	AUDIODIR_LANG_ITALIAN		L"ITALIAN\\"	//�����
#define AUDIODIR_LANG_SPANISH		L"SPANISH\\"	//������
#define AUDIODIR_LANG_PORTUGUESE	L"PORTUGUESE\\"	//������
#define AUDIODIR_LANG_POLISH		L"POLISH\\"		//����
#define	AUDIODIR_LANG_DANISH		L"DANISH\\"		//����
#define AUDIODIR_LANG_SWEDISH		L"SWEDISH\\"	//���
#define AUDIODIR_LANG_NORWEGIAN		L"NORWEGIAN\\" 	//Ų��
#define AUDIODIR_LANG_FINNISH		L"FINNISH\\"	//����
#define AUDIODIR_LANG_DUTCH			L"DUTCH\\" 		//����
#define AUDIODIR_LANG_UKRAINIAN		L"UKRAINIAN\\"	//�ڿ���
#define AUDIODIR_LANG_RUSSIAN		L"RUSSIAN\\"	//����˹
#define	AUDIODIR_LANG_GREEK			L"GREEK\\" 		//ϣ��
#define AUDIODIR_LANG_TURKISH		L"TURKISH\\"	//������
#define AUDIODIR_LANG_ARABIC		L"ARABIC\\"		//������
#define AUDIODIR_LANG_HEBREW		L"HEBREW\\"		//ϣ������(��ɫ��)
#define AUDIODIR_LANG_PERSIAN		L"PERSIAN\\"	//��˹��(����)
#define AUDIODIR_LANG_URDU			L"URDU\\"		//�ڶ�����(�ͻ�˹̹)
#define AUDIODIR_LANG_HINDI			L"HINDI\\" 		//ӡ����(ӡ��)
#define AUDIODIR_LANG_BENGALI		L"BENGALI\\"	//�ϼ���
#define AUDIODIR_LANG_LAO			L"LAO\\"		//����
#define AUDIODIR_LANG_KHMER			L"KHMER\\"		//������(����կ)
#define AUDIODIR_LANG_MYANMAR		L"MYANMAR\\"	//���
#define	AUDIODIR_LANG_VIETNAMESE	L"VIETNAMESE\\"	//Խ��
#define AUDIODIR_LANG_INDONESIAN	L"INDONESIAN\\"	//ӡ��������
#define AUDIODIR_LANG_MALAY			L"MALAY\\" 		//������(��������,����)
#define AUDIODIR_LANG_THAI			L"THAI\\"		//̩��
#define AUDIODIR_LANG_FILIPINO		L"FILIPINO\\"	//���ɱ���
#define AUDIODIR_LANG_CHN			L"CHN\\"		//������ͨ��
#define AUDIODIR_LANG_CHN_SC		L"CHN_SC\\"		//�����Ĵ���
#define AUDIODIR_LANG_CHN_GD		L"CHN_GD\\"		//���Ĺ㶫��
#define AUDIODIR_LANG_CHN_MN		L"CHN_MN\\"		//�������ϻ�
#define AUDIODIR_LANG_CHN_XZ		L"CHN_XZ\\"		//���Ĳ���
#define AUDIODIR_LANG_CHN_XZ_LASA	L"CHN_XZ_LASA\\"		//���Ĳ�������
#define AUDIODIR_LANG_CHN_XZ_ANDUO	L"CHN_XZ_ANDUO\\"		//���Ĳ��ﰲ��
#define AUDIODIR_LANG_CHN_XZ_KANGBA	L"CHN_XZ_KANGBA\\"		//���Ĳ��￵��
#define AUDIODIR_LANG_CHN_EXTRA		L"CHN_EXTRA\\" 	//������������
#define AUDIODIR_LANG_KOREAN		L"KOREAN\\"		//������(����,����)
#define AUDIODIR_LANG_JAPANESE		L"JAPANESE\\"	//�ձ�
#endif

/*****************************************************************************
*	Enum					ö�����Ͷ���
*****************************************************************************/
typedef enum
{
	kjx_country_id_none=0,
	kjx_country_id_Brazil,				//����
	kjx_country_id_Malaysia,			//��������
	kjx_country_id_Thai,				//̩��
	kjx_country_id_Indonesia_xl,		//ӡ��������excelcom
	kjx_country_id_Indonesia,			//ӡ��������Telkomsel&indosat
	kjx_country_id_Vietnamese,			//Խ��
	kjx_country_id_Turkey,				//������
	kjx_country_id_Argentina,			//����͢
	kjx_country_id_Egypt,				//����
	kjx_country_id_Russia,				//����˹
	kjx_country_id_Colombia,			//���ױ���
	kjx_country_id_Kazakhstan,			//������˹̹
	kjx_country_id_Peru,				//��³
	kjx_country_id_MexicoMiu,			//ī����Movistar&Iusacell&Unefon
	kjx_country_id_MexicoTel,			//ī����Telcel 				
	kjx_country_id_Southafrica,			//�Ϸ�
	kjx_country_id_Nigeria,				//��������
	kjx_country_id_SaudiarabiaMob,		//ɳ�ذ�����Mobily
	kjx_country_id_SaudiarabiaStc,		//ɳ�ذ����� Stc
	kjx_country_id_SaudiarabiaZain,		//ɳ�ذ�����Zain
	kjx_country_id_Venezuela,			//ί������
	kjx_country_id_Ukraine,				//�ڿ���
	kjx_country_id_IraqAsia,			//������Asia
	kjx_country_id_IraqZain,			//������Zain
	kjx_country_id_India,				//ӡ��
	kjx_country_id_India2,				//ӡ��2
	kjx_country_id_chile,				//����
	kjx_country_id_China
}KJX_COUNTRY_ID_ENUM;	

typedef enum
{
	SMS_LIGHT_FALL_OFF,
	SMS_BT_ANTI_LOST
}kjx_sms_send_type;

#if defined(__KJX_MULTI_LANGUAGE__)
typedef enum
{
	LANG_BEGIN,
	LANG_ENGLISH = LANG_BEGIN,	//Ӣ
	LANG_FRENCH,				//��
	LANG_GERMAN,				//��
	LANG_ITALIAN,				//�����
	LANG_SPANISH,				//������
	LANG_PORTUGUESE,			//������
	LANG_POLISH,				//����
	LANG_DANISH,				//����
	LANG_SWEDISH,				//���
	LANG_NORWEGIAN,				//Ų��
	LANG_FINNISH,				//����
	LANG_DUTCH,					//����
	LANG_UKRAINIAN,				//�ڿ���
	LANG_RUSSIAN,				//����˹
	LANG_GREEK,					//ϣ��
	LANG_TURKISH,				//������
	LANG_ARABIC,				//������
	LANG_HEBREW,				//ϣ������(��ɫ��)
	LANG_PERSIAN,				//��˹��(����)
	LANG_URDU,					//�ڶ�����(�ͻ�˹̹)
	LANG_HINDI,					//ӡ����(ӡ��)
	LANG_BENGALI,				//�ϼ���
	LANG_LAO,					//����
	LANG_KHMER,					//������(����կ)
	LANG_MYANMAR,				//���
	LANG_VIETNAMESE,			//Խ��
	LANG_INDONESIAN,			//ӡ��������
	LANG_MALAY,					//������(��������,����)
	LANG_THAI,					//̩��
	LANG_FILIPINO,				//���ɱ���
	LANG_CHN,					//������ͨ��
	LANG_CHN_SC,				//�����Ĵ���
	LANG_CHN_GD,				//���Ĺ㶫��
	LANG_CHN_MN,				//�������ϻ�
	LANG_CHN_XZ,				//���Ĳ���
	LANG_CHN_XZ_LASA,			//���Ĳ�������
	LANG_CHN_XZ_ANDUO,			//���Ĳ��ﰲ��
	LANG_CHN_XZ_KANGBA,			//���Ĳ��￵��
	LANG_CHN_EXTRA,				//������������
	LANG_KOREAN,				//������(����,����)
	LANG_JAPANESE,				//�ձ�
	LANG_MAX
}KJX_SYSTEM_LANGUAGE;
#endif

/*****************************************************************************
 *	Struct					���ݽṹ����
 *****************************************************************************/
typedef struct
{
    S8 mcc[4];
    S8 mnc[4];
    U16 lac;
    U16 cid;
}kjx_lbs_info_struct;

#if defined(__KJX_NBR_CELL__)
/*cell info structure*/
typedef struct
{
    U16 arfcn;           /*ARFCN*/
    U8 bsic;              /*BSIC*/
    U8 rxlev;            /*Received signal level*/
    U16 mcc;            /*MCC*/
    U16 mnc;            /*MNC*/
    U16 lac;              /*LAC*/
    U16 ci;                /*CI*/
}kjx_nbr_cell_info_struct;
#endif

typedef void (*kjx_void) (void);
typedef void (*kjx_U16) (U16);
typedef void (*kjx_point)(unsigned short * );
typedef void (*kjx_sms) (kjx_sms_send_type);

typedef struct
{
    kjx_void kjx_check_fun;
    kjx_void kjx_main_custom;
    kjx_U16 kjx_set_alarm_status;
    kjx_U16 kjx_set_move_status;
    kjx_U16 kjx_set_speed_status;
#if defined(__KJX_OBD__)
    kjx_void kjx_send_obd_data;
    kjx_point kjx_send_obd_alarm;
#endif
    kjx_U16 kjx_set_gsm_led;

    kjx_void sms_out_area_alarm;
    kjx_void sms_in_area_alarm;
    kjx_void call_area_alarm;
    kjx_sms light_fall_off;
    kjx_sms bt_anti_lost;
} kjx_main_func;

#ifdef __KJX_MULTI_LANGUAGE__
typedef struct
{
	U8 id;
	U8 name[50];
}kjx_language_struct;
#endif

/*****************************************************************************
* Local variable				�ֲ�����
*****************************************************************************/

/****************************************************************************
* Global Variable           	ȫ�ֱ���
*****************************************************************************/
#if defined(__KJX_MULTI_LANGUAGE__)
extern U8 g_kjx_language;
extern U8 g_kjx_titlestr[256];
#endif

/****************************************************************************
* Global Variable - Extern			����ȫ�ֱ���
*****************************************************************************/
extern BOOL HaveGetIMSI;
extern BOOL EntryTestModeReady; 	/*�ж��Ƿ��ڲ���ģʽ*/

extern U8 QueryCommandState;	/*0:SMS 1:ONLINE 2:AT*/
extern kal_uint8 IMEIBuffer[16];
extern kal_uint8 IMSI[17];

extern kjx_lbs_info_struct g_kjx_lbs_info_struct;
extern kjx_socket_context g_kjx_socket_context;
extern kjx_lbs_info_struct g_kjx_lbs_info_struct;
extern kjx_main_func g_kjx_main_func;

/*****************************************************************************
* Global Functions	- Extern		�����ⲿ����
*****************************************************************************/
#if defined(__KJX_NBR_CELL__)
extern void kjx_get_nbr_cellid_req(void);
extern double kjx_get_lbs_distance(U8 signal_leve);
#endif

extern void kjx_agps_request(void);
extern void kjx_write_work_time(void);
extern BOOL kjx_check_shut_down(void);
#if defined(__KJX_FUN_SENSOR__)
#if defined(__MOTION_SENSOR_MC3413_SUPPORT__)
extern void kjx_sensor_mc3413(void);
#endif
extern void kjx_sensor_reset(void);
extern void kjx_sensor_entry_timer(void);
#endif
extern void kjx_stop_get_cellid(void);
extern void kjx_steps_teller_send_data(void);

/*****************************************************************************
* Local Functions 		���غ���
******************************************************************************/

/*****************************************************************************
* Local Functions 		ȫ�ֺ���
*****************************************************************************/

#endif/*__KJX_FUN__*/

#endif/*__KJX_MAIN_H__*/

