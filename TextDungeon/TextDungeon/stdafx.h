// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>


// Mencionar aquí los encabezados adicionales que el programa necesita

#using <mscorlib.dll>
#include <vcclr.h>

// Mencionar aquí los namespace que el programa necesite

using namespace System;
using namespace System::Threading;
using namespace System::Collections;

// Mencionar aquí encabezados del porgrama

#include "Audio.h"
#include "Writter.h"
#include "DungeonObject.h"
#include "Key.h"
#include "Room.h"
#include "Door.h"
#include "Player.h"
#include "Dungeon.h"
