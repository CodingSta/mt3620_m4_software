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

#include "nvic.h"
#include "os_hal_adc.h"
#include "os_hal_gpio.h"
#include "os_hal_dma.h"

#define CM4_ADC_BASE					0x38000000
#define CM4_ADC_TOPCFGAON_CLK_RG		0x30030208

struct mtk_adc_controller_rtos {
	struct mtk_adc_controller *ctlr;
	/* the type based on OS */
	volatile u8 rx_completion;
};
static struct adc_fsm_param adc_fsm_parameter;

static struct mtk_adc_controller adc_controller;

static struct mtk_adc_controller_rtos g_adc_ctlr_rtos;

static struct mtk_adc_controller_rtos *_mtk_os_hal_adc_get_ctlr(void)
{
	return &g_adc_ctlr_rtos;
}

static int _mtk_os_hal_adc_config_gpio(void)
{
	int ret = 0;

	ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_41);
	if (ret != 0)
		printf("request gpio[%d] fail\n",
			OS_HAL_GPIO_41);
	ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_41,
				OS_HAL_MODE_0);
	ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_41,
				OS_HAL_GPIO_DIR_INPUT);
	if (ret != 0)
		printf("config gpio[%d] fail\n",
			OS_HAL_GPIO_41);
	ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_42);
	if (ret != 0)
		printf("request gpio[%d] fail\n",
			OS_HAL_GPIO_42);
	ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_42,
				OS_HAL_MODE_0);
	ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_42,
				OS_HAL_GPIO_DIR_INPUT);
	if (ret != 0)
		printf("config gpio[%d] fail\n",
			OS_HAL_GPIO_42);
	ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_43);
	if (ret != 0)
		printf("request gpio[%d] fail\n",
			OS_HAL_GPIO_43);
	ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_43,
				OS_HAL_MODE_0);
	ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_43,
				OS_HAL_GPIO_DIR_INPUT);
	if (ret != 0)
		printf("config gpio[%d] fail\n",
			OS_HAL_GPIO_43);
	ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_44);
	if (ret != 0)
		printf("request gpio[%d] fail\n",
			OS_HAL_GPIO_44);
	ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_44,
				OS_HAL_MODE_0);
	ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_44,
				OS_HAL_GPIO_DIR_INPUT);
	if (ret != 0)
		printf("config gpio[%d] fail\n",
			OS_HAL_GPIO_44);
	ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_45);
	if (ret != 0)
		printf("request gpio[%d] fail\n",
			OS_HAL_GPIO_45);
	ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_45,
				OS_HAL_MODE_0);
	ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_45,
				OS_HAL_GPIO_DIR_INPUT);
	if (ret != 0)
		printf("config gpio[%d] fail\n",
			OS_HAL_GPIO_45);
	ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_46);
	if (ret != 0)
		printf("request gpio[%d] fail\n",
			OS_HAL_GPIO_46);
	ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_46,
				OS_HAL_MODE_0);
	ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_46,
				OS_HAL_GPIO_DIR_INPUT);
	if (ret != 0)
		printf("config gpio[%d] fail\n",
			OS_HAL_GPIO_46);
	ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_47);
	if (ret != 0)
		printf("request gpio[%d] fail\n",
			OS_HAL_GPIO_47);
	ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_47,
				OS_HAL_MODE_0);
	ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_47,
				OS_HAL_GPIO_DIR_INPUT);
	if (ret != 0)
		printf("config gpio[%d] fail\n",
			OS_HAL_GPIO_47);
	ret |= mtk_os_hal_gpio_request(OS_HAL_GPIO_48);
	if (ret != 0)
		printf("request gpio[%d] fail\n",
			OS_HAL_GPIO_48);
	ret |= mtk_os_hal_gpio_pmx_set_mode(OS_HAL_GPIO_48,
				OS_HAL_MODE_0);
	ret |= mtk_os_hal_gpio_set_direction(OS_HAL_GPIO_48,
				OS_HAL_GPIO_DIR_INPUT);
	if (ret != 0)
		printf("config gpio[%d] fail\n",
			OS_HAL_GPIO_48);

	return ret;
}

