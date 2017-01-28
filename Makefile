all: main	

main: main.o review.o trie.o
	g++ main.o review.o trie.o -o NaiveBayesClassifier

main.o: main.cpp review.h trie.h
	g++ -c main.cpp

review.o: review.cpp review.h
	g++ -c review.cpp

trie.o: trie.cpp trie.h
	g++ -c trie.cpp

clean:
	rm NaiveBayesClassifier
	rm *.o
