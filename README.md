# Pipex

## Description

This project aims to deepen your understanding of the two concepts that you already know: Redirections and Pipes. It is an introductory project for the bigger UNIX projects that will appear later on in the cursus.

## Skills

* Unix
* Imperative programming

## Idea

The general idea: we read from infile, execute cmd1 with infile as input, send the output to cmd2, which will write to outfile.
[pipe()](https://www.geeksforgeeks.org/pipe-system-call/) sends the output of the first [execve()] (https://man7.org/linux/man-pages/man2/execve.2.html) as input to the second execve(); [fork()](https://www.geeksforgeeks.org/fork-system-call/#:~:text=Fork%20system%20call%20is%20used,the%20fork()%20system%20call.) runs two processes (i.e. two commands) in one single program; [dup2()](https://www.geeksforgeeks.org/dup-dup2-linux-system-call/) swaps our files with stdin and stdout.

```
// each cmd needs a stdin (input) and returns an output (to stdout)

infile                                             outfile
as stdin for cmd1                                 as stdout for cmd2            
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    end[1]       ↔       end[0]   -->     cmd2           
                     |                       |
            cmd1   |---------------------------|  end[0]
           output                             reads end[1]
         is written                          and sends cmd1
          to end[1]                          output to cmd2
       (end[1] becomes                      (end[0] becomes 
        cmd1 stdout)                           cmd2 stdin)
```