static int _mtk_os_hal_adc_release_gpio(void)
{
	int ret = 0;

	ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_41);
	if (ret != 0)
		printf("release gpio[%d] fail\n",
			OS_HAL_GPIO_41);
	ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_42);
	if (ret != 0)
		printf("release gpio[%d] fail\n",
			OS_HAL_GPIO_42);
	ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_43);
	if (ret != 0)
		printf("release gpio[%d] fail\n",
			OS_HAL_GPIO_43);
	ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_44);
	if (ret != 0)
		printf("release gpio[%d] fail\n",
			OS_HAL_GPIO_44);
	ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_45);
	if (ret != 0)
		printf("release gpio[%d] fail\n",
			OS_HAL_GPIO_45);
	ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_46);
	if (ret != 0)
		printf("release gpio[%d] fail\n",
			OS_HAL_GPIO_46);
	ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_47);
	if (ret != 0)
		printf("release gpio[%d] fail\n",
			OS_HAL_GPIO_47);
	ret = mtk_os_hal_gpio_free(OS_HAL_GPIO_48);
	if (ret != 0)
		printf("release gpio[%d] fail\n",
			OS_HAL_GPIO_48);

	return ret;
}
static int _mtk_os_hal_adc_irq_handler(struct mtk_adc_controller *ctlr)
{
	if (!ctlr)
		return -EPTR;

	if (ctlr->adc_fsm_parameter->fifo_mode != ADC_FIFO_DIRECT)
		return -EPARAMETER;

	mtk_mhal_adc_fifo_handle_rx(ctlr);

	return 0;
}

static void _mtk_os_hal_adc_irq_event(void)
{
	struct mtk_adc_controller_rtos *ctlr_rtos =
		_mtk_os_hal_adc_get_ctlr();
	struct mtk_adc_controller *ctlr;

	ctlr = ctlr_rtos->ctlr;
	_mtk_os_hal_adc_irq_handler(ctlr);

}


static int _mtk_os_hal_adc_request_irq(struct mtk_adc_controller *ctlr)
{
	if (!ctlr)
		return -EPTR;

	CM4_Install_NVIC(CM4_IRQ_ADC, CM4_ADC_PRI, IRQ_LEVEL_TRIGGER,
		_mtk_os_hal_adc_irq_event, TRUE);


	return 0;
}

static int _mtk_os_hal_adc_wait_for_completion_timeout(
				struct mtk_adc_controller_rtos
				*ctlr_rtos, int time_ms)
{
	while(ctlr_rtos->rx_completion==0){}
	ctlr_rtos->rx_completion--;
	return 0;
}

static int _mtk_os_hal_adc_rx_done_callback(void *data)
{
	struct mtk_adc_controller_rtos *ctlr_rtos = data;
	ctlr_rtos->rx_completion++;
	return 0;
}

