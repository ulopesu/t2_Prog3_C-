COMPILADOR := g++ -std=c++11
all:	build clean


build:
	@$(COMPILADOR) util/*.cpp -c -g
	@$(COMPILADOR) execoes/*.cpp -c -g
	@$(COMPILADOR) inOut/*.cpp -c -g
	@$(COMPILADOR) prprof/*.cpp -c -g
	@$(COMPILADOR) *.cpp -c -g
	@$(COMPILADOR) *.o -o trabalhoC++ -g
run:
	@./trabalhoC++ -d docentes.csv -p publicacoes.csv -v veiculos.csv -q qualis.csv -r regras.csv -a 2017
clean:
	@rm -f *.o
