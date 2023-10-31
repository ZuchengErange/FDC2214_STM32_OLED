#include "OLED.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
#include "sys.h"

#if CONNECTION==0//IIC
#include "IIC.h"
#endif

#if CONNECTION==2//Ӳ��SPI
#include "SPI.h"
#endif

#ifdef OLED_HAVE_FLASH
#include "ff.h"
FIL FontFile;
#endif

#ifdef FONT_6_8
unsigned char const F6x8[][6] =//6*8�ĵ���
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// sp
	0x00, 0x00, 0x00, 0x2f, 0x00, 0x00,// !
	0x00, 0x00, 0x07, 0x00, 0x07, 0x00,// "
	0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14,// #
	0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12,// $
	0x00, 0x62, 0x64, 0x08, 0x13, 0x23,// %
	0x00, 0x36, 0x49, 0x55, 0x22, 0x50,// &
	0x00, 0x00, 0x05, 0x03, 0x00, 0x00,// '
	0x00, 0x00, 0x1c, 0x22, 0x41, 0x00,// (
	0x00, 0x00, 0x41, 0x22, 0x1c, 0x00,// )
	0x00, 0x14, 0x08, 0x3E, 0x08, 0x14,// *
	0x00, 0x08, 0x08, 0x3E, 0x08, 0x08,// +
	0x00, 0x00, 0x00, 0xA0, 0x60, 0x00,// ,
	0x00, 0x08, 0x08, 0x08, 0x08, 0x08,// -
	0x00, 0x00, 0x60, 0x60, 0x00, 0x00,// .
	0x00, 0x20, 0x10, 0x08, 0x04, 0x02,// /
	0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
	0x00, 0x00, 0x42, 0x7F, 0x40, 0x00,// 1
	0x00, 0x42, 0x61, 0x51, 0x49, 0x46,// 2
	0x00, 0x21, 0x41, 0x45, 0x4B, 0x31,// 3
	0x00, 0x18, 0x14, 0x12, 0x7F, 0x10,// 4
	0x00, 0x27, 0x45, 0x45, 0x45, 0x39,// 5
	0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
	0x00, 0x01, 0x71, 0x09, 0x05, 0x03,// 7
	0x00, 0x36, 0x49, 0x49, 0x49, 0x36,// 8
	0x00, 0x06, 0x49, 0x49, 0x29, 0x1E,// 9
	0x00, 0x00, 0x36, 0x36, 0x00, 0x00,// :
	0x00, 0x00, 0x56, 0x36, 0x00, 0x00,// ;
	0x00, 0x08, 0x14, 0x22, 0x41, 0x00,// <
	0x00, 0x14, 0x14, 0x14, 0x14, 0x14,// =
	0x00, 0x00, 0x41, 0x22, 0x14, 0x08,// >
	0x00, 0x02, 0x01, 0x51, 0x09, 0x06,// ?
	0x00, 0x32, 0x49, 0x59, 0x51, 0x3E,// @
	0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C,// A
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x36,// B
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x22,// C
	0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C,// D
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x41,// E
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x01,// F
	0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A,// G
	0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,// H
	0x00, 0x00, 0x41, 0x7F, 0x41, 0x00,// I
	0x00, 0x20, 0x40, 0x41, 0x3F, 0x01,// J
	0x00, 0x7F, 0x08, 0x14, 0x22, 0x41,// K
	0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,// L
	0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F,// M
	0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F,// N
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E,// O
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x06,// P
	0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
	0x00, 0x7F, 0x09, 0x19, 0x29, 0x46,// R
	0x00, 0x46, 0x49, 0x49, 0x49, 0x31,// S
	0x00, 0x01, 0x01, 0x7F, 0x01, 0x01,// T
	0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F,// U
	0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F,// V
	0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F,// W
	0x00, 0x63, 0x14, 0x08, 0x14, 0x63,// X
	0x00, 0x07, 0x08, 0x70, 0x08, 0x07,// Y
	0x00, 0x61, 0x51, 0x49, 0x45, 0x43,// Z
	0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,// [
	0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55,// 55
	0x00, 0x00, 0x41, 0x41, 0x7F, 0x00,// ]
	0x00, 0x04, 0x02, 0x01, 0x02, 0x04,// ^
	0x00, 0x40, 0x40, 0x40, 0x40, 0x40,// _
	0x00, 0x00, 0x01, 0x02, 0x04, 0x00,// '
	0x00, 0x20, 0x54, 0x54, 0x54, 0x78,// a
	0x00, 0x7F, 0x48, 0x44, 0x44, 0x38,// b
	0x00, 0x38, 0x44, 0x44, 0x44, 0x20,// c
	0x00, 0x38, 0x44, 0x44, 0x48, 0x7F,// d
	0x00, 0x38, 0x54, 0x54, 0x54, 0x18,// e
	0x00, 0x08, 0x7E, 0x09, 0x01, 0x02,// f
	0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C,// g
	0x00, 0x7F, 0x08, 0x04, 0x04, 0x78,// h
	0x00, 0x00, 0x44, 0x7D, 0x40, 0x00,// i
	0x00, 0x40, 0x80, 0x84, 0x7D, 0x00,// j
	0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,// k
	0x00, 0x00, 0x41, 0x7F, 0x40, 0x00,// l
	0x00, 0x7C, 0x04, 0x18, 0x04, 0x78,// m
	0x00, 0x7C, 0x08, 0x04, 0x04, 0x78,// n
	0x00, 0x38, 0x44, 0x44, 0x44, 0x38,// o
	0x00, 0xFC, 0x24, 0x24, 0x24, 0x18,// p
	0x00, 0x18, 0x24, 0x24, 0x18, 0xFC,// q
	0x00, 0x7C, 0x08, 0x04, 0x04, 0x08,// r
	0x00, 0x48, 0x54, 0x54, 0x54, 0x20,// s
	0x00, 0x04, 0x3F, 0x44, 0x40, 0x20,// t
	0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C,// u
	0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C,// v
	0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C,// w
	0x00, 0x44, 0x28, 0x10, 0x28, 0x44,// x
	0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C,// y
	0x00, 0x44, 0x64, 0x54, 0x4C, 0x44,// z
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14,// ~
};
#endif

