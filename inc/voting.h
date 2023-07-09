#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct candidate
{
	int cid;
	char cname[20];
	int votes;
} CANDIDATE;

struct currentValidID
{
	int Date;
	char Location[10];
	int totalVoters;
};
struct currentValidID currentValidID; 
CANDIDATE candidateArray[20];
int numberOfCandidates;
char votes_count[200];

void initiateNewElection();
void createCandidateFiles();
void saveElectionInfoInFile();
int getWinner();
void LoadElectionInfoFromFile();
void adminPanel();
int authenticateAdmin();
int extractDate(char VoterID[]);
int extractID(char VoterID[]);
int checklocation(char VoterID[]);
int isValid(char VoterID[]);
int isVoted(char VoterID[]);
void saveVote(char VoterID[], int);
void deleteIllegalVote(char voterID[]);
void voterPanel();

