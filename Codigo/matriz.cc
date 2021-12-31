
// Declaración/Implementación de las funciones miembro de la clase
// Matriz que se encuentra en el fichero matriz.h

#include <cmath> // Para usar log().

#include "matriz.h"

// Constructor.
//------------------------------------------------------------------------------
Matriz::Matriz(char* entrada) {
  // Abrimos el fichero de entrada en modo lectura.
  m_gestor_ficheros = new GestorFicheros(0, entrada);

  //  El proceso de leer las líneas del .txt, procesarlas  y guardarlas en
  // m_mapa.

  //  Extrae los datos de los documentos del .txt, los procesa y crea la
  // tabla final con los datos pedidos.
  CargarFicheroEnMatriz();

  //CalcularIDF();
  // Cálculo del IDF y del TF-IDF.
  CalcularFrecuencias();

  std::cout << "\n\n";

  MostrarMatrizDocumentos();
}

// Lee línea a línea el fichero .txt pasado, cada línea es un documento.
// Separa cada palabra del documento, analiza las veces que aparecen y genera
// con ello TF, IDF y TF-IDF.
//------------------------------------------------------------------------------
void Matriz::CargarFicheroEnMatriz()  {
  std::string linea;
  //std::vector<int> filaMatriz;
  std::vector<std::string> filaMatriz;
  bool finalizar = false;
  int contador = 0;

  std::cout << "\n\n";

  while (finalizar == false) {
    if (m_gestor_ficheros->LeerLinea(linea)) {
      contador++;

      // Muestro cada documento.
      std::cout << linea << "\n\n";

      //  Extrae todas las palabras de un documento y las guarda en el
      // mismo orden de extracción en un vector de std::string.
      //  Obviamente habrá palabras repetidas, sólo ha hecho la extracción.
      std::vector<std::string> palabras = ExtraerPalabrasDocumento(linea);

      // Elimina símbolos de puntuación.
      palabras = EliminarPuntFin(palabras);

      palabras = EliminarEspaciosFinales(palabras);

      palabras = PasarAMinusculas(palabras);

      palabras = EliminarStopWords(palabras);

      //  Crea un mapa (std::map) vacío , cada elemento es una palabra
      // única como clave y una tupla con los valores de las frecuencias.
      mapa_t vPalabrasVeces;

      //  Cuenta el número de veces que aparece cada palabra en el
      // documento y guarda como elemento del mapa, la palabra y el
      // número de veces repetido, el TF o frecuencia absoluta del término.
      vPalabrasVeces = ContarPalabrasDocumento(palabras);

      // Guardamos el mapa incompleto del documento actual en un vector.
      m_mapa.push_back(vPalabrasVeces);
    } else {
      finalizar = true;

      if (contador == 0) {
        std::cout << "Fichero vacío, incompleto o con datos distintos a los\n";
        std::cout << "de una matriz,.\n";
        std::cout << "Saliendo del programa.\n";
        // Parar la ejecución del programa y devolver un código de error -3.
        exit(-3);
      }
    }
  }
}

//  Recibe un string con todo el contenido del documento y separa cada palabra
// una a una.
//------------------------------------------------------------------------------
std::vector<std::string> Matriz::ExtraerPalabrasDocumento(std::string linea) {
  std::vector<std::string> palabrasLinea;
  std::string espacio = " ";

  int ini = 0;
  int fin = 0;

  // Una idea de Internet : Usar el "find()" junto con el "substr()"

  // Busca la posición del primer espacio.
  fin = linea.find(espacio);

  //  Mientras siga encontrando espacios intenta extraer la posible
  // palabra que esté justo después del espacio anterior y este
  // espacio actual.
  while (fin != -1) {
    // Extraigo la palabra entre dos espacios
    std::string palabra = linea.substr(ini, fin - ini);

    palabrasLinea.push_back(palabra); 

    // Recalcular "ini" y "fin"
    // 'ini' ahora es la primera pos. de la nueva palabra a extraer.
    ini = fin + espacio.size();
    //  'fin' ahora es la posición del nuevo espacio, una pos. sig.
    // al último caracter de la nueva palabra a extraer.
    fin = linea.find(espacio, fin + espacio.size());
  }

  //  Nota : Falta la última palabra del documento, que no se suele insertar
  // con el bucle anterior.
  palabrasLinea.push_back(linea.substr(ini, linea.size() - ini));

  return palabrasLinea;
}

