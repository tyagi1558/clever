/*
 * Clever programming language
 * Copyright (c) 2011 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * $Id$
 */

#include <iostream>
#include "compiler/value.h"
#include "compiler/typetable.h"
#include "std/file/file.h"
#include "std/file/filestream.h"

namespace clever { namespace packages { namespace std {

namespace file {
/**
 * println(object a, [ ...])
 * Prints the object values without trailing newline
 */
/*static CLEVER_FUNCTION(print) {
	for (int i = 0, size = args->size(); i < size; ++i) {
		::std::cout << args->at(i)->toString();
	}
}*/

} // namespace file

/**
 * Initializes Standard module
 */
void File::init() throw() {
	//const Type* string_type = TypeTable::getType(CSTRING("String"));
	Class* filestream = new file::FileStream();
	filestream->init();
	
	using namespace file;
	addClass(filestream);
}

}}} // clever::packages::std
