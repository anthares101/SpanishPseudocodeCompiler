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

escribir_cadena 'mientras no hace siempre una primera iteración\n';
contador := 0;
mientras(falso) hacer
	contador := contador + 1;
fin_mientras
si (contador = 0) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'repetir hasta\n';
repeticiones := 5;
contador := 0;
repetir
	repeticiones := repeticiones - 1;
	contador := contador + 1;
hasta (repeticiones = 0);
si (contador = 5) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'repetir si hace siempre una primera iteración\n';
contador := 0;
repetir
	contador := contador + 1;
hasta(verdadero);
si (contador = 1) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'para con paso por defecto\n';
contador := 0;
para i desde 0 hasta 5 hacer
	contador := contador + 1;
fin_para;
escribir contador;
escribir_cadena '/n';
si (contador = 6 _y i = 6) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
	escribir_cadena 'contador:' || contador || '\n';
	escribir_cadena 'i:' || i || '\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'para con paso 3\n';
contador := 0;
para i desde 0 hasta 5 paso 3 hacer
	contador := contador + 1;
fin_para;
escribir contador;
escribir_cadena '/n';
si (contador = 2 _y i = 6) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'para con paso -1\n';
contador := 0;
para i desde 5 hasta 0 paso -1 hacer
	contador := contador + 1;
fin_para;
escribir contador;
escribir_cadena '/n';
si (contador = 6 _y i = -1) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'para con paso -3\n';
contador := 0;
para i desde 5 hasta 0 paso -3 hacer
	contador := contador + 1;
fin_para;
escribir contador;
escribir_cadena '/n';
si (contador = 2 _y i = -1) entonces
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

escribir_cadena 'Asignación\n';
dato := 3;
escribir dato;
escribir_cadena '\n';
cadena := 'cadena';
escribir_cadena cadena;
escribir_cadena '\n';

si ((cadena = 'cadena') _y (dato = 3)) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '3 + 2\n';
dato1 := 3;
dato2 := 2;
escribir dato1 + dato2;
escribir_cadena '\n';

si ((dato1 + dato2) = 5) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '3 + +2\n';
dato1 := 3;
dato2 := +2;
escribir dato1 + dato2;
escribir_cadena '\n';

si ((dato1 + dato2) = 5) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '2 - 3\n';
dato1 := 2;
dato2 := 3;
escribir dato1 - dato2;
escribir_cadena '\n';

si ((dato1 - dato2) = -1) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '2 - -3\n';
dato1 := 2;
dato2 := -3;
escribir dato1 - dato2;
escribir_cadena '\n';

si ((dato1 - dato2) = 5) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '2 * 3\n';
dato1 := 2;
dato2 := 3;
escribir dato1 * dato2;
escribir_cadena '\n';

si ((dato1 * dato2) = 6) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '2 / 3\n';
dato1 := 2;
dato2 := 3;
escribir dato1 / dato2;
escribir_cadena '\n';

si ((dato1 / dato2) = 0.6666666) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '2 ** 3\n';
dato1 := 2;
dato2 := 3;
escribir dato1 ** dato2;
escribir_cadena '\n';

si ((dato1 ** dato2) = 8) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'cadena || 3e-3 || verdadero\n';
cadena := 'cadena' || 3e-3 || verdadero;
escribir_cadena cadena;
escribir_cadena '\n';

si (cadena = 'cadena0.003verdadero') entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '2 < 3 _y \'hola\' < \'buenos_dias\'';
escribir_cadena '\n';

si (2 < 3 _y 'hola' < 'buenos_dias') entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '3 > 2 _y \'buenos_dias\' > \'hola\'';
escribir_cadena '\n';

si (3 > 2 _y 'buenos_dias' > 'hola') entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';


escribir_cadena '2 <= 2 _y \'hola\' <= \'buenos_dias\'';
escribir_cadena '\n';

si (2 < 3 _y 'hola' < 'buenos_dias') entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '3 >= 3 _y \'buenos_dias\' >= \'hola\'';
escribir_cadena '\n';

si (3 >= 3 _y 'buenos_dias' >= 'hola') entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena '3 <> 2 _y \'buenos_dias\' <> \'hola\'';
escribir_cadena '\n';

si (3 <> 2 _y 'buenos_dias' <> 'hola') entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

escribir_cadena 'Cambio dinámico de tipo\n';

dato := 'cadena';
escribir_cadena dato;
escribir_cadena '\n';

dato := 1;

si (dato < 3) entonces
	testsCorrectos := testsCorrectos + 1;
	escribir_cadena '¡Éxito!\n';
si_no
	escribir_cadena 'Error\n';
fin_si
tests := tests + 1;

escribir_cadena '---------\n';

#
comentario
de
varias
lineas
#

@ Comentario de una linea

escribir_cadena 'Se han pasado ';
escribir testsCorrectos;
escribir_cadena ' tests de ';
escribir tests;
escribir_cadena '\n';
