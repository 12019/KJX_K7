/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*****************************************************************************
 *
 * Filename:
 * ---------
 *    CstarEngine.c
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

//#include "MMI_features.h"



#ifdef  __MMI_CSTAR__
#include "GlobalConstants.h"
#include "mmi_frm_gprot.h"
#include "gui_data_types.h"
#include "Fat_fs.h"
#include "IMERes.h"     /* include for sIMEModeDetails */

#include "mmi_frm_gprot.h"
#include "ImeGprot.h"

#include "Word_engine.h"  
#include "Imc_symbol.h"
#include "Imc_config.h"
#include "ImmProt.h"
#include "imc.h"
#include "kmxime.h"

#if defined(__MMI_CSTAR_MULTITAP__)
#include "Multitap_engine.h"
#endif

/*****************************************************************************
 * Global variables
 *****************************************************************************/
#if defined(__MMI_IME_FUZZY_PINYIN__)
extern U32 g_mmi_imm_enabled_fuzzy_pinyin;
#endif
/*****************************************************************************
 * Define
 *****************************************************************************/
#define    MMI_CSTAR_UDB_BLOCK_SIZE          1024 /* 1k bytes, Cstar recommended */
#define    MMI_CSTAR_UDB_SIZE_PINYIN         8  /* 8k bytes, Cstar recommended */
#define    MMI_CSTAR_UDB_SIZE_ZHUYIN         8  /* 8k bytes, Cstar recommended */
#define    MMI_CSTAR_UDB_SIZE_STROKE         1  /* 1k bytes, Cstar recommended */
#define    MMI_CSTAR_UDB_SIZE_ALPHABETIC     4  /* 4k bytes, Cstar recommended */

#define MMI_IME_USER_DATABASE_FILE           L"ime_ud.dat"

/*****************************************************************************
 * Typedefs
 *****************************************************************************/

typedef enum
{
    MMI_CSTAR_UDB_SIZE_NONE = -1,
        
#if defined(__MMI_CSTAR_ENGLISH__) || defined(__MMI_CSTAR_MULTITAP__) 
    MMI_CSTAR_UDB_ENGLISH_START,
    MMI_CSTAR_UDB_ENGLISH_LAST = MMI_CSTAR_UDB_ENGLISH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_ENGLISH__) */

#if defined(__MMI_CSTAR_SM_CHINESE__) && defined  __MMI_CSTAR_STROKE_INPUT__
    MMI_CSTAR_UDB_SM_STROKE_START,
    MMI_CSTAR_UDB_SM_STROKE_LAST = MMI_CSTAR_UDB_SM_STROKE_START + MMI_CSTAR_UDB_SIZE_STROKE - 1,
#endif /* defined(__MMI_CSTAR_SM_CHINESE__) */

#if defined(__MMI_CSTAR_TR_CHINESE__) && defined __MMI_CSTAR_STROKE_INPUT__
    MMI_CSTAR_UDB_TR_STROKE_START,
    MMI_CSTAR_UDB_TR_STROKE_LAST = MMI_CSTAR_UDB_TR_STROKE_START + MMI_CSTAR_UDB_SIZE_STROKE - 1,
#endif /* defined(__MMI_CSTAR_TR_CHINESE__) */

#if defined(__MMI_CSTAR_SM_CHINESE__) 
    MMI_CSTAR_UDB_PINYIN_START,
    MMI_CSTAR_UDB_PINYIN_LAST = MMI_CSTAR_UDB_PINYIN_START + MMI_CSTAR_UDB_SIZE_PINYIN - 1,
#endif /* defined(__MMI_CSTAR_SM_CHINESE__) */

#if defined(__MMI_CSTAR_TR_CHINESE__) 
    MMI_CSTAR_UDB_ZHUYIN_START,
    MMI_CSTAR_UDB_ZHUYIN_LAST = MMI_CSTAR_UDB_ZHUYIN_START + MMI_CSTAR_UDB_SIZE_ZHUYIN - 1,
#endif /* defined(__MMI_CSTAR_TR_CHINESE__) */

#if defined(__MMI_CSTAR_DANISH__) 
    MMI_CSTAR_UDB_DANISH_START,
    MMI_CSTAR_UDB_DANISH_LAST = MMI_CSTAR_UDB_DANISH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_DANISH__) */

#if defined(__MMI_CSTAR_DUTCH__) 
    MMI_CSTAR_UDB_DUTCH_START,
    MMI_CSTAR_UDB_DUTCH_LAST = MMI_CSTAR_UDB_DUTCH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_DANISH__) */
    
#if defined(__MMI_CSTAR_FRENCH__) 
    MMI_CSTAR_UDB_FRENCH_START,
    MMI_CSTAR_UDB_FRENCH_LAST = MMI_CSTAR_UDB_FRENCH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_FRENCH__) */

#if defined(__MMI_CSTAR_GERMAN__) 
    MMI_CSTAR_UDB_GERMAN_START,
    MMI_CSTAR_UDB_GERMAN_LAST = MMI_CSTAR_UDB_GERMAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_FRENCH__) */
    
#if defined(__MMI_CSTAR_GREEK__) 
    MMI_CSTAR_UDB_GREEK_START,
    MMI_CSTAR_UDB_GREEK_LAST = MMI_CSTAR_UDB_GREEK_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_GREEK__) */

#if defined(__MMI_CSTAR_HUNGARIAN__) 
    MMI_CSTAR_UDB_HUNGARIAN_START,
    MMI_CSTAR_UDB_HUNGARIAN_LAST = MMI_CSTAR_UDB_HUNGARIAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_HUNGARIAN__) */

#if defined(__MMI_CSTAR_HINGLISH__) 
    MMI_CSTAR_UDB_HINGLISH_START,
    MMI_CSTAR_UDB_HINGLISH_LAST = MMI_CSTAR_UDB_HINGLISH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_HINGLISH__) */

#if defined(__MMI_CSTAR_ITALIAN__) 
    MMI_CSTAR_UDB_ITALIAN_START,
    MMI_CSTAR_UDB_ITALIAN_LAST = MMI_CSTAR_UDB_ITALIAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_ITALIAN__) */

#if defined(__MMI_CSTAR_POLISH__) 
    MMI_CSTAR_UDB_POLISH_START,
    MMI_CSTAR_UDB_POLISH_LAST = MMI_CSTAR_UDB_POLISH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_POLISH__) */

#if defined(__MMI_CSTAR_PORTUGUESE__) 
    MMI_CSTAR_UDB_PORTUGUESE_START,
    MMI_CSTAR_UDB_PORTUGUESE_LAST = MMI_CSTAR_UDB_PORTUGUESE_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_PORTUGUESE__) */

#if defined(__MMI_CSTAR_SPANISH__) 
    MMI_CSTAR_UDB_SPANISH_START,
    MMI_CSTAR_UDB_SPANISH_LAST = MMI_CSTAR_UDB_SPANISH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_SPANISH__) */

#if defined(__MMI_CSTAR_SWAHILI__) 
        MMI_CSTAR_UDB_SWAHILI_START,
        MMI_CSTAR_UDB_SWAHILI_LAST = MMI_CSTAR_UDB_SWAHILI_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_SWAHILI__) */

#if defined(__MMI_CSTAR_SLOVENIAN__) 
        MMI_CSTAR_UDB_SLOVENIAN_START,
        MMI_CSTAR_UDB_SLOVENIAN_LAST = MMI_CSTAR_UDB_SLOVENIAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_SLOVENIAN__) */

#if defined(__MMI_CSTAR_LITHUANIAN__) 
        MMI_CSTAR_UDB_LITHUANIAN_START,
        MMI_CSTAR_UDB_LITHUANIAN_LAST = MMI_CSTAR_UDB_LITHUANIAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_LITHUANIAN__) */

#if defined(__MMI_CSTAR_VIETNAMESE__)
    MMI_CSTAR_UDB_VIETNAMESE_START,
    MMI_CSTAR_UDB_VIETNAMESE_LAST = MMI_CSTAR_UDB_VIETNAMESE_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_VIETNAMESE__) */

#if defined(__MMI_CSTAR_INDONESIAN__)
    MMI_CSTAR_UDB_INDONESIAN_START,
    MMI_CSTAR_UDB_INDONESIAN_LAST = MMI_CSTAR_UDB_INDONESIAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_INDONESIAN__) */

#if defined(__MMI_CSTAR_THAI__)
    MMI_CSTAR_UDB_THAI_START,
    MMI_CSTAR_UDB_THAI_LAST = MMI_CSTAR_UDB_THAI_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_THAI__) */

#if defined(__MMI_CSTAR_MALAY__)
    MMI_CSTAR_UDB_MALAY_START,
    MMI_CSTAR_UDB_MALAY_LAST = MMI_CSTAR_UDB_MALAY_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /*defined(__MMI_CSTAR_MALAY__) */

#if defined(__MMI_CSTAR_PERSIAN__)
    MMI_CSTAR_UDB_PERSIAN_START,
    MMI_CSTAR_UDB_PERSIAN_LAST = MMI_CSTAR_UDB_PERSIAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /*  defined(__MMI_CSTAR_PERSIAN__) */

#if defined(__MMI_CSTAR_ARABIC__)
    MMI_CSTAR_UDB_ARABIC_START,
    MMI_CSTAR_UDB_ARABIC_LAST = MMI_CSTAR_UDB_ARABIC_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_ARABIC__) */

#if defined(__MMI_CSTAR_TURKISH__)
    MMI_CSTAR_UDB_TURKISH_START,
    MMI_CSTAR_UDB_TURKISH_LAST = MMI_CSTAR_UDB_TURKISH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_TURKISH__) */

#if defined(__MMI_CSTAR_RUSSIAN__)
    MMI_CSTAR_UDB_RUSSIAN_START,
    MMI_CSTAR_UDB_RUSSIAN_LAST = MMI_CSTAR_UDB_RUSSIAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_RUSSIAN__) */

#if defined(__MMI_CSTAR_BENGALI__) 
    MMI_CSTAR_UDB_BENGALI_START,
    MMI_CSTAR_UDB_BENGALI_LAST = MMI_CSTAR_UDB_BENGALI_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_BENGALI__) */

#if defined(__MMI_CSTAR_BULGARIAN__) 
    MMI_CSTAR_UDB_BULGARIAN_START,
    MMI_CSTAR_UDB_BULGARIAN_LAST = MMI_CSTAR_UDB_BULGARIAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_BULGARIAN__) */

#if defined(__MMI_CSTAR_CZECH__) 
    MMI_CSTAR_UDB_CZECH_START,
    MMI_CSTAR_UDB_CZECH_LAST = MMI_CSTAR_UDB_CZECH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_CZECH__) */

#if defined(__MMI_CSTAR_FINNISH__) 
    MMI_CSTAR_UDB_FINNISH_START,
    MMI_CSTAR_UDB_FINNISH_LAST = MMI_CSTAR_UDB_FINNISH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_FINNISH__) */

#if defined(__MMI_CSTAR_HEBREW__) 
    MMI_CSTAR_UDB_HEBREW_START,
    MMI_CSTAR_UDB_HEBREW_LAST = MMI_CSTAR_UDB_HEBREW_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_HEBREW__) */

#if defined(__MMI_CSTAR_HINDI__) 
    MMI_CSTAR_UDB_HINDI_START,
    MMI_CSTAR_UDB_HINDI_LAST = MMI_CSTAR_UDB_HINDI_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_HINDI__) */

#if defined(__MMI_CSTAR_MYANMAR__) 
    MMI_CSTAR_UDB_MYANMAR_START,
    MMI_CSTAR_UDB_MYANMAR_LAST = MMI_CSTAR_UDB_MYANMAR_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_MYANMAR__) */

#if defined(__MMI_CSTAR_MOLDOVAN__) 
    MMI_CSTAR_UDB_MOLDOVAN_START,
    MMI_CSTAR_UDB_MOLDOVAN_LAST = MMI_CSTAR_UDB_MOLDOVAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_MOLDOVAN__) */

#if defined(__MMI_CSTAR_SLOVAKIAN__) 
    MMI_CSTAR_UDB_SLOVAK_START,
    MMI_CSTAR_UDB_SLOVAK_LAST = MMI_CSTAR_UDB_SLOVAK_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_SLOVAKIAN__) */

#if defined(__MMI_CSTAR_ROMANIAN__) 
    MMI_CSTAR_UDB_ROMANIAN_START,
    MMI_CSTAR_UDB_ROMANIAN_LAST = MMI_CSTAR_UDB_ROMANIAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_ROMANIAN__) */

#if defined(__MMI_CSTAR_SWEDISH__) 
    MMI_CSTAR_UDB_SWEDISH_START,
    MMI_CSTAR_UDB_SWEDISH_LAST = MMI_CSTAR_UDB_SWEDISH_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_SWEDISH__) */

#if defined(__MMI_CSTAR_UKRAINIAN__) 
    MMI_CSTAR_UDB_UKRAINIAN_START,
    MMI_CSTAR_UDB_UKRAINIAN_LAST = MMI_CSTAR_UDB_UKRAINIAN_START + MMI_CSTAR_UDB_SIZE_ALPHABETIC - 1,
#endif /* defined(__MMI_CSTAR_UKRAINIAN__) */

    MMI_CSTAR_UDB_SIZE
}mmi_ime_cstar_user_data_size_enum;


/*****************************************************************************
 * Typedefs
 *****************************************************************************/

typedef struct
{
    mmi_imm_input_mode_enum         input_mode;
    const void * *                    ldb_ptr;
    U32                             required_keys;
    U32                             symbol_keys;
    U8                              udb_start_block_index;
    U8                              udb_size;
    mmi_ime_get_spellings_funcptr   get_spell_func;
    mmi_ime_get_associates_funcptr  get_assoc_func;
    mmi_ime_get_candidates_funcptr  get_cand_func;
}   mmi_ime_cstar_mode_info_struct, *mmi_ime_cstar_mode_info_struct_p;


typedef struct
{
    KMX_IME_ENGINE                      cstar_engine;
    KMX_IME_ENGINE_INIT                 init_info;
    MMI_BOOL                            is_inited;
    mmi_ime_cstar_mode_info_struct_p    curr_mode_info;
    mmi_imm_input_mode_enum             input_mode;
    U8                                  get_context;
    mmi_ime_word_capital_state_enum     case_type;
#if defined(__MMI_CSTAR_MULTITAP__)
    S32                  multitap_string_length;
    UI_character_type    mt_page_buff[MULTITAP_MAX_KEY_CHAR];
#endif /* #if defined(__MMI_CSTAR_MULTITAP__) */
}   mmi_ime_cstar_word_engine_struct, *mmi_ime_cstar_word_engine_struct_p;

/*****************************************************************************
 * Local functions
 *****************************************************************************/

/* Utility functions */

static const mmi_ime_cstar_mode_info_struct * mmi_ime_cstar_query_mode_info( mmi_imm_input_mode_enum input_mode );

static void  mmi_ime_cstar_change_candidates_case(mmi_ime_query_result_struct_p result_str);

static UI_character_type mmi_ime_cstar_char_to_upper(UI_character_type char_code);

static UI_character_type mmi_ime_cstar_char_to_lower(UI_character_type char_code);


/* Query functions */

#if defined(__MMI_CSTAR_SM_CHINESE__) || defined(__MMI_CSTAR_TR_CHINESE__)
static void  mmi_ime_cstar_get_associates_chinese( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );
#endif /* #if defined(__MMI_CSTAR_SM_CHINESE__) || defined(__MMI_CSTAR_TR_CHINESE__) */

static void  mmi_ime_cstar_get_associates_alphabetic( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );

#if defined __MMI_SMART_ALPHABETIC_INPUT_METHODS__ || defined(__MMI_CSTAR_MULTITAP__)
static void     mmi_ime_cstar_get_candidates_alphabetic( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );
#endif

#if  defined __MMI_CSTAR_STROKE_INPUT__
static void     mmi_ime_cstar_get_spellings_stroke( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );
static void     mmi_ime_cstar_get_candidates_stroke( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );
#endif /* #if defined(__MMI_CSTAR_SM_CHINESE__) || defined(__MMI_CSTAR_TR_CHINESE__) */

/* Simplified Chinese functions */
#if defined(__MMI_CSTAR_SM_CHINESE__)
static void mmi_ime_cstar_get_spellings_pinyin_multitap( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );

#if defined(__MMI_CSTAR_SMART_PHONETIC_INPUT__)

#ifndef __MMI_IME_SMART_WITH_INPUT_AREA__
static void mmi_ime_cstar_get_spellings_pinyin_smart( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );
#else
static void mmi_ime_cstar_get_candidate_pinyin_cstar_style( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );
#endif

#endif /* #if defined(__MMI_CSTAR_SMART_PHONETIC_INPUT__) */

static void mmi_ime_cstar_get_candidates_pinyin( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );

#endif /* #if defined(__MMI_CSTAR_SM_CHINESE__) */

/* Traditional Chinese functions */
#if defined(__MMI_CSTAR_TR_CHINESE__)

#if defined(__MMI_CSTAR_MULTITAP_PHONETIC_INPUT__)
static void mmi_ime_cstar_get_spellings_zhuyin_multitap( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );
#endif /* #if defined(__MMI_CSTAR_MULTITAP_PHONETIC_INPUT__) */

#if defined(__MMI_CSTAR_SMART_PHONETIC_INPUT__)
static void mmi_ime_cstar_get_spellings_zhuyin_smart( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );
#endif /* #if defined(__MMI_CSTAR_SMART_PHONETIC_INPUT__) */

static void mmi_ime_cstar_get_candidates_zhuyin( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr );

