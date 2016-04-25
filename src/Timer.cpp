#ifdef WIN32
#	include <SDL.h>
#	undef main
#else
#	include <SDL2/SDL.h>
#endif

#include <csaru-core-cpp/csaru-core-cpp.h>

#include "../include/Timer.hpp"

namespace CSaruGame {

//===========================================================================
void Timer::Advance () {
	if (m_paused)
		return;

	uint64_t now = SDL_GetPerformanceCounter();
	if (m_sdlCounterLast) {
		m_delta            = (now - m_sdlCounterLast);
		m_ticksAccumulated += m_delta;
	}
	else {
		m_delta = 0;
	}

	m_sdlCounterLast   = now;
}

//===========================================================================
uint64_t Timer::GetMs () const {
	return m_ticksAccumulated / (m_frequency / 1000);
}

//===========================================================================
uint64_t Timer::GetMsDelta () const {
	return m_delta / (m_frequency / 1000);
}

//===========================================================================
uint64_t Timer::GetSeconds () const {
	return m_ticksAccumulated / m_frequency;
}

//===========================================================================
uint64_t Timer::GetTicksPerSecond () const {
	return m_frequency;
}

//===========================================================================
void Timer::SetPaused (bool paused) {
	// If unpausing, don't count all the previous time that's elapsed.
	if (m_paused && !paused) {
		m_sdlCounterLast = SDL_GetPerformanceCounter();
	}

	m_paused = paused;
}

//===========================================================================
void Timer::Reset () {
	m_ticksAccumulated = 0;
	m_sdlCounterLast   = 0;
	m_delta            = 0;

	if (!m_paused)
		m_sdlCounterLast = SDL_GetPerformanceCounter();

	// Should we reset m_frequency here?  Power-managing laptops and such
	// may give different frequencies at different times, right?
	// Or is that now a thing of the past?
}

//===========================================================================
void Timer::UpdateFrequency () {
	m_frequency = SDL_GetPerformanceFrequency();
}

} // namespace CSaruGame

