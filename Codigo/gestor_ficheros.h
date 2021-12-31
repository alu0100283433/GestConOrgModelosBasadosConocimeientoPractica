
/*
  Universidad de la Laguna
  Escuela de Ingenieria y Tecnologia
  Autor: Manuel Ramón Regalado Peraza
  Datos de contacto: alu00100283433@ull.edu.es
  Fecha:
  Asignatura:
  Curso:
  Práctica:
  Finalidad del código: Fichero con la declaración de una clase que abre un
                        fichero en modo lectura y otro en escritura y lee y
                        escribe los mismos. Puede leer el fichero línea a
                        línea o carácter a carácter.
*/

#ifndef GESTOR_FICHEROS_H
#define GESTOR_FICHEROS_H

#include <fstream>
#include <string>

//345678901234567890123456789012345678901234567890123456789012345678901234567890

// Esta clase se dedica a gestionar las operaciones de apertura de 
// los ficheros de entrada y salida. 
// La lectura consiste en leer línea a línea el fichero, cada línea un lenguaje 
// La escritura consiste en escribir en el fichero de salida 
// las operaciones resultantes con Lenguajes 
class GestorFicheros {
 private: 
  std::ifstream flectura_;  // El flujo del fichero abierto en modo lectura
  std::ofstream fescritura_;  // El flujo del fichero abierto en modo escritura 
  bool flectura_abierto_ = false;  // Hasta que no se pueda abrir el 1º fich.
                                   // de lectura seguirá en estado false.

 public:
  // Constructor. Abrirá sólo un único fichero y le especificamos
  // si se quiere abrir en modo lectura o en modo escritura.
  GestorFicheros(bool modo, char* fichero); 
  ~GestorFicheros () {}

  bool LeerLinea(std::string& guarda_linea);
  bool IsF1Open() { return flectura_abierto_; }
};

#endif
