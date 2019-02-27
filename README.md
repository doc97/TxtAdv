# TxtAdv

**The project development has halted for now due to me concentrating on my
studies. I plan on continuing this project once I have more time.**

TxtAdv is a framework for creating awesome text adventure games!

While the reasons for why I started this project were for me to learn more C++,
practice TDD and Agile, I am still planning on making this project a usable
product.

This project is in early development and some of the designs are still very
loose. If you'd like to help and contribute, please create a Github issue and
we can talk about your ideas.

## Features

- **Lua scripting**: Power your game by writing scripts with the easy-to-use
language [Lua](https://www.lua.org/manual/5.3/)
- **Text markup**: Write flexible text markup with support for variables and
styling

## Documentation

Usage instructions can now be found on the [Wiki](https://github.com/doc97/TxtAdv/wiki).
Note that the documentation lives and may change over time as I add new features
and change existing ones.

The API has been documented with [NaturalDocs](https://www.naturaldocs.org/)
and can be found under the `Docs/`-folder. Please download the files and open
the `index.html` file in your browser.

**Last generated:** 15-Jan-2019

To build the documentation yourself, [download](https://www.naturaldocs.org/download/)
and install NaturalDocs. Add NaturalDocs to your PATH, clone this repository
and execute

```bash
C:\> NaturalDocs.exe TxtAdv\.NDConfig
```

and open the generated `index.html` file found under the TxtAdv/Docs folder.

**Extra**  
I also encourage you to read some of the unit tests, as they provide invaluable
examples on how the software works.

## Testing

The framework is tested with [Catch2](https://github.com/catchorg/Catch2) and
the tests can be found under the TestTxtAdv Visual Studio project.

_(15-Jan-2019)_  
**Commit:** [8b3526a](https://github.com/doc97/TxtAdv/commit/8b3526a9598ab0cfc8288bf3c8405e277e4636df)  
**Tests:** 958 assertions in 150 test cases  
**Coverage:** 19 test files (8 excluded)

Excluded:
- `AdvGame.cpp` (experimentation class)
- `ConsoleIO.cpp` (stdio implementation class)
- `Game.cpp` (abstract class)
- `LambdaExpression.cpp` (simple function wrapper)
- `LuaExpression.cpp` (Lua function wrapper)
- `LuaGameState.cpp` (Lua wrapper)
- `LuaManager.cpp` (Lua state will not be tested)
- `LuaStoryBranch.cpp` (Lua wrapper)

## Github Projects

Yes, I decided to try out the new Github Projects feature and I am using a
simple Kanban workflow. The project boards can found
[here](https://github.com/doc97/TxtAdv/projects).

- [Epics Board](https://github.com/doc97/TxtAdv/projects/2)
- [Current Sprint Board](https://github.com/doc97/TxtAdv/projects/5) (out-of-date)
