#include "parser_array.hpp"
#include <cstring>
#include <iostream>

namespace json_parse {

Parser::ParseResult ParserArray::parse(InputStream& is) {
	char c = is.get();
	switch (c) {
		case ']':
			return ParseResult::Done;
		case '[':
			// check for empty array
			skipws(is);
			if (is.peek() == ']') {
				is.get();
				return ParseResult::Done;
			}
			return ParseResult::NextState;
		case ',':
			return ParseResult::NextState;
		default:
			return ParseResult::Error;
	}
}

Json ParserArray::finish() {
	return Json { std::move(array) };
}

void ParserArray::process_item(Json&& json) {
	array.emplace_back(std::unique_ptr<Json> { new Json { std::move(json) } });
}

}
