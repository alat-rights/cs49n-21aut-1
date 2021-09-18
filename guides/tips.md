# My development tips and tricks

## Tool recommendations

These tools are not installed by default, but I find them very useful and worth
installing.

* `fd`: for finding files. Usage: `fd FILE`, recursively searches for files
  with the given name in the current directory. Also useful: `fd -g FILE` to
  search with globs.

* `exa`: a better version of `ls`. Reduces the clutter and displays
  human-readable file sizes. Drop-in replacement (mostly), so I just
  `alias ls=exa` in my `.bashrc`.

* `rg`: for searching for strings within files. Usage: `rg PATTERN`,
  recursively searches all files starting from the current directory for the
  given pattern.

* `ag`: alternative to `rg`, does the same thing.

* `clang-format`: automatically formats C code. Usage: run `clang-format -i
  *.c` to autoformat in-place all the C files in the current directory. I don't
  like the default formatting, so I customize it by creating a `.clang-format` file
  in the current directory that contains `{BasedOnStyle: Chromium, IndentWidth:
  4, SpaceAfterCStyleCast: true}` (this is my preferred style).

## `cd -`

The command `cd -` will bring you to the previous directory you were in most
recently. This is useful if you need to switch back and forth between two
places or you accidentally change to another directory and want to go back.

```
~/cs49n-21aut/docs$ cd ../labs/1-gpio
~/cs49n-21aut/labs/1-gpio$ cd -
~/cs49n-21aut/docs$ cd -
~/cs49n-21aut/labs/1-gpio$
```

## Open

You should try to do almost everything in the shell. However, there are cases
where opening GUI application is useful (opening PDF files, using a file
browser in certain cases, opening an html file with a browser, etc.). On MacOS,
the `open` command will open a file as if you had double clicked it in the
Finder.

```
~$ open example.pdf
[Preview window opens with example.pdf]
~$ open .
[Finder window opens in the current directory]
~$ open example.html
[Browser opens pointed to the local file example.html]
```

This is extremely useful as it allows you to conveniently reach to graphical
applications from the shell if you need to do so.

On Linux, you can get similar behavior with the command
`xdg-open`. Sometimes it generates some bogus messages on
stderr, so I alias `open` to the following on Linux:

```
alias open='xdg-open 2>/dev/null'
```

## Window swapping

Swapping between multiple windows is constantly necessary. Usually I have
multiple terminal windows containing code, a browser window, and possibly a PDF
viewer open while coding. There are two useful keybindings for managing these
windows:

* Alt-tab (Command-tab on MacOS): switch between most recently used
  applications.
* Alt-\` (Command-\` on MacOS): switch between most recently used windows
  within the current application.

I use Alt-tab to switch between the terminal and the browser/PDF viewer, and
Alt-\` to switch between the multiple terminal windows.

## Parallel make

If you use `make` to build large projects, you will want to use the `-jN`
option to have make use multiple cores (your computer is probably multicore).
To have `make -jN` permanently enabled with the correct core count, put the
following in `~/.bashrc`, where `N` is the number of cores on your machine (you
can try to automatically detect this, but it's easier to just know it and
hardcode it):

```
export MAKEFLAGS="-jN"
```

## Clipboard

On linux, make sure to install `xclip` so that your terminal editor can access
your system clipboard.
