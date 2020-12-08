/*****************************************************************************
 *
 * Filename:  	Tracker_SOC.h
 *
 *
 * Author :    	Guojie
 *
 *
 * Date : 	2012-05-31
 *
 *
 * Comment:  soc����
 *
 *
 ****************************************************************************/
#if defined(__KJX_SOC_APP__)

#ifndef __SOC_APP_H__
#define __SOC_APP_H__

/****************************************************************************
* Include Files                   		����ͷ�ļ�
*****************************************************************************/
#include "stack_ltlcom.h"
#include "soc_api.h"
#include "EngineerModeSocketDemoApp.h"
#include "Common_nvram_editor_data_item.h"
#include "DataAccountDef.h"

/*****************************************************************************
 *  Define					�궨��
 *****************************************************************************/
//#define __Tracker_SOC_DEBUG__

#if defined(__SPECIAL_EPO_SOCKET__)||defined(__SPECIAL_AGPS_SOCKET__)
#define SIGLELEN_SOC_MAX 512     //��ַ�ظ������ǳ�
#define PACKET_SOC_MAX 3            //����֧�����3��ƴ��
#else
#define SIGLELEN_SOC_MAX 1100   //SOC�������ճ���>1034 AGPS��
#define PACKET_SOC_MAX 3            //����֧�����3��ƴ��
#endif


/*****************************************************************************
* Typedef  Enum
*****************************************************************************/
#if defined(__NEW_PROTOCOL__)

typedef enum
{
    GPRS_LOGIN_INFO,
	GPRS_STATUS_INFO,
	GPRS_ANALOG_INPUT_INFO,
	GPRS_DIGITAL_INPUT_INFO,
	GPRS_ADJUSTTIME_INFO,
	GPRS_LBS_GETLATLON_INFO,
#if defined(__GPS_ON_MTK__)
    GPRS_GPS_INFO,
    GPRS_GPS_LBS_INFO,
    GPRS_GPS_LBS_STATUS_INFO,
    GPRS_GPS_PHB_INFO,
#endif/*__GPS_ON_MTK__*/    
    GPRS_LBS_INFO,
#if defined(__MULTI_CELLID__)||defined(__NBR_CELL_INFO__)
    GPRS_LBSEXPAND_INFO,
#endif /* __MULTI_CELLID__ */    
    GPRS_LBS_STATUS_INFO,
    GPRS_LBS_PHB_INFO,
#if defined(__AGPS_EPO_SUPPORT__)
    GPRS_PASS_AGPS_INFO,
#endif
#if defined(__FUEL_SENSOR__)
    GPRS_FUEL_SENSOR_INFO,
#endif
#if defined(__CAR_OBD__)
    GPRS_OBD_REALTIME_INFO,
    GPRS_OBD_MILEAGE_INFO,
    GPRS_OBD_TROUBLE_INFO,
    GPRS_OBD_ONLINE_REALTIME_INFO,
    GPRS_OBD_ONLINE_MILEAGE_INFO,
    GPRS_OBD_ONLINE_TROUBLE_INFO,
#endif
#ifdef __ONLINE_CMD_NORMAL_REPLY__
	GPRS_ONLINE_ASCII_DATA_REPLY,  //ASCII���ݻظ�ƽ̨�Ĳ�ѯ
	GPRS_ONLINE_UNICODE_DATA_REPLY, //UNICODE���ݻظ�ƽ̨�Ĳ�ѯ
	GPRS_ONLINE_ASCII_DATA_REPLY_EX,  //ASCII���ݻظ�ƽ̨�Ĳ�ѯ
	GPRS_ONLINE_UNICODE_DATA_REPLY_EX,	//UNICODE���ݻظ�ƽ̨�Ĳ�ѯ
#endif
    GPRS_ONLINE_RESULT_INFO,
    GPRS_ONLINE_SEESOS_INFO,
    GPRS_ONLINE_SEEPARAM_INFO,
    GPRS_ONLINE_SEETIME_INFO,
    
    GPRS_SEND_MAX_INFO
} GPRS_SEND_INFO_TYPE;

#elif defined(__OLD_PROTOCOL__)

typedef enum
{
    GPRS_GETIP_INFO,
    GPRS_STATUS_INFO,
    GPRS_ABNORMAL_STATUS_INFO,
    GPRS_GPS_LBS_INFO,
    GPRS_GPS_PHB_INFO,
    GPRS_ONLINE_RESULT_INFO,
    GPRS_SEND_MAX_INFO
} GPRS_SEND_INFO_TYPE;

#endif


extern GPRS_SEND_INFO_TYPE  gprs_send_type;


