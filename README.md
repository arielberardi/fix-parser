# FIX Parser

This is a practical example of a parser for FIX messages. It's not a full implementation as there is so much
more that its needed to work with a FIX engine (session, more messages, local storage, etc). 

If you need a full implementation please have a look at QuickFIX that's on References.

Note: Current average benchmark is 330k messages decode then encoded per seconds 

### References

- [FIX Trading Community](https://www.fixtrading.org/online-specification/)
- [ONIXS](https://www.onixs.biz/fix-dictionary/latest/index.html)
- [QuickFIX](https://github.com/quickfix/quickfix)

## Setup & Run

Requirement: cmake and some c++ compiler (gcc/clang, etc)

1) From root folder run: cmake -S . -B build -DCMAKE_BUILD_TYPE=Release (or Debug)
2) Then ./build/FixParser 

## Contact

For any questions or suggestions, please reach out [Ariel Berardi](https://www.linkedin.com/in/aberardi95/).
