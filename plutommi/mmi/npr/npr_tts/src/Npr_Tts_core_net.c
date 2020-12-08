//file name: Npr_Tts_core_net.c
//  hyc
#ifdef __NPR_TTS__
#ifdef __MTK_TARGET__ 
#include "MMI_include.h"
#include "stdC.h"
#include "UCS2Prot.h"
#include "fs_type.h"
#include "fs_errcode.h"
#include "med_utility.h"
#include "mdi_datatype.h"
#include "mdi_audio.h"

/* system includes */
#include "kal_release.h" 
#include "kal_trace.h"
#include "stack_common.h"  
#include "stack_msgs.h"
#include "app_buff_alloc.h"        /* Declaration of buffer management API */
#include "Unicodexdcl.h"
#include "PixtelDataTypes.h"
#include "med_utility.h"
#include "app_datetime.h"



#include "npr_TTSPlayer.h"
#include "npr_ivTTS.h"
#include "npr_ivDefine.h"

//#include "jd_base_types.h"
//#include "../../../../../../ggt/inc/GGT_utility.h"
//extern void GT_TRACE(const char *fmt, ...); 
///////////////////////////////////////////////////////////


//������֤BEGIN


////////////////////////////////////////////////////////////

typedef enum {
	ivTTS_STATUS_IDLE,			// ��Ч
	ivTTS_STATUS_INITIALIZED,	// ��ʼ�����
	ivTTS_STATUS_PAUSE,			// ��ͣ
	ivTTS_STATUS_SYNTHESIZING,	// ���ںϳ�
	ivTTS_STATUS_PLAYING,		// ���ڲ���
	ivTTS_STATUS_SYNTHESIZED,	// �ϳ����
	ivTTS_STATUS_PALYEND		// �������
} ivTTS_status;

typedef struct
{
	ivHTTS				hTTS;			/* TTS�ں�ʵ����� */
	ivPByte				pHeap;			/* TTS�ں�ʵ���� */
	ivTTS_status		status;			/* TTS Player ����״̬ */
	ivTTS_status		last_status;	/* TTS Player ��ͣǰ��״̬ */
	U32 				nOutLen;		/* ���PCM����ͳ�ƣ����ڼ����ʱ��ʼ���� */
	U32 				nFlag;			/* ��ʶ�������ж�TTS Service�Ƿ��� */
	U8					bOpenDevice;		/* ��ʾTTS�ں�ʵ������Ȩ */
	ivTTSErrID			iResult;		/* ������ */
	ivUInt8				iTextSelect;	/* �ı�ѡ�� */
	ivPointer			pText[2];			/* ��Ҫ�ϳɵ��ı� */
	ivUInt32			nTextSize[2];		/* �ϳ��ı���С */
	ivUInt32			nMaxTextBuff[2];	/* �ı���������С */

	U8					*pTTS_Audio_Buff;
	ivUInt32			iTTSParam;
	ivUInt32			iCodePage;
	ivUInt8				nMsg;
	ivUInt8				iSuspend;
	MHdl *mhdl_handle;
#ifndef IV_TTS_MEMORY_PREASSIGN
	ivUInt32			id_array[20];
	ivUInt32      value_array[20];
	ivUInt8				set_param_time;
#endif	
}ivTTS_cntx_struct;


static BOOL g_tts_flag = ivTrue;
static U8 npr_tts_pre_day;
static BOOL npr_tts_need_net_conect;

extern ivTTS_cntx_struct g_ivTTS_cntx;
void iv_tts_wait(void);
ivBool NPR_TTS_GetValid(void)
{
		g_tts_flag = ivTrue;
		return ivTrue;
}

void ivTTS_CloseTTS(void)
{
//GT_TRACE("ivTTS_CloseTTS g_ivTTS_cntx.nFlag=%d,,g_tts_flag=%d",g_ivTTS_cntx.nFlag,g_tts_flag);
	if(g_ivTTS_cntx.nFlag == 0)
	{
		if(g_tts_flag == ivTrue)
		{
			IFLYTEK_TTSPlayer_ServiceOpen();
		}
	}
	else
	{
		if(g_tts_flag == ivFalse)
		{
		//GT_TRACE("ivTTS_CloseTTS line=%d",__LINE__);
			IFLYTEK_TTSPlayer_ServiceClose();
		}
	}
}



