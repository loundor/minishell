/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfux <alexis.t.fuchs@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:05:20 by alfux             #+#    #+#             */
/*   Updated: 2022/10/06 03:27:35 by alfux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "flags_macros.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>

//-----------------------------------TOOLS--------------------------------------
//Free string tabs and return 0
int		ft_sfree(char **spl);
//Free ptr and return 0
int		ft_free(void *ptr);
//Sets errno to value and returns errno
int		ft_errno(int value);
//Print error messages
int		ft_errmsg(int errn);
//Returns size of tab;
size_t	ft_strtlen(char **tab);
//Returns a concatenation of t1 and t2
char	**ft_strtcat(char **t1, char **t2);
//Returns a new allocated duplicate of tab
char	**ft_strtdup(char **tab);
//Returns adress of pointer on variable str in tab, returns 0 if not found
char	**ft_isvarin(char *str, char **tab);
//Delete addr from tab
int		ft_strtdelone(char **addr, char ***tab);
//Copies src into dst, but with strings tabs (uses strdups)
int		ft_strtlcpy(char **dst, char **src, int dstsize);
//Return a copy of a sub-stringtab
char	**ft_substrt(char **strt, int start, int len);
//Sends sig to all pids
int		ft_killall(pid_t *pid, int sig);
//Waits all processes, only one if pid=NULL, and stores the first exit_status
pid_t	ft_waitall(pid_t *pid, int *exit_status, int opt);
//------------------------------------------------------------------------------
//-------------------------------BONUS------------------------------------------
//Returns 2 if parenthesis, 1 if token, 0 otherwise
int		ft_istokn(char *c);
//Returns the first index after a ')' token in a string tab
int		ft_skppar(char **strt, int start);
//Returns the first index after a group of characters between quotes
size_t	ft_skpqts(char *str, size_t start);
//Returns the first index after a group of spaces
size_t	ft_skpspc(char *str, size_t start);
//Sets integer to value and returns value
int		ft_setint(int *integer, int value);
//Returns 1 is file is a directory, 0 if it is not, -1 on error and sets errno
int		ft_isdir(char const *file);
//------------------------------------------------------------------------------

//-------------------------------MINISHELL--------------------------------------
//Get new pwd (allocate memory)
char	*ft_newpwd(void);
//Returns standard input (allocate memory)
char	*ft_prompt(char **ev, char ***his);
//Split the prompted command line according to (d)quotes
char	**ft_cmdspl(char *pmt);
//Parse	the split command line to remove (d)quotes and replaces variables ($)
int		ft_root_parse(char **cmd, char **ev, char **var);
//Execute the parsed command line
int		ft_execute(char **av, char ***ev, char ***var);
//Search the builtins to match command line (récup ft_isntvar)
int		ft_isbuiltin(char **cmd, char ***ev, char ***var);
//Initialize var to contain at least "$?" for last process exit status
char	**ft_init_var(void);
//Returns the environnement variables and sets var and his
char	**ft_setenv(char **ev, char ***var, char ***his);
//Returns non zero if cmd has another command than variable affectation
int		ft_isntvar(char **cmd);
//Add the last typed command line to history and his tab
int		ft_addhis(char *pmt, char ***his);
//Saves history in a file
int		ft_savhis(char *path, char *fname, char **his);
//Adds history stored in fname file
int		ft_gethis(char *path, char *fname);
//Tries to start external binaries, returns non-zero if an error occurs
pid_t	ft_isextern(char **av, char **ev, pid_t (*e)(char *, char **, char **));
//Forks a child to hold the call to execve, parent process gets pid
pid_t	ft_newpro(char *path, char **av, char **ev);
//Make forks linked by pipes, returns null in parent and each cmd in childs
char	**ft_pipmkr(char **av, pid_t **pid);//RETHINK ARCHITECTURE OF THIS
//Returns a string for new exit status $="" and frees previous one
char	*ft_extsta(int exit_status, char *prev_status);
//Redirects output or input according to > >> and < <<
int		ft_redio(char **av, char **ev, char **var);
//SAVE_IO saves tty's stdin stdout, RESET_IO, RESET_IN to reset, CLOSE_IO closes
int		ft_stdio(int flag);
//Change behavior of SIGINT/SIGQUIT according to flag for the calling process
int		ft_sighdl(int flag);
//SIGINT handler for minishell in interactive mode, show new prompt
void	ft_newpmt(int sig);
//Show signal termination message. If signal is SIGINT, only shows \n
void	ft_sigmsg(int first_status, int exit_status);
//Terminate minishell, saving or not history and freeing memory
void	ft_exit(char **ev, char **var, char **his);
//---------------------------------BONUS----------------------------------------
//Tokenize the prompted command line
char	**ft_tknize(char *pmt);
//Macro execution for &&, || and parenthesis
int		ft_macro_exec(char **av, char ***ev, char ***var);
//Exit toggle
int		ft_exit_toggle(int toggle, char *ex_sav, int *ex_get);
//Frees and removes outer border elements from av, shifts all and returns it
char	**ft_remout(char **av);
//SAVE_IO saves current stdin and stdout, RESET_IO resets, CLOSE_IO closes
int		ft_setio(int flag);
//Returns 1 if syntax is incorrect, 0 otherwise
int		ft_syntax_err(char **tkn);
//Returns a list of parsed wildcard tokens
t_list	*ft_wldprep(char *pattern, char **ev, char **var);
//Skips tkn in lst, returns the first one who isn't tkn
t_list	*ft_skptkn(t_list *lst, char const *tkn);
//Searches for match, lets match to NULL if no match, return 1 on error, or 0
int		ft_search(char *schdir, t_list *tkn, t_list **match);
//Returns a list of match according to list tkn
t_list	*ft_match(t_list *tkn);
//Swaps av with a new parsed av, returns 0 on success and 1 on failure
int		ft_parse(char ***av, char **ev, char ***var);
//Called before parsing to remove or do variable affectations
int		ft_remaff(char **av, char **ev, char ***var);
//Expands every "$pattern" if it exists in env or var, str must be allocated
int		ft_expvar(char **str, char **ev, char **var);
//Removes every quotes in str, str must be allocated
int		ft_remqts(char **str);
//Compare beginning of candidate with cleared of quotes token
int		ft_cndcmp(char **cnd, t_list *tkn);
//Searches for cleared of quotes token in candidate
int		ft_cndstr(char **cnd, t_list *tkn);
//Reorder lst in lexicographical order
t_list	*ft_lexord(t_list *lst);
//------------------------------------------------------------------------------

//---------------------------------BUILTINS-------------------------------------
//Builtin echo with -n option
int		ft_echo(char **av);
//Buildin cd
int		ft_cd(char **av, char ***ev, char **var);
//Look into CDPATH if cd fails
int		ft_cdpath(char *path, char **ev, char **var);
//Builtin pwd without option
int		ft_pwd(int err);
//Builtin env without option or argument
int		ft_env(char **ev);
//Builtin exit without option
int		ft_exicmd(char **av, char *last_status);
//Builtin variable affectation
int		ft_setvar(char **av, char **ev, char ***var);
//Builtin export without option
int		ft_export(char **av, char ***ev, char ***var);//Rework for lists
//Builtin unset without option
int		ft_unset(char **av, char ***ev, char ***var);
//------------------------------------------------------------------------------

//----------------------------------DEBUG---------------------------------------
void	ft_trace(char *file, char **av);
//------------------------------------------------------------------------------
#endif
