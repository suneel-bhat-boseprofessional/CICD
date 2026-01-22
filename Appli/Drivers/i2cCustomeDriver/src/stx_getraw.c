
#include "main.h" // for hi2c1
#include "../inc/stx_getraw.h"
#include <stdio.h>
#include "stx_upgrade_fw_bin.h"
#define ST_80XX_RAWTYPE_RAW		0x06
#define ST_80XX_DISTYPE_RAW		0x86
#define ST_GET_RAW_DELAY		5
#define ST_GET_RAW_FRAME_NUM		5
#include <stdint.h>
#include <stdlib.h>

// Typedefs for compatibility
typedef uint8_t u8;
typedef uint16_t u16;

// macros and constants
#define MAX_NUM_TOUCHES 10
#define MOVE_LIMIT 2
// macros moved to stx_getraw.h

// Dummy variables
int is_power_down = 0;
int max_touches = MAX_NUM_TOUCHES;
struct coop_data finger[40];

// Dummy function stubs
#define STX_INFO(fmt, args...) \
do{	\
	printf("[SITRONIX][Info]" fmt "\n", ##args);\
}while(0)

#define STX_ERROR(fmt, args...) \
do{	\
	printf("[SITRONIX][ERR]" fmt "\n", ##args);\
}while(0)


#define STX_DEBUG(fmt, args...) \
do{	\
	printf("[SITRONIX][Debug]" fmt "\n", ##args);\
}while(0)

void STX_report_touch_one_sync(struct coop_data *f) { /* stub */ }



/*******************HFST Platform specific***********************************/
int stx_i2c_read_bytes(unsigned char addr, unsigned char *rxbuf, int len)
{
	// I2C start -> 0xAA -> RegAddr ->I2C stop -> delay -> I2C start -> 0xAB  -> read with ACK -> ...read with NACK -> I2C stop
	HAL_StatusTypeDef status;
	uint16_t deviceAddr = 0x55 << 1; // Left shift for HAL (0xAA for write, 0xAB for read)
	
	// Step 1: Write register address (0xAA = write address)
	status = HAL_I2C_Master_Transmit(&hi2c1, deviceAddr, &addr, 1, HAL_MAX_DELAY);
	if (status != HAL_OK)
	{
		STX_ERROR("I2C Write failed: 0x%02X", status);
		return -1;
	}
	
	// Step 2: Add delay as specified
	HAL_Delay(1);
	
	// Step 3: Read data (0xAB = read address, automatically handled by HAL)
	status = HAL_I2C_Master_Receive(&hi2c1, deviceAddr, rxbuf, len, HAL_MAX_DELAY);
	if (status != HAL_OK)
	{
		STX_ERROR("I2C Read failed: 0x%02X", status);
		return -1;
	}
	
	return len;
}

int stx_i2c_write_bytes(unsigned char *txbuf, int len)
{
	//	I2C start -> 0xAA -> RegAddr ->value0 ->value1 ->value2 ...I2C stop
	HAL_StatusTypeDef status;
	uint16_t deviceAddr = 0x55 << 1; // Left shift for HAL (0xAA for write address)
	
	// Send register address and data in one transaction
	// txbuf[0] = register address, txbuf[1..len-1] = data bytes
	status = HAL_I2C_Master_Transmit(&hi2c1, deviceAddr, txbuf, len, HAL_MAX_DELAY);
	if (status != HAL_OK)
	{
		STX_ERROR("I2C Write failed: 0x%02X", status);
		return -1;
	}
	
	return len;
}

void st_msleep(int time)
{
	//delay time (ms)
	HAL_Delay(time);
}

// Add stx_i2c_read function for compatibility
int stx_i2c_read(int addr, unsigned char *rxbuf, int len) 
{
    return stx_i2c_read_bytes((unsigned char)addr, rxbuf, len);
}
/************************************************************************/

int STX_RD_Reg(unsigned char addr, unsigned char *rxbuf, int len)
{ 
    // Read from I2C device using HAL
    if (HAL_I2C_Mem_Read(&hi2c1, 0x55 << 1, addr, I2C_MEMADD_SIZE_8BIT, rxbuf, len, 100) == HAL_OK)
        return len;
    else
        return -1;
}

int STX_WR_Reg_direct(short addr, unsigned char *rxbuf, int len) 
{ 
    // Write to I2C device using HAL
    // rxbuf[0] should be register address, rxbuf[1..] is data
    if (HAL_I2C_Mem_Write(&hi2c1, 0x55 << 1, rxbuf[0], I2C_MEMADD_SIZE_8BIT, &rxbuf[1], len-1, 100) == HAL_OK)
        return len;
    else
        return -1;
}

/************************************************************************/

int rx_chs;
int tx_chs;
static int sitronix_get_xy_chs(void)
{
	int ret = 0;
	unsigned char txflag = 0;
	unsigned char buf[2];

	ret = stx_i2c_read_bytes(0xF0, &txflag, 1);
	if (ret < 0)
	{
		printf("%s: Read 0xF0 error!(%d)\n", __func__, ret);
		return ret;
	}

	ret = stx_i2c_read_bytes(0xF5, buf, 2);
	if (ret < 0)
	{
		printf("%s: Read XY channels error!(%d)\n", __func__, ret);
		return ret;
	}

	txflag = (txflag & 0x4) >> 2;

	if (txflag)
	{
		rx_chs = buf[0];
		tx_chs = buf[1];
	}
	else
	{
		rx_chs = buf[1];
		tx_chs = buf[0];
	}
	printf("RX_chs = %d\n", rx_chs);
	printf("TX_chs = %d\n", tx_chs);

	return 0;
}

int stx_get_mutualRaw_value(void)
{
	signed short disv;
	unsigned char disbuf[128] = {0};
	unsigned char buf[2];
	int i,j;
	int index;
	int count;
	
	for(j = 0;j < ST_GET_RAW_DELAY ; j++)
		st_msleep(1000);

	sitronix_get_xy_chs();
	// Send channel info over UART
	extern UART_HandleTypeDef huart1;
	char uart_buf[64];
	int uart_len = snprintf(uart_buf, sizeof(uart_buf), "RAW:(tx_chs = %d,rx_chs = %d)\r\n", tx_chs, rx_chs);
	HAL_UART_Transmit(&huart1, (uint8_t*)uart_buf, uart_len, HAL_MAX_DELAY);

	printf("RAW:(tx_chs = %d,rx_chs = %d)\n",tx_chs,rx_chs);
	

	buf[0] = 0xFF;
	buf[1] = 0xEF;
	stx_i2c_write_bytes(buf,2);
	HAL_Delay(500);

	count = rx_chs * ST_GET_RAW_FRAME_NUM;
	while(count)
	{
		stx_i2c_read_bytes(0x40,disbuf,(tx_chs * 2 + 8));
		if (disbuf[0] == ST_80XX_RAWTYPE_RAW)
		{
			index = disbuf[2];
			count--;
			printf("RX%d :",index);
			for (i = 0; i < tx_chs; i++)
			{
				disv = (signed short)((disbuf[4 + 2 * i]) * 0x100 + disbuf[5 + 2 * i]);
				printf("%d,",disv);
			}
			printf("\n");
		}
	}

	buf[0] = 0x02;
	buf[1] = 0x01;
	stx_i2c_write_bytes(buf,2);
	st_msleep(100);
	return 0;
}



int stx_get_algorithmRaw_value(void)
{
	signed short disv;
	unsigned char disbuf[128] = {0};
	// unsigned char buf[2]; // Unused, remove warning
	int i,j;
	int index;
	int count;

	for(j = 0;j < ST_GET_RAW_DELAY ; j++)
		st_msleep(1000);

	sitronix_get_xy_chs();

	printf("DIST:(tx_chs = %d,rx_chs = %d)\n",tx_chs,rx_chs);

	count = rx_chs * ST_GET_RAW_FRAME_NUM;
	while(count)
	{
		stx_i2c_read_bytes(0x40,disbuf,(tx_chs * 2 + 8));
		if (disbuf[0] == ST_80XX_DISTYPE_RAW)
		{
			index = disbuf[2];
			count--;
			printf("RX%d :",index);
			for (i = 0; i < tx_chs; i++)
			{
				disv = (signed short)((disbuf[4 + 2 * i]) * 0x100 + disbuf[5 + 2 * i]);
				printf("%d,",disv);
			}
			printf("\n");
		}
	}
	return 0;
}

static int sitronix_get_max_touches(void)
{
    int ret = 0;
    uint8_t buffer[1];
    STX_DEBUG("%s,line=%d", __FUNCTION__, __LINE__);

    ret = stx_i2c_read(MAX_NUM_TOUCHES, buffer, 1);
    if (ret < 0)
    {
        STX_ERROR("read max touches error (%d)", ret);
        return ret;
    }
    else
    {
        max_touches = buffer[0];
        STX_INFO("max touches = %d ", max_touches);
    }
    return 0;
}

int STX_thread()
{
	// u16 valuebit[10] = {}; // Unused, remove warning
    u8 i;
    u8 buf[42];
    if (is_power_down == 0)
    {
#ifdef SITRONIX_GESTURE
    ...
#endif
		sitronix_get_max_touches();
        STX_RD_Reg(0x12, buf, 40);
        for (i = 0; i < max_touches; i++)
        {
            if (buf[i * 4] & 0x80)
            {
                finger[i].x = (u16)((buf[i * 4] & 0x70) << 4 | buf[i * 4 + 1]);
                finger[i].y = (u16)((buf[i * 4] & 0x07) << 8 | buf[i * 4 + 2]);
                if(finger[i].per_valuebit == 0)
                {
                    finger[i].status = KEY_DOWN;
                    finger[i].per_x = finger[i].x;
                    finger[i].per_y = finger[i].y;
                }
                else if((abs(finger[i].per_x - finger[i].x) > MOVE_LIMIT)||(abs(finger[i].per_y - finger[i].y) > MOVE_LIMIT))
                {
                    finger[i].status = KEY_MOVE;
                    finger[i].per_x = finger[i].x;
                    finger[i].per_y = finger[i].y;
                }
                else
                {
                    finger[i].status = KEY_PRESS;
                }
                finger[i].per_valuebit = 1;
				printf(" touch down X=%d,Y=%d\r\n", finger[i].x, finger[i].y);
            }
            else
            {
                finger[i].x = 0;
                finger[i].y = 0;
                finger[i].per_x = 0;
                finger[i].per_y = 0;
                if(finger[i].per_valuebit == 0)
                {
                    finger[i].status = NO_TOUCH;
                }
                else
                {
                    finger[i].status = KEY_UP;
                }
                finger[i].per_valuebit = 0;
				printf(" touch up  X=%d,Y=%d\r\n", finger[i].x, finger[i].y);
            }
        }
        STX_report_touch_one_sync(finger);
    }
#ifdef ST_SMART_WAKE_UP
    ...
#endif
    return 0;
}

