
/*
  Universidad de la Laguna
  Escuela de Ingenieria y Tecnologia
  Autor: Manuel Ramón Regalado Peraza
  Datos de contacto: alu00100283433@ull.edu.es
  Fecha:
  Asignatura:
  Curso:
  Práctica:
  Finalidad del código: Contiene las funciones de similitud. Y
                        También guarda los valores generados con
                        esas funciones para cada uno de los
                        usuarios/vecinos.
*/

/*
  + NOTAS : 
 Vamos a necesitar dos "tablas" como atributos de la clase :

  - Una "tabla", que va a servir como "lookup table" con los valores
 del vector normalizado.

  - Otra "tabla", que usa la anterior para generar todos los valores
 de similitud coseno entre pares de documentos. Esta tabla será
 de tamaño regular (n x n), conteniendo cada celda el valor de similitud
 coseno entre el documento de la fila 'i' con el documento de la columna
 'j'. Tanto en la fila como en la columna tendremos los mismos documentos
 (filas : documento 1 a documento n; columnas : documento 1 a documento n).

  Método que genera la función del coeficiente de correlación de Pearson para
 cada una de los otras personas/usuarios distintas al usuario actual. Los
 usuarios sin puntuación distintos al que se calcula no se tienen en cuenta.
*/

#ifndef SIM_COSENO_H 
#define SIM_COSENO_H

#include <map>
#include <cmath>

#include "matriz.h"

using matrizDouble_t = std::vector<std::vector<double>>;

using mapaLookup_t = std::map<std::string, double>;
using vMapaLookup_t = std::vector<mapaLookup_t>;

class SimilitudCoseno {
  private:
    // Donde guardaremos los valores intermedios
    vMapaLookup_t m_lookupTable;

    //  En esta matriz/tabla de 'n x n' se guardarán en cada celda las
    // similitudes entre documentos/artículos.
    matrizDouble_t m_tablaSimilitudes;

    //  Copia los datos del mapa con los documentos, pero sólo las palabras
    // y el TF, el resto (IDF, TF-IDF) se descarta. Se vuelva entonces en
    // 'm_lookupTable'.
    void VolcarMatrizLookup(std::vector<mapa_t> documentosTabla);

    //  Normaliza los valores de los TF de cada término de cada documento
    // según la fórmula '1 + log(TF)' que aparece en la página 130 de los
    // apuntes. Los valores a normalizar están en 'm_lookupTable'
    void NormalizarTF();

    // Calculamos el vector normalizado de cada término a partir de cada
    // TF normalizado de un documento de 'm_lookupTable'. Los resultados
    // nuevos se sustituyen por los anteriores en 'm_lookupTable'
    void NormalizarTerminos();

    //  Rellena la tabla/matriz 'm_tablaSimilitudes' con los cálculos de la
    // similaridad entre los documentos mediante el coseno. Siendo la
    // matriz regular 'n x n' en el que la celda (i,j) contiene la similitud
    // entre el documento i (fila) y el documento j (columna). La filas y las
    // columnas representan los mismos documentos en el mismo orden.
    void CalcularSimCoseno();

    void MostrarLookup();

    void MostrarTablaSimilitudes();
  public:
    SimilitudCoseno(std::vector<mapa_t> documentosTabla);
};

#endif
