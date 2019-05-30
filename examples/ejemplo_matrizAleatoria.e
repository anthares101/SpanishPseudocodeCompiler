_borrar;
_lugar(3,10);

escribir 'Crear matriz aleatoria\n\n';

escribir 'Filas: ';
leer (filas);
escribir 'Columnas: ';
leer (columnas);

para k desde 1 hasta filas paso 1 hacer
	escribir '\n';
	para l desde 1 hasta columnas paso 1 hacer
		escribir random()*20 || '\t\t';
	fin_para
fin_para;

escribir '\n\n';
escribir 'Pulse una tecla para terminar... ';
leer_cadena (pausa);
