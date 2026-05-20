#include "hal_data.h"
#include "mode_switch.h"
#include "hal_data.h"
#include "AudioRecord.h"

fsp_err_t Switch_To_QSPI_Mode(void)
{
    fsp_err_t err = FSP_SUCCESS;
    #if 0
    err = R_SPI_Close(&g_spi1_ctrl);
    if (FSP_SUCCESS != err)
        return err;

    R_IOPORT_PinCfg(&g_ioport_ctrl, SHARED_PIN_P101, (uint32_t)(IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_QSPI));
    R_IOPORT_PinCfg(&g_ioport_ctrl, SHARED_PIN_P102, (uint32_t)(IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_QSPI));
    R_IOPORT_PinCfg(&g_ioport_ctrl, SHARED_PIN_P103, (uint32_t)(IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_QSPI));

    err = R_QSPI_Open(&g_qspi_ctrl, &g_qspi_cfg);
    #endif
    return err;
}

fsp_err_t Switch_To_DMIC_Right_Mode(void)
{
    fsp_err_t err = FSP_SUCCESS;
    #if 0
    err = R_QSPI_Close(&g_qspi_ctrl);
    if (FSP_SUCCESS != err)
        return err;

    R_IOPORT_PinCfg(&g_ioport_ctrl, SHARED_PIN_P101, (uint32_t)(IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_SPI));
    R_IOPORT_PinCfg(&g_ioport_ctrl, SHARED_PIN_P102, (uint32_t)(IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_SPI));
    R_IOPORT_PinCfg(&g_ioport_ctrl, SHARED_PIN_P103, (uint32_t)(IOPORT_CFG_PERIPHERAL_PIN | IOPORT_PERIPHERAL_SPI));

    // err = R_SPI_Open(&g_spi1_ctrl, &g_spi1_cfg);
    #endif
    return err;
}

fsp_err_t Switch_To_AMIC_Left(void)
{
    Audio_Channel_Init();
    AudioRecordModeSet(AMIC_L_MODE);
    return FSP_SUCCESS;
}

fsp_err_t Switch_To_AMIC_Right(void)
{
    Audio_Channel_Init();
    AudioRecordModeSet(AMIC_R_MODE);
    return FSP_SUCCESS;
}
