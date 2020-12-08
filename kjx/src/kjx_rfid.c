/**********************************************************************************
*Filename:     kjx_rfid.c
*
*Description:  
*
*Author:        caoweijie
*
*Datetime:    2015/09/02
*
***********************************************************************************/
#if defined(__KJX_FUN__)

/****************************************************************************
* Include Files                   		����ͷ�ļ�
*****************************************************************************/
#include "kjx_include.h"
#include "Kjx_prin.h"
#include "gpiosrvgprot.h"
#include "SoundRecSrvGProt.h"
#include "ProfilesSrv.h"
#ifdef __KJX_AGAINST_THEFT__
#include "mmi_rp_srv_prof_def.h"
#endif
/*****************************************************************************
 *  Define					�궨��
 *****************************************************************************/
#define MIN_FREE_SIZE   1024*20	//20K
#define MAX_TRY_GET_DURATION		3
#if defined(__KJX_RESET_USED_COUNT__)	
#define RFID_NUM_MAX	20
#define RFID_NUM_CAUSE_RUC	3
#endif

/*****************************************************************************
*Enum					ö�����Ͷ���
*****************************************************************************/

/*****************************************************************************
 *Struct					���ݽṹ����
 *****************************************************************************/

/*****************************************************************************
*Local variable				�ֲ�����
*****************************************************************************/
#if defined(__KJX_FUN_SNDREC__)
static U16 sndrecName[64] = {0};
#endif

#ifdef __KJX_AGAINST_THEFT_TO_PILE__
static U8 against_sms_count = 0;
#endif

#if defined(__KJX_RESET_USED_COUNT__)	
static U8 rfid_count = 0;//��һ��ʹ�ÿ�ʼ�ۻ��յ�����ͨ��Դ�ĸ���
static U32 rfid_num[RFID_NUM_MAX] = {0};//��һ��ʹ�ÿ�ʼ�ۻ��յ�����ͨ��Դ�ı���
#endif

#if defined(__KJX_RFID_SEQUENTIAL_TRIGGER__)
static U32 MAX_RFID_SEQUENTIAL_PLAYED = 0;	//��ʱ��¼����󲥷ž������,������·�����ļ������ã��������·�ĸ���
#endif

/****************************************************************************
*Global Variable - Extern          ȫ�ֱ���
*****************************************************************************/
BOOL kjx_audio_is_playing = FALSE;
BOOL kjx_tts_play_is_stop = FALSE;
BOOL g_rfid_low_bat = FALSE;
BOOL hadRead = FALSE;
#if defined(__KJX_RESET_USED_COUNT__)
BOOL g_rfid_has_playing = FALSE;
#endif
#if defined(__KJX_AGAINST_THEFT__)
kal_bool g_rfid_against_theft = KAL_FALSE;
#endif
S32 last_id = -1;
S32 g_rfid_played_id = -1;

U8 kjx_audio_status = 0xff;//0: ֹͣ,1: ����,2:������ͣ,3:���ŵ�ʱ��ǿ���ж�,255:δ�ѵ�RFID����δ���Ź�
U8 kjx_get_duration = 0;
U16 TTsPlayRepeat = 0;
U32 kjx_rfid_id = 0; //huzheng
U32 kjx_duration_time = 0;
U32 kjx_audio_time = 0;
U32 kjx_play_time = 0;
U32 myID = 0;

#if defined(BLOCK_WITH_RFID)
S8* fileString = NULL;
#endif

S8 TtsPlayString[1024] = {0};
kjxRfidPlayInfo g_kjxRfidPlayInfo = {0};
#ifdef __KJX_TOUR_NAME_STORE_CARD__
kjxTourNameInfo g_kjxTourNameInfo = {0};
#endif
#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
KjxRfidSequenInfo g_kjxRfidSequenInfo = {0};
kjxLineInfo g_kjxPlayedInfo = {0};
#endif
#if defined(__KJX_RESET_USED_COUNT__)
kjxPlayRecInfo g_kjxTourRecInfo = {0};
kjxPlayRecInfo g_kjxTourCfgInfo = {0};
#endif

/****************************************************************************
*Global Variable - Extern          ����ȫ�ֱ���
*****************************************************************************/
#if defined(__KJX_POSITION_TRIGGER_PLAY__)||defined(__KJX_SERVER_CMD_PLAY__)
extern U8 g_play_cause; //0:RFID�������� 1:λ�ô�������
#endif
#if defined(__KJX_SERVER_CMD_PLAY__)
extern U8 g_server_play_result;	//0:��ʼֵ 1:���óɹ� 2:��Ÿ�ʽ���� 3:�����Ƶδ�ҵ�
#endif

extern U32 g_kjx_rfid_id;
#ifdef __BLE_MODULE_SUPPORT__
extern U32 g_kjx_ble_id;
#endif

extern BOOL socketConnet;

extern BOOL g_rfid_test_timer;

#if defined(__KJX_AGAINST_THEFT__)
extern U8 g_str_rfid_against[10];
#endif

#if defined(__KJX_OLED_64_48_UI__)
extern S8 kjxTourInfor[512];
extern UI_string_type kjx_scrolling_show[512];
#endif/*__KJX_OLED_64_48_UI__*/
extern srv_prof_cntx_struct g_srv_prof;

extern U32 g_kjx_current_dj_or_rfid_mode;

/*****************************************************************************
*Global Functions	- Extern		�����ⲿ����
*****************************************************************************/
#if defined(__KJX_OLED_64_48_UI__)
extern void mmi_show_scrolling_infor(void);
extern void mmi_redraw_idlescreen(void);
#endif/*__KJX_OLED_64_48_UI__*/
extern U8 kjx_get_earphone_plugged(void);
#if defined(__KJX_TOURIST_MAP_SUPPORT__)
extern void kjx_show_tour_image(void);
extern void kjx_exit_tour_image(void);
#endif

/*****************************************************************************
 *Local Functions			���غ���
*****************************************************************************/
void kjx_set_with_play_tts(void);

static void Npr_Ttsplayer_play_cb_hdlr(void *info);

/*#############################################################*/
/*RFID��ػ�ȡ�����ļ�*/
/*#############################################################*/
BOOL kjx_rfid_playinfo_add(U32 timer, U8 flag, U8* rfid_id, U8* filestring)
{
	U32 i=1;
	KJXRFIDINFO *pnew;
	static KJXRFIDINFO *head = NULL;

	if(g_kjxRfidPlayInfo.rfidinfo == NULL)
	{
		g_kjxRfidPlayInfo.maxID = 0;
		g_kjxRfidPlayInfo.rfidinfo = NULL;

		media_get_ext_buffer(MOD_MMI, (void **)&head, sizeof(KJXRFIDINFO));
		if (head == NULL) 
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ��001���޷����!");
		#endif
		#endif
		
			return FALSE;
		}

		memset(head->rfid_id, 0x00, sizeof(head->rfid_id));
		memset(head->file_name, 0x00, sizeof(head->file_name));
		head->next = NULL;

		memcpy(head->rfid_id, rfid_id, strlen(rfid_id));
		memcpy(head->file_name, filestring, strlen(filestring));
		head->durtime = timer;
		head->played = flag;
		
		g_kjxRfidPlayInfo.rfidinfo = head;
		g_kjxRfidPlayInfo.maxID = 1;

	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("��ӳɹ�! num:%d", g_kjxRfidPlayInfo.maxID);
	#endif
	#endif
		
		return TRUE;
	}
	else
	{
		if(head == NULL)
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("����");
		#endif
		#endif
		
			head = g_kjxRfidPlayInfo.rfidinfo;
			while(1)
			{
				if(head->next == NULL)
					break;
				else
					head = head->next;
			}
		}
		
		media_get_ext_buffer(MOD_MMI, (void **)&pnew, sizeof(KJXRFIDINFO));
		if (pnew == NULL) 
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ��002���޷����!");
		#endif
		#endif
		
			return FALSE;
		}
		else
		{
			memset(pnew->rfid_id, 0x00, sizeof(pnew->rfid_id));
			memset(pnew->file_name, 0x00, sizeof(pnew->file_name));
			pnew->next = NULL;

			strcpy(pnew->rfid_id, rfid_id);
			strcpy(pnew->file_name, filestring);
			pnew->durtime = timer;
			pnew->played = flag;
			
			head->next = pnew;
			head = pnew;//xb add 2017-05-08 ��¼������β

			g_kjxRfidPlayInfo.maxID++;

		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("��ӳɹ�! sum:%d", g_kjxRfidPlayInfo.maxID);
		#endif
		#endif

			return TRUE;
		}
	}
}

KJXRFIDINFO *kjx_rfid_playinfo_find(U32 rfid_id)
{
	U32 i=1;
	BOOL ret;
	KJXRFIDINFO *head,*tail,*pnew;

	if(g_kjxRfidPlayInfo.rfidinfo == NULL)
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("����û�д������޷�����!");
	#endif
	#endif

		return NULL;
	}

	head = g_kjxRfidPlayInfo.rfidinfo;
	while(head != NULL)
	{
		if(atoi(head->rfid_id) == rfid_id)
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("���ҳɹ�! %d", i);
		#endif
		#endif
			return head;
		}
		else
		{
			i++;
			head = head->next;
		}
	}

#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("�����޽��!");
#endif
#endif	
	return NULL;
}

void kjx_rfid_playinfo_update(U32 index, U32 time, U8 flag, U8* rfid_id, U8* filestring)
{
	U32 i=1;
	BOOL ret;
	KJXRFIDINFO *head;

	if(g_kjxRfidPlayInfo.rfidinfo == NULL)
	{
		g_kjxRfidPlayInfo.maxID = 0;
		g_kjxRfidPlayInfo.rfidinfo = NULL;

		media_get_ext_buffer(MOD_MMI, (void **)&head, sizeof(KJXRFIDINFO));
		if (head == NULL) 
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ�ܣ��޷�����!");
		#endif
		#endif
		
			return;
		}

		memset(head->rfid_id, 0x00, sizeof(head->rfid_id));
		memset(head->file_name, 0x00, sizeof(head->file_name));
		head->durtime = 0;
		head->played = 0;
		head->next = NULL;
		g_kjxRfidPlayInfo.rfidinfo = head;
	}

	head = g_kjxRfidPlayInfo.rfidinfo;
	if(index == 1)
	{
		head->durtime = time;
		head->played = flag;
		strcpy(head->rfid_id, rfid_id);
		strcpy(head->file_name, filestring);
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("���³ɹ�1!");
	#endif
	#endif

		if(g_kjxRfidPlayInfo.maxID == 0)
			g_kjxRfidPlayInfo.maxID = 1;
		
		return;
	}
	else if(index > 1)
	{
		while(head != NULL)
		{
			if(i == index)
			{
				head->durtime = time;
				strcpy(head->rfid_id, rfid_id);
				strcpy(head->file_name, filestring);

			#ifdef RFID_DEBUG	
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("���³ɹ�2!");
			#endif
			#endif		
				return;
			}
			else
			{
				i++;
				head = head->next;
			}
		}
	}

#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("����ʧ��!");
#endif
#endif		
}

void kjx_rfid_playinfo_delete(U32 index)
{
	U32 i=1;
	BOOL ret;
	KJXRFIDINFO *head;

	if(g_kjxRfidPlayInfo.rfidinfo == NULL)
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("����δ�������޷�ɾ��!");
	#endif
	#endif
		return;
	}

	head = g_kjxRfidPlayInfo.rfidinfo;
	if(index == 1)
	{
		media_free_ext_buffer(MOD_MMI, (void**)&head);
		
		if(g_kjxRfidPlayInfo.maxID > 0)
			g_kjxRfidPlayInfo.maxID--;
		g_kjxRfidPlayInfo.rfidinfo = head->next;

	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("ɾ���ɹ�1!");
	#endif
	#endif

		return;
	}
	else if(index > 1)
	{
		while(head != NULL)
		{
			if(i == index)
			{
				if(g_kjxRfidPlayInfo.maxID > 0)
					g_kjxRfidPlayInfo.maxID--;

				if(head->next != NULL)
				{
					g_kjxRfidPlayInfo.rfidinfo = head->next;
					media_free_ext_buffer(MOD_MMI, (void**)&head);
				}

			#ifdef RFID_DEBUG	
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("ɾ���ɹ�2!");
			#endif
			#endif		
				return;
			}
			else
			{
				i++;
				head = head->next;
			}
		}
	}

#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("ɾ��ʧ��!");
#endif
#endif	
}

void kjx_rfid_playinfo_delete_all(void)
{
	BOOL ret;
	KJXRFIDINFO *head, *tail;

	if(g_kjxRfidPlayInfo.rfidinfo != NULL)
	{
		head = g_kjxRfidPlayInfo.rfidinfo;
		while(head != NULL)
		{
			tail = head->next;
			media_free_ext_buffer(MOD_MMI, (void**)&head);
			head = tail;
		}

		g_kjxRfidPlayInfo.maxID = 0;
		g_kjxRfidPlayInfo.rfidinfo = NULL;

	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("ɾ���ɹ�!");
	#endif
	#endif			
	}
	else
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("������δ����������ɾ��!");
	#endif
	#endif		
	}
}

BOOL kjx_rfid_nameinfo_add(U8* rfid_id, U8* namestring)
{
	U32 i=1;
	KJXNAMEINFO *pnew;
	static KJXNAMEINFO *head = NULL;
	
	if(g_kjxTourNameInfo.nameinfo == NULL)
	{
		g_kjxTourNameInfo.maxID = 0;
		g_kjxTourNameInfo.nameinfo = NULL;
		
		media_get_ext_buffer(MOD_MMI, (void **)&head, sizeof(KJXNAMEINFO));
		if (head == NULL) 
		{
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ�� 001���޷����!");
		#endif
		#endif
				
			return FALSE;
		}

		memset(head->rfid_id, 0x00, sizeof(head->rfid_id));
		memset(head->name, 0x00, sizeof(head->name));
		head->next = NULL;
		
		memcpy(head->rfid_id, rfid_id, strlen(rfid_id));
		memcpy(head->name, namestring, strlen(namestring));

		g_kjxTourNameInfo.nameinfo = head;
		g_kjxTourNameInfo.maxID = 1;
		
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("��ӳɹ�! num:%d", g_kjxTourNameInfo.maxID);
	#endif
	#endif
				
		return TRUE;
	}
	else
	{
		if(head == NULL)
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("����");
		#endif
		#endif
			head = g_kjxTourNameInfo.nameinfo;
			while(1)
			{
				if(head->next == NULL)
					break;
				else
					head = head->next;
			}
		}

		media_get_ext_buffer(MOD_MMI, (void **)&pnew, sizeof(KJXNAMEINFO));
		if (pnew == NULL) 
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ��002���޷����!");
		#endif
		#endif
		
			return FALSE;
		}
		else
		{
			memset(pnew->rfid_id, 0x00, sizeof(pnew->rfid_id));
			memset(pnew->name, 0x00, sizeof(pnew->name));
			pnew->next = NULL;
			
			strcpy(pnew->rfid_id, rfid_id);
			strcpy(pnew->name, namestring);
			
			head->next = pnew;
			head = pnew;//xb add 2017-05-08 ��¼������β

			g_kjxTourNameInfo.maxID++;

		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("��ӳɹ�! sum:%d", g_kjxTourNameInfo.maxID);
		#endif
		#endif	

			return TRUE;
		}
	}
}

KJXNAMEINFO *kjx_rfid_nameinfo_find(U32 rfid_id)
{
	U32 i=1;
	BOOL ret;
	KJXNAMEINFO *head,*tail,*pnew;

	if(g_kjxTourNameInfo.nameinfo == NULL)
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("����û�д������޷�����!");
	#endif
	#endif

		return NULL;
	}

	head = g_kjxTourNameInfo.nameinfo;
	while(head != NULL)
	{
		if(atoi(head->rfid_id) == rfid_id)
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("���ҳɹ�! %d", i);
		#endif
		#endif
			return head;
		}
		else
		{
			i++;
			head = head->next;
		}
	}

#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("�����޽��!");
#endif
#endif	
	return NULL;

}