//  Elimina los símbolos de puntuación finales de las palabras de la lista de
// palabras.
//------------------------------------------------------------------------------
vectorString_t Matriz::EliminarPuntFin(vectorString_t listaPalabras) {
  vectorString_t palabrasLimpias;

  char coma = ',';
  char punto = '.';
  char puntoComa = ';';
  char dosPuntos = ':';
  char interrogacion = '?';

  for (int i = 0; i < listaPalabras.size(); ++i)  {
    std::string palabra = listaPalabras[i];

    // Último carácter de la palabra.
    char uC = palabra[palabra.size() - 1];
    if (uC == coma || uC == punto || uC == puntoComa ||
        uC == dosPuntos || uC == interrogacion) {
      palabra.pop_back();
    }

    // Asegurarnos que la palabra no fuera sólo un símbolo de puntuación.
    if (palabra.size() > 0) palabrasLimpias.push_back(palabra);
  }

  return palabrasLimpias;
}

//------------------------------------------------------------------------------
vectorString_t Matriz::EliminarEspaciosFinales(vectorString_t listaPalabras) {
  vectorString_t palabrasLimpias;

  for (int i = 0; i < listaPalabras.size(); ++i)  {
    std::string palabra = listaPalabras[i];

    // Último carácter de la palabra.
    char uC = palabra[palabra.size() - 1];
    if (uC == ' ') {
      palabra.pop_back();
    }

    // Asegurarnos que la palabra no fuera sólo un espacio.
    if (palabra.size() > 0) palabrasLimpias.push_back(palabra);
  }

  return palabrasLimpias;
}

//------------------------------------------------------------------------------
vectorString_t Matriz::PasarAMinusculas(vectorString_t listaPalabras) {
  vectorString_t palabrasLimpias;

  std::locale loc; // Parece necesario.

  for (int i = 0; i < listaPalabras.size(); ++i)  {
    std::string palabraAux = listaPalabras[i];
    std::string palabra = "";

    for (int j = 0; j < palabraAux.length(); ++j) {
      palabra += std::tolower(palabraAux[j], loc);
    }

    // Asegurarnos que la palabra no fuera sólo un espacio.
    if (palabra.size() > 0) palabrasLimpias.push_back(palabra);
  }

  return palabrasLimpias;
}

// Elimina las StopWords de la lista de palabras del documento.
//------------------------------------------------------------------------------
vectorString_t Matriz::EliminarStopWords(vectorString_t listaPalabras) {
  vectorString_t palabrasLimpias;

  for (int i = 0; i < listaPalabras.size(); ++i)  {
    std::string palabraActual = listaPalabras[i];
    bool esSW = false;

    for (int k = 0; k < m_stopWords.size(); ++k) {
      if (palabraActual == m_stopWords[k]) esSW = true;
    }

    if (esSW == false) palabrasLimpias.push_back(palabraActual);
  }

  return palabrasLimpias;
}

