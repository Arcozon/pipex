Almost a perfect Pipex.
Variable, single and double quote expansion for commands
Single and double quote expansion for heredoc limiter
NoMalloc, NoTmpFile heredoc for no expansion
One malloc for heredoc expantion (maxlen(varname) inside the heredoc, should be min(maxlen(varname in heredoc), maxlen(varname in env)), but 2 pipes :(
Only one malloc per arg for cmds
Finding the exe might be in child process
Opening and creation of infile SHOULD be in childs (didnt do :( )
Could only do one malloc to find the exe (Maxlen(path) + len(exe_name) + 2) (puting "/exe_name\0" at the end and copying the path next to that could be fun, but would need to keep a copy of the allocated address) Bad error managment for errdoc (pipe error, read write error, malloc error are the same error code)
Poor readability on the 2nd part of cmd expansion
Cmd and heredoc expansion could use a struct
