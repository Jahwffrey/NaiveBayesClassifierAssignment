all: main	

main: main.cpp
	g++ main.cpp -o NaiveBayesClassifier

clean:
	rm NaiveBayesClassifier