#ifdef FONT_8_16
unsigned char const F8X16[][16]=//8*16�ĵ���	  
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// 0
	0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,//! 1
	0x00,0x10,0x0C,0x06,0x10,0x0C,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//" 2
	0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,//# 3
	0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,//$ 4
	0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,//% 5
	0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,//& 6
	0x10,0x16,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//' 7
	0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//( 8
	0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//) 9
	0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//* 10
	0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,//+ 11
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,//, 12
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//- 13
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//. 14
	0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,/// 15
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//0 16
	0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//1 17
	0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//2 18
	0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//3 19
	0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//4 20
	0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//5 21
	0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//6 22
	0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//7 23
	0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//8 24
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//9 25
	0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//: 26
	0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x00,0x00,0x00,0x00,//; 27
	0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//< 28
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//= 29
	0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//> 30
	0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,//? 31
	0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,//@ 32
	0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A 33
	0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B 34
	0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C 35
	0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D 36
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E 37
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F 38
	0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G 39
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H 40
	0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I 41
	0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J 42
	0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K 43
	0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L 44
	0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,//M 45
	0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N 46
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O 47
	0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P 48
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,//Q 49
	0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R 50
	0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S 51
	0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T 52
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U 53
	0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V 54
	0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,//W 55
	0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X 56
	0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y 57
	0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z 58
	0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[ 59
	0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\ 60
	0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//] 61
	0x00,0x00,0x04,0x02,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^ 62
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_ 63
	0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//` 64
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,//a 65
	0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b 66
	0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c 67
	0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,//d 68
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,//e 69
	0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f 70
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g 71
	0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//h 72
	0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i 73
	0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j 74
	0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,//k 75
	0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l 76
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m 77
	0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n 78
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o 79
	0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,//p 80
	0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,//q 81
	0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r 82
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s 83
	0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,//t 84
	0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//u 85
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,//v 86
	0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,//w 87
	0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,//x 88
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,//y 89
	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z 90
	0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,//{ 91
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//| 92
	0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,//} 93
	0x00,0x06,0x01,0x01,0x02,0x02,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~ 94
};
#endif

