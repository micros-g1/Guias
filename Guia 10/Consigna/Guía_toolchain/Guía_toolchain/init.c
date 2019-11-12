#include <string.h>
#include <stdint.h>

#define __IO volatile
typedef struct {
  __IO uint16_t STCTRLH;                           /**< Watchdog Status and Control Register High, offset: 0x0 */
  __IO uint16_t STCTRLL;                           /**< Watchdog Status and Control Register Low, offset: 0x2 */
  __IO uint16_t TOVALH;                            /**< Watchdog Time-out Value Register High, offset: 0x4 */
  __IO uint16_t TOVALL;                            /**< Watchdog Time-out Value Register Low, offset: 0x6 */
  __IO uint16_t WINH;                              /**< Watchdog Window Register High, offset: 0x8 */
  __IO uint16_t WINL;                              /**< Watchdog Window Register Low, offset: 0xA */
  __IO uint16_t REFRESH;                           /**< Watchdog Refresh register, offset: 0xC */
  __IO uint16_t UNLOCK;                            /**< Watchdog Unlock register, offset: 0xE */
  __IO uint16_t TMROUTH;                           /**< Watchdog Timer Output Register High, offset: 0x10 */
  __IO uint16_t TMROUTL;                           /**< Watchdog Timer Output Register Low, offset: 0x12 */
  __IO uint16_t RSTCNT;                            /**< Watchdog Reset Count register, offset: 0x14 */
  __IO uint16_t PRESC;                             /**< Watchdog Prescaler register, offset: 0x16 */
} WDOG_Type;
#define WDOG                                     ((WDOG_Type *)0x40052000u)

void init(void) {
    extern char _bss_start[];
    extern char _bss_end[];

	extern char _data_start[];
	extern char _data_end[];
	extern char _data_init_values[];

	WDOG->UNLOCK = 0xC520;
	WDOG->UNLOCK = 0xD928;
	WDOG->STCTRLH = 0x01D2;

    memset(_bss_start, 0, (_bss_end - _bss_start));
	
	memcpy(_data_start, _data_init_values, (_data_end - _data_start));
}
