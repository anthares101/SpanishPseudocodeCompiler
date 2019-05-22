escribir_cadena '\nTest de constantes\n';

testsCorrectos := 0;
tests := 0;

escribir_cadena '\n---------\n';
escribir_cadena '5 _mod 3:\n';
escribir 5 _mod 3;
escribir_cadena '\n';

si (5 _mod 3 = 2) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '5 _div 3:\n';
escribir 5 _div 3;
escribir_cadena '\n';

si (5 _div 3 = 1) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'verdadero _o verdadero\n';
escribir verdadero _o verdadero;
escribir_cadena '\n';

si ((verdadero _o verdadero) = verdadero) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'falso _o verdadero\n';
escribir falso _o verdadero;
escribir_cadena '\n';

si ((falso _o verdadero) = verdadero) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'verdadero _o falso\n';
escribir verdadero _o falso;
escribir_cadena '\n';

si ((verdadero _o falso) = verdadero) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'falso _o falso\n';
escribir falso _o falso;
escribir_cadena '\n';

si ((falso _o falso) = falso) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'verdadero _y verdadero\n';
escribir verdadero _y verdadero;
escribir_cadena '\n';

si ((verdadero _y verdadero) = verdadero) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'falso _y verdadero\n';
escribir falso _y verdadero;
escribir_cadena '\n';

si ((falso _y verdadero) = falso) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'verdadero _y falso\n';
escribir verdadero _y falso;
escribir_cadena '\n';

si ((verdadero _y falso) = falso) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'falso _y falso\n';
escribir falso _y falso;
escribir_cadena '\n';

si ((falso _y falso) = falso) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '_no falso\n';
escribir _no falso;
escribir_cadena '\n';

si (_no falso = verdadero) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '_no verdadero\n';
escribir _no verdadero;
escribir_cadena '\n';

si (_no verdadero = falso) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'leer';
escribir_cadena '\nInserte un valor numérico: ';
leer(numero);
escribir_cadena 'Se ha leido: ';
escribir numero;
escribir_cadena '\n---------\n';

escribir_cadena 'leer_cadena';
escribir_cadena '\nInserte una cadena: ';
leer_cadena(cadena);
escribir_cadena 'Se ha leido: ';
escribir_cadena cadena;
escribir_cadena '\n---------\n';

escribir_cadena 'si entonces fin_si\n';
si (verdadero) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'si entonces si_no fin_si\n';
si (falso) entonces
	escribir_cadena 'Error\n';
si_no
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'mientras hacer fin_mientras\n';
repeticiones := 5;
contador := 0;
mientras(repeticiones > 0) hacer
	repeticiones := repeticiones - 1;
	contador := contador + 1;
fin_mientras
si (contador = 5) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'Pulse intro para probar las macros _borrar y _lugar \n';
leer(intro);
_borrar;
_lugar(1, 1);
escribir_cadena '          v Aquí debería empezar la cadena';
_lugar(2, 11);
escribir_cadena 'cadena';

escribir_cadena '\n---------\n';

escribir_cadena 'No se distinguen entre mayúsculas y minúsculas\n';
Si (vErDadERo) enTONCES
	tesTSCorRECtOS := teSTsCORRECTOs + 1;
	ESCriBIR_cADENa '¡Éxito!\n';
fIN_Si
tESTS := TESts + 1;

escribir_cadena '---------\n';

escribir_cadena 'Número\n';
numero := 5;
escribir numero;
escribir_cadena '\n';

si (numero = 5) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'Reales de punto fijo\n';
numero := 5.015;
escribir numero;
escribir_cadena '\n';

si (numero = 5.015) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'Reales con notación científica\n';
numero := 5e-3;
escribir numero;
escribir_cadena '\n';

si (numero = 5e-3) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'Delimitadas por comillas simples no incluidas en la cadena\n';
cadena := 'cadena';
escribir_cadena cadena;
escribir_cadena '\n';

si (cadena = 'cadena') entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'Pueden incluir comillas simples\n';
comilla := 'comilla \' ';
escribir_cadena comilla;
escribir_cadena '\n';

si (comilla = 'comilla \' ') entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'Se han pasado ';
escribir testsCorrectos;
escribir_cadena ' tests de ';
escribir tests;
escribir_cadena '\n';
