CXX := g++
CXX_FLAGS := -std=c++17

MatrizContenidos: main.o gestor_ficheros.o matriz.o sim_coseno.o
	$(CXX) $(CXX_FLAGS) -o CalcSim main.o gestor_ficheros.o matriz.o sim_coseno.o

main.o: main.cc
	$(CXX) $(CXX_FLAGS) -c main.cc

matriz.o: matriz.cc matriz.h
	$(CXX) $(CXX_FLAGS) -c matriz.cc

gestor_ficheros.o: gestor_ficheros.cc gestor_ficheros.h
	$(CXX) $(CXX_FLAGS) -c gestor_ficheros.cc

sim_coseno.o: sim_coseno.cc sim_coseno.h
	$(CXX) $(CXX_FLAGS) -c sim_coseno.cc

# Colocada la opción -f a rm, así no muestra mensajes al intentar borrar
# ficheros inexistentes
clean:
	rm -f CalcSim main.o matriz.o gestor_ficheros.o sim_coseno.o