int mtk_os_hal_adc_ctlr_init(adc_pmode pmode, adc_fifo_mode fifo_mode,
					u16 bit_map)
{
	struct mtk_adc_controller_rtos *ctlr_rtos;
	struct mtk_adc_controller *ctlr;
	u32 channel_index = 0;
	int ret = 0;

	ctlr_rtos =	_mtk_os_hal_adc_get_ctlr();
	if (!ctlr_rtos)
		return -EPTR;

	if ((pmode != ADC_PMODE_ONE_TIME) && (pmode != ADC_PMODE_PERIODIC))
		return -EPARAMETER;

	if ((fifo_mode != ADC_FIFO_DIRECT) && (fifo_mode != ADC_FIFO_DMA))
		return -EPARAMETER;


	ctlr_rtos->ctlr = &adc_controller;

	if (!ctlr_rtos->ctlr)
		return -EPTR;

	ctlr = ctlr_rtos->ctlr;

	ctlr->adc_fsm_parameter = &adc_fsm_parameter;

	ctlr->base = (void __iomem *)CM4_ADC_BASE;
	ctlr->cg_base = (void __iomem *)CM4_ADC_TOPCFGAON_CLK_RG;

	ret = _mtk_os_hal_adc_config_gpio();
	if (ret)
		return ret;

	ret = mtk_mhal_adc_enable_clk(ctlr);
	if (ret)
		return ret;

	ctlr->adc_fsm_parameter->pmode = pmode;
	ctlr->adc_fsm_parameter->avg_mode = ADC_AVG_32_SAMPLE;
	ctlr->adc_fsm_parameter->channel_map = bit_map;
	ctlr->adc_fsm_parameter->period = PMODE_PERIOD;
	ctlr->adc_fsm_parameter->fifo_mode = fifo_mode;
	ctlr->adc_fsm_parameter->ier_mode = ADC_FIFO_IER_RXFULL;
	if (ctlr->adc_fsm_parameter->fifo_mode == ADC_FIFO_DMA) {
		ctlr->adc_fsm_parameter->dma_vfifo_len = ADC_DMA_BUF_WORD_SIZE;

		ctlr->dma_channel = VDMA_ADC_RX_CH29;
		ctlr->use_dma = 1;
		printf("mtk os_hal_adc_ctlr_init dma_vfifo_len == %d\n",
			ctlr->adc_fsm_parameter->dma_vfifo_len);
		printf("mtk os_hal_adc_ctlr_init dma_vfifo_addr == %p\n",
			ctlr->adc_fsm_parameter->dma_vfifo_addr);
	}
	printf("mtk os_hal_adc_ctlr_init ctlr->rx_buf == %p\n",
		ctlr->rx_buf);

	for (channel_index = 0; channel_index < ADC_CHANNEL_MAX;
			channel_index++) {
		ctlr->current_xfer[channel_index].count = 0;
		ctlr->current_xfer[channel_index].write_point = 0;
		ctlr->current_xfer[channel_index].read_point = 0;
	}

	ret = mtk_mhal_adc_init(ctlr);
	if (ret)
		return ret;

	if (fifo_mode == ADC_FIFO_DIRECT) {
		ctlr->use_dma = 0;
		ret = _mtk_os_hal_adc_request_irq(ctlr);
		if (ret)
			return ret;
	}

	ctlr_rtos->rx_completion = 1;

	ret = mtk_mhal_adc_rx_notify_callback_register(ctlr,
					 _mtk_os_hal_adc_rx_done_callback,
					 (void *)ctlr_rtos);
	if (ret)
		return ret;

	ret = mtk_mhal_adc_fsm_param_set(ctlr, ctlr->adc_fsm_parameter);
	if (ret)
		return ret;

	if (ctlr->adc_fsm_parameter->pmode == ADC_PMODE_ONE_TIME) {
		ret = mtk_mhal_adc_start_ch(ctlr_rtos->ctlr,
			ctlr->adc_fsm_parameter->channel_map);
		if (ret)
			return ret;
	}
	printf("mtk os_hal_adc_ctlr_init success\n");

	return ret;
}

int mtk_os_hal_adc_start(void)
{
	struct mtk_adc_controller_rtos *ctlr_rtos =
		_mtk_os_hal_adc_get_ctlr();

	if (!ctlr_rtos)
		return -EPTR;

	return mtk_mhal_adc_start(ctlr_rtos->ctlr);
}

int mtk_os_hal_adc_start_ch(u16 ch_bit_map)
{
	struct mtk_adc_controller_rtos *ctlr_rtos =
		_mtk_os_hal_adc_get_ctlr();

	if (!ctlr_rtos)
		return -EPTR;

	 return mtk_mhal_adc_start_ch(ctlr_rtos->ctlr, ch_bit_map);
}

int mtk_os_hal_adc_ctlr_deinit(void)
{
	int ret = 0;
	struct mtk_adc_controller_rtos *ctlr_rtos =
		_mtk_os_hal_adc_get_ctlr();

	if (!ctlr_rtos)
		return -EPTR;

	if (!ctlr_rtos->ctlr)
		return -EPTR;

	if (ctlr_rtos->ctlr->adc_fsm_parameter->fifo_mode == ADC_FIFO_DIRECT) {
		/* Disable ADC IRQ */
		NVIC_DisableIRQ((IRQn_Type)CM4_IRQ_ADC);
	}
	ret = mtk_mhal_adc_stop(ctlr_rtos->ctlr);
	if (ret)
		return ret;

	ret = mtk_mhal_adc_deinit(ctlr_rtos->ctlr);
	if (ret)
		return ret;

	ret = mtk_mhal_adc_disable_clk(ctlr_rtos->ctlr);
	if (ret)
		return ret;

	ret = _mtk_os_hal_adc_release_gpio();
	if (ret)
		return ret;

	return 0;
}

