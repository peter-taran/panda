
// main Panda library include file

#pragma once



// dependencies
#include "dependencies/include_boost.h"
#include "dependencies/include_std.h"



// prefix
#pragma warning(push)
#include "src/config/prefix.h"



// predeclarations
class Error;
template<class NormalObject> class Err;



// public declarations
#include "src/utils/consts.h"
#include "src/logic/null.h"
#include "src/logic/bool.h"
#include "src/type/traits.h"
#include "src/utils/assertions.h"
#include "src/utils/foreach.h"
#include "src/utils/oneof.h"
#include "src/numerics/nativeintegers.h"
#include "src/memory/byte.h"
#include "src/containers/seq.h"
#include "src/containers/array.h"
#include "src/memory/memsize.h"
#include "src/memory/memoffs.h"
#include "src/memory/memaddr.h"
#include "src/utils/misc.h"
#include "src/memory/memarea.h"
#include "src/memory/membuff.h"
#include "src/type/facade.h"
#include "src/memory/mem.h"
#include "src/strings/encodings.h"
#include "src/strings/char.h"
#include "src/strings/str.h"
#include "src/errors/error.h"



// inline implementation
// (please, keep the same order as in public declarations above)
#include "src/errors/error.inl"
#include "src/numerics/nativeintegers.inl"
#include "src/memory/memsize.inl"
#include "src/memory/memoffs.inl"
#include "src/memory/memaddr.inl"
#include "src/memory/memarea.inl"
#include "src/memory/membuff.inl"
#include "src/memory/mem.inl"
#include "src/strings/encodings.inl"
#include "src/strings/char.inl"
#include "src/strings/str.inl"



// postfix
#include "src/config/postfix.h"



#pragma warning(pop)
