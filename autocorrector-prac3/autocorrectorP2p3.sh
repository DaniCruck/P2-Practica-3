#!/bin/bash

DIRPRAC=.
MAXTIME=10 	   # Tiempo máximo de ejecución (en segundos) de una prueba
ENT=$DIRPRAC/pruebas	   # Directorio con los ficheros de pruebas de entrada
SAL=$DIRPRAC/salida-correcta-esperada	   # Directorio con los ficheros de salidas correctas
OBT=$DIRPRAC/salida-obtenida       # Directorio con los ficheros obtenidos tras la ejecución de la práctica
npruebasES=1
EXE=prac3
VAL="valgrind -q"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR" || exit 1

mata=./mata
comparefiles=./comparefiles
autoco=autocorrector-prac3
meikfail=$autoco/makefile-corrector

# nombres de las pruebas unitarias (debe coincidir con el makefile-corrector) y su valor
pruebasAuto=(p3TestSuiteAC-Coordinate p3TestSuiteAC-Piece p3TestSuiteAC-Gameboard p3TestSuiteAC-Game)

# ---------------------------
function compilarPruebasUnitarias() {

  make -f $meikfail clean > /dev/null

  for nompr in "${pruebasAuto[@]}"; do
     make -f $meikfail $nompr 2>&1
  done

}