int mtk_os_hal_adc_fsm_param_set(struct adc_fsm_param *adc_fsm_parameter)
{
	struct mtk_adc_controller_rtos *ctlr_rtos;
	struct mtk_adc_controller *ctlr;
	u32 channel_index = 0;
	int ret = 0;

	ctlr_rtos =	_mtk_os_hal_adc_get_ctlr();
	if (!ctlr_rtos)
		return -EPTR;

	ctlr = ctlr_rtos->ctlr;

	ctlr->adc_fsm_parameter->pmode = adc_fsm_parameter->pmode;
	ctlr->adc_fsm_parameter->avg_mode = adc_fsm_parameter->avg_mode;
	ctlr->adc_fsm_parameter->channel_map = adc_fsm_parameter->channel_map;
	ctlr->adc_fsm_parameter->period = adc_fsm_parameter->period;
	ctlr->adc_fsm_parameter->fifo_mode = adc_fsm_parameter->fifo_mode;
	ctlr->adc_fsm_parameter->ier_mode = adc_fsm_parameter->ier_mode;

	if (ctlr->adc_fsm_parameter->fifo_mode == ADC_FIFO_DMA) {
		ctlr->adc_fsm_parameter->dma_vfifo_len = ADC_DMA_BUF_WORD_SIZE;
		printf("mtk os_hal_adc_ctlr_init dma_vfifo_len == %d\n",
			ctlr->adc_fsm_parameter->dma_vfifo_len);
		printf("mtk os_hal_adc_ctlr_init dma_vfifo_addr == %p\n",
			ctlr->adc_fsm_parameter->dma_vfifo_addr);
	}

	for (channel_index = 0; channel_index < ADC_CHANNEL_MAX;
		channel_index++) {
		ctlr->current_xfer[channel_index].count = 0;
		ctlr->current_xfer[channel_index].write_point = 0;
		ctlr->current_xfer[channel_index].read_point = 0;
	}

	ret = mtk_mhal_adc_fsm_param_set(ctlr, adc_fsm_parameter);
	if (ret)
		return ret;

	return 0;
}
int mtk_os_hal_adc_one_shot_get_data(adc_channel sample_channel, u32 *data)
{
	struct mtk_adc_controller_rtos *ctlr_rtos;
	struct mtk_adc_controller *ctlr;
	int ret = 0;

	ctlr_rtos =	_mtk_os_hal_adc_get_ctlr();
	if (!ctlr_rtos)
		return -EPTR;

	ctlr = ctlr_rtos->ctlr;

	if ((ctlr == NULL) || (ctlr->adc_fsm_parameter == NULL))
		return -EPTR;

	if (sample_channel > ADC_CHANNEL_7)
		return -EPARAMETER;

	if ((ctlr->adc_fsm_parameter->pmode != ADC_PMODE_ONE_TIME) ||
		(ctlr->adc_fsm_parameter->fifo_mode != ADC_FIFO_DIRECT))
		return -EPARAMETER;

	printf("sample_channel->%d data point:%p\n", sample_channel, data);

	ret = mtk_mhal_adc_one_shot_get_data(ctlr_rtos->ctlr,
		sample_channel, data);
	if (ret)
		return ret;

	printf("one_shot_get_data sample_channel:->%d, data:%d\n",
		sample_channel, *data);

	return 0;
}

int mtk_os_hal_adc_period_get_data(adc_channel sample_channel)
{
	struct mtk_adc_controller_rtos *ctlr_rtos;
	struct mtk_adc_controller *ctlr;
	int ret = 0;
	int count = 0;

	ctlr_rtos =	_mtk_os_hal_adc_get_ctlr();
	if (!ctlr_rtos)
		return -EPTR;

	ctlr = ctlr_rtos->ctlr;
	if ((ctlr == NULL) || (ctlr->adc_fsm_parameter == NULL))
		return -EPTR;

	ret = mtk_mhal_adc_start(ctlr_rtos->ctlr);
	if (ret)
		return ret;

	ret = _mtk_os_hal_adc_wait_for_completion_timeout(ctlr_rtos, 1000);
	if (ret)
		printf("Take adc master Semaphore timeout!\n");

	ret = mtk_mhal_adc_period_get_data(ctlr, sample_channel);
	if (ret)
		return ret;

	printf("channel->%d,size:%d\n", sample_channel,
	ctlr->rx_size);
	for (count = 0; count < ctlr->rx_size; count++) {
		printf("data%d:%d\n",
		count,
		ctlr->rx_buf[count]);
	}
	ret = mtk_mhal_adc_stop(ctlr);
	if (ret)
		return ret;

	if (ctlr->adc_fsm_parameter->fifo_mode == ADC_FIFO_DMA) {
		ret = mtk_mhal_adc_stop_dma(ctlr);
		if (ret)
			return ret;
	}

	return 0;
}


