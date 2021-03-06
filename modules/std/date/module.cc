/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "core/value.h"
#include "core/modmanager.h"
#include "modules/std/date/module.h"
#include "modules/std/date/date.h"

namespace clever { namespace modules { namespace std {

/// Standard date module initialization
CLEVER_MODULE_INIT(DateModule)
{
	addType(new Date);
}

}}} // clever::modules::std