void kjx_rfid_nameinfo_update(U32 index, U8* rfid_id, U8* namestring)
{
	U32 i=1;
	BOOL ret;
	KJXNAMEINFO *head;

	if(g_kjxTourNameInfo.nameinfo == NULL)
	{
		g_kjxTourNameInfo.maxID = 0;
		g_kjxTourNameInfo.nameinfo = NULL;
		
		media_get_ext_buffer(MOD_MMI, (void **)&head, sizeof(KJXNAMEINFO));
		if (head == NULL) 
		{
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ�ܣ��޷�����!");
		#endif
		#endif
				
			return;
		}

		memset(head->rfid_id, 0x00, sizeof(head->rfid_id));
		memset(head->name, 0x00, sizeof(head->name));
		head->next = NULL;
		g_kjxTourNameInfo.nameinfo = head;
	}

	head = g_kjxTourNameInfo.nameinfo;
	if(index == 1)
	{
		strcpy(head->rfid_id, rfid_id);
		strcpy(head->name, namestring);
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("���³ɹ�1!");
	#endif
	#endif

		if(g_kjxTourNameInfo.maxID == 0)
			g_kjxTourNameInfo.maxID = 1;
		
		return;
	}
	else if(index > 1)
	{
		while(head != NULL)
		{
			if(i == index)
			{
				strcpy(head->rfid_id, rfid_id);
				strcpy(head->name, namestring);

			#ifdef RFID_DEBUG	
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("���³ɹ�2!");
			#endif
			#endif		
				return;
			}
			else
			{
				i++;
				head = head->next;
			}
		}
	}

#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("����ʧ��!");
#endif
#endif	
}

void kjx_rfid_nameinfo_delete(U32 index)
{
	U32 i=1;
	BOOL ret;
	KJXNAMEINFO *head;

	head = g_kjxTourNameInfo.nameinfo;
	if(head == NULL)
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("����δ�������޷�ɾ��!");
	#endif
	#endif
		return;
	}

	if(index == 1)
	{
		media_free_ext_buffer(MOD_MMI, (void**)&head);
		
		if(g_kjxTourNameInfo.maxID > 0)
			g_kjxTourNameInfo.maxID--;
		g_kjxTourNameInfo.nameinfo = head->next;

	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("ɾ���ɹ�1!");
	#endif
	#endif

		return;
	}
	else if(index > 1)
	{
		while(head != NULL)
		{
			if(i == index)
			{
				media_free_ext_buffer(MOD_MMI, (void**)&head);

				if(g_kjxTourNameInfo.maxID > 0)
					g_kjxTourNameInfo.maxID--;
				g_kjxTourNameInfo.nameinfo = head->next;
	
			#ifdef RFID_DEBUG	
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("ɾ���ɹ�2!");
			#endif
			#endif		
				return;
			}
			else
			{
				i++;
				head = head->next;
			}
		}
	}

#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("ɾ��ʧ��!");
#endif
#endif	
}

void kjx_rfid_nameinfo_delete_all(void)
{
	BOOL ret;
	KJXNAMEINFO *head, *tail;

	head = g_kjxTourNameInfo.nameinfo;
	if(head != NULL)
	{
		while(head != NULL)
		{
			tail = head->next;
			media_free_ext_buffer(MOD_MMI, (void**)&head);
			head = tail;
		}

		g_kjxTourNameInfo.maxID = 0;
		g_kjxTourNameInfo.nameinfo = NULL;

	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("ɾ���ɹ�!");
	#endif
	#endif			
	}
	else
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("������δ����������ɾ��!");
	#endif
	#endif		
	}
}

#if defined(__KJX_FUN_SNDREC__)
kal_int32 kjx_file_get_free_size(U16* drive_name)
{
	FS_DiskInfo disk_info;
	FS_GetDiskInfo((U16*)drive_name, &disk_info, FS_DI_FREE_SPACE);
	return disk_info.BytesPerSector * disk_info.SectorsPerCluster * disk_info.FreeClusters;
}


U32 kjx_check_free_size(void)
{
	WCHAR path[255];
	U32 free_size= 0;
	kal_wsprintf((WCHAR*) path, "%c", SRV_FMGR_PUBLIC_DRV);
	free_size = kjx_file_get_free_size(path);
	return free_size;
}


kal_int32 kjx_file_get_size(FS_HANDLE fh,kal_uint32* file_size)
{
	kal_int32 ret ;
	ret = FS_GetFileSize((FS_HANDLE)fh,file_size);
	return (ret == FS_NO_ERROR) ? TRUE : -1L;
}

BOOL kjx_file_is_path_exist(const U16* path)
{
	return (FS_GetAttributes(path) < 0) ? FALSE : TRUE;
}

void kjx_sndrec_fs_check_file(U16 *file)
{
    FS_HANDLE handle;

    handle = FS_Open(file, FS_READ_ONLY);
    if (handle >= FS_NO_ERROR)
    {
       FS_Close(handle);
       FS_Delete((const WCHAR*)file);            
    }
}

void kjx_sndrec_get_new_file(void)
{
	memset(sndrecName,0,sizeof(sndrecName));
	kal_wsprintf((WCHAR*) sndrecName, "%c%w", SRV_FMGR_PUBLIC_DRV, L":\\kjx_sndrec.amr");

	if (kjx_file_is_path_exist(sndrecName))
	{
		kjx_sndrec_fs_check_file(sndrecName);
	}    
}

BOOL kjx_sndrec_stop_record(void)
{
	mdi_audio_stop_record();
}

BOOL kjx_sndrec_new_record(void)
{
	BOOL res;

	if(kjx_check_free_size()<MIN_FREE_SIZE)
	{
		return;
	}

	kjx_sndrec_get_new_file();

	res = mmi_sndrec_send_record_req(
	        sndrecName,
	        (U8)MEDIA_FORMAT_NONE,
	        SRV_SOUNDREC_QUALITY_NORMAL);

	return res;
}
#endif

#if defined(__KJX_POSITION_TRIGGER_PLAY__)
/*****************************************************************************
* FUNCTION
*  	kjx_handle_send_position_trigger_data
* DESCRIPTION
*   ���ռ�����λ�ò������ݷ��͸�ƽ̨���Ա�ͳ��
* PARAMETERS
*
* RETURNS
*	none
*****************************************************************************/
void kjx_handle_send_position_trigger_data(void)
{
#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

	if(socketConnet && (kjx_rfid_id > 0))
	{
		kjx_socket_send_data_with_type(SERVER_TYPE_72);
	}
}
#endif

#if defined(BLOCK_WITH_RFID)
/*****************************************************************************
* FUNCTION
*  	kjx_handle_send_rfid_data
* DESCRIPTION
*   ���ռ�����RFID���ݷ��͸�ƽ̨���Ա�ͳ��
* PARAMETERS
*
* RETURNS
*	none
*****************************************************************************/
void kjx_handle_send_rfid_data(void)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

	if(socketConnet && (kjx_rfid_id > 0))
    {
    	kjx_socket_send_data_with_type(SERVER_TYPE_70);
	}
}

#if defined(__KJX_AGAINST_THEFT__)
#ifdef __KJX_AGAINST_THEFT_TO_PILE__
void kjx_send_against_theft_to_sos_callback(void)
{
	static U16 sms_send = 0;
	char smsString[512];
	char strbuf[128] = {0};
	//�豸�����������豸�ţ�
	char warnStr[]={0xBE,0x8B,0x07,0x59,0xE6,0x89,0xD1,0x53,0xA5,0x62,0x66,0x8B,0x01,0xFF,0xBE,0x8B,0x07,0x59,0xF7,0x53,0x1A,0xFF,0x0,0x0};

	memset(smsString, 0x00, sizeof(smsString));
	mmi_ucs2cpy((CHAR *)smsString, (const CHAR *)warnStr);
	mmi_asc_to_ucs2((CHAR*)strbuf, (CHAR*)g_str_rfid_against);
	mmi_ucs2cat((CHAR *)smsString, (const CHAR *)strbuf);

	sms_send = against_sms_count;
	sms_send++;
	if(sms_send < 3)
	{
		if(strlen(g_kjx_nvram_struct.sosNum[sms_send])>0)
		{
			against_sms_count = sms_send;
			kjx_sms_send_sms(g_kjx_nvram_struct.sosNum[against_sms_count],(unsigned short *)smsString, 0x08, kjx_send_against_theft_to_sos_callback);
		}
		else if(strlen(g_kjx_nvram_struct.sosNum[sms_send+1])>0)
		{
			against_sms_count = (sms_send+1);
			kjx_sms_send_sms(g_kjx_nvram_struct.sosNum[against_sms_count],(unsigned short *)smsString, 0x08, kjx_send_against_theft_to_sos_callback);
		}
	}
	else if(sms_send >= 3)
	{
		sms_send = 0;
	}
}

void kjx_send_against_theft_to_sos(void)
{
	U16 i = 0;
	char smsString[512];
	char strbuf[128] = {0};
	//�豸�����������豸�ţ�
	char warnStr[]={0xBE,0x8B,0x07,0x59,0xE6,0x89,0xD1,0x53,0xA5,0x62,0x66,0x8B,0x01,0xFF,0xBE,0x8B,0x07,0x59,0xF7,0x53,0x1A,0xFF,0x0,0x0};

	memset(smsString, 0x00, sizeof(smsString));
	mmi_ucs2cpy((CHAR *)smsString, (const CHAR *)warnStr);
	mmi_asc_to_ucs2((CHAR*)strbuf, (CHAR*)g_str_rfid_against);
	mmi_ucs2cat((CHAR *)smsString, (const CHAR *)strbuf);
	
	for(i=0;i<3;i++)
	{
	#ifdef GPRS_FORMAT_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("sosNum[%d]:%s", i, g_kjx_nvram_struct.sosNum[i]);
	#endif	
	#endif
		if(strlen(g_kjx_nvram_struct.sosNum[i])>0)
		{
			against_sms_count = i;
			kjx_sms_send_sms(g_kjx_nvram_struct.sosNum[i],(unsigned short *)smsString, 0x08, kjx_send_against_theft_to_sos_callback);
			break;
		}
	}
}
#endif

void kjx_start_against_theft_alarm(void)
{
	srv_prof_ret ret;

	if(kjx_is_in_call())
		mmi_ucm_end_all_action();

	if(kjx_rfid_is_in_play())
		kjx_rfid_stop_play_audio();

	srv_vibrator_off();

	g_srv_prof.cur_setting.ring_vol = 7;
	mdi_audio_set_volume(VOL_TYPE_MEDIA, (U8)(MDI_AUD_VOL_MUTE(g_srv_prof.cur_setting.ring_vol)));

	ret = srv_prof_play_tone_with_id(
            SRV_PROF_TONE_INCOMING_CALL,
            AUD_ID_PROF_CUST_ALARM_1,
            SRV_PROF_RING_TYPE_REPEAT,
            NULL);

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("ret:%d", ret);
#endif
#endif
	
	if(ret == SRV_PROF_RET_SUCCESS)
	{
		g_rfid_against_theft = KAL_TRUE;
	}

#ifdef __KJX_AGAINST_THEFT_TO_PILE__
	kjx_send_against_theft_to_sos();
#endif
}

void kjx_stop_against_theft_alarm(void)
{
	g_rfid_against_theft = KAL_FALSE;

	srv_prof_stop_tone(SRV_PROF_TONE_INCOMING_CALL);
}
#endif

#if defined(__KJX_RESET_USED_COUNT__)
void kjx_handle_send_reset_count_data(void)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif
	
	kjx_socket_send_data_with_type(SERVER_TYPE_74);
}

BOOL kjx_rfid_playrec_add(U8 flag, U8* rfid_id, U32 count)
{
	U32 i=1;
	KJXRECORDINFO *tail,*pnew;
	static KJXRECORDINFO *pRec = NULL;
	static KJXRECORDINFO *pCfg = NULL;

	if(flag == 0)
		tail = g_kjxTourRecInfo.recinfo;//��¼�ļ�
	else
		tail = g_kjxTourCfgInfo.recinfo;//�����ļ�
	
	if(tail == NULL)
	{
		media_get_ext_buffer(MOD_MMI, (void **)&tail, sizeof(KJXRECORDINFO));
		if(tail == NULL) 
		{
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ�� 001���޷����!");
		#endif
		#endif
				
			return FALSE;
		}

		memset(tail->rfid_id, 0x00, sizeof(tail->rfid_id));
		tail->next = NULL;

		memcpy(tail->rfid_id, rfid_id, strlen(rfid_id));
		tail->count = count;

		if(flag == 0)//��¼�ļ�
		{
			pRec = tail;
			g_kjxTourRecInfo.recinfo = tail;
			g_kjxTourRecInfo.maxID = 1;

		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("��ӳɹ�001! num:%d, rfid_id:%s, count:%d", g_kjxTourRecInfo.maxID, g_kjxTourRecInfo.recinfo->rfid_id, g_kjxTourRecInfo.recinfo->count);
		#endif
		#endif
		}
		else//�����ļ�
		{
			pCfg = tail;
			g_kjxTourCfgInfo.recinfo = tail;
			g_kjxTourCfgInfo.maxID = 1;

		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("��ӳɹ�002! num:%d, rfid_id:%s, count:%d", g_kjxTourCfgInfo.maxID, g_kjxTourCfgInfo.recinfo->rfid_id, g_kjxTourCfgInfo.recinfo->count);
		#endif
		#endif	
		}
		
				
		return TRUE;
	}
	else
	{
		if(flag == 0)
			tail = pRec;//��¼�ļ�
		else
			tail = pCfg;//�����ļ�
			
		if(tail == NULL)
		{
			while(1)
			{
				if(tail->next == NULL)
					break;
				else
					tail = tail->next;
			}
		}

		media_get_ext_buffer(MOD_MMI, (void **)&pnew, sizeof(KJXRECORDINFO));
		if (pnew == NULL) 
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ��002���޷����!");
		#endif
		#endif
		
			return FALSE;
		}
		else
		{
			memset(pnew->rfid_id, 0x00, sizeof(pnew->rfid_id));
			pnew->count = 0;
			pnew->next = NULL;

			strcpy(pnew->rfid_id, rfid_id);
			pnew->count = count;
			
			tail->next = pnew;
			tail = pnew;//xb add 2017-05-08 ��¼������β

			if(flag == 0)
			{
				pRec = tail;
				g_kjxTourRecInfo.maxID++;//��¼�ļ�

			#ifdef RFID_DEBUG	
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("��ӳɹ�001! sum:%d", g_kjxTourRecInfo.maxID);
			#endif
			#endif
			}
			else
			{
				pCfg = tail;
				g_kjxTourCfgInfo.maxID++;//�����ļ�

			#ifdef RFID_DEBUG	
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("��ӳɹ�002! sum:%d", g_kjxTourCfgInfo.maxID);
			#endif
			#endif
			}

			return TRUE;
		}
	}
}

KJXRECORDINFO *kjx_rfid_playrec_find(U8 flag, U32 rfid_id)
{
	U32 i=1;
	BOOL ret;
	KJXRECORDINFO *head = NULL,*tail,*pnew;

	if(flag == 0)
		head = g_kjxTourRecInfo.recinfo;//��¼�ļ�
	else
		head = g_kjxTourCfgInfo.recinfo;//�����ļ�
		
	if(head == NULL)
	{
		if(flag == 0)
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("��¼����û�д������޷�����!");
		#endif
		#endif
		}
		else
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("��������û�д������޷�����!");
		#endif
		#endif	
		}

		return NULL;
	}

	while(head != NULL)
	{
		if(atoi(head->rfid_id) == rfid_id)
		{
			if(flag == 0)
			{
			#ifdef RFID_DEBUG	
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("��¼���ҳɹ�! %d", i);
			#endif
			#endif
			}
			else
			{
			#ifdef RFID_DEBUG	
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("���ò��ҳɹ�! %d", i);
			#endif
			#endif
			}
			return head;
		}
		else
		{
			i++;
			head = head->next;
		}
	}

	if(flag == 0)
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("��¼�����޽��!");
	#endif
	#endif
	}
	else
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("���ò����޽��!");
	#endif
	#endif		
	}

	return NULL;
}

