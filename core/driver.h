/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_DRIVER_H
#define CLEVER_DRIVER_H

#include <stack>
#include "core/compiler.h"
#include "core/parser.hh"

namespace clever { namespace ast {

class ASTNode;

}} // clever::ast

namespace clever {

extern int* g_clever_argc;
extern char*** g_clever_argv;

class ScannerState;

// Lexer prototype
Parser::token_type yylex(Parser::semantic_type*,
		Parser::location_type*, Driver&,
		ScannerState&);

/// Driver - Handles the lexer, parser and compiler
class Driver {
public:
	typedef std::stack<ScannerState*> ScannerStack;

	Driver()
		: m_is_file(false), m_trace_parsing(false), m_loaded(false),
			m_file(NULL), m_cflags(0), m_compiler(this)
#ifdef CLEVER_DEBUG
			, m_dump_opcode(false)
#endif
		 {}

	virtual ~Driver() {}

	// Returns the parsed file
	CString* getFile() const {
		return const_cast<CString*>(m_file);
	}

	// Read file to the scanner
	void readFile(std::string&) const;

	// Starts the parser and loads the Symbol table
	int loadStr(const std::string&, bool importStd);
	int loadFile(const std::string&, const std::string& = "");

	// Error handling
	void error(const location&, const std::string&) const;
	void error(const std::string&) const;

	// Executes the script
	virtual void execute(bool) = 0;

	// Tracing
	void setTraceParsing(bool trace) { m_trace_parsing = trace; }

	// Compiler flags
	void setCompilerFlags(size_t flags) { m_cflags |= flags; }
	Compiler& getCompiler() { return m_compiler; }

	size_t getCompilerFlags() const { return m_cflags; }
protected:
	// Indicates if it's a file is being parsed
	bool m_is_file;

	// Debug option
	bool m_trace_parsing;

	// Indicates if some file/string has been loaded to be executed
	bool m_loaded;

	// The file path -f
	const CString* m_file;

	// Compiler flags
	size_t m_cflags;

	// Compiler
	Compiler m_compiler;

	// Scanners stack
	ScannerStack m_scanners;

#ifdef CLEVER_DEBUG
	// Opcode dumping option
	bool m_dump_opcode;
#endif

private:
	DISALLOW_COPY_AND_ASSIGN(Driver);
};

/// Interpreter
class Interpreter : public Driver {
public:
	Interpreter(int*, char***);

#ifdef CLEVER_DEBUG
	void setDebug() { m_dump_opcode = true; }
#endif
	void execute(bool interactive);
	void shutdown();
private:
	DISALLOW_COPY_AND_ASSIGN(Interpreter);
};

} // clever

#endif // CLEVER_DRIVER_H
