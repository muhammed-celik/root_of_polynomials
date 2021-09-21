#include <iostream>
#include <string>
#include <cmath>
using namespace std;

double f(double x, double function[], int size);  // returns f(x) for corresponding input
double bisection(double guess1, double guess2, double tol, double coeffs[], double size);  // bisection function
double secant(double guess1, double guess2, double tol, double coeffs[], double size);  // secant function
double hybrid(double guess1, double guess2, double tol, double coeffs[], double size);  // hybrid method function

int main(int argc, char *argv[]){
    int i,num_of_coefficients;
    num_of_coefficients = argc-4;  // declaring a variable that holds the number of coefficients
    double guess1 = stod(argv[argc-3]); // taking other arguments...
    double guess2 = stod(argv[argc-2]);
    double tolerance = stod(argv[argc-1]);
    double zero_check = 0;  // to check if the given function is constant 0 function

    double* coeffs = new double [num_of_coefficients]; // declaring dynamically allocated array of coefficients
    
    
    for(i=1;i<=num_of_coefficients;i++){
        coeffs[num_of_coefficients-i] = stod(argv[i]); // assigning coefficients to array accordingly
        if (stod(argv[i]) != 0){
        	zero_check += 1;  // checking if all coefficients of the function are 0.
		}
    }
    if (zero_check == 0){ // if all coefficients are 0
    	cout << "User entered constant zero function. Its root is whole real axis." << endl; // print out result and quit
    	return 0;
	}
	
    cout << bisection(guess1, guess2, tolerance, coeffs, num_of_coefficients) << " is the root found in bisection method." << endl << endl; // printing out results
    cout << secant(guess1, guess2, tolerance, coeffs, num_of_coefficients) << " is the root found in secant method." << endl << endl; // printing out results
    cout << hybrid(guess1, guess2, tolerance, coeffs, num_of_coefficients) << " is the root found in hybrid method." << endl; // printing out results
 




    delete[] coeffs;  // deleting array
    return 0;
}

double f(double x, double function[], int size){ // getting f(x) result
    int i;
    double result = 0;
    for(i=size-1;i>=0;i--){
        result += pow(x,i) * function[i]; // adding all calculations term by term
    }
    return result;
}

double bisection(double a, double b, double tol, double coeffs[], double size){ // bisection algorithm from the textbook applied
    double m;
    int counter = 0;
    while (abs(b - a) > tol && counter < 10000){ // until achieving desired presicion or predefined number of iterations algorithm goes on.
        m = a + (b - a) / 2;
        if (f(a,coeffs,size) * f(m,coeffs,size) > 0){  // checking sign of the results
            a = m;
        }
        else{
            b = m;
        }
        counter++;  // counter is used to output the number of iterations as well as preventing infinite loop
    }
    if (counter == 10000){
    	cout << "The algorithm failed to converge or to converge fast enough !";
    	return 0;
	}
    cout << counter << " iterations made in the bisection method." << endl; 
    return m;
}

double secant(double guess1, double guess2, double tol, double coeffs[], double size){ // secant algorithm from the textbook applied
    double x_k = guess1;
    double x_k1 = guess2;
    double result = x_k1 - f(x_k1,coeffs,size)*((x_k1 - x_k)/(f(x_k1,coeffs,size) - f(x_k,coeffs,size))); // inital iteration applied
    int counter = 1;
    
    while(abs(result - x_k1) > tol && counter < 10000){ // until achieving desired presicion or predefined number of iterations algorithm goes on.
        x_k = x_k1;
        x_k1 = result;
        result = x_k1 - f(x_k1,coeffs,size)*((x_k1 - x_k)/(f(x_k1,coeffs,size) - f(x_k,coeffs,size))); // actual iterations
        counter++; // counter is used to output the number of iterations as well as preventing infinite loop
    }
    if (counter == 10000){
    	cout << "The algorithm failed to converge or to converge fast enough !";
    	return 0;
	}
	cout << counter << " iterations made in the secant method." << endl; 
    return result;

}

double hybrid(double a, double b, double tol, double coeffs[], double size){
    double m,n;
    int counter = 0;
    while (counter < 2){ // firstly 2 iterations made with bisection algorithm
        n = m;
        m = a + (b - a) / 2;
        if (f(a,coeffs,size) * f(m,coeffs,size) > 0){
            a = m;
        }
        else{
            b = m;
        }
        counter++;
    }

    double result = m - f(m,coeffs,size)*((m - n)/(f(m,coeffs,size) - f(n,coeffs,size))); // after 2 iterations, secant method is used
    counter++;
    while(abs(result - m) > tol && counter < 10000){
        n = m;
        m = result;
        result = m - f(m,coeffs,size)*((m - n)/(f(m,coeffs,size) - f(n,coeffs,size)));
        counter++; // counter is used to output the number of iterations as well as preventing infinite loop
    }
    if (counter == 10000){
    	cout << "The algorithm failed to converge or to converge fast enough !";
    	return 0;
	}
    cout << counter << " iterations made in the hybrid method." << endl; 
    return result;
}