
#include "stm32f0xx_hal.h"
#include "ir_lib.h"
#include "dwt.h"

uint32_t data;
uint8_t count;


uint32_t receive_data (void)
{
	uint32_t code=0;

		  /* The START Sequence begin here
	   * there will be a pulse of 9ms LOW and
	   * than 4.5 ms space (HIGH)
	   */
	  while (!(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_1)));  // wait for the pin to go high.. 9ms LOW

	  while ((HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_1)));  // wait for the pin to go low.. 4.5ms HIGH

	  /* START of FRAME ends here*/

	  /* DATA Reception
	   * We are only going to check the SPACE after 562.5us pulse
	   * if the space is 562.5us, the bit indicates '0'
	   * if the space is around 1.6ms, the bit is '1'
	   */

	  for (int i=0; i<32; i++)
	  {
		  count=0;

		  while (!(HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_1))); // wait for pin to go high.. this is 562.5us LOW

		  while ((HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_1)))  // count the space length while the pin is high
		  {
			  count++;
			  delay_us(100);
		  }

		  if (count > 12) // if the space is more than 1.2 ms
		  {
			  code |= (1UL << (31-i));   // write 1
		  }

		  else code &= ~(1UL << (31-i));  // write 0
	  }

		return code;
}

uint32_t convert_code (uint32_t code)
{
		switch (code)
		{
			case (0xFFA25D)://0xFFA25D
		data=1;//0x06
				break;

			case (0xFF629D):
		data=2;//0x5B
				break;

			case (0xFFE21D):
		data=3;//0x4F
				break;

			case (0xFF22DD):
		data=4;//0x66
				break;

			case (0xFF02FD):
		data=5;//0x6D
				break;

			case (0xFFC23D):
		data=6;//0x7D
				break;

			case (0xFFE01F):
		data=7;//0x07
				break;

			case (0xFFA857):
		data=8;//0x7F
				break;

			case (0xFF906F):
		data=9;//0x6F
				break;

			case (0xFFB04F):
		data=('#');//0x76
				break;

			case (0XFF6897):
		data=('*');//0x76
				break;

			case (0xFF9867):
		data=0;//0x3F
				break;

			case (0xFF38C7):
		data=('K');//0x40
				break;

			case (0xFF18E7):
		data=('^');//0x23
				break;

			case (0xFF10EF):
		data=('<');//0x30
				break;

			case (0xFF5AA5):
		data= ('>');//0x06
				break;

			case (0xFF4AB5):
		data=('u') ;//0x1C
				break;

			default :
				break;
		}

	return data;
}

