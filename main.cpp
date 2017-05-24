//===========================================================================
//                              Radix Sort
//                      Developed By: Leron Julian
//               PROGRAM COMPLETED PER PROGRAM SPECIFICATION
//===========================================================================


#include <iostream>
#include <string>

//For Files
#include <fstream>

//For random numbers
#include <ctime>
#include <cstdlib>

using namespace std;

struct bin_node{
    int value;
    
    bin_node* next;
};
typedef bin_node* bin_ptr;

//===========================================================================
// This function prints out the linked list in reverse
//===========================================================================
void ReversePrint(bin_node *tempNode)
{
    if (tempNode == NULL) {
        return;
    }
 
    ReversePrint(tempNode->next);
    
    cout << tempNode->value << " ";
}

//===========================================================================
// This function performs the radix sort with the input of the unsorted
// linked list and returns a sorted linked list
//===========================================================================
bin_node *radixsort(bin_ptr List, int passes)
{
    int i, j, digit, m = 1;
    
    bin_ptr temp, radix_bin[10], rear_radix_bin[10];
    
    for (j = 1; j  <= passes ; j++)
    {
        for (i = 0; i <= 9; i++)
        {
            radix_bin[i] = NULL;
            rear_radix_bin[i] = NULL;
        }
        
        while (List != NULL)
        {
            digit = ( (List->value/m) % 10);
            
            temp = List;
            
            List = List->next;
            
            temp->next = NULL;
            
            if (radix_bin[digit]!= NULL)
            {
                rear_radix_bin[digit]->next = temp;
                rear_radix_bin[digit] = temp;
            }
            else
            {
                radix_bin[digit] = temp;
                rear_radix_bin[digit] = temp;
            }
        }
        
        digit = 0;
        while (radix_bin[digit] == NULL)
            digit++;
        
        List = radix_bin[digit];
        
        temp = rear_radix_bin[digit];
        
        digit++;
        while (digit < 10)
        {
            if (radix_bin[digit] != NULL)
            {
                temp->next = radix_bin[digit];
                
                temp = rear_radix_bin[digit];
            }
            digit++;
        }
        
        m = m * 10;
    }
    
    return List;
}



int main()
{
    int size = 100;
    int *unsorted_Arr = new int[size];
    
    int min = 1;
    int maxSize = 2;
    int choice;
    
    do{
        cout << "Enter 1 to sort N random numbers in a range from x to y, or enter 2 to input your own numbers" << endl;
        cout << "Enter choice -> ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear() ;
            cin.ignore(1000, '\n');
            cout << endl << "ENTER a valid input " << endl << endl;
            continue ;
        }
        
        cin.clear();
        cin.ignore(500, '\n');
        
        if (choice < min || choice > maxSize)
            cout << endl << "ENTER a number in the valid range " << endl << endl;
        
    } while (choice < min || choice > maxSize);
    
    switch (choice){
        case 1:
        {
            int y;
            int maxRange;
            int minRange;
            
            cout << "Enter the number of random terms you would like -> ";
            cin >> size;
            
            cout << "Enter the min range of these numbers -> ";
            cin >> minRange;
            
            cout << "Enter the max range of these numbers -> ";
            cin >> maxRange;
            
            cout << endl;
            cout << "Generated Numbers..." << endl;
            
            unsigned long int seed = time(0);
            srand(seed);
            
            ofstream number_File;
            string file = "random_num_file.txt";

            number_File.open(file);
            
            for(int i = 0; i < size; i++)
            {
                y = (rand() % (maxRange - minRange)) + minRange;
                number_File << y << endl;
                
                cout << y << " ";
            }
            
            number_File.close();
            
            ifstream input_File;
            input_File.open("random_num_file.txt");
            
            int j = 0;
            
            while (!input_File.eof())
            {
                 input_File >> unsorted_Arr[j];
                 j++;
            }
             
            input_File.close();
            
            break;
        }
        case 2:
        {
            int count = 1;
            
            cout << "Enter the numbers, each seperated by a space -> ";
            cin >> unsorted_Arr[0];
            
            while (count < size && cin.get() != '\n')
            {
                cin >> unsorted_Arr[count];
                count++;
            }

            size = count;
            break;
        }
    }
    
    int i;
    int max =- 1;
    int passes = 0;
    
    bin_ptr start = NULL , end = NULL, tempPtr, descendingPtr;
    
    for (i = 0; i < size; i++)
    {
        if (unsorted_Arr[i] > max)
            max = unsorted_Arr[i];
        
        tempPtr = new bin_node;
        
        tempPtr->value = unsorted_Arr[i];
        
        tempPtr->next = NULL;
        
        if (start != NULL)
        {
            end->next = tempPtr;
            end = tempPtr;
        }
        
        else
        {
            start = tempPtr;
            end = tempPtr;
        }
    }
    
    while (max > 0)
    {
        passes = passes + 1;
        max = max/10;
    }
    
    start = radixsort(start, passes);
    
    cout << endl << endl << "Sorted Numbers in Ascending Order..." << endl;
    cout << "-----------------" << endl;
    
    tempPtr = start;
    descendingPtr = new bin_node;
    descendingPtr = start;
    
    for (i = 0; i < size; i++)
    {
        cout << tempPtr->value << " ";
        tempPtr = tempPtr->next;
    }
    
    cout << endl;
    
    cout << endl << "Sorted Numbers in Descending Order..." << endl;
    cout << "-----------------" << endl;
    
    ReversePrint(descendingPtr);
    
    cout << endl;
    
    return 0;
}
