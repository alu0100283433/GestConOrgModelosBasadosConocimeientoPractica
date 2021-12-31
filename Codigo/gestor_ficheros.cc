
// Declaración/Implementación de las funciones miembro de la clase
// GestorFicheros que se encuentra en el fichero gestor_ficheros.h

#include "gestor_ficheros.h"

// El bool identifica si el fichero se abre en modo lectura o en escritura
//------------------------------------------------------------------------------
GestorFicheros::GestorFicheros(bool modo, char* fichero) { 
  // modo = 0 -> Lectura
  // modo = 1 -> Escritura
  if (modo == 0) 
    flectura_.open(fichero, std::ifstream::in);

    if(flectura_.is_open()) {
      flectura_abierto_ = true;
    }
  else
    fescritura_.open(fichero, std::ofstream::out);
}

// Lee una linea del fichero cada vez. Devuelve un false cuando ha llegado al
// final del fichero.
//------------------------------------------------------------------------------
bool GestorFicheros::LeerLinea(std::string& guarda_linea) {
  std::getline(flectura_, guarda_linea);

  if (flectura_) { 
    return true;
  }

  flectura_.close();
  return false;
}
