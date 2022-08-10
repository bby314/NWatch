/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */

#include "common.h"
#include "delay.h"
#include "led.h"
#include "sys.h"

static const int faces1[6][4] = {{0, 1, 2, 3}, {1, 5, 6, 2}, {5, 4, 7, 6}, {4, 0, 3, 7}, {0, 4, 5, 1}, {3, 2, 6, 7}};
static const int nvert1 = 8;
static const int nfaces1 = 6;

uint8_t vertices[1440][3] =
{
    { 42, 10, 1}, { 85, 10, 1}, { 85, 53, 1}, { 42, 53, 1}, { 51, 19, 1}, { 76, 19, 1}, { 76, 44, 1}, { 51, 44, 1},
    { 41, 11, 1}, { 83, 9, 1}, { 85, 52, 1}, { 42, 53, 1}, { 51, 20, 1}, { 76, 19, 1}, { 77, 44, 1}, { 52, 45, 1},
    { 40, 11, 1}, { 82, 7, 1}, { 86, 50, 1}, { 42, 53, 1}, { 51, 21, 1}, { 76, 19, 1}, { 78, 45, 1}, { 53, 46, 1},
    { 40, 12, 1}, { 80, 6, 1}, { 86, 49, 1}, { 42, 53, 1}, { 51, 22, 1}, { 76, 19, 1}, { 80, 45, 1}, { 53, 47, 1},
    { 39, 13, 1}, { 78, 5, 1}, { 86, 47, 1}, { 42, 53, 1}, { 52, 23, 1}, { 76, 19, 1}, { 81, 45, 1}, { 54, 48, 1},
    { 39, 14, 1}, { 76, 4, 1}, { 87, 46, 1}, { 43, 53, 1}, { 52, 24, 1}, { 76, 19, 1}, { 82, 44, 1}, { 55, 49, 1},
    { 38, 15, 1}, { 75, 3, 1}, { 87, 44, 1}, { 43, 53, 1}, { 52, 26, 1}, { 76, 19, 1}, { 83, 44, 1}, { 56, 50, 1},
    { 38, 16, 1}, { 73, 2, 1}, { 87, 41, 1}, { 43, 53, 1}, { 52, 27, 1}, { 75, 19, 1}, { 84, 44, 1}, { 57, 51, 1},
    { 37, 17, 1}, { 71, 2, 1}, { 86, 39, 1}, { 43, 53, 1}, { 53, 28, 1}, { 75, 19, 1}, { 85, 44, 1}, { 58, 52, 1},
    { 37, 18, 1}, { 69, 1, 1}, { 86, 36, 1}, { 43, 53, 1}, { 53, 29, 1}, { 75, 19, 1}, { 86, 43, 1}, { 59, 53, 1},
    { 37, 19, 1}, { 68, 1, 1}, { 86, 34, 1}, { 43, 53, 1}, { 53, 30, 1}, { 75, 20, 1}, { 87, 42, 1}, { 60, 54, 1},
    { 37, 20, 1}, { 66, 1, 1}, { 85, 31, 1}, { 44, 53, 1}, { 54, 32, 1}, { 75, 20, 1}, { 88, 42, 1}, { 62, 54, 1},
    { 37, 21, 1}, { 65, 1, 1}, { 84, 28, 1}, { 44, 52, 1}, { 54, 33, 1}, { 74, 20, 1}, { 88, 41, 1}, { 63, 55, 1},
    { 37, 23, 1}, { 63, 2, 1}, { 83, 25, 1}, { 44, 52, 1}, { 55, 34, 1}, { 74, 20, 1}, { 89, 40, 1}, { 64, 56, 1},
    { 37, 24, 1}, { 62, 2, 1}, { 82, 22, 1}, { 44, 52, 1}, { 55, 36, 1}, { 74, 21, 1}, { 90, 39, 1}, { 65, 57, 1},
    { 37, 25, 1}, { 60, 3, 1}, { 81, 20, 1}, { 44, 51, 1}, { 56, 37, 1}, { 73, 21, 1}, { 91, 38, 1}, { 66, 57, 1},
    { 37, 26, 1}, { 59, 3, 1}, { 80, 17, 1}, { 44, 51, 1}, { 56, 38, 1}, { 73, 22, 1}, { 91, 37, 1}, { 68, 58, 1},
    { 37, 28, 1}, { 58, 4, 1}, { 79, 14, 1}, { 45, 50, 1}, { 57, 39, 1}, { 73, 22, 1}, { 92, 36, 1}, { 69, 58, 1},
    { 37, 29, 1}, { 57, 5, 1}, { 77, 12, 1}, { 45, 49, 1}, { 57, 41, 1}, { 73, 23, 1}, { 92, 34, 1}, { 70, 59, 1},
    { 37, 30, 1}, { 56, 6, 1}, { 76, 10, 1}, { 45, 48, 1}, { 58, 42, 1}, { 72, 23, 1}, { 92, 33, 1}, { 71, 59, 1},
    { 37, 31, 1}, { 55, 7, 1}, { 74, 8, 1}, { 45, 47, 1}, { 58, 43, 1}, { 72, 24, 1}, { 92, 32, 1}, { 73, 59, 1},
    { 37, 33, 1}, { 54, 8, 1}, { 73, 6, 1}, { 45, 46, 1}, { 59, 44, 1}, { 72, 25, 1}, { 92, 30, 1}, { 74, 59, 1},
    { 37, 34, 1}, { 54, 10, 1}, { 71, 4, 1}, { 45, 45, 1}, { 60, 46, 1}, { 72, 25, 1}, { 92, 29, 1}, { 76, 59, 1},
    { 38, 35, 1}, { 53, 11, 1}, { 69, 3, 1}, { 45, 44, 1}, { 60, 47, 1}, { 72, 26, 1}, { 92, 27, 1}, { 77, 59, 1},
    { 38, 37, 1}, { 53, 12, 1}, { 68, 2, 1}, { 45, 42, 1}, { 61, 48, 1}, { 72, 27, 1}, { 92, 26, 1}, { 79, 58, 1},
    { 38, 38, 1}, { 52, 14, 1}, { 66, 2, 1}, { 46, 40, 1}, { 62, 49, 1}, { 71, 28, 1}, { 92, 25, 1}, { 80, 57, 1},
    { 38, 39, 1}, { 52, 15, 1}, { 65, 1, 1}, { 46, 39, 1}, { 63, 51, 1}, { 71, 28, 1}, { 91, 23, 1}, { 81, 56, 1},
    { 38, 40, 1}, { 51, 16, 1}, { 64, 1, 1}, { 46, 37, 1}, { 63, 52, 1}, { 71, 29, 1}, { 91, 22, 1}, { 83, 55, 1},
    { 38, 41, 1}, { 51, 18, 1}, { 62, 1, 1}, { 46, 35, 1}, { 64, 53, 1}, { 71, 30, 1}, { 90, 21, 1}, { 84, 54, 1},
    { 39, 43, 1}, { 51, 19, 1}, { 61, 1, 1}, { 45, 33, 1}, { 65, 54, 1}, { 71, 31, 1}, { 89, 20, 1}, { 85, 52, 1},
    { 39, 44, 1}, { 50, 21, 1}, { 60, 1, 1}, { 45, 31, 1}, { 66, 55, 1}, { 71, 32, 1}, { 88, 19, 1}, { 87, 50, 1},
    { 39, 45, 1}, { 50, 22, 1}, { 59, 2, 1}, { 45, 29, 1}, { 67, 56, 1}, { 71, 33, 1}, { 88, 18, 1}, { 88, 48, 1},
    { 39, 46, 1}, { 50, 24, 1}, { 58, 2, 1}, { 45, 27, 1}, { 68, 56, 1}, { 72, 34, 1}, { 87, 18, 1}, { 89, 45, 1},
    { 39, 47, 1}, { 50, 26, 1}, { 57, 3, 1}, { 45, 25, 1}, { 69, 57, 1}, { 72, 34, 1}, { 86, 17, 1}, { 89, 43, 1},
    { 40, 48, 1}, { 50, 27, 1}, { 56, 4, 1}, { 45, 23, 1}, { 70, 58, 1}, { 72, 35, 1}, { 85, 17, 1}, { 90, 40, 1},
    { 40, 49, 1}, { 50, 29, 1}, { 56, 5, 1}, { 45, 21, 1}, { 72, 58, 1}, { 72, 36, 1}, { 84, 16, 1}, { 90, 37, 1},
    { 40, 50, 1}, { 50, 30, 1}, { 55, 6, 1}, { 44, 19, 1}, { 73, 59, 1}, { 72, 37, 1}, { 83, 16, 1}, { 91, 34, 1},
    { 40, 51, 1}, { 50, 32, 1}, { 54, 7, 1}, { 44, 18, 1}, { 74, 59, 1}, { 73, 38, 1}, { 82, 16, 1}, { 91, 31, 1},
    { 41, 51, 1}, { 50, 33, 1}, { 54, 9, 1}, { 44, 16, 1}, { 75, 59, 1}, { 73, 39, 1}, { 82, 16, 1}, { 91, 28, 1},
    { 41, 52, 1}, { 50, 35, 1}, { 53, 10, 1}, { 44, 15, 1}, { 77, 59, 1}, { 73, 40, 1}, { 81, 16, 1}, { 90, 25, 1},
    { 41, 52, 1}, { 50, 37, 1}, { 53, 11, 1}, { 43, 14, 1}, { 78, 58, 1}, { 74, 41, 1}, { 80, 16, 1}, { 90, 22, 1},
    { 41, 53, 1}, { 50, 38, 1}, { 52, 13, 1}, { 43, 12, 1}, { 80, 58, 1}, { 74, 41, 1}, { 79, 17, 1}, { 89, 19, 1},
    { 41, 53, 1}, { 50, 40, 1}, { 52, 14, 1}, { 43, 12, 1}, { 81, 57, 1}, { 75, 42, 1}, { 78, 17, 1}, { 88, 17, 1},
    { 42, 53, 1}, { 50, 41, 1}, { 51, 16, 1}, { 43, 11, 1}, { 82, 56, 1}, { 75, 43, 1}, { 78, 18, 1}, { 87, 14, 1},
    { 42, 53, 1}, { 50, 43, 1}, { 51, 17, 1}, { 42, 10, 1}, { 84, 54, 1}, { 76, 44, 1}, { 77, 18, 1}, { 86, 12, 1},
    { 42, 53, 1}, { 51, 44, 1}, { 51, 19, 1}, { 42, 10, 1}, { 85, 53, 1}, { 76, 44, 1}, { 76, 19, 1}, { 85, 10, 1},
    { 42, 53, 1}, { 51, 46, 1}, { 50, 20, 1}, { 42, 10, 1}, { 86, 51, 1}, { 77, 45, 1}, { 76, 19, 1}, { 84, 9, 1},
    { 43, 52, 1}, { 51, 47, 1}, { 50, 22, 1}, { 42, 10, 1}, { 87, 49, 1}, { 78, 45, 1}, { 75, 20, 1}, { 82, 7, 1},
    { 43, 51, 1}, { 52, 49, 1}, { 50, 23, 1}, { 41, 10, 1}, { 88, 46, 1}, { 78, 46, 1}, { 75, 21, 1}, { 81, 6, 1},
    { 43, 51, 1}, { 52, 50, 1}, { 50, 25, 1}, { 41, 10, 1}, { 89, 44, 1}, { 79, 46, 1}, { 74, 22, 1}, { 80, 5, 1},
    { 43, 49, 1}, { 53, 52, 1}, { 50, 26, 1}, { 41, 11, 1}, { 90, 41, 1}, { 80, 47, 1}, { 74, 22, 1}, { 78, 5, 1},
    { 44, 48, 1}, { 53, 53, 1}, { 50, 28, 1}, { 41, 11, 1}, { 90, 38, 1}, { 81, 47, 1}, { 73, 23, 1}, { 77, 4, 1},
    { 44, 47, 1}, { 54, 54, 1}, { 50, 30, 1}, { 41, 12, 1}, { 91, 35, 1}, { 82, 47, 1}, { 73, 24, 1}, { 75, 4, 1},
    { 44, 45, 1}, { 54, 56, 1}, { 50, 31, 1}, { 40, 12, 1}, { 91, 32, 1}, { 82, 47, 1}, { 73, 25, 1}, { 74, 4, 1},
    { 44, 44, 1}, { 55, 57, 1}, { 50, 33, 1}, { 40, 13, 1}, { 91, 29, 1}, { 83, 47, 1}, { 72, 26, 1}, { 73, 4, 1},
    { 45, 42, 1}, { 56, 58, 1}, { 50, 34, 1}, { 40, 14, 1}, { 90, 26, 1}, { 84, 47, 1}, { 72, 27, 1}, { 72, 5, 1},
    { 45, 40, 1}, { 56, 59, 1}, { 50, 36, 1}, { 40, 15, 1}, { 90, 23, 1}, { 85, 46, 1}, { 72, 28, 1}, { 70, 5, 1},
    { 45, 38, 1}, { 57, 60, 1}, { 50, 37, 1}, { 39, 16, 1}, { 89, 20, 1}, { 86, 46, 1}, { 72, 29, 1}, { 69, 6, 1},
    { 45, 36, 1}, { 58, 61, 1}, { 50, 39, 1}, { 39, 17, 1}, { 89, 18, 1}, { 87, 45, 1}, { 72, 29, 1}, { 68, 7, 1},
    { 45, 34, 1}, { 59, 61, 1}, { 50, 41, 1}, { 39, 18, 1}, { 88, 15, 1}, { 88, 45, 1}, { 71, 30, 1}, { 67, 7, 1},
    { 45, 32, 1}, { 60, 62, 1}, { 50, 42, 1}, { 39, 19, 1}, { 87, 13, 1}, { 88, 44, 1}, { 71, 31, 1}, { 66, 8, 1},
    { 45, 30, 1}, { 61, 62, 1}, { 51, 44, 1}, { 39, 20, 1}, { 85, 11, 1}, { 89, 43, 1}, { 71, 32, 1}, { 65, 9, 1},
    { 46, 28, 1}, { 62, 62, 1}, { 51, 45, 1}, { 38, 22, 1}, { 84, 9, 1}, { 90, 42, 1}, { 71, 33, 1}, { 64, 10, 1},
    { 46, 26, 1}, { 64, 62, 1}, { 51, 47, 1}, { 38, 23, 1}, { 83, 8, 1}, { 91, 41, 1}, { 71, 34, 1}, { 63, 11, 1},
    { 46, 24, 1}, { 65, 62, 1}, { 52, 48, 1}, { 38, 24, 1}, { 81, 7, 1}, { 91, 40, 1}, { 71, 35, 1}, { 63, 12, 1},
    { 46, 23, 1}, { 66, 61, 1}, { 52, 49, 1}, { 38, 25, 1}, { 80, 6, 1}, { 92, 38, 1}, { 71, 35, 1}, { 62, 14, 1},
    { 45, 21, 1}, { 68, 61, 1}, { 53, 51, 1}, { 38, 26, 1}, { 79, 5, 1}, { 92, 37, 1}, { 72, 36, 1}, { 61, 15, 1},
    { 45, 19, 1}, { 69, 60, 1}, { 53, 52, 1}, { 38, 28, 1}, { 77, 4, 1}, { 92, 36, 1}, { 72, 37, 1}, { 60, 16, 1},
    { 45, 18, 1}, { 71, 59, 1}, { 54, 53, 1}, { 37, 29, 1}, { 76, 4, 1}, { 92, 34, 1}, { 72, 38, 1}, { 60, 17, 1},
    { 45, 17, 1}, { 73, 57, 1}, { 54, 55, 1}, { 37, 30, 1}, { 74, 4, 1}, { 92, 33, 1}, { 72, 38, 1}, { 59, 19, 1},
    { 45, 16, 1}, { 74, 55, 1}, { 55, 56, 1}, { 37, 32, 1}, { 73, 4, 1}, { 92, 31, 1}, { 72, 39, 1}, { 58, 20, 1},
    { 45, 15, 1}, { 76, 53, 1}, { 56, 57, 1}, { 37, 33, 1}, { 71, 4, 1}, { 92, 30, 1}, { 72, 40, 1}, { 58, 21, 1},
    { 45, 14, 1}, { 77, 51, 1}, { 57, 58, 1}, { 37, 34, 1}, { 70, 4, 1}, { 92, 29, 1}, { 73, 40, 1}, { 57, 22, 1},
    { 45, 13, 1}, { 79, 49, 1}, { 58, 59, 1}, { 37, 35, 1}, { 69, 5, 1}, { 92, 27, 1}, { 73, 41, 1}, { 57, 24, 1},
    { 44, 12, 1}, { 80, 46, 1}, { 59, 60, 1}, { 37, 37, 1}, { 68, 5, 1}, { 91, 26, 1}, { 73, 41, 1}, { 56, 25, 1},
    { 44, 12, 1}, { 81, 43, 1}, { 60, 60, 1}, { 37, 38, 1}, { 66, 6, 1}, { 91, 25, 1}, { 73, 42, 1}, { 56, 26, 1},
    { 44, 11, 1}, { 82, 41, 1}, { 62, 61, 1}, { 37, 39, 1}, { 65, 6, 1}, { 90, 24, 1}, { 74, 42, 1}, { 55, 27, 1},
    { 44, 11, 1}, { 83, 38, 1}, { 63, 61, 1}, { 37, 40, 1}, { 64, 7, 1}, { 89, 23, 1}, { 74, 43, 1}, { 55, 29, 1},
    { 44, 11, 1}, { 84, 35, 1}, { 65, 62, 1}, { 37, 42, 1}, { 63, 8, 1}, { 88, 22, 1}, { 74, 43, 1}, { 54, 30, 1},
    { 44, 10, 1}, { 85, 32, 1}, { 66, 62, 1}, { 37, 43, 1}, { 62, 9, 1}, { 88, 21, 1}, { 75, 43, 1}, { 54, 31, 1},
    { 43, 10, 1}, { 86, 29, 1}, { 68, 62, 1}, { 37, 44, 1}, { 60, 9, 1}, { 87, 21, 1}, { 75, 43, 1}, { 53, 33, 1},
    { 43, 10, 1}, { 86, 27, 1}, { 69, 62, 1}, { 37, 45, 1}, { 59, 10, 1}, { 86, 20, 1}, { 75, 44, 1}, { 53, 34, 1},
    { 43, 10, 1}, { 86, 24, 1}, { 71, 61, 1}, { 37, 46, 1}, { 58, 11, 1}, { 85, 19, 1}, { 75, 44, 1}, { 53, 35, 1},
    { 43, 10, 1}, { 87, 22, 1}, { 73, 61, 1}, { 38, 47, 1}, { 57, 12, 1}, { 84, 19, 1}, { 75, 44, 1}, { 52, 36, 1},
    { 43, 10, 1}, { 87, 19, 1}, { 75, 60, 1}, { 38, 48, 1}, { 56, 13, 1}, { 83, 19, 1}, { 76, 44, 1}, { 52, 37, 1},
    { 43, 10, 1}, { 87, 17, 1}, { 76, 59, 1}, { 39, 49, 1}, { 55, 14, 1}, { 82, 19, 1}, { 76, 44, 1}, { 52, 39, 1},
    { 42, 10, 1}, { 86, 16, 1}, { 78, 58, 1}, { 39, 50, 1}, { 54, 15, 1}, { 81, 18, 1}, { 76, 44, 1}, { 52, 40, 1},
    { 42, 10, 1}, { 86, 14, 1}, { 80, 57, 1}, { 40, 51, 1}, { 53, 16, 1}, { 80, 18, 1}, { 76, 44, 1}, { 51, 41, 1},
    { 42, 10, 1}, { 86, 13, 1}, { 82, 56, 1}, { 40, 52, 1}, { 53, 17, 1}, { 78, 18, 1}, { 76, 44, 1}, { 51, 42, 1},
    { 42, 10, 1}, { 85, 11, 1}, { 83, 54, 1}, { 41, 52, 1}, { 52, 18, 1}, { 77, 19, 1}, { 76, 44, 1}, { 51, 43, 1},
    { 42, 10, 1}, { 85, 10, 1}, { 85, 53, 1}, { 42, 53, 1}, { 51, 19, 1}, { 76, 19, 1}, { 76, 44, 1}, { 51, 44, 1},
    { 42, 10, 1}, { 84, 9, 1}, { 86, 51, 1}, { 43, 53, 1}, { 50, 20, 1}, { 75, 19, 1}, { 76, 44, 1}, { 51, 45, 1},
    { 42, 10, 1}, { 84, 9, 1}, { 88, 50, 1}, { 44, 54, 1}, { 49, 20, 1}, { 74, 19, 1}, { 76, 44, 1}, { 50, 46, 1},
    { 42, 10, 1}, { 83, 8, 1}, { 89, 48, 1}, { 46, 54, 1}, { 48, 21, 1}, { 73, 19, 1}, { 76, 44, 1}, { 50, 47, 1},
    { 42, 10, 1}, { 83, 7, 1}, { 90, 47, 1}, { 47, 54, 1}, { 47, 22, 1}, { 72, 20, 1}, { 76, 44, 1}, { 50, 48, 1},
    { 43, 10, 1}, { 82, 7, 1}, { 91, 45, 1}, { 49, 54, 1}, { 46, 23, 1}, { 71, 20, 1}, { 76, 44, 1}, { 50, 49, 1},
    { 43, 10, 1}, { 81, 7, 1}, { 92, 44, 1}, { 50, 54, 1}, { 46, 24, 1}, { 70, 20, 1}, { 76, 44, 1}, { 50, 50, 1},
    { 43, 10, 1}, { 81, 7, 1}, { 92, 42, 1}, { 52, 54, 1}, { 45, 24, 1}, { 69, 21, 1}, { 75, 44, 1}, { 50, 51, 1},
    { 44, 9, 1}, { 80, 7, 1}, { 93, 41, 1}, { 54, 53, 1}, { 44, 25, 1}, { 68, 21, 1}, { 75, 44, 1}, { 50, 52, 1},
    { 44, 9, 1}, { 80, 7, 1}, { 93, 40, 1}, { 56, 53, 1}, { 43, 26, 1}, { 67, 22, 1}, { 75, 44, 1}, { 50, 53, 1},
    { 45, 9, 1}, { 79, 7, 1}, { 93, 39, 1}, { 58, 52, 1}, { 42, 26, 1}, { 66, 22, 1}, { 74, 44, 1}, { 50, 53, 1},
    { 45, 8, 1}, { 78, 7, 1}, { 93, 38, 1}, { 60, 52, 1}, { 42, 27, 1}, { 65, 22, 1}, { 74, 45, 1}, { 50, 54, 1},
    { 46, 8, 1}, { 78, 7, 1}, { 93, 37, 1}, { 62, 51, 1}, { 41, 27, 1}, { 64, 23, 1}, { 73, 45, 1}, { 50, 55, 1},
    { 46, 8, 1}, { 77, 7, 1}, { 93, 37, 1}, { 64, 50, 1}, { 40, 28, 1}, { 63, 23, 1}, { 73, 45, 1}, { 50, 55, 1},
    { 47, 7, 1}, { 77, 7, 1}, { 93, 36, 1}, { 66, 50, 1}, { 39, 28, 1}, { 62, 24, 1}, { 73, 45, 1}, { 50, 56, 1},
    { 48, 7, 1}, { 76, 8, 1}, { 93, 35, 1}, { 68, 49, 1}, { 39, 28, 1}, { 61, 24, 1}, { 72, 45, 1}, { 50, 56, 1},
    { 49, 6, 1}, { 76, 8, 1}, { 93, 35, 1}, { 70, 48, 1}, { 38, 28, 1}, { 61, 24, 1}, { 71, 45, 1}, { 50, 57, 1},
    { 50, 6, 1}, { 75, 8, 1}, { 92, 35, 1}, { 72, 48, 1}, { 37, 29, 1}, { 60, 25, 1}, { 71, 45, 1}, { 50, 57, 1},
    { 51, 6, 1}, { 75, 9, 1}, { 92, 35, 1}, { 74, 47, 1}, { 37, 29, 1}, { 59, 25, 1}, { 70, 46, 1}, { 50, 58, 1},
    { 52, 5, 1}, { 75, 9, 1}, { 91, 34, 1}, { 76, 46, 1}, { 36, 29, 1}, { 58, 25, 1}, { 70, 46, 1}, { 50, 58, 1},
    { 54, 5, 1}, { 74, 9, 1}, { 91, 34, 1}, { 78, 46, 1}, { 36, 29, 1}, { 57, 25, 1}, { 69, 46, 1}, { 50, 58, 1},
    { 55, 4, 1}, { 74, 10, 1}, { 90, 34, 1}, { 79, 45, 1}, { 35, 28, 1}, { 56, 25, 1}, { 68, 46, 1}, { 51, 59, 1},
    { 56, 4, 1}, { 74, 10, 1}, { 90, 35, 1}, { 81, 45, 1}, { 35, 28, 1}, { 56, 26, 1}, { 67, 46, 1}, { 51, 59, 1},
    { 57, 4, 1}, { 73, 10, 1}, { 89, 35, 1}, { 82, 44, 1}, { 35, 28, 1}, { 55, 26, 1}, { 67, 46, 1}, { 51, 59, 1},
    { 59, 3, 1}, { 73, 11, 1}, { 89, 35, 1}, { 83, 44, 1}, { 34, 27, 1}, { 54, 26, 1}, { 66, 47, 1}, { 51, 59, 1},
    { 60, 3, 1}, { 73, 11, 1}, { 88, 35, 1}, { 85, 44, 1}, { 34, 27, 1}, { 54, 26, 1}, { 65, 47, 1}, { 51, 59, 1},
    { 62, 3, 1}, { 73, 11, 1}, { 87, 36, 1}, { 86, 43, 1}, { 34, 26, 1}, { 53, 26, 1}, { 64, 47, 1}, { 50, 59, 1},
    { 63, 3, 1}, { 73, 12, 1}, { 87, 36, 1}, { 86, 43, 1}, { 34, 26, 1}, { 52, 26, 1}, { 64, 47, 1}, { 50, 59, 1},
    { 65, 3, 1}, { 73, 12, 1}, { 86, 36, 1}, { 87, 43, 1}, { 34, 25, 1}, { 52, 26, 1}, { 63, 47, 1}, { 50, 59, 1},
    { 66, 3, 1}, { 73, 13, 1}, { 85, 37, 1}, { 88, 44, 1}, { 34, 24, 1}, { 51, 25, 1}, { 62, 47, 1}, { 50, 59, 1},
    { 68, 3, 1}, { 73, 13, 1}, { 85, 37, 1}, { 88, 44, 1}, { 34, 24, 1}, { 51, 25, 1}, { 61, 47, 1}, { 50, 59, 1},
    { 69, 3, 1}, { 73, 13, 1}, { 84, 38, 1}, { 89, 44, 1}, { 34, 23, 1}, { 50, 25, 1}, { 60, 47, 1}, { 50, 59, 1},
    { 70, 3, 1}, { 73, 14, 1}, { 84, 38, 1}, { 89, 44, 1}, { 34, 22, 1}, { 50, 25, 1}, { 60, 47, 1}, { 49, 59, 1},
    { 72, 3, 1}, { 73, 14, 1}, { 83, 39, 1}, { 89, 45, 1}, { 35, 21, 1}, { 50, 24, 1}, { 59, 47, 1}, { 49, 59, 1},
    { 73, 4, 1}, { 73, 14, 1}, { 82, 39, 1}, { 89, 45, 1}, { 35, 20, 1}, { 49, 24, 1}, { 58, 47, 1}, { 49, 58, 1},
    { 75, 4, 1}, { 73, 15, 1}, { 82, 39, 1}, { 89, 46, 1}, { 35, 19, 1}, { 49, 23, 1}, { 57, 47, 1}, { 48, 58, 1},
    { 76, 4, 1}, { 73, 15, 1}, { 81, 40, 1}, { 89, 46, 1}, { 36, 18, 1}, { 49, 23, 1}, { 56, 47, 1}, { 48, 58, 1},
    { 77, 5, 1}, { 74, 15, 1}, { 80, 40, 1}, { 89, 47, 1}, { 37, 17, 1}, { 49, 23, 1}, { 56, 47, 1}, { 47, 57, 1},
    { 78, 5, 1}, { 74, 16, 1}, { 80, 41, 1}, { 88, 48, 1}, { 37, 16, 1}, { 49, 22, 1}, { 55, 47, 1}, { 47, 57, 1},
    { 79, 6, 1}, { 74, 16, 1}, { 79, 41, 1}, { 88, 48, 1}, { 38, 15, 1}, { 49, 22, 1}, { 54, 46, 1}, { 46, 56, 1},
    { 80, 7, 1}, { 74, 17, 1}, { 79, 42, 1}, { 88, 49, 1}, { 38, 14, 1}, { 49, 21, 1}, { 54, 46, 1}, { 46, 56, 1},
    { 81, 7, 1}, { 75, 17, 1}, { 78, 42, 1}, { 87, 50, 1}, { 39, 13, 1}, { 49, 21, 1}, { 53, 46, 1}, { 45, 55, 1},
    { 82, 8, 1}, { 75, 17, 1}, { 78, 43, 1}, { 87, 51, 1}, { 40, 13, 1}, { 50, 20, 1}, { 52, 46, 1}, { 44, 55, 1},
    { 83, 9, 1}, { 75, 18, 1}, { 77, 43, 1}, { 86, 51, 1}, { 41, 12, 1}, { 50, 20, 1}, { 52, 45, 1}, { 44, 54, 1},
    { 84, 9, 1}, { 76, 18, 1}, { 77, 44, 1}, { 86, 52, 1}, { 41, 11, 1}, { 50, 19, 1}, { 51, 45, 1}, { 43, 54, 1},
    { 85, 10, 1}, { 76, 19, 1}, { 76, 44, 1}, { 85, 53, 1}, { 42, 10, 1}, { 51, 19, 1}, { 51, 44, 1}, { 42, 53, 1},
    { 86, 11, 1}, { 77, 19, 1}, { 76, 45, 1}, { 84, 54, 1}, { 43, 9, 1}, { 51, 18, 1}, { 50, 44, 1}, { 41, 52, 1},
    { 86, 12, 1}, { 77, 20, 1}, { 75, 45, 1}, { 83, 54, 1}, { 44, 9, 1}, { 52, 18, 1}, { 50, 43, 1}, { 41, 51, 1},
    { 87, 12, 1}, { 78, 20, 1}, { 75, 46, 1}, { 82, 55, 1}, { 44, 8, 1}, { 52, 17, 1}, { 50, 43, 1}, { 40, 50, 1},
    { 87, 13, 1}, { 78, 21, 1}, { 75, 46, 1}, { 81, 56, 1}, { 45, 8, 1}, { 53, 17, 1}, { 49, 42, 1}, { 39, 50, 1},
    { 88, 14, 1}, { 79, 21, 1}, { 74, 46, 1}, { 80, 56, 1}, { 46, 7, 1}, { 54, 17, 1}, { 49, 42, 1}, { 38, 49, 1},
    { 88, 15, 1}, { 79, 22, 1}, { 74, 47, 1}, { 79, 57, 1}, { 46, 7, 1}, { 54, 17, 1}, { 49, 41, 1}, { 38, 48, 1},
    { 88, 15, 1}, { 80, 22, 1}, { 74, 47, 1}, { 78, 58, 1}, { 47, 6, 1}, { 55, 16, 1}, { 49, 41, 1}, { 37, 47, 1},
    { 89, 16, 1}, { 80, 23, 1}, { 74, 48, 1}, { 77, 58, 1}, { 47, 6, 1}, { 56, 16, 1}, { 49, 40, 1}, { 37, 46, 1},
    { 89, 17, 1}, { 81, 23, 1}, { 73, 48, 1}, { 76, 59, 1}, { 48, 5, 1}, { 56, 16, 1}, { 49, 40, 1}, { 36, 45, 1},
    { 89, 17, 1}, { 82, 24, 1}, { 73, 48, 1}, { 75, 59, 1}, { 48, 5, 1}, { 57, 16, 1}, { 49, 40, 1}, { 35, 44, 1},
    { 89, 18, 1}, { 82, 24, 1}, { 73, 49, 1}, { 73, 59, 1}, { 49, 5, 1}, { 58, 16, 1}, { 49, 39, 1}, { 35, 43, 1},
    { 89, 18, 1}, { 83, 24, 1}, { 73, 49, 1}, { 72, 60, 1}, { 49, 4, 1}, { 59, 16, 1}, { 50, 39, 1}, { 35, 42, 1},
    { 89, 19, 1}, { 84, 25, 1}, { 73, 49, 1}, { 70, 60, 1}, { 49, 4, 1}, { 60, 16, 1}, { 50, 38, 1}, { 34, 41, 1},
    { 89, 19, 1}, { 84, 25, 1}, { 73, 50, 1}, { 69, 60, 1}, { 50, 4, 1}, { 60, 16, 1}, { 50, 38, 1}, { 34, 40, 1},
    { 88, 19, 1}, { 85, 26, 1}, { 73, 50, 1}, { 68, 60, 1}, { 50, 4, 1}, { 61, 16, 1}, { 51, 38, 1}, { 34, 39, 1},
    { 88, 19, 1}, { 85, 26, 1}, { 73, 50, 1}, { 66, 60, 1}, { 50, 4, 1}, { 62, 16, 1}, { 51, 38, 1}, { 34, 39, 1},
    { 87, 20, 1}, { 86, 27, 1}, { 73, 51, 1}, { 65, 60, 1}, { 50, 4, 1}, { 63, 16, 1}, { 52, 37, 1}, { 34, 38, 1},
    { 86, 20, 1}, { 87, 27, 1}, { 73, 51, 1}, { 63, 60, 1}, { 50, 4, 1}, { 64, 16, 1}, { 52, 37, 1}, { 34, 37, 1},
    { 86, 20, 1}, { 87, 27, 1}, { 73, 52, 1}, { 62, 60, 1}, { 50, 4, 1}, { 64, 16, 1}, { 53, 37, 1}, { 34, 37, 1},
    { 85, 19, 1}, { 88, 28, 1}, { 73, 52, 1}, { 60, 60, 1}, { 51, 4, 1}, { 65, 16, 1}, { 54, 37, 1}, { 34, 36, 1},
    { 83, 19, 1}, { 89, 28, 1}, { 73, 52, 1}, { 59, 60, 1}, { 51, 4, 1}, { 66, 16, 1}, { 54, 37, 1}, { 34, 36, 1},
    { 82, 19, 1}, { 89, 28, 1}, { 73, 53, 1}, { 57, 59, 1}, { 51, 4, 1}, { 67, 17, 1}, { 55, 37, 1}, { 35, 35, 1},
    { 81, 18, 1}, { 90, 28, 1}, { 74, 53, 1}, { 56, 59, 1}, { 51, 4, 1}, { 67, 17, 1}, { 56, 37, 1}, { 35, 35, 1},
    { 79, 18, 1}, { 90, 29, 1}, { 74, 53, 1}, { 55, 59, 1}, { 51, 4, 1}, { 68, 17, 1}, { 56, 38, 1}, { 35, 35, 1},
    { 78, 17, 1}, { 91, 29, 1}, { 74, 54, 1}, { 54, 58, 1}, { 50, 5, 1}, { 69, 17, 1}, { 57, 38, 1}, { 36, 34, 1},
    { 76, 17, 1}, { 91, 29, 1}, { 75, 54, 1}, { 52, 58, 1}, { 50, 5, 1}, { 70, 17, 1}, { 58, 38, 1}, { 36, 34, 1},
    { 74, 16, 1}, { 92, 28, 1}, { 75, 54, 1}, { 51, 57, 1}, { 50, 5, 1}, { 70, 17, 1}, { 59, 38, 1}, { 37, 34, 1},
    { 72, 15, 1}, { 92, 28, 1}, { 75, 55, 1}, { 50, 57, 1}, { 50, 6, 1}, { 71, 18, 1}, { 60, 38, 1}, { 37, 34, 1},
    { 70, 15, 1}, { 93, 28, 1}, { 76, 55, 1}, { 49, 57, 1}, { 50, 6, 1}, { 71, 18, 1}, { 61, 39, 1}, { 38, 35, 1},
    { 68, 14, 1}, { 93, 28, 1}, { 76, 55, 1}, { 48, 56, 1}, { 50, 7, 1}, { 72, 18, 1}, { 61, 39, 1}, { 39, 35, 1},
    { 66, 13, 1}, { 93, 27, 1}, { 77, 56, 1}, { 47, 56, 1}, { 50, 7, 1}, { 73, 18, 1}, { 62, 39, 1}, { 39, 35, 1},
    { 64, 13, 1}, { 93, 26, 1}, { 77, 56, 1}, { 46, 55, 1}, { 50, 8, 1}, { 73, 18, 1}, { 63, 40, 1}, { 40, 35, 1},
    { 62, 12, 1}, { 93, 26, 1}, { 78, 56, 1}, { 46, 55, 1}, { 50, 8, 1}, { 73, 18, 1}, { 64, 40, 1}, { 41, 36, 1},
    { 60, 11, 1}, { 93, 25, 1}, { 78, 56, 1}, { 45, 55, 1}, { 50, 9, 1}, { 74, 18, 1}, { 65, 41, 1}, { 42, 36, 1},
    { 58, 11, 1}, { 93, 24, 1}, { 79, 56, 1}, { 45, 54, 1}, { 50, 10, 1}, { 74, 19, 1}, { 66, 41, 1}, { 42, 37, 1},
    { 56, 10, 1}, { 93, 23, 1}, { 80, 56, 1}, { 44, 54, 1}, { 50, 10, 1}, { 75, 19, 1}, { 67, 41, 1}, { 43, 37, 1},
    { 54, 10, 1}, { 93, 22, 1}, { 80, 56, 1}, { 44, 54, 1}, { 50, 11, 1}, { 75, 19, 1}, { 68, 42, 1}, { 44, 38, 1},
    { 52, 9, 1}, { 92, 21, 1}, { 81, 56, 1}, { 43, 53, 1}, { 50, 12, 1}, { 75, 19, 1}, { 69, 42, 1}, { 45, 39, 1},
    { 50, 9, 1}, { 92, 19, 1}, { 81, 56, 1}, { 43, 53, 1}, { 50, 13, 1}, { 76, 19, 1}, { 70, 43, 1}, { 46, 39, 1},
    { 49, 9, 1}, { 91, 18, 1}, { 82, 56, 1}, { 43, 53, 1}, { 50, 14, 1}, { 76, 19, 1}, { 71, 43, 1}, { 46, 40, 1},
    { 47, 9, 1}, { 90, 16, 1}, { 83, 56, 1}, { 42, 53, 1}, { 50, 15, 1}, { 76, 19, 1}, { 72, 43, 1}, { 47, 41, 1},
    { 46, 9, 1}, { 89, 15, 1}, { 83, 55, 1}, { 42, 53, 1}, { 50, 16, 1}, { 76, 19, 1}, { 73, 44, 1}, { 48, 42, 1},
    { 44, 9, 1}, { 88, 13, 1}, { 84, 54, 1}, { 42, 53, 1}, { 50, 17, 1}, { 76, 19, 1}, { 74, 44, 1}, { 49, 43, 1},
    { 43, 10, 1}, { 86, 12, 1}, { 84, 54, 1}, { 42, 53, 1}, { 51, 18, 1}, { 76, 19, 1}, { 75, 44, 1}, { 50, 43, 1}
};



