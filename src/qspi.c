#include "hal_data.h"
#include <string.h>
#include <stdio.h>
#include "DbgTrace.h"
#include "UartMgr.h"
#include "qspi.h"
/* RA 系列 QSPI 預設映射的基底位址 */
#define QSPI_FLASH_ADDRESS 0x60000000 
/* 假設我們使用 4KB Sector Erase */
#define SECTOR_SIZE        4096       

const char *test_string = "Hello RA6E1 QSPI Flash AT25SF641B Test!";
char read_buffer[64];


int qspi_flash_test(void)
{
    fsp_err_t err;
    spi_flash_status_t status;
    uint32_t write_length = strlen(test_string) + 1; // 包含字串結尾的 '\0'

    // 1. 初始化並開啟 QSPI 模組
    err = R_QSPI_Open(&g_qspi0_ctrl, &g_qspi0_cfg);
    if (FSP_SUCCESS != err) {
        DBG_UART_TRACE("QSPI Open Failed!\n");
        return err;
    }

    // 2. 擦除 (Erase) 區塊 - 寫入資料前必須先擦除為 0xFF
    // 我們從 QSPI 的起始位址 (0x60000000) 擦除一個 Sector (4KB)
    err = R_QSPI_Erase(&g_qspi0_ctrl, (uint8_t *)QSPI_FLASH_ADDRESS, SECTOR_SIZE);
    if (FSP_SUCCESS == err) {
        do {
            R_QSPI_StatusGet(&g_qspi0_ctrl, &status);
        } while (status.write_in_progress);
    } else {
        DBG_UART_TRACE("QSPI Erase Failed!\n");
        return err;
    }

    // 3. 寫入 (Write) 字串資料到 Flash
    err = R_QSPI_Write(&g_qspi0_ctrl, (uint8_t *)test_string, (uint8_t *)QSPI_FLASH_ADDRESS, write_length);
    if (FSP_SUCCESS == err) {
        // 輪詢等待寫入動作完成
        do {
            R_QSPI_StatusGet(&g_qspi0_ctrl, &status);
        } while (status.write_in_progress);
    } else {
        DBG_UART_TRACE("QSPI Write Failed!\n");
        return err;
    }

    // 4. 讀取 (Read) 資料
    // 由於 RA 系列的 QSPI 是 Memory-Mapped (記憶體映射) 的，
    // 我們可以直接利用 memcpy 或指標從 0x60000000 將資料拷貝回 RAM 的 Buffer 裡
    memset(read_buffer, 0, sizeof(read_buffer)); // 清空 buffer
    memcpy(read_buffer, (uint8_t *)QSPI_FLASH_ADDRESS, write_length);

    // 5. 比對 (Compare) 結果
    if (strcmp(test_string, read_buffer) == 0) {
        // 字串一致，測試成功
        DBG_UART_TRACE("QSPI Test Passed! Read string: %s\n", read_buffer);
    } else {
        // 字串不一致，測試失敗
        DBG_UART_TRACE("QSPI Test Failed! Expected: %s, Read: %s\n", test_string, read_buffer);
    }

    // 測試結束，關閉 QSPI 模組
    R_QSPI_Close(&g_qspi0_ctrl);

    return 0;
}
