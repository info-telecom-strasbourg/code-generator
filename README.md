# Code-Generator
Code-Generator is a tool that can be used to automate the creation of projects in C or C++. For now,
it mainly does three things:

- Automaticly creates a Makefile for the current directory containing the project

- Allows the user to load templates that already have basic files with the usual
	libraries included and a working Makefile

- Allows the user to add a new couple of files (test.c and test.h for exemple) with
	usual libraries included and inclusion guards for the .h

## Installation

Here is the list of commands to install codegen:

```
git clone X
```

Then, place the cloned directory where you want it to be. After this, you need to set
the path of codegen; you can do this by going in the directory of codegen and type: 

```
bash set_path.sh
```

Finaly, codegen uses scripts in order to work; meaning you need to give permissions
to those scripts so they can be accessed by codegen. You can do this with the command:

```
chmod 755 ./scripts/*.sh
```

You can now compile codegen and add it to PATH by doing:

```
make
sudo make move_to_bin
```

## The Options

### Option -t

This option means template, so it is specialy usefull in an empty directory.
Imagine you are starting a function called foo.c. You create a directory called
foo and then you can just run ```codegen -t c```. 
This is what the previously empty directory looks like now:

```
codegen_config.txt  foo.c  Makefile
```

Codegen built the Makefile automaticly so now I can compile foo.c with ```make``` directly.
The file foo.c looks like this:

```c
#include <stdio.h>
#include <stdlib.h>

//int main (int argc, char **argv) {

int main (void) {

	return 0;
}
```

This is a standard main file (smf) and can be modified if you change the file smf.c
under ```/user/templates/smf.c``` 


The file codegen_config.txt is very important because it is what codegen
will parse to find out what you directory structure is. For our previous
exemple, the file could look like this:

```
Source = .
Extensions = c/h
Include = .
Object = .
Bin = .
Name = foo
```

You can see that Source, Include, Object and Bin are directories. Here they are
set to the current directory but if they were not, every directory you add to
codegen_config.txt will be created (for exemple Source = ```./src/``` will
create ```./src``` and update the Makefile so it builds with source files inside
of ```./src```)

Extensions is the extensions of you files. Codegen supports c, cc, cpp, h and hpp.

Name is the name of the binary that you can execute after ```make``` is called.

By default they are 4 default templates:
- c : for a single c file
- c++ : for a single c++ file
- c_proj : for a project in c (adds source folders, include folders ect...)
- c++_proj : for a project in c++ (adds source folders, include folders ect...)

But you can add more if you want. This is how:

### Option -t : set templates

In reality, the configuration file of our folder ```foo``` created with option -t,
is not exactly like I say it would look like. In reality this is what the configuration
file looks like:

```
Source = ${ echo $(basename $PWD).c }
Extensions = c/h
Include = .
Object = .
Bin = .
Name = ${ echo $(basename $PWD) }
```

This is because, under ```user/templates/``` there is a folder called ```c``` and
it contains this exact ```codegen_config.txt```. When you call ```codegen -t [OPT]```
codgen will go through ```user/templates``` and search for a directory called ```[OPT]```.
When found, everything that is inside is copied into the directory from where codegen was
called and the makefile is built.

Source is defined as ```${ echo $(basename $PWD).c }``` so codegen adds the file foo.c
because the directory we were in was called foo.
**This means that everything you write inside ```${ ... }``` will be excuted as ```bash```.**

You might be surprised to see that Source = ./foo.c is a file a,d not a directory. In reality, 
codegen will only add . to the Makefile but adding /foo.c will indicate codegen that you want
this file to also be created.

If you want to add your own template under /user/templates, it is useful to use ```${ }```
so you can call the folder you create with names linked to the current directory they are
being created in.

### Option -m: building the makefile

```codegen -m``` is executed right after you call ```codegen -t c```, so the makefile can
be built. Indeed, this option will look at codegen_config.txt and create the Makefile that
will work for that configuration. **If no codegen_config.txt file exists, it will attempt to**
**automaticly build a working makefile**

Take this C exercice for exemple. The directory looks like this:

```
chiffrement  chiffrement.c  desc.html  desc.md  fonctions.sh  p  test-0  test-1  test-2  test.cfg  test.log  test.sh
```

When you use ```codegen -m``` this is the output:

```
Using current directory by default
Using target "chiffrement" by default.

Successfully created/updated codegen_config.txt !
Be aware that this is can be a guess on what the current directory structure is.
 
			Source = .
 			Include = .
 			Source extensions = c
 			Include extensions = h
 			Object = .
 			Bin = .
 			Name = chiffrement
 

info: Successfully created the Makefile !
```

This means that you can now use ```make``` to compile the exercice.
**Be aware that the default makefile has Werror flags. You can change that by changing the default**
**makefile of codegen in /user/makefile/**

### Option -a: adding new files

This is the most basic option. Often in C/C++ projects you need to add a couple of files like
foo.c and foo.h. This option allows you to that automaticly and fills the files with some
standard data (you can change this under /user/standard_files/sf.c -- sf means standard files).

For exemple, for ```codegen -a foo``` you get the following files:

```c
#include <stdio.h>
#include <stdlib.h>


```
for foo.c

```c
#ifndef FOO_H
#define FOO_H
 
#endif
```
for foo.h