void kjx_rfid_playrec_update(U32 rfid_num, U32 count)
{
	U32 i=0,rfid_id,flag = 0,str_len = 0;
	kal_uint32 fs_len;
	FS_HANDLE handle;
	S8 usc2Path[64] = {0};
	char tmpbuf[512] = {0};
	KJXRECORDINFO *recordinfo = NULL;
	S8* Stringbuf = NULL;
	U32 Stringlen = 0;
	
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("rfid_num:%d, count:%d", rfid_num, count);
#endif
#endif

	if(rfid_num <= 0)
	{
		return;
	}

	if(g_kjxTourCfgInfo.maxID == 0)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("û���ҵ������ļ������ø��¼�¼�ļ�");
	#endif
	#endif
	
		return;
	}
	
	recordinfo = kjx_rfid_playrec_find(0, rfid_num);
	if(recordinfo)
	{
		recordinfo->count += count;
		flag = 1;
	}
	else
	{
		char strrfid[MAX_RFID_LEN+1] = {0};

	#ifdef __KJX_RFID_LOCATION__
		sprintf(strrfid, "%06d", rfid_num);
	#else
		sprintf(strrfid, "%08d", rfid_num);
	#endif
		if(kjx_rfid_playrec_add(0, strrfid, count))
		{
			flag = 1;
		}
	}

	if(flag == 1)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("need update file!");
	#endif
	#endif
		kal_wsprintf((WCHAR*) usc2Path, "%c%w", SRV_FMGR_CARD_DRV, AUDIODIR);
		handle = FS_SetCurrentDir((WCHAR*)usc2Path);
		if(handle>=FS_NO_ERROR)
		{
			FS_SetAttributes(AUDIOPLAYREC, FS_ATTR_ARCHIVE);
			FS_Delete(AUDIOPLAYREC);
			
			handle = FS_Open(AUDIOPLAYREC, FS_READ_WRITE | FS_ATTR_ARCHIVE |FS_CREATE_ALWAYS | FS_ATTR_HIDDEN);
			if(handle>=FS_NO_ERROR)
			{
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("file creat!");
			#endif
			#endif

				memset(tmpbuf, 0, sizeof(tmpbuf));
				sprintf(tmpbuf, "%d", g_kjxTourRecInfo.maxID);
				
				Stringlen = strlen(tmpbuf)+strlen("|")+g_kjxTourRecInfo.maxID*(sizeof(KJXRECORDINFO)+strlen(",")+strlen(";"))+2;
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("maxID:%d, Stringlen:%d", g_kjxTourRecInfo.maxID, Stringlen);
			#endif
			#endif

				media_get_ext_buffer(MOD_MMI, (void **)&Stringbuf, Stringlen);
				if(Stringbuf == NULL)
				{
				#ifdef RFID_DEBUG
				#if defined(__KJX_LOG_OUTPUT__)
					LOGD("�����ڴ�ʧ��!");
				#endif
				#endif
					FS_Close(handle);
					return;
				}

				memset(Stringbuf, 0x00, Stringlen);
				strcpy(Stringbuf, tmpbuf);
				strcat(Stringbuf, "|");

				i = 0;
				recordinfo = g_kjxTourRecInfo.recinfo;
				while((i < g_kjxTourRecInfo.maxID) && (recordinfo != NULL))
				{
				#ifdef RFID_DEBUG
				#if defined(__KJX_LOG_OUTPUT__)
					LOGD("rfid_id:%s, count:%d", recordinfo->rfid_id, recordinfo->count);
				#endif
				#endif
					strcat(Stringbuf, recordinfo->rfid_id);
					strcat(Stringbuf, ",");
					memset(tmpbuf, 0, sizeof(tmpbuf));
					sprintf(tmpbuf, "%d", recordinfo->count);
					strcat(Stringbuf, tmpbuf);
					strcat(Stringbuf, ";");
					
					recordinfo = recordinfo->next;
					i++;
				}

				str_len = strlen(Stringbuf);
			#if defined(__KJX_AUDIO_FILE_DECODE__)
				kjx_decode_string(Stringbuf, str_len);
			#endif
				FS_Write(handle, (void*)Stringbuf, str_len, &fs_len);
				FS_Commit(handle);
				FS_Close(handle);

				if(Stringbuf != NULL)
				{
					media_free_ext_buffer(MOD_MMI, (void**)&Stringbuf);
					Stringbuf = NULL;
				}				
			}
		}
		else
		{
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ļ���ʧ��!");
		#endif
		#endif
		}
	}
}

void kjx_rfid_playrecord_delete_all(void)
{
	BOOL ret;
	FS_HANDLE handle;
	S8 usc2Path[64] = {0};
	char tmpbuf[512] = {0};	
	KJXRECORDINFO *head, *tail;
	U8 i = 0;
	
#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("maxID:%d", g_kjxTourRecInfo.maxID);
#endif
#endif

	kal_wsprintf((WCHAR*) usc2Path, "%c%w", SRV_FMGR_CARD_DRV, AUDIODIR);
	handle = FS_SetCurrentDir((WCHAR*)usc2Path);
	if(handle>=FS_NO_ERROR)
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("delete rec file");
	#endif
	#endif
		FS_SetAttributes(AUDIOPLAYREC, FS_ATTR_ARCHIVE);
		FS_Delete(AUDIOPLAYREC);
	}

	if(g_kjxTourRecInfo.recinfo != NULL)
	{
		head = g_kjxTourRecInfo.recinfo;
		while(head != NULL)
		{
			tail = head->next;
			media_free_ext_buffer(MOD_MMI, (void**)&head);
			head = tail;
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d", i++);
		#endif
		#endif			
		}

		g_kjxTourRecInfo.maxID = 0;
		g_kjxTourRecInfo.recinfo = NULL;

	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("ɾ���ɹ�!");
	#endif
	#endif			
	}
	else
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("������δ����������ɾ��!");
	#endif
	#endif		
	}
}

void kjx_rfid_set_playrecord(U8 flag, char* infor)
{
	char* temString = NULL;
	char* temString1 = NULL;
	char* myString = NULL;
	int i = 0, j=0;
	U32 filenum = 0;

	if(flag == 0)//��¼�ļ�
		g_kjxTourRecInfo.maxID = 0;
	else//�����ļ�
		g_kjxTourCfgInfo.maxID = 0;
	
	temString = NULL;
	temString = kjx_get_parameter_string_only_in_buffer(infor,"|",1);
#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("temString:%s", temString);
#endif
#endif
	if(atoi(temString)>0)
	{
		filenum = atoi(temString);
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("filenum:%d", filenum);
	#endif
	#endif
		myString = strstr(infor,"|");
		myString += strlen("|");

		for(i=0;i<filenum;i++)
		{
			U32 len = 0;
			char rfid_id[MAX_RFID_LEN+1] = {0};
			char playString[128] = {0};
			U32 count = 0;
		
			temString = NULL;
			temString = kjx_get_parameter_string_only_in_buffer(myString+j,";",1);
			memcpy(playString,temString,strlen(temString));
			j += strlen(temString)+1;
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d, playString=%s", i, playString);
		#endif
		#endif
			temString1 = NULL;
			temString1 = kjx_get_parameter_string_only_in_buffer(playString,",",1);
			len = (MAX_RFID_LEN > strlen(temString1)) ? strlen(temString1) : MAX_RFID_LEN;
			memcpy(rfid_id, temString1, len);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d, rfid_id:%s", i, rfid_id);
		#endif
		#endif
			temString1 = NULL;
			temString1 = kjx_get_parameter_string_only_in_buffer(playString,",",2);
			count = atoi(temString1);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d, count:%d", i, count);
		#endif
		#endif

			if(!kjx_rfid_playrec_add(flag, rfid_id, count))
			{
				break;
			}
		}

		if(flag == 0)//��¼�ļ�
		{
			if(i == filenum)
				g_kjxTourRecInfo.maxID = filenum;
			else
				g_kjxTourRecInfo.maxID = i+1;			
		}
		else//�����ļ�
		{
			if(i == filenum)
				g_kjxTourCfgInfo.maxID = filenum;
			else
				g_kjxTourCfgInfo.maxID = i+1;			
		}
	}
}

void kjx_rfid_playrecord_read(U8 flag)
{
	kal_uint32 fs_len;
	FS_HANDLE handle;
	S8 usc2Path[64];
	UINT filesize;

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("flag:%d", flag);
#endif
#endif

	memset(usc2Path, 0x00, sizeof(usc2Path));	
	kal_wsprintf((WCHAR*) usc2Path, "%c%w", SRV_FMGR_CARD_DRV, AUDIODIR);
	handle = FS_SetCurrentDir((WCHAR*)usc2Path);
	if(handle>=FS_NO_ERROR)
	{
		if(flag == 0)//��¼�ļ�
		{
			FS_SetAttributes(AUDIOPLAYREC, FS_ATTR_ARCHIVE | FS_ATTR_HIDDEN);
			handle = FS_Open(AUDIOPLAYREC, FS_READ_ONLY | FS_ATTR_ARCHIVE);
		}
		else//�����ļ�
		{
			FS_SetAttributes(AUDIOPLAYCFG, FS_ATTR_ARCHIVE | FS_ATTR_HIDDEN);
			handle = FS_Open(AUDIOPLAYCFG, FS_READ_ONLY | FS_ATTR_ARCHIVE);	
		}
		
		if (handle>=FS_NO_ERROR)
		{
			FS_GetFileSize(handle, &filesize);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("filesize:%d", filesize);
		#endif
		#endif

			if(filesize == 0)
			{
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("�ļ�����Ϊ��!");
			#endif
			#endif
				FS_Close(handle);
				return;
			}
			
			if(fileString == NULL)
			{
				media_get_ext_buffer(MOD_MMI, (void **)&fileString, filesize+1);
				if(fileString == NULL)
				{
				#ifdef RFID_DEBUG
				#if defined(__KJX_LOG_OUTPUT__)
					LOGD("�����ڴ�ʧ��!");
				#endif
				#endif
					FS_Close(handle);
					return;
				}
			}
			memset(fileString, 0x00, filesize+1);
			FS_Read(handle, (void *)fileString, filesize, &fs_len);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("001, fs_len:%d", fs_len);
		#endif
		#endif
			FS_Close(handle);

		#if defined(__KJX_AUDIO_FILE_DECODE__)
			kjx_encode_string(fileString, fs_len);
		#endif

			if(strlen(fileString)>0)
			{
				kjx_rfid_set_playrecord(flag, fileString);
			}

			if(fileString != NULL)
			{
				media_free_ext_buffer(MOD_MMI, (void**)&fileString);
				fileString = NULL;
			}
		}
	}
}

void kjx_read_playrec_file(void)
{
	static BOOL readflag = FALSE;

	if(readflag == FALSE)
	{
		readflag = TRUE;
		
		kjx_rfid_playrecord_read(1);//��ȡ�����ļ�
		kjx_rfid_playrecord_read(0);//��ȡ��¼�ļ�
	}
}

void kjx_handle_reset_show_timerout(void)
{
	memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
	mmi_show_scrolling_infor();
}

void kjx_handle_receive_reset_rfid(U8 flag)
{
    //��λ�ɹ�
    char ResetSuccString[]={0x88,0x63,0x43,0x67,0x10,0x62,0x9F,0x52,0x00,0x00};
	char tts_buf[128] = {0};
	
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("useflag:%d,rfid_count:%d", g_kjx_nvram_struct.useflag, rfid_count);
#endif
#endif

#if defined(__KJX_AGAINST_THEFT__)
	kjx_stop_against_theft_alarm();
#endif

	if((g_kjx_nvram_struct.useflag == 1) && (rfid_count >= RFID_NUM_CAUSE_RUC))	//xb add 2017-10-13 �����ڿ�ʼͳ��״̬�²�ֹͣ���ţ���ֹ�շ���ͬʱ�յ���λ�źź;�Դ�źţ����²��ű��ж�
	{
		U8 i;
		
	#ifdef __BLE_MODULE_SUPPORT__
		if(flag == 1)
			g_kjx_ble_id = 0;
		else
	#endif
			g_kjx_rfid_id = 0;
		
		kjx_rfid_id = 0;
		
		myID = 0;
		last_id = -1;

		rfid_count = 0;
		for(i=0;i<RFID_NUM_MAX;i++)
		{
			rfid_num[i] = 0;
		}
		
		mmi_idle_display();
		
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_ucs2cpy((CHAR*)kjx_scrolling_show, (const CHAR*)GetString(STR_KJX_IDLE_RESET_SUCCESS_BY_RFID));
		mmi_show_scrolling_infor();
		StartTimer(KJX_TIMER_RESET_SHOW, 2*1000, kjx_handle_reset_show_timerout);
		
		g_kjx_nvram_struct.useflag = 0;
		if(g_kjx_nvram_struct.usecount > 0)
			kjx_handle_send_reset_count_data();

		kjx_nvram_write();

	#if defined(__NPR_TTS__)
	 	if(mmi_ucs2strlen((const CHAR*)ResetSuccString)>0)
	 	{
		 	Npr_Tts_play_stop();
		 	Npr_Ttsplayer_playtextw((char*)ResetSuccString,NULL);  
	 	}
	#endif

	#if defined(__KJX_FUN_SENSOR__)
		StartTimer(KJX_TIMER_ID_SENSOR_INIT, 1000, kjx_sensor_reset);
	#endif

	#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
		kjx_rfid_sequential_played_infor_reset();
	#endif
	}

	kjx_rfid_playrecord_delete_all();
}

void kjx_reset_ruc(void)
{
	//��λ�ƴγ�ʼ���ɹ�
	char ResetSuccString[]={0x88,0x63,0x43,0x67,0x10,0x62,0x9F,0x52,0x00,0x00};//{0x0D,0x59,0x4D,0x4F,0xA1,0x8B,0x21,0x6B,0x1D,0x52,0xCB,0x59,0x16,0x53,0x10,0x62,0x9F,0x52,0x00,0x00};
	char tts_buf[128] = {0};
	U8 i;

#if defined(__KJX_AGAINST_THEFT__)
	kjx_stop_against_theft_alarm();
#endif

#ifdef __BLE_MODULE_SUPPORT__
	g_kjx_ble_id = 0;
#endif
	g_kjx_rfid_id = 0;
	kjx_rfid_id = 0;	
	
	myID = 0;
	last_id = -1;

	mmi_idle_display();
	
	kjx_audio_is_playing = FALSE;
	kjx_audio_status = 0;
	mdi_audio_stop_file();

	memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
	mmi_ucs2cpy((CHAR*)kjx_scrolling_show, (const CHAR*)GetString(STR_KJX_IDLE_RESET_SUCCESS_BY_RUC));
	mmi_show_scrolling_infor();
	StartTimer(KJX_TIMER_RESET_SHOW, 2*1000, kjx_handle_reset_show_timerout);

	rfid_count = 0;
	for(i=0;i<RFID_NUM_MAX;i++)
	{
		rfid_num[i] = 0;
	}
	
	g_kjx_nvram_struct.useflag = 0;
	g_kjx_nvram_struct.usecount = 0;
	kjx_nvram_write();

	kjx_rfid_playrecord_delete_all();
	
#if defined(__NPR_TTS__)
	if(mmi_ucs2strlen((const CHAR *)ResetSuccString)>0)
	{
		Npr_Tts_play_stop();
		Npr_Ttsplayer_playtextw(ResetSuccString,NULL);	
	}
#endif	
}

#endif