#endif /* #if defined(__MMI_CSTAR_TR_CHINESE__) */

#if defined(__MMI_IME_USER_DATABASE__)

static FS_HANDLE mmi_ime_cstar_open_file(PU16 path_name_ptr, PU16 file_name_ptr, MMI_BOOL is_create_always);

static void mmi_ime_cstar_close_file(FS_HANDLE file_handle);

static U32 mmi_ime_cstar_write_file(FS_HANDLE file_handle, PU16 data_ptr, U32 size_in_byte);

static U32 mmi_ime_cstar_read_file(FS_HANDLE file_handle, PU16 data_ptr, U32 size_in_byte);

#endif

#if defined(__MMI_CSTAR_MULTITAP__)
static MMI_BOOL mmi_ime_multitap_vendor_valid_key_check( mmi_imc_symbol_key_enum sym);
static UI_string_type mmi_ime_multitap_vendor_get_string(S32 index);
#endif
/*****************************************************************************
 * Local variables
 *****************************************************************************/

#if defined(__MMI_IME_USER_DATABASE__)

static U16 mmi_ime_cstar_user_data[MMI_CSTAR_UDB_SIZE * MMI_CSTAR_UDB_BLOCK_SIZE / 2];

#endif /* defined(__MMI_IME_USER_DATABASE__) */



#if defined __MMI_CSTAR_STROKE_INPUT__

static const mmi_imc_symb_stroke_enum g_cstar_keys_stroke[MMI_IMC_SYMB_KEY_MAX - MMI_IMC_SYMB_KEY_BASE] =
{
    0,                         /* MMI_IMC_SYMB_KEY_0 */
    MMI_IMC_SYMB_STROKE_OVER,  /* MMI_IMC_SYMB_KEY_1 */
    MMI_IMC_SYMB_STROKE_DOWN,  /* MMI_IMC_SYMB_KEY_2 */
    MMI_IMC_SYMB_STROKE_LEFT,  /* MMI_IMC_SYMB_KEY_3 */
    MMI_IMC_SYMB_STROKE_DOT,   /* MMI_IMC_SYMB_KEY_4 */
    MMI_IMC_SYMB_STROKE_OVER_DOWN, /* MMI_IMC_SYMB_KEY_5 */
    MMI_IMC_SYMB_STROKE_WILDCARD, /* MMI_IMC_SYMB_KEY_6 */
    0,   /* MMI_IMC_SYMB_KEY_7 */
    0,   /* MMI_IMC_SYMB_KEY_8 */
    0,   /* MMI_IMC_SYMB_KEY_9 */
    0,   /* MMI_IMC_SYMB_KEY_STAR */
    0    /* MMI_IMC_SYMB_KEY_POUND */
};

static const char   g_cstar_codes_stroke[MMI_IMC_SYMB_STROKE_MAX - MMI_IMC_SYMB_STROKE_BASE] =
{
    KMX_STROKE_WILDCARD,  /* MMI_IMC_SYMB_STROKE_WILDCARD, */
    KMX_STROKE_SHU,      /* MMI_IMC_SYMB_STROKE_DOWN, */
    KMX_STROKE_DIAN,    /* MMI_IMC_SYMB_STROKE_DOT, */
    0,                  /* MMI_IMC_SYMB_STROKE_CURVED_HOOK, */
    KMX_STROKE_HENG,    /* MMI_IMC_SYMB_STROKE_OVER, */
    KMX_STROKE_ZHE,     /* MMI_IMC_SYMB_STROKE_OVER_DOWN, */
    0,                  /* MMI_IMC_SYMB_STROKE_DOWN_OVER, */
    KMX_STROKE_PIE,     /* MMI_IMC_SYMB_STROKE_LEFT, */
    0,                  /* MMI_IMC_SYMB_STROKE_OVER_DOWN_OVER, */
    0,                  /* MMI_IMC_SYMB_STROKE_MORE, */
    0,                  /* MMI_IMC_SYMB_STROKE_TURN, */
    0,                  /* MMI_IMC_SYMB_STROKE_DOT_OR_LEFT, */
};
#endif /* #if defined(__MMI_CSTAR_SM_CHINESE__) || defined(__MMI_CSTAR_TR_CHINESE__) */

/* All input mode informations */
static const mmi_ime_cstar_mode_info_struct   g_mode_infos[] =
{
#if defined(__MMI_CSTAR_TR_CHINESE__) && defined(__MMI_CSTAR_MULTITAP_PHONETIC_INPUT__)
    {   
        IMM_INPUT_MODE_TR_MULTITAP_BOPOMO,
    #if defined(__MMI_IME_SMART_WITH_INPUT_AREA__) 
        &kmx_ldb_zhuyin_cizu,
    #else
        &kmx_ldb_zhuyin_danzi,
    #endif
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ZHUYIN_START,
        MMI_CSTAR_UDB_SIZE_ZHUYIN,
        mmi_ime_cstar_get_spellings_zhuyin_multitap,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidates_zhuyin
    },
    {   
        IMM_INPUT_MODE_QUICK_SEARCH_BOPOMO,
    #if defined(__MMI_IME_SMART_WITH_INPUT_AREA__) 
        &kmx_ldb_zhuyin_cizu,
    #else
        &kmx_ldb_zhuyin_danzi,
    #endif
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ZHUYIN_START,
        MMI_CSTAR_UDB_SIZE_ZHUYIN,
        mmi_ime_cstar_get_spellings_zhuyin_multitap,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidates_zhuyin
    },
#endif 

#if defined(__MMI_CSTAR_SM_CHINESE__)
    {
        IMM_INPUT_MODE_SM_MULTITAP_PINYIN,
            
    #if defined(__MMI_IME_SMART_WITH_INPUT_AREA__) 
        &kmx_ldb_pinyin_cizu,
    #else
        &kmx_ldb_pinyin_danzi,
    #endif
    
        MMI_IME_REQUIRED_ALL_KEYS & (~MMI_IME_REQUIRED_KEY_1),
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_1) & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_PINYIN_START,
        MMI_CSTAR_UDB_SIZE_PINYIN,
        mmi_ime_cstar_get_spellings_pinyin_multitap,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidates_pinyin
    },
    {
        IMM_INPUT_MODE_QUICK_SEARCH_PINYIN,
    #if defined(__MMI_IME_SMART_WITH_INPUT_AREA__)
        &kmx_ldb_pinyin_cizu,
    #else
        &kmx_ldb_pinyin_danzi,
    #endif
        MMI_IME_REQUIRED_ALL_KEYS & (~MMI_IME_REQUIRED_KEY_1),
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_1) & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_PINYIN_START,
        MMI_CSTAR_UDB_SIZE_PINYIN,
        mmi_ime_cstar_get_spellings_pinyin_multitap,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidates_pinyin
    },
#endif /* #if defined(__MMI_CSTAR_SM_CHINESE__)

#if defined(__MMI_CSTAR_TR_CHINESE__) && defined(__MMI_CSTAR_SMART_PHONETIC_INPUT__)
    {   
        IMM_INPUT_MODE_TR_BOPOMO,
        &kmx_ldb_zhuyin_cizu,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ZHUYIN_START,
        MMI_CSTAR_UDB_SIZE_ZHUYIN,
        mmi_ime_cstar_get_spellings_zhuyin_smart,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidates_zhuyin
    },
#endif /* #if defined(__MMI_CSTAR_TR_CHINESE__) && defined(__MMI_CSTAR_SMART_PHONETIC_INPUT__) */    

#if defined(__MMI_CSTAR_SM_CHINESE__) && defined(__MMI_CSTAR_SMART_PHONETIC_INPUT__)

#ifndef __MMI_IME_SMART_WITH_INPUT_AREA__
    {
        IMM_INPUT_MODE_SM_PINYIN,
        &kmx_ldb_pinyin_danzi,
        MMI_IME_REQUIRED_ALL_KEYS & (~MMI_IME_REQUIRED_KEY_1),
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0) & (~MMI_IME_REQUIRED_KEY_1), /* 1 is magic key */
        MMI_CSTAR_UDB_PINYIN_START,
        MMI_CSTAR_UDB_SIZE_PINYIN,
        mmi_ime_cstar_get_spellings_pinyin_smart,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidates_pinyin
    },
#else
    {
        IMM_INPUT_MODE_SM_PINYIN,
        &kmx_ldb_pinyin_cizu,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS, /* 1 is magic key */
        MMI_CSTAR_UDB_PINYIN_START,
        MMI_CSTAR_UDB_SIZE_PINYIN,
        NULL,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidate_pinyin_cstar_style
    },
#endif /* __MMI_TOUCH_SCREEN__ */

#endif /* #if defined(__MMI_CSTAR_SM_CHINESE__) && defined(__MMI_CSTAR_SMART_PHONETIC_INPUT__) */

#if defined(__MMI_CSTAR_TR_CHINESE__)&& defined __MMI_CSTAR_STROKE_INPUT__
    {
        IMM_INPUT_MODE_TR_STROKE, 
        &kmx_ldb_stroke_big5,
        MMI_IME_REQUIRED_ALL_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0), /* key 7 is magic key */
        MMI_CSTAR_UDB_TR_STROKE_START,
        MMI_CSTAR_UDB_SIZE_STROKE,
        mmi_ime_cstar_get_spellings_stroke,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidates_stroke
    },
    {
        IMM_INPUT_MODE_QUICK_SEARCH_TR_STROKE,
        &kmx_ldb_stroke_big5,
        MMI_IME_REQUIRED_ALL_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_TR_STROKE_START,
        MMI_CSTAR_UDB_SIZE_STROKE,
        mmi_ime_cstar_get_spellings_stroke,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidates_stroke
    },
#endif /* #if defined(__MMI_CSTAR_TR_CHINESE__) */

#if defined(__MMI_CSTAR_SM_CHINESE__)  && defined __MMI_CSTAR_STROKE_INPUT__
    {
        IMM_INPUT_MODE_SM_STROKE,
        &kmx_ldb_stroke_gb2312,
        MMI_IME_REQUIRED_ALL_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0), /* key 7 is magic key */
        MMI_CSTAR_UDB_SM_STROKE_START,
        MMI_CSTAR_UDB_SIZE_STROKE,
        mmi_ime_cstar_get_spellings_stroke,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidates_stroke 
    },
    {
        IMM_INPUT_MODE_QUICK_SEARCH_SM_STROKE,
        &kmx_ldb_stroke_gb2312,
        MMI_IME_REQUIRED_ALL_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SM_STROKE_START,
        MMI_CSTAR_UDB_SIZE_STROKE,
        mmi_ime_cstar_get_spellings_stroke,
        mmi_ime_cstar_get_associates_chinese,
        mmi_ime_cstar_get_candidates_stroke 
    },
#endif /* #if defined(__MMI_CSTAR_TR_CHINESE__) */

#if defined(__MMI_CSTAR_ENGLISH__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_ABC,
        &kmx_ldb_english,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_ENGLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_ABC,
        &kmx_ldb_english,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_ENGLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_ABC,
        &kmx_ldb_english,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_ENGLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_ENGLISH__) */

#if defined(__MMI_CSTAR_MULTITAP__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_ABC,
        &kmx_ldb_english,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ENGLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_ABC,
        &kmx_ldb_english,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ENGLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_ABC,
        &kmx_ldb_english,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ENGLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_DANISH__) && defined(__MMI_CSTAR_DANISH__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_DANISH,
        &kmx_ldb_danish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_DANISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_DANISH,
        &kmx_ldb_danish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_DANISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_DANISH,
        &kmx_ldb_danish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_DANISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_DUTCH__)&& defined(__MMI_CSTAR_DUTCH__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_DUTCH,
        &kmx_ldb_dutch,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_DUTCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_DUTCH,
        &kmx_ldb_dutch,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_DUTCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_DUTCH,
        &kmx_ldb_dutch,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_DUTCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_FRENCH__) &&  defined(__MMI_CSTAR_FRENCH__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_FRENCH,
        &kmx_ldb_french,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_FRENCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_FRENCH,
        &kmx_ldb_french,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_FRENCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_FRENCH,
        &kmx_ldb_french,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_FRENCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_GERMAN__) &&  defined(__MMI_CSTAR_GERMAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_GERMAN,
        &kmx_ldb_german,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_GERMAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_GERMAN,
        &kmx_ldb_german,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_GERMAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_GERMAN,
        &kmx_ldb_german,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_GERMAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_GREEK__) &&  defined(__MMI_CSTAR_GREEK__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_GREEK,
        &kmx_ldb_greek,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_GREEK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_GREEK,
        &kmx_ldb_greek,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_GREEK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_GREEK,
        &kmx_ldb_greek,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_GREEK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_HUNGARIAN__) &&  defined(__MMI_CSTAR_HUNGARIAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_HUNGARIAN,
        &kmx_ldb_hungarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_HUNGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_HUNGARIAN,
        &kmx_ldb_hungarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_HUNGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_HUNGARIAN,
        &kmx_ldb_hungarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_HUNGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_ITALIAN__) &&  defined(__MMI_CSTAR_ITALIAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_ITALIAN,
        &kmx_ldb_italian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ITALIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_ITALIAN,
        &kmx_ldb_italian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ITALIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_ITALIAN,
        &kmx_ldb_italian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ITALIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_POLISH__) &&  defined(__MMI_CSTAR_POLISH__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_POLISH,
        &kmx_ldb_polish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_POLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_POLISH,
        &kmx_ldb_polish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_POLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_POLISH,
        &kmx_ldb_polish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_POLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_PORTUGUESE__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_PORTUGUESE,
        &kmx_ldb_portuguese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        NULL,
        NULL,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_PORTUGUESE,
        &kmx_ldb_portuguese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        NULL,
        NULL,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_PORTUGUESE,
        &kmx_ldb_portuguese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        NULL,
        NULL,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_SPANISH__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_SPANISH,
        &kmx_ldb_spanish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        NULL,
        NULL,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_SPANISH,
        &kmx_ldb_spanish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        NULL,
        NULL,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_SPANISH,
        &kmx_ldb_spanish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        NULL,
        NULL,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_SWAHILI__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_SWAHILI,
        &kmx_ldb_swahili,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        NULL,
        NULL,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_SWAHILI,
        &kmx_ldb_swahili,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        NULL,
        NULL,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_SWAHILI,
        &kmx_ldb_swahili,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        NULL,
        NULL,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_SLOVENIAN__)&&  defined(__MMI_CSTAR_SLOVENIAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_SLOVENIAN,
        &kmx_ldb_slovenian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_SLOVENIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_SLOVENIAN,
        &kmx_ldb_slovenian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_SLOVENIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_SLOVENIAN,
        &kmx_ldb_slovenian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_SLOVENIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_LITHUANIAN__) &&  defined(__MMI_CSTAR_LITHUANIAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_LITHUANIAN,
        &kmx_ldb_lithuanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_LITHUANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_LITHUANIAN,
        &kmx_ldb_lithuanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_LITHUANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_LITHUANIAN,
        &kmx_ldb_lithuanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_LITHUANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_VIETNAMESE__) && defined(__MMI_CSTAR_VIETNAMESE__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_VIETNAMESE,
        &kmx_ldb_vietnamese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_VIETNAMESE_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_VIETNAMESE,
        &kmx_ldb_vietnamese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_VIETNAMESE_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_VIETNAMESE,
        &kmx_ldb_vietnamese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_VIETNAMESE_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_INDONESIAN__) && defined(__MMI_CSTAR_INDONESIAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_INDONESIAN,
        &kmx_ldb_indonesian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_INDONESIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_INDONESIAN,
        &kmx_ldb_indonesian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_INDONESIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_INDONESIAN,
        &kmx_ldb_indonesian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_INDONESIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_MALAY__) &&  defined(__MMI_CSTAR_MALAY__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_MALAY,
        &kmx_ldb_malay,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_MALAY_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_MALAY,
        &kmx_ldb_malay,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_MALAY_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_MALAY,
        &kmx_ldb_malay,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_MALAY_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_TURKISH__) && defined(__MMI_CSTAR_TURKISH__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_TURKISH,
        &kmx_ldb_turkish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_TURKISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_TURKISH,
        &kmx_ldb_turkish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_TURKISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_TURKISH,
        &kmx_ldb_turkish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_TURKISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_MULTITAP__) && defined(__MMI_MULTITAP_RUSSIAN__)&& defined(__MMI_CSTAR_RUSSIAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_RUSSIAN,
        &kmx_ldb_russian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_RUSSIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_RUSSIAN,
        &kmx_ldb_russian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_RUSSIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_RUSSIAN,
        &kmx_ldb_russian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_RUSSIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_ARABIC__) && defined(__MMI_MULTITAP_ARABIC__)
    {
        IMM_INPUT_MODE_MULTITAP_ARABIC,
        &kmx_ldb_arabic,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ARABIC_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },    
#endif /* #if defined(__MMI_CSTAR_ARABIC__) */
#if defined(__MMI_CSTAR_THAI__) && defined(__MMI_MULTITAP_THAI__)
    {
        IMM_INPUT_MODE_MULTITAP_THAI,
        &kmx_ldb_thai,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_THAI_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },    
#endif /* #if defined(__MMI_CSTAR_THAI__) */
#if defined(__MMI_CSTAR_PERSIAN__) && defined(__MMI_MULTITAP_PERSIAN__)
    {
        IMM_INPUT_MODE_MULTITAP_PERSIAN,
        &kmx_ldb_persian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_PERSIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },    
#endif /* #if defined(__MMI_CSTAR_PERSIAN__) */



