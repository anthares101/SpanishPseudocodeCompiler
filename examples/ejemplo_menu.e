error_state:=Falso;
exit_state:=Falso;

mientras (_no exit_state) hacer
	_borrar;
	_lugar(3,10);

	escribir 'Bienvenido/a, seleccione una opción:\n\n';
	escribir '1) Calcular los n primeros elementos de la serie de Fibonacci\n';
	escribir '2) Ni idea ahora mismo\n\n';
	escribir '0) Salir\n\n\n';

	si (error_state) entonces
		escribir 'Error, opción no válida\n';
		error_state:=Falso;
	fin_si

	escribir 'Opción: ';
	leer (opcion);

	segun(opcion)
		valor 1:
			escribir '\n';
			escribir 'Introduzca cuantos elementos de la serie de fibonacci desea: ';
			leer (n);

			si (n > 0) entonces
				escribir 0 || ' ';

				si (n > 1) entonces
					i := 0;
					j := 1;

					escribir 1 || ' ';
					si (n > 2) entonces
						para k desde 3 hasta n paso 1 hacer
							t := i + j;
							i := j;
							j := t;

							escribir t || ' ';
						fin_para;
					fin_si
				fin_si
			fin_si

			escribir '\n\n';
			escribir 'Introduzca una tecla para continuar... ';
			leer (t);

			salir;
		valor 2:
			salir;
		valor 0:
			exit_state:=Verdadero;
			salir;
		defecto:
			error_state:=Verdadero;
			salir;
	fin_segun

fin_mientras;
