/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2008
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
*  LAWS PRINCIPLES. ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*******************************************************************************
 * Filename:
 * ---------
 *  vcp_pluto_idle_calendar.cpp
 *
 * Project:
 * --------
 *  Venus UI Components
 *
 * Description:
 * ------------
 *  Idle calendar adaptor to Pluto UI component
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
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

/***************************************************************************** 
 * Include
 *****************************************************************************/
#include "vfx_uc_include.h"
#include "vcp_idle_calendar.h"

#ifdef __cplusplus
extern "C"
{
    #include "GUI\vadp_v2p_idle_calendar.h"    
    #include "MMI_features.h"
    #include "kal_release.h"
    #include "kal_general_types.h"
}
#endif 

#include "vfx_sys_memory.h"
#include "vrt_datatype.h"    

/*
 * Static variables
 */

VFX_IMPLEMENT_CLASS("IdleCalendar", VcpIdleCalendar, VcpPlutoControl);


/*
 * Static functions
 */


/*
 * Member functions
 */
VcpIdleCalendar::VcpIdleCalendar()
{}


void VcpIdleCalendar::updateCalendarForPluto(void *object)
{
    VcpIdleCalendar *calendar = (VcpIdleCalendar *) object;

    VFX_OBJ_ASSERT_VALID(calendar);
    calendar->m_signalUpdate.emit();
    updateScreenForPluto(object);
}


void VcpIdleCalendar::onPlutoCreate()
{
    VfxSize size = VFX_SIZE_ZERO;

    vadp_v2p_create_idle_calendar(
        &size.width,
        &size.height,
        updateCalendarForPluto,
        this,
        getLayerHandle());
    setBounds(VfxRect(0, 0, size.width, size.height));
}


void VcpIdleCalendar::onPlutoClose()
{
    vadp_v2p_close_idle_calendar();
}


void VcpIdleCalendar::onPlutoDraw()
{
    vadp_v2p_show_idle_calendar();
}


VfxSize VcpIdleCalendar::onPlutoGetPreferredSize()
{
    return VfxSize(WIDTH, HEIGHT);
}

VfxBool VcpIdleCalendar::onPlutoNeedAlphaChannel()
{
#ifdef __MMI_VUI_HOMESCREEN_LITE_DISPLAY__
    // Use RGB565 to reduce RAM usage
    return VFX_FALSE;
#else
    // Use PNG background image in theme
    return VFX_TRUE;
#endif
}
