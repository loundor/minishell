#include <stdio.h>

int main()
{
	char	*str = "Voila une chaine ou je vais comptre le nombre de pointeur entre deux caracteres...";
	int		i = 13;
	unsigned char	ret;

	ret = &str[i] - *str;
	printf("Valeur de ret: %d\n", ret);
	return 0;
}