#if defined(__MMI_CSTAR_BENGALI__) && defined(__MMI_MULTITAP_BENGALI__)
    {
        IMM_INPUT_MODE_MULTITAP_BENGALI,
        &kmx_ldb_bengali,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_BENGALI_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },    
#endif /* #if defined(__MMI_CSTAR_BENGALI__) */
#if defined(__MMI_CSTAR_BULGARIAN__) && defined(__MMI_MULTITAP_BULGARIAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_BULGARIAN,
        &kmx_ldb_bulgarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_BULGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_BULGARIAN,
        &kmx_ldb_bulgarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_BULGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_BULGARIAN,
        &kmx_ldb_bulgarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_BULGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_BULGARIAN__) */
#if defined(__MMI_CSTAR_CZECH__) && defined(__MMI_MULTITAP_CZECH__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_CZECH,
        &kmx_ldb_czech,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_CZECH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_CZECH,
        &kmx_ldb_czech,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_CZECH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_CZECH,
        &kmx_ldb_czech,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_CZECH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_CZECH__) */
#if defined(__MMI_CSTAR_FINNISH__) && defined(__MMI_MULTITAP_FINNISH__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_FINNISH,
        &kmx_ldb_finnish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_FINNISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_FINNISH,
        &kmx_ldb_finnish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_FINNISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_FINNISH,
        &kmx_ldb_finnish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_FINNISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_FINNISH__) */
#if defined(__MMI_CSTAR_HEBREW__) && defined(__MMI_MULTITAP_HEBREW__)
    {
        IMM_INPUT_MODE_MULTITAP_HEBREW,
        &kmx_ldb_hebrew,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_HEBREW_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },    
#endif /* #if defined(__MMI_CSTAR_HEBREW__) */
#if defined(__MMI_CSTAR_HINDI__) && defined(__MMI_MULTITAP_HINDI__)
    {
        IMM_INPUT_MODE_MULTITAP_HINDI,
        &kmx_ldb_hindi,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_HINDI_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },    
#endif /* #if defined(__MMI_CSTAR_HINDI__) */
#if defined(__MMI_CSTAR_MYANMAR__) && defined(__MMI_MULTITAP_MYANMAR__)
    {
        IMM_INPUT_MODE_MULTITAP_MYANMAR,
        &kmx_ldb_myanmar,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_MYANMAR_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },    
#endif /* #if defined(__MMI_CSTAR_MYANMAR__) */
#if defined(__MMI_CSTAR_MOLDOVAN__) && defined(__MMI_MULTITAP_MOLDOVAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_MOLDOVAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_MOLDOVAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_MOLDOVAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_MOLDOVAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_MOLDOVAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_MOLDOVAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_MOLDOVAN__) */
#if defined(__MMI_CSTAR_ROMANIAN__) && defined(__MMI_MULTITAP_ROMANIAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_ROMANIAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_ROMANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_ROMANIAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ROMANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_ROMANIAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ROMANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_ROMANIAN__) */
#if defined(__MMI_CSTAR_SLOVAKIAN__) && defined(__MMI_MULTITAP_SLOVAK__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_SLOVAK,
        &kmx_ldb_slovak,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_SLOVAK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_SLOVAK,
        &kmx_ldb_slovak,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_SLOVAK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_SLOVAK,
        &kmx_ldb_slovak,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_SLOVAK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_SLOVAKIAN__) */
#if defined(__MMI_CSTAR_SWEDISH__) && defined(__MMI_MULTITAP_SWEDISH__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_SWEDISH,
        &kmx_ldb_swedish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_SWEDISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_SWEDISH,
        &kmx_ldb_swedish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_SWEDISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_SWEDISH,
        &kmx_ldb_swedish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_SWEDISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_SWEDISH__) */
#if defined(__MMI_CSTAR_UKRAINIAN__) && defined(__MMI_MULTITAP_UKRAINIAN__)
    {
        IMM_INPUT_MODE_MULTITAP_UPPERCASE_UKRAINIAN,
        &kmx_ldb_ukrainian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_UKRAINIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_LOWERCASE_UKRAINIAN,
        &kmx_ldb_ukrainian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_UKRAINIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_MULTITAP_FIRST_UPPERCASE_UKRAINIAN,
        &kmx_ldb_ukrainian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_UKRAINIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_UKRAINIAN__) */

#if defined(__MMI_IME_MAGIC_ONE__)
    {
        IMM_INPUT_MODE_MAGIC_NUMBER,
        &kmx_ldb_english,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS,
        MMI_CSTAR_UDB_ENGLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif
#if defined(__MMI_CSTAR_DANISH__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_DANISH,
        &kmx_ldb_danish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_DANISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_DANISH,
        &kmx_ldb_danish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_DANISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_DANISH,
        &kmx_ldb_danish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_DANISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_DANISH__) */

#if defined(__MMI_CSTAR_DUTCH__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_DUTCH,
        &kmx_ldb_dutch,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_DUTCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_DUTCH,
        &kmx_ldb_dutch,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_DUTCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_DUTCH,
        &kmx_ldb_dutch,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_DUTCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_DUTCH__) */

    
#if defined(__MMI_CSTAR_FRENCH__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_FRENCH,
        &kmx_ldb_french,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_FRENCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_FRENCH,
        &kmx_ldb_french,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_FRENCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_FRENCH,
        &kmx_ldb_french,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_FRENCH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_FRENCH__) */

    
#if defined(__MMI_CSTAR_GERMAN__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_GERMAN,
        &kmx_ldb_german,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_GERMAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_GERMAN,
        &kmx_ldb_german,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_GERMAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_GERMAN,
        &kmx_ldb_german,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_GERMAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_GERMAN__) */

#if defined(__MMI_CSTAR_GREEK__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_GREEK,
        &kmx_ldb_greek,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_GREEK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_GREEK,
        &kmx_ldb_greek,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_GREEK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_GREEK,
        &kmx_ldb_greek,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_GREEK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_GREEK__) */

#if defined(__MMI_CSTAR_HUNGARIAN__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_HUNGARIAN,
        &kmx_ldb_hungarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_HUNGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_HUNGARIAN,
        &kmx_ldb_hungarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_HUNGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_HUNGARIAN,
        &kmx_ldb_hungarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_HUNGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_HUNGARIAN__) */

#if defined(__MMI_CSTAR_HINGLISH__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_HINGLISH,
        &kmx_ldb_hinglish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_HINGLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_HINGLISH,
        &kmx_ldb_hinglish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_HINGLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    
#endif /* #if defined(__MMI_CSTAR_HINGLISH__) */

#if defined(__MMI_CSTAR_ITALIAN__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_ITALIAN,
        &kmx_ldb_italian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_ITALIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_ITALIAN,
        &kmx_ldb_italian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_ITALIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_ITALIAN,
        &kmx_ldb_italian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_ITALIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_ITALIAN__) */

#if defined(__MMI_CSTAR_POLISH__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_POLISH,
        &kmx_ldb_polish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_POLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_POLISH,
        &kmx_ldb_polish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_POLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_POLISH,
        &kmx_ldb_polish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_POLISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_POLISH__) */

#if defined(__MMI_CSTAR_PORTUGUESE__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_PORTUGUESE,
        &kmx_ldb_portuguese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_PORTUGUESE_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_PORTUGUESE,
        &kmx_ldb_portuguese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_PORTUGUESE_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_PORTUGUESE,
        &kmx_ldb_portuguese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_PORTUGUESE_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_PORTUGUESE__) */

#if defined(__MMI_CSTAR_SPANISH__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_SPANISH,
        &kmx_ldb_spanish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SPANISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_SPANISH,
        &kmx_ldb_spanish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SPANISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_SPANISH,
        &kmx_ldb_spanish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SPANISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_SPANISH__) */

#if defined(__MMI_CSTAR_SWAHILI__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_SWAHILI,
        &kmx_ldb_swahili,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SWAHILI_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_SWAHILI,
        &kmx_ldb_swahili,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SWAHILI_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_SWAHILI,
        &kmx_ldb_swahili,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SWAHILI_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_SWAHILI__) */

#if defined(__MMI_CSTAR_SLOVENIAN__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_SLOVENIAN,
        &kmx_ldb_slovenian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SLOVENIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_SLOVENIAN,
        &kmx_ldb_slovenian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SLOVENIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_SLOVENIAN,
        &kmx_ldb_slovenian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SLOVENIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_SLOVENIAN__) */

#if defined(__MMI_CSTAR_LITHUANIAN__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_LITHUANIAN,
        &kmx_ldb_lithuanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_LITHUANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_LITHUANIAN,
        &kmx_ldb_lithuanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_LITHUANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_LITHUANIAN,
        &kmx_ldb_lithuanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_LITHUANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_LITHUANIAN__) */

#if defined(__MMI_CSTAR_VIETNAMESE__)
   {
        IMM_INPUT_MODE_SMART_UPPERCASE_VIETNAMESE,
        &kmx_ldb_vietnamese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_VIETNAMESE_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_VIETNAMESE,
        &kmx_ldb_vietnamese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_VIETNAMESE_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_VIETNAMESE,
        &kmx_ldb_vietnamese,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_VIETNAMESE_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_VIETNAMESE__) */

#if defined(__MMI_CSTAR_INDONESIAN__)
{
        IMM_INPUT_MODE_SMART_UPPERCASE_INDONESIAN,
        &kmx_ldb_indonesian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_INDONESIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_INDONESIAN,
        &kmx_ldb_indonesian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_INDONESIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_INDONESIAN,
        &kmx_ldb_indonesian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_INDONESIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },

#endif /* #if defined(__MMI_CSTAR_INDONESIAN__) */

#if defined(__MMI_CSTAR_THAI__)
{
        IMM_INPUT_MODE_SMART_THAI,
        &kmx_ldb_thai,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_THAI_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_THAI__) */

#if defined(__MMI_CSTAR_MALAY__)
{
        IMM_INPUT_MODE_SMART_UPPERCASE_MALAY,
        &kmx_ldb_malay,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_MALAY_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_MALAY,
        &kmx_ldb_malay,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_MALAY_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_MALAY,
        &kmx_ldb_malay,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_MALAY_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_MALAY__) */

#if defined(__MMI_CSTAR_PERSIAN__)
{
        IMM_INPUT_MODE_SMART_PERSIAN,
        &kmx_ldb_persian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_PERSIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    
#endif /* #if defined(__MMI_CSTAR_PERSIAN__) */

#if defined(__MMI_CSTAR_ARABIC__)
{
        IMM_INPUT_MODE_SMART_ARABIC,
        &kmx_ldb_arabic,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_ARABIC_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_ARABIC__) */

#if defined(__MMI_CSTAR_TURKISH__)
{
        IMM_INPUT_MODE_SMART_UPPERCASE_TURKISH,
        &kmx_ldb_turkish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_TURKISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_TURKISH,
        &kmx_ldb_turkish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_TURKISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_TURKISH,
        &kmx_ldb_turkish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_TURKISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_TURKISH__) */

#if defined(__MMI_CSTAR_RUSSIAN__)
{
        IMM_INPUT_MODE_SMART_UPPERCASE_RUSSIAN,
        &kmx_ldb_russian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_RUSSIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_RUSSIAN,
        &kmx_ldb_russian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_RUSSIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_RUSSIAN,
        &kmx_ldb_russian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_RUSSIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_RUSSIAN__) */

#if defined(__MMI_CSTAR_BENGALI__)    
    {
        IMM_INPUT_MODE_SMART_BENGALI,
        &kmx_ldb_bengali,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_BENGALI_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_BENGALI__) */


#if defined(__MMI_CSTAR_BULGARIAN__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_BULGARIAN,
        &kmx_ldb_bulgarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_BULGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_BULGARIAN,
        &kmx_ldb_bulgarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_BULGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_BULGARIAN,
        &kmx_ldb_bulgarian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_BULGARIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_BULGARIAN__) */


#if defined(__MMI_CSTAR_CZECH__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_CZECH,
        &kmx_ldb_czech,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_CZECH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_CZECH,
        &kmx_ldb_czech,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_CZECH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_CZECH,
        &kmx_ldb_czech,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_CZECH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_CZECH__) */


#if defined(__MMI_CSTAR_FINNISH__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_FINNISH,
        &kmx_ldb_finnish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_FINNISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_FINNISH,
        &kmx_ldb_finnish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_FINNISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_FINNISH,
        &kmx_ldb_finnish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_FINNISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_FINNISH__) */


#if defined(__MMI_CSTAR_HEBREW__)
    {
        IMM_INPUT_MODE_SMART_HEBREW,
        &kmx_ldb_hebrew,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_HEBREW_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_HEBREW__) */


#if defined(__MMI_CSTAR_HINDI__)
    {
        IMM_INPUT_MODE_SMART_HINDI,
        &kmx_ldb_hindi,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_HINDI_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_HINDI__) */


#if defined(__MMI_CSTAR_MYANMAR__)
    {
        IMM_INPUT_MODE_SMART_MYANMAR,
        &kmx_ldb_myanmar,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS ,
        MMI_CSTAR_UDB_MYANMAR_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_MYANMAR__) */


#if defined(__MMI_CSTAR_MOLDOVAN__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_MOLDOVAN,
        &kmx_ldb_romanian, /* picking up moldovan from romanian */
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_MOLDOVAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_MOLDOVAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_MOLDOVAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_MOLDOVAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_MOLDOVAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_MOLDOVAN__) */


#if defined(__MMI_CSTAR_ROMANIAN__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_ROMANIAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_ROMANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_ROMANIAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_ROMANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_ROMANIAN,
        &kmx_ldb_romanian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_ROMANIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_ROMANIAN__) */


#if defined(__MMI_CSTAR_SLOVAKIAN__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_SLOVAK,
        &kmx_ldb_slovak,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SLOVAK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_SLOVAK,
        &kmx_ldb_slovak,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SLOVAK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_SLOVAK,
        &kmx_ldb_slovak,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SLOVAK_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_SLOVAKIAN__) */


#if defined(__MMI_CSTAR_SWEDISH__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_SWEDISH,
        &kmx_ldb_swedish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SWEDISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_SWEDISH,
        &kmx_ldb_swedish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SWEDISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_SWEDISH,
        &kmx_ldb_swedish,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_SWEDISH_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_SWEDISH__) */


#if defined(__MMI_CSTAR_UKRAINIAN__)
    {
        IMM_INPUT_MODE_SMART_UPPERCASE_UKRAINIAN,
        &kmx_ldb_ukrainian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_UKRAINIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_LOWERCASE_UKRAINIAN,
        &kmx_ldb_ukrainian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_UKRAINIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
    {
        IMM_INPUT_MODE_SMART_FIRST_UPPERCASE_UKRAINIAN,
        &kmx_ldb_ukrainian,
        MMI_IME_REQUIRED_ALL_KEYS,
        MMI_IME_REQUIRED_ALL_NUM_KEYS & (~MMI_IME_REQUIRED_KEY_0),
        MMI_CSTAR_UDB_UKRAINIAN_START,
        MMI_CSTAR_UDB_SIZE_ALPHABETIC,
        NULL,
        mmi_ime_cstar_get_associates_alphabetic,
        mmi_ime_cstar_get_candidates_alphabetic
    },
#endif /* #if defined(__MMI_CSTAR_UKRAINIAN__) */

    {
        IMM_INPUT_MODE_MAX_NUM,
        0,
        0,
        0,
        0,
        0,
        NULL,
        NULL,
        NULL
    }
};

/*****************************************************************************
 * Local variables
 *****************************************************************************/

// The Cstar engine singleton
static mmi_ime_cstar_word_engine_struct    g_engine;
static const UI_character_type g_chinese_symbol_string[] = 
{
    0xff0c,
    0x3002,
    0x3001,
    0xff1a,
    0xff1b,
    0xff1f,
    0xff01,
    0x300a,
    0x300b,
    0x300e,
    0x300f,
    0x201c,
    0x201d,
    0xff08,
    0xff09,
    0x300c,
    0x300d,
    0x2018,
    0x2019,
    0xff0e,
    0xff1c,
    0xff1e,
    0xff5e,
    0xff3b,
    0xff3d,
    0x0020,
    0x0000
};

/*****************************************************************************
 *          Macros
 *****************************************************************************/

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_set_context
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
void    mmi_ime_word_set_context( U8 context )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    switch ( context )
    {
    case MMI_IME_WORD_CONTEXT_DEFAULT:
    case MMI_IME_WORD_CONTEXT_SMS:
    case MMI_IME_WORD_CONTEXT_SURNAME:
    case MMI_IME_WORD_CONTEXT_GIVENNAME:
        g_engine.get_context = context;
        break;

    default:
        break;
    }
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_init
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
MMI_BOOL mmi_ime_word_init( void )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    if ( MMI_FALSE != g_engine.is_inited )
        return MMI_TRUE;

    memset( &g_engine, 0, sizeof(mmi_ime_cstar_word_engine_struct) );

    g_engine.is_inited = MMI_TRUE;
    
#if defined(__MMI_IME_USER_DATABASE__)
	g_engine.is_inited = mmi_ime_word_load_user_database();
