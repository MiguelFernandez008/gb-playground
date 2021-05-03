#include <gb/gb.h>
#include <stdio.h>
#include "sprites/big_sprite.c"
#include "maps/bg_data.c"
#include "maps/bg_data.map"

// Global variables
const UINT16 wait_time = 10; // Delay time

// Functions
inline void animate() {
    set_sprite_tile(0, 4);
    set_sprite_tile(1, 6);
    delay(250);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 2);
    delay(250);
}

inline void beep() {
    NR10_REG = 0x38U;
    NR11_REG = 0x70U;
    NR12_REG = 0xE0U;
    NR13_REG = 0x0AU;
    NR14_REG = 0xC6U;
    NR51_REG |= 0x11;
}

void main() 
{
    UINT8 x = 50; // Sprite x pos
    UINT8 y = 75; // Sprite y pos

    // Initial configuration  
    set_bkg_data(0, 131, tiledata);
    VBK_REG = 1;
    VBK_REG = 0;
    set_bkg_tiles(0, 0, 20, 18, tilemap);
    SPRITES_8x16;
    set_sprite_data(0, 8, big_sprite);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 2);
    move_sprite(0, x, y);
    move_sprite(1, x + 8, y);
 
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    //NR50_REG = 0xFF;
    //NR51_REG = 0xFF;
    //NR52_REG = 0x80;
    
    //printf("GBDK Playground");

    while (1) 
    {
        // Moving sprite
        switch (joypad())
        {
        case J_RIGHT:
            x++;
            move_sprite(0, x, y);
            move_sprite(1, x + 8, y);            
            delay(wait_time);
            break;
        case J_LEFT:
            x--;
            move_sprite(0, x, y);
            move_sprite(1, x + 8, y);
            delay(wait_time);
            break;
        case J_UP:
            y--;
            move_sprite(0, x, y);
            move_sprite(1, x + 8, y);
            delay(wait_time);
            break;
        case J_DOWN:
            y++;
            move_sprite(0, x, y);
            move_sprite(1, x + 8, y);
            delay(wait_time);
            break;
        }
        //beep();
        //animate();
    }    
}