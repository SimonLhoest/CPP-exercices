#include <iostream>
#include <iostream>
#include <math.h>      
#include <numeric>
#include <vector>
#include <unistd.h>
#include <mutex>
#define Nphilo 6

using namespace std;


// Declare you variables, structures, forks, etc.
int forks [6]={1,1,1,1,1,1};
mutex m;


//Function declaration
void Think(int threadid)
{
   cout<<"I am the Philosopher number "<<threadid<<" and I am thinking " << endl;
   sleep(5);  
};

void PickupForks(int threadid)
{
    cout<<"I am the Philosopher number "<<threadid<<" and I am PickingupForks "<< endl; 
    int minus=1;
    if (threadid==0){
    	minus=-5;
	};
    int right=0;
    int left=0;
	while(left+right!=2){
		right = forks[threadid];
		left = forks[threadid-minus];
	};
	m.lock();
	forks[threadid]=0;
	forks[threadid-minus]=0; 
	m.unlock();
};

void Eat(int threadid)
{
    cout<<"I am the Philosopher number "<<threadid<<" and I am Eating "<< endl;
    sleep(2);
};

void PutForks(int threadid)
{
	int minus=1;
    if (threadid==0){
    	minus=-5;
	};
	cout<<"I am the Philosopher number "<<threadid<<" and I am Putting the forks ";
	m.lock();
	forks[threadid]=1;
	forks[threadid-minus]=1;
	m.unlock();
};


//CREATE THE THREAD philosopher
void *philoprocess(void *threadid)
{
	int id=*(int *)threadid-1;
	cout<<"I am the Philosopher number "<<id<<" : "<< endl;
    Think(id);
    PickupForks(id);
	Eat(id);
	PutForks(id);
    //Functions inside a thread
    //Call the function Think();
    //Call the function PickupForks();
    //Call the function Eat();
    //Call the function PutForks();
    pthread_exit(NULL);
}

///// MAIN /////
int main() {
    //cout<<"Info: "<<endl;
    //cout<<"Philosophers and forks are numbered, in counter-clockwise direction. The fork to the right of a philosopher 'i' and the left 'i-1' (with the exeption of the first philosopher)."<<endl<<endl;
	int c=0;
    while(true) {
	    //Create threads
	    pthread_t tphilo[Nphilo];
	    
	    for(int i = 0; i<Nphilo; i++){
	        
			int rc;
			cout<<"Here comes "<<i<<'\n';
	        rc = pthread_create(&tphilo[i], NULL, philoprocess, &i);
	        
	        if (rc){
	            cout << "Error:unable to create thread for philosopher " << i << endl;
	        }
	    };
	    //Check if all the threads are finished before ending the execution
	    for(int i =0; i<Nphilo;i++){
	        pthread_join(tphilo[i],NULL);
	    }
		if(c>2){
			break;
		}
		c++;
    };
    return 0;
}