#endif
   
    return g_engine.is_inited;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_deinit
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
void mmi_ime_word_deinit( void )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    if ( MMI_FALSE != g_engine.is_inited )
    {
        memset( &g_engine, 0, sizeof(mmi_ime_cstar_word_engine_struct) );
        g_engine.is_inited = MMI_FALSE;
    }
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_leave_current_mode
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
void  mmi_ime_word_leave_current_mode(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    g_engine.curr_mode_info = NULL;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_change_mode
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
MMI_BOOL mmi_ime_word_change_mode(const sIMEModeDetails * mode_details_ptr, U32 reserved )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    S32                             ret_val = 0;
    mmi_ime_cstar_mode_info_struct_p      mode_info_ptr;


    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    if ( MMI_FALSE == g_engine.is_inited )
        return MMI_FALSE;

    mode_info_ptr = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info( (mmi_imm_input_mode_enum)mode_details_ptr->imm_mode_id );

    g_engine.curr_mode_info = NULL;
    
    if ( NULL == mode_info_ptr )
        return MMI_FALSE;

    g_engine.init_info.database = *(mode_info_ptr->ldb_ptr);
   
    #if defined(__MMI_IME_FUZZY_PINYIN__)
        g_engine.init_info.flags = (int)g_mmi_imm_enabled_fuzzy_pinyin;  
    #else
        g_engine.init_info.flags = 0;   
    #endif

#if defined(__MMI_IME_USER_DATABASE__)
    g_engine.init_info.user_data = &mmi_ime_cstar_user_data[mode_info_ptr->udb_start_block_index * MMI_CSTAR_UDB_BLOCK_SIZE / 2];
    g_engine.init_info.user_data_size = mode_info_ptr->udb_size * MMI_CSTAR_UDB_BLOCK_SIZE;
#else
    g_engine.init_info.user_data = NULL;
    g_engine.init_info.user_data_size = 0;
#endif

    

    if (mode_details_ptr->Lang_Special_Attrib & IME_LANG_ATTR_PHONETIC)
    {
    	#if defined(__MMI_CSTAR_TR_CHINESE__)
        if (mode_details_ptr->lang_id == IME_WRITING_LANG_ZHTW)
        {
            ret_val = (S32)kmx_zhuyin_initialize(&g_engine.cstar_engine, (const KMX_IME_ENGINE_INIT *)&g_engine.init_info);
        }
        #endif
        #if defined(__MMI_CSTAR_SM_CHINESE__)   
        if (mode_details_ptr->lang_id == IME_WRITING_LANG_ZHCN)
        {
            ret_val = (S32)kmx_pinyin_initialize(&g_engine.cstar_engine, (const KMX_IME_ENGINE_INIT *)&g_engine.init_info);
        }
        #endif
    }
 
    #if defined __MMI_CSTAR_STROKE_INPUT__
    if (mode_details_ptr->Lang_Special_Attrib & IME_LANG_ATTR_STROKE)
    {
        ret_val = (S32)kmx_stroke_initialize(&g_engine.cstar_engine, (const KMX_IME_ENGINE_INIT *)&g_engine.init_info);
    }
    #endif
    #if defined __MMI_SMART_ALPHABETIC_INPUT_METHODS__ || defined(__MMI_CSTAR__)
    if (mode_details_ptr->Lang_Special_Attrib & IME_LANG_ATTR_ALPHABETIC)
    {
        ret_val = (S32)kmx_latin_initialize(&g_engine.cstar_engine, (const KMX_IME_ENGINE_INIT *)&g_engine.init_info);
    }
    #endif

    if (ret_val == 0)
        return MMI_FALSE;
    
    if ( (mode_details_ptr->Mode_Special_Attrib & IME_MODE_ATTR_UPPERCASE) )
    {
        g_engine.case_type = MMI_IME_WORD_CAPITAL_STATE_UPPER;
    }
    else if ( mode_details_ptr->Mode_Special_Attrib & IME_MODE_ATTR_LOWERCASE )
    {
        g_engine.case_type = MMI_IME_WORD_CAPITAL_STATE_LOWER;
    }
    else if ( mode_details_ptr->Mode_Special_Attrib & IME_MODE_ATTR_TITLECASE )
    {
        g_engine.case_type = MMI_IME_WORD_CAPITAL_STATE_FIRST_UPPER;
    }
    else
    {
        g_engine.case_type = MMI_IME_WORD_CAPITAL_STATE_NONE;
    }

    g_engine.curr_mode_info = mode_info_ptr; /* Append new input mode */
    g_engine.input_mode = mode_info_ptr->input_mode;
        
    return MMI_TRUE;
}   


#if defined(__MMI_SMART_ALPHABETIC_INPUT_METHODS__) && defined(__MMI_IME_V3__)
void mmi_ime_reset_group_letters(const sIMEModeDetails * mode_details_ptr)
{
	#if 0// defined(__MMI_COSMOS_KEYPAD_SLIDER__) && defined(__MMI_IME_VK_TYPE_QWERTY__)
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
	#endif

	#if defined(__MMI_QWERTY_KEYPAD_SUPPORT__)
    	mmi_imm_qwerty_get_group_letters_for_cur_lang(mode_details_ptr->lang_id);
    	if( !(mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON))
            && IME_WRITING_LANG_ENUK!= mode_details_ptr->lang_id 
            && IME_WRITING_LANG_ABC!= mode_details_ptr->lang_id 
            && IME_WRITING_LANG_SW!= mode_details_ptr->lang_id
            && IME_WRITING_LANG_MS!= mode_details_ptr->lang_id
            && IME_WRITING_LANG_MS!= mode_details_ptr->lang_id
            && IME_WRITING_LANG_ID!= mode_details_ptr->lang_id)  /* these languages do not need group letter information*/
        {
            kmx_latin_set_letter_group(&g_engine.cstar_engine,(const unsigned short *)g_mmi_imm_group_letter_set);
        }
    #endif    /*__MMI_QWERTY_KEYPAD_SUPPORT__*/
        
    #if defined(__MMI_IME_VK_TYPE_QWERTY__)  && defined(__MMI_UI_VIRTUAL_KEYBOARD_DEFAULT_VERSION_3__)
        if ((mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY) && (mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
            if(IME_WRITING_LANG_ENUK!= mode_details_ptr->lang_id 
               && IME_WRITING_LANG_ABC!= mode_details_ptr->lang_id 
               && IME_WRITING_LANG_SW!= mode_details_ptr->lang_id
               && IME_WRITING_LANG_MS!= mode_details_ptr->lang_id
               && IME_WRITING_LANG_MS!= mode_details_ptr->lang_id
               && IME_WRITING_LANG_ID!= mode_details_ptr->lang_id)  /* these languages do not need group letter information*/
            {
                mmi_imm_get_group_letters_from_vk();
                kmx_latin_set_letter_group(&g_engine.cstar_engine,(const unsigned short *)g_mmi_imm_group_letter_set_for_vk);
            }
    #endif    /*__MMI_IME_VK_TYPE_QWERTY__*/
}
#endif

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_is_valid_key
 * DESCRIPTION
 * PARAMETERS
 *  input_mode    [IN]    Input mode
 * RETURNS
 *  Is valid key for this input mode
 *****************************************************************************/
MMI_BOOL mmi_ime_word_is_valid_key( mmi_imm_input_mode_enum input_mode, U16 key_code )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_ime_cstar_mode_info_struct_p  mode_info_p;
    U32 required_key;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    mode_info_p = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info(input_mode);

    if (mode_info_p == NULL)
        return MMI_FALSE;

    required_key = mode_info_p->required_keys;
    
    switch(key_code)
    {
    case KEY_LSK:
    case KEY_RSK:
    case KEY_CSK:
    case KEY_UP_ARROW:
    case KEY_DOWN_ARROW:
    case KEY_LEFT_ARROW:
    case KEY_RIGHT_ARROW:
        return MMI_TRUE;
    case KEY_0:
    case KEY_1:
    case KEY_2:
    case KEY_3:
    case KEY_4:
    case KEY_5:
    case KEY_6:
    case KEY_7:
    case KEY_8:
    case KEY_9:
        if (required_key & (MMI_IME_REQUIRED_KEY_0 << (key_code - KEY_0)))
        {
            return MMI_TRUE;
        }
        else
        {
            return MMI_FALSE;
        }
    case KEY_STAR:
        if (required_key & MMI_IME_REQUIRED_KEY_STAR)
        {
            return MMI_TRUE;
        }
        else
        {
            return MMI_FALSE;
        }
    case KEY_POUND:
        if (required_key & MMI_IME_REQUIRED_KEY_POUND)
        {
            return MMI_TRUE;
        }
        else
        {
            return MMI_FALSE;
        }
    default:
        return MMI_FALSE;
    }
    return MMI_FALSE;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_get_candidates
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
void mmi_ime_word_get_candidates( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    result_ptr->result_cnt = 0;
    
    if (g_engine.curr_mode_info)
    {
        if ( NULL != g_engine.curr_mode_info->get_cand_func )
        {
            g_engine.curr_mode_info->get_cand_func( param_ptr, result_ptr);
        }
    }
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_get_associates
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
void mmi_ime_word_get_associates( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    result_ptr->result_cnt = 0;
    
    if (g_engine.curr_mode_info)
    {
        if ( NULL != g_engine.curr_mode_info->get_assoc_func )
        {
            g_engine.curr_mode_info->get_assoc_func( param_ptr, result_ptr );
        }
    }
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_get_spellings
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
void mmi_ime_word_get_spellings( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    result_ptr->result_cnt = 0;

    if (g_engine.curr_mode_info)
    {
        if ( NULL != g_engine.curr_mode_info->get_spell_func )
        {
            g_engine.curr_mode_info->get_spell_func( param_ptr, result_ptr );
        }
    }
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_symbol_to_code
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
UI_character_type mmi_ime_word_symbol_to_code(U16 symbol)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    if (MMI_IMC_IS_SYMB_TONE(symbol))
    {
        switch (symbol)
        {
            case MMI_IMC_SYMB_TONE_1:
                return 0x02C9;
                
            case MMI_IMC_SYMB_TONE_2:
                return 0x02CA;
            case MMI_IMC_SYMB_TONE_3:
                return 0x02C7;
            case MMI_IMC_SYMB_TONE_4:
                return 0x02CB;
            case MMI_IMC_SYMB_TONE_5:
                return 0x02D9;
            default:
                ASSERT(0);
        }
    }
#if defined __MMI_CSTAR_STROKE_INPUT__
    else if (MMI_IMC_IS_SYMB_STROKE(symbol))
    {
        switch(symbol)
        {
        case MMI_IMC_SYMB_STROKE_WILDCARD:
            return 0xF000;
            break;
            
        case MMI_IMC_SYMB_STROKE_DOWN:
            return 0xF001;
            break;
            
        case MMI_IMC_SYMB_STROKE_DOT:
            return 0xF002;
            break;
            
        case MMI_IMC_SYMB_STROKE_OVER:
            return 0xF004;
            break;
            
        case MMI_IMC_SYMB_STROKE_OVER_DOWN:
            return 0xF005;
            break;
            
        case MMI_IMC_SYMB_STROKE_LEFT:
            return 0xF007;
            break;
            
        default:
            return 0;
            break;
        }
    }
#endif /* defined(__MMI_LANG_SM_CHINESE__) || defined(__MMI_LANG_TR_CHINESE__) */
#if defined(__MMI_LANG_SM_CHINESE__)
    else if (MMI_IMC_IS_SYMB_PY(symbol))
    {
        return symbol - MMI_IMC_SYMB_PY_BASE + 'a';
    }
#if defined(__MMI_CSTAR_PHRASE_INPUT__)    
    else if (symbol == MMI_IMC_SYMB_SEPARATER)
    {
        return 0x0027;
    }
#endif
#endif /* #if defined(__MMI_LANG_SM_CHINESE__) */
#if defined(__MMI_LANG_TR_CHINESE__)
    else if (MMI_IMC_IS_SYMB_ZY(symbol))
    {
        return symbol - MMI_IMC_SYMB_ZY_BASE + 0x3105;
    }
#endif /* #if defined(__MMI_LANG_TR_CHINESE__) */

    return 0;
}

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_code_to_symbol
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
U16  mmi_ime_word_code_to_symbol(UI_character_type code)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    switch (code)
    {
    case 0x002D:
        return MMI_IMC_SYMB_TONE_1;
        
    case 0x02CA:
        return MMI_IMC_SYMB_TONE_2;
        
    case 0x02C7:
        return MMI_IMC_SYMB_TONE_3;
        
    case 0x02CB:
        return MMI_IMC_SYMB_TONE_4;
        
    case 0x02D9:
        return MMI_IMC_SYMB_TONE_5;
#if defined __MMI_CSTAR_STROKE_INPUT__      
    case 0xF000:      
        return MMI_IMC_SYMB_STROKE_WILDCARD;
        
    case 0xF007:          
        return MMI_IMC_SYMB_STROKE_LEFT;
        
    case 0xF004:
        return MMI_IMC_SYMB_STROKE_OVER;
        
    case 0xF002:           
        return MMI_IMC_SYMB_STROKE_DOT;
        
    case 0xF001:  
        return MMI_IMC_SYMB_STROKE_DOWN;
        
    case 0xF005:      
        return MMI_IMC_SYMB_STROKE_OVER_DOWN;

#endif /* defined(__MMI_CSTAR_SM_CHINESE__) || defined(__MMI_CSTAR_TR_CHINESE__) */        
    default:
#ifdef __MMI_CSTAR_SM_CHINESE__
        if (code >= 0x0061 && code <= 0x007A) 
        {
            return code - 0x0061 + MMI_IMC_SYMB_PY_BASE; /* mmi_imc_symbol_pinyin_enum */
        }
#if defined(__MMI_CSTAR_PHRASE_INPUT__)    
        else if (code == 0x0027)
        {
            return MMI_IMC_SYMB_SEPARATER;
        }
#endif        
        else 
#endif /* __MMI_CSTAR_SM_CHINESE__ */
#ifdef __MMI_CSTAR_TR_CHINESE__
        if (code >= 0x3105 && code <= 0x3129)
        {
            return code - 0x3105 + MMI_IMC_SYMB_ZY_BASE; /* mmi_imc_symbol_bopomofo_enum */
        }
        else
#endif /* __MMI_CSTAR_TR_CHINESE__ */
        {
            return 0xFF;
        }
        break;
    }
    
    return 0xFF; 
}

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_is_symbol_key
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
MMI_BOOL  mmi_ime_word_is_symbol_key( mmi_imm_input_mode_enum input_mode, mmi_imc_key_custom_value key_code )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    mmi_ime_cstar_mode_info_struct_p      mode_info_ptr = NULL;        
    U32 symbol_keys = 0;
	const sIMEModeDetails *mode_detail1 = NULL, *mode_detail2 = NULL;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (input_mode == g_engine.curr_mode_info->input_mode)
    {
        symbol_keys = g_engine.curr_mode_info->symbol_keys;
    }
    else
    {
        mode_detail1 = mmi_imm_get_input_mode_array_item(input_mode);
        mode_detail2 = mmi_imm_get_input_mode_array_item(g_engine.curr_mode_info->input_mode);

		if (!mode_detail1 || !mode_detail2)
		{
			return MMI_FALSE;
		}

		if (mode_detail1->lang_id == mode_detail2->lang_id 
			&& (mode_detail1->Mode_Special_Attrib & IME_MODE_ATTR_SMART)
			&& (mode_detail2->Mode_Special_Attrib & IME_MODE_ATTR_SMART)
			&& (mode_detail1->Mode_Special_Attrib & IME_MODE_ATTR_TITLECASE))
		{
            symbol_keys = g_engine.curr_mode_info->symbol_keys;
		}
        else
		{
            mode_info_ptr = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info(input_mode );

            if (mode_info_ptr != NULL)
            {
                symbol_keys = mode_info_ptr->symbol_keys;
            }
        }
    }
    
    switch(key_code)
    {
    case MMI_IMC_KEY_UP:
    case MMI_IMC_KEY_DOWN:
    case MMI_IMC_KEY_LEFT:
    case MMI_IMC_KEY_RIGHT:
    case MMI_IMC_KEY_CONFIRM: 
    case MMI_IMC_KEY_CANCEL: 
    case MMI_IMC_KEY_CLEAR: 
        return MMI_FALSE;
    case MMI_IMC_KEY_SYM_0:
    case MMI_IMC_KEY_SYM_1:
    case MMI_IMC_KEY_SYM_2:
    case MMI_IMC_KEY_SYM_3:
    case MMI_IMC_KEY_SYM_4:
    case MMI_IMC_KEY_SYM_5:
    case MMI_IMC_KEY_SYM_6:
    case MMI_IMC_KEY_SYM_7:
    case MMI_IMC_KEY_SYM_8:
    case MMI_IMC_KEY_SYM_9:
        if (symbol_keys & (MMI_IME_REQUIRED_KEY_0 << (key_code - MMI_IMC_KEY_SYM_0)))
        {
            return MMI_TRUE;
        }
        else
        {
            return MMI_FALSE;
        }
    case MMI_IMC_KEY_SYM_STAR:
        if (symbol_keys & MMI_IME_REQUIRED_KEY_STAR)
        {
            return MMI_TRUE;
        }
        else
        {
            return MMI_FALSE;
        }
    case MMI_IMC_KEY_SYM_POUND:
        if (symbol_keys & MMI_IME_REQUIRED_KEY_POUND)
        {
            return MMI_TRUE;
        }
        else
        {
            return MMI_FALSE;
        }
    default:
        return MMI_FALSE;
    }
    
    return MMI_FALSE;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_is_redical
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
MMI_BOOL  mmi_ime_word_is_redicals(UI_character_type key_code )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return MMI_FALSE;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_is_wildcard
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
MMI_BOOL mmi_ime_word_is_wildcard(UI_character_type code)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (code == 0xF000)
    	return MMI_TRUE;
    return MMI_FALSE;
}

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_get_word_case
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
mmi_ime_word_capital_state_enum mmi_ime_word_get_word_case(void)
{
	/*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
	return g_engine.case_type;
}

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_change_word_case
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
void   mmi_ime_word_change_word_case(mmi_ime_word_capital_state_enum capital_state)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    g_engine.case_type = capital_state;
}

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_add_separator_to_candidate_buffer
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
void mmi_ime_word_add_separator_to_candidate_buffer(UI_character_type * destination_buffer, UI_character_type * source_buffer, S32 num)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    S32 i = 0, j = 0;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    while (i < num && source_buffer[i] != 0)
    {
        destination_buffer[j] = source_buffer[i];
        destination_buffer[j + 1] = 0; /* Default separator is '\0' */
        i++;
        j += 2;
    }

    destination_buffer[j] = 0;
}


