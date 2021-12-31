
// Declaración/Implementación de las funciones miembro de la clase
// Similitud que se encuentra en el fichero similitud.h

#include "sim_coseno.h"

// Constructor.
//------------------------------------------------------------------------------
SimilitudCoseno::SimilitudCoseno(std::vector<mapa_t> documentosTabla) {

  std::cout << "\n\n";
  //  Vuelca los valores que nos interesan (palabras y sus TF) en una
  // lookup table atributo de esta clase.
  VolcarMatrizLookup(documentosTabla);

  NormalizarTF();

  NormalizarTerminos();

  CalcularSimCoseno();

  MostrarTablaSimilitudes();
}

//  Un método que copia la tabla con los datos de palabras y frecuencias
// de cada documento pero sin incluir los IDF y TF-IDF
//------------------------------------------------------------------------------
void SimilitudCoseno::VolcarMatrizLookup(std::vector<mapa_t> documentosTabla) {
  for (int i = 0; i < documentosTabla.size();  ++i) {
    mapa_t docActual = documentosTabla[i];
    mapaLookup_t docAux;
    mapa_t::iterator itDoc;

    for (itDoc = docActual.begin(); itDoc != docActual.end(); ++itDoc) {
      int tf = std::get<0>(itDoc->second);

      docAux.insert({itDoc->first, tf});
    }

    m_lookupTable.push_back(docAux);
  }
}

// Normaliza los valores TF de la LookUp Table que tenemos como atributo.
//------------------------------------------------------------------------------
void SimilitudCoseno::NormalizarTF() {
  for (int i = 0; i < m_lookupTable.size();  ++i) {
    mapaLookup_t docActual = m_lookupTable[i];
    mapaLookup_t docAux;
    mapaLookup_t::iterator itDoc;

    for (itDoc = docActual.begin(); itDoc != docActual.end(); ++itDoc) {
      double tfTransformado = 1 + log10(itDoc->second);

      docAux.insert({itDoc->first, tfTransformado});
    }

    m_lookupTable[i] = docAux;
  }
}

// Calcula el vector normalizado de cada término de cada documento a partir
// de los TF normalizados de 'm_lookupTable'
//------------------------------------------------------------------------------
void SimilitudCoseno::NormalizarTerminos() {
  for (int i = 0; i < m_lookupTable.size();  ++i) {
    mapaLookup_t docActual = m_lookupTable[i];
    mapaLookup_t docAux;
    mapaLookup_t::iterator itDoc;

    double longitudVector = 0;

    // Calculando la longitud del vector del documento (Length of Vector) (1)
    for (itDoc = docActual.begin(); itDoc != docActual.end(); ++itDoc) {
      longitudVector += (itDoc->second * itDoc->second);
    }

    // Calculando 'Length of Vector' (2)
    longitudVector = sqrt(longitudVector);

    // Calculando la normalización de cada término.
    for (itDoc = docActual.begin(); itDoc != docActual.end(); ++itDoc) {
      double terminoTransformado = (itDoc->second) / longitudVector;

      docAux.insert({itDoc->first, terminoTransformado});
    }

    m_lookupTable[i] = docAux;
  }
}

//  Calcula la "similaridad coseno" para todas las combinaciones de pares de
// documentos y guarda los resultados en una tabla, el atributo
// 'm_tablaSimilitudes'
//------------------------------------------------------------------------------
void SimilitudCoseno::CalcularSimCoseno() {
  // Como si recorriéramos las filas de la tabla
  for (int i = 0; i < m_lookupTable.size();  ++i) {
    // 1º Documento a comparar : A1.
    mapaLookup_t docA1 = m_lookupTable[i];

    mapaLookup_t::iterator itDoc;

    double simCoseno = 0;

    std::vector<double> filaSimCoseno;

    // Como si recorriéramos las columnas de la tabla
    for (int j = 0; j < m_lookupTable.size(); ++j) {
      // 2º Documento a comparar : A2.
      mapaLookup_t docA2 = m_lookupTable[j];

      // Recorremos todas las palabras/términos de A1 con el iterador.
      for (itDoc = docA1.begin(); itDoc != docA1.end(); ++itDoc) {
        // Comprobamos si la palabra actual de A1 está en A2 : Si es así,
        // hacemos el cálculo intermedio de 'simCoseno'. En caso contrario
        // no se hace nada.

        mapaLookup_t::iterator itPalabra = docA2.find(itDoc->first);

        if (itPalabra != docA2.end()) {
          simCoseno += (itDoc->second * itPalabra->second);
        }
      }

      //  Se supone que tenemos por aquí el resultado a insertar en la celda
      // de la tabla 'm_tablaSimilitudes', así que hacemos eso.
      filaSimCoseno.push_back(simCoseno);
      simCoseno = 0;
    }

    // Insertar fila en tabla de simCoseno.
    m_tablaSimilitudes.push_back(filaSimCoseno);
  }

}

// Muestra el contenido de la tabla Lookup
//------------------------------------------------------------------------------
void SimilitudCoseno::MostrarLookup() {
  for (int i = 0; i < m_lookupTable.size();  ++i) {
    int contador = 1;
    std::cout << " Documento " << i+1 << " :\n";
    std::cout << " -------------\n";

    mapaLookup_t docActual = m_lookupTable[i];
    mapaLookup_t::iterator itDoc;

    for (itDoc = docActual.begin(); itDoc != docActual.end(); ++itDoc) {
      std::cout << "|" << contador << "| - ";
      std::cout << "{ " << itDoc->first << ", " << itDoc->second << " }\n";
      ++contador;
    }

    std::cout << "\n\n";
  }
}

// Muestra la tabla con los datos de similitudes entre pares de documentos.
//------------------------------------------------------------------------------
void SimilitudCoseno::MostrarTablaSimilitudes() {
  std::cout << "       ";
  for (int i = 0; i < m_tablaSimilitudes.size();  ++i) {
    std::cout << "(D" << i+1 << ")  ";
  }

  std::cout << "\n";

  for (int i = 0; i < m_tablaSimilitudes.size();  ++i) {
    std::vector<double> filaTablaSim = m_tablaSimilitudes[i];

    std::cout << "(D" << i+1 << ")  |";

    for (int j = 0; j < filaTablaSim.size(); ++j) {
      std::cout << " " << filaTablaSim[j] << " ";

      if (j < (filaTablaSim.size() - 1)) std::cout << "||";
    }

    std::cout << "|";

    std::cout << "\n";
  }
}
