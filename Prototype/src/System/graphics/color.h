#pragma once

struct Color {
    uint8_t r, g, b, a;
};

//Simple colours
const Color COLOR_BLACK = { 0, 0, 0, 255 };
const Color COLOR_WHITE = { 255, 255, 255, 255 };
const Color COLOR_RED = { 255, 0, 0, 255 };
const Color COLOR_GREEN = { 0, 255, 0, 255 };
const Color COLOR_BLUE = { 0, 0, 255, 255 };
const Color COLOR_YELLOW = { 255, 255, 0, 255 };
const Color COLOR_PURPLE = { 255, 0, 255, 255 };
const Color COLOR_CYAN = { 0, 255, 255, 255 };
const Color COLOR_NONE = { 0, 0, 0, 0 };
//Non-simple colours
const Color COLOR_PINK = { 255, 128, 160, 255 };