all: main	

main: main.o review.o
	g++ main.o review.o -o NaiveBayesClassifier

main.o: main.cpp review.h
	g++ -c main.cpp

review.o: review.cpp review.h
	g++ -c review.cpp

clean:
	rm NaiveBayesClassifier
	rm *.o