#if CONNECTION==2//Ӳ��SPI
void OLED_cmd(unsigned char byte)
{
	while(!SPI_SendBusy(OLED_HW_SPI));//�ȴ��������
   OLED_DC = 0;//����ָ��
	SPI_Buff(OLED_HW_SPI) = byte;//����һ���ֽ�
}

void OLED_dat(unsigned char byte)
{
	while(!SPI_SendBusy(OLED_HW_SPI));//�ȴ��������
   OLED_DC = 1;//��������
	SPI_Buff(OLED_HW_SPI) = byte;//����һ���ֽ�
}
#endif

#if CONNECTION==1//����SPI
__inline void OLED_cmd(unsigned char byte)
{
	unsigned char i;
	OLED_DC = 0;
	for(i = 0;i < 8;i ++) //����һ����λ���� 
	{
		OLED_SCL = 0;
		if(byte & 0x80)
		{
			OLED_SDA = 1;
		}
		else
		{
			OLED_SDA = 0;
		}
		OLED_SCL = 1;
		byte = byte << 1;
	}
}

__inline void OLED_dat(unsigned char byte)
{
	unsigned char i;
	OLED_DC = 1;
	for(i = 0;i < 8;i ++) //����һ����λ���� 
	{
		OLED_SCL = 0;
		if(byte & 0x80)
		{
			OLED_SDA = 1;
		}
		else
		{
			OLED_SDA = 0;
		}
		OLED_SCL = 1;
		byte = byte << 1;
	}
}
#endif

#if CONNECTION==0//IIC
void OLED_dat(unsigned char byte)//OLEDд������
{
	IIC_Start();
	IIC_Send_Byte(OLED_ADDR);
	IIC_NAck();
	IIC_Send_Byte(0x40);//д������
	IIC_NAck();
	IIC_Send_Byte(byte);
	IIC_NAck();
	IIC_Stop();
}

void OLED_cmd(unsigned char byte)//OLEDд��ָ��
{
	IIC_Start();
	IIC_Send_Byte(OLED_ADDR);
	IIC_NAck();
	IIC_Send_Byte(0x00);//д��ָ��
	IIC_NAck();
	IIC_Send_Byte(byte);
	IIC_NAck();
	IIC_Stop();
}
#endif

void OLED_Port_Init(void)//��ʼ��OLED�ӿ�
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(OLED_GPIO_Init,ENABLE);
	GPIO_InitStructure.GPIO_Pin = 0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	#if CONNECTION!=0//����IIC
	GPIO_InitStructure.GPIO_Pin = OLED_RST_Init | OLED_DC_Init;
	#endif
	
	#if CONNECTION==1//����Ӳ��SPI
	GPIO_InitStructure.GPIO_Pin |= (OLED_SCL_Init | OLED_SDA_Init);//SCK&MOSI
	#endif
	
	GPIO_Init(OLED_PORT,&GPIO_InitStructure);
}

void OLED_contrast(unsigned char contrast)//�趨�Աȶȣ�0-255
{
	OLED_cmd(0x81);
	OLED_cmd(contrast);
}

void OLED_switch(unsigned char power)//OLED��ʾ����
{
	if(power)
	{
		OLED_cmd(0xAF);
	}
	else
	{
		OLED_cmd(0xAE);
	}
}

__inline void OLED_set_position(unsigned char column,unsigned char page)//�趨ҳд��ģʽ��page(0-7)��column(0-127)
{
	#ifdef SH1106
	column += 2;
	#endif
	OLED_cmd(0xB0 + page);//�趨page
	OLED_cmd(0x0F & column);//�趨column�ĸ���λ
	OLED_cmd(0x10 + (column >> 4));//�趨column�ĵ���λ
}

