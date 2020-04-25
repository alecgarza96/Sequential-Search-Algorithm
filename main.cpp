//
//  Name:                Alec Garza
//
//  Program Description: This program prompts the user for input data related to packages that are to be shipped.
//                       The data is verified and then assigned the appropriate shipping cost determined by the
//                       sequential search algorithm. Information about the transaction is printed and the user is
//                       prompted to enter another transaction or exit the program.
//
//  Program Status:      Complete
//

#include <iostream>
#include <string>
using namespace std;

//create struct data type to hold shipping weight/cost data
struct Packages{
    int weight;
    float cost;
};

//function to verify package dimensions are valid
//input: integer array
//processing: count-controlled loop to verify dimension requirements
//output: boolean verification status variable
bool verifiedPkg(int dim[], int weight){
    bool verified = false;
    bool verifyDim = false; //set boolean value to false
    bool verifyWeight = false;
    int reject = 0;
    
    for(int i = 0; i < 3; i++){
        if(dim[i] > 36){
            reject += 1;
        }
    }
    
    if(reject > 0){
        verifyDim = false;
    }
    else{
        verifyDim = true;
    }
    
    if(weight <= 50){
        verifyWeight = true;
    }
    else{
        verifyWeight = false;
    }

    if(verifyWeight == true && verifyDim == true){
        verified = true;
    }
    else{
        verified = false;
    }
    return verified;
}


//function that verifies girth measurements of package
//input package girth
//processing set boolean flag to true if package girth is less than 60
//output return verification status
bool verifyGirth(int pkgGirth){
    bool verified = false;
    
    if(pkgGirth <= 60){
        verified = true;
    }
    
    return verified;
}


//function to format and display output
//input: transaction number, status, package weight, and package cost
//processing: format and display output
//output: print data
void displayOutput(int txnNum, string status, int pkgWeight, float pkgCost){
    cout << "Transaction: " << txnNum << endl;
    cout << "Status: " << status << endl;
    cout << "Weight: " << pkgWeight << endl;
    cout << "Cost: " << pkgCost << endl;
}


//sequential search function
//input: packages array, weight of package, and size of array
//processing: utilize sequential search algorithm to determine accurate pricing based on weight
//output: return index position of price
int search(const Packages rates[], int weight, int size){
    bool found = false;
    int position = -1;
    int i = 0;
    
    while(i < size && !found){
        if(weight <= rates[i].weight){
            found = true;
            position = i;
        }
        i++;
    }
    return position;
}

//calculate girth of package
//input: array holding package dimensions
//processing: get sum of array, and largest dimension, then calculate girth
//output: return girth
int girth(const int dimensions[]){
    int girth;
    int sum = 0;
    int largest = dimensions[0];
    int size = 3;
    int i = 0;
    
    for(i = 0; i < size; i++){
        sum += dimensions[i];
    }
    
    for(i = 1; i < size; i++){
        if(largest < dimensions[i]){
            largest = dimensions[i];
        }
    }
    girth = 2*sum-largest;
    
    return girth;
}


int main(){
    
    
    int txnCount = 0, //accumulator for transaction count
        acceptedCount = 0, //accumulator for accepted transactions
        rejectedCount = 0, //accumulator for rejected transactions
        CHARGES = 15, //size declarator for struct-array package rates
        weight, //package weight
        length, //package length
        width, //package width
        height, //package height
        index, //index for package cost position in array
        pkgGirth; //package girth: 2*(length+width+height-largest)
    bool error, //flag for invalid user input
         verified, //flag indicating verification status
         girthVerified, //return verification of girth
         contLoop = true; //flag to control transaction processing loop
    int dimensions[3]; //array to store dimension values
    string statusMessage; //string to reflect status of transaction to user
    float pkgCost; //floating point variable to represent dollar cost of shipping package
    
    //initialize array of structs containing shipping weight/cost data
    Packages pkgRates[CHARGES];
    pkgRates[0] = {1, 1.50};
    pkgRates[1] = {2, 2.10};
    pkgRates[2] = {3, 4.00};
    pkgRates[3] = {5, 6.75};
    pkgRates[4] = {7, 9.90};
    pkgRates[5] = {10, 14.95};
    pkgRates[6] = {13, 19.40};
    pkgRates[7] = {16, 24.20};
    pkgRates[8] = {20, 27.30};
    pkgRates[9] = {25, 31.90};
    pkgRates[10] = {30, 38.50};
    pkgRates[11] = {35, 43.50};
    pkgRates[12] = {40, 44.80};
    pkgRates[13] = {45, 47.40};
    pkgRates[14] = {50, 55.20};
    
    while(contLoop == true){
        
        //display program requirements
        cout << "For each transaction, enter package weight and 3 dimensions." << endl;
        cout << "Enter -1 to quit." << endl;
        
        cout << "\n";
        
        //prompt user for input
        cout << "Enter package weight and 3 dimensions: ";
        cin >> weight;
        
        //quit program if input = -1
        if(weight == -1){
            contLoop = false;
            break;
        }
        
        //prompt user for dimension input
        cin >> length >> width >> height;
        
        //skip transaction and display error message if input is invalid
        if(weight < -1){
            error = true;
            cout << "Input error" << endl;
            continue;
        }
        
        //store input data in array
        dimensions[0] = length;
        dimensions[1] = width;
        dimensions[2] = height;
        
        //initialize pkgGirth to value returned by girth function
        pkgGirth = girth(dimensions);
        
        //initialize girth verification status to boolean returned by verifyGirth function
        girthVerified = verifyGirth(pkgGirth);
        
        //initialize verification status to boolean returned by verifiedPkg function
        verified = verifiedPkg(dimensions, weight);
        
        //increment number of total transactions
        txnCount++;
        
        //process transaction and display cost and transaction inormation if package dimensions and girth are verified
        if(verified == true && girthVerified == true){
            acceptedCount++; //increment number of accepted transactions
            statusMessage = "Accepted";
            
            index = search(pkgRates, weight, CHARGES);
            
            pkgCost = pkgRates[index].cost;
            
            displayOutput(txnCount, statusMessage, weight, pkgCost);
        }
        
        //reject transaction if package is not verified
        else{
            rejectedCount++; //increment number of rejected transactions
            statusMessage = "Rejected";
            pkgCost = 0.0;
            displayOutput(txnCount, statusMessage, weight, pkgCost);
            
            
        }
        
        cout << "\n";
        
    }
    
    cout << "\n";
    
    //display total number of rejected and accepted packages
    cout << "Number of accepted packages: " << acceptedCount << endl;
    cout << "Number of rejected packages: " << rejectedCount << endl;
    
    
    return 0;
}
