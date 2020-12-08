#ifndef KJX_DOG_DISPLAY_H
#define KJX_DOG_DISPLAY_H

#if defined(__KJX_DOG__)

#ifndef bool
#define bool unsigned char
#endif

typedef enum
{
    DATA_TYPE_NONE,
    DATA_TYPE_SECTION_INTO,/*1:����������*/
    DATA_TYPE_SECTION_LEAVE,/*2:��������յ�*/
    DATA_TYPE_SECTION_SPEED,/*3:�������*/
    DATA_TYPE_FIXED_CAMERA,/*4:�̶���������*/
    DATA_TYPE_OUSIDE_TUNNEL_CAMERA,/*5:������������*/
    DATA_TYPE_THE_TUNNEL_CAMERA,/*6:����ڳ�������*/
    DATA_TYPE_ON_BRIDGE,/*7:�߼��ϲ���*/
    DATA_TYPE_UNDER_BRIDGE,/*8:�߼��²���*/
    DATA_TYPE_RED_LED,/*9:���������*/
    DATA_TYPE_UNDER_BRIDGE_LED,/*10:�߼����º��*/
    DATA_TYPE_SIGNAL_LED,/*11:��ͨ�źŵ�*/
    DATA_TYPE_BRIDGE_CAMERA,/*12:�߼��ϼ��*/
    DATA_TYPE_BUS_LANE,/*13:����ר�õ�*/
    DATA_TYPE_WAY_STREET,/*14:���е�*/
    DATA_TYPE_NO_LEFT,/*15:��ֹ��ת*/
    DATA_TYPE_NO_RIGHT,/*16:��ֹ��ת*/
    DATA_TYPE_MOBILE_CAMERA,/*17:�ƶ�������*/
    DATA_TYPE_RADAR,/*18:�״ﾭ����û·��*/
    DATA_TYPE_NO_CROSSING,/*19:Խ�߽�ֹ*/
    DATA_TYPE_RADAR_SPEED,/*20:�״������*/
    DATA_TYPE_RAILWAY,/*21:��·����*/
    DATA_TYPE_TUNNEL,/*22:���*/
    DATA_TYPE_ACCIDET_LOAD,/*23:������·��*/
    DATA_TYPE_SCHOOL,/*24:ѧУ*/
    DATA_TYPE_STEEP_DOWNHILL,/*25:������*/
    DATA_TYPE_HIGH_SPEED_LOAD,/*26:���ٳ����*/
    DATA_TYPE_TOLL_GATE,/*27:�շ�վ*/
    DATA_TYPE_SERVICE_AREA,/*28:������*/
    DATA_TYPE_FILLING_STATION,/*29:����վ*/
    DATA_TYPE_WINE_TEST,/*30:�Ʋ�·��*/
    DATA_TYPE_CAMERA,/*31:���Ӽ��*/
    DATA_TYPE_MAX
} KJX_DOG_DATA_TYPE;


typedef struct 
{
  bool sec_string;
  char play_string[64];
}kjx_dog_play_string;

#endif
#endif/*KJX_DOG_DISPLAY_H*/