void kjx_rfid_set_playinfos(char* infor)
{
	char* temString = NULL;
	char* temString1 = NULL;
	char* myString = NULL;
	U32 i = 0, j=0, k=0;
	U16 file_path_name[2*(MAX_PLAY_NAME_LEN+1)] = {0};
	U16 tmpbuf[2*(MAX_PLAY_NAME_LEN+1)] = {0};
	U32 time = 0;
	U32 filenum = 0;
	mdi_result result;

	g_kjxRfidPlayInfo.maxID = 0;
	
	temString = NULL;
	temString = kjx_get_parameter_string_only_in_buffer(infor,"|",1);
#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("temString:%s", temString);
#endif
#endif
	if(atoi(temString)>0)
	{
		filenum = atoi(temString);
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("filenum:%d", filenum);
	#endif
	#endif
		myString = strstr(infor,"|");
		myString += strlen("|");

		for(i=0;i<filenum;i++)
		{
			char rfid_id[MAX_RFID_LEN+1] = {0};	
			char file_name[MAX_PLAY_NAME_LEN+1] = {0};
			char playString[MAX_RFID_LEN+MAX_PLAY_NAME_LEN+10] = {0};
			U32 durtime = 0;
			U32 len = 0;
			U8 played = 0;			
		
			temString = NULL;
			temString = kjx_get_parameter_string_only_in_buffer(myString+k,";",1);
			memcpy(playString,temString,strlen(temString));
			k += strlen(temString)+1;
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d, j:%d, playString=%s", i, j, playString);
		#endif
		#endif
			temString1 = NULL;
			temString1 = kjx_get_parameter_string_only_in_buffer(playString,",",1);
			len = (MAX_RFID_LEN > strlen(temString1)) ? strlen(temString1) : MAX_RFID_LEN;
			memcpy(rfid_id, temString1, len);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d, rfid_id=%s", i, temString1);
		#endif
		#endif
			temString1 = NULL;
			temString1 = kjx_get_parameter_string_only_in_buffer(playString,",",2);
			len = (MAX_PLAY_NAME_LEN > strlen(temString1)) ? strlen(temString1) : MAX_PLAY_NAME_LEN;
			memcpy(file_name, temString1, len);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d, file_name=%s", i, temString1);
		#endif
		#endif

			kal_wsprintf((WCHAR*) file_path_name, "%c%w", SRV_FMGR_CARD_DRV, AUDIODIR);
		#ifdef __KJX_MULTI_LANGUAGE__
			switch(g_kjx_language)
			{
			case LANG_ENGLISH:				//Ӣ
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ENGLISH);
				break;
			case LANG_FRENCH:				//��
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FRENCH);
				break;
			case LANG_GERMAN:				//��
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_GERMAN);
				break;
			case LANG_ITALIAN:				//�����
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ITALIAN);
				break;
			case LANG_SPANISH:				//������
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_SPANISH);
				break;
			case LANG_PORTUGUESE:			//������
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_PORTUGUESE);
				break;
			case LANG_POLISH:				//����
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_POLISH);
				break;
			case LANG_DANISH:				//����
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_DANISH);
				break;
			case LANG_SWEDISH:				//���
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_SWEDISH);
				break;
			case LANG_NORWEGIAN:			//Ų��
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_NORWEGIAN);
				break;
			case LANG_FINNISH:				//����
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FINNISH);
				break;
			case LANG_DUTCH:				//����
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_DUTCH);
				break;
			case LANG_UKRAINIAN:			//�ڿ���
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_UKRAINIAN);
				break;
			case LANG_RUSSIAN:				//����˹
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_RUSSIAN);
				break;
			case LANG_GREEK:				//ϣ��
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_GREEK);
				break;
			case LANG_TURKISH:				//������
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_TURKISH);
				break;
			case LANG_ARABIC:				//������
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ARABIC);
				break;
			case LANG_HEBREW:				//ϣ������(��ɫ��)
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_HEBREW);
				break;
			case LANG_PERSIAN:				//��˹��(����)
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_PERSIAN);
				break;
			case LANG_URDU: 				//�ڶ�����(�ͻ�˹̹)
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_URDU);
				break;
			case LANG_HINDI:				//ӡ����(ӡ��)
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_HINDI);
				break;
			case LANG_BENGALI:				//�ϼ���
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_BENGALI);
				break;
			case LANG_LAO:					//����
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_LAO);
				break;
			case LANG_KHMER:				//������(����կ)
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_KHMER);
				break;
			case LANG_MYANMAR:				//���
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_MYANMAR);
				break;
			case LANG_VIETNAMESE:			//Խ��
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_VIETNAMESE);
				break;
			case LANG_INDONESIAN:			//ӡ��������
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_INDONESIAN);
				break;
			case LANG_MALAY:				//������(��������,����)
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_MALAY);
				break;
			case LANG_THAI: 				//̩��
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_THAI);
				break;
			case LANG_FILIPINO: 			//���ɱ���
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FILIPINO);
				break;
			case LANG_KOREAN:				//������(����,����)
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_KOREAN);
				break;
			case LANG_JAPANESE: 			//�ձ�
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_JAPANESE);
				break;
			case LANG_CHN:					//������ͨ��
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN);
				break;
			case LANG_CHN_SC:				//�����Ĵ���
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_SC);
				break;
			case LANG_CHN_GD:				//���Ĺ㶫��
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_GD);
				break;
			case LANG_CHN_MN:				//�������ϻ�
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_MN);
				break;
			case LANG_CHN_XZ:				//���Ĳ���
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ);
				break;
			case LANG_CHN_XZ_LASA:				//���Ĳ�������
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_LASA);
				break;
			case LANG_CHN_XZ_ANDUO:				//���Ĳ��ﰲ��
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_ANDUO);
				break;
			case LANG_CHN_XZ_KANGBA:			//���Ĳ��￵��
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_KANGBA);
				break;
			case LANG_CHN_EXTRA:			//������������
				mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_EXTRA);
				break;
			}	
		#endif
			mmi_chset_convert(MMI_CHSET_GB18030, MMI_CHSET_UCS2, file_name, (char*)tmpbuf, sizeof(tmpbuf));
			mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)tmpbuf);

		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("result:%d, time:%d", result, time);
		#endif
		#endif

			played = 0;

			if(!kjx_rfid_playinfo_add(durtime, played, rfid_id, file_name))
			{
				break;
			}
		}

		if(i == filenum)
			g_kjxRfidPlayInfo.maxID = filenum;
		else
			g_kjxRfidPlayInfo.maxID = i+1;
	}
}

void kjx_rfid_play_infos_read(void)
{
	kal_uint32 fs_len;
	FS_HANDLE handle;
	S8 usc2Path[128];
	UINT filesize;

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

	kjx_rfid_playinfo_delete_all();

	memset(usc2Path, 0x00, sizeof(usc2Path));	
	kal_wsprintf((WCHAR*) usc2Path, "%c%w", SRV_FMGR_CARD_DRV, AUDIODIR);
#ifdef __KJX_MULTI_LANGUAGE__
	switch(g_kjx_language)
	{
	case LANG_ENGLISH:				//Ӣ
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_ENGLISH);
		break;
	case LANG_FRENCH:				//��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_FRENCH);
		break;
	case LANG_GERMAN:				//��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_GERMAN);
		break;
	case LANG_ITALIAN:				//�����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_ITALIAN);
		break;
	case LANG_SPANISH:				//������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_SPANISH);
		break;
	case LANG_PORTUGUESE:			//������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_PORTUGUESE);
		break;
	case LANG_POLISH:				//����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_POLISH);
		break;
	case LANG_DANISH:				//����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_DANISH);
		break;
	case LANG_SWEDISH:				//���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_SWEDISH);
		break;
	case LANG_NORWEGIAN:			//Ų��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_NORWEGIAN);
		break;
	case LANG_FINNISH:				//����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_FINNISH);
		break;
	case LANG_DUTCH:				//����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_DUTCH);
		break;
	case LANG_UKRAINIAN:			//�ڿ���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_UKRAINIAN);
		break;
	case LANG_RUSSIAN:				//����˹
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_RUSSIAN);
		break;
	case LANG_GREEK:				//ϣ��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_GREEK);
		break;
	case LANG_TURKISH:				//������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_TURKISH);
		break;
	case LANG_ARABIC:				//������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_ARABIC);
		break;
	case LANG_HEBREW:				//ϣ������(��ɫ��)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_HEBREW);
		break;
	case LANG_PERSIAN:				//��˹��(����)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_PERSIAN);
		break;
	case LANG_URDU: 				//�ڶ�����(�ͻ�˹̹)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_URDU);
		break;
	case LANG_HINDI:				//ӡ����(ӡ��)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_HINDI);
		break;
	case LANG_BENGALI:				//�ϼ���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_BENGALI);
		break;
	case LANG_LAO:					//����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_LAO);
		break;
	case LANG_KHMER:				//������(����կ)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_KHMER);
		break;
	case LANG_MYANMAR:				//���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_MYANMAR);
		break;
	case LANG_VIETNAMESE:			//Խ��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_VIETNAMESE);
		break;
	case LANG_INDONESIAN:			//ӡ��������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_INDONESIAN);
		break;
	case LANG_MALAY:				//������(��������,����)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_MALAY);
		break;
	case LANG_THAI: 				//̩��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_THAI);
		break;
	case LANG_FILIPINO: 			//���ɱ���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_FILIPINO);
		break;
	case LANG_KOREAN:				//������(����,����)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_KOREAN);
		break;
	case LANG_JAPANESE: 			//�ձ�
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_JAPANESE);
		break;
	case LANG_CHN:					//������ͨ��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN);
		break;
	case LANG_CHN_SC:				//�����Ĵ���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_SC);
		break;
	case LANG_CHN_GD:				//���Ĺ㶫��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_GD);
		break;
	case LANG_CHN_MN:				//�������ϻ�
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_MN);
		break;
	case LANG_CHN_XZ:				//���Ĳ���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_XZ);
		break;
	case LANG_CHN_XZ_LASA:				//���Ĳ�������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_XZ_LASA);
		break;
	case LANG_CHN_XZ_ANDUO:				//���Ĳ��ﰲ��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_XZ_ANDUO);
		break;
	case LANG_CHN_XZ_KANGBA:			//���Ĳ��￵��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_XZ_KANGBA);
		break;
	case LANG_CHN_EXTRA:			//������������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_EXTRA);
		break;
	}	
#endif

	handle = FS_SetCurrentDir((WCHAR*)usc2Path);
	if(handle>=FS_NO_ERROR)
	{
		FS_SetAttributes(AUDIOPLAYINFO, FS_ATTR_ARCHIVE);
		handle = FS_Open(AUDIOPLAYINFO, FS_READ_ONLY | FS_ATTR_ARCHIVE);
		if(handle>=FS_NO_ERROR)
		{
			FS_GetFileSize(handle, &filesize);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("filesize:%d", filesize);
		#endif
		#endif

			if(filesize == 0)
			{
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("�ļ�����Ϊ��!");
			#endif
			#endif
				FS_Close(handle);
				return;
			}
			
			if(fileString == NULL)
			{
				media_get_ext_buffer(MOD_MMI, (void **)&fileString, filesize+1);
				if(fileString == NULL)
				{
				#ifdef RFID_DEBUG
				#if defined(__KJX_LOG_OUTPUT__)
					LOGD("�����ڴ�ʧ��!");
				#endif
				#endif
					FS_Close(handle);
					return;
				}
			}
			memset(fileString, 0x00, filesize+1);
			FS_Read(handle, (void *)fileString, filesize, &fs_len);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("001, fs_len:%d", fs_len);
		#endif
		#endif
			FS_Close(handle);
		
		#if defined(__KJX_AUDIO_FILE_DECODE__)
			kjx_encode_string(fileString, fs_len);
		#endif

			if(strlen(fileString)>0)
			{
				kjx_rfid_set_playinfos(fileString);
			}

			if(fileString != NULL)
			{
				media_free_ext_buffer(MOD_MMI, (void**)&fileString);
				fileString = NULL;
			}		
		}
		else
		{
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ļ�������");
		#endif
		#endif
		}
	}
}

#ifdef __KJX_TOUR_NAME_STORE_CARD__
void kjx_rfid_get_nameinfos(char* infor)
{
	char* temString = NULL;
	char* temString1 = NULL;
	char* myString = NULL;
	U32 i = 0, j=0;
	U32 time = 0;
	U32 filenum = 0;
	mdi_result result;

	temString = NULL;
	temString = kjx_get_parameter_string_only_in_buffer(infor,"|",1);
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("temString:%s", temString);
#endif
#endif
	if(atoi(temString)>0)
	{
		filenum = atoi(temString);
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("filenum:%d", filenum);
	#endif
	#endif
		myString = strstr(infor,"|");
		myString += strlen("|");
		for(i=0;i<filenum;i++)
		{
			U32 len = 0;
			char rfid_id[MAX_RFID_LEN+1] = {0};	
			char name[MAX_SHOW_NAME_LEN+1] = {0};
			char playString[MAX_RFID_LEN+MAX_SHOW_NAME_LEN+10] = {0};
			
			temString = NULL;
			temString = kjx_get_parameter_string_only_in_buffer(myString+j,";",1);
			memcpy(playString,temString,strlen(temString));
			j += strlen(temString)+1;
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d, playString=%s", i, playString);
		#endif
		#endif
			temString1 = NULL;
			temString1 = kjx_get_parameter_string_only_in_buffer(playString,",",1);
			len = (MAX_RFID_LEN > strlen(temString1)) ? strlen(temString1) : MAX_RFID_LEN;
			memcpy(rfid_id, temString1, len);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d, rfid_id:%s", i, temString1);
		#endif
		#endif
			temString1 = NULL;
			temString1 = kjx_get_parameter_string_only_in_buffer(playString,",",2);
			len = (MAX_SHOW_NAME_LEN > strlen(temString1)) ? strlen(temString1) : MAX_SHOW_NAME_LEN;
			memcpy(name, temString1, len);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d, name:%s", i, temString1);
		#endif
		#endif

			if(!kjx_rfid_nameinfo_add(rfid_id, name))
			{
				break;
			}
		}

		if(i == filenum)
			g_kjxTourNameInfo.maxID = filenum;
		else
			g_kjxTourNameInfo.maxID = i+1;
	}	
}

void kjx_rfid_name_infos_read(void)
{
	kal_uint32 fs_len;
	FS_HANDLE handle;
	S8 usc2Path[128];
	UINT filesize;

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

	kjx_rfid_nameinfo_delete_all();

	memset(usc2Path, 0x00, sizeof(usc2Path));	
	kal_wsprintf((WCHAR*) usc2Path, "%c%w", SRV_FMGR_CARD_DRV, AUDIODIR);
#ifdef __KJX_MULTI_LANGUAGE__
	switch(g_kjx_language)
	{
	case LANG_ENGLISH:				//Ӣ
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_ENGLISH);
		break;
	case LANG_FRENCH:				//��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_FRENCH);
		break;
	case LANG_GERMAN:				//��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_GERMAN);
		break;
	case LANG_ITALIAN:				//�����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_ITALIAN);
		break;
	case LANG_SPANISH:				//������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_SPANISH);
		break;
	case LANG_PORTUGUESE:			//������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_PORTUGUESE);
		break;
	case LANG_POLISH:				//����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_POLISH);
		break;
	case LANG_DANISH:				//����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_DANISH);
		break;
	case LANG_SWEDISH:				//���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_SWEDISH);
		break;
	case LANG_NORWEGIAN:			//Ų��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_NORWEGIAN);
		break;
	case LANG_FINNISH:				//����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_FINNISH);
		break;
	case LANG_DUTCH:				//����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_DUTCH);
		break;
	case LANG_UKRAINIAN:			//�ڿ���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_UKRAINIAN);
		break;
	case LANG_RUSSIAN:				//����˹
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_RUSSIAN);
		break;
	case LANG_GREEK:				//ϣ��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_GREEK);
		break;
	case LANG_TURKISH:				//������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_TURKISH);
		break;
	case LANG_ARABIC:				//������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_ARABIC);
		break;
	case LANG_HEBREW:				//ϣ������(��ɫ��)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_HEBREW);
		break;
	case LANG_PERSIAN:				//��˹��(����)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_PERSIAN);
		break;
	case LANG_URDU: 				//�ڶ�����(�ͻ�˹̹)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_URDU);
		break;
	case LANG_HINDI:				//ӡ����(ӡ��)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_HINDI);
		break;
	case LANG_BENGALI:				//�ϼ���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_BENGALI);
		break;
	case LANG_LAO:					//����
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_LAO);
		break;
	case LANG_KHMER:				//������(����կ)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_KHMER);
		break;
	case LANG_MYANMAR:				//���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_MYANMAR);
		break;
	case LANG_VIETNAMESE:			//Խ��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_VIETNAMESE);
		break;
	case LANG_INDONESIAN:			//ӡ��������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_INDONESIAN);
		break;
	case LANG_MALAY:				//������(��������,����)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_MALAY);
		break;
	case LANG_THAI: 				//̩��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_THAI);
		break;
	case LANG_FILIPINO: 			//���ɱ���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_FILIPINO);
		break;
	case LANG_KOREAN:				//������(����,����)
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_KOREAN);
		break;
	case LANG_JAPANESE: 			//�ձ�
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_JAPANESE);
		break;
	case LANG_CHN:					//������ͨ��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN);
		break;
	case LANG_CHN_SC:				//�����Ĵ���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_SC);
		break;
	case LANG_CHN_GD:				//���Ĺ㶫��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_GD);
		break;
	case LANG_CHN_MN:				//�������ϻ�
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_MN);
		break;
	case LANG_CHN_XZ:				//���Ĳ���
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_XZ);
		break;
	case LANG_CHN_XZ_LASA:				//���Ĳ�������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_XZ_LASA);
		break;
	case LANG_CHN_XZ_ANDUO:				//���Ĳ��ﰲ��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_XZ_ANDUO);
		break;
	case LANG_CHN_XZ_KANGBA:			//���Ĳ��￵��
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_XZ_KANGBA);
		break;
	case LANG_CHN_EXTRA:			//������������
		mmi_ucs2cat((CHAR*)usc2Path, (CHAR*)AUDIODIR_LANG_CHN_EXTRA);
		break;
	}	
