## Feature Wishlist ##
- add &{ ... } semantic predicates to the language
- add ~{ ... } failure actions to the language
- Add cut syntax
- Rewrite compiler to have a code generator again, rather than just using the combinators (investigate performance)
- Unicode string support
  - Include Unicode escapes for character literals
  - Normalize input Unicode
- Add interpreter visitor (this may be non-trivial)
- Add doxygen-generated docs to the docs folder
- Install to system path
- Better escaping for character classes; also perhaps support for semantic tests, e.g. whitespace

## Bugs ##
- Cannot include ']' in a character class - should include an escape.
- Non-syntactic '{' and '}' characters in actions (e.g. those in comments or string literals) may break the parser if unmatched.
- Parens in grammar pretty-printer are not entirely correct
- Actions that modify psVal rather than assigning to it may behave differently under memoization than not
- Should modify "many" and "some" combinators to break their loop on empty match (i.e. silently treat the language matched by their subexpression e as _L(e) \ epsilon_)

## Code Cleanup ##
- Maybe move to `unique_ptr` from `shared_ptr`
- Replace `ast::make_ptr()` and `ast::as_ptr()` with standard library equivalents
- Inline parse.hpp in generated grammars
  - This may have licencing ramifications - consider a Bison-style exception
- Modify makefile to remake `egg.hpp` from `egg.egg` or `egg-bak.hpp` as appropriate
- Move redundant checks from compiler to normalizer
- Rewrite normalizer to flatten nested sequences/choices (might fail for sequences if you re-introduce psStart)
- Add flag to make "#pragma once" optional in generated files
- Rewrite `parser::state.matches(string)` to use the deque iterators instead of generating a second string object
- Maybe make Egg-based argument parsing grammar (might be more work to make input stream that inputs (argc, argv) than it's worth)
- 1-index line numbers
- add hash table to consolidate memoization entries for identical '*' and '+' grammars