#if CONNECTION==0//IIC
void OLED_bmp(unsigned char x0,unsigned char y0,unsigned char x_lenth,unsigned char y_lenth,const unsigned char *bmp_tab)//��ʾһ��ͼƬ�������귶ΧΪ0-127�������귶ΧΪ0-7
{
	unsigned int k = 0;
	unsigned char x,y;
	for(y = 0;y < y_lenth;y ++)//����
	{
		OLED_set_position(x0,y0 + y);
		
		IIC_Start();
		IIC_Send_Byte(OLED_ADDR);
		IIC_NAck();
		IIC_Send_Byte(0x40);//д������
		IIC_NAck();
		
		for(x = 0;x < x_lenth;x ++)//����
		{
			IIC_Send_Byte(*(bmp_tab + k));
			IIC_NAck();
			k ++;
		}
		IIC_Stop();
	}
}

void OLED_clear(void)//����
{
	unsigned char i,j;
	for(i = 0;i < 8;i ++)//����
	{
		OLED_set_position(0,i);
		
		IIC_Start();
		IIC_Send_Byte(OLED_ADDR);
		IIC_NAck();
		IIC_Send_Byte(0x40);//д������
		IIC_NAck();
		
		for(j = 0;j < 128;j ++)//����
		{
			IIC_Send_Byte(0);
			IIC_NAck();
		}
		IIC_Stop();
	}
}
#elif CONNECTION==1//����SPI
void OLED_bmp(unsigned char x0,unsigned char y0,unsigned char x_lenth,unsigned char y_lenth,const unsigned char *bmp_tab)//��ʾһ��ͼƬ�������귶ΧΪ0-127�������귶ΧΪ0-7
{
	unsigned int k = 0;
	unsigned char x,y;
	for(y = 0;y < y_lenth;y ++)//����
	{
		OLED_set_position(x0,y0 + y);
		OLED_DC = 1;
		for(x = 0;x < x_lenth;x ++)//����
		{
			OLED_dat(*(bmp_tab + k));
			k ++;
		}
	}
}

void OLED_clear(void)//����
{
	unsigned char i,j;
	for(i = 0;i < 8;i ++)//����
	{
		OLED_set_position(0,i);
		OLED_DC = 1;
		for(j = 0;j < 128;j ++)//����
		{
			OLED_dat(0);
		}
	}
}

#elif CONNECTION==2//Ӳ��SPI
void OLED_bmp(unsigned char x0,unsigned char y0,unsigned char x_lenth,unsigned char y_lenth,const unsigned char *bmp_tab)//��ʾһ��ͼƬ�������귶ΧΪ0-127�������귶ΧΪ0-7
{
	unsigned int k = 0;
	unsigned char x,y;
	for(y = 0;y < y_lenth;y ++)//����
	{
		OLED_set_position(x0,y0 + y);
		OLED_DC = 1;
		for(x = 0;x < x_lenth;x ++)//����
		{
			while(!SPI_SendBusy(OLED_HW_SPI));
			SPI_Buff(OLED_HW_SPI) = *(bmp_tab + k);
			k ++;
		}
	}
}

void OLED_clear(void)//����
{
	unsigned char i,j;
	for(i = 0;i < 8;i ++)//����
	{
		OLED_set_position(0,i);
		#if CONNECTION!=0
		OLED_DC = 1;
		#endif
		for(j = 0;j < 128;j ++)//����
		{
			while(!SPI_SendBusy(OLED_HW_SPI));
			SPI_Buff(OLED_HW_SPI) = 0;
		}
	}
}
#endif
#ifdef SH1106
void OLED_Shift(unsigned char y)
{
	OLED_cmd(0x40 + y);//��COM0��ʼ��ʾ(0-63)
}

