#pragma once
#include "raylib.h"
#include <iostream>
#include <math.h>
#include <vector>

#include "mathfunctions.hpp"



constexpr int WindowWidth{ 1600 };
constexpr int WindowHeight{ 900 };
constexpr int TargetFPS{ 60 };
static int FramesPassed{ 0 };