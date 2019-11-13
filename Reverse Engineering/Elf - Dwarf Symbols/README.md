# Elf debugging symbols

A veces la metadata dice más que la ingeniería.

# Reto
Este reto no es tan distinto de lo que se podría encontrar en un clásico *crack me*, pero propone una solución distinta a las normales.

Diría que el reto tiene una limitación, se quiere resolver sin usar un disassembler (como IDA, Binary Ninja), y además sin usar *strings* y buscar en el resultado la bandera.

Sí, el objetivo del reto es encontrar la 'bandera', sin embargo, no considero que el objetivo del reto represente el objetivo de este walkthrough.

# Objetivo
El objetivo de este reto es ampliar la visión que se tiene sobre los binarios.

La manera de lograr esto es resolviendo este simple *crack me* solo con información de **símbolos** que genera el compilador.

Idealmente, después de este walkthrough vas a tener claro qué es elf y como esta compuesto, qué son los símbolos, por qué se usan, y como podes usarlos para tu ventaja. Esto es el verdadero objetivo del reto.

# Pre requisitos
- Sistema operativo Linux
- Paquete *elfutils - xxd* (```$ apt install elfutils xxd -y```)


# Challenge

De nuevo, el reto no es nada distintos de un clásico crack me, se pide una contraseña que no se sabe, pero con un twist en su resolución. La solución esperada es encontrar, en la 'metadata' del binario, el offset exacto donde reside la 'bandera'.

Tenemos un binario llamado *chall*, el primer paso es ver la información más abstracta del mismo. Para eso usamos el clásico comando *file*.

```sh
$ file chall
chall: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=dfede2540bbba918d616465ce8c0e7c4eaf2d589, with debug_info, not stripped

```

Es obvio que un binario tiene las instrucciones que necesita para funcionar, como referencias hacia las distintas librerias que necesita usar para funcionar (/lib64/ld-linux-x86-64.so.2), lo que no es tan obvio es que también tenga información que facilite muchísimo el arte de entender un programa sin su código fuente, y que para la computadora es irrelevante.

Una de estas *informaciones* son los símbolos, y por el output anterior vemos que no solo tenemos acceso a símbolos normales, sino también a símbolos de debugging.

Antes de indagar en la información deberiamos de aclarar a que me refiero con información irrelevante.

Para entender el concepto de información irrelevante tenemos que entrar en el contexto de que estamos hablando de un binario, en particular, un programa que una computadora va a ejecutar, y más que mostrar en que información es innecesaria para una computadora (que no es poca) prefiero mostrar que información es *necesaria* para una computadora, lo cúal no es tan obvio.

Vamos un paso más arriba de la corriente eléctrica que representan los 0s y 1s para analizar el funcionamiento de **assembly**.

Parece algo complejo pero la idea abstracta de assembly es simple, por eso se podría comparar con hacer un café con leche.

Tenemos una serie de instrucciones, la primera sería tomar una taza, la segunda poner leche en la taza y luego café, luego calentas la tasa en un microondas.

Cada paso es una instrucción, cada instrucción tiene distintos objetos que interactuan entre sí.

La primera instrucción fué tomar una taza, la segunda fué poner leche en la taza. Abstractamente tenemos una operación, poner, esa operación requiere 2 objetos, un objeto para almacenar, y otro para que reciba ese almacenamiento, ¿Qué se almacena? La leche, ¿Dondé? En la taza.

Lo único que necesitamos para realizar esa instrucción fué responder esas dos preguntas, curiosamente, en la computación pasa lo mismo.

Hay una instrucción llamada añadir, añadir un objeto en otro, para realizarla tenemos que responder las mismas dos preguntas que antes, ¿Qué almacenamos? y ¿Dondé lo almacenamos?.

Y así realizamos la operacion *add* en assembly:

```
add dest, src
```

Programar es usar un conjunto de instrucciones en ciertos orden para que generen el resultado que queremos, en cada instrucción necesitamos responder la pregunta que tiene esa instrucción.

Cuando añadimos el pequeño detalle a esta teoría de que el único lugar donde se almacenan objetos en la computadora es en memoria, nos damos cuenta que lo **único** que necesita un binario para funcionar es decirle en que parte de la memoria esta el destino y en que parte esta la fuente a almacenar.

Los nombres de variables, de funciones, de macros se vuelven irrelevante, solo se necesita las direcciones de memoria.

