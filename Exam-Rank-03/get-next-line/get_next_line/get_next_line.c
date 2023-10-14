#include "get_next_line.h"

int ft_strlen(char *line)
{
    int i = 0;

    if(!line)
        return(0);
    while(line[i])
        i++;
    return(i);
}

int ft_nl_find(char *str)
{
    int i = 0;

    if(!str)
        return(-1);
    while(str[i])
    {
        if(str[i] == '\n')
            return(i);
        i++;
    }
    return(-1);
}

char *ft_substr(char *line, int start, int n)
{
    int i = 0;
    char *final = malloc(sizeof(char *) * (n - start) + 1);

    if(!line)
        return(NULL);
    while(n > 0 && line[start + i])
    {
        final[i] = line[start + i];
        n--;
        i++;
    }
    final[i] = '\0';
    return(final);
}

char *ft_strjoin(char *line, char *str)
{
    int i = 0;
    int j = 0;
    char *final = malloc(sizeof(char *) * (ft_strlen(line) + ft_strlen(str)) + 1);

    if(!str)
        return(NULL);
    if(line)
    {
        while(line[i])
        {
            final[i] = line[i];
            i++;
        }
    }
    while(str[j])
    {
        final[i + j] = str[j];
        j++;
    }
    final[i + j] = '\0';
    return(final);
}

char *ft_clean_buffer(char *buffer)
{
    char *new_buffer;

    new_buffer = ft_substr(buffer, ft_nl_find(buffer) + 1, __INT_MAX__);
    // printf("\n\033[32m-%s-|\033[0m\n", buffer);
    // printf("\n\033[31m-%s-|\033[0m\n", new_buffer);
    free(buffer);
    return(new_buffer);
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *final = 0;
    // static int i = 0;

    // printf("\n%d\n", i++);
    if(fd <= 0 || BUFFER_SIZE <= 0)
        return(NULL);
    if(buffer == 0)
        buffer = malloc(sizeof(char *) * BUFFER_SIZE + 1);
    do
    {
        if(read(fd, buffer, BUFFER_SIZE) <= 0)
            return(NULL);
        if(ft_nl_find(buffer) >= 0)
        {
            final = ft_substr(buffer, 0, ft_nl_find(buffer) + 1);
            buffer = ft_clean_buffer(buffer);
            // printf("porcodio");
            return(final);
        }
        final = ft_strjoin(final, buffer);
        // printf("\n\033[31m---%s---|\033[0m\n", buffer);
        // printf("\n\033[32m---%s---|\033[0m\n", final);
    }
    while(ft_nl_find(final) < 0);
    buffer = ft_clean_buffer(buffer);
    return(final);
}

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    for(int i = 0; i < 4; i++)
    {
        line = get_next_line(fd);
        printf("%s", line);
    }
    close(fd);
    return(0);
}