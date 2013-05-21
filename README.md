nesicide
========

Integrated Development Environment for the 8-bit Nintendo Entertainment System



# Building


## OS X

Install dependencies via [Homebrew](http://mxcl.github.io/homebrew/):

    $ brew install sdl qscintilla2 qt lua
    $ brew tap homebrew/versions
    $ brew install gcc48
    $ brew install wine --use-gcc

Now we have to hack qmake&gcc:

Create symlinks to new gcc:

Replace in `/usr/local/Cellar/qt/4.8.4/mkspecs/common/g++-macx.conf`

    QMAKE_CFLAGS_X86_64 += -Xarch_x86_64 -mmacosx-version-min=10.5

    
with 

    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.5
    

Then run:

    $ make
