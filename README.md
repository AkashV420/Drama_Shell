# An interactive user defined bash-like C-Shell

*Coded by:*
**Akash Verma**

_______________

This **README** file contains :
 1. Information About the Shell
 2. How to run
 3. List of builtin commands
 4. Features
 5. File structure

----------

## About The Shell
An interactive user defined bash-like shell which supports semi-colon separated list of commands.It can take commands in input check if a builtin exists if exists then run the builtin else run it as separate process.
The shell also supports input and output redirection along with piping of commands.

----------
## Running the program 
- make
- ./drama

#### To quit the shell
- quit OR exit 
-----------
## Builts in Commands

Command | Description | Flags | No. of Arguments
---- | ---- | ---- | ----
ls | Shows files and directory |-a,-l,-al,-la |0 or more
pwd| Shows current directory | - | -
cd| Change directory | ~ | 1 or more
echo| Print on terminal |-| 0 or more
exit|Exit terminal|-|-
pinfo|Display process Info of given process id|-|0 or 1
setenv|Can be used to set(i.e create or change) environment variable|-|1 or 2
unsetenv|Can be used to unset(remove) an environment variable|-|1
jobs|Shows  all background process with status and index|-|-
kjob|Used to send kill signal to process listed in jobs|-|2
fg|Used to bring a background process to foreground|-|1
bg|Used to make stopped background process running|-|1
overkill|Kills all the background processes|-|-
quit|Graceful exits|-|-
mkdir|Creates a new directory|-p|1 or 2

## Features
* Supports semi-colon separated commands
* Modular code structure  
* Supports input and output file redirection
* Supports background process creation when command followed by '&'.
* Prints exit message when background exits
* Supports piping of commands
* Handles Ctrl + C and Ctrl + Z signals
* Unique builtins like pinfo,jobs, kjob, overkill ,quit.

## File Structure
* drama_run : infinite loop for the shell to run.
* drama_readandsplit : consists of the read() function used by run and tokenizes the input.
* drama_check : checks wether process is background or not. 
* drama_builtin : Implements built in commands cd, echo, pwd, calls ls function and history.
* drama_ls : This implements ls command along with the flags -a, -l, &, -al, -la. 
* drama_pinfo : Implements pinfo command.
* drama_notbuiltin : Implements regular shell functions using exec.
* drama_displayprompt : Displays the prompt. 
* drama_piping : do piping. 
* drama_redirection : do redirection.
* drama_argumentize : count the args passed.
_______________

## Akash Verma
