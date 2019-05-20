#
  Asignatura:    Procesadores de Lenguajes

  Titulación:    Ingeniería Informática
  Especialidad:  Computación
  Curso:         Tercero
  Cuatrimestre:  Segundo

  Departamento:  Informática y Análisis Numérico
  Centro:        Escuela Politécnica Superior de Córdoba
  Universidad de Córdoba
 
  Curso académico: 2018 - 2019

  Fichero de ejemplo nº 1 para el intérprete de pseudocódigo en español: ipe.exe
#

@ Bienvenida

_borrar;

_lugar(10,10);

escribir('Introduce tu nombre --> ');
leer_cadena(nombre);

_borrar;
_lugar(10,10);

escribir(' Bienvenido/a << ');

escribir(nombre);

escribir(' >> al intérprete de pseudocódigo en español:\'ipe.exe\'.');

_lugar(40,10);
escribir('Pulsa una tecla para continuar \t --> ');
leer_cadena(pausa);

_borrar;
_lugar(10,10);
escribir('El programa ha concluido \n');
