#pragma once

namespace CSaruGame {

class Timer {
private:
	uint64_t m_ticksAccumulated = 0;
	uint64_t m_frequency        = 0; // ticks per second
	uint64_t m_sdlCounterLast   = 0; // Counter at last Unpause
	bool     m_paused           = true;

public:
	Timer ()              = default;
	Timer (const Timer &) = default;

	// Queries
	uint64_t GetTicks () const  { return m_ticksAccumulated; }
	uint64_t GetTicksPerSecond () const;
	uint64_t GetSeconds () const;
	uint64_t GetMs () const;
	bool     GetPaused () const { return m_paused; }

	// Commands
	void Reset ();

	void SetPaused (bool paused);
	void Advance ();

	void UpdateFrequency ();
};

} // namespace CSaruGame

