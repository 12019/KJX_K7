/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2010
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
 *  DialerCuiClassic.h
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  This file defines the interface of the classic dialer.
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
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#ifndef DIALER_CUI_CLASSIC_H
#define DIALER_CUI_CLASSIC_H

/* auto add by kw_check begin */
#include "DialerCuiObject.h"
#include "DialerCuiGprot.h"
#include "MMIDataType.h"
#include "custom_phb_config.h"
#include "kal_general_types.h"
/* auto add by kw_check end */

/****************************************************************************
 * Define
 ****************************************************************************/

#if !defined(__MMI_TOUCH_DIAL_SCREEN_WITH_FUNCTION__)
#define CUI_DIALER_CLASSIC_SUPPORT_CSK
#endif


/****************************************************************************
 * Object Definition
 ****************************************************************************/

typedef void (*cui_dialer_classic_on_enter_cb)(
    struct cui_dialer_obj_st *obj);

typedef void (*cui_dialer_classic_on_exit_cb)(
    struct cui_dialer_obj_st *obj);

typedef void (*cui_dialer_classic_on_set_cat_hdlr_cb)(
    void);

#define CUI_DIALER_CLASSIC_FIELD                                \
    CUI_DIALER_OBJ_FIELD;                                       \
    cui_dialer_classic_on_enter_cb          on_enter;           \
    cui_dialer_classic_on_exit_cb           on_exit;            \
    cui_dialer_classic_on_set_cat_hdlr_cb   on_set_cat_hdlr

typedef struct
{
    CUI_DIALER_CLASSIC_FIELD;
} cui_dialer_classic_struct;


/****************************************************************************
 * Function
 ****************************************************************************/

extern void cui_dialer_classic_on_enter(cui_dialer_obj_struct *obj);


extern void cui_dialer_classic_on_exit(cui_dialer_obj_struct *obj);


extern void cui_dialer_classic_on_set_cat_hdlr(void);


extern void cui_dialer_classic_on_init(cui_dialer_obj_struct *obj);


#ifdef __OP01_FWPBW__
/****************************************************************************
 * Object Defitition
 ****************************************************************************/

#define CUI_DIALER_BWT_FIELD            \
    CUI_DIALER_CLASSIC_FIELD;           \
    MMI_BOOL    is_phone_up;            \
    mmi_id      phb_group_id;           \
    MMI_BOOL    is_can_close;           \
    MMI_BOOL    blacklist_call_set;     \
    MMI_BOOL    is_can_make_call

typedef struct
{
    CUI_DIALER_BWT_FIELD;
} cui_dialer_bwt_struct;


/****************************************************************************
 * Function
 ****************************************************************************/

extern void cui_dialer_bwt_on_init(cui_dialer_obj_struct *obj);
extern MMI_BOOL cui_dialer_bwt_on_want_to_run(void);

#endif

#endif /* DIALER_CUI_CLASSIC_H */

