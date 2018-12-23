# TxtAdv

TxtAdv is a framework for creating awesome text adventure games!

While the reasons for why I started this project is for me to learn more C++,
practice TDD and Agile, I am still planning on making this project a usable
product.

This project is in early development and the designs are still very loose. If
you'd like to help and contribute, please create a Github issue and we can talk about
your ideas.

## Features

- **Lua scripting**: Power your game by writing scripts with the easy to use language Lua
- **Text markup**: Write flexible text markup with support for variables

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

## Testing

The framework is tested with [Catch2](https://github.com/catchorg/Catch2) and
the tests can be found under the TestTxtAdv Visual Studio project.


## Github Projects

Yes, I decided to try out the new Github Projects feature and I am using a
simple Kanban workflow. The project boards can found
[here](https://github.com/doc97/TxtAdv/projects).

- [Epics Board](https://github.com/doc97/TxtAdv/projects/2)
- [Current Sprint Board](https://github.com/doc97/TxtAdv/projects/1)
