#include "../include/RWopsPhysicsFS.hpp"

#include <physfs.h>


namespace {

//==============================================================================
int SDLCALL close (SDL_RWops * context) {

	PHYSFS_File * file = context->hidden->unknown->data1;

	const int physFsCloseResult = PHYSFS_close(file);
	SDL_assert_paranoid(physFsCloseResult);
	if (!PHYSFS_close(file)) {
		SDL_SetError(
			"Failed to close PhysicsFS file; handle remains open: %s",
			PHYSFS_getLastError()
		);
	}

	SDL_FreeRW(context);
	// return 0 on success; -1 if failed to flush to disk, etc.
	return physFsCloseResult == 0 ? -1 : 0;

}

//==============================================================================
std::size_t SDLCALL read (
	SDL_RWops * context,
	void *      ptr,
	std::size_t size,
	std::size_t maxnum
) {
}

//==============================================================================
Sint64 SDLCALL seek (SDL_RWops * context, Sint64 offset, int whence) {
}

//==============================================================================
Sint64 SDLCALL size (SDL_RWops * context) {
}

//==============================================================================
Sint64 SDLCALL tell (SDL_RWops * context) {
}

//==============================================================================
std::size_t SDLCALL write (
	SDL_RWops *  context,
	const void * ptr,
	std::size_t  size,
	std::size_t  num
) {
}

} // anonymous namespace


namespace CSaruGame {

//==============================================================================
SDL_RWops * AllocRWopsPhysFs (const char * path, const char mode) {

	SDL_assert(mode == 'a' || mode == 'r' || mode == 'w');

	PHYSFS_File * physFsFile = nullptr;
	switch (mode) {
		case 'a': physFsFile = PHYSFS_openAppend(path); break;
		case 'r': physFsFile = PHYSFS_openRead(path);   break;
		case 'w': physFsFile = PHYSFS_openWrite(path);  break;

		default:
			SDL_SetError("Invalid PhysicsFS RWops mode {%c}.  Use one of a,r,w.", mode);
			return nullptr;
	}
	if (!physFsFile) {
		SDL_SetError("PhysicsFS error while creating RWops: %s", PHYSFS_getLastError());
		return nullptr;
	}

	SDL_RWops * rwOps = SDL_AllocRW();
	rwOps->close = close;
	rwOps->read  = read;
	rwOps->seek  = seek;
	rwOps->size  = size;
	rwOps->tell  = tell;
	rwOps->write = write;
	rwOps->type  = SDL_RWOPS_UNKNOWN; // application-defined RWops type
	rwOps->hidden->unknown->data1 = physFsFile;
	rwOps->hidden->unknown->data2 = mode;

	// Must be SDL_RWclose()'d to be freed by SDL_FreeRW()!
	return rwOps;

}

} // namespace CSaruGame

