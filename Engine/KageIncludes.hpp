/*
All of the header files needed for KAGE

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

// any "standard" C++ includes
#include <memory>

// third party libraries
#include "entt/entt.hpp"
#include "libtcod/libtcod.hpp"

/* KAGE header files */

// Constants... will likely eventually delete this
#include "Constants.hpp"

// Engine Files
#include "KageException.hpp"
#include "State.hpp"
#include "GUI.hpp"
#include "Map.hpp"
#include "MapSpace.hpp"

// Custom Types
#include "Vector2D.hpp"

// Components
#include "PositionComponent.hpp"
#include "RenderComponent.hpp"
#include "VelocityComponent.hpp"
#include "MouseStatus.hpp"

// Systems
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include "MovementHandler.hpp"