# Typing Practice Tool

## REQUIREMENTS

Install [ncurses](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/)!

## Build

1. Locate into `src` directory
```
cd src
```

2. Clean previous builds
```
make clean
```

3. Build the project
```
make
```

Executable file is available on `./src/bin/typing`

## Usage

(These examples supose you appended `src/bin` to PATH)

Run with.
```
typing filename
```

For now, only text files are supported.

## Moving around the document

I am used to vim motions, so this project tries to imitate them.

Use `Esc` to enter normal mode, and `i`, `a` or `o` to enter insert mode, insert mode is set when you first run the program.

While in normal mode, you can move around the document using the keyboard arrows or `hjkl` if you are familiar with vim.
