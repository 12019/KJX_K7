#ifndef KJX_DOG_GPS_DATA_H
#define KJX_DOG_GPS_DATA_H

#if defined(__KJX_DOG__)

/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/

#define  __KJX_DOG_GPS_DATA_EXTERN__   /*GPS���ݸ�������*/

typedef enum
{
    DOG_POSITION_NONE,
    DOG_POSITION_NE,
    DOG_POSITION_SE,
    DOG_POSITION_SW,
    DOG_POSITION_NW,
} DOG_POSITION_TYPE;

/*��ǰ��GPS ����*/
typedef struct 
{
     int32   longitude;              /*  ����NTU���� = 116.34528 * 100000 = 11634528��NTU��= -116.34528 * 100000 = -11634528��NTU�� */    
     int32   latitude;                /*  γ�� NTUγ�� = 39.21028 * 100000 = 3921028��NTU��= -39.21028 * 100000 = -3921028��NTU��*/  
	 
     uint32 longitude_gps;      /*  ���� 004388535  DDDMM.MMMM  */    
     uint32 latitude_gps;        /*  γ�� 51459414   DDMM.MMMM     */    
	 
     uint16 altitude;                /*��ȡ�ĺ��θ߶� hpgaodu = 11233;     //1123.3��  */
     uint16 angle;                   /*��ȡ����ʻ�Ƕ�ֵ jiaodu = 3459;          //345.9��*/
	 
     uint16 speed_knot;          /*  speed_knot = 1587;    = 158.7knot /H ����*/    
     uint16 speed_mile;          /*  speed_mile = 1587;     = 158.7mile /H Ӣ�� */   
     uint16 speed_kh;             /*  speed_kh = 1587;       = 158.7KM   /H ���� */   
	 
     S8      data_status;          /*  GPS����A = ���ݿ��ã�V = ���ݲ����á�*/
     U16    position;                /*   NE = 1 ;    SE = 2 ;    SW = 3;    NW = 4 ; */
     U16    lgn_error_value;   /* ��ǰ�ľ�������100 NTUΪ��׼  ����˵ 80��ʾ100NTU  100�׵���ֻ��80M*/    
     U16    direction ;             /* ����0 - 7 */
     U16    satellite_total;      /*��ȡ������ */
	 
     MYTIME  date;                 /*  ���� */
     MYTIME  time;                 /*  ʱ�� */
}kjx_dog_gps_data;

extern void kjx_dog_gps_data_decode(U8 *data,U16 data_len);
extern void kjx_dog_get_data_start(void);
extern void kjx_trace_dog(const char *fmt, ...);
#endif
#endif/*KJX_DOG_GPS_DATA_H*/