#endif

	handle = FS_SetCurrentDir((WCHAR*)usc2Path);
	if(handle>=FS_NO_ERROR)
	{
		FS_SetAttributes(AUDIONAMEINFO, FS_ATTR_ARCHIVE);
		handle = FS_Open(AUDIONAMEINFO, FS_READ_ONLY | FS_ATTR_ARCHIVE);
		if (handle>=FS_NO_ERROR)
		{
			FS_GetFileSize(handle, &filesize);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("filesize:%d", filesize);
		#endif
		#endif
			if(filesize == 0)
			{
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("�ļ�����Ϊ��!");
			#endif
			#endif
				FS_Close(handle);
				return;
			}
			
			if(fileString == NULL)
			{
				media_get_ext_buffer(MOD_MMI, (void **)&fileString, filesize+1);
				if(fileString == NULL)
				{
				#ifdef RFID_DEBUG
				#if defined(__KJX_LOG_OUTPUT__)
					LOGD("�����ڴ�ʧ��!");
				#endif
				#endif
					FS_Close(handle);
					return;
				}
			}
			memset(fileString, 0x00, filesize+1);
			FS_Read(handle, (void*)fileString, filesize, &fs_len);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("001, fs_len:%d", fs_len);
		#endif
		#endif
			FS_Close(handle);
		
		#if defined(__KJX_AUDIO_FILE_DECODE__)
			kjx_encode_string(fileString, fs_len);
		#endif

			if(strlen(fileString)>0)
			{
				kjx_rfid_get_nameinfos(fileString);
			}
		
			if(fileString != NULL)
			{
				media_free_ext_buffer(MOD_MMI, (void**)&fileString);
				fileString = NULL;
			}
		}
		else
		{
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ļ�������");
		#endif
		#endif
		}	
	}
}
#endif

#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
void kjx_rfid_sequential_played_infor_reset(void)
{
	KJXDOTINFO *head = NULL;

	if(g_kjxPlayedInfo.DotInfo == NULL || g_kjxPlayedInfo.maxdot == 0)
	{
		return;
	}

	head = g_kjxPlayedInfo.DotInfo;
	while(head)
	{
		g_kjxPlayedInfo.DotInfo = head->next;
		media_free_ext_buffer(MOD_MMI, (void**)&head);
		head = g_kjxPlayedInfo.DotInfo;
	}

	g_kjxPlayedInfo.maxdot = 0;
}

void kjx_rfid_sequential_played_infor_add(U32 rfid_id)
{
	U32 i=1;
	KJXDOTINFO *pnew;
	static KJXDOTINFO *head = NULL;

	if(MAX_RFID_SEQUENTIAL_PLAYED == 0)
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("��·��󾰵�Ϊ�գ������¼!");
	#endif
	#endif
		
		return;
	}
	
	if(g_kjxPlayedInfo.DotInfo == NULL)
	{
		g_kjxPlayedInfo.maxdot = 0;

		media_get_ext_buffer(MOD_MMI, (void **)&head, sizeof(KJXDOTINFO));
		if(head == NULL) 
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ��001���޷���¼!");
		#endif
		#endif
		
			return;
		}

		head->rfid_id = rfid_id;
		head->next = NULL;

		g_kjxPlayedInfo.DotInfo = head;
		g_kjxPlayedInfo.maxdot = 1;

	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("��ӵ�%d�����ż�¼�ɹ�! ����:%d", g_kjxPlayedInfo.maxdot, rfid_id);
	#endif
	#endif
	}
	else
	{
		if(head == NULL)
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("����");
		#endif
		#endif
		
			head = g_kjxPlayedInfo.DotInfo;
			while(1)
			{
				if(head->next == NULL)
					break;
				else
					head = head->next;
			}
		}
		
		media_get_ext_buffer(MOD_MMI, (void **)&pnew, sizeof(KJXDOTINFO));
		if(pnew == NULL) 
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ��002���޷���¼!");
		#endif
		#endif

			return;
		}
		else
		{
			pnew->rfid_id = rfid_id;
			pnew->next = NULL;

			head->next = pnew;
			head = pnew;//xb add 2017-05-08 ��¼������β

			g_kjxPlayedInfo.maxdot++;
			if(g_kjxPlayedInfo.maxdot > MAX_RFID_SEQUENTIAL_PLAYED)
			{
				//��������¼���������ʼ��һ����¼
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("��������¼���������ʼ��һ����¼");
			#endif
			#endif
				
				g_kjxPlayedInfo.maxdot = MAX_RFID_SEQUENTIAL_PLAYED;

				pnew = g_kjxPlayedInfo.DotInfo;
				g_kjxPlayedInfo.DotInfo = pnew->next;
				media_free_ext_buffer(MOD_MMI, (void**)&pnew);
				pnew = NULL;
			}
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("��ӵ�%d�����ż�¼�ɹ�! ����:%d", g_kjxPlayedInfo.maxdot, rfid_id);
		#endif
		#endif
		}
	}
}

BOOL kjx_rfid_sequential_infor_check(U32 rfid_id)
{
	U32 i=0,j=0,k=0;
	BOOL flag = FALSE;//�ж���·����û�м�¼ƥ�䣬���ǵ�ǰ���㲻ƥ��
	KJXDOTINFO *dotinfo = NULL;
	KJXDOTINFO *tmpinfo = NULL;
	KJXDOTINFO *playedinfo = NULL;

	if(g_kjxRfidSequenInfo.maxLine == 0)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("û�����ò���˳��ֱ�Ӳ���");
	#endif
	#endif
		return TRUE;
	}

	if(g_kjxPlayedInfo.maxdot == 0)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("û�в��ż�¼��ֱ�Ӳ���");
	#endif
	#endif
		return TRUE;
	}

	for(i=0;i<g_kjxRfidSequenInfo.maxLine;i++)
	{
		if(g_kjxRfidSequenInfo.LineInfo[i].maxdot == 0)
			continue;

		j = 0;
		playedinfo = g_kjxPlayedInfo.DotInfo;
		while(1)
		{
			dotinfo = g_kjxRfidSequenInfo.LineInfo[i].DotInfo;
			
			//�Ӳ��ż�¼���ҵ�һ����ǰ��·�ĵ�һ����
			while(j<g_kjxPlayedInfo.maxdot)
			{
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("��%d�����ż�¼���:%d, ��%d����·��1��������:%d", j+1, playedinfo->rfid_id, i+1, dotinfo->rfid_id);
			#endif
			#endif
				if(playedinfo->rfid_id == dotinfo->rfid_id)
				{
					break;
				}
				else
				{
					playedinfo = playedinfo->next;
					j++;
				}
			}

			if(j == g_kjxPlayedInfo.maxdot)
			{
				//���ż�¼��δ�ҵ���ǰ��·�ĵ�һ���㣬�����Ƚ���һ����·�ĵ�һ����
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("δ�ҵ���%d����·��1��������%d, �����Ƚ���һ����·", i+1, dotinfo->rfid_id);
			#endif
			#endif
				
				break;
			}
			else
			{
				//�жϲ��ż�¼��һ�������·��һ�����ǲ���ƥ��
				//�ݴ沥�ż�¼�з��ֵ�λ��
				tmpinfo = playedinfo;
				dotinfo = dotinfo->next;
				playedinfo = playedinfo->next;
				while(playedinfo&&dotinfo)
				{
					if(playedinfo->rfid_id != dotinfo->rfid_id)
						break;
					
					playedinfo = playedinfo->next;
					dotinfo = dotinfo->next;
				}

				if(playedinfo == NULL)
				{
					//���ż�¼����ǰ��·��ȫƥ�䣬�жϵ�ǰ����
					if(dotinfo)
					{
					#ifdef RFID_DEBUG
					#if defined(__KJX_LOG_OUTPUT__)
						LOGD("��ǰ������%d,��%d����·������%d", rfid_id, i+1, dotinfo->rfid_id);
					#endif
					#endif
					
						if(rfid_id == dotinfo->rfid_id)
						{
						#ifdef RFID_DEBUG
						#if defined(__KJX_LOG_OUTPUT__)
							LOGD("��%d����·��������ɹ�!", i+1);
						#endif
						#endif

							return TRUE;
						}
						else
						{
						#ifdef RFID_DEBUG
						#if defined(__KJX_LOG_OUTPUT__)
							LOGD("���ż�¼���%d����·����ɹ�������ǰ��������ʧ��!�����ж���һ����·", i+1);
						#endif
						#endif
						
							k = i;
							flag = TRUE;
							break;
						}
					}
					else
					{
					#ifdef RFID_DEBUG
					#if defined(__KJX_LOG_OUTPUT__)
						LOGD("������·��Χ��������������");
					#endif
					#endif
						return TRUE;	
					}
				}
				else
				{
					//�жϲ��ż�¼�Ƿ������ɣ�û�м���������һ��λ�ã���������һ����·�в���
					j++;
					playedinfo = tmpinfo->next;
					if(playedinfo)
					{
					#ifdef RFID_DEBUG
					#if defined(__KJX_LOG_OUTPUT__)
						LOGD("���ż�¼��λ�ÿ�ʼ����ǰ��·��ƥ�䣬�����Ӽ�¼��һ��λ�ò���");
					#endif
					#endif

						continue;
					}
					else
					{
					#ifdef RFID_DEBUG
					#if defined(__KJX_LOG_OUTPUT__)
						LOGD("���ż�¼����ǰ��·��ƥ�䣬�����ж���һ����·");
					#endif
					#endif

						break;
					}
				}
			}
		}
	}

	if(flag)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("���ż�¼���%d����·����ɹ�������ǰ��������ʧ�ܣ���������!", k+1);
	#endif
	#endif
		return FALSE;
	}
	else
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("���ż�¼��������·����ƥ�䣬������������");
	#endif
	#endif
		return TRUE;	
	}
}

BOOL kjx_rfid_sequential_infor_add(U8 line_num, char *rfid_id)
{
	U32 i=1;
	KJXDOTINFO *pnew;
	static KJXDOTINFO *head = NULL;

	if(rfid_id == NULL)
	{
	#ifdef RFID_DEBUG	
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("������Ч��ֱ�ӷ���!");
	#endif
	#endif
		return FALSE;
	}
	
	if(g_kjxRfidSequenInfo.LineInfo[line_num].DotInfo == NULL)
	{
		g_kjxRfidSequenInfo.LineInfo[line_num].maxdot = 0;

		media_get_ext_buffer(MOD_MMI, (void **)&head, sizeof(KJXDOTINFO));
		if(head == NULL) 
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ��001���޷����!");
		#endif
		#endif
		
			return FALSE;
		}

		head->rfid_id = atoi(rfid_id);
		head->next = NULL;

		g_kjxRfidSequenInfo.LineInfo[line_num].DotInfo = head;
		g_kjxRfidSequenInfo.LineInfo[line_num].maxdot = 1;

	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("��ӵ�%d����·�ɹ�! ������:%d", line_num+1, g_kjxRfidSequenInfo.LineInfo[line_num].maxdot);
	#endif
	#endif
		
		return TRUE;
	}
	else
	{
		if(head == NULL)
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("����");
		#endif
		#endif
		
			head = g_kjxRfidSequenInfo.LineInfo[line_num].DotInfo;
			while(1)
			{
				if(head->next == NULL)
					break;
				else
					head = head->next;
			}
		}
		
		media_get_ext_buffer(MOD_MMI, (void **)&pnew, sizeof(KJXDOTINFO));
		if(pnew == NULL) 
		{
		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("�ڴ�����ʧ��002���޷����!");
		#endif
		#endif
		
			return FALSE;
		}
		else
		{
			pnew->rfid_id = atoi(rfid_id);
			pnew->next = NULL;

			head->next = pnew;
			head = pnew;//xb add 2017-05-08 ��¼������β

			g_kjxRfidSequenInfo.LineInfo[line_num].maxdot++;

		#ifdef RFID_DEBUG	
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("��ӵ�%d����·�ɹ�! ������:%d", line_num+1, g_kjxRfidSequenInfo.LineInfo[line_num].maxdot);
		#endif
		#endif

			return TRUE;
		}
	}
}

void kjx_rfid_set_triggerinfos(char* infor)
{
	char* temString = NULL;
	char* temString1 = NULL;
	char* myString = NULL;
	int i=0, j=0, k=0;
	U16 file_path_name[2*(MAX_PLAY_NAME_LEN+1)] = {0};
	U16 tmpbuf[2*(MAX_PLAY_NAME_LEN+1)] = {0};
	U32 time = 0;
	U32 linenum = 0;
	mdi_result result;

	g_kjxRfidSequenInfo.maxLine = 0;
	
	temString = NULL;
	temString = kjx_get_parameter_string_only_in_buffer(infor,"|",1);
#ifdef RFID_DEBUG	
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("temString:%s", temString);
#endif
#endif
	if(atoi(temString)>0)
	{
		linenum = atoi(temString);
		if(linenum > MAX_RFID_SEQUENTIAL_LINE)
			linenum = MAX_RFID_SEQUENTIAL_LINE;

	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("linenum:%d", linenum);
	#endif
	#endif
		
		myString = strstr(infor,"|");
		myString += strlen("|");

		for(i=0;i<linenum;i++)
		{
			char rfid_id[MAX_RFID_LEN+1] = {0}; 
			char* sequenString = NULL;
			U32 dot_num = 0;
			U32 len = 0;
		
			temString = NULL;
			temString = kjx_get_parameter_string_only_in_buffer(myString+k,";",1);
			len = strlen(temString);
			media_get_ext_buffer(MOD_MMI, (void **)&sequenString, len+2);
			if(sequenString == NULL)
			{
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("�����ڴ�ʧ��!");
			#endif
			#endif
				return;
			}
			
			memset(sequenString,0x00,len+2);
			memcpy(sequenString,temString,len);
			memcpy(sequenString+len,",",strlen(","));//���Ϸָ�����
			k += len+1;
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("i:%d, k:%d, sequenString:%s", i, k, sequenString);
		#endif
		#endif
		
			temString1 = NULL;
			temString1 = kjx_get_parameter_string_only_in_buffer(sequenString,"^",1);
			dot_num = atoi(temString1);
			temString = strstr(sequenString,"^");
			temString += strlen("^");
			for(j=0;j<dot_num;j++)
			{
				temString1 = NULL;
				temString1 = kjx_get_parameter_string_only_in_buffer(temString,",",j+1);
				len = (MAX_RFID_LEN > strlen(temString1)) ? strlen(temString1) : MAX_RFID_LEN;
				memcpy(rfid_id, temString1, len);
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("i:%d, j:%d, rfid_id:%s", i, j, temString1);
			#endif
			#endif
				if(!kjx_rfid_sequential_infor_add(i, rfid_id))
				{
					break;
				}
			}
			
			if(sequenString != NULL)
			{
				media_free_ext_buffer(MOD_MMI, (void**)&sequenString);
				sequenString = NULL;
			}

			if(MAX_RFID_SEQUENTIAL_PLAYED < dot_num)
				MAX_RFID_SEQUENTIAL_PLAYED = dot_num;
		}

		if(i == linenum)
			g_kjxRfidSequenInfo.maxLine = linenum;
		else
			g_kjxRfidSequenInfo.maxLine = i;

		MAX_RFID_SEQUENTIAL_PLAYED += 1;//��¼����Ҫ�������·�������¼1�����Ա������ж�

	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("MAX_RFID_SEQUENTIAL_PLAYED:%d", MAX_RFID_SEQUENTIAL_PLAYED);
	#endif
	#endif
	}
}

void kjx_rfid_trigger_infos_read(void)
{
	kal_uint32 fs_len;
	FS_HANDLE handle;
	S8 usc2Path[64];
	UINT filesize;

	memset(usc2Path, 0x00, sizeof(usc2Path));	
	kal_wsprintf((WCHAR*) usc2Path, "%c%w", SRV_FMGR_CARD_DRV, AUDIODIR);
	handle = FS_SetCurrentDir((WCHAR*)usc2Path);
	if(handle>=FS_NO_ERROR)
	{
		FS_SetAttributes(AUDIOSEQUENINFO, FS_ATTR_ARCHIVE);
		handle = FS_Open(AUDIOSEQUENINFO, FS_READ_ONLY | FS_ATTR_ARCHIVE); 
		if (handle>=FS_NO_ERROR)
		{
			FS_GetFileSize(handle, &filesize);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("filesize:%d", filesize);
		#endif
		#endif

			if(filesize == 0)
			{
			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("�ļ�����Ϊ��!");
			#endif
			#endif
				FS_Close(handle);
				return;
			}
			
			if(fileString == NULL)
			{
				media_get_ext_buffer(MOD_MMI, (void **)&fileString, filesize+1);
				if(fileString == NULL)
				{
				#ifdef RFID_DEBUG
				#if defined(__KJX_LOG_OUTPUT__)
					LOGD("�����ڴ�ʧ��!");
				#endif
				#endif
					FS_Close(handle);
					return;
				}
			}
			memset(fileString, 0x00, filesize+1);
			FS_Read(handle, (void *)fileString, filesize, &fs_len);
		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("001, fs_len:%d", fs_len);
		#endif
		#endif
			FS_Close(handle);

		#if defined(__KJX_AUDIO_FILE_DECODE__)
			kjx_encode_string(fileString, fs_len);
		#endif

			if(strlen(fileString)>0)
			{
				kjx_rfid_set_triggerinfos(fileString);
			}

			if(fileString != NULL)
			{
				media_free_ext_buffer(MOD_MMI, (void**)&fileString);
				fileString = NULL;
			}
		}
	}
}
#endif

