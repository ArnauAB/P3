PAV - P3: estimación de pitch
=============================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 3](https://github.com/albino-pav/P3).
Siga las instrucciones de la [Práctica 2](https://github.com/albino-pav/P2) para realizar un `fork` de la
misma y distribuir copias locales (*clones*) del mismo a los distintos integrantes del grupo de prácticas.

Recuerde realizar el *pull request* al repositorio original una vez completada la práctica.

Ejercicios básicos
------------------

- Complete el código de los ficheros necesarios para realizar la estimación de pitch usando el programa
  `get_pitch`.

   * Complete el cálculo de la autocorrelación e inserte a continuación el código correspondiente.

   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un segmento de
     unos 30 ms de un fonema sonoro y su periodo de pitch; y, en otro *subplot*, se vea con claridad la
	 autocorrelación de la señal y la posición del primer máximo secundario.

	 NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la biblioteca matplotlib de Python.  
	> Para la señal de audio 'prueba.wav' el primer fonema se trata de un diftongo ya que la palabra "I" en inglés se pronuncia como la combinación "ai", por tanto si hacemos zoom para separar las vocales diferenciamos un fonema inicial correspondiente a la vocal "a" de duración 15ms (empezando a pronunciarse en el milisegundo 582 de grabación), calculando la autocorrelación de este tramo de señal observamos el primer máximo secundario alrededor de la muestra #21:  
 	> ![image](https://github.com/user-attachments/assets/8b6ddd46-f00b-44a0-8004-005314f4d8f4)



   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.
	> Usamos el siguiente algoritmo para encontrar el primer máximo secundario de la señal de autocorrelación indicado en la gráfica anterior como:  
 > ![image](https://github.com/user-attachments/assets/5f05155c-62d0-40fc-b7a5-5b93856db03f)

   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.
     > Para implementar la regla de decisión de fonema sonoro o sordo implementamos la función unvoiced, que retorna un resultado boolean en función de si la autocorrelación y la potencia de la señal están dentro de unos rangos, entonces será sorda (true) o en caso contrario sonora (false) tal que:  
     > ![image](https://github.com/user-attachments/assets/eaa1ae2a-660f-4703-aa9d-f648512fe5df)  
     > Luego la usamos más adelante para que nos diga si la señal es sorda, o en caso de que sea sonora nos calcule además el pitch correspondiente:  
     > ![image](https://github.com/user-attachments/assets/7ce1d8cc-859c-458c-bab7-d7e61f0f8229)


   * Puede serle útil seguir las instrucciones contenidas en el documento adjunto `código.pdf`.

- Una vez completados los puntos anteriores, dispondrá de una primera versión del estimador de pitch. El 
  resto del trabajo consiste, básicamente, en obtener las mejores prestaciones posibles con él.

  * Utilice el programa `wavesurfer` para analizar las condiciones apropiadas para determinar si un
    segmento es sonoro o sordo. 
	
	  - Inserte una gráfica con la estimación de pitch incorporada a `wavesurfer` y, junto a ella, los 
	    principales candidatos para determinar la sonoridad de la voz: el nivel de potencia de la señal
		(r[0]), la autocorrelación normalizada de uno (r1norm = r[1] / r[0]) y el valor de la
		autocorrelación en su máximo secundario (rmaxnorm = r[lag] / r[0]).

		Puede considerar, también, la conveniencia de usar la tasa de cruces por cero.

	    Recuerde configurar los paneles de datos para que el desplazamiento de ventana sea el adecuado, que
		en esta práctica es de 15 ms.

      - Use el estimador de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos estimadores.
     
		Aunque puede usar el propio Wavesurfer para obtener la representación, se valorará
	 	el uso de alternativas de mayor calidad (particularmente Python).
  
  * Optimice los parámetros de su sistema de estimación de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..

Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  estimador a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del estimador. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la estimación de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.
	> Este es el mensaje de ayuda que muestra el programa por pantalla con los valores por defecto que hemos establecido con los cuales hemos optimizado la detección de tramas sonoras y sordas:  
  > ![image](https://github.com/user-attachments/assets/492a826a-9428-4ed2-b38d-387658020f6e)

- Implemente las técnicas que considere oportunas para optimizar las prestaciones del sistema de estimación
  de pitch.

  Entre las posibles mejoras, puede escoger una o más de las siguientes:

  * Técnicas de preprocesado: filtrado paso bajo, diezmado, *center clipping*, etc.
  * Técnicas de postprocesado: filtro de mediana, *dynamic time warping*, etc.
  * Métodos alternativos a la autocorrelación: procesado cepstral, *average magnitude difference function*
    (AMDF), etc.
  * Optimización **demostrable** de los parámetros que gobiernan el estimador, en concreto, de los que
    gobiernan la decisión sonoro/sordo.
  * Cualquier otra técnica que se le pueda ocurrir o encuentre en la literatura.

  Encontrará más información acerca de estas técnicas en las [Transparencias del Curso](https://atenea.upc.edu/pluginfile.php/2908770/mod_resource/content/3/2b_PS%20Techniques.pdf)
  y en [Spoken Language Processing](https://discovery.upc.edu/iii/encore/record/C__Rb1233593?lang=cat).
  También encontrará más información en los anexos del enunciado de esta práctica.

  Incluya, a continuación, una explicación de las técnicas incorporadas al estimador. Se valorará la
  inclusión de gráficas, tablas, código o cualquier otra cosa que ayude a comprender el trabajo realizado.

  También se valorará la realización de un estudio de los parámetros involucrados. Por ejemplo, si se opta
  por implementar el filtro de mediana, se valorará el análisis de los resultados obtenidos en función de
  la longitud del filtro.
   > Nosotros hemos optado por los métodos de preprocesado y postprocesado que nos resultaban más familiares de la parte teórica de la asignatura.  
   >  Para el preprocesado de la señal, hemos optado por una técnica de central-clipping que elimina los valores absolutos de la señal de audio x que están por debajo de un porcentaje (llindar_cclip) del valor máximo absoluto de la señal, estableciéndolos en 0 para reducir el efecto de armónicos débiles o ruido de baja amplitud en el cálculo del pitch:  
   > ![image](https://github.com/user-attachments/assets/e6ed41f6-2fb5-4bbb-82f0-d9a4b323f2a8)  
   > En cuanto al postprocesado de la señal, hemos escogido un filtro de mediana para suavizar la señal f0 (vector de valores de pitch estimados para la señal original x), reemplazando cada valor intermedio de una ventana de 3 muestras por la mediana de ese conjunto de valores, reduciendo así picos y valores atípicos en el postprocesado, mejorando la estabilidad de la señal y eliminando ruido (pitch suavizado sin saltos bruscos):  
   > ![image](https://github.com/user-attachments/assets/9c343ecb-43ba-43f6-8cbd-abedcc1c3154)



Evaluación *ciega* del estimador
-------------------------------

Antes de realizar el *pull request* debe asegurarse de que su repositorio contiene los ficheros necesarios
para compilar los programas correctamente ejecutando `make release`.

Con los ejecutables construidos de esta manera, los profesores de la asignatura procederán a evaluar el
estimador con la parte de test de la base de datos (desconocida para los alumnos). Una parte importante de
la nota de la práctica recaerá en el resultado de esta evaluación.
