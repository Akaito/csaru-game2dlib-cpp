cmake_minimum_required(VERSION 3.2)

# Could file(GLOB_RECURSE ...) for these, but specifying each one
#	manually means the build system knows when something changes.
set(src_files
	src/GameObject.cpp
	#src/GameObjectDatabase.cpp
	src/GocGobjRotator.cpp
	src/GocSpriteSimple.cpp
	src/GocSrcRectAnimator.cpp
	src/Level.cpp
	src/SDL_RWopsPhysicsFS.cpp
	src/Texture.cpp
	src/TextureAnimation.cpp
	src/Timer.cpp
	src/Transform.cpp
)
set(header_files
	include/csaru-game2dlib-cpp.h
	include/GameObject.hpp
	include/GameObjectComponent.hpp
	#include/GameObjectDatabase.hpp
	include/GocGobjRotator.hpp
	include/GocSpriteSimple.hpp
	include/GocSrcRectAnimator.hpp
	include/Level.hpp
	include/ObjId.hpp
	include/SDL_RWopsPhysicsFS.hpp
	include/Texture.hpp
	include/TextureAnimation.hpp
	include/Timer.hpp
	include/Transform.hpp
)

# CSaruDir must be set in your environment variables!  It should point to a
#	directory with src/bin/pkg directories (or at least src; others can be
#	created later).  Open CSaru.cmake in a text editor to see what it's doing.
#	CSaru_Lib() has been written with the intent of being broken out in this
#	file if you need finer control over your project.
include($ENV{CSaruDir}/cmake/CSaru.cmake)

# Pass the version of your project; it's not related to the CSaruEnviron.
CSaru_Lib(0.1 "${src_files}" "${header_files}")

# Custom stuff hand-edited into this CMakeLists ...

# Add <CSaruDir>/pkg/vendor/CML/ to compiler's paths for include-searching
CSaru_UseVendor("CML")

CSaru_Depends("csaru-core-cpp")

if (WIN32)
	# Note! On Windows, be sure you've set env vars SDL2, SDL2_IMAGE, and SDL2_TTF.
	# They should be a path that has sub-dirs like "include" and "lib".
	set(SDL_BUILDING_LIBRARY True)  # This doesn't seem to be needed?
	include(FindSDL2)
	include_directories("${SDL2_INCLUDE_DIR}")
	link_libraries("${SDL2_LIBRARY}")
	include(FindSDL2_image)
	include_directories("${SDL2_IMAGE_INCLUDE_DIR}")
	link_libraries("${SDL2_IMAGE_LIBRARY}")
	include(FindSDL2_ttf)
	include_directories("${SDL2_TTF_INCLUDE_DIR}")
	link_libraries("${SDL2_TTF_LIBRARY}")
elseif (UNIX)
	# SDL-finding not needed here?
else()
	message(SEND_ERROR "Non-*nix/Win platform.  SDL-finding style unknown.")
endif()

set(CXX_STANDARD_REQUIRED true)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# Disable compiler optimizations.
if (UNIX)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
endif()

set(CMAKE_BUILD_TYPE "Debug")

