# Minishell
**As beautiful as a shell**

This project is a custom implementation of a lightweight shell, mimicking the core functionalities of bash. Built from scratch in C, it focuses on deep system-level programming, including process creation , file descriptor management, parsing, and signal handling. The architecture was designed with a highly logical, modular approach to guarantee complete memory safety, and strictly adhere to the 42 Norminette standard.

## CORE FEATURES
- **`Command Execution`**: Resolves and executes external commands via absolute paths, relative paths, or the system PATH environment variable.

- **`Parsing and Quotes`**: Robust handling of single and double quotes, ensuring literal interpretations where necessary and allowing for proper environment variable expansion.

- **`Pipes`**: Chaining of commands, successfully managing multiple piped child processes without file descriptor or memory leaks.

- **`Redirections`**: Full support for standard input, standard output, append mode, and heredocs.

- **`Environment Variables`**: Expands system environment variables and properly handles exit status variables.

- **`Signal Handling`**: Accurately replicates bash behavior for interrupt and quit signals across interactive mode, child processes, and heredocs.

## BUILTIN COMMANDS
- `echo` with -n flag support
- `cd` relative and absolute path support
- `pwd` without options
- `export` without options
- `unset` without options
- `env` without options or arguments
- `exit` with numeric exit code support

## INSTALLATION AND USAGE
**`Prerequisites`**: Requires a C compiler (GCC/Clang), Make, and the standard readline library.

**`Compilation`**: Run the make command at the root of the repository to build the executable. Other standard rules include make clean, make fclean, and make re.
Running the Shell: Start the program by executing `./minishell` in your terminal. You will be greeted by the custom prompt and can begin entering standard shell commands.

## RESOURCES FOR FURTHER STUDY
If you are interested in building your own shell or diving deeper into Unix system programming, here are some highly recommended resources:

- [The Essential Linux Man Pages](https://man7.org/linux/man-pages/)
- [Minishell: Building a mini-bash](https://medium.com/@zouhairlrs/minishell-building-a-mini-bash-a-42-project-5dc20d671fbb)
- [
Communicating between processes (using pipes) in C](https://www.youtube.com/watch?v=Mqb2dVRe0uo&t=435s)

## AUTHORS
[wiboonpr (New)](https://github.com/Wirayabovorn007)

[pphuntph (Modtanoy)](https://github.com/Modey-Codey)

## ACKNOWLEDGMENTS
Developed as part of the core software engineering curriculum at 42 Bangkok.