U32 kjx_rfid_em24g(void)
{
	return kjx_rfid_id;
}

U32 kjx_rfid_get_rfid_id(void)
{
	U32 rfid_id = 0;
	
	rfid_id = kjx_rfid_em24g();

	return rfid_id;
}

void kjx_rfid_get_rfid_str(char* strbuf, U32 buflen)
{
	U32 i,rfid_id;

	if(buflen < 1)
	{
		return;
	}
	
	i = buflen-1;
	memset(strbuf, 0, buflen);
	rfid_id = kjx_rfid_em24g();
	while(i>0)
	{
		strbuf[--i] = '0' + rfid_id%10;
		rfid_id = rfid_id/10;
	}

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("strbuf:%s", strbuf);
#endif
#endif	
}

KJXRFIDINFO *kjx_rfid_get_file_id(U32 rfid_num)
{
	U32 get_rfid = 0;
	U32 rfid_id = 0;
	S32 i = 0;
#ifdef __KJX_RFID_LOCATION__
	U32 temp_id = rfid_num%1000000;
#else
	U32 temp_id = rfid_num;
#endif
#ifdef __KJX_TOUR_NAME_STORE_CARD__
	U32 name_id = 0;
#endif
	KJXRFIDINFO *playinfo = NULL;

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("hadRead:%d", hadRead);
#endif
#endif
	if(!hadRead)
	{
		hadRead = TRUE;
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("001");
	#endif
	#endif
		kjx_rfid_play_infos_read();

	#ifdef __KJX_TOUR_NAME_STORE_CARD__
		kjx_rfid_name_infos_read();
	#endif
	}
	
	if(g_kjxRfidPlayInfo.maxID==0)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("002");
	#endif
	#endif
		return NULL;
	}

	playinfo = kjx_rfid_playinfo_find(temp_id);
	if(playinfo)
	{
		get_rfid = 1;
	}

#ifdef __KJX_TOUR_NAME_STORE_CARD__	
    if (get_rfid == 1)
    {
		KJXNAMEINFO *nameinfo = NULL;
	
		nameinfo = kjx_rfid_nameinfo_find(temp_id);
		if(nameinfo)
		{
			memset(kjxTourInfor, 0, sizeof(kjxTourInfor));
			mmi_chset_convert(MMI_CHSET_GB18030, MMI_CHSET_UCS2, (char*)nameinfo->name, (char*)kjxTourInfor, sizeof(kjxTourInfor));
		}
    }
#endif

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("playinfo:%d, rfid_id:%d", playinfo, temp_id);
#endif
#endif

	return playinfo;
}

void kjx_update_play_timer(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
	U32 play_timer;
	mdi_result result;
	static U32 count_time = 0;
	
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	//LOGD("kjx_audio_status:%d", kjx_audio_status);
#endif
#endif

    if(kjx_audio_status == 1)
    {
		result = mdi_audio_get_progress_time(&play_timer); 
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		//LOGD("result:%d, play_timer:%d, duration_time:%d", result, play_timer, kjx_duration_time);
	#endif
	#endif		
	    if((result != MDI_AUDIO_SUCCESS) || (kjx_play_time > kjx_duration_time) || (kjx_duration_time <= 0))
	    {
			play_timer = 0;
	    }

		kjx_play_time = play_timer;
		kjx_audio_time = (kjx_duration_time - kjx_play_time)/1000;			

        StartTimer(KJX_TIMER_ID_SHOW_TIME, 500, kjx_update_play_timer);
    }
}

BOOL kjx_rfid_is_in_play(void)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("kjx_audio_is_playing:%d", kjx_audio_is_playing);
#endif
#endif
	return kjx_audio_is_playing;
}

void kjx_rfid_play_cb_hdlr(S32 result, void *user_data)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("kjx_audio_status:%d", kjx_audio_status);
#endif
#endif

	if(kjx_get_foctory_test_mode() == 1)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("test mode, return");
	#endif
	#endif
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif
		return;
	}

	if(IsMyTimerExist(KJX_TIMER_ID_SHOW_TIME))
		StopTimer(KJX_TIMER_ID_SHOW_TIME);
	
	switch (result)
	{
	case MDI_AUDIO_END_OF_FILE://play completed!
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play completed!");
	#endif
	#endif	
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();
		break;
		
	case MDI_AUDIO_TERMINATED://play terminated
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play terminated!");
	#endif
	#endif
	#if defined(__KJX_RFID_PLAY_CONTINUE_AGAIN__)	//xb add 2016-08-25 ���滹Ҫ���Ų��ţ���Ҫ���
		if(kjx_audio_status == 1)
		{
			kjx_audio_status = 3;
		}
		else
		{
			kjx_audio_is_playing = FALSE;
			kjx_audio_status = 0;
		#ifdef __KJX_TOURIST_MAP_SUPPORT__
			kjx_exit_tour_image();
		#endif
		}
	#else
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif
	#endif
		mdi_audio_stop_file();

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();
		break;
		
	default:
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play error:%d", result);
	#endif
	#endif		
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();		
		break;
	}
}

void kjx_rfid_pause_cb_hdlr(mdi_result result, void *user_data)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("kjx_audio_status:%d", kjx_audio_status);
#endif
#endif

	if(kjx_get_foctory_test_mode() == 1)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("test mode, return");
	#endif
	#endif
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif
		return;
	}

	if(IsMyTimerExist(KJX_TIMER_ID_SHOW_TIME))
		StopTimer(KJX_TIMER_ID_SHOW_TIME);

	switch (result)
	{
	case MDI_AUDIO_END_OF_FILE:
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play completed!");
	#endif
	#endif	
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();
		break;
		
	case MDI_AUDIO_TERMINATED:
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play terminated!");
	#endif
	#endif
	#if defined(__KJX_RFID_PLAY_CONTINUE_AGAIN__)	//xb add 2016-08-25 ���滹Ҫ���Ų��ţ���Ҫ���
		if(kjx_audio_status == 1)
		{
			kjx_audio_status = 3;
		}
		else
		{
			kjx_audio_is_playing = FALSE;
			kjx_audio_status = 0;
		#ifdef __KJX_TOURIST_MAP_SUPPORT__
			kjx_exit_tour_image();
		#endif
		}
	#else
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif
	#endif
		mdi_audio_stop_file();
		break;
		
	default:
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play completed!");
	#endif
	#endif	
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();
		break;
	}
}

void kjx_rfid_resume_cb_hdlr(mdi_result result, void *user_data)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("kjx_audio_status:%d", kjx_audio_status);
#endif
#endif

	if(kjx_get_foctory_test_mode() == 1)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("test mode, return");
	#endif
	#endif

		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif
		
		return;
	}

	if(IsMyTimerExist(KJX_TIMER_ID_SHOW_TIME))
		StopTimer(KJX_TIMER_ID_SHOW_TIME);

	switch (result)
	{
	case MDI_AUDIO_END_OF_FILE:
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play completed!");
	#endif
	#endif	
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();
		break;
		
	case MDI_AUDIO_TERMINATED:
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play terminated!");
	#endif
	#endif
	#if defined(__KJX_RFID_PLAY_CONTINUE_AGAIN__)	//xb add 2016-08-25 ���滹Ҫ���Ų��ţ���Ҫ���
		if(kjx_audio_status == 1)
		{
			kjx_audio_status = 3;
		}
		else
		{
			kjx_audio_is_playing = FALSE;
			kjx_audio_status = 0;
		#ifdef __KJX_TOURIST_MAP_SUPPORT__
			kjx_exit_tour_image();
		#endif
		}
	#else
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif
	#endif
		mdi_audio_stop_file();
		break;
		
	default:
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play completed!");
	#endif
	#endif	
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();
	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_exit_tour_image();
	#endif

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();
		break;
	}
}

void kjx_key_handler_vol_up(void)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

#if defined(__KJX_AGAINST_THEFT__)
	if(g_rfid_against_theft)
		return;
#endif

	g_srv_prof.cur_setting.ring_vol++;
	if(g_srv_prof.cur_setting.ring_vol>7)
	{
		g_srv_prof.cur_setting.ring_vol = 7;
	}

	if (srv_ucm_query_call_count(SRV_UCM_INCOMING_STATE, SRV_UCM_CALL_TYPE_ALL, NULL) > 0)
	{
		mmi_vol_set_ring_vol((U8)g_srv_prof.cur_setting.ring_vol);
	}
	else if (srv_ucm_query_call_count(SRV_UCM_CALL_STATE_ALL, SRV_UCM_CALL_TYPE_ALL, NULL) > 0 &&
			 srv_ucm_query_call_count(SRV_UCM_CALL_STATE_ALL, SRV_UCM_CSD_CALL_TYPE_ALL, NULL) <= 0)
	{
		srv_speech_save_mode_volume((U8)MDI_AUD_VOL_MUTE(g_srv_prof.cur_setting.ring_vol));
	}
	else
	{
		mdi_audio_set_volume(VOL_TYPE_MEDIA, (U8)(MDI_AUD_VOL_MUTE(g_srv_prof.cur_setting.ring_vol)));
	}
}

void kjx_key_handler_vol_down(void)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

#if defined(__KJX_AGAINST_THEFT__)
	if(g_rfid_against_theft)
		return;
#endif

	g_srv_prof.cur_setting.ring_vol--;
	if(g_srv_prof.cur_setting.ring_vol<=0)
	{
		g_srv_prof.cur_setting.ring_vol = 0;
	}

	if (srv_ucm_query_call_count(SRV_UCM_INCOMING_STATE, SRV_UCM_CALL_TYPE_ALL, NULL) > 0)
	{
		mmi_vol_set_ring_vol((U8)g_srv_prof.cur_setting.ring_vol);
	}
	else if (srv_ucm_query_call_count(SRV_UCM_CALL_STATE_ALL, SRV_UCM_CALL_TYPE_ALL, NULL) > 0 &&
			 srv_ucm_query_call_count(SRV_UCM_CALL_STATE_ALL, SRV_UCM_CSD_CALL_TYPE_ALL, NULL) <= 0)
	{
		srv_speech_save_mode_volume((U8)MDI_AUD_VOL_MUTE(g_srv_prof.cur_setting.ring_vol));
	}
	else
	{
		mdi_audio_set_volume(VOL_TYPE_MEDIA, (U8)(MDI_AUD_VOL_MUTE(g_srv_prof.cur_setting.ring_vol)));
	}
}

void kjx_key_handler_extra_a(void)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif
}

void kjx_key_handler_end(void)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif
}

void kjx_rfid_continue_play_audio(void)
{
	U16 file_path_name[2*(MAX_PLAY_NAME_LEN+1)];
	U16 tmpbuf[2*(MAX_PLAY_NAME_LEN+1)] = {0};
	FS_HANDLE handle;
	S32 result = 0;
	S32 file_id = -1;
	KJXRFIDINFO *playinfo = NULL;
	
	playinfo = kjx_rfid_get_file_id(last_id);
	if(playinfo == NULL)
    {
        return;
    }
	
	if(kjx_rfid_is_in_play())
	{
		kjx_rfid_stop_play_audio();
	}

	memset(file_path_name,0,sizeof(file_path_name));
	kal_wsprintf((WCHAR*) file_path_name, "%c%w", SRV_FMGR_CARD_DRV, AUDIODIR);
#ifdef __KJX_MULTI_LANGUAGE__
	switch(g_kjx_language)
	{
	case LANG_ENGLISH:				//Ӣ
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ENGLISH);
		break;
	case LANG_FRENCH:				//��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FRENCH);
		break;
	case LANG_GERMAN:				//��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_GERMAN);
		break;
	case LANG_ITALIAN:				//�����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ITALIAN);
		break;
	case LANG_SPANISH:				//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_SPANISH);
		break;
	case LANG_PORTUGUESE:			//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_PORTUGUESE);
		break;
	case LANG_POLISH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_POLISH);
		break;
	case LANG_DANISH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_DANISH);
		break;
	case LANG_SWEDISH:				//���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_SWEDISH);
		break;
	case LANG_NORWEGIAN:			//Ų��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_NORWEGIAN);
		break;
	case LANG_FINNISH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FINNISH);
		break;
	case LANG_DUTCH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_DUTCH);
		break;
	case LANG_UKRAINIAN:			//�ڿ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_UKRAINIAN);
		break;
	case LANG_RUSSIAN:				//����˹
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_RUSSIAN);
		break;
	case LANG_GREEK:				//ϣ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_GREEK);
		break;
	case LANG_TURKISH:				//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_TURKISH);
		break;
	case LANG_ARABIC:				//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ARABIC);
		break;
	case LANG_HEBREW:				//ϣ������(��ɫ��)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_HEBREW);
		break;
	case LANG_PERSIAN:				//��˹��(����)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_PERSIAN);
		break;
	case LANG_URDU: 				//�ڶ�����(�ͻ�˹̹)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_URDU);
		break;
	case LANG_HINDI:				//ӡ����(ӡ��)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_HINDI);
		break;
	case LANG_BENGALI:				//�ϼ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_BENGALI);
		break;
	case LANG_LAO:					//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_LAO);
		break;
	case LANG_KHMER:				//������(����կ)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_KHMER);
		break;
	case LANG_MYANMAR:				//���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_MYANMAR);
		break;
	case LANG_VIETNAMESE:			//Խ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_VIETNAMESE);
		break;
	case LANG_INDONESIAN:			//ӡ��������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_INDONESIAN);
		break;
	case LANG_MALAY:				//������(��������,����)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_MALAY);
		break;
	case LANG_THAI: 				//̩��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_THAI);
		break;
	case LANG_FILIPINO: 			//���ɱ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FILIPINO);
		break;
	case LANG_KOREAN:				//������(����,����)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_KOREAN);
		break;
	case LANG_JAPANESE: 			//�ձ�
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_JAPANESE);
		break;
	case LANG_CHN:					//������ͨ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN);
		break;
	case LANG_CHN_SC:				//�����Ĵ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_SC);
		break;
	case LANG_CHN_GD:				//���Ĺ㶫��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_GD);
		break;
	case LANG_CHN_MN:				//�������ϻ�
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_MN);
		break;
	case LANG_CHN_XZ:				//���Ĳ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ);
		break;
	case LANG_CHN_XZ_LASA:				//���Ĳ�������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_LASA);
		break;
	case LANG_CHN_XZ_ANDUO:				//���Ĳ��ﰲ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_ANDUO);
		break;
	case LANG_CHN_XZ_KANGBA:			//���Ĳ��￵��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_KANGBA);
		break;
	case LANG_CHN_EXTRA:			//������������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_EXTRA);
		break;
	}	
#endif
	mmi_chset_convert(MMI_CHSET_GB18030, MMI_CHSET_UCS2, playinfo->file_name, (char*)tmpbuf, sizeof(tmpbuf));
	mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)tmpbuf);
	
	handle = FS_Open((const unsigned short *) file_path_name, FS_READ_ONLY);
	if(handle<0)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("(handle<0) return");
	#endif
	#endif
		FS_Close(handle);
		return;
	}
	FS_Close(handle);

	kjx_audio_time = (kjx_duration_time - kjx_play_time)/1000;
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("kjx_play_time:%d", kjx_play_time);
#endif
#endif
	result = mdi_audio_play_file_portion_with_vol_path(
					   file_path_name,
					   kjx_play_time,
					   kjx_duration_time,
					   DEVICE_AUDIO_PLAY_ONCE,
					   NULL,
					   kjx_rfid_play_cb_hdlr,
					   NULL,
		   				(U8)srv_prof_get_ring_vol(),
					   MDI_DEVICE_SPEAKER2);
	
	if(result == MDI_AUDIO_SUCCESS)//xb add 2016-08-24	���ųɹ�
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play success!");
	#endif
	#endif
		
		kjx_audio_is_playing = TRUE;
		kjx_audio_status = 1;
		kjx_update_play_timer();

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_ucs2cpy((CHAR*)kjx_scrolling_show, (CHAR*)kjxTourInfor);
		mmi_show_scrolling_infor();

		srv_backlight_turn_on(SRV_BACKLIGHT_SHORT_TIME);//xb add 20106-09-07 ������Ļ
	}
	else
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play fail!result:%d", result);
	#endif
	#endif

		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
	}
}

