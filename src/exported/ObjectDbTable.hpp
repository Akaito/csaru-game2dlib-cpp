#pragma once

#include <map>

#ifdef WIN32
#	include <SDL.h>
#	undef main
#else
#	include <SDL2/SDL.h>
#endif

#include <csaru-container-cpp/csaru-container-cpp.hpp>

namespace CSaruGame {

enum class FindStyle {
	FAIL = 0,
	CREATE_NOW, // Create object if not found; block until done.
};

/*
struct IGameObjectDatabase {
	// virtual // TODO : Return dict? Iter? Gob?
	virtual ~IGameObjectDatabase () = 0;
};
//*/


template <typename T_Id, typename T_Object>
class ObjectDbTable { //: public IGameObjectDatabase {
public: // Types and constants
	typedef CSaruContainer::ObjectPool<T_Object> ObjectPool;
	typedef typename ObjectPool::Handle          Handle;
	typedef std::map<T_Id, Handle>               LookupTable;

protected: // Data
	ObjectPool  m_objectPool;
	LookupTable m_lookupTable;

public: // Construction
	ObjectDbTable ()
	{}


	~ObjectDbTable () {
		Clear();
	}

public: // Queries
	Handle Find (FindStyle findStyle, const T_Id & id) {
		auto iter = m_lookupTable.find(id);
		if (iter != m_lookupTable.end())
			return iter->second;

		switch (findStyle) {
			case FindStyle::CREATE_NOW: {
				return CreateNow(id);
			}

			case FindStyle::FAIL: {
				SDL_assert(iter != m_lookupTable.end());
				return Handle();
			}
		}
		return Handle();
	}

public: // Commands
	void Init () {
		m_objectPool.Prepare();
	}


	void Clear () {
		m_objectPool.DestroyAll();
		m_lookupTable.clear();
	}


	Handle CreateNow (T_Id id) {
		auto findResult = m_lookupTable.find(id);
		SDL_assert(findResult == m_lookupTable.end());
		if (findResult != m_lookupTable.end()) {
			SDL_SetError(
				"ObjectDbTable::Create: Object already exists at {%lu,%lu}.",
				id.high,
				id.low
			);
			return Handle();
		}

		Handle handle;
		T_Object * obj = m_objectPool.Alloc(&handle);
		SDL_assert(obj);
		m_lookupTable[id] = handle;
		return handle;
	}
};

} // namespace CSaruGame

