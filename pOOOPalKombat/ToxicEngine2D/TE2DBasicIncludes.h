/* BASIC INCLUDES */

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")	// no console
#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <math.h>

using namespace std;
using namespace sf;

enum TE2D_VIEW { TE2D_DEFAULT_VIEW = -1 };
enum TE2D_DIRECTION { TE2D_UP = 0, TE2D_DOWN, TE2D_LEFT, TE2D_RIGHT };

const Vector2f TE2D_FULL_HD_SCREEN_SIZE(1920, 1080);
const Vector2f TE2D_HD_SCREEN_SIZE(1366, 768);