void kjx_rfid_pause_play_audio(void)
{
	mdi_result result;

	result = mdi_audio_pause(kjx_rfid_pause_cb_hdlr, NULL);
	if(result == MDI_AUDIO_SUCCESS)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("paush success!");
	#endif
	#endif
	
		kjx_audio_is_playing = TRUE;
		kjx_audio_status = 2;

		if(IsMyTimerExist(KJX_TIMER_ID_SHOW_TIME))
			StopTimer(KJX_TIMER_ID_SHOW_TIME);
	}
	else if(result == MDI_AUDIO_UNSUPPORTED_OPERATION)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("paush unsupported opreation!");
	#endif
	#endif	
	}
	else
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("paush fail, result:%d", result);
	#endif
	#endif	
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();
	}
}

void kjx_rfid_resume_play_audio(void)
{
	mdi_result result;

	result = mdi_audio_resume(kjx_rfid_resume_cb_hdlr, NULL);
	if(result == MDI_AUDIO_SUCCESS)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("resume success!");
	#endif
	#endif

		kjx_audio_is_playing = TRUE;
		kjx_audio_status = 1;
		
		kjx_update_play_timer();
	}
	else if (result == MDI_AUDIO_END_OF_FILE)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("resume play completed!");
	#endif
	#endif	
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();
	}
	else
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("resume fail!result:%d", result);
	#endif
	#endif		

		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
		mdi_audio_stop_file();

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();
	}
}

void kjx_rfid_stop_play_audio(void)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

	kjx_audio_is_playing = FALSE;
	kjx_audio_status = 0;
	mdi_audio_stop_file();

#if defined(__NPR_TTS__)
	if(Npr_Tts_is_playing())
	{
		Npr_Tts_play_stop();
		kjx_tts_play_is_stop = TRUE;
	}
#endif
}

void kjx_rfid_play_key_handler(void)
{
	if(!kjx_is_in_call()
		#ifdef __KJX_AGAINST_THEFT__
			&& !g_rfid_against_theft
		#endif
		)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("kjx_audio_status:%d", kjx_audio_status);
	#endif
	#endif
		switch(kjx_audio_status)
		{
		case 0://û�в��Ż��߲��Ž���
			kjx_rfid_play_audio_again();
			break;
		case 1://���ڲ���
			kjx_rfid_pause_play_audio();
			break;
		case 2://��ͣ����
			kjx_rfid_resume_play_audio();
			break;
		}
	}
}


void kjx_rfid_play_audio_again(void)
{
	U16 file_path_name[2*(MAX_PLAY_NAME_LEN+1)];
	U16 tmpbuf[2*(MAX_PLAY_NAME_LEN+1)] = {0};
	FS_HANDLE handle;
	S32 result = 0;
	S32 file_id = -1;
	KJXRFIDINFO *playinfo = NULL;

	if(srv_ucm_query_call_count(SRV_UCM_CALL_STATE_ALL, SRV_UCM_CALL_TYPE_ALL, NULL) > 0)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("is in call return");
	#endif
	#endif
		return;
	}

	playinfo = kjx_rfid_get_file_id(last_id);
	if (playinfo == NULL)
    {
        return;
    }

	if(kjx_rfid_is_in_play() )
	{
		kjx_rfid_stop_play_audio();
	}
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("file_name:%s", playinfo->file_name);
#endif
#endif

	memset(file_path_name,0,sizeof(file_path_name));
	kal_wsprintf((WCHAR*) file_path_name, "%c%w", SRV_FMGR_CARD_DRV, AUDIODIR);
#ifdef __KJX_MULTI_LANGUAGE__
	switch(g_kjx_language)
	{
	case LANG_ENGLISH:				//Ӣ
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ENGLISH);
		break;
	case LANG_FRENCH:				//��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FRENCH);
		break;
	case LANG_GERMAN:				//��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_GERMAN);
		break;
	case LANG_ITALIAN:				//�����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ITALIAN);
		break;
	case LANG_SPANISH:				//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_SPANISH);
		break;
	case LANG_PORTUGUESE:			//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_PORTUGUESE);
		break;
	case LANG_POLISH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_POLISH);
		break;
	case LANG_DANISH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_DANISH);
		break;
	case LANG_SWEDISH:				//���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_SWEDISH);
		break;
	case LANG_NORWEGIAN:			//Ų��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_NORWEGIAN);
		break;
	case LANG_FINNISH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FINNISH);
		break;
	case LANG_DUTCH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_DUTCH);
		break;
	case LANG_UKRAINIAN:			//�ڿ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_UKRAINIAN);
		break;
	case LANG_RUSSIAN:				//����˹
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_RUSSIAN);
		break;
	case LANG_GREEK:				//ϣ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_GREEK);
		break;
	case LANG_TURKISH:				//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_TURKISH);
		break;
	case LANG_ARABIC:				//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ARABIC);
		break;
	case LANG_HEBREW:				//ϣ������(��ɫ��)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_HEBREW);
		break;
	case LANG_PERSIAN:				//��˹��(����)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_PERSIAN);
		break;
	case LANG_URDU: 				//�ڶ�����(�ͻ�˹̹)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_URDU);
		break;
	case LANG_HINDI:				//ӡ����(ӡ��)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_HINDI);
		break;
	case LANG_BENGALI:				//�ϼ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_BENGALI);
		break;
	case LANG_LAO:					//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_LAO);
		break;
	case LANG_KHMER:				//������(����կ)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_KHMER);
		break;
	case LANG_MYANMAR:				//���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_MYANMAR);
		break;
	case LANG_VIETNAMESE:			//Խ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_VIETNAMESE);
		break;
	case LANG_INDONESIAN:			//ӡ��������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_INDONESIAN);
		break;
	case LANG_MALAY:				//������(��������,����)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_MALAY);
		break;
	case LANG_THAI: 				//̩��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_THAI);
		break;
	case LANG_FILIPINO: 			//���ɱ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FILIPINO);
		break;
	case LANG_KOREAN:				//������(����,����)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_KOREAN);
		break;
	case LANG_JAPANESE: 			//�ձ�
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_JAPANESE);
		break;
	case LANG_CHN:					//������ͨ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN);
		break;
	case LANG_CHN_SC:				//�����Ĵ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_SC);
		break;
	case LANG_CHN_GD:				//���Ĺ㶫��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_GD);
		break;
	case LANG_CHN_MN:				//�������ϻ�
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_MN);
		break;
	case LANG_CHN_XZ:				//���Ĳ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ);
		break;
	case LANG_CHN_XZ_LASA:				//���Ĳ�������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_LASA);
		break;
	case LANG_CHN_XZ_ANDUO:				//���Ĳ��ﰲ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_ANDUO);
		break;
	case LANG_CHN_XZ_KANGBA:			//���Ĳ��￵��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_KANGBA);
		break;
	case LANG_CHN_EXTRA:			//������������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_EXTRA);
		break;
	}	
#endif
	mmi_chset_convert(MMI_CHSET_GB18030, MMI_CHSET_UCS2, playinfo->file_name, (char*)tmpbuf, sizeof(tmpbuf));
	mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)tmpbuf);

	handle = FS_Open((const unsigned short *) file_path_name, FS_READ_ONLY);
	if(handle<0)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("(handle<0) return");
	#endif
	#endif
		FS_Close(handle);
		return;
	}
	FS_Close(handle);

	if(playinfo->durtime == 0)
	{
		U8 j;
		U32 time = 0;

		for(j=0;j<MAX_TRY_GET_DURATION;j++)
		{
			result = mdi_audio_get_duration(file_path_name, &time);
			if(result == MDI_AUDIO_SUCCESS)
			{
				playinfo->durtime = time;
				break;
			}
		}
	}

	kjx_duration_time = playinfo->durtime;
	kjx_get_duration = 0;
	kjx_audio_time = kjx_duration_time/1000;

	result = mdi_audio_play_file(file_path_name, DEVICE_AUDIO_PLAY_ONCE, NULL, kjx_rfid_play_cb_hdlr, NULL);
	if(result == MDI_AUDIO_SUCCESS)//xb add 2016-08-24	���ųɹ�
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play success!");
	#endif
	#endif
		
		kjx_audio_is_playing = TRUE;
		kjx_audio_status = 1;
		kjx_update_play_timer();

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_ucs2cpy((CHAR*)kjx_scrolling_show, (CHAR*)kjxTourInfor);
		mmi_show_scrolling_infor();

		srv_backlight_turn_on(SRV_BACKLIGHT_SHORT_TIME);//xb add 20106-09-07 ������Ļ
	}
	else
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play fail!result:%d", result);
	#endif
	#endif

		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
	}
}

void kjx_play_mp3(void)
{
	U16 file_path_name[2*(MAX_PLAY_NAME_LEN+1)];
	S32 result = 0;

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

	memset(file_path_name,0,sizeof(file_path_name));
	kal_wsprintf((WCHAR*) file_path_name, "%c%w", SRV_FMGR_CARD_DRV, L":\\Audio\\00000000.mp3");
	result = mdi_audio_play_file(file_path_name, DEVICE_AUDIO_PLAY_ONCE, NULL, kjx_rfid_play_cb_hdlr, NULL);
	if(result == MDI_AUDIO_SUCCESS)//xb add 2016-08-24	���ųɹ�
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play success!");
	#endif
	#endif
		
		kjx_audio_is_playing = TRUE;
		kjx_audio_status = 1;

		srv_backlight_turn_on(SRV_BACKLIGHT_SHORT_TIME);//xb add 20106-09-07 ������Ļ
	}
	else
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play fail!result:%d", result);
	#endif
	#endif

		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
	}
}

applib_time_struct first_Time = {0};

extern void kjx_factory_rfid_test_end(void);
void kjx_rfid_play_audio(void)
{
	U16 file_path_name[2*(MAX_PLAY_NAME_LEN+1)];
	U16 tmpbuf[2*(MAX_PLAY_NAME_LEN+1)] = {0};
	FS_HANDLE handle;
	S32 result = 0;
	S32 file_id = -1;
	KJXRFIDINFO *playinfo = NULL;
	U8 *ptr1,*ptr2;

	StopTimer(KJX_TIMER_ID_PLAY_AUDIO);

	playinfo = kjx_rfid_get_file_id(kjx_rfid_id);
	if (playinfo == NULL)
    {
	#if defined(__KJX_SERVER_CMD_PLAY__)
		g_server_play_result = 3;
	#endif
		return;
    }

#if defined(__KJX_SERVER_CMD_PLAY__)
	g_server_play_result = 1;
#endif

#if defined(__KJX_RESET_USED_COUNT__)
	g_rfid_has_playing = TRUE;
#endif

	if(srv_ucm_query_call_count(SRV_UCM_CALL_STATE_ALL, SRV_UCM_CALL_TYPE_ALL, NULL) > 0)
	{
	#if defined(__KJX_SERVER_CMD_PLAY__)
		mmi_ucm_end_all_action();
		StartTimer(KJX_TIMER_ID_PLAY_AUDIO, 500, kjx_rfid_play_audio);
		return;
	#endif
	
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("is in call return");
	#endif
	#endif
		return;
	}
	
	if((last_id != atoi(playinfo->rfid_id)) || (kjx_get_foctory_test_mode() == 1)	//xb add 2016-11-08 ��������ģʽ�����β���ͬһ��Ƶ
		#if defined(__KJX_SERVER_CMD_PLAY__)
			||(g_play_cause == 2)	//xb add 2017-02-24 ��ָ̨�������β���ͬһ�ļ�
		#endif
		)
	{
		if(kjx_rfid_is_in_play())
			kjx_rfid_stop_play_audio();
	}
	else
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("002");
	#endif
	#endif
		return;
	}

	last_id = atoi(playinfo->rfid_id);

#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
	kjx_rfid_sequential_played_infor_add((U32)last_id);
#endif

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("file_name:%s", playinfo->file_name);
#endif
#endif

	memset(file_path_name,0,sizeof(file_path_name));
	kal_wsprintf((WCHAR*) file_path_name, "%c%w", SRV_FMGR_CARD_DRV, AUDIODIR);
#ifdef __KJX_MULTI_LANGUAGE__
	switch(g_kjx_language)
	{
	case LANG_ENGLISH:				//Ӣ
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ENGLISH);
		break;
	case LANG_FRENCH:				//��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FRENCH);
		break;
	case LANG_GERMAN:				//��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_GERMAN);
		break;
	case LANG_ITALIAN:				//�����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ITALIAN);
		break;
	case LANG_SPANISH:				//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_SPANISH);
		break;
	case LANG_PORTUGUESE:			//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_PORTUGUESE);
		break;
	case LANG_POLISH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_POLISH);
		break;
	case LANG_DANISH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_DANISH);
		break;
	case LANG_SWEDISH:				//���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_SWEDISH);
		break;
	case LANG_NORWEGIAN:			//Ų��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_NORWEGIAN);
		break;
	case LANG_FINNISH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FINNISH);
		break;
	case LANG_DUTCH:				//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_DUTCH);
		break;
	case LANG_UKRAINIAN:			//�ڿ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_UKRAINIAN);
		break;
	case LANG_RUSSIAN:				//����˹
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_RUSSIAN);
		break;
	case LANG_GREEK:				//ϣ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_GREEK);
		break;
	case LANG_TURKISH:				//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_TURKISH);
		break;
	case LANG_ARABIC:				//������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_ARABIC);
		break;
	case LANG_HEBREW:				//ϣ������(��ɫ��)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_HEBREW);
		break;
	case LANG_PERSIAN:				//��˹��(����)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_PERSIAN);
		break;
	case LANG_URDU: 				//�ڶ�����(�ͻ�˹̹)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_URDU);
		break;
	case LANG_HINDI:				//ӡ����(ӡ��)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_HINDI);
		break;
	case LANG_BENGALI:				//�ϼ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_BENGALI);
		break;
	case LANG_LAO:					//����
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_LAO);
		break;
	case LANG_KHMER:				//������(����կ)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_KHMER);
		break;
	case LANG_MYANMAR:				//���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_MYANMAR);
		break;
	case LANG_VIETNAMESE:			//Խ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_VIETNAMESE);
		break;
	case LANG_INDONESIAN:			//ӡ��������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_INDONESIAN);
		break;
	case LANG_MALAY:				//������(��������,����)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_MALAY);
		break;
	case LANG_THAI: 				//̩��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_THAI);
		break;
	case LANG_FILIPINO: 			//���ɱ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_FILIPINO);
		break;
	case LANG_KOREAN:				//������(����,����)
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_KOREAN);
		break;
	case LANG_JAPANESE: 			//�ձ�
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_JAPANESE);
		break;
	case LANG_CHN:					//������ͨ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN);
		break;
	case LANG_CHN_SC:				//�����Ĵ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_SC);
		break;
	case LANG_CHN_GD:				//���Ĺ㶫��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_GD);
		break;
	case LANG_CHN_MN:				//�������ϻ�
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_MN);
		break;
	case LANG_CHN_XZ:				//���Ĳ���
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ);
		break;
	case LANG_CHN_XZ_LASA:				//���Ĳ�������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_LASA);
		break;
	case LANG_CHN_XZ_ANDUO:				//���Ĳ��ﰲ��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_ANDUO);
		break;
	case LANG_CHN_XZ_KANGBA:			//���Ĳ��￵��
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_XZ_KANGBA);
		break;
	case LANG_CHN_EXTRA:			//������������
		mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)AUDIODIR_LANG_CHN_EXTRA);
		break;
	}	
