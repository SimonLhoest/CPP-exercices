#include <iostream>
#include <thread>
#include <time.h>  

using namespace std;

int totalTime [2]= {0,0}; // variable to store the total time taken by the team
int numberofrunners=3; //Number of runners, in case.
int t=time(NULL); //time at which program starts
//we take one t, and then a different int for each runner, so each runner has a different seed:
//int for runner = runnernumber+(teamnumber-1)*3
//For team 1 : 1 2 3
//For team 2 : 4 5 6

void* Run(void* data) {
	//Store the team number and runner number
    int* numbers =(int*) data;
    int teamnumber = numbers[0];
    int runnumber = numbers[1];
    //Run starts
    cout <<"Team "<<teamnumber<<" Runner "<<runnumber+1<<" started running.\n";
    //Take random run time
    srand(t+(teamnumber-1)*3+(runnumber+1));
    int runtime=rand()%5+1;
    this_thread::sleep_for(chrono::seconds(runtime));
    //When run finish, print appropriated sentence
    if (runnumber+1==numberofrunners){
    	cout <<"Team "<<teamnumber<<" Runner "<<runnumber+1<<" ran for "<<runtime<<" seconds and finished the race.\n";
	}
    else{
    	cout <<"Team "<<teamnumber<<" Runner "<<runnumber+1<<" ran for "<<runtime<<" seconds and passed the baton.\n";
	}
    //Add runtime to total time
    totalTime[teamnumber-1]+=runtime;
}

void* team(void* tnumber){
	//Create threads for runners
	pthread_t team[numberofrunners];
	//Store team number
	int number =*(int *)tnumber;
	//Start the runners 
	for (int i=0;i<numberofrunners;i++){
		//Store team number and runner number
		int data[2]={number, i};
		int rc;
		//Start runner thread
		rc = pthread_create(&team[i], NULL, Run, (void*) data);
	    if (rc){
	        cout << "Error:unable to create thread for runner " << i << endl;
        }
        //Join runner thread
        pthread_join(team[i],NULL);
	};
}


int main() {
	//Create two thread for the two teams
	pthread_t game[2];
	//Do the countdown start
	cout<<"3, ";
	//Loop to start the two threads
	for(int j=0;j<2;j++){
		int rc;
		//Countdown
		cout<<2-j<<", ";
		if(j==1){
			cout<<"go !\n";
		}
		//Start the threads
		rc=pthread_create(&game[j],NULL,team,&j);
	}
	
	//Join the threads
	for(int j =0; j<2;j++){
        pthread_join(game[j],NULL);
	}
	
	//Display total time
    cout<<"Team 1 : "<<totalTime[0]<<" seconds.\n";
	cout<<"Team 2 : "<<totalTime[1]<<" seconds.\n";
	//Display winner
	if(totalTime[0]<totalTime[1]){
		cout<<"Team 1 won !\n";
	}
	else if(totalTime[0]>totalTime[1]){
		cout<<"Team 2 won !\n";
	}
	else{
		cout<<"Draw !\n";
	}
    return 0;
}

