/**
 * @author Haeramb Jajpura
 * @date 2024-07-14
 */

/**
 * @brief
 * This is an employee record system in C langauge.
 * I wrote this program in 2020 and now added some more features to it.
 */


#include <stdio.h>
#include <stdlib.h>

// file pointer for performing various kinds of tasks with files
FILE *fp, *fp2;

// structures used in program
struct IdAllot
{
	int Id;
} a;
struct Emp
{
	char Name[30];
	int Id, Flag;
	long int Salary;
} s;

// function declaration
int MainScreenInput();
void ExecuteChoice(int);
void Add();
void Display(int);
void Delete();
void Recall();
void Modify();
void Export();
void Initialise(int);
void EmptyTrash();
void NotFoundError(int);

int main()
{
	//Initialise(6000);
	while (1)
	{
		ExecuteChoice(MainScreenInput());
	}
	return 0;
}

// fucntion definitions

int MainScreenInput()
{
	int Choice;
	system("cls");
	printf("Employee Record System\n\n");
	printf("1. Add\n");
	printf("2. Display\n");
	printf("3. Delete\n");
	printf("4. Trash/Recall\n");
	printf("5. Modify\n");
	printf("6. Export Records\n");
	printf("7. Empty Trash\n");
	printf("8. Exit\n\n");
	printf("Enter the choice(1,2,3....) : ");
	scanf("%d", &Choice);
	return Choice;
}
void ExecuteChoice(int Choice)
{
	if (Choice == 1)
	{
		// Add a record
		Add();
	}
	if (Choice == 2)
	{
		// display records
		printf("Displaying Records\n\n");
		Display(0);
		system("pause");
	}
	if (Choice == 3)
	{
		// delete a record
		Delete();
	}
	if (Choice == 4)
	{
		// Recall a record
		Recall();
	}
	if (Choice == 5)
	{
		// modify a record
		Modify();
	}
	if (Choice == 6)
	{
		// export records
		Export();
	}
	if (Choice == 7)
	{
		// empty trash
		EmptyTrash();
	}
	if (Choice == 8)
	{
		// exit from program
		exit(0);
	}
}

void Add()
{
	system("cls");
	printf("Add A record\n\n");
	printf("Enter the name: ");
	scanf("%s", s.Name);
	printf("Enter the Salary: ");
	scanf("%ld", &s.Salary);
	s.Flag = 0;
	fp = fopen("idallot.txt", "r");
	fread(&a, sizeof(a), 1, fp);
	s.Id = a.Id;
	a.Id = a.Id + 1;
	fseek(fp, -sizeof(a), SEEK_CUR);
	fclose(fp);
	fp = fopen("idallot.txt", "w");
	fwrite(&a, sizeof(a), 1, fp);
	fclose(fp);
	printf("The allotted Id is %d\n", s.Id);
	fp = fopen("empdata.txt", "a");
	fwrite(&s, sizeof(s), 1, fp);
	fclose(fp);
	printf("The Record has been added\n");
	system("pause");
}
void Delete()
{
	int SampleId, IsFound;
	IsFound = 1;
	printf("Deleting Records\n\n");
	Display(0);
	printf("Enter the Id you want to delete: ");
	scanf("%d", &SampleId);
	fp = fopen("empdata.txt", "r+");
	while (fread(&s, sizeof(s), 1, fp))
	{
		if (s.Id == SampleId && s.Flag == 0)
		{
			IsFound = 0;
			s.Flag = 1;
			fseek(fp, -sizeof(s), SEEK_CUR);
			fwrite(&s, sizeof(s), 1, fp);
			fclose(fp);
			printf("Record is moved to Trash\n");
		}
	}
	NotFoundError(IsFound);
	fclose(fp);
	system("pause");
}
void Recall()
{
	int SampleId, IsFound;
	IsFound = 1;
	printf("Recalling Records\n\n");
	Display(1);
	printf("Enter the Id you want to recall: ");
	scanf("%d", &SampleId);
	fp = fopen("empdata.txt", "r+");
	while (fread(&s, sizeof(s), 1, fp))
	{
		if (s.Id == SampleId && s.Flag == 1)
		{
			IsFound = 0;
			s.Flag = 0;
			fseek(fp, -sizeof(s), SEEK_CUR);
			fwrite(&s, sizeof(s), 1, fp);
			fclose(fp);
			printf("Record is recalled\n");
		}
	}
	NotFoundError(IsFound);
	fclose(fp);
	system("pause");
}
void Modify()
{
	int SampleId, IsFound;
	IsFound = 1;
	printf("Modifying Records\n\n");
	Display(0);
	printf("Enter the Id you want to modify: ");
	scanf("%d", &SampleId);
	fp = fopen("empdata.txt", "r+");
	while (fread(&s, sizeof(s), 1, fp))
	{
		if (s.Id == SampleId && s.Flag == 0)
		{
			IsFound = 0;
			s.Flag = 0;
			printf("Enter the New Name: ");
			scanf("%s", s.Name);
			printf("Enter the New salary: ");
			scanf("%ld", &s.Salary);
			fseek(fp, -sizeof(s), SEEK_CUR);
			fwrite(&s, sizeof(s), 1, fp);
			fclose(fp);
			printf("Record is modified\n");
		}
	}
	NotFoundError(IsFound);
	fclose(fp);
	system("pause");
}
void Export()
{
	system("cls");
	printf("exporting the records....\n");
	fp = fopen("empdata.txt", "r");
	fp2 = fopen("exported.txt", "w");
	while (fread(&s, sizeof(s), 1, fp))
	{
		if (s.Flag == 0)
		{
			fprintf(fp2, "Name: %s\n", s.Name);
			fprintf(fp2, "ID: %d\n", s.Id);
			fprintf(fp2, "Salary: %ld\n\n", s.Salary);
			fprintf(fp2, "----------------------------------------------\n");
		}
	}
	fclose(fp);
	fclose(fp2);
	printf("exporting done...\n");
	system("pause");
}
void Display(int FlagValue)
{
	system("cls");
	fp = fopen("empdata.txt", "r");
	while (fread(&s, sizeof(s), 1, fp))
	{
		if (s.Flag == FlagValue)
		{
			printf("Name: %s\n", s.Name);
			printf("Id: %d\n", s.Id);
			printf("Salary: %ld\n\n\n", s.Salary);
		}
	}
}
void Initialise(int Id)
{
	remove("idallot.txt");
	a.Id = Id;
	fp = fopen("idallot.txt", "w");
	fwrite(&a, sizeof(a), 1, fp);
	fclose(fp);
}
void EmptyTrash()
{
	fp = fopen("empdata.txt", "r");
	fp2 = fopen("tempdata.txt", "w");
	while (fread(&s, sizeof(s), 1, fp))
	{
		if (s.Flag == 0)
		{
			fwrite(&s, sizeof(s), 1, fp2);
		}
	}
	fclose(fp);
	fclose(fp2);
	fp = fopen("empdata.txt", "w");
	fp2 = fopen("tempdata.txt", "r");
	while (fread(&s, sizeof(s), 1, fp2))
	{
		fwrite(&s, sizeof(s), 1, fp);
	}
	fclose(fp);
	fclose(fp2);
	printf("trash is cleared\n");
	system("pause");
}
void NotFoundError(int IsFound)
{
	if (IsFound == 1)
	{
		printf("Record Not found\n");
	}
}