ivUInt8 iv_tts_is_playing(void)
{
	ivUInt8 ret ;
	ret = ( iv_pcm_check(1) && iv_pcm_check(0) );

	return ret;
}

void iv_pcm_stop(void)
{
	if ( iv_tts_is_playing() )
	{
		iv_pcm_do(0);
		iv_pcm_do(1);
		iv_pcm_do(13);
		iv_pcm_do(8);
	}
	iv_pcm_do(0);
}

void iv_tts_start_step1(void)
{
	
	iv_pcm_do(5);
}

void iv_tts_start_step2(void)
{
	
	iv_pcm_do(3);
	iv_pcm_do(7);
}

void iv_tts_play(void)
{
	iv_pcm_do(15);
	
	ivTTS_CloseTTS();
}

void iv_tts_wait(void)
{
	iv_pcm_do(14);
	iv_pcm_do(10);
	iv_pcm_do(16);
}


/*****************************************************************************
* FUNCTION
*  IFLYTEK_TTSCheckStatus
* DESCRIPTION
*  Check status to pause or not
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
/* ���״̬�Ƿ���Ҫ��ͣ */
void IFLYTEK_TTSCheckStatus(void)
{
	if ( ivTTS_STATUS_PAUSE == g_ivTTS_cntx.status )
	{
		IV_TTS_Media_Pause();
		do
		{
			IV_TTS_Sleep(5);
		}while ( ivTTS_STATUS_PAUSE == g_ivTTS_cntx.status );
		IV_TTS_Media_Resume();
	}
}

void IFLYTEK_TTSCheckBuffer(void)
{
	if ( IV_TTS_Media_GetDataCount() < 100 )
	{
		if ( g_ivTTS_cntx.status == ivTTS_STATUS_SYNTHESIZED )
		{
			g_ivTTS_cntx.status = ivTTS_STATUS_PALYEND;
		}
	}
}

/*****************************************************************************
* FUNCTION
*  IFLYTEK_MMI_StopTTSCB
* DESCRIPTION
*  Call back to stop TTS
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
/* MMI��Ϣ�ص�������TTS */
void IFLYTEK_MMI_StopTTSCB(void *info)
{
	IV_TTS_Media_Stop();
	
	if ( 1 == g_ivTTS_cntx.iSuspend )
	{
		if ( IV_TTS_Is_Background_Suspended() )
		{
			IV_TTS_Resume_Background();
		}
		g_ivTTS_cntx.iSuspend = 0;
	}
}

int iv_tts_allow_plays(void)
{
	static int playCount = 0;
	
	if(playCount >=5)
	return 0;
	
	playCount++;
	
	return 1;
	
}

/*****************************************************************************
* FUNCTION
*  IFLYTEK_TTSEngineSetParam
* DESCRIPTION
*  Set Param for TTS application
* PARAMETERS
*  nParamID,
*  nParamValue,    
* RETURNS
*  void
*****************************************************************************/
ivTTSErrID IFLYTEK_TTSEngineSetParam(ivUInt32 nParamID,  ivUInt32 nParamValue)
{
	ivTTSErrID	iErrCode;
	
	/* �������õĲ��� */
	if ( ivTTS_PARAM_INPUT_MODE == nParamID 
		|| ivTTS_PARAM_INPUT_TEXT_BUFFER == nParamID
		|| ivTTS_PARAM_INPUT_TEXT_SIZE == nParamID
		|| ivTTS_PARAM_INPUT_CALLBACK == nParamID
		|| ivTTS_PARAM_PROGRESS_BEGIN == nParamID
		|| ivTTS_PARAM_PROGRESS_LENGTH == nParamID
		|| ivTTS_PARAM_PROGRESS_CALLBACK == nParamID
		|| ivTTS_PARAM_OUTPUT_CALLBACK == nParamID
		|| ivTTS_PARAM_PARAMCH_CALLBACK == nParamID
#ifdef ivTTS_PARAM_EVENT_CALLBACK
		|| ivTTS_PARAM_DELAYTIME == nParamID
		|| ivTTS_PARAM_EVENT_CALLBACK == nParamID
		|| ivTTS_PARAM_OUTPUT_BUF == nParamID
		|| ivTTS_PARAM_OUTPUT_BUFSIZE == nParamID
#endif
		)
	{
		return ivTTS_ERR_INVALID_PARAMETER;
	}

	if(iv_tts_allow_plays() == ivFalse)
	{
		return ivTTS_ERR_FAILED;
	}
	
	if( ivFalse == g_tts_flag)
		return ivTTS_ERR_FAILED;
	
	iErrCode = ivTTS_SetParam(g_ivTTS_cntx.hTTS, nParamID, nParamValue);
	
	/* ��������ǷǷ����������һ���ڲ����� */
	if ( ivTTS_ERR_INVALID_HANDLE == iErrCode )
	{
		iErrCode = ivTTS_ERR_FAILED;
	}
	
	return iErrCode;
}

/*****************************************************************************
* FUNCTION
*  IFLYTEK_TTSPlayer_IsPlaying
* DESCRIPTION
*  Check TTs is playing or not 
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
/* ���TTS�Ƿ��������� */
ivBool IFLYTEK_TTSPlayer_IsPlaying(void)
{
	if ( g_ivTTS_cntx.status > ivTTS_STATUS_INITIALIZED )
	{
		return ivTrue;
	}
	else
	{
		return ivFalse;
	}
}

/*****************************************************************************
* FUNCTION
*  IFLYTEK_TTSEngineStop
* DESCRIPTION
*  Stop of TTS application
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
/* ֹͣ */
void IFLYTEK_TTSEngineStop(void)
{
	if (g_ivTTS_cntx.status > ivTTS_STATUS_INITIALIZED)
	{
		g_ivTTS_cntx.status = ivTTS_STATUS_INITIALIZED;
	}
}

/*****************************************************************************
* FUNCTION
*  IFLYTEK_TTSPlayer_Stop
* DESCRIPTION
*  Stop  TTS 
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
/* ֹͣ */
void IFLYTEK_TTSPlayer_Stop(void)
{
	
	IFLYTEK_TTSEngineStop();
	
	/* �ͷŲ����豸 */
	IV_TTS_Media_Stop();
	
	if ( 1 == g_ivTTS_cntx.iSuspend )
	{
		IV_TTS_Resume_Background();
		g_ivTTS_cntx.iSuspend = 0;
	}
}


/*****************************************************************************
* FUNCTION
*  IFLYTEK_TTSEnginePause
* DESCRIPTION
*  Pause of TTS application
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
/* ��ͣ */
void IFLYTEK_TTSEnginePause(void)
{
	if ( g_ivTTS_cntx.status > ivTTS_STATUS_PAUSE )
	{
		g_ivTTS_cntx.last_status = g_ivTTS_cntx.status;
		g_ivTTS_cntx.status = ivTTS_STATUS_PAUSE;
	}
}

/*****************************************************************************
* FUNCTION
*  IFLYTEK_TTSEngineResume
* DESCRIPTION
*  Resume of TTS application
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
/* ���� */
void IFLYTEK_TTSEngineResume(void)
{
	if ( ivTTS_STATUS_PAUSE == g_ivTTS_cntx.status )
	{
		g_ivTTS_cntx.status = g_ivTTS_cntx.last_status;
	}
}

/*****************************************************************************
* FUNCTION
*  IFLYTEK_TTSPlayer_Pause
* DESCRIPTION
*  Pause API of TTS application
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
/* ��ͣ */
void IFLYTEK_TTSPlayer_Pause(void)
{
	IFLYTEK_TTSEnginePause();
}

/*****************************************************************************
* FUNCTION
*  IFLYTEK_TTSPlayer_Resume
* DESCRIPTION
*  Resume API of TTS application
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
/* ���� */
void IFLYTEK_TTSPlayer_Resume(void)
{
	IFLYTEK_TTSEngineResume();
}


#endif
#endif
