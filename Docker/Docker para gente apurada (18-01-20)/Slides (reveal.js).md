---
type: slide
slideOptions:
  transition: slide
  theme: moon
---

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

# Docker

### para gente apurada

---

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

## Hackfun

hackfunrosario.com

---

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

## Qué

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### "Serie de productos SaaS que utiliza virtualización a nivel de OS para producir software empaquetado en forma de **contenedores**"

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### "Docker es una herramienta para empaquetar una aplicación junto con sus dependencias en un contenedor virtual que puede ejecutarse en cualquier plataforma*"

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

### ¿Gestor de paquetes?

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

### ¿VM?

---

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

## Para qué

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

<span><!-- .element: class="fragment" data-fragment-index="1" -->Entorno de desarrollo local == remoto / producción</span>

<span><!-- .element: class="fragment" data-fragment-index="2" -->Forma "limpia" de instalar/probar software</span>

<span><!-- .element: class="fragment" data-fragment-index="3" -->Forma simple de instalar servicios complejos</span>

<span><!-- .element: class="fragment" data-fragment-index="4" -->Múltiples instancias de la misma app</span>

---

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

## Cómo

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

### Instalación

Debian -> +repo, +keys, +paquete con apt

Arch -> Community

Windows/Mac -> Docker Desktop

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### (Opcional en Linux)

<span><!-- .element: class="fragment" data-fragment-index="1" -->Agregar usuario a grupo `docker`</span>

<span><!-- .element: class="fragment" data-fragment-index="2" -->Instalar `bash completion`</span>

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### Palabras clave

<span><!-- .element: class="fragment" data-fragment-index="1" -->"Imágen"</span>

<span><!-- .element: class="fragment" data-fragment-index="2" -->"Contenedor/Container"</span>

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### Palabras clave (imagen)

<span><!-- .element: class="fragment" data-fragment-index="1" -->`pull` -> descarga imágen</span>

<span><!-- .element: class="fragment" data-fragment-index="2" -->`run` -> crea container</span>

<span><!-- .element: class="fragment" data-fragment-index="3" -->`rm` -> elimina imágen</span>

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### Palabras clave (container)

<span><!-- .element: class="fragment" data-fragment-index="1" -->`start` -> arrancar contenedor</span>

<span><!-- .element: class="fragment" data-fragment-index="2" -->`stop` -> detiene ejecución</span>

<span><!-- .element: class="fragment" data-fragment-index="3" -->`rm` -> elimina contenedor</span>

---

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### `docker`

```
docker info
docker --help
docker <comando> --help
```

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### `docker run`

```
docker run --help
docker run <imagen>
```

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### hello-world ??

`docker run hello-world`

<span><!-- .element: class="fragment" data-fragment-index="1" -->1. Busca imágen llamada `hello-world` en local</span>

<span><!-- .element: class="fragment" data-fragment-index="2" -->1.1 Busca en docker hub</span>

<span><!-- .element: class="fragment" data-fragment-index="3" -->1.2 Descarga</span>

<span><!-- .element: class="fragment" data-fragment-index="4" -->2. Crea container</span>

<span><!-- .element: class="fragment" data-fragment-index="5" -->3. Corre container</span>

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### "Tipos" de contenedores


<span><!-- .element: class="fragment" data-fragment-index="1" -->Se ejecutan y terminan</span>

<span><!-- .element: class="fragment" data-fragment-index="2" -->Se ejecutan y siguen en ejecución</span>

<span><!-- .element: class="fragment" data-fragment-index="3" -->Se usan interactivamente</span>

----


#### Correr como daemon
```
docker run -d <imagen>
```

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### docker ps

```
docker ps  // muestra contenedores en ejecución
docker ps -a  // muestra todos los contenedores
```

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### run / stop / rm

```
docker run <imagen>  // Sigue en ejecución*
docker stop <id>
(opcional) docker rm <id>
```

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### Otros parámetros útiles

Eliminar container al finalizar la ejecución:
```
docker run --rm <imagen>
```

Mapear puerto local a puerto del container:
```
docker run -p 1234:80 <imagen>
```

Definir un nombre personalizado
```
docker run --name micontenedor <imagen>
```

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### Otros parámetros (interacción)

Comando dentro de container en ejecución:
```
docker exec <id> <comando>
```

Modo interactivo* (nuevo container):
```
docker run -it <imagen> /bin/bash
```

Modo interactivo (container en ejecución):
```
docker exec -it  <id> bash
```

---

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

### Volumes

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### `docker run -v`

```
docker run -v /ruta/local:/ruta/interna ...
```

```
docker run -v /home/user/miweb:/usr/share/nginx/html ...
```

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### Otros parámetros (información)

Información (sistema)
```
docker info
```

Espacio en uso
```
docker system df [-v]
```

Inspeccionar contenedor
```
docker inspect <id>
```

Logs
```
docker logs <id>
```

---

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

### docker-compose

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

```
docker-compose.yml:
```

```dockerfile=
- version:
- services:
  - un_servicio:
    - image:
    - ports:
    - volumes:
    - restart:
    ...

  - otro_servicio:
    - image:
    - ports:
    - volumes:
    - restart:
    ...

- volumes:
  - mi_volumen1
  - mi_volumen2
  ...

```

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

```
restart: [no, always, on-failure, unless-stopped]
```

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

```
docker-compose up [-d]
```

```
docker-compose ps
```

```
docker-compose stop
```

----

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

### Portainer

portainer.io/installation

---

<!-- .slide: data-background="https://i.imgur.com/Vf1T8rT.jpg"-->

#### Material

- https://github.com/wsargent/docker-cheat-sheet
- https://developers.redhat.com/blog/2018/02/22/container-terminology-practical-introduction/

