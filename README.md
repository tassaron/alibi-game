# Alibi
An interactive fiction in which you're accused of a crime and have to devise an alibi. Will your story be good enough to keep you out of jail?

**CURRENTLY UNFINISHED**
I uploaded this because I haven't touched it in a while. The game isn't finished, but I kept the scope small to make it completable so I'll definitely finish it soon!

# Installation
1. Install `gcc`, `aclocal`, `autoconf`, `automake`
1. Run `autogen.sh` to create the configure script
1. Run `./configure` to create the makefile
1. Run `make` to create the `alibi-game` binary (the game itself)
1. _Optional:_ Run `make install` (to put `alibi-game` in $PATH so you can run it from anywhere)

# Development
* If you have files leftover from a previous invokation of `autogen.sh`:
  * Use `autogen.sh clean` to delete build files before regenerating
  * Use `autogen.sh clean-only` to _just_ clean leftover files without regenerating

# Questions
## Why not make this game with Inform or TADS?
This game would be more portable, easier to make, and probably better in every way had I made it with Inform or TADS. However, the only reason I started this project was for the sake of familarizing myself with basic C++. So that's what I'm using.

## Did you choose to exclude *x* command from Inform/TADS or just forgot it?
I chose to exclude some standard verbs that would have no use in "Alibi" and aren't likely to be noticed. If you want to add a new verb to the game, please feel free to submit a pull request or make a new issue on Github with your suggestion.

## Are these real questions?
No, of course not. In fact, you're the first person to ever find this repo and read this far into the readme. Congratulations!