# -------------- generar y compilar el fichero auxiliar mata.c -----
function genMata() {

if ! test -x mata ; then  # si ya existe no se genera
echo "#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

const int TAMMAXFICH=300000;
int f;int segundos,st;
int segejec=0;
char *nfsal=NULL;
void SeAcabo(int i){
  fprintf(stderr,\"ERROR, tiempo de ejecución agotado... (%d segundos)\\n\",segundos);
  fflush(stderr);
  kill(f,SIGKILL);
  exit(-1);
}
void SeAcaboFich(int i){
  fprintf(stderr,\"ERROR, fichero de salida muy grande (cuelgue?)... \\n\");
  fflush(stderr);
  kill(f,SIGKILL);
  exit(-1);
}
int FicheroGrande() {
  struct stat s;  int ret=0;
  if (nfsal != NULL) {
    stat(nfsal,&s);
    if (s.st_size > TAMMAXFICH) ret = 1;
  }
  return ret;
}
void Control(int i){
  segejec++;
  if (segejec >= segundos) SeAcabo(i);
  else if (FicheroGrande()) SeAcaboFich(i);
  else alarm(1);
}
void Salir(int i){exit(1);}
int main(int argc,char *argv[]){
  if (argc < 4) exit(1);
  segundos = atoi(argv[1]);
  nfsal = argv[2];
  signal(SIGALRM,Control);
  signal(SIGCHLD,Salir);
  alarm(1);
  if ((f = fork()) == 0) execvp(argv[3],&argv[3]);
  else wait(&st);
}
" > mata.c
gcc -o mata mata.c
fi
}

function genComparefiles() {

if ! test -x comparefiles ; then # si ya existe no se genera
echo "#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
  int salida=0;
  if (argc!=3) cout << \"Sintaxis: \" << argv[0] << \" <obtenido.txt> <correcto.txt>\" << endl;
  else 
  {
    ifstream fo(argv[1]);
    ifstream fc(argv[2]);
    if (fo.is_open() && fc.is_open())
    {
      string so,sc,tmp;

      fo >> tmp;
      while (!fo.eof() || tmp.length()!=0)
      {
        so=so+tmp;
        tmp=\"\";
        fo >> tmp;
      }
      fc >> tmp;
      while (!fc.eof() || tmp.length()!=0)
      {
        sc=sc+tmp;
        tmp=\"\";
        fc >> tmp;
      }

      // ignorar los '-' en las líneas
      string scok, sook;
      for (unsigned int i=0; i<so.length(); i++)
        if (so[i]!='-') sook=sook+so[i];
      for (unsigned int i=0; i<sc.length(); i++)
        if (sc[i]!='-') scok=scok+sc[i];
                                 
      if (sook!=scok) {
        exit(-1);
      }
    }
    else {
      cout << \"Fichero \" << argv[1] << \" o \" << argv[2] << \" no encontrado\" << endl;
      exit(-1);
    }
  }
  exit(0);
  return salida;
}
" > comparefiles.cc

g++ -o comparefiles comparefiles.cc

fi
}



function redondear()
{
  ntrunc=`echo - | awk -v K=$1 '{printf("%d",K)}'`
  nred=`echo - | awk -v K=$1 -v M=0.05 '{printf("%d",K+M)}'`

  if test "$ntrunc" != "$nred"; then
    echo $nred
  else
    echo $1
  fi
}

#-----------------------------------------------------------------

function pruebaok() {
        echo "OK"
        let pok++
}


function pruebasES() {
  # Ejecucion y comprobacion de la salida

  echo

  echo
  echo "*********************************************************"
  echo " Ejecutando partidas de prueba (entrada/salida)"
  echo "*********************************************************"
  
  pok=0
  for i in `ls $ENT`
  do
        bn=$(basename $i .txt)

	echo "Prueba $bn"

	tempfile=`mktemp /tmp/prog2iiXXXXX`

	# Ejecucion del programa
	$mata $MAXTIME $OBT/${bn}.salida-obtenida $VAL ./$EXE < $ENT/$i > $OBT/${bn}.salida-obtenida 2> $tempfile

	if test -s $tempfile; then
		echo "ERROR DE EJECUCION..."
		cat $tempfile
		rm -rf $OBT/${bn}.salida-obtenida $tempfile
	else
		$comparefiles $OBT/${bn}.salida-obtenida $SAL/${bn}.salida-esperada
		if [ $? -ne 0 ]; then
			diff -EwB $OBT/${bn}.salida-obtenida $SAL/${bn}.salida-esperada 2>&1
		else
  		  pruebaok $i
		fi
	fi
	echo "--------------------------"
  done

  if [ $pok -eq $npruebasES ]; then
	echo -e "\nTODAS LAS PRUEBAS DE PARTIDAS DEL AUTOCORRECTOR FUNCIONAN\n"
  else
	echo -e "\nOJO: FALLAN" $[npruebasES-pok] "PRUEBAS DE PARTIDA DEL AUTOCORRECTOR\n"
  fi
}

function pruebasUnitarias() {

  echo "*********************************************************"
  echo " Ejecutando las pruebas unitarias del autocorrector..."
  echo "*********************************************************"

  pok=0
  npruebasUnitarias=0
  tempfile=`mktemp /tmp/prog2iiXXXXX`
  tempfile2=`mktemp /tmp/prog2iiXXXXX`
  for i in "${pruebasAuto[@]}" ; do
    let npruebasUnitarias++
    if test -s ./$i ; then
  
      $mata $MAXTIME $tempfile2 $VAL ./$i > $tempfile2 2> $tempfile
      sgr=$(grep "\.OK\!$" $tempfile)
  
      if test "$sgr" != "" ; then
        echo "$i OK"
        let pok++
      else
       echo -e "\nFALLA LA PRUEBA UNITARIA $i DEL AUTOCORRECTOR:\n"
         cat $tempfile
       echo

      fi

      rm -f $tempfile
      rm -f $tempfile2

    else
      echo "NO COMPILA LA PRUEBA UNITARIA $i DEL AUTOCORRECTOR"
    fi
  done

  if [ $pok -eq $npruebasUnitarias ]; then
	echo -e "\nTODAS LAS PRUEBAS UNITARIAS DEL AUTOCORRECTOR FUNCIONAN\n"
  else
	echo -e "\nOJO: FALLAN" $[npruebasUnitarias-pok] "PRUEBAS UNITARIAS DEL AUTOCORRECTOR\n"
  fi


}

echo "*********************************************************"
echo "Autoorrector P2p3"


# Comprobar si está valgrind instalado
hayValgrind=$(which valgrind)
if test "$hayValgrind" == "" ; then
  echo "AVISO: El corrector se ejecutará sin valgrind, por lo que es posible que"
  echo "el resultado de la corrección no sea fiable. Para comprobar realmente que la"
  echo "práctica es correcta, debes probar el corrector en un ordenador Linux"
  echo "con valgrind instalado antes de la entrega."
  echo
  read -p "Pulsa [Enter] para continuar"
  VAL=""
fi


echo " Generando ficheros auxiliares... "
genMata
genComparefiles
rm -f mata.c
rm -f comparefiles.cc

# Compilacion
echo
echo "*********************************************************"
echo " Compilando..."
echo "*********************************************************"

cd ..  # los fuentes están en el directorio superior
compilarPruebasUnitarias
echo
echo "Compilando $EXE"
make -f $meikfail $EXE 2>&1
mv $EXE $autoco
cd -


pruebasES          # pruebas de partidas (entrada/salida)
pruebasUnitarias

# Clean all temporal files
rm -rf mata comparefiles "${pruebasAuto[@]}" $EXE
rm -f ../*.o
