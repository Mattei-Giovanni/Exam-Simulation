#include "get_next_line.h"

int ft_strlen(char *line)
{
    int i = 0;

    if(!line)
        return(-1);
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
    while(n > 0)
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

char *get_next_line(int fd)
{
    static char *buffer;
    char *final;

    if(buffer == 0)
        buffer = malloc(sizeof(char *) * BUFFER_SIZE + 1);
    if(fd <= 0 || BUFFER_SIZE <= 0)
        return(NULL);
    do{
        if(read(fd, buffer, BUFFER_SIZE) <= 0)
            return(NULL);
        final = ft_strjoin(final, buffer);
    }
    while(ft_nl_find(final) < 0);
    return(final);
}

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    for(int i = 0; i <5; i++)
    {
        line = get_next_line(fd);
        printf("%s", line);
        i++;
    }
    close(fd);
    return(0);
}