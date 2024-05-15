#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

//Action to take!
# define SHIFT_TO_STACK		0
# define REDUCE_STACK		1
# define ACCEPT				2
# define REJECT				3


# define LINES				100
# define BISON_AUTOMATON	"./syntax_analysis/parsing_table"

typedef struct s_stack
{
	int type;
	int state;
	int quote;
	void *data;
	struct s_stack *next;
}				t_stack;

typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*next;
	void			*data;
	int				type;
	int				reduc;
	int				qt_rm;
}				t_tree;

typedef struct s_table
{
	int	action;
	int state;
	int token_type;
	int	next_state;
	int nb_reduce;
}				t_table;

typedef enum e_token_types
{
	T_END = -2,
	T_WORD = 0,
	T_RED_TO,
	T_RED_FROM,
	T_DLESS,
	T_DGREAT,
	T_PIPE
}	t_ttypes;

typedef struct s_sdQuote
{
	int	single_q;
	int	double_q;
	int	type;
}				t_sdQuote;

typedef struct s_token
{
	int				quote;
	int				type;
	void			*value;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*name;
	char			*content;
	int				if_env;
	struct s_env	*next;
}					t_env;

extern t_env	*g_envp;

typedef struct s_cd
{
	char	*ar;
	char	*code;

}	t_cd;

//Lexical!
t_token *ft_lexer(char *line);
t_token	*ft_newtoken(void *content, int c);
void	ft_tokenadd_back(t_token **lst, t_token *new);
t_ttypes	catego_toketype(char *content, int c);
t_token *token_creation(int token_len, char *line, char *exit, int *q);
int	check_env(char *str, char *exit, char *new, int *i, int *i_new);
char    *token_str(int token_len, char *line);

int replace_quote(char *str, char *exit, char *new, int *i, int *i_new);
int sq_dollar(char *str, char sq);
int replace_double(char *str, char *exit, char *new, int *i_new, int a, int i, int quote_type);
int check_envvar(char *str, char *exit, char *new, int *i_new, int a, int i, int quote_type);
int replace_var(char *str, char *exit, int index, char *new, int *i_new);
int replace_var_2(char *new, char *newstr, int *i_new, int len);
int envvar_len(char *str);
int strchr_check(char *str, int temp, int i, char sd);
int check_ds(char *str, int a, int i);
int check_quote(int *i, char *str);
int quote_count(int *i, char *str, t_sdQuote *quote);
int quote_type(t_sdQuote *quote);

void    init_sdQuote(t_sdQuote *q);
int sep_to_sep_len(char *line, t_sdQuote *sdQ);
int check_sep(char c);
int tok_sep_len(char *line, int i);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_itoa(int n);
int	ft_digits(int n);
char	*ft_strdup(const char *s1);
int	ft_strlen(const char *s);
int	ft_isdigit(int c);
int	ft_isalnum(int c);
char	*ft_getenv(char *var);

//syntactical!
int	ms_add_tree(t_tree **tree, t_stack **popped, int reduction);
int	ms_build_tree(t_tree **tree, t_tree *reduc_node, t_stack **popped);
t_tree	*ms_add_reduction_front(t_tree **tree, int reduction);
t_tree	*ms_search_reduction(t_tree **tree, int reduction);
void	ms_remove_node_from_list(t_tree **tree, t_tree *node);
t_tree	*ms_stack_to_node(t_stack *popped);

t_tree	*syntax_analysis(t_token *token, t_table **parsing_table);
t_tree	*ms_fix_param_types(t_tree *tree);
static void	ms_visit_fix_types(t_tree *node);
int	reject(void);
int	accept(void);
t_table *getEntry(t_token *token, t_table **parsing_table, t_stack *stack);

t_stack *init_stack();
int	shift_to_stack(t_table *table_entry, t_stack **stack, t_token *token);
int	change_stack_state(int next_state, t_stack **stack);
int	reduce_stack(t_table *table_entry, t_tree **tree, t_stack **stack, t_table **pt);
int	pro_red_next_state(t_stack *stack, t_table **parsing_table);
int	push_reducted(t_stack **stack, int next);
t_stack	*pop_oper(t_stack **stack, int reduce);
void	pop_check(t_stack **red, t_stack *stack);

// t_table	**ft_init_parsing_table(void);
// int	ft_create_table_state(int fd, t_table **table);
// static int	free_line_args(char *line, char **args, int code);
// t_table	*ft_add_table_line(char **arg_line);

t_table	**ms_init_parsing_table(void);
int	ms_create_all_transitions(int fd, t_table **trans);
void	ms_free_table(t_table **trans);
static t_table	*ms_new_transition(char **args);
static int	ms_free_line_args(char *line, char **args, int code);

int ft_get_next_line(int fd, char **line, int code);

char	**ft_split(const char *s, char c);
char	**ft_free(char **split_array);
static size_t	ft_slen(const char *s, char c);
int	ft_atoi(const char *str);
char	*ft_substr(char const *s, int start, size_t len);
void	*ft_calloc(size_t count, size_t size);

#endif