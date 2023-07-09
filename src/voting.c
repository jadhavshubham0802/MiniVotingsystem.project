#include<voting.h>




void initiateNewElection()
{
	printf ("\nNew Election Initiation:\n");

	printf ("\nElections for which Date: ");
	scanf ("%d", &currentValidID.Date);
	printf ("Enter Election Location:");
	scanf ("%s", currentValidID.Location);
	printf ("Enter max voterIds:");
	scanf ("%d", &currentValidID.totalVoters);
	printf ("Enter the no. of candidates:");
	scanf ("%d", &numberOfCandidates);

	for(int i=0;i<currentValidID.totalVoters;i++){
		votes_count[i]='0';
	}
	for (int i = 0; i < numberOfCandidates; i++)
	{
		candidateArray[i].cid = i + 1;
		printf ("Enter name of candidate %d: ", i + 1);
		scanf (" %s", candidateArray[i].cname);
		candidateArray[i].votes = 0;
	}
	return;
}

void createCandidateFiles()
{
	printf ("\nCreating candidate files...\n");
	FILE *fp;
	char filename[20];
	for (int i = 1; i <= numberOfCandidates; i++)
	{
		sprintf (filename, "candidate%d.txt", i);
		fp = fopen (filename, "w");
		fprintf (fp, "0\n%s", candidateArray[i - 1].cname);
		fclose (fp);
	}
	printf ("Created Files successfully\n");
}

void saveElectionInfoInFile(){
	printf("Saving Election Info in File...\n");
	FILE *fp = fopen("ElectionInfo.txt", "w");
	if(fp==NULL)
	{
		printf("\nError in file creation\n");
		fclose(fp);
		return;
	}
	fprintf(
			fp,"%d\n%s\n%d\n%d",
			currentValidID.Date,
			currentValidID.Location,
			currentValidID.totalVoters,
			numberOfCandidates
	       );
	fclose(fp);
	printf("Saved Successfully : )");
}
void loadElectionInfoFromFile()
{
	FILE *f1,*f2;
	f1=fopen("ElectionInfo.txt","r");
	if(f1==NULL)
		printf("Not Exist");
	fscanf(f1,"%d",&currentValidID.Date);
	fseek(f1,2,SEEK_CUR);
	fscanf(f1,"%s",currentValidID.Location);
	fseek(f1,2,SEEK_CUR);
	fscanf(f1,"%d",&currentValidID.totalVoters);
	fseek(f1,2,SEEK_CUR);
	fscanf(f1,"%d",&numberOfCandidates);
	fclose(f1);

	for (int i = 0; i < currentValidID.totalVoters; i++)
	{
		votes_count[i] = '0';
	}
	for(int i=1;i<=numberOfCandidates;i++)
	{
		int loc;
		char filename[20];
		sprintf(filename,"candidate%d.txt",i);
		f2=fopen(filename,"r+");
		candidateArray[i-1].cid=i;
		fscanf(f2,"%d",&candidateArray[i-1].votes);
		fscanf(f2,"%s",candidateArray[i-1].cname);
		while(!feof(f2)){
			fscanf(f2,"%d",&loc);
			votes_count[loc-1] = i+48;
		}
		fclose(f2);
	}

}
int getWinner(){
	int maxV = -1;
	int winnerCid;
	for(int i = 0;i < numberOfCandidates; i++){
		if(candidateArray[i].votes > maxV) {
			winnerCid = candidateArray[i].cid;
			maxV = candidateArray[i].votes;
		}
		else if(candidateArray[i].votes == maxV) {
			return -1;
		}
	}
	return winnerCid;
}


void adminPanel()
{
	while(1){

		if(authenticateAdmin()!=1){
			printf("\n Wrong Username or Password \n");
			break;
		}

		printf("\n\nLOGGED IN SUCCESSFULLY (Press Enter)");

		while(1)
		{
			char inputID[15];
			char input;
			int winnerCid,totalVotedNow=0;
			printf("\n1.New Election\n2.Continue Previous Election\n3.Delete Illegal Vote\n4.Result\n5.Logout\nOption:");
			scanf(" %c",&input);

			switch(input)
			{
				case '1':
					initiateNewElection();
					saveElectionInfoInFile();
					createCandidateFiles();
					break;
				case '2':
					loadElectionInfoFromFile();
					break;
				case  '3':
					printf("\nenter voterid to delete :");
					scanf("%s",inputID);
					deleteIllegalVote(inputID);
					break;
				case '4':
					winnerCid = getWinner();
					if(winnerCid != -1){
						printf("\nWinner is %s with %d votes\n",candidateArray[winnerCid-1].cname,candidateArray[winnerCid-1].votes);
					}
					else{
						printf("\nIts A TIE");
					}
					printf("\nFull Result\n");
					for(int i=0;i<numberOfCandidates;i++){
						totalVotedNow+=candidateArray[i].votes;
						printf("%d. %s -> %d votes\n",candidateArray[i].cid,candidateArray[i].cname,candidateArray[i].votes);
					}
					printf("\nVoting Percentage: %d %%\n\n",(totalVotedNow*100)/currentValidID.totalVoters);
					break;
				case '5':
					return;
				default:
					printf("Invalid Option");
			}

		}
	}

};

