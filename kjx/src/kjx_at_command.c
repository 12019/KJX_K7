/******************************************************************************
* Tracker_AT_Command.c
* 
* Describe:  RDA AT command ����
*        AT 
* 
* modification history
* --------------------
* v1.0   2014-04-21 guojie 
* 
******************************************************************************/
#if defined(__KJX_AT_APP__) 
/****************************************************************************
* Include Files                   		����ͷ�ļ�
*****************************************************************************/
#include "kjx_sms_command.h"
#include "kjx_prin.h"

/*****************************************************************************
 *  Define					�궨��
 *****************************************************************************/
#define MAX_GROUP_NUM 15     /*���ڷ��鹦��*/
#define GROUP_DATA_LEN 50

/*****************************************************************************
* Typedef  Enum
*****************************************************************************/

/*****************************************************************************
 *  Struct					���ݽṹ����
 *****************************************************************************/

/*****************************************************************************
* Local variable				�ֲ�����
*****************************************************************************/
static char data_group[MAX_GROUP_NUM][GROUP_DATA_LEN+1];

/*****************************************************************************
* Local variable				ȫ�ֱ���
*****************************************************************************/
char receive_string[256] = {0};

AT_DATA_STRUCT DATA_SET;

/****************************************************************************
* Global Variable - Extern          ����ȫ�ֱ���
*****************************************************************************/
#if defined(__AT_USE_UART1__)
extern BOOL is_uart1_or_hostuart;
#endif
extern RECEIVED_DATA_STRUCT received_data;

/*****************************************************************************
 *  Local Functions			���غ���
 *****************************************************************************/
static char* Parse_AT_Head(char  *data_ptr)
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
 *  Function    -  Tracker_Custom_Apart_Data
 *
 *  Purpose     - �����ַ������ݷָ��������ݽ��з���
 *
 *  Description -
 *
 * modification history
 ******************************************************************************/
U8 Tracker_Custom_Apart_Data(char apart_char, U8 group_num, char* buf)
{
    U8 start = 0, cur, num = 0;

    if(apart_char == NULL || group_num == 0 || buf == NULL) return 0;
    if(group_num >= MAX_GROUP_NUM) group_num = MAX_GROUP_NUM;

    memset(&data_group, 0x00,MAX_GROUP_NUM*(GROUP_DATA_LEN+1) );  //[MAX_GROUP_NUM][GROUP_DATA_LEN+1]  //sizeof(data_group)
    for(cur = 0; cur < strlen(buf); cur ++)
    {
        if(buf[cur] == apart_char)
        {
            strncpy(data_group[num], &buf[start], cur - start);
            start = cur + 1;
            num ++;
            if(num == group_num) return num;
        }
    }

    if(start < cur && num < group_num)
    {
        strncpy(data_group[num], &buf[start], cur - start);

        /*����������СдҲת��Ϊ��д*/
        make_Capital_Letter((char*)data_group[num]);

        num ++;
    }
    return num;
}

/*****************************************************************************
 *  global Functions		ȫ�ֺ���
 *****************************************************************************/
/******************************************************************************
 *  Function    -  Tracker_Custom_Cmd_Parse
 *
 *  Purpose     -  �Դ����ַ������н���
 *
 *  Description -  ATD10086  -->ATD,10086
 *
 * modification history
 * ----------------------------------------
 * v1.0  , 2014-04-21,  guojie  written
 * ----------------------------------------
 ******************************************************************************/
BOOL Tracker_Custom_Cmd_Parse(char* string)
{
    U8 num;
    U16 length =0;
    char data_temp[GROUP_DATA_LEN+1];

	rmmi_write_to_uart((kal_uint8*)"Tracker_Custom_Cmd_Parse begin", strlen("Tracker_Custom_Cmd_Parse begin"), KAL_TRUE); 

    memset(&received_data, 0x00, sizeof(RECEIVED_DATA_STRUCT));

    num = Tracker_Custom_Apart_Data(',', 12, (char*)string);//���ַ����ֶ�
    received_data.part = num - 1;

    //����ATָ�����#�Ž�����ֱ��ȥ��guojie,2014-04-01
    //SCXSZ#  --> SCXSZ
    length = strlen((char*)data_group[received_data.part]);
    memset(data_temp, 0, sizeof(data_temp));

   	if(data_group[received_data.part][length-1] == '#')
    {
        memcpy(data_temp, data_group[received_data.part], length - 1);
        memset(data_group[received_data.part], 0, sizeof(data_group[received_data.part]));
        strcpy((char*)data_group[received_data.part], data_temp);
    }

    //ATD10086 ---> ATD,10086
    if((received_data.part==0)&&((!strncmp((char*)&data_group[0], "ATD", 3))))
    {
        received_data.part = 1;
        strcpy((char*)(received_data.main_str), (char*)"ATD");
        strcpy((char*)(received_data.param0), (char*)&data_group[3]);
    }
    else
    {
        strcpy((char*)(received_data.main_str), (char*)data_group[0]);
        strcpy((char*)(received_data.param0), data_group[1]);//���ֶ��˵��ַ����洢��p_DATA_SET��
        strcpy((char*)(received_data.param1), data_group[2]);
        strcpy((char*)(received_data.param2), data_group[3]);
        strcpy((char*)(received_data.param3), data_group[4]);
        strcpy((char*)(received_data.param4), data_group[5]);
        strcpy((char*)(received_data.param5), data_group[6]);
        strcpy((char*)(received_data.param6), data_group[7]);
        strcpy((char*)(received_data.param7), data_group[8]);
        strcpy((char*)(received_data.param8), data_group[9]);
        strcpy((char*)(received_data.param9), data_group[10]);
        strcpy((char*)(received_data.param10), data_group[11]);
    }

#if defined(__AT_USE_UART1__)
    if(is_uart1_or_hostuart)
		Tracker_UART1_Command_Process();
    else
#endif
    Kjx_ATCommand_Process();

    return TRUE;
}

    
#endif
