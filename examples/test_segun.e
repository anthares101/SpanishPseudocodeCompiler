a:=5;
b:=3;

segun(a)
	valor 3:

		escribir 'no es\n';
		salir;
	valor 5:

		segun(a+b)
			valor 2:
				escribir 'tampoco es\n';
				salir;
			valor 8:
				escribir 'correcto\n';
				salir;
			defecto:
				escribir 'defecto anidado\n';
				salir;
		fin_segun
		salir;
	defecto:
		escribir 'defecto\n';
		salir;
fin_segun