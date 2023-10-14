#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

int ft_putstr(char *str)
{
	int i = 0;

	if(!str)
		str = "(null)";
	while(str[i])
		i += write(1, &str[i], 1);
	return(i);
}

void ft_putnbr(long long int number, int base, int *count)
{
	char *hexa = "0123456789abcdef";

	if(number < 0)
	{
		number *= -1;
		*count += write(1, "-", 1);
	}
	if(number >= base)
		ft_putnbr(number / base, base, count);
	*count += write(1, &hexa[number % base], 1);
}

int ft_printf(char *format, ...)
{
	int i = 0;
	int count = 0;
	va_list ap;

	va_start(ap, format);
	while(format[i])
	{
		if(format[i] == '%' && (format[i + 1] == 's' || format[i + 1] == 'd' || format[i + 1] == 'x'))
		{
			i++;
			if(format[i] == 's')
				count += ft_putstr(va_arg(ap, char *));
			else if(format[i] == 'd')
				ft_putnbr(va_arg(ap, int), 10, &count);
			else if(format[i] == 'x')
				ft_putnbr(va_arg(ap, unsigned int), 16, &count);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	return(count);
}

int main(void)
{
	printf("\n Printed: %d", ft_printf("ciao, come %s, ho %d torte e %x gatti", "stai", 5, 42));
	printf("\n\n\n Printed: %d", printf("ciao, come %s, ho %d torte e %x gatti", "stai", 5, 42));
}