//  De las palabras de un documento pasado por argumento creará una estructura
// donde guardará cada palabra/término del mismo, sin repetir, y las veces
// que aparecieron en el documento en una estructura tipo mapa (el término es
// la clave y las veces repetidas el TF).
//------------------------------------------------------------------------------
mapa_t Matriz::ContarPalabrasDocumento(vectorString_t words) {
  mapa_t palabrasVeces;
  tupla_t tupla;

  for (int i = 0; i < words.size(); ++i) {
    std::string palabraActual = words[i];
    bool encontrado = false;

    // Si la palabra ya había sido insertada en el std::map...
    // Es decir : Si ya existía.
    mapa_t::iterator itPalabra = palabrasVeces.find(palabraActual);

    if(itPalabra != palabrasVeces.end()) {
      encontrado = true;
      //  Extraigo e incremento en uno el número de veces repetidas de la
      // palabra.
      int incremento = std::get<0>(itPalabra->second);
      tupla_t tupla_aux(++incremento, 0.0, 0.0);

      itPalabra->second = tupla_aux;
    } else {
      encontrado = false;
    }

    // Si no existe la palabra en el vector de mapas  ...
    if (encontrado == false) {
      std::pair<std::string,int> parInsertar;

      tupla_t tupla_aux(1, 0.0, 0.0);
      mapa_t mapaInsertar = {{palabraActual, tupla_aux}};

      palabrasVeces.insert({palabraActual, tupla_aux});
    }
  }

  return palabrasVeces;
}

//------------------------------------------------------------------------------
//void Matriz::CalcularIDF() {
void Matriz::CalcularFrecuencias() {
  const int n = m_mapa.size();

  // Recorrer documento a documento
  for (int i = 0; i < n; ++i) {
    mapa_t docActual = m_mapa[i];
    mapa_t::iterator it;
    
    // Recorrer palabra a palabra del doc actual.
    for (it = docActual.begin(); it != docActual.end(); ++it) {
      std::string palActual = it->first;
      // Veces que aparece el término actual del doc. en el resto de docs.
      int dfx = 1;

      //  Teniendo la palabra actual hay que buscar si existe en
      // el resto de documentos al actual.
      for (int k = 0; k < n; ++k) {
        // No comparar el documento actual (docActual) consigo mismo.

        if (k != i) {
          mapa_t docComparar = m_mapa[k];
          mapa_t::iterator itPalabraBuscar = docComparar.find(palActual);

          // Si la palabra existe.
          if (itPalabraBuscar != docComparar.end()) dfx++;
        }
      }

      //const double idf = log(double(n)/double(dfx)); // logaritmo neperiano
      const double idf = log10(double(n)/double(dfx)); // logaritmo común (log).

/*
      std::cout << "   --| " << palActual << ":";
      std::cout << " log(" << n << "/" << dfx << ") : ";
      std::cout << idf << "  ~~ " << std::get<0>(it->second) << ".\n";
*/

      //  Añadimos el valor calculado del IDF a los datos de la palabra del doc.
      // actual.
      const int tf = std::get<0>(it->second);
      // Calculamos de paso el TF-IDF
      //const double tf_idf = std::get<2>(it->second);
      const double tf_idf = tf * idf;

      it->second = std::make_tuple(tf, idf, tf_idf);

      //  Como lo que se ha modificado es una copia de la "tabla" del documento
      // debemos sobreescribir los datos en el vector de mapas original.
      m_mapa[i] = docActual;
    }

    //std::cout << "\n\n";
  }

}


//  Muestra la matriz que contiene los documentos y las veces que se repiten
// cada término.
//------------------------------------------------------------------------------
void Matriz::MostrarMatrizDocumentos() {

  for (int i = 0; i < m_mapa.size(); ++i) {
    mapa_t datosDocumento = m_mapa[i];
    mapa_t::iterator it;

    int nTermino = 1;

    std::cout << "Documento " << i+1 << " : \n";
    std::cout << "--------------\n";
    std::cout << "\n";

    for (it = datosDocumento.begin(); it != datosDocumento.end(); ++it) {
      int tf;
      double idf;
      double tf_idf;

      //  Extrae directamente cada uno de los campos de la tupla en el mismo
      // orden en el que estaban en la estructura.
      std::tie(tf, idf, tf_idf) = it->second;

      std::cout << "|"  << nTermino << "| -  ";
      std::cout << "{ " << it->first << ", (";
      std::cout << tf << ", " << idf << ", " << tf_idf; 
      std::cout << ")} \n";

      nTermino++;
    }

    std::cout << "\n\n";
  }
}