void OLED_Init(void)//��ʼ��
{
	#if CONNECTION==2
	OLED_SPI_Init();//��ʼ��Ӳ��SPI
	#endif
	
	#if CONNECTION!=0//����IIC
	OLED_Port_Init();//��ʼ���˿�
	OLED_RST = 0;//��λOLED
	delay_ms(1);
	OLED_RST = 1;
	#else
	IIC_Init();
	#endif
	
	OLED_cmd(0xA1);//���Ҳ�����(0xA0���ҷ��� 0xA1����)
	OLED_cmd(0xC8);//���²�����(0xC0���·��� 0xC8����)	
	
	OLED_switch(0);//����ʾ
	OLED_set_position(0,0);//����λ
	OLED_contrast(0x80);//�����������
	
	OLED_cmd(0xA6);//������(A6������A7����)
	OLED_cmd(0x40);//��ʾRAM��0�ж�Ӧ����COM1(Ӳ�����ӵ���ʼ)
	OLED_cmd(0xD3);//����������ʾƫ��(оƬˢ�µĿ�ʼ)
	OLED_cmd(0x00);//��COM0��ʼ��ʾ(0-63)
	
	OLED_cmd(0x32);//�趨���õ�ɱõ�ѹֵ��Ĭ��ֵ8v
	OLED_cmd(0xAD);//����DC-DCģʽ
	OLED_cmd(0x8B);//��������DC-DC
	
	OLED_cmd(0xA8);//����ˢ���ʱ���
	OLED_cmd(0x3F);//Ĭ��ֵ1/64
	
	OLED_cmd(0xD5);//������ʾʱ�ӷ�Ƶ�ʺ;���Ƶ��
	OLED_cmd(0x50);//ʱ��Ƶ��+0%������Ƶ(Ĭ��ֵ)

	OLED_cmd(0xD9);//�趨�ŵ�/Ԥ�������
	OLED_cmd(0x22);//Ԥ������2ʱ�ӣ��ŵ����2ʱ��(Ĭ��ֵ)
	
	OLED_cmd(0xDA);//�趨�ܽ�����
	OLED_cmd(0x01);//Ĭ��˳��
	
	OLED_cmd(0xDB);//�趨��������������
	OLED_cmd(0x35);//Ĭ��ֵ
	
	OLED_clear();
	OLED_switch(1);//����ʾ
}
#else
void OLED_Shift(unsigned char y)
{
	OLED_cmd(0x40 + y);
}
void OLED_Init(void)//��ʼ��
{
	#if CONNECTION==2
	OLED_SPI_Init();//��ʼ��Ӳ��SPI
	#endif
	
	#if CONNECTION!=0//����IIC
	OLED_Port_Init();//��ʼ���˿�
	OLED_RST = 0;//��λOLED
	delay_ms(1);
	OLED_RST = 1;
	#else
	IIC_Init();
	#endif
	
	OLED_switch(0);//����ʾ	
	OLED_contrast(0xFF);//�������
	
	OLED_cmd(0xA1);//���Ҳ�����(0xA0���ҷ��� 0xA1����)
	OLED_cmd(0xC8);//���²�����(0xC0���·��� 0xC8����)
	OLED_cmd(0xA6);//������(A6������A7����)
	OLED_cmd(0xA4);//������ʾ(A4������ʾ A5ȫ����)
	
	OLED_cmd(0xDA);//COM��������(2�ֽ�)
	OLED_cmd(0x12);//��ʼ����
	OLED_cmd(0x40);//RAM��0�ж�ӦCOM0
	
	OLED_cmd(0xA8);//����ˢ���ʱ���
	OLED_cmd(0x3F);//Ĭ��ֵ1/64
	
	OLED_cmd(0xD3);//������ʾƫ��(2�ֽ�)
	OLED_cmd(0x00);//��ƫ��(0-63)
	
	OLED_cmd(0xD5);//���� �����ͷ�Ƶ(2�ֽ�)
	OLED_cmd(0xF0);//����λΪ��Ƶ���ʣ�����λΪ����Ƶ��
	
	OLED_cmd(0xD9);//�趨Ԥ���(2�ֽ�)
	OLED_cmd(0xF1);//Ԥ���15ʱ�����ڣ��ŵ�1ʱ������
	
	OLED_cmd(0xDB);//�趨��������������
	OLED_cmd(0x40);//Ĭ��ֵ
	
	OLED_cmd(0x8D);//��ɱ�����
	OLED_cmd(0x14);//������ɱ�
	
	OLED_cmd(0x20);//����д��ģʽ
	OLED_cmd(0x00);
	
	OLED_clear();
	OLED_switch(1);//����ʾ	
} 
#endif

