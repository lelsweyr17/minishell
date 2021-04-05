#include "minishell.h"

void    echo_command(t_command *com, char **envp)
{
    int i;
    int j;
    int len;
    char *s;

    i = 0;
    if (com->quote)
        write(1, com->arg, ft_strlen(com->arg));
    else
        while (com->arg[i])
        {
            while (com->arg[i] != '$' && com->arg[i])
                write(1, &com->arg[i++], 1);
            if (com->arg[i] == '$')
            {
                if (com->arg[++i] == '?')
                    ft_putnbr_fd(com->error, 1);
                j = -1;
                len = 0;
                while (com->arg[i + len] != ' ' && com->arg[i + len] && com->arg[i + len] != '$' && com->arg[i + len] != '\n')
                    len++;
                s = ft_substr(com->arg, i, len + 1);
                s[len++] = '=';
                while (envp[++j])
                    if (!ft_strncmp(s, envp[j], len))
                        break;
                if (envp[j])
                    write(1, envp[j] + len, ft_strlen(envp[j]) - len);
                i += len - 1;
            }
        }
    write(1, "\n", 1);
}

void    pwd_command(t_command *com)
{
    char *a;

    a = NULL;
    a = getcwd(a, 0);
    write(1, a, ft_strlen(a));
    write(1, "\n", 1);
    // free(a);
}

void    cd_command(t_command *com, char **envp)
{
    chdir(com->arg);
    if (errno != 0)
    {
        write(1, "cd: ", 4);
        write(1, com->arg, ft_strlen(com->arg));
        write(1, ": ", 2);
        write(1, strerror(errno), ft_strlen(strerror(errno)));
        write(1, "\n", 1);
    }
}

void    exp_command(t_command *com, char **envp)
{
    
}

void    commands(t_command *com, char **envp)
{
    if (com->echo)
        echo_command(com, envp);
    else if (com->cd)
        cd_command(com, envp);
    else if (com->pwd)
        pwd_command(com);
    else if (com->exp)
        exp_command(com, envp);
    // else if (com->unset)
    //     ...;
    // else if (com->env)
    //     ...;
    // else if (com->exit)
    //     ...;
}

int main(int argc, char **argv, char **envp)
{
    t_command *com;
    // int i;

    // i = 0;
    // while (envp[i])
    //     printf("%s\n", envp[i++]);
    com = (t_command *)calloc(1, sizeof(t_command));
    // com->quote = 1;
    com->echo = 1;
    com->arg = "$LOGNAME  |  $LANG";
    // com->arg = "/Users/111";
    // com->cd = 1;
    commands(com, envp);
    // com->cd = 0;
    // com->pwd = 1;
    // commands(com, envp);
}