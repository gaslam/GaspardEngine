#pragma once
#include <iostream>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // WIN32
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <platforms/log.h>
#include <memory>