int authenticateAdmin(){
	char username[15], password[6];
label:
	printf("\nEnter username: ");
	scanf("%s",username);
	if((strcmp(username,"Admin"))!=0){
		printf("Invalid user name.Try again");
		goto label;
	}
	else
	{
		printf("Enter Password: ");
		scanf("%s", password);
		if((strcmp(password,"admiN"))==0)
		{
			printf("PASSWORD IS CORRECT.\n LOGGED IN SUCCESFULLY.");

		}
		else {

			printf("PASSWORD IS INCORRECT.\n LOGIN FAILED.TRY AGAIN.");
			goto label;

		}

	}
	return 1;
}
int extractDate(char voterID[15])
{
	int date=0;
	char tmp;
	for(int i=0;i<4;i++){
		tmp=voterID[i];
		date=(date*10)+(tmp-48);
	}
	return date;
}
int extractID(char voterID[15])
{
	int ID=0;
	char tmp;
	for(int i=11;i<14;i++){
		tmp=voterID[i];
		ID=(ID*10)+(tmp-48);
	}
	return ID;
}
int checklocation(char voterID[15])
{
	char location[20];
	for(int i=2;i<11;i++){
		location[i-2]=voterID[i];
	}
	location[9]='\0';
	if(strcmp(location,currentValidID.Location)==0)
		return 1;
	else
		return 0;
}

int isValid(char voterID[15])
{

	if(strlen(voterID)!=14)
		return 0;



	int inputeddate=extractDate(voterID);
	int inputedid = extractID(voterID);


	if(inputeddate!=currentValidID.Date ||  inputedid>currentValidID.totalVoters)
		return 0;

	return 1;
}

int isVoted(char voterID[15])
{
	int location=extractID(voterID);
	if(votes_count[location-1]=='0')
		return 0;
	else
		return 1;
}

void saveVote(char voterID[15],int voteInput)
{
	char filename[20];
	sprintf(filename,"candidate%d.txt",voteInput);
	FILE *fp = fopen(filename,"r+");
	int location=extractID(voterID);
	votes_count[location-1]=voteInput;
	candidateArray[voteInput-1].votes++;
	fseek(fp, 0, SEEK_SET);
	fprintf(fp,"%d\n",candidateArray[voteInput].votes);
	fseek(fp, 0, SEEK_END);
	fprintf(fp,"\n%d",location);
	fclose(fp);
}
void deleteIllegalVote(char voterID[15])
{
	FILE *fp,*fcp;
	char filename[20];
	char line[20];

	int location = extractID(voterID);
	sprintf(filename,"candidate%d.txt",candidateArray[votes_count[location-1]-49].cid);
	candidateArray[votes_count[location-1]-49].votes--;
	votes_count[location-1]='0';
	if ((fp = fopen(filename,"r")) == NULL)
	{
		printf("\nFile cannot be opened...Operation Failed");
		return;
	}
	printf("\nDeleting in process...\n ");
	if ((fcp = fopen("tmp.txt","w")) == NULL)
	{
		printf("\nFile cannot be opened...Operation Failed");
		return;
	}

	while (!feof(fp))
	{
		fscanf(fp,"%s",line);
		fprintf(fcp,"%s\n",line);
	}
	fclose(fp);
	fclose(fcp);
	if ((fp = fopen(filename,"w")) == NULL)
	{
		printf("\nFile cannot be opened...Operation Failed");
		return;
	}
	int numFromFile;
	char cnameFromFile[20];
	fcp = fopen("tmp.txt","r");
	fscanf(fcp,"%d",&numFromFile);
	fprintf(fp,"%d",numFromFile-1);
	fscanf(fcp,"%s",cnameFromFile);
	fprintf(fp,"\n%s",cnameFromFile);
	while(!feof(fcp)){
		fscanf(fcp,"%d",&numFromFile);
		if(numFromFile!=location)
			fprintf(fp,"\n%d",numFromFile);
	}
	fclose(fp);
	fclose(fcp);
	remove("tmp.txt");
	printf("\nVote deleted successfully\nPress any key to continue...");
}


void voterPanel()
{
	char voterID[15];
	int voteInput;
	while(1)
	{
		printf("\n\n  To exit press 0");
		printf("\n  Enter voterID:");
		scanf("%s",voterID);
		if(strcmp(voterID, "0")==0)
			return;
		if(isValid(voterID)!=1)
		{
			printf("\n  Invalid  voterID(Press Enter)");
			continue;
		}
		if(isVoted(voterID)!=0)
		{
			printf("\n  Your PRN entered is already voted\n  Contact Admin for furthur query");
			continue;
		}
		printf("\n\n  Candidates for election:");
		for (int i = 0; i < numberOfCandidates; i++)
		{
			printf("\n  %d. %s",i+1,candidateArray[i].cname);
		}
		printf("\n\n  Your Vote(Enter Number):");
		scanf("%d",&voteInput);

		saveVote(voterID,voteInput);
		printf("\n\nThanks for your precious vote(Press Enter)");
	}
}

