// Ansteuerung eines HD44780 kompatiblen LCD im 4-Bit-Interfacemodus
// http://www.mikrocontroller.net/articles/HD44780
// http://www.mikrocontroller.net/articles/AVR-GCC-Tutorial/LCD-Ansteuerung
//
// Die Pinbelegung ist �ber defines in lcd-routines.h einstellbar

#include <XMC4500.h>
#include "lcd-routines.h"
//#include <util/delay.h>

////////////////////////////////////////////////////////////////////////////////
// Erzeugt einen Enable-Puls

void delay_ms(long unsigned int i)
{
	while(i--)
	{
		__NOP();
	}
}


static void lcd_enable( void )
{
	PORT2->OUT &= ~(0x00000400);    // Enable auf 0 setzen
    delay_ms( LCD_ENABLE_US );  // kurze Pause us
    PORT2->OUT |= 0x00000400;     // Enable auf 1 setzen
}

static void buffer_enable( void )
{
	PORT2->OUT |= 0x00000040;
	delay_ms( LCD_ENABLE_US );  // kurze Pause us
	PORT2->OUT &= ~(0x00000040);
}

////////////////////////////////////////////////////////////////////////////////
// Sendet eine 4-bit Ausgabeoperation an das LCD
static void lcd_out( uint8_t data )
{
    data &= 0xF0;                       // obere 4 Bit maskieren

    LCD_PORT &= ~(0xF0>>(4-LCD_DB));    // Maske l�schen
    LCD_PORT |= (data>>(4-LCD_DB));     // Bits setzen
    lcd_enable();
}

////////////////////////////////////////////////////////////////////////////////
// Initialisierung: muss ganz am Anfang des Programms aufgerufen werden.
void lcd_init( void )
{



    // verwendete Pins auf Ausgang schalten

	PORT3->IOCR0=0x80808080;
	PORT3->IOCR4=0x00000080;
	PORT2->IOCR8=0x00800000;
	PORT2->IOCR4=0x00800000;
	//PORT1->IOCR12=0x80000000;

	/*uint32_t pins = (0x0F << LCD_DB) |           // 4 Datenleitungen
                   (1<<LCD_RS) |                // R/S Leitung
                   (1<<LCD_EN);                 // Enable Leitung
    LCD_DDR |= pins;*/
 uint32_t pins=0x0000001F;
    // initial alle Ausg�nge auf Null
    LCD_PORT &= ~pins;
    //PORT1->OUT|=0x00008000;
    // warten auf die Bereitschaft des LCD
    delay_ms( LCD_BOOTUP_MS );

    // Soft-Reset muss 3mal hintereinander gesendet werden zur Initialisierung
    lcd_out( LCD_SOFT_RESET );
    delay_ms( LCD_SOFT_RESET_MS1 );

    lcd_enable();
    delay_ms( LCD_SOFT_RESET_MS2 );

    lcd_enable();
    delay_ms( LCD_SOFT_RESET_MS3 );

    // 4-bit Modus aktivieren
    lcd_out( LCD_SET_FUNCTION |
             LCD_FUNCTION_4BIT );
    delay_ms( LCD_SET_4BITMODE_MS );

    // 4-bit Modus / 2 Zeilen / 5x7
    lcd_command( LCD_SET_FUNCTION |
                 LCD_FUNCTION_4BIT |
                 LCD_FUNCTION_2LINE |
                 LCD_FUNCTION_5X7 );

    // Display ein / Cursor aus / Blinken aus
    lcd_command( LCD_SET_DISPLAY |
                 LCD_DISPLAY_ON |
                 LCD_CURSOR_OFF |
                 LCD_BLINKING_OFF);

    // Cursor inkrement / kein Scrollen
    lcd_command( LCD_SET_ENTRY |
                 LCD_ENTRY_INCREASE |
                 LCD_ENTRY_NOSHIFT );

    lcd_clear();
}

////////////////////////////////////////////////////////////////////////////////
// Sendet ein Datenbyte an das LCD
void lcd_data( uint8_t data )
{
    LCD_PORT |= (1<<LCD_RS);    // RS auf 1 setzen
    buffer_enable();
    lcd_out( data );            // zuerst die oberen,
    lcd_out( data<<4 );         // dann die unteren 4 Bit senden

    delay_ms( LCD_WRITEDATA_US );//us
}

////////////////////////////////////////////////////////////////////////////////
// Sendet einen Befehl an das LCD
void lcd_command( uint8_t data )
{
    LCD_PORT &= ~(1<<LCD_RS);    // RS auf 0 setzen
    buffer_enable();
    lcd_out( data );             // zuerst die oberen,
    lcd_out( data<<4 );           // dann die unteren 4 Bit senden

    delay_ms( LCD_COMMAND_US ); //us
}

////////////////////////////////////////////////////////////////////////////////
// Sendet den Befehl zur L�schung des Displays
void lcd_clear( void )
{
    lcd_command( LCD_CLEAR_DISPLAY );
    delay_ms( LCD_CLEAR_DISPLAY_MS );
}

////////////////////////////////////////////////////////////////////////////////
// Sendet den Befehl: Cursor Home
void lcd_home( void )
{
    lcd_command( LCD_CURSOR_HOME );
    delay_ms( LCD_CURSOR_HOME_MS );
}

////////////////////////////////////////////////////////////////////////////////
// Setzt den Cursor in Spalte x (0..15) Zeile y (1..4)

void lcd_setcursor( uint8_t x, uint8_t y )
{
    uint8_t data;

    switch (y)
    {
        case 1:    // 1. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE1 + x;
            break;

        case 2:    // 2. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE2 + x;
            break;

        default:
            return;                                   // f�r den Fall einer falschen Zeile
    }

    lcd_command( data );
}

////////////////////////////////////////////////////////////////////////////////
// Schreibt einen String auf das LCD

void lcd_string( const char *data )
{
    while( *data != '\0' )
        lcd_data( *data++ );
}

////////////////////////////////////////////////////////////////////////////////
// Schreibt ein Zeichen in den Character Generator RAM

void lcd_generatechar( uint8_t code, const uint8_t *data )
{
    // Startposition des Zeichens einstellen
    lcd_command( LCD_SET_CGADR | (code<<3) );

    // Bitmuster �bertragen
    for ( uint8_t i=0; i<8; i++ )
    {
        lcd_data( data[i] );
    }
}
