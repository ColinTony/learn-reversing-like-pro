#!/bin/bash

#Colors
greenColour="\e[0;32m\033[1m";
endColour="\033[0m\e[0m";
redColour="\e[0;31m\033[1m";
blueColour="\e[0;34m\033[1m";
yellowColour="\e[0;33m\033[1m";
purpleColour="\e[0;35m\033[1m";
turquoiseColour="\e[0;36m\033[1m";
grayColour="\e[0;37m\033[1m";

trap ctrl_c INT;

declare -i counter=0;


function check_root()
{
  uid=$(id -u);

  if [[ $uid -ne 0 ]]; then
    echo -e "${redColour}Debes ser root para ejecutar esta herramienta.${endColour}";
    exit_tool 1;
  fi
}

function starLab64()
{
	echo -e "\n\n ${grenColour}[+]${endColour} ${yellowColour}Iniciando Docker vulnerable (Recuerda que esto afecta tu ASLR del host)${endColour}\n"
	sleep 2
  hola_cursor;
	sudo docker run -it --privileged --rm -v ./ctf:/ctf lab64 bash -c "echo 0 > /proc/sys/kernel/randomize_va_space && exec bash"
	echo -e '[-] Saliendo ...\n'
	echo -e 'Reiniciando ASLR del host...\n'
	sleep 2
	sudo echo 2 > /proc/sys/kernel/randomize_va_space
	status=$(cat /proc/sys/kernel/randomize_va_space)
	if [ "$status" -eq 2 ]; then
		echo 'ASLR de nuevo activado en hosts.'
	else
		echo 'Hubo un error al activar ASLR. (urgente comprobarlo podria dejar el host vulnerable)'
	fi
  adios_cursor;
}

function startLab32()
{
    echo -e "\n\n ${grenColour}[+]${endColour} ${yellowColour}Iniciando Docker vulnerable de 32 bits (Recuerda que esto afecta tu ASLR del host)${endColour}\n"
    sleep 2
    hola_cursor;
    sudo docker run -it --privileged --rm -v ./ctf:/ctf lab32 bash -c "echo 0 > /proc/sys/kernel/randomize_va_space && exec bash"
    echo -e '[-] Saliendo ...\n'
    echo -e 'Reiniciando ASLR del host...\n'
    sleep 2
    sudo echo 2 > /proc/sys/kernel/randomize_va_space
    status=$(cat /proc/sys/kernel/randomize_va_space)
    if [ "$status" -eq 2 ]; then
        echo 'ASLR de nuevo activado en host.'
    else
        echo 'Hubo un error al activar ASLR. (urgente comprobarlo, podría dejar el host vulnerable)'
    fi
    adios_cursor;
}


# funciones del cursor
function adios_cursor()
{
  tput civis;
}

function hola_cursor()
{
  tput cnorm;
}

function create_docker()
{
  if [[ -f "./Dockerfile" ]]; then
    echo -e "${blueColour}[-] Iniciando contenedor Docker.${endColour}";
    sudo docker build -t lab64 .
    starLab64;
  else
    exit_tool 1 "Error no existe el archivo Dockerfile";
  fi
}

function create_docker32() {
  if [[ -f "./Dockerfile32" ]]; then
    echo -e "${blueColour}[-] Construyendo contenedor Docker 32 bits...${endColour}"
    sudo docker build -t lab32 -f Dockerfile32 .
    startLab32
  else
    exit_tool 1 "Error: no existe el archivo Dockerfile32"
  fi
}

# Captura el control c
function ctrl_c()
{
  echo -e "\n\n\n${yellowColour}[!]${endColour} ${redColour} Saliendo ... ${endColour} \n";
  exit_tool 1 "Has matado el programa. ${yellowColour}[!] Revisa tu ASLR${endColour}";
}

#system funtions
function exit_tool()
{
  code=$1;
  mensaje=$2;

  if [[ $code -eq 1 ]]; then
    echo -e "\n\n ${redColour}[ X ] Error: ${mensaje} ${endColour}";
    hola_cursor;
    exit $code;
  fi

  echo -e "\n\n${grenColour} Espero haya disfrutado su estancia hackeando ${endColour}";
  hola_cursor;
  exit $code;
}

