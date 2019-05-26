a:='hola';
b:=3;

segun(a)
	valor 'adios':

		escribir 'no es\n';
		salir;
	valor 'hola':

		segun(a||b)
			valor 'hola'||3:
				escribir 'correcto\n';
			valor 'asd':
				escribir 'tampoco es\n';
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