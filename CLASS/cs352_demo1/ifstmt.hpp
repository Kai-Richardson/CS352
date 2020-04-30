#pragma once

/* THE FOLLOWING HAS BEEN AUTOMATICALLY GENERATED BY THE EGG PARSER GENERATOR.
 * DO NOT EDIT. */

// {%

#include <stdio.h>

// %}

#include <string>
#include "parser.hpp"

namespace ifstmt {

	bool IfStmt(parser::state&);
	bool Expr(parser::state&);
	bool Stmt(parser::state&);
	bool IF(parser::state&);
	bool ELSE(parser::state&);
	bool OPEN(parser::state&);
	bool CLOSE(parser::state&);
	bool _(parser::state&);

	bool IfStmt(parser::state& ps) {
		return parser::memoize(1, 
			parser::sequence({
				IF,
				OPEN,
				Expr,
				CLOSE,
				[&](parser::state& ps) { printf("[");  return true; },
				Stmt,
				[&](parser::state& ps) { printf("]");  return true; },
				parser::option(
					parser::sequence({
						ELSE,
						[&](parser::state& ps) { printf("[");  return true; },
						Stmt,
						[&](parser::state& ps) { printf("]");  return true; }}))}))(ps);
	}

	bool Expr(parser::state& ps) {
		return parser::memoize(2, 
			parser::sequence({
				parser::memoize_some(3, parser::between('0', '9')),
				_}))(ps);
	}

	bool Stmt(parser::state& ps) {
		return parser::memoize(4, parser::memoize_some(5, 
			parser::sequence({
				parser::memoize_some(6, 
					parser::choice({
						parser::between('A', 'Z'),
						parser::between('a', 'z'),
						parser::literal('_')})),
				_})))(ps);
	}

	bool IF(parser::state& ps) {
		return parser::memoize(7, 
			parser::sequence({
				parser::literal("if"),
				_}))(ps);
	}

	bool ELSE(parser::state& ps) {
		return parser::memoize(8, 
			parser::sequence({
				parser::literal("else"),
				_}))(ps);
	}

	bool OPEN(parser::state& ps) {
		return parser::memoize(9, 
			parser::sequence({
				parser::literal("("),
				_}))(ps);
	}

	bool CLOSE(parser::state& ps) {
		return parser::memoize(10, 
			parser::sequence({
				parser::literal(")"),
				_}))(ps);
	}

	bool _(parser::state& ps) {
		return parser::memoize(11, parser::memoize_many(12, 
			parser::choice({
				parser::literal(' '),
				parser::literal('\t'),
				parser::literal('\r'),
				parser::literal('\n')})))(ps);
	}

} // namespace ifstmt
