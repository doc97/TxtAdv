# TxtAdv

TxtAdv is a framework for creating awesome text adventure games!

While the reasons for why I started this project were for me to learn more C++,
practice TDD and Agile, I am still planning on making this project a usable
product.

This project is in early development and some of the designs are still very loose. If
you'd like to help and contribute, please create a Github issue and we can talk about
your ideas.

## Features

- **Lua scripting**: Power your game by writing scripts with the easy-to-use language
[Lua](https://www.lua.org/manual/5.3/)
- **Text markup**: Write flexible text markup with support for variables and
styling

## Documentation

The API has been documented with [NaturalDocs](https://www.naturaldocs.org/)
and can be found under the `Docs/`-folder. Please download the files and open
the `index.html` file in your browser.

To build the documentation yourself, [download](https://www.naturaldocs.org/download/)
and install NaturalDocs. Add NaturalDocs to your PATH, clone this repository
and execute

```bash
C:\> NaturalDocs.exe TxtAdv\.NDConfig
```

and open the generated `index.html` file found under the TxtAdv/Docs folder.

In the future I will write documentation on how to use the framework on the
Wiki. For now, if you're interested, you can take a look at
[AdvGame.cpp](https://github.com/doc97/TxtAdv/blob/master/TxtAdv/AdvGame.cpp)
to see how the different components work together.

I also encourage you to read some of the unit tests, as they provide invaluable
examples on how the software works.

## Testing

The framework is tested with [Catch2](https://github.com/catchorg/Catch2) and
the tests can be found under the TestTxtAdv Visual Studio project.

_(06-Jan-2019)_  
**Commit:** [2af3335](https://github.com/doc97/TxtAdv/commit/2af33358a5009b9214a35d742ece8eebf1fd3bfd)  
**Tests:** 903 assertions in 128 test cases  
**Coverage:** 14 files (10 excluded)

Excluded:
- `AdvGame.cpp` (experimentation class)
- `ConsoleIO.cpp` (stdio implementation class)
- `Game.cpp` (abstract class)
- `LambdaExpression.cpp` (simple function wrapper)
- `LuaExpression.cpp` (Lua function wrapper)
- `LuaGameState.cpp` (Lua wrapper)
- `LuaManager.cpp` (Lua state will not be tested)
- `LuaStoryBranch.cpp` (Lua wrapper)
- `MetaFileReader.cpp` (tested by `TestStoryLoader`)
- `TxtFileReader.cpp` (tested by `TestStoryLoader`)

## Github Projects

Yes, I decided to try out the new Github Projects feature and I am using a
simple Kanban workflow. The project boards can found
[here](https://github.com/doc97/TxtAdv/projects).

- [Epics Board](https://github.com/doc97/TxtAdv/projects/2)
- [Current Sprint Board](https://github.com/doc97/TxtAdv/projects/4)
