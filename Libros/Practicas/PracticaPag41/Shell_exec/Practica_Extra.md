# Practica Extra

Mas adelante en el libro nos comenta que podemos lanzar una shell en lugar de ejecutar una funcnion ya predefinida en el programa
para ello debemos lograr algunas cosas:

## Obtener una shellcode - payload.

Debemos obtener un payload o desarrollarlo , el codigo debe lanzar o ejecutar una shell , podemos lograrlo de muchas formas, 
usando metasplouit , programandolo en C , python , asm, etc. La idea es que obtengamos las instrucciones en Hex. Para que 
al inicio del buffer la podamos ingresar.

Una vez lograda la inyeccion , se llena lo demas del padding hasta llegar al punto donde sobreescribimos el EIP. Que en nuestra
practica fue 44 bytes. Asi que una parte es 

`paylaod + padding = 44 bytes`

Para que lo siguiente que pongamos sea la direccion de retorno de donde se ubica nuestro buffer.

asi cuando se haga el salto ira a la parte donde existe nuestras instrucciones y ejecute la shell.

