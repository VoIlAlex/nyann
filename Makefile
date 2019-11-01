bin/main: bin/intermediate/main.o bin/intermediate/io_draft.o
	g++ -g -std=c++17 -lstdc++fs bin/intermediate/main.o bin/intermediate/io_draft.o -o bin/main.exe

bin/intermediate/main.o: nya-nn/nyann.h nya-nn/examples/labs.h nya-nn/nyann/drafts.h bin/intermediate/io_draft.o
	g++ -g -std=c++17 -lstdc++fs -c nya-nn/main.cpp -o bin/intermediate/main.o

# Draft stuff
bin/intermediate/io_draft.o: nya-nn/nyann/drafts/DataSet_draft.h nya-nn/nyann/drafts/io_draft.cpp nya-nn/nyann/drafts/io_draft.h
	g++ -g -std=c++17 -c nya-nn/nyann/drafts/io_draft.cpp -o bin/intermediate/io_draft.o

clear:
	sh clear.sh
	
	

run: bin/main.exe
	./bin/main.exe