#include <iostream>
#include <memory>
using namespace std;
// Resource class
class Resource
{
public:
 Resource()
 {
 cout << "Resource acquired" << endl;
 }
 ~Resource()
 {
 cout << "Resource released" << endl;
 }
 void use()
 {
 cout << "Resource is being used" << endl;
 }
};
// Manual Smart Pointer using RAII
class MySmartPointer
{
private:
 Resource* ptr;
public:
 MySmartPointer(Resource* p)
 {
 ptr = p;
 }
 ~MySmartPointer()
 {
 delete ptr;
cout << "Manual smart pointer destroyed" << endl;
 }
 Resource* operator->()
 {
 return ptr;
 }
 // Disable copying to avoid double deletion
 MySmartPointer(const MySmartPointer&) = delete;
 MySmartPointer& operator=(const MySmartPointer&) = delete;
};
int main()
{
 cout << "----- Manual RAII Smart Pointer -----" << endl;
 {
 MySmartPointer smartPtr(new Resource());
 smartPtr->use();
 }
 cout << "\n----- unique_ptr -----" << endl;
 {
 unique_ptr<Resource> uniquePtr =
 make_unique<Resource>();
 uniquePtr->use();
 }
 cout << "\n----- shared_ptr -----" << endl;
{
 shared_ptr<Resource> sharedPtr1 =
 make_shared<Resource>();
 shared_ptr<Resource> sharedPtr2 = sharedPtr1;
 sharedPtr1->use();
 cout << "Shared Pointer Count: "
 << sharedPtr1.use_count() << endl;
 }
 cout << "\nProgram completed successfully." << endl;
 return 0;
}
Output
----- Manual RAII Smart Pointer -----
Resource acquired
Resource is being used
Resource released
Manual smart pointer destroyed
----- unique_ptr -----
Resource acquired
Resource is being used
Resource released
----- shared_ptr -----
Resource acquired
Resource is being used
Shared Pointer Count: 2
30
Resource released
Program completed successfully.
Valgrind Command
First, compile the program with debugging information:
g++ -g smart_pointer.cpp -o smart_pointer
Then run Valgrind:
valgrind --leak-check=full ./smart_pointer
Sample Valgrind Result
HEAP SUMMARY:
 in use at exit: 0 bytes in 0 blocks
 total heap usage: ...
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors
