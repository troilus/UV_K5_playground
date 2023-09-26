#pragma once
#include "system.hpp"
#include "uv_k5_display.hpp"

class CRssiPrinter
{
public:
    static void Handle(void)
    {
        TUV_K5Display DisplayBuff(gDisplayBuffer);
        const TUV_K5SmallNumbers FontSmallNr(gSmallDigs);
        CDisplay Display(DisplayBuff);

        if (!(GPIOC->DATA & 0b1))
        {
            return;
        }

        Display.SetCoursor(3, 0);
        Display.SetFont(&FontSmallNr);

        char C8RssiString[] = "g000";
        unsigned char u8Rssi = ((BK4819Read(0x67) >> 1) & 0xFF);
        if (!u8Rssi)
        {
            return;
        }

        if (u8Rssi > 160)
        {
            u8Rssi -= 160;
            C8RssiString[0] = ' ';
        }
        else
        {
            u8Rssi = 160 - u8Rssi;
            C8RssiString[0] = '-';
        }

        C8RssiString[1] = '0' + u8Rssi / 100;
        C8RssiString[2] = '0' + (u8Rssi / 10) % 10;
        C8RssiString[3] = '0' + u8Rssi % 10;

        Display.Print(C8RssiString);
    }
};
