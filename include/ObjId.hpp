#pragma once

#include <csaru-core-cpp/csaru-core-cpp.h>

namespace CSaruGame {

#define CSARU_MODULE_MASK     0xFFFF000000000000
#define CSARU_TYPE_MASK       0x0000FFFF00000000
#define CSARU_GENERATION_MASK 0x00000000FFFFFFFF

#define CSARU_MODULE_ID(moduleId) \
	((static_cast<uint64_t>(moduleId) << 12) & CSARU_MODULE_MASK)
#define CSARU_TYPE_ID(moduleId, typeId) \
	(CSARU_MODULE_ID(moduleId) | ((static_cast<uint64_t>(typeId) << 8) & CSARU_TYPE_MASK))
#define CSARU_ID(moduleId, typeId, generation) \
	(CSARU_TYPE_ID(moduleId, typeId) | (static_cast<uint64_t>(generation) & CSARU_GENERATION_MASK))

#define CSARU_GET_MODULE_ID(objectId) \
	(static_cast<uint16_t>((objectId & CSARU_MODULE_MASK) >> 12))
#define CSARU_GET_TYPE_ID(objectId) \
	(static_cast<uint16_t>((objectId & CSARU_TYPE_MASK) >> 8))
#define CSARU_GET_GENERATION(objectId) \
	(static_cast<uint32_t>(objectId & CSARU_GENERATION_MASK))

typedef uint64_t ObjId;
static const ObjId s_ObjId_Invalid = 0;
static const ObjId s_Module_Base   = CSARU_MODULE_ID(0x0001);

} // namespace CSaruGame

