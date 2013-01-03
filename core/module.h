/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_MODULE_H
#define CLEVER_MODULE_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <string>
#include "types/function.h"

#define CLEVER_MODULE_INIT(x) void x::init(int flags)

#define CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION \
	void init(int flags);

/* {{{ Accessor Macros for Function Arguments */
#define CARG_COUNT		 args.size
/* {{{ CString */
#define CARG_CSTR(index) args[index]->getStr() /* }}} */
/* {{{ String Pointer */
#define CARG_PSTR(index) ((char*) (args[index]->getStr())->c_str()) /* }}} */
#define CARG_DBL(index)	 args[index]->getDouble()
#define CARG_LONG(index) args[index]->getLong()
#define CARG_OBJ(index)	 args[index]->getObj()
#define CARG_DATA(index) args[index]->getData()
#define CARG_DUMP(index) args[index]->dump()
/* }}} */

#define CRETURN_STR(r)	
#define CRETURN_DBL(d)
#define CRETURN_LONG(l)
#define CRETURN_OBJ(o)

namespace clever {

typedef std::tr1::unordered_map<const CString*, Function*> FunctionMap;
typedef std::pair<const CString*, Function*> FuncMapEntry;

/// Module representation
class Module {
public:
	enum ModuleStatus { UNLOADED, LOADED };

	Module(std::string name)
		: m_name(name), m_flags(UNLOADED), m_funcs() {}

	virtual ~Module() {}

	void addFunction(Function* func) {
		m_funcs.insert(FuncMapEntry(CSTRING(func->getName()), func));
	}

	FunctionMap& getFunctions() { return m_funcs; }

	std::string getName() { return m_name; }

	void setLoaded() { m_flags = LOADED; }
	bool isLoaded() const { return m_flags == LOADED; }

	virtual void init(int) = 0;
private:
	std::string m_name;
	ModuleStatus m_flags;
	FunctionMap m_funcs;
};

typedef std::tr1::unordered_map<const CString*, Module*> ModuleMap;
typedef std::pair<const CString*, Module*> ModulePair;

/// Package representation
class Package {
public:
	enum PackageStatus { UNLOADED, LOADED };

	Package(std::string name)
		: m_name(name), m_flags(UNLOADED) {}

	virtual ~Package() {}

	void addModule(Module* module) {
		m_modules.insert(ModulePair(CSTRING(module->getName()), module));
	}

	ModuleMap& getModules() { return m_modules; }

	void setLoaded() { m_flags = LOADED; }
	bool isLoaded() const { return m_flags == LOADED; }

	virtual void init() = 0;
	virtual const char* getVersion() const = 0;
private:
	std::string m_name;
	PackageStatus m_flags;
	ModuleMap m_modules;
};

} // clever

#endif // CLEVER_MODULE_H
