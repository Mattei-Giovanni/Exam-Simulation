#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

int ft_putstr(char *str)
{
	int count = 0;
	int i = 0;

	if(!str)
		str = "(null)";
	while(str[i])
	{
		count += write(1, &str[i], 1);
		i++;
	}
	return(count);
}

void ft_putnbr(long long int n, int base, int *count)
{
	char *hexa = "0123456789abcdef";

	if(n < 0)
	{
		n *= -1;
		*count += write(1, "-", 1);
	}
	if(n >= base)
		ft_putnbr((n / base), base, count);
	*count += write(1, &hexa[n % base], 1);
}

int ft_printf(char *line, ...)
{
	int i = 0;
	int count = 0;
	va_list ap;

	va_start(ap, line);
	while(line[i])
	{
		if(line[i] == '%' && line[i + 1] != '%')
		{
			i++;
			if(line[i] == 's')
				count += ft_putstr(va_arg(ap, char *));
			if(line[i] == 'd')
				ft_putnbr((long long int)va_arg(ap, int), 10, &count);
			if(line[i] == 'x')
				ft_putnbr((long long int)va_arg(ap, unsigned int), 16, &count);
		}
		else
			count += write(1, &line[i], 1);
		i++;
	}
	va_end(ap);
	return(count);
}

int main(void)
{
	printf("\nNumber of print: %d\n", ft_printf("Ehi ciao %s stai, ho %d torte e %x pancakes", "80000000", 80000000, 80000000));
}