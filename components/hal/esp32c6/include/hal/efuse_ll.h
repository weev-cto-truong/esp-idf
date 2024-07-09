/*
 * SPDX-FileCopyrightText: 2022-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "soc/efuse_periph.h"
#include "hal/assert.h"
#include "esp32c6/rom/efuse.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    EFUSE_CONTROLLER_STATE_RESET            = 0,    ///< efuse_controllerid is on reset state.
    EFUSE_CONTROLLER_STATE_IDLE             = 1,    ///< efuse_controllerid is on idle state.
    EFUSE_CONTROLLER_STATE_READ_INIT        = 2,    ///< efuse_controllerid is on read init state.
    EFUSE_CONTROLLER_STATE_READ_BLK0        = 3,    ///< efuse_controllerid is on reading block0 state.
    EFUSE_CONTROLLER_STATE_BLK0_CRC_CHECK   = 4,    ///< efuse_controllerid is on checking block0 crc state.
    EFUSE_CONTROLLER_STATE_READ_RS_BLK      = 5,    ///< efuse_controllerid is on reading RS block state.
} efuse_controller_state_t;

// Always inline these functions even no gcc optimization is applied.

/******************* eFuse fields *************************/

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_flash_crypt_cnt(void)
{
    return EFUSE.rd_repeat_data1.spi_boot_crypt_cnt;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_wdt_delay_sel(void)
{
    return EFUSE.rd_repeat_data1.wdt_delay_sel;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_mac0(void)
{
    return EFUSE.rd_mac_spi_sys_0.mac_0;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_mac1(void)
{
    return EFUSE.rd_mac_spi_sys_1.mac_1;
}

__attribute__((always_inline)) static inline bool efuse_ll_get_secure_boot_v2_en(void)
{
    return EFUSE.rd_repeat_data2.secure_boot_en;
}

// use efuse_hal_get_major_chip_version() to get major chip version
__attribute__((always_inline)) static inline uint32_t efuse_ll_get_chip_wafer_version_major(void)
{
    return EFUSE.rd_mac_spi_sys_3.wafer_version_major;
}

// use efuse_hal_get_minor_chip_version() to get minor chip version
__attribute__((always_inline)) static inline uint32_t efuse_ll_get_chip_wafer_version_minor(void)
{
    return EFUSE.rd_mac_spi_sys_3.wafer_version_minor;
}

__attribute__((always_inline)) static inline bool efuse_ll_get_disable_wafer_version_major(void)
{
    return EFUSE.rd_repeat_data4.disable_wafer_version_major;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_active_hp_dbias(void)
{
    return EFUSE.rd_mac_spi_sys_2.active_hp_dbias;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_active_lp_dbias(void)
{
    return EFUSE.rd_mac_spi_sys_2.active_lp_dbias;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_lslp_dbg(void)
{
    return EFUSE.rd_mac_spi_sys_2.lslp_hp_dbg;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_lslp_hp_dbias(void)
{
    return EFUSE.rd_mac_spi_sys_2.lslp_hp_dbias;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_dslp_dbg(void)
{
    return EFUSE.rd_mac_spi_sys_2.dslp_lp_dbg;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_dslp_lp_dbias(void)
{
    return EFUSE.rd_mac_spi_sys_2.dslp_lp_dbias;
}

__attribute__((always_inline)) static inline int32_t efuse_ll_get_dbias_vol_gap(void)
{
    return EFUSE.rd_mac_spi_sys_2.dbias_vol_gap;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_blk_version_major(void)
{
    return EFUSE.rd_mac_spi_sys_3.blk_version_major;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_blk_version_minor(void)
{
    return EFUSE.rd_mac_spi_sys_3.blk_version_minor;
}

__attribute__((always_inline)) static inline bool efuse_ll_get_disable_blk_version_major(void)
{
    return EFUSE.rd_repeat_data4.disable_blk_version_major;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_chip_ver_pkg(void)
{
    return EFUSE.rd_mac_spi_sys_3.pkg_version;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_ocode(void)
{
    return EFUSE.rd_sys_part1_data4.ocode;
}

/******************* eFuse control functions *************************/

__attribute__((always_inline)) static inline bool efuse_ll_get_read_cmd(void)
{
    return EFUSE.cmd.read_cmd;
}

__attribute__((always_inline)) static inline bool efuse_ll_get_pgm_cmd(void)
{
    return EFUSE.cmd.pgm_cmd;
}

__attribute__((always_inline)) static inline void efuse_ll_set_read_cmd(void)
{
    EFUSE.cmd.read_cmd = 1;
}

__attribute__((always_inline)) static inline void efuse_ll_set_pgm_cmd(uint32_t block)
{
    HAL_ASSERT(block < ETS_EFUSE_BLOCK_MAX);
    EFUSE.cmd.val = ((block << EFUSE_BLK_NUM_S) & EFUSE_BLK_NUM_M) | EFUSE_PGM_CMD;
}

__attribute__((always_inline)) static inline void efuse_ll_set_conf_read_op_code(void)
{
    EFUSE.conf.op_code = EFUSE_READ_OP_CODE;
}

__attribute__((always_inline)) static inline void efuse_ll_set_conf_write_op_code(void)
{
    EFUSE.conf.op_code = EFUSE_WRITE_OP_CODE;
}

__attribute__((always_inline)) static inline void efuse_ll_set_dac_num(uint8_t val)
{
    EFUSE.dac_conf.dac_num = val;
}

__attribute__((always_inline)) static inline void efuse_ll_set_dac_clk_div(uint8_t val)
{
    EFUSE.dac_conf.dac_clk_div = val;
}

__attribute__((always_inline)) static inline void efuse_ll_set_pwr_on_num(uint16_t val)
{
    EFUSE.wr_tim_conf1.pwr_on_num = val;
}

__attribute__((always_inline)) static inline void efuse_ll_set_pwr_off_num(uint16_t value)
{
    EFUSE.wr_tim_conf2.pwr_off_num = value;
}

__attribute__((always_inline)) static inline uint32_t efuse_ll_get_controller_state(void)
{
    return EFUSE.status.state;
}

/******************* eFuse control functions *************************/

#ifdef __cplusplus
}
#endif
