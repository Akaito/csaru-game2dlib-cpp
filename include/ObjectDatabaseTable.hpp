#pragma once

#include <map>

#include <csaru-uuid-cpp/csaru-uuid-cpp.h>
#include <csaru-container-cpp/csaru-container-cpp.h>

// TODO : include SDL for SDL_assert_release

namespace CSaruGame {

using CSaruUuid::Uuid;

enum class FindStyle {
	FAIL = 0,
	CREATE_NOW, // create object if not found; block until done
};

/*
struct IGameObjectDatabase {
	// virtual // TODO : Return dict? Iter? Gob?
	virtual ~IGameObjectDatabase () = 0;
};
//*/


template <typename T_Type>
class ObjectDatabaseTable { //: public IGameObjectDatabase {
public: // Types and constants
	typedef std::map<Uuid, T_Type *> ObjectLookupTable;
	// TODO : Pointer-generation pair style handle-supporting array.

protected: // Data
	ObjectLookupTable m_lookupTable;
	ObjId             m_nextTransientId;

public: // Construction
	ObjectDatabaseTable (ObjId moduleTypeId) :
		m_nextTransientId(moduleTypeId + 1)
	{}

	~ObjectDatabaseTable () {
		Clear();
	}

public: // Queries
	T_Type * Find (FindStyle findStyle, const Uuid & id) {
		auto iter = m_lookupTable.find(id);
		if (iter != lookupTable.end())
			return iter->second;

		T_Type * result = nullptr;
		switch (findStyle) {
			case FindStyle::CREATE_NOW: {
				Create(id);
				return Find(FindStyle::FAIL, id);
			}

			case FindStyle::FAIL: {
				SDL_assert_release(iter != m_lookupTable.end());
				return nullptr;
			}
		}
		return result;
	}

public: // Commands
	void Init () {}
	void Clear () {
		// TODO : LEEAAAKKS!!
		m_lookupTable.clear();
	}

	bool Create (Uuid id) {
		return m_lookupTable.insert(id, new T_Type(m_nextTransientId++)) != m_lookupTable.end();
	}
};

} // namespace CSaruGame