#endif
	
	mmi_chset_convert(MMI_CHSET_GB18030, MMI_CHSET_UCS2, playinfo->file_name, (char*)tmpbuf, sizeof(tmpbuf));
	mmi_ucs2cat((CHAR*)file_path_name, (CHAR*)tmpbuf);

	handle = FS_Open((const unsigned short *) file_path_name, FS_READ_ONLY);
	if(handle<0)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("(handle<0) return");
	#endif
	#endif
		FS_Close(handle);
		return;
	}
	FS_Close(handle);
	
    playinfo->played = 1;
	
	if(playinfo->durtime == 0)
	{
		U8 j;
		U32 time = 0;
		
		for(j=0;j<MAX_TRY_GET_DURATION;j++)
		{
			result = mdi_audio_get_duration(file_path_name, &time);
			if(result == MDI_AUDIO_SUCCESS)
			{
				playinfo->durtime = time;
				break;
			}
		}
	}
	
	kjx_duration_time = playinfo->durtime;
	kjx_get_duration = 0;
	kjx_audio_time = kjx_duration_time/1000;
	
	result = mdi_audio_play_file(file_path_name, DEVICE_AUDIO_PLAY_ONCE, NULL, kjx_rfid_play_cb_hdlr, NULL);
	if(result == MDI_AUDIO_SUCCESS)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play success! kjx_audio_time:%d", kjx_audio_time);
	#endif
	#endif

		g_rfid_played_id = last_id;
		kjx_audio_is_playing = TRUE;
		kjx_audio_status = 1;
		kjx_update_play_timer();

		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_ucs2cpy((CHAR*)kjx_scrolling_show, (CHAR*)kjxTourInfor);
		mmi_show_scrolling_infor();

		mmi_redraw_idlescreen();
		
		srv_backlight_turn_on(SRV_BACKLIGHT_SHORT_TIME);//xb add 20106-09-07 ������Ļ

	#ifdef __KJX_TOURIST_MAP_SUPPORT__
		kjx_show_tour_image();
	#endif
	}
	else
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("play fail!result:%d", result);
	#endif
	#endif
	
		kjx_audio_is_playing = FALSE;
		kjx_audio_status = 0;
	}
}
 
void kjx_rfid_check_id(void)
{
	static BOOL firstInto = TRUE;
	static BOOL audioInit = TRUE;
#if defined(__KJX_RESET_USED_COUNT__)
	static U8 count_flag = 0;//����ƴεı�ǣ�0:����׼�� 1:�Ѿ���λ������ʼͳ�� 
	KJXRECORDINFO *pRec, *pCfg;
#endif
	U32 currID = 0;

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

	if(g_kjx_current_dj_or_rfid_mode == 1)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("is dj mode,return!");
	#endif
	#endif
		return;
	}
	
	if(!firstInto)
	{
		g_rfid_test_timer = TRUE;
	}

	firstInto = FALSE;

	currID = kjx_rfid_get_rfid_id();
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("currID:%d, myID:%d", currID, myID);
#endif
#endif

	if(currID != 0)
	{
	#ifdef __KJX_RFID_LOCATION__
		U32 temp_id = currID%1000000;
	#else
		U32 temp_id = currID;
	#endif
	
		if(myID == 0)
		{
			myID = currID;
		#if defined(__KJX_RESET_USED_COUNT__)
			if(kjx_get_foctory_test_mode() == 0)
			{
				U8 i;

				if(g_kjx_nvram_struct.useflag == 0)
				{
					g_kjx_nvram_struct.useflag = 1;
					count_flag = 0;//׼���µ�һ��ʹ�üƴ�
					kjx_nvram_write();
				}

				for(i=0;i<RFID_NUM_MAX;i++)
				{
					if(rfid_num[i] == 0)
						break;
				}
				rfid_num[i] = temp_id;
				rfid_count = i+1;				

			#ifdef RFID_DEBUG
			#if defined(__KJX_LOG_OUTPUT__)
				LOGD("001 useflag:%d, count_flag:%d, rfid_count:%d", g_kjx_nvram_struct.useflag, count_flag, rfid_count);
			#endif
			#endif
				pCfg = kjx_rfid_playrec_find(1, temp_id);
				if(pCfg && (pCfg->count > 0))
				{
					pRec = kjx_rfid_playrec_find(0, temp_id);
					if(pRec && (pRec->count + 1 > pCfg->count))
					{
					#ifdef RFID_DEBUG
					#if defined(__KJX_LOG_OUTPUT__)
						LOGD("�Ѿ��ﵽ��󲥷Ŵ�������!");
					#endif
					#endif
						g_rfid_has_playing = FALSE;
					}
					else
					{
					#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
						if(kjx_rfid_sequential_infor_check(temp_id))
					#endif
						{
							g_rfid_has_playing = TRUE;
							kjx_rfid_playrec_update(temp_id, 1);
							kjx_rfid_play_audio();
						}
					}
				}
				else
				{
				#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
					if(kjx_rfid_sequential_infor_check(temp_id))
				#endif
					{
						g_rfid_has_playing = TRUE;
						kjx_rfid_playrec_update(temp_id, 1);
						kjx_rfid_play_audio();
					}
				}
			}
			else
			{
			#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
				if(kjx_rfid_sequential_infor_check(temp_id))
			#endif
				{
					g_rfid_has_playing = TRUE;
					kjx_rfid_play_audio();			
				}
			}
		#else	
		  #ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
			if(kjx_rfid_sequential_infor_check(temp_id))
		  #endif
		  	{
				kjx_rfid_play_audio();
		  	}
		#endif
		
			if(kjx_get_foctory_test_mode() == 0)
            {
			#if defined(__KJX_POSITION_TRIGGER_PLAY__)
				if(g_play_cause == 1)
				{
					//xb add 2017-11-01 ��ʱһ�ᣬ���豸�ȴ𸴺�̨�Ѿ��յ�ָ��,��ñ�Ǳ����
					StartTimer(KJX_TIMER_ID_SEND_POSITION_TRIGGER_RFID, 1000, kjx_handle_send_position_trigger_data);
				}
				else
			#endif
				{
				#if defined(__KJX_SERVER_CMD_PLAY__)
					if(g_play_cause != 2)
				#endif
		            	kjx_handle_send_rfid_data();
				}
			}
		}
		else
		{
			if((currID != myID)
			#if defined(__KJX_SERVER_CMD_PLAY__)
				|| (g_play_cause == 2)
			#endif
			)
			{/*ֹͣ��ǰ�����ļ������ŵ�ǰID��Ӧ�ļ�*/
				myID = currID;
			#if defined(__KJX_RESET_USED_COUNT__)
				if(kjx_get_foctory_test_mode() == 0)
				{
					U8 i;

					if(g_kjx_nvram_struct.useflag == 0)
					{
						g_kjx_nvram_struct.useflag = 1;
						count_flag = 0;//׼���µ�һ��ʹ�üƴ�
						kjx_nvram_write();
					}

					for(i=0;i<rfid_count;i++)
					{
						if(rfid_num[i] == temp_id)
							break;
					}

					if((i == rfid_count)&&(rfid_count < RFID_NUM_MAX))
					{
						rfid_num[rfid_count] = temp_id;
						rfid_count += 1;
					}

					if((count_flag == 0) && (rfid_count >= RFID_NUM_CAUSE_RUC))
					{
						count_flag = 1;//���ʹ�õļƴ�
						g_kjx_nvram_struct.usecount++;
						kjx_nvram_write();
					}			

				#ifdef RFID_DEBUG
				#if defined(__KJX_LOG_OUTPUT__)
					LOGD("002 useflag:%d, count_flag:%d, rfid_count:%d", g_kjx_nvram_struct.useflag, count_flag, rfid_count);
				#endif
				#endif
					
					pCfg = kjx_rfid_playrec_find(1, temp_id);
					if(pCfg && (pCfg->count > 0))
					{
						pRec = kjx_rfid_playrec_find(0, temp_id);
						if(pRec && (pRec->count + 1 > pCfg->count))
						{
						#ifdef RFID_DEBUG
						#if defined(__KJX_LOG_OUTPUT__)
							LOGD("�Ѿ��ﵽ��󲥷Ŵ�������!");
						#endif
						#endif
							g_rfid_has_playing = FALSE;
						}
						else
						{
						#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
						  	if(kjx_rfid_sequential_infor_check(temp_id))
						#endif
							{
								g_rfid_has_playing = TRUE;
								kjx_rfid_playrec_update(temp_id, 1);
								kjx_rfid_play_audio();
							}
						}
					}
					else
					{
					#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
					  	if(kjx_rfid_sequential_infor_check(temp_id))
					#endif
						{
							g_rfid_has_playing = TRUE;
							kjx_rfid_playrec_update(temp_id, 1);
							kjx_rfid_play_audio();
						}
					}
				}
				else
				{
				#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
				  	if(kjx_rfid_sequential_infor_check(temp_id))
				#endif
					{
						g_rfid_has_playing = TRUE;
						kjx_rfid_play_audio();
					}
				}
			#else
			  #ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
			  	if(kjx_rfid_sequential_infor_check(temp_id))
			  #endif
				{
					kjx_rfid_play_audio();
			  	}
			#endif

				if(kjx_get_foctory_test_mode() == 0)
				{
				#if defined(__KJX_POSITION_TRIGGER_PLAY__)
					if(g_play_cause == 1)
					{
						//xb add 2017-11-01 ��ʱһ�ᣬ���豸�ȴ𸴺�̨�Ѿ��յ�ָ��,��ñ�Ǳ����
						StartTimer(KJX_TIMER_ID_SEND_POSITION_TRIGGER_RFID, 1000, kjx_handle_send_position_trigger_data);
					}
					else
				#endif
					{
					#if defined(__KJX_SERVER_CMD_PLAY__)
						if(g_play_cause != 2)
					#endif
       		         		kjx_handle_send_rfid_data();
					}
				}
			}
		}
	}
}

void kjx_rfid_main(void)
{
	static U16 playTotal = 0;
	static BOOL firstInto = TRUE;
	//�𾴵��οͣ����ã��������е����������ο�״̬δ���
	char playString[]={0xa,0x5c,0x6c,0x65,0x84,0x76,0x38,0x6e,0xa2,0x5b,0xc,0xff,0xa8,0x60,0x7d,0x59,0x1,0xff,0xa8,0x60,0x40,0x62,0x1,0x63,0x9,0x67,0x84,0x76,0x7a,0x66,0x38,0x6e,0x1f,0x66,0xc5,0x65,0x38,0x6e,0x61,0x53,0xb6,0x72,0x1,0x60,0x2a,0x67,0xc0,0x6f,0x3b,0x6d,0x1,0xff,0x0,0x0};
	
	StopTimer(KJX_TIMER_ID_RFID_MAIN);
	
	if(!firstInto)
	{
		g_rfid_test_timer = TRUE;
	}

	firstInto = FALSE;
	
	if(kjx_rfid_will_stop_work())
	{
	#if defined(__NPR_TTS__)
	 	if(!playTotal)
	 	{
	 		playTotal = 1;
		 	Npr_Tts_play_stop();
		 	Npr_Ttsplayer_playtextw(playString,NULL);
	 	}
	#endif

		StartTimer(KJX_TIMER_ID_RFID_MAIN,1000*30, kjx_rfid_main);
		return;
	}
	
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

	kjx_rfid_uart_init();
}
/*#############################################################*/
#endif

#if defined(BLOCK_WITH_VOICE_PUSH)
/*#############################################################*/
/*��������*/
/*#############################################################*/
void kjx_voice_push_and_play(void)
{
	extern S8 kjxPlayTts[];

#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

	StopTimer(KJX_TIMER_ID_PLAY_TTS);

#if defined(__KJX_AGAINST_THEFT__)
	if(g_rfid_against_theft)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("����״̬����������������");
	#endif
	#endif

		return;
	}
#endif

	if(kjx_tts_play_is_stop)
	{
	#ifdef RFID_DEBUG
	#if defined(__KJX_LOG_OUTPUT__)
		LOGD("return kjx_tts_play_is_stop");
	#endif
	#endif
	
		TTsPlayRepeat = 0;
		return;
	}
	
	if(Npr_Tts_is_playing())
	{
		StartTimer(KJX_TIMER_ID_PLAY_TTS, 5000,kjx_voice_push_and_play);
		return;
	}
	
	memset(TtsPlayString,0,sizeof(TtsPlayString));
	mmi_chset_utf8_to_ucs2_string((kal_uint8 *)TtsPlayString, sizeof(TtsPlayString), kjxPlayTts);

	if(mmi_ucs2strlen((const CHAR *)TtsPlayString)>0)
	{
		if(kjx_rfid_is_in_play())
		{
			mdi_audio_stop_file();//xb add 2016-09-25 ��ʱ�ж�RFID���ţ����滹Ҫ��������
		}
	
		srv_vibrator_on();
		StartTimer(KJX_TIMER_ID_PLAY_TTS_AFTER, 3000,kjx_set_with_play_tts);
	}
}

/*****************************************************************************
* FUNCTION
*  	Npr_Ttsplayer_play_cb_hdlr
* DESCRIPTION
*   TTS���Ž����ص�֪ͨ
* PARAMETERS
*
* RETURNS
*	none
* 
* Author
*   xiebiao 2016-08-25
*****************************************************************************/
void Npr_Ttsplayer_play_cb_hdlr(void *info)
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("kjx_audio_status:%d, TTsPlayRepeat:%d", kjx_audio_status, TTsPlayRepeat);
#endif
#endif

	if(TTsPlayRepeat > 0)
	{
		StartTimer(KJX_TIMER_ID_PLAY_TTS, 5000,kjx_voice_push_and_play);
	}
	else
	{
		TTsPlayRepeat = 0;
		memset(TtsPlayString,0,sizeof(TtsPlayString));	//xb add 2016-09-05 ������֮�����BUF

	#if defined(__KJX_OLED_64_48_UI__)
		memset(kjx_scrolling_show, 0, sizeof(kjx_scrolling_show));
		mmi_show_scrolling_infor();
		mmi_redraw_idlescreen();
	#endif/*__KJX_OLED_64_48_UI__*/
		
	#if defined(__KJX_RFID_PLAY_CONTINUE_AGAIN__)	//xb add 2016-08-24	ͨ��������ָ�ǰ�汻�жϵ�RFID����
		if(kjx_rfid_is_in_play() && (kjx_audio_status == 3))
		{
			kjx_rfid_continue_play_audio();
		}
	#endif
	}
}

void kjx_set_with_play_tts(void)
{
	int ret;
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("begin");
#endif
#endif

#ifdef __KJX_FENCE_SUPPORT__
	if(IsMyTimerExist(KJX_TIMER_ID_FENCE_ALARM_TIMEROUT))
		StopTimer(KJX_TIMER_ID_FENCE_ALARM_TIMEROUT);
#endif

	srv_vibrator_off();
#if defined(__NPR_TTS__)
	if(TTsPlayRepeat > 0)
	{
		TTsPlayRepeat--;
		if(mmi_ucs2strlen((const CHAR *)TtsPlayString)>0)
		{
			Npr_Tts_play_stop();
			ret = Npr_Ttsplayer_playtextw(TtsPlayString, Npr_Ttsplayer_play_cb_hdlr);

		#ifdef RFID_DEBUG
		#if defined(__KJX_LOG_OUTPUT__)
			LOGD("ret:%d", ret);
		#endif
		#endif

		#if defined(__KJX_OLED_64_48_UI__)
			mmi_ucs2cpy((CHAR*)kjx_scrolling_show, (CHAR*)TtsPlayString);
			mmi_show_scrolling_infor();
			mmi_redraw_idlescreen();
		#endif/*__KJX_OLED_64_48_UI__*/
		}
	}
#endif
}

/*#############################################################*/
#endif/*BLOCK_WITH_VOICE_PUSH*/

void kjx_system_init(void)	//xb add 2016-10-18 �����ļ������ȡ����������ж��������������׵�������
{
#ifdef RFID_DEBUG
#if defined(__KJX_LOG_OUTPUT__)
	LOGD("hadRead:%d", hadRead);
#endif
#endif

	if(!hadRead)
	{
		hadRead = TRUE;
		
		kjx_rfid_play_infos_read();
	#ifdef __KJX_TOUR_NAME_STORE_CARD__
		kjx_rfid_name_infos_read();
	#endif

	#ifdef __KJX_POSITION_TRIGGER_IN_LOCAL__
		kjx_position_play_infos_read();
	#endif

	#ifdef __KJX_RFID_SEQUENTIAL_TRIGGER__
		kjx_rfid_trigger_infos_read();
	#endif

	#ifdef __KJX_RESET_USED_COUNT__
		kjx_read_playrec_file();
	#endif
	}
}

#if defined(__KJX_AUDIO_FILE_DECODE__)
void kjx_decode_string(char* buffer, U32 buflen)
{
	U32 i;

	if(buffer == NULL || buflen == 0)
		return;

	for(i=0;i<buflen;i++)
	{
		buffer[i] = buffer[i]^37;
	}
}

void kjx_encode_string(char* buffer, U32 buflen)
{
	U32 i;

	if(buffer == NULL || buflen == 0)
		return;
	
	for(i=0;i<buflen;i++)
	{
		buffer[i] = buffer[i]^37;
	}
}
#endif

#endif/*__KJX_FUN__*/
