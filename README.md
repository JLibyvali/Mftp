# Manual

<!-- TOC -->

- [Manual](#manual)
- [Build](#build)
  - [Required](#required)
  - [Options](#options)
  - [CMake](#cmake)
- [Usage](#usage)
  - [Server](#server)
  - [Client](#client)

<!-- TOC -->

# Build

## Required
C++20, because used some template concept.
CMake 3.28, support lots of C++ 20 features.

## Options

| Macro       | Usage                                       |
| ----------- | ------------------------------------------- |
| GEN_LOGFILE | Generate log file When running the program. |

## CMake

# Usage

## Server

Mftp [subcommand] [options]

subcommand:

* user                    " ftp user configurations "
* config                  " ftp connect configurations    "

| user options               | detail                                              |
| -------------------------- | --------------------------------------------------- |
| --list [username]          | list all users information or specific user configs |
| --add [username] [passwd]  | add user account                                    |
| --del [username] [--clear] | delete a user account, clear it's files or not.     |
| --set [username] [options] | Set user's  name,passwd,home,privilege              |
| --anonymous [options]      | Anonymous users configs                             |


| config options | detail                                                 |
| -------------- | ------------------------------------------------------ |
| --space        | position of storage files                              |
| --telnet       | enable telnet connection: default ON                   |
| --database     | connect the database                                   |
| --console      | entering server manage backend                         |
| --port         | default console port, data port. default 2121 and 2222 |


options:

* -d,--dir,--directory    " ftp Server database storage path "
* --log                    " IF set Mftp will generate log file when running. Default OFF. "
* --backend               " IF set Mftp will run in the backend. Default OFF. "
* --port                  " Set ftp Server control port, default 2121 "

## Client

Support use client,browser to access FTP server. 

| client cmd            | detail                             |
| --------------------- | ---------------------------------- |
| look                  | Browse current file database       |
| w,who                 | current login account information  |
| pwd                   | current  absolute path             |
| cd  [dir]             | change current working directory   |
| touch [filename]      | create a empty file with name      |
| del [-options] [name] | delete file or directory           |
| ls                    | list all current files as list     |
| mkdir [name]          | create a directory with [name]     |
| file [-options]       | get file more information          |
| cat [file]            | print text files into stdout       |
| download [file]       | download files into client storage |
| upload [file]         | upload file to server              |
| logout                | Logout current user                |
| q,quit,exit           | Quit and close the connection      |
