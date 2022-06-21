/*
 * Copyright (C) 2022 Rockchip Electronics Co., Ltd.
 * Authors:
 *  Cerf Yu <cerf.yu@rock-chips.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _im2d_task_h_
#define _im2d_task_h_

#include "im2d_type.h"

#ifdef __cplusplus

/**
 * Create an rga job
 *
 * @param flags
 *      Some configuration flags for this job
 *
 * @returns job id.
 */
IM_API im_job_id_t im_BeginJob(uint64_t flags = 0);

/**
 * Submit and run an rga job
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param sync_mode
 *      run mode:
 *          IM_SYNC
 *          IM_ASYNC
 * @param acquire_fence_fd
 * @param release_fence_fd
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_EndJob(im_job_id_t job_id, int sync_mode = IM_SYNC, int acquire_fence_fd = 0, int *release_fence_fd = NULL);

/**
 * Cancel and delete an rga job
 *
 * @param flags
 *      Some configuration flags for this job
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_CancelJob(im_job_id_t job_id);

/**
 * Add copy task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddCopyTask(im_job_id_t job_id, const rga_buffer_t src, rga_buffer_t dst);

/**
 * Add resize task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 * @param fx
 *      X-direction resize factor.
 * @param fy
 *      X-direction resize factor.
 * @param interpolation
 *      Interpolation formula(Only RGA1 support).
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddResizeTask(im_job_id_t job_id,
                                  const rga_buffer_t src, rga_buffer_t dst,
                                  double fx = 0, double fy = 0,
                                  int interpolation = 0);

/**
 * Add crop task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 * @param rect
 *      The rectangle on the source image that needs to be cropped.
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddCropTask(im_job_id_t job_id, const rga_buffer_t src, rga_buffer_t dst, im_rect rect);

/**
 * Add format convert task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 * @param sfmt
 *      The source image format.
 * @param dfmt
 *      The destination image format.
 * @param mode
 *      color space mode:
 *          IM_YUV_TO_RGB_BT601_LIMIT
 *          IM_YUV_TO_RGB_BT601_FULL
 *          IM_YUV_TO_RGB_BT709_LIMIT
 *          IM_RGB_TO_YUV_BT601_FULL
 *          IM_RGB_TO_YUV_BT601_LIMIT
 *          IM_RGB_TO_YUV_BT709_LIMIT
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddCvtColorTask(im_job_id_t job_id,
                                    rga_buffer_t src, rga_buffer_t dst,
                                    int sfmt, int dfmt, int mode = IM_COLOR_SPACE_DEFAULT);

/**
 * Add translate task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 * @param x
 *      Output the coordinates of the starting point in the X-direction of the destination image.
 * @param y
 *      Output the coordinates of the starting point in the Y-direction of the destination image.
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddTranslateTask(im_job_id_t job_id,
                                     const rga_buffer_t src, rga_buffer_t dst, int x, int y);

/**
 * Add rotation task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 * @param rotation
 *      IM_HAL_TRANSFORM_ROT_90
 *      IM_HAL_TRANSFORM_ROT_180
 *      IM_HAL_TRANSFORM_ROT_270
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddRotateTask(im_job_id_t job_id,
                                  const rga_buffer_t src, rga_buffer_t dst, int rotation);

/**
 * Add flip task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 * @param mode
 *      IM_HAL_TRANSFORM_FLIP_H
 *      IM_HAL_TRANSFORM_FLIP_V
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddFlipTask(im_job_id_t job_id,
                                const rga_buffer_t src, rga_buffer_t dst, int mode);

/**
 * Add blend(SRC + DST -> DST) task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param fg_image
 *      The foreground image.
 * @param bg_image
 *      The background image, which is also the output destination image.
 * @param mode
 *      Port-Duff mode:
 *          IM_ALPHA_BLEND_SRC
 *          IM_ALPHA_BLEND_DST
 *          IM_ALPHA_BLEND_SRC_OVER
 *          IM_ALPHA_BLEND_DST_OVER
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddBlendTask(im_job_id_t job_id,
                                 const rga_buffer_t fg_image, rga_buffer_t bg_image,
                                 int mode = IM_ALPHA_BLEND_SRC_OVER);

/**
 * Add composite(SRCA + SRCB -> DST) task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param fg_image
 *      The foreground image.
 * @param bg_image
 *      The background image.
 * @param output_image
 *      The output destination image.
 * @param mode
 *      Port-Duff mode:
 *          IM_ALPHA_BLEND_SRC
 *          IM_ALPHA_BLEND_DST
 *          IM_ALPHA_BLEND_SRC_OVER
 *          IM_ALPHA_BLEND_DST_OVER
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddCompositeTask(im_job_id_t job_id,
                                     const rga_buffer_t fg_image, const rga_buffer_t bg_image,
                                     rga_buffer_t output_image,
                                     int mode = IM_ALPHA_BLEND_SRC_OVER);

/**
 * Add color key task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param fg_image
 *      The foreground image.
 * @param bg_image
 *      The background image, which is also the output destination image.
 * @param colorkey_range
 *      The range of color key.
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddColorKeyTask(im_job_id_t job_id,
                                    const rga_buffer_t fg_image, rga_buffer_t bg_image,
                                    im_colorkey_range range, int mode = IM_ALPHA_COLORKEY_NORMAL);

/**
 * Add OSD task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param osd
 *      The osd text block.
 * @param dst
 *      The background image.
 * @param osd_rect
 *      The rectangle on the source image that needs to be OSD.
 * @param osd_config
 *      osd mode configuration.
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddOsdTask(im_job_id_t job_id,
                               const rga_buffer_t osd,const rga_buffer_t bg_image,
                               const im_rect osd_rect, im_osd_t *osd_config);

/**
 * Add nn quantize task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 * @param nninfo
 *      nn configuration
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddQuantizeTask(im_job_id_t job_id,
                                    const rga_buffer_t src, rga_buffer_t dst, im_nn_t nn_info);

/**
 * Add ROP task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 * @param rop_code
 *      The ROP opcode.
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddRopTask(im_job_id_t job_id,
                               const rga_buffer_t src, rga_buffer_t dst, int rop_code);

/**
 * Add mosaic task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param image
 *      The output destination image.
 * @param rect
 *      The rectangle on the source image that needs to be mosaicked.
 * @param mosaic_mode
 *      mosaic block width configuration:
 *          IM_MOSAIC_8
 *          IM_MOSAIC_16
 *          IM_MOSAIC_32
 *          IM_MOSAIC_64
 *          IM_MOSAIC_128
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddMosaicTask(im_job_id_t job_id,
                                  const rga_buffer_t image, im_rect rect, int mosaic_mode);

/**
 * Add color fill task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 * @param rect
 *      The rectangle on the source image that needs to be filled with color.
 * @param color
 *      The fill color value.
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddFillTask(im_job_id_t job_id, rga_buffer_t dst, im_rect rect, int color);

/**
 * Add palette task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image.
 * @param dst
 *      The output destination image.
 * @param lut
 *      The LUT table.
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddPaletteTask(im_job_id_t job_id, rga_buffer_t src, rga_buffer_t dst, rga_buffer_t lut);

/**
 * Add process task
 *
 * @param job_id
 *      Insert the job number of the task.
 * @param src
 *      The input source image and is also the foreground image in blend.
 * @param dst
 *      The output destination image and is also the foreground image in blend.
 * @param pat
 *      The foreground image, or a LUT table.
 * @param srect
 *      The rectangle on the src channel image that needs to be processed.
 * @param drect
 *      The rectangle on the dst channel image that needs to be processed.
 * @param prect
 *      The rectangle on the pat channel image that needs to be processed.
 * @param opt
 *      The image processing options configuration.
 * @param usage
 *      The image processing usage.
 *
 * @returns success or else negative error code.
 */
IM_API IM_STATUS im_AddProcessTask(im_job_id_t job_id,
                                   rga_buffer_t src, rga_buffer_t dst, rga_buffer_t pat,
                                   im_rect srect, im_rect drect, im_rect prect,
                                   im_opt_t *opt_ptr, int usage);
#endif

#endif /* #ifndef _im2d_task_h_ */
