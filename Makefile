bin/main: bin/intermediate/main.o bin/intermediate/io_draft.o
	g++ -g -std=c++17 -lstdc++fs bin/intermediate/main.o bin/intermediate/io_draft.o -o bin/main.exe

bin/intermediate/main.o: nyann/nyann.h nyann/nyann-examples/labs.h nyann/nyann/drafts.h bin/intermediate/io_draft.o
	g++ -g -std=c++17 -lstdc++fs -c nyann/main.cpp -o bin/intermediate/main.o

# Draft stuff
bin/intermediate/io_draft.o: nyann/nyann/drafts/DataSet_draft.h nyann/nyann/drafts/io_draft.cpp nyann/nyann/drafts/io_draft.h
	g++ -g -std=c++17 -c nyann/nyann/drafts/io_draft.cpp -o bin/intermediate/io_draft.o

clear:
	sh clear.sh
	
package: 
	mkdir -p build/nyann
	mkdir -p build/nyann/nyann
	cp -r nyann/nyann build/nyann/
	cp nyann/nyann.h build/nyann
	tar cvf build/nyann.tar.gz -C build nyann
	rm -rf build/nyann

run: bin/main.exe
	./bin/main.exe