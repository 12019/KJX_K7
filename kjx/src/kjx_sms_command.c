/*****************************************************************************
 *
 * Filename:  	Tracker_SMS_Command.c
 *
 *
 * Author :    	Guojie
 *
 *
 * Date : 	2011-09-15
 *
 *
 * Comment:  ���Ŵ���
 *
 *
 ****************************************************************************/
#if defined(__KJX_SMS_APP__)

/****************************************************************************
* Include Files                   		����ͷ�ļ�
*****************************************************************************/
#include "Mmi_rp_app_sms_def.h"   //for  STR_GET_ADDRESS_FAIL
#include "mmi_rp_srv_general_setting_def.h"    //NVRAM_SETTING_LANG NVRAM_RESET_BOOTUP
#include "Init.h"   //for version_struct
#include "CharBatSrvGprot.h"   //srv_charbat_get_battery_level
#include "UcmProt.h"     //mmi_ucm_enter_incoming_call
#include "UcmSrvIntProt.h"
#include "GeneralSettingSrvGprot.h"   //srv_setting_get_language();
#include "AlarmFrameworkProt.h" /* AlmATPowerReset */
#include "SmsSrvGprot.h"    //srv_sms_get_msg_content
#include "bmt.h"
#include "CharBatSrvprot.h"
#include "ProfilesAppGprot.h"
#include "TimerEvents.h"
#include "rtc_sw_new.h"
#include "SimCtrlSrvGprot.h"
#include "ImeiSrvGprot.h"
#include "gpiosrvgprot.h"

//#include "Tracker_Call.h"
#include "kjx_main.h"
#include "Kjx_sms_command.h"
#include "kjx_prin.h"
#include "kjx_main_tour.h"
#include "kjx_gps.h"
#include "kjx_include.h"

//#include "Tracker_SMS_Sender.h"
//#include "Tracker_Main.h"
//#include "Tracker_Remind.h"
//#include "Tracker_Util.h"
//#include "Tracker_GPRS_Send.h"
//#include "Tracker_SOC.h"
#if defined(__SOS_CALL__)
#include "Tracker_Call.h"
#endif /*__SOS_CALL__*/


#if defined(__NBR_CELL_INFO__)
//#include "Tracker_Multi_cellID.h"
#endif

#if defined(__PARAM_BACKUP__)
#include "Tracker_IMEI_Backup.h"
#endif

#if defined(__BOSCH_BMA250E__)
#include "Tracker_Sensor.h"
#endif

#if defined(__GPS_ON_MTK__)
#if defined(__GPRS_SEND_FILTER__)
#include "Tracker_Filter.h"
#endif
#include "Tracker_GPS_Decode.h"
#include "Tracker_GPS_Driver.h"
#if defined(__GPS_FENCE__)
#include "Tracker_Fence.h"
#endif  /*__GPS_FENCE__*/

#if defined(__GPS_BACKUP__)
#include "Tracker_Backup.h"
#endif

#if defined(__AGPS_EPO_SUPPORT__)
#include "Tracker_GPRS_AGPS.h"
#include "Tracker_GPS_EPO.h"
#endif

#if defined(__SPECIAL_AGPS_SOCKET__)
#include "Tracker_SOC_AGPS.h"
#endif

#if defined(__SPECIAL_EPO_SOCKET__)
#include "Tracker_SOC_EPO.h"
#endif

#endif /*__GPS_ON_MTK__*/

#if defined(__DETECT_VOICE__)
#include "Tracker_Voice_Detect.h"
#endif

#if defined(__ACC_DETECT__)
#include "Tracker_ACCOil.h"
#endif

#if defined(__EXPAND_PORT_SUPPORT__)
#include "Tracker_Expand_Port.h"
#include "Tracker_Analog_Backup.h"
#include "Tracker_Digital_Backup.h"
#endif

#if defined(__CAR_OBD__)
#include "Tracker_Car_OBD.h"
#endif

#if defined(__FUEL_SENSOR__)
#include "Tracker_Fuel_Sensor.h"
#include "Tracker_Fuel_Backup.h"
#endif

/*****************************************************************************
 *  Define					�궨��
 *****************************************************************************/
#define TRACKER_CMD_SEG_MAX 12
#define PACKET_PHBNUM_LEN_MAX 21   //�������·��ĵ绰���볤�ȹ̶�Ϊ21λ
#define AT_FRAME_MAX_LEN 190
#define MAX_REPLEY_SMS 120
#define MAX_CMD_HEAD_LEN  20
#define IS_IN_CALL() (srv_ucm_query_call_count(SRV_UCM_CALL_STATE_ALL, SRV_UCM_CALL_TYPE_ALL, NULL) > 0)
#define KJX_TEST
/************************************************************
*ERROR:100   ָ�����ָ��ȳ�����Χ��
*                     Error: The command length exceeds the ruled length.
*                     Error: Extend ruled length.
*ERROR:101   ָ�����ָ�����������Χ��
*                     Error: The command parameters is out of range.
*                     Error: Data is out of range.
*ERROR:102   ָ�����ָ���ʽ����ȷ��
*                     Error: Wrong command format.
*ERROR:103   ָ����������ʽ����ȷ��
*                     Error: Wrong password format.
*ERROR:104   ָ���������绰��������������
*                     Error: Family numbers exceeds the range that system can support.
*ERROR:104   ָ�����:SOS������������.
*                     Error:SOS NO. exceeds the range that system can support.
*ERROR:105   ָ���������绰���������ѿա�
*                     Error: Family numbers is empty.
*ERROR:105   ָ�����:SOS������Ϊ��.
*                     SOS NO.is null.
*ERROR:106   ָ�����ɾ����SOS�绰������Ų���ȷ��
*                     Error: The serial NO. of deleted SOS NO. is wrong.
*ERROR:107   ָ�����ָ����ڡ�
*                     Error: No this command exsited,please check the command string.
*ERROR:108   ָ�������ָ���������#����
*                     Error: No terminal bit, please end it with #.
*ERROR:109   ָ�����ָ���������
*                     Error: Wrong password.
*ERROR:110   ָ����󣺷�������벻��ʹ�ô�ָ��ܡ�
*                     Error: Not supported for Non-Family number.
*ERROR:111   ָ�����:  ��SOS���벻��ʹ�ô�ָ��ܡ�
*                    Error:Only SOS phone number to set.
*ERROR:112  �Է�����ͨ�������Ժ��ڼ�����
*                    the other party is during a conversation, please monitor later.
*ERROR:113  ���õ�SOS�����������������롣
*                    Set the SOS number must be a family number.
*ERROR:114  ָ�����:��SOS�ͷ�������벻��ʹ�ô�ָ��ܡ�
                      Error: Not supported for Non-Family and Non-SOS number.
*ERROR:115  ָ�����:����ʱ����ڣ������������
                      Error: Don't allow monitoring during stealth period.
*ERROR:116   ָ����󣺷����ĺ��벻��ʹ�ô�ָ��ܡ�
*                     Error:Only center phone number to set.
*ERROR:117   ָ����󣺷����ĺ���ͷ�SOS���벻��ʹ�ô�ָ��ܡ�
*                     Error:Only center phone number and SOS phone number to set.
*ERROR:118   ������IP�������������޸�.
*                     The domain name or IP is locked,not allowed to modify.
*ERROR:119   ָ�����:������;����벻����ͬ.
*                     Error:The new password and old password can not be the same.
*ERROR:120   ָ�����:����3 �Ͳ���4 ֮�˻�Ӧ�����ڲ���1��
*                     Error:The parameters 3 and parameters 4 of the product should be less than or equal to the value of parameter 1.
*ERROR:121   ָ�����:����2 Ӧ�����ڲ���3��
*                    Error:The value of parameters 2 should be less than or equal to the value of parameter 3.
*ERROR:122   ָ�����:���ų��ȳ�������ܴ����ȡ�
*                    Error:The content of the message exceeds the maximum length.
*ERROR:123   �ն˴����Զ����ģʽ�������ֶ�����򳷷���
*                    The terminal is in automatic security model, can not be manually fortification or disarm.
*ERROR:124
*


************************************************************/

/*****************************************************************************
* Typedef  Enum
*****************************************************************************/
static ERROR_CODE_STRUCT  error_code_table[] =
{
    {"ERROR:100", TRUE},
    {"ERROR:101", TRUE},
    {"ERROR:102", TRUE},
    {"ERROR:103", TRUE},
    {"ERROR:104", TRUE},

    {"ERROR:105", TRUE},
    {"ERROR:106", TRUE},
    {"ERROR:107", TRUE},
    {"ERROR:108", TRUE},
    {"ERROR:109", TRUE},

    {"ERROR:110", TRUE},
    {"ERROR:111", TRUE},
    {"ERROR:112", TRUE},
    {"ERROR:113", TRUE},
    {"ERROR:114", TRUE},

    {"ERROR:115", FALSE},
    {"ERROR:116", TRUE},
    {"ERROR:117", TRUE},
    {"ERROR:118", TRUE},
    {"ERROR:119", TRUE},


    {"ERROR:120", TRUE},
    {"ERROR:121", TRUE},
    {"ERROR:122", TRUE},
    {"ERROR:123", TRUE},
    {"ERROR:124", TRUE},

};

#define ERRORCODETOTAL (sizeof(error_code_table)/sizeof(ERROR_CODE_STRUCT))
/*****************************************************************************
  *  Struct					���ݽṹ����
  *****************************************************************************/
#if defined(__STRING_USE_ARRAY__ )
static const char  ascii_error_code[25][180] =
{
    {"Error: The command length exceeds the ruled length."},
    {"Error: The command parameters is out of range."},
    {"Error: Wrong command format."},
    {"Error: Wrong password format."},
    {"Error: Family numbers exceeds the range that system can support."},

    {"Error: Family numbers is empty."},
    {"Error: The serial number is incorrect."},
    {"Error: This command does not exist."},
    {"Error: No terminal character, please end it with #."},
    {"Error: The command password is incorrect."},

    {"Error: Not supported for Non-Family number."},
    {"Error:Only SOS phone number to set."},
    {"the other party is during a conversation, please monitor later."},
    {"Set the SOS number must be a family number."},
    {"Error: Not supported for Non-Family and Non-SOS number."},

    {"Error: Don't allow monitoring during stealth period."},
    {"Error:Only center phone number to set."},
    {"Error:Only center phone number and SOS phone number to set."},
    {"The domain name or IP is locked,not allowed to modify."},
    {"Error:The new password and old password can not be the same."},

    {"Error:The parameters 3 and parameters 4 of the product should be less than or equal to the value of parameter 1."},
    {"Error:The value of parameters 2 should be less than or equal to the value of parameter 3."},
    {"Error:The content of the message exceeds the maximum length."},
    {"The terminal is in automatic security model, can not be manually fortification or disarm."},
    {""}

};

//ָ 6307
//{0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00,  0x53, 0x00, 0x4F, 0x00,  0x53, 0x00, 0x85, 0x8D,   0xFA, 0x51,  0x03, 0x83,   0xF4, 0x56, 0x2E, 0x00 },

static const char  unicode_error_code[25][80] =
{
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00, 0x07, 0x63, 0xE4, 0x4E, 0x7F, 0x95, 0xA6 , 0x5E,  0x85, 0x8D, 0xFA, 0x51, 0x03, 0x83, 0xF4, 0x56, 0x21, 0x00},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00, 0x07, 0x63, 0xE4, 0x4E, 0xC2, 0x53, 0x70, 0x65, 0x85, 0x8D, 0xFA, 0x51, 0x03, 0x83, 0xF4, 0x56, 0x21, 0x00},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00, 0x07, 0x63, 0xE4, 0x4E, 0x3C, 0x68, 0x0F, 0x5F, 0x0D, 0x4E, 0x63, 0x6B, 0x6E, 0x78, 0x21, 0x00},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00, 0xC6, 0x5B, 0x01, 0x78, 0x3C, 0x68, 0x0F, 0x5F, 0x0D, 0x4E, 0x63, 0x6B, 0x6E, 0x78, 0x21, 0x00},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00, 0xB2, 0x4E, 0xC5, 0x60, 0x35, 0x75, 0xDD, 0x8B, 0xF7, 0x53, 0x01, 0x78, 0x70, 0x65, 0xCF, 0x91, 0xF2, 0x5D, 0xE1, 0x6E, 0x21, 0x00},

    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00, 0xB2, 0x4E, 0xC5, 0x60, 0x35, 0x75, 0xDD, 0x8B, 0xF7, 0x53, 0x01, 0x78, 0x70, 0x65, 0xCF, 0x91, 0xF2, 0x5D, 0x7A, 0x7A, 0x21, 0x00},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00, 0x20, 0x52, 0x64, 0x96, 0x84, 0x76, 0x35, 0x75, 0xDD, 0x8B, 0xF7, 0x53, 0x01, 0x78, 0x8F, 0x5E, 0xF7, 0x53, 0x0D, 0x4E, 0x63, 0x6B , 0x6E, 0x78, 0x21, 0x00},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00, 0x07, 0x63, 0xE4 , 0x4E, 0x0D, 0x4E, 0x58, 0x5B, 0x28, 0x57, 0x21, 0x00},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00, 0xE0, 0x65, 0x07, 0x63, 0xE4, 0x4E, 0xD3, 0x7E, 0x5F, 0x67, 0x26, 0x7B, 0x23, 0x00, 0x21, 0x00},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B,  0x3A, 0x00, 0x07, 0x63, 0xE4, 0x4E, 0xC6, 0x5B, 0x01, 0x78, 0x19, 0x95, 0xEF, 0x8B, 0x21, 0x00},

    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B, 0x3A, 0x00, 0x5E, 0x97, 0xB2, 0x4E, 0xC5, 0x60, 0xF7, 0x53, 0x01, 0x78, 0x0D, 0x4E, 0xFD, 0x80, 0x7F, 0x4F, 0x28, 0x75, 0x64, 0x6B, 0x07, 0x63, 0xE4, 0x4E, 0x9F, 0x52, 0xFD, 0x80, 0x21, 0x00},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B, 0x1A, 0xFF, 0x5E, 0x97, 0x53, 0x00, 0x4F, 0x00, 0x53, 0x00, 0xF7, 0x53, 0x01, 0x78, 0x0D, 0x4E, 0xFD, 0x80, 0x7F, 0x4F, 0x28, 0x75, 0x64, 0x6B, 0x07, 0x63, 0xE4, 0x4E, 0x9F, 0x52, 0xFD, 0x80, 0x01, 0xFF},
    {0xF9, 0x5B, 0xB9, 0x65, 0x63, 0x6B, 0x28, 0x57, 0x1A, 0x90, 0xDD, 0x8B, 0x0C, 0xFF, 0xF7, 0x8B, 0x0D, 0x7A, 0x0E, 0x54, 0xD1, 0x76, 0x2C, 0x54, 0x21, 0x00},
    {0xBE, 0x8B, 0x6E, 0x7F, 0x84, 0x76, 0x53, 0x00, 0x4F, 0x00, 0x53, 0x00, 0xF7, 0x53, 0x01, 0x78, 0xC5, 0x5F, 0x7B, 0x98, 0x48, 0x51, 0x2F, 0x66, 0xB2, 0x4E, 0xC5, 0x60, 0xF7, 0x53, 0x01, 0x78, 0x02, 0x30},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B, 0x3A, 0x00, 0x5E, 0x97, 0x53, 0x00, 0x4F, 0x00, 0x53, 0x00, 0x8C, 0x54, 0x5E, 0x97, 0xB2, 0x4E, 0xC5, 0x60, 0xF7, 0x53, 0x01, 0x78, 0x0D, 0x4E, 0xFD, 0x80, 0x7F, 0x4F, 0x28, 0x75, 0x64, 0x6B, 0x07, 0x63, 0xE4, 0x4E, 0x9F, 0x52, 0xFD, 0x80, 0x02, 0x30},

    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B, 0x3A, 0x00, 0x90, 0x96, 0xAB, 0x8E, 0xF6, 0x65, 0xF4, 0x95, 0xB5, 0x6B, 0x85, 0x51, 0x0C, 0xFF, 0x0D, 0x4E, 0x41, 0x51, 0xB8, 0x8B, 0xD1, 0x76, 0x2C, 0x54, 0x02, 0x30},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B, 0x1A, 0xFF, 0x5E, 0x97, 0x2D, 0x4E, 0xC3, 0x5F, 0xF7, 0x53, 0x01, 0x78, 0x0D, 0x4E, 0xFD, 0x80, 0x7F, 0x4F, 0x28, 0x75, 0x64, 0x6B, 0x07, 0x63, 0xE4, 0x4E, 0x9F, 0x52, 0xFD, 0x80, 0x02, 0x30},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B, 0x1A, 0xFF, 0x5E, 0x97, 0x2D, 0x4E, 0xC3, 0x5F, 0xF7, 0x53, 0x01, 0x78, 0x8C, 0x54, 0x5E, 0x97, 0x53, 0x00, 0x4F, 0x00, 0x53, 0x00, 0xF7, 0x53, 0x01, 0x78, 0x0D, 0x4E, 0xFD, 0x80, 0x7F, 0x4F, 0x28, 0x75, 0x64, 0x6B, 0x07, 0x63, 0xE4, 0x4E, 0x9F, 0x52, 0xFD, 0x80, 0x02, 0x30},
    {0xDF, 0x57, 0x0D, 0x54, 0x16, 0x62, 0x49, 0x00, 0x50, 0x00, 0xF2, 0x5D, 0x01, 0x95, 0x0C, 0xFF, 0x0D, 0x4E, 0x41, 0x51, 0xB8, 0x8B, 0xEE, 0x4F, 0x39, 0x65, 0x02, 0x30},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B, 0x3A, 0x00, 0xB0, 0x65, 0xC6, 0x5B, 0x01, 0x78, 0x8C, 0x54, 0xE7, 0x65, 0xC6, 0x5B, 0x01, 0x78, 0x0D, 0x4E, 0xFD, 0x80, 0xF8, 0x76, 0x0C, 0x54, 0x02, 0x30},

    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B, 0x3A, 0x00, 0xC2, 0x53, 0x70, 0x65, 0x33, 0x00, 0x20, 0x00, 0x8C, 0x54, 0xC2, 0x53, 0x70, 0x65, 0x34, 0x00, 0x20, 0x00, 0x4B, 0x4E, 0x58, 0x4E, 0xEF, 0x79, 0x94, 0x5E, 0x0D, 0x4E, 0x27, 0x59, 0x8E, 0x4E, 0xC2, 0x53, 0x70, 0x65, 0x31, 0x00, 0x02, 0x30},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B, 0x3A, 0x00, 0xC2, 0x53, 0x70, 0x65, 0x32, 0x00, 0x20, 0x00, 0x94, 0x5E, 0x0D, 0x4E, 0x27, 0x59, 0x8E, 0x4E, 0xC2, 0x53, 0x70, 0x65, 0x33, 0x00, 0x02, 0x30},
    {0x07, 0x63, 0xE4, 0x4E, 0x19, 0x95, 0xEF, 0x8B, 0x3A, 0x00, 0xED, 0x77, 0xE1, 0x4F, 0x7F, 0x95, 0xA6, 0x5E, 0x85, 0x8D, 0xC7, 0x8F, 0x00, 0x67, 0x27, 0x59, 0xFD, 0x80, 0x04, 0x59, 0x06, 0x74, 0x7F, 0x95, 0xA6, 0x5E, 0x02, 0x30},
    {0xC8, 0x7E, 0xEF, 0x7A, 0x04, 0x59, 0x8E, 0x4E, 0xEA, 0x81, 0xA8, 0x52, 0xBE, 0x8B, 0x32, 0x96, 0x21, 0x6A, 0x0F, 0x5F, 0x0C, 0xFF, 0x0D, 0x4E, 0xFD, 0x80, 0x4B, 0x62, 0xA8, 0x52, 0xBE, 0x8B, 0x32, 0x96, 0x16, 0x62, 0xA4, 0x64, 0x32, 0x96, 0x02, 0x30},
    {0x00, 0x00}
};

//���ԷǷ����ĺ����ָ�ִ��!  //STR_SMS_OILELEC_NOT_CENTER
char oilelec_not_center[2][90] =
{
    {"The command is not from the center number, The command is not executed!"},
    {0x65, 0x67, 0xEA, 0x81, 0x5E, 0x97, 0xD5, 0x6C, 0x2D, 0x4E, 0xC3, 0x5F, 0xF7, 0x53, 0x01, 0x78, 0x84, 0x76, 0x07, 0x63, 0xE4, 0x4E, 0x0D, 0x4E, 0x67, 0x62, 0x4C, 0x88, 0x01, 0xFF}
};

//��ǰGPSδ��λ�����Ժ�����!   //STR_SMS_GPS_NO_LOCATION
char gps_noLocation_code[2][80] =
{
    {"GPS not fixed,please wait for a while, and then try again."},
    {0x53, 0x5F, 0x4D, 0x52, 0x47, 0x00, 0x50, 0x00, 0x53, 0x00, 0x2A, 0x67, 0x9A, 0x5B, 0x4D, 0x4F, 0x0C, 0xFF, 0xF7, 0x8B, 0x0D, 0x7A, 0x19, 0x50, 0x8D, 0x51, 0xD5, 0x8B, 0x01, 0xFF}
};

#if defined(__BOSCH_BMA250E__)
//Զ������ɹ�!
char defense_on_success[2][40] =
{
    {"Remote fortification success!"},
    {0xDC, 0x8F, 0x0B, 0x7A, 0xBE, 0x8B, 0x32, 0x96, 0x10, 0x62, 0x9F, 0x52, 0x01, 0xFF}
};

//Զ��������ɹ����뽫�𶯱������ܴ򿪺����ԡ�
//STR_SMS_DEFENSE_START_FAIL
char defense_on_fail[2][110] =
{
    {"The remote fortification unsuccessful, please vibration alarm function is turned on and try again."},
    {0xDC, 0x8F, 0x0B, 0x7A, 0xBE, 0x8B, 0x32, 0x96, 0x0D, 0x4E, 0x10, 0x62, 0x9F, 0x52, 0x0C, 0xFF, 0xF7, 0x8B, 0x06, 0x5C, 0x07, 0x97, 0xA8, 0x52, 0xA5, 0x62, 0x66, 0x8B, 0x9F, 0x52, 0xFD, 0x80, 0x53, 0x62, 0x00, 0x5F, 0x0E, 0x54, 0x8D, 0x51, 0xD5, 0x8B, 0x02, 0x30}
};

//�ն��Ѵ������״̬����ָ���ִ�У�
char defense_already_on[2][80] =
{
    {"Already in the state of fortification, The command is not executed!"},
    {0xC8, 0x7E, 0xEF, 0x7A, 0xF2, 0x5D, 0x04, 0x59, 0x8E, 0x4E, 0xBE, 0x8B, 0x32, 0x96, 0xB6, 0x72, 0x01, 0x60, 0x0C, 0xFF, 0x2C, 0x67, 0x07, 0x63, 0xE4, 0x4E, 0x0D, 0x4E, 0x8D, 0x51, 0x67, 0x62, 0x4C, 0x88, 0x01, 0xFF}
};

//Զ�̳����ɹ���
char defense_stop_success[2][30] =
{
    {"Remote disarm success!"},
    {0xDC, 0x8F, 0x0B, 0x7A, 0xA4, 0x64, 0x32, 0x96, 0x10, 0x62, 0x9F, 0x52, 0x01, 0xFF}
};

//�ն��Ѵ��ڳ���״̬����ָ���ִ�У�
char defense_stop_already[2][80] =
{
    {"Already in the state of disarm, The command is not executed!"},
    {0xC8, 0x7E, 0xEF, 0x7A, 0xF2, 0x5D, 0x04, 0x59, 0x8E, 0x4E, 0xA4, 0x64, 0x32, 0x96, 0xB6, 0x72, 0x01, 0x60, 0x0C, 0xFF, 0x2C, 0x67, 0x07, 0x63, 0xE4, 0x4E, 0x0D, 0x4E, 0x8D, 0x51, 0x67, 0x62, 0x4C, 0x88, 0x01, 0xFF}
};
#endif/*__BOSCH_BMA250E__*/
#endif/*__STRING_USE_ARRAY__*/

char syn_cmd_head[][MAX_CMD_HEAD_LEN] =
{
    "GTIMER",
    "TIMER",
    "PWRLIMIT",
    "RING",
    "CALLMODE",
    "SIMALM",
    "BATALM",
    "PWRONALM",
    "PWROFFALM",
    "BLINDALM",
    "SOSALM",
    "RINGVOL",
    "CALLVOL"
};

//U16 *ch_str =   L"����";
//coverting to execution character set:Invalid or incomplete multibte or wide character.

/*****************************************************************************
* Local variable				�ֲ�����
*****************************************************************************/
kal_bool is_unicode_replay_msg = KAL_FALSE;
#ifdef __ONLINE_CMD_NORMAL_REPLY__
char sms_buf[1024]; //[512];
char sms_buf_ex[1024];
static BOOL online_reply_encode_ascii = TRUE;  //�ظ��Ƿ�unicode ����
#else
char sms_buf[1024]; //[512];
char sms_buf_ex[1024];
#endif

static BOOL FactoryAllRestore = FALSE;   //�������в����ָ���������
#if defined(__SMS_TRANSMISSION__)
static kal_bool g_is_wait_DTU_msg = KAL_FALSE;
#endif

static BOOL SuperCommandHead = FALSE;     /*SUPER ����ָ��ͷ*/
static U8 DWSocConnecttimes = 0;        //DW ��ѯʱ�����쳣������������
BOOL is_sms_asc_dcs = FALSE ;


/****************************************************************************
* Global Variable            ȫ�ֱ���
*****************************************************************************/
BOOL is_online_see_cmd = FALSE; //�Ƿ��� SEEFN��ƽ̨�·�ָ����ظ���ѯ
U8 dwxx_flg = 0;
SYS_COMMAND_STATE Command_State = SMS_Command_State;
RECEIVED_DATA_STRUCT received_data = {0}; //���յ�������
SYS_SMS_STRUCT sys_rcv_sms = {0};       //���յ��Ķ�������
SYS_SMS_STRUCT sys_send_sms = {0};     //Ҫ���͵Ķ�������

#if defined(__SMS_TRANSMISSION__)
tracker_queryfee_struct queryfee_sms = {0};
#endif

#if defined(__KJX_AT_APP__)
kal_bool GPS_Updata_state = FALSE;//�鿴gps��Ϣ�Ƿ������־λ
#endif /*__AT_APP__*/

#if defined(__GPS_ON_MTK__)
int GetAddressLen = 0;    /*�������·���ַ����*/
#endif
kal_bool g_is_1hour_setup_open = KAL_FALSE; //�Ƿ��״�SOS 1Сʱ����ͨ��״̬

/****************************************************************************
* Global Variable - Extern          ����ȫ�ֱ���
*****************************************************************************/
extern kal_uint8 IMEIBuffer[SRV_IMEI_MAX_LEN + 1];    //358626020147641  /*���ں�̨��½*/
extern kal_uint8 IMSIBuffer[SRV_MAX_IMSI_LEN + 1]; 			/*�����жϷ�����*/ 
extern BOOL socketConnet;
extern U8 kjxImei[SRV_IMEI_MAX_LEN + 1];

#ifdef __KJX_FUN_GPS__
extern kjx_gps_data g_kjx_gps_data;
#endif
extern nvram_ef_kjx_nvram_struct g_kjx_nvram_struct;
extern kjx_socket_event_func g_kjx_socket_event_func;

#if defined(__SOC_APP__)
extern nvram_ef_tracker_apn_param_struct const  NVRAM_EF_TRACKER_APN_PARAM_DEFAULT[];
extern nvram_ef_tracker_server_param_struct const  NVRAM_EF_TRACKER_SERVER_PARAM_DEFAULT[];
#endif /*__SOC_APP__*/
#ifndef KJX_TEST
extern nvram_ef_tracker_sos_phb_struct const  NVRAM_EF_TRACKER_SOS_PHB_DEFAULT[];
extern nvram_ef_tracker_ctrl_data_struct const  NVRAM_EF_TRACKER_CTRL_DATA_DEFAULT[];
extern nvram_ef_tracker_last_lbs_data_struct NVRAM_EF_TRACKER_LBS_DATA_DEFAULT[];
extern nvram_ef_tracker_time_zone_struct const  NVRAM_EF_TRACKER_TIME_ZONE_DEFAULT[];
extern nvram_ef_tracker_imsi_change_struct const  NVRAM_EF_TRACKER_IMSI_DEFAULT[];
extern nvram_ef_tracker_low_battery_struct const  NVRAM_EF_TRACKER_LOW_BATTERY_DEFAULT[];
extern nvram_ef_tracker_permit_level_struct const NVRAM_EF_TRACKER_PERMIT_LEVEL_DEFAULT[];
#endif

#if defined(__KJX_LOG_OUTPUT__)
extern nvram_ef_kjx_log_param_struct const NVRAM_EF_KJX_LOG_PARAM_DEFAULT[];
#endif

#if defined(__SMS_PASSWORD__)
extern nvram_ef_tracker_password_struct const NVRAM_EF_TRACKER_PASSWORD_DEFAULT[];
#endif

#if defined(__SOS_CALL__)
extern nvram_ef_tracker_sos_type_struct const NVRAM_EF_TRACKER_SOS_TYPE_DEFAULT[];
#endif


#if defined(__BOSCH_BMA250E__)
extern nvram_ef_tracker_sensor_time_struct const NVRAM_EF_TRACKER_SENSOR_TIME_DEFAULT[];
#endif /*__BOSCH_BMA250E__*/



#if defined(__GPS_ON_MTK__)
#if defined(__GPS_OVERSPEED__)
extern nvram_ef_tracker_overspeed_alarm_struct const  NVRAM_EF_TRACKER_OVERSPEED_ALARM_DEFAULT[];
#endif
extern nvram_ef_tracker_gpsblindarea_alarm_struct const  NVRAM_EF_TRACKER_GPSBLINDAREA_ALARM_DEFAULT[];
#if defined(__GPS_FENCE__)
extern nvram_ef_tracker_electronic_fence_struct const  NVRAM_EF_TRACKER_ELECTRONIC_FENCE_DEFAULT[];
#endif /*__GPS_FENCE__*/
extern nvram_ef_tracker_delay_active_time_struct const NVRAM_EF_TRACKER_DELAY_ACTIVE_TIME_DEFAULT[];
#if defined(__GPS_BACKUP__)
extern nvram_ef_tracker_gps_backup_data_param_struct NVRAM_EF_TRACKER_GPS_BACKUP_DATA_PARAM_DEFAULT[];
#endif
#if defined(__MOVING_ALARM__)
extern nvram_ef_tracker_moving_param_struct const NVRAM_EF_TRACKER_MOVING_PARAM_DEFAULT[];
#endif

#endif  /*__GPS_ON_MTK__*/

#if defined(__ACC_DETECT__)
extern nvram_ef_tracker_acc_data_struct const NVRAM_EF_TRACKER_ACC_DATA_DEFAULT[];
#endif

#if defined(__OIL_ELECTRONIC_CONTROL__)
extern nvram_ef_tracker_cut_power_struct const NVRAM_EF_TRACKER_CUT_POWER_DEFAULT[];
#endif


#if defined(__SPECIAL_EPO_SOCKET__)
extern nvram_ef_tracker_epo_sever_struct const NVRAM_EF_TRACKER_EPO_SERVER_PARAM_DEFAULT[];
#elif defined(__SPECIAL_AGPS_SOCKET__)
extern nvram_ef_tracker_agps_sever_struct const NVRAM_EF_TRACKER_AGPS_SERVER_PARAM_DEFAULT[];
#endif


#if defined(__EXPAND_PORT_SUPPORT__)
extern nvram_ef_tracker_expand_export_struct const NVRAM_EF_TRACKER_EXPAND_EXPORT_DEFAULT[];
extern nvram_ef_tracker_backup_analog_param_struct const NVRAM_EF_TRACKER_BACKUP_ANALOG_PARAM_DEFAULT[];
extern nvram_ef_tracker_backup_digital_param_struct const NVRAM_EF_TRACKER_BACKUP_DIGITAL_PARAM_DEFAULT[];
#endif

#if defined(__CAR_OBD__)
extern nvram_ef_tracker_obd_param_struct const NVRAM_EF_TRACKER_OBD_PARAM_DEFAULT[];
#endif

#if defined(__FUEL_SENSOR__)
extern nvram_ef_tracker_fuel_param_struct NVRAM_EF_TRACKER_FUEL_PARAM_DEFAULT[];
extern nvram_ef_tracker_backup_fuel_param_struct const NVRAM_EF_TRACKER_BACKUP_FUEL_PARAM_DEFAULT[];
#endif

#if defined(__GPS_ON_MTK__)
#if defined(__GPS_BACKUP__)
extern nvram_ef_tracker_gps_backup_data_param_struct backup_data_param;
#endif
#endif
/*****************************************************************************
 *  Global Functions	- Extern		�����ⲿ����
 *****************************************************************************/
extern void KbCBackCallIncomingAccepted(void);
extern void log_printftofile(char * log_PintfBuf, kal_bool  is_delete_file);

/******************************************************************************
 *  Function    -  Get_GPS_Coordinate
 *
 *  Purpose     -  �����������ת��������
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 07-08-2010,  jwj  written
 * ----------------------------------------
 ******************************************************************************/
static kal_bool Get_GPS_Coordinate(char* coordinate, double* data)
{
    U8 i;
    char len;
    double  tmp;
    if((*coordinate == '0'))
    {
        *data = 0;
    }
    else if(!((*coordinate == 'N') || (*coordinate == 'S') || (*coordinate == 'E') || (*coordinate == 'W')
              || (*coordinate == '+') || (*coordinate == '-')))
    {
        return FALSE;
    }

    len = strlen(coordinate + 1);
    for(i = 1; i < len; i++)
    {
        if(*(coordinate + i) == '.')
            continue;
        if((*(coordinate + i) > '9') || (*(coordinate + i) < '0'))
        {
            *data = 0;
            return FALSE;

        }
    }
    tmp = atof(coordinate + 1);
    if((*coordinate == 'S') || (*coordinate == 'W') || (*coordinate == '-'))
    {
        tmp = -tmp;
    }
    if((tmp > 180) || (tmp < -180))
    {
        *data = 0;
        return FALSE;
    }
    *data = tmp;
    return TRUE;
}

/******************************************************************************
 *  Function    -  make_Capital_Letter
 *
 *  Purpose     -  ��Сд�ַ�ת��Ϊ��д�ַ�
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 26-05-2012,  guojie  arrange
 * ----------------------------------------
 ******************************************************************************/ 
 void make_Capital_Letter(char* buf)
 {
 	kal_uint16  i;
    for(i = 0; i < strlen(buf); i++)
    {
    	if(buf[i] >= 0x61 && buf[i] <= 0x7a)
        {
        	buf[i] -= 0x20;
		}
	}
}

/******************************************************************************
 *  Function    -  make_Capital_Letter_Ucs2
 *
 *  Purpose     -  ��UnicodeСд�ַ�ת��Ϊ��д�ַ�
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 26-05-2012,  guojie  arrange
 * ----------------------------------------
 ******************************************************************************/
void make_Capital_Letter_Ucs2(char* buf)
{
    kal_uint16  i, len;
    kal_uint16 *p;

    p = (kal_uint16 *)buf;
    len = mmi_ucs2strlen((char *)p);
    for(i = 0; i < len; i++)
    {
        if(p[i] >= 0x0061 && p[i] <= 0x007a)
        {
            p[i] -= 0x20;
        }
    }
}
/******************************************************************************
 *  Function    -  Make_Small_Letter_Ucs2
 *
 *  Purpose     -  ��Unicode�ַ���ת����Сд
 *
 *  Description -
 *
 * modification history

 ******************************************************************************/
void Make_Small_Letter_Ucs2(char* buf)
{
    kal_uint16  i, len;
    kal_uint16 *p;

    p = (kal_uint16 *)buf;
    len = mmi_ucs2strlen((char *)p);
    for(i = 0; i < len; i++)
    {
        if(p[i] >= 0x0041 && p[i] <= 0x005a)
        {
            p[i] += 0x20;
        }
    }
}
/******************************************************************************
 *  Function    -  make_ASCLL_Comma
 *
 *  Purpose     -  �����ת�ɶ���
 *
 *  Description -
 *  Input          -  *data
 *  Output       -   *content
 *  modification history
 * ----------------------------------------
 * v1.0  , 2011-11-2,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void make_ASCLL_Comma(void *content)
{
    U8  i;
    kal_wchar UCS2_String[10][4];
    kal_wchar   *UCS2_String_P, *UCS2_SMS_String;

    memset(UCS2_String, 0x00, sizeof(UCS2_String));
    UCS2_String[0][0] = 0XFF0C; //�����ַ�
    UCS2_String[1][0] = 12290; //���
    UCS2_String[2][0] = 0x3001; //�ٺ�
    UCS2_String[3][0] = 0xFF1B; //�ֺ�
    UCS2_String[4][0] = 59; //ASCLL��ķֺ�
    for(i = 0; i < 5; i++)
    {
        UCS2_String_P = (kal_wchar*)app_ucs2_wcsstr((kal_wchar*)content, UCS2_String[i]); //��������
        while(UCS2_String_P != NULL)
        {
            *UCS2_String_P = 44; //���ŵ�ASCLL��
            UCS2_SMS_String = UCS2_String_P;
            UCS2_String_P = (kal_wchar*)app_ucs2_wcsstr((kal_wchar*)UCS2_SMS_String, UCS2_String[i]);
        }
    }
}

/******************************************************************************
 *  Function    -  interval_Time_Manage
 *
 *  Purpose     -  ��ָ�����ʱ������Ϣת��Ϊ���ݣ�
 *
 *  Description - ��Ϊ��λ
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2011-11-04
 * ----------------------------------------
 ******************************************************************************/
 U16 interval_Time_Manage(U8 *data_str, U16 time_interval_min, U16  time_interval_max)
 {
 	U16 interval = 0;
    U8 str_len;
    U8 i = 0;
    S8 interval_data[5];

	str_len = strlen((char *)data_str);
    if((str_len == 1) && (*data_str == '0'))
    {
    	if(interval < time_interval_min)
        {
        	return 0xFFFF;
		}
        else
        {
        	interval = 0;
            return 0;
		}
	}
    if(str_len > 5 || str_len == 0)
    {
    	return 0xFFFF;
	}
    memset(interval_data, 0, 5);
    //interval_data[4] �����λ
    for(i = 0; i < str_len; i++)
    {
    	if(*(data_str + i) < '0' || *(data_str + i) > '9')
        {
        	return 0xFFFF;
		}
        interval_data[i] = (*(data_str + i)) - '0';
	}
    for(i = 0; i < str_len; i++)
    {
    	interval = interval * 10 + interval_data[i];
	}
    if((interval < time_interval_min) || (interval > time_interval_max))
	{
		return 0xFFFF;
	}
    return interval;
}

/******************************************************************************
 * FUNCTION:  - ���Ҷ��ŵ�ָ���־ͷ
 *
 * DESCRIPTION: -
 *    ���Ҷ��ŵ�ָ���־ͷ
 *
 * Input:
 * Output:
 * Returns:
 *
 * modification history
 ******************************************************************************/
static char* Parse_SMS_Head(char *data_ptr)
{
    U8 SMS_LEN;
    char* SMS_STR = NULL;
    char STR_LEN;
    char SMS_Head_STR[15] = {"GT_CM="};

    SMS_STR = strstr((char *)data_ptr, SMS_Head_STR);
    if(SMS_STR != NULL)
    {
        STR_LEN = strlen(SMS_Head_STR);
    }
    else
    {
        return NULL;
    }

    return (SMS_STR + STR_LEN);
}


/******************************************************************************
 *  Function    -  Parse_SUPER_Head
 *
 *  Purpose     -  SUPER,RECOVER#
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2014-07-17
 * ----------------------------------------
 ******************************************************************************/
static char* Parse_SUPER_Head(char *data_ptr)
{
	U8 SMS_LEN;
	char* SMS_STR = NULL;
	char STR_LEN;
	char SMS_SUPER_STR[15] = {"SUPER,"};

	SMS_STR = strstr((char *)data_ptr, SMS_SUPER_STR);
	if(SMS_STR != NULL)
	{
		STR_LEN = strlen(SMS_SUPER_STR);
		SuperCommandHead = TRUE;
	}
	else
	{
		SuperCommandHead = FALSE;
		return NULL;
	}

	return (SMS_STR + STR_LEN);
}

/******************************************************************************
 * FUNCTION:  - Tracker_TrimAllStr
 *
 * DESCRIPTION: -
 *    ȥ������ǰ��Ŀո�
 *
 * Input:
 * Output:
 * Returns:
 *
 * modification history
 ******************************************************************************/
void  Tracker_TrimAllStr(char * str, int len)
{
    char *p, *q;

    if(str == NULL)
    {
        return ;
    }

    for(p = str; (*p == ' ' || *p == '\t' || *p == '\n') && *p != '\0'; p++) ;

    for(q = str + len - 1 ; (*q == ' ' || *q == '\t'  || *p == '\n') && *q != '\0'; q--) ;
    *(++q) = '\0';
    if(q - p >= 1)
    {
        memmove(str, p, q - p + 1);
    }
}

/*---------------------------------------------------------------------------------------
 * FUNCTION			GPS_smscmd_checkparts
 *
 * DESCRIPTION		������ָ���ÿһ�������ֱ���ڲ�ͬ��buffer�У�
 *					����֮����,����
 *
 * PARAMETERS		void *src_data	����ָ��
 *					void *dest_data	���������buffer
 *
 * RETURNS			BOOL
 *
 *---------------------------------------------------------------------------------------*/
static BOOL Tracker_smscmd_checkparts(void *src_data, void *dest_data)
{
    int i = 0;
    U8 *dest = (U8*)dest_data;
    U8 *src = (U8*)src_data;

    for(i = 0; i < RCV_PARAM_DATA_MAX - 1; i++)
    {
        if(((*src) != ',') && ((*src) != '#'))
        {
            *dest = *src;
            src++;
            dest++;
        }
        else
        {
            *dest = '\0';
            return TRUE;
        }
    }
    return FALSE;
}


/*---------------------------------------------------------------------------------------
 * FUNCTION			Server_command_checkparts
 *
 * DESCRIPTION		���������·����ĵ�ַ��Ϣ�͵绰����ֶ�
 *					����֮����&&���� ��##��β
 *
 * PARAMETERS		void *src_data	����ָ��
 *					void *dest_data	���������buffer
 *
 * RETURNS			BOOL
 *
 *---------------------------------------------------------------------------------------*/
static BOOL Server_command_checkparts(void *src_data, void *dest_data)
{
    int i = 0;
    U8 *dest = (U8*)dest_data;
    U8 *src = (U8*)src_data;

    for(i = 0; i < RCV_PARAM_DATA_MAX * 4 - 1; i++)
    {
        if((((*src) == '&') && ((*(src + 1)) == '&')) || (((*src) == '#') && ((*(src + 1)) == '#')))
        {
            *dest = '\0';
            return TRUE;
        }
        else
        {
            *dest = *src;
            src++;
            dest++;
        }
    }
    return FALSE;
}

/*---------------------------------------------------------------------------------------
 * FUNCTION			Server_command_fn_checkparts
 *
 * DESCRIPTION		���������·����ĵ�ַ��Ϣ�͵绰����ֶ�
 *					����֮����&&���� ��##��β
 *
 * PARAMETERS		void *src_data	����ָ��
 *					void *dest_data	���������buffer
 *
 * RETURNS			BOOL
 *
 *---------------------------------------------------------------------------------------*/
static BOOL Server_command_fn_checkparts(void *src_data, void *dest_data)
{
    int i = 0;
    U8 *dest = (U8*)dest_data;
    U8 *src = (U8*)src_data;

    for(i = 0; i < RCV_PARAM_DATA_MAX * 4 - 1; i = i + 2)
    {
        if((((*(src)) == '&') && ((*(src + 2)) == '&')) || (((*(src)) == '#') && ((*(src + 2)) == '#')))
        {
            *dest = '\0';
            *(dest + 1) = '\0';
            return TRUE;
        }
        else
        {
            *dest = *src;
            src++;
            dest++;
            *dest = *src;
            src++;
            dest++;
        }
    }
    return FALSE;
}


/******************************************************************************
 *  Function    -  Is_Fetion_Num
 *
 *  Purpose     -  �Ƿ��Ƿ��Ų�ѯ
 *
 *  Description - ����:12520
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-07-02
 * ----------------------------------------
 ******************************************************************************/
static BOOL Is_Fetion_Num(void)
{
#if defined(__KD6113__)		//xb add 2015-12-03 ��ֹ����������֤ʱ��ʹ�÷���û����ȫƥ�䣬�������뵱��123ָ�����ִ�� ��PARAM,123456#
	return FALSE;
#endif

    if(strncmp((const char *)sys_rcv_sms.num, (const char *)"12520", 5) == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************
 *  Function    -  Delete_SmsPrefix_Confirm_SOSNum
 *
 *  Purpose     -  ɾ�����ź���ǰ׺ƥ���Ƿ���SOS����
 *
 *  Description - ����:12520
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-08-09
 * ----------------------------------------
 ******************************************************************************/
static U8 Delete_SmsPrefix_Confirm_SOSNum()
{
    U8 NumberIndex = 0XFF;
    char ReceiveSmsNum[21];

    memset(ReceiveSmsNum, 0, sizeof(ReceiveSmsNum));
    if(strncmp((const char *)sys_rcv_sms.num, (const char *)"12520", 5) == 0)
    {
        memcpy(ReceiveSmsNum, &sys_rcv_sms.num[5], 21 - 5);
    }
    else
    {
        memcpy(ReceiveSmsNum, &sys_rcv_sms.num[0], 21);
    }

#if defined(__SOS_CALL__)
    if(strlen((char*)ReceiveSmsNum) != 0)
    {
        NumberIndex = ConfirmNumberIsSOS((char*)ReceiveSmsNum);
    }
    else
    {
        NumberIndex = ConfirmNumberIsSOS((char*)sys_rcv_sms.num);
    }
#endif
    LOGD("%d,%s", NumberIndex, sys_rcv_sms.num);

    return NumberIndex;

}

/******************************************************************************
 *  Function    -  Delete_SmsPrefix_Confirm_CenterNum
 *
 *  Purpose     -  ɾ�����ź���ǰ׺ƥ���Ƿ������ĺ���
 *
 *  Description - ����:12520
 *                      //RDA �ֻ����͵ĺ������Ϊ 8615012584105
 * modification history  ֻ�����ĺ���ſ���ִ�ж��͵�ָ��
 * ----------------------------------------
 * v1.0  , 2012-08-09
 * ----------------------------------------
 ******************************************************************************/
static BOOL Delete_SmsPrefix_Confirm_CenterNum()
{
    BOOL Result = FALSE;
    char ReceiveSmsNum[21];

    memset(ReceiveSmsNum, 0, sizeof(ReceiveSmsNum));
    if(strncmp((const char *)sys_rcv_sms.num, (const char *)"12520", 5) == 0)
    {
        memcpy(ReceiveSmsNum, &sys_rcv_sms.num[5], 21 - 5);
    }
    else
    {
        memcpy(ReceiveSmsNum, &sys_rcv_sms.num[0], 21);
    }

    if(strlen((char*)ReceiveSmsNum) != 0)
    {
        Result = ConfirmNumberIsCenter((char*)ReceiveSmsNum);
    }
    else
    {
        Result = ConfirmNumberIsCenter((char*)sys_rcv_sms.num);
    }
    LOGD("%d,%s", Result, sys_rcv_sms.num);

    return Result;

}

#if defined(__SMS_PASSWORD__)
/*---------------------------------------------------------------------------------------
 * FUNCTION			tracker_is_password_format
 *
 * DESCRIPTION		�ж������ʽ�Ƿ���ȷ
 *
 * PARAMETERS		void *data	������ַ���
 *
 * RETURNS                  ֧�ִ�Сд��ĸ�����ֻ�����19λ
 *
 *---------------------------------------------------------------------------------------*/
static BOOL tracker_is_password_format(S8 *data, int len)
{
    int i = 0;

    if(len > 20 || len < 0)
    {
        return FALSE;
    }

    for(i = 0; i < len; i++)
    {
        if((*(data + i) < '0') || ((*(data + i) > '9') && (*(data + i) < 'A')) || ((*(data + i) > 'Z') && (*(data + i) < 'a')) || (*(data + i) > 'z'))
        {
            return FALSE;
        }
    }

    return TRUE;
}



/******************************************************************************
 *  Function    -  Tracker_Check_Authentication
 *
 *  Purpose     -  ������֤
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-12-22, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static BOOL Tracker_Check_Authentication(void)
{
    LOGD("  pass:%s,rec:%s", tracker_password.passwd, received_data.passwd);
    if(strcmp((char *)tracker_password.passwd, (char *)received_data.passwd) == 0)
    {
        return TRUE;
    }

    sprintf(sms_buf, "ERROR:109");
    Send_Command_Message_Replay();
    return FALSE;
}
#endif

/******************************************************************************
 *  Function    -  Tracker_Command_RESET
 *
 *  Purpose     -  �豸����
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-15, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Command_RESET(void)
{
    StopTimer(KJX_TIMER_RESET);
    LOGD(" Tracker_Command_RESET");

    AlmATPowerReset(MMI_FALSE, 3);
}

/******************************************************************************
 *  Function    -  SetNumber_is_num
 *
 *  Purpose     -  ��������Ƿ��Ǻ���
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 26-05-2012,  guojie  arrange
 * ----------------------------------------
 ******************************************************************************/
 BOOL SetNumber_is_num(S8 *data, int len)
 {
 	int i = 0;
    for(i = 0; i < len; i++)
    {
    	if(((*(data + i) > '9') || (*(data + i) < '0')) && (*(data + i) != '+'))
			return FALSE;
	}
    return TRUE;
}

/******************************************************************************
 *  Function    -  Tracker_Set_IMEI
 *
 *  Purpose     -  ��������IMEI
 *
 *  Description -  AT^GT_CM=IMEI,358626020147658#
 *        ����IMEI�ź��Զ�����
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-11-15, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_IMEI(void)
{
    U8 Len = 0, i = 0, j = 0;
    kal_bool ret;
    BOOL is_num = TRUE;
    U8 Char_Imei_L, Char_Imei_H, Str_Imei[17], IMEI_to_NVRAM[10];
    S16 Error;
    U8 tempbuf[16];
    U8 len = 0;

    if(Command_State == AT_Command_State 
 #if defined(__AT_USE_UART1__)
	|| Command_State == UART1_Command_State
 #endif
	|| Command_State == SMS_Command_State)
    {
        memset(sms_buf, 0, sizeof(sms_buf));
        if(received_data.part == 0)
        {
            sprintf(sms_buf, "IMEI:");
            strcat(sms_buf, IMEIBuffer);
            strcat(sms_buf, ";");
        }
        else if(received_data.part == 1)
        {
            Len = strlen((char *)received_data.param0);
            is_num = SetNumber_is_num((S8*)received_data.param0, Len);
            if(Len >= 16 || is_num == FALSE)
            {
                sprintf(sms_buf, "ERROR:102");
                if((Command_State == AT_Command_State)
			#if defined(__AT_USE_UART1__)
				||(Command_State == UART1_Command_State)
			#endif
			)
                {
                    strcat(sms_buf, ";IMEI,358626020147682#");
                }
                return;
            }

            memset(Str_Imei, 0, sizeof(Str_Imei));
            memset(IMEI_to_NVRAM, 0, sizeof(IMEI_to_NVRAM));

            memcpy(Str_Imei, received_data.param0, Len);

            memset(IMEIBuffer, 0x00, sizeof(IMEIBuffer));
            memcpy(IMEIBuffer, received_data.param0, Len);
			memcpy(kjxImei, IMEIBuffer, SRV_IMEI_MAX_LEN);

            for(i = 0, j = 0; i < 16;)
            {
                Char_Imei_L = Str_Imei[i] - 0x30;
                i++;
                Char_Imei_H = Str_Imei[i] - 0x30;
                i++;
                IMEI_to_NVRAM[j] = ((Char_Imei_H << 4) & 0xF0) | (Char_Imei_L & 0x0F);
                j++;
            }

            IMEI_to_NVRAM[8] = 0x00;
            IMEI_to_NVRAM[9] = 0x01;
            WriteRecord(NVRAM_EF_IMEI_IMEISV_LID, 1, &IMEI_to_NVRAM, NVRAM_EF_IMEI_IMEISV_SIZE, &Error);

		#if defined(__PARAM_BACKUP__)
            StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
		#endif
		
            sprintf(sms_buf, "OK!The system will reconnent after 10s");

			if(IsMyTimerExist(KJX_TIMER_ID_IS_CONNET))
				StopTimer(KJX_TIMER_ID_IS_CONNET);
			if(IsMyTimerExist(KJX_TIMER_ID_LOGIN_AGAIN))
				StopTimer(KJX_TIMER_ID_LOGIN_AGAIN);
			
			if(socketConnet)
				socketConnet = FALSE;
			kjx_socket_session_free();
			StartTimer(KJX_TIMER_ID_LOGIN_AGAIN, 10*1000, g_kjx_socket_event_func.socket_login_again);

		#if 0
            len = strlen((char*)IMEIBuffer);
            i = len % 2;
            memset(tempbuf, 0, sizeof(tempbuf));
            if(i)
            {
                tempbuf[0] = '0';
                memcpy((void *)&tempbuf[1], IMEIBuffer, len);
            }
            else
            {
                memcpy((void *)tempbuf, IMEIBuffer, len);
            }

            len = strlen((char *)tempbuf);

            //GPS_string2Hex(tempbuf, tracker_dev_id, len);

            //�رյ�ǰ���������������޸�IMEI��¼����
            //if(tracker_ctrl_data.GPRSAlwaysOn == 1 || tracker_ctrl_data.GPRSAlwaysOn == 2)
            //{
            //    StartTimer(TRACKER_SOCKET_CONNECT_TIMER, 5 * 1000, Tracker_Socket_TCP_Close_ReConnect);
            //}
		#endif
        }
        else
        {
            sprintf(sms_buf, (char*) "ERROR:100");//ָ������ֶζ�������ȷ
            if((Command_State == AT_Command_State)
		#if defined(__AT_USE_UART1__)
			||(Command_State == UART1_Command_State)
		#endif
			)
            {
                strcat(sms_buf, ";IMEI,358626020147682#");
            }
        }
    }
}



/******************************************************************************
 *  Function    -  Tracker_See_SIM_IMSI
 *
 *  Purpose     -  �鿴��ǰSIM����IMSI��
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-06-06, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_See_SIM_IMSI(void)
{
    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part == 0)
    {
        if(HaveGetIMSI == TRUE)
        {
            sprintf(sms_buf, "IMSI:%s.", IMSIBuffer);
        }
        else
        {
            sprintf(sms_buf, "Have not get IMSI.");
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");
    }


}

/******************************************************************************
 *  Function    -  Tracker_Sms_Set_Number
 *
 *  Purpose     -  ���ڷ��Ͷ���
 *
 *  Description -  AT^GT_CM=SMS,10086,123456
 *
 * modification history
  * ----------------------------------------
 * V1.0  , 2019-03-01, xiebiao written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Sms_Set_Number(void)
{
	U8 context[256] = {0};

	LOGD("num:%s,context:%s", received_data.param0, received_data.param1);
	
    if(received_data.part == 2)
    {
        if(SetNumber_is_num((S8*)received_data.param0, strlen((char*)received_data.param0))&&(strlen((S8*)received_data.param1) > 0))
        {
        	mmi_chset_convert(MMI_CHSET_GB18030, MMI_CHSET_UCS2, received_data.param1, context, sizeof(context));
			kjx_sms_send_sms(received_data.param0, context, SMSAL_UCS2_DCS, NULL);
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");
    }
}

/******************************************************************************
 *  Function    -  Tracker_Call_Set_Number
 *
 *  Purpose     -  ���ڲ���绰
 *
 *  Description -  AT^GT_CM=ATD,10086
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2014-05-14, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Call_Set_Number(void)
{
    U8 ucs2_phoneNum[42];
    if(received_data.part == 1)
    {
        if(SetNumber_is_num((S8*)received_data.param0, strlen((char*)received_data.param0)))
        {
            memset(ucs2_phoneNum, 0, sizeof(ucs2_phoneNum));
            mmi_asc_to_ucs2(ucs2_phoneNum, (S8 *)received_data.param0);  //�������
            MakeCall((PS8)ucs2_phoneNum);
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
        }

    }
    else
    {
        sprintf(sms_buf, "ERROR:100");
    }
}

/******************************************************************************
 *  Function    -  Tracker_Hangup_Call
 *
 *  Purpose     -  ���ڹҶϵ绰
 *
 *  Description -  AT^GT_CM=ATH
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2014-05-14, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Hangup_Call(void)
{
    if(received_data.part == 0)
    {
        if(IS_IN_CALL())
        {
            srv_ucm_end_all_action();
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "Not In Call.");
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");
    }
}

/******************************************************************************
 *  Function    -  Tracker_Accepted_Call
 *
 *  Purpose     -  ���ڽ����绰
 *
 *  Description -  AT^GT_CM=ATA
 *
 * modification history
 * ----------------------------------------
 * V1.0  , 2014-05-14, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Accepted_Call(void)
{
    if(received_data.part == 0)
    {
        StartTimer(KJX_TIMER_ID_REJECT_CALL, 1000, mmi_ucm_enter_incoming_call);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");
    }
}

/******************************************************************************
 *  Function    -  Tracker_Reply_Query_Battery_Voltage
 *
 *  Purpose     -  ��ѯ��ص�ѹ
 *
 *  Description -  AT^GT_CM=BMT
 *    3906-->3.906
 * modification history
  * ----------------------------------------
 * v1.0  , 2014-06-04, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Reply_Query_Battery_Voltage(void)
{
    U8 batter_precent = 0;
    kal_int32 battery_voltage = 0;
    char temp[12];

    StopTimer(KJX_TIMER_ID_QUERY_BATTERY_VOLTAGE);

    //����λ
    bmt_get_adc_channel_voltage(DCL_VBAT_ADC_CHANNEL, &battery_voltage);

    memset(temp, 0, sizeof(temp));
    sprintf(temp, "%d.%03d", battery_voltage/1000000, (battery_voltage-(battery_voltage/1000000)*1000000)/1000);

    memset(sms_buf, 0, sizeof(sms_buf));

	if(srv_charbat_get_charger_status(SRV_CHARBAT_STATUS_CHARGER_IN))
	{
		sprintf(sms_buf, "Chargering! voltage:");
	}
	else if(srv_charbat_get_charger_status(SRV_CHARBAT_STATUS_CHARGE_COMPLETE))
	{	
		sprintf(sms_buf, "Chargering full! voltage:");
	}
	else
	{
		sprintf(sms_buf, "No charger! voltage:");
	}

    strcat(sms_buf, temp);

    if(QueryCommandState == SMS_Command_State)
    {
        Command_State = SMS_Command_State;
    }
    else if(QueryCommandState == AT_Command_State)
    {
        Command_State = AT_Command_State;
    }
 #if defined(__AT_USE_UART1__)
	else if(QueryCommandState == UART1_Command_State)
    {
        Command_State = UART1_Command_State;
    }
 #endif
    else
    {
        Command_State = ONLine_Command_State;
    }
    Send_Command_Message_Replay();
}

/******************************************************************************
 *  Function    -  Tracker_Query_Battery_Voltage
 *
 *  Purpose     -  ��ѯ��ص�ѹ
 *
 *  Description -  AT^GT_CM=BMT
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2014-06-04, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Query_Battery_Voltage(void)
{
    if(Command_State == SMS_Command_State)
    {
        QueryCommandState = SMS_Command_State;
    }
    else if(Command_State == AT_Command_State)
    {
        QueryCommandState = AT_Command_State;
    }
 #if defined(__AT_USE_UART1__)
	else if(QueryCommandState == UART1_Command_State)
    {
        Command_State = UART1_Command_State;
    }
 #endif
    else
    {
        QueryCommandState = ONLine_Command_State;
    }
    StartTimer(KJX_TIMER_ID_QUERY_BATTERY_VOLTAGE, 1000, Tracker_Reply_Query_Battery_Voltage);
}

#if defined(__KJX_LOG_OUTPUT__)
/******************************************************************************
*  Function    -  Tracker_Set_Log_Param
*
*  Purpose     -  ������־���
*
*  Description -  AT^GT_CM=LOG,0#   �ر�
*                       AT^GT_CM=LOG,255#  ��������־
*                       AT^GT_CM=LOG,3,5#  ��������־
*                       AT^GT_CM=LOG,1,0#   ��1��־
* modification history
 * ----------------------------------------
* v1.0  , 2013-01-08, guojie  written
 * ----------------------------------------
******************************************************************************/
static void Tracker_Set_Log_Param(void)
{
    S16 error;
    U16 interval[3] = {0xffff, 0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[3][20];

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part > 3)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }

    //LOG#   ��ѯ��־��ǰ����
    //module:[0 0 0 0 0 0 0 ],target:1
    if(received_data.part == 0)
    {
        LOGD("  (Info:%s)", Kjx_Log_Modue_Info());
        sprintf(sms_buf, "%s", Kjx_Log_Modue_Info());
        return;
    }
    else if(received_data.part == 1)
    {
        memset(interval_str, 0, 60);
        memcpy(interval_str[0], received_data.param0, 20);
        interval[0] = interval_Time_Manage(interval_str[0], 0, 255);

        //LOG,0#   
        //�ر�������־���
        if(interval[0] == 0)
        {
            kjx_log_param.logd_module[L_CON] = 0;
            kjx_log_param.logd_module[L_DRV] = 0;
            kjx_log_param.logd_module[L_SOC] = 0;
            kjx_log_param.logd_module[L_CMD] = 0;
            kjx_log_param.logd_module[L_OS] = 0;
            kjx_log_param.logd_module[L_APP] = 0;
            kjx_log_param.logd_module[L_SYS] = 0;

            kjx_log_param.mod_level[L_CON] = 0;
            kjx_log_param.mod_level[L_DRV] = 0;
            kjx_log_param.mod_level[L_SOC] = 0;
            kjx_log_param.mod_level[L_CMD] = 0;
            kjx_log_param.mod_level[L_OS] = 0;
            kjx_log_param.mod_level[L_APP] = 0;
            kjx_log_param.mod_level[L_SYS] = 0;

            kjx_log_param.logd_target = LOG_OFF;
			log_printftofile(NULL, KAL_TRUE);
        }
        //LOG,255#  ��Ĭ�ϵȼ�5����������־
        else if(interval[0] == 255)
        {
            kjx_log_param.logd_module[L_CON] = 1;
            kjx_log_param.logd_module[L_DRV] = 1;
            kjx_log_param.logd_module[L_SOC] = 1;
            kjx_log_param.logd_module[L_CMD] = 1;
            kjx_log_param.logd_module[L_OS] = 1;
            kjx_log_param.logd_module[L_APP] = 1;
            kjx_log_param.logd_module[L_SYS] = 1;

            kjx_log_param.mod_level[L_CON] = 5;
            kjx_log_param.mod_level[L_DRV] = 5;
            kjx_log_param.mod_level[L_SOC] = 5;
            kjx_log_param.mod_level[L_CMD] = 5;
            kjx_log_param.mod_level[L_OS] = 5;
            kjx_log_param.mod_level[L_APP] = 5;
            kjx_log_param.mod_level[L_SYS] = 5;

            kjx_log_param.logd_target = LOG_SERIAL;
			log_printftofile(NULL, KAL_TRUE);
        }
		//LOG,100#	��Ĭ�ϵȼ�5����������־��������־д��T��
		else if(interval[0] == 100)
		{
			kjx_log_param.logd_module[L_CON] = 1;
            kjx_log_param.logd_module[L_DRV] = 1;
            kjx_log_param.logd_module[L_SOC] = 1;
            kjx_log_param.logd_module[L_CMD] = 1;
            kjx_log_param.logd_module[L_OS] = 1;
            kjx_log_param.logd_module[L_APP] = 1;
            kjx_log_param.logd_module[L_SYS] = 1;

            kjx_log_param.mod_level[L_CON] = 5;
            kjx_log_param.mod_level[L_DRV] = 5;
            kjx_log_param.mod_level[L_SOC] = 5;
            kjx_log_param.mod_level[L_CMD] = 5;
            kjx_log_param.mod_level[L_OS] = 5;
            kjx_log_param.mod_level[L_APP] = 5;
            kjx_log_param.mod_level[L_SYS] = 5;

            kjx_log_param.logd_target = LOG_FILE;
		}
        //LOG,2#
        else if((interval[0] >= 1) && (interval[0] <= 6))
        {
            kjx_log_param.logd_module[interval[0]] = 1;
            kjx_log_param.mod_level[interval[0]] = 5;
            kjx_log_param.logd_target = LOG_SERIAL;
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");//ָ��Ȳ���ȷ
            return;
        }
    }
    //LOG,3,0#   LOG,3,5#   LOG,255,2#
    else if(received_data.part == 2)
    {
        memset(interval_str, 0, 40);
        memcpy(interval_str[0], received_data.param0, 20);
        memcpy(interval_str[1], received_data.param1, 20);
        interval[0] = interval_Time_Manage(interval_str[0], 0, 255);      //0--6, 255
        interval[1] = interval_Time_Manage(interval_str[1], 0, 9);

        if(interval[0] == 0xffff || interval[1] == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
            return;
        }

        if(interval[0] == 255) //LOG,255,2#
        {
            kjx_log_param.logd_module[L_CON] = 1;
            kjx_log_param.logd_module[L_DRV] = 1;
            kjx_log_param.logd_module[L_SOC] = 1;
            kjx_log_param.logd_module[L_CMD] = 1;
            kjx_log_param.logd_module[L_OS] = 1;
            kjx_log_param.logd_module[L_APP] = 1;
            kjx_log_param.logd_module[L_SYS] = 1;

            kjx_log_param.mod_level[L_CON] = interval[1];
            kjx_log_param.mod_level[L_DRV] = interval[1];
            kjx_log_param.mod_level[L_SOC] = interval[1];
            kjx_log_param.mod_level[L_CMD] = interval[1];
            kjx_log_param.mod_level[L_OS] = interval[1];
            kjx_log_param.mod_level[L_APP] = interval[1];
            kjx_log_param.mod_level[L_SYS] = interval[1];

            kjx_log_param.logd_target = LOG_SERIAL;

        }
        else if((interval[0] >= 0) && (interval[0] <= 6)) //LOG,3,0#   LOG,3,5#
        {
            if(interval[1] == 0)
            {
                kjx_log_param.logd_module[interval[0]] = 0;
                kjx_log_param.mod_level[interval[0]] = 0;
            }
            else
            {
                kjx_log_param.logd_module[interval[0]] = 1;
                kjx_log_param.mod_level[interval[0]] = interval[1] ;

			#if defined(__KJX_LOG_OUTPUT__)
                LOGD(" %d,%d,module[%d]=%d", interval[0], interval[1], kjx_log_param.logd_module[interval[0]]);
			#endif
            }
            kjx_log_param.logd_target = LOG_SERIAL;
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
            return;
        }
    }
    else if(received_data.part == 3)
    {
        memset(interval_str, 0, 60);
        memcpy(interval_str[0], received_data.param0, 20);
        memcpy(interval_str[1], received_data.param1, 20);
        memcpy(interval_str[2], received_data.param2, 20);

        interval[0] = interval_Time_Manage(interval_str[0], 0, 6);
        interval[1] = interval_Time_Manage(interval_str[1], 1, 9);
        interval[2] = interval_Time_Manage(interval_str[2], 0, 5);  //OFF  OUTO SERIAL CATCHER FILE GPRS

        if(interval[0] == 0xffff || interval[1] == 0xffff || interval[2] == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
            return;
        }

        kjx_log_param.logd_module[interval[0]] = 1;
        kjx_log_param.mod_level[interval[0]] = interval[1];
        kjx_log_param.logd_target = interval[2];
        if(kjx_log_param.logd_target == LOG_FILE)
        {
            log_printftofile(" ", 1);
        }
    }

    LOGD(" %s", Kjx_Log_Modue_Info());

    WriteRecord(NVRAM_EF_KJX_LOG_PARAM_LID, 1, &kjx_log_param, NVRAM_EF_KJX_LOG_PARAM_SIZE, &error);
    sprintf(sms_buf, "OK");
}
#endif


/*****************************************************************************
*  Function    -  Update_System_Time
*
*  Purpose     -  GPS��λ�����ϵͳʱ��
*
*  Description - 	��������һ�ζ�λ�ɹ����ʱ��ͬ������?
*                   �ڶ���ͬ���Ÿ���
* modification history
* ----------------------------------------
* v1.0  , 2012-06-14,  guojie  written
* ----------------------------------------
*****************************************************************************/
void Update_System_Time(MYTIME *currTime)
{
	S16 Error;
    t_rtc rtctime = {0};
    rtc_format_struct   New_DateTime;
    
    memset(&New_DateTime, 0, sizeof(MYTIME));
    memset(&rtctime, 0, sizeof(t_rtc));
    New_DateTime.rtc_year = currTime->nYear - 2000;
    New_DateTime.rtc_mon = currTime->nMonth;
    New_DateTime.rtc_day = currTime->nDay;
    New_DateTime.rtc_hour = currTime->nHour;
    New_DateTime.rtc_min = currTime->nMin;
    New_DateTime.rtc_sec = currTime->nSec;
    SetDateTime(&New_DateTime);
    rtctime.rtc_year = currTime->nYear - 2000;
    rtctime.rtc_mon = currTime->nMonth;
    rtctime.rtc_day = currTime->nDay;
    rtctime.rtc_hour = currTime->nHour;
    rtctime.rtc_min = currTime->nMin;
    rtctime.rtc_sec = currTime->nSec;
    RTC_InitTC_Time(&rtctime);
#ifndef __MTK_TARGET__
	DateTimerProc();
    /* Fucntion to update and display date and time. This function is used in PC simulator only.*/
#endif
	update_mainlcd_dt_display();
    update_sublcd_dt_display();
}

/******************************************************************************
 *  Function    -  Tracker_Set_Datetime
 *
 *  Purpose     - ����ʱ��
 *
 *  Description -  TIMESET,Y,M,D,H,M,S#
 *                        TIMESET#   ��ѯ����
 * modification history
 * ----------------------------------------
 * v1.0  , 2014-02-14, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Datetime(void)
{
    S16 Error;
    MYTIME t, old_t;

    if(received_data.part == 0)
    {
        GetDateTime(&t);
        sprintf(sms_buf, "DateTime: %d-%d-%d %d:%d:%d"
                , t.nYear, t.nMonth, t.nDay, t.nHour, t.nMin, t.nSec);
        return;
    }

    if(received_data.part != 5 && received_data.part != 6 && received_data.part != 3)
    {
        sprintf(sms_buf, "Error: TIMESET,2013,8,23,11,20,0#");
        return;
    }

    GetDateTime(&old_t);  //ԭ��ʱ��

    memset(&t, 0, sizeof(MYTIME));
    t.nYear = atoi(received_data.param0);
    t.nMonth = atoi(received_data.param1);
    t.nDay = atoi(received_data.param2);
    if(received_data.part > 3)
    {
        t.nHour = atoi(received_data.param3);
        t.nMin = atoi(received_data.param4);
        t.nSec = atoi(received_data.param5);
    }
    else
    {
        t.nHour = old_t.nHour;
        t.nMin = old_t.nMin;
        t.nSec = old_t.nSec;
    }

    if(!t.nYear || !t.nMonth || !t.nDay)
    {
        t.nYear = old_t.nYear;
        t.nMonth = old_t.nMonth;
        t.nDay = old_t.nDay;
    }

    if((t.nMonth < 1 || t.nMonth > 12) || (t.nDay < 1 || t.nDay > 31)
            || (t.nHour < 0 || t.nHour > 23) || (t.nMin < 0 || t.nMin > 59) || (t.nSec < 0 || t.nSec > 59))
    {
        sprintf(sms_buf, "Error: TIMESET,2013,8,23,11,20,0#");
        return;
    }

    Update_System_Time(&t);
    sprintf(sms_buf, "OK. DateTime: %d-%d-%d %d:%d:%d"
            , t.nYear, t.nMonth, t.nDay, t.nHour, t.nMin, t.nSec);
}

/******************************************************************************
 *  Function    -  Tracker_Set_APN
 *
 *  Purpose     -  ����APN
 *
 *  Description -  AT^GT_CM=APN,������[,��½��,����]#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-01, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_APN(void)
{
#ifdef __KJX_FUN__
    U16 str_len,len;
	extern kal_bool g_set_gprs_account;//�˺��Ѿ����ñ��

    if(received_data.part == 0)
    {
        sprintf(sms_buf, "Currently in use APN:%s,%s,%s;", g_kjx_nvram_struct.apn.apnMode, g_kjx_nvram_struct.apn.userName, g_kjx_nvram_struct.apn.passWord);
    }
    else if(received_data.part <= 3)
    {
        memset(sms_buf, 0, sizeof(sms_buf));

	   	str_len = strlen((char *)received_data.param0);//APN
	   	len = str_len < sizeof(g_kjx_nvram_struct.apn.apnMode) ? str_len : sizeof(g_kjx_nvram_struct.apn.apnMode);
		memcpy(g_kjx_nvram_struct.apn.apnMode, (char *)received_data.param0, len);

		str_len = strlen((char *)received_data.param1); //�û���
	   	len = str_len < sizeof(g_kjx_nvram_struct.apn.userName) ? str_len : sizeof(g_kjx_nvram_struct.apn.userName);
		memcpy(g_kjx_nvram_struct.apn.userName, (char *)received_data.param1, len);
		
		str_len = strlen((char *)received_data.param2); //����
	   	len = str_len < sizeof(g_kjx_nvram_struct.apn.passWord) ? str_len : sizeof(g_kjx_nvram_struct.apn.passWord);
		memcpy(g_kjx_nvram_struct.apn.passWord, (char *)received_data.param2, len);

        sprintf(sms_buf, "OK!Set APN:%s,%s,%s;The system will reconnent after 10s", g_kjx_nvram_struct.apn.apnMode, g_kjx_nvram_struct.apn.userName, g_kjx_nvram_struct.apn.passWord);  

		kjx_set_apn_infos();
		
		if(IsMyTimerExist(KJX_TIMER_ID_IS_CONNET))
			StopTimer(KJX_TIMER_ID_IS_CONNET);
		if(IsMyTimerExist(KJX_TIMER_ID_LOGIN_AGAIN))
			StopTimer(KJX_TIMER_ID_LOGIN_AGAIN);
					
		if(socketConnet)
			socketConnet = FALSE;
		kjx_socket_session_free();
		StartTimer(KJX_TIMER_ID_LOGIN_AGAIN, 10*1000, g_kjx_socket_event_func.socket_login_again);
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");                 //ָ������ֶζ�������ȷ
    }

#else

    S8 ip[4];
    S8 dev_id[6];
    U16 server_port = 0;
    U16 str_len1, str_len2, len;
    U8 accout_id = 0;
    U8 temp[20];
    S16 Error;
    BOOL rpt = TRUE;
    char temp1[200] = {0};

    if(received_data.part == 0)
    {
        memset(temp1, 0, sizeof(temp1));

        sprintf(temp1, "Currently in use APN:%s,%s,%s;", (S8*)tracker_apn_param.apn, (S8*)tracker_apn_param.user_name, (S8*)tracker_apn_param.password);

        strcpy((char*)sms_buf, (char*)temp1);
    }
    else if(received_data.part <= 4)
    {
        memset(sms_buf, 0, sizeof(sms_buf));
        if(strlen((char*)received_data.param3) != 0)  //���ipΪ��Ϊ������ip�Ƿ���ȷ
        {
            if((system_string2U16(received_data.param3)) >= 256)
            {
                rpt = FALSE;
            }
            else
            {
                accout_id = system_string2U16(received_data.param3);
            }
        }
        else
        {
            accout_id = tracker_apn_param.Net_ID;
        }
        if(strlen((char*)received_data.param4) != 0)  //���ipΪ��Ϊ������ip�Ƿ���ȷ
        {
            if(sys_asciiIP2Hex(received_data.param4, ip) == FALSE)
            {
                rpt = FALSE;
            }
        }
        else
        {
            memset(ip, 0, 4);
        }
        str_len1 = strlen((char *)received_data.param1); //�û���
        str_len2 = strlen((char *)received_data.param2); //����

        if((!str_len1 && str_len2) || (str_len1 >= 32) || (str_len2 >= 32))
        {
            rpt = FALSE;
        }
        if(rpt == TRUE)
        {
            strcpy((S8*)tracker_apn_param.apn, (S8 *)received_data.param0);
            tracker_apn_param.Net_ID = accout_id;
            memset(tracker_apn_param.user_name, 0, 32);
            memset(tracker_apn_param.password, 0, 32);
            if(str_len1)
            {
                memcpy(tracker_apn_param.user_name, received_data.param1, str_len1);
                memcpy(tracker_apn_param.password, received_data.param2, str_len2);
            }
            memcpy(tracker_apn_param.ip, ip, 4);

		#if defined(__APN_ADAPT__)
            //�ֶ�����APN�󣬹ر�����Ӧ����
            tracker_apn_param.AutoSetAPN = 0;
		#endif

            WriteRecord(NVRAM_EF_TRACKER_APN_LID, 1, &tracker_apn_param, NVRAM_EF_TRACKER_APN_SIZE, &Error);

		#if defined(__PARAM_BACKUP__)
            StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
		#endif


            sprintf(sms_buf, "OK");

            Tracker_socket_APN_Set();

            if(tracker_ctrl_data.GPRSAlwaysOn == 1 || tracker_ctrl_data.GPRSAlwaysOn == 2)
            {
                StartTimer(TRACKER_SOCKET_CONNECT_TIMER, 5 * 1000, Tracker_Socket_TCP_Close_ReConnect);
            }
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");                 //ָ������ֶζ�������ȷ
    }
#endif
}

#if defined(__APN_ADAPT__)
/******************************************************************************
 *  Function    -  Tracker_Set_APN_Auto_Adaption
 *
 *  Purpose     -  APN����Ӧ���ܿ����͹ر�
 *
 *  Description -  ASETAPN,ON#   ASETAPN,OFF#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-12-19, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_APN_Auto_Adaption(void)
{
    S16 Error;
    char temp[100] = {0};
    char data[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));
    memset(temp, 0, 100);
    memset(data, 0, 200);

    if(received_data.part == 0)
    {
        if(tracker_apn_param.AutoSetAPN == 0)
        {
            sprintf(temp, "ASETAPN:OFF;");
        }
        else
        {
            sprintf(temp, "ASETAPN:ON;");
        }
        strcpy(data, temp);

        memset(temp, 0, 100);
        sprintf(temp, "Currently in use APN:%s;", (char *)tracker_apn_param.apn);
        strcat(data, temp);

        memset(temp, 0, 100);
        sprintf(temp, "UserName:%s;", (char *)tracker_apn_param.user_name);
        strcat(data, temp);

        memset(temp, 0, 100);
        sprintf(temp, "Password:%s;", (char *)tracker_apn_param.password);
        strcat(data, temp);

        strcpy((char*)sms_buf, (char*)data);
    }
    else if(received_data.part == 1)
    {
        if((strcmp((char*)received_data.param0, "ON") == 0) || (strcmp((char*)received_data.param0, "OFF") == 0))
        {

            if(strcmp((char*)received_data.param0, "ON") == 0)
            {
                tracker_apn_param.AutoSetAPN = 1;
            }
            else
            {
                tracker_apn_param.AutoSetAPN = 0;
            }
            WriteRecord(NVRAM_EF_TRACKER_APN_LID, 1, (void *)&tracker_apn_param, NVRAM_EF_TRACKER_APN_SIZE, &Error);
            sprintf(sms_buf, "OK");

            StartTimer(TRACKER_GET_IMSI_TIMER, 10 * 1000, Tracker_get_IMSI_req);
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");       //ָ������ֶζ�������ȷ
    }

    LOGD(" %d", tracker_apn_param.AutoSetAPN);

}
#endif

/******************************************************************************
 *  Function    -  Tracker_Set_Server
 *
 *  Purpose     -  ����SERVER
 *
 *  Description -  SERVER,113.105.139.158,8827#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-01, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Server(void)
{
#ifdef __KJX_FUN__
	U16 server_port = 0;
    U16 len;
    S16 Error;
    BOOL rpt = TRUE;
	
    if(received_data.part == 0)
    {
		sprintf((char *)sms_buf, "Currently in use Server:%s:%d;", g_kjx_nvram_struct.domain.domain, g_kjx_nvram_struct.domain.port);
    }
    else if(received_data.part == 2)
    {
        memset(sms_buf, 0, sizeof(sms_buf));

		memset(g_kjx_nvram_struct.domain.domain, 0, sizeof(g_kjx_nvram_struct.domain.domain));
		memcpy(g_kjx_nvram_struct.domain.domain, (void *)&received_data.param0, strlen(received_data.param0));
		g_kjx_nvram_struct.domain.port = atoi(received_data.param1);
        WriteRecord(NVRAM_EF_KJX_APPICON_LID,1, &g_kjx_nvram_struct, NVRAM_EF_KJX_APPICON_SIZE, &Error);

		sprintf(sms_buf, "OK!The system will reconnent after 10s");

		kjx_set_domain_infos();
		
		if(IsMyTimerExist(KJX_TIMER_ID_IS_CONNET))
			StopTimer(KJX_TIMER_ID_IS_CONNET);
		if(IsMyTimerExist(KJX_TIMER_ID_LOGIN_AGAIN))
			StopTimer(KJX_TIMER_ID_LOGIN_AGAIN);
				
		if(socketConnet)
			socketConnet = FALSE;
		kjx_socket_session_free();
		StartTimer(KJX_TIMER_ID_LOGIN_AGAIN, 10*1000, g_kjx_socket_event_func.socket_login_again);
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");  //ָ������ֶζ�������ȷ
    }

#else
    U16 server_port = 0;
    U16 len;
    S16 Error;
    BOOL rpt = TRUE;
    if(received_data.part == 0)
    {
        if(tracker_server_param.conecttype == 0)
        {
            sprintf((char *)sms_buf, "Currently in use Server:%d,%d.%d.%d.%d,%d,%d;", tracker_server_param.conecttype, tracker_server_param.server_ip[0], tracker_server_param.server_ip[1], \
                    tracker_server_param.server_ip[2], tracker_server_param.server_ip[3], tracker_server_param.server_port, tracker_server_param.soc_type);
        }
        else
        {
            sprintf((char *)sms_buf, "Currently in use Server:%d,%s,%d,%d;", tracker_server_param.conecttype, tracker_server_param.url, tracker_server_param.server_port, tracker_server_param.soc_type);
        }
    }
    else if(received_data.part == 4)
    {
        //��������
        if(tracker_server_param.lock)
        {
            sprintf(sms_buf, "ERROR:118");
            return;
        }

        memset(sms_buf, 0, sizeof(sms_buf));
        if(((received_data.param0[0] == '0') || (received_data.param0[0] == '1')) && (strlen((S8*)received_data.param0) == 1))
        {
            rpt = TRUE ;
        }
        else
        {
            rpt = FALSE;
        }
        if(received_data.param0[0] == '0')
        {
            if(sys_asciiIP2Hex(received_data.param1, ip) == FALSE)
            {
                rpt = FALSE;
            }
        }
        else
        {
            len = strlen((char *)received_data.param1);
            if(!len || len >= 100 || strstr((char*)received_data.param1, "http://"))
                rpt = FALSE;
        }

        if(check_right_data_of_param(received_data.param2) == TRUE)
        {
            server_port = system_string2U16(received_data.param2);
        }
        else
        {
            rpt = FALSE;
        }
        if(((received_data.param3[0] != '0') && (received_data.param3[0] != '1')) || (strlen((S8*)received_data.param3) != 1))
        {
            rpt = FALSE;
        }
        if(rpt == TRUE)
        {
            tracker_server_param.conecttype = received_data.param0[0] - '0';
            tracker_server_param.soc_type = received_data.param3[0] - '0';
            if(received_data.param0[0] == '1')
            {
                memset((void *)tracker_server_param.url, 0, 100);
                memcpy((void *)&tracker_server_param.url, (void *)&received_data.param1, len);
                tracker_server_param.server_port = server_port;
                tracker_server_param.IsSaveIP = 0;
            }
            else if((received_data.param0[0] == '0'))
            {
                memcpy(tracker_server_param.server_ip, ip, 4);
                tracker_server_param.server_port = server_port;
                tracker_server_param.IsSaveIP = 0;
            }

            WriteRecord(NVRAM_EF_TRACKER_SERVER_LID, 1, &tracker_server_param, NVRAM_EF_TRACKER_SERVER_SIZE, &Error);

		#if defined(__PARAM_BACKUP__)
            StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
		#endif

            sprintf(sms_buf, "OK");

            if(tracker_server_param.conecttype == 1)
            {
                memset(&soc_content.soc_addr, 0, sizeof(soc_content.soc_addr));
            }

            if(tracker_ctrl_data.GPRSAlwaysOn == 1 || tracker_ctrl_data.GPRSAlwaysOn == 2)
            {
                StartTimer(TRACKER_SOCKET_CONNECT_TIMER, 5 * 1000, Tracker_Socket_TCP_Close_ReConnect);
            }
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
        }

    }
    else
    {
        sprintf(sms_buf, "ERROR:100");  //ָ������ֶζ�������ȷ
    }
#endif	
}


#if defined(__SPECIAL_EPO_SOCKET__)
/******************************************************************************
 *  Function    -  Tracker_Set_EPOServer
 *
 *  Purpose     -  ����EPOSERVER
 *
 *  Description -  EPOSERVER,1,agps.topstargps.com,12283,0#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2014-06-09, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_EPOServer(void)
{
    S8 ip[4];
    U16 server_port = 0;
    U16 len;
    S16 Error;
    BOOL rpt = TRUE;
    if(received_data.part == 0)
    {
        if(tracker_epo_server.conecttype == 0)
        {
            sprintf((char *)sms_buf, "Currently in use EPOServer:%d,%d.%d.%d.%d,%d,%d;", tracker_epo_server.conecttype, tracker_epo_server.server_ip[0], tracker_epo_server.server_ip[1], \
                    tracker_epo_server.server_ip[2], tracker_epo_server.server_ip[3], tracker_epo_server.server_port, tracker_epo_server.soc_type);
        }
        else
        {
            sprintf((char *)sms_buf, "Currently in use EPOServer:%d,%s,%d,%d;", tracker_epo_server.conecttype, tracker_epo_server.url, tracker_epo_server.server_port, tracker_epo_server.soc_type);
        }
    }
    else if(received_data.part == 4)
    {

        memset(sms_buf, 0, sizeof(sms_buf));
        if(((received_data.param0[0] == '0') || (received_data.param0[0] == '1')) && (strlen((S8*)received_data.param0) == 1))
        {
            rpt = TRUE ;
        }
        else
        {
            rpt = FALSE;
        }
        if(received_data.param0[0] == '0')
        {
            if(sys_asciiIP2Hex(received_data.param1, ip) == FALSE)
            {
                rpt = FALSE;
            }
        }
        else
        {
            len = strlen((char *)received_data.param1);
            if(!len || len >= 100 || strstr((char*)received_data.param1, "http://"))
                rpt = FALSE;
        }

        if(check_right_data_of_param(received_data.param2) == TRUE)
        {
            server_port = system_string2U16(received_data.param2);
        }
        else
        {
            rpt = FALSE;
        }
        if(((received_data.param3[0] != '0') && (received_data.param3[0] != '1')) || (strlen((S8*)received_data.param3) != 1))
        {
            rpt = FALSE;
        }
        if(rpt == TRUE)
        {
            tracker_epo_server.conecttype = received_data.param0[0] - '0';
            tracker_epo_server.soc_type = received_data.param3[0] - '0';
            if(received_data.param0[0] == '1')
            {
                memset((void *)tracker_epo_server.url, 0, 100);
                memcpy((void *)&tracker_epo_server.url, (void *)&received_data.param1, len);
                tracker_epo_server.server_port = server_port;
                tracker_epo_server.IsSaveIP = 0;
            }
            else if((received_data.param0[0] == '0'))
            {
                memcpy(tracker_epo_server.server_ip, ip, 4);
                tracker_epo_server.server_port = server_port;
                tracker_epo_server.IsSaveIP = 0;
            }

            WriteRecord(NVRAM_EF_TRACKER_EPO_SERVER_LID, 1, &tracker_epo_server, NVRAM_EF_TRACKER_EPO_SERVER_SIZE, &Error);

            sprintf(sms_buf, "OK");

		#if defined (__PARAM_BACKUP__)
            StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
		#endif
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
        }

    }
    else
    {
        sprintf(sms_buf, "ERROR:100");  //ָ������ֶζ�������ȷ
    }
}


/******************************************************************************
 *  Function    -  Tracker_Set_EPO_State
 *
 *  Purpose     -  ����EPO��ȡ״̬
 *
 *  Description -  EPOSTATE,1#
 *                       EPOSTATE,1,2014,7,22#
 *                       EPOSTATE,0#
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-15, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_EPO_State(void)
{
#ifndef KJX_TEST
    S16 error;
    U16  interval[4];
    U8 interval_str[20][4];
    char temp1[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));
    memset(interval, 0, sizeof(interval));
    if(received_data.part == 0)
    {
        sprintf(sms_buf, "EPOSTATE:%d,%d,%d,%d.", tracker_epo_server.currdaygetepo, tracker_epo_server.curryear, tracker_epo_server.currmonth, tracker_epo_server.currday);
    }
    else if(received_data.part == 1)
    {
        if(strcmp((char*)received_data.param0, "0") == 0)
        {
            tracker_epo_server.currdaygetepo = 0;
            tracker_epo_server.curryear = 0;
            tracker_epo_server.currmonth = 0;
            tracker_epo_server.currday = 0;
            WriteRecord(NVRAM_EF_TRACKER_EPO_SERVER_LID, 1, (void *)&tracker_epo_server, NVRAM_EF_TRACKER_EPO_SERVER_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");
        }
    }
    else if(received_data.part == 4)
    {
        if(strcmp((char*)received_data.param0, "1") == 0)
        {
            memset(&interval_str, 0, 80);
            memcpy(interval_str[1], received_data.param1, 20);
            memcpy(interval_str[2], received_data.param2, 20);
            memcpy(interval_str[3], received_data.param3, 20);

            interval[1] = interval_Time_Manage(interval_str[1], 2014 , 2114);
            interval[2] = interval_Time_Manage(interval_str[2], 1 , 12);
            interval[3] = interval_Time_Manage(interval_str[3], 1 , 31);


            if(interval[1] != 0xffff && interval[2] != 0xffff && interval[3] != 0xffff)
            {
                tracker_epo_server.currdaygetepo = 1;
                tracker_epo_server.curryear = interval[1];
                tracker_epo_server.currmonth = interval[2];
                tracker_epo_server.currday = interval[2];
                WriteRecord(NVRAM_EF_TRACKER_EPO_SERVER_LID, 1, (void *)&tracker_epo_server, NVRAM_EF_TRACKER_EPO_SERVER_SIZE, &error);
                sprintf(sms_buf, "OK");
            }
            else
            {
                sprintf(sms_buf, "ERROR:101");
            }
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");
        }

    }
    else
    {
        sprintf(sms_buf, "ERROR:100");
    }
#endif	
}
#elif defined(__SPECIAL_AGPS_SOCKET__)
/******************************************************************************
 *  Function    -  Tracker_Set_AGPSServer
 *
 *  Purpose     -  ����AGPSSERVER
 *
 *  Description -  AGPSSERVER,1,supl.google.com,7276,0#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2014-08-08, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_AGPSServer(void)
{
    S8 ip[4];
    U16 server_port = 0;
    U16 len;
    S16 Error;
    BOOL rpt = TRUE;
    if(received_data.part == 0)
    {
        if(tracker_agps_server.conecttype == 0)
        {
            sprintf((char *)sms_buf, "Currently in use AGPSServer:%d,%d.%d.%d.%d,%d,%d;", tracker_agps_server.conecttype, tracker_agps_server.server_ip[0], tracker_agps_server.server_ip[1], \
                    tracker_agps_server.server_ip[2], tracker_agps_server.server_ip[3], tracker_agps_server.server_port, tracker_agps_server.soc_type);
        }
        else
        {
            sprintf((char *)sms_buf, "Currently in use AGPSServer:%d,%s,%d,%d;", tracker_agps_server.conecttype, tracker_agps_server.url, tracker_agps_server.server_port, tracker_agps_server.soc_type);
        }
    }
    else if(received_data.part == 4)
    {
        memset(sms_buf, 0, sizeof(sms_buf));
        if(((received_data.param0[0] == '0') || (received_data.param0[0] == '1')) && (strlen((S8*)received_data.param0) == 1))
        {
            rpt = TRUE ;
        }
        else
        {
            rpt = FALSE;
        }
        if(received_data.param0[0] == '0')
        {
            if(sys_asciiIP2Hex(received_data.param1, ip) == FALSE)
            {
                rpt = FALSE;
            }
        }
        else
        {
            len = strlen((char *)received_data.param1);
            if(!len || len >= 100 || strstr((char*)received_data.param1, "http://"))
                rpt = FALSE;
        }

        if(check_right_data_of_param(received_data.param2) == TRUE)
        {
            server_port = system_string2U16(received_data.param2);
        }
        else
        {
            rpt = FALSE;
        }
        if(((received_data.param3[0] != '0') && (received_data.param3[0] != '1')) || (strlen((S8*)received_data.param3) != 1))
        {
            rpt = FALSE;
        }
        if(rpt == TRUE)
        {
            tracker_agps_server.conecttype = received_data.param0[0] - '0';
            tracker_agps_server.soc_type = received_data.param3[0] - '0';
            if(received_data.param0[0] == '1')
            {
                memset((void *)tracker_agps_server.url, 0, 100);
                memcpy((void *)&tracker_agps_server.url, (void *)&received_data.param1, len);
                tracker_agps_server.server_port = server_port;
                tracker_agps_server.IsSaveIP = 0;
            }
            else if((received_data.param0[0] == '0'))
            {
                memcpy(tracker_agps_server.server_ip, ip, 4);
                tracker_agps_server.server_port = server_port;
                tracker_agps_server.IsSaveIP = 0;
            }

            WriteRecord(NVRAM_EF_TRACKER_AGPS_SERVER_LID, 1, &tracker_agps_server, NVRAM_EF_TRACKER_AGPS_SERVER_SIZE, &Error);

            sprintf(sms_buf, "OK");

		#if defined (__PARAM_BACKUP__)
            StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
		#endif


        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
        }

    }
    else
    {
        sprintf(sms_buf, "ERROR:100");  //ָ������ֶζ�������ȷ
    }
}


/******************************************************************************
 *  Function    -  Tracker_RDA_AGPS_Conncet
 *
 *  Purpose     - AGPSCONNECT
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2014-08-08, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_RDA_AGPS_Conncet(void)
{
    LOGD(" %d ", received_data.part);
    if(received_data.part == 0)
    {
        sprintf(sms_buf, "OK");

        StartTimer(TRACKER_AGPS_SOCKET_CONNECT_TIMER , 5 * 1000,  Tracker_AGPS_Socket_TCP_Start);
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");
    }
}

#endif

#if defined(__AMS_BK_URL__)
/******************************************************************************
 *  Function    -  Tracker_Set_AMS
 *
 *  Purpose     - MSERVER(n)
 *
 *  Description -
 *				MSERVER(n),1,<����>,<�˿�>[,0]#   
 *				MSERVER(n),0,<IP>,<�˿�>[,0]#
 *					n=1-4�� n �����޸ĵڼ���AMS����
 *					������������0 TCP��Ĭ�ϣ���1 UDP
 *				MSERVER��n��#
 *					��ѯ��n������
 *				MSERVER#
 *					��ѯAMS��������
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2016-03-15, xiebiao  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_AMS(void)
{
	int i,j,num;
	int connect_type, soc_type;
	char tmp[DOMAIN_URL_MAX_LENGTH+10] = {0};
	S16 error;
	extern BOOL is_Ip_String(char *str);
	
	memset(sms_buf, 0, sizeof(sms_buf));
	
	if(strcmp((char *)received_data.main_str, "MSERVER") == 0)
	{
		if(0 == received_data.part)
		{
			for (i = 0,j = 0; i<DOMAIN_IP_MAX_COUNT; i++)
			{
				if(strlen(tracker_epo_server.ams_data[i].domain) > 0)
				{
					j++;
					sprintf(tmp, "[%d]:%d,%s,%d,%d", j, 
													tracker_epo_server.ams_data[i].conecttype, 
													tracker_epo_server.ams_data[i].domain, 
													tracker_epo_server.ams_data[i].port, 
													tracker_epo_server.ams_data[i].soc_type
													);
					strcat(sms_buf, tmp);
					strcat(sms_buf, "\r\n");
				}
			}
			return;
		}
		else
		{
			sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
			strcat(sms_buf, ";MSERVER");
		}
	}
	else if(strcmp((char *)received_data.main_str, "MSERVER1") == 0
			|| strcmp((char *)received_data.main_str, "MSERVER2") == 0
			|| strcmp((char *)received_data.main_str, "MSERVER3") == 0
			|| strcmp((char *)received_data.main_str, "MSERVER4") == 0
			)
	{
		char *pstr;
		char strbuf[10] = {0};

		pstr = received_data.main_str;
		pstr += 7;
		memcpy(strbuf, pstr, 1);

		LOGD("%s", strbuf);
		
		num = atoi(strbuf);
		
		if(0 == received_data.part)
		{
			sprintf(sms_buf, "MSERVER%d,", num);
			sprintf(tmp, "%d,%s,%d,%d", tracker_epo_server.ams_data[num-1].conecttype, 
										tracker_epo_server.ams_data[num-1].domain, 
										tracker_epo_server.ams_data[num-1].port,
										tracker_epo_server.ams_data[num-1].soc_type
										);
			strcat(sms_buf, tmp);
		}
		else if(4 == received_data.part)
		{
			connect_type = atoi(received_data.param0);
			if((connect_type != 0) && (connect_type != 1))
			{
				strcpy(sms_buf, "ERROR:101");//ָ�����ݳ�����Χ
				sprintf(tmp, ";MSERVER%d,1,www.baidu.com,8000,0", num);
				strcat(sms_buf, tmp);
				return;
			}

			soc_type = atoi(received_data.param3);
			if((soc_type != 0) && (soc_type != 1))
			{
				strcpy(sms_buf, "ERROR:101");//ָ�����ݳ�����Χ
				sprintf(tmp, ";MSERVER%d,1,www.baidu.com,8000,0", num);
				strcat(sms_buf, tmp);
				return;
			}

			if((connect_type == 0) && !is_Ip_String((char*)received_data.param1))
			{
				sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
				strcat(sms_buf, ";SERVER2,1,www.baidu.com,1111,0");
				return;
			}
			else if((connect_type == 1) && is_Ip_String((char*)received_data.param1))
			{
				sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
				strcat(sms_buf, ";SERVER2,0,111.111.111.162,1111,0");
				return;
			}

			if(atoi(received_data.param2) > 65535)
			{
				if(connect_type == 0)
				{
					sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
					strcat(sms_buf, ";SERVER2,1,www.baidu.com,1111,0");
					return;				
				}
				else
				{
					sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
					strcat(sms_buf, ";SERVER2,0,111.111.111.162,1111,0");
					return;				
				}
			}
			
			tracker_epo_server.ams_data[num-1].conecttype = connect_type;
			strcpy(tracker_epo_server.ams_data[num-1].domain, received_data.param1);
			tracker_epo_server.ams_data[num-1].port = atoi(received_data.param2);
			tracker_epo_server.ams_data[num-1].soc_type = soc_type;

			WriteRecord(NVRAM_EF_TRACKER_EPO_SERVER_LID, 1, (void *)&tracker_epo_server, NVRAM_EF_TRACKER_EPO_SERVER_SIZE, &error);

			sprintf(sms_buf, "OK");
		}
		else
		{
			sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
			strcat(sms_buf, ";MSERVER1,1,www.baidu.com,8000,0");
		}	
	}
}


/******************************************************************************
 *  Function    -  Tracker_Set_AMS_Current_IP
 *
 *  Purpose     - SERVER2
 *
 *  Description -	���õ�ǰAGPS��̨��ʵ���ӵ�IP��ַ
 *				
 *				SERVER2#
 *					��ѯ��ǰAGPS��̨���ӵ�IP
 *
 *				SERVER2,0,111.111.111.162,1111,0#
 *					���õ�ǰAGPS��̨���ӵ�IP
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2016-03-15, xiebiao  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_AMS_Current_IP(void)
{
	int connect_type, soc_type;
	char strtmp[DOMAIN_URL_MAX_LENGTH+10] = {0};
	S16 error;
	kal_uint8 server_ip[4] = {0};
	extern U8 g_ams_bk_idx;
	
	memset(sms_buf, 0, sizeof(sms_buf));
	
	if(0 == received_data.part)
	{
		strcpy(sms_buf, "SERVER2,");
		sprintf(strtmp, "%d,%d.%d.%d.%d,%d,%d", 0, 
										tracker_epo_server.server_ip[0],tracker_epo_server.server_ip[1],tracker_epo_server.server_ip[2],tracker_epo_server.server_ip[3], 
										tracker_epo_server.server_port,
										tracker_epo_server.soc_type
										);
		strcat(sms_buf, strtmp);
	}
	else if(4 == received_data.part)
	{
		connect_type = atoi(received_data.param0);
		if((connect_type!=0) && (connect_type!=1))
		{
			sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
			strcat(sms_buf, ";SERVER2,0,111.111.111.162,1111,0");
			return;
		}

		soc_type = atoi(received_data.param3);
		if((soc_type!=0) && (soc_type!=1))
		{
			sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
			strcat(sms_buf, ";SERVER2,0,111.111.111.162,1111,0");
			return;
		}
		
		if(atoi(received_data.param2) > 65535)
		{
			if(connect_type == 0)
			{
				sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
				strcat(sms_buf, ";SERVER2,0,111.111.111.162,1111,0");
				return;
			}
			else
			{
				sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
				strcat(sms_buf, ";SERVER2,1,www.baidu.com,1111,0");
				return;				
			}
		}
		

		
		if(!is_Ip_String((char*)received_data.param1))
		{
			if(connect_type == 0)
			{
				sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
				strcat(sms_buf, ";SERVER2,1,www.baidu.com,1111,0");
				return;
			}
			
			tracker_epo_server.IsSaveIP = 0;
			tracker_epo_server.conecttype = connect_type;
			strcpy(tracker_epo_server.url, received_data.param1);
		}
		else
		{
			U8 i;
			
			if(connect_type == 1)
			{
				sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
				strcat(sms_buf, ";SERVER2,0,111.111.111.162,1111,0");
				return;
			}

			if(sys_asciiIP2Hex((char*)received_data.param1, server_ip) == FALSE)
			{
				sprintf(sms_buf, "ERROR:101");//ָ�����ݲ���
				strcat(sms_buf, ";SERVER2,0,111.111.111.162,1111,0");
				return;
			}

			for(i=0;i<4;i++)
			{
				tracker_epo_server.server_ip[i] = server_ip[i];
			}
			
			tracker_epo_server.IsSaveIP = 1;
			tracker_epo_server.conecttype = connect_type;
		}


		tracker_epo_server.soc_type = soc_type;		
		tracker_epo_server.server_port = atoi(received_data.param2);
		WriteRecord(NVRAM_EF_TRACKER_EPO_SERVER_LID, 1, &tracker_epo_server, NVRAM_EF_TRACKER_EPO_SERVER_SIZE, &error); 

		sprintf(sms_buf, "OK");

		Tracker_EPO_Socket_TCP_Close();	
		g_ams_bk_idx = 0;
		epo_connect_times = 0;
		StartTimer(TRACKER_EPO_SOCKET_CONNECT_TIMER, 5 * 1000, Tracker_EPO_Socket_TCP_Start);
	}
	else
	{
		sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
		strcat(sms_buf, ";SERVER2");
	}
}
#endif

/******************************************************************************
 *  Function    -  Traceker_Set_Time_Zone
 *
 *  Purpose     -  ����ʱ��
 *
 *  Description -  GMT,ʱ����λ����ʱ������ʱ��#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-15, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Traceker_Set_Time_Zone(void)
{
#ifndef KJX_TEST
    U8  Time, Time_min = 0;
    U8 min_len = 0;
    BOOL rpt = TRUE;
    S16 Error;
    char temp1[200] = {0};

    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
        sprintf(temp1, "Currently Timezone(GMT):%c,%d,%d;", tracker_time_zone.zone, tracker_time_zone.time, tracker_time_zone.time_min);

        strcpy((char*)sms_buf, (char*)temp1);
    }
    else if((received_data.part == 2) || (received_data.part == 3))
    {
        memset(sms_buf, 0, sizeof(sms_buf));
        if(((received_data.param0[0] == 'E') || (received_data.param0[0] == 'W')) && (strlen((S8*)received_data.param0) == 1))
        {
            rpt = TRUE ;
        }
        else
        {
            rpt = FALSE;
        }
        if((Time = system_string2U16(received_data.param1)) != 0xffff)
        {
            if(Time >= 0 && Time <= 12)
            {
                ;
            }
            else
            {
                rpt = FALSE;
            }
        }
        else
        {
            rpt = FALSE;
        }
        if((received_data.part == 3))
        {
            if((Time_min = system_string2U16(received_data.param2)) != 0xffff)
            {
                if(Time_min == 0 || Time_min == 15 || Time_min == 30 || Time_min == 45)
                {
                    ;
                }
                else
                {
                    rpt = FALSE;
                }
            }
            else
            {
                rpt = FALSE;
            }
        }
        if(rpt)
        {
            tracker_time_zone.zone = received_data.param0[0];
            tracker_time_zone.time = Time;
            tracker_time_zone.time_min = Time_min;

#if defined(__TIMEZONE_ADAPT__)
            //�ֶ�����ʱ���󣬹ر�����Ӧ����
            tracker_time_zone.AutoSetGMT = 0;
#endif

            WriteRecord(NVRAM_EF_TRACKER_TIME_ZONE_LID, 1, (void *)&tracker_time_zone, NVRAM_EF_TRACKER_TIME_ZONE_SIZE, &Error);
		#if defined(__PARAM_BACKUP__)
            StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
		#endif

            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");     //���ݳ�����Χ
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ������ֶζ�������ȷ
    }
#endif
}

#if defined(__TIMEZONE_ADAPT__)
/******************************************************************************
 *  Function    -  Tracker_Set_GMT_Auto_Adaption
 *
 *  Purpose     -  ʱ������Ӧ���ܿ����͹ر�
 *
 *  Description -  ASETGMT,ON#   ASETGMT,OFF#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-12-19, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_GMT_Auto_Adaption(void)
{
    S16 Error;
    char temp[100] = {0};
    char data[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        memset(temp, 0, 100);
        memset(data, 0, 200);

        if(tracker_time_zone.AutoSetGMT == 0)
        {
            sprintf(temp, "ASETGMT:OFF; ");
        }
        else
        {
            sprintf(temp, "ASETGMT:ON; ");
        }
        strcpy(data, temp);

        memset(temp, 0, 100);
        sprintf(temp, "Currently Timezone(GMT):%c,%d,%d", tracker_time_zone.zone, tracker_time_zone.time, tracker_time_zone.time_min);
        strcat(data, temp);

        strcpy((char*)sms_buf, (char*)data);
    }
    else if(received_data.part == 1)
    {
        if((strcmp((char*)received_data.param0, "ON") == 0) || (strcmp((char*)received_data.param0, "OFF") == 0))
        {

            if(strcmp((char*)received_data.param0, "ON") == 0)
            {
                tracker_time_zone.AutoSetGMT = 1;
                //���»�ȡIMSI�ţ��Զ�����GMT
                StartTimer(TRACKER_GET_IMSI_TIMER, 10 * 1000, Tracker_get_IMSI_req);
            }
            else
            {
                tracker_time_zone.AutoSetGMT = 0;
            }
            WriteRecord(NVRAM_EF_TRACKER_TIME_ZONE_LID, 1, (void *)&tracker_time_zone, NVRAM_EF_TRACKER_TIME_ZONE_SIZE, &Error);
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");       //ָ������ֶζ�������ȷ
    }

    LOGD(" %d", tracker_time_zone.AutoSetGMT);
}
#endif


/******************************************************************************
 *  Function    -  Tracker_Server_Reconnect
 *
 *  Purpose     -  ��������SOC
 *
 *  Description -  RECONNECT#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2013-05-30, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Server_Reconnect(void)
{
#ifndef KJX_TEST
    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        sprintf(sms_buf, "OK");

        if(tracker_ctrl_data.GPRSAlwaysOn == 1 || tracker_ctrl_data.GPRSAlwaysOn == 2)
        {
            StartTimer(TRACKER_SOCKET_CONNECT_TIMER, 5 * 1000, Tracker_Socket_TCP_Close_ReConnect);
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
    }
#endif
}

/******************************************************************************
 *  Function    -  Traceker_Query_Server_Lock
 *
 *  Purpose     -
 *
 *  Description -  QLOCKIP,0#
 *                        LOCKIP,1#
 * modification history   ֻ��SOS��������ĺ���������
  * ----------------------------------------
 * v1.0  , 2013-02-04, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Traceker_Query_Server_Lock(void)
{
#ifndef KJX_TEST
    if((Command_State == SMS_Command_State) && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE)
            && (Delete_SmsPrefix_Confirm_SOSNum() == 0xFF) && (SuperCommandHead == FALSE))
    {
        sprintf(sms_buf, "ERROR:117");                     //����SOS����
        return;
    }

    if(received_data.part == 0)
    {
        if(tracker_server_param.lock)
        {
            sprintf(sms_buf, "LOCK:ON;");
        }
        else
        {
            sprintf(sms_buf, "LOCK:OFF;");
        }
    }
#endif
}


/******************************************************************************
 *  Function    -  Traceker_Set_Server_Lock
 *
 *  Purpose     -
 *
 *  Description -  LOCKIP#
 *
 * modification history   ֻ��SOS��������ĺ���������
  * ----------------------------------------
 * v1.0  , 2013-02-04, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Traceker_Set_Server_Lock(void)
{
#ifndef KJX_TEST
    S16 Error;

    memset(sms_buf, 0, sizeof(sms_buf));

    if((Command_State == SMS_Command_State) && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE)
            && (Delete_SmsPrefix_Confirm_SOSNum() == 0xFF) && (SuperCommandHead == FALSE))
    {
        sprintf(sms_buf, "ERROR:117");                     //����SOS����
        return;
    }

    if(received_data.part == 0)
    {
        tracker_server_param.lock = 1;
        WriteRecord(NVRAM_EF_TRACKER_SERVER_LID, 1, &tracker_server_param, NVRAM_EF_TRACKER_SERVER_SIZE, &Error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
		if((Command_State == AT_Command_State)
	 #if defined(__AT_USE_UART1__)
		||(Command_State == UART1_Command_State)
	 #endif
		)
        {
            strcat(sms_buf, ";LOCKIP# ");
        }
    }
#endif
}

/******************************************************************************
 *  Function    -  Traceker_Set_Server_UnLock
 *
 *  Purpose     -
 *
 *  Description -  UNLOCKIP#
 *
 * modification history   ֻ��SOS��������ĺ���������
  * ----------------------------------------
 * v1.0  , 2016-03-16, xiebiao  written
  * ----------------------------------------
 ******************************************************************************/
static void Traceker_Set_Server_UnLock(void)
{
#ifndef KJX_TEST

    memset(sms_buf, 0, sizeof(sms_buf));

    if((Command_State == SMS_Command_State) && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE)
            && (Delete_SmsPrefix_Confirm_SOSNum() == 0xFF) && (SuperCommandHead == FALSE))
    {
        sprintf(sms_buf, "ERROR:117");                     //����SOS����
        return;
    }

    if(received_data.part == 0)
    {
        tracker_server_param.lock = 0;
        WriteRecord(NVRAM_EF_TRACKER_SERVER_LID, 1, &tracker_server_param, NVRAM_EF_TRACKER_SERVER_SIZE, &Error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
		if((Command_State == AT_Command_State)
	 #if defined(__AT_USE_UART1__)
		||(Command_State == UART1_Command_State)
	 #endif
		)
        {
            strcat(sms_buf, ";UNLOCKIP# ");
        }
    }
#endif	
}

/******************************************************************************
 *  Function    -  Traceker_Set_GPRS_OnOff_Status
 *
 *  Purpose     -  ���ö�GPRS�ǿ����
 *
 *  Description -   GPRSON,1#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-04, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Traceker_Set_GPRS_OnOff_Status(void)
{
#ifndef KJX_TEST
    S16 error;
    U16 interval = 0;
    char temp1[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
        if(tracker_ctrl_data.GPRSAlwaysOn == 0)
        {
            sprintf((char *)temp1, "GPRS:OFF;");
        }
        else
        {
            sprintf((char *)temp1, "GPRS:ON;");
        }

        strcpy((char *)sms_buf, (char *)temp1);
        return ;
    }
    else if(received_data.part != 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ������ֶζ�������ȷ
        if(Command_State == SMS_Command_State)
        {
            strcat(sms_buf, ";GPRSON,1# ");
        }
        return;
    }
    interval = interval_Time_Manage(received_data.param0, 0, 1);

    if(interval == 0xffff)
    {
        sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
        if(Command_State == SMS_Command_State)
        {
            strcat(sms_buf, ";GPRSON,1# ");
        }
    }
    else
    {
        if(interval == 1) //GPRS ON
        {
            tracker_ctrl_data.GPRSAlwaysOn = 1;
        }
        else    //GPRS OFF
        {
            tracker_ctrl_data.GPRSAlwaysOn = 0;
        }

        if(tracker_ctrl_data.GPRSAlwaysOn == 0)
        {
            Tracker_Socket_TCP_Close();

#if defined(__SPECIAL_EPO_SOCKET__)
            Tracker_EPO_Socket_TCP_Close();
#elif defined(__SPECIAL_AGPS_SOCKET__)
            Tracker_AGPS_Socket_TCP_Close();
#endif
        }
        else
        {
            StartTimer(TRACKER_SOCKET_CONNECT_TIMER, 5 * 1000, Tracker_Socket_TCP_Close_ReConnect);
        }

        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
#endif
}




/******************************************************************************
 *  Function    -  Traceker_Set_GPRS_Link_Times
 *
 *  Purpose     -  ����GPRS ��������
 *
 *  Description - LINK,N#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-04, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Traceker_Set_GPRS_Link_Times(void)
{
#ifndef KJX_TEST
    S16 error;
    U16  interval = 0xffff;
    U8 interval_str[20];
    char temp1[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
        sprintf(temp1, "Reconnect Times:%d;", tracker_ctrl_data.gprs_relink_times);

        strcpy((char *)sms_buf, (char *)temp1);
        return ;
    }
    else if(received_data.part != 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }

    memset(interval_str, 0, 20);
    memcpy(interval_str, received_data.param0, 20);

    if(strlen((char*)interval_str) == 0)
    {
        interval = 0xffff;
    }
    else
    {
        interval = interval_Time_Manage(interval_str, 1 , 10);
        if(interval == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
            return ;
        }
    }

    if(interval != 0xffff)
    {
        tracker_ctrl_data.gprs_relink_times = interval;
    }
    WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
    sprintf(sms_buf, "OK");
#endif
}


/******************************************************************************
 *  Function    -  Traceker_Set_GPRS_Block_Alarm_Status
 *
 *  Purpose     -  ����GPRS ������������
 *
 *  Description - GPRSALM,ON#  GPRSALM,OFF#  GPRSALM#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-04, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Traceker_Set_GPRS_Block_Alarm_Status(void)
{
#ifndef KJX_TEST
    S16 error;
    char temp1[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
        if(tracker_ctrl_data.gprs_block_alarm == 0)
        {
            sprintf((char *)temp1, "GPRS block alarm:OFF;");
        }
        else
        {
            sprintf((char *)temp1, "GPRS block alarm:ON;");
        }
        strcpy((char*)sms_buf, (char*)temp1);
    }
    else if(received_data.part == 1)
    {
        if((strcmp((char*)received_data.param0, "ON") == 0) || (strcmp((char*)received_data.param0, "OFF") == 0))
        {

            if(strcmp((char*)received_data.param0, "ON") == 0)
            {
                tracker_ctrl_data.gprs_block_alarm = 1;
            }
            else
            {
                tracker_ctrl_data.gprs_block_alarm = 0;
            }
            WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");       //ָ������ֶζ�������ȷ
    }
#endif
}

/******************************************************************************
 *  Function    -  Tracker_Set_LowBat_Status
 *
 *  Purpose     - ���õ͵�����״̬
 *
 *  Description -  BATALM,ON[,M]#
 *                        BATALM,OFF#
 *                       BATALM#
 *                         M=0 , GPRS  M=1,GPRS+SMS
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_LowBat_Status(void)
{
#ifndef KJX_TEST
    S16 error;
    U16  interval = 0xffff;
    U8 interval_str[20];
    char temp[50];

    memset(sms_buf, 0, sizeof(sms_buf));

    LOGD(" %s", received_data.param0);

    if(received_data.part == 0)
    {
        if(tracker_low_battery.remindstate)
        {
            sprintf(sms_buf, "BATALM:ON,");
        }
        else
        {
            sprintf(sms_buf, "BATALM:OFF");
        }

        if(tracker_low_battery.alarmmode == 0)
        {
            strcat(sms_buf, "GPRS;");
        }
        else if(tracker_low_battery.alarmmode == 1)
        {
            strcat(sms_buf, "GPRS+SMS;");
        }

    }
    else if(strcmp("ON", ((char *)received_data.param0)) == 0)
    {
        if((received_data.part != 1) && (received_data.part != 2))
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        if(received_data.part == 1)
        {
            tracker_low_battery.remindstate = 1;
        }
        else if(received_data.part == 2)
        {
            memset(interval_str, 0, 20);
            memcpy(interval_str, received_data.param1, 20);

            interval = interval_Time_Manage(interval_str, 0, 1);
            if(interval == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return;
            }

            tracker_low_battery.remindstate = 1;
            tracker_low_battery.alarmmode =  interval;
        }

        WriteRecord(NVRAM_EF_TRACKER_LOW_BATTERY_LID, 1, &tracker_low_battery, NVRAM_EF_TRACKER_LOW_BATTERY_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else if(strcmp("OFF", ((char *)received_data.param0)) == 0)
    {
        if(received_data.part != 1)
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        tracker_low_battery.remindstate = 0;
        WriteRecord(NVRAM_EF_TRACKER_LOW_BATTERY_LID, 1, &tracker_low_battery, NVRAM_EF_TRACKER_LOW_BATTERY_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else if((strcmp("STATUS", ((char *)received_data.param0)) == 0) && (received_data.part != 0))
    {
        if(received_data.part != 1)
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        if(tracker_low_battery.remindstate == 1)
        {
            sprintf(sms_buf, "BATALM:ON,");
        }
        else
        {
            sprintf(sms_buf, "BATALM:OFF;");
        }

        memset(temp, 0, sizeof(temp));
        sprintf(temp, "lowbatsms:%d,pwroffsms:%d;", tracker_low_battery.sendlowbatterysms, tracker_low_battery.sendpwroffsms);
        strcat(sms_buf, "temp");

        if(tracker_low_battery.alarmmode == 0)
        {
            strcat(sms_buf, "GPRS;");
        }
        else if(tracker_low_battery.alarmmode == 1)
        {
            strcat(sms_buf, "GPRS+SMS;");
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
    }
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Set_Current_Language
 *
 *  Purpose     -  ���õ�ǰ����
 *
 *  Description -   LANG,1#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-10, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Current_Language(void)
{
#ifndef KJX_TEST
    U16  interval = 0xffff;
    S16 error;

    if(received_data.part == 0)
    {
        memset(sms_buf, 0, sizeof(sms_buf));
        sprintf(sms_buf, "Currently Language:%d;", CurrentLang);
    }
    else if(received_data.part == 1)
    {
        interval = interval_Time_Manage(received_data.param0, 0, 1);
        LOGD("%d,%d", received_data.param0[0], interval);

        if(interval == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
        }
        else
        {
            CurrentLang = interval;
            tracker_ctrl_data.language = CurrentLang;
            WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ������ֶζ�������ȷ
    }
#endif
}


/******************************************************************************
 *  Function    -  Tracker_SOS_Phone_Number
 *
 *  Purpose     -  SOS������Ӻ�ɾ��
 *
 *  Description -  SOS,A,num1,num2,num3#
 *                       SOS,D,1,2,3#
 *                       SOS,D,2#
 *                       SOS,D,num1#
 * modification history  SOS,A,15012584105#
 *** tracker_permit_level.commandpermit  =0
 * a.������������SOS���롣
 * b.���ĺ���ֻ��SOS����������á�
 * c.ֻ�����ĺ�����Զ��͵硣
 * **tracker_permit_level.commandpermit  =1
 *a.ֻ�����ĺ���(��SOS����)������SOS����
 *b.���ĺ���Ϊ�գ������������裬���ĺ�������
 *����ֻ�����ĺ�������޸ı���
 *c.ֻ�����ĺ�����Զ��͵�
 * ----------------------------------------
 * v1.0  , 2012-08-21, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_SOS_Phone_Number(void)
{
#ifdef __KJX_FUN__
	S16 error;
	int i = 0, j = 0;
	char num[SOS_NUM_LAN];
	S8 temp[160];
	U8 sos_sum = 0;
	U8 lenth = 0, NumberIndex = 0xFF;
	BOOL is_num = TRUE;
	char phone_num[SOS_NUM_MAX][SOS_NUM_LAN] = {0};
	U16 index[SOS_NUM_MAX];
	char temp1[200] = {0};

	memset(sms_buf, 0, sizeof(sms_buf));
	memset(temp, 0, sizeof(temp));
	memset(num, 0, SOS_NUM_LAN);

	if(received_data.part == 0)
	{
		memset(temp1, 0, 200);
		sprintf(temp1, "SOS number:%s,%s,%s;", g_kjx_nvram_struct.sosNum[0], g_kjx_nvram_struct.sosNum[1], g_kjx_nvram_struct.sosNum[2]);
		strcpy((char*)sms_buf, (char*)temp1);
	}
	else if((received_data.part > SOS_NUM_MAX + 1) || (received_data.part < 2))
	{
		sprintf(sms_buf, "ERROR:100");		  //ָ��Ȳ���ȷ
	}
	else
	{
		/*add sos number*/
		if(strlen((char*)received_data.param0) != 1)
		{
			sprintf(sms_buf, "ERROR:101");		  //ָ���������ȷ
		}
		else
		{
			if(received_data.param0[0] == 'A') //Ϊ��Ӻ���
			{
				strcpy(phone_num[0], (char*)received_data.param1);
				strcpy(phone_num[1], (char*)received_data.param2);
				strcpy(phone_num[2], (char*)received_data.param3);
				for(j = 0; j < SOS_NUM_MAX; j++)
				{
					lenth = strlen((char *)phone_num[j]);
					is_num = SetNumber_is_num((S8*)phone_num[j], lenth);
					if(lenth > SOS_NUM_LAN - 1 || is_num == FALSE)
					{
						sprintf(sms_buf, "ERROR:101");
						return;
					}

					memset(g_kjx_nvram_struct.sosNum[j], 0, SOS_NUM_LAN);
					memcpy(g_kjx_nvram_struct.sosNum[j], phone_num[j], lenth);
				}
			}
			/*delete sos number*/
			else if(received_data.param0[0] == 'D')
			{
				/*according to phonenumber delete sos number*/
				if(strlen((char*)received_data.param1) != 1)
				{
					is_num = SetNumber_is_num((S8*)received_data.param1, lenth);
					if((lenth > SOS_NUM_LAN - 1 || lenth < 0 || is_num == FALSE) || (received_data.part != 2))
					{
						sprintf(sms_buf, "ERROR:101");
						return;
					}

					NumberIndex = ConfirmNumberIsSOS((char*)received_data.param1);
					if((NumberIndex >= 1) && (NumberIndex <= SOS_NUM_MAX))
					{
						for(j = 0; j < SOS_NUM_MAX; j++)
						{
							if(strcmp((char*)g_kjx_nvram_struct.sosNum[j], (char*) received_data.param1) == 0)
							{
								//����2����ͬ�ĺ��룬��Ҫɾ��
								memset(g_kjx_nvram_struct.sosNum[j], 0, SOS_NUM_LAN);
							}
						}
					}
					else
					{
						sprintf(sms_buf, "ERROR:101");
						return;
					}
				}
				else
				{
					index[0] = system_string2U16(received_data.param1) - 1;
					index[1] = system_string2U16(received_data.param2) - 1;
					index[2] = system_string2U16(received_data.param3) - 1;
					for(j = 0; j < received_data.part - 1; j++)
					{
						if((index[j] < 0) || (index[j] >= SOS_NUM_MAX))
						{
							sprintf(sms_buf, "ERROR:101");
							return;
						}
						else
						{
							memset(g_kjx_nvram_struct.sosNum[index[j]], 0, SOS_NUM_LAN);
						}
					}
				}
			}
			else
			{
				sprintf(sms_buf, "ERROR:101");
				return;
			}
		}
		sprintf(sms_buf, "OK!");
		sos_sum = 0;
		for(i = 0; i < SOS_NUM_MAX; i++)
		{
			lenth = strlen((char *)g_kjx_nvram_struct.sosNum[i]);
			if(lenth > 0)
			{
				sos_sum++;
			}
		}

		if(sos_sum)
		{
			strcat((char *)sms_buf, "SOS1:");
			memset(temp1, 0, sizeof(temp1));
			if(strlen((char*)g_kjx_nvram_struct.sosNum[0]))
			{
				sprintf(temp1, "%s,", (S8 *)g_kjx_nvram_struct.sosNum[0]);
				strcat((char *)sms_buf, temp1);
			}
			else
			{
				strcat((char *)sms_buf, ",");
			}

			strcat((char *)sms_buf, "SOS2:");
			memset(temp1, 0, sizeof(temp1));

			if(strlen((char*)g_kjx_nvram_struct.sosNum[1]))
			{
				sprintf(temp1, "%s,", (S8 *)g_kjx_nvram_struct.sosNum[1]);
				strcat((char *)sms_buf, temp1);
			}
			else
			{
				strcat((char *)sms_buf, ",");
			}


			strcat((char *)sms_buf, "SOS3:");
			memset(temp1, 0, sizeof(temp1));

			if(strlen((char*)g_kjx_nvram_struct.sosNum[2]))
			{
				sprintf(temp1, "%s.", (S8 *)g_kjx_nvram_struct.sosNum[2]);
				strcat((char *)sms_buf, temp1);
			}
			else
			{
				strcat((char *)sms_buf, ",");
			}
		}
		else
		{
			strcat((char *)sms_buf, "SOS number is empty!");
		}

		kjx_nvram_write();
	}

#else
    S16 error;
    int i = 0, j = 0;
    char num[FAMILY_PHB_NUM_LEN_MIN];
    S8 temp[160];
    U8 lenth = 0, NumberIndex = 0xFF;
    BOOL is_num = TRUE;
    char phone_num[SOS_PHB_NUM_MAX][FAMILY_PHB_NUM_LEN_MIN] = {0};
    U16 index[SOS_PHB_NUM_MAX];
    char temp1[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));
    memset(temp, 0, sizeof(temp));
    memset(num, 0, FAMILY_PHB_NUM_LEN_MIN);

    //Ȩ�޷���1:  �κκ����������SOS����
    //Ȩ�޷���2:  ֻ�����ĺ���(��SOS)������SOS����
    if(tracker_permit_level.commandpermit == 1)
    {
        if((Command_State == SMS_Command_State)
                && (Delete_SmsPrefix_Confirm_SOSNum() == 0XFF)
                && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE)
                && (SuperCommandHead == FALSE))
        {
            sprintf(sms_buf, "ERROR:117");                     //����SOS��������ĺ���
            return ;
        }
    }

    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
        sprintf(temp1, "SOS number:%s,%s,%s;", (S8*)tracker_sos_phb.ph_num[0], (S8*)tracker_sos_phb.ph_num[1], (S8*)tracker_sos_phb.ph_num[2]);
        strcpy((char*)sms_buf, (char*)temp1);
    }
    else if((received_data.part > SOS_PHB_NUM_MAX + 1) || (received_data.part < 2))
    {
        sprintf(sms_buf, "ERROR:100");        //ָ��Ȳ���ȷ
        if(Command_State == ONLine_Command_State)
        {
            Tracker_Online_State = TRACKER_ONLINE_SOS_FAIL;
            gprs_send_type = GPRS_ONLINE_RESULT_INFO;
            Tracker_Socket_Send_Current_Data();
        }
    }
    else
    {
        /*add sos number*/
        if(strlen((char*)received_data.param0) != 1)
        {
            sprintf(sms_buf, "ERROR:101");        //ָ���������ȷ
            if(Command_State == ONLine_Command_State)
            {
                Tracker_Online_State = TRACKER_ONLINE_SOS_FAIL;
                gprs_send_type = GPRS_ONLINE_RESULT_INFO;
                Tracker_Socket_Send_Current_Data();
            }
        }
        else
        {
            if(received_data.param0[0] == 'A') //Ϊ��Ӻ���
            {
                strcpy(phone_num[0], (char*)received_data.param1);
                strcpy(phone_num[1], (char*)received_data.param2);
                strcpy(phone_num[2], (char*)received_data.param3);
                for(j = 0; j < SOS_PHB_NUM_MAX; j++)
                {
                    lenth = strlen((char *)phone_num[j]);
                    is_num = SetNumber_is_num((S8*)phone_num[j], lenth);
                    if(lenth == 0)
                    {
                        //�������ӺͶ���һ������ȫ������
                        continue;
                    }
                    if(lenth > FAMILY_PHB_NUM_LEN_MIN - 1 || lenth < 3 || is_num == FALSE)
                    {
                        sprintf(sms_buf, "ERROR:101");
                        if(Command_State == ONLine_Command_State)
                        {
                            Tracker_Online_State = TRACKER_ONLINE_SOS_FAIL;
                            gprs_send_type = GPRS_ONLINE_RESULT_INFO;
                            Tracker_Socket_Send_Current_Data();
                        }
                        return;
                    }

                    memset(tracker_sos_phb.ph_num[j], 0, FAMILY_PHB_NUM_LEN_MIN);
                    memcpy(tracker_sos_phb.ph_num[j], phone_num[j], lenth);

                }
                if(Command_State == ONLine_Command_State)
                {
                    Tracker_Online_State = TRACKER_ONLINE_SOS_SUCCESS;
                    gprs_send_type = GPRS_ONLINE_RESULT_INFO;
                    Tracker_Socket_Send_Current_Data();
                }
            }
            /*delete sos number*/
            else  if(received_data.param0[0] == 'D')
            {
                /*according to phonenumber delete sos number*/
                if(strlen((char*)received_data.param1) != 1)
                {
                    is_num = SetNumber_is_num((S8*)received_data.param1, lenth);
                    if((lenth > FAMILY_PHB_NUM_LEN_MIN - 1 || lenth < 0 || is_num == FALSE) || (received_data.part != 2))
                    {
                        sprintf(sms_buf, "ERROR:101");
                        if(Command_State == ONLine_Command_State)
                        {
                            Tracker_Online_State = TRACKER_ONLINE_SOS_FAIL;
                            gprs_send_type = GPRS_ONLINE_RESULT_INFO;
                            Tracker_Socket_Send_Current_Data();
                        }
                        return;
                    }
				#if defined(__SOS_CALL__)
                    NumberIndex = ConfirmNumberIsSOS((char*)received_data.param1);
				#endif
                    if((NumberIndex >= 1) && (NumberIndex <= SOS_PHB_NUM_MAX))
                    {
                        for(j = 0; j < SOS_PHB_NUM_MAX; j++)
                        {
                            if(strcmp((char*)tracker_sos_phb.ph_num[j], (char*) received_data.param1) == 0)
                            {
                                //����2����ͬ�ĺ��룬��Ҫɾ��
                                memset(tracker_sos_phb.ph_num[j], 0, FAMILY_PHB_NUM_LEN_MIN);
                            }
                        }
                    }
                    else
                    {
                        sprintf(sms_buf, "ERROR:101");
                        return;
                    }
                }
                else
                {
                    index[0]  = system_string2U16(received_data.param1) - 1;
                    index[1] = system_string2U16(received_data.param2) - 1;
                    index[2] = system_string2U16(received_data.param3) - 1;
                    for(j = 0; j < received_data.part - 1; j++)
                    {
                        if((index[j] < 0) || (index[j] >= SOS_PHB_NUM_MAX))
                        {
                            sprintf(sms_buf, "ERROR:101");
                            if(Command_State == ONLine_Command_State)
                            {
                                Tracker_Online_State = TRACKER_ONLINE_SOS_FAIL;
                                gprs_send_type = GPRS_ONLINE_RESULT_INFO;
                                Tracker_Socket_Send_Current_Data();

                            }
                            return;
                        }
                        else
                        {
                            memset(tracker_sos_phb.ph_num[index[j]], 0, FAMILY_PHB_NUM_LEN_MIN);
                        }
                    }
                }
                if(Command_State == ONLine_Command_State)
                {
                    Tracker_Online_State = TRACKER_ONLINE_SOS_SUCCESS;
                    gprs_send_type = GPRS_ONLINE_RESULT_INFO;
                    Tracker_Socket_Send_Current_Data();
                }
            }
            else
            {
                sprintf(sms_buf, "ERROR:101");
                return;
            }
        }
        sprintf(sms_buf, "OK!");
        tracker_sos_phb.phb_sum = 0;
        for(i = 0; i < SOS_PHB_NUM_MAX; i++)
        {
            lenth = strlen((char *)tracker_sos_phb.ph_num[i]);
            if(lenth > 0)
            {
                tracker_sos_phb.phb_sum++;
            }
        }

        /*�޸ĺ�ͬ����ǰ�������̨*/
        //StartTimer(GPRS_SEND_SEESOS_TIMER, 5 * 1000, Tracker_Send_See_SOS_Data);

        if(tracker_sos_phb.phb_sum)
        {
            strcat((char *)sms_buf, "SOS1:");
            memset(temp1, 0, sizeof(temp1));
            if(strlen((char*)tracker_sos_phb.ph_num[0]))
            {
                sprintf(temp1, "%s,", (S8 *)tracker_sos_phb.ph_num[0]);
                strcat((char *)sms_buf, temp1);
            }
            else
            {
                strcat((char *)sms_buf, ",");
            }

            strcat((char *)sms_buf, "SOS2:");
            memset(temp1, 0, sizeof(temp1));

            if(strlen((char*)tracker_sos_phb.ph_num[1]))
            {
                sprintf(temp1, "%s,", (S8 *)tracker_sos_phb.ph_num[1]);
                strcat((char *)sms_buf, temp1);
            }
            else
            {
                strcat((char *)sms_buf, ",");
            }


            strcat((char *)sms_buf, "SOS3:");
            memset(temp1, 0, sizeof(temp1));

            if(strlen((char*)tracker_sos_phb.ph_num[2]))
            {
                sprintf(temp1, "%s.", (S8 *)tracker_sos_phb.ph_num[2]);
                strcat((char *)sms_buf, temp1);
            }
            else
            {
                strcat((char *)sms_buf, ",");
            }


            //��������������Ϣ
            if((GPRSBlockSMSSend == 1) && (tracker_ctrl_data.gprs_block_sms == 0))
            {
                StartTimer(TRACKER_SEND_GPRS_BLOCKSMS_TIMER, 3 * 1000, Tracker_GPRS_Block_Alarm_Sms);
            }
        }
        else
        {
            strcat((char *)sms_buf, "SOS number is empty!");
        }

        WriteRecord(NVRAM_EF_TRACKER_SOS_PHB_LID, 1, &tracker_sos_phb, NVRAM_EF_TRACKER_SOS_PHB_SIZE, &error);

	#if defined(__PARAM_BACKUP__)
        StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
	#endif

    }

    LOGD(" %d,%s,%s,%s", tracker_sos_phb.phb_sum, tracker_sos_phb.ph_num[0], tracker_sos_phb.ph_num[1], tracker_sos_phb.ph_num[2]);
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Online_See_SOS_PhbNum
 *
 *  Purpose     -  ���߲�ѯSOS����
 *
 *  Description -  SEESOS#
 *
 * modification history
 *   �ظ�SOS,����1,����1,����2,����3#
 * ----------------------------------------
 * v1.0  , 2012-09-18, guojie  written
  * ----------------------------------------
 ******************************************************************************/
void Tracker_Online_See_SOS_PhbNum(void)
{
#ifndef KJX_TEST
    if(Command_State == ONLine_Command_State)
    {
        is_online_see_cmd = TRUE;
        StartTimer(GPRS_SEND_SEESOS_TIMER,  1000, Tracker_Send_See_SOS_Data);
    }
#endif
}


/*****************************************************************************
*  Function    -  Tracker_Send_See_System_Param
*
*  Purpose     -  �����ն˲���
*
*  Description -
*
* modification history
* ----------------------------------------
* v1.0  , 2012-06-06,  guojie  written
* ----------------------------------------
*****************************************************************************/
void Tracker_Send_See_System_Param(void)
{
#ifndef KJX_TEST
    if((tracker_ctrl_data.GPRSAlwaysOn == 1) && (tracker_login_info.Success == TRUE))
    {
        gprs_send_type = GPRS_ONLINE_SEEPARAM_INFO;
        Tracker_Socket_Send_AllType_GPRS_Data();
    }
#endif
}

/******************************************************************************
 *  Function    -  Tracker_Set_Command_Permit
 *
 *  Purpose     -  ָ��Ȩ�޵ȼ�����
 *
 *  Description - PERMIT,N#    N=0,
 *                                               A.������������SOS����
 *                                               B.���ĺ���ֻ��SOS�����������
 *                                               C.ֻ�����ĺ�����Զ��͵�
 *
 *  Description - PERMIT,N#    N=1,
 * A.���ĺ���Ϊ��ʱ�������������ã����ĺ��������ã�ֻ�����ĺ���������䱾��
 * B.ֻ�����ĺ���(��SOS����)������SOS����
 * C.ֻ�����ĺ�����Զ��͵�
 *
 * PERMIT#       ��ѯ
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Command_Permit(void)
{
#ifndef KJX_TEST
    S16 error;
    U16  interval = 0xffff;
    U8 interval_str[20];
    char temp[50] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        memset(temp, 0, 50);
        sprintf(temp, "PERMIT:%d;", tracker_permit_level.commandpermit);
        strcpy((char*)sms_buf, (char*)temp);
    }
    else if(received_data.part == 1)
    {
        //���������Ը���Ȩ��
        //��PERMIT,1# ʱ��SOSΪ�գ�CENTERΪ�գ���ʱCENTER���ú���ʱд��һ������ĺ���
        //����ô�������޸�SOS�����CENTER������
        //ֻ�ָܻ��������û򳬼�����ָ��ָ�
        if((Command_State == SMS_Command_State)
                && (Delete_SmsPrefix_Confirm_SOSNum() == 0XFF)
                && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE)
                && (SuperCommandHead == FALSE))
        {
            sprintf(sms_buf, "ERROR:117");                     //����SOS��������ĺ���
            return ;
        }

        memset(interval_str, 0, 20);
        memcpy(interval_str, received_data.param0, 20);

        if(strlen((char*)interval_str) == 0)
        {
            interval = 0xffff;
        }
        else
        {
            interval = interval_Time_Manage(interval_str, 0, 1);


            if(interval == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return;
            }
        }

        if(interval != 0xffff)
        {
            tracker_permit_level.commandpermit =  interval;
        }

        WriteRecord(NVRAM_EF_TRACKER_PERMIT_LEVEL_LID, 1, &tracker_permit_level, NVRAM_EF_TRACKER_PERMIT_LEVEL_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
    }
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Set_SOS_Permit
 *
 *  Purpose     -  ����SOS����ȼ�
 *
 *  Description - SOSPERMIT,X[,Y]#    X=0,��������ѯ�����ò���
 *                                                       X=1, ��SOS������Բ�ѯ�����ò���
 *                                                       Y=0,��������һ��SOS����
 *                                                       Y=1,����������SOS����
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_SOS_Permit(void)
{
#ifndef KJX_TEST
    S16 error;
    U16  interval[2] = {0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[2][20];
    char temp[50] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        memset(temp, 0, 50);
        sprintf(temp, "SOSPERMIT:%d,%d;", tracker_permit_level.sospermit, tracker_permit_level.alarmmode);
        strcpy((char*)sms_buf, (char*)temp);
    }
    else if(received_data.part <= 2)
    {
        if((Command_State == SMS_Command_State)
                && (Delete_SmsPrefix_Confirm_SOSNum() == 0XFF)
                && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE)
                && (SuperCommandHead == FALSE))
        {
            sprintf(sms_buf, "ERROR:117");                     //����SOS��������ĺ���
            return ;
        }
        memset(interval_str, 0, 40);
        memcpy(interval_str[0], received_data.param0, 20);
        memcpy(interval_str[1], received_data.param1, 20);

        for(i = 0; i < received_data.part ; i++)
        {
            if(strlen((char*)interval_str[i]) == 0)
            {
                interval[i] = 0xffff;
                continue ;
            }

            if(i == 0)
            {
                interval[i] = interval_Time_Manage(interval_str[i], 0, 1);
            }
            else if(i == 1)
            {
                interval[i] = interval_Time_Manage(interval_str[i], 0, 1);
            }


            if(interval[i] == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return;
            }
        }

        if(interval[0] != 0xffff)
        {
            tracker_permit_level.sospermit = interval[0];
        }

        if(interval[1] != 0xffff)
        {
            tracker_permit_level.alarmmode = interval[1];
        }

        WriteRecord(NVRAM_EF_TRACKER_PERMIT_LEVEL_LID, 1, &tracker_permit_level, NVRAM_EF_TRACKER_PERMIT_LEVEL_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
    }
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Set_Monitor_Permit
 *
 *  Purpose     -  ���ü�������ȼ�
 *
 *  Description - MONPERMIT,N#    N=0,��ֹ����,N=1,���������ĺ������
 *                                                  N=2,SOS+CENTER     N=3, ������붼���Լ���
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Monitor_Permit(void)
{
#ifndef KJX_TEST
    S16 error;
    U16  interval = 0xffff;
    U8 interval_str[20];
    char temp[50] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        memset(temp, 0, 50);
        sprintf(temp, "MONITORPERMIT:%d;", tracker_permit_level.monitorpermit);
        strcpy((char*)sms_buf, (char*)temp);
    }
    else if(received_data.part == 1)
    {
        if((Command_State == SMS_Command_State)
                && (Delete_SmsPrefix_Confirm_SOSNum() == 0XFF)
                && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE)
                && (SuperCommandHead == FALSE))
        {
            sprintf(sms_buf, "ERROR:117");                     //����SOS��������ĺ���
            return ;
        }
        memset(interval_str, 0, 20);
        memcpy(interval_str, received_data.param0, 20);

        if(strlen((char*)interval_str) == 0)
        {
            interval = 0xffff;
        }
        else
        {
            interval = interval_Time_Manage(interval_str, 0, 3);


            if(interval == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return;
            }
        }

        if(interval != 0xffff)
        {
            tracker_permit_level.monitorpermit =  interval;
        }

        WriteRecord(NVRAM_EF_TRACKER_PERMIT_LEVEL_LID, 1, &tracker_permit_level, NVRAM_EF_TRACKER_PERMIT_LEVEL_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
    }
#endif
}

/******************************************************************************
 *  Function    -  Tracker_Get_Software_Version
 *
 *  Purpose     -  ��ȡ�汾��
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-15, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Get_Software_Version(void)
{
    version_struct ver_struct;
    U8 temp[300], temp2[50];

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");//ָ������ֶζ�������ȷ
        return;
    }

    memset(temp, 0, 300);
    memset(temp2, 0, 50);
    INT_VersionNumbers(&ver_struct);

    sprintf((char *)temp, "[VERSION]:");
    strcat((char *)temp, ver_struct.mcu_sw);
    sprintf((char *)temp2, "\r\n[BRANCH]:");
    strcat((char *)temp, (char *)temp2);
    strcat((char *)temp, ver_struct.mcu_sw_branch);
    sprintf((char *)temp2, "\r\n[BUILD]:");
    strcat((char *)temp, (char *)temp2);
    strcat((char *)temp, (char*)build_date_time());
    strcpy(sms_buf, (char*) temp);
}

/******************************************************************************
 *  Function    -  Traceker_Phb_Imei_Param_See
 *
 *  Purpose     -  �鿴��������
 *
 *  Description -
 *
 * modification history
 * ��ѯָ��: PARAM#
 * �ظ�: IMEI:868120103643505;TIMER:20,20; SENDS:5; SOS:13730454825,,; Center Number:; Sensoralm:10,3,1,180; Defense time:10; TimeZone:E,8,0;
 * ----------------------------------------
 * v1.0  , 2012-08-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Traceker_Phb_Imei_Param_See(void)
{
#ifndef KJX_TEST
    S8 temp[200], data[400];
    int i = 0;

    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }
    memset(data, 0, sizeof(data));
    memset(temp, 0, sizeof(temp));
    memset(sms_buf, 0, sizeof(sms_buf));


    sprintf(temp, "IMEI:%s;", IMEIBuffer);
    strcpy(data, temp);
    memset(temp, 0, sizeof(temp));
    if(tracker_ctrl_data.reportstrategy == 1)
    {
        strcat(data, "TIMER:");
	#if defined(__ACC_DETECT__)
		sprintf((char *)temp, "%d,%d;", tracker_ctrl_data.gps_accon_interval / 1000, tracker_ctrl_data.gps_accoff_interval / 1000);
	#else	
		sprintf((char *)temp, "%d,%d;", tracker_ctrl_data.lbs_time_interval / (60*1000), tracker_ctrl_data.gps_time_interval / 1000);
	#endif
        strcat(data, temp);
        memset(temp, 0, sizeof(temp));
    }
    else if(tracker_ctrl_data.reportstrategy == 2)
    {
        strcat(data, "Distance:");
        sprintf((char *)temp, "%d;", tracker_ctrl_data.distance);
        strcat(data, temp);
        memset(temp, 0, sizeof(temp));
    }

#if defined(__BOSCH_BMA250E__)
    sprintf(temp, "SENDS:%d;", tracker_sensor_time.gpsworktime / 60 / 1000);
    strcat(data, temp);
    memset(temp, 0, sizeof(temp));
#endif/*__BOSCH_BMA250E__*/

    strcat(data, "SOS:");
    for(i = 0; i < SOS_PHB_NUM_MAX; i++)
    {
        //RDA �пո��������
        if(strlen((char *)tracker_sos_phb.ph_num[i]))
        {
            sprintf(temp, "%s", (S8 *)tracker_sos_phb.ph_num[i]);
        }
        if((i + 1) < SOS_PHB_NUM_MAX)
        {
            strcat(temp, ",");
        }
        else
        {
            strcat(temp, ";");
        }
        strcat(data, temp);
        memset(temp, 0, sizeof(temp));
    }

    sprintf(temp, "CENTER:%s;", tracker_sos_phb.center_num);
    strcat(data, temp);
    memset(temp, 0, sizeof(temp));

#if defined(__BOSCH_BMA250E__)
    sprintf(temp, "Sensorset:%d,%d,%d,%d;", tracker_sensor_time.detecttime / 1000, tracker_sensor_time.activegpsnum, \
            tracker_sensor_time.detectnum, tracker_sensor_time.detect_interval / 1000);
    strcat(data, temp);
    memset(temp, 0, sizeof(temp));

    //sprintf(temp, "Defense time:%d;", tracker_sensor_time.defence_start_time / 60000);
    //strcat(data, temp);
    //memset(temp, 0, sizeof(temp));
#endif

    sprintf(temp, "TimeZone:%c,%d,%d;", tracker_time_zone.zone, tracker_time_zone.time, tracker_time_zone.time_min);
    strcat(data, temp);
    memset(temp, 0, sizeof(temp));

    strcpy((char *)sms_buf, (char *)data);
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Apn_Server_Time_Interval_See
 *
 *  Purpose     -  �鿴�ն˾������
 *
 *  Description -
 *
 * modification history
 * ��ѯָ��: SCXSZ#
 * �ظ�: CMNET,,;2000;5;E8,0;1,hgt06.szdatasource.com,8841,0;13730454825,,;;10;10;1;
 * ʵ��: cmnet,,;E8,0;1,gt200.szdatasource.com,8841,0;10;3;5;13434431506,,;;10;10;1;
 * ----------------------------------------
 * v1.0  , 2012-06-06, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Apn_Server_Time_Interval_See(void)
{
#ifndef KJX_TEST
    char temp[100];
    char i;

    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }
    memset(sms_buf, 0, sizeof(sms_buf));
    memset(temp, 0, sizeof(temp));

    if(mmi_bootup_is_sim_valid())
    {
        sprintf((char *)temp, "%s,%s,%s;", (S8*)tracker_apn_param.apn, (S8*)tracker_apn_param.user_name, (S8*)tracker_apn_param.password);
        strcat(sms_buf, temp);
        memset(temp, 0, sizeof(temp));
    }
    else
    {
        sprintf((char *)temp, ",,;");
        strcat(sms_buf, temp);
        memset(temp, 0, sizeof(temp));
    }

    sprintf((char *)temp, "%c%d,%d;", tracker_time_zone.zone, tracker_time_zone.time, tracker_time_zone.time_min);
    strcat(sms_buf, temp);
    memset(temp, 0, sizeof(temp));

    if(tracker_server_param.conecttype == 0)
    {
        sprintf((char *)temp, "%d,%d.%d.%d.%d,%d,%d;", tracker_server_param.conecttype, tracker_server_param.server_ip[0], tracker_server_param.server_ip[1], \
                tracker_server_param.server_ip[2], tracker_server_param.server_ip[3], tracker_server_param.server_port, tracker_server_param.soc_type);
    }
    else
    {
        sprintf((char *)temp, "%d,%s,%d,%d;", tracker_server_param.conecttype, tracker_server_param.url, tracker_server_param.server_port, tracker_server_param.soc_type);
    }
    strcat(sms_buf, temp);
    memset(temp, 0, sizeof(temp));

    //�ϴ�����
    if(tracker_ctrl_data.reportstrategy == 1)
    {
        sprintf((char *)temp, "%d;", tracker_ctrl_data.gps_time_interval / 1000);
    }
    else if(tracker_ctrl_data.reportstrategy == 2)
    {
        sprintf((char *)temp, "%d;", tracker_ctrl_data.distance);
    }
    else if(tracker_ctrl_data.reportstrategy == 3)
    {
        sprintf((char *)temp, "%d,%d;", tracker_ctrl_data.gps_time_interval / 1000, tracker_ctrl_data.distance);
    }
    else
    {
        sprintf((char *)temp, "%d,%d;", tracker_ctrl_data.inflection_interval, tracker_ctrl_data.inflection_detect_time / 1000);
    }
    strcat(sms_buf, temp);
    memset(temp, 0, sizeof(temp));


    //״̬���ϴ�ʱ��
    sprintf(temp, "%d;", tracker_ctrl_data.status_time_interval / 60 / 1000);
    strcat(sms_buf, temp);
    memset(temp, 0, sizeof(temp));


#if defined(__BOSCH_BMA250E__)
    sprintf(temp, "%d;", tracker_sensor_time.gpsworktime / 60 / 1000);
    strcat(sms_buf, temp);
    memset(temp, 0, sizeof(temp));
#endif

    for(i = 0; i < SOS_PHB_NUM_MAX; i++)
    {
        //RDA �пո��������
        if(strlen((char *)tracker_sos_phb.ph_num[i]))
        {
            sprintf(temp, "%s", (S8 *)tracker_sos_phb.ph_num[i]);
        }
        if((i + 1) < SOS_PHB_NUM_MAX)
        {
            strcat(temp, ",");
        }
        else
        {
            strcat(temp, ";");
        }
        strcat(sms_buf, temp);
        memset(temp, 0, sizeof(temp));
    }

    if(strlen((char *)tracker_sos_phb.center_num))
    {
        sprintf(temp, "%s;", tracker_sos_phb.center_num);
    }
    else
    {
        sprintf(temp, ";");
    }
    strcat(sms_buf, temp);
    memset(temp, 0, sizeof(temp));

#if defined(__BOSCH_BMA250E__)
    //ACC OFF �����ʱ��
    //sprintf(temp, "%d;", tracker_sensor_time.defence_start_time / 60000);
    //strcat(sms_buf, temp);
    //memset(temp, 0, sizeof(temp));
#endif

#if defined(__GPS_ON_MTK__)
    //GPS��ʱ����ʱ��
    sprintf(temp, "%d;", tracker_delay_active_time.time / 1000);
    strcat(sms_buf, temp);
    memset(temp, 0, sizeof(temp));
#endif

    //Ĭ������
    sprintf(temp, "%d;", CurrentLang);
    strcat(sms_buf, temp);
    memset(temp, 0, sizeof(temp));

    LOGD(" %s", sms_buf);
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Gprs_Param_See
 *
 *  Purpose     -  �鿴gprs���õĲ���
 *
 *  Description -  GPRSSET#
 *  Return: GPRS:ON; APN:CMNET,,; Server:1,hgt06.szdatasource.com,8841,0; URL:http://maps.google.com/maps?q=;
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-06-06 guojie written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Gprs_Param_See(void)
{
#ifndef KJX_TEST
    S8 temp[300], data[300];
    int i = 0;
    U32 time = 0;
    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }
    memset(data, 0, sizeof(data));

    memset(temp, 0, sizeof(temp));
    memset(sms_buf, 0, sizeof(sms_buf));

    if(tracker_ctrl_data.GPRSAlwaysOn == 0)
    {
        sprintf((char *)temp, "GPRS:OFF;");
    }
    else
    {
        sprintf((char *)temp, "GPRS:ON;");
    }
    strcpy(data, temp);

    if(mmi_bootup_is_sim_valid())
    {
        memset(temp, 0, 300);
        sprintf((char *)temp, "APN:%s,%s,%s;", (S8*)tracker_apn_param.apn, (S8*)tracker_apn_param.user_name, (S8*)tracker_apn_param.password);
        strcat(data, temp);
        memset(temp, 0, 300);
    }
    else
    {
        strcat(data, "APN:,,;");
        memset(temp, 0, 300);
    }

    strcat(data, "Server:");
    if(tracker_server_param.conecttype == 0)
    {
        sprintf((char *)temp, "%d,%d.%d.%d.%d,%d,%d;", tracker_server_param.conecttype, tracker_server_param.server_ip[0], tracker_server_param.server_ip[1], \
                tracker_server_param.server_ip[2], tracker_server_param.server_ip[3], tracker_server_param.server_port, tracker_server_param.soc_type);
    }
    else
    {
        sprintf((char *)temp, "%d,%s,%d,%d;", tracker_server_param.conecttype, tracker_server_param.url, tracker_server_param.server_port, tracker_server_param.soc_type);
    }
    strcat(data, temp);

#if defined (__GPS_ON_MTK__)
    memset(temp, 0, 300);
    sprintf((char *)temp, "URL:%s;", tracker_ctrl_data.URL_Address);
    strcat(data, temp);
#endif

    strcpy((char *)sms_buf, (char *)data);
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Get_Current_Status
 *
 *  Purpose     -  ��ȡ�ն˵�ǰ״̬
 *
 *  Description -  STATUS#
 *
 *  Return - Battery:3.41V,Battery too low! Warning; GPRS:Link Up; GSM Signal Level:Strong;
 *               GPS:Successful positioning, SVS Used in fix:10(11), GPS Signal Level:32,31,32,31,28,29,29,36,32,33; ACC:OFF; Defense:OFF
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-15, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Get_Current_Status(void)
{
    char temp[300]={0};
    U8 Battery_State;
    U8 GSM_State;
    U8 GPS_State;
    U8 i = 0;
    double RESULT;
    U8 batter_precent = 0;
    U32 battery_voltage = 0;

    memset(sms_buf, 0, sizeof(sms_buf));

#if defined(__CHARGER_CHECK_EINT__)||defined(__CHARGER_CHECK_GPIO__)
    if(tracker_exterpower_state == EXTERPOWER_OFF)
#else
    if(srv_charbat_is_charging())	
#endif
    {
		sprintf((char *)temp, "Battery: Charging,");
		strcpy(sms_buf, temp);
    }
    else
    {
		sprintf((char *)temp, "Battery: Only battery supply,");
		strcpy(sms_buf, temp);
    }

	bmt_get_adc_channel_voltage(DCL_VBAT_ADC_CHANNEL, &battery_voltage);
	Battery_State = srv_charbat_get_battery_level();

    //��ص���
    memset(temp, 0, sizeof(temp));
	sprintf(temp, "Voltage:%d.%02dV,", battery_voltage/1000000, (battery_voltage-(battery_voltage/1000000)*1000000)/10000);
	strcat(sms_buf,temp);

	if(Battery_State > 2)
	{
		strcat(sms_buf, "NORMAL;\r\n");
	}
	else if(Battery_State == 2)
	{
		strcat(sms_buf, "LOW;\r\n");
	}
	else
	{
		strcat(sms_buf, "Battery too low!Warning!;\r\n");
	}

    //GPRS����״̬
    memset(temp, 0, sizeof(temp));
	if(kjx_gprs_is_connect())
    {
        sprintf((char *)temp, "GPRS: Link Up;\r\n");
    }
    else
    {
        sprintf((char *)temp, "GPRS: Link Down;\r\n");
    }
    strcat(sms_buf, temp);

    //GSM
    memset(temp, 0, sizeof(temp));
    GSM_State = srv_nw_info_get_signal_strength_in_percentage(MMI_SIM1) / 25;

    LOGD("Tracker_Get_Current_Status ^^ %d ", GSM_State);

    switch(GSM_State)
    {
    case 1:
        sprintf((char *)temp, "GSM: Signal Level:low;\r\n");
        break;

    case 2:
    case 3:
        sprintf((char *)temp, "GSM: Signal Level:middle;\r\n");
        break;

    case 4:
        sprintf((char *)temp, "GSM: Signal Level:strong;\r\n");
        break;
    default:
        break;
    }
    strcat(sms_buf, temp);

#if defined( __KJX_FUN_GPS__ )
	switch(g_kjx_gps_category)
	{
	case GPS_ZKW_MODE:		//�п�΢GPSģ��
		strcat(sms_buf, "GPS:(ZKW)");
		break;
	case GPS_HD_MODE:		//����GPSģ��
		strcat(sms_buf, "GPS:(HD)");
		break;
	case GPS_TD_MODE:		//̩��GPSģ��
		strcat(sms_buf, "GPS:(TD)");
		break;
	case GPS_UBLOX_MODE:		//ublox GPSģ��
		strcat(sms_buf, "GPS:(UBLOX)");
		break;
	case GPS_MAX_MODE:
		strcat(sms_buf, "GPS:");
		break;
	}
	
	if(kjx_gps_is_on())
	{
		if(mmi_get_gps_status())
		{
			sprintf(temp, "Successful Positioning,SVS used in fix:%d;\r\n", g_kjx_gps_data.satellite_total);
			strcat(sms_buf, temp);
		}
		else
		{
			sprintf(temp, "Searching Satellite;\r\n");
	        strcat((char *)sms_buf, temp);
		}		
	}
	else
	{
		sprintf(temp, "OFF;\r\n");
        strcat((char *)sms_buf, temp);
	}
#endif

#ifdef __KJX_RFID__
	if(g_kjx_nvram_struct.rfidflag == 1)
	{
		sprintf(temp, "RFID: ON;\r\n");
        strcat((char *)sms_buf, temp);
	}
	else
	{
		sprintf(temp, "RFID: OFF;\r\n");
        strcat((char *)sms_buf, temp);
	}
#endif

#ifdef __BLE_MODULE_SUPPORT__
	if(g_kjx_nvram_struct.btflag == 1)
	{
		sprintf(temp, "BLE: ON;\r\n");
        strcat((char *)sms_buf, temp);
	}
	else
	{
		sprintf(temp, "BLE: OFF;\r\n");
        strcat((char *)sms_buf, temp);
	}
#endif

    //����ģʽ:
    switch(g_kjx_nvram_struct.workMode)
    {
    case 0:
		sprintf(temp, "WorkMode: ����ģʽ 10��һ��");
        strcat((char *)sms_buf, temp);
		break;
	case 1:
		sprintf(temp, "WorkMode: ����ģʽ %d����һ��",     GPS_DATA_TIME/(60*1000));
        strcat((char *)sms_buf, temp);
		break;
	case 2:
		sprintf(temp, "WorkMode: �Զ���ģʽ %d����һ��",    g_kjx_nvram_struct.sendTime/(60*1000));
        strcat((char *)sms_buf, temp);
		break;
    }
	
#if defined(__ACC_DETECT__)
    //ACC
    memset(temp, 0, sizeof(temp));
    if(tracker_acc_state == ACC_ON)
    {
        sprintf((char *)temp, "ACC:ON;");
    }
    else
    {
        sprintf((char *)temp, "ACC:OFF;");
    }
    strcat(sms_buf, temp);
#endif

#if defined(__BOSCH_BMA250E__)
    //DEFENCE
    memset(temp, 0, sizeof(temp));
    if((Defense_Switch == TRUE) && (tracker_sensor_time.defencestate == 1)) ////
    {
        sprintf((char *)temp, "Defense:ON;");
    }
    else
    {
        sprintf((char *)temp, "Defense:OFF;");
    }
    strcat(sms_buf, temp);
#endif
}

/******************************************************************************
 *  Function    -  Tracker_Command_Power_off
 *
 *  Purpose     -  �豸�ػ�
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-15, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Command_Power_off(void)
{
    StopTimer(KJX_TIMER_RESET);

    srv_shutdown_normal_start(0);
}

/******************************************************************************
 *  Function    -  Tracker_Set_POWER_OFF
 *
 *  Purpose     -  �رջ���
 *
 *  Description - 
 *                      
 *                      
 * modification history
 * ----------------------------------------
 * v1.0  , 2015-01-19, xiebiao  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Set_Power_off(void)
{
	sprintf(sms_buf, "The terminal will poweroff after 5 seconds!");
	StartTimer(KJX_TIMER_ID_END_KEY_DELAY, 5*1000, Tracker_Command_Power_off);
}

/******************************************************************************
 *  Function    -  Tracker_Reset_Process
 *
 *  Purpose     -  ����ָ����������
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-08-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Reset_Process(void)
{
    sprintf(sms_buf, "The terminal will restart after 20 seconds!");
    StartTimer(KJX_TIMER_RESET, 20000, Tracker_Command_RESET);
}

/******************************************************************************
 *  Function    -  Tracker_Resume_Factory_Set
 *
 *  Purpose     -  �ָ���������
 *
 *  Description -  FACTORY#
 *                        OK
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-11, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Resume_Factory_Set(void)
{
#ifndef KJX_TEST
    S16 error;
#if defined(__KD6113_MCU_CONTROL__)&&defined(__KD6113_WORK_MODE__)
	char tmpbuf[128] = {0};
#endif

    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");//ָ������ֶζ�������ȷ
    }
    else
    {
        memset(sms_buf, 0, sizeof(sms_buf));

        if(FactoryAllRestore == TRUE)
        {
            memcpy(&tracker_apn_param, &NVRAM_EF_TRACKER_APN_PARAM_DEFAULT, NVRAM_EF_TRACKER_APN_SIZE);
            memcpy(&tracker_server_param, &NVRAM_EF_TRACKER_SERVER_PARAM_DEFAULT, NVRAM_EF_TRACKER_SERVER_SIZE);
        }
        memcpy(&tracker_sos_phb, &NVRAM_EF_TRACKER_SOS_PHB_DEFAULT, NVRAM_EF_TRACKER_SOS_PHB_SIZE);
        memcpy(&tracker_ctrl_data, &NVRAM_EF_TRACKER_CTRL_DATA_DEFAULT, NVRAM_EF_TRACKER_CTRL_DATA_SIZE);
        memcpy(&tracker_last_lbs_data, &NVRAM_EF_TRACKER_LBS_DATA_DEFAULT, NVRAM_EF_TRACKER_LBS_DATA_SIZE);
        memcpy(&tracker_time_zone, &NVRAM_EF_TRACKER_TIME_ZONE_DEFAULT, NVRAM_EF_TRACKER_TIME_ZONE_SIZE);
        memcpy(&tracker_imsi, &NVRAM_EF_TRACKER_IMSI_DEFAULT, NVRAM_EF_TRACKER_IMSI_SIZE);
        memcpy(&tracker_low_battery, &NVRAM_EF_TRACKER_LOW_BATTERY_DEFAULT, NVRAM_EF_TRACKER_LOW_BATTERY_SIZE);
        memcpy(&tracker_permit_level, &NVRAM_EF_TRACKER_PERMIT_LEVEL_DEFAULT, NVRAM_EF_TRACKER_PERMIT_LEVEL_SIZE);

	#if defined(__KJX_LOG_OUTPUT__)
        memcpy(&kjx_log_param, &NVRAM_EF_KJX_LOG_PARAM_DEFAULT, NVRAM_EF_KJX_LOG_PARAM_SIZE);
	#endif
	#if defined(__SMS_PASSWORD__)
        memcpy(&tracker_password, &NVRAM_EF_TRACKER_PASSWORD_DEFAULT, NVRAM_EF_TRACKER_PASSWORD_SIZE);
	#endif

	#if defined(__SOS_CALL__)
        memcpy(&tracker_sos_type, &NVRAM_EF_TRACKER_SOS_TYPE_DEFAULT, NVRAM_EF_TRACKER_SOS_TYPE_SIZE);
	#endif

	#if defined(__BOSCH_BMA250E__)
        memcpy(&tracker_sensor_time, &NVRAM_EF_TRACKER_SENSOR_TIME_DEFAULT, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE);
	#endif /*__BOSCH_BMA250E__*/


	#if defined(__GPS_ON_MTK__)
        memset(&Last_valide_data, 0, NVRAM_EF_TRACKER_GPS_POSITION_SIZE);
        memcpy(&tracker_gpsblindarea_alarm, &NVRAM_EF_TRACKER_GPSBLINDAREA_ALARM_DEFAULT, NVRAM_EF_TRACKER_GPSBLINDAREA_ALARM_SIZE);
        memcpy(&tracker_delay_active_time, &NVRAM_EF_TRACKER_DELAY_ACTIVE_TIME_DEFAULT, NVRAM_EF_TRACKER_DELAY_ACTIVE_TIME_SIZE);
	#if defined(__GPS_OVERSPEED__)
        memcpy(&tracker_overspeed_alarm, &NVRAM_EF_TRACKER_OVERSPEED_ALARM_DEFAULT, NVRAM_EF_TRACKER_OVERSPEED_ALARM_SIZE);
	#endif
	#if defined(__GPS_FENCE__)
        memcpy(&tracker_electronic_fence, &NVRAM_EF_TRACKER_ELECTRONIC_FENCE_DEFAULT, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE);
	#endif /*__GPS_FENCE__*/
	#if defined(__MOVING_ALARM__)
        memcpy(&tracker_moving_param, &NVRAM_EF_TRACKER_MOVING_PARAM_DEFAULT, NVRAM_EF_TRACKER_MOVING_PARAM_SIZE);
	#endif

	#if defined(__GPS_BACKUP__)
        memcpy(&backup_data_param, &NVRAM_EF_TRACKER_GPS_BACKUP_DATA_PARAM_DEFAULT, NVRAM_EF_TRACKER_GPS_BACKUP_DATA_PARAM_SIZE);
	#endif
	#endif /*__GPS_ON_MTK__*/

	#if defined(__ACC_DETECT__)
        memcpy(&tracker_acc_data, &NVRAM_EF_TRACKER_ACC_DATA_DEFAULT, NVRAM_EF_TRACKER_ACC_DATA_SIZE);
	#endif
	#if defined(__OIL_ELECTRONIC_CONTROL__)
        memcpy(&tracker_cut_power, &NVRAM_EF_TRACKER_CUT_POWER_DEFAULT, NVRAM_EF_TRACKER_CUT_POWER_SIZE);
	#endif


	#if defined(__SPECIAL_EPO_SOCKET__)
        memcpy(&tracker_epo_server, &NVRAM_EF_TRACKER_EPO_SERVER_PARAM_DEFAULT, NVRAM_EF_TRACKER_EPO_SERVER_SIZE);
	#elif defined(__SPECIAL_AGPS_SOCKET__)
        memcpy(&tracker_agps_server, &NVRAM_EF_TRACKER_AGPS_SERVER_PARAM_DEFAULT, NVRAM_EF_TRACKER_AGPS_SERVER_SIZE);
	#endif

	#if defined(__EXPAND_PORT_SUPPORT__)
        memcpy(&tracker_expand_export, &NVRAM_EF_TRACKER_EXPAND_EXPORT_DEFAULT, NVRAM_EF_TRACKER_EXPAND_EXPORT_SIZE);
        memcpy(&analog_backup_param, &NVRAM_EF_TRACKER_BACKUP_ANALOG_PARAM_DEFAULT, NVRAM_EF_TRACKER_BACKUP_ANALOG_PARAM_SIZE);
        memcpy(&digital_backup_param, &NVRAM_EF_TRACKER_BACKUP_DIGITAL_PARAM_DEFAULT, NVRAM_EF_TRACKER_BACKUP_DIGITAL_PARAM_SIZE);
	#endif    /*__EXPAND_PORT_SUPPORT__*/

	#if defined(__CAR_OBD__)
        memcpy(&tracker_obd_param, &NVRAM_EF_TRACKER_OBD_PARAM_DEFAULT, NVRAM_EF_TRACKER_OBD_PARAM_SIZE);
	#endif

	#if defined(__FUEL_SENSOR__)
        memcpy(&tracker_fuel_param, &NVRAM_EF_TRACKER_FUEL_PARAM_DEFAULT, NVRAM_EF_TRACKER_FUEL_PARAM_SIZE);
        memcpy(&fuel_backup_param, &NVRAM_EF_TRACKER_BACKUP_FUEL_PARAM_DEFAULT, NVRAM_EF_TRACKER_BACKUP_FUEL_PARAM_SIZE);
	#endif

        if(FactoryAllRestore == TRUE)
        {
            WriteRecord(NVRAM_EF_TRACKER_APN_LID, 1, (void *)&tracker_apn_param, NVRAM_EF_TRACKER_APN_SIZE, &error);
            WriteRecord(NVRAM_EF_TRACKER_SERVER_LID, 1, &tracker_server_param, NVRAM_EF_TRACKER_SERVER_SIZE, &error);
        }

        WriteRecord(NVRAM_EF_TRACKER_SOS_PHB_LID, 1, (void *)&tracker_sos_phb, NVRAM_EF_TRACKER_SOS_PHB_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, (void *)&tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_LBS_DATA_LID, 1, (void *)&tracker_last_lbs_data, NVRAM_EF_TRACKER_LBS_DATA_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_TIME_ZONE_LID, 1, (void *)&tracker_time_zone, NVRAM_EF_TRACKER_TIME_ZONE_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_IMSI_LID, 1, (void *)&tracker_imsi, NVRAM_EF_TRACKER_IMSI_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_LOW_BATTERY_LID, 1, (void *)&tracker_low_battery, NVRAM_EF_TRACKER_LOW_BATTERY_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_PERMIT_LEVEL_LID, 1, (void *)&tracker_permit_level, NVRAM_EF_TRACKER_PERMIT_LEVEL_SIZE, &error);

	#if defined(__KJX_LOG_OUTPUT__)
        WriteRecord(NVRAM_EF_KJX_LOG_PARAM_LID, 1, (void *)&kjx_log_param, NVRAM_EF_KJX_LOG_PARAM_SIZE, &error);
	#endif

	#if defined(__SMS_PASSWORD__)
        WriteRecord(NVRAM_EF_TRACKER_PASSWORD_LID, 1, &tracker_password, NVRAM_EF_TRACKER_PASSWORD_SIZE, &error);
	#endif

	#if defined(__SOS_CALL__)
        WriteRecord(NVRAM_EF_TRACKER_SOS_TYPE_LID, 1, (void *)&tracker_sos_type, NVRAM_EF_TRACKER_SOS_TYPE_SIZE, &error);
	#endif

	#if defined(__BOSCH_BMA250E__)
        WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, &tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &error);
	#endif/*__BOSCH_BMA250E__*/

	#if defined(__GPS_ON_MTK__)
        WriteRecord(NVRAM_EF_TRACKER_GPS_POSITION_LID, 1, (void *)&Last_valide_data, NVRAM_EF_TRACKER_GPS_POSITION_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_GPSBLINDAREA_ALARM_LID, 1, (void *)&tracker_gpsblindarea_alarm, NVRAM_EF_TRACKER_GPSBLINDAREA_ALARM_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_DELAY_ACTIVE_TIME_LID, 1, (void *)&tracker_delay_active_time, NVRAM_EF_TRACKER_DELAY_ACTIVE_TIME_SIZE, &error);

	#if defined(__GPS_BACKUP__)
        WriteRecord(NVRAM_EF_TRACKER_GPS_BACKUP_DATA_PARAM_LID, 1, (void *)&backup_data_param, NVRAM_EF_TRACKER_GPS_BACKUP_DATA_PARAM_SIZE, &error);
	#endif

	#if defined(__GPS_OVERSPEED__)
        WriteRecord(NVRAM_EF_TRACKER_OVERSPEED_ALARM_LID, 1, (void *)&tracker_overspeed_alarm, NVRAM_EF_TRACKER_OVERSPEED_ALARM_SIZE, &error);
	#endif
	#if defined(__GPS_FENCE__)
        WriteRecord(NVRAM_EF_TRACKER_ELECTRONIC_FENCE_LID, 1, (void *)&tracker_electronic_fence, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE, &error);
	#endif  /*__GPS_FENCE__*/
	#if defined(__MOVING_ALARM__)
        WriteRecord(NVRAM_EF_TRACKER_MOVING_PARAM_LID, 1, (void *)&tracker_moving_param, NVRAM_EF_TRACKER_MOVING_PARAM_SIZE, &error);
	#endif
	#endif  /*__GPS_ON_MTK__*/

	#if defined(__ACC_DETECT__)
        WriteRecord(NVRAM_EF_TRACKER_ACC_DATA_LID, 1, (void *)&tracker_acc_data, NVRAM_EF_TRACKER_ACC_DATA_SIZE, &error);
	#endif

	#if defined(__OIL_ELECTRONIC_CONTROL__)
        WriteRecord(NVRAM_EF_TRACKER_CUT_POWER_LID, 1, (void *)&tracker_cut_power, NVRAM_EF_TRACKER_CUT_POWER_SIZE, &error);
	#endif

	#if defined(__SPECIAL_EPO_SOCKET__)
        WriteRecord(NVRAM_EF_TRACKER_EPO_SERVER_LID, 1, (void *)&tracker_epo_server, NVRAM_EF_TRACKER_EPO_SERVER_SIZE, &error);
	#elif defined(__SPECIAL_AGPS_SOCKET__)
        WriteRecord(NVRAM_EF_TRACKER_AGPS_SERVER_LID, 1, (void *)&tracker_agps_server, NVRAM_EF_TRACKER_AGPS_SERVER_SIZE, &error);
	#endif

	#if defined(__EXPAND_PORT_SUPPORT__)
        WriteRecord(NVRAM_EF_TRACKER_EXPAND_EXPORT_LID, 1, (void *)&tracker_expand_export, NVRAM_EF_TRACKER_EXPAND_EXPORT_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_BACKUP_ANALOG_PARAM_LID, 1, (void *)&analog_backup_param, NVRAM_EF_TRACKER_BACKUP_ANALOG_PARAM_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_BACKUP_DIGITAL_PARAM_LID, 1, (void *)&digital_backup_param, NVRAM_EF_TRACKER_BACKUP_DIGITAL_PARAM_SIZE, &error);
	#endif

	#if defined(__CAR_OBD__)
        WriteRecord(NVRAM_EF_TRACKER_OBD_PARAM_LID, 1, (void *)&tracker_obd_param, NVRAM_EF_TRACKER_OBD_PARAM_SIZE, &error);
	#endif

	#if defined(__FUEL_SENSOR__)
        WriteRecord(NVRAM_EF_TRACKER_FUEL_PARAM_LID, 1, &tracker_fuel_param, NVRAM_EF_TRACKER_FUEL_PARAM_SIZE, &error);
        WriteRecord(NVRAM_EF_TRACKER_BACKUP_FUEL_PARAM_LID, 1, &fuel_backup_param, NVRAM_EF_TRACKER_BACKUP_FUEL_PARAM_SIZE, &error);
	#endif

	#if defined(__PARAM_BACKUP__)
        StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
	#endif

	#if defined(__KD6113_MCU_CONTROL__)&&defined(__KD6113_WORK_MODE__)
		sprintf(tmpbuf,"AT^GT_CM=04,%d,%d#",tracker_ctrl_data.workmode.type,tracker_ctrl_data.workmode.time);
		Tracker_Send_Message_To_MCU(tmpbuf);
	#endif/*__KD6113_MCU_CONTROL__*/
	
        strcpy(sms_buf, (char*)"OK");
    }
#endif
}





/******************************************************************************
 *  Function    -  Tracker_Resume_Factory_SetPart
 *
 *  Purpose     -  �ָ����в���������IP����
 *
 *  Description -  FACTORY#
 *                        OK
 * modification history
  * ----------------------------------------
 * v1.0  , 2013-10-08, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Resume_Factory_SetPart(void)
{
    FactoryAllRestore = FALSE;
    Tracker_Resume_Factory_Set();
}

/******************************************************************************
 *  Function    -  Tracker_Resume_Factory_SetAll
 *
 *  Purpose     -  �ָ����в���
 *
 *  Description -  FACTORYALL#
 *                        OK
 * modification history
  * ----------------------------------------
 * v1.0  , 2013-10-08, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Resume_Factory_SetAll(void)
{
    FactoryAllRestore = TRUE;
    Tracker_Resume_Factory_Set();
}

#ifdef __AUTOTEST_TOOL__
kal_bool g_is_autotest_mode = KAL_FALSE; //�Զ�����ģʽ�� ��Ҫ���������� cjt
#include "mmi_msg_struct.h"
#include "MMI_FRM_QUEUE_GPROT.H"
#if 0
/*****************************************************************************
 * FUNCTION
 *  EngineerModeSendMsg
 * DESCRIPTION
 *
 * PARAMETERS
 *  msg_id              [IN]
 *  local_param_ptr     [?]
 *  peer_buf_ptr        [?]
 * RETURNS
 *  void
 *****************************************************************************/
void EngineerModeSendMsg(U16 msg_id, void *local_param_ptr, void *peer_buf_ptr)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    mmi_frm_send_ilm((oslModuleType) MOD_L4C, (oslMsgType)msg_id,
                     (oslParaType*)local_param_ptr, (oslPeerBuffType*)peer_buf_ptr);

}

/*****************************************************************************
 * FUNCTION
 *  EngineerModeSetSleepModeReq
 * DESCRIPTION
 *
 * PARAMETERS
 *  index       [IN]
 * RETURNS
 *  void
 *****************************************************************************/
void EngineerModeSetSleepModeReq(U8 index)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_eq_set_sleep_mode_req_struct *msg_p;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    msg_p = OslConstructDataPtr(sizeof(mmi_eq_set_sleep_mode_req_struct));
    msg_p->on_off = (index == 0);

    EngineerModeSendMsg(MSG_ID_MMI_EQ_SET_SLEEP_MODE_REQ, msg_p, NULL);

}
#endif

extern void EngineerModeSetSleepModeReq(U8 index);

//�����ֻ�˯��
void mmi_gsm_security_sleep_enable(void)
{
    EngineerModeSetSleepModeReq(0);
}
//�������ֻ�˯��
void mmi_gsm_security_sleep_disable(void)
{
    EngineerModeSetSleepModeReq(1);
}

#endif

/******************************************************************************
 *  Function    -  Tracker_Entry_Test_Mode
 *
 *  Purpose     -  ���빤������ģʽ����
 *
 *  Description -  �ϵ緢TESTָ��
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-06-20, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Entry_Test_Mode(void)
{
#ifndef KJX_TEST
	char str_mcp[128] = {0};

    if(EntryTestModeReady == FALSE)
    {
        sprintf(sms_buf, "No Ready");
    }
    else
    {
        if(PhoneTestMode == FALSE)
        {
            PhoneTestMode = TRUE;
		#if defined(__GPS_ON_MTK__)
            if(!GPSOnFlag)
            {
                GPS_ON();
            }
		#endif /*__MTK_ON_GPS__*/

		#if defined(__LED_APP__)	//xb add 2015-5-7 ����ģʽ��Ϩ�𣬵�ʱ�ɲ������ٵ���
			pmu_drv_keypad_blink(KAL_FALSE);
		#endif/*__LED_APP__*/
		
		#if defined(__KD6113_MCU_CONTROL__)
			strcpy(str_mcp, "AT^GT_CM=02,00,00#");
			Tracker_Send_Message_To_MCU(str_mcp);
		#endif/*__KD6113_MCU_CONTROL__*/

		#if defined(__KD6113_WORK_MODE__)
		if(IsMyTimerExist(TRACKER_POWER_OFF_TIMER_ID))
			StopTimer(TRACKER_POWER_OFF_TIMER_ID);
			
		if(IsMyTimerExist(TRACKER_POWER_OFF_WAIT_TIMER_ID))
			StopTimer(TRACKER_POWER_OFF_WAIT_TIMER_ID);
		#endif/*__KD6113_WORK_MODE__*/
        }

		g_is_autotest_mode = KAL_TRUE;  //�����ģʽ
		
        sprintf(sms_buf, "OK");
    }
#endif
}

/******************************************************************************
 *  Function    -  Tracker_Get_Software_Version_For_Factory
 *
 *  Purpose     -  ��ȡ�汾��
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-15
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Get_Software_Version_For_Factory(void)
{
    U8 temp[100];

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");//ָ������ֶζ�������ȷ
        return;
    }

    memset(temp, 0, 300);
    sprintf((char *)temp, "[VERSION]");
    strcat((char *)temp, "GT02R_8851C_V01");
    strcpy(sms_buf, (char*) temp);

}


#if defined(__SMS_PASSWORD__)
/******************************************************************************
 *  Function    -  Tracker_Set_Password_Status
 *
 *  Purpose     -  ���뿪��
 *
 *  Description - PWDSW,ON# ��PWDSW,����(000000 - 999999),OFF#
 *
 * modification history   ,������������ʱ�ж�
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Password_Status(void)
{
#ifndef KJX_TEST
    S16 error;

    if((Command_State == SMS_Command_State)
            && (Delete_SmsPrefix_Confirm_SOSNum() == 0XFF)
            && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE)
            && (SuperCommandHead == FALSE))
    {
        sprintf(sms_buf, "ERROR:117");                     //����SOS��������ĺ���
        return ;
    }

    if(received_data.part == 0)
    {
        if(tracker_password.state == 0)
        {
            sprintf(sms_buf, "PWDSW:OFF");
        }
        else
        {
            sprintf(sms_buf, "PWDSW:ON");
        }
    }
    else if(received_data.part == 1)
    {
        if(strcmp("ON", ((char *)received_data.param0)) == 0)
        {
            tracker_password.state = 1;
            WriteRecord(NVRAM_EF_TRACKER_PASSWORD_LID, 1, &tracker_password, NVRAM_EF_TRACKER_PASSWORD_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
        else if(strcmp("OFF", ((char *)received_data.param0)) == 0)
        {
            tracker_password.state = 0;
            WriteRecord(NVRAM_EF_TRACKER_PASSWORD_LID, 1, &tracker_password, NVRAM_EF_TRACKER_PASSWORD_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");//ָ���ʽ����
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
    }
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Change_Password
 *
 *  Purpose     -  ����������
 *
 *  Description -  PASSWORD,A,B#    A:������ ; B:������  (000000 - 999999)
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Change_Password(void)
{
#ifndef KJX_TEST
    S16 error;
    BOOL is_pw = FALSE;
    int oldlen, newlen;
    char oldpassword[GPS_PASSWD_LEN_MAX] = {0};
    char newpassword[GPS_PASSWD_LEN_MAX] = {0};

    //��������Tracker_Check_Authentication ��У��
    LOGD("cur:%s ,old:%s, new:%s", tracker_password.passwd, received_data.param0, received_data.param1);
	
    if(received_data.part != 2)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return ;
    }

    memcpy(oldpassword, received_data.param0, GPS_PASSWD_LEN_MAX);
    memcpy(newpassword, received_data.param1, GPS_PASSWD_LEN_MAX);

    oldlen = strlen((char*)oldpassword);
    newlen = strlen((char*)newpassword);
	
    if((tracker_is_password_format((S8*)oldpassword, oldlen) == FALSE) 
		|| (tracker_is_password_format((S8*)newpassword, newlen) == FALSE)
		)
    {
    	sprintf(sms_buf, "ERROR:103");//�����ʽ����ȷ
    	return;
    }
	
	if(strcmp((char*)tracker_password.passwd, (char*)oldpassword) != 0)
	{
		sprintf(sms_buf, "ERROR:109");//���������
	}
	else
	{
		//������;�����һ��
	    if(strcmp((char *)tracker_password.passwd, (char *)newpassword) == 0)
	    {
	    	sprintf(sms_buf, "ERROR:119");  //������;����벻����ͬ
	    }
		else
		{
			memset(tracker_password.passwd, 0, GPS_PASSWD_LEN_MAX);
			memcpy(tracker_password.passwd, newpassword, GPS_PASSWD_LEN_MAX);
			WriteRecord(NVRAM_EF_TRACKER_PASSWORD_LID, 1, &tracker_password, NVRAM_EF_TRACKER_PASSWORD_SIZE, &error);
			sprintf(sms_buf, "OK");
		}
	}
#endif
}

/******************************************************************************
 *  Function    -  Tracker_Resume_Password
 *
 *  Purpose     -  �ָ�ΪĬ������
 *
 *  Description - SUPER,RECOVER#
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Resume_Password(void)
{
#ifndef KJX_TEST
    S16 error;
    char password[GPS_PASSWD_LEN_MAX] = {0};

    LOGD("  %d,%s", received_data.part, received_data.passwd);
	
    if(received_data.part == 0)
    {
        memset(tracker_password.passwd, 0, GPS_PASSWD_LEN_MAX);
        memcpy(tracker_password.passwd, NVRAM_EF_TRACKER_PASSWORD_DEFAULT[0].passwd, GPS_PASSWD_LEN_MAX);
        WriteRecord(NVRAM_EF_TRACKER_PASSWORD_LID, 1, &tracker_password, NVRAM_EF_TRACKER_PASSWORD_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
    }
#endif
}

#endif

#if defined(__SOS_CALL__)
/******************************************************************************
 *  Function    -  Tracker_Set_SOS_Alarm_Status
 *
 *  Purpose     - ����SOS����״̬
 *
 *  Description -  SOSALM,ON[,M]#
 *                        SOSALM,OFF#
 *                        M:SOS�����ظ����� SOS_NO_ALARM, SOS_CALL_ONLY, SOS_SMS_ONLY, SOS_SMS_AND_CALL, SOS_GPRS_ONLY
 *                        SOSALM#   ��ѯ����
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_SOS_Alarm_Status(void)
{
    S16 error;
    U16  interval = 0xffff;
    U8 interval_str[20];


    memset(sms_buf, 0, sizeof(sms_buf));
    LOGD(" %s", received_data.param0);

    if(received_data.part == 0)
    {
        if(tracker_sos_type.remindstate)
        {
            sprintf(sms_buf, "SOSALM:ON,");
        }
        else
        {
            sprintf(sms_buf, "SOSALM:OFF;");
        }

		switch(tracker_sos_type.Alerttype)
		{
		case SOS_NO_ALARM:
			strcat(sms_buf, "NO ALARM;");
			break;
		case SOS_CALL_ONLY:
			strcat(sms_buf, "GPRS+CALL;");
			break;
		case SOS_SMS_ONLY:
			strcat(sms_buf, "GPRS+SMS;");
			break;
		case SOS_SMS_AND_CALL:
			strcat(sms_buf, "GPRS+SMS+CALL;");
			break;
		case SOS_GPRS_ONLY:
			strcat(sms_buf, "GPRS;");
			break;
		}
    }
    else if((strcmp("ON", ((char *)received_data.param0)) == 0) && (received_data.part != 0))
    {
        if((received_data.part != 1) && (received_data.part != 2))
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        if(received_data.part == 1)
        {
            tracker_sos_type.remindstate = 1;
        }
        else
        {
            memset(interval_str, 0, 20);
            memcpy(interval_str, received_data.param1, 20);

            interval = interval_Time_Manage(interval_str, 0, 3);

            if(interval == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return;
            }

            tracker_sos_type.remindstate = 1;
            tracker_sos_type.Alerttype = interval;
        }

        WriteRecord(NVRAM_EF_TRACKER_SOS_TYPE_LID, 1, &tracker_sos_type, NVRAM_EF_TRACKER_SOS_TYPE_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else if((strcmp("OFF", ((char *)received_data.param0)) == 0) && (received_data.part != 0))
    {
        if(received_data.part != 1)
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        tracker_sos_type.remindstate = 0;
        WriteRecord(NVRAM_EF_TRACKER_SOS_TYPE_LID, 1, &tracker_sos_type, NVRAM_EF_TRACKER_SOS_TYPE_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
    }
}




/******************************************************************************
 *  Function    -  Tracker_Set_SOS_Call_Times
 *
 *  Purpose     - SOSѭ���������
 *
 *  Description -  CALL,N#   CALL#
 *                       N (1-3)
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_SOS_Call_Times(void)
{
    S16 error;
    U16  interval = 0xffff;
    U8 interval_str[20];


    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part > 1)
    {
        sprintf(sms_buf, "ERROR:100");
        return;
    }

    if(received_data.part == 0)
    {
        sprintf(sms_buf, "CALL:%d;", tracker_sos_type.Recall);
    }
    else
    {
        memset(interval_str, 0, 20);
        memcpy(interval_str, received_data.param0, 20);

        interval = interval_Time_Manage(interval_str, 1, 3);

        if(interval == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");
            return;
        }
        tracker_sos_type.Recall = interval;
        WriteRecord(NVRAM_EF_TRACKER_SOS_TYPE_LID, 1, &tracker_sos_type, NVRAM_EF_TRACKER_SOS_TYPE_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
}

#endif


#if defined(__LED_APP__)


/******************************************************************************
 *  Function    -  Tracker_Set_Led_Sleep_Status
 *
 *  Purpose     -  LED��˯��
 *
 *  Description -  LEDSLEEP,ON/OFF#
 *                       LEDSLEEP#            ON  :��������  Ĭ��ON
 * modification history                      OFF :  �ر�����
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Led_Sleep_Status(void)
{
    S16 Error;
    U16  interval;

    if(received_data.part == 0)
    {
        if(tracker_ctrl_data.led_sleep == 1)
        {
            sprintf(sms_buf, "LEDSLEEP:ON;", tracker_ctrl_data.led_sleep);
        }
        else
        {
            sprintf(sms_buf, "LEDSLEEP:OFF;");
        }
    }
    else if(received_data.part == 1)
    {
        if((strcmp((char *) received_data.param0, "ON") == 0) || (strcmp((char *) received_data.param0, "OFF") == 0))
        {
            //LED��������
            if(strcmp((char *) received_data.param0, "ON") == 0)
            {
                tracker_ctrl_data.led_sleep = 1;

                if(GPSOnFlag == FALSE)
                {
                    LED_Stop();
                }
            }
            else
            {
                //LED��ֹ����
                tracker_ctrl_data.led_sleep = 0;
			#if defined(__BOSCH_BMA250E__)
                if(tracker_ctrl_data.keystate == 1)
                {
                    if(Defense_Switch == TRUE)
                    {
                        LED_Defense_Indicate();
                    }
                    else
                    {
                        LED_HW_Init();
                    }
                }
			#endif/*__BOSCH_BMA250E__*/
            }

            sprintf(sms_buf, "OK");
            WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, (void *)&tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &Error);
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
			if((Command_State == AT_Command_State)
		#if defined(__AT_USE_UART1__)
			||(Command_State == UART1_Command_State)
		#endif
			)
            {
                strcat(sms_buf, ";LEDSLEEP,ON /OFF");
            }
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
		if((Command_State == AT_Command_State)
	 #if defined(__AT_USE_UART1__)
		||(Command_State == UART1_Command_State)
	 #endif
		)
        {
            strcat(sms_buf, ";LEDSLEEP,ON/OFF#");
        }
    }

}


#endif


#if defined(__SMS_TRANSMISSION__)
/******************************************************************************
 *  Function    -  Tracker_Message_Need_Upload
 *
 *  Purpose     -  ��FW ����ѯ�ĺ��뷢������ָ�ת��
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2014-07-11, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static BOOL Tracker_Message_Need_Upload(void)
{
    if(g_is_wait_DTU_msg)
    {
        if(ConfirmNumberIsUploadNumber((char*)sys_rcv_sms.num))
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }
}



/******************************************************************************
 *  Function    -  Tracker_Upload_DTU_Message
 *
 *  Purpose     -  �ϴ�ָ�����뷢����͸������
 *
 *  Description - ���ﳤ��Ϊ141*2=282 ���ȳ���256ʱ��ת���ĳ��Ȳ���
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-08-17, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Upload_DTU_Message(const S8 * content, U16 len)
{
    memset(sms_buf, 0, sizeof(sms_buf));
    LOGD(" len:%d,%d", sys_rcv_sms.len, len);

    if(len > 0)
    {
        //ÿһ��ת������ǰҪ���֮ǰ��������
        memset(queryfee_sms.content, 0, sizeof(queryfee_sms.content));
        queryfee_sms.contentlen = 0;
        if(queryfee_sms.isonlineorsms == ONLine_Command_State)
        {
            queryfee_sms.contentlen = len;    //���ﳤ��Ϊ��������UNICODE

            LOGD(" ^^ len:%d,%d", sys_rcv_sms.len, queryfee_sms.contentlen);
            memcpy(queryfee_sms.content, content, queryfee_sms.contentlen);
            Tracker_Online_State = TRACKER_ONLINE_FEE_RELAY;
            gprs_send_type = GPRS_ONLINE_RESULT_INFO;
            Tracker_Socket_Send_Current_Data();
        }
        else if(queryfee_sms.isonlineorsms == SMS_Command_State)
        {
            memcpy(queryfee_sms.content, content, len);
            LOGD("^^ len:%d", len);
            SetSendSMS(FALSE, queryfee_sms.receiver_num, 0, queryfee_sms.content);
        }
        else
        {
            sprintf(sms_buf, "Query Fee Sucess!");
            rmmi_write_to_uart((kal_uint8*)sms_buf, strlen(sms_buf), KAL_TRUE);
        }
    }
}

/******************************************************************************
 *  Function    -  Tracker_DTU_Message_Timeout
 *
 *  Purpose     -  ͸�����Ż�ȡ��ʱ
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-08-17, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_DTU_Message_Timeout(void)
{
    memset(sms_buf, 0, sizeof(sms_buf));
    g_is_wait_DTU_msg = KAL_FALSE ;
    LOGD("^^  DTU:%d", g_is_wait_DTU_msg);

    StopTimer(TRACKER_DTU_SMS_WAIT_TIMER);

    if(queryfee_sms.isonlineorsms == ONLine_Command_State)
    {

    }
    else  if(queryfee_sms.isonlineorsms == SMS_Command_State)
    {

    }
    else
    {
        sprintf(sms_buf, "Query Fee OverTime!");
        Send_Command_Message_Replay();
        queryfee_sms.isonlineorsms = SMS_Command_State;
    }
}

/******************************************************************************
 *  Function    -  Tracker_Query_Balance_Fee
 *
 *  Purpose     -  ��ѯSIM���������
 *
 *  Description -  //FW,10086,101#
 *                       //queryfee_sms.receiver_num ���뷢������ָ�ת��
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-08-17, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Query_Balance_Fee(void)
{
    S16 error;
    char number[21];
    char content[400] = {0};
    U8 lenth = 0;
    BOOL is_num = TRUE;

    memset(number, 0, sizeof(number));
    memset(content, 0, sizeof(content));
    memset(sms_buf, 0, sizeof(sms_buf));

    LOGD(" %d", received_data.part);

	if((Command_State == AT_Command_State)
#if defined(__AT_USE_UART1__)
	||(Command_State == UART1_Command_State)
#endif
	)
    {
        sprintf(sms_buf, "ERROR:107");
        Send_Command_Message_Replay();
        return;
    }


    if(received_data.part != 2)
    {
        if(Command_State == ONLine_Command_State)
        {
            //���յ������ٻظ�
            sprintf(sms_buf, "ERROR:100");
            Tracker_Online_State = TRACKER_ONLINE_FEE_FAIL;
            gprs_send_type = GPRS_ONLINE_RESULT_INFO;
            Tracker_Socket_Send_Current_Data();
        }
        else if(Command_State == SMS_Command_State)
        {
            sprintf(sms_buf, "ERROR:100");
            Send_Command_Message_Replay();
        }
        else
        {
            sprintf(sms_buf, "ERROR:100");
            Send_Command_Message_Replay();
        }
        return;
    }

    strcpy(content, (char*)received_data.param1);   //101
    strcpy(number, (char*)received_data.param0);   //10086

    lenth = strlen((char *)number);
    is_num = SetNumber_is_num((S8*)number, lenth);

    if(lenth > 21 - 1 || lenth < 3 || is_num == FALSE || (strlen((char *)content) == 0))
    {
        if(Command_State == ONLine_Command_State)
        {
            sprintf(sms_buf, "ERROR:101");
            Tracker_Online_State = TRACKER_ONLINE_FEE_FAIL;
            gprs_send_type = GPRS_ONLINE_RESULT_INFO;
            Tracker_Socket_Send_Current_Data();
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
        }
        return;
    }

    memset(&queryfee_sms, 0, sizeof(tracker_queryfee_struct));
    if(Command_State == SMS_Command_State)
    {
        queryfee_sms.isonlineorsms = SMS_Command_State;
        memcpy(queryfee_sms.receiver_num, sys_rcv_sms.num, strlen((char*)sys_rcv_sms.num));
    }
    else if(Command_State == ONLine_Command_State)
    {
        queryfee_sms.isonlineorsms = ONLine_Command_State;
    }
#if defined(__AT_USE_UART1__)
    else if(Command_State == UART1_Command_State)
    {
        queryfee_sms.isonlineorsms = UART1_Command_State;
    }
#endif
    else
    {
        queryfee_sms.isonlineorsms = AT_Command_State;
    }

    //���Ͳ�ѯSIM���������ƶ�/��ͨ��Ӫ��
    memset(queryfee_sms.operator_num, 0, sizeof(queryfee_sms.operator_num));
    memcpy(queryfee_sms.operator_num, number, lenth);

    g_is_wait_DTU_msg = TRUE;
    SetSendSMS(TRUE, number, 0, content);

    StartTimer(TRACKER_DTU_SMS_WAIT_TIMER, 10 * 60 * 1000, Tracker_DTU_Message_Timeout);
}


#endif

#if defined(__BOSCH_BMA250E__)
/******************************************************************************
 *  Function    -  Tracker_Set_Defense_Mode
 *
 *  Purpose     -  �Զ����ֵ����
 *
 *  Description -  DEFENMODE,0#     0,�Զ����������1���ֶ������Ĭ��1
 *                       DEFENMODE#
 * modification history
 * ----------------------------------------
 * v1.0  , 2014-04-14,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Defense_Mode(void)
{
    S16 Error;
    U16  interval;

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part > 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
		if((Command_State == AT_Command_State)
	#if defined(__AT_USE_UART1__)
		||(Command_State == UART1_Command_State)
	#endif
		)
        {
            strcat(sms_buf, ";DEFMODE,1#;DEFMODE#");
        }
        return;
    }

    if(received_data.part == 0)
    {
        sprintf(sms_buf, "DEFMODE:%d;", tracker_sensor_time.defencemode);
    }
    else if(received_data.part == 1)
    {
        interval = interval_Time_Manage(received_data.param0, 0, 1);   // ��λ:����

        if(interval == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
			if((Command_State == AT_Command_State)
		#if defined(__AT_USE_UART1__)
			||(Command_State == UART1_Command_State)
		#endif
			)
            {
                strcat(sms_buf, ";DEFENSE,1#");
            }
            return;
        }

        tracker_sensor_time.defencemode = interval;

	#if defined(__ACC_DETECT__)
        //��Ϊ�Զ���������ACCΪON�����˳����
        if((tracker_sensor_time.defencemode == 0) && (tracker_sensor_time.defencestate  == 1) && (tracker_acc_state == ACC_ON))
        {
            Bosch_Sensor_Defence_Stop();
        }

        //��Ϊ�Զ��������ǰACC OFF ,�𶯱�������Ҫ�������
        //��ACC �ǹر�״̬�����ý������״̬

        //ACC OFF ���Զ����ģʽ�Ž����
        if(tracker_acc_state == ACC_OFF && tracker_sensor_time.defencemode == 0)
        {

            if(tracker_sensor_time.defence_start_time == 0)
            {
                tracker_sensor_time.defence_start_time = 10 * 60 * 1000;
            }

            if((tracker_sensor_time.state == 1) && (tracker_sensor_time.defence_start_time != 0))
            {
                LOGD("  starttime:%d", tracker_sensor_time.defence_start_time / 60000);
                StopTimer(SENSOR_DEFENCE_START_TIMER);
                StartTimer(SENSOR_DEFENCE_START_TIMER, tracker_sensor_time.defence_start_time, Bosch_Sensor_Defence_Start);
            }
        }
	#endif/*__ACC_DETECT__*/

	#if defined(__SENALM_NOT_ACC_DETECT__)//wnq	     
        //��Ϊ�Զ��������ǰACC OFF ,�𶯱�������Ҫ�������
        //��ACC �ǹر�״̬�����ý������״̬
        // �����ACC,���Զ����ģʽ�Ž����
        if(tracker_sensor_time.defencemode == 0)
        {
            if(tracker_sensor_time.defence_start_time == 0)
            {
                tracker_sensor_time.defence_start_time = 10 * 60 * 1000;
            }

            if((tracker_sensor_time.state == 1) && (tracker_sensor_time.defence_start_time != 0))
            {
                LOGD("  starttime:%d", tracker_sensor_time.defence_start_time / 60000);
                StopTimer(SENSOR_DEFENCE_START_TIMER);
                StartTimer(SENSOR_DEFENCE_START_TIMER, tracker_sensor_time.defence_start_time, Bosch_Sensor_Defence_Start);
            }
        }
	#endif/*__SENALM_NOT_ACC_DETECT__*/


        WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, &tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &Error);
        LOGD(" %d", tracker_sensor_time.defencemode);
        sprintf(sms_buf, "OK");
    }

}

/******************************************************************************
 *  Function    -  Tracker_Set_Defense_Start
 *
 *  Purpose     -  �ֶ����
 *
 *  Description -  111#
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2014-05-19,  guojie  written
 * ----------------------------------------
******************************************************************************/
void Tracker_Set_Defense_Start(void)
{
    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part == 0)
    {
        if((Command_State == SMS_Command_State) && (Delete_SmsPrefix_Confirm_SOSNum() == 0xFF))
        {
            sprintf(sms_buf, "ERROR:111");   //��SOS���벻��ʹ�ô�ָ��
            Send_Command_Message_Replay();
            return;
        }


        //���ֶ����ģʽ
        if(tracker_sensor_time.defencemode == 1)
        {
            //�𶯹ر�ʱ��Զ��������ɹ����뽫�𶯱������ܴ򿪺����ԡ�
            if(tracker_sensor_time.state == 0)
            {
                if(Command_State == SMS_Command_State)
                {
				#if defined(__STRING_USE_ARRAY__)
                    memset(&sys_send_sms, 0, sizeof(SYS_SMS_STRUCT));
                    if(CurrentLang == 1)
                    {
                        sys_send_sms.len = app_ucs2_strlen((char *)defense_on_fail[1]) * 2;
                        memcpy(sys_send_sms.content, &defense_on_fail[1], sys_send_sms.len);
                        SetSendSMS(FALSE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
                    }
                    else
                    {
                        sys_send_sms.len = strlen((char *)defense_on_fail[0]);
                        memcpy(sys_send_sms.content, &defense_on_fail[0], sys_send_sms.len);
                        SetSendSMS(TRUE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
                    }
				#else
                    SetSendSMS(FALSE,  sys_rcv_sms.num, STR_SMS_DEFENSE_START_FAIL , NULL);
				#endif
                }
                else
                {
                    sprintf(sms_buf, "The remote fortification unsuccessful, please vibration alarm function is turned on and try again.");
                    Send_Command_Message_Replay();
                }
            }
            else
            {
                if(tracker_sensor_time.defencestate == 1)
                {
                    if(Command_State == SMS_Command_State)
                    {
					#if defined(__STRING_USE_ARRAY__)
                        memset(&sys_send_sms, 0, sizeof(SYS_SMS_STRUCT));
                        if(CurrentLang == 1)
                        {
                            sys_send_sms.len = app_ucs2_strlen((char *)defense_already_on[1]) * 2;
                            memcpy(sys_send_sms.content, &defense_already_on[1], sys_send_sms.len);
                            SetSendSMS(FALSE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
                        }
                        else
                        {
                            sys_send_sms.len = strlen((char *)defense_already_on[0]);
                            memcpy(sys_send_sms.content, &defense_already_on[0], sys_send_sms.len);
                            SetSendSMS(TRUE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
                        }
					#else
                        SetSendSMS(FALSE,  sys_rcv_sms.num, STR_SMS_DEFENSE_ALREADY_ON , NULL);
					#endif
                    }
                    else
                    {
                        sprintf(sms_buf, "Already in the state of fortification, The command is not executed!");
                        Send_Command_Message_Replay();
                    }
                }
                else
                {
                    //�ֶ��������״̬
                    Bosch_Sensor_Defence_Start();
                    if(Command_State == SMS_Command_State)
                    {
					#if defined(__STRING_USE_ARRAY__)
                        memset(&sys_send_sms, 0, sizeof(SYS_SMS_STRUCT));
                        if(CurrentLang == 1)
                        {
                            sys_send_sms.len = app_ucs2_strlen((char *)defense_on_success[1]) * 2;
                            memcpy(sys_send_sms.content, &defense_on_success[1], sys_send_sms.len);
                            SetSendSMS(FALSE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
                        }
                        else
                        {
                            sys_send_sms.len = strlen((char *)defense_on_success[0]);
                            memcpy(sys_send_sms.content, &defense_on_success[0], sys_send_sms.len);
                            SetSendSMS(TRUE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
                        }
					#else
                        SetSendSMS(FALSE,  sys_rcv_sms.num, STR_SMS_DEFENSE_START_SUCCESS , NULL);
					#endif
                    }
                    else
                    {
                        sprintf(sms_buf, "OK");
                        Send_Command_Message_Replay();
                    }
                }
            }
        }
        else
        {
            sprintf(sms_buf, "ERROR:123");   //�ն˴����Զ����ģʽ�������ֶ�����򳷷���
            Send_Command_Message_Replay();
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
		if((Command_State == AT_Command_State)
	#if defined(__AT_USE_UART1__)
		||(Command_State == UART1_Command_State)
	#endif
		)
        {
            strcat(sms_buf, ";111#");
        }
        Send_Command_Message_Replay();
    }

}


/******************************************************************************
 *  Function    -  Tracker_Set_Defense_Stop
 *
 *  Purpose     -  �ֶ�����
 *
 *  Description -  000#
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2014-05-19,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Set_Defense_Stop(void)
{

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part == 0)
    {
        if((Command_State == SMS_Command_State) && (Delete_SmsPrefix_Confirm_SOSNum() == 0xFF))
        {
            sprintf(sms_buf, "ERROR:111");   //��SOS���벻��ʹ�ô�ָ��
            Send_Command_Message_Replay();
            return;
        }

        //���ֶ����ģʽ
        if(tracker_sensor_time.defencemode == 1)
        {
            if(tracker_sensor_time.defencestate == 0)
            {
			#if defined(__STRING_USE_ARRAY__)
                memset(&sys_send_sms, 0, sizeof(SYS_SMS_STRUCT));
                if(CurrentLang == 1)
                {
                    sys_send_sms.len = app_ucs2_strlen((char *)defense_stop_already[1]) * 2;
                    memcpy(sys_send_sms.content, &defense_stop_already[1], sys_send_sms.len);
                    SetSendSMS(FALSE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
                }
                else
                {
                    sys_send_sms.len = strlen((char *)defense_stop_already[0]);
                    memcpy(sys_send_sms.content, &defense_stop_already[0], sys_send_sms.len);
                    SetSendSMS(TRUE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
                }
			#else
                SetSendSMS(FALSE,  sys_rcv_sms.num, STR_SMS_DEFENSE_ALREADY_OFF , NULL);
			#endif
            }
            else
            {
                //�ֶ�����
                Bosch_Sensor_Defence_Stop();
                //����Ѿ������𶯱�������ʱ���ͣ�����ʱ��ֹͣ����
                StopTimer(SENSOR_SHAKE_DELAY_ALARM_TIMER);
                StopTimer(SENSOR_SHAKE_ALRAM_INTERVAL_TIMER);
                StopTimer(SENSOR_SHAKE_ALRAM_OVERTIME_TIMER);
                SensorHaveAlarm = FALSE;
                if(Command_State == SMS_Command_State)
                {
				#if defined(__STRING_USE_ARRAY__)
                    memset(&sys_send_sms, 0, sizeof(SYS_SMS_STRUCT));
                    if(CurrentLang == 1)
                    {
                        sys_send_sms.len = app_ucs2_strlen((char *)defense_stop_success[1]) * 2;
                        memcpy(sys_send_sms.content, &defense_stop_success[1], sys_send_sms.len);
                        SetSendSMS(FALSE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
                    }
                    else
                    {
                        sys_send_sms.len = strlen((char *)defense_stop_success[0]);
                        memcpy(sys_send_sms.content, &defense_stop_success[0], sys_send_sms.len);
                        SetSendSMS(TRUE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
                    }
				#else
                    SetSendSMS(FALSE,  sys_rcv_sms.num, STR_SMS_DEFENSE_STOP_SUCCESS , NULL);
				#endif
                }
                else
                {
                    sprintf(sms_buf, "OK");
                    Send_Command_Message_Replay();
                }
            }
        }
        else
        {
            sprintf(sms_buf, "ERROR:123");   //�ն˴����Զ����ģʽ�������ֶ�����򳷷���
            Send_Command_Message_Replay();
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
		if((Command_State == AT_Command_State)
	#if defined(__AT_USE_UART1__)
		||(Command_State == UART1_Command_State)
	#endif
		)
        {
            strcat(sms_buf, ";000#");
        }
        Send_Command_Message_Replay();
    }
}

/******************************************************************************
 *  Function    -  Tracker_Set_Defense_Timer
 *
 *  Purpose     -  ���������ʱ����
 *
 *  Description -  DEFENSE,T#     1-60min, 0:���ùر����
 *                       DEFENSE#
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-20,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Defense_Timer(void)
{
    S16 Error;
    U16  interval;

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part > 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
		if((Command_State == AT_Command_State)
	#if defined(__AT_USE_UART1__)
		||(Command_State == UART1_Command_State)
	#endif
		)
        {
            strcat(sms_buf, ";DEFENSE,1#;DEFENSE#");
        }
        return;
    }

    if(received_data.part == 0)
    {
        sprintf(sms_buf, "DEFENSE:%d;", tracker_sensor_time.defence_start_time / 60000);
    }
    else if(received_data.part == 1)
    {
        interval = interval_Time_Manage(received_data.param0, 0, 60);   // ��λ:����

        if(interval == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
			if((Command_State == AT_Command_State)
		#if defined(__AT_USE_UART1__)
			||(Command_State == UART1_Command_State)
		#endif
			)
            {
                strcat(sms_buf, ";DEFENSE,1#");
            }
            return;
        }

        //���ùر����//�˳����
        if(interval == 0)
        {
            tracker_sensor_time.defence_start_time = 0;
            Bosch_Sensor_Defence_Stop();
        }
        else
        {
            tracker_sensor_time.defence_start_time = interval * 1000 * 60;

		#if defined(__ACC_DETECT__)
            //�Զ����ģʽ�Ž����
            if((tracker_sensor_time.detecttime != 0) && (tracker_acc_state == ACC_OFF) && (tracker_sensor_time.defencemode == 0) && (tracker_sensor_time.state == 1))
            {
                StopTimer(SENSOR_DEFENCE_START_TIMER);

                if(tracker_sensor_time.defence_start_time == 0)
                {
                    tracker_sensor_time.defence_start_time = 10 * 60 * 1000;
                }
                StartTimer(SENSOR_DEFENCE_START_TIMER, tracker_sensor_time.defence_start_time, Bosch_Sensor_Defence_Start);
            }
		#endif/*__ACC_DETECT__*/
		#if defined(__SENALM_NOT_ACC_DETECT__)//wnq	
            //�����ACC״̬,�Զ����ģʽ�Ž����
            if((tracker_sensor_time.detecttime != 0) && (tracker_sensor_time.defencemode == 0) && (tracker_sensor_time.state == 1))
            {
                StopTimer(SENSOR_DEFENCE_START_TIMER);

                if(tracker_sensor_time.defence_start_time == 0)
                {
                    tracker_sensor_time.defence_start_time = 10 * 60 * 1000;
                }
                StartTimer(SENSOR_DEFENCE_START_TIMER, tracker_sensor_time.defence_start_time, Bosch_Sensor_Defence_Start);
            }
		#endif/*__SENALM_NOT_ACC_DETECT__*/
        }

        WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, &tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &Error);
        LOGD(" %d", tracker_sensor_time.defence_start_time);
        sprintf(sms_buf, "OK");
    }

}

/******************************************************************************
 *  Function    -  Tracker_Set_Sensor_GPS_Time
 *
 *  Purpose     -  sensor�𶯺���GPS����ʱ��
 *
 *  Description -  SENDS,T#    T--(0--300MIN)   Ĭ��5���� 0 ��ʾGPS����
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-12-20, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Sensor_GPS_Time(void)
{
    S16 error;
    U16  interval = 0xffff;
    U8 interval_str[20];

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part > 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }

    if(received_data.part == 0)
    {
        sprintf(sms_buf, "SENDS:%d;", tracker_sensor_time.gpsworktime / 60000);
    }
    else if(received_data.part == 1)
    {
        memset(interval_str, 0, 20);
        memcpy(interval_str, received_data.param0, 20);

        interval = interval_Time_Manage(interval_str, 0 , 300);
        if(interval == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
            return ;
        }

        if(interval == 0)
        {
            tracker_sensor_time.gpsworktime = 0;

            //gps������Ҫ����GPS
            if(GPSOnFlag == FALSE)
            {
                GPS_ON();
            }
        }
        else
        {
            tracker_sensor_time.gpsworktime = interval * 60 * 1000;

			if(!IsMyTimerExist(GPS_OFF_TIMER_ID) && GPSOnFlag)
			{
				StartTimer(GPS_OFF_TIMER_ID, tracker_sensor_time.gpsworktime, GPS_OFF);
			}
        }

        WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, &tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &error);

	#if defined(__PARAM_BACKUP__)
        StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
	#endif

        sprintf(sms_buf, "OK");
    }
    LOGD("  time=%d", tracker_sensor_time.gpsworktime / 60 / 1000);


}





/******************************************************************************
 *  Function    -  Tracker_Set_Sensor_Detect_Time
 *
 *  Purpose     -  SENSOR�𶯼��ʱ��
 *
 *  Description -  SENSOR,T1,T2,T3#   T1(10-300S)  T2(10-300S)  T3(1--300MIN)
 *                        T1 ���ʱ�� T2 ������ʱʱ�� 10-300
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-12-20, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Sensor_Detect_Time(void)
{
    S16 error;
    U16  interval[3] = {0xffff, 0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[3][20];

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part != 0 && received_data.part != 2 && received_data.part != 3)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }


    if(received_data.part == 0)
    {
        sprintf(sms_buf, "SENSOR:%d,%d,%d;",
                tracker_sensor_time.detecttime / 1000,
                tracker_sensor_time.delayalarmtime / 1000,
                tracker_sensor_time.alarmintervaltime / 60000);

    }
    else if(received_data.part == 2 || received_data.part == 3)
    {
        memset(interval_str, 0, 60);
        memcpy(interval_str[0], received_data.param0, 20);
        memcpy(interval_str[1], received_data.param1, 20);
        memcpy(interval_str[2], received_data.param2, 20);

        for(i = 0; i < received_data.part; i++)
        {
            if(strlen((char*)interval_str[i]) == 0)
            {
                interval[i] = 0xffff;
                continue ;
            }

            if(i == 0 || i == 1)
            {
                interval[i] = interval_Time_Manage(interval_str[i], 10, 300);
            }
            else if(i == 2)
            {
                interval[i] = interval_Time_Manage(interval_str[i], 1, 300);
            }

            if(interval[i] == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");     //���ݳ�����Χ
                return;
            }
        }

        if(interval[0] != 0xffff)
        {
            tracker_sensor_time.detecttime =  interval[0] * 1000;
        }
        if(interval[1] != 0xffff)
        {
            tracker_sensor_time.delayalarmtime =  interval[1] * 1000;
        }
        if(interval[2] != 0xffff)
        {
            tracker_sensor_time.alarmintervaltime = interval[2] * 60 * 1000;
        }


        if(tracker_sensor_time.defence_start_time == 0)
        {
            tracker_sensor_time.defence_start_time = 10 * 60 * 1000;
        }

        WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, &tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &error);

	#if defined(__PARAM_BACKUP__)
        StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
	#endif

        //������𶯣������״̬�£�Ҫ����
        if((tracker_sensor_time.detecttime == 0) && (Defense_Switch == TRUE || tracker_sensor_time.defencestate != 0))
        {
            Bosch_Sensor_Defence_Stop();
        }

	#if defined(__ACC_DETECT__)
        else if((tracker_sensor_time.detecttime != 0) && (tracker_acc_state == ACC_OFF) && (tracker_sensor_time.state == 1) && (tracker_sensor_time.defence_start_time != 0))
        {
            StartTimer(SENSOR_DEFENCE_START_TIMER, tracker_sensor_time.defence_start_time, Bosch_Sensor_Defence_Start);
        }
	#endif
	#if defined(__SENALM_NOT_ACC_DETECT__)//wnq	
        //������û��ACC�������
        else if((tracker_sensor_time.detecttime != 0) && (tracker_sensor_time.state == 1) && (tracker_sensor_time.defence_start_time != 0))
        {
            StartTimer(SENSOR_DEFENCE_START_TIMER, tracker_sensor_time.defence_start_time, Bosch_Sensor_Defence_Start);
        }
	#endif/*__SENALM_NOT_ACC_DETECT__*/

        sprintf(sms_buf, "OK");
    }
    LOGD("  time=%d,%d", tracker_sensor_time.detecttime / 1000, tracker_sensor_time.delayalarmtime / 1000);

}


/******************************************************************************
 *  Function    -  Tracker_Bosch_Sensor_Alarm_Switch
 *
 *  Purpose     -  �𶯱�������
 *
 *  Description -  �񶯱������عر�ʱ�����������
 *                       �𶯱��������Ҫ����
 * modification history
 * ----------------------------------------
 * v1.0  ,
 *
 *  ָ��: SENALM,ON[,N]#         SENALM,OFF#   SENALM#
 *  ����: OK
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Bosch_Sensor_Alarm_Switch(void)
{
    S16 Error;
    U16  interval;
    if(received_data.part > 2)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
		if((Command_State == AT_Command_State)
	#if defined(__AT_USE_UART1__)
		||(Command_State == UART1_Command_State)
	#endif
		)
        {
            strcat(sms_buf, ";SENALM,ON/OFF#");
        }
        return;
    }

    if(received_data.part == 0)
    {
        if(tracker_sensor_time.state == 1)
        {
        	switch(tracker_sensor_time.alarmmode)
        	{
        	case SENSOR_GPRS_ONLY:
				sprintf(sms_buf, "SENALM:ON,GPRS;");
				break;
			case SENSOR_GPRS_SMS:
				sprintf(sms_buf, "SENALM:ON,GPRS+SMS;");
				break;
			case SENSOR_GPRS_SMS_CALL:
				sprintf(sms_buf, "SENALM:ON,GPRS+SMS+CALL;");
				break;
        	}
        }
        else
        {
            sprintf(sms_buf, "SENALM:OFF;");
        }
    }
    else if(received_data.part == 1)
    {
        if((strcmp((char *) received_data.param0, "ON") == 0) || (strcmp((char *) received_data.param0, "OFF") == 0))
        {
            if(strcmp((char *) received_data.param0, "ON") == 0)
            {
                tracker_sensor_time.state = 1;
                if(tracker_sensor_time.defence_start_time == 0)
                {
                    tracker_sensor_time.defence_start_time = 10 * 60 * 1000;
                }

			#if defined(__ACC_DETECT__)
                //��ACC �ǹر�״̬�����ý������״̬
                //ACC OFF ���Զ����ģʽ�Ž����
                if(tracker_acc_state == ACC_OFF && tracker_sensor_time.defencemode == 0)
                {
                    if((tracker_sensor_time.state == 1) && (tracker_sensor_time.defence_start_time != 0))
                    {
                        LOGD("  starttime:%d", tracker_sensor_time.defence_start_time / 60000);
                        StopTimer(SENSOR_DEFENCE_START_TIMER);
                        StartTimer(SENSOR_DEFENCE_START_TIMER, tracker_sensor_time.defence_start_time, Bosch_Sensor_Defence_Start);
                    }
                }
			#elif defined(__SENALM_NOT_ACC_DETECT__)//wnq
			#if defined(__BOSCH_BMA250E__)//wnq
                Bosch_Sensor_Init();
			#endif/*__BOSCH_BMA250E__*/

                //����ҪACC��鿪�����
                LOGD(" state:%d, defence_start_time:%d, defencemode:%d",  tracker_sensor_time.state, tracker_sensor_time.defence_start_time, tracker_sensor_time.defencemode);//wnq
                if((tracker_sensor_time.state == 1) && (tracker_sensor_time.defence_start_time != 0) && (tracker_sensor_time.defencemode == 0))
                {
                    LOGD("  starttime:%d", tracker_sensor_time.defence_start_time / 60000);
                    StopTimer(SENSOR_DEFENCE_START_TIMER);
                    StartTimer(SENSOR_DEFENCE_START_TIMER, tracker_sensor_time.defence_start_time, Bosch_Sensor_Defence_Start);
                }
			#endif/*__ACC_DETECT__*/
            }
            else
            {
			#if defined(__SENALM_NOT_ACC_DETECT__) && defined(__BOSCH_BMA250E__)//wnq
                //�Զ�����ģʽ���˳����ֶ����˳�
                //if(tracker_sensor_time.defencemode == 0)
                {
                    Bosch_Sensor_Defence_Cancel();
                    Bosch_Sensor_Off();
                }
			#endif/*__SENALM_NOT_ACC_DETECT__*/

                tracker_sensor_time.state = 0;
                tracker_sensor_time.defencestate = 0;
                Defense_Switch = FALSE;
                if(IsMyTimerExist(SENSOR_DEFENCE_START_TIMER))
                {
                    StopTimer(SENSOR_DEFENCE_START_TIMER);
                }
            }
		#if defined(__LED_APP__)
            if(tracker_ctrl_data.keystate == 1)
            {
                if(GPSOnFlag)
                {
                    if(Defense_Switch == TRUE)
                    {
                        LED_Defense_Indicate();
                    }
                    else
                    {
                        LED_HW_Init();
                    }
                }
                else
                {
                    if(tracker_ctrl_data.led_sleep == 0)
                    {
                        LED_HW_Init();
                    }
                    else
                    {
                        LED_Stop();
                    }
                }
            }
		#endif

            sprintf(sms_buf, "OK");
            WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, (void *)&tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &Error);
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
			if((Command_State == AT_Command_State)
		#if defined(__AT_USE_UART1__)
			||(Command_State == UART1_Command_State)
		#endif
			)
            {
                strcat(sms_buf, ";SENALM,ON /OFF");
            }
        }
    }
    else   //SENALM,ON,1#
    {
        if(strcmp((char *) received_data.param0, "ON") == 0)
        {
            interval = interval_Time_Manage(received_data.param1, 0, 2);
            if(interval == 0xffff)
            {
                sprintf(sms_buf, "ERROR:102");
                return;
            }
            tracker_sensor_time.state = 1;
            tracker_sensor_time.alarmmode = interval;
            if(tracker_sensor_time.defence_start_time == 0)
            {
                tracker_sensor_time.defence_start_time = 10 * 60 * 1000;
            }

            //��ACC �ǹر�״̬�����ý������״̬

		#if defined(__ACC_DETECT__)
            LOGD(" acc:%d,state:%d,time:%d,%d,mode:%d", tracker_acc_state, tracker_sensor_time.state, tracker_sensor_time.defence_start_time / 60000, IsMyTimerExist(SENSOR_DEFENCE_START_TIMER), tracker_sensor_time.defencemode);

            if(tracker_acc_state == ACC_OFF && tracker_sensor_time.defencemode == 0)
            {
                if((tracker_sensor_time.state == 1) && (tracker_sensor_time.defence_start_time != 0))
                {
                    LOGD("  starttime :%d", tracker_sensor_time.defence_start_time / 60000);
                    StopTimer(SENSOR_DEFENCE_START_TIMER);
                    StartTimer(SENSOR_DEFENCE_START_TIMER, tracker_sensor_time.defence_start_time, Bosch_Sensor_Defence_Start);
                }
            }
		#elif defined(__SENALM_NOT_ACC_DETECT__)//wnq
            LOGD("state:%d, defence_start_time:%d, mode:%d",  tracker_sensor_time.state, tracker_sensor_time.defence_start_time / 60000, tracker_sensor_time.defencemode);//wnq

		#if defined(__BOSCH_BMA250E__)//wnq
            Bosch_Sensor_Init();
		#endif/*__BOSCH_BMA250E__*/

            if((tracker_sensor_time.state == 1) && (tracker_sensor_time.defence_start_time != 0) && (tracker_sensor_time.defencemode == 0))
            {
                LOGD("  starttime :%d", tracker_sensor_time.defence_start_time / 60000);
                StopTimer(SENSOR_DEFENCE_START_TIMER);
                StartTimer(SENSOR_DEFENCE_START_TIMER, tracker_sensor_time.defence_start_time, Bosch_Sensor_Defence_Start);
            }
		#endif/*__ACC_DETECT__*/

		#if defined(__LED_APP__)
            if(tracker_ctrl_data.keystate == 1)
            {
                if(GPSOnFlag)
                {
                    if(Defense_Switch == TRUE)
                    {
                        LED_Defense_Indicate();
                    }
                    else
                    {
                        LED_HW_Init();
                    }
                }
                else
                {
                    if(tracker_ctrl_data.led_sleep == 0)
                    {
                        LED_HW_Init();
                    }
                    else
                    {
                        LED_Stop();
                    }
                }
            }
		#endif
            sprintf(sms_buf, "OK");
            WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, (void *)&tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &Error);

        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
        }
    }

}



/******************************************************************************
 *  Function    -  Tracker_Bosch_Sensor_Alarm_Param
 *
 *  Purpose     -  �𶯱�������
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  ,
 *
 *  ָ��: //SENSORALM,<A>,<B>,<C>[,D]#
 *  ��Ϊ: SENSORSET,<A>,<B>,<C>[,D]#
 *                  A=10-300�룻SENSOR���ʱ�䷶Χ��Ĭ��ֵ��10��
 *                  B=1-20�Σ��𶯼���GPS������������:Ĭ��ֵ:1��
 *                 C=1-20; �𶯱��������������ޣ�Ĭ��ֵ:5��
 *                  D=1-3�룻SENSOR�����(��)��Ĭ��1
 *                  ����������//A��B*2(C-1)
 *                  A>=C*D >=B*D
 *                  SENSORSET#  ��ѯ���õ��𶯱�����������
 *
 *  ����:
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Bosch_Sensor_Alarm_Param(void)
{
    S16 error;
    U16 timetemp = 0;
    U16  interval[4] = {0xffff, 0xffff, 0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[4][20];
    char temp[300];

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part == 0)
    {
        memset(temp, 0, 300);
        sprintf(temp, "SENSORSET:%d,%d,%d,%d;",
                tracker_sensor_time.detecttime / 1000,
                tracker_sensor_time.activegpsnum,
                tracker_sensor_time.detectnum,                    //tracker_sensor_time.delayalarmtime / 1000
                tracker_sensor_time.detect_interval / 1000);
        strcpy((char*)sms_buf, (char*)temp);
    }
    else if((received_data.part == 3) || (received_data.part == 4))
    {
        memset(interval_str, 0, 80);
        memcpy(interval_str[0], received_data.param0, 20);
        memcpy(interval_str[1], received_data.param1, 20);
        memcpy(interval_str[2], received_data.param2, 20);
        memcpy(interval_str[3], received_data.param3, 20);

        for(i = 0; i < received_data.part; i++)
        {
            if(strlen((char*)interval_str[i]) == 0)
            {
                if(i == 0)
                {
                    interval[i] = tracker_sensor_time.detecttime / 1000;
                }
                else if(i == 1)
                {
                    interval[i] = tracker_sensor_time.activegpsnum;
                }
                else if(i == 2)
                {
                    interval[i] = tracker_sensor_time.detectnum;
                }
                else if(i == 3)
                {
                    interval[i] = tracker_sensor_time.delayalarmtime / 1000;
                }
                continue ;
            }

            if(i == 0)
            {
                interval[i] = interval_Time_Manage(interval_str[i], 10, 300);
            }
            else if(i == 1)
            {
                interval[i] = interval_Time_Manage(interval_str[i], 1, 20);
            }
            else if(i == 2)
            {
                interval[i] = interval_Time_Manage(interval_str[i], 1, 20);
            }
            else if(i == 3)
            {
                interval[i] = interval_Time_Manage(interval_str[i], 1, 3);
            }

            if(interval[i] == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return;
            }
        }

        //A>=C*D >=B*D
        if((interval[0] >= interval[2]*interval[3]) && (interval[2] >= interval[1]))
        {
            tracker_sensor_time.detecttime = interval[0] * 1000;
            tracker_sensor_time.activegpsnum = interval[1];
            tracker_sensor_time.detectnum = interval[2];
            tracker_sensor_time.detect_interval =  interval[3] * 1000;

            WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, &tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
        else
        {
            //A<C*D  A>=B*D
            if((interval[0] < interval[2]*interval[3]) && (interval[0] >= interval[1]*interval[3]))
            {
                sprintf(sms_buf, "ERROR:120");
            }
            //C<B  A>=B*D
            else if((interval[0] >= interval[1]*interval[3]) && (interval[2] < interval[1]))
            {
                sprintf(sms_buf, "ERROR:121");
            }
            else
            {
                sprintf(sms_buf, "ERROR:101");
            }
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");
    }
}



/******************************************************************************
 *  Function    -  Tracker_Set_Sensor_Level
 *
 *  Purpose     -  SENSOR�����ȵȼ�
 *
 *  Description -  LEVEL,N#      1~5 Ĭ��2 //N--1~255  Ĭ��:16
 *                       LEVEL#
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Sensor_Level(void)
{
    S16 error;
    U16 interval = 0xffff;
    U8 interval_str[20];

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part > 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }

    if(received_data.part == 0)
    {
        sprintf(sms_buf, "LEVEL:%d;", tracker_sensor_time.sensitivity_level);
    }
    else if(received_data.part == 1)
    {
        memset(interval_str, 0, 20);
        memcpy(interval_str, received_data.param0, 20);

        interval = interval_Time_Manage(interval_str, 1, 4);
        if(interval == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
            return ;
        }
        tracker_sensor_time.sensitivity_level = interval;

        if(tracker_sensor_time.sensitivity_level == 1)
        {
            Gsensor_Duration = 1;
            Gsensor_Threshold = 6;
        }
        else if(tracker_sensor_time.sensitivity_level == 2)
        {
            Gsensor_Duration = 2;
            Gsensor_Threshold = 10;
        }
        else if(tracker_sensor_time.sensitivity_level == 3)
        {
            Gsensor_Duration = 3;
            Gsensor_Threshold = 18;
        }
        else if(tracker_sensor_time.sensitivity_level == 4)
        {
            Gsensor_Duration = 4;    //3
            Gsensor_Threshold = 32;
        }
		else if(tracker_sensor_time.sensitivity_level == 5)
		{
            Gsensor_Duration = 5;    //3
            Gsensor_Threshold = 64;
		}
        else
        {
            Gsensor_Duration = 2;   //4
            Gsensor_Threshold = 10;
        }

        WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, &tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &error);

	#if defined(__PARAM_BACKUP__)
        StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
	#endif
        sprintf(sms_buf, "OK");
    }
    LOGD("  sensitivity_level=%d", tracker_sensor_time.sensitivity_level);
}




/******************************************************************************
 *  Function    -  Tracker_Set_Static_Send_LastGPS
 *
 *  Purpose     -  ����SENSOR��⵽��ֹ���ϴ�GPS���һ��λ��
 *
 *  Description -   STATICREP,ON,T,V,N#
                           T   ��ֹʱ�����:10--300S  Ĭ��:20
                           ��С�ٶȷ�Χ: 0-100KM/h  Ĭ��:6km/h
                           ������ : 1--20    Ĭ��:3
 *                        STATICREP,OFF#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2013-09-29, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Static_Send_LastGPS(void)
{
    S16 error;
    U16  interval[3] = {0xffff, 0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[3][20];


    memset(sms_buf, 0, sizeof(sms_buf));
    LOGD(" %s", received_data.param0);

    if(received_data.part == 0)
    {
        if(tracker_sensor_time.staticsendlaststate == 1)
        {
            sprintf(sms_buf, "STATICREP:ON,%d,%d,%d;", tracker_sensor_time.statictime / 1000, tracker_sensor_time.staticminspeed, tracker_sensor_time.staticdetecttimes);
        }
        else
        {
            sprintf(sms_buf, "STATICREP:OFF;");
        }
    }
    else if(strcmp("ON", ((char *)received_data.param0)) == 0)
    {
        if(received_data.part > 4)
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        if(received_data.part == 1)
        {
            tracker_sensor_time.staticsendlaststate = 1;
        }
        else
        {
            memset(interval_str, 0, 60);
            memcpy(interval_str[0], received_data.param1, 20);
            memcpy(interval_str[1], received_data.param2, 20);
            memcpy(interval_str[2], received_data.param3, 20);

            for(i = 0; i < received_data.part - 1; i++)
            {
                if(strlen((char*)interval_str[i]) == 0)
                {
                    interval[i] = 0xffff;
                    continue ;
                }

                if(i == 0)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 10, 300);
                }
                else if(i == 1)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 0, 100);
                }
                else if(i == 2)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 1, 20);
                }


                if(interval[i] == 0xffff)
                {
                    sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                    return;
                }
            }

            tracker_sensor_time.staticsendlaststate = 1;
            if(interval[0] != 0xffff)
            {
                tracker_sensor_time.statictime =  interval[0] * 1000;
            }
            if(interval[1] != 0xffff)
            {
                tracker_sensor_time.staticminspeed =  interval[1];
            }
            if(interval[2] != 0xffff)
            {
                tracker_sensor_time.staticdetecttimes =  interval[2];
            }
        }

        WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, &tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else if(strcmp("OFF", ((char *)received_data.param0)) == 0)
    {
        if(received_data.part != 1)
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        tracker_sensor_time.staticsendlaststate = 0;
        WriteRecord(NVRAM_EF_TRACKER_SENSOR_TIME_LID, 1, &tracker_sensor_time, NVRAM_EF_TRACKER_SENSOR_TIME_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
    }

}



/******************************************************************************
 *  Function    -  Tracker_Defences_Reset
 *
 *  Purpose     -  �������״̬
 *
 *  Description -  DSRESET#
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
  * ----------------------------------------
 ******************************************************************************/
void Tracker_Defences_Reset(void)
{
    S16 error;

    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");//ָ������ֶζ�������ȷ
    }
    else
    {
        Bosch_Sensor_Defence_Stop();
        sprintf(sms_buf, "OK");
    }
}
#endif

/******************************************************************************
 *  Function    -  Tracker_At_Vibrateor
 *
 *  Purpose     -  ָ��򿪹ر���
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-06-14, guojie  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_At_Vibrateor(void)
{  
   char buffer[128] = {0};
   static kal_bool is_vibrator_test_on =KAL_FALSE;

    is_vibrator_test_on =!is_vibrator_test_on;
    if(is_vibrator_test_on)
    {
    	srv_vibrator_on();
		sprintf(buffer, "Vibrator ON");
    }
	else
	{
		srv_vibrator_off();
		sprintf(buffer, "Vibrator OFF");
	}
	rmmi_write_to_uart((kal_uint8*)buffer, strlen(buffer), KAL_TRUE);
}

#ifdef __KJX_RFID__
/******************************************************************************
 *  Function    -  Tracker_RFID_Set
 *
 *  Purpose     -  rfid����
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-06-14, xiebiao written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_RFID_Set(void)
{
	memset(sms_buf, 0, sizeof(sms_buf));

	if(received_data.part > 1)
	{
		sprintf(sms_buf, "ERROR:100");	 //ָ��Ȳ���ȷ
		return;
	}

	if(received_data.part == 1)
	{
		if(strcmp((const char*)received_data.param0, "ON") == 0)
		{
			if(g_kjx_nvram_struct.rfidflag == 0)
			{
				g_kjx_nvram_struct.rfidflag = 1;
				kjx_rfid_init();
				kjx_nvram_write();
			}
			sprintf(sms_buf, "OK, RFID turn on!");
		}
		else if(strcmp((const char*)received_data.param0, "OFF") == 0)
		{
			if(g_kjx_nvram_struct.rfidflag == 1)
			{
				g_kjx_nvram_struct.rfidflag = 0;
				kjx_rfid_off();
				kjx_nvram_write();
			}
			sprintf(sms_buf, "OK, RFID turn off!");
		}
		else
		{
			sprintf(sms_buf, "ERROR:102");	 //���ݳ�����Χ
		}
	}
	else if(received_data.part == 0)   //������������ѯ״̬
	{
		if(g_kjx_nvram_struct.rfidflag == 1)
		{
			sprintf(sms_buf, "RFID: ON");
		}
		else
		{
			sprintf(sms_buf, "RFID: OFF");
		}
	}
}
#endif

#ifdef __BLE_MODULE_SUPPORT__
/******************************************************************************
 *  Function    -  Tracker_BLE_iBeacom_Set
 *
 *  Purpose     -  iBeacon����
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-06-14, xiebiao written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_BLE_iBeacom_Set(void)
{
	memset(sms_buf, 0, sizeof(sms_buf));

	if(received_data.part > 1)
	{
		sprintf(sms_buf, "ERROR:100");	 //ָ��Ȳ���ȷ
		return;
	}

	if(received_data.part == 1)
	{
		if(strcmp((const char*)received_data.param0, "ON") == 0)
		{
			if(g_kjx_nvram_struct.btflag == 0)
			{
				g_kjx_nvram_struct.btflag = 1;
				kjx_bt_ibeacon_init();
				kjx_nvram_write();
			}
			sprintf(sms_buf, "OK, BLE turn on!");
		}
		else if(strcmp((const char*)received_data.param0, "OFF") == 0)
		{
			if(g_kjx_nvram_struct.btflag == 1)
			{
				g_kjx_nvram_struct.btflag = 0;
				kjx_bt_ibeacon_off();
				kjx_nvram_write();
			}
			sprintf(sms_buf, "OK, BLE turn off!");
		}
		else
		{
			sprintf(sms_buf, "ERROR:102");	 //���ݳ�����Χ
		}
	}
	else if(received_data.part == 0)   //������������ѯ״̬
	{
		if(g_kjx_nvram_struct.btflag == 1)
		{
			sprintf(sms_buf, "BLE: ON");
		}
		else
		{
			sprintf(sms_buf, "BLE: OFF");
		}
	}
}
#endif

#if defined(__KJX_FUN_SENSOR__)
/******************************************************************************
 *  Function    -  Tracker_Sensor_Set
 *
 *  Purpose     -  ��������������
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2018-08-27, xiebiao written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Sensor_Set(void)
{
	memset(sms_buf, 0, sizeof(sms_buf));

	if(received_data.part > 1)
	{
		sprintf(sms_buf, "ERROR:100");	 //ָ��Ȳ���ȷ
		return;
	}

	if(received_data.part == 1)
	{
		if(strcmp((const char*)received_data.param0, "ON") == 0)
		{
			sprintf(sms_buf, "OK, Sensor turn on!");
		}
		else if(strcmp((const char*)received_data.param0, "OFF") == 0)
		{
			sprintf(sms_buf, "OK, Sensor turn off!");
		}
		else if(strcmp((const char*)received_data.param0, "RESET") == 0)
		{
			kjx_sensor_reset();
			
			sprintf(sms_buf, "OK, Sensor reset!");
		}
		else
		{
			sprintf(sms_buf, "ERROR:102");	 //���ݳ�����Χ
		}
	}
	else if(received_data.part == 0)   //������������ѯ״̬
	{
		sprintf(sms_buf, "Sensor: ON");
	}
}
#endif

#if defined(__KJX_FUN_GPS__)
#ifndef KJX_TEST
/******************************************************************************
 *  Function    -  Tracker_Send_DW_QuerySMS
 *
 *  Purpose     -  ��ѯ�ն�λ��
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-06-14, guojie  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Send_DW_QuerySMS(void)
{
#if defined(__SMS_APP_DEBUG__)
    LOGD(" num:%s,%d", sys_rcv_sms.num, DWQuery);
#endif

    if(IsMyTimerExist(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER))
    {
        StopTimer(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER);
    }
    if(DWQuery != 0)
    {
        Tracker_Reback_Address_URL((U8*)sys_rcv_sms.num);
        DWQuery = 0;
    }
}

/******************************************************************************
 *  Function    -  Tracker_Send_WHERE_QuerySMS
 *
 *  Purpose     -  ����WHERE ��ѯ��ַ
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-11, guojie  written
  * ----------------------------------------
 ******************************************************************************/
void Tracker_Send_WHERE_QuerySMS(void)
{
    U8 len = 0;
    S8 dir[2];
    S8 temp[30];
    S8 STR_D[50];//�洢�ȵ��ַ���
    S8 STR_M[50];//����ֵ��ַ���
    S8 *STR_D_P, *STR_M_P;
    double  DATA_M, DATA_D;//�����ת���� �������ı���

    if(IsMyTimerExist(SMS_SEND_MANY_DELAY_GPS_ID))
    {
        StopTimer(SMS_SEND_MANY_DELAY_GPS_ID);
    }

    memset(sys_send_sms.content, 0, sizeof(sys_send_sms.content));

    if(GPSCurrentLocation == TRUE)
    {
		sprintf((char *)sys_send_sms.content, "Current position!");
        strcat((char *)sys_send_sms.content, "Lat:");

        memset(temp, 0, 30);
        dir[0] = (Last_valide_data.location_info.direct & 0x0f) + GPS_LOCATION_DIR_BAS;
        len = strlen((char *)sys_send_sms.content);
        sys_send_sms.content[len] = dir[0];
        //γ��
        memset(STR_D, 0, sizeof(STR_D));
        memset(STR_M, 0, sizeof(STR_M));
        STR_D_P = strstr((char *)Last_valide_data.location_info.latitude, "d");
        memcpy(STR_D, (char *)Last_valide_data.location_info.latitude, STR_D_P - (char *)Last_valide_data.location_info.latitude);
        STR_M_P = strstr((char *) STR_D_P, "m");
        memcpy(STR_M, STR_D_P + 2, STR_M_P - STR_D_P - 2);
        DATA_M = atof(STR_M) / 60;
        DATA_D = atof(STR_D);
        sprintf(STR_D, "%f", DATA_D + DATA_M);
        strcat((char *)sys_send_sms.content, (char *)STR_D);

        //����
        strcat((char *)sys_send_sms.content, ",Lon:");

        if((Last_valide_data.location_info.direct >> 4) == 1)
            dir[1] = 'E';
        else
            dir[1] = ((Last_valide_data.location_info.direct & 0xf0) >> 4) + GPS_LOCATION_DIR_BAS;
        len = strlen((char *)sys_send_sms.content);
        sys_send_sms.content[len] = dir[1];

        memset(STR_D, 0, sizeof(STR_D));
        memset(STR_M, 0, sizeof(STR_M));
        STR_D_P = strstr((char *)(char *)Last_valide_data.location_info.longtitude, "d");
        memcpy(STR_D, (char *)(char *)Last_valide_data.location_info.longtitude, STR_D_P - (char *)(char *)Last_valide_data.location_info.longtitude);
        STR_M_P = strstr((char *) STR_D_P, "m");
        memcpy(STR_M, STR_D_P + 2, STR_M_P - STR_D_P - 2);

        DATA_M = atof(STR_M) / 60;
        DATA_D = atof(STR_D);
        sprintf(STR_D, "%f", DATA_D + DATA_M);
        strcat((char *)sys_send_sms.content, (char *)STR_D);

        //�Ƕ�
        memset(temp, 0, 30);
        sprintf((char *)temp, ",Course:");
        strcat((char *)sys_send_sms.content, (char *)temp);
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.location_info.course);

        //�ٶ�
        memset(temp, 0, 30);
        sprintf((char *)temp, ",Speed:");
        strcat((char *)sys_send_sms.content, (char *)temp);
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.location_info.speed);

        //ʱ��
        memset(temp, 0, 30);
        sprintf((char *)temp, ",DateTime:");
        strcat((char *)sys_send_sms.content, (char *)temp);
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.year);
        len = strlen((char *)sys_send_sms.content);
        sys_send_sms.content[len] = '-';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.month);
        sys_send_sms.content[len+3] = '-';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.day);
        sys_send_sms.content[len+6] = ' ';
        sys_send_sms.content[len+7] = ' ';

        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.hour);
        len = strlen((char *)sys_send_sms.content);
        sys_send_sms.content[len] = ':';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.minute);
        sys_send_sms.content[len+3] = ':';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.second);

        sys_send_sms.len = strlen((char *)sys_send_sms.content);

    	if(strlen((char*)sys_rcv_sms.num))
    	{
    	#if defined(__STACK_SENDSMS__)
	        SetSendSMS(TRUE, sys_rcv_sms.num, 0, sys_send_sms.content);
		#else
	    	Tracker_Send_Ascii_Msg((U8*)sys_rcv_sms.num , (void*)sys_send_sms.content);
		#endif
	    }
	    else
	    {
			strcpy((char*)sms_buf, sys_send_sms.content);
            Send_Command_Message_Replay();
	    }	
    }
    else
    {
		if(strlen((char*)sys_rcv_sms.num))
        {
		#if defined(__STRING_USE_ARRAY__)
	        memset(&sys_send_sms, 0, sizeof(SYS_SMS_STRUCT));
	        if(CurrentLang == 1)
	        {
	            //����ȡ�ĳ��ȸ�ʵ�ʳ��Ȳ�һ�»�����
	            sys_send_sms.len = app_ucs2_strlen((char *)gps_noLocation_code[1]) * 2;
	            memcpy(sys_send_sms.content, &gps_noLocation_code[1], sys_send_sms.len);
	            SetSendSMS(FALSE, sys_rcv_sms.num, NULL, sys_send_sms.content);
	        }
	        else
	        {
	            sys_send_sms.len = strlen((char *)gps_noLocation_code[0]);
	            memcpy(sys_send_sms.content, &gps_noLocation_code[0], sys_send_sms.len);
	            SetSendSMS(TRUE, sys_rcv_sms.num, NULL, sys_send_sms.content);
	        }
		#else
	        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_GPS_NO_LOCATION, NULL);
		#endif
		}
		else
		{
			strcpy((char*)sms_buf, "GPS Not Location!");
            Send_Command_Message_Replay();
		}
    }	
    WhereQuery = FALSE;
}


/******************************************************************************
 *  Function    -  Tracker_Send_URL_QuerySMS
 *
 *  Purpose     -  ��ѯ�ն�λ��
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 04-26-2011, guojie  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Send_URL_QuerySMS(void)
{
#if defined(__SMS_APP_DEBUG__)
    LOGD("Tracker_Send_URL_QuerySMS");
#endif

    if(IsMyTimerExist(SMS_SEND_MANY_DELAY_GPS_ID))
    {
        StopTimer(SMS_SEND_MANY_DELAY_GPS_ID);
    }

    Tracker_Reback_Address_URL((U8*)sys_rcv_sms.num);
    URLQuery = FALSE;
}


/******************************************************************************
 *  Function    -  Tracker_Query_Address_SocConnect_Fail_SendSMS
 *
 *  Purpose     -  DW��ѯLBS��ַʧ�ܻظ���Ϣ
 *
 *  Description -  LBS�汾(��������2��):δ�鵽���ݣ�������!
 *                       GPS�汾:
 *                       ��λ:
 *                 δ��λ:GPSδ��λ!
 * modification history
 *  �ظ���3��:
 *  1.GPRS���������� ������GPSδ��λ����ʱδ��ȡ��λ�ã��ظ�����:
 *                  δ�鵽���ݣ������ԣ�
 *  2.GPRS �����쳣��GPS��λ���ظ�����:
 *                  http://maps.google.com/maps?q=N22.543419,E113.92093
 *  2.GPRS�����쳣,GPSδ��λ���ظ�����:
 *                  GPSδ��λ!
 * ----------------------------------------
 * v1.0  , 2011-11-09, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Query_Address_SocConnect_Fail_SendSMS(void)
{
    if(tracker_ctrl_data.GPRSAlwaysOn == 2)
    {
        Flag_ReqGPRS = Flag_ReqGPRS & 0x0F;
	#if defined (__GPS_ON_MTK__)
        GPS_have_Location = FALSE;
	#endif
        Tracker_Socket_TCP_Close();
    }

#if defined (__GPS_ON_MTK__)
    LOGD("SocConnect_Fail_SendSMS %d,%d", soc_content.soc_state, GPSCurrentLocation);
#endif

    if(DWQuery)
    {
        DWQuery = 0;
        memset((char *)sys_send_sms.content , 0, 320);

        if(soc_content.soc_state >= SOC_CONNECTED)
        {
            SetSendSMS(FALSE, sys_rcv_sms.num, STR_GET_ADDRESS_FAIL, NULL);
        }
        else
        {
            if(GPSCurrentLocation)
            {
                Tracker_Reback_Address_URL(sys_rcv_sms.num);
                if(GPSOnFlag == FALSE)
                {
                    GPSCurrentLocation = FALSE;
                }
            }
            else
            {
                //��Ҫ����ʱ�������߲���λ�ظ�
                if(tracker_ctrl_data.GPRSAlwaysOn == 2 || tracker_ctrl_data.GPRSAlwaysOn == 0)
                {
                    SetSendSMS(FALSE, sys_rcv_sms.num, STR_GET_ADDRESS_FAIL, NULL);
                }
                else
                {
                    SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_GPS_NO_LOCATION, NULL);
                }
            }
        }
    }
}


/*---------------------------------------------------------------------------
 * FUNCTION			Tracker_Qurey_GetLBS_Address_Fail_SendSMS
 *
 * DESCRIPTION		DW��ѯLBS��ַʧ�ܻظ���Ϣ
 *
 * PARAMETERS
 *		kal_bool          ����: δ�鵽���ݣ������ԣ�
 * RETURNS                   Ӣ��:Not get address data, please try again!
 *  		void                1.�����ӣ�����������ʱδ��ȡ��λ��(GPSδ��λ)
 *                                  2.�����ӣ�(GPSδ��λ)
 *                                  3.�رգ�(GPSδ��λ)
 * ----------------------------------------
 * v1.0  , 22-12-2010,  guojie  written
 * ----------------------------------------
 *---------------------------------------------------------------------------*/
static void Tracker_Qurey_GetLBS_Address_Fail_SendSMS(void)
{
#if defined(__SMS_APP_DEBUG__)
	LOGD("begin");
#endif

    if(tracker_ctrl_data.GPRSAlwaysOn == 2)
    {
        Flag_ReqGPRS = Flag_ReqGPRS & 0x0F;
	#if defined (__GPS_ON_MTK__)
        GPS_have_Location = FALSE;
	#endif
        Tracker_Socket_TCP_Close();
    }

    if((tracker_ctrl_data.GPRSAlwaysOn == 1) && (soc_content.soc_state == SOC_CONNECTED))
    {
	#if defined (__GPS_ON_MTK__)
        if(DWQuery)
        {
            DWQuery = 0;

		#if defined(__STACK_SENDSMS__)
            SetSendSMS(FALSE, sys_rcv_sms.num, STR_GET_ADDRESS_FAIL, NULL);
		#else
            Tracker_Send_String_SMS(STR_GET_ADDRESS_FAIL, (char *)sys_rcv_sms.num);
		#endif
        }
	#else
        if(DWQuery)
        {
            DWQuery = 0;
		#if defined(__STACK_SENDSMS__)
            SetSendSMS(FALSE, sys_rcv_sms.num, STR_GET_ADDRESS_FAIL, NULL);
		#else
			Tracker_Send_String_SMS(STR_GET_ADDRESS_FAIL, (char *)sys_rcv_sms.num);
		#endif
        }
	#endif/*__GPS_ON_MTK__*/
    }
    else
    {
        //Tracker_Query_Address_SocConnect_Fail_SendSMS();
        if(DWQuery)
        {
            DWQuery = 0;
		#if defined(__STACK_SENDSMS__)
            SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_GPS_NO_LOCATION, NULL);
		#else
			Tracker_Send_String_SMS(STR_SMS_GPS_NO_LOCATION, (char *)sys_rcv_sms.num);
		#endif
        }
    }
}


/*---------------------------------------------------------------------------
 * FUNCTION			Tracker_Qurey_Get_Address_Fail_SendSMS
 *
 * DESCRIPTION		DW��ѯGPS��ַʧ�ܻظ���Ϣ
 *
 * PARAMETERS
 *		kal_bool
 * RETURNS
 *  		void                1.�����ӣ�����������ʱδ��ȡ��λ��(GPSδ��λ)
 *                                  2.�����ӣ�(GPSδ��λ)
 *                                  3.�رգ�(GPSδ��λ)
 * ----------------------------------------
 * v1.0  , 22-12-2010,  guojie  written
 * ----------------------------------------
 *---------------------------------------------------------------------------*/
void Tracker_Qurey_Get_Address_Fail_SendSMS(void)
{
#if defined(__SMS_APP_DEBUG__)
	LOGD("begin");
#endif

    StopTimer(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER);

    if(DWQuery)
    {
        if(GPSCurrentLocation)
        {
			DWQuery = 0;

            Tracker_Reback_Address_URL(sys_rcv_sms.num);
        }
        else
        {
        	if((tracker_ctrl_data.GPRSAlwaysOn == 1) && (soc_content.soc_state >= SOC_CONNECTED))
        	{
        		Tracker_Query_GetLBS_Address();
        	}
			else
			{
				DWQuery = 0;
				
			#if defined(__STACK_SENDSMS__)
	            SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_GPS_NO_LOCATION, NULL);
			#else
				Tracker_Send_String_SMS(STR_SMS_GPS_NO_LOCATION, (char *)sys_rcv_sms.num);
			#endif
			}
        }
    }
}


/******************************************************************************
 *  Function    -  Tracker_Get_Address_SendSMS
 *
 *  Purpose     -  �ظ����ĵ�ַ����
 *
 *  Description -  SOS�����ѯ��DWλ�ò�ѯ�ظ�
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 15-09-2010,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Get_Address_SendSMS(void)
{
    int i = 0;
    int NumLen = 0;
    U8 phbNumIndex = 0;
    char phone_num[21];
    U8 FindZero = 0xFF;
    U8 ZeroNumber = 0;

    Command_State = SMS_Command_State;
    memset(sys_send_sms.num, 0, FAMILY_PHB_NUM_LEN_MIN);

    NumLen = strlen((char *)received_data.param1);

    //�������·��ĺ���Ϊ 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30 0x30
    //000 000 000 000 000 000 000
    //000000000000000000000
    if(NumLen == 21)
    {
        for(i = 0; i < NumLen; i++)
        {
            if(received_data.param1[i] == 0x30)
            {
                ZeroNumber ++;
            }
        }

        if(NumLen == ZeroNumber)
        {
            memset(received_data.param1, 0, sizeof(received_data.param1));
            NumLen = 0;
        }
    }

    //����̺Ų��ظ���ַ
    //685080 (363835303830000000000000000000000000000000)
    LOGD(" %d,%d", FindZero, NumLen);

    if(NumLen == 0)
    {
        //��GPRS����״̬����Ҫ�ظ���Ϣ
        //SOS���ϵ硢Χ�����𶯡�λ�ơ�����
        if(IsMyTimerExist(SOS_CALL_QUERY_ADDRESS_OVER_TIMER))
        {
            StopTimer(SOS_CALL_QUERY_ADDRESS_OVER_TIMER);
        }
	#if defined(__CUT_POWER_ALARM__)
        if(IsMyTimerExist(TRACKER_POWER_CUT_QUERY_ADRESS_OVER_TIMER))
        {
            StopTimer(TRACKER_POWER_CUT_QUERY_ADRESS_OVER_TIMER);
        }
	#endif
	#if defined(__GPS_FENCE__)
        if(IsMyTimerExist(TRACKER_FENCE_QUERY_ADDRESS_OVER_TIMER))
        {
            StopTimer(TRACKER_FENCE_QUERY_ADDRESS_OVER_TIMER);
        }
	#endif
	#if defined(__BOSCH_BMA250E__)
        if(IsMyTimerExist(SENSOR_SHAKE_ALRAM_OVERTIME_TIMER))
        {
            StopTimer(SENSOR_SHAKE_ALRAM_OVERTIME_TIMER);
        }
	#endif
	#if defined(__MOVING_ALARM__)
        if(IsMyTimerExist(SHIFT_QUERY_ADDRESS_OVER_TIMER))
        {
            StopTimer(SHIFT_QUERY_ADDRESS_OVER_TIMER);
        }
	#endif
	#if defined(__GPS_OVERSPEED__)
        if(IsMyTimerExist(OVERSPEED_QUERY_ADDRESS_OVER_TIMER))
        {
            StopTimer(OVERSPEED_QUERY_ADDRESS_OVER_TIMER);
        }
	#endif
        memcpy(sys_send_sms.num, sys_rcv_sms.num, 21);
    }
    else   //�к���GPS_PHB��ѯ
    {
        if(IsMyTimerExist(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER))
        {
            StopTimer(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER);
        }

        //��ʱ�ն˻��Ϸ����������ַ��
        if(DWQuery == 0)
        {
            LOGD(" DWQuery==0");
            return;
        }

        if(DWQuery)
        {
            memcpy(sys_send_sms.num, received_data.param1, 21);
            DWQuery = 0;
        }

    }

    memset((char *)sys_send_sms.content, 0, 320);

    if(GetAddressLen % 2)
    {
        GetAddressLen = GetAddressLen + 1;
    }

    //��ַ�ߵ��ֽ�ת��
    for(i = 0; i < GetAddressLen / 2 ; i++)
    {
        sys_send_sms.content[2*(i)+1] = received_data.param0[2*i];
        sys_send_sms.content[2*(i)] = received_data.param0[2*i+1];
    }
    sys_send_sms.len = GetAddressLen  / 2;

    LOGD(" %d,%d", sys_send_sms.len, mmi_ucs2strlen(sys_send_sms.content));

    if(NumLen == 0)
    {
        for(phbNumIndex = 0; phbNumIndex < SOS_PHB_NUM_MAX; phbNumIndex++)
        {
            if(strlen((S8*) tracker_sos_phb.ph_num[phbNumIndex]))
            {
                SetSendSMS(FALSE, tracker_sos_phb.ph_num[phbNumIndex] , 0, sys_send_sms.content);
                if(tracker_permit_level.alarmmode == 0)
                {
                    break;
                }
            }
        }
    }
    else
    {
        SetSendSMS(FALSE, sys_send_sms.num, 0, sys_send_sms.content);
    }
}


/******************************************************************************
 *  Function    -  Tracker_GPS_Send_Position_Data
 *
 *  Purpose     -  ����WHERE ��ѯ��ַ
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-11, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_GPS_Send_Position_Data(void)
{
    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");     //ָ��Ȳ���ȷ
        Send_Command_Message_Replay();
        return;
    }

    if(Command_State == SMS_Command_State)
    {
        if(Delete_SmsPrefix_Confirm_SOSNum() == 0XFF)
        {
            sprintf(sms_buf, "ERROR:114");
            Send_Command_Message_Replay();
            return;
        }
    }
    else if(Command_State == AT_Command_State)
    {
        memset(sys_rcv_sms.num, 0, sizeof(sys_rcv_sms.num));
    }
    else
    {
        sprintf(sms_buf, "ERROR:114");
        Send_Command_Message_Replay();
        return;
    }

#ifdef __SMS_APP_DEBUG__
    LOGD("Tracker_GPS_Send_Position_Data num:%s", sys_rcv_sms.num);
#endif

    if(GPSOnFlag)
    {
        if(GPSCurrentLocation == TRUE)
        {
            Tracker_Send_WHERE_QuerySMS();
        }
        else
        {
            WhereQuery = TRUE;
			
			if(IsMyTimerExist(GPS_OFF_TIMER_ID))
				StopTimer(GPS_OFF_TIMER_ID);
            StartTimer(GPS_OFF_TIMER_ID, GPS_WORK_VALID_TIME, GPS_OFF);
			
			StartTimer(SMS_SEND_MANY_DELAY_GPS_ID,  3 * 60 * 1000 , Tracker_Send_WHERE_QuerySMS);
        }
    }
    else
    {
        WhereQuery = TRUE;
        GPS_Work_Mode = GPS_SAVE_MOD1;
		
        GPS_ON();
		StartTimer(SMS_SEND_MANY_DELAY_GPS_ID,  3 * 60 * 1000 , Tracker_Send_WHERE_QuerySMS);
    }
}

/******************************************************************************
 *  Function    -  Tracker_Query_Get_Latitude_and_Longitude
 *
 *  Purpose     -  ��ѯ��ǰ��γ��
 *                       ������GPS ��ǰ��λ��ֱ�ӻظ���γ��
 *                       ��ǰδ��������ֱ�ӻظ���һ�ζ�λ��Ϣ
 *                       ��δ��λ�ظ�"No Data!"
 *  Description -  WHERE#
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-06-06,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Query_Get_Latitude_and_Longitude(void)
{
    if(Command_State == SMS_Command_State)
    {
        if(received_data.part != 0)
        {
            sprintf(sms_buf, "ERROR:100");     //ָ��Ȳ���ȷ
            return;
        }

        if((tracker_permit_level.sospermit == 1)
                && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE)
                && (Delete_SmsPrefix_Confirm_SOSNum() == 0xFF)
                && (SuperCommandHead == FALSE))
        {
            sprintf(sms_buf, "ERROR:117");   //ERROR:110
            return;
        }
    }

    LOGD(" %s,%d,%d", sys_rcv_sms.num, GPS_Work_Mode, GPSCurrentLocation);
    Tracker_Packet_Alarm_String_Data();
    strcpy(sms_buf, sys_send_sms.content);
}




/******************************************************************************
 *  Function    -  Tracker_Query_Get_Address_From_Server
 *
 *  Purpose     -  �����ѯ��ַ��Ϣ
 *
 *  Description -  DW /POSITION/123
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 15-09-2010,  guojie  written   ֻ�����������Բ�ѯλ����Ϣ
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Query_Get_Address_From_Server(void)
{
	if(Command_State == AT_Command_State)
	{
		strcpy(sys_rcv_sms.num, tracker_sos_phb.ph_num[0]);
		Command_State = SMS_Command_State;
	}

#ifdef __SMS_APP_DEBUG__
	LOGD("Tracker_Query_Get_Address_From_Server num:%s", sys_rcv_sms.num);
#endif
	if(Command_State == SMS_Command_State)
	{
		if(Delete_SmsPrefix_Confirm_SOSNum() == 0XFF)
		{
			sprintf(sms_buf, "ERROR:114");
			Send_Command_Message_Replay();
		}
		else
		{
			DWQuery = 1;
			DWSocConnecttimes = 0;

			if(GPSOnFlag)
			{
				if(GPSCurrentLocation)
				{
					gprs_send_type = GPRS_GPS_PHB_INFO;
					Tracker_Socket_Send_AllType_GPRS_Data();
				}
				else
				{
					if(IsMyTimerExist(GPS_OFF_TIMER_ID))
						StopTimer(GPS_OFF_TIMER_ID);
					StartTimer(GPS_OFF_TIMER_ID, GPS_WORK_VALID_TIME, GPS_OFF);

					StartTimer(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER, 5 * 60 * 1000, Tracker_Qurey_Get_Address_Fail_SendSMS);
				}
			}
			else
			{
				GPS_Work_Mode = GPS_SAVE_MOD1;

				GPS_ON();
				StartTimer(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER, 5 * 60 * 1000, Tracker_Qurey_Get_Address_Fail_SendSMS);
			}
		}
	}	
}


/******************************************************************************
 *  Function    -  Tracker_Packet_Reback_URLAddress
 *
 *  Purpose     -  �������������ϲ�ѯλ�õľ�γ�����ӵ�ַ
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2013-11-08 guojie
 * ----------------------------------------
 *  ָ��: URL#
 *  ����: [Date Time:10-10-10 14:28:42] http://maps.google.com/maps?q=N23.111785,E114.409293
 *  ����: NO DATA!
 ******************************************************************************/
void Tracker_Packet_Reback_URLAddress(void)
{
    double Now_Lat, Now_Lon;
    U8 len = 0;
    memset(sms_buf, 0, sizeof(sms_buf));
    memset(sys_send_sms.content, 0, sizeof(sys_send_sms.content));

    LOGD("begin");

    if((Last_valide_data.status == AK_TRUE) || (GPSCurrentLocation == TRUE))
    {
        //ʱ��
        sprintf((char *)sys_send_sms.content, "<");
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.year);
        len = strlen((char *)sys_send_sms.content);
        sys_send_sms.content[len] = '-';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.month);
        sys_send_sms.content[len+3] = '-';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.day);
        sys_send_sms.content[len+6] = ' ';
        sys_send_sms.content[len+7] = ' ';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.hour);
        len = strlen((char *)sys_send_sms.content);
        sys_send_sms.content[len] = ':';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.minute);
        sys_send_sms.content[len+3] = ':';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.second);
        sys_send_sms.content[len+6] = '>';
        sys_send_sms.content[len+7] = ' ';
        len = strlen((char *)sys_send_sms.content);

        Get_GPS_Unsigned_Doble_LatLon();

        strcat((char *)sys_send_sms.content, tracker_ctrl_data.URL_Address);

        //�ϱ�γN: 0000 0011   S:0000 1000
        if((Last_valide_data.location_info.direct & 0x0f) == GPS_LOCATION_DIR_S)
        {
            strcat((char *)sys_send_sms.content, "S");
            strcat((char *)sys_send_sms.content, latlon_info.lat_string);
        }
        else
        {
            strcat((char *)sys_send_sms.content, "N");
            strcat((char *)sys_send_sms.content, latlon_info.lat_string);

        }

        //������E:0001 0000  W:1100 0000
        if((Last_valide_data.location_info.direct & 0xf0) == GPS_LOCATION_DIR_E)
        {
            strcat((char *)sys_send_sms.content, ",E");
            strcat((char *)sys_send_sms.content, latlon_info.lon_string);
        }
        else
        {
            strcat((char *)sys_send_sms.content, ",W");
            strcat((char *)sys_send_sms.content, latlon_info.lon_string);
        }

        strcpy(sms_buf, sys_send_sms.content);
    }
    else
    {
        sprintf(sms_buf, "No Data!");
    }
}


/******************************************************************************
 *  Function    -  Tracker_See_Address_URL
 *
 *  Purpose     -  �������������ϲ�ѯλ�õľ�γ�����ӵ�ַ
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-06-05 guojie written
 * ----------------------------------------
 *  ָ��: URL#
 *  ����: [Date Time:10-10-10 14:28:42] http://maps.google.com/maps?q=N23.111785,E114.409293
 *  ����: NO DATA!
 ******************************************************************************/
static void Tracker_See_Address_URL(void)
{
    char tmp[100];
    char tmp1[100];

#ifdef __SMS_APP_DEBUG__
    LOGD("sms_num:%s", sys_rcv_sms.num);
#endif

    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        Send_Command_Message_Replay();
        return;
    }

    if(Command_State == SMS_Command_State)
    {
        if(Delete_SmsPrefix_Confirm_SOSNum() == 0XFF)
        {
            sprintf(sms_buf, "ERROR:114");
            Send_Command_Message_Replay();
            return;
        }
    }
    else if(Command_State == AT_Command_State)
    {
        memset(sys_rcv_sms.num, 0, sizeof(sys_rcv_sms.num));
    }
    else
    {
        sprintf(sms_buf, "ERROR:114");
        Send_Command_Message_Replay();
        return;
    }

    if(GPSOnFlag)
    {
        if(GPSCurrentLocation == TRUE)
        {
            Tracker_Send_URL_QuerySMS();
        }
        else
        {
            URLQuery = TRUE;
			
			if(IsMyTimerExist(GPS_OFF_TIMER_ID))
				StopTimer(GPS_OFF_TIMER_ID);
			StartTimer(GPS_OFF_TIMER_ID, GPS_WORK_VALID_TIME, GPS_OFF);
			
			StartTimer(SMS_SEND_MANY_DELAY_GPS_ID,  3 * 60 * 1000 , Tracker_Send_URL_QuerySMS);
        }
    }
    else
    {
        URLQuery = TRUE;
        GPS_Work_Mode = GPS_SAVE_MOD1;
		
        GPS_ON();
		StartTimer(SMS_SEND_MANY_DELAY_GPS_ID,  3 * 60 * 1000 , Tracker_Send_URL_QuerySMS);
    }
}

/******************************************************************************
 *  Function    -  Tracker_EDIT_Address_URL
 *
 *  Purpose     -  ����URL���ӵ�ַ
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-06-05,  guojie  written
 *
 *  ָ��: EURL,66666,http://maps.google.com/maps?q=#
 *  ָ��: EURL,http://maps.google.com/maps?q=#
 *  ����: OK
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_EDIT_Address_URL(void)
{
    S16 error;
    char temp1[200] = {0};

    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
        sprintf(temp1, "Currently URL:%s;", tracker_ctrl_data.URL_Address);

        strcpy((char*)sms_buf, (char*)temp1);
    }
    else if(received_data.part == 1)
    {
        memset(tracker_ctrl_data.URL_Address, 0, 100);
        Make_Small_Letter((char*)received_data.param0);
        strcpy(tracker_ctrl_data.URL_Address, (char*)received_data.param0);
        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, (void *)&tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error); //�޸�ģʽ,��ʱʱ���
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
    }
}


/******************************************************************************
 *  Function    -  Tracker_Get_LatLon_Information
 *
 *  Purpose     -  �������������ϲ�ѯλ�õľ�γ�����ӵ�ַ
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2014-06-27 guojie written
 * ----------------------------------------
 *  ָ��: DWXX,000000#   //ƽ̨�·�Ĭ�϶��Ǵ�����
 *  ����: DWXX=Command Error!  (ʧ�ܷ���)
 *  ����: DWXX=Lat:,Lon:,Course:,Speed:,DateTime:. (δ��λ)
 *  ����: DWXX=Lat:N23d 5.1708m,Lon:E114d 23.6212m,Course:120,Speed:53.02,DateTime:14-06-27 14:52:36
 *  ����: DWXX=Lat:N22d 34.6272m,Lon:E113d 55.0049m,Course:120,Speed:53.02,DateTime:14-06-27 14:52:36
 ******************************************************************************/
static void Tracker_Get_LatLon_Information(void)
{
    char temp[50];

    //ƽ̨Ĭ�ϴ������·�
    if(received_data.part == 0 || received_data.part == 1)
    {
        if(GPSCurrentLocation == TRUE)
        {
            sprintf(sms_buf, "DWXX=Lat:%s,", Last_valide_data.location_info.latitude);
            memset(temp, 0, sizeof(temp));
            sprintf(temp, "Lon:%s,", Last_valide_data.location_info.longtitude);
            strcat(sms_buf, temp);
            memset(temp, 0, sizeof(temp));
            sprintf(temp, "Course:%s,", Last_valide_data.location_info.course);
            strcat(sms_buf, temp);
            memset(temp, 0, sizeof(temp));
            sprintf(temp, "Speed:%s,", Last_valide_data.location_info.speed);
            strcat(sms_buf, temp);
            memset(temp, 0, sizeof(temp));
            sprintf((char *)temp, ",DateTime:");
            strcat((char *)sms_buf, (char *)temp);
            strcat((char *)sms_buf, (char *)Last_valide_data.data_time.year);
            strcat((char *)sms_buf, (char *)"-");
            strcat((char *)sms_buf, (char *)Last_valide_data.data_time.month);
            strcat((char *)sms_buf, (char *)"-");
            strcat((char *)sms_buf, (char *)Last_valide_data.data_time.day);
            strcat((char *)sms_buf, (char *)" ");
            strcat((char *)sms_buf, (char *)Last_valide_data.data_time.hour);
            strcat((char *)sms_buf, (char *)":");
            strcat((char *)sms_buf, (char *)Last_valide_data.data_time.minute);
            strcat((char *)sms_buf, (char *)":");
            strcat((char *)sms_buf, (char *)Last_valide_data.data_time.second);
            strcat((char *)sms_buf, (char *)".");
        }
        else
        {
            sprintf(sms_buf, "DWXX=Lat:,Lon:,Course:,Speed:,DateTime:.");
        }
    }
    else
    {
        sprintf(sms_buf, "DWXX=Command Error!");
    }

    if(Command_State == ONLine_Command_State)
    {
        Tracker_Online_State = TRACKER_ONLINE_DWXX;
    }
}


/******************************************************************************
 *  Function    -  Tracker_Set_Static_Filtering_Status
 *
 *  Purpose     - ���þ�̬���˿���
 *
 *  Description -  SF,ON#     SF,ON,30#    10--1000��Ĭ��ֵ 100��
 *                       SF,OFF#
 *                       SF#
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Static_Filtering_Status(void)
{
    S16 error;
    U8 interval_str[20];
    U16  interval = 0xffff;

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        if(tracker_ctrl_data.staticfilter)
        {
            sprintf(sms_buf, "SF:ON,%d.", tracker_ctrl_data.filterdistance);
        }
        else
        {
            sprintf(sms_buf, "SF:OFF.");
        }
    }
    else if(received_data.part == 1)
    {
        if(strcmp("ON", ((char *)received_data.param0)) == 0)
        {
            tracker_ctrl_data.staticfilter = 1;
            WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
        else if(strcmp("OFF", ((char *)received_data.param0)) == 0)
        {
            tracker_ctrl_data.staticfilter = 0;
            WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
        }
    }
    else if(received_data.part == 2)
    {
        if(strcmp("ON", ((char *)received_data.param0)) == 0)
        {
            memcpy(interval_str, received_data.param1, 20);
            interval = interval_Time_Manage(interval_str, 10, 1000);
            if(interval == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return ;
            }
            tracker_ctrl_data.filterdistance =  interval;
            tracker_ctrl_data.staticfilter = 1;
            WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
    }
}

/******************************************************************************
 *  Function    -  Tracker_Set_Report_Mode
 *
 *  Purpose     -  ���ö�λ���ϱ���ʽ
 *
 *  Description -  REPORT,X,T1/D[,T2]#
 *                        REPORT,0,T1,T2#         ��ʱ��T1(0,5-18000S ACC ON),T2(0,5-18000S ,ACC OFF)
 *                        REPORT,1,D#          ���� ��D(0,50-10000M)
 *                        REPORT#
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Report_Mode(void)
{
    S16 error;
    U8 i = 0;
    U8 interval_str[2][20];
    U16  interval[2] = {0xffff, 0xffff};
    char temp1[100] = {0};

    if((received_data.part != 0) && (received_data.part != 1) && (received_data.part > 3))
    {
        sprintf(sms_buf, "ERROR:100");    //ָ��Ȳ���ȷ
        return ;
    }

    if(received_data.part == 0)
    {
        memset(temp1, 0, sizeof(temp1));
        if(tracker_ctrl_data.reportstrategy == 1)
        {
            sprintf(temp1, "PEPORT:TIME,%d,%d;", tracker_ctrl_data.gps_accon_interval / 1000, tracker_ctrl_data.gps_accoff_interval / 1000);
        }
        else if(tracker_ctrl_data.reportstrategy == 2)
        {
            sprintf(temp1, "PEPORT:DISTANCE,%d;", tracker_ctrl_data.distance);
        }
        else if(tracker_ctrl_data.reportstrategy == 4)
        {
            sprintf(temp1, "PEPORT:ANGLEREP,%d,%d;", tracker_ctrl_data.inflection_interval, tracker_ctrl_data.inflection_detect_time / 1000);
        }
        strcpy((char*)sms_buf, (char*)temp1);
        return;
    }

    if(strlen((char*)received_data.param0) != 1)
    {
        sprintf(sms_buf, "ERROR:101");    //���ݳ�����Χ
        return ;
    }

    memset(interval_str, 0, 40);

    if(received_data.param0[0] == '0') //Ϊ��ʱ�ϴ�
    {
        if((received_data.part != 2) && (received_data.part != 3))
        {
            sprintf(sms_buf, "ERROR:100");    //ָ��Ȳ���ȷ
            return ;
        }

        memcpy(interval_str[0], received_data.param1, 20);
        memcpy(interval_str[1], received_data.param2, 20);

        for(i = 0; i < received_data.part - 1; i++)
        {
            if(strlen((char*)interval_str[i]) == 0)
            {
                interval[i] = 0xffff;
                continue ;
            }

            if((strlen((char*)interval_str[i]) == 1) && (interval_str[i][0] == '0'))
            {
                interval[i] = 0;
            }
            else
            {
                interval[i] = interval_Time_Manage(interval_str[i], 5, 18000);
            }

            if(interval[i] == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return;
            }
        }

        tracker_ctrl_data.reportstrategy = 1;
        if(interval[0] != 0xffff)
        {
            tracker_ctrl_data.gps_accon_interval =  interval[0] * 1000;
        }
        if(interval[1] != 0xffff)
        {
            tracker_ctrl_data.gps_accoff_interval =  interval[1] * 1000;
        }
        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
	#if defined(__PARAM_BACKUP__)
        StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
	#endif
        sprintf(sms_buf, "OK");
    }
    else  if(received_data.param0[0] == '1')
    {
        if((received_data.part != 2))
        {
            sprintf(sms_buf, "ERROR:100");    //ָ��Ȳ���ȷ
            return ;
        }

        memcpy(interval_str[0], received_data.param1, 20);
        if(strlen((char*)interval_str[0]) == 0)
        {
            interval[0] = 0xffff;
        }
        else
        {
            if((strlen((char*)interval_str[0]) == 1) && (interval_str[0][0] == '0'))
            {
                interval[0] = 0;
            }
            else
            {
                interval[0] = interval_Time_Manage(interval_str[0], 50, 10000);
            }

            if(interval[0] == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return ;
            }
        }

        tracker_ctrl_data.reportstrategy = 2;
        if(interval[0] != 0xffff)
        {
            tracker_ctrl_data.distance =  interval[0];
            if(tracker_ctrl_data.distance_time_interval == 0)
            {
                tracker_ctrl_data.distance_time_interval = 10 * 1000;
            }
        }
        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
	#if defined(__PARAM_BACKUP__)
        StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
	#endif
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:101");
    }
}


/******************************************************************************
 *  Function    -  Tracker_Set_Timer_interval
 *
 *  Purpose     -  �޸��ϴ�ʱ��
 *
 *  Description -  TIMER,T1,T2#   
 *							T1=1-60���ӣ�LBS��λ�ϴ������Ĭ��ֵ��2,
 *							T2=0��5��18000�룻GPS�ϴ������Ĭ��ֵ��20
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-20,  guojie  written   TIMER,10,60#
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Timer_interval(void)
{
    S16 error;
    U16 interval[2] = {0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[2][20];
    char temp1[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
        sprintf((char *)temp1, "TIMER:%d,%d;", tracker_ctrl_data.lbs_time_interval / (60*1000), tracker_ctrl_data.gps_time_interval / 1000);

        strcpy((char *)sms_buf, temp1);
        return;
    }
    else if(received_data.part == 2)
    {
	    memset(interval_str, 0, 40);
	    memcpy(interval_str[0], received_data.param0, 20);
	    memcpy(interval_str[1], received_data.param1, 20);

	    for(i = 0; i < received_data.part; i++)
	    {
	        if(strlen((char*)interval_str[i]) == 0)
	        {
	            interval[i] = 0xffff;
	            continue ;
	        }

	        if((strlen((char*)interval_str[i]) == 1) && (interval_str[i][0] == '0'))
	        {
	            interval[i] = 0;
	        }
	        else
	        {
	            if(i == 0)
	            {
	                interval[i] = interval_Time_Manage(interval_str[i], 1, 60);
	            }
	            else
	            {
	                interval[i] = interval_Time_Manage(interval_str[i], 5, 18000);
	            }
	        }

	        if(interval[i] == 0xffff)
	        {
	            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
	            return;
	        }
	    }

	    if(interval[0] != 0xffff)
	    {
	        tracker_ctrl_data.lbs_time_interval = interval[0] * 60 * 1000;
	    }
	    if(interval[1] != 0xffff)
	    {
	        tracker_ctrl_data.gps_time_interval = interval[1] * 1000;
	    }

	    tracker_ctrl_data.reportstrategy = 1;

	#if defined(__ACC_DETECT__)
	    if(tracker_acc_state == ACC_ON)
	    {
	        tracker_ctrl_data.gps_time_interval = tracker_ctrl_data.gps_accon_interval;

	        if((tracker_ctrl_data.gps_accon_interval <= 10 * 1000) && (tracker_ctrl_data.gps_accon_interval >= 5000))
	        {
	            tracker_ctrl_data.distance_time_interval  = tracker_ctrl_data.gps_accon_interval;
	        }
	    }
	#endif/*__ACC_DETECT__*/

	    //�ϴ����С��10Sʱ����������ҲӦС��10S
	    if((tracker_ctrl_data.gps_time_interval <= 10 * 1000) && (tracker_ctrl_data.gps_time_interval >= 5000))
	    {
	        tracker_ctrl_data.distance_time_interval  = tracker_ctrl_data.gps_time_interval;
	    }
	    else
	    {
	        tracker_ctrl_data.distance_time_interval  = 10 * 1000;
	        LOGD(" tracker_ctrl_data.distance_time_interval==10");//wnq
	    }

	    if(tracker_ctrl_data.gps_time_interval == 5000)
	    {
	        GPSBackupSum1Min = 20;
	    }
	    else
	    {
	        GPSBackupSum1Min = 12;
	    }

	    if(tracker_ctrl_data.reportstrategy == 1)
	    {
	        //ֹͣ��ʱ�ϴ���ǰ����
	        if((tracker_ctrl_data.gps_time_interval == 0) && (tracker_ctrl_data.inflectstate == 0))
	        {
	            if(IsMyTimerExist(GPS_DISTANCE_DETECT_TIMER))
	            {
	                StopTimer(GPS_DISTANCE_DETECT_TIMER);
	            }
	            if(IsMyTimerExist(GPRS_SEND_GPS_TIMMER))
	            {
	                StopTimer(GPRS_SEND_GPS_TIMMER);
	            }
	        }
	        else if((tracker_ctrl_data.gps_time_interval == 0) && (tracker_ctrl_data.inflectstate  != 0)
	                && (tracker_ctrl_data.inflection_detect_time != 0) && (tracker_ctrl_data.inflection_interval != 0))
	        {
	            tracker_ctrl_data.reportstrategy = 4;
	            DistanceTimeDelay = TRUE;
	            Tracker_Send_Detect_Timing();
	        }
	        //������ǰ�����ϴ�
	        else
	        {
	            DistanceTimeDelay = TRUE;
	            Tracker_Send_Detect_Timing();
	        }
	    }

	#if defined(__PARAM_BACKUP__)
	    StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
	#endif

	    WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
	    sprintf(sms_buf, "OK");
	#if defined(__ACC_DETECT__)//wnq
	    LOGD(" tracker_ctrl_data.reportstrategy==%d,tracker_acc_state==%d", tracker_ctrl_data.reportstrategy, tracker_acc_state);
	#else/*__ACC_DETECT__*/
	    LOGD(" tracker_ctrl_data.reportstrategy==%d", tracker_ctrl_data.reportstrategy);
	#endif/*__ACC_DETECT__*/    
    }
	else
	{
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;	
	}
}



/******************************************************************************
 *  Function    -  Tracker_Set_Distance
 *
 *  Purpose     -  �޸Ķ����ϴ�����
 *
 *  Description -  DISTANCE,D#   D(0,5-10000M)   Ĭ��:300
 *                       DISTANCE#
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-20,  guojie  written   DISANCE,300#
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Distance(void)
{
    S16 error;
    U16  interval = 0xffff;
    U8 i = 0;
    U8 interval_str[20];
    char temp1[200] = {0};

    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
        sprintf((char *)temp1, "DISTANCE:%d;", tracker_ctrl_data.distance);

        strcpy((char *)sms_buf, (char *)temp1);
    }
    else if(received_data.part == 1)
    {
        memcpy(interval_str, received_data.param0, 20);
        if(strlen((char*)interval_str) == 0)
        {
            interval = 0xffff;
        }
        else
        {
            if((strlen((char*)interval_str) == 1) && (interval_str[0] == '0'))
            {
                interval = 0;
            }
            else
            {
                interval = interval_Time_Manage(interval_str, 50, 10000);
            }

            if(interval == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return ;
            }
        }

        if(interval != 0xffff)
        {
            tracker_ctrl_data.distance =  interval;

            if(tracker_ctrl_data.distance_time_interval == 0)
            {
                tracker_ctrl_data.distance_time_interval = 10 * 1000;
            }

        }

        tracker_ctrl_data.reportstrategy = 2;

        //ֹͣ�ϴ���ǰ����
        if(tracker_ctrl_data.reportstrategy == 2)
        {
            if((tracker_ctrl_data.distance == 0) && (tracker_ctrl_data.inflectstate == 0))
            {
                if(IsMyTimerExist(GPS_DISTANCE_DETECT_TIMER))
                {
                    StopTimer(GPS_DISTANCE_DETECT_TIMER);
                }
                if(IsMyTimerExist(GPRS_SEND_GPS_TIMMER))
                {
                    StopTimer(GPRS_SEND_GPS_TIMMER);
                }
                GPSDataSendRoll = FALSE;
            }
            else if((tracker_ctrl_data.distance == 0) && (tracker_ctrl_data.inflectstate != 0)
                    && (tracker_ctrl_data.inflection_detect_time != 0) && (tracker_ctrl_data.inflection_interval != 0))
            {
                tracker_ctrl_data.reportstrategy = 4;
                DistanceTimeDelay = TRUE;
                Tracker_Send_Detect_Timing();
            }
            else
            {
                DistanceTimeDelay = TRUE;
                Tracker_Send_Detect_Timing();
            }
        }

	#if defined(__PARAM_BACKUP__)
        StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
	#endif

        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");    //ָ��Ȳ���ȷ
    }
}

/******************************************************************************
 *  Function    -  Tracker_Set_Status_Timer_interval
 *
 *  Purpose     -  �޸�״̬���ϴ�ʱ��
 *
 *  Description -  HBT,T1[,T2]#      T1(1-300min ACC ON  default:3)    T2(1-300min ACC OFF default:5)
 *
 * modification history   ƽ̨�ж�6�����������ߣ�HBT���ܴ���6����
 * ----------------------------------------
 * v1.0  , 2012-08-07,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Status_Timer_interval(void)
{
    S16 error;
    U16 interval[2] = {0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[2][20];
    char temp1[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
		
	#if defined(__ACC_DETECT__)//wnq
        sprintf(temp1, "HBT:%d,%d;", tracker_ctrl_data.status_accon_interval / 60 / 1000, tracker_ctrl_data.status_accoff_interval / 60 / 1000);
	#else
		sprintf(temp1, "HBT:%d;", tracker_ctrl_data.status_time_interval / 60 / 1000);
	#endif

        strcpy((char *)sms_buf, temp1);
        return;
    }
    else if(
			#if defined(__ACC_DETECT__)//wnq
				received_data.part > 2
			#else
				received_data.part > 1
			#endif
			)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }
    memset(interval_str, 0, 40);
    memcpy(interval_str[0], received_data.param0, 20);
    memcpy(interval_str[1], received_data.param1, 20);

    for(i = 0; i < received_data.part; i++)
    {
        if(strlen((char*)interval_str[i]) == 0)
        {
            interval[i] = 0xffff;
            continue ;
        }

        interval[i] = interval_Time_Manage(interval_str[i], 1, 300);

        if(interval[i] == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
            return;
        }
    }
#if defined(__ACC_DETECT__)//wnq
    if(interval[0] != 0xffff)
    {
        tracker_ctrl_data.status_accon_interval = interval[0] * 60 * 1000;
    }
    if(interval[1] != 0xffff)
    {
        tracker_ctrl_data.status_accoff_interval = interval[1] * 60 * 1000;
    }

    if(tracker_acc_state == ACC_ON)
    {
        tracker_ctrl_data.status_time_interval = tracker_ctrl_data.status_accon_interval;
    }
    else
    {
        tracker_ctrl_data.status_time_interval = tracker_ctrl_data.status_accoff_interval;
    }
#else
	tracker_ctrl_data.status_time_interval = interval[0] * 60 * 1000;
#endif/*__ACC_DETECT__*/

    WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);

#if defined(__PARAM_BACKUP__)
    StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
#endif

    sprintf(sms_buf, "OK");

}



/******************************************************************************
 *  Function    -  Tracker_Set_GPS_Ephemeris_Time
 *
 *  Purpose     -  GPS�رպ󣬶�ʱ��������һ������
 *
 *  Description -  EPH,T#    T--(60-240MIN)
 *                        EPH#
 * modification history     //GPS��һ�ι�������һ�ι������ʱ��
 * ----------------------------------------
 * v1.0  , 2012-12-20,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_GPS_Ephemeris_Time(void)
{
    S16 error;
    U16  interval = 0xffff;
    U8 interval_str[20];

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part > 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }

    if(received_data.part == 0)
    {
        sprintf(sms_buf, "EPH:%d;", tracker_ctrl_data.gps_work_interval / 60000);
    }
    else if(received_data.part == 1)
    {
        memset(interval_str, 0, 20);
        memcpy(interval_str, received_data.param0, 20);

        interval = interval_Time_Manage(interval_str, 60 , 240);
        if(interval == 0xffff)
        {
            sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
            return ;
        }

        tracker_ctrl_data.gps_work_interval =  interval * 60 * 1000;

        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);

	#if defined(__PARAM_BACKUP__)
        StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
	#endif

        sprintf(sms_buf, "OK");

    }

}
/******************************************************************************
 *  Function    -  Tracker_Set_Inflection_Point_Report
 *
 *  Purpose     -  �յ㲹������
 *
 *  Description -  ANGLEREP,ON,ƫת�Ƕ�,���ʱ��#     // 5-180��  default:20  ���ʱ��:2--5s��default:2s
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-20,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Inflection_Point_Report(void)
{
    S16 error;
    U16  interval[2] = {0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[2][20];
    char temp1[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
        if(tracker_ctrl_data.inflectstate == 0)
        {
            sprintf(temp1, "ANGLEREP:OFF;");
        }
        else
        {
            sprintf(temp1, "ANGLEREP:ON,%d,%d;", tracker_ctrl_data.inflection_interval, tracker_ctrl_data.inflection_detect_time / 1000);
        }

        strcpy((char *)sms_buf, (char *)temp1);
        return;
    }

    if((strcmp("ON", ((char *)received_data.param0)) == 0))
    {
        if(received_data.part != 1 && received_data.part != 3)
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        if(received_data.part == 1)   //ANGLEREP,ON#
        {
            if(tracker_ctrl_data.inflection_interval == 0)
            {
                tracker_ctrl_data.inflection_interval = 20;
            }

            if(tracker_ctrl_data.inflection_detect_time == 0)
            {
                tracker_ctrl_data.inflection_detect_time = 2000;
            }
            tracker_ctrl_data.inflectstate = 1;
        }
        else
        {
            memset(interval_str, 0, 40);
            memcpy(interval_str[0], received_data.param1, 20);
            memcpy(interval_str[1], received_data.param2, 20);

            for(i = 0; i < received_data.part - 1; i++)
            {
                if(strlen((char*)interval_str[i]) == 0)
                {
                    interval[i] = 0xffff;
                    continue ;
                }

                if(i == 0)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 5, 180);
                }
                else if(i == 1)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 2, 5);
                }

                if(interval[i] == 0xffff)
                {
                    sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                    return;
                }
            }

            tracker_ctrl_data.inflectstate = 1;
            if(interval[0] != 0xffff)
            {
                tracker_ctrl_data.inflection_interval =  interval[0];
            }
            if(interval[1] != 0xffff)
            {
                tracker_ctrl_data.inflection_detect_time =  interval[1] * 1000;
            }

            if((tracker_ctrl_data.distance == 0) && (tracker_ctrl_data.gps_time_interval == 0))
            {
                tracker_ctrl_data.reportstrategy = 4;
            }
        }
        Tracker_Send_Detect_Timing();
        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else if((strcmp("OFF", ((char *)received_data.param0)) == 0))
    {
        if(received_data.part != 1)
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }
        tracker_ctrl_data.inflectstate = 0;

        if(((tracker_ctrl_data.reportstrategy == 1) && (tracker_ctrl_data.gps_time_interval == 0))
                || ((tracker_ctrl_data.reportstrategy == 2) && (tracker_ctrl_data.distance == 0)))
        {
            if(IsMyTimerExist(GPS_DISTANCE_DETECT_TIMER))
            {
                StopTimer(GPS_DISTANCE_DETECT_TIMER);
            }
            if(IsMyTimerExist(GPRS_SEND_GPS_TIMMER))
            {
                StopTimer(GPRS_SEND_GPS_TIMMER);
            }
            GPSDataSendRoll = FALSE;
        }
        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
    }
}



#if defined(__ACC_DETECT__)

/******************************************************************************
 *  Function    -  Tracker_Set_ACC_Report_Status
 *
 *  Purpose     -  ����ACC״̬�仯����
 *
 *  Description -  ACCREP,ON#   ACCREP,OFF#
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-20,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_ACC_Report_Status(void)
{
    S16 error;

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        if(tracker_acc_data.accreportstate == 0)
        {
            sprintf(sms_buf, "ACCREP:OFF;");
        }
        else
        {
            sprintf(sms_buf, "ACCREP:ON;");
        }
        return ;

    }
    else if(received_data.part != 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }

    if((strcmp("ON", ((char *)received_data.param0)) == 0))
    {
        tracker_acc_data.accreportstate = 1;
        WriteRecord(NVRAM_EF_TRACKER_ACC_DATA_LID, 1, &tracker_acc_data, NVRAM_EF_TRACKER_ACC_DATA_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else if((strcmp("OFF", ((char *)received_data.param0)) == 0))
    {
        tracker_acc_data.accreportstate = 0;
        WriteRecord(NVRAM_EF_TRACKER_ACC_DATA_LID, 1, &tracker_acc_data, NVRAM_EF_TRACKER_ACC_DATA_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
    }
    LOGD(" accreportstate=%d", tracker_acc_data.accreportstate);

}
#endif


/******************************************************************************
 *  Function    -  Tracker_Set_Packting_Number
 *
 *  Purpose     -  ����GPS���ݴ����������
 *
 *  Description -  BATCH,ON,N#     BATCH,OFF#     BATCH#
 *
 * modification history    N(2--50)
 * ----------------------------------------
 * v1.0  , 2012-12-20,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Packting_Number(void)
{
    S16 error;
    U16  interval = 0xffff;
    U8 interval_str[20];

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part > 2)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }

    if(received_data.part == 0)
    {
        if(tracker_ctrl_data.packetstate == 0)
        {
            sprintf(sms_buf, "BATCH:OFF;");
        }
        else
        {
            sprintf(sms_buf, "BATCH:ON,%d;", tracker_ctrl_data.pack_count);
        }
    }
    else if(received_data.part == 1)
    {
        if(strcmp("ON", ((char *)received_data.param0)) == 0)
        {
            tracker_ctrl_data.packetstate = 1;
            if(tracker_ctrl_data.pack_count == 0)
            {
                tracker_ctrl_data.pack_count = 20;
            }
            WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
        else if(strcmp("OFF", ((char *)received_data.param0)) == 0)
        {
            tracker_ctrl_data.packetstate = 0;
            WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");
        }
    }
    else if((received_data.part == 2) && (strcmp("ON", ((char *)received_data.param0)) == 0))
    {
        memset(interval_str, 0, 20);
        memcpy(interval_str, received_data.param1, 20);

        if(strlen((char*)interval_str) == 0)
        {
            interval = 0xffff;
        }
        else
        {
            interval = interval_Time_Manage(interval_str, 1, 50);
            if(interval == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return;
            }
        }

        tracker_ctrl_data.packetstate = 1;
        if(interval != 0xffff)
        {
            tracker_ctrl_data.pack_count =  interval;
        }

        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);

        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");//ָ���ʽ����
    }

    LOGD(" %d,%d", tracker_ctrl_data.packetstate, tracker_ctrl_data.pack_count);

}
#endif

kal_bool g_force_open_gps = KAL_FALSE; //ǿ�ƴ�GPS cjt

void stop_force_open_gps(void)
{
	g_force_open_gps = KAL_FALSE;
	kjx_close_gps();
}

static void Tracker_Gps_Off(void)
{
    stop_force_open_gps();

    if(!kjx_gps_is_on())
    {
        sprintf(sms_buf, "OK! GPS off");
    }
    else
    {
        sprintf(sms_buf, "ERROR: any apps using GPS, cancel gps off");
    }
}

/******************************************************************************
 *  Function    -  Tracker_Command_Active_GPS
 *
 *  Purpose     -  ���߼���GPS    �� ��������GPS������ʱ��
 *
 *  Description -  AT^GT_CM=GPSON#     δ��ʱ�䣬��Ĭ���ֻ����20����
 *
 * 301   ���߼���GPS�����䳤T����,��λ������ϴ�GPSλ����Ϣ
 * ----------------------------------------
 * v1.0  , 2012-06-01, guojie  written
 * ----------------------------------------
 *******************************************************************************/
void Tracker_Command_Active_GPS(void)
{
	S16 error;
	U16 interval = 0xffff;
	U8 interval_str[20];
	int gps_work_time = 0;

	LOGD("begin");
	
	memset(sms_buf, 0, sizeof(sms_buf));

	if(received_data.part > 1)
	{
	#if 0	//xb test
		if(Command_State == ONLine_Command_State)
		{
			Tracker_Online_State = TRACKER_ONLINE_GPS_INACTIVATE;
			gprs_send_type = GPRS_ONLINE_RESULT_INFO;
			Tracker_Socket_Send_Current_Data();
		}
		else
	#endif
		{
			sprintf(sms_buf, "ERROR:100");	 //ָ��Ȳ���ȷ
			strcat(sms_buf, ";GPSON#;GPSON,20#");
		}
		return;
	}

	if(received_data.part == 1) 	 //GPSON,20#
	{
		memset(interval_str, 0, sizeof(interval_str));
		memcpy(interval_str, received_data.param0, 20);

		if(strlen((char*)interval_str) == 0)
		{
			interval = 0xffff;
		}
		else
		{
			interval = interval_Time_Manage(interval_str, Tracker_GPS_Work_Time_Min, Tracker_GPS_Work_Time_Max);
		}

		if(interval == 0xffff)
		{
		#if 0	//xb test
			if(Command_State == ONLine_Command_State)
			{
				Tracker_Online_State = TRACKER_ONLINE_GPS_INACTIVATE;
				gprs_send_type = GPRS_ONLINE_RESULT_INFO;
				Tracker_Socket_Send_AllType_GPRS_Data();
			}
			else
		#endif
			{
				sprintf(sms_buf, "ERROR:101");	 //���ݳ�����Χ
				strcat(sms_buf, ";GPSON#;GPSON,20#");
			}
			return;
		}
		else
		{
			gps_work_time = interval * 1000 * 60;
		}
	}
	else if(received_data.part == 0)   //��������������20����
	{
	#if defined(__KD6113__)
		gps_work_time = 5 * 1000 * 60;
	#else
		gps_work_time = 20 * 1000 * 60;
	#endif
	}

	//------------------��GPS-----------------------------------------------------
	g_force_open_gps = KAL_TRUE;
	StartTimer(KJX_TIMER_ID_GPS_OPEN, gps_work_time, stop_force_open_gps); // ���ʱ���ڲ������κ�GPS_OFF

#if 0	//xb test
    if(Command_State == ONLine_Command_State)
    {
        Tracker_Online_State = TRACKER_ONLINE_GPS_ACTIVATE;
		gprs_send_type = GPRS_ONLINE_RESULT_INFO;
		Tracker_Socket_Send_AllType_GPRS_Data();
    }
    else
#endif		
    {
        sprintf(sms_buf, "OK! GPS ON!");
	#if 0	//xb test
        if(soc_content.soc_state == SOC_CONNECTED)
        {
            Tracker_Send_See_System_Param();
        }
	#endif
    }

	if(!kjx_gps_is_on())
	{
		kjx_open_gps();
	}
	else
	{
		StartTimer(KJX_TIMER_ID_GPS_CLOSE, gps_work_time, kjx_close_gps);
	}

#if 0	//xb test
	else
	{
		if(GPS_Work_Mode == GPS_SAVE_MOD1)
		{
			StartTimer(GPS_OFF_TIMER_ID, GPS_WORK_VALID_TIME, GPS_OFF);
		}
		else if(GPS_Work_Mode == GPS_SAVE_MOD2)
		{
			StartTimer(GPS_OFF_TIMER_ID, GPS_WORK_LONG_VALID_TIME, GPS_OFF);
		}
		else if(GPS_Work_Mode == GPS_SAVE_MOD3)
		{
			StartTimer(GPS_OFF_TIMER_ID, gps_work_time, GPS_OFF);
		}
	}
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Command_Active_GPS
 *
 *  Purpose     -  ���߼���GPS    �� ��������GPS������ʱ��
 *
 *  Description -  AT^GT_CM=GPSON#     δ��ʱ�䣬��Ĭ���ֻ����20����
 *
 * 301   ���߼���GPS�����䳤T����,��λ������ϴ�GPSλ����Ϣ
 * ----------------------------------------
 * v1.0  , 2012-06-01, guojie  written
 * ----------------------------------------
 *******************************************************************************/
void Tracker_Command_Close_GPS(void)
{
    stop_force_open_gps();
    if(!kjx_gps_is_on())
    {
        sprintf(sms_buf, "OK! GPS off");
    }
    else
    {
        sprintf(sms_buf, "ERROR: any apps using GPS, cancel gps off");
    }
}


/******************************************************************************
 *  Function    -  Tracker_Command_Restart_GPS
 *
 *  Purpose     -  �ֶ�������GPS������GPS
 *
 *  Description -  AT^GT_CM=REOPENGPS#
 *
 * ----------------------------------------
 * v1.0  , 2013-03-13, guojie  written
 * ----------------------------------------
 *******************************************************************************/
static void Tracker_Command_Restart_GPS(void)
{
    kjx_close_gps();
    StartTimer(KJX_TIMER_ID_GPS_OPEN, 5000, kjx_open_gps);
    sprintf(sms_buf, "OK! GPS Restart");
}

/******************************************************************************
 *  Function    -  Tracker_Command_Reset_GPS
 *
 *  Purpose     -  ��λGPSģ��
 *
 *  Description -  AT^GT_CM=RESETGPS#
 *
 * ----------------------------------------
 * v1.0  , 2013-03-13, guojie  written
 * ----------------------------------------
 *******************************************************************************/
static void Tracker_Command_Reset_GPS(void)
{
    kjx_gps_software_reset();
    sprintf(sms_buf, "OK! GPS Reset");
}

/******************************************************************************
 *  Function    -  Tracker_GPS_Transparent_Transmission
 *
 *  Purpose     -  GPS͸����־
 *
 *  Description -  306GPS��ʱ��ο�����͸��ʱGPSû����Ҫ�ȴ���͸��
 *                       δ��ʱ������ʱһ��ʱ����͸������������
 * modification history
 * ----------------------------------------
 * v1.0  ,
 *
 *  ָ��: GPSTC#
 *  ����: OK
 * ----------------------------------------
 * ----------------------------------------
 * v1.0  , 2012-06-20, guojie  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_GPS_Transparent_Transmission(void)
{
    StopTimer(KJX_TIMER_ID_GPS_UPDATE_STATE);
#if defined(__KJX_AT_APP__)
    if(GPS_Pass_state == KAL_FALSE)
    {
        GPS_Pass_state = KAL_TRUE;
    }
    else
    {
        GPS_Pass_state = KAL_FALSE;
    }
#endif
}



/******************************************************************************
 *  Function    -  Tracker_GPS_Transparent_Set
 *
 *  Purpose     - GPS͸������
 *
 *  Description -  GPSTC,0#    //͸���ر�
 *                       GPSTC#       //��
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2013-05-08, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_GPS_Transparent_Set(void)
{
    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        if(!kjx_gps_is_on())
        {
            kjx_open_gps();
            StartTimer(KJX_TIMER_ID_GPS_UPDATE_STATE, 3000, Tracker_GPS_Transparent_Transmission);
        }
        else
        {
            StartTimer(KJX_TIMER_ID_GPS_UPDATE_STATE, 1000, Tracker_GPS_Transparent_Transmission);
        }
        sprintf(sms_buf, "OK");
    }
    else if((strcmp("0", ((char *)received_data.param0)) == 0) || (strcmp("1", ((char *)received_data.param0)) == 0))
    {
        sprintf(sms_buf, "OK");
        StartTimer(KJX_TIMER_ID_GPS_UPDATE_STATE, 1000, Tracker_GPS_Transparent_Transmission);
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
    }
}

/******************************************************************************
 *  Function    -  Tracker_GPS_WorkMode_Set
 *
 *  Purpose     - GPS����ģʽ����
 *
 *  Description - 
 *               
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2013-05-08, xiebiao written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_GPS_WorkMode_Set(void)
{
    U16 interval = 0xffff;

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part == 0)
    {
	    switch(g_kjx_nvram_struct.workMode)
	    {
	    case 0:
			sprintf(sms_buf, "WorkMode: ����ģʽ 10��һ��");
			break;
		case 1:
			sprintf(sms_buf, "WorkMode: ����ģʽ %d����һ��",     GPS_DATA_TIME/(60*1000));
			break;
		case 2:
			sprintf(sms_buf, "WorkMode: �Զ���ģʽ %d����һ��",    g_kjx_nvram_struct.sendTime/(60*1000));
			break;
	    }
    }
    else if(received_data.part == 1)
    {
		interval = interval_Time_Manage(received_data.param0, 0, 2);
		if(interval == 0xffff)
		{
			sprintf(sms_buf, "ERROR:101");  //ָ���ʽ����
			return;
		}

		g_kjx_nvram_struct.workMode = interval;
		switch(g_kjx_nvram_struct.workMode)
		{
		case 0:
			sprintf(sms_buf, "WorkMode Set OK: ����ģʽ 10��һ��");
			break;
		case 1:
			sprintf(sms_buf, "WorkMode Set OK: ����ģʽ %d����һ��",	   GPS_DATA_TIME/(60*1000));
			break;
		case 2:
			sprintf(sms_buf, "WorkMode Set OK: �Զ���ģʽ %d����һ��",	g_kjx_nvram_struct.sendTime/(60*1000));
			break;
		}

		kjx_nvram_write();
		kjx_reset_gps_data_send_func();
    }
	else if((received_data.part == 2) && (atoi(received_data.param0) == 2))
	{
		interval = interval_Time_Manage(received_data.param1, 3, 99);
		if(interval == 0xffff)
		{
			sprintf(sms_buf, "ERROR:101");  //ָ���ʽ����
			return;
		}

		g_kjx_nvram_struct.workMode = 2;
		g_kjx_nvram_struct.sendTime = 1000*60*(atoi(received_data.param1));

		sprintf(sms_buf, "WorkMode Set OK: �Զ���ģʽ %d����һ��",	g_kjx_nvram_struct.sendTime/(60*1000));
		
		kjx_nvram_write();
		kjx_reset_gps_data_send_func();
	}
    else
    {
        sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
    }
}


#if defined(__GPS_BACKUP__)
/******************************************************************************
 *  Function    -  Tracker_Get_GPS_Backup_Status
 *
 *  Purpose     -  �鿴���������������Ƿ񱸷���
 *
 *  Description -   BACKUP#
 *                        BACKUP,X#   ��ѯX������
 *                        BACKUP,FIRST,LAST#   ��д���һ������
 * modification history
  * ----------------------------------------
 * v1.0  , 2013-05-09, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Get_GPS_Backup_Status(void)
{
    char temp1[200] = {0};
    U16  interval[2] = {0xffff, 0xffff};
    int total = 0;
    S16 Error;
    U32 LatitudeTemp = 0, longitudeTemp = 0, SepTemp = 0, DegreeTemp = 0;
    U16 degree = 0;
#if defined(__GPS_BACKUP_TOFILE__)
    char  FilePathBuf[30] = {0};
    char FilePath[60] = {0};
    FS_HANDLE file = 0;
    int result;
    kal_uint32 read;
#endif

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part == 0)
    {
        total = backup_data_get_total_in_queue();
        if(total == BACKUP_DATA_MAX)
        {
            sprintf(sms_buf, "gps backup data is full.");
            memset(temp1, 0, 200);
            sprintf(temp1, "total :%d,first:%d,last:%d.", BACKUP_DATA_MAX, backup_data_param.data_first, backup_data_param.data_last);
            strcat(sms_buf, temp1);
        }
        else
        {
            sprintf(sms_buf, "gps backup data is not full.");
            memset(temp1, 0, 200);
            sprintf(temp1, "total :%d,first:%d,last:%d;", total, backup_data_param.data_first, backup_data_param.data_last);
            strcat(sms_buf, temp1);
        }
    }
    else if(received_data.part == 1)
    {
        interval[0] = interval_Time_Manage(received_data.param0, 1, 2000);

        if(interval[0] != 0xffff)
        {
		#if defined(__GPS_BACKUP_TONVRAM__)
            ReadRecord(NVRAM_EF_TRACKER_GPS_BACKUP_DATA_LID, interval[0], (void *)&backup_data_buf, NVRAM_EF_TRACKER_GPS_BACKUP_DATA_SIZE, &Error);
		#elif defined(__GPS_BACKUP_TOFILE__)

            memset(FilePathBuf, 0, sizeof(FilePathBuf));
            memset(FilePath, 0, sizeof(FilePath));

            strcat(FilePathBuf, gpsbackup_file_path);
            mmi_asc_to_ucs2((CHAR*)FilePath, (CHAR*)FilePathBuf);
            //���ļ�
            file = FS_Open((const WCHAR *)FilePath, FS_READ_ONLY);
            if(file < 0)
            {
                FS_Close(file);
                return;
            }

            //��ȡ��һ��ʱ��
            result = FS_Seek(file, (backup_data_param.data_first - 1) * GPS_BACKUP_DATA_LENGTH, FS_FILE_BEGIN);
            if(result < 0)
            {
                FS_Close(file);
                return;
            }

            result = FS_Read(file, &backup_data_buf, GPS_BACKUP_DATA_LENGTH, &read);
            FS_Close(file);
		#endif
            sprintf(sms_buf, "BACKUP,%d,DateTime:%d-%d-%d,%d:%d:%d;", interval[0], backup_data_buf.date[0], backup_data_buf.date[1], backup_data_buf.date[2],
                    backup_data_buf.date[3], backup_data_buf.date[4], backup_data_buf.date[5]);
            memset(temp1, 0, 200);

            SepTemp = backup_data_buf.gps_data.lat[0];
            SepTemp = SepTemp << 24;
            LatitudeTemp += SepTemp;

            SepTemp = backup_data_buf.gps_data.lat[1];
            SepTemp = SepTemp << 16;
            LatitudeTemp += SepTemp;

            SepTemp = backup_data_buf.gps_data.lat[2];
            SepTemp = SepTemp << 8;
            LatitudeTemp += SepTemp;

            SepTemp = backup_data_buf.gps_data.lat[3];
            LatitudeTemp += SepTemp;

            SepTemp = backup_data_buf.gps_data.lon[0];
            SepTemp = SepTemp << 24;
            longitudeTemp += SepTemp;

            SepTemp = backup_data_buf.gps_data.lon[1];
            SepTemp = SepTemp << 16;
            longitudeTemp += SepTemp;

            SepTemp = backup_data_buf.gps_data.lon[2];
            SepTemp = SepTemp << 8;
            longitudeTemp += SepTemp;

            SepTemp = backup_data_buf.gps_data.lon[3];
            longitudeTemp += SepTemp;

            SepTemp = backup_data_buf.gps_data.degree[0];
            SepTemp = SepTemp << 8;
            DegreeTemp += SepTemp;

            SepTemp = backup_data_buf.gps_data.degree[1];
            DegreeTemp += SepTemp;

		#if defined(__NEW_PROTOCOL__)
            sprintf(temp1, "GPS:%x,%x,%x,%x,%x;", backup_data_buf.gps_data.gps_len, LatitudeTemp, longitudeTemp,
                    backup_data_buf.gps_data.speed, DegreeTemp);
            strcat(sms_buf, temp1);
            memset(temp1, 0, 200);
            sprintf(temp1, "HOLD:%x,%x", backup_data_buf.hold[0], backup_data_buf.hold[1]);
            strcat(sms_buf, temp1);
		#elif defined(__OLD_PROTOCOL__)
            sprintf(temp1, "GPS:%x,%x,%x,%x;", LatitudeTemp, longitudeTemp,
                    backup_data_buf.gps_data.speed, DegreeTemp);
            strcat(sms_buf, temp1);
		#endif
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
        }
    }
    else if(received_data.part == 2)
    {
        interval[1] = interval_Time_Manage(received_data.param0, 1, 2000);
        interval[2] = interval_Time_Manage(received_data.param1, 1, 2000);

        if(interval[1] != 0xffff && interval[2] != 0xffff)
        {
            backup_data_param.data_first = interval[1];
            backup_data_param.data_last = interval[2];
            backup_data_param.data_full = 0;
            WriteRecord(NVRAM_EF_TRACKER_GPS_BACKUP_DATA_PARAM_LID, 1, (void *)&backup_data_param, NVRAM_EF_TRACKER_GPS_BACKUP_DATA_PARAM_SIZE, &Error);
            sprintf(sms_buf, "OK");
        }
        else
        {
            sprintf(sms_buf, "ERROR:101");
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");
    }
}


/******************************************************************************
 *  Function    -  Tracker_Init_GPS_Backup_Data
 *
 *  Purpose     -  ���³�ʼ��GPS������
 *
 *  Description -  
 *                       
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Init_GPS_Backup_Data(void)
{
    S16 error;

	backup_data_param.data_first = 1;
	backup_data_param.data_last = 1;
	backup_data_param.data_full = 0;
	WriteRecord(NVRAM_EF_TRACKER_GPS_BACKUP_DATA_PARAM_LID, 1, (void *)&backup_data_param, NVRAM_EF_TRACKER_GPS_BACKUP_DATA_PARAM_SIZE, &error);

#if defined(__EXPAND_PORT_SUPPORT__)
	analog_backup_param.data_first = 1;
	analog_backup_param.data_last = 1;
	WriteRecord(NVRAM_EF_TRACKER_BACKUP_ANALOG_PARAM_LID, 1, (void *)&digital_backup_param, NVRAM_EF_TRACKER_BACKUP_ANALOG_PARAM_SIZE, &error);

	digital_backup_param.data_first = 1;
	digital_backup_param.data_last = 1;
	WriteRecord(NVRAM_EF_TRACKER_BACKUP_DIGITAL_PARAM_LID, 1, (void *)&digital_backup_param, NVRAM_EF_TRACKER_BACKUP_DIGITAL_PARAM_SIZE, &error);
#endif

#if defined(__FUEL_SENSOR__)
	fuel_backup_param.data_first = 1;
	fuel_backup_param.data_last = 1;
	fuel_backup_param.data_full = 0;
	WriteRecord(NVRAM_EF_TRACKER_BACKUP_FUEL_PARAM_LID, 1, (void *)&fuel_backup_param, NVRAM_EF_TRACKER_BACKUP_FUEL_PARAM_SIZE, &error);
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Clear_GPS_Backup_Data
 *
 *  Purpose     -  ���GPS��������
 *
 *  Description -  CLEAR#
 *                        OK
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Clear_GPS_Backup_Data(void)
{
    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");//ָ������ֶζ�������ȷ
    }
    else
    {
		Tracker_Init_GPS_Backup_Data();
        sprintf(sms_buf, "OK");
    }
}
#endif


#if defined(__PARAM_BACKUP__)
static void Tracker_Clear_Param_Backup_Data(void)
{
    if(received_data.part != 0)
    {
        sprintf(sms_buf, "ERROR:100");//ָ������ֶζ�������ȷ
    }
    else
    {
		StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 1000, Backup_SMS_Delete_All_Msg);
		sprintf(sms_buf, "OK");
    }
}
#endif

#if defined(__GPS_OVERSPEED__)
/******************************************************************************
 *  Function    -  Tracker_Set_OverSpeed_Threshold
 *
 *  Purpose     - ���ó��ٱ�������
 *
 *  Description -  SPEED,ON[,T][,V][,M]#
 *                       SPEED,OFF#
 *                       T (5-600S)     V(1-255KM/S)  M=0,GPRS,  M=1,GPRS+SMS
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_OverSpeed_Threshold(void)
{
    S16 error;
    U16  interval[3] = {0xffff, 0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[3][20];


    memset(sms_buf, 0, sizeof(sms_buf));
    LOGD(" %s", received_data.param0);

    if(received_data.part == 0)
    {
        if(tracker_overspeed_alarm.remindstate)
        {
            sprintf(sms_buf, "SPEED:ON,%d,%d,", tracker_overspeed_alarm.detect_sum_time / 1000, tracker_overspeed_alarm.overspeedvalue);
            if(tracker_overspeed_alarm.alarmmode == 0)
            {
                strcat(sms_buf, "GPRS;");
            }
            else if(tracker_overspeed_alarm.alarmmode == 1)
            {
                strcat(sms_buf, "GPRS+SMS;");
            }
        }
        else
        {
            sprintf(sms_buf, "SPEED:OFF;");
        }
    }
    else if(strcmp("ON", ((char *)received_data.param0)) == 0)
    {
        if((received_data.part != 1) && (received_data.part != 3) && (received_data.part != 4))
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        if(received_data.part == 1)
        {
            tracker_overspeed_alarm.remindstate = 1;
        }
        else
        {
            memset(interval_str, 0, 60);
            memcpy(interval_str[0], received_data.param1, 20);
            memcpy(interval_str[1], received_data.param2, 20);
            memcpy(interval_str[2], received_data.param3, 20);

            for(i = 0; i < received_data.part - 1; i++)
            {
                if(strlen((char*)interval_str[i]) == 0)
                {
                    interval[i] = 0xffff;
                    continue ;
                }

                if(i == 0)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 5, 600);
                }
                else if(i == 1)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 1, 255);
                }
                else if(i == 2)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 0, 1);
                }


                if(interval[i] == 0xffff)
                {
                    sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                    return;
                }
            }

            tracker_overspeed_alarm.remindstate = 1;
            if(interval[0] != 0xffff)
            {
                tracker_overspeed_alarm.detect_sum_time =  interval[0] * 1000;
            }
            if(interval[1] != 0xffff)
            {
                tracker_overspeed_alarm.overspeedvalue =  interval[1];
            }
            if(interval[2] != 0xffff)
            {
                tracker_overspeed_alarm.alarmmode =  interval[2];
            }

            tracker_overspeed_alarm.detect_next_interval = 5 * 1000;
            tracker_overspeed_alarm.sendalarmsms = 0;
        }

        WriteRecord(NVRAM_EF_TRACKER_OVERSPEED_ALARM_LID, 1, &tracker_overspeed_alarm, NVRAM_EF_TRACKER_OVERSPEED_ALARM_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else if(strcmp("OFF", ((char *)received_data.param0)) == 0)
    {
        if(received_data.part != 1)
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        tracker_overspeed_alarm.remindstate = 0;
        WriteRecord(NVRAM_EF_TRACKER_OVERSPEED_ALARM_LID, 1, &tracker_overspeed_alarm, NVRAM_EF_TRACKER_OVERSPEED_ALARM_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
    }
}
#endif


#if defined(__MOVING_ALARM__)
/******************************************************************************
 *  Function    -  Tracker_Set_Moving_Param
 *
 *  Purpose     -  ����λ�Ʋ���
 *
 *  Description -  MOVING,A[,R][,M]#
 *                       MOVING#
 * modification history   A --ON/OFF   R --100-1000��  λ�ư뾶  M --0 GPRS 1 :GPRS+SMS  2 GPRS+SMS+CALL
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Moving_Param(void)
{
    S16 error;
    U16  interval[2] = {0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[2][20];
    char tmp[100];
    char data[200];

    memset(sms_buf, 0, sizeof(sms_buf));

    LOGD(" %s", received_data.param0);

    if(received_data.part == 0)
    {
        memset(tmp, 0x00, 100);
        memset(data, 0x00, 200);

        if(tracker_moving_param.remindstate == 0)
        {
            sprintf(tmp, "Moving Switch:OFF;");
            strcat(data, tmp);

            memset(tmp, 0x00, 100);
            sprintf(tmp, "Radius:%dm;", tracker_moving_param.dis);
            strcat(data, tmp);

            memset(tmp, 0x00, 100);
            sprintf(tmp, "Alarm Type:%d;", tracker_moving_param.alarmmode);
            strcat(data, tmp);
        }
        else
        {
            sprintf(tmp, "Moving Switch:ON;");
            strcat(data, tmp);

            memset(tmp, 0x00, 100);
            if(tracker_moving_param.lat > 0)
            {
                strcat(data, "Lat:N");
                DoubleToString(tracker_moving_param.lat, tmp);
                strcat(data, tmp);
                strcat(data, ";");
            }
            else if(tracker_moving_param.lat < 0)
            {
                strcat(data, "Lat:S");
                DoubleToString(tracker_moving_param.lat, tmp);
                strcat(data, tmp);
                strcat(data, ";");
            }

            memset(tmp, 0x00, 100);
            if(tracker_moving_param.lon > 0)
            {
                strcat(data, "Lon:E");
                DoubleToString(tracker_moving_param.lon, tmp);
                strcat(data, tmp);
                strcat(data, ";");
            }
            else if(tracker_moving_param.lon < 0)
            {
                strcat(data, "Lon:W");
                DoubleToString(tracker_moving_param.lon, tmp);
                strcat(data, tmp);
                strcat(data, ";");
            }

            memset(tmp, 0x00, 100);
            sprintf(tmp, "Radius:%dm;", tracker_moving_param.dis);
            strcat(data, tmp);

            memset(tmp, 0x00, 100);
            sprintf(tmp, "Alarm Type:%d;", tracker_moving_param.alarmmode);
            strcat(data, tmp);
        }
        strcat(sms_buf, data);
    }
    else if(received_data.part == 1)
    {
        if(strcmp("OFF", ((char *)received_data.param0)) == 0)
        {
            tracker_moving_param.remindstate = 0;
            tracker_moving_param.dis = 0;
            WriteRecord(NVRAM_EF_TRACKER_MOVING_PARAM_LID, 1, &tracker_moving_param, NVRAM_EF_TRACKER_MOVING_PARAM_SIZE, &error);
            Tracker_Set_Moving_Replay();
            return;
        }
        else if(strcmp("ON", ((char *)received_data.param0)) == 0)
        {
            tracker_moving_param.remindstate = 1;
            if(tracker_moving_param.dis == 0)
            {
                tracker_moving_param.dis = 300;
            }
            WriteRecord(NVRAM_EF_TRACKER_MOVING_PARAM_LID, 1, &tracker_moving_param, NVRAM_EF_TRACKER_MOVING_PARAM_SIZE, &error);
            Tracker_Set_Moving_Replay();
            return;
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
        }
    }
    else if(received_data.part <= 3)
    {
        if(strcmp("ON", ((char *)received_data.param0)) == 0)
        {
            if((Last_valide_data.status == AK_TRUE) || (GPSCurrentLocation == TRUE))
            {
                memset(interval_str, 0, 40);
                memcpy(interval_str[0], received_data.param1, 20);
                memcpy(interval_str[1], received_data.param2, 20);

                for(i = 0; i < received_data.part - 1; i++)
                {
                    if(strlen((char*)interval_str[i]) == 0)
                    {
                        interval[i] = 0xffff;
                        continue ;
                    }

                    if(i == 0)
                    {
                        interval[i] = interval_Time_Manage(interval_str[i], 100, 10000);
                    }
                    else if(i == 1)
                    {
                        interval[i] = interval_Time_Manage(interval_str[i], 0, 2);
                    }

                    if(interval[i] == 0xffff)
                    {
                        sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                        return;
                    }
                }

                tracker_moving_param.remindstate = 1;
                if(interval[0] != 0xffff)
                {
                    tracker_moving_param.dis =  interval[0];
                }
                if(interval[1] != 0xffff)
                {
                    tracker_moving_param.alarmmode =  interval[1];
                }

                //λ��ԭ��Ļ�ȡ������ACC OFF֮���ȡ��ȡ���һ�ζ�λ��λ����Ϊλ��ԭ�㡣
                if((Last_valide_data.status == AK_TRUE)
				#if defined(__ACC_DETECT__)//wnq
                    && (tracker_acc_state == ACC_OFF)
				#endif/*__ACC_DETECT__*/
                    )
                {
                    Get_GPS_Signed_Doble_LatLon();
                    tracker_moving_param.lat = latlon_info.lat;
                    tracker_moving_param.lon = latlon_info.lon;
                    MovingSavePoint = TRUE;
                }


                WriteRecord(NVRAM_EF_TRACKER_MOVING_PARAM_LID, 1, &tracker_moving_param, NVRAM_EF_TRACKER_MOVING_PARAM_SIZE, &error);
                Tracker_Set_Moving_Replay();
                return;

            }
            else if(Command_State == SMS_Command_State)
            {
                SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_MOVING_NOT_LOCATION , NULL);
                return ;
            }
            else
            {
                sprintf(sms_buf, "No GPS data,The displacement alarm setting unsuccessfull!");
            }
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
    }

    Send_Command_Message_Replay();
}
#endif

#ifndef KJX_TEST
/******************************************************************************
 *  Function    -  Tracker_GPS_Delay_Active_Time
 *
 *  Purpose     -  Tracker_GPS_Delay_Active_Time
 *
 *  Description -  GK306 GK301 ������뼤����ʱ5-17S����
 *                        GTM100 ���������ʱʱ������
 * modification history
 * ----------------------------------------
 * v1.0  ,
 *
 *  ָ��: DELAY,17#
 *  ����: OK
 * ----------------------------------------
 * ----------------------------------------
 * v1.0  , 2012-06-01, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_GPS_Delay_Active_Time(void)
{
    S16 error;
    U16  interval = 0xffff;
    U8 interval_str[20];

    if(received_data.part > 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }

    if(received_data.part == 0)
    {
        sprintf(sms_buf, "DELAY:%d;", tracker_delay_active_time.time / 1000);

    }
    else
    {
        memset(interval_str, 0, sizeof(interval_str));
        memcpy(interval_str, received_data.param0, 20);
        interval = interval_Time_Manage(interval_str, 5, 18);
        if(interval < 5 || (interval > 18))
        {
            sprintf(sms_buf, "ERROR:102");//ָ��Ȳ���ȷ
        }
        else
        {
            tracker_delay_active_time.time = interval * 1000;
            WriteRecord(NVRAM_EF_TRACKER_DELAY_ACTIVE_TIME_LID, 1, (void *)&tracker_delay_active_time, NVRAM_EF_TRACKER_DELAY_ACTIVE_TIME_SIZE, &error);
            sprintf(sms_buf, "OK");
        }
    }
}

/******************************************************************************
 *  Function    -  Tracker_Set_GPS_StartMode
 *
 *  Purpose     - ����GPS����ģʽ
 *                       ��������Ч����λ��֮������Ĭ�϶���������
 *  Description -  GPSMODE,0#    //������
 *                       GPSMODE,1#      //������
 *                       GPSMODE,2#      //������
 * modification history
 * ----------------------------------------
 * v1.0  , 2013-05-30, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_GPS_StartMode(void)
{
    U16  interval = 0xffff;
    U8 interval_str[20];

    if(received_data.part > 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }

    if(received_data.part == 0)
    {
	#if defined(__GPS_MT3336__)
        if(gps_first_pwron >= 2)
        {
            sprintf(sms_buf, "GPSMODE:HOT;");
        }
        else if(gps_first_pwron == 1)
        {
            sprintf(sms_buf, "GPSMODE:WARM;");
        }
        else
	#endif
        {
            sprintf(sms_buf, "GPSMODE:CLODE;");
        }
    }
    else
    {
        memset(interval_str, 0, sizeof(interval_str));
        memcpy(interval_str, received_data.param0, 20);
        interval = interval_Time_Manage(interval_str, 0, 2);
        if(interval < 0 || (interval > 2))
        {
            sprintf(sms_buf, "ERROR:102");//ָ��Ȳ���ȷ
        }
        else
        {
		#if defined(__GPS_MT3336__)
            gps_first_pwron = interval;
		#endif
            if(GPSOnFlag)
            {
                GPSNeedOff = TRUE;
                GPS_OFF();
                StartTimer(GPS_ON_TIMER_ID, 5000, GPS_ON);
            }

            sprintf(sms_buf, "OK");
        }
    }
}

/******************************************************************************
 *  Function    -  Tracker_SendData_AccordingTo_Speed
 *
 *  Purpose     -  ���ø����ٶ��ϴ����ݵ�
 *
 *  Description -  SPD,V1,V2#
 *                        OK
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_SendData_AccordingTo_Speed(void)
{
    S16 error;
    U16  interval[2] = {0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[2][20];

    memset(sms_buf, 0, sizeof(sms_buf));
    if(received_data.part == 0)
    {
        sprintf((char *)sms_buf, "SPD:%d,%d;", tracker_ctrl_data.senddataprohibitspeed, tracker_ctrl_data.senddataallowspeed);
    }
    else if(received_data.part <= 2)
    {
        memset(interval_str, 0, 40);
        memcpy(interval_str[0], received_data.param0, 20);
        memcpy(interval_str[1], received_data.param1, 20);
        for(i = 0; i < received_data.part; i++)
        {
            if(strlen((char*)interval_str[i]) == 0)
            {
                interval[i] = 0xffff;
                continue ;
            }

            if((strlen((char*)interval_str[i]) == 1) && (interval_str[i][0] == '0'))
            {
                interval[i] = 0;
            }
            else
            {
                if(i == 0)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 0, 5);
                }
                else
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 5, 20);
                }
            }

            if(interval[i] == 0xffff)
            {
                sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                return;
            }
        }

        if(interval[0] != 0xffff)
        {
            tracker_ctrl_data.senddataprohibitspeed =  interval[0];
        }
        if(interval[1] != 0xffff)
        {
            tracker_ctrl_data.senddataallowspeed =  interval[1];
        }

        WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
        sprintf(sms_buf, "OK");

    }
    else
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
    }
}

/******************************************************************************
 *  Function    -  Tracker_Get_LatLon_TurnTo_String
 *
 *  Purpose     -  ����γ��30000*60��ת��Ϊstring
 *
 *  Description -  LATLON,26C098C,C38D1D1#
 *                       LAT:22.575611,LON:113.916845.
 * ----------------------------------------
 * v1.0  , 2014-06-12, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Get_LatLon_TurnTo_String(void)
{
    char Latbuf[4], Lonbuf[4];
    char Lattemp[12], Lontemp[12];
    U32 Latval = 0, Lonval = 0;
    UINT8 Highbyte = 0, Lowbyte = 0;

    double Lat = 0.0, Lon = 0.0 ;
    U8 i = 0;


    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 2)
    {
        if(strlen((char *)received_data.param0) <= 8 || strlen((char *)received_data.param1) <= 8)
        {
            memset(Latbuf, 0, sizeof(Latbuf));
            memset(Lonbuf, 0, sizeof(Lonbuf));
            memset(Lattemp, 0, sizeof(Lattemp));
            memset(Lontemp, 0, sizeof(Lontemp));

            if(strlen((char *)received_data.param0) % 2 == 1)
            {
                Lattemp[0] = '0';
                memcpy(&Lattemp[1], received_data.param0, strlen(received_data.param0));
            }
            else
            {
                memcpy(&Lattemp[0], received_data.param0, strlen(received_data.param0));
            }

            if(strlen((char *)received_data.param1) % 2 == 1)
            {
                Lontemp[0] = '0';
                memcpy(&Lontemp[1], received_data.param1, strlen(received_data.param1));
            }
            else
            {
                memcpy(&Lontemp[0], received_data.param1, strlen(received_data.param1));
            }

            for(i = 0; i < strlen((char*)Lattemp) / 2; i++)
            {
                if(Lattemp[2*i] >= '0' && Lattemp[2*i] <= '9')
                {
                    Highbyte = Lattemp[2*i] - '0';
                }
                else if(Lattemp[2*i] >= 'A' && Lattemp[2*i] <= 'F') //C = 67 = 0x43   0 = 48 0x30
                {
                    Highbyte = Lattemp[2*i] - 55;
                }
                else if(Lattemp[2*i] >= 'a' && Lattemp[2*i] <= 'f') //c = 99
                {
                    Highbyte = Lattemp[2*i] - 87;
                }

                if(Lattemp[2*i+1] >= '0' && Lattemp[2*i+1] <= '9')
                {
                    Lowbyte = Lattemp[2*i+1] - '0';
                }
                else  if(Lattemp[2*i+1] >= 'A' && Lattemp[2*i+1] <= 'F') //C = 67 = 0x43   0 = 48 0x30   C = 12
                {
                    Lowbyte = Lattemp[2*i+1] - 55;
                }
                else if(Lattemp[2*i+1] >= 'a' && Lattemp[2*i+1] <= 'f')
                {
                    Lowbyte = Lattemp[2*i+1] - 87;
                }

                Latbuf[i] = Highbyte * 16 + Lowbyte;
            }

            for(i = 0; i < strlen((char*)Lontemp) / 2; i++)
            {
                if(Lontemp[2*i] >= '0' && Lontemp[2*i] <= '9')
                {
                    Highbyte = Lontemp[2*i] - '0';
                }
                else if(Lontemp[2*i] >= 'A' && Lontemp[2*i] <= 'F') //C = 67 = 0x43   0 = 48 0x30
                {
                    Highbyte = Lontemp[2*i] - 55;
                }
                else if(Lontemp[2*i] >= 'a' && Lontemp[2*i] <= 'f')
                {
                    Highbyte = Lontemp[2*i] - 87;
                }

                if(Lontemp[2*i+1] >= '0' && Lontemp[2*i+1] <= '9')
                {
                    Lowbyte = Lontemp[2*i+1] - '0';
                }
                else if(Lontemp[2*i+1] >= 'A' && Lontemp[2*i+1] <= 'F') //C = 67 = 0x43   0 = 48 0x30   C = 12
                {
                    Lowbyte = Lontemp[2*i+1] - 55;
                }
                else if(Lontemp[2*i+1] >= 'a' && Lontemp[2*i+1] <= 'f')
                {
                    Lowbyte = Lontemp[2*i+1] - 87;
                }
                Lonbuf[i] = Highbyte * 16 + Lowbyte;
            }

            Latval = HEX_To_U32(&Latbuf[0], 4);
            Lonval = HEX_To_U32(&Lonbuf[0], 4);

            //��������ȸ�ֵΪdouble���ͣ��������double����
            Lat = Latval;
            Lon = Lonval;

            DoubleToString(Lat, Lattemp);
            DoubleToString(Lon, Lontemp);

            Lat = Lat / 30000 / 60;
            Lon = Lon / 30000 / 60;

            memset(Lattemp, 0, sizeof(Lattemp));
            memset(Lontemp, 0, sizeof(Lontemp));

            DoubleToString(Lat, Lattemp);
            DoubleToString(Lon, Lontemp);

            sprintf(sms_buf, "Lat:%s,Lon:%s", Lattemp, Lontemp);
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");
    }
}

/******************************************************************************
 *  Function    -  Tracker_Set_Status_Reply_Process
 *
 *  Purpose     -  �������������ϲ�ѯλ�õľ�γ�����ӵ�ַ
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2014-06-17,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Status_Reply_Process(void)
{
    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 1)
    {
        if(strcmp("ON", ((char *)received_data.param0)) == 0)
        {
            StatusReplyProcess = TRUE;
        }
        else if(strcmp("OFF", ((char *)received_data.param0)) == 0)
        {
            StatusReplyProcess = FALSE;
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:100");
    }
}


/******************************************************************************
 *  Function    -  Tracker_Reback_Address_URL
 *
 *  Purpose     -  �������������ϲ�ѯλ�õľ�γ�����ӵ�ַ
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 01-10-2010,  jwj  written
 * ----------------------------------------
 *  ָ��: URL#
 *  ����: [Date Time:10-10-10 14:28:42] http://maps.google.com/maps?q=N23.111785,E114.409293
 *  ����: NO DATA!
 ******************************************************************************/
void Tracker_Reback_Address_URL(U8* number)
{
    double Now_Lat, Now_Lon;
    U8 len = 0;
    memset(sms_buf, 0, sizeof(sms_buf));
    memset(sys_send_sms.content, 0, sizeof(sys_send_sms.content));

    LOGD(" %s", number);

    if(GPSCurrentLocation == TRUE)
    {
        //ʱ��
        sprintf((char *)sys_send_sms.content, "<");
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.year);
        len = strlen((char *)sys_send_sms.content);
        sys_send_sms.content[len] = '-';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.month);
        sys_send_sms.content[len+3] = '-';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.day);
        sys_send_sms.content[len+6] = ' ';
        sys_send_sms.content[len+7] = ' ';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.hour);
        len = strlen((char *)sys_send_sms.content);
        sys_send_sms.content[len] = ':';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.minute);
        sys_send_sms.content[len+3] = ':';
        strcat((char *)sys_send_sms.content, (char *)Last_valide_data.data_time.second);
        sys_send_sms.content[len+6] = '>';
        sys_send_sms.content[len+7] = ' ';
        len = strlen((char *)sys_send_sms.content);

        Get_GPS_Unsigned_Doble_LatLon();

        strcat((char *)sys_send_sms.content, tracker_ctrl_data.URL_Address);

        //�ϱ�γN: 0000 0011   S:0000 1000
        if((Last_valide_data.location_info.direct & 0x0f) == GPS_LOCATION_DIR_S)
        {
            strcat((char *)sys_send_sms.content, "S");
            strcat((char *)sys_send_sms.content, latlon_info.lat_string);
        }
        else
        {
            strcat((char *)sys_send_sms.content, "N");
            strcat((char *)sys_send_sms.content, latlon_info.lat_string);
        }

        //������E:0001 0000  W:1100 0000
        if((Last_valide_data.location_info.direct & 0xf0) == GPS_LOCATION_DIR_E)
        {
            strcat((char *)sys_send_sms.content, ",E");
            strcat((char *)sys_send_sms.content, latlon_info.lon_string);
        }
        else
        {
            strcat((char *)sys_send_sms.content, ",W");
            strcat((char *)sys_send_sms.content, latlon_info.lon_string);
        }

        if(strlen((char*) sys_rcv_sms.num))
        {
		#if defined(__STACK_SENDSMS__)
            SetSendSMS(TRUE, (U8 *) sys_rcv_sms.num, 0, sys_send_sms.content);
		#else
            Tracker_Send_Ascii_Msg((U8*)number , (void*)sys_send_sms.content);
		#endif
        }
        else
        {
            strcat((char *)sms_buf, sys_send_sms.content);
            Send_Command_Message_Replay();
        }
    }
	else
	{
		if(strlen((char*) sys_rcv_sms.num))
        {
		#if defined(__STRING_USE_ARRAY__)
	        memset(&sys_send_sms, 0, sizeof(SYS_SMS_STRUCT));
	        if(CurrentLang == 1)
	        {
	            //����ȡ�ĳ��ȸ�ʵ�ʳ��Ȳ�һ�»�����
	            sys_send_sms.len = app_ucs2_strlen((char *)gps_noLocation_code[1]) * 2;
	            memcpy(sys_send_sms.content, &gps_noLocation_code[1], sys_send_sms.len);
	            SetSendSMS(FALSE, sys_rcv_sms.num, NULL, sys_send_sms.content);
	        }
	        else
	        {
	            sys_send_sms.len = strlen((char *)gps_noLocation_code[0]);
	            memcpy(sys_send_sms.content, &gps_noLocation_code[0], sys_send_sms.len);
	            SetSendSMS(TRUE, sys_rcv_sms.num, NULL, sys_send_sms.content);
	        }
		#else
	        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_GPS_NO_LOCATION, NULL);
		#endif
		}
		else
		{
			strcpy((char*)sms_buf, "GPS Not Location!");
            Send_Command_Message_Replay();
		}
	}
}
#endif

#endif

/******************************************************************************
 *  Function    -  Tracker_Query_GetLBS_Address
 *
 *  Purpose     -  ��ѯ�ն�λ��(GPS��λ���ɹ�����LBS��ַ)
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-06-14, guojie  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Query_GetLBS_Address(void)
{
#ifndef KJX_TEST
#if defined(__SMS_APP_DEBUG__)
	LOGD("begin");
#endif

	if(IsMyTimerExist(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER))
		StopTimer(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER);
	
	gprs_send_type = GPRS_LBS_PHB_INFO;
	Tracker_Socket_Send_AllType_GPRS_Data();
	if(soc_content.soc_state >= SOC_CONNECTED)
	{
		StartTimer(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER, 3 * 60 * 1000, Tracker_Qurey_GetLBS_Address_Fail_SendSMS);
	}
	else
	{
		StartTimer(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER, 5 * 60 * 1000, Tracker_Qurey_GetLBS_Address_Fail_SendSMS);
	}
#endif
}

/******************************************************************************
 *  Function    -  Tracker_Set_Center_PhoneNum
 *
 *  Purpose     -  �������ĺ���
 *
 *  Description - ������SOS����ſ����������ĺ���
 *
 * modification history   CENTER,A,13810001000#
  * ----------------------------------------
 * v1.0  , 2012-08-09, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Center_PhoneNum(void)
{
#ifndef KJX_TEST
    S16 error;
    char centernum[FAMILY_PHB_NUM_LEN_MIN];
    U8 lenth = 0;
    BOOL is_num = TRUE;
    char temp1[200] = {0};

    memset(sms_buf, 0, sizeof(sms_buf));
    memset(centernum, 0, sizeof(centernum));

    LOGD(" %d", tracker_sos_phb.phb_sum);

    //Ȩ�޷���1:  ���ĺ���ֻ��SOS ���������
    //Ȩ�޷���2:  �����ĺ���Ϊ��ʱ��������������;�����ĺ��������ã�ֻ�����ĺ��뱾����޸ġ�
    if(tracker_permit_level.commandpermit == 0)
    {
        if((Command_State == SMS_Command_State)
                && (Delete_SmsPrefix_Confirm_SOSNum() == 0XFF)
                && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE)
                && (SuperCommandHead == FALSE))
        {
            sprintf(sms_buf, "ERROR:111");                     //����SOS����
            return ;
        }
    }
    else if(tracker_permit_level.commandpermit == 1)
    {
        if((Command_State == SMS_Command_State) &&
                (strlen(tracker_sos_phb.center_num) > 0) && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE) && (SuperCommandHead == FALSE))
        {
            sprintf(sms_buf, "ERROR:116");                     //�������ĺ���
            return ;
        }
    }

    if(received_data.part == 0)
    {
        memset(temp1, 0, 200);
        if(strlen((char *)tracker_sos_phb.center_num) == 0)
        {
            sprintf(temp1, "Center number is empty.");
        }
        else
        {
            sprintf(temp1, "Center number:%s", (S8*)tracker_sos_phb.center_num);
        }
        strcpy((char*)sms_buf, (char*)temp1);
        return;
    }

    if(strlen((char*)received_data.param0) != 1)
    {
        sprintf(sms_buf, "ERROR:101");   //�������ݳ�����Χ
        return ;
    }

    if(received_data.param0[0] == 'A') //Ϊ��Ӻ���
    {
        if((received_data.part != 2))
        {
            sprintf(sms_buf, "ERROR:100");    //ָ��Ȳ���ȷ
        }
        else
        {
            strcpy(centernum, (char*)received_data.param1);
            lenth = strlen((char *)centernum);
            is_num = SetNumber_is_num((S8*)centernum, lenth);

            if(lenth > FAMILY_PHB_NUM_LEN_MIN - 1 || lenth < 3 || is_num == FALSE)
            {
                sprintf(sms_buf, "ERROR:101");
            }
            else
            {
                memset(tracker_sos_phb.center_num, 0, FAMILY_PHB_NUM_LEN_MIN);
                memcpy(tracker_sos_phb.center_num, centernum, lenth);
                WriteRecord(NVRAM_EF_TRACKER_SOS_PHB_LID, 1, &tracker_sos_phb, NVRAM_EF_TRACKER_SOS_PHB_SIZE, &error);
			#if defined(__PARAM_BACKUP__)
                StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
			#endif
                sprintf(sms_buf, "OK");

                memset(temp1, 0, 200);
                sprintf(temp1, "!Center number:%s", (S8*)tracker_sos_phb.center_num);
                strcat((char*)sms_buf, (char*)temp1);
            }
        }
    }
    else if(received_data.param0[0] == 'D')
    {
        if(received_data.part != 1)
        {
            sprintf(sms_buf, "ERROR:100");
        }
        else
        {
            memset(tracker_sos_phb.center_num, 0, FAMILY_PHB_NUM_LEN_MIN);
            WriteRecord(NVRAM_EF_TRACKER_SOS_PHB_LID, 1, &tracker_sos_phb, NVRAM_EF_TRACKER_SOS_PHB_SIZE, &error);
		#if defined(__PARAM_BACKUP__)
            StartTimer(IMEI_SMS_BACKUP_TIMER_ID, 5000, Backup_SMS_Delete_All_Msg);
		#endif
            sprintf(sms_buf, "OK");
            memset(temp1, 0, 200);
            sprintf(temp1, "!Center number is empty!");
            strcat((char*)sms_buf, (char*)temp1);
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");
    }
#endif
}


#if defined(__OIL_ELECTRONIC_CONTROL__)
/******************************************************************************
 *  Function    -  Tracker_Set_CutPower_Status
 *
 *  Purpose     - ���öϵ�����״̬
 *
 *  Description - POWERALM,ON[,M][,T1][,T2][,T3]#  // POWERALM,ON,T[,M]#  T (2-60S)   M=0,GPRS,  M=1,GPRS+SMS
 *                       POWERALM,OFF#
 *                       POWERALM#
 *                       M=1,    M=0,GPRS; M=1;GPRS+SMS; M=2,GPRS+SMS+CALL
 *                       T1 = 5S       (2--60S)   �ϵ���ʱ��
 *                       T2 = 300S   (1--3600S)  �����Сʱ��
 *                       T3 = 0         (0-3600S)   ��ֹ����ʱ��
 * modification history
 * ----------------------------------------
 * v1.0  , 2012-12-21, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_CutPower_Status(void)
{
    S16 error;
    U16  interval[4] = {0xffff, 0xffff, 0xffff, 0xffff};
    U8 i = 0;
    U8 interval_str[4][20];

    memset(sms_buf, 0, sizeof(sms_buf));

    if(received_data.part == 0)
    {
        if(tracker_cut_power.remindstate)
        {
            sprintf(sms_buf, "POWERALM:ON,%d,%d,%d,%d;", tracker_cut_power.alarmmode,
                    tracker_cut_power.alarmdelaytime / 1000, tracker_cut_power.chargemintime / 1000,
                    tracker_cut_power.prohibitalarmtime / 1000);
        }
        else
        {
            sprintf(sms_buf, "POWERALM:OFF;");
        }
    }
    else if(strcmp("ON", ((char *)received_data.param0)) == 0)
    {
        if(received_data.part > 5)
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        if(received_data.part == 1)
        {
            tracker_cut_power.remindstate = 1;
        }
        else   //if(received_data.part != 1)
        {
            memset(interval_str, 0, 80);
            memcpy(interval_str[0], received_data.param1, 20);
            memcpy(interval_str[1], received_data.param2, 20);
            memcpy(interval_str[2], received_data.param3, 20);
            memcpy(interval_str[3], received_data.param4, 20);

            for(i = 0; i < received_data.part - 1; i++)
            {
                if(strlen((char*)interval_str[i]) == 0)
                {
                    interval[i] = 0xffff;
                    continue ;
                }

                if(i == 0)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 0, 2);
                }
                else if(i == 1)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 2, 60);
                }
                else if(i == 2)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 1, 3600);
                }
                else if(i == 3)
                {
                    interval[i] = interval_Time_Manage(interval_str[i], 0, 3600);
                }

                if(interval[i] == 0xffff)
                {
                    sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
                    return;
                }
            }

            tracker_cut_power.remindstate = 1;
            if(interval[0] != 0xffff)
            {
                tracker_cut_power.alarmmode =  interval[0];
            }
            if(interval[1] != 0xffff)
            {
                tracker_cut_power.alarmdelaytime =  interval[1] * 1000;
            }
            if(interval[2] != 0xffff)
            {
                tracker_cut_power.chargemintime =  interval[2] * 1000;
            }
            if(interval[3] != 0xffff)
            {
                tracker_cut_power.prohibitalarmtime =  interval[3] * 1000;
            }
        }

        WriteRecord(NVRAM_EF_TRACKER_CUT_POWER_LID, 1, &tracker_cut_power, NVRAM_EF_TRACKER_CUT_POWER_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else if(strcmp("OFF", ((char *)received_data.param0)) == 0)
    {
        if(received_data.part != 1)
        {
            sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
            return;
        }

        tracker_cut_power.remindstate = 0;
        WriteRecord(NVRAM_EF_TRACKER_CUT_POWER_LID, 1, &tracker_cut_power, NVRAM_EF_TRACKER_CUT_POWER_SIZE, &error);
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");  //ָ���ʽ����
    }

}

/******************************************************************************
 *  Function    -  Tracker_Set_OilElectronic
 *
 *  Purpose     -  �͵�Ͽ�/�ָ�
 *
 *  Description -        RELAY,1#  ���͵�
 *                             RELAY,0#  �ָ��͵�
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-08-08, guojie  written
  * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_OilElectronic(void)
{
    S16 error;
    U16  interval = {0xffff};
    U8 interval_str[20];

    memset(sms_buf, 0, sizeof(sms_buf));
    memset(sys_send_sms.content, 0, sizeof(sys_send_sms.content));
    if((Command_State == SMS_Command_State) && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE) && (SuperCommandHead == FALSE))
    {
#if defined(__STRING_USE_ARRAY__)
        memset(&sys_send_sms, 0, sizeof(SYS_SMS_STRUCT));
        if(CurrentLang == 1)
        {
            sys_send_sms.len = app_ucs2_strlen((char *)oilelec_not_center[1]) * 2;
            memcpy(sys_send_sms.content, &oilelec_not_center[1], sys_send_sms.len);
            SetSendSMS(FALSE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
        }
        else
        {
            sys_send_sms.len = strlen((char *)oilelec_not_center[0]);
            memcpy(sys_send_sms.content, &oilelec_not_center[0], sys_send_sms.len);
            SetSendSMS(TRUE,  sys_rcv_sms.num, NULL, sys_send_sms.content);
        }
#else
        SetSendSMS(FALSE,  sys_rcv_sms.num, STR_SMS_OILELEC_NOT_CENTER , NULL);
#endif
        return;
    }

    if(received_data.part > 1)
    {
        if(Command_State == ONLine_Command_State)
        {
            sprintf(sms_buf, "ERROR:100");
            Tracker_Online_State = TRACKER_ONLINE_RELAY;
            gprs_send_type = GPRS_ONLINE_RESULT_INFO;
            Tracker_Socket_Send_Current_Data();
        }
        else if(Command_State == SMS_Command_State)
        {
            memset(sys_send_sms.content, 0, sizeof(sys_send_sms.content));
            sprintf(sys_send_sms.content, "ERROR:100");   //ָ��Ȳ���ȷ
            SetSendSMS(TRUE, sys_rcv_sms.num, NULL, sys_send_sms.content);
        }
        else
        {
            sprintf(sms_buf, "ERROR:100");
            Send_Command_Message_Replay();
        }
        return;
    }


    if(received_data.part == 0)
    {
        if(tracker_ctrl_data.oilstate == 1)
        {
            sprintf(sms_buf, "RELAY:1;");
        }
        else
        {
            sprintf(sms_buf, "RELAY:0;");
        }
        Send_Command_Message_Replay();
    }
    else
    {
        memset(interval_str, 0, 20);
        memcpy(interval_str, received_data.param0, 20);

        if(strlen((char*)interval_str) == 0)
        {
            interval = 0xffff;
        }
        else
        {
            interval = interval_Time_Manage(interval_str, 0, 1);
        }

        LOGD(" %d", interval);

        if(interval == 0xffff)
        {
            if(Command_State == ONLine_Command_State)
            {
                sprintf(sms_buf, "ERROR:101");
                Tracker_Online_State = TRACKER_ONLINE_RELAY;
                gprs_send_type = GPRS_ONLINE_RESULT_INFO;
                Tracker_Socket_Send_Current_Data();
            }
            else if(Command_State == SMS_Command_State)
            {
                sprintf(sys_send_sms.content, "ERROR:101");    //��ʱ���ݳ�����Χ
                SetSendSMS(TRUE, sys_rcv_sms.num, NULL, sys_send_sms.content);
            }
            else
            {
                sprintf(sms_buf, "ERROR:101");
                Send_Command_Message_Replay();
            }
            return;
        }

        if(interval == 1)
        {
            Tracker_Set_OilElectronic_Off();
        }
        else
        {
            Tracker_Set_OilElectronic_On();
        }
    }

}
#endif

#if defined(__GPS_ON_MTK__)
/**************************************************************************************
*  Function    -  Tracker_Set_Blindalarm
*
*  Purpose	   -  ����ä���澯����
*
*  Description -		BLINDALM,<A>[,B][,C,][M]#
* 							    	A=ON/OFF��GPS ä���������أ�Ĭ��ֵ��OFF
* 								B=5��600 �룻ʱ�䷶Χ��Ĭ��ֵ��60 ��
* 								C=5��600 �룻ʱ�䷶Χ��Ĭ��ֵ��20 ��
* 								M=0/1�������ϱ���ʽ��0 ��GPRS��1 SMS+GPRS��Ĭ��ֵ��1
* 					BLINDALM#
* 							��ѯ�����õĲ���
* modification history
* ----------------------------------------
* v1.0	, 2015-01-15, xiebiao  written
* ----------------------------------------
***************************************************************************************/
void Tracker_Set_Blindalarm(void)
{
    S16 error;
    U16 times = 0;
    char status_s[10], rep_s[10];

    LOGD("---entry Tracker_Set_Blindalarm=:%s,%s,%s,%s,%s"
         , received_data.main_str, received_data.param0, received_data.param1, received_data.param2, received_data.param3);
    if(0 == received_data.part)
    {
        //---------��ѯ����-------

        ReadRecord(NVRAM_EF_TRACKER_GPSBLINDAREA_ALARM_LID, 1, (void *)&tracker_gpsblindarea_alarm, NVRAM_EF_TRACKER_GPSBLINDAREA_ALARM_SIZE, &error);
        if(tracker_gpsblindarea_alarm.remindstate)
        {
            strcpy(status_s, "ON");
        }
        else
        {
            strcpy(status_s, "OFF");
            sprintf(sms_buf, "Blind Alarm: OFF");
            return;
        }

        if(0 == tracker_gpsblindarea_alarm.commit_type)
        {
            strcpy(rep_s, "GPRS");
        }
        else
        {
            strcpy(rep_s, "GPRS+SMS");
        }

        sprintf(sms_buf, "Blind_Alarm:%s, in:%d, out:%d, report:%s"
                , status_s, tracker_gpsblindarea_alarm.in_blind_times, tracker_gpsblindarea_alarm.out_blind_times, rep_s);
    }
    else  //��������
    {
        if(0 == strcmp("ON", received_data.param0))
        {
            tracker_gpsblindarea_alarm.remindstate = 1;
        }
        else if(0 == strcmp("OFF", received_data.param0))
        {
            tracker_gpsblindarea_alarm.remindstate = 0;
        }
        else
        {
            sprintf(sms_buf, "ERROR: BLINDALM,ON#");
            return;
        }

        if(strlen(received_data.param1) > 0)
        {
            times = interval_Time_Manage(received_data.param1, 5, 600);
            if(0xFFFF == times)
            {
                sprintf(sms_buf, "ERROR:111");
                return;
            }
        }
        else
        {
            times = 60;
        }
        tracker_gpsblindarea_alarm.in_blind_times = times;

        if(strlen(received_data.param2) > 0)
        {
            times = interval_Time_Manage(received_data.param2, 5, 600);
            if(0xFFFF == times)
            {
                sprintf(sms_buf, "ERROR:111");
                return;
            }
        }
        else
        {
            times = 20;
        }
        tracker_gpsblindarea_alarm.out_blind_times = times;

        if(strlen(received_data.param3) > 0)
        {
            times = interval_Time_Manage(received_data.param3, 0, 1);
            if(0xFFFF == times)
            {
                sprintf(sms_buf, "ERROR:111");
                return;
            }
        }
        else
        {
            times = 1;
        }
        tracker_gpsblindarea_alarm.commit_type = times;

        WriteRecord(NVRAM_EF_TRACKER_GPSBLINDAREA_ALARM_LID, 1, &tracker_gpsblindarea_alarm, NVRAM_EF_TRACKER_GPSBLINDAREA_ALARM_SIZE, &error);

        if(tracker_gpsblindarea_alarm.remindstate)
        {
            strcpy(status_s, "ON");
        }
        else
        {
            strcpy(status_s, "OFF");
            sprintf(sms_buf, "OK#BLINDALM# Blind Alarm: OFF");
            return;
        }

        if(0 == tracker_gpsblindarea_alarm.commit_type)
        {
            strcpy(rep_s, "GPRS");
        }
        else
        {
            strcpy(rep_s, "GPRS+SMS");
        }

        sprintf(sms_buf, "OK#BLINDALM# Blind_Alarm:%s, in:%d, out:%d, report:%s"
                , status_s, tracker_gpsblindarea_alarm.in_blind_times, tracker_gpsblindarea_alarm.out_blind_times, rep_s);

    }
}
#endif

#if defined(__KD6113_WORK_MODE__)
/******************************************************************************
 *  Function    -  Tracker_Set_Work_Mode
 *
 *  Purpose     -  ˯��ģʽ��ѯ����
 *
 *  Description -        WORKMODE,M,T# 	���ù���ģʽģʽ 
 *									M:����ģʽ1 ����ģʽ��2 ÿ��ָ��ʱ�䶨λһ�Σ� 3 ���ʱ����λһ��
 *									T:����ʱ�䣬1 ģʽ��Ϊ��ʱ���(10~1800��)��2 ģʽ��λ�ƶ���24Сʱ��ʱ��(��8:30 ��ת��Ϊ0830)��3 �ƶ���ʱ��������λСʱ
 *				    WORKMODE# 		�鿴��ǰ����
 * modification history
  * ----------------------------------------
 * v1.0  , 2015-01-15, xiebiao  written
  * ----------------------------------------
 ******************************************************************************/
void Tracker_Set_Work_Mode(void)
{
	S16 error;
	U8 str_mcp[128] = {0};
	U16 interval1, interval2;

	LOGD("%s, %s", received_data.param0, received_data.param1);

	memset(sms_buf, 0, sizeof(sms_buf));

	if(received_data.part == 0)//�鿴��ǰģʽ
	{
		sprintf(sms_buf, "Work Mode:%d, %d", tracker_ctrl_data.workmode.type, tracker_ctrl_data.workmode.time);
	}
	else if(received_data.part == 2)
	{
		interval1 = interval_Time_Manage(received_data.param0, MODE_WORK_BEGIN+1, MODE_WORM_END-1);//����ģʽ//xb add 20150630 �¹滮�Ѿ�ȥ����ģʽMODE_SET_TIME
		if(interval1 == 0xffff)
		{
			sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
        	if(Command_State == ONLine_Command_State)
        	{
            	Tracker_Online_State = TRACKER_ONLINE_WORKMODE_FAIL;
	            gprs_send_type = GPRS_ONLINE_RESULT_INFO;
	            Tracker_Socket_Send_Current_Data();
	        }			
			return;
		}

		switch(interval1)
		{
		case MODE_WORK_1:
			interval2 = interval_Time_Manage(received_data.param1, 10, 1800);//��λ��
			break;
		case MODE_WORK_2:
			interval2 = interval_Time_Manage(received_data.param1, 10, 7200);//��λ����
			break;
		case MODE_WORK_3:
			if(atoi((char*)received_data.param1) == 0)
			{
				interval2 = 0;
			}
			else
			{
				interval2 = interval_Time_Manage(received_data.param1, 5, 7200);//��λ����
			}
			break;
		}

		if(interval2 == 0xffff)
		{
			sprintf(sms_buf, "ERROR:101");//���ݳ�����Χ
        	if(Command_State == ONLine_Command_State)
	        {
	            Tracker_Online_State = TRACKER_ONLINE_WORKMODE_FAIL;
	            gprs_send_type = GPRS_ONLINE_RESULT_INFO;
	            Tracker_Socket_Send_Current_Data();
	        }			
			return;
		}

		LOGD("interval1:%d, interval2:%d", interval1, interval2);

		tracker_ctrl_data.workmode.type = interval1;
		tracker_ctrl_data.workmode.time = interval2;
		tracker_ctrl_data.workmode.flag = 0;
		WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);//xb add 2015-5-5 ��ֹ�ػ����ߵ��絼�±�־û����

		//֪ͨ��Ƭ���ӿ�xb add 2015-1-15
		sprintf(str_mcp, "AT^GT_CM=04,%d,%d#", interval1, interval2);
		Tracker_Send_Message_To_MCU(str_mcp);
		
        if(Command_State == ONLine_Command_State)
        {
            Tracker_Online_State = TRACKER_ONLINE_WORKMODE_SUCCESS;
            gprs_send_type = GPRS_ONLINE_RESULT_INFO;
            Tracker_Socket_Send_Current_Data();
        }

		switch(tracker_ctrl_data.workmode.type)
		{
		case MODE_WORK_1:
			if(IsMyTimerExist(GPS_DSDW_SCANER_TIMER_ID))
				StopTimer(GPS_DSDW_SCANER_TIMER_ID);
			if(IsMyTimerExist(TRACKER_POWER_OFF_TIMER_ID))
				StopTimer(TRACKER_POWER_OFF_TIMER_ID);
			if(IsMyTimerExist(TRACKER_POWER_OFF_WAIT_TIMER_ID))
				StopTimer(TRACKER_POWER_OFF_WAIT_TIMER_ID);
			if(IsMyTimerExist(TRACKER_POWER_OFF_DELAY_TIMER_ID))
				StopTimer(TRACKER_POWER_OFF_DELAY_TIMER_ID);
			
			tracker_ctrl_data.gps_time_interval = tracker_ctrl_data.workmode.time * 1000;
			GPS_ON();

            DistanceTimeDelay = TRUE;
            Tracker_Send_Detect_Timing();
		case MODE_WORK_3:
			if(IsMyTimerExist(TRACKER_POWER_OFF_TIMER_ID))
				StopTimer(TRACKER_POWER_OFF_TIMER_ID);
			if(IsMyTimerExist(TRACKER_POWER_OFF_WAIT_TIMER_ID))
				StopTimer(TRACKER_POWER_OFF_WAIT_TIMER_ID);
			if(IsMyTimerExist(TRACKER_POWER_OFF_DELAY_TIMER_ID))
				StopTimer(TRACKER_POWER_OFF_DELAY_TIMER_ID);
			if(IsMyTimerExist(GPS_DSDW_SCANER_TIMER_ID))
				StopTimer(GPS_DSDW_SCANER_TIMER_ID);
			
			StartTimer(GPS_DSDW_SCANER_TIMER_ID, 10*1000, Gps_Dsdw_Open); //10S��������ʱ��λ cjt
			break;
		case MODE_WORK_2:
			if(IsMyTimerExist(GPS_DSDW_SCANER_TIMER_ID))
				StopTimer(GPS_DSDW_SCANER_TIMER_ID);
			if(IsMyTimerExist(TRACKER_POWER_OFF_WAIT_TIMER_ID))
				StopTimer(TRACKER_POWER_OFF_WAIT_TIMER_ID);			
			if(IsMyTimerExist(TRACKER_POWER_OFF_TIMER_ID))
				StopTimer(TRACKER_POWER_OFF_TIMER_ID);
			if(IsMyTimerExist(TRACKER_POWER_OFF_DELAY_TIMER_ID))
				StopTimer(TRACKER_POWER_OFF_DELAY_TIMER_ID);
			
			StartTimer(TRACKER_POWER_OFF_TIMER_ID, 5 * 60 * 1000, Tracker_WorkMode_Internval_Timeout);			
			
			Tracker_Init_GPS_Backup_Data();
			break;
		}
		
		sprintf(sms_buf, "OK!");
	}
	else
	{
		sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        if(Command_State == ONLine_Command_State)
        {
           	Tracker_Online_State = TRACKER_ONLINE_WORKMODE_FAIL;
	        gprs_send_type = GPRS_ONLINE_RESULT_INFO;
	        Tracker_Socket_Send_Current_Data();
	    }		
	}
}
#endif/*__KD6113_WORK_MODE__*/

#if defined(__KD6113_POWER_ON_ALARM__)
/******************************************************************************
 *  Function    -  Tracker_Set_BootOn_Alarm
 *
 *  Purpose     -  ���õ�ǰ��������״̬
 *
 *  Description -        BOOTALM#  �鿴��ǰ��������״̬
 *                             BOOTALM,ON#  �򿪿�������
 *                             BOOTALM,OFF#  �رտ�������
 * modification history
 * ----------------------------------------
 * v1.0  , 2015-01-19, xiebiao  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Set_BootOn_Alarm(void)
{
	S16 error;

	memset(sms_buf, 0, sizeof(sms_buf));

	if(received_data.part == 0)
	{
		if(tracker_ctrl_data.poweronAlarm == 1)
		{
			sprintf(sms_buf, "BOOTALM:ON");
		}
		else
		{
			sprintf(sms_buf, "BOOTALM:OFF");
		}
	}
	else if(received_data.part == 1)
	{
		if(strcmp("ON", ((char*)received_data.param0)) == 0)
		{
			tracker_ctrl_data.poweronAlarm = 1;
			WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
			
			sprintf(sms_buf, "OK!Set BootAlarm ON!");
		}
		else if(strcmp("OFF", ((char*)received_data.param0)) == 0)
		{
			tracker_ctrl_data.poweronAlarm = 0;
			WriteRecord(NVRAM_EF_TRACKER_CTRL_DATA_LID, 1, &tracker_ctrl_data, NVRAM_EF_TRACKER_CTRL_DATA_SIZE, &error);
			
			sprintf(sms_buf, "OK!Set BootAlarm OFF!");
		}
		else
		{
			sprintf(sms_buf, "ERROR:102");
		}
	}
}
#endif/*__KD6113_POWER_ON_ALARM__*/


/******************************************************************************
 *  Function    -  Tracker_Led_Test_Delay_Reply
 *
 *  Purpose     -  LED����ʱ���ӳٻظ�����LED����һ���Ա�۲�
 *
 *  Description - 
 *                      
 *                      
 * modification history
 * ----------------------------------------
 * v1.0  , 2015-01-19, xiebiao  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Led_Test_Delay_Reply(void)
{
	sprintf(sms_buf, "OK!LEDON!");
}

/******************************************************************************
 *  Function    -  Tracker_Set_LED_ON
 *
 *  Purpose     -  ��LED״̬��
 *
 *  Description - 
 *                      
 *                      
 * modification history
 * ----------------------------------------
 * v1.0  , 2015-01-19, xiebiao  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Set_LED_ON(void)
{
#ifndef KJX_TEST
	memset(sms_buf, 0, sizeof(sms_buf));

	if(received_data.part == 0)
	{
		pmu_drv_keypad_blink(KAL_TRUE);

		if(PhoneTestMode)
		{
			StartTimer(TRACKER_PWR_LIGHT_TIMER, 2000, Tracker_Led_Test_Delay_Reply);
		}
		else
		{
			sprintf(sms_buf, "OK!LEDON!");
		}
	}
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Set_LED_OFF
 *
 *  Purpose     -  ��LED״̬��
 *
 *  Description - 
 *                      
 *                      
 * modification history
 * ----------------------------------------
 * v1.0  , 2015-01-19, xiebiao  written
 * ----------------------------------------
 ******************************************************************************/
void Tracker_Set_LED_OFF(void)
{
	memset(sms_buf, 0, sizeof(sms_buf));

	if(received_data.part == 0)
	{
		pmu_drv_keypad_blink(KAL_FALSE);

		sprintf(sms_buf, "OK!LEDOFF!");
	}
}

//------------- ������-----------------------------
static U16 g_cur_min = 10;  //��������������
static U16 g_cur_max = 500;  //��������������

void Tracker_Charge_Test(void)
{
#ifndef KJX_TEST
    double vol = 0, cur = 0;
    static U8 charge_times = 0; //�����������ɹ�����10��ʧ�ܹ���

    Get_Battery_Vol_1(&vol, &cur, NULL);
    charge_times++;

#if 1
    sprintf(sms_buf, " ��%d��(��ֵ%d-%d)����current=%5.2fma ��ѹbat=%5.2fv"
            , charge_times, g_cur_min, g_cur_max, cur, vol);
    rmmi_write_to_uart((kal_uint8*)sms_buf, strlen(sms_buf), KAL_TRUE);
#endif

    //�����ɹ�
    if(cur >= g_cur_min && cur <= g_cur_max)
    {
        sprintf(sms_buf, "OK!charge_OK!current=%5.2fma bat=%5.2fv", cur, vol);
        rmmi_write_to_uart((kal_uint8*)sms_buf, strlen(sms_buf), KAL_TRUE);
        charge_times = 0; //����
        //Send_Command_Message_Replay(sms_buf);
        return;
    }

    //����ʧ��
    if(charge_times < 10)
    {
        StartTimer(TRACKER_CHARGE_TEST_TIMER_ID, 1000, Tracker_Charge_Test);
    }
    else
    {
        sprintf(sms_buf, "error!charge_error!current=%5.2fma bat=%5.2fv", cur, vol);
        rmmi_write_to_uart((kal_uint8*)sms_buf, strlen(sms_buf), KAL_TRUE);
        charge_times = 0; //����
        //Send_Command_Message_Replay(sms_buf);
    }
#endif
}

#if defined(__GPS_FENCE__)
/******************************************************************************
 *  Function    -  Tracker_Set_Fence_Circle_Single
 *
 *  Purpose     -  Բ�β�������
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Fence_Circle_Single(void)
{
    double  data_lon, data_lat;
    char temp[50];
    S16 error;
    U8 str_len;
    BOOL rpt = TRUE;
    double  data;

    if((Get_GPS_Coordinate((char *)(received_data.param2), &data_lat) != FALSE)
            || ((*received_data.param3 == '0') && (*received_data.param2 == '0')))
    {
        ;
    }
    else
    {
        LOGD("false rpt3");
        rpt = FALSE;
    }
    if(((Get_GPS_Coordinate((char *)(received_data.param3), &data_lon) != FALSE))
            || ((*received_data.param2 == '0') && (*received_data.param3 == '0')))
    {
        ;
    }
    else
    {
        LOGD("false rpt4");
        rpt = FALSE;
    }
    if(data_lat > 90)
    {
        rpt = FALSE;
    }
    if(interval_Time_Manage((received_data.param4), 100, 9999) == 0XFFFF)
    {
        sprintf(sms_buf, "ERROR:101");//����������Χ
        return ;
    }
    if((strcmp("IN", ((char *)received_data.param5)) == 0)
            || (strcmp("OUT", ((char *)received_data.param5)) == 0)
            || (strlen(((char *)received_data.param5)) == 0))
    {
        ;
    }
    else
    {
        rpt = FALSE;
    }

    if(rpt == TRUE)
    {
        tracker_electronic_fence.FenceType = Fence_Circle;
        tracker_electronic_fence.dis = interval_Time_Manage((received_data.param4), 100, 9999);
        if((data_lat == 0) && (data_lon == 0))
        {
            if((sys_gps_state == GPS_LOCATION_STATE))
            {
                Get_GPS_Signed_Doble_LatLon();
                tracker_electronic_fence.lat = latlon_info.lat;
                tracker_electronic_fence.lon = latlon_info.lon;

                if(latlon_info.lat < 0)
                {
                    tracker_electronic_fence.latzone = 1;
                }
                else
                {
                    tracker_electronic_fence.latzone = 0;
                }

                if(latlon_info.lon < 0)
                {
                    tracker_electronic_fence.lonzone = 1;
                }
                else
                {
                    tracker_electronic_fence.lonzone = 0;
                }
            }
            else
            {
                sprintf(sms_buf, "FAIL! GPS Fix Invaid");
                return;
            }
        }
        else
        {
            tracker_electronic_fence.lat = data_lat;
            tracker_electronic_fence.lon = data_lon;

            if(data_lat < 0)
            {
                tracker_electronic_fence.latzone = 1;
            }
            else
            {
                tracker_electronic_fence.latzone = 0;
            }

            if(data_lon < 0)
            {
                tracker_electronic_fence.lonzone = 1;
            }
            else
            {
                tracker_electronic_fence.lonzone = 0;
            }
        }
        if(strcmp("ON", ((char *)received_data.param0)) == 0)
        {
            tracker_electronic_fence.state = KAL_TRUE;
        }
        else
        {
            tracker_electronic_fence.state = KAL_FALSE;
        }

        if(strcmp("IN", ((char *)received_data.param5)) == 0)
        {
            tracker_electronic_fence.FenceAlarmType = Fence_IN;
        }
        else if(strcmp("OUT", ((char *)received_data.param5)) == 0)
        {
            tracker_electronic_fence.FenceAlarmType = Fence_OUT;
        }
        else if((strcmp("INOUT", ((char *)received_data.param5)) == 0) || (strlen((char*)received_data.param5) == 0))
        {
            tracker_electronic_fence.FenceAlarmType = Fence_IN_OUT;
        }

        LOGD("tracker_electronic_fence.FenceAlarmType %d", tracker_electronic_fence.FenceAlarmType);
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
        return;
    }

    tracker_electronic_fence.lon1 = 0;
    tracker_electronic_fence.lat1 = 0;
    WriteRecord(NVRAM_EF_TRACKER_ELECTRONIC_FENCE_LID, 1, (void *)&tracker_electronic_fence, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE, &error);

    isLastFenceIn = Fence_NO;
    /*��GPS����ʱ��ο�������Χ��*/
    //StartTimer(GPS_FENCE_CHECK_TIMER_ID, 10000, GPS_Fence_ON);

    sprintf(sms_buf, "OK");

#if defined(__GK306_GPS__)&&defined(__GK306_GPS_SETTING_UI__)
    if(mmi_frm_group_is_present(GRP_ID_GPS_REMIND_FENCE_SET))
    {
        mmi_frm_group_close(GRP_ID_GPS_REMIND_FENCE_SET);
        mmi_gps_set_fence_screen();
    }

    if(mmi_frm_group_is_present(GRP_ID_GPS_REMIND_OVER_LINE))
    {
        mmi_frm_group_close(GRP_ID_GPS_REMIND_OVER_LINE);
        mmi_gps_set_over_line_screen();
    }
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Set_Fence_Rectangle_Single
 *
 *  Purpose     -  ���β�������
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Fence_Rectangle_Single(void)
{
    S16 error;
    U8 str_len;
    BOOL rpt = TRUE;
    double  data_lon, data_lat, data_lon1, data_lat1;

    if(Get_GPS_Coordinate((char *)received_data.param2, &data_lat) == FALSE)
    {
        rpt = FALSE;
    }
    if((Get_GPS_Coordinate((char *)received_data.param3, &data_lon) == FALSE))
    {
        rpt = FALSE;
    }
    if(Get_GPS_Coordinate((char *)received_data.param4, &data_lat1) == FALSE)
    {
        rpt = FALSE;
    }
    if((Get_GPS_Coordinate((char *)received_data.param5, &data_lon1) == FALSE))
    {
        rpt = FALSE;
    }
    if((data_lat > 90) || (data_lat1 > 90))
    {
        rpt = FALSE;
    }

    if((strcmp("IN", ((char *)received_data.param6)) == 0)
            || (strcmp("OUT", ((char *)received_data.param6)) == 0)
            || (strlen(((char *)received_data.param6)) == 0))
    {
        ;
    }
    else
    {
        rpt = FALSE;
    }


    if(rpt == TRUE)
    {
        if(strcmp("ON", ((char *)received_data.param0)) == 0)
        {
            tracker_electronic_fence.state = KAL_TRUE;
        }
        else
        {
            tracker_electronic_fence.state = KAL_FALSE;
        }

        tracker_electronic_fence.FenceType = Fence_Rectangle;
        tracker_electronic_fence.lat = data_lat;
        tracker_electronic_fence.lon = data_lon;
        tracker_electronic_fence.lat1 = data_lat1;
        tracker_electronic_fence.lon1 = data_lon1;

        if(strcmp("IN", ((char *)received_data.param6)) == 0)
        {
            tracker_electronic_fence.FenceAlarmType = Fence_IN;

        }
        else   if(strcmp("OUT", ((char *)received_data.param6)) == 0)
        {
            tracker_electronic_fence.FenceAlarmType = Fence_OUT;
        }
        else
        {
            tracker_electronic_fence.FenceAlarmType = Fence_IN_OUT;
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
        return;
    }
    sprintf(sms_buf, "OK");//���ݸ�ʽ����
    WriteRecord(NVRAM_EF_TRACKER_ELECTRONIC_FENCE_LID, 1, (void*)&tracker_electronic_fence, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE, &error);

    isLastFenceIn = Fence_NO;

    //StartTimer(GPS_FENCE_CHECK_TIMER_ID, 10000, GPS_Fence_ON);
}


/******************************************************************************
 *  Function    -  Tracker_Set_Electronic_Fence_Single
 *
 *  Purpose     -  ����Χ������
 *
 *  Description -
 *
 * modification history
 * AT^GT_CM=FENCE, ON, 0, N23.10267,E114.39671,100#                received_data.part == 5
 * AT^GT_CM=FENCE, ON, 0, N23.10267,E114.39671,100,OUT#                received_data.part == 6
 * AT^GT_CM=FENCE, ON, 1, N23.10267,E114.39671,N23.10267,E114.39671#   received_data.part == 6
 * AT^GT_CM=FENCE, ON, 1, N23.10267,E114.39671,N23.10267,E114.39671,OUT#   received_data.part == 7
 * ----------------------------------------
 * v1.0  , 2012-06-01, guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Electronic_Fence_Single(void)
{
    S16 error;
    S8 temp[100];
    U8 str_len;
    BOOL rpt = TRUE;

    if(strcmp("OFF", ((char *)received_data.param0)) == 0)
    {
        tracker_electronic_fence.state = KAL_FALSE;
        WriteRecord(NVRAM_EF_TRACKER_ELECTRONIC_FENCE_LID, 1, (void*)&tracker_electronic_fence, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE, &error);

        if(IsMyTimerExist(GPS_FENCE_CHECK_TIMER_ID))
        {
            StopTimer(GPS_FENCE_CHECK_TIMER_ID);
        }
        StartTimer(GPS_FENCE_CHECK_TIMER_ID, 2000, GPS_Fence_OFF);
        sprintf(sms_buf, "OK");
        return;
    }

    if((received_data.part != 6) && (received_data.part != 7) && (received_data.part != 5))
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        if(Command_State == SMS_Command_State)
        {
            strcat(sms_buf, ";FENCE,ON,0,N23.10827,E114.41396,200, IN #");
        }
        return;
    }
    if((strcmp("ON", ((char *)received_data.param0)) == 0) || (strcmp("OFF", ((char *)received_data.param0)) == 0))
    {
        ;
    }
    else
    {
        LOGD("false rpt1");
        rpt = FALSE;
    }

    if(strlen((char *)received_data.param1) == 1 && ((received_data.param1[0] == '1') || (received_data.param1[0] == '0')))
    {
        ;
    }
    else
    {
        LOGD("false rpt2");
        rpt = FALSE;

    }

    if(rpt == TRUE)
    {
        if(received_data.param1[0] == '0')
        {
            Tracker_Set_Fence_Circle_Single();
        }
        else if(received_data.param1[0] == '1')
        {
            Tracker_Set_Fence_Rectangle_Single();
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
        if(Command_State == SMS_Command_State)
        {
            strcat(sms_buf, ";FENCE,ON,0,N23.10827,E114.41396,200, IN #");
        }
    }
}

/******************************************************************************
 *  Function    -  Tracker_See_Electronic_Fence_Set_Single
 *
 *  Purpose     -  �鿴Բ�β�������
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_See_Electronic_Fence_Set_Single(void)
{
    char tmp[200];
    char data[100];
    U16  Data;
    S16 Error;
    S32 ret = 0;
    memset(tmp, 0x00, 200);
    memset(data, 0x00, 100);

    ret = ReadRecord(NVRAM_EF_TRACKER_ELECTRONIC_FENCE_LID, 1, (void *)&tracker_electronic_fence, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE, &Error);
#ifdef __SMS_APP_DEBUG__
    LOGD("ReadRecord tracker_electronic_fence ret:%d", ret);
#endif
    if(tracker_electronic_fence.state == KAL_FALSE)
    {
        sprintf(data, "Switch:OFF;");
        strcat(sms_buf, data);
        return;
    }
    else
    {
        sprintf(data, "Switch:ON;");
    }
    strcat(tmp, data);
    if(tracker_electronic_fence.FenceAlarmType == Fence_IN)
    {
        sprintf(data, "State:IN;");
    }
    else if((tracker_electronic_fence.FenceAlarmType == Fence_OUT))
    {
        sprintf(data, "State:OUT;");
    }
    else
    {
        sprintf(data, "State:IN&OUT;");
    }
    strcat(tmp, data);

    if(tracker_electronic_fence.lat > 0)
    {
        sprintf(data, " Lat:N%f;", tracker_electronic_fence.lat);
    }
    else if(tracker_electronic_fence.lat < 0)
    {
        sprintf(data, " Lat:S%f;", -tracker_electronic_fence.lat);
    }
    strcat(tmp, data);


    if(tracker_electronic_fence.lon > 0)
    {
        sprintf(data, " Lon:E%f;", tracker_electronic_fence.lon);
    }
    else if(tracker_electronic_fence.lon < 0)
    {
        sprintf(data, " Lon:W%f;", -tracker_electronic_fence.lon);
    }
    strcat(tmp, data);


    if(tracker_electronic_fence.FenceType == Fence_Rectangle)
    {
        if(tracker_electronic_fence.lat1 > 0)
        {
            sprintf(data, " Lat:N%f;", tracker_electronic_fence.lat1);
        }
        else if(tracker_electronic_fence.lat1 < 0)
        {
            sprintf(data, " Lat:S%f;", -tracker_electronic_fence.lat1);
        }
        strcat(tmp, data);

        if(tracker_electronic_fence.lon1 > 0)
        {
            sprintf(data, "Lon:E%f;", tracker_electronic_fence.lon1);
        }
        else if(tracker_electronic_fence.lon1 < 0)
        {
            sprintf(data, "Lon:W%f;", -tracker_electronic_fence.lon1);
        }
        strcat(tmp, data);
        sprintf(data, "FenceType:Rectangle;");
        strcat(tmp, data);
    }
    else if(tracker_electronic_fence.FenceType == Fence_Circle)
    {
        sprintf(data, "Radius:%dM;", tracker_electronic_fence.dis);
        strcat(tmp, data);
        sprintf(data, "FenceType:Circle;");
        strcat(tmp, data);
    }
    //sprintf(data, "now LAT:%f;", Get_GPS_Now_Coordinat_LAT());
	//strcat(tmp, data);
	//sprintf(data, "now LON:%f;", Get_GPS_Now_Coordinat_LON());
	//strcat(tmp, data);

    sprintf(sms_buf, tmp);//���ݸ�ʽ����

}

#if defined(__MULTI_FENCE__)
/******************************************************************************
 *  Function    -  create_close_gfence_reply
 *
 *  Purpose     -  �ر�Χ��ʱ�ظ�
 *
 *  Description - �ر�Χ��ʱ�ظ�
 *				���ģ�Χ��N �ѹر�!
 *				Ӣ�ģ�Dsiable Fence N set successfully!
 * modification history
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
static void create_close_gfence_reply(U8 fence_order, U8 fence_type)
{
    char tmp[100], ucs2_tmp[200];
    //MYTIME t;
    nvram_ef_tracker_electronic_fence_struct *p;

    LOGD("entry_create_close_gfence_reply Command_State=%d order=%d, type=%d"
         , Command_State, fence_order, fence_type);

    if(Command_State != SMS_Command_State) // || Command_State == AT_Command_State)
    {
        is_unicode_replay_msg = KAL_FALSE;
        sprintf(sms_buf, "OK! Disable Fence%d Successfully,type=%d", fence_order + 1, fence_type);
    }
    else
    {
        is_unicode_replay_msg = KAL_TRUE;
        mmi_ucs2cpy(sms_buf, GetString(STR_KKSAPP_FENCE_TITLE));
        sprintf(tmp, " %d", fence_order + 1);
        asc_cat_ucs2(sms_buf, tmp);
        mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_6));//�ѹر�
        mmi_ucs2cat(sms_buf, GetString(STR_ID_EXCLAMATION));// !
        //asc_cat_ucs2(sms_buf,"!");
	#if 0  // Բ��Χ���������ѹر�!
        if(1 == fence_type)
        {
            mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_3));//Բ��Χ�� or����
        }
        else
        {
            mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_2));//Բ��Χ�� or����
        }
        asc_cat_ucs2(sms_buf, ",");

        mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_5));//�����ѹر�
        asc_cat_ucs2(sms_buf, "!");
	#endif
    }
}

/******************************************************************************
 *  Function    -  create_rect_gfence_reply
 *
 *  Purpose     -  ���þ���Χ��ʱ�ظ�
 *
 *  Description - ���þ���Χ��ʱ�ظ�:
 *					���ģ�Χ��N ���óɹ�! ����Χ���������ѿ�����γ��1��N22.577091,
 *								����1��E113.916748,γ��2��N22.577091,����2��E113.916748����Χ
 *								���������������ͣ�1
 *					Ӣ�ģ�Fence N set successfully! FenceType:Square, ON,
 *								Latitude1:N22.575069, Longitude1:E113.911140, Latitude2:N22.573568,
 *								Longitude2:E113.921463, in out:OUT, alarm type:1.
  *
 * modification history
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
static void create_rect_gfence_reply(U8 fence_order)
{
    char tmp[100], ucs2_tmp[200];
    //MYTIME t;
    nvram_ef_tracker_electronic_fence_struct *p;

    LOGD("entry_create_rect_gfence_reply Command_State=%d", Command_State);
    p = &tracker_electronic_fence;
    if(Command_State != SMS_Command_State) // || Command_State == AT_Command_State)
    {
        is_unicode_replay_msg = KAL_FALSE;
        sprintf(sms_buf, "OK! ");
        if(p->m_lat[fence_order] >= 0)
        {
            sprintf(tmp, " Lat:N%f,", p->m_lat[fence_order]);
        }
        else if(p->m_lat[fence_order] < 0)
        {
            sprintf(tmp, " Lat:S%f,", -p->m_lat[fence_order]);
        }
        strcat(sms_buf, tmp);

        if(p->m_lon[fence_order] >= 0)
        {
            sprintf(tmp, " Lon:E%f,", p->m_lon[fence_order]);
        }
        else if(p->m_lon[fence_order] < 0)
        {
            sprintf(tmp, " Lon:W%f,", -p->m_lon[fence_order]);
        }
        strcat(sms_buf, tmp);

        if(p->m_lat1[fence_order] >= 0)
        {
            sprintf(tmp, " Lat:N%f,", p->m_lat1[fence_order]);
        }
        else if(p->m_lat1[fence_order] < 0)
        {
            sprintf(tmp, " Lat:S%f,", -p->m_lat1[fence_order]);
        }
        strcat(sms_buf, tmp);

        if(p->m_lon1[fence_order] >= 0)
        {
            sprintf(tmp, " Lon:E%f,", p->m_lon1[fence_order]);
        }
        else if(p->m_lon1[fence_order] < 0)
        {
            sprintf(tmp, " Lon:W%f,", -p->m_lon1[fence_order]);
        }
        strcat(sms_buf, tmp);
    }
    else //���Żظ�
    {
        is_unicode_replay_msg = KAL_TRUE;
        mmi_ucs2cpy(sms_buf, GetString(STR_KKSAPP_FENCE_TITLE));
        sprintf(tmp, " %d ", fence_order + 1);
        asc_cat_ucs2(sms_buf, tmp);
        mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_1));//���óɹ�
        mmi_ucs2cat(sms_buf, GetString(STR_ID_EXCLAMATION));// !
        //asc_cat_ucs2(sms_buf,"!");
        mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_3));//����Χ��
        asc_cat_ucs2(sms_buf, ",");
        mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_4));//�����ѿ���
        asc_cat_ucs2(sms_buf, ";");

        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_14));//ά��1

        if(p->m_lat[fence_order] >= 0)
        {
            sprintf(tmp, ":N%f,", p->m_lat[fence_order]);
        }
        else
        {
            sprintf(tmp, ":S%f,", -p->m_lat[fence_order]);
        }
        asc_cat_ucs2(sms_buf, tmp);

        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_15));//����1

        if(p->m_lon[fence_order] >= 0)
        {
            sprintf(tmp, ":E%f,", p->m_lon[fence_order]);
        }
        else if(p->m_lon[fence_order] < 0)
        {
            sprintf(tmp, ":W%f,", -p->m_lon[fence_order]);
        }
        asc_cat_ucs2(sms_buf, tmp);
        //asc_cat_ucs2(sms_buf,",");

        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_16));//ά��2

        if(p->m_lat1[fence_order] >= 0)
        {
            sprintf(tmp, ":N%f,", p->m_lat1[fence_order]);
        }
        else
        {
            sprintf(tmp, ":S%f,", -p->m_lat1[fence_order]);
        }
        asc_cat_ucs2(sms_buf, tmp);

        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_17));//����2

        if(p->m_lon1[fence_order] >= 0)
        {
            sprintf(tmp, ":E%f", p->m_lon1[fence_order]);
        }
        else if(p->m_lon1[fence_order] < 0)
        {
            sprintf(tmp, ":W%f", -p->m_lon1[fence_order]);
        }
        asc_cat_ucs2(sms_buf, tmp);
        asc_cat_ucs2(sms_buf, ";");

        switch(p->m_FenceAlarmType[fence_order])  //���뱨������
        {
            case 1:
                mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_12));//��澯
                break;
            case 2:
                mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_11));//���澯
                break;
            case 3:
                mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_13));//����澯
                break;
        }
        asc_cat_ucs2(sms_buf, ",");
        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_10));//�ϱ�����
        sprintf(tmp, ":%d", p->m_commit_type[fence_order]);
        asc_cat_ucs2(sms_buf, tmp);
    }
}

/******************************************************************************
 *  Function    -  create_cirle_gfence_reply
 *
 *  Purpose     -  ����Բ��Χ��ʱ�ظ�
 *
 *  Description - ����Բ��Χ��ʱ�ظ�:
 *						���ģ�Χ��N ���óɹ�! Բ��Χ���������ѿ�����Բ�ģ�N22.577091,
 *									E113.916748���뾶��600 �ף�����Χ���������������ͣ�1
 *						Ӣ�ģ�Fence N set successfully! FenceType:Circle, ON,
 *									Latitude:N22.577091, Longitude:E113.916748, radius:600m, in
 *						out:IN or OUT, alarm type:1.
 *
 * modification history
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
static void create_cirle_gfence_reply(U8 fence_order)
{
    char tmp[100], ucs2_tmp[200];
    //MYTIME t;
    nvram_ef_tracker_electronic_fence_struct *p;

    LOGD("entry_create_cirle_gfence_reply Command_State=%d", Command_State);
    p = &tracker_electronic_fence;
    if(Command_State != SMS_Command_State) // || Command_State == AT_Command_State)
    {
        is_unicode_replay_msg = KAL_FALSE;
        sprintf(sms_buf, "OK! ");
        if(p->m_lat[fence_order] >= 0)
        {
            sprintf(tmp, " Lat:N%f,", p->m_lat[fence_order]);
        }
        else if(p->m_lat[fence_order] < 0)
        {
            sprintf(tmp, " Lat:S%f,", -p->m_lat[fence_order]);
        }
        strcat(sms_buf, tmp);

        if(p->m_lon[fence_order] >= 0)
        {
            sprintf(tmp, " Lon:E%f,", p->m_lon[fence_order]);
        }
        else if(p->m_lon[fence_order] < 0)
        {
            sprintf(tmp, " Lon:W%f,", -p->m_lon[fence_order]);
        }
        strcat(sms_buf, tmp);

        sprintf(tmp, " Radius:%dm", p->m_dis[fence_order]);
        strcat(sms_buf, tmp);
    }
    else //���Żظ�
    {
        is_unicode_replay_msg = KAL_TRUE;
        mmi_ucs2cpy(sms_buf, GetString(STR_KKSAPP_FENCE_TITLE));
        sprintf(tmp, " %d ", fence_order + 1);
        asc_cat_ucs2(sms_buf, tmp);
        mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_1));//���óɹ�
        mmi_ucs2cat(sms_buf, GetString(STR_ID_EXCLAMATION));// !
        //asc_cat_ucs2(sms_buf,"!");
        mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_2));//Բ��Χ��
        asc_cat_ucs2(sms_buf, ",");
        mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_4));//�����ѿ���
        asc_cat_ucs2(sms_buf, ";");
        mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_7));//Բ��
        //asc_cat_ucs2(sms_buf,":");
        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_LATITUDE));//ά��

        if(p->m_lat[fence_order] >= 0)
        {
            sprintf(tmp, ":N%f,", p->m_lat[fence_order]);
        }
        else
        {
            sprintf(tmp, ":S%f,", -p->m_lat[fence_order]);
        }
        asc_cat_ucs2(sms_buf, tmp);

        mmi_ucs2cat(sms_buf, GetString(STR_KKSAPP_GFENCE_7));//Բ��
        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_LONGITUDE));//����

        if(p->m_lon[fence_order] >= 0)
        {
            sprintf(tmp, ":E%f,", p->m_lon[fence_order]);
        }
        else if(p->m_lon[fence_order] < 0)
        {
            sprintf(tmp, ":W%f,", -p->m_lon[fence_order]);
        }
        asc_cat_ucs2(sms_buf, tmp);
        //asc_cat_ucs2(sms_buf,",");

        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_8));//�뾶
        sprintf(tmp, ":%d", p->m_dis[fence_order]);
        asc_cat_ucs2(sms_buf, tmp);
        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_9));//��
        asc_cat_ucs2(sms_buf, ",");
        switch(p->m_FenceAlarmType[fence_order])  //���뱨������
        {
            case 1:
                mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_12));//��澯
                break;
            case 2:
                mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_11));//���澯
                break;
            case 3:
                mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_13));//����澯
                break;
        }
        asc_cat_ucs2(sms_buf, ",");
        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_GFENCE_10));//�ϱ�����
        sprintf(tmp, ":%d", p->m_commit_type[fence_order]);
        asc_cat_ucs2(sms_buf, tmp);
    }
}

/******************************************************************************
 *  Function    -  create_cirle_auto_get_sms
 *
 *  Purpose     -  �Զ���ȡԲ��ʱ�ظ�
 *
 *  Description - �Զ���ȡ�ɹ���ظ���
 * 					���ģ�OK��Χ��N ���Զ���ȡԲ��λ�ã�N22.577091,E113.916748��
 *					ʱ�䣺2013-01-08 19:14:57
 *					Ӣ�ģ�OK! The Fence N Automatically obtain latitude��N22.577091
 *					Longitude��E113.916748, in the time 2013-01-08 19:14:57
 *
 * modification history
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
static void create_cirle_auto_get_sms(U8 fence_order)
{
    char tmp[100], ucs2_tmp[200];
    MYTIME t;

    if(Command_State == SMS_Command_State) // || Command_State == AT_Command_State)
    {
        is_unicode_replay_msg = KAL_TRUE;
        mmi_ucs2cpy(sms_buf, (char *)GetString(STR_KKSAPP_FENCE_OK)); //OK!Χ��

        sprintf(tmp, " %d", fence_order + 1); //N
        mmi_asc_to_ucs2(ucs2_tmp, tmp);
        mmi_ucs2cat(sms_buf, ucs2_tmp);

        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_AUTO_GET_OK));//���Զ���ȡԲ��λ��:
        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_LATITUDE));//ά��

        if(tracker_electronic_fence.m_lat[fence_order] >= 0)
        {
            sprintf(tmp, " :N%f,", tracker_electronic_fence.m_lat[fence_order]);
        }
        else if(tracker_electronic_fence.m_lat[fence_order] < 0)
        {
            sprintf(tmp, " :S%f,", -tracker_electronic_fence.m_lat[fence_order]);
        }
        mmi_asc_to_ucs2(ucs2_tmp, tmp);
        mmi_ucs2cat(sms_buf, ucs2_tmp);

        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_LONGITUDE));//����

        if(tracker_electronic_fence.m_lon[fence_order] >= 0)
        {
            sprintf(tmp, " :E%f,", tracker_electronic_fence.m_lon[fence_order]);
        }
        else if(tracker_electronic_fence.m_lon[fence_order] < 0)
        {
            sprintf(tmp, " :W%f,", -tracker_electronic_fence.m_lon[fence_order]);
        }
        mmi_asc_to_ucs2(ucs2_tmp, tmp);
        mmi_ucs2cat(sms_buf, ucs2_tmp);

        mmi_ucs2cat(sms_buf, (char *)GetString(STR_KKSAPP_TIME_STR));//ʱ��
        GetDateTime(&t);
        sprintf(tmp, ":%d-%02d-%02d %02d:%02d:%02d", t.nYear, t.nMonth, t.nDay, t.nHour, t.nMin, t.nSec);
        mmi_asc_to_ucs2(ucs2_tmp, tmp);
        mmi_ucs2cat(sms_buf, ucs2_tmp);
    }
    else
    {
        is_unicode_replay_msg = KAL_FALSE;
        sprintf(sms_buf, "OK! ");
        if(tracker_electronic_fence.m_lat[fence_order] >= 0)
        {
            sprintf(tmp, " Lat:N%f,", tracker_electronic_fence.m_lat[fence_order]);
        }
        else if(tracker_electronic_fence.m_lat[fence_order] < 0)
        {
            sprintf(tmp, " Lat:S%f,", -tracker_electronic_fence.m_lat[fence_order]);
        }
        strcat(sms_buf, tmp);

        if(tracker_electronic_fence.m_lon[fence_order] >= 0)
        {
            sprintf(tmp, " Lon:E%f,", tracker_electronic_fence.m_lon[fence_order]);
        }
        else if(tracker_electronic_fence.m_lon[fence_order] < 0)
        {
            sprintf(tmp, " Lon:W%f,", -tracker_electronic_fence.m_lon[fence_order]);
        }
        strcat(sms_buf, tmp);
    }
}

/******************************************************************************
 *  Function    -  is_any_fence_open_flag
 *
 *  Purpose     -  �Ƿ���Χ�����ÿ����� ������Χ����Χ����
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
kal_bool is_any_fence_open_flag(void)
{
    int i;
    kal_bool ret = KAL_FALSE;

    if(tracker_electronic_fence.state)
    {
        return KAL_TRUE;
    }
    for(i = 0; i < MAX_FENCE_NUM; i++)
    {
        if(tracker_electronic_fence.m_state[i])
        {
            ret = KAL_TRUE;
            break;
        }
    }
    return ret;
}


/******************************************************************************
 *  Function    -  Tracker_Electronic_Fence_Multi_Test
 *
 *  Purpose     -  GFENCE ����ָ��
 *
 *  Description -	AT^GT_CM=GFENCETEST,DIS,100# // ǿ�����о���Ϊ100��
 * 				AT^GT_CM=GFENCETEST,GPS,N23.10827,E114.41396# // ǿ�����е�ָ������
 *
 * modification history
 *
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
extern S32 g_test_distance;
extern double g_test_lat;
extern double g_test_lon;

void Tracker_Electronic_Fence_Multi_Test(void)
{
    kal_bool ret = KAL_TRUE;
    char ss[500];

    LOGD("part =%d, param0 = %s,param1 = %s,param2 = %s",
         received_data.part, received_data.param0, received_data.param1, received_data.param2);
    if(received_data.part == 0)
    {
        sprintf(sms_buf, "testdata dis=%d lat=%f lon=%f", g_test_distance, g_test_lat, g_test_lon);
        return;
    }
    if(0 == strcmp("DIS", received_data.param0))
    {
        g_test_distance = atoi(received_data.param1);
    }
    else if(0 == strcmp("GPS", received_data.param0))
    {
        if(Get_GPS_Coordinate((char *)received_data.param1, &g_test_lat) == FALSE)
        {
            ret = KAL_FALSE;
        }
        if(Get_GPS_Coordinate((char *)received_data.param2, &g_test_lon) == FALSE)
        {
            ret = KAL_FALSE;
        }
        if(!ret)
        {
            g_test_lat = 0;
            g_test_lon = 0;
        }
    }
    else
    {
        g_test_distance = 0;
        g_test_lat = 0;
        g_test_lon = 0;
    }
    sprintf(ss, "g_test_distance=%d g_test_lat=%f g_test_lon=%f", g_test_distance, g_test_lat, g_test_lon);
    LOGD("%s", ss);
    if(ret)
    {
        sprintf(sms_buf, "OK");
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
    }
}


/******************************************************************************
 *  Function    -  Tracker_Set_Fence_Circle_Multi
 *
 *  Purpose     -  Բ�β�������
 *
 *  Description -
 *
 * modification history
 *
 * Բ��
 * AT^GT_CM=GFENCE,1,ON,0,N23.10123,E113.12323,100#   received_data.part == 6
 * AT^GT_CM=GFENCE,1,ON,0,N23.10123,E113.12323,100,OUT#   received_data.part == 7
 * AT^GT_CM=GFENCE,1,ON,0,N23.10123,E113.12323,100,OUT,1#   received_data.part == 8
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Fence_Circle_Multi(void)
{
    double data_lon, data_lat;
    char temp[50];
    S16 error;
    U8 str_len;
    BOOL rpt = TRUE;
    double data;
    U16 order; //Χ�����
    BOOL auto_get = FALSE; //�Զ�Բ��

    is_unicode_replay_msg = KAL_FALSE;
    order = received_data.param0[0] - 0x31; // ���- ��1��

    LOGD("order:%d", order);

    if(order < 0 || order > MAX_FENCE_NUM - 1)
    {
        sprintf(sms_buf, "ERROR:101");//����������Χ
        return ;
    }
    if((Get_GPS_Coordinate((char *)(received_data.param3), &data_lat) != FALSE)
            || ((*received_data.param3 == '0') && (*received_data.param4 == '0')))
    {
        ;
    }
    else
    {
        LOGD("false rpt3");
        rpt = FALSE;
    }
    if(((Get_GPS_Coordinate((char *)(received_data.param4), &data_lon) != FALSE))
            || ((*received_data.param3 == '0') && (*received_data.param4 == '0')))
    {
        ;
    }
    else
    {
        LOGD("false rpt4");
        rpt = FALSE;
    }
    if(data_lat > 90)
    {
        rpt = FALSE;
    }
    if(interval_Time_Manage((received_data.param5), 1, 9999) == 0XFFFF) //cjt ��λ����
    {
        sprintf(sms_buf, "ERROR:101");//����������Χ
        return ;
    }
    if((strcmp("IN", ((char *)received_data.param6)) == 0)
            || (strcmp("OUT", ((char *)received_data.param6)) == 0)
            || (strlen(((char *)received_data.param6)) == 0))
    {
        ;
    }
    else
    {
        rpt = FALSE;
    }

    if(rpt == TRUE)
    {
        U32 rad_m = 0;
        tracker_electronic_fence.m_FenceType[order] = Fence_Circle;
        //tracker_electronic_fence.m_dis[order] = interval_Time_Manage((received_data.param5), 100, 9999); //����Ϊ��λ cjt
        tracker_electronic_fence.m_dis[order] = interval_Time_Manage((received_data.param5), 1, 9999) * 100; //��100��Ϊ��λ cjt

        rad_m = atoi(received_data.param5) * 100;
        if(rad_m < 100 || rad_m > 999900)
        {
            // �뾶��Χ����
            if(Command_State == SMS_Command_State)
            {
                memset(sms_buf, 0, sizeof(sms_buf));
                mmi_ucs2cpy(sms_buf, GetString(STR_SMS_SET_ERROR1));
                is_unicode_replay_msg = KAL_TRUE;
            }
            else
            {
                sprintf(sms_buf, "Error!R=1--9999");
            }
            return;
        }
        else
        {
            tracker_electronic_fence.m_dis[order] = rad_m;
        }

        LOGD("�뾶=%d", tracker_electronic_fence.m_dis[order]);
        if((data_lat == 0) && (data_lon == 0))
        {
            auto_get = KAL_TRUE;
            if(FALSE == GPSOnFlag)   //gps δ����
            {
                LOGD("---gpsδ����-----");
                if(Command_State == SMS_Command_State)
                {
                    memset(sms_buf, 0, sizeof(sms_buf));
                    mmi_ucs2cpy(sms_buf, GetString(STR_KKSAPP_AUTO_GET_NO_OPEN));
                    is_unicode_replay_msg = KAL_TRUE;
                }
                else
                {
                    sprintf(sms_buf, "FAIL!GPS is not working, Please open the GPS first!");
                }
                return;
            }
            else if((sys_gps_state == GPS_LOCATION_STATE))
            {
                LOGD("---gpsԲ�ĳɹ�-----");
                Get_GPS_Signed_Doble_LatLon();
                tracker_electronic_fence.m_lat[order] = latlon_info.lat;
                tracker_electronic_fence.m_lon[order] = latlon_info.lon;

                if(latlon_info.lat < 0)
                {
                    tracker_electronic_fence.m_latzone[order] = 1;
                }
                else
                {
                    tracker_electronic_fence.m_latzone[order] = 0;
                }

                if(latlon_info.lon < 0)
                {
                    tracker_electronic_fence.m_lonzone[order] = 1;
                }
                else
                {
                    tracker_electronic_fence.m_lonzone[order] = 0;
                }

                create_cirle_auto_get_sms(order);
            }
            else
            {
                LOGD("---gpsδ��λ-----");
                if(Command_State == SMS_Command_State) // || Command_State == AT_Command_State)
                {
                    memset(sms_buf, 0, sizeof(sms_buf));
                    mmi_ucs2cpy(sms_buf, GetString(STR_KKSAPP_AUTO_GET_NO_LOCA));
                    is_unicode_replay_msg = KAL_TRUE;
                }
                else
                {
                    sprintf(sms_buf, "FAIL! GPS Fix Invaid");
                    return;
                }
            }
        }
        else
        {
            tracker_electronic_fence.m_lat[order] = data_lat;
            tracker_electronic_fence.m_lon[order] = data_lon;

            if(data_lat < 0)
            {
                tracker_electronic_fence.m_latzone[order] = 1;
            }
            else
            {
                tracker_electronic_fence.m_latzone[order] = 0;
            }

            if(data_lon < 0)
            {
                tracker_electronic_fence.m_lonzone[order] = 1;
            }
            else
            {
                tracker_electronic_fence.m_lonzone[order] = 0;
            }
        }

        if(strcmp("ON", ((char *)received_data.param1)) == 0)
        {
            tracker_electronic_fence.m_state[order] = KAL_TRUE;
        }
        else
        {
            tracker_electronic_fence.m_state[order] = KAL_FALSE;
        }

        if(strcmp("IN", ((char *)received_data.param6)) == 0)
        {
            tracker_electronic_fence.m_FenceAlarmType[order] = Fence_IN;
        }
        else if(strcmp("OUT", ((char *)received_data.param6)) == 0)
        {
            tracker_electronic_fence.m_FenceAlarmType[order] = Fence_OUT;
        }
        else if((strcmp("INOUT", ((char *)received_data.param6)) == 0)
                || (strlen((char*)received_data.param6) == 0))
        {
            tracker_electronic_fence.m_FenceAlarmType[order] = Fence_IN_OUT;
        }

        //LOGD("tracker_electronic_fence.FenceAlarmType %d", tracker_electronic_fence.m_FenceAlarmType[order]);

        if(received_data.param7[0] == '0')
        {
            //LOGD("Բ��Χ���ϴ�����GPRS param7=%s", received_data.param7);
            tracker_electronic_fence.m_commit_type[order] = COMMIT_ONLY_GPRS;
        }
        else
        {
            //LOGD("Բ��Χ���ϴ�����GPRS+SMS param7=%s", received_data.param7);
            tracker_electronic_fence.m_commit_type[order] = COMMIT_GPRS_AND_SMS;
        }

    }
    else
    {
        sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
        return;
    }

    tracker_electronic_fence.m_lon1[order] = 0;
    tracker_electronic_fence.m_lat1[order] = 0;
    WriteRecord(NVRAM_EF_TRACKER_ELECTRONIC_FENCE_LID, 1, (void *)&tracker_electronic_fence, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE, &error);

    m_isLastFenceIn[order] = Fence_NO;
    /*��GPS����ʱ��ο�������Χ��*/
    //StartTimer(GPS_FENCE_CHECK_TIMER_ID, 10000, GPS_Fence_ON);

    if(!auto_get)
    {
        //sprintf(sms_buf, "OK");//
        if(tracker_electronic_fence.m_state[order])
        {
            create_cirle_gfence_reply(order); //�ظ��ɹ�
        }
        else
        {
            create_close_gfence_reply(order, 0); //�ظ��ر�
        }
    }
    else
    {
        //debug_print_ucs2str(sms_buf,"sms_buf");
    }

    //-----�����SMS ATָ���������ϴ�ͬ��������---------------
    // OK#GFENCE# ���,����,��״0,�ϱ�ά,������,Բ�ľ�γ��,�뾶(����),�澯ģʽ,�ϴ�ģʽ
    if(Command_State != ONLine_Command_State)
    {
	#if 1
        LOGD("Բ��Χ��ͬ��");
        Commit_All_Gfences();
	#else
        nvram_ef_tracker_electronic_fence_struct *p;
        p = &tracker_electronic_fence;
        memset(sms_buf_ex, 0, sizeof(sms_buf_ex));
        sprintf(sms_buf_ex, "OK#GFENCE# %d,%d,%d,%d,%d,%f,%f,%d,%d,%d",
                order + 1, p->m_state[order], p->m_FenceType[order],
                p->m_latzone[order], p->m_lonzone[order],
                p->m_lat[order], p->m_lon[order],
                p->m_dis[order] / 100,
                p->m_FenceAlarmType[order],
                p->m_commit_type[order]);
        LOGD("Բ��Χ��ͬ��");
        LOGD("Բ��-%s", sms_buf_ex);
        gprs_send_type = GPRS_ONLINE_ASCII_DATA_REPLY_EX;
        Tracker_Socket_Send_Current_Data();
	#endif
    }

	//-----------ͬ������-------------------------------------
#if defined(__GK306_GPS__)&&defined(__GK306_GPS_SETTING_UI__)  //cjt
    if(mmi_frm_group_is_present(GRP_ID_GPS_REMIND_FENCE_SET))
    {
        mmi_frm_group_close(GRP_ID_GPS_REMIND_FENCE_SET);
        mmi_gps_set_fence_screen();
    }

    if(mmi_frm_group_is_present(GRP_ID_GPS_REMIND_OVER_LINE))
    {
        mmi_frm_group_close(GRP_ID_GPS_REMIND_OVER_LINE);
        mmi_gps_set_over_line_screen();
    }
#endif
}


/******************************************************************************
 *  Function    -  Tracker_Set_Fence_Rectangle_Multi
 *
 *  Purpose     -  ���β�������
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * ����
 * AT^GT_CM=FENCE, 1,ON, 1, N23.10267,E114.39671,N23.10267,E114.39671#   received_data.part == 7
 * AT^GT_CM=FENCE, 1,ON, 1, N23.10267,E114.39671,N23.10267,E114.39671,OUT#   received_data.part == 8
 * AT^GT_CM=FENCE, 1,ON, 1, N23.10267,E114.39671,N23.10267,E114.39671,OUT,1#   received_data.part == 9
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Set_Fence_Rectangle_Multi(void)
{
    S16 error;
    U8 str_len;
    BOOL rpt = TRUE;
    double  data_lon, data_lat, data_lon1, data_lat1;
    U16 order; //Χ�����

    order = received_data.param0[0] - 0x31; // ���- ��1��
    if(order < 0 || order > MAX_FENCE_NUM - 1)
    {
        sprintf(sms_buf, "ERROR:101");//����������Χ
        return ;
    }

    LOGD("Entry Tracker_Set_Fence_Rectangle_Multi order=%d", order);

    if(Get_GPS_Coordinate((char *)received_data.param3, &data_lat) == FALSE)
    {
        rpt = FALSE;
    }
    if((Get_GPS_Coordinate((char *)received_data.param4, &data_lon) == FALSE))
    {
        rpt = FALSE;
    }
    if(Get_GPS_Coordinate((char *)received_data.param5, &data_lat1) == FALSE)
    {
        rpt = FALSE;
    }
    if((Get_GPS_Coordinate((char *)received_data.param6, &data_lon1) == FALSE))
    {
        rpt = FALSE;
    }
    if((data_lat > 90) || (data_lat1 > 90))
    {
        rpt = FALSE;
    }

    if((strcmp("IN", ((char *)received_data.param7)) == 0)
            || (strcmp("OUT", ((char *)received_data.param7)) == 0)
            || (strlen(((char *)received_data.param7)) == 0))
    {
        ;
    }
    else
    {
        rpt = FALSE;
    }

    if(rpt == TRUE)
    {
        if(strcmp("ON", ((char *)received_data.param1)) == 0)
        {
            tracker_electronic_fence.m_state[order] = KAL_TRUE;
        }
        else
        {
            tracker_electronic_fence.m_state[order] = KAL_FALSE;
        }

        tracker_electronic_fence.m_FenceType[order] = Fence_Rectangle;
        tracker_electronic_fence.m_lat[order] = data_lat;
        tracker_electronic_fence.m_lon[order] = data_lon;
        tracker_electronic_fence.m_lat1[order] = data_lat1;
        tracker_electronic_fence.m_lon1[order] = data_lon1;

        if(data_lat < 0)
        {
            tracker_electronic_fence.m_latzone[order] = 1;
        }
        else
        {
            tracker_electronic_fence.m_latzone[order] = 0;
        }

        if(data_lon < 0)
        {
            tracker_electronic_fence.m_lonzone[order] = 1;
        }
        else
        {
            tracker_electronic_fence.m_lonzone[order] = 0;
        }

	#ifdef __FENCE_CROSS_LATLON__
        if(data_lat1 < 0)
        {
            tracker_electronic_fence.m_latzone1[order] = 1;
        }
        else
        {
            tracker_electronic_fence.m_latzone1[order] = 0;
        }

        if(data_lon1 < 0)
        {
            tracker_electronic_fence.m_lonzone1[order] = 1;
        }
        else
        {
            tracker_electronic_fence.m_lonzone1[order] = 0;
        }
	#endif

        if(strcmp("IN", ((char *)received_data.param7)) == 0)
        {
            //LOGD("����Χ���澯����in param7=%s", received_data.param7);
            tracker_electronic_fence.m_FenceAlarmType[order] = Fence_IN;
        }
        else   if(strcmp("OUT", ((char *)received_data.param7)) == 0)
        {
            //LOGD("����Χ���澯����out param7=%s", received_data.param7);
            tracker_electronic_fence.m_FenceAlarmType[order] = Fence_OUT;
        }
        else
        {
            //LOGD("����Χ���澯����default param7=%s", received_data.param7);
            tracker_electronic_fence.m_FenceAlarmType[order] = Fence_IN_OUT;
        }

        if(received_data.param8[0] == '0')
        {
            //LOGD("����Χ���ϴ�����GPRS param7=%s", received_data.param8);
            tracker_electronic_fence.m_commit_type[order] = COMMIT_ONLY_GPRS;
        }
        else
        {
            //LOGD("����Χ���ϴ�����GPRS+SMS param7=%s", received_data.param8);
            tracker_electronic_fence.m_commit_type[order] = COMMIT_GPRS_AND_SMS;
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
        return;
    }
    //sprintf(sms_buf, "OK");//���ݸ�ʽ����

    if(tracker_electronic_fence.m_state[order])
    {
        create_rect_gfence_reply(order); //�ظ��ɹ�
    }
    else
    {
        create_close_gfence_reply(order, 1); //�ظ��ر�
    }

    WriteRecord(NVRAM_EF_TRACKER_ELECTRONIC_FENCE_LID, 1, (void*)&tracker_electronic_fence, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE, &error);

    m_isLastFenceIn[order] = Fence_NO;

    //-----�����SMS ATָ���������ϴ�ͬ��������---------------
    // OK#GFENCE# ���,����,��״1,�ϱ�ά,������,���Ͼ�γ��,���¾�γ��,�澯ģʽ,�ϴ�ģʽ
    if(Command_State != ONLine_Command_State)
    {
	#if 1
        LOGD("����Χ��ͬ��");
        Commit_All_Gfences();
	#else
        nvram_ef_tracker_electronic_fence_struct *p;
        p = &tracker_electronic_fence;
        memset(sms_buf_ex, 0, sizeof(sms_buf_ex));
        sprintf(sms_buf_ex, "OK#GFENCE# %d,%d,%d,%d,%d,%f,%f,%f,%f,%d,%d",
                order + 1, p->m_state[order], p->m_FenceType[order],
                p->m_latzone[order], p->m_lonzone[order],
                p->m_lat[order], p->m_lon[order],
                p->m_lat1[order], p->m_lon1[order],
                p->m_FenceAlarmType[order],
                p->m_commit_type[order]);
        LOGD("����Χ��ͬ��");
        LOGD("����%s", sms_buf_ex);
        gprs_send_type = GPRS_ONLINE_ASCII_DATA_REPLY_EX;
        Tracker_Socket_Send_Current_Data();
	#endif
    }
    //-----------ͬ������-------------------------------------

    //StartTimer(GPS_FENCE_CHECK_TIMER_ID, 10000, GPS_Fence_ON);
}


/******************************************************************************
 *  Function    -  Tracker_See_Electronic_Fence_Set_Multi
 *
 *  Purpose     -  �鿴ȫ������Χ����������
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_See_Electronic_Fence_Set_Multi(void)
{
    char tmp[1024];
    char data[100];
    U16  Data;
    S16 Error;
    S32 ret = 0;
    int fence_order;

    memset(tmp, 0x00, 512);
    memset(data, 0x00, 100);

    ret = ReadRecord(NVRAM_EF_TRACKER_ELECTRONIC_FENCE_LID, 1, (void *)&tracker_electronic_fence, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE, &Error);

#ifdef __SMS_APP_DEBUG__
    LOGD("ReadRecord tracker_electronic_fence ret:%d", ret);
#endif

    for(fence_order = 0; fence_order < MAX_FENCE_NUM; fence_order++)
    {
        if(KAL_FALSE == tracker_electronic_fence.m_state[fence_order])
        {
            sprintf(data, " {%d:OFF;}", fence_order + 1);
            //strcat(sms_buf, data);
            strcat(tmp, data);
            continue;
        }
        else
        {
            sprintf(data, " {%d:ON;", fence_order + 1);
        }
        strcat(tmp, data);
        if(tracker_electronic_fence.m_FenceAlarmType[fence_order] == Fence_IN)
        {
            sprintf(data, "IN;");
        }
        else if((tracker_electronic_fence.m_FenceAlarmType[fence_order] == Fence_OUT))
        {
            sprintf(data, "OUT;");
        }
        else
        {
            sprintf(data, "IN&OUT;");
        }
        strcat(tmp, data);

        if(tracker_electronic_fence.m_lat[fence_order] >= 0)
        {
            sprintf(data, "N%f;", tracker_electronic_fence.m_lat[fence_order]);
        }
        else if(tracker_electronic_fence.m_lat[fence_order] < 0)
        {
            sprintf(data, "S%f;", -tracker_electronic_fence.m_lat[fence_order]);
        }
        strcat(tmp, data);


        if(tracker_electronic_fence.m_lon[fence_order] >= 0)
        {
            sprintf(data, "E%f;", tracker_electronic_fence.m_lon[fence_order]);
        }
        else if(tracker_electronic_fence.m_lon[fence_order] < 0)
        {
            sprintf(data, "W%f;", -tracker_electronic_fence.m_lon[fence_order]);
        }
        strcat(tmp, data);


        if(tracker_electronic_fence.m_FenceType[fence_order] == Fence_Rectangle)
        {
            if(tracker_electronic_fence.m_lat1[fence_order] >= 0)
            {
                sprintf(data, "N%f;", tracker_electronic_fence.m_lat1[fence_order]);
            }
            else if(tracker_electronic_fence.m_lat1[fence_order] < 0)
            {
                sprintf(data, "S%f;", -tracker_electronic_fence.m_lat1[fence_order]);
            }
            strcat(tmp, data);

            if(tracker_electronic_fence.m_lon1[fence_order] >= 0)
            {
                sprintf(data, "E%f;", tracker_electronic_fence.m_lon1[fence_order]);
            }
            else if(tracker_electronic_fence.m_lon1[fence_order] < 0)
            {
                sprintf(data, "W%f;", -tracker_electronic_fence.m_lon1[fence_order]);
            }
            strcat(tmp, data);
            sprintf(data, "Rect;");
            strcat(tmp, data);
        }
        else if(tracker_electronic_fence.m_FenceType[fence_order] == Fence_Circle)
        {
            //sprintf(data, "R:%dM;", tracker_electronic_fence.m_dis[fence_order]);    //��λ100�� cjt
            sprintf(data, "R:%dM;", tracker_electronic_fence.m_dis[fence_order]);  //��λ100�� cjt
            strcat(tmp, data);
            sprintf(data, "Circle;");
            strcat(tmp, data);
        }

        if(tracker_electronic_fence.m_commit_type[fence_order] == COMMIT_ONLY_GPRS)
        {
            sprintf(data, "GPRS;");
            strcat(tmp, data);
        }
        else
        {
            sprintf(data, "GPRS+SMS;");
            strcat(tmp, data);
        }
		//sprintf(data, "now LAT:%f;", Get_GPS_Now_Coordinat_LAT());
		//strcat(tmp, data);
		//sprintf(data, "now LON:%f;", Get_GPS_Now_Coordinat_LON());
		//strcat(tmp, data);*/
		//strcat(tmp, "}");
        //strcat(tmp,"}\r\n");
    }
	
    tmp[1023] = 0x00;
    LOGD("###Χ�������ܳ���=%d", strlen(tmp));
    sprintf(sms_buf, tmp);//���ݸ�ʽ����
    debug_print_str(sms_buf, "sms_buf", strlen(sms_buf));
}


/******************************************************************************
 *  Function    -  Tracker_See_Electronic_Fence_Set_Multi_1
 *
 *  Purpose     -  �鿴��������Χ����������
 *
 *  Description -
 *
 * modification history
 * ----------------------------------------
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_See_Electronic_Fence_Set_Multi_1(int fence_order)
{
    char tmp[1024];
    char data[100];
    U16  Data;
    S16 Error;
    S32 ret = 0;
    int i;

    memset(tmp, 0x00, 512);
    memset(data, 0x00, 100);

    ret = ReadRecord(NVRAM_EF_TRACKER_ELECTRONIC_FENCE_LID, 1, (void *)&tracker_electronic_fence, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE, &Error);

    if(fence_order < 0 || fence_order > MAX_FENCE_NUM - 1)
    {
        fence_order = 0;
    }
#ifdef __SMS_APP_DEBUG__
    LOGD("Tracker_See_Electronic_Fence_Set_Multi_1:%d", fence_order);
#endif

    {
        LOGD("---tracker_electronic_fence.m_state[%d]=%d", fence_order, tracker_electronic_fence.m_state[fence_order]);
        if(KAL_FALSE == tracker_electronic_fence.m_state[fence_order])
        {
            sprintf(data, "{Fence_%d Switch:OFF;}", fence_order + 1);
            strcat(sms_buf, data);
            return;
        }
        else
        {
            sprintf(data, " {Fence_%d Switch:ON;", fence_order + 1);
        }
        strcat(tmp, data);
        if(tracker_electronic_fence.m_FenceAlarmType[fence_order] == Fence_IN)
        {
            sprintf(data, "State:IN;");
        }
        else if((tracker_electronic_fence.m_FenceAlarmType[fence_order] == Fence_OUT))
        {
            sprintf(data, "State:OUT;");
        }
        else
        {
            sprintf(data, "State:IN&OUT;");
        }
        strcat(tmp, data);

        if(tracker_electronic_fence.m_lat[fence_order] >= 0)
        {
            sprintf(data, " Lat:N%f;", tracker_electronic_fence.m_lat[fence_order]);
        }
        else if(tracker_electronic_fence.m_lat[fence_order] < 0)
        {
            sprintf(data, " Lat:S%f;", -tracker_electronic_fence.m_lat[fence_order]);
        }
        strcat(tmp, data);


        if(tracker_electronic_fence.m_lon[fence_order] >= 0)
        {
            sprintf(data, " Lon:E%f;", tracker_electronic_fence.m_lon[fence_order]);
        }
        else if(tracker_electronic_fence.m_lon[fence_order] < 0)
        {
            sprintf(data, " Lon:W%f;", -tracker_electronic_fence.m_lon[fence_order]);
        }
        strcat(tmp, data);


        if(tracker_electronic_fence.m_FenceType[fence_order] == Fence_Rectangle)
        {
            if(tracker_electronic_fence.m_lat1[fence_order] >= 0)
            {
                sprintf(data, " Lat:N%f;", tracker_electronic_fence.m_lat1[fence_order]);
            }
            else if(tracker_electronic_fence.m_lat1[fence_order] < 0)
            {
                sprintf(data, " Lat:S%f;", -tracker_electronic_fence.m_lat1[fence_order]);
            }
            strcat(tmp, data);

            if(tracker_electronic_fence.m_lon1[fence_order] >= 0)
            {
                sprintf(data, "Lon:E%f;", tracker_electronic_fence.m_lon1[fence_order]);
            }
            else if(tracker_electronic_fence.m_lon1[fence_order] < 0)
            {
                sprintf(data, "Lon:W%f;", -tracker_electronic_fence.m_lon1[fence_order]);
            }
            strcat(tmp, data);
            sprintf(data, "FenceType:Rectangle;");
            strcat(tmp, data);
        }
        else if(tracker_electronic_fence.m_FenceType[fence_order] == Fence_Circle)
        {
            sprintf(data, "Radius:%dM;", tracker_electronic_fence.m_dis[fence_order]);//��λ1�� cjt
            //sprintf(data, "Radius:%dM;", tracker_electronic_fence.m_dis[fence_order]/100);//��λ100�� cjt
            strcat(tmp, data);
            sprintf(data, "FenceType:Circle;");
            strcat(tmp, data);
        }

        if(tracker_electronic_fence.m_commit_type[fence_order] == COMMIT_ONLY_GPRS)
        {
            sprintf(data, "AlarmType:GPRS;");
            strcat(tmp, data);
        }
        else
        {
            sprintf(data, "AlarmType:GPRS+SMS;");
            strcat(tmp, data);
        }
        strcat(tmp, "}");
    }/*for fence_order */
    sprintf(sms_buf, tmp);
}


/**********************************************************************************************************************************
 *  Function    -  Tracker_Set_Electronic_Fence_Multi
 *
 *  Purpose     -  ����Χ������
 *
 *  Description -
 *
 * modification history
 * AT^GT_CM=FENCE, ON, 0, N23.10267,E114.39671,100#                received_data.part == 5
 * AT^GT_CM=FENCE, ON, 0, N23.10267,E114.39671,100,OUT#                received_data.part == 6
 * AT^GT_CM=FENCE, ON, 1, N23.10267,E114.39671,N23.10267,E114.39671#   received_data.part == 6
 * AT^GT_CM=FENCE, ON, 1, N23.10267,E114.39671,N23.10267,E114.39671,OUT#   received_data.part == 7
 * ----------------------------------------
 * v1.0  , 2012-06-01, guojie  written
 * ----------------------------------------
 * �ն�Ĭ�ϵ���Χ���ǹرյģ��������ֻ��˵��ڣ���ƽ̨���նˣ���������Χ����
 * GFENCE,<N>,<B>,0,<D>,<E>,<F>[,X][,M]#
 * Բ������
 * N=1-5��Χ����ţ�
 * B=ON/OFF������/�ر�Χ��������Ĭ��ֵΪ���ر�
 * D=Բ��γ��
 * E=Բ�ľ���
 * F=1��9999��Χ���뾶����λ������
 * X=IN/OUT��IN:��Χ��������OUT:��Χ��������Ϊ�ձ�ʾ��/��Χ�����ᱨ����Ĭ��Ϊ��/��Χ��
 * ���ᱨ����
 * M=0��1�������ϱ���ʽ��0����GPRS��1��SMS+GPRS��Ĭ��Ϊ��1
 * GFENCE,<N>,<B>,1,<D>,<E>,<F>,<G>[,X][,M]#
 * ������������
 * N=1-5��Χ����ţ�
 * B=ON/OFF������/�ر�Χ��������Ĭ��ֵΪ���ر�
 * D=����1 γ�ȣ���Χ��-90 ��90 �ȣ�
 * E=����1 ���ȣ���Χ��-180��180 �ȣ�
 * F=����2 γ�ȣ���Χ��-90 ��90 �ȣ�
 * G=����2 ���ȣ���Χ��-180��180 �ȣ�
 * γ����ֵǰ��֧��N/S �������룬Ҳ֧��+/-�������룻
 * ������ֵǰ��֧��E/W �������룬Ҳ֧��+/-�������룻
 * ԰
 * AT^GT_CM=GFENCE,1,ON,0,N23.10123,E113.12323,100#   received_data.part == 6
 * AT^GT_CM=GFENCE,1,ON,0,N23.10123,E113.12323,100,OUT#   received_data.part == 7
 * AT^GT_CM=GFENCE,1,ON,0,N23.10123,E113.12323,100,OUT,1#   received_data.part == 8
 * ����
 * AT^GT_CM=GFENCE,1,ON,1,N23.10267,E114.39671,N23.10267,E114.39671#   received_data.part == 7
 * AT^GT_CM=GFENCE,1,ON,1,N23.10267,E114.39671,N23.10267,E114.39671,OUT#   received_data.part == 8
 * AT^GT_CM=GFENCE,1,ON,1,N23.10267,E114.39671,N23.10267,E114.39671,OUT,1#   received_data.part == 9
 ***********************************************************************************************************************************/
static void Tracker_Set_Electronic_Fence_Multi(void)
{
    S16 error;
    S8 temp[100];
    U8 str_len;
    BOOL rpt = TRUE;
    U16 order; //Χ�����

    if(0 == received_data.part)    //�鿴Χ������
    {
        Tracker_See_Electronic_Fence_Set_Multi();
        return;
    }

    order = received_data.param0[0] - 0x31; // ���- ��1��

    if(order < 0 || order > MAX_FENCE_NUM - 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        return;
    }

    if(1 == received_data.part)    //�鿴Χ������
    {
        Tracker_See_Electronic_Fence_Set_Multi_1(order);
        return;
    }

    if(received_data.part < 2 || order < 0 || order > MAX_FENCE_NUM - 1)
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        if(Command_State == SMS_Command_State)
        {
            strcat(sms_buf, ";GFENCE,1,ON,0,N23.10123,E113.12323,200,OUT,1#");
        }
        return;
    }

    if(strcmp("OFF", ((char *)received_data.param1)) == 0)
    {
        tracker_electronic_fence.m_state[order] = KAL_FALSE;
        WriteRecord(NVRAM_EF_TRACKER_ELECTRONIC_FENCE_LID, 1, (void*)&tracker_electronic_fence, NVRAM_EF_TRACKER_ELECTRONIC_FENCE_SIZE, &error);
        //LOGD("--close fence: order=%d m_state[%d]=%d", order, order,tracker_electronic_fence.m_state[order]);
        if(KAL_FALSE == is_any_fence_open_flag())   //���û��Χ������
        {
            if(IsMyTimerExist(GPS_FENCE_CHECK_TIMER_ID))
            {
                StopTimer(GPS_FENCE_CHECK_TIMER_ID);
            }
            StartTimer(GPS_FENCE_CHECK_TIMER_ID, 2000, GPS_Fence_OFF);
        }
        //sprintf(sms_buf, "OK");
        /*-----�����SMS ATָ���������ϴ�ͬ��������---------------*/
        // OK#GFENCE# ���,����,��״0,�ϱ�ά,������,Բ�ľ�γ��,�뾶(����),�澯ģʽ
        if(Command_State != ONLine_Command_State)
        {
		#if 1
            LOGD("�ر�Χ��ͬ��");
            Commit_All_Gfences();
		#else
            nvram_ef_tracker_electronic_fence_struct *p;
            p = &tracker_electronic_fence;
            memset(sms_buf_ex, 0, sizeof(sms_buf_ex));
            sprintf(sms_buf_ex, "OK#GFENCE# %d,0", order + 1);
            LOGD("�ر�Χ��ͬ��-%s", sms_buf_ex);
            gprs_send_type = GPRS_ONLINE_ASCII_DATA_REPLY_EX;
            Tracker_Socket_Send_Current_Data();
		#endif
        }

		//-----------ͬ������-------------------------------------
        create_close_gfence_reply(order, tracker_electronic_fence.m_FenceType[order]); //�ظ��ر�
        return;
    }

    if((received_data.part != 6) && (received_data.part != 7) && (received_data.part != 8) && (received_data.part != 9))
    {
        sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
        if(Command_State == SMS_Command_State)
        {
            strcat(sms_buf, ";FENCE,ON,0,N23.10827,E114.41396,2,IN #");
        }
        return;
    }
    if((strcmp("ON", ((char *)received_data.param1)) == 0) || (strcmp("OFF", ((char *)received_data.param1)) == 0))
    {
        ;  // ON or OFFָ��
    }
    else
    {
        LOGD("false rpt1");
        rpt = FALSE;
    }

    if(strlen((char *)received_data.param2) == 1 && ((received_data.param2[0] == '1') || (received_data.param2[0] == '0')))
    {
        ; // Բ�����
    }
    else
    {
        LOGD("false rpt2");
        rpt = FALSE;

    }
    LOGD("received_data.param0 = %s,received_data.param1 = %s", received_data.param0, received_data.param1);

    if(rpt == TRUE)
    {
        if(received_data.param2[0] == '0')
        {
            Tracker_Set_Fence_Circle_Multi();
        }
        else if(received_data.param2[0] == '1')
        {
            Tracker_Set_Fence_Rectangle_Multi();
        }
        else
        {
            sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
            if(Command_State == SMS_Command_State)
            {
                strcat(sms_buf, ";FENCE,1,ON,0,N23.10827,E114.41396,200,IN#");
            }
        }
    }
    else
    {
        sprintf(sms_buf, "ERROR:102");//���ݸ�ʽ����
        if(Command_State == SMS_Command_State)
        {
            strcat(sms_buf, ";FENCE,1,ON,0,N23.10827,E114.41396,200,IN#");
        }
    }
}

#endif/*__MULTI_FENCE__*/

/******************************************************************************
 *  Function    -  Tracker_Fence_Alarm_Address_SendSMS
 *
 *  Purpose     -  �ظ����ĵ�ַ����
 *
 *  Description -  �������·�����Χ��������Ϣ
 *
 * modification history    ��Ϣ���͸��������
 * ----------------------------------------
 * v1.0  , 26-05-2012,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
static void Tracker_Fence_Alarm_Address_SendSMS(void)
{
    int i = 0;
    int NumLen = 0;
    U8 phbNumIndex = 0;
    char phone_num[21];

    Command_State = SMS_Command_State;
    memset(sys_send_sms.num, 0, 21);

    NumLen = strlen((char *)received_data.param1);

    //  ����Ϊ��ʱ����������������
    if(NumLen == 0)
    {
        memcpy(sys_send_sms.num, sys_rcv_sms.num, 21);
    }
    else
    {
        memcpy(sys_send_sms.num, received_data.param1, 21);
    }

    memset((char *)sys_send_sms.content, 0, 320);

    if(GetAddressLen % 2)
    {
        GetAddressLen = GetAddressLen + 1;
    }

    for(i = 0; i < GetAddressLen / 2 ; i++)
    {
        sys_send_sms.content[2*(i)+1] = received_data.param0[2*i];
        sys_send_sms.content[2*(i)] = received_data.param0[2*i+1];
    }
    sys_send_sms.len = GetAddressLen  / 2;

    LOGD("Fence_Alarm_SendSMS %d,%d ,%d", NumLen, sys_send_sms.len, mmi_ucs2strlen(sys_send_sms.content));

    if(NumLen == 0)
    {
        for(phbNumIndex = 0; phbNumIndex < SOS_PHB_NUM_MAX; phbNumIndex++)
        {
            if(strlen((S8*) tracker_sos_phb.ph_num[phbNumIndex]))
            {
                SetSendSMS(FALSE, tracker_sos_phb.ph_num[phbNumIndex] , 0, sys_send_sms.content);
            }
        }
    }
    else
    {
        SetSendSMS(FALSE, sys_send_sms.num, 0, sys_send_sms.content);
    }
}

#endif/*__GPS_FENCE__*/

#if defined(__KJX_RESET_USED_COUNT__)
void Tracker_Reset_Used_Count(void)
{
	if(received_data.part == 0)
	{
		kjx_reset_ruc();	
		sprintf(sms_buf, "OK");
	}
	else
	{
		sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
	}
}

void Tracker_Get_Used_Count(void)
{
	if(received_data.part == 0)
	{
		sprintf((char *)sms_buf, "Currently in useflag:%d, usecount:%d;", g_kjx_nvram_struct.useflag, g_kjx_nvram_struct.usecount);
	}
	else
	{
		sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
	}
}
#endif

#ifdef __KJX_FUN_AGPS__
extern U16 kjx_gps_uart_write(U8 *buffer,U16 len);
extern void kjx_handle_get_agps_data(void);
#ifdef __KJX_FUN_GPS_ZKW__
extern void kjx_gps_open_agps_status_check(void);
extern void kjx_gps_close_agps_status_check(void);
#endif

void Tracker_GPS_AGPS_Update(void)
{
	if(received_data.part == 0)
	{
		kjx_handle_get_agps_data();	
		sprintf(sms_buf, "OK!AGPS Update start!");
	}
	else
	{
		sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
	}
}

#ifdef __KJX_FUN_GPS_ZKW__
void Tracker_GPS_AGPS_Status_Check_Set(void)
{
	if(received_data.part == 1)
	{
		if(strcmp("ON", ((char *)received_data.param0)) == 0)
		{
			kjx_gps_open_agps_status_check();	
			sprintf(sms_buf, "OK!AGPS check turn on!");
		}
		else if(strcmp("OFF", ((char *)received_data.param0)) == 0)
		{
			kjx_gps_close_agps_status_check();
			sprintf(sms_buf, "OK!AGPS check turn off!");
		}
		else
		{
			sprintf(sms_buf, "ERROR:101");//ָ��Ȳ���ȷ
		}
	}
	else
	{
		sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
	}
}
#endif

#ifdef __KJX_FUN_GPS_HD__
extern void Tracker_HD_AGPS_Put_AID_Time(applib_time_struct systime);
extern void Tracker_HD_AGPS_Put_AID_Pos(double latitude, double longitude);
extern void Tracker_HD_AGPS_Put_AID_PEPH_GPS(U8 *data, U32 datalen);
extern void Tracker_HD_AGPS_Put_AID_PEPH_BDS(U8 *data, U32 datalen);

void Tracker_HD_GPS_Set(void)
{
	if(received_data.part == 1)
	{
		if(!kjx_gps_is_on())
		{
			kjx_open_gps();
			StartTimer(KJX_TIMER_ID_GPS_SUSPEND, 500, Tracker_HD_GPS_Set);
		}
			
		if(strcmp("VER", ((char *)received_data.param0)) == 0)
		{
			U8 cmdstr[] = {0xF1,0xD9,0x0A,0x04,0x00,0x00,0x0E,0x34};
			
			kjx_gps_uart_write(cmdstr, 8);
			
			sprintf(sms_buf, "OK!get version!");
		}
		else if(strcmp("COLDRST", ((char *)received_data.param0)) == 0)
		{
			U8 cmdstr[] = {0xF1,0xD9,0x06,0x40,0x01,0x00,0x01,0x48,0x22};
			
			kjx_gps_uart_write(cmdstr, 9);
			
			sprintf(sms_buf, "OK!cold reset!");
		}
		else if(strcmp("WARMRST", ((char *)received_data.param0)) == 0)
		{
			U8 cmdstr[] = {0xF1,0xD9,0x06,0x40,0x01,0x00,0x02,0x49,0x23};
			
			kjx_gps_uart_write(cmdstr, 9);
			
			sprintf(sms_buf, "OK!warm reset!");
		}	
		else if(strcmp("HOTRST", ((char *)received_data.param0)) == 0)
		{
			U8 cmdstr[] = {0xF1,0xD9,0x06,0x40,0x01,0x00,0x03,0x4A,0x24};
			
			kjx_gps_uart_write(cmdstr, 9);
			
			sprintf(sms_buf, "OK!hot reset!");
		}
		else if(strcmp("ONLYGPS", ((char *)received_data.param0)) == 0)
		{
			U8 cmdstr[] = {0xF1,0xD9,0x06,0x0C,0x04,0x00,0x01,0x00,0x00,0x00,0x17,0xA0};
			
			kjx_gps_uart_write(cmdstr, 12);

			sprintf(sms_buf, "OK!only gps mode");
		}
		else if(strcmp("ONLYBDS", ((char *)received_data.param0)) == 0)
		{
			U8 cmdstr[] = {0xF1,0xD9,0x06,0x0C,0x04,0x00,0x04,0x00,0x00,0x00,0x1A,0xAC};
			
			kjx_gps_uart_write(cmdstr, 12);
			
			sprintf(sms_buf, "OK!only bds mode!");
		}
		else if(strcmp("BDSGPS", ((char *)received_data.param0)) == 0)
		{
			U8 cmdstr[] = {0xF1,0xD9,0x06,0x0C,0x04,0x00,0x05,0x00,0x00,0x00,0x1B,0xB0};
			
			kjx_gps_uart_write(cmdstr, 12);

			sprintf(sms_buf, "OK!gps and bds mode!");
		}
		else if(strcmp("AIDTIME", ((char *)received_data.param0)) == 0)
		{
			applib_time_struct rtc_time,utc_time;

			applib_dt_get_rtc_time(&rtc_time);	
			applib_dt_rtc_to_utc_with_default_tz(&rtc_time, &utc_time);
			Tracker_HD_AGPS_Put_AID_Time(utc_time);
		}
		else if(strcmp("AIDPOS", ((char *)received_data.param0)) == 0)
		{
			Tracker_HD_AGPS_Put_AID_Pos(22.5006727, 114.2424747);
		}
		else if(strcmp("AIDPEPHGPS", ((char *)received_data.param0)) == 0)
		{
			U8 cmdstr[325] = {0x0b,0x01,0x3f,0x32,0x0d,0xa1,0x9f,0x66,0xdd,0x02,0xbd,0x5b,0x69,0xf9,0x20,0x2e,0xa6,0x59,0x58,0x54,
							  0x50,0x27,0xd7,0x02,0xae,0x74,0x91,0x93,0xee,0xa9,0xff,0xff,0x66,0x9a,0x73,0x13,0xa0,0xf8,0x0e,0x16,
							  0xba,0x16,0x5f,0xf7,0x21,0x00,0x16,0x00,0xa6,0x59,0xea,0xcd,0x00,0x00,0x0b,0x00,0x00,0x0b,0x6e,0x03,
							  0x56,0x00,0x56,0x02,0x00,0x0b,0x02,0xd9,0xb9,0x0c,0xa1,0xcb,0xb4,0x15,0x08,0x8e,0x00,0x92,0x08,0xc4,
							  0x33,0xa6,0x59,0xdb,0x31,0x73,0x26,0x1d,0x02,0x24,0xc5,0xb0,0x91,0x93,0xa5,0xff,0xff,0xab,0xc9,0x1d,
							  0xaa,0x4a,0xf7,0x1e,0x18,0x38,0x13,0x5e,0xf6,0x98,0xff,0x79,0x00,0xa6,0x59,0xc0,0x1e,0x13,0x00,0xe9,
							  0xff,0x00,0xd6,0x6e,0x03,0x36,0x00,0x36,0x02,0x00,0x0b,0x03,0xf8,0x62,0x0d,0xa1,0x93,0xc2,0x1c,0x00,
							  0x62,0x1f,0xc6,0x21,0x64,0x36,0xa6,0x59,0xd9,0x3d,0x11,0x27,0x9a,0x05,0x90,0x3d,0x00,0xbe,0xe5,0xa6,
							  0xff,0xff,0x30,0x4a,0xaf,0xbc,0x1b,0x03,0x54,0x0f,0xea,0x1d,0x82,0x03,0xed,0xff,0x10,0x00,0xa6,0x59,
							  0x3e,0xb7,0xfd,0xff,0xe3,0xff,0x00,0x03,0x6e,0x03,0x50,0x00,0x50,0x02,0x00,0x0b,0x04,0x83,0x3b,0x0d,
							  0xa1,0xae,0xb7,0x5b,0x04,0x5f,0x81,0x3e,0x7b,0xe3,0x38,0xa6,0x59,0xa8,0x73,0x0d,0x28,0x08,0x03,0x6e,
							  0xbe,0xef,0x3e,0x79,0xa9,0xff,0xff,0x60,0x62,0x9b,0x24,0x15,0x0a,0x08,0x08,0x90,0x27,0xa8,0x0b,0x09,
							  0x00,0xd6,0xff,0xa6,0x59,0x74,0x8a,0xf7,0xff,0xfd,0xff,0x00,0xd7,0x6e,0x03,0x4c,0x00,0x4c,0x02,0x3f,
							  0x0b,0x05,0xf2,0x7f,0x0e,0xa1,0x69,0xef,0x5f,0x02,0xb4,0xb2,0x7a,0x98,0xdc,0x38,0x68,0x5b,0x30,0x65,
							  0x8a,0x26,0x6f,0x06,0x22,0xb5,0x7f,0xbd,0x43,0xa6,0xff,0xff,0x68,0x0c,0x90,0x12,0x34,0x03,0x8c,0x0f,
							  0xfe,0x1c,0x3a,0x04,0xf6,0xff,0xda,0xff,0x68,0x5b,0x3f,0x5f,0xfc,0xff,0x19,0x00,0x00,0xe9,0x6e,0x03,
							  0x13,0x00,0x03,0x02,0x00};
			
			Tracker_HD_AGPS_Put_AID_PEPH_GPS(cmdstr, 325);
		}
		else if(strcmp("AIDPEPHBDS", ((char *)received_data.param0)) == 0)
		{
			U8 cmdstr[325] = {0x0b,0x01,0x3f,0x32,0x0d,0xa1,0x9f,0x66,0xdd,0x02,0xbd,0x5b,0x69,0xf9,0x20,0x2e,0xa6,0x59,0x58,0x54,
							  0x50,0x27,0xd7,0x02,0xae,0x74,0x91,0x93,0xee,0xa9,0xff,0xff,0x66,0x9a,0x73,0x13,0xa0,0xf8,0x0e,0x16,
							  0xba,0x16,0x5f,0xf7,0x21,0x00,0x16,0x00,0xa6,0x59,0xea,0xcd,0x00,0x00,0x0b,0x00,0x00,0x0b,0x6e,0x03,
							  0x56,0x00,0x56,0x02,0x00,0x0b,0x02,0xd9,0xb9,0x0c,0xa1,0xcb,0xb4,0x15,0x08,0x8e,0x00,0x92,0x08,0xc4,
							  0x33,0xa6,0x59,0xdb,0x31,0x73,0x26,0x1d,0x02,0x24,0xc5,0xb0,0x91,0x93,0xa5,0xff,0xff,0xab,0xc9,0x1d,
							  0xaa,0x4a,0xf7,0x1e,0x18,0x38,0x13,0x5e,0xf6,0x98,0xff,0x79,0x00,0xa6,0x59,0xc0,0x1e,0x13,0x00,0xe9,
							  0xff,0x00,0xd6,0x6e,0x03,0x36,0x00,0x36,0x02,0x00,0x0b,0x03,0xf8,0x62,0x0d,0xa1,0x93,0xc2,0x1c,0x00,
							  0x62,0x1f,0xc6,0x21,0x64,0x36,0xa6,0x59,0xd9,0x3d,0x11,0x27,0x9a,0x05,0x90,0x3d,0x00,0xbe,0xe5,0xa6,
							  0xff,0xff,0x30,0x4a,0xaf,0xbc,0x1b,0x03,0x54,0x0f,0xea,0x1d,0x82,0x03,0xed,0xff,0x10,0x00,0xa6,0x59,
							  0x3e,0xb7,0xfd,0xff,0xe3,0xff,0x00,0x03,0x6e,0x03,0x50,0x00,0x50,0x02,0x00,0x0b,0x04,0x83,0x3b,0x0d,
							  0xa1,0xae,0xb7,0x5b,0x04,0x5f,0x81,0x3e,0x7b,0xe3,0x38,0xa6,0x59,0xa8,0x73,0x0d,0x28,0x08,0x03,0x6e,
							  0xbe,0xef,0x3e,0x79,0xa9,0xff,0xff,0x60,0x62,0x9b,0x24,0x15,0x0a,0x08,0x08,0x90,0x27,0xa8,0x0b,0x09,
							  0x00,0xd6,0xff,0xa6,0x59,0x74,0x8a,0xf7,0xff,0xfd,0xff,0x00,0xd7,0x6e,0x03,0x4c,0x00,0x4c,0x02,0x3f,
							  0x0b,0x05,0xf2,0x7f,0x0e,0xa1,0x69,0xef,0x5f,0x02,0xb4,0xb2,0x7a,0x98,0xdc,0x38,0x68,0x5b,0x30,0x65,
							  0x8a,0x26,0x6f,0x06,0x22,0xb5,0x7f,0xbd,0x43,0xa6,0xff,0xff,0x68,0x0c,0x90,0x12,0x34,0x03,0x8c,0x0f,
							  0xfe,0x1c,0x3a,0x04,0xf6,0xff,0xda,0xff,0x68,0x5b,0x3f,0x5f,0xfc,0xff,0x19,0x00,0x00,0xe9,0x6e,0x03,
							  0x13,0x00,0x03,0x02,0x00};
						
			Tracker_HD_AGPS_Put_AID_PEPH_BDS(cmdstr, 325);
		}
		else
		{
			sprintf(sms_buf, "ERROR:101");//ָ��Ȳ���ȷ
		}
	}
	else
	{
		sprintf(sms_buf, "ERROR:100");//ָ��Ȳ���ȷ
	}

}
#endif

#endif

/******************************************************************************
 * FUNCTION			AT_OR_SMS_Command_Pro
 *
 * DESCRIPTION
 *
 * PARAMETERS
 *		void
 * RETURNS
 *  		void
 * ----------------------------------------
 * v1.0  , 2011-10-27, guojie  written
 * ----------------------------------------
 *****************************************************************************/
static void AT_OR_SMS_Command_Pro(void)
{
    memset(sms_buf, 0, sizeof(sms_buf));

    LOGD("CMD_str:%s State:%d ", received_data.main_str, Command_State);
	kal_prompt_trace(MOD_TST,"AT_OR_SMS_Command_Pro main_str is:%s, State:%d ", received_data.main_str, Command_State);

#ifndef KJX_TEST
    if(!EntryTestModeReady)
    {
        memset(sms_buf, 0, sizeof(sms_buf));
        sprintf(sms_buf, "No Ready");
        Send_Command_Message_Replay();
        return;
    }
#endif

	if(strcmp((char *)received_data.main_str, "IMEI") == 0)
    {
        Tracker_Set_IMEI();
    }
    //��ѯָ��
    else if(strcmp((char *)received_data.main_str, "IMSI") == 0)
    {
        Tracker_See_SIM_IMSI();
    }
    else if(strcmp((char *)received_data.main_str, "ATD") == 0)
    {
        Tracker_Call_Set_Number();
    }
	else if(strcmp((char *)received_data.main_str, "SMS") == 0)
	{
		Tracker_Sms_Set_Number();
	}
    else if(strcmp((char *)received_data.main_str, "VERSION") == 0)
    {
        Tracker_Get_Software_Version();
    }
    else if(strcmp((char *)received_data.main_str, "STATUS") == 0)
    {
        Tracker_Get_Current_Status();
    }
    else if(strcmp((char *)received_data.main_str, "SOS") == 0)
    {
        Tracker_SOS_Phone_Number();
    }
    else if(strcmp((char*)received_data.main_str, "TEST") == 0)
    {
        Tracker_Entry_Test_Mode();
    }
	else if(strcmp((char *)received_data.main_str, "VIBRATOR") == 0)
	{
		Tracker_At_Vibrateor();
	}
#if defined(__KJX_RFID__)
	else if(strcmp((char *)received_data.main_str, "RFID") == 0)
	{
		Tracker_RFID_Set();
	}
#endif
#if defined(__BLE_MODULE_SUPPORT__)
	else if(strcmp((char *)received_data.main_str, "BLE") == 0)
	{
		Tracker_BLE_iBeacom_Set();
	}
#endif
#if defined(__KJX_FUN_SENSOR__)
	else if(strcmp((char *)received_data.main_str, "SENSOR") == 0)
	{
		Tracker_Sensor_Set();
	}
#endif
#if defined(__KJX_FUN_GPS__)
    else if(strcmp((char *)received_data.main_str, "GPSON") == 0)
    {
        Tracker_Command_Active_GPS();
    }
    else if(strcmp((char *)received_data.main_str, "GPSOFF") == 0)
    {
        Tracker_Command_Close_GPS();
    }
    else if(strcmp((char*)received_data.main_str, "GPSTC") == 0)
    {
        Tracker_GPS_Transparent_Set();
    }
	else if(strcmp((char *)received_data.main_str, "REOPENGPS") == 0)
    {
        Tracker_Command_Restart_GPS();
    }
	else if(strcmp((char *)received_data.main_str, "RESETGPS") == 0)
	{
		Tracker_Command_Reset_GPS();
    }	
	else if(strcmp((char*)received_data.main_str, "GPSMODE") == 0)
    {
        Tracker_GPS_WorkMode_Set();
    }
#ifdef __KJX_FUN_AGPS__
#ifdef __KJX_FUN_GPS_ZKW__
	else if(strcmp((char*)received_data.main_str, "AGPSCHK") == 0)
    {
        Tracker_GPS_AGPS_Status_Check_Set();
    }
#endif
#ifdef __KJX_FUN_GPS_HD__
	else if(strcmp((char*)received_data.main_str, "HDGPS") == 0)
    {
        Tracker_HD_GPS_Set();
    }
#endif
	else if(strcmp((char*)received_data.main_str, "AGPSUPDATE") == 0)
    {
        Tracker_GPS_AGPS_Update();
    }	
#endif
#endif
#if defined(__KJX_RESET_USED_COUNT__)
	else if(strcmp((char *)received_data.main_str, "RUCRESET") == 0)
    {
        Tracker_Reset_Used_Count();
    }
	else if(strcmp((char *)received_data.main_str, "RUC") == 0)
    {
        Tracker_Get_Used_Count();
    }	
#endif
    else if(strcmp((char *)received_data.main_str, "GPRSSET") == 0)
    {
        Tracker_Gprs_Param_See();
    }
    else if(strcmp((char *)received_data.main_str, "PARAM") == 0)
    {
        Traceker_Phb_Imei_Param_See();
    }
#if defined(__KD6113_MCU_CONTROL__)
	else if(strcmp((char *)received_data.main_str, "MCUCHECK") == 0)
	{
		Tracker_Send_Message_To_MCU("AT^GT_CM=01#");
	}
	else if(strcmp((char *)received_data.main_str, "MCUTEST") == 0)
	{
		Tracker_Send_Message_To_MCU("AT^GT_CM=04,0,1000#");
	}
	else if(strcmp((char *)received_data.main_str, "MCUDEBUG") == 0)
	{
		char cmdbuf[128] = {0};

		strcpy(cmdbuf, "AT^GT_CM=");
		
		if(received_data.part >= 1)
		{
			strcat(cmdbuf, (char*)received_data.param0);
		}
		if(received_data.part >= 2)
		{
			strcat(cmdbuf, ",");
			strcat(cmdbuf, (char*)received_data.param1);
		}
		if(received_data.part >= 3)
		{
			strcat(cmdbuf, ",");
			strcat(cmdbuf, (char*)received_data.param2);
		}
		if(received_data.part >= 4)
		{
			strcat(cmdbuf, ",");
			strcat(cmdbuf, (char*)received_data.param3);
		}
		if(received_data.part >= 5)
		{
			strcat(cmdbuf, ",");
			strcat(cmdbuf, (char*)received_data.param4);
		}
		
		strcat(cmdbuf, "#");
		
		Tracker_Send_Message_To_MCU(cmdbuf);
		
		sprintf(sms_buf, "OK");
	}
#endif/*__KD6113_MCU_CONTROL__*/
	else if(strcmp((char *)received_data.main_str, "CHARGETEST") == 0)	  // ������
	{
		if(1 == received_data.part)
		{
			g_cur_min = atoi(received_data.param0);
			g_cur_max = 500;
		}
		else if(2 == received_data.part)
		{
			g_cur_min = atoi(received_data.param0);
			g_cur_max = atoi(received_data.param1);;
		}
		else
		{
			g_cur_min = 10;
			g_cur_max = 500;
		}

		if(0 == g_cur_min)
		{
			g_cur_min = 10;
		}
		if(0 == g_cur_max)
		{
			g_cur_min = 500;
		}
	
		Tracker_Charge_Test();
		return; //10��ѭ�������ڲ��ظ�
	}
	else if(strcmp((char *)received_data.main_str, "TFCARDTEST") == 0)
	{
		FS_HANDLE file = 0;
		U8 drive;
		U32 written = 0;
		int result;
		char FilePathBuf[30] = {0};
		char FilePath[60] = {0};
		char tmpbuf[50] = {0};
		
		drive = FS_GetDrive(FS_DRIVE_V_REMOVABLE, 1, FS_NO_ALT_DRIVE);
		sprintf(FilePathBuf, "%c:\\", drive);

		mmi_asc_to_ucs2((CHAR*)FilePath, (CHAR*)FilePathBuf);
		mmi_ucs2cat((CHAR*)FilePath,(const CHAR*)L"Test.txt");
		
		file = FS_Open((const WCHAR *)FilePath, FS_READ_WRITE | FS_CREATE_ALWAYS);
		if(file >= 0)
		{
			result = FS_Write(file, "\r\n", strlen("\r\n"), &written);
			if(result >= FS_NO_ERROR)
			{
				strcpy(tmpbuf,"TFCARDOK");
			}
			else
			{
				strcpy(tmpbuf,"TFCARDFAIL 001");
			}
			FS_Commit(file);
			FS_Close(file);
			FS_Delete((const WCHAR*)FilePath);
        }
		else
		{
			strcpy(tmpbuf,"TFCARDFAIL 002");
		}
		
		rmmi_write_to_uart((kal_uint8*)tmpbuf, strlen(tmpbuf), KAL_TRUE);
		return;
	}
#if defined(__LED_APP__)
	else if(strcmp((char *)received_data.main_str, "LEDON") == 0)
	{
		Tracker_Set_LED_ON();
	}
	else if(strcmp((char *)received_data.main_str, "LEDOFF") == 0)
	{
		Tracker_Set_LED_OFF();
	}
#endif/*__LED_APP__*/

#if defined(__KJX_LOG_OUTPUT__)
    else if(strcmp((char *)received_data.main_str, "LOG") == 0)
    {
        Tracker_Set_Log_Param();
    }
#endif /*__KJX_LOG_OUTPUT__*/	
#if defined(__KD6113_WORK_MODE__)	//xb add 2015-01-16 ˯��ģʽ�³���˯��ָ�������һ�ɲ�ִ��
	else if(strcmp((char *)received_data.main_str, "WORKMODE") == 0)
	{
		Tracker_Set_Work_Mode();
	}
	else if((tracker_ctrl_data.workmode.type == MODE_WORK_2) && (Command_State == SMS_Command_State))//�ǳ���ģʽ���¶���ָ���Ӧ
	{
	#if defined(__KJX_AT_APP__)
        //�����ָ��ͷֻ��ATָ��ظ�
		if((Command_State == AT_Command_State)
	#if defined(__AT_USE_UART1__)
		||(Command_State == UART1_Command_State)
	#endif
		)
        {
            sprintf(sms_buf, "ERROR:107");
		    Send_Command_Message_Replay();
			return;
        }
        else
	#endif
        {
            return ;
        }
	}
#endif/*__KD6113_WORK_MODE__*/	
    else if(strcmp((char *)received_data.main_str, "ATH") == 0)
    {
        Tracker_Hangup_Call();
    }
    else if(strcmp((char *)received_data.main_str, "ATA") == 0)
    {
        Tracker_Accepted_Call();
    }
    else if(strcmp((char *)received_data.main_str, "BMT") == 0)
    {
        Tracker_Query_Battery_Voltage();
        return;
    }
    else if(strcmp((char *)received_data.main_str, "TIMESET") == 0)
    {
        Tracker_Set_Datetime();
    }
    //����ָ��
    else if(strcmp((char *)received_data.main_str, "APN") == 0)
    {
        Tracker_Set_APN();
    }
#if defined(__APN_ADAPT__)
    else if(strcmp((char *)received_data.main_str, "ASETAPN") == 0)
    {
        Tracker_Set_APN_Auto_Adaption();
    }
#endif
    else if(strcmp((char *)received_data.main_str, "SERVER") == 0)
    {
        Tracker_Set_Server();
    }
#if defined(__SPECIAL_EPO_SOCKET__)
    else if(strcmp((char *)received_data.main_str, "EPOSERVER") == 0)
    {
        Tracker_Set_EPOServer();
    }
    else if(strcmp((char *)received_data.main_str, "EPOSTATE") == 0)
    {
        Tracker_Set_EPO_State();
    }
#elif defined(__SPECIAL_AGPS_SOCKET__)
    else if(strcmp((char *)received_data.main_str, "AGPSSERVER") == 0)
    {
        Tracker_Set_AGPSServer();
    }
    else if(strcmp((char *)received_data.main_str, "AGPSCONNECT") == 0)
    {
        Tracker_RDA_AGPS_Conncet();
    }
#endif
#if defined(__AMS_BK_URL__)
	else if((strcmp((char *)received_data.main_str, "MSERVER") == 0)
				|| (strcmp((char *)received_data.main_str, "MSERVER1") == 0)
				|| (strcmp((char *)received_data.main_str, "MSERVER2") == 0)
				|| (strcmp((char *)received_data.main_str, "MSERVER3") == 0)
				|| (strcmp((char *)received_data.main_str, "MSERVER4") == 0)
				) // ����AGPS������������������ʽָ��
	{
		Tracker_Set_AMS();
	}
	else if(strcmp((char *)received_data.main_str, "SERVER2") == 0)
	{
		Tracker_Set_AMS_Current_IP();
	}	
#endif
    else if(strcmp((char *)received_data.main_str, "GMT") == 0)
    {
        Traceker_Set_Time_Zone();
    }
#if defined(__TIMEZONE_ADAPT__)
    else if(strcmp((char *)received_data.main_str, "ASETGMT") == 0)
    {
        Tracker_Set_GMT_Auto_Adaption();
    }
#endif
    else if(strcmp((char *)received_data.main_str, "RECONNECT") == 0)
    {
        Tracker_Server_Reconnect();
    }
    else if(strcmp((char *)received_data.main_str, "QLOCKIP") == 0)
    {
        Traceker_Query_Server_Lock();
    }
    else if(strcmp((char *)received_data.main_str, "LOCKIP") == 0)
    {
        Traceker_Set_Server_Lock();
    }
	else if(strcmp((char *)received_data.main_str, "UNLOCKIP") == 0)
    {
        Traceker_Set_Server_UnLock();
    }	
    else if(strcmp((char *)received_data.main_str, "GPRSON") == 0)
    {
        Traceker_Set_GPRS_OnOff_Status();
    }
    else if(strcmp((char *)received_data.main_str, "LINK") == 0)
    {
        Traceker_Set_GPRS_Link_Times();
    }
    else if(strcmp((char *)received_data.main_str, "GPRSALM") == 0)
    {
        Traceker_Set_GPRS_Block_Alarm_Status();
    }
    else if(strcmp((char *)received_data.main_str, "BATALM") == 0)
    {
        Tracker_Set_LowBat_Status();
    }
    else if(strcmp((char *)received_data.main_str, "LANG") == 0)
    {
        Tracker_Set_Current_Language();
    }
    else if(strcmp((char *)received_data.main_str, "SEESOS") == 0)
    {
        Tracker_Online_See_SOS_PhbNum();
        return;
    }	
    else if(strcmp((char *)received_data.main_str, "PERMIT") == 0)
    {
        Tracker_Set_Command_Permit();
    }
    else if(strcmp((char *)received_data.main_str, "SOSPERMIT") == 0)
    {
        Tracker_Set_SOS_Permit();
    }
    else if(strcmp((char *)received_data.main_str, "MONPERMIT") == 0)
    {
        Tracker_Set_Monitor_Permit();
    }
    else if(strcmp((char *)received_data.main_str, "SEEPARAM") == 0)     //�������鿴�ն˲���
    {
        is_online_see_cmd = TRUE;
        Tracker_Send_See_System_Param();
        return;
    }	
    else if(strcmp((char *)received_data.main_str, "SCXSZ") == 0)
    {
        Tracker_Apn_Server_Time_Interval_See();
    }
    //����ָ��
    else if(strcmp((char *)received_data.main_str, "RESET") == 0)
    {
        Tracker_Reset_Process();
    }
	else if(strcmp((char *)received_data.main_str, "POWEROFF") == 0)
	{
		Tracker_Set_Power_off();
	}
    else if(strcmp((char *)received_data.main_str, "FACTORY") == 0)
    {
        Tracker_Resume_Factory_SetPart();
    }
    else if(strcmp((char *)received_data.main_str, "FACTORYALL") == 0)
    {
        Tracker_Resume_Factory_SetAll();
    }
    else  if(strcmp((char*)received_data.main_str, "PCBA") == 0)
    {
    #ifndef KJX_TEST
        Tracker_Factory_AutoTest();
	#endif
    }
    else if(strcmp((char *)received_data.main_str, "UPDATE") == 0)    //�ն�����
    {

    }
    else if(strcmp((char *)received_data.main_str, "VERSION_PC") == 0 && 
		(Command_State == AT_Command_State
	#if defined(__AT_USE_UART1__)
		||Command_State == UART1_Command_State
	#endif
		)
	)		
    {
        Tracker_Get_Software_Version_For_Factory();
    }
#if defined(__SMS_PASSWORD__)
    else if(strcmp((char *)received_data.main_str, "PWDSW") == 0)
    {
        Tracker_Set_Password_Status();
    }
    else if(strcmp((char *)received_data.main_str, "PASSWORD") == 0)
    {
        Tracker_Change_Password();
    }
    else if(strcmp((char *)received_data.main_str, "RECOVER") == 0)
    {
        Tracker_Resume_Password();
    }
#endif
#if defined(__SOS_CALL__)
    else if(strcmp((char *)received_data.main_str, "SOSALM") == 0)
    {
        Tracker_Set_SOS_Alarm_Status();
    }
    else if(strcmp((char *)received_data.main_str, "CALL") == 0)
    {
        Tracker_Set_SOS_Call_Times();
    }
#endif
#if defined(__LED_APP__)
    else if(strcmp((char *)received_data.main_str, "LEDSLEEP") == 0)
    {
        Tracker_Set_Led_Sleep_Status();
    }
#endif
#if defined(__SMS_TRANSMISSION__)
    else  if(strcmp((char*)received_data.main_str, "FW") == 0)
    {
        Tracker_Query_Balance_Fee();
        return ;
    }
#endif /*__SMS_TRANSMISSION__*/
#if defined(__BOSCH_BMA250E__)
    else if(strcmp((char *) received_data.main_str, "DEFMODE") == 0)
    {
        Tracker_Set_Defense_Mode();
    }
    else if(strcmp((char *) received_data.main_str, "111") == 0)
    {
        Tracker_Set_Defense_Start();
        return;
    }
    else if(strcmp((char *) received_data.main_str, "000") == 0)
    {
        Tracker_Set_Defense_Stop();
        return;
    }
    else if(strcmp((char *) received_data.main_str, "DEFENSE") == 0)
    {
        Tracker_Set_Defense_Timer();
    }
    else if(strcmp((char *)received_data.main_str, "SENDS") == 0)
    {
        Tracker_Set_Sensor_GPS_Time();
    }
    else if(strcmp((char *)received_data.main_str, "SENSOR") == 0)
    {
        Tracker_Set_Sensor_Detect_Time();
    }
    else if(strcmp((char*) received_data.main_str, "SENALM") == 0)
    {
        Tracker_Bosch_Sensor_Alarm_Switch();
    }
    else if(strcmp((char*) received_data.main_str, "SENSORSET") == 0)
    {
        Tracker_Bosch_Sensor_Alarm_Param();
    }
    else if(strcmp((char *)received_data.main_str, "LEVEL") == 0)
    {
        Tracker_Set_Sensor_Level();
    }
    else if(strcmp((char *)received_data.main_str, "STATICREP") == 0)
    {
        Tracker_Set_Static_Send_LastGPS();
    }
    else if(strcmp((char *)received_data.main_str, "DSRESET") == 0)
    {
        Tracker_Defences_Reset();
    }
#endif
#if defined(__GPS_ON_MTK__)
    else if(strcmp((char *) received_data.main_str, "ADDRESS") == 0)     //�������·�
    {
        Tracker_Get_Address_SendSMS();
        return;
    }
    else if(strcmp((char *) received_data.main_str, "ALARMSMS") == 0)
    {
        Tracker_Get_Address_SendSMS();
        return;
    }
    else if(strcmp((char *)received_data.main_str, "WHERE") == 0)
    {
        //Tracker_Query_Get_Latitude_and_Longitude();
        if(Command_State == SMS_Command_State || Command_State == AT_Command_State)
        {
            if(is_empty_sos_set())
            {
                // SOS����ȫ�ղ����� WHERE
                LOGD("***WHERE����Ȩ SOS����ȫ��****");
                SetSendSMS(FALSE, sys_rcv_sms.num , STR_KKSAPP_ERROR_PHONE, NULL);
            }
            else
            {
            	tracker_gpspoint_state = TRACKER_GPS_CMD_SEND;	//xb add 2015-09-20 ָ���ѯGPSǿ���ϴ�
                Tracker_GPS_Send_Position_Data();
            }
            return ;
        }
        else
        {
            sprintf(sms_buf, "ERROR:107");
        }        
    }
    else if((strcmp((char *)received_data.main_str, "DW") == 0)\
            || (strcmp((char *)received_data.main_str, "POSITION") == 0)\
            || (strcmp((char *)received_data.main_str, "123") == 0))    //λ�ò�ѯָ��
    {
    	tracker_gpspoint_state = TRACKER_GPS_CMD_SEND;	//xb add 2015-09-20 ָ���ѯGPSǿ���ϴ�
        Tracker_Query_Get_Address_From_Server();
        return;
    }
    else if(strcmp((char *)received_data.main_str, "URL") == 0)
    {
        if(is_empty_sos_set())
        {
            // SOS����ȫ�ղ����� URL
            LOGD("***URL����Ȩ SOS����ȫ��****");
            SetSendSMS(FALSE, sys_rcv_sms.num , STR_KKSAPP_ERROR_PHONE, NULL);
        }
        else
        {
        	tracker_gpspoint_state = TRACKER_GPS_CMD_SEND;	//xb add 2015-09-20 ָ���ѯGPSǿ���ϴ�
            Tracker_See_Address_URL();
        }
        return;
    }
    else if(strcmp((char *)received_data.main_str, "DWXX") == 0)
    {
        Tracker_Get_LatLon_Information();
    }
    else if(strcmp((char *)received_data.main_str, "EURL") == 0)
    {
        Tracker_EDIT_Address_URL();
    }
    else if(strcmp((char *)received_data.main_str, "SF") == 0)
    {
        Tracker_Set_Static_Filtering_Status();
    }
    else if(strcmp((char *)received_data.main_str, "REPORT") == 0)
    {
        Tracker_Set_Report_Mode();
    }
    else if(strcmp((char *)received_data.main_str, "TIMER") == 0)
    {
        Tracker_Set_Timer_interval();
    }
    else if(strcmp((char *)received_data.main_str, "DISTANCE") == 0)
    {
        Tracker_Set_Distance();
    }
    else if(strcmp((char *) received_data.main_str, "HBT") == 0)
    {
        Tracker_Set_Status_Timer_interval();
    }
    else if(strcmp((char *) received_data.main_str, "EPH") == 0)
    {
        Tracker_Set_GPS_Ephemeris_Time();
    }
    else if(strcmp((char *) received_data.main_str, "ANGLEREP") == 0)
    {
        Tracker_Set_Inflection_Point_Report();
    }
#if defined(__ACC_DETECT__)
    else if(strcmp((char *) received_data.main_str, "ACCREP") == 0)
    {
        Tracker_Set_ACC_Report_Status();
    }
#endif
    else if(strcmp((char *) received_data.main_str, "BATCH") == 0)
    {
        Tracker_Set_Packting_Number();
    }
    else if(strcmp((char *)received_data.main_str, "DELAY") == 0)
    {
        Tracker_GPS_Delay_Active_Time();
    }
    else  if(strcmp((char*)received_data.main_str, "GPSMODE") == 0)
    {
        Tracker_Set_GPS_StartMode();
    }
    else if(strcmp((char *)received_data.main_str, "SPD") == 0)
    {
        Tracker_SendData_AccordingTo_Speed();
    }
#if defined(__GPS_BACKUP__)
    else if(strcmp((char *)received_data.main_str, "BACKUP") == 0)
    {
        Tracker_Get_GPS_Backup_Status();
    }
    else if(strcmp((char *)received_data.main_str, "CLEAR") == 0)
    {
        Tracker_Clear_GPS_Backup_Data();
    }
#endif
#if defined(__PARAM_BACKUP__)
	else if(strcmp((char *)received_data.main_str, "CLRPARAMBK") == 0)
	{
		Tracker_Clear_Param_Backup_Data();
	}
#endif
#if defined(__BACKUP_FILE_TRANSFER__) && defined(__GPS_BACKUP_TOFILE__)//wnq
    else if(strcmp((char *)received_data.main_str, "GETFILE") == 0)
    {
        Tracker_Get_GPS_Backup_File();
    }

#endif/*__BACKUP_FILE_TRANSFER__*/
#if defined(__GPS_OVERSPEED__)
    else if(strcmp((char *)received_data.main_str, "SPEED") == 0)
    {
        Tracker_Set_OverSpeed_Threshold();
    }
#endif
#if defined(__GPS_FENCE__)
	else if(strcmp((char *)received_data.main_str, "SFENCE") == 0)	//��Χ��
	{
		Tracker_Set_Electronic_Fence_Single();
	}
	else if(strcmp((char *)received_data.main_str, "SEEFENCE") == 0)//����Χ��
	{
		Tracker_See_Electronic_Fence_Set_Single();
	}
#ifdef __MULTI_FENCE__
	else if(strcmp((char *)received_data.main_str, "GFENCE") == 0)//�����Χ��
	{
		Tracker_Set_Electronic_Fence_Multi();
		if(Command_State == ONLine_Command_State && received_data.part >= 2)
		{
			if(sms_buf[0] == 'O' || sms_buf[0] == 'o')
			{
				LOGD("--ONline_GFENCE_OK---");
				Tracker_Online_State = TRACKER_ONLINE_GFENCE_SUCCESS;
			}
			else
			{
				LOGD("--ONline_GFENCE_FAIL---");
				Tracker_Online_State = TRACKER_ONLINE_GFENCE_FAIL;
			}
			gprs_send_type = GPRS_ONLINE_RESULT_INFO;
			Tracker_Socket_Send_Current_Data();
		}
	}
	else if(strcmp((char *)received_data.main_str, "GFENCETEST") == 0)//�����Χ������
	{
		Tracker_Electronic_Fence_Multi_Test();
	}
#endif
	else if(strcmp((char *)received_data.main_str, "FENCEALARM") == 0)   //�������·�
    {
        Tracker_Fence_Alarm_Address_SendSMS();
    }
#endif /*__GPS_FENCE__*/
#if defined(__MOVING_ALARM__)
    else if(strcmp((char *)received_data.main_str, "MOVING") == 0)
    {
        Tracker_Set_Moving_Param();
        return ;
    }
#endif
#if defined(__AGPS_EPO_SUPPORT__)
    else if(strcmp((char *)received_data.main_str, "AGPS") == 0)
    {
        Traceker_Set_AGPS_State();
    }
#endif
    else if(strcmp((char *) received_data.main_str, "LATLON") == 0)     //��γ��ת��
    {
        Tracker_Get_LatLon_TurnTo_String();
    }
    else if(strcmp((char *) received_data.main_str, "STATUSTEST") == 0)     //״̬���ظ�����
    {
        Tracker_Set_Status_Reply_Process();
    }
    else if(strcmp((char *)received_data.main_str, "BLINDALM") == 0)	  //ä������
    {
        Tracker_Set_Blindalarm();
    }	
#endif  /*__GPS_ON_MTK__*/
	else  if(strcmp((char*)received_data.main_str, "CENTER") == 0)
	{
		Tracker_Set_Center_PhoneNum();
	}
#if defined(__OIL_ELECTRONIC_CONTROL__)
    else  if(strcmp((char*)received_data.main_str, "MOTOR_LOCK") == 0)
    {
        Tracker_Factory_Motor_Lock();
    }
    else  if(strcmp((char*)received_data.main_str, "MOTOR_OPEN") == 0)
    {
        Tracker_Factory_Motor_Open();
    }
    else if(strcmp((char *)received_data.main_str, "POWERALM") == 0)
    {
        Tracker_Set_CutPower_Status();
    }
    else  if(strcmp((char*)received_data.main_str, "RELAY") == 0)   //����ָ����͵磬�ָ��͵�
    {
        Tracker_Set_OilElectronic();
        return;
    }
    else if(strcmp((char*)received_data.main_str, "DYD") == 0)
    {
        if(Command_State == ONLine_Command_State)
        {
            if(received_data.part == 0 || received_data.part == 1) //ƽ̨�·����Ǵ�����
            {
                Tracker_Set_OilElectronic_Off();
            }
            else
            {
                sprintf(sms_buf, "ERROR:100");
                Tracker_Online_State = TRACKER_ONLINE_RELAY;
                gprs_send_type = GPRS_ONLINE_RESULT_INFO;
                Tracker_Socket_Send_Current_Data();
            }
        }
        return ;

    }
    else if(strcmp((char*)received_data.main_str, "HFYD") == 0)
    {
        if(Command_State == ONLine_Command_State)
        {
            if(received_data.part == 0 || received_data.part == 1)
            {
                Tracker_Set_OilElectronic_On();
            }
            else
            {
                sprintf(sms_buf, "ERROR:100");
                Tracker_Online_State = TRACKER_ONLINE_RELAY;
                gprs_send_type = GPRS_ONLINE_RESULT_INFO;
                Tracker_Socket_Send_Current_Data();
            }
        }
        return ;
    }
#endif/*__OIL_ELECTRONIC_CONTROL__*/
    else if(strcmp((char *)received_data.main_str, "SOCDETACH") == 0)
    {
    #ifndef KJX_TEST
        Tracker_Socket_Set_GPRS_Detached();
	#endif
    }
#if defined(__EXPAND_PORT_SUPPORT__)
    else if(strcmp((char *)received_data.main_str, "AIDIREPORT") == 0)
    {
        Tracker_Set_Analog_Digital_Transport();
    }
    else if((strcmp((char *)received_data.main_str, "DI") == 0) || (strcmp((char *)received_data.main_str, "DIPARAM") == 0))
    {
        Tracker_Set_Digital_Trigger_Mode();
    }
    else if(strcmp((char *)received_data.main_str, "DITIMER") == 0)
    {
        Tracker_Set_Digital_Timer();
    }
    else if(strcmp((char *)received_data.main_str, "DIALM") == 0)
    {
        Tracker_Set_Digital_Alarm_Mode();
    }
    else if(strcmp((char *)received_data.main_str, "DIMEG") == 0)
    {
        Tracker_Set_Digital_Alarm_Content();
    }
    else if(strcmp((char *)received_data.main_str, "AITIMER") == 0)
    {
        Tracker_Set_Analog_Timer();
    }
    else if(strcmp((char *)received_data.main_str, "AIMODE") == 0)
    {
        Tracker_Set_Analog_Transmission_Mode();
    }
    else if((strcmp((char *)received_data.main_str, "AI") == 0) || (strcmp((char *)received_data.main_str, "AIPARAM") == 0))
    {
        Tracker_Set_Analog_Input_Param();
    }
    else if(strcmp((char *)received_data.main_str, "AIALM") == 0)
    {
        Tracker_Set_Analog_Input_Alarm();
    }
    else if(strcmp((char *)received_data.main_str, "AIMEG") == 0)
    {
        Tracker_Set_Analog_Alarm_Content();
    }
    else if(strcmp((char *)received_data.main_str, "DO") == 0)
    {
        Tracker_Set_Expand_Output();
    }
    else if(strcmp((char *)received_data.main_str, "DOMEG") == 0)
    {
        Tracker_Set_Expand_Output_Alarm_Message();
    }
#endif
#if defined(__DETECT_VOICE__)
    else if(strcmp((char *)received_data.main_str, "MIC") == 0)
    {
        Tracker_Mic_Param_Set();	 
    }
    else if(strcmp((char *)received_data.main_str, "MICTEST") == 0)
    {
        Tracker_Mic_Factory_Test();
    }
#endif
#if defined(__KD6113_POWER_ON_ALARM__)
	else if(strcmp((char *)received_data.main_str, "BOOTALM") == 0)
	{
		Tracker_Set_BootOn_Alarm();
	}
#endif/*__KD6113_POWER_ON_ALARM__*/
    else
    {
	#if defined(__KJX_AT_APP__)
        //�����ָ��ͷֻ��ATָ��ظ�
		if((Command_State == AT_Command_State)
	#if defined(__AT_USE_UART1__)
		||(Command_State == UART1_Command_State)
	#endif
		)
        {
            sprintf(sms_buf, "ERROR:107");
        }
        else
	#endif
        {
            return ;
        }
    }
    Send_Command_Message_Replay();
}


/******************************************************************************
 *  Function    -  Tracker_DW_Query_Connect_Abnormal
 *
 *  Purpose     -  DW��ȡ����λ����Ϣ��������������
 *
 *  Description - 1,�����ӣ�GPSδ��λ�������쳣
 *
 * modification history  5����������ʧ��2�β�������
  * ----------------------------------------
 * v1.0  , 2012-06-14, guojie  written
  * ----------------------------------------
 ******************************************************************************/
void Tracker_DW_Query_Connect_Abnormal(void)
{
#ifndef KJX_TEST
    LOGD("Tracker_DW_Query_Connect_Abnormal %d,%d,%d", DWSocConnecttimes, DWQuery, IsMyTimerExist(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER));

    if((tracker_ctrl_data.GPRSAlwaysOn == 1) && (DWQuery == 1 || DWQuery == 2))
    {
        //5���ӳ�ʱ�ظ���Ϣ,���ڴ˴λظ���Ϣ��������ӳ�ʱʱ�ͻظ�
        //if(IsMyTimerExist(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER))
        //{
        //    StopTimer(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER);
        //}
        //Tracker_Query_Address_SocConnect_Fail_SendSMS();
    }
    else if((tracker_ctrl_data.GPRSAlwaysOn == 2) && (DWQuery == 1 || DWQuery == 2))
    {
        if(DWSocConnecttimes < 2)
        {
            DWSocConnecttimes++;
        }

        if(DWSocConnecttimes >= 2)
        {
            if(IsMyTimerExist(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER))
            {
                StopTimer(TRACKER_QUERY_GET_ADDRESS_OVER_TIMER);
                Tracker_Query_Address_SocConnect_Fail_SendSMS();
            }
            DWSocConnecttimes = 0;
            DWQuery = 0;
        }
    }
#endif
}


/******************************************************************************
 *  Function    -  Tracker_SMSCommand_Process
 *
 *  Purpose     -  ����ָ���
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-01, guojie  written
  * ----------------------------------------
 ******************************************************************************/
void Tracker_SMSCommand_Process(void)
{
#ifndef KJX_TEST
    //ƥ�����Ȩ��,��SOS����ɲ�ѯ�����ò���
    if(tracker_permit_level.sospermit == 1)
    {
        //���͵�Ȩ�޽��������ĺ��벻��SOS����
        if((SuperCommandHead == FALSE) && (Delete_SmsPrefix_Confirm_CenterNum() == FALSE) && (!is_empty_sos_set()&&(Delete_SmsPrefix_Confirm_SOSNum() == 0xFF)))
        {
            sprintf(sms_buf, "ERROR:117");                     //����SOS����
            Send_Command_Message_Replay();
            return;
        }
    }

    //ƥ������Ȩ��
    if(((tracker_password.state == 1) && (SuperCommandHead == FALSE) && (Tracker_Check_Authentication() == TRUE))
            || (tracker_password.state == 0) || (SuperCommandHead == TRUE))
    {
        Command_State = SMS_Command_State;
        AT_OR_SMS_Command_Pro();
    }
#endif
}

/*****************************************************************************
 *  Global Functions			ȫ�ֺ���
 *****************************************************************************/


/******************************************************************************
 *  Function    -  Kjx_ATCommand_Process
 *
 *  Purpose     -  ATָ���
 *
 *  Description - ATָ���Ҫ�����ж�
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2014-04-22, guojie  written
  * ----------------------------------------
 ******************************************************************************/
void Kjx_ATCommand_Process(void)
{
    Command_State = AT_Command_State;
    AT_OR_SMS_Command_Pro();
    Command_State = SMS_Command_State;
}

#if defined(__AT_USE_UART1__)
void Tracker_UART1_Command_Process(void)
{
    Command_State = UART1_Command_State;
    AT_OR_SMS_Command_Pro();
    Command_State = SMS_Command_State;
}
#endif
 
#if defined(__STRING_USE_ARRAY__)
/******************************************************************************
 *  Function    -  Tracker_Search_Error_Result
 *
 *  Purpose     -  ������ָ���������ת��Ϊ��Ӧ����˵��
 *
 *  Description -  ������Ļظ���ֱ������
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-06-10, guojie  ����
  * ----------------------------------------
 ******************************************************************************/
BOOL Tracker_Search_Error_Result(char * Message)
{
    char* String_P = NULL;
    BOOL Result = FALSE, find = FALSE;
    U8 index = 0;

    for(index = 0; index < ERRORCODETOTAL; index++)
    {
        if((error_code_table[index].valid) && (strncmp((char *)error_code_table[index].cmd_string, (char *)Message, ERRORCODELENGTH) == 0))
        {
            find = TRUE;
            break;
        }
    }

    memset(&sys_send_sms, 0, sizeof(SYS_SMS_STRUCT));

    if(find)
    {
        memset(&sys_send_sms, 0, sizeof(SYS_SMS_STRUCT));
        if(CurrentLang == 1)
        {
            //����ȡ�ĳ��ȸ�ʵ�ʳ��Ȳ�һ�»�����
            sys_send_sms.len = app_ucs2_strlen((char *)unicode_error_code[index]) * 2;
            memcpy(sys_send_sms.content, &unicode_error_code[index], sys_send_sms.len);

            SetSendSMS(FALSE, sys_rcv_sms.num, NULL, sys_send_sms.content);
        }
        else
        {
            sys_send_sms.len = strlen((char *)ascii_error_code[index]);
            memcpy(sys_send_sms.content, &ascii_error_code[index], sys_send_sms.len);
            SetSendSMS(TRUE, sys_rcv_sms.num, NULL, sys_send_sms.content);
        }
        Result = TRUE;
    }
    else
    {
        Result = FALSE;
    }

    return Result;

}
#else

/******************************************************************************
 *  Function    -  Tracker_Search_Error_Result
 *
 *  Purpose     -  ������ָ���������ת��Ϊ��Ӧ����˵��
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2012-06-10, guojie  ����
  * ----------------------------------------
 ******************************************************************************/
static kal_bool Tracker_Search_Error_Result(char * Message)
{
#ifndef KJX_TEST
    char* String_P = NULL;

    String_P = strstr(Message, "ERROR");
    if(String_P == NULL)
        return FALSE;
    String_P = strstr(Message, "ERROR:100");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR0, NULL);
        return TRUE;
    }
    String_P = strstr(Message, "ERROR:101");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR1, NULL);
        return TRUE;
    }
    String_P = strstr(Message, "ERROR:102");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR2, NULL);
        return TRUE;
    }
    String_P = strstr(Message, "ERROR:103");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR3, NULL);
        return TRUE;
    }
    String_P = strstr(Message, "ERROR:104");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR4, NULL);
        return TRUE;
    }
    String_P = strstr(Message, "ERROR:105");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR5, NULL);
        return TRUE;
    }
    String_P = strstr(Message, "ERROR:106");

    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR6, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:108");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR8, NULL);
        return TRUE;
    }
    String_P = strstr(Message, "ERROR:109");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR9, NULL);
        return TRUE;
    }
    String_P = strstr(Message, "ERROR:110");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR10, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:111");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR11, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:112");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR12, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:113");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR13, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:114");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR14, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:115");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR15, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:116");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR16, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:117");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR17, NULL);
        return TRUE;
    }


    String_P = strstr(Message, "ERROR:118");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR18, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:119");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR19, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:120");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR20, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:121");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR21, NULL);
        return TRUE;
    }

    String_P = strstr(Message, "ERROR:122");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR22, NULL);
        return TRUE;
    }


    String_P = strstr(Message, "ERROR:123");
    if(String_P != NULL)
    {
        SetSendSMS(FALSE, sys_rcv_sms.num, STR_SMS_SET_ERROR23, NULL);
        return TRUE;
    }
    return FALSE;
#endif
}
#endif


/***********************************************************************
 *	�ַ�������õ�
 * in:	szInput������һ����
 *	    iPos������ؼ��ֵ�λ��
 *	    cSplit �Ƿָ���
 * out:   szOutBuf ���������
 *
 * ret: �Ƿ����ָ���ֶ�  ���ⲿ�����жϽ�����
************************************************************************/
BOOL GetStrToken(char *szInput, kal_uint16 iPos,char cSplit,char *szOutBuf) 	
{			
	kal_uint16 i = 0;		
	char *c = szInput;		
	char *p = szOutBuf; 	
    BOOL found = FALSE;
	
	if(szInput == NULL) 	
		return FALSE; 

	while( *c != '\0' ) 	
	{		
		if(i == iPos &&  *c!=cSplit)
		{	
			*p++ = *c;
		}	
		else if(i > iPos)
		{	
			break;
		}	

		if( *c == cSplit)
		{	
			i++;
		}	

		c++;	
	}

    if (i >= iPos) 
    {
	  found = TRUE;   // "0" 1������  "0," 2������
    }

	*p = '\0';

	return found;
}	

/******************************************************************************
 *  Function    -  Send_Command_Message_Replay
 *
 *  Purpose     -  ����ָ������󣬷�����Ӧ�Ķ�����Ϣ���ߴ�����Ϣ
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-10-27, guojie  written
  * ----------------------------------------
 ******************************************************************************/
void Send_Command_Message_Replay(void)
{
    kal_bool Result;
    char *p;
    int i = 0;
    BOOL need_to_server = FALSE;  //��Ҫ�ϴ���������ͬ������
    char head_str[30] = {0};

    need_to_server = FALSE;
    if(strlen(sms_buf) > 3)
    {
        memset(head_str, 0, sizeof(head_str));
        memcpy(head_str, sms_buf, 3); //"OK#"
        make_Capital_Letter(head_str);
        if(0 == strcmp(head_str, "OK#"))
        {
            memset(head_str, 0, sizeof(head_str));
            GetStrToken(sms_buf, 1, '#', head_str);
            for(i = 0; i < sizeof(syn_cmd_head) / MAX_CMD_HEAD_LEN; i++)
            {
                if(0 == strcmp(head_str, syn_cmd_head[i]))
                {
                    need_to_server = TRUE;
                    break;
                }
            }
        }
    }

    if(Command_State == AT_Command_State)
    {
        Command_State = SMS_Command_State;
		
		p = sms_buf;
		while(strlen(p) > AT_FRAME_MAX_LEN)
		{
			rmmi_write_to_uart((kal_uint8*)p, AT_FRAME_MAX_LEN, KAL_TRUE);
			p += AT_FRAME_MAX_LEN;
			i++;
		}
		rmmi_write_to_uart((kal_uint8*)p, strlen(p), KAL_TRUE);

        if(need_to_server)  //��Ҫ�ϴ������� cjt
        {
            LOGD("--ATͬ��--%s", sms_buf);

            Commit_All_Params();  //ȫ���ύ
        }
    }
    else if(Command_State == SMS_Command_State)
    {
    #ifndef KJX_TEST
        //�������--------�ظ�����------------------------------------
        LOGD("���Żظ� is_un=%d ����=%s", is_unicode_replay_msg, sms_buf);

        strcpy((char *)sys_send_sms.num, (char *)sys_rcv_sms.num);

        if(is_unicode_replay_msg)
        {
            LOGD("--unicode���Żظ�");
            is_unicode_replay_msg = KAL_FALSE;
            SetSendSMS(FALSE, sys_rcv_sms.num, 0, sms_buf);
            return;
        }

        LOGD("--ascii���Żظ�");
		
        Result = Tracker_Search_Error_Result(sms_buf);

        if(Result == FALSE)
        {
            char *p = sms_buf;
            U16 all_len;
            U8 repley_num[FAMILY_PHB_NUM_LEN_MIN];
            U16 i;

            if(need_to_server)  //��Ҫ�ϴ������� cjt
            {
                LOGD("--SMSͬ��--%s", sms_buf);
                Commit_All_Params();
            }

            all_len = strlen(p);

            if(all_len < MAX_REPLEY_SMS)
            {
                memset((char*)sys_send_sms.content, 0 , sizeof((char*)sys_send_sms.content));
                strcpy((char*)sys_send_sms.content, (char*)sms_buf);
                SetSendSMS(TRUE, sys_rcv_sms.num, 0, sys_send_sms.content);
                LOGD("all_len < MAX_REPLEY_SMS text=%s" , sys_send_sms.content);
            }
            else  //�������Żظ� �ִη���
            {
                LOGD("all_len > MAX_REPLEY_SMS all_len=%d" , all_len);
                memset(repley_num, 0, FAMILY_PHB_NUM_LEN_MIN);
                memcpy(repley_num, sys_rcv_sms.num, FAMILY_PHB_NUM_LEN_MIN);
                i = 0;
                for(;;)
                {
                    if(strlen(p) > MAX_REPLEY_SMS)
                    {
                        strncpy((char *)sys_send_sms.content, p, MAX_REPLEY_SMS);
                        LOGD("--�ִ�%d :%s,%s", i, repley_num, sys_send_sms.content);
                        SetSendSMS(TRUE, repley_num, 0, sys_send_sms.content);
                        p += MAX_REPLEY_SMS;
                        i++;
                    }
                    else
                    {
                        strcpy((char *)sys_send_sms.content, p);
                        LOGD("--����: %s,%s", sys_send_sms.num, sys_send_sms.content);
                        SetSendSMS(TRUE, repley_num, 0, sys_send_sms.content);
                        break;
                    }
                }
            }
        }
	#endif
    }
    else if(Command_State == ONLine_Command_State)
    {
    #ifndef KJX_TEST
	#ifdef __ONLINE_CMD_NORMAL_REPLY__ // ��AT��������ݻظ�ƽ̨��ѯ  cjt 1016
		if(!is_unicode_replay_msg)
		{
			gprs_send_type = GPRS_ONLINE_ASCII_DATA_REPLY;
		}
		else
		{
			gprs_send_type = GPRS_ONLINE_UNICODE_DATA_REPLY;
			is_unicode_replay_msg = FALSE;  //unicode �ظ���ԭ
		}

        Tracker_Socket_Send_Current_Data();
	#else
		Command_State = SMS_Command_State;
		memset(sms_buf, 0, sizeof(sms_buf));
	#endif
	#endif
    }	
}


#if defined(__KJX_AT_APP__)
/*---------------------------------------------------------------------------
 * FUNCTION			ATCommand_Set_Handler
 *
 * DESCRIPTION
 *
 * PARAMETERS
 *		void
 * RETURNS
 *  		void
 * ----------------------------------------
 * v1.0  , 2011-10-27, guojie  written
  * ----------------------------------------
 *---------------------------------------------------------------------------*/
void ATCommand_Set_Handler(void *msg)
{
    Command_State = AT_Command_State;
    strcpy((char*)(received_data.param0), (char*)(DATA_SET.param0));
    strcpy((char*)(received_data.param1), (char*)(DATA_SET.param1));
    strcpy((char*)(received_data.param2), (char*)(DATA_SET.param2));
    strcpy((char*)(received_data.param3), (char*)(DATA_SET.param3));
    strcpy((char*)(received_data.param4), (char*)(DATA_SET.param4));
    strcpy((char*)(received_data.param5), (char*)(DATA_SET.param5));
    strcpy((char*)(received_data.param6), (char*)(DATA_SET.param6));
    strcpy((char*)(received_data.param7), (char*)(DATA_SET.param7));
    strcpy((char*)(received_data.param8), (char*)(DATA_SET.param8));
    strcpy((char*)(received_data.main_str), (char*)(DATA_SET.main_string));
    received_data.part = DATA_SET.part;
	
    //��MAINSTRING ת�ɴ�д
    make_Capital_Letter(received_data.main_str);

    //��ʼ����ɲ��ܷ�����ָ��
    //GPSδ��ʼ����ɣ��ʹ�͸����ֱ������
    if(EntryTestModeReady == TRUE)
    {
        AT_OR_SMS_Command_Pro();
    }
    else
    {
        memset(sms_buf, 0, sizeof(sms_buf));
        sprintf(sms_buf, "No Ready");
        Send_Command_Message_Replay();
    }

    Command_State = SMS_Command_State;
}
#endif/*__KJX_AT_APP__*/


/******************************************************************************
 *  Function    -  Tracker_SMSComand_Analyse
 *
 *  Purpose     -  ����ָ�����
 *
 *  Description -
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-01, guojie  written
  * ----------------------------------------
 ******************************************************************************/
BOOL Tracker_SMSComand_Analyse(char *data, U16 data_len)
{
#ifndef KJX_TEST
    int i = 0, j = 0;
    U8 comma_sum = 0;
    U8 pos_comma[TRACKER_CMD_SEG_MAX];
    U8 pos_end = 0;
    U8 *data_ptr;
    char* data_dw;
    U8 sig_str[RCV_PARAM_DATA_MAX];
    U8 sig = 0;
    U8  SMS_LEN;
    char contTem[400] = {0};
    char* head_ptr ;
    BOOL  result;

    memcpy(contTem, data, data_len);
    head_ptr  = contTem;

    make_Capital_Letter((char *)head_ptr);//ת���ɴ�д

    data_ptr = (U8 *)(Parse_SMS_Head((char *)head_ptr));//������û��"GT_CM="�ַ�//ADD jwj
    if(data_ptr)
    {
        SMS_LEN = strlen((char*)data_ptr);
    }
    else
    {
        data_ptr = (U8*)head_ptr;
        SMS_LEN = strlen((char*)data_ptr);
    }

    data_ptr = (U8 *)(Parse_SUPER_Head((char *)data_ptr));//xb add 2015-12-03 ������û��"SUPER"�ַ�
    if(data_ptr)
    {
        SMS_LEN = strlen((char*)data_ptr);
    }
    else
    {
        data_ptr = (U8*)head_ptr;
        SMS_LEN = strlen((char*)data_ptr);
    }

    LOGD("SuperCommandHead:%d, data_ptr:%s,SMS_LEN:%d", SuperCommandHead, data_ptr, SMS_LEN);

    //���½�����ָ���ѯ����Ҫ���յĵ绰����
    //����Ҫ����ʱ
    if((Command_State == SMS_Command_State) && (tracker_password.state == 0))
    {
        data_dw = strstr((char *)head_ptr, (char *)"DW");
        //������Ų鳤�Ȳ�Ϊ2���ȡ����λ��
        if(((data_dw != NULL) && (SMS_LEN == 2) && (Is_Fetion_Num() == FALSE))
                || ((data_dw != NULL) && (Is_Fetion_Num() == TRUE)))
        {
            strcpy((char*) received_data.main_str, (char*)"DW");
            received_data.part = 0;
            return TRUE;
        }

        data_dw = strstr((char *)head_ptr, (char *)"123");
        if(((data_dw != NULL) && (SMS_LEN == 3) && (Is_Fetion_Num() == FALSE))
                || ((data_dw != NULL) && (Is_Fetion_Num() == TRUE)))
        {
            strcpy((char*) received_data.main_str, (char*)"123");
            received_data.part = 0;
            return TRUE;
        }

	#if defined(__GPS_FENCE__)
        //WL200#    SEEWL#  ���ֿ�
        if(strncmp((const char *)head_ptr, (const char *)"WL", 2) == 0)
        {
            strcpy((char*) received_data.main_str, (char*)"WL");
            Tracker_smscmd_checkparts(data_ptr + 2, received_data.param0);
            received_data.part = 0;
            return TRUE;
        }
	#endif/*__GPS_FENCE__*/

        data_dw = strstr((char *)head_ptr, (char *)"POSITION");
        if(((data_dw != NULL) && (SMS_LEN == 8) && (Is_Fetion_Num() == FALSE))
                || ((data_dw != NULL) && (Is_Fetion_Num() == TRUE)))
        {
            strcpy((char*) received_data.main_str, (char*)"POSITION");
            received_data.part = 0;
            return TRUE;
        }

        data_dw = strstr((char *)head_ptr, (char *)"LC");
        if(((data_dw != NULL) && (SMS_LEN == 2) && (Is_Fetion_Num() == FALSE))
                || ((data_dw != NULL) && (Is_Fetion_Num() == TRUE)))
        {
            strcpy((char*) received_data.main_str, (char*)"LC");
            received_data.part = 0;
            return TRUE;
        }

        data_dw = strstr((char *)head_ptr, (char *)"JT");
        if(data_dw != NULL && SMS_LEN == 2)
        {
            strcpy((char*) received_data.main_str, (char*)"JT");
            received_data.part = 0;
            return TRUE;
        }

        data_dw = strstr((char *)head_ptr, (char *)"111");
        if(data_dw != NULL && SMS_LEN == 3)
        {
            strcpy((char*) received_data.main_str, (char*)"111");
            received_data.part = 0;
            return TRUE;
        }

        data_dw = strstr((char *)head_ptr, (char *)"000");
        if(data_dw != NULL && SMS_LEN == 3)
        {
            strcpy((char*) received_data.main_str, (char*)"000");
            received_data.part = 0;
            return TRUE;
        }
    }

    for(i = 0; i < SMS_LEN; i++)
    {
        if((*(data_ptr + i)) == '#')
        {
            pos_end = i;
            break;
        }
    }
    LOGD(" %d",  pos_end);

    if(pos_end == 0)
    {
        memset(&received_data, 0, sizeof(received_data));
        return  FALSE;
    }

    memset(pos_comma, 0, sizeof(pos_comma));

    for(i = 0; i < SMS_LEN; i++)
    {
        if((j < TRACKER_CMD_SEG_MAX) && ((*(data_ptr + i)) == ','))
        {
            pos_comma[j] = i;
            j++;
            comma_sum = j;
        }
        else
        {
            if(j >= TRACKER_CMD_SEG_MAX)
                return FALSE;
        }
    }

    memset(&received_data, 0, sizeof(received_data));

    j = comma_sum + 1;

    //������
    if(tracker_password.state == 1 && SuperCommandHead == FALSE)
    {
        if(comma_sum != 0)
        {
            received_data.part = comma_sum - 1;
        }
        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr, sig_str);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[0] + 1), received_data.passwd);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[1] + 1), received_data.param0);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[2] + 1), received_data.param1);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[3] + 1), received_data.param2);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[4] + 1), received_data.param3);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[5] + 1), received_data.param4);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[6] + 1), received_data.param5);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[7] + 1), received_data.param6);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[8] + 1), received_data.param7);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[9] + 1), received_data.param8);
    }
    else  //SuperCommandHead =TRUE  ��������֤
    {
        if(comma_sum != 0)
        {
            received_data.part = comma_sum;
        }

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr, sig_str);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[0] + 1), received_data.param0);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[1] + 1), received_data.param1);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[2] + 1), received_data.param2);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[3] + 1), received_data.param3);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[4] + 1), received_data.param4);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[5] + 1), received_data.param5);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[6] + 1), received_data.param6);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[7] + 1), received_data.param7);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[8] + 1), received_data.param8);

        if(j-- > 0)
            Tracker_smscmd_checkparts(data_ptr + (pos_comma[9] + 1), received_data.param9);
    }
    strcpy((char*) received_data.main_str, (char*)sig_str);

    LOGD(" %s,%d", sig_str, received_data.part);
    return TRUE;
#endif
}


/*---------------------------------------------------------------------------------------
 * FUNCTION			Tracker_Server_Comand_Analyse
 *
 * DESCRIPTION		��������ַָ����
 *
 * PARAMETERS		void *data	��������
 *					U8 data_len	���ų���
 *                                 ����UNICODE���뷶Χ 4E00--9FBF
 * RETURNS			NULL ADDRESS&&���ĵ�ַ��Ϣ&&�绰����#
 *
 *---------------------------------------------------------------------------------------*/
BOOL Tracker_Server_Comand_Analyse(char *data, U16 data_len)
{
    int i = 0, j = 0;
    U8 comma_sum = 0;
    U8 pos_comma[TRACKER_CMD_SEG_MAX];
    int pos_end = 0;
    U8 *data_ptr;
    U8 sig_str[RCV_PARAM_DATA_MAX];
    int  SMS_LEN = 0;
    char head_ptr[1000];

    memset(head_ptr, 0, sizeof(head_ptr));
    memcpy(head_ptr, data, data_len);
    data_ptr = (U8 *)head_ptr;
    SMS_LEN = data_len;

    memset(pos_comma, 0, sizeof(pos_comma));
    LOGD(" %d", SMS_LEN);

    for(i = 0; i < SMS_LEN; i++)
    {
        if((j < TRACKER_CMD_SEG_MAX) && (head_ptr[i] == '&') && (head_ptr[i+1] == '&')) //���������ĵ�ַ��Ϣ��","����
        {
            pos_comma[j] = i;
            i++;
            j++;
            comma_sum = j;
        }
        else
        {

            if(j >= TRACKER_CMD_SEG_MAX)
                return FALSE;
        }
    }

    for(i = 0; i < SMS_LEN; i++)
    {
        if((head_ptr[i] == '#') && (head_ptr[i+1] == '#'))
        {
            pos_end = i;
            break;
        }
    }
    LOGD(" pos_end=%d,sum:%d,%d,%d", pos_end, comma_sum, pos_comma[0], pos_comma[1]);

    if(pos_end == 0)
    {
        memset(&received_data, 0, sizeof(received_data));
        return FALSE;
    }

    memset(&received_data, 0, sizeof(received_data));

    j = comma_sum + 1;

    if(comma_sum != 0)
    {
        received_data.part = comma_sum;
    }

    //�������·���ַ��Ϣ��������֤

    if(j-- > 0)   //��������֤
        Server_command_checkparts(data_ptr, sig_str);

    if(j-- > 0)
        Server_command_checkparts(data_ptr + (pos_comma[0] + 2), received_data.param0);

    if(j-- > 0)
        Server_command_checkparts(data_ptr + (pos_comma[1] + 2), received_data.param1);

    if(j-- > 0)
        Server_command_checkparts(data_ptr + (pos_comma[2] + 2), received_data.param2);

    if(j-- > 0)
        Server_command_checkparts(data_ptr + (pos_comma[3] + 2), received_data.param3);

    if(j-- > 0)
        Server_command_checkparts(data_ptr + (pos_comma[4] + 2), received_data.param4);

    if(j-- > 0)
        Server_command_checkparts(data_ptr + (pos_comma[5] + 2), received_data.param5);

    if(j-- > 0)
        Server_command_checkparts(data_ptr + (pos_comma[6] + 2), received_data.param6);

    if(j-- > 0)
        Server_command_checkparts(data_ptr + (pos_comma[7] + 2), received_data.param7);

    if(j-- > 0)
        Server_command_checkparts(data_ptr + (pos_comma[8] + 2), received_data.param8);

    if(j-- > 0)
        Server_command_checkparts(data_ptr + (pos_comma[9] + 2), received_data.param9);


    strcpy((char*) received_data.main_str, (char*)sig_str);
    make_Capital_Letter(received_data.main_str);

    LOGD(" %s,%d", sig_str, received_data.part);

    return TRUE;
}


/******************************************************************************
 *  Function    -  Tracker_Server_Command_Process
 *
 *  Purpose     -  �������·����ݴ���
 *
 *  Description -  �������·�ָ������룬���·�������ַ��������
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-18, guojie  written
  * ----------------------------------------
 ******************************************************************************/
void Tracker_Server_Command_Process(void)
{
#ifndef KJX_TEST
    //�������ظ���ַû��������֤
    if(strcmp((char *)received_data.main_str, "ADDRESS") == 0)
    {
        Command_State = ONLine_Command_State;
        AT_OR_SMS_Command_Pro();
        Command_State = SMS_Command_State;
    }
    else if(strcmp((char *)received_data.main_str, "ALARMSMS") == 0)
    {
        Command_State = ONLine_Command_State;
        AT_OR_SMS_Command_Pro();
        Command_State = SMS_Command_State;
    }
    //��������ָ��ƥ������Ȩ��
    else if(((tracker_password.state == 1) && (Tracker_Check_Authentication() == TRUE))
            || (tracker_password.state == 0))
    {
        Command_State = ONLine_Command_State;
        AT_OR_SMS_Command_Pro();
        Command_State = SMS_Command_State;
    }
#endif
}


//-----------------------����ȫ�Ƕ���----------------------
void translate_special_char(U8 *sms, U16 byte_len)
{
    int i;
    U8 *p;

    p = (U8 *)sms;

    for(i = 0; i < byte_len / 2; i++)
    {
        if(0x0C == *p && 0xFF == *(p + 1))
        {
            *p = 0x2C;
            *(p + 1) = 0x00;
            //LOGD("---����ת��--");
        }
        p += 2;
    }
}

/******************************************************************************
 *  Function    -  Tracker_SMS_Handle_My_Msg
 *
 *  Purpose     -  �������ݽ�ȡ
 *
 *  Description -  ��������һ��ҪΪӢ�ĲŻ��лظ�����UNICODE����ֱ��ɾ��
 *
 * modification history
  * ----------------------------------------
 * v1.0  , 2011-11-02, guojie  written
  * ----------------------------------------
 ******************************************************************************/
U8 Tracker_SMS_Handle_My_Msg(srv_sms_event_new_sms_struct * event_info)
{
    int i = 0 ;
    U8 cmd_content[30] = {0};
    char *p = NULL;
    U8 *data_ptr;
    S8 sms_content[400];
    U8 sms_length = 0;
    char* String_Instruct = NULL;
    srv_sms_new_msg_struct *msg_info = (srv_sms_new_msg_struct*)event_info->msg_data;
    const S8*  UCS2content = NULL;

    LOGD(" num:%s,dcs:%d,sim:%d,len:%d", msg_info->number, msg_info->dcs, msg_info->sim_id, msg_info->message_len);

    memset(sys_rcv_sms.num, 0, sizeof(sys_rcv_sms.num));
    memset(sys_rcv_sms.content, 0, sizeof(sys_rcv_sms.content));

    p = (char*)msg_info->number;

    strcpy((char *)sys_rcv_sms.num, (char *)p);

    if(msg_info->dcs == SMSAL_DEFAULT_DCS)
    {
        /*����ȡ��Ϣ����̫������event_info->contentȡ134�Ժ�Ϊ00*/
        //sys_rcv_sms.len = msg_info->message_len / 2;
        //mmi_ucs2_n_to_asc((S8*)sys_rcv_sms.content, (S8*)event_info->content, msg_info->message_len);
        UCS2content = srv_sms_get_msg_content(event_info->msg_id);
        if(NULL != UCS2content)
        {
            sys_rcv_sms.len = mmi_ucs2strlen(UCS2content);
        }
        mmi_ucs2_n_to_asc((S8*)sys_rcv_sms.content, (S8*)UCS2content, sys_rcv_sms.len * 2);

        LOGD("default  sms:%d,content:%s", sys_rcv_sms.len, sys_rcv_sms.content);
        //��Щ����ָ����ų��ȴ���30
        memset(sms_content, 0x00, sizeof(sms_content));
        mmi_ucs2_n_to_asc((S8*)sms_content, (S8*)UCS2content, sys_rcv_sms.len * 2);
        make_Capital_Letter((char *)sms_content);//ת���ɴ�д
        data_ptr = (U8 *)(Parse_SMS_Head((char *)sms_content));     //������û��"GT_CM="�ַ�
        /*ȥ������ͷGT_CM=*/
        if(data_ptr)
        {
            memset(sms_content, 0, sizeof(sms_content));
            memcpy(sms_content, sys_rcv_sms.content, sizeof(sys_rcv_sms.content));
            sms_length = strlen((char*)data_ptr);
            memset(sys_rcv_sms.content, 0, sizeof(sys_rcv_sms.content));
            memcpy(sys_rcv_sms.content, &sms_content[sys_rcv_sms.len-sms_length], sms_length);
            sys_rcv_sms.len = sms_length;
		#if defined(__SMS_TRANSMISSION__)
            LOGD("default sms:%d,content:%s,%d", sys_rcv_sms.len, sys_rcv_sms.content, g_is_wait_DTU_msg);
		#else
			LOGD("default sms:%d,content:%s", sys_rcv_sms.len, sys_rcv_sms.content);
		#endif
        }
        else
        {
            sms_length = strlen((char*)sms_content);
            memset(sys_rcv_sms.content, 0, sizeof(sys_rcv_sms.content));
            memcpy(sys_rcv_sms.content, sms_content, sms_length);
            sys_rcv_sms.len = sms_length;
		#if defined(__SMS_TRANSMISSION__)
			LOGD("default sms:%d,content:%s,%d", sys_rcv_sms.len, sys_rcv_sms.content, g_is_wait_DTU_msg);
		#else
    		LOGD("default sms:%d,content:%s", sys_rcv_sms.len, sys_rcv_sms.content);        
		#endif
        }

	#if defined(__SMS_TRANSMISSION__)
        if(Tracker_Message_Need_Upload())
        {
            Tracker_Upload_DTU_Message(UCS2content, sys_rcv_sms.len * 2);
        }
	#endif
        Command_State = SMS_Command_State;
        if(Tracker_SMSComand_Analyse((char*)sys_rcv_sms.content, sys_rcv_sms.len) == TRUE)
        {
            Tracker_SMSCommand_Process();
        }

        mmi_sms_delete_msg(event_info->msg_id, NULL);
        return 1;
    }
    else if(msg_info->dcs == SMSAL_8BIT_DCS)
    {
        mmi_sms_delete_msg(event_info->msg_id, NULL);
        return 1;
    }
    else if(msg_info->dcs == SMSAL_UCS2_DCS)
    {
        /*����ȡ��Ϣ����̫������event_info->contentȡ134�Ժ�Ϊ00*/
        UCS2content = srv_sms_get_msg_content(event_info->msg_id);
        if(NULL != UCS2content)
        {
            sys_rcv_sms.len = mmi_ucs2strlen(UCS2content);
        }

	#if defined(__SMS_TRANSMISSION__)
        if(Tracker_Message_Need_Upload())
        {
            Tracker_Upload_DTU_Message(UCS2content, (sys_rcv_sms.len * 2));

			mmi_sms_delete_msg(event_info->msg_id, NULL);
            return 1;
        }
	#endif/*__SMS_TRANSMISSION__*/
	
		//------------����ȫ�Ƕ���---------------------------
		translate_special_char((U8*)UCS2content, sys_rcv_sms.len * 2);
		//------------�������-------------------------------

        mmi_ucs2_n_to_asc((S8*)sms_content, (S8*)UCS2content, sys_rcv_sms.len * 2);
        LOGD(" UNICODE^  len:%d,content:%s", sys_rcv_sms.len, sys_rcv_sms.content);

        make_Capital_Letter((char *)sms_content);//ת���ɴ�д

        LOGD(" UNICODE^^  len:%d,content:%s,%x,%x", sys_rcv_sms.len, sms_content, sms_content[sys_rcv_sms.len], sms_content[sys_rcv_sms.len+1]);

        sms_content[sys_rcv_sms.len] = 0x00;
        sms_content[sys_rcv_sms.len+1] = 0x00;

        data_ptr = (U8 *)(Parse_SMS_Head((char *)sms_content));     //������û��"GT_CM="�ַ�
        if(data_ptr)
    	{
            sms_length = strlen((char*)data_ptr);
            memset(sys_rcv_sms.content, 0, sizeof(sys_rcv_sms.content));
            memcpy(sys_rcv_sms.content, &sms_content[sys_rcv_sms.len-sms_length], sms_length);
            sys_rcv_sms.len = sms_length;
            LOGD(" UNICODE^^^  sms:%d,content:%s", sys_rcv_sms.len, sys_rcv_sms.content);
    	}
    	else
    	{
            sms_length = strlen((char*)sms_content);
            memset(sys_rcv_sms.content, 0, sizeof(sys_rcv_sms.content));
            memcpy(sys_rcv_sms.content, sms_content, sms_length);
            sys_rcv_sms.len = sms_length;
            LOGD(" ^^UNICODE^^ sms:%d,content:%s", sys_rcv_sms.len, sys_rcv_sms.content);
        }

        Command_State = SMS_Command_State;
        if(Tracker_SMSComand_Analyse((char*)sys_rcv_sms.content, sys_rcv_sms.len) == TRUE)
		{
            Tracker_SMSCommand_Process();
        }

        mmi_sms_delete_msg(event_info->msg_id, NULL);
        return 1;
    }
    else
    {
        mmi_sms_delete_msg(event_info->msg_id, NULL);
        return 1;
    }
}

static char param_str[1024];

#ifndef KJX_TEST
#if !defined(__KD6113__)
static char* Get_Param_GTIMER(void)
{
    sprintf(param_str, "GTIMER=%d", tracker_ctrl_data.gps_dsdw_time);
    return param_str;
}

static char* Get_Param_PWRLIMIT(void)
{
    sprintf(param_str, "PWRLIMIT=%d", tracker_ctrl_data.poweroff_limit);

    return param_str;
}

static char* Get_Param_RING(void)
{
    srv_prof_play_audio_struct play_info;
    U16 index = 0;
    U16 value = 0;

    srv_prof_get_current_profile_value(SRV_PROF_SETTINGS_MT_CALL_TONE, &value);
    index = value - AUD_ID_PROF_RING1 + 1;
    sprintf(param_str, "RING=%d", index);

    return param_str;
}

static char* Get_Param_RINGVOL(void)
{
    srv_prof_play_audio_struct play_info;
    U16 index = 0;
    U8 volume_level = 0;

    srv_prof_get_current_profile_value(SRV_PROF_SETTINGS_RING_VOL_LEVEL, &volume_level);
    if(MDI_AUD_VOL_IS_MUTE_LEVEL(volume_level))
    {
        volume_level = volume_level & 0x0F;
    }
    sprintf(param_str, "RINGVOL=%d", volume_level);

    return param_str;
}

static char* Get_Param_CALLVOL(void)
{
    U8 level;

    level = mmi_vol_get_speech_vol();
    sprintf(param_str, "CALLVOL=%d", level);

    return param_str;
}

static char* Get_Param_CALLMODE(void)
{
    sprintf(param_str, "CALLMODE=%d", 
					tracker_ctrl_data.ring_mode);

    return param_str;
}

static char* Get_Param_SIMALM(void)
{
    sprintf(param_str, "SIMALM=%d,%d", 
					tracker_imsi.isset, 
					tracker_imsi.gprs_sms);

    return param_str;
}

static char* Get_Param_BATALM(void)
{
    sprintf(param_str, "BATALM=%d,%d", 
					tracker_ctrl_data.lowbat_alm, 
					tracker_ctrl_data.lowbat_alm_type);

    return param_str;
}

static char* Get_Param_PWRONALM(void)
{
    sprintf(param_str, "PWRONALM=%d,%d", 
					tracker_ctrl_data.poweron_alm, 
					tracker_ctrl_data.poweron_alm_type);

    return param_str;
}

static char* Get_Param_PWROFFALM(void)
{
    sprintf(param_str, "PWROFFALM=%d,%d", 
					tracker_ctrl_data.poweroff_alm, 
					tracker_ctrl_data.poweroff_alm_type);

    return param_str;
}
#endif


static char* Get_Param_TIMER(void)
{
    sprintf(param_str, "TIMER=%d,%d",
            		tracker_ctrl_data.lbs_time_interval / 1000 / 60,
		            tracker_ctrl_data.gps_time_interval / 1000);

    return param_str;
}

static char* Get_Param_BLINDALM(void)
{
    sprintf(param_str, "BLINDALM=%d,%d,%d,%d", 
					tracker_gpsblindarea_alarm.remindstate, 
					tracker_gpsblindarea_alarm.in_blind_times, 
					tracker_gpsblindarea_alarm.out_blind_times, 
					tracker_gpsblindarea_alarm.commit_type);

    return param_str;
}

#if defined(__GPS_OVERSPEED__)
static char* Get_Param_OverSpeed(void)
{
    sprintf(param_str, "SPEED=%d,%d,%d,%d", 
					tracker_overspeed_alarm.remindstate, 
					tracker_overspeed_alarm.detect_sum_time / 1000, 
					tracker_overspeed_alarm.overspeedvalue, 
					tracker_overspeed_alarm.alarmmode);

    return param_str;
}
#endif

#if defined(__BOSCH_BMA250E__)
static char* Get_Param_SENALM(void)
{
    sprintf(param_str, "SENALM=%d,%d", 
					tracker_sensor_time.state, 
					tracker_sensor_time.alarmmode);

    return param_str;
}
#endif

static char* Get_Param_SOSNum(void)
{
	int i;
	char data[50] = {0};
	
    sprintf(param_str, "SOS=");
	for(i = 0; i < SOS_PHB_NUM_MAX; i++)
	{
		memset(data, 0, sizeof(data));

		sprintf(data, "%s", (S8*)tracker_sos_phb.ph_num[i]);
		strcat(param_str,data);
		strcat(param_str,",");
	}

	return param_str;
}

static char* Get_Param_SOSALM(void)
{
    switch(tracker_sos_type.Alerttype)
    {
    case SOS_NO_ALARM:
        sprintf(param_str, "SOSALM=0,2"); //sos�澯�ر�
        break;
    case SOS_GPRS_ONLY:
        sprintf(param_str, "SOSALM=1,0"); //GPRS
        break;
    case SOS_SMS_ONLY:
        sprintf(param_str, "SOSALM=1,1"); //GPRS+SMS
        break;
    case SOS_SMS_AND_CALL:
        sprintf(param_str, "SOSALM=1,2"); //GPRS+SMS+CALL
        break;
    case SOS_CALL_ONLY:
        sprintf(param_str, "SOSALM=1,3"); //GPRS+CALL
        break;
    default:
        sprintf(param_str, "SOSALM=1,%d", tracker_sos_type.Alerttype); //unknown
        break;
    }
    return param_str;
}

static char* Get_Param_GPRSON(void)
{
    sprintf(param_str, "GPRSON=%d", 
					tracker_ctrl_data.GPRSAlwaysOn);
	
    return param_str;
}

static char* Get_Param_LowBatALM(void)
{
    sprintf(param_str, "BATALM=%d,%d", 
					tracker_low_battery.remindstate,
					tracker_low_battery.alarmmode);
	
    return param_str;
}

#if defined(__KD6113_WORK_MODE__)
static char* Get_Param_WorkMode(void)
{
    sprintf(param_str, "WORKMODE=%d,%d", 
					tracker_ctrl_data.workmode.type, 
					tracker_ctrl_data.workmode.time);
	
    return param_str;
}
#endif
#endif

/*----------------------------------
���� һ�����Ʋ�������������Ϊ��
����ʱ��λ�� GTIMER
LBS/GPS�ϴ������TIMER
���ƿ��ػ� PWRLIMIT
����  RING
�������� RINGVOL
��������ģʽ CALLMODE
��������  SIMALM
��ص͵�����  BATALM
�������� PWRONALM
�ػ����� PWROFFALM
GPSä������ BLINDALM
SOS���� SOSALM
"RINGVOL",
"CALLVOL"
------------------------------------*/
void Commit_All_Params(void)
{
#ifndef KJX_TEST
    LOGD("�ϴ����Ʋ���");
    memset(sms_buf_ex, 0, sizeof(sms_buf_ex));
    sprintf(sms_buf_ex, "CTRLPARAMS:");

#if !defined(__KD6113__)	
    strcat(sms_buf_ex, Get_Param_GTIMER());
    strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_PWRLIMIT());
    strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_RING());
    strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_CALLMODE());
    strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_SIMALM());
    strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_BATALM());
    strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_PWRONALM());
    strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_PWROFFALM());
    strcat(sms_buf_ex, ";");
#endif
	
    strcat(sms_buf_ex, Get_Param_TIMER());
    strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_SOSNum());
    strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_LowBatALM());
    strcat(sms_buf_ex, ";");
#if defined(__GPS_OVERSPEED__)
	strcat(sms_buf_ex, Get_Param_OverSpeed());
	strcat(sms_buf_ex, ";");
#endif
#if defined(__BOSCH_BMA250E__)
	strcat(sms_buf_ex, Get_Param_SENALM());
	strcat(sms_buf_ex, ";");
#endif
	strcat(sms_buf_ex, Get_Param_GPRSON());
	strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_BLINDALM());
    strcat(sms_buf_ex, ";");
    strcat(sms_buf_ex, Get_Param_SOSALM());
#if defined(__KD6113_WORK_MODE__)
	strcat(sms_buf_ex, ";");
	strcat(sms_buf_ex, Get_Param_WorkMode());
#endif

    strcat(sms_buf_ex, "#");
    LOGD("%s", sms_buf_ex);
    gprs_send_type = GPRS_ONLINE_ASCII_DATA_REPLY_EX;
    Tracker_Socket_Send_Current_Data();
#endif
}

#ifndef KJX_TEST
static char* Get_Param_GFENCE(U16 order)
{
    nvram_ef_tracker_electronic_fence_struct *p;
    p = &tracker_electronic_fence;

    memset(param_str, 0, sizeof(param_str));
    if(0 == p->m_state[order])   //Χ���ر�
    {
        sprintf(param_str, "%d,0", order + 1);
    }
    else
    {
        if(0 == p->m_FenceType[order])  //Բ��Χ��
        {
            sprintf(param_str, "%d,%d,%d,%d,%d,%f,%f,%d,%d,%d",
                    order + 1, p->m_state[order], p->m_FenceType[order],
                    p->m_latzone[order], p->m_lonzone[order],
                    p->m_lat[order], p->m_lon[order],
                    p->m_dis[order] / 100,
                    p->m_FenceAlarmType[order],
                    p->m_commit_type[order]);
        }
        else //����Χ��
        {
            sprintf(param_str, "%d,%d,%d,%d,%d,%f,%f,%f,%f,%d,%d",
                    order + 1, p->m_state[order], p->m_FenceType[order],
                    p->m_latzone[order], p->m_lonzone[order],
                    p->m_lat[order], p->m_lon[order],
                    p->m_lat1[order], p->m_lon1[order],
                    p->m_FenceAlarmType[order],
                    p->m_commit_type[order]);
        }
    }
    //LOGD("%s", param_str);
    return param_str;
}

void Commit_All_Gfences(void)
{
    int i;

    LOGD("�ϴ����е���Χ��");
    memset(sms_buf_ex, 0, sizeof(sms_buf_ex));
    sprintf(sms_buf_ex, "ALLGFENCES:");
    for(i = 0; i < MAX_FENCE_NUM; i++)
    {
        strcat(sms_buf_ex, Get_Param_GFENCE(i));
        if(i < MAX_FENCE_NUM - 1)
        {
            strcat(sms_buf_ex, ";");
        }
    }
    strcat(sms_buf_ex, "#");
    LOGD("%s", sms_buf_ex);
    gprs_send_type = GPRS_ONLINE_ASCII_DATA_REPLY_EX;
    Tracker_Socket_Send_Current_Data();
}
#endif
#endif/*__KJX_SMS_APP__*/
