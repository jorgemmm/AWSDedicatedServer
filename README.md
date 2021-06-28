# AWSDedicatedServer
Se trata de un proyecto ya compilado de la versión github de unreal que te permite crear/compilar tu versión de dedicated Server y tu versión clienteserver 

Prerequisitos:
1º) Debes tener instalado una versión compilada del motor unreal engine (En este caso 4.26) 
2º) Debes tener instalado VS 2017 o VS 2019


Abrir El Proyecto en el editor del Unreal engine

1º) Descargate la versión ZIP y descomprime,

2º) Sobre el ejecutable del proyecto, haz clic dercho, cambiar versión y elegir la versión 4.26 compilada. 

2º) Sobre el ejecutable del proyecto, haz clic derecho y crea genera los ficheros del proyecto de visual studio.

3º) Intenta abrir el proyecto; Te pedirá Compilar el proyecto, Si es VS 2017 te pedirá que compiles a mano con el IDE. Con 2019 dependerá del SDK. 

Aun así es recomendable seguir los pasos siguientes:

5º)Abre el Visual studio En conficuración de Soluciones Elige: "Development Server", Ahora ve al explorador de soluciones y haz clic derecho sobre el proyecto del juego,
Clic en Compilar. De esta forma aseguras compilar el Juego pero no el motor.
NO compiles toda la solución, El motor compilado comprende un porrazo de prestaciones que ya están compiladas en este ZIP-> tardarias un montón!!!
Normalmente si le das a F7 te compilará solo los cambios. (Depende de la configuración de tu IDE.)  20-30 min depende specs.

6º) Idem 5º) pero en configuracióm de Soluciones elige: "Development Editor"  40-50 min. depende specs.

7º) Abrir el proyecto en el editor.

Packaging / Empaquetado 

1)  Descarga Mi proyecto Multiplayer Quick start https://github.com/jorgemmm/UE4CPPMultiplayerQuickStart.git
2)  [Opcional] Si lo prefieres puedes abrir un template en tercera persona sin contenido Multiplayer o crearlo tú mismo.
3)   Create 2 maps: EntryMap (Void), and serverMap. In Editor, in Projectsettings-> In Map&modes-> Set Entrymaps as Game and editor defaults 
and ServerMap as Server default.
2) In entry Map: A void Level, en  level blueprint. coloca un nodo begin play que setee un nodo open level que nos lleve a la URL:("127.0.0.1"); 
(Si dispones de un servidor externo tipo Amazón ponlo aquí: vigila el puerto. Normalmente es 7777 pero si crea varias sesiones el servidor, 
cada uno ocupará un puerto distinto: 7778, 7779)


3)  Go to File > Package Project > Build Target y elige server (NombreprojectServer); elige carpeta. 
4)  Idem para client (NombreprojectClient).

5)  En la carpeta de empaquetado, se crearán 2 carpetas el proyecto cliente y el server.
Dentro de la carpeta server, creamos un acceso directo al ejecutable. Hacemos clic derecho
sobre el acceso directo, propiedades y añadimos -log.Con log puedes ver mediante terminal la actividad del servidro. Sino pones -log el servidor dedicado no lanzará nada. 

6)doble clic izquierdo sobre el acceso directo al server dedicado.
7)clic sobre el Proyecto cliente.

8) Just FUN!

Cualquier duda Pregúntame....