Una vez que se entiende esto, vemos que las computadoras se orientan de manera muy distinta a nosotros para operar, y que tratar de entender un programa a base de leer instrucciones y los objetos que usa para realizar esa operación (en sí, entender un programa leyendo assembly) no es la forma más óptima de entender un programa.

Esta es la razón por la cúal quiero hacer este reto sin tocar un disassembler, y simplemente centrandonos en información que esta hecha para ser usada por humanos y que para la computadora es irrelevante.

Primero dijé que este binario tenía 'metadata' y después 'información irrelevante' (en relación a la necesidad de la computadora), pero en realidad la información/metadata que nos sirve para resolver el challenge tiene nombre y se llama *símbolos*.

Ahora, con la obligación de explicar que son los símbolos, podría buscar una definición de diccionario y tirarla acá, pero hacer eso, en la mayoría de los casos, genera una memoria sobre el concepto, más que un entendimiento del mismo.

Por eso, voy a tratar de poner un problema cuya solución la puedan dar los símbolos.

Esta es la situación:
    - Hay un programa, un binarion, con un bug.
    - No hay código fuente o sí lo hay no es el mismo código que compilo el binario (por que, quizás, el programador no usaba un controlador de versiones (no usaba git)).
    - Se necesita, mediante un analisís dinamico (viendo al programa correr con distintos input) encontrar el bug.

Ahora, supongamos que se tiene el binario de producción, el binario que fué compilado de una manera tal que sea extredamente rápida (¿Quién quiere que su aplicación sea lenta?).

Si solo tendriamos ese binario, encontrar el bug sería una tarea súper dolorosa, tratar de descifrar que quiere decir el código assembly (que ya en sí no es muy amigable para un humano) que generó el compilador para hacerlo rápido! (los compiladores usan métodos para nada obvios, súper inteligentes, para acelerar la velocidad de ejecución del programa, el coste es, el código assembly es súper dificíl de entender).

En el caso en el que no podamos tener la solución ideal, el código fuente del binario. La próxima mejor solución sería darse cuenta que la programación es perversa y dejar de programar. En caso de que esta tampoco se pueda, la siguiente mejor solución sería tener un binario que mantenga en sí información de nivel algo, ¿Para qué? para que cuando se corra en un debugger (gdb) se tenga acceso a las variables, funciones, clases con los nombres que tenían en el programa! (además de que el código assembly sea un mucho más legible).

