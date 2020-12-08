/**********************************************************************************
*Filename:     kjx_obd.h
*
*Description:  
*
*Author:        caoweijie
*
*Datetime:    2014/04/21
*
***********************************************************************************/
#if !defined(KJX_OBD_H)
#define KJX_OBD_H

#if defined(__KJX_OBD__)


#define  MAX_OBD_DATA_ID    67

typedef enum
{
    OBD_PARSE_NONE,/**/
    OBD_PARSE_NEXT,/**/
    OBD_PARSE_CLOSE/**/
} KJX_OBD_PARSE;


typedef enum
{
    KJX_OBD_UART_START,/*�������ݴ���*/
    KJX_OBD_UART_SETTING,/*�궨��ϵ*/
    KJX_OBD_UART_CLOSE,/*�ر�OBD*/
    KJX_OBD_UART_SHAKE,/*����Э��*/
    KJX_OBD_UART_MAX
} KJX_OBD_UART_COMMAND;

typedef struct 
{
     uint16    obd_sign;  	   /*��ʼ��־*/  
     uint8      destination;  	   /*Ŀ���ַ*/  
     uint8      source;  	          /*Դ��ַ*/  
     uint16    dataLen;  	          /*������*/  
     uint8      count;  	          /*������*/  
     uint16    command;  	   /*������*/  
     uint8      data[8];  	          /*������*/  
     uint8      checksum;  	   /*��У��*/  
}kjx_obd_uart_data;

typedef struct 
{
     uint8    name_string[18];   /*��������*/  
     uint8    lenght;  	           /*���ݳ���*/  
     float     value;  	           /*����ֵ*/  
     BOOL   status;  	           /*״ֵ̬*/  
     char     unit[16];          /*��λ*/
}kjx_obd_data;


typedef struct 
{
     uint8    command[2];  	   /*������*/  
     uint8    lenght;  	          /*����������*/  
     uint8    data[16];  	          /*������*/  
}kjx_obd_uart_command;

extern int obd_len;
extern kal_uint8 ObdUartBuffer[];
extern void kjx_obd_write_car_infos(S8 * recvbuf, kal_uint16 len);
extern U16 kjx_obd_parse_data(U16 dataLen);
extern void kjx_obd_open_uart(void);
extern void kjx_obd_uart_init(void);
extern void kjx_obd_status_play_tts(void);
extern void kjx_obd_uart_send(U16 command);
extern void kjx_obd_read_obd_start(void);
extern void kjx_obd_open_uart(void);
extern BOOL kjx_obd_is_working(void);
extern BOOL kjx_obd_acc_valid(void);
extern void kjx_obd_exit_uart(void);
extern BOOL kjx_obd_is_working(void);
extern void kjx_obd_alarm_with_value(void);
extern void kjx_obd_send_data_timeout(void);
#endif/*__KJX_OBD__*/
#endif/*KJX_OBD_H*/
