badi
===

A bad Lisp dialect & interpreter written in C.

# Goals

* To implement a minimal version of Lisp to learn...
  - How to build simple interpreters
  - How Lisp works and can be implemented
  - To learn C (forgive me I'm very new)
* To be [fast and usable](#Usability)
* To be easy to comprehend

# Get Started

Below is a quick example of how to get started immediately with using **badi**.

*Please see [Build](#Build) for instructions on building the project for your platform.*

## Requirements

* [editline](https://github.com/troglobit/editline)

## Finally
```bash
$ git clone badi.git
$ cd badi/
$ make
$ ./bin/badi
Welcome to bad! Try (help) or (source) or (exit).
bad>
```

# Tutorial

Here's a short tutorial on all the language features. Currently there's not much!

```lisp
(+ 1 1)               -> 2
(- 20 10.5)           -> 9.5
(* (+ 2 2) 2)         -> 8
(/ 50 10)             -> 5
(dvar x 20)           -> 20
(+ 20 x)              -> 40
x                     -> 20
(> x 40)              -> 0 (false)
(+ (>= 1 1) (<= 5 5)) -> 2 (both are true, 1 if one is true, 0 if none)
```

# TODO

Here's a list of language features that are on my immediate todo list.

1. Strings and string manipulation
2. Different return options besides float (see code for details)
3. Basic set of functions (car, cdr, apply, abs, cons, min, max, null?, number?, string?, do, while, print, etc)
4. Add ability to create and load shared dynamic libraries
5. more coming soon...


# Usability

## Speed

Nothing really to see here yet. I'm just getting it working. I'll focus on optimizations once I learn more about C.

Coming soon!

## Usable

**Can we use it yet?** `KINDA`

**Is it really usable though?** `NO`

I'm defining "usable" with the following points that are required for this project.

1. Easy to install and run
2. Complete and readable documentation for the language
3. Turing complete

There are some usability concerns that are not within the scope of the current version but I hope to get to it later as I learn more...

In the future, usability will also mean being extensible in the sense that you should be able to tie in libraries that provide useful functionality (e.g networking, string manipulation, etc).

# Resources

Below is a list of resources that I've found notable while working on this
project.

* [Paul Graham On Lisp](http://www.paulgraham.com/lisp.html) (paulgraham.com)
* [Build Your Own Lisp](https://buildyourownlisp.com) by Daniel Holden (buildyourownlisp.com)
* [Lispy](https://norvig.com/lispy.html) by Peter Norvig (norvig.com)
* [Building Lisp](https://lwh.jp/lisp/) (lwh.jp)
* [Optimization of Interpreters](https://craftinginterpreters.com/optimization.html) (craftinginterpreters.com)
* [Optimizations of Programs in C](http://icps.u-strasbg.fr/~bastoul/local_copies/lee.html)