Este binario con ese añadido de información útil para debugging esta usando **símbolos**, en especifico, en el caso de nuestro binario, se le añadió símbolos de debugging en formato [DWARF](https://en.wikipedia.org/wiki/DWARF).

Sabemos que nuestro binario tiene símbolos, lo cúal implica que tiene información de nivel alto en el binario. Con esto en mente, si logramos acceder e interpretar esa información, podemos encontrar la 'bandera' del reto sin haber tenido que abrir un disassembler, no tener que correr strings y buscar el resultado en el binario, y lo más importante, resolverlo de una forma elegante entendiendo que estamos haciendo.

Ahora hay que transformar la teoría en práctica, para eso, vamos a usar un programa que esta hecho para ver toda la información que tiene un binario en formato [ELF](https://en.wikipedia.org/wiki/.elf) , ```readelf```.

Para leer todos los símbolos del binario podemos correr este comando:

```sh
$ readelf -S chall
```

Para más info sobre los comandos que tiene ```readelf``` siempre se puede, y recomienda, leer su man page (```man readelf```).

Hay un monton de output al escribir ese comando ya que el binario tiene 34 símbolos.

Explicar cada uno es ineficiente y haría este walkthrough más largo de lo que ya es, por eso, y más importante aún para no desbordarte con información, vamos a prestar atención a los símbolos que empiezan con *.debug*, en particular, en *.debug_info*.

Sabemos que este símbolos tiene algo de información de nivel alto, para ver exactamente qué información es poder usar de nuevo ```readelf``` y decirle que nos muestre la información que tiene ese símbolo. El comando específicamente es:

```sh
$ readelf --debug-dump=info chall
```

De nuevo, hay un monton de output, y la sintaxis parece media arcaica (o mitológica dado el contexto). El output esta en formato DIE, el cúal usa DWARF para describir la información que guarda.

No se necesita saber este formato para saber que información es útil, ya que, si se presta atención, se puede ver que entre muchas cosas, parece que nos esta describiendo el nombre de las variables que el programa usa.

La que nos interesa es *password*, para obtener solo la información de esta podemos usar el siguiente comando.

```sh
$ readelf --debug-dump=info chall | grep -A6 -E "\bpassword\b"
```

Si recordamos, el objetivo de este reto era encontrar mediante el uso de la información en el binario, el lugar exacto donde estaba la bandera. El output del anterior comando nos esta diciendo, en la última línea, que esta variable esta en la **memoría virtual** 0x4060. Sí podemos convertir esa memoría virtual en un offset en el binario, podemos acceder a su contenido.

La memoría virtual es un tema bastante extenso, pero en un modo simple, se puede ver como una 'abstracción' o un 'engaño' que el sistema operativo impone a todos los programas que estan corriendo en la computadora (digo impone por que en sí es una medida de seguridad, hace que un programa no pueda acceder a la memoria de otro). Basicamente, le hace creer al programa que corre que tiene 'toda la memoria de la computadora a su disposición' y que es el único programa que esta corriendo. Por eso, el hecho de que la bandera este en la memoria virtual 0x4060 no significa que este en ese offset en el binario (que la bandera este a 0x4060 bytes de distancia del comienzo del binario).

Para hacer esa transformación, de memoría virtual a offset físico, podemos leer los **segmentos** del binario, que son otra información extra que el binario tienen.

Los segmentos son la manera de dividir un programa en distintas partes, decimos 'este segmentos se llama *.text* y solo tiene las instrucciones que el programa va a correr, mientras que este se llama *.data* y en este segmento van a estar todas las variables que tenga el programa'. Además, podemos aplicar reglas específicas a los segmentos y darle más seguridad. Podemos hacer que el segmento *.text* no se pueda escribir, asi evitamos que alguien pueda explotar nuestro programa con un exploit.

Los segmentos son en parte información que almacenan los headers del formato ELF, pueden leer más sobre los headers, y evitar que esto se siga haciendo más largo, [acá](https://blog.k3170makan.com/2018/09/introduction-to-elf-format-elf-header.html).

Corriendo este comando, podemos ver los segmentos del programa:

```sh
$ readelf -l chall
```

El output no es el más amigable, pero sabemos que queremos ver cúal es el offset real del segmento que se mapea en el rango de la memoria virtual 0x4060.

Si prestamos atención a este segmento:

```
  LOAD           0x0000000000002de8 0x0000000000003de8 0x0000000000003de8
                 0x0000000000000299 0x00000000000002b8  RW     0x1000
```

Dice que empieza en la memoria virtual 0x03de8 y que abarca un tamaño de 0x0002b8, haciendo la suma, vemos que tiene en su memoria la variable password, que se encuentra en 0x4060. Y más importante, nos dice que esta ubicado en el offset 0x02de8 en el archivo real, a 0x1000 bytes menos que su posición en la memoria virtual, entonces, el lugar exacto donde esta el contenido de la variable password es en: 0x4060 - 0x1000 = **0x3060**.

Ahora, y finalmente, con un poco de xxd foo podemos recuperar la 'bandera':

```sh
$ xxd -p -l 32 -seek +0x3060 chall | xxd -r -p
```

Y, si usamos ese valor en el programa

```sh
$ ./chall
                ~~[ Hackfun elf symbols ]~~

Password: UArfStPzkuZNJMDy1TtMY7JWaGjO4UHy
Got it! Congrats!
```

# Conclusión

En este momento, me veo obligado a responder la muy comprensiba crítica de ¿Por qué aprendí todo esto si haciendo strings podía resolver esto en 10 segundos?.

Si tu objetivo es resolver CTF's y sumar puntos (que no tiene nada de malo), la verdad esto no te sirvió demasiado (quizas si te sirva, en caso de que tengas en el futuro un reto que requiera este conocimiento), aunque creo haber aclarado al comienzo de este walkthrough que el objetivo no era resolver el reto, si no entender.

Hacking es entender la tecnología. **Entender**. Que es algo distinto a saber.

Entender es lo que diferencia a un experto de un aficionado, entender fué lo que propulso la personalidad de 'hacker'.

Si tu deseo es ser un gran Reverse Engineering tenes que ir más haya de saber ciertos trucos, tenes que entender con lo que estas trabajando, tenes que entender un binario, sus partes, lo que lo afecta o lo hace distinto. Y este fué el objetivo de este reto, que se entienda un poco mejor los binarios y el arte de la ingeniería inversa.

Entender estos pequeños conceptos son lo que, en mi opinión, forman a un experto.
