/*
  Universidad de la Laguna
  Escuela de Ingenieria y Tecnologia
  Autor: Manuel Ramón Regalado Peraza
  Datos de contacto: alu00100283433@ull.edu.es
  Fecha:
  Asignatura:
  Curso:
  Práctica:
  Finalidad del código: Se encarga de abrir ficheros .txt con la matriz
                        y cargar esos datos en una estructura que simula
                        esa matriz.
*/

//------------------------------------------------------------------------------

//345678901234567890123456789012345678901234567890123456789012345678901234567890

// NOTA : Prefijo m_ indica que la variable es un miembro de la clase.

#ifndef MATRIZ_H 
#define MATRIZ_H

#include <string>
#include <vector>
#include <iostream>
#include <set>

#include <tuple>
#include <map>
#include <locale> // Para tolower()

#include "gestor_ficheros.h"

// Alias.
using vectorString_t = std::vector<std::string>;
using tupla_t = std::tuple<int, double, double>;
using mapa_t = std::map<std::string, tupla_t>;

//  Esta clase se encargará de cargar los datos del fichero .txt con la matriz,
// y guardar esos datos en una estructura tipo "vector" bidimensional.
class Matriz {
 private:

  // Puntero a objeto dinámico que gestiona todas las operaciones de ficheros 
  GestorFicheros* m_gestor_ficheros;  

  // Guarda las "stop words" (and , with, of, ...) aquí.
  std::vector<std::string> m_stopWords = {"a","an","and","with","this","these",
  "those","that","as","of","the","to","from","in","if"};

  //  Matriz de tipo std::map con la clave siendo la palabra la clave
  // y las frecuencias una tupla.
  std::vector<mapa_t> m_mapa;

  //  Hace la carga de los documentos en el fichero, procesa los datos y los
  // guarda en m_matriz.
  void CargarFicheroEnMatriz();

  //  Coge cada línea, que es un documento y separa las palabras en el orden
  // de aparición además de guardarlas en un vector de string>
  //std::vector<std::string> ExtraerPalabras(std::string linea);
  vectorString_t ExtraerPalabrasDocumento(std::string linea);

  // Elimina símbolos de puntuación finales de las palabras.
  vectorString_t EliminarPuntFin(vectorString_t listaPalabras);

  // Elimina los espacios sueltos o como parte de una palabra.
  vectorString_t EliminarEspaciosFinales(vectorString_t listaPalabras);

  // Todas las palabras de la lista a minúsculas.
  vectorString_t PasarAMinusculas(vectorString_t listaPalabras);

  vectorString_t EliminarStopWords(vectorString_t listaPalabras);

  //  Genera los elementos del mapa : Cada uno compuestos por la palabra,
  // que será la clave, y una tupla con las "frecuencias".
  mapa_t ContarPalabrasDocumento(vectorString_t words);

  //void CalcularIDF();
  // Cálculo del IDF y el TF-IDF tras obtener el TF.
  void CalcularFrecuencias();

  void MostrarMatrizDocumentos();
 public:
  // El constructor se encargará de abrir el fichero de lectura
  Matriz(char* entrada);
  ~Matriz() { delete m_gestor_ficheros; } 

  std::vector<mapa_t> getMapa() {return m_mapa;}
};

#endif