function helpPanel()
{
  echo -e "\n ${yellowColour}[?]${endColour}${grayColour} PANEL DE AYUDA ${endColour} \n";
  echo -e "\n\t${yellowColour}-h: ${endColour}${grayColour}Muestra este panel de ayuda.${endColour}";
  echo -e "\n\t${yellowColour}-i: ${endColour}${grayColour}Crea la imagen vulnerable de docker.${endColour}";
  echo -e "\n\t${yellowColour}-k: ${endColour}${grayColour}Crea la imagen vulnerable de docker (32 Bits).${endColour}";
  echo -e "\n\t${yellowColour}-s: ${endColour}${grayColour}Inicia el contenedor vulnerable para reversing.${endColour}";
  echo -e "\n\t${yellowColour}-l: ${endColour}${grayColour}Inicia el contenedor vulnerable para reversing 32 Bits.${endColour}";
  echo -e "\n\n";
}

function catch_default()
{
  echo -e "\n\n";
  sleep 1;
  echo -e "\n\n ${redColour}Error al ejecutar el programa. ${endColour} \n";
  echo -e "\n ${yellowColour}Uso de la herramienta: ${endColour} \n";
  echo -e "\n ${purpleColour}[*] Ser usuario root. ${endColour} \n";
  echo -e "\n ${purpleColour}[*] Respetar las opciones del programa: ${endColour} \n";
  helpPanel;
  exit_tool 1 "Revise la forma de ejecutar";
}

function banner()
{
  echo -e " █████                 █████                ███████████                                                    ███                     
░░███                 ░░███                ░░███░░░░░███                                                  ░░░                      
 ░███         ██████   ░███████   █████     ░███    ░███   ██████  █████ █████  ██████  ████████   █████  ████  ████████    ███████
 ░███        ░░░░░███  ░███░░███ ███░░      ░██████████   ███░░███░░███ ░░███  ███░░███░░███░░███ ███░░  ░░███ ░░███░░███  ███░░███
 ░███         ███████  ░███ ░███░░█████     ░███░░░░░███ ░███████  ░███  ░███ ░███████  ░███ ░░░ ░░█████  ░███  ░███ ░███ ░███ ░███
 ░███      █ ███░░███  ░███ ░███ ░░░░███    ░███    ░███ ░███░░░   ░░███ ███  ░███░░░   ░███      ░░░░███ ░███  ░███ ░███ ░███ ░███
 ███████████░░████████ ████████  ██████     █████   █████░░██████   ░░█████   ░░██████  █████     ██████  █████ ████ █████░░███████
░░░░░░░░░░░  ░░░░░░░░ ░░░░░░░░  ░░░░░░     ░░░░░   ░░░░░  ░░░░░░     ░░░░░     ░░░░░░  ░░░░░     ░░░░░░  ░░░░░ ░░░░ ░░░░░  ░░░░░███
                                                                                                                           ███ ░███
                                                                                                                          ░░██████ 
                                                                                                                           ░░░░░░  
 █████                                     █████    ████  ████                          █████       █████     █████                
░░███                                    ███░░░███ ░░███ ░░███                        ███░░░███   ███░░░███  ░░███                 
 ░███████  █████ ████    ██     ██████  ███   ░░███ ░███  ░███  ████████   ████████  ███   ░░███ ███   ░░███ ███████               
 ░███░░███░░███ ░███    ░░     ███░░███░███    ░███ ░███  ░███ ░░███░░███ ░░███░░███░███    ░███░███    ░███░░░███░                
 ░███ ░███ ░███ ░███          ░███ ░░░ ░███    ░███ ░███  ░███  ░███ ░███  ░███ ░░░ ░███    ░███░███    ░███  ░███                 
 ░███ ░███ ░███ ░███          ░███  ███░░███   ███  ░███  ░███  ░███ ░███  ░███     ░░███   ███ ░░███   ███   ░███ ███             
 ████████  ░░███████     ██   ░░██████  ░░░█████░   █████ █████ ████ █████ █████     ░░░█████░   ░░░█████░    ░░█████              
░░░░░░░░    ░░░░░███    ░░     ░░░░░░     ░░░░░░   ░░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░        ░░░░░░      ░░░░░░      ░░░░░               
            ███ ░███                                                                                                               
           ░░██████                                                                                                                
            ░░░░░░                                                                                                                 ";
            echo -e "\n\n";
}

clear;
banner;
adios_cursor;
check_root;


while getopts ":hislk" arg; do

  case $arg in
    h)let counter=1; ;;
    i)let counter=2; ;;
    k)let counter=5; ;;
    s)let counter=3; ;;
    l)let counter=4; ;;
  esac 
done;

  # Valuacion de opciones
  case $counter in
    1) helpPanel;;
    2) create_docker;;
    3) starLab64;;
    4) startLab32;;
    5) create_docker32;;
    *) catch_default;;
  esac;

  hola_cursor;
