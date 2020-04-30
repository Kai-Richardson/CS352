#pragma once

/* THE FOLLOWING HAS BEEN AUTOMATICALLY GENERATED BY THE EGG PARSER GENERATOR.
 * DO NOT EDIT. */

#include <string>
#include "parser.hpp"

namespace phone {

	bool Phone(parser::state&);
	bool D(parser::state&);
	bool DDD(parser::state&);
	bool DDDD(parser::state&);

	bool Phone(parser::state& ps) {
		return parser::memoize(1, 
			parser::sequence({
				
					parser::choice({
						
							parser::sequence({
								parser::literal("("),
								DDD,
								parser::literal(") "),
								DDD,
								parser::literal('-'),
								DDDD}),
						
							parser::sequence({
								DDD,
								parser::literal('-'),
								DDD,
								parser::literal('-'),
								DDDD}),
						
							parser::sequence({
								parser::literal("+1"),
								DDD,
								DDD,
								DDDD})}),
				parser::look_not(parser::any())}))(ps);
	}

	bool D(parser::state& ps) {
		return parser::memoize(2, parser::between('0', '9'))(ps);
	}

	bool DDD(parser::state& ps) {
		return parser::memoize(3, 
			parser::sequence({
				D,
				D,
				D}))(ps);
	}

	bool DDDD(parser::state& ps) {
		return parser::memoize(4, 
			parser::sequence({
				D,
				D,
				D,
				D}))(ps);
	}

} // namespace phone