#if defined(__MMI_IME_USER_DATABASE__)

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_add_new_word
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
mmi_ime_word_add_new_word_ret_value_enum mmi_ime_word_add_new_word(mmi_imm_input_mode_enum input_mode, UI_string_type str_ptr)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    sIMEModeDetails * mode_details_ptr = NULL;
    MMI_BOOL engine_changed = MMI_FALSE;
    mmi_imm_input_mode_enum   mode_bkup = IMM_INPUT_MODE_NONE;
    int ret_val = 0; 
    S32 str_len;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    mode_details_ptr = (sIMEModeDetails *)mmi_imm_get_input_mode_array_item(input_mode);

    if (mode_details_ptr == NULL)
    {
        return MMI_IME_WORD_ADD_NEW_WORD_FAILED;
    }

    if (input_mode != g_engine.input_mode) /* Change cstar engine to the specified input mode */
    {
       if(g_engine.input_mode == IMM_INPUT_MODE_NONE)
	   {
			return MMI_IME_WORD_ADD_NEW_WORD_FAILED;
	   }
		mode_bkup = g_engine.input_mode;
        
        if (!mmi_ime_word_change_mode((const sIMEModeDetails *)mode_details_ptr, 0))
        {
            mmi_ime_word_change_mode(mmi_imm_get_input_mode_array_item(mode_bkup), 0);
            
            return MMI_IME_WORD_ADD_NEW_WORD_FAILED;
        }
        else
        {
            engine_changed = MMI_TRUE;
        }
    }

    str_len = mmi_ucs2strlen((const S8 *)str_ptr);
        
    if (mode_details_ptr->Lang_Special_Attrib & IME_LANG_ATTR_PHONETIC)
    {
    #if defined(__MMI_CSTAR_TR_CHINESE__)
        if (mode_details_ptr->lang_id == IME_WRITING_LANG_ZHTW)
        {
            ret_val = kmx_zhuyin_update_cache(&g_engine.cstar_engine, (const unsigned short*)str_ptr, (unsigned short)str_len);
        }
    #endif 
    #if defined(__MMI_CSTAR_SM_CHINESE__)
        if (mode_details_ptr->lang_id == IME_WRITING_LANG_ZHCN)
        {
            ret_val = kmx_pinyin_update_cache(&g_engine.cstar_engine, (const unsigned short*)str_ptr, (unsigned short)str_len);
        }
    #endif
    }
    #if defined __MMI_CSTAR_STROKE_INPUT__
    if (mode_details_ptr->Lang_Special_Attrib & IME_LANG_ATTR_STROKE)
    {
        ret_val = kmx_stroke_update_cache(&g_engine.cstar_engine, (const unsigned short*)str_ptr, (unsigned short)str_len);
    }
    #endif
    #if defined __MMI_SMART_ALPHABETIC_INPUT_METHODS__
    if (mode_details_ptr->Lang_Special_Attrib & IME_LANG_ATTR_ALPHABETIC)
    {
        ret_val = kmx_latin_update_cache(&g_engine.cstar_engine, (const unsigned short*)str_ptr, (unsigned short)str_len);
    }
    #endif

    if (engine_changed && (mode_bkup != IMM_INPUT_MODE_NONE)) /* Resume cstar engine */
    {
        mmi_ime_word_change_mode(mmi_imm_get_input_mode_array_item(mode_bkup), 0);
    }

    if (ret_val != 0)
    {
        return MMI_IME_WORD_ADD_NEW_WORD_SUCCESS;
    }
    else
    {
        return MMI_IME_WORD_ADD_NEW_WORD_FAILED;
    }
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_scan_and_add_new_words
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
void mmi_ime_word_scan_and_add_new_words(UI_string_type str)
{
	/*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
	S32 str_len, i, ret_val = 0;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

	str_len = mmi_ucs2strlen((const S8 *)str);

	if (str_len == 0)
    {
        return;
	}
  #if defined __MMI_SMART_ALPHABETIC_INPUT_METHODS__
	for ( i = 0; g_mode_infos[i].input_mode != IMM_INPUT_MODE_MAX_NUM; ++i )
    {
        if ( g_mode_infos[i].get_cand_func == mmi_ime_cstar_get_candidates_alphabetic )
        {
            g_engine.init_info.database = *(g_mode_infos[i].ldb_ptr);
            g_engine.init_info.flags = 0;
            g_engine.init_info.user_data = &mmi_ime_cstar_user_data[g_mode_infos[i].udb_start_block_index * MMI_CSTAR_UDB_BLOCK_SIZE / 2];
            g_engine.init_info.user_data_size = g_mode_infos[i].udb_size * MMI_CSTAR_UDB_BLOCK_SIZE;
            ret_val = (S32)kmx_latin_initialize(&g_engine.cstar_engine, (const KMX_IME_ENGINE_INIT *)&g_engine.init_info);

            if (ret_val)
            {
                ret_val = kmx_latin_update_cache(&g_engine.cstar_engine, (const unsigned short*)str, (unsigned short)str_len);
            }
        }
    }
    #endif
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_update_word_frequency
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
MMI_BOOL mmi_ime_word_update_word_frequency(mmi_imm_input_mode_enum input_mode, UI_string_type str_ptr)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    return mmi_ime_word_add_new_word(input_mode, str_ptr);
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_load_user_database
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
MMI_BOOL mmi_ime_word_load_user_database(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    FS_HANDLE file_handle;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    file_handle = mmi_ime_cstar_open_file(MMI_IME_USER_DATABASE_PATH, MMI_IME_USER_DATABASE_FILE, MMI_TRUE);
    
    if (file_handle == -1)
        return MMI_FALSE;

    mmi_ime_cstar_read_file(file_handle, &mmi_ime_cstar_user_data[0], sizeof(mmi_ime_cstar_user_data) );
    
    mmi_ime_cstar_close_file(file_handle);

    return MMI_TRUE;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_save_user_database
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
MMI_BOOL mmi_ime_word_save_user_database(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    FS_HANDLE file_handle;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    file_handle = mmi_ime_cstar_open_file(MMI_IME_USER_DATABASE_PATH, MMI_IME_USER_DATABASE_FILE, MMI_TRUE);
    
    if (file_handle == -1)
        return MMI_FALSE;

    mmi_ime_cstar_write_file(file_handle, &mmi_ime_cstar_user_data[0], sizeof(mmi_ime_cstar_user_data) );
    mmi_ime_cstar_close_file(file_handle);

    return MMI_TRUE;

}

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_open_file
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 ****************************************************************************/
static FS_HANDLE mmi_ime_cstar_open_file(PU16 path_name_ptr, PU16 file_name_ptr, MMI_BOOL is_create_always)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    int ret_val;
    FS_HANDLE file_handle;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_ASSERT(NULL != path_name_ptr);
    MMI_ASSERT(NULL != file_name_ptr);

    ret_val = FS_SetCurrentDir(path_name_ptr);
    if (ret_val < 0)
    {
        ret_val = FS_CreateDir(path_name_ptr);
        if (ret_val < 0 )
        {
            return -1;
        }
        ret_val = FS_SetCurrentDir(path_name_ptr);
        if (ret_val < 0)
        {
            return -1;
        }
    }

    FS_SetAttributes(file_name_ptr, FS_ATTR_ARCHIVE);

    /* try to open file */
    file_handle = FS_Open(file_name_ptr, FS_READ_WRITE | FS_ATTR_ARCHIVE);
    if (file_handle < 0)    /* failed to open existing file, or file not exists */
    {
        if (MMI_FALSE == is_create_always)
        {
            return -1;
        }

        /* try to create file */
        file_handle = FS_Open(file_name_ptr, FS_READ_WRITE | FS_CREATE_ALWAYS | FS_ATTR_ARCHIVE);
        if (file_handle < 0)
        {
            return -1;
        }
    }

    return file_handle;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_close_file
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 ****************************************************************************/
static void mmi_ime_cstar_close_file(FS_HANDLE file_handle)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (file_handle < 0)
        return;

    FS_Close(file_handle);
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_write_file
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static U32 mmi_ime_cstar_write_file(FS_HANDLE file_handle, PU16 data_ptr, U32 size_in_byte)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int ret_val;
    U32 writen;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (file_handle < 0)
        return 0;

    writen = 0;
    ret_val = FS_Write(file_handle, (void*)data_ptr, size_in_byte, &writen);
    if (ret_val < 0)
        return 0;

    return writen;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_read_file
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static U32 mmi_ime_cstar_read_file(FS_HANDLE file_handle, PU16 data_ptr, U32 size_in_byte)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int ret_val;
    U32 readed;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (file_handle < 0)
        return 0;

    readed = 0;
    ret_val = FS_Read(file_handle, (void*)data_ptr, size_in_byte, &readed);
    if (ret_val < 0)
        return 0;

    return readed;
}

#endif /* defined(__MMI_IME_USER_DATABASE__) */


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_map_char_to_symbol
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
mmi_imc_symbol_key_enum mmi_ime_word_map_char_to_symbol(mmi_imm_input_mode_enum input_mode, UI_character_type char_code)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_ime_cstar_mode_info_struct_p      mode_info_ptr;
    unsigned short                        key_code;
    int                                   ret = 0;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    mode_info_ptr = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info(input_mode);
    
    if ( NULL == mode_info_ptr )
        return MMI_IMC_SYMB_KEY_INVALID;

    #if defined __MMI_SMART_ALPHABETIC_INPUT_METHODS__
    ret = kmx_latin_query_key_map(*(mode_info_ptr->ldb_ptr), char_code, &key_code);
    #endif
    if (!ret)
    {
        return MMI_IMC_SYMB_KEY_INVALID;
    }
    else
    {
        return (key_code + MMI_IMC_SYMB_KEY_BASE);
    }
}


#if defined(__MMI_CSTAR_SM_CHINESE__) || defined(__MMI_CSTAR_TR_CHINESE__)
/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_associates_chinese
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void  mmi_ime_cstar_get_associates_chinese( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    unsigned short buffer[KMX_MAX_ASSOCIATION_QUERY_BUFFER];
    int ret_val;
    S32 i, j, cnt;
    void * database;
    S32 pre_string_len = 0;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    ASSERT( NULL != param_ptr );
   
    if (param_ptr->pre_string[0] == 0)
    {
        return;
    }

#if defined(__MMI_CSTAR_SM_CHINESE__) && defined  __MMI_CSTAR_STROKE_INPUT__
    if (g_engine.init_info.database == kmx_ldb_stroke_gb2312)
    {
    #if defined(__MMI_IME_SMART_WITH_INPUT_AREA__)
        database = (void *)kmx_ldb_pinyin_cizu;
    #else
        database = (void *)kmx_ldb_pinyin_danzi;
    #endif
    }
    else 
#endif /* defined(__MMI_CSTAR_SM_CHINESE__) */
#if defined(__MMI_CSTAR_TR_CHINESE__)
    if (g_engine.init_info.database == kmx_ldb_stroke_big5)
    {
    #if defined(__MMI_IME_SMART_WITH_INPUT_AREA__)
        database = (void *)kmx_ldb_zhuyin_cizu;
    #else
        database = (void *)kmx_ldb_zhuyin_danzi;
    #endif
    }
    else
#endif /* defined(__MMI_CSTAR_TR_CHINESE__) */
    {
        database = (void *)g_engine.init_info.database;
    }
    
#if defined(__MMI_CSTAR_SM_CHINESE__)
    #if defined(__MMI_IME_SMART_WITH_INPUT_AREA__)
    if (database != kmx_ldb_pinyin_cizu)
    #else
    if (database != kmx_ldb_pinyin_danzi)
    #endif
#endif /* defined(__MMI_CSTAR_SM_CHINESE__) */  
#if defined(__MMI_CSTAR_TR_CHINESE__)
    #if defined(__MMI_IME_SMART_WITH_INPUT_AREA__)
    if (database != kmx_ldb_zhuyin_cizu)
    #else
	if (database != kmx_ldb_zhuyin_danzi)
    #endif
#endif /* defined(__MMI_CSTAR_TR_CHINESE__) */
    {
        return;
    }
    
    pre_string_len = mmi_ucs2strlen((const S8*)param_ptr->pre_string);

    if (pre_string_len == 0)
    {
        return;
    }
    
    ret_val = kmx_chinese_query_association((const void *)database,
                                            (unsigned short) param_ptr->pre_string[pre_string_len - 1],
                                            buffer,
                                            KMX_MAX_ASSOCIATION_QUERY_BUFFER);

    if (!ret_val)
    {
        return;
    }

    i = param_ptr->first_index;
    j = 0;
    cnt = 0;
    
    while(i < KMX_MAX_ASSOCIATION_QUERY_BUFFER - 1 && cnt < param_ptr->desired_cnt)
    {
        if (buffer[i] == 0 )
        {
            break;
        }
        
        result_ptr->result_buffer[j++] = (UI_character_type)buffer[i++];
        result_ptr->result_buffer[j++] = 0;
        cnt++;
    }
	result_ptr->result_buffer[j] = 0;
    result_ptr->result_cnt = cnt;
    
    if (cnt == param_ptr->desired_cnt)
    {
        if (i < KMX_MAX_ASSOCIATION_QUERY_BUFFER - 1)
        {
            if(buffer[i] != 0)
            {
                result_ptr->next_page = MMI_TRUE;
            }
            else
            {
                result_ptr->next_page = MMI_FALSE;
            }
        }
        else
        {
            result_ptr->next_page = MMI_FALSE;
        }
    }
    else
    {
        result_ptr->next_page = MMI_FALSE;
    }
}
#endif /* #if defined(__MMI_CSTAR_SM_CHINESE__) || defined(__MMI_CSTAR_TR_CHINESE__) */

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_associates_alphabetic
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void  mmi_ime_cstar_get_associates_alphabetic( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_engine_get_char_info
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
MMI_BOOL mmi_ime_word_engine_get_char_info(UI_character_type code, UI_string_type info_buffer, S32 buffer_size, mmi_imm_input_mode_enum mode)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    const sIMEModeDetails * mode_details_ptr;
    MMI_BOOL ret_val = MMI_FALSE;
    S32 i=0;
#if defined(__MMI_CSTAR_SM_CHINESE__)
    KMX_CHAR_PINYIN  pinyin;
#endif
#if defined(__MMI_CSTAR_TR_CHINESE__)
    KMX_CHAR_ZHUYIN  zhuyin;
#endif
    char stroke_buffer[10];
    mmi_ime_cstar_mode_info_struct_p mode_info_ptr;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    mode_details_ptr = mmi_imm_get_input_mode_array_item(mode);

    //MMI_ASSERT(mode_details_ptr != NULL);
    /* people are not wrapping where they are using */
    if ( mode_details_ptr == NULL)
    	return MMI_FALSE;
    
    switch(mode)
    {
    case IMM_INPUT_MODE_QUICK_SEARCH_BOPOMO:
    case IMM_INPUT_MODE_TR_BOPOMO:
    case IMM_INPUT_MODE_SM_PINYIN:
    case IMM_INPUT_MODE_QUICK_SEARCH_PINYIN:
    case IMM_INPUT_MODE_QUICK_SEARCH_SM_STROKE:
    case IMM_INPUT_MODE_QUICK_SEARCH_TR_STROKE:
    case IMM_INPUT_MODE_SM_STROKE:
    case IMM_INPUT_MODE_TR_STROKE:
        mode_info_ptr = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info(mode);
        break;

    default:
        return MMI_FALSE;
        break;
    }

    MMI_ASSERT(mode_info_ptr != NULL);

    g_engine.init_info.database = *(mode_info_ptr->ldb_ptr);
    g_engine.init_info.flags = 0;

#if defined(__MMI_IME_USER_DATABASE__)
    g_engine.init_info.user_data = &mmi_ime_cstar_user_data[mode_info_ptr->udb_start_block_index * MMI_CSTAR_UDB_BLOCK_SIZE / 2];
    g_engine.init_info.user_data_size = mode_info_ptr->udb_size * MMI_CSTAR_UDB_BLOCK_SIZE;
#else
    g_engine.init_info.user_data = NULL;
    g_engine.init_info.user_data_size = 0;
#endif
    
    if (mode_details_ptr->Lang_Special_Attrib & IME_LANG_ATTR_ALPHABETIC)
    {
    #if defined(__MMI_CSTAR_TR_CHINESE__)
        if (mode_details_ptr->lang_id == IME_WRITING_LANG_ZHTW)
        {
            ret_val = (S32)kmx_zhuyin_initialize(&g_engine.cstar_engine, (const KMX_IME_ENGINE_INIT *)&g_engine.init_info);
        }
    #endif
    #if defined(__MMI_CSTAR_SM_CHINESE__)       	
        if (mode_details_ptr->lang_id == IME_WRITING_LANG_ZHCN)
        {
            ret_val = (S32)kmx_pinyin_initialize(&g_engine.cstar_engine, (const KMX_IME_ENGINE_INIT *)&g_engine.init_info);
        }
    #endif
    }
    #if defined __MMI_CSTAR_STROKE_INPUT__
    else if (mode_details_ptr->Lang_Special_Attrib & IME_LANG_ATTR_STROKE)
    {
        ret_val = (S32)kmx_stroke_initialize(&g_engine.cstar_engine, (const KMX_IME_ENGINE_INIT *)&g_engine.init_info);
    }
    #endif
    MMI_ASSERT(ret_val);
    
    switch(mode)
    {
    case IMM_INPUT_MODE_QUICK_SEARCH_BOPOMO:
    case IMM_INPUT_MODE_TR_BOPOMO:
#if defined(__MMI_CSTAR_TR_CHINESE__)
        ret_val = kmx_chinese_query_zhuyin(*(mode_info_ptr->ldb_ptr), code, &zhuyin);
        if (ret_val)
        {
            for (i = 0; i < zhuyin.length && i < buffer_size; i++)
            {
                info_buffer[i] = zhuyin.string[i];
            }
            info_buffer[i] = 0;
        }
#endif /* defined(__MMI_CSTAR_TR_CHINESE__) */
        break;
    case IMM_INPUT_MODE_QUICK_SEARCH_PINYIN:
    case IMM_INPUT_MODE_SM_PINYIN:
#if defined(__MMI_CSTAR_SM_CHINESE__)
        ret_val = kmx_chinese_query_pinyin(*(mode_info_ptr->ldb_ptr), code, &pinyin);
        if (ret_val)
        {
            for (i = 0; i < pinyin.length && i < buffer_size; i++)
            {
                info_buffer[i] = pinyin.string[i];
            }
            info_buffer[i] = 0;
        }
#endif /* defined(__MMI_CSTAR_SM_CHINESE__) */
        break;
    case IMM_INPUT_MODE_QUICK_SEARCH_SM_STROKE:
    case IMM_INPUT_MODE_QUICK_SEARCH_TR_STROKE:
    case IMM_INPUT_MODE_TR_STROKE:
    case IMM_INPUT_MODE_SM_STROKE:
#if defined __MMI_CSTAR_STROKE_INPUT__
        ret_val = kmx_chinese_query_stroke(*(mode_info_ptr->ldb_ptr), code, stroke_buffer, 10);
        if (ret_val)
        {
            for (i = 0; stroke_buffer[i] && i < buffer_size; i++)
            {
                switch(stroke_buffer[i])
                {
                case KMX_STROKE_HENG:
                    info_buffer[i] = 0xF004;
                    break;
                    
                case KMX_STROKE_SHU:
                    info_buffer[i] = 0xF001;
                    break;
                    
                case KMX_STROKE_PIE:
                    info_buffer[i] = 0xF007;
                    break;
                    
                case KMX_STROKE_DIAN:
                    info_buffer[i] = 0xF002;
                    break;
                    
                case KMX_STROKE_ZHE:
                    info_buffer[i] = 0xF005;
                    break;
                    
                case KMX_STROKE_WILDCARD:
                    info_buffer[i] = 0xFF1F;
                    break;
                    
                default:
                    break;
                }
                
            }
            info_buffer[i] = 0;
        }
#endif /* defined(__MMI_CSTAR_SM_CHINESE__) || defined(__MMI_CSTAR_TR_CHINESE__) */

        break;

    default:
        return MMI_FALSE;
        break;
    }

    /* Resume current input mode */
	if (g_engine.input_mode != IMM_INPUT_MODE_NONE)
    {
        mmi_ime_word_change_mode(mmi_imm_get_input_mode_array_item(g_engine.input_mode), 0); 
	}

    if (ret_val == 0)
    {
        return MMI_FALSE;
    }
    else
    {
        return MMI_TRUE;
    }
}
 #if defined __MMI_SMART_ALPHABETIC_INPUT_METHODS__ || defined(__MMI_CSTAR_MULTITAP__)
