#ifndef MODE_SWITCH_H_
#define MODE_SWITCH_H_

/*
 * P001 = ADC Channel 1 (Left)
 * P000 = ADC Channel 0 (Right)
 */
#define AMIC_LEFT_CHANNEL  ADC_CHANNEL_0
#define AMIC_RIGHT_CHANNEL ADC_CHANNEL_1

#define SHARED_PIN_P101  BSP_IO_PORT_01_PIN_01
#define SHARED_PIN_P102  BSP_IO_PORT_01_PIN_02
#define SHARED_PIN_P103  BSP_IO_PORT_01_PIN_03

fsp_err_t Switch_To_QSPI_Mode(void);
fsp_err_t Switch_To_DMIC_Mode(void);
fsp_err_t Switch_To_AMIC_Right(void);
fsp_err_t Switch_To_AMIC_Left(void);


#endif
