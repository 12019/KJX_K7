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
 *  vapp_op_launcher_key_mainmenu_util.h
 *
 * Project:
 * --------
 *  
 *
 * Description:
 * ------------
 *  Mainmenu helper function
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
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef _VAPP_OP_LAUNCHER_KEY_MAINMENU_UTIL_H_
#define _VAPP_OP_LAUNCHER_KEY_MAINMENU_UTIL_H_

#include "MMI_features.h"
#include "MMIDataType.h"

typedef enum
{
#ifdef __MMI_OP01_MIDLET_FETION__
    VAPP_OP01_LAUNCHER_KEY_MIDLET_FETION,
#endif
#ifdef __MMI_OP01_MIDLET_MUSIC_WALKMAN__
    VAPP_OP01_LAUNCHER_KEY_MIDLET_MUSIC,
#endif
#ifdef __MMI_OP01_MIDLET_MOBILE_MARKET__
    VAPP_OP01_LAUNCHER_KEY_MIDLET_MOBILE_MARKET,
#endif
#ifdef __MMI_OP01_MIDLET_CMREAD__
    VAPP_OP01_LAUNCHER_KEY_MIDLET_MOBILE_READER,
#endif
#ifdef __MMI_OP01_MIDLET_139MAIL__
    VAPP_OP01_LAUNCHER_KEY_MIDLET_139_MAIL,
#endif
#ifdef __MMI_OP01_MIDLET_MOBILE_GAME__
    VAPP_OP01_LAUNCHER_KEY_MIDLET_MOBILE_GAME,
#endif
#ifdef __MMI_OP01_MIDLET_MOBILE_STOCK__
    VAPP_OP01_LAUNCHER_KEY_MIDLET_MOBILE_STOCK,
#endif
    VAPP_OP_LAUNCHER_KEY_MIDLET_TOTAL
} vapp_op_launcher_key_midlet_enum;

typedef struct
{
    vapp_op_launcher_key_midlet_enum midlet_id;
    const WCHAR *midlet_name;
} vapp_op_launcher_key_midlet_info_struct;

extern const vapp_op_launcher_key_midlet_info_struct vapp_op_launcher_key_midlet_info[];
extern U32 vapp_op_launcher_key_get_midlet_count(void);


#endif /* _VAPP_OP_LAUNCHER_KEY_MAINMENU_UTIL_H_ */


