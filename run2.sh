if make debug ; then
	valgrind --leak-check=yes --track-origins=yes ./ft_select hi hello
fi