typedef enum
{
    REC_LENZERO_ERROR,   //�������ݳ���Ϊ0
    REC_LEN_ERROR,      //���Ȳ��Խ��ճ��Ⱥ����ݰ��ﳤ�Ȳ���Ӧ
    REC_END_ERROR,  //β��
    REC_HEAD_ERROR,   //ͷ��
    REC_CRC_ERROR,    //CRC����
    REC_SUCCESS,         //����������ȷ
    REC_TYPE_MAX
} TRACKER_RECERROR_TYPE;


#if defined(__NEW_PROTOCOL__)

typedef enum
{
    TRACKER_LOGIN_REPLY,   //��½�ظ���
    TRACKER_LBS_REPLY,    //LBS�ظ���
    TRACKER_LBS_EXPAND_REPLY,    //LBS��չ�ظ���
    TRACKER_STATUS_REPLY,  //״̬�ظ���
    TRACKER_ADJUSTTIME_REPLY,  //ʱ��У׼
    TRACKER_ONLINECOM_SET,     //����ָ������
    TRACKER_ONLINECOM_QUERY,  //����ָ���ѯ
    TRACKER_GETCHADRESS_REPLY,  //��ȡ���ĵ�ַ�ظ�
    TRACKER_GETENADRESS_REPLY,  //��ȡӢ�ĵ�ַ�ظ�
    TRACKER_FENCE_GETCHADRESS_REPLY,	//������ֱ���·�����Χ���������ĵ�ַ
    TRACKER_FENCE_GETENADRESS_REPLY,	//������ֱ���·�����Χ������Ӣ�ĵ�ַ
#if defined(__GPS_ON_MTK__)
    TRACKER_GPS_REPLY,    //GPS�ظ���
#if defined(__AGPS_EPO_SUPPORT__)
    TRACKER_LATLON_REPLY,   //LBS��ȡ��γ�Ȼظ�
    TRACKER_EPOAGPS_REPLY,     //EPO�ļ���ȡ�ظ�
#endif
#endif
#if defined(__LOG_OUTPUT__)&&!defined(WIN32)
    TRACKER_LOG_OUTPUT,     //����������־���
#endif
    TRACKER_RECDATA_OTHER,  //�������ظ�
    TRACKER_RECDATA_MAX
} TRACKER_RECDATA_TYPE;

#elif defined(__OLD_PROTOCOL__)
typedef enum
{
    TRACKER_STATUS_REPLY,  //״̬�ظ���
    TRACKER_ABNORMAL_STATUS_REPLY,  //�쳣״̬�ظ�
    TRACKER_ONLINECOM_SET,     //����ָ������
    TRACKER_GETCHADRESS_REPLY,  //��ȡ���ĵ�ַ�ظ�
    TRACKER_GETENADRESS_REPLY,  //��ȡӢ�ĵ�ַ�ظ�
    TRACKER_GETIP_REPLY,     //��ȡIP��ַ�ظ�
#if defined(__LOG_OUTPUT__)&&!defined(WIN32)
    TRACKER_LOG_OUTPUT,     //����������־���
#endif
#if defined(__AGPS_EPO_SUPPORT__)
    TRACKER_LATLON_REPLY,   //LBS��ȡ��γ�Ȼظ�
    TRACKER_EPOAGPS_REPLY,     //EPO�ļ���ȡ�ظ�
#endif
    TRACKER_RECDATA_OTHER,  //�������ظ�
    TRACKER_RECDATA_MAX
} TRACKER_RECDATA_TYPE;
#endif


/*****************************************************************************
 *  Struct					���ݽṹ����
 *****************************************************************************/
typedef enum
{
    SOC_NO_MEMORY = -3,
    SOC_CON_ERROR = -2,
    SOC_DNS_FAIL = -1,
    SOC_DNS_SUCCESS = 0, //0
    SOC_CON_SUCCESS = 1, //1
    SOC_CON_MAX
} mmi_soc_con_app_result;

typedef enum
{
    SOC_INVALID,
    SOC_STATE_CREATED,
    SOC_CONNECTED,
    SOC_SEND
} TRACKER_SOC_STATE_ENUM;

/* Structs */
typedef struct
{
    char host_name[DOMAIN_URL_MAX_LENGTH];    //DOMAIN_URL_MAX_LENGTH  100
    kal_int32 host_name_len;
    char url_link[DOMAIN_URL_MAX_LENGTH];          //DOMAIN_URL_MAX_LENGTH  100
    kal_int32 url_link_len;
    int ser_port_num;
} http_url_struct;


typedef enum
{
    SOCKET_CREATING,
    SOCKET_CREATED,
    SOCKET_CONNECTED,
    SOCKET_DNS_QUERY,
    SOCKET_HTTP_TCP_CREATING,
    SOCKET_HTTP_TCP_CREATED,
    SOCKET_SEND_RETRY,
    SOCKET_SENDING,
    SOCKET_SENT,
    SOCKET_RCVING,
    SOCKET_RCVD,
    SOCKET_CLOSING,
    SOCKET_CLOSED
} mmi_soc_state_enum;



