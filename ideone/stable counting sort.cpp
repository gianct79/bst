#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Person
{
public:
    Person()
    {
    }

    Person(int age, const string &name)
    {
        this->age = age;
        this->name = name;
    }

    int age;
    string name;
};

void printVector(const vector<Person> &vectorParam)
{
    for(size_t i = 0; i < vectorParam.size(); ++i)
    {
        cout << vectorParam[i].name << " - " << vectorParam[i].age << endl;
    }
}

int main(void)
{
    cout << "STABLE COUNTING SORT" << endl << endl;

    //Original array to be sorted
    vector<Person> originalVector;
    originalVector.push_back(Person(28, "Rafael"));
    originalVector.push_back(Person(19, "Vitor")); 
    originalVector.push_back(Person(53, "Ricardo")); 
    originalVector.push_back(Person(28, "Patricia")); 
    originalVector.push_back(Person(52, "Katia"));
    originalVector.push_back(Person(3, "Giu"));
    originalVector.push_back(Person(19, "Carolina"));
    originalVector.push_back(Person(32, "Gian"));
    originalVector.push_back(Person(28, "Gabriel"));
    originalVector.push_back(Person(30, "Fernando"));
    
    cout << "Printing original vector..." << endl << endl;
    printVector(originalVector);

    //Defining the range of the histogram (min and max values)
    int min_value = originalVector[0].age;
    int max_value = originalVector[0].age;

    for(size_t i = 0; i < originalVector.size(); ++i)
    {
        if (originalVector[i].age < min_value)
            min_value = originalVector[i].age;

        if (originalVector[i].age > max_value)
            max_value = originalVector[i].age;
    }

    //Filling the histogram
    vector<int> histogram(max_value - min_value + 1);

    for(size_t i = 0; i < originalVector.size(); ++i)
        ++histogram[originalVector[i].age - min_value];
        
    //Converting histogram into an offset map
    map<int, int> offSetMap;
    int currentSum = 0;
    for(size_t i = 0; i < histogram.size(); ++i)
    {
        if(histogram[i])
        {
            offSetMap.insert(pair<int,int>(i + min_value, currentSum));
            currentSum += histogram[i];
        }
    }

    //Generating sorted vector from the offset map
    vector<Person> sortedVector(originalVector.size());
    for(size_t i = 0; i < originalVector.size(); ++i)
        sortedVector[offSetMap[originalVector[i].age]++] = originalVector[i];

    cout << endl << endl << "======================================" << endl << endl;

    cout << "Printing sorted vector..." << endl << endl;
    printVector(sortedVector);

    return 0;
}