#ifdef FONT_6_8
#if CONNECTION!=0//����IIC
void OLED_6_8_Char(unsigned char y,unsigned char x,char ch)
{
	unsigned char i;
	ch -= 32;
	OLED_set_position(x,y);
	for(i = 0;i < 6;i ++)//ѭ��д��6�ֽ�
	{
		OLED_dat(F6x8[ch][i]);
	}
}
#else
void OLED_6_8_Char(unsigned char y,unsigned char x,char ch)
{
	unsigned char i;
	ch -= 32;
	
	OLED_set_position(x,y);
	IIC_Start();
	IIC_Send_Byte(OLED_ADDR);
	IIC_NAck();
	IIC_Send_Byte(0x40);//д������
	IIC_NAck();
	
	for(i = 0;i < 6;i ++)//ѭ��д��6�ֽ�
	{
		IIC_Send_Byte(F6x8[ch][i]);
		IIC_NAck();
	}
	IIC_Stop();
}
#endif
unsigned char OLED_6_8_Number(unsigned char y,unsigned char x,int number,unsigned char digits)
{
	unsigned char dig,minus = 0;//λ��
	unsigned int dig_temp;
	unsigned char i;
	unsigned char x_temp = x;
	
	if(number < 0)//�ж��Ƿ��Ǹ���
	{
		minus = 1;
		number = -number;
	}
	dig_temp = 1;
	for(dig = 0;dig < 10;dig ++)//ͳ��λ��
	{
		if(number / dig_temp == 0)
			break;
		dig_temp *= 10;
	}
	
	if(digits && dig + minus < digits)//����������С�ڹ涨λ�� ��������λ��
	{
		for(i = 0;i < digits-(dig + minus);i ++)//��ӡ�ո�
		{
			OLED_6_8_Char(y,x_temp,' ');
			x_temp += 6;
		}
	}
	
	if(minus)
	{
		OLED_6_8_Char(y,x_temp,'-');
		x_temp += 6;
	}
	
	dig_temp = 1;
	for(i = 0;i < dig-1;i ++)
	{
		dig_temp *= 10;//��dig_tempָ�����λ
	}
	
	for(i = 0;i < dig;i ++)
	{
		OLED_6_8_Char(y,x_temp,'0' + number / dig_temp);
		x_temp += 6;
		
		if(x_temp > 122)
			break;
		
		number *= 10;//����ʮ��
		number %= (dig_temp*10);//�����λ֮ǰ��λ���
	}
	
	if(dig + minus < digits)//���ش�ӡ��λ��
	{
		dig = digits;
	}
	
	if(minus)
	{
		dig ++;
	}
	return dig;
}

void OLED_6_8(unsigned char y,unsigned char x,char string[])//��ʾ6*8�ַ���
{
	while(*string != '\0')
	{
		if(x > 122 || *string == '\n')//����
		{
			x = 0;
			y ++;
			if(y > 7)
				break;
		}
		else if(*string<32 || *string>127)
			continue;
		
		OLED_6_8_Char(y,x,*string);//ƫ��32byte
		
		x += 6;
		string ++;
	}
}
#endif

#ifdef FONT_8_16
#if CONNECTION!=0//�������IIC
void OLED_8_16_Char(unsigned char y,unsigned char x,char Font)
{
	unsigned char i;
	Font -= 32;//ƫ��32byte
	OLED_set_position(x,y);
	for(i = 0;i < 8;i ++)//ѭ��д����ҳ8�ֽ�
	{
		OLED_dat(F8X16[Font][i]);
	}
	OLED_set_position(x,y + 1);
	for(;i < 16;i ++)//ѭ��д����ҳ8�ֽ�
	{
		OLED_dat(F8X16[Font][i]);
	}
}
#else
void OLED_8_16_Char(unsigned char y,unsigned char x,char Font)
{
	unsigned char i;
	Font -= 32;//ƫ��32byte
	
	OLED_set_position(x,y);
	IIC_Start();
	IIC_Send_Byte(OLED_ADDR);
	IIC_NAck();
	IIC_Send_Byte(0x40);//д������
	IIC_NAck();
	
	for(i = 0;i < 8;i ++)//ѭ��д����ҳ8�ֽ�
	{
		IIC_Send_Byte(F8X16[Font][i]);
		IIC_NAck();
	}
	IIC_Stop();
	
	OLED_set_position(x,y + 1);
	IIC_Start();
	IIC_Send_Byte(OLED_ADDR);
	IIC_NAck();
	IIC_Send_Byte(0x40);//д������
	IIC_NAck();
	
	for(;i < 16;i ++)//ѭ��д����ҳ8�ֽ�
	{
		IIC_Send_Byte(F8X16[Font][i]);
		IIC_NAck();
	}
	IIC_Stop();
}
#endif

