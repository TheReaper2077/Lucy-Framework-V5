#pragma once

#include <stdint.h>
#ifndef UUID_SYSTEM_GENERATOR
	#define UUID_SYSTEM_GENERATOR
#endif
#include <stduuid/uuid.h>

#define LUTIL_UUID uint64_t
#define LUTIL_NULL_UUID (LUTIL_UUID)0
#define LUTIL_GENERATE_UUID *(LUTIL_UUID*)uuids::uuid_system_generator{}().as_bytes().data()