typedef enum
{
    DNS_PARSE_IDLE,
    DNS_PARSE_START,
    DNS_PARSE_END,
    DNS_PARSE_MAX
} DNS_PARSE_STATUS;

extern DNS_PARSE_STATUS DNS_Parse_Status;


typedef struct
{
    kal_uint8 cbm_app_id;
    kal_uint32 nwt_account_id;
    kal_int8 soc_id;
    kal_uint8 soc_type;
    kal_uint8 connect_overtimes;                                        /*���ӳ�ʱ��������*/
    TRACKER_SOC_STATE_ENUM soc_state;
    sockaddr_struct soc_addr;
    char http_url[DOMAIN_URL_MAX_LENGTH];          //http_url[100];  100
    kal_uint8   http_url_len;
    http_url_struct url_parsed_info;

    mmi_soc_state_enum sendstate;                          /*���з���*/
    kal_uint8 post_retry_counter;
    kal_char snd_buffer[MAX_SND_BUFFER_SIZE];
    kal_uint32 snd_data_len;
    kal_uint32 snd_counter;
} TRACKER_SOC_STRUCT;


typedef struct
{
    BOOL  Success;                                     /*��½�ɹ�*/
    kal_uint8 sendtimes;                              /*��½�����ʹ���*/
    BOOL  used_domain_login;			/* ʹ��������¼*/
    kal_uint8	used_ip_login_fail_time;		/* ʹ��IP ��¼ʧ�ܴ���*/
    kal_uint8	domain_index;				/* ����ID  */
} TRACKER_LOGIN_INFO_STRUCT;


typedef struct
{
    U8 Content[PACKET_SOC_MAX*SIGLELEN_SOC_MAX];
    U16 ContLen;
} SOC_RECEIVE_DATA_STRUCT;


typedef struct
{
    LOCAL_PARA_HDR kal_char buffer[MAX_SND_BUFFER_SIZE];
    int len;
} gprs_socket_backup_req_struct;

/*****************************************************************************
* Local variable				�ֲ�����
*****************************************************************************/


/****************************************************************************
* Global Variable - Extern          ȫ�ֱ���
*****************************************************************************/
extern U16 gprs_inf_ind;
extern TRACKER_SOC_STRUCT soc_content;
extern TRACKER_LOGIN_INFO_STRUCT tracker_login_info;
extern SOC_RECEIVE_DATA_STRUCT Soc_Receive_Data;

extern BOOL AlreadyGetNetworkId;
/*****************************************************************************
 *  Local Functions			���غ���
 *****************************************************************************/
void Tracker_Soc_Reset(void);
static void Tracker_Socket_ApnSet_Req(const char *mode, char* apn, PsFuncPtr functionAction);
static void Tracker_Socket_ApnSet_Rsp(void* info);
static void Tracker_socket_set_account_id(cbm_sim_id_enum sim_id);
static void Tracker_Socket_OutputResult(mmi_soc_con_app_result ret);
static void Tracker_Socket_Http_GetUrl(const kal_int8 *in_str, int str_len, http_url_struct * purl_parsed_info);
static void Tracker_Socket_DNS_GetHostByName_Ind(void *inMsg);
static void Tracker_Socket_DNS_GetHostByName(const kal_uint8 *hostname);
static void Tracker_Socket_DNS_Parse(void);
static void Tracker_Socket_TCP_Start(void);
static BOOL Tracker_Socket_TCP_Create(void);
static void Tracker_Socket_TCP_Connect(void);
static void Tracker_Socket_TCP_Receive(void);
static void Tracker_Socket_TCP_ReStart(void);

/*****************************************************************************
 *  Global Functions			ȫ�ֺ���
 *****************************************************************************/
extern BOOL Tracker_Socket_Register_Id_Get_NetworkId(void);
extern void Tracker_Socket_Notify(void * inMsg);
extern void Tracker_socket_APN_Set(void);
extern void Tracker_Socket_Initial(void);
extern void Tracker_Socket_TCP_Close(void);
extern void Tracker_Socket_TCP_ReConnect(void);
extern void Tracker_GPRS_Socket_Send_Req(U8* data, int len);
extern void Tracker_Socket_TCP_Close_ReConnect(void);
extern void Tracker_Socket_Notify_OverTime(void);
extern void Tracker_Socket_Check_Connect_Normal(void);
extern void Tracker_Socket_Set_GPRS_Detached(void);
extern void System_GetLatLon_Handle(void);
#endif   /*__SOC_APP__*/
#endif	/*__SOC_APP_H__ */


