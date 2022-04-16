#include <unistd.h>
#include <stdarg.h>

int ft_col_num(long long dig, int base_len)
{
	int i = 1;
	while(dig >= base_len)
	{
		dig = dig / base_len;
		i++;
	}
	return(i);
}

void ft_putnbr(long long n, int base_len, char *s)
{
	if (n >= base_len)
		ft_putnbr(n/base_len, base_len, s);
	write(1, &s[n%base_len], 1);
}

int ft_strlen(char *str)
{
	int i = 0;
	while (str && str[i] != '\0')
		i++;
	return(i);
}
int ft_printf(const char *tmp, ...)
{
	long long i;
	char *str;
	int res = 0;
	va_list ap;
	va_start(ap, tmp);
	while(*tmp)
	{
		if (*tmp == '%')
		{
			tmp++;
			if (*tmp == 's')
			{
				str = va_arg(ap, char *);
				if (!str)
					str = "(null)";
				res = ft_strlen(str);
				write(1, str, ft_strlen(str));
			}
			if (*tmp == 'd')
			{
				i = va_arg(ap, int);
				if (i < 0)
				{
					write(1, "-", 1);
					res+= 1;
					i = -i;
				}
				res += ft_col_num(i, 10);
				ft_putnbr(i, 10, "0123456789");
			}
			if (*tmp == 'x')
			{
				i = va_arg(ap, unsigned int);
				res += ft_col_num(i, 16);
				ft_putnbr(i, 16, "0123456789abcdef");
			}
		}
		else
			res += write(1, tmp, 1);
		tmp++;
	}
	va_end(ap);
	return(res);
}