unsigned char OLED_8_16_Number(unsigned char y,unsigned char x,int number,unsigned char digits)
{
	unsigned char dig,minus = 0;//λ��
	unsigned int dig_temp;
	unsigned char i;
	unsigned char x_temp = x;
	
	if(number < 0)//�ж��Ƿ��Ǹ���
	{
		minus = 1;
		number = -number;
	}
	dig_temp = 1;
	for(i = 0;i < 10;i ++)//ͳ��λ��
	{
		if(number / dig_temp == 0)
			break;
		dig_temp *= 10;
	}
	dig = i;
	
	if(digits && dig + minus < digits)//����������С�ڹ涨λ�� ��������λ��
	{
		for(i = 0;i < digits-(dig + minus);i ++)//��ӡ0
		{
			OLED_8_16_Char(y,x_temp,' ');
			x_temp += 8;
		}
	}
	
	if(minus)
	{
		OLED_8_16_Char(y,x_temp,'-');
		x_temp += 8;
	}
	
	dig_temp = 1;
	for(i = 0;i < dig-1;i ++)
	{
		dig_temp *= 10;//��dig_tempָ�����λ
	}
	
	for(i = 0;i < dig;i ++)
	{
		OLED_8_16_Char(y,x_temp,'0' + number / dig_temp);
		x_temp += 8;
		
		if(x_temp > 120)
			break;
		
		number *= 10;//����ʮ��
		number %= (dig_temp*10);//�����λ֮ǰ��λ���
	}
	
	if(dig + minus < digits)//���ش�ӡ��λ��
	{
		dig = digits;
	}
	
	if(minus)
	{
		dig ++;
	}
	return dig;
}

void OLED_8_16(unsigned char y,unsigned char x,char* string)
{
	while(*string)
	{
		if(x > 120 || *string == '\n')//����
		{
			x = 0;
			y += 2;
			if(y > 7)
				break;
		}
		else if(*string<32 || *string>127)
			continue;
		
		OLED_8_16_Char(y,x,*string);//ƫ��32byte
		
		x += 8;
		string ++;
	}
}
#endif

#ifdef OLED_HAVE_FLASH
void Get_HzMat(unsigned char *Code,unsigned char *mat,unsigned char Size)
{
	unsigned char High8bit,Low8bit;
	unsigned int offset;
	unsigned int NumOfRead;
   High8bit = *Code;//ȡ��8λ����
   Low8bit = *(++Code);//ȡ��8λ����
	//W25Qxx_Read(mat,((High8bit-0xa0-1) * 94 + (Low8bit-0xa0-1)) * 32 + FontOffset,32);
		//��ΪGB2312�����ȡ�ֿ�Ĵ���
	if(High8bit > 0xFE || High8bit < 0x81)
		return;
	High8bit -= 0x81;
	Low8bit -= 0x40;
	offset = ((unsigned int)192 * High8bit + Low8bit) * Size;//��ȡGBK������ָ��ĺ��ֵ�����
	//W25Qxx_Read(mat,offset,Size);
	
	f_lseek(&FontFile,offset);
	f_read(&FontFile,mat,Size,&NumOfRead);
}

unsigned char OLED_OpenFont(char* FileName)
{
	return f_open(&FontFile,FileName,FA_READ);
}