uint8_t  iAng1 = 0;
int Cnt1, Cnt1v;
uint8_t vert1[8][3];
uint8_t x11 = 0, x21 = 0, y11 = 0, y21 = 0; //,statu=0;

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127
byte __OLED_GRAM[512];






static bool down(void);
static bool up(void);
static display_t draw(void);


static  void __SysTick(void);
static  void _OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);

static  void _OLED_DrawLine(u16 x11, u16 y11, u16 x21, u16 y21);



#define TIME_POS_X	1
#define TIME_POS_Y	1
#define TICKER_GAP	14


typedef struct
{
    byte x;
    byte y;
    const byte* bitmap;
    byte w;
    byte h;
    byte offsetY;
    byte val;
    byte maxVal;
    bool moving;
} tickerData_t;

static void drawDate(void);
#if COMPILE_ANIMATIONS
    static bool animateIcon(bool, byte*);
#endif
static display_t ticker(void);
static void drawTickerNum(tickerData_t*);





void watchfaceOpen()
{

    appConfig.showFPS = 0;   //禁用FPS
    display_setDrawFunc(draw);
    buttons_setFuncs(up, menu_select, down);
    animation_start(NULL, ANIM_MOVE_ON);

}

static bool down()
{
    // Set watchface
    display_set(watchface_normal);
    display_load();

    return true;
}

