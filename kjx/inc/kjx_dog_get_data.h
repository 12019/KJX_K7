#ifndef KJX_DOG_GET_DATA_H
#define  KJX_DOG_GET_DATA_H

#ifndef ABS
#define ABS(x) ((x) > 0 ? (x) : -(x))
#endif

#ifndef PI
//#define PI 3.1415926535897932384626433832795f
#define   PI     3.1415926535898
#endif

/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/

#define  MAX_DATA   50  /*����ɨ��BUFER  ���洢�ĵ���*/

#define MAX_DISTANCE   8000  /*����ɨ��������룻��λm*/

#define MAX_READ_DATA   1024*30  /*����ɨ��BUFER  ��С*/
 
#define  USER_ADDTP   0x0D      /*�Խ������*/ 


#define  DATABASE_SIGN_ONE_POINT    'X'     /*��ʾ������Ч���*/
#define  DATABASE_SIGN_TWO_POINT   'W'   /*��ʾ������Ч���*/ 


#define Is_Invalid   0
#define Is_Ready     1
#define Is_Into        2

#define  radar_shield    0xFF        /*�״����������*/

#define  POSITION_ANY   4760   /*  ��ʾ���ⷽ��*/

#define  DOG_LEAVE  2   /*�뿪*/    
#define  DOG_NEAR   0   /*����*/

#define  UserData   1      
#define  Database   2    

#define MIN_SPEED  10/*��С�����ٶȣ���λKm*/


typedef struct 
{
     uint8    position ;  	      /* ����(NE:1 ;  SE :2 ; SW:3 ; NW:4 )*/
	 
     int32    longitude_start ; /*�𱨵㾭��*/        
     int32    latitude_start ;    /*�𱨵�γ��*/        
	 
     int32    longitude ;          /*�����㾭��*/
     int32    latitude ;             /*������γ��*/
	 
     uint8    speed ;               /*���Ե��ٶ�*/
     uint8    sound_status ;   /*���Ե�������ʾ���*/
	 
     uint16  position_start ;  /*�𱨵㷽��*/
	 
     uint8    data_type ;        /*���Ե����ͣ� Database �ǹ̶�����    UserData���û��Լ��ӵ����� ��*/
     uint32  data_num;         /*��¼��ǰ�����FLASH���Ǹ�λ�ã�������*/
	 
     uint16  line_position ;   /*��ʼ��ͽ��������ߵķ���*/
	 
     uint32  end_distance ;   /*���������ľ���*/
     uint32  start_distance ; /*�ϴ��ж��뿪�ĳ�����Ե�ľ���*/
	 
     uint8    current_status ;/*0��ʾ�뿪��־ 1��ʾ������־*/
     uint16  angle ;               /*�������������ߵķ���*/
}kjx_dog_use_data;



typedef struct 
{
     BOOL   current_data_is_alert;      /*���Ե��Ƿ�ʼ����*/
     BOOL   current_alert_is_updata ; /*���Ե�����˱�������*/
	 
     uint16  end_distance ;                  /*���뱨����ľ���*/
     uint8    speed ;                              /*���Ե��ٶ�*/ 
     uint8    sound_status;                  /*���Ե�������ʾ���*/
     uint8    data_type ;                       /*���Ե����ͣ� Database �ǹ̶�����    UserData���û��Լ��ӵ����� ��*/
     uint32  data_num;                        /*��¼��ǰ�����FLASH���Ǹ�λ�ã�������*/
}kjx_dog_alert;


typedef struct 
{
     U16  nYear ;         /*���ݿ����ڰ汾*/         
     U16  nMonth ;      /*���ݿ����ڰ汾*/      
     U16  nDay ;          /*���ݿ����ڰ汾*/      
       
     U16  speed_radar_quiet;   /*�״��Զ������趨0 - 60 ����*/
     U16  speed_limit_alert;     /*���پ����ٶ��趨0 - 150 ����*/
     U16  speed_error_value;   /*�ٶ����΢���趨-10 - +10  (0-20��ʾ)����*/
     U16  sound_value;             /*��������0 - 8 */
     U16  driving_mode;           /* ��ʻģʽ�л��趨0-3(0-��ȫ��ʻ����ģʽ1-����ϵͳ����ģʽ2-��ȫ��ʻģʽ3-����ϵͳģʽ)*/
     U16  radar_level;               /*�״����ȼ��趨0-2 (0 �ر�\1 ��\2��)*/
     U16  sound_auto_set;       /*�����Զ��趨1 ����0 �ر�*/
     U16  led_level;                  /*�趨 LED  ���� �ȼ�*/
}kjx_dog_database_struct;        


extern uint32 kjx_dog_get_angle_with_two_point(int32 lng1,int32 lat1,int32 lng2,int32 lat2);
extern void kjx_dog_get_distance_with_car_to_alert_point(kjx_dog_use_data *dog_use_data);
#endif
