/*
 * (C) 2005-2019 MediaTek Inc. All rights reserved.
 *
 * Copyright Statement:
 *
 * This MT3620 driver software/firmware and related documentation
 * ("MediaTek Software") are protected under relevant copyright laws.
 * The information contained herein is confidential and proprietary to
 * MediaTek Inc. ("MediaTek"). You may only use, reproduce, modify, or
 * distribute (as applicable) MediaTek Software if you have agreed to and been
 * bound by this Statement and the applicable license agreement with MediaTek
 * ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User"). If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE
 * PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS
 * ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO
 * LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED
 * HEREUNDER WILL BE ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY
 * RECEIVER TO MEDIATEK DURING THE PRECEDING TWELVE (12) MONTHS FOR SUCH
 * MEDIATEK SOFTWARE AT ISSUE.
 */

#ifndef __OS_HAL_EINT_H__
#define __OS_HAL_EINT_H__

#include "mhal_eint.h"

#define IRQ_EDGE_TRIGGER        0x00
#define IRQ_LEVEL_TRIGGER       0x01
#define IRQ_EDGE2LVL_TRIGGER    0x02

int mtk_os_hal_eint_register(eint_number eint_num,
			eint_trigger_mode trigger_mode, void (*handle)(void));

int mtk_os_hal_eint_unregister(eint_number eint_num);

int mtk_os_hal_eint_set_debounce(eint_number eint_num,
			u32 debounce_time);

int mtk_os_hal_eint_set_type(eint_number eint_num,
			eint_trigger_mode trigger_mode);

int mtk_os_hal_eint_enable_debounce(eint_number eint_num);

int mtk_os_hal_eint_disable_debounce(eint_number eint_num);

#endif /* __HAL_EINT_H__ */