static bool up()
{
    // Set watchface
    display_set(watchface_normal);
    display_load();

    return true;
}





static display_t draw()
{

    // Infinite loop

    __SysTick();

    // Get vertices for the current angle
    //获取当前角度的顶点
    for(Cnt1v = 0; Cnt1v < nvert1; ++Cnt1v)
    {
        vert1[Cnt1v][0] = vertices[iAng1 * nvert1 + Cnt1v][0];
        vert1[Cnt1v][1] = vertices[iAng1 * nvert1 + Cnt1v][1];
        vert1[Cnt1v][2] = vertices[iAng1 * nvert1 + Cnt1v][2];
    }

    // Draw wireframe for each face of the cube
    //为立方体的每个面绘制线框
    //一个面有四条边，画六个面就是 4x6 =24次就可以完整显示
    for(Cnt1 = 0; Cnt1 < nfaces1; ++Cnt1)
    {

        x11 = vert1[faces1[Cnt1][0]][0] - 34;
        y11 = vert1[faces1[Cnt1][0]][1] - 1;
        x21 = vert1[faces1[Cnt1][1]][0] - 34;
        y21 = vert1[faces1[Cnt1][1]][1] - 1;
        _OLED_DrawLine(x11, y11, x21, y21);

        x11 = vert1[faces1[Cnt1][1]][0] - 34;
        y11 = vert1[faces1[Cnt1][1]][1] - 1;
        x21 = vert1[faces1[Cnt1][2]][0] - 34;
        y21 = vert1[faces1[Cnt1][2]][1] - 1;
        _OLED_DrawLine(x11, y11, x21, y21);

        x11 = vert1[faces1[Cnt1][2]][0] - 34;
        y11 = vert1[faces1[Cnt1][2]][1] - 1;
        x21 = vert1[faces1[Cnt1][3]][0] - 34;
        y21 = vert1[faces1[Cnt1][3]][1] - 1;
        _OLED_DrawLine(x11, y11, x21, y21);


        x11 = vert1[faces1[Cnt1][3]][0] - 34;
        y11 = vert1[faces1[Cnt1][3]][1] - 1;
        x21 = vert1[faces1[Cnt1][0]][0] - 34;
        y21 = vert1[faces1[Cnt1][0]][1] - 1;
        _OLED_DrawLine(x11, y11, x21, y21);

    }

    // Draw platform

    draw_bitmap(0, 0, (const byte *)__OLED_GRAM, 64, 64, NOINVERT, 0);
    memset(&__OLED_GRAM, 0x00, FRAME_BUFFER_SIZE / 2);


    #if COMPILE_ANIMATIONS
    static byte usbImagePos = FRAME_HEIGHT;
    static byte chargeImagePos = FRAME_HEIGHT;
    #endif


    drawDate();
    ticker();
    
    // Draw battery icon
//    uint battLevel =    battery_voltage();
    uint battLevel =    2000;
    const byte* battIcon;

    if(battLevel < 3100)
        battIcon = battIconEmpty;
    else if(battLevel < 3200)
        battIcon = battIconLow;
    else if(battLevel < 3300)
        battIcon = battIconHigh;
    else
        battIcon = battIconFull;

    draw_bitmap(60, 2, battIcon, 16, 8, NOINVERT, 0);


    byte x = 0;

    #if COMPILE_ANIMATIONS

    if(animateIcon(1, &usbImagePos))
    {
        draw_bitmap(x, usbImagePos, usbIcon, 16, 8, NOINVERT, 0);
        x += 20;
    }

    #else

    if(UDADDR != 0)
    {
        draw_bitmap(x, FRAME_HEIGHT - 9, usbIcon, 16, 8, NOINVERT, 0);
        x += 20;
    }

    #endif

    // Draw charging icon
    #if COMPILE_ANIMATIONS

//    if(animateIcon(CHARGING(), &chargeImagePos))
//    {
//        draw_bitmap(x, chargeImagePos, chargeIcon, 8, 8, NOINVERT, 0);
//        x += 12;
//    }

    #else

    if(CHARGING())
    {
        draw_bitmap(x, FRAME_HEIGHT - 9, chargeIcon, 8, 8, NOINVERT, 0);
        x += 12;
    }

    #endif

    #if COMPILE_STOPWATCH

    // Stopwatch icon
    if(stopwatch_active())
    {
        draw_bitmap(x, FRAME_HEIGHT - 8, stopwatch, 8, 8, NOINVERT, 0);
        x += 12;
    }

    #endif
    return DISPLAY_DONE;
}





