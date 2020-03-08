#  C-Shell

**--To run the shell, enter the following commands:--**
	1. make
	2. ./drama


**DESCRIPTION** :
	1. drama_run : infinite loop for the shell to run.
	2. drama_readandsplit : consists of the read() function used  by run and tokenizes the input.
	3. drama_check : checks wether process is background or not.
	4. drama_builtin : Implements built in commands cd, echo, pwd, calls ls function and history.
	5. drama_ls : This implements ls command along with the flags -a, -l, &, -al, -la, ls <directory name>.
	6. drama_pinfo : Implements pinfo command.
	7. drama_notbuiltin : Implements regular shell functions using exec.
	8. drama_displayprompt : Displays the prompt.
    9. drama_piping : do piping.
    10.drama_redirection : do redirection
    11.drama_argumentize : count the args passed.
**COMMANDS**:
	1. cd 
	2. echo
	3. pwd
	4. ls
	5. ls -a, ls -a -l, ls -al, ls -la, ls &, ls <directory name>
	6. jobs
	7. kjob
	8. overkill
	9. sl
    10. fg
    11. bg
    12. setenv
    13. unsetenv
    14. handled ctrl-z and ctrl-c

Short-description :
    When code is executed in shell, a shell prompt similar to the following appears: <username@system_name:curr_dir>
    -> Finishes Background Processes also.

**--To Exit the command :--**
	1.quit 
	 OR
	2.exit

***********************************---- Made By AKASH VERMA ---*********************************