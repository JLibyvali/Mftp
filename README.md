# Manual
# Server
Mftp [subcommand] [options]  
subcommand:  
    user                    " ftp user related configs "
    config                  " ftp configurations    "
    port                    " ftp control port, default 2121 "
options:
    -d,--dir,--directory    "ftp server storage path "
    --log                    "ftp output a log files  "
    --backend               "ftp server run in backend "

| config options |          detail                |
| ---      | ---  |
| space    | position of storage files            |
| telnet   | enable telnet connection: default ON |
| database | connect the database                 |
| console  | entering server manage backend       |
| port     | default console port, data port. default 2121 and 2222 |

| user options |                detail                                       |
| ---           |   ---                                                      |
| list [username] |  list all users information or specific user configs     |
| add [username] [passwd] | add user account                                 |
| del [username] [--clear] | delete a user account, clear it's files or not. |
| set [username] [options] | Set user's  name,passwd,home,privilege          |
| anonymous [options]      | Anonymous users configs                         |


# Client
can use client,browser,or client program to access server  

| client cmd |         detail                      |
|   ---      |  ---                                |
|   look     | Browse current file database        |
|   w,who    | current login account information   |
|  pwd       | current  absolute path              |
|  cd  [dir] | change current working directory    |
| touch [filename] | create a empty file with name |
| del [-options] [name] | delete file or directory |
|   ls       | list all current files as list      |
| mkdir [name] | create a directory with [name]    | 
| file [-options] | get file more information      |
| cat [file] |     print text files into stdout    |
| download [file] | download files into client storage|
| upload [file] |  upload file to server           | 
| logout     |      Logout current user            |
| q,quit,exit|  Quit and close the connection      |
