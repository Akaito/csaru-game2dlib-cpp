#pragma once

#include <csaru-core-cpp/csaru-core-cpp.hpp>

namespace CSaruGame {

typedef uint64_t ObjId;

#define CSARU_MODULE_MASK     static_cast<ObjId>(0xFFFF000000000000)
#define CSARU_TYPE_MASK       static_cast<ObjId>(0x0000FFFF00000000)
#define CSARU_GENERATION_MASK static_cast<ObjId>(0x00000000FFFFFFFF)

// TODO : ObjectDb[Table] gains internal array of T_Id as encountered;
//        treat ObjId generation as index into that table?
//        Enables use of uint64_t as transient, untyped, intra-program
//        ID to any object in a pool.


#define CSARU_MODULE_ID(moduleId) \
	((static_cast<ObjId>(moduleId) << 48) & CSARU_MODULE_MASK)
#define CSARU_TYPE_ID(moduleId, typeId) \
	(moduleId | ((static_cast<ObjId>(typeId) << 32) & CSARU_TYPE_MASK))
#define CSARU_ID(moduleId, typeId, generation) \
	(moduleId | typeId | (static_cast<ObjId>(generation) & CSARU_GENERATION_MASK))

static const ObjId s_ObjId_Invalid = 0;
static const ObjId s_Module_Base   = CSARU_MODULE_ID(0xC5A2);

} // namespace CSaruGame

