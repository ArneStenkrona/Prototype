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
//Dark versions of simple colours
const Color COLOR_GREY = { 128, 128, 128, 255 };
const Color COLOR_DARK_RED = { 128, 0, 0, 255 };
const Color COLOR_DARK_GREEN = { 0, 128, 0, 255 };
const Color COLOR_DARK_BLUE = { 0, 0, 128, 255 };
const Color COLOR_DARK_YELLOW = { 128, 128, 0, 255 };
const Color COLOR_DARK_PURPLE = { 128, 0, 128, 255 };
const Color COLOR_DARK_CYAN = { 0, 128, 128, 255 };
//Very dark versions of simple colours
const Color COLOR_DARK_GREY = { 64, 64, 64, 255 };
const Color COLOR_VERY_DARK_RED = { 64, 0, 0, 255 };
const Color COLOR_VERY_DARK_GREEN = { 0, 64, 0, 255 };
const Color COLOR_VERY_DARK_BLUE = { 0, 0, 64, 255 };
const Color COLOR_VERY_DARK_YELLOW = { 64, 64, 0, 255 };
const Color COLOR_VERY_DARK_PURPLE = { 64, 0, 64, 255 };
const Color COLOR_VERY_DARK_CYAN = { 0, 64, 64, 255 };
//Non-simple colours
const Color COLOR_PINK = { 255, 128, 160, 255 };