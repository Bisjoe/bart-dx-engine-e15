#ifndef COMMON_H
#define COMMON_H

// Global constants
#ifndef DEFAULT_WIN_TITLE
#define DEFAULT_WIN_TITLE "Engine - "
#endif

#ifndef DEFAULT_WIN_W
#define DEFAULT_WIN_W 800
#endif

#ifndef DEFAULT_WIN_H
#define DEFAULT_WIN_H 600
#endif

#ifndef DEFAULT_FRAMERATE
#define DEFAULT_FRAMERATE 30
#endif

#ifndef RESOLUTION_NTSC
#define RESOLUTION_NTSC {256, 240}
#endif

#ifndef RESOLUTION_PAL
#define RESOLUTION_PAL {256, 224}
#endif


// STD Lib
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// DirectX
#include <d3dx9.h>

// Framework
#include "App.h"

// Engine
//#include "Input.h"
//#include "Timer.h"
#include "ResourceHolder.h"

// Renderer
#include "Vertex.h"

#endif
