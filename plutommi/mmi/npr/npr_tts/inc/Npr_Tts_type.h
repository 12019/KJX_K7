#ifndef NPR_TTS_TYPE__H
#define NPR_TTS_TYPE__H
#include "mmi_features.h"
#ifdef __NPR_TTS__
#include "NPR_ivTTS.h"
#ifndef IV_TTS_MEMORY_PREASSIGN
#define ivMaxSetParamClass 20
#endif

#ifdef __NPR_BASE2_SUPPORT__
#include "jd_base_types.h"
#else
typedef unsigned char			jdU8;
typedef char					jdCHAR;
typedef unsigned short			jdU16;
typedef unsigned short			jdWCHAR;
typedef unsigned int			jdUINT;
typedef unsigned int			jdU32;
typedef void					jdVOID;

typedef signed char				jdI8;
typedef signed short int		jdI16;
typedef int						jdINT;
typedef signed int				jdI32;
typedef unsigned long			jdU64;
typedef signed long				jdI64;

#ifdef WIN32
	typedef unsigned __int64	jdU128;
	typedef __int64				jdI128;
#else
	typedef unsigned long long	jdU128;
	typedef long long			jdI128;
#endif
typedef enum {
	jdFALSE = 0,
	jdTRUE = 1
} jdBOOL;
typedef int jdFILE;

#ifndef NULL
#define NULL					0
#endif


#define PUBLIC
#define LOCAL					static

#endif

typedef void* (*jt_pvNPREntry)(void*);

void* JT_pvLoadTTSNPR(jdBOOL bLoad, void *pvData);
#if 1
typedef enum {
	ivTTS_STATUS_IDLE,			// ��Ч
	ivTTS_STATUS_INITIALIZED,	// ��ʼ�����
	ivTTS_STATUS_PAUSE,			// ��ͣ
	ivTTS_STATUS_SYNTHESIZING,	// ���ںϳ�
	ivTTS_STATUS_PLAYING,		// ���ڲ���
	ivTTS_STATUS_SYNTHESIZED,	// �ϳ����
	ivTTS_STATUS_PALYEND		// �������
} ivTTS_status;

typedef struct {
	ivHTTS				hTTS;			/* TTS�ں�ʵ����� */
	ivPByte				pHeap;			/* TTS�ں�ʵ���� */
	ivTTS_status		status;			/* TTS Player ����״̬ */
	ivTTS_status		last_status;	/* TTS Player ��ͣǰ��״̬ */
	jdU32 				nOutLen;		/* ���PCM����ͳ�ƣ����ڼ����ʱ��ʼ���� */
	jdU32 				nFlag;			/* ��ʶ�������ж�TTS Service�Ƿ��� */
	jdU8				bOpenDevice;		/* ��ʾTTS�ں�ʵ������Ȩ */
	ivTTSErrID			iResult;		/* ������ */
	ivUInt8				iTextSelect;	/* �ı�ѡ�� */
	ivPointer			pText[2];			/* ��Ҫ�ϳɵ��ı� */
	ivUInt32			nTextSize[2];		/* �ϳ��ı���С */
	ivUInt32			nMaxTextBuff[2];	/* �ı���������С */

	jdU8				*pTTS_Audio_Buff;
	ivUInt32			iTTSParam;
	ivUInt32			iCodePage;
	ivUInt8				nMsg;
	ivUInt8				iSuspend;
	void *mhdl_handle; // MHdl
#ifndef IV_TTS_MEMORY_PREASSIGN
	ivUInt32			id_array[ivMaxSetParamClass];
	ivUInt32            value_array[ivMaxSetParamClass];
	ivUInt8				set_param_time;
#endif	
}ivTTS_cntx_struct;
#endif
#endif
#endif 
