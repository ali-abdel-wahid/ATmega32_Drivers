/*
*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<       CLCD_Program.c        >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
* 
*  Author: Ali Abdelwahed
*   Layar : HAL
*   SWC   : CLCD
*
*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <util/delay.h>

#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"

void  CLCD_voidInit          (void              )
{
    /*========================== 8 Bits Mode ==================================*/
    #if CLCD_MODE == 8

    _delay_ms(50);

    DIO_enumSetPortDirection     (CLCD_DATA_PORT, DIO_PORT_OUTPUT            );
    DIO_enumSetPinDirection      (CLCD_CONTROL_PORT, CLCD_RS , DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection      (CLCD_CONTROL_PORT, CLCD_RW , DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection      (CLCD_CONTROL_PORT, CLCD_EN , DIO_PIN_OUTPUT);
    
    /* Return cursor to the first position on the first line */
    CLCD_voidSendCommand (lcd_Home);
    _delay_ms(1);

    /* Function SET Commend : 2 Lines , 5*8 font size */
    CLCD_voidSendCommand ( EIGHT_BITS );
    _delay_ms(1); 

    /* Disolay & Cursor (ON/OFF) Control*/
    CLCD_voidSendCommand (lcd_DisplayOn_CursorOff);
    _delay_ms(1);

    /*DISPLAY CLEAR*/
    CLCD_voidClearScreen ();

    /*ENTRY MODE SET*/
    CLCD_voidSendCommand (lcd_EntryMode);
    _delay_ms(1);
   
   /*========================== 4 Bits Mode ==================================*/
   #elif CLCD_MODE == 4

   _delay_ms(50);
    DIO_enumSetPinDirection      (CLCD_DATA_PORT,DIO_PIN4,DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection      (CLCD_DATA_PORT,DIO_PIN5,DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection      (CLCD_DATA_PORT,DIO_PIN6,DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection      (CLCD_DATA_PORT,DIO_PIN7,DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection      (CLCD_CONTROL_PORT, CLCD_RS , DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection      (CLCD_CONTROL_PORT, CLCD_RW , DIO_PIN_OUTPUT);
    DIO_enumSetPinDirection      (CLCD_CONTROL_PORT, CLCD_EN , DIO_PIN_OUTPUT);

    /* Return cursor to the first position on the first line */
    CLCD_voidSendCommand (lcd_Home);
    _delay_ms(30);

    /* Function SET Commend : 2 Lines , 5*8 font size */
    CLCD_voidSendCommand ( FOUR_BITS );
    _delay_ms(1); 

    /* Disolay & Cursor (ON/OFF) Control*/
    CLCD_voidSendCommand (lcd_DisplayOn_CursorOff);
    _delay_ms(1);

    /*DISPLAY CLEAR*/
    CLCD_voidClearScreen ();

    /*ENTRY MODE SET*/
    CLCD_voidSendCommand (lcd_EntryMode);
    _delay_ms(1);

#endif

}
/****************************************************************************************************/
void  CLCD_voidSendData      (u8 Copy_u8Data    )
{
    /*========================== 8 Bits Mode ==================================*/
    #if CLCD_MODE == 8

    DIO_enumSetPortValue (CLCD_DATA_PORT    , Copy_u8Data);
    DIO_enumSetPinValue  (CLCD_CONTROL_PORT , CLCD_RS, DIO_PIN_HIGH);
    DIO_enumSetPinValue  (CLCD_CONTROL_PORT , CLCD_RW, DIO_PIN_LOW);
    CLCD_voidSendFallingEdge();

    /*========================== 4 Bits Mode ==================================*/
    #elif CLCD_MODE == 4

    DIO_enumSetPinValue          (CLCD_CONTROL_PORT , CLCD_RS, DIO_PIN_HIGH);
    DIO_enumSetPinValue          (CLCD_CONTROL_PORT , CLCD_RW, DIO_PIN_LOW);
    DIO_voidWriteHighNibbles     (CLCD_DATA_PORT,(Copy_u8Data>>4));
    CLCD_voidSendFallingEdge     ();
    DIO_voidWriteHighNibbles     (CLCD_DATA_PORT,Copy_u8Data);
    CLCD_voidSendFallingEdge     ();

    #endif
}
/****************************************************************************************************/
void  CLCD_voidSendCommand   (u8 Copy_u8Command )
{
    /*========================== 8 Bits Mode ==================================*/
    #if CLCD_MODE == 8

    DIO_enumSetPortValue (CLCD_DATA_PORT    , Copy_u8Command);
    DIO_enumSetPinValue  (CLCD_CONTROL_PORT , CLCD_RS, DIO_PIN_LOW);
    DIO_enumSetPinValue  (CLCD_CONTROL_PORT , CLCD_RW, DIO_PIN_LOW);
    CLCD_voidSendFallingEdge();

    /*========================== 4 Bits Mode ==================================*/
    #elif CLCD_MODE == 4
    DIO_enumSetPinValue          (CLCD_CONTROL_PORT , CLCD_RS, DIO_PIN_LOW);
    DIO_enumSetPinValue          (CLCD_CONTROL_PORT , CLCD_RW, DIO_PIN_LOW);
    DIO_voidWriteHighNibbles     (CLCD_DATA_PORT,(Copy_u8Command>>4));
    CLCD_voidSendFallingEdge     ();
    DIO_voidWriteHighNibbles     (CLCD_DATA_PORT,Copy_u8Command);
    CLCD_voidSendFallingEdge     ();
    #endif
}
/****************************************************************************************************/
void  CLCD_voidSendString    (const u8 * Copy_u8PtrString   )
{
    u8 LOC_Iterator = 0;

    while (Copy_u8PtrString[LOC_Iterator] != '\0' )
    {
        CLCD_voidSendData (Copy_u8PtrString[LOC_Iterator]);
        LOC_Iterator++;
    }
    
}
/****************************************************************************************************/
static void CLCD_voidSendFallingEdge(void) 
{
    DIO_enumSetPinValue  (CLCD_CONTROL_PORT , CLCD_EN, DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_enumSetPinValue  (CLCD_CONTROL_PORT , CLCD_EN, DIO_PIN_LOW);
    _delay_ms(1);
}
/****************************************************************************************************/
void  CLCD_voidClearScreen   (void              )
{
    CLCD_voidSendCommand   (lcd_Clear);
    _delay_ms(10);
}

/*================================================ END ===================================================*/