static  void __SysTick(void)
{

    iAng1++;

    if(iAng1 == 180) iAng1 = 0;

}


//画点
//x:0~63
//y:0~63
//t:1 填充 0,清空
static  void _OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t)
{
    //对应 byte __OLED_GRAM[512];	  // x= 64 ,y=8
    //变换一哈形式
    uint8_t pos, bx, temp = 0;

    if(x > 63 || y > 63)return; //超出范围了.

    pos = y / 8;
    bx = y % 8;
    temp = 1 << (bx);

    if(t) __OLED_GRAM[64 * pos + x] |= temp; // 做到的效果是竖着存放 竖着为y ，横着为x
    else __OLED_GRAM[64 * pos + x] &= ~temp;
}


//画线
//x11,y11:起点坐标
//x21,y21:终点坐标
static  void _OLED_DrawLine(u16 x11, u16 y11, u16 x21, u16 y21)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x21 - x11; //计算坐标增量
    delta_y = y21 - y11;
    uRow = x11;
    uCol = y11;

    if(delta_x > 0)incx = 1; //设置单步方向
    else if(delta_x == 0)incx = 0; //垂直线
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if(delta_y > 0)incy = 1;
    else if(delta_y == 0)incy = 0; //水平线
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if( delta_x > delta_y)distance = delta_x; //选取基本增量坐标轴
    else distance = delta_y;

    for(t = 0; t <= distance + 1; t++ ) //画线输出
    {
        _OLED_DrawPoint(uRow, uCol, 1); //画点
        xerr += delta_x ;
        yerr += delta_y ;

        if(xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }

        if(yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}



static void drawDate()
{
    // Get day string
    char day[BUFFSIZE_STR_DAYS];
    strcpy(day, days[timeDate.date.day]);

    // Get month string
    char month[BUFFSIZE_STR_MONTHS];
    strcpy(month, months[timeDate.date.month]);

    // Draw date
    char buff[BUFFSIZE_DATE_FORMAT];
    sprintf_P(buff, "%s %02hhu", day, timeDate.date.date);
    draw_string(buff, false, 87, 30);

    //sprintf_P(buff, PSTR(DATE_FORMAT), day, timeDate.date.date, month, timeDate.date.year);

    sprintf_P(buff, "%s", month);

    draw_string(buff, false, 60, 35);

    sprintf_P(buff, "20");

    draw_string(buff, false, 64, 25);

    sprintf_P(buff, "%02hhu", timeDate.date.year);

    draw_string(buff, false, 67, 15);

}

#if COMPILE_ANIMATIONS
static bool animateIcon(bool active, byte* pos)
{
    byte y = *pos;

    if(active || (!active && y < FRAME_HEIGHT))
    {
        if(active && y > FRAME_HEIGHT - 8)
            y -= 1;
        else if(!active && y < FRAME_HEIGHT)
            y += 1;

        *pos = y;
        return true;
    }

    return false;
}
#endif

static display_t ticker()
{
    static byte yPos;
    static byte yPos_secs;
    static bool moving = false;
    static bool moving2[5];

    #if COMPILE_ANIMATIONS
    static byte hour2;
    static byte mins;
    static byte secs;

    if(appConfig.animations)
    {
        if(timeDate.time.secs != secs)
        {
            yPos = 0;
            yPos_secs = 0;
            moving = true;

            moving2[0] = div10(timeDate.time.hour) != div10(hour2);
            moving2[1] = mod10(timeDate.time.hour) != mod10(hour2);
            moving2[2] = div10(timeDate.time.mins) != div10(mins);
            moving2[3] = mod10(timeDate.time.mins) != mod10(mins);
            moving2[4] = div10(timeDate.time.secs) != div10(secs);

            //memcpy(&timeDateLast, &timeDate, sizeof(timeDate_s));
            hour2 = timeDate.time.hour;
            mins = timeDate.time.mins;
            secs = timeDate.time.secs;
        }

        if(moving)
        {
            if(yPos <= 3)
                yPos++;
            else if(yPos <= 6)
                yPos += 3;
            else if(yPos <= 16)
                yPos += 5;
            else if(yPos <= 22)
                yPos += 3;
            else if(yPos <= 24 + TICKER_GAP)
                yPos++;

            if(yPos >= MIDFONT_HEIGHT + TICKER_GAP)
                yPos = 255;

            if(yPos_secs <= 1)
                yPos_secs++;
            else if(yPos_secs <= 13)
                yPos_secs += 3;
            else if(yPos_secs <= 16 + TICKER_GAP)
                yPos_secs++;

            if(yPos_secs >= FONT_SMALL2_HEIGHT + TICKER_GAP)
                yPos_secs = 255;

            if(yPos_secs > FONT_SMALL2_HEIGHT + TICKER_GAP && yPos > MIDFONT_HEIGHT + TICKER_GAP)
            {
                yPos = 0;
                yPos_secs = 0;
                moving = false;
                memset(moving2, false, sizeof(moving2));
            }
        }
    }
    else
    #endif
    {
        yPos = 0;
        yPos_secs = 0;
        moving = false;
        memset(moving2, false, sizeof(moving2));
    }

    tickerData_t data;

    // Seconds
    data.x = 50;
    data.y = 48 + TIME_POS_Y;
    data.bitmap = (const byte*)&small2Font;
    data.w = FONT_SMALL2_WIDTH;
    data.h = FONT_SMALL2_HEIGHT;
    data.offsetY = yPos_secs;
    data.val = div10(timeDate.time.secs);
    data.maxVal = 5;
    data.moving = moving2[4];
    drawTickerNum(&data);

    data.x = 65;
    data.val = mod10(timeDate.time.secs);
    data.maxVal = 9;
    data.moving = moving;
    drawTickerNum(&data);

    // Set new font data for hours and minutes
    data.y = 25 + TICKER_GAP + TIME_POS_Y;
    data.w = MIDFONT_WIDTH;
    data.h = MIDFONT_HEIGHT;
    data.bitmap = (const byte*)&midFont;
    data.offsetY = yPos;

    // Minutes
    data.x = 80;
    data.val = div10(timeDate.time.mins);
    data.maxVal = 5;
    data.moving = moving2[2];
    drawTickerNum(&data);

    data.x = 110;
    data.val = mod10(timeDate.time.mins);
    data.maxVal = 9;
    data.moving = moving2[3];
    drawTickerNum(&data);

    // Hours
    data.y = TIME_POS_Y;
    data.x = 80;
    data.val = div10(timeDate.time.hour);
    data.maxVal = 5;
    data.moving = moving2[0];
    drawTickerNum(&data);

    data.x = 110;
    data.val = mod10(timeDate.time.hour);
    data.maxVal = 9;
    data.moving = moving2[1];
    drawTickerNum(&data);


    // Draw AM/PM character
    char tmp[2];
    tmp[0] = timeDate.time.ampm;
    tmp[1] = 0x00;
    draw_string(tmp, false, 104, 20);

    return (moving ? DISPLAY_BUSY : DISPLAY_DONE);
}

static void drawTickerNum(tickerData_t* data)
{
    byte arraySize = (data->w * data->h) / 8;
    byte yPos = data->offsetY;
    const byte* bitmap = &data->bitmap[data->val * arraySize];
    byte x = data->x;
    byte y = data->y;

    if(!data->moving || yPos == 0 || yPos == 255)
        draw_bitmap(x, y, bitmap, data->w, data->h, NOINVERT, 0);
    else
    {
        byte prev = data->val - 1;

        if(prev == 255)
            prev = data->maxVal;

        draw_bitmap(x, y, bitmap, data->w, data->h, NOINVERT, yPos - data->h - TICKER_GAP);
        draw_bitmap(x, y, &data->bitmap[prev * arraySize], data->w, data->h, NOINVERT, yPos);
    }
}