/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_candidates_alphabetic
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void  mmi_ime_cstar_get_candidates_alphabetic( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U16  i, j, k;
    int ret_val;
    unsigned short match_flags;
    KMX_LATIN_MATCH_RESULT match_result;
#if defined(__MMI_IME_USER_DATABASE__)
    MMI_BOOL new_word_item = MMI_FALSE;
#endif
	#if defined(__MMI_IME_V3__)
    unsigned char input_symbol[MMI_IMC_MAX_INPUT_SYMBOL_BUFFSIZE];
    unsigned short input_string[MMI_IMC_MAX_INPUT_SYMBOL_BUFFSIZE];
	MMI_BOOL is_grid_state = FALSE;
	if(mmi_imc_get_state() == MMI_IMC_STATE_CAND_SELECTING_GRID_ALPHABETIC || mmi_imc_get_state() == MMI_IMC_STATE_CAND_SELECTING_GRID)
	{
		is_grid_state = TRUE;
	}
#else
    unsigned char input_string[MMI_IMC_MAX_INPUT_SYMBOL_BUFFSIZE];
#endif
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    ASSERT( NULL != param_ptr );
    
    if ( 0 == param_ptr->elembuf_cnt )
        return;
#if defined(__MMI_IME_V3__)
    #if !defined(__MMI_QWERTY_KEYPAD_SUPPORT__)
        if ((mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY) && (mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
        {
			for (i = 0; i < param_ptr->elembuf_cnt; i++)
				{
					input_string[i] = param_ptr->elembuf_ptr[i];
				} 
        }
		else
		{
			if(is_grid_state && mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY)
			{
					for (i = 0; i < param_ptr->elembuf_cnt; i++)
				{
					input_string[i] = param_ptr->elembuf_ptr[i];
				} 
			}
			else
			{
				for (i = 0; i < param_ptr->elembuf_cnt; i++)
				{
					input_symbol[i] = param_ptr->elembuf_ptr[i] - MMI_IMC_SYMB_KEY_BASE + '0';
				}
			}
		}
    #else
        if( !(mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
        {	if(is_grid_state && mmi_imm_get_keyboard_type() != IMM_KEYPAD_QWERTY)
			{
				for (i = 0; i < param_ptr->elembuf_cnt; i++)
				{
					input_symbol[i] = param_ptr->elembuf_ptr[i] - MMI_IMC_SYMB_KEY_BASE + '0';
				}
			}
			else
			{
				for (i = 0; i < param_ptr->elembuf_cnt; i++)
				{
					input_string[i] = param_ptr->elembuf_ptr[i];
				}
			}
        }
        else
		{
			if ((mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY) && (mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
			{
				for (i = 0; i < param_ptr->elembuf_cnt; i++)
				{
					input_string[i] = param_ptr->elembuf_ptr[i];
				}
			}
			else
			{
				for (i = 0; i < param_ptr->elembuf_cnt; i++)
				{
					input_symbol[i] = param_ptr->elembuf_ptr[i] - MMI_IMC_SYMB_KEY_BASE + '0';
				}
			}
		}
    #endif
#else
    for (i = 0; i < param_ptr->elembuf_cnt; i++)
    {
        input_string[i] = param_ptr->elembuf_ptr[i] - MMI_IMC_SYMB_KEY_BASE + '0';
    }
#endif
    switch(g_engine.case_type)
    {
	case MMI_IME_WORD_CAPITAL_STATE_FIRST_UPPER:
		match_flags = KMX_LATIN_INITIAL_CASE;
		break;
	case MMI_IME_WORD_CAPITAL_STATE_UPPER:
		match_flags = KMX_LATIN_UPPER_CASE;
		break;
	case MMI_IME_WORD_CAPITAL_STATE_LOWER:
        match_flags = KMX_LATIN_LOWER_CASE;
		break;
	default:
        match_flags = KMX_LATIN_INITIAL_CASE;
		break;
    }

#if defined(__MMI_IME_MAGIC_ONE__)
    if (g_engine.input_mode == IMM_INPUT_MODE_MAGIC_NUMBER)
        match_flags |= KMX_LATIN_NUMBER_FIRST;
#endif  

#if defined(__MMI_IME_V3__)
#if !defined(__MMI_QWERTY_KEYPAD_SUPPORT__)
    if ((mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY) && (mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
	{
		 ret_val = kmx_latin_query_association_ex(&g_engine.cstar_engine, 
                             input_string, 
                             param_ptr->elembuf_cnt,
                             match_flags, 
                             param_ptr->first_index,
                             &match_result);
	}
	else
	{
        if(is_grid_state && mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY)
		{
			ret_val = kmx_latin_query_association_ex(&g_engine.cstar_engine, 
                             input_string, 
                             param_ptr->elembuf_cnt,
                             match_flags, 
                             param_ptr->first_index,
                             &match_result);
		}
		else
		{
			ret_val = kmx_latin_match(&g_engine.cstar_engine, 
                              NULL, 
                              (char*)input_symbol, 
                              param_ptr->elembuf_cnt, 
                              match_flags, 
                              param_ptr->first_index,
                              &match_result);
		}
    }
#else
    if( !(mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
    {	
      	if(is_grid_state && mmi_imm_get_keyboard_type() != IMM_KEYPAD_QWERTY)
			{
				ret_val = kmx_latin_match(&g_engine.cstar_engine, 
                              NULL, 
                              (char*)input_symbol, 
                              param_ptr->elembuf_cnt, 
                              match_flags, 
                              param_ptr->first_index,
                              &match_result);
			}
			else
			{
				ret_val = kmx_latin_query_association_ex(&g_engine.cstar_engine, 
                             input_string, 
                             param_ptr->elembuf_cnt,
                             match_flags, 
                             param_ptr->first_index,
                             &match_result);
			}
		
    }
    else
	{
		if ((mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY) && (mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
		{
			ret_val = kmx_latin_query_association_ex(&g_engine.cstar_engine, 
                             input_string, 
                             param_ptr->elembuf_cnt,
                             match_flags, 
                             param_ptr->first_index,
                             &match_result);
		}
		else
		{
			 ret_val = kmx_latin_match(&g_engine.cstar_engine, 
                              NULL, 
                              (char*)input_symbol, 
                              param_ptr->elembuf_cnt, 
                              match_flags, 
                              param_ptr->first_index,
                              &match_result);
		}
	}
#endif
#else
    ret_val = kmx_latin_match(&g_engine.cstar_engine, 
                              NULL, 
                              (char*)input_string, 
                              param_ptr->elembuf_cnt, 
                              match_flags, 
                              param_ptr->first_index,
                              &match_result);
#endif
    if (!ret_val)
    {
    #if defined(__MMI_IME_USER_DATABASE__)
    #if defined(__MMI_IME_V3__)
        #if !defined(__MMI_QWERTY_KEYPAD_SUPPORT__)
             if ((mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY) && (is_grid_state || mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
			 {
				ret_val = kmx_latin_query_association_ex(&g_engine.cstar_engine, 
                             input_string, 
                             param_ptr->elembuf_cnt,
                             match_flags, 
                             param_ptr->first_index-1,
                             &match_result);
			}
			else
			{
				ret_val = kmx_latin_match(&g_engine.cstar_engine, 
                              NULL, 
                              (char*)input_symbol, 
                              param_ptr->elembuf_cnt, 
                              match_flags, 
                              param_ptr->first_index - 1,
                              &match_result);
			}
        #else
            if( !(mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
            {
				if(is_grid_state && mmi_imm_get_keyboard_type() != IMM_KEYPAD_QWERTY)
				{
					 ret_val = kmx_latin_match(&g_engine.cstar_engine, 
                              NULL, 
                              (char*)input_symbol, 
                              param_ptr->elembuf_cnt, 
                              match_flags, 
                              param_ptr->first_index - 1,
                              &match_result);
				}
				else
				{
					ret_val = kmx_latin_query_association_ex(&g_engine.cstar_engine, 
                             input_string, 
                             param_ptr->elembuf_cnt,
                             match_flags, 
                             param_ptr->first_index - 1,
                             &match_result);
				}
            }
            else
			{
				if ((mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY) && (mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
				{
					ret_val = kmx_latin_query_association_ex(&g_engine.cstar_engine, 
                             input_string, 
                             param_ptr->elembuf_cnt,
                             match_flags, 
                             param_ptr->first_index - 1,
                             &match_result);
				}
				else
				{
					 ret_val = kmx_latin_match(&g_engine.cstar_engine, 
                              NULL, 
                              (char*)input_symbol, 
                              param_ptr->elembuf_cnt, 
                              match_flags, 
                              param_ptr->first_index - 1,
                              &match_result);
				}
			}
        #endif
    #else
        ret_val = kmx_latin_match(&g_engine.cstar_engine, 
                              NULL, 
                              (char*)input_string, 
                              param_ptr->elembuf_cnt, 
                              match_flags, 
                              param_ptr->first_index - 1,
                              &match_result);
		#endif
        if (ret_val != 0)
        {
            result_ptr->result_cnt = 1;
            result_ptr->next_page = MMI_FALSE;
            result_ptr->result_buffer[0] = MMI_IME_USER_DATABASE_NEW_WORD;
            result_ptr->result_buffer[1] = 0;
            
            return;
        }
    #endif
    
        return;
    
    }

    if (match_result.count < param_ptr->desired_cnt)
    {
        result_ptr->result_cnt = (U8)match_result.count;

        if (match_result.count == KMX_MAX_WORD_MATCH
            && match_result.more_available)
        {
            result_ptr->next_page = MMI_TRUE;
        }
        else
        {
            result_ptr->next_page = MMI_FALSE;
    #if defined(__MMI_IME_USER_DATABASE__)
            new_word_item = MMI_TRUE;
    #endif
        }    
    }
    else if (match_result.count == param_ptr->desired_cnt )
    {
        result_ptr->result_cnt = (U8)match_result.count;
        
        if (match_result.more_available)
        {
            result_ptr->next_page = MMI_TRUE;
        }
        else
        {
        #if defined(__MMI_IME_USER_DATABASE__)
            result_ptr->next_page = MMI_TRUE;
        #else
            result_ptr->next_page = MMI_FALSE;
        #endif
        }
    }
    else
    {
        result_ptr->result_cnt = param_ptr->desired_cnt;
        result_ptr->next_page = MMI_TRUE;
    }

    for (i = 0, k = 0; i < result_ptr->result_cnt; i++)
    {
        for (j = 0; j < match_result.table[i].length; j ++)
        {
            result_ptr->result_buffer[k++] = (UI_character_type)match_result.table[i].string[j];
        }
        
        result_ptr->result_buffer[k++] = 0;
    }
    /*    
#if defined(__MMI_IME_USER_DATABASE__)
    if (result_ptr->next_page)
    {
        result_ptr->result_buffer[k] = MMI_IME_USER_DATABASE_NEW_WORD;
        result_ptr->result_buffer[k + 1] = 0;
        result_ptr->result_cnt++;
    }
#endif*/
    result_ptr->result_buffer[k] = 0; 
        
    if ( result_ptr->result_cnt > 0 )
    {
        /* adjust result case */
        mmi_ime_cstar_change_candidates_case(result_ptr);
    }
}

#endif


#if defined __MMI_CSTAR_STROKE_INPUT__
/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_spellings_stroke
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void   mmi_ime_cstar_get_spellings_stroke( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U8  i;
    U8  symb;
    UI_string_type temp_str;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    ASSERT( NULL != param_ptr );
    
    if ( 0 == param_ptr->elembuf_cnt )
        return;
    
    temp_str = result_ptr->result_buffer;
    
    for ( i = 0; i < param_ptr->elembuf_cnt; ++i )
    {
        symb = param_ptr->elembuf_ptr[i];
        if ( MMI_FALSE != MMI_IMC_IS_SYMB_KEY(symb) )
        {
            if (g_cstar_keys_stroke[symb - MMI_IMC_SYMB_KEY_BASE])
            {
                *temp_str = mmi_ime_word_symbol_to_code((U8)g_cstar_keys_stroke[symb - MMI_IMC_SYMB_KEY_BASE]);
                temp_str++;
            }
            else /* Invalid key */
            {
                i = 0;
                temp_str = result_ptr->result_buffer;
                break;
            }
        }
        else
        {
            i = 0;
            temp_str = result_ptr->result_buffer;
            break;
        }       
    }

    *temp_str = 0;

    result_ptr->result_cnt = i;
    
}

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_candidates_stroke
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void   mmi_ime_cstar_get_candidates_stroke( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    char stroke_string[KMX_MAX_STROKE_LENGTH];
    S32 i;
    int ret_val;
    KMX_STROKE_MATCH_RESULT match_result;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    ASSERT( NULL != param_ptr );
    
    if ( 0 == param_ptr->elembuf_cnt )
    {
        return;
    }
    if(param_ptr->elembuf_cnt >27)
	{
		return;
	}
    if (param_ptr->elembuf_cnt == 1 && param_ptr->elembuf_ptr[0] == MMI_IMC_SYMB_KEY_7)
    {
        S32 cnt = 0;
        UI_character_type cand = NULL;
        for (cnt = 0; cnt <= param_ptr->desired_cnt & (cand = g_chinese_symbol_string[param_ptr->first_index + cnt]) != 0; cnt ++)
        {
            result_ptr->result_buffer[(cnt<<1)] = cand;
            result_ptr->result_buffer[(cnt<<1) + 1] = 0x00; 
        }
        if (cnt >= param_ptr->desired_cnt)
        {
            result_ptr->next_page = MMI_TRUE;
            result_ptr->result_cnt = param_ptr->desired_cnt;
        }
        else
        {
            result_ptr->next_page = MMI_FALSE;
            result_ptr->result_cnt = cnt;
        }

    }

    for(i = 0; i < param_ptr->elembuf_cnt; i++)
    {
        stroke_string[i] = g_cstar_codes_stroke[param_ptr->elembuf_ptr[i] - MMI_IMC_SYMB_STROKE_BASE];
    }
    
    stroke_string[i] = 0;
    
    ret_val = kmx_stroke_match(&g_engine.cstar_engine, 
                               stroke_string, 
                               (unsigned short)param_ptr->elembuf_cnt,
                               (unsigned short)param_ptr->first_index,
                               &match_result);

    if (!ret_val)
    {
        return;
    }

    if (match_result.count < param_ptr->desired_cnt)
    {
        result_ptr->result_cnt = (U8)match_result.count;
        result_ptr->next_page = MMI_FALSE;
    }
    else if (match_result.count == param_ptr->desired_cnt )
    {
        result_ptr->result_cnt = (U8)match_result.count;
        
        if (match_result.more_available)
        {
            result_ptr->next_page = MMI_TRUE;
        }
        else
        {
            result_ptr->next_page = MMI_FALSE;
        }
    }
    else
    {
        result_ptr->result_cnt = param_ptr->desired_cnt;
        result_ptr->next_page = MMI_TRUE;
    }

    mmi_ime_word_add_separator_to_candidate_buffer(result_ptr->result_buffer, (UI_character_type *)match_result.table, result_ptr->result_cnt);
}
#endif /* #if defined(__MMI_CSTAR_SM_CHINESE__) || defined(__MMI_CSTAR_TR_CHINESE__) */

#if defined(__MMI_CSTAR_SM_CHINESE__)
/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_spellings_pinyin_multitap
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void   mmi_ime_cstar_get_spellings_pinyin_multitap( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    U8          i;
    UI_string_type temp_str;
    U8          symb;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    ASSERT( NULL != param_ptr );
    
    if ( 0 == param_ptr->elembuf_cnt )
        return;

    temp_str = result_ptr->result_buffer;
    
    for ( i = 0; i < param_ptr->elembuf_cnt; i++ )
    {
        symb = param_ptr->elembuf_ptr[i];
        if ( MMI_FALSE != MMI_IMC_IS_SYMB_PY( symb ) )
        {
            *temp_str = mmi_ime_word_symbol_to_code(symb);
            temp_str++;
        }
        else
        {
            i = 0;
            temp_str = result_ptr->result_buffer;
            break;
        }
    }

    *temp_str = 0;
    result_ptr->result_cnt = i;
}


#if defined(__MMI_CSTAR_SMART_PHONETIC_INPUT__)

#ifndef __MMI_IME_SMART_WITH_INPUT_AREA__
/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_spellings_pinyin_smart
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void mmi_ime_cstar_get_spellings_pinyin_smart( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    U16  i, j, k;
    char digit_string[MMI_IMC_MAX_INPUT_SYMBOL_BUFFSIZE];
    int ret_val;
    KMX_PINYIN_COMPOSITION     pinyin_composition;
    KMX_PINYIN_MATCH_RESULT     pinyin_match_result;
    KMX_PINYIN_WORD_MATCH_RESULT    word_match_result;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    ASSERT( NULL != param_ptr );
    
    if ( 0 == param_ptr->elembuf_cnt )
        return;

    for (i = 0; i < param_ptr->elembuf_cnt; i++)
    {
        if (param_ptr->elembuf_ptr[i] == MMI_IMC_SYMB_KEY_0)
        {
            digit_string[i] = 0x20;
        }
        else
        {
            digit_string[i] = param_ptr->elembuf_ptr[i] - MMI_IMC_SYMB_KEY_BASE + '0';
        }
    }
    
    digit_string[i] = 0;
    
    ret_val = kmx_digit_pinyin_match(&g_engine.cstar_engine, 
                                     (const char *)digit_string,
                                     (unsigned short)param_ptr->elembuf_cnt,
                                     KMX_PINYIN_MATCH_INDEX_NONE,
                                     0,
                                     &pinyin_composition,
                                     &pinyin_match_result,
                                     &word_match_result);

    if (!ret_val || pinyin_match_result.count == 0)
    {
        return;
    }

    if ((U8)(pinyin_match_result.count - param_ptr->first_index) > param_ptr->desired_cnt)
    {
        result_ptr->result_cnt = param_ptr->desired_cnt;
        result_ptr->next_page = MMI_TRUE;
    }
    else
    {
        result_ptr->result_cnt = (U8)(pinyin_match_result.count - param_ptr->first_index);
        result_ptr->next_page = MMI_FALSE;
    }                                 

    for (i = 0, k = 0; i < result_ptr->result_cnt ; i++)
    {
        for (j = 0; j < pinyin_match_result.table[i + param_ptr->first_index].length; j++)
        {
            result_ptr->result_buffer[k++] = (UI_character_type)pinyin_match_result.table[i + param_ptr->first_index].string[j];
        }

        result_ptr->result_buffer[k++] = 0;
    }
	result_ptr->result_buffer[k++] = 0;
}

#else

#if defined(__MMI_CSTAR_SM_CHINESE__)

#if defined(__MMI_CSTAR_PHRASE_INPUT__)
/* element is pinyin string not digit string */
static void mmi_ime_cstar_get_candidates_pinyin_cstar_style( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U16 i, k, j;
    char pinyin_string[MMI_IMC_MAX_INPUT_SYMBOL_BUFFSIZE];
    int ret_val;
    KMX_PINYIN_WORD_MATCH_RESULT    match_result;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    ASSERT( NULL != param_ptr );
    
    if ( 0 == param_ptr->elembuf_cnt )
        return;
        
    if ( param_ptr->tone_value >= MMI_IMC_SYMB_TONE_1 && param_ptr->tone_value <= MMI_IMC_SYMB_TONE_5)
    {
        return;
    }
        
    for (i = 0; i < param_ptr->elembuf_cnt; i++)
    {
        pinyin_string[i] = mmi_ime_word_symbol_to_code(param_ptr->elembuf_ptr[i]); /* Cstar use unicode to query */
    }

    pinyin_string[i] = 0;

    ret_val = kmx_pinyin_match(&g_engine.cstar_engine, 
                               (const char *)pinyin_string,
                               (unsigned short)param_ptr->elembuf_cnt,
                               (unsigned short)param_ptr->first_index,
                               &match_result);

    if (!ret_val)
    {
        return;
    }

    if (match_result.count < param_ptr->desired_cnt)
    {
        result_ptr->result_cnt = (U8)match_result.count;
        result_ptr->next_page = MMI_FALSE;
    }
    else if (match_result.count == param_ptr->desired_cnt )
    {
        result_ptr->result_cnt = (U8)match_result.count;
        
        if (match_result.more_available)
        {
            result_ptr->next_page = MMI_TRUE;
        }
        else
        {
            result_ptr->next_page = MMI_FALSE;
        }
    }
    else
    {
        result_ptr->result_cnt = param_ptr->desired_cnt;
        result_ptr->next_page = MMI_TRUE;
    }
        
    for (i = 0, k = 0; i < result_ptr->result_cnt ; i++)
    {
        for (j = 0; j < match_result.table[i].length; j++)
        {
            result_ptr->result_buffer[k++] = (UI_character_type)match_result.table[i].string[j];
        }

        result_ptr->result_buffer[k++] = 0;        
        result_ptr->match_length_table[i] = (U8)match_result.table[i].match_length;
    }
#if defined(__MMI_IME_CANDIDATE_GRID__)
	if(param_ptr->desired_cnt > 9)  // the limitation is cstar can only return 9 candidates
		result_ptr->match_length_table += result_ptr->result_cnt;
#endif
	 result_ptr->result_buffer[k++] = 0;
}

#endif

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_candidate_pinyin_cstar_style
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void mmi_ime_cstar_get_candidate_pinyin_cstar_style( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    KMX_PINYIN_COMPOSITION        pinyin_composition = {0};
    KMX_PINYIN_MATCH_RESULT       pinyin_match_result = {0};
    KMX_PINYIN_WORD_MATCH_RESULT  word_match_result = {0};
    unsigned char                 digit_string[MMI_IMC_MAX_INPUT_SYMBOL_BUFFSIZE] = {0};
    int ret_val;
    U16 i = 0, k, j;
    unsigned short pinyin_match_index = param_ptr->composition_index;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    ASSERT( NULL != param_ptr );

#if defined(__MMI_IME_V3__)    
#if defined(__MMI_IME_FTE_ENHANCE__) && defined(__MMI_CSTAR_PHRASE_INPUT__) 

    if ((mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY) && (mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)))
    {
        /* pinyin string, not digit string */
        mmi_ime_cstar_get_candidates_pinyin_cstar_style(param_ptr, result_ptr);
        return;
    }
#if defined(__MMI_IME_CANDIDATE_GRID__)
    if ((mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY) && (mmi_imc_is_grid_state()))
    {
        /* pinyin string, not digit string */
        mmi_ime_cstar_get_candidates_pinyin_cstar_style(param_ptr, result_ptr);
        return;
    }

#endif

    #if defined(__MMI_QWERTY_KEYPAD_SUPPORT__)
        if(!(mmi_imc_get_ui_style(MMI_IMC_UI_STYLE_VK_ON)) 
			#if defined(__MMI_IME_CANDIDATE_GRID__)
			&& mmi_imc_get_state() != MMI_IMC_STATE_CAND_SELECT_WITH_INPUT_GRID
#endif
			)
		
        {
            /* pinyin string, not digit string */
            mmi_ime_cstar_get_candidates_pinyin_cstar_style(param_ptr, result_ptr);
            return;
        }
    #endif
#endif  
#else
#if defined(__MMI_IME_FTE_ENHANCE__) && defined(__MMI_CSTAR_PHRASE_INPUT__)
    if (mmi_imm_get_keyboard_type() == IMM_KEYPAD_QWERTY)
    {
        /* pinyin string, not digit string */
        mmi_ime_cstar_get_candidates_pinyin_cstar_style(param_ptr, result_ptr);
        return;
    }
#endif
#endif   
    if (pinyin_match_index == 0xff)
    {
        pinyin_match_index = KMX_PINYIN_MATCH_INDEX_NONE;
    }

    if ( 0 == param_ptr->elembuf_cnt || param_ptr->elembuf_cnt > KMX_MAX_PINYIN_COMPOSITION)
        return;

    for (i = 0; i < param_ptr->elembuf_cnt; i++)
    {
        if (param_ptr->elembuf_ptr[i] == MMI_IMC_SYMB_KEY_0)
        {
            digit_string[i] = 0x20;
        }
        else
        {
            digit_string[i] = param_ptr->elembuf_ptr[i] - MMI_IMC_SYMB_KEY_BASE + '0';
        }
    }

    digit_string[i] = 0;

    if (param_ptr->elembuf_cnt == 1 && param_ptr->elembuf_ptr[0] == MMI_IMC_SYMB_KEY_1)
    {
        S32 cnt = 0;
        UI_character_type cand = 0;
        for (cnt = 0; cnt <= param_ptr->desired_cnt & (cand = g_chinese_symbol_string[param_ptr->first_index + cnt]) != 0; cnt ++)
        {
            result_ptr->result_buffer[(cnt<<1)] = cand;
            result_ptr->result_buffer[(cnt<<1) + 1] = 0x00; 
        }
        if (cnt > param_ptr->desired_cnt)
        {
            result_ptr->next_page = MMI_TRUE;
            result_ptr->result_cnt = param_ptr->desired_cnt;
        }
        else
        {
            result_ptr->next_page = MMI_FALSE;
            result_ptr->result_cnt = cnt;
        }
        
    }
    
    ret_val = kmx_digit_pinyin_match(&g_engine.cstar_engine, 
                                     (const char *)digit_string,
                                     (unsigned short)param_ptr->elembuf_cnt,
                                     (unsigned short)pinyin_match_index,
                                     (unsigned short)param_ptr->first_index,
                                     &pinyin_composition,
                                     &pinyin_match_result,
                                     &word_match_result);

    if (!ret_val)
    {
        return;
    }

    /* Copy symbol string to result */
    for (i = 0; i < pinyin_composition.length; i++)
    {
        result_ptr->symbol_string[i] = (UI_character_type)pinyin_composition.string[i];
    }

    result_ptr->symbol_string[i] = 0;

    /* Copy compositions to result */
    if ((U8)(pinyin_match_result.count - param_ptr->composition_first_index) > param_ptr->composition_desired_cnt)
    {
        result_ptr->composition_result_cnt = param_ptr->composition_desired_cnt;
        result_ptr->composition_next_page = MMI_TRUE;
    }
    else
    {
        result_ptr->composition_result_cnt = (U8)(pinyin_match_result.count - param_ptr->composition_first_index);
        result_ptr->composition_next_page = MMI_FALSE;
    }                                 

    for (i = 0, k = 0; i < result_ptr->composition_result_cnt ; i++)
    {
        for (j = 0; j < pinyin_match_result.table[i + param_ptr->composition_first_index].length; j++)
        {
            result_ptr->composition_buffer[k++] = (UI_character_type)pinyin_match_result.table[i + param_ptr->composition_first_index].string[j];
        }

        result_ptr->composition_buffer[k++] = 0;
    }

    /* Copy candidates and matched length information to result */
    if ((U8)word_match_result.count > param_ptr->desired_cnt)
    {
        result_ptr->result_cnt = param_ptr->desired_cnt;
        result_ptr->next_page = MMI_TRUE;
    }
    else if ((U8)word_match_result.count == param_ptr->desired_cnt)
    {
        result_ptr->result_cnt = param_ptr->desired_cnt;

        if (word_match_result.more_available)
        {
            result_ptr->next_page = MMI_TRUE;
        }
        else
        {
            result_ptr->next_page = MMI_FALSE;
        }
    }
    else
    {
        result_ptr->result_cnt = (U8)word_match_result.count;
        result_ptr->next_page = MMI_FALSE;
    }

    for (i = 0, k = 0; i < result_ptr->result_cnt ; i++)
    {
        for (j = 0; j < word_match_result.table[i].length; j++)
        {
            result_ptr->result_buffer[k++] = (UI_character_type)word_match_result.table[i].string[j];
        }
        result_ptr->match_length_table[i] = (U8)word_match_result.table[i].match_length;
        result_ptr->result_buffer[k++] = 0;
    }
	result_ptr->result_buffer[k++] = 0;
	if(param_ptr->desired_cnt > 9)//grid state
	{
		result_ptr->match_length_table += result_ptr->result_cnt;
	}
}

#endif

#endif

#endif /* __MMI_CSTAR_SMART_PHONETIC_INPUT__ */

#if defined(__MMI_CSTAR_SM_CHINESE__)
                                     

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_candidates_pinyin
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void mmi_ime_cstar_get_candidates_pinyin( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U16 i, k, j;
    char pinyin_string[MMI_IMC_MAX_INPUT_SYMBOL_BUFFSIZE];
    int ret_val;
    KMX_PINYIN_WORD_MATCH_RESULT    match_result;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    ASSERT( NULL != param_ptr );
    
    if ( 0 == param_ptr->elembuf_cnt )
        return;
        
    if ( param_ptr->tone_value >= MMI_IMC_SYMB_TONE_1 && param_ptr->tone_value <= MMI_IMC_SYMB_TONE_5)
    {
        return;
    }
    
    for (i = 0; i < param_ptr->elembuf_cnt; i++)
    {
        pinyin_string[i] = mmi_ime_word_symbol_to_code(param_ptr->elembuf_ptr[i]); /* Cstar use unicode to query */
    }

    pinyin_string[i] = 0;

    ret_val = kmx_pinyin_match(&g_engine.cstar_engine, 
                               (const char *)pinyin_string,
                               (unsigned short)param_ptr->elembuf_cnt,
                               (unsigned short)param_ptr->first_index,
                               &match_result);

    if (!ret_val)
    {
        return;
    }

    if (match_result.count < param_ptr->desired_cnt)
    {
        result_ptr->result_cnt = (U8)match_result.count;
        result_ptr->next_page = MMI_FALSE;
    }
    else if (match_result.count == param_ptr->desired_cnt )
    {
        result_ptr->result_cnt = (U8)match_result.count;
        
        if (match_result.more_available)
        {
            result_ptr->next_page = MMI_TRUE;
        }
        else
        {
            result_ptr->next_page = MMI_FALSE;
        }
    }
    else
    {
        result_ptr->result_cnt = param_ptr->desired_cnt;
        result_ptr->next_page = MMI_TRUE;
    }

    for (i = 0, k = 0; i < result_ptr->result_cnt ; i++)
    {
        for (j = 0; j < match_result.table[i].length; j++)
        {
            result_ptr->result_buffer[k++] = (UI_character_type)match_result.table[i].string[j];
        }

        result_ptr->result_buffer[k++] = 0;
    }
	result_ptr->result_buffer[k++] = 0;
}

#endif

#endif /* __MMI_CSTAR_SM_CHINESE__ */



#if defined(__MMI_CSTAR_TR_CHINESE__)

#if defined(__MMI_CSTAR_MULTITAP_PHONETIC_INPUT__)
/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_spellings_zhuyin_multitap
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void   mmi_ime_cstar_get_spellings_zhuyin_multitap( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    U8          i, symb;
    UI_string_type temp_str;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    ASSERT( NULL != param_ptr );
    
    if ( 0 == param_ptr->elembuf_cnt )
        return;

    temp_str = result_ptr->result_buffer;
        
    for ( i = 0; i < param_ptr->elembuf_cnt; i++ )
    {
        symb = param_ptr->elembuf_ptr[i];
        if ( MMI_FALSE != MMI_IMC_IS_SYMB_ZY(symb) )
        {
            *temp_str = mmi_ime_word_symbol_to_code(symb);
            temp_str++;
        }
        else if (MMI_IMC_IS_SYMB_TONE(symb))
        {
            *temp_str = mmi_ime_word_symbol_to_code(symb);
            temp_str++;
        }
        else
        {
            i = 0;
            temp_str = result_ptr->result_buffer;
            break;
        }
    }
    
    *temp_str = 0;
    result_ptr->result_cnt = i;
}

#endif /* __MMI_CSTAR_MULTITAP_PHONETIC_INPUT__) */


#if defined(__MMI_CSTAR_SMART_PHONETIC_INPUT__)
/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_spellings_zhuyin_smart
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void   mmi_ime_cstar_get_spellings_zhuyin_smart( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    return; /* Not support smart zhuyin */
}

#endif /* __MMI_CSTAR_SMART_PHONETIC_INPUT__ */

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_get_candidates_zhuyin
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void   mmi_ime_cstar_get_candidates_zhuyin( mmi_ime_query_param_struct_p param_ptr, mmi_ime_query_result_struct_p result_ptr )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U16 i, k, j;
    unsigned short zhuyin_string[MMI_IMC_MAX_INPUT_SYMBOL_BUFFSIZE];
    int ret_val;
    KMX_ZHUYIN_WORD_MATCH_RESULT    match_result;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    ASSERT( NULL != param_ptr );
    
    /*Temp set to 4 need to check what can be better solution*/
    if ( 0 == param_ptr->elembuf_cnt || param_ptr->elembuf_cnt > 4)
        return;
    
    for (i = 0; i < param_ptr->elembuf_cnt; i++)
    {
        zhuyin_string[i] = mmi_ime_word_symbol_to_code(param_ptr->elembuf_ptr[i]); /* Cstar use unicode to query */
    }

    zhuyin_string[i] = 0;

    ret_val = kmx_zhuyin_match(&g_engine.cstar_engine, 
                               (const unsigned short *)zhuyin_string,
                               (unsigned short)param_ptr->elembuf_cnt,
                               (unsigned short)param_ptr->first_index,
                               &match_result);

    if (!ret_val)
    {
        return;
    }

    if (match_result.count < param_ptr->desired_cnt)
    {
        result_ptr->result_cnt = (U8)match_result.count;
        result_ptr->next_page = MMI_FALSE;
    }
    else if (match_result.count == param_ptr->desired_cnt )
    {
        result_ptr->result_cnt = (U8)match_result.count;
        
        if (match_result.more_available)
        {
            result_ptr->next_page = MMI_TRUE;
        }
        else
        {
            result_ptr->next_page = MMI_FALSE;
        }
    }
    else
    {
        result_ptr->result_cnt = param_ptr->desired_cnt;
        result_ptr->next_page = MMI_TRUE;
    }

    for (i = 0, k = 0; i < result_ptr->result_cnt ; i++)
    {
        for (j = 0; j < match_result.table[i].length; j++)
        {
            result_ptr->result_buffer[k++] = (UI_character_type)match_result.table[i].string[j];
        }
    #if defined(__MMI_IME_SMART_WITH_INPUT_AREA__)
        result_ptr->match_length_table[i] = (U8)match_result.table[i].match_length;
    #endif
        result_ptr->result_buffer[k++] = 0;
    }
	result_ptr->result_buffer[k++] = 0;
}

#endif /* #if defined(__MMI_CSTAR_TR_CHINESE__) */

/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_mode_info_struct
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static const mmi_ime_cstar_mode_info_struct * mmi_ime_cstar_query_mode_info( mmi_imm_input_mode_enum input_mode )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    U16  i;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    if ( input_mode >= IMM_INPUT_MODE_MAX_NUM )
        return NULL;
    
    for ( i = 0; g_mode_infos[i].input_mode != IMM_INPUT_MODE_MAX_NUM; ++i )
    {
        if ( g_mode_infos[i].input_mode == input_mode )
        {
            return &g_mode_infos[i];
        }
    }
    
    return NULL;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_change_candidates_case
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static void  mmi_ime_cstar_change_candidates_case(mmi_ime_query_result_struct_p result_str)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    S32 i = 0, j = 0;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    if (g_engine.case_type == MMI_IME_WORD_CAPITAL_STATE_FIRST_UPPER)
    {
        while (j < result_str->result_cnt)
        {
            result_str->result_buffer[i] = mmi_ime_cstar_char_to_upper(result_str->result_buffer[i]);

            i++;

            while (result_str->result_buffer[i])
            {
                result_str->result_buffer[i] = mmi_ime_cstar_char_to_lower(result_str->result_buffer[i]);
                i++;
            }
            i++;
            j++;
        }
    }
    else if (g_engine.case_type == MMI_IME_WORD_CAPITAL_STATE_UPPER)
    {
        while (j < result_str->result_cnt)
        {
            result_str->result_buffer[i] = mmi_ime_cstar_char_to_upper(result_str->result_buffer[i]);
            i++;
            
            while (result_str->result_buffer[i])
            {
                result_str->result_buffer[i] = mmi_ime_cstar_char_to_upper(result_str->result_buffer[i]);
                i++;
            }
            i++;
            j++;
        }
    }
    else if (g_engine.case_type == MMI_IME_WORD_CAPITAL_STATE_LOWER)
    {
        while (j < result_str->result_cnt)
        {
            result_str->result_buffer[i] = mmi_ime_cstar_char_to_lower(result_str->result_buffer[i]);
            i++;
            
            while (result_str->result_buffer[i])
            {
                result_str->result_buffer[i] = mmi_ime_cstar_char_to_lower(result_str->result_buffer[i]);
                i++;
            }
            i++;
            j++;
        }
    }
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_char_to_upper
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static UI_character_type mmi_ime_cstar_char_to_upper(UI_character_type char_code)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    return (UI_character_type)mmi_towupper((kal_wchar)char_code);

}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_cstar_char_to_lower
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
static UI_character_type mmi_ime_cstar_char_to_lower(UI_character_type char_code)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    return (UI_character_type)mmi_towlower((kal_wchar)char_code);

}

#if defined(__MMI_IME_MAGIC_ONE__)
/*****************************************************************************
 * FUNCTION
 *  mmi_ime_word_is_magic_key
 * DESCRIPTION
 * PARAMETERS
 * RETURNS
 *****************************************************************************/
MMI_BOOL mmi_ime_word_is_magic_key( mmi_imm_input_mode_enum input_mode, mmi_imc_key_custom_value key_code )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    MMI_BOOL ret = MMI_FALSE;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    switch(input_mode)
    {
        case IMM_INPUT_MODE_SM_PINYIN:
            if (key_code == MMI_IMC_KEY_SYM_1)
                ret = MMI_TRUE;
            break;
        case IMM_INPUT_MODE_SM_STROKE:
        case IMM_INPUT_MODE_TR_STROKE:
            if (key_code == MMI_IMC_KEY_SYM_7)
                ret = MMI_TRUE;
                break;
    }
    return ret;
}
#endif

#ifdef __MMI_UI_VIRTUAL_KEYBOARD_DEFAULT_VERSION_3__ && defined(__MMI_IME_ALPHANUMERIC_VK_SUPPORT__)

#if !defined(__MMI_CSTAR_MULTITAP__)
    S32                  multitap_string_length;
    UI_character_type    mt_page_buff[MULTITAP_MAX_KEY_CHAR];
#endif 


UI_string_type mmi_ime_multitap_vendor_for_vk_get_string(S32 index)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_ime_cstar_mode_info_struct_p      mode_info_ptr = NULL;
    U16*  candidate_buf;
    const sIMEModeDetails * mode_details_ptr;
    S32 i=0;
    U16 len =10;
	S32 count =0;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    #ifdef __MMI_CSTAR_MULTITAP__
        S32 *string_length = &g_engine.multitap_string_length;
        UI_character_type *page_buff = g_engine.mt_page_buff;
    #else
        S32 *string_length = &multitap_string_length;
        UI_character_type *page_buff = mt_page_buff;
    #endif
    *string_length = 0;
    if ( (index >=0  && index <= MMI_IMC_SYMB_KEY_POUND - MMI_IMC_SYMB_KEY_0) )
    {
       mode_info_ptr = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info(g_engine.input_mode);
       mode_details_ptr = mmi_imm_get_input_mode_array_item(g_engine.input_mode);
       	
       if(mode_details_ptr->Mode_Special_Attrib & KMX_LATIN_UPPER_CASE)
       {
           if(!kmx_latin_query_multitap(*(mode_info_ptr->ldb_ptr),index,KMX_LATIN_UPPER_CASE,(const U16**)&candidate_buf,&len))
           ASSERT(0);
       }
       else
       {
           if(!kmx_latin_query_multitap(*(mode_info_ptr->ldb_ptr),index,KMX_LATIN_LOWER_CASE,(const U16**)&candidate_buf,&len))       	
           ASSERT(0);
       }

       while (len)
       {
           /* To append a space on Key 0 in multitap mode */
           if (index ==0)
           {
               if(!count)
			   {
                page_buff[(*string_length) ++] = 0x20;
				   count++;
			   }
           }
           
           
           page_buff[(*string_length) ++] = candidate_buf[i];
           
           i++;
           len--;
       }
       *string_length = *string_length;
       page_buff[*string_length] = 0;

    }
    return page_buff;
}

get_multitap_string mmi_ime_multitap_vendor_for_vk_get_string_func( mmi_imm_input_mode_enum input_mode )
{
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    mmi_ime_cstar_mode_info_struct_p      mode_info_ptr = NULL;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    if ( MMI_FALSE == g_engine.is_inited )
        return NULL;
  
    mode_info_ptr = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info(input_mode);

    if (mode_info_ptr)
    {
        return mmi_ime_multitap_vendor_for_vk_get_string;
    }
    else
    {
            return NULL;
    }
}

#endif


#if defined(__MMI_CSTAR_MULTITAP__)
/*****************************************************************************
 * FUNCTION
 *  mmi_ime_multitap_vendor_init
 * DESCRIPTION
 * Initalize Cstar engine for multitap
 * PARAMETERS
 * NONE
 * RETURNS
 * MMI_BOOL
 * MMI_TRUE Engine was initialized properly
 * MMI_FALSE Enfine was not able to initialize ,most probabaly because user databse was not able to load
 *****************************************************************************/
MMI_BOOL mmi_ime_multitap_vendor_init( void )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    return mmi_ime_word_init();
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_multitap_vendor_deinit
 * DESCRIPTION
 * Deinits cstar engine object
 * PARAMETERS
 * NONE
 * RETURNS
 * NONE
 *****************************************************************************/
void mmi_ime_multitap_vendor_deinit( void )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_multitap_vendor_get_string_func
 * DESCRIPTION
 * Returns function pointer which returns multitap string for a given input key
 * PARAMETERS
 * mmi_imm_input_mode_enum input mode for which function pointer to return multitap string is needed
 * RETURNS
 * Returns function pointer which returns multitap string for a given input key
 *****************************************************************************/
get_multitap_string mmi_ime_multitap_vendor_get_string_func( mmi_imm_input_mode_enum input_mode )
{
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    
    mmi_ime_cstar_mode_info_struct_p      mode_info_ptr = NULL;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    if ( MMI_FALSE == g_engine.is_inited )
        return NULL;
  
    mode_info_ptr = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info(input_mode);

    if (mode_info_ptr)
    {
        return mmi_ime_multitap_vendor_get_string;
    }
    else
    {
            return NULL;
    }
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_multitap_vendor_query_key_check_function
 * DESCRIPTION
 * Returns function pointer which checks whether input key is multitap key or not
 * PARAMETERS
 * mmi_imm_input_mode_enum input mode for which function pointer to check key input
 * RETURNS
 * Returns function pointer which checks whether input key is multitap key or not
 *****************************************************************************/
valid_key_check_func mmi_ime_multitap_vendor_query_key_check_function( mmi_imm_input_mode_enum input_mode )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_ime_cstar_mode_info_struct_p      mode_info_ptr = NULL;
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    if ( MMI_FALSE == g_engine.is_inited )
        return NULL;

    mode_info_ptr = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info(input_mode);

    if (mode_info_ptr)
    {
        return mmi_ime_multitap_vendor_valid_key_check;
    }
    else
    {
       return NULL;
    }
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_multitap_vendor_change_mode
 * DESCRIPTION
 * Changes multitap mode in cstar engine
 * PARAMETERS
 *  sIMEModeDetails *mode_details_ptr to the mode which is needed
 * RETURNS
 * MMI_BOOL
 * MMI_TRUR if successful in changing mode
 *****************************************************************************/
MMI_BOOL mmi_ime_multitap_vendor_change_mode( const sIMEModeDetails *mode_details_ptr, U32 reserved )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    return mmi_ime_word_change_mode( mode_details_ptr, reserved );
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_multitap_vendor_valid_key_check
 * DESCRIPTION
 * Function which checks whether input key is to be treated as multitap key
 * PARAMETERS
 * mmi_imc_symbol_key_enum sym 
 * RETURNS
 * MMI_BOOL
 * MMI_TRUR in case key is a multitap key
 * MMI_FAlse in case key is not a valid multitap key

 *****************************************************************************/
static MMI_BOOL mmi_ime_multitap_vendor_valid_key_check( mmi_imc_symbol_key_enum sym)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return mmi_ime_word_is_symbol_key(g_engine.curr_mode_info->input_mode, sym);
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_multitap_vendor_get_string
 * DESCRIPTION
 * Function which returns multitap string for given key
 * PARAMETERS
 * S32 key pressed
 * RETURNS
 * UI_string_type multitap string mapped on input key
 *****************************************************************************/
static UI_string_type mmi_ime_multitap_vendor_get_string(S32 index)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_ime_cstar_mode_info_struct_p      mode_info_ptr = NULL;
    U16*  candidate_buf;
    const sIMEModeDetails * mode_details_ptr;
    S32 i=0;
    U16 len =10;
	S32 count =0;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    g_engine.multitap_string_length = 0;
    if ( (index >=0  && index <= MMI_IMC_SYMB_KEY_POUND - MMI_IMC_SYMB_KEY_0) )
    {
       mode_info_ptr = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info(g_engine.input_mode);
       mode_details_ptr = mmi_imm_get_input_mode_array_item(g_engine.input_mode);
       	
       if(mode_details_ptr->Mode_Special_Attrib & IME_MODE_ATTR_LOWERCASE)
       {
           if(!kmx_latin_query_multitap(*(mode_info_ptr->ldb_ptr),index,KMX_LATIN_LOWER_CASE,(const U16**)&candidate_buf,&len))
           ASSERT(0);
       }
       else
       {
           if(!kmx_latin_query_multitap(*(mode_info_ptr->ldb_ptr),index,KMX_LATIN_UPPER_CASE,(const U16**)&candidate_buf,&len))       	
           ASSERT(0);
       }

       while (len)
       {
           /* To append a space on Key 0 in multitap mode */
          if (index ==0)  
           {
               if(0 == count && candidate_buf[0] != 0x20)
			   {
					g_engine.mt_page_buff[g_engine.multitap_string_length ++] = 0x20;
				    count++;
			   }


           }
           
           g_engine.mt_page_buff[g_engine.multitap_string_length ++] = candidate_buf[i];
           
           i++;
           len--;
       }
       g_engine.multitap_string_length = g_engine.multitap_string_length;
       g_engine.mt_page_buff[g_engine.multitap_string_length] = 0;

    }
    return g_engine.mt_page_buff;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_ime_multitap_vendor_get_string
 * DESCRIPTION
 * Function which returns multitap string for given key
 * PARAMETERS
 * S32 key pressed
 * RETURNS
 * UI_string_type multitap string mapped on input key
 *****************************************************************************/
 UI_string_type mmi_ime_multitap_vendor_get_string_ext(S32 index , S32 input_mode )
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_ime_cstar_mode_info_struct_p      mode_info_ptr = NULL;
    U16*  candidate_buf;
    const sIMEModeDetails * mode_details_ptr;
    S32 i=0;
    U16 len =10;
	S32 count =0;
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    g_engine.multitap_string_length = 0;
    if ( (index >=0  && index <= MMI_IMC_SYMB_KEY_POUND - MMI_IMC_SYMB_KEY_0) )
    {
       mode_info_ptr = (mmi_ime_cstar_mode_info_struct_p)mmi_ime_cstar_query_mode_info(input_mode);
       mode_details_ptr = mmi_imm_get_input_mode_array_item(input_mode);
       	
       if(mode_details_ptr->Mode_Special_Attrib & IME_MODE_ATTR_LOWERCASE)
       {
           if(!kmx_latin_query_multitap(*(mode_info_ptr->ldb_ptr),index,KMX_LATIN_LOWER_CASE,(const U16**)&candidate_buf,&len))
           ASSERT(0);
       }
       else
       {
           if(!kmx_latin_query_multitap(*(mode_info_ptr->ldb_ptr),index,KMX_LATIN_UPPER_CASE,(const U16**)&candidate_buf,&len))       	
           ASSERT(0);
       }

       while (len)
       {
           /* To append a space on Key 0 in multitap mode */
           if (index ==0)
           {
               if(!count)
			   {
                g_engine.mt_page_buff[g_engine.multitap_string_length ++] = 0x20;
				   count++;
			   }


           }
           
           
               g_engine.mt_page_buff[g_engine.multitap_string_length ++] = candidate_buf[i];
           
           i++;
           len--;
       }
       g_engine.multitap_string_length = g_engine.multitap_string_length;
       g_engine.mt_page_buff[g_engine.multitap_string_length] = 0;

    }
    return g_engine.mt_page_buff;
}

#endif /* defined(__MMI_CSTAR_MULTITAP__) */

#endif /* #ifdef  __MMI_CSTAR__ */