void OLED_DrawGBK16(unsigned char y,unsigned char x,char* Font)
{
	unsigned char i;
	unsigned char Buff[Font_Buff_Size];
	Get_HzMat((unsigned char*)Font,Buff,Font_Buff_Size);
	
	OLED_set_position(x,y);//�ϰ���

	for(i = 0;i < Font_Size;i ++)
	{
		OLED_dat(Buff[i]);
	}
	
	OLED_set_position(x,y+1);//�°���

	for(;i < Font_Size*2;i ++)
	{
		OLED_dat(Buff[i]);
	}
}

unsigned char OLED_GBK16(unsigned char y,unsigned char x0,const char* str)
{
	unsigned char* s = (unsigned char*)str;
	unsigned char x = x0;
	unsigned char* s0 = s;
	while(*s)
	{
		if (*s < 32)//�����ַ�
		{
			if(*s == '\n')//����
			{
				y += Font_Size/8;
				if(y >= OLED_Y)//���������8��
					break;
				x = x0;//����λ
			}
			s++;//��һ���� ASCIIռ��һ���ֽ�
		}
		else if(*s < 128)//Ӣ�Ļ�����
		{
			if(x > OLED_X-Font_Size/2)//���������
			{
				x = x0;//����λ
				y += Font_Size/8;
				if(y >= OLED_Y)//���������8��
					break;
			}
			OLED_8_16_Char(y,x,*s);
			x += Font_Size/2;//��һ���� һ��ASCIIռ��8��
			s++;//��һ���� ASCIIռ��һ���ֽ�
		}
		else//����Ǻ���
		{
			if(x > OLED_X-Font_Size)//���������
			{
				x = x0;//����λ
				y += Font_Size/8;
				if(y >= OLED_Y)//���������8��
					break;
			}
			OLED_DrawGBK16(y,x,(char*)s);//��ʾ����
			x += Font_Size;//һ�����ֺ���16��
			s += 2;//һ������ռ��2�ֽ�
		}
	}
	return (unsigned char)(s - s0);//������ʾ�����ַ���
}

#endif

void OLED_putc(char ch)
{
	static unsigned char x_pos = 0,y_pos = 0;
	static unsigned char Printf_Overflow = 0;
	unsigned char i;
	
	if(ch == '\n')
	{
		for(i = x_pos;i < 126;i += 6)//���ʣ������
		{
			OLED_6_8_Char(y_pos,i,' ');
		}
		
		x_pos = 0;
		y_pos ++;
	}
	/*
	else if(ch == '\r')
	{
		x_pos = 0;
	}
	*/
	else if(ch == '\b')
	{
		if(x_pos > 0)
			x_pos -= 6;
		else
		{
			x_pos = 126;
			if(y_pos > 0)
				y_pos --;
			else
				y_pos = 7;
		}
		OLED_6_8_Char(y_pos,x_pos,' ');
	}
	else if(ch == '\f')
	{
		OLED_clear();
		Printf_Overflow = 0;
		x_pos = 0;
		y_pos = 0;
		OLED_Shift(0);
	}
	else if(ch > 31)
	{
		OLED_6_8_Char(y_pos,x_pos,ch);
		x_pos += 6;
	}

	if(x_pos >= 126)//���򳬹���
	{
		y_pos ++;
		x_pos = 0;
		for(i = 0;i < 126;i += 6)//�����һ��
		{
			OLED_6_8_Char(y_pos,i,' ');
		}
	}
	
	if(y_pos >= OLED_Y)//���򳬹���
	{
		Printf_Overflow = 1;
		y_pos = 0;
	}
	
	if(Printf_Overflow)
		OLED_Shift(y_pos*8);
}

#ifdef OLED_PRINTF_REMAP
#include <stdio.h>
#pragma import(__use_no_semihosting)
struct __FILE
{ 
	int handle;
};

FILE __stdout;

void _sys_exit(int x)//����_sys_exit()�Ա���ʹ�ð�����ģʽ
{ 
	x = x; 
}

int fputc(int ch, FILE *f)
{
	OLED_putc((char)ch);
	return ch;
}
#endif