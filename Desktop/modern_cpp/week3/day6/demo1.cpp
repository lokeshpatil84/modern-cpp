#include <iostream>

#include <future>

/*]
option 1: onr after the other . always complete one thing before starting the next task

name - single thread technique

option 2: i will complete all task in a such way that i practically start all of them at the same time " but"
   keep juggling the based on some criteria

   name - multi- thread approch

option 3: map number of task amongst number of available  "workers"

name - Parallel execution

option4 : start a task. either delegate it to another worker or do it yourself after some time

if some else is doing a task moniter it wait for thier work to be done take follow-up action
accordingly

name : asynchronous execution
*/

/*
2 task
calculate factorial of 5
calculate square of a number given by the user

*/

int sqaure(std::future<int> &f)
{
   std::this_thread::sleep_for(std::chrono::seconds(2));
   std::cout << " Hello from square. i have started my work! \n";
   int number = f.get();
   return number * number;
}

int factorial(int number)
{
   std::this_thread::sleep_for(std::chrono::seconds(3));
   if (number < 0)
   {
      throw std::runtime_error("negative number error!");
   }
   if (number == 0 || number == 1)
   {
      return 1;
   }
   else
   {
      return number * factorial(number - 1);
   }
}

int main()
{

   // step 1: make a promise
   std::promise<int> pr;

   // step 2 : a future object linked to a promise
   std::future<int> ft = pr.get_future();

   /*
      OS : lauch sqaure (if possible as a new thread )
   */
   std::future<int> result_ft = std::async(std::launch::async, &sqaure, std::ref(ft));
   int val = 0;
   std::cin >> val;
   pr.set_value(val);

   std::cout << factorial(5);

   std::cout << "Result of factoiral is : " << result_ft.get();
}

/*
client-server architechture

future promise model


square calculation
main needs to delegate the task of square calculation

------> new thread for sqaure will be register
*/
