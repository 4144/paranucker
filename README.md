# Ast Dumper - static code analyser for C/C++

This is [gcc](https://gcc.gnu.org) plugin for dump [AST](https://en.wikipedia.org/wiki/Abstract_syntax_tree) tree and search possible null pointers.

Version 1.0       Date: 2015-06-22

## Build deps
 - gcc 5 with plugin includes. (gcc-5-plugin)
   For older gcc build possible, but need change make file.
 - automake/autoconf.

## Run time deps
 - gcc 5 / g++ 5 or older.

## Features
 - Dump AST tree from gcc.
 - Search missing basic null pointer checks for function input parameters.
 - Dont check parameters with attribute [NONNULL](https://gcc.gnu.org/onlinedocs/gcc-5.1.0/gcc/Function-Attributes.html#index-g_t_0040code_007bnonnull_007d-function-attribute-3189).
 - In future probably other checks...

## Build
 - Run build.sh
 - You will get astdumper.so for gcc binary
   and cppastdumper.so for g++ binary

## Usage examples
In directory [examples](examples) present two examples one for C++ and other for C.

## Real world usage examples
 - [ManaPlus](http://manaplus.org/)
 - [Hercules](http://herc.ws/)

## Advanced usage
Ast Dumper support one plugin paramater named -fplugin-arg-astdumper-command or -fplugin-arg-cppastdumper-command depend what you using C or C++

Example:
  gcc-5 -fplugin=../astdumper.so -fplugin-arg-astdumper-command=detectnullpointers


Known parameter values:

| name               | action                                                |
|:-------------------|:------------------------------------------------------|
| parse              | silently parse AST                                    |
| dump               | dump whole AST                                        |
| smalldump          | small AST dump without indention                      |
| memoryusage        | show how many nodes parsed                            |
| dumpunsupported    | dump nodes what cant be parsed                        |
| findargs           | dump functions and argument names what can be checked |
| detectnullpointers | search null pointers                                  |
| dumpnullpointers   | search null pointers and dump some debug info         |

Readme on russian [README.ru.md](README.ru.md)
