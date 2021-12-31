
/*
  Universidad de la Laguna
  Escuela de Ingenieria y Tecnologia
  Autor: Manuel Ramón Regalado Peraza
  Datos de contacto: alu00100283433@ull.edu.es
  Fecha:
  Asignatura:
  Curso:
  Práctica:
  Finalidad del código:
*/

#include <iostream> 
#include <string>

#include <map>
#include <tuple>

#include <algorithm>


#include "matriz.h"
#include "sim_coseno.h"

//Los números de argumentos pasados por terminal
int UN_ARG     = 1;
int DOS_ARG    = 2;
int TRES_ARG   = 3;
int CUATRO_ARG = 4;
int CINCO_ARG = 5;

// Cuando se pasa el comando de ayuda
std::string HELP = "--help";

//345678901234567890123456789012345678901234567890123456789012345678901234567890

// Este mensaje siempre se muestra cuando escribamos sólo el ejecutable, si se
// pasó un segundo argumento que no sea '--help' y cuando se use un número
// mayor de 4 argumentos
//------------------------------------------------------------------------------
void mensaje () {
  std::cout << "\n -Modo de empleo: '$ ./Ejecutable documentos.txt'\n\n";
  std::cout << "(Pruebe '$ ./CalcSim --help' para más información)\n";
}

// Este mensaje aparecerá por la terminal siempre que se escriba
// './main --help'
//------------------------------------------------------------------------------
void mensaje_ayuda () {
  std::cout << "\n\tPractica : Sistemas de recomendacion. Modelos basados en contenidos\n";
  std::cout << "\t-------------------------------------------------------------------\n";
  std::cout << "\n\t  Utilidad que recibe un fichero 'txt' con una serie de documentos";
  std::cout << "\n\t y genera valores de pesos (frecuencias) y similitudes de sus";
  std::cout << "\n\t terminos.";
  std::cout << "\n\t\n";
}

//------------------------------------------------------------------------------
int main (int argc, char* argv[]) {

  std::string aux = std::to_string(3);
  std::vector <std::vector<std::string>> vectorDeDocumentos;
  std::vector <Matriz> vectorDeTablas; // Guarda cada tabla de cada documento.
  std::vector<std::string> documentos;

  // Si sólo se ha pasado el ejecutable. 
  if (argc == UN_ARG) {
    mensaje();
  } else if (argc == DOS_ARG) {           // Si se han pasado 2 argumentos
    aux = argv[1];

    if (aux == HELP) {                    // Si se ha invocado la ayuda 
      mensaje_ayuda();
    } else {

      std::cout << "\n - Datos de los documentos - \n";
      std::cout << "------------------------------------------------------------\n";
      std::cout << "------------------------------------------------------------\n";

      // Generación de la matriz con datos de recomendación.
      Matriz matriz(argv[1]);

      std::cout << "\n - Datos de similaridades coseno - \n";
      std::cout << "------------------------------------------------------------\n";
      std::cout << "------------------------------------------------------------\n";

      // Generación de la matriz con los datos de la similitud coseno.
      SimilitudCoseno sm(matriz.getMapa());
    }
  } else {                                // nº de argumentos incorrecto
    mensaje();
  }

  std::cout << '\n';

  return 0;
}
