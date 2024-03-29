// PROGRAM BEGINS HERE
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
////////////////////////////////////////////////////////////////////////////////
struct Patient
{
	char name[30];
	char disease[30], address[30], phone[15];
	int cabin, age;
} x[100];

void add();	   // Add Patient Details
void view();   // View Patient Details
void search(); // Search Patient Details
void edit();   // Edit Patient Details
void del();	   // Delete Patient Details
////////////////////////////////////////////////////////////////////////////////
struct User
{
	char password[30];
	char userName[30];
} y[5]; // Modify Max User Strength here

void editSelf();   // Edit Current User Details
void removeSelf(); // Delete Current User Details
void addUser();	   // Add New User
void viewUsers();  // View All Users
void delUsers();   // Delete All Users
////////////////////////////////////////////////////////////////////////////////
struct Admin
{
	char hospName[30];
	char hospAdrs[30];
	char hospContact[15];
	char adminKey[6];
} admin0[1];

void addAdmin();   // Add Admin Details
void editAdmin();  // Edit Admin Details
void changeKey();  // Change Admin Key
void viewAdmin();  // View Admin Details
void removeUser(); // Delete A User

////////////////////////////////////////////////////////////////////////////////
int in1;			   // stands for input1, declare more incrementally if needed
int i, j = 0;		   // primary variables of methods, except main()
int a = 0, sum = 0, g; // some other variables as required
int patCount;		   // stores no of patients
int userCount;		   // stores no of users
int adminCount;		   // must be 1, but just for future-proofing

time_t mytime;

int activeUser = -1;		 // stores index no of active User
int isUser = -1;			 // stores login status of user, -1 for not logged in
int isAdmin = -1;			 // stores login status of admin, -1 for not logged in
const int maxLoginCount = 3; // stores no of login attempts allowed

// Utility Functions
void authorize(int);  // Function to authorize user/admin
void import();		  // imports data from backup files
void backup();		  // backs up data to backup files
void wait(int);		  // utility function to wait for given no of seconds
void screenReset();	  // refreshes the screen and content (header only)
void encrypt(char *); // utility function to encrypt a string
void decrypt(char *); // utility function to decrypt a string
int encryptInt(int);  // utility function to encrypt an integer
int decryptInt(int);  // utility function to decrypt an integer

int main()
{
	screenReset();
	import();
	screenReset();
	fflush(stdin);

	int m = -1; // for input below
	while (m != 0)
	{
		isUser = -1, isAdmin = -1; // Resetting Login Data as it might have changed, since all this is iterating
		screenReset();
		printf("\n\nLOGIN MENU:\n");
		printf("\nLog in as?\n");
		printf("\n1. User");
		printf("\n2. Administrator");
		printf("\n0. CLOSE THE PROGRAM");
		printf("\n\nEnter Your Choice = ");

		fflush(stdin);
		scanf("%d", &m);

		if (m == 1 || m == 2)
			authorize(m);
		int c, d, e; // for temporary requirements below
		if (isUser == 1 || isAdmin == 1)
		{
			printf("\n\t\tWelcome to Hospital Records Manager!");
			wait(2);
			screenReset();
		}
		else
		{
			continue;
		}
		c = -1;

		if (m == 1) // USER SECTION
		{
			while (c != 0)
			{
				screenReset();

				if (isUser == 1)
				{
					printf("\n\t\t\t/////MAIN MENU/////");
					printf("\n\t\t\t1.Show Patient Menu");
					printf("\n\t\t\t2.Show User Menu");
					printf("\n\t\t\t0.LOG OUT\n");
					printf("\n\n\t\t\tWhat do you want to be done? = ");

					fflush(stdin);
					scanf("%d", &d);
				}
				else
					d = 0; // to move user out of the login as he/she is unauthorized now

				if (d == 1)
				{
					e = -1;
					while (e != 0)
					{
						wait(1);
						screenReset();
						if (isUser == 1)
						{
							printf("\n\t\t\t/////PATIENT MENU/////\n");
							printf("\n\t\t\t1.Add Patients");
							printf("\n\t\t\t2.View Patients List");
							printf("\n\t\t\t3.Search Patients");
							printf("\n\t\t\t4.Edit Patient Details");
							printf("\n\t\t\t5.Delete Patient Details");
							printf("\n\t\t\t0.BACK TO MAIN MENU\n");
							printf("\n\n\t\t\tEnter your choice = ");

							fflush(stdin);
							scanf("%d", &e);
						}
						else
							e = 0; // security Action

						if (e == 1) // add
						{
							add();
						}
						else if (e == 2) // view
						{
							view();
						}
						else if (e == 3) // search
						{
							search();
						}
						else if (e == 4) // edit
						{
							edit();
						}
						else if (e == 5) // delete
						{
							del();
						}
						else if (e == 0)
						{
							printf("\nRedirecting to Main Menu...");
						}
						else
						{
							printf("\nOops! %d is an Invalid input!", e);
						}
					} // inner while closed
				}
				else if (d == 2)
				{
					e = -1;
					while (e != 0)
					{
						wait(1);
						screenReset();
						if (isUser == 1)
						{
							printf("\n\t\t\t/////USER MENU/////\n");
							printf("\n\t\t\t1.\tChange username/password");
							printf("\n\t\t\t2.\tDelete my User Account");
							printf("\n\t\t\t0\tBACK TO MAIN MENU");
							printf("\n\n\t\t\tEnter your choice = ");

							fflush(stdin);
							scanf("%d", &e);
						}
						else
							e = 0;

						if (e == 1)
						{
							editSelf();
							printf("\nDirecting to the User Menu...");
						}
						else if (e == 2)
						{
							removeSelf();
							printf("\nDirecting to the User Menu...");
						}
						else if (e == 0)
						{
							printf("\nRedirecting to Main Menu...");
						}
						else
						{
							printf("\nOops! %d is an invalid input.", e);
							printf("\nDirecting to the User Menu...");
						}
					}
				}
				else if (d == 0)
				{
					wait(1);
					screenReset();

					if (isUser == 1)
						printf("\nLogging out...");
					else
					{
						printf("\nWE COULDN'T VALIDATE YOUR AUTHORISATION.\nYou can try to login again...");
						isUser = 0;
						wait(2);
						screenReset();
					}

					break;
				}
				else
				{
					printf("\nOops! %d is an invalid input.", d);
				}

			} // end of while(MAIN ONE)
		}

		else if (m == 2) // ADMIN SECTION
		{
			c = -1;
			while (c != 0)
			{
				screenReset();

				if (isAdmin == 1)
				{
					printf("\n\t\t\t/////ADMIN MENU/////\n");
					printf("\n\t\t\t1.Show Patient Menu");
					printf("\n\t\t\t2.Show Admin Menu");
					printf("\n\t\t\t0.LOG OUT\n");
					printf("\n\t\t\tWhat do you want to be done? = ");

					fflush(stdin);
					scanf("%d", &d);
				}
				else
					d = 0; // to move user out of the program as he/she is unauthorized now

				if (d == 1)
				{
					e = -1;
					while (e != 0)
					{
						wait(1);
						screenReset();
						if (isAdmin == 1)
						{
							printf("\n\t\t\t/////PATIENT MENU/////\n");
							printf("\n\t\t\t1.Add Patients");
							printf("\n\t\t\t2.View Patients List");
							printf("\n\t\t\t3.Search Patients");
							printf("\n\t\t\t4.Edit Patient Details");
							printf("\n\t\t\t5.Delete Patient Details");
							printf("\n\t\t\t0.BACK TO MAIN MENU\n");
							printf("\n\n\t\t\tEnter your choice = ");

							fflush(stdin);	 // making it clear
							scanf("%d", &e); // choice for option
						}
						else
							e = 0; // security action

						if (e == 1) // add
						{
							add();
						}
						else if (e == 2) // view
						{
							view();
						}
						else if (e == 3) // search
						{
							search();
						}
						else if (e == 4) // edit
						{
							edit();
						}
						else if (e == 5) // delete
						{
							del();
						}
						else if (e == 0)
						{
							printf("\nRedirecting to Main Menu...");
						}
						else
						{
							printf("\nOops! %d is an Invalid input!", e);
						}
					} // inner while closed
				}
				else if (d == 2)
				{
					e = -1;
					while (e != 0)
					{
						wait(1);
						screenReset();
						if (isAdmin == 1)
						{
							printf("\n\t\t\t/////ADMIN MENU/////\n");
							printf("\n\t\t\t1.Add new User");
							printf("\n\t\t\t2.View Users");
							printf("\n\t\t\t3.Delete Users");
							printf("\n\t\t\t4.View Admin Details");
							printf("\n\t\t\t5.Edit Admin Details");
							printf("\n\t\t\t6.CHANGE ADMIN KEY");
							printf("\n\t\t\t0.BACK TO MAIN MENU\n");
							printf("\n\n\t\t\tEnter your choice = ");

							fflush(stdin);
							scanf("%d", &e);
						}
						else
							e = 0;

						if (e == 1)
						{
							addUser();
							printf("\nDirecting to the User Menu...");
						}
						else if (e == 2)
						{
							viewUsers();
							printf("\nDirecting to the User Menu...");
						}
						else if (e == 3)
						{
							delUsers();
							printf("\nDirecting to the User Menu...");
						}
						else if (e == 4)
						{
							viewAdmin();
							printf("\nDirecting to the User Menu...");
						}
						else if (e == 5)
						{
							editAdmin();
							printf("\nDirecting to the User Menu...");
						}
						else if (e == 6)
						{
							changeKey();
							printf("\nDirecting to the User Menu...");
						}

						else if (e == 0)
						{
							printf("\nRedirecting to Main Menu...");
						}
						else
						{
							printf("\nOops! %d is an invalid input.", e);
						}
					}
				}
				else if (d == 0)
				{
					wait(1);
					screenReset();

					if (isAdmin == 1)
						printf("\nLogging Out...");
					else
					{
						printf("\nWE COULDN'T VALIDATE YOUR AUTHORISATION.\nYou can try to login again.");
						isAdmin = 0;
					}

					break;
				}
				else
				{
					printf("\nOops! %d is an invalid input.", d);
				}

			} // end of while(MAIN ONE)
		}

		else if (m != 0)
		{
			printf("\n\t\t\tINVALID INPUT! TRY AGAIN!");
		}
	} // end of login while loop
	screenReset();
	backup();

	printf("\nClosing the application...");
	printf("\n------------------------------------------------------------------------------------------------------------------------");

	return 0;
} // main closed

////////////////////////////////////////////////////////////////////////////////
// UTILITY FUNCTIONS
void authorize(int m) // m=1 for user, m=2 for admin
{
	wait(2);
	screenReset();

	char uName[30], uPass[30], admKey[6];
	int i, f = 0, count = 0; // count is for no of times user has tried to access

	if (m == 1) // Authorisation as user
	{
		printf("\nAUTHORISATION AS USER:");

		while (count < maxLoginCount && isUser != 1)
		{
			if (userCount != 0)
			{
				printf("\nEnter Your Credentials below:");

				printf("\nUserName : ");

				fflush(stdin);
				fgets(uName, 30, stdin);

				printf("\nPassword : ");

				fflush(stdin);
				fgets(uPass, 30, stdin);

				for (i = 0; i < userCount; i++)
				{
					if (strcmp(uName, y[i].userName) == 0)
						if (strcmp(uPass, y[i].password) == 0)
						{
							f = 1;
							break;
						}
				}
				if (f == 1)
				{
					isUser = 1;
					break;
				}
				else
				{
					printf("\nUSERNAME OR PASSWORD IS INCORRECT!");

					if (count < maxLoginCount - 1)
						printf("\n%d CHANCES LEFT", (maxLoginCount - count - 1));
					wait(2);
					screenReset();
				}
			}
			else
			{
				printf("\nNO USERS FOUND! ASK YOUR ADMIN TO ADD YOU AS A USER.");
				break;
			}
			count++;
		}

		if (f == 1)
		{
			activeUser = i;
			printf("\nLogged in as %s", y[activeUser].userName);
		}
		else if (count >= maxLoginCount)
		{
			printf("\nToo Many Unsuccessful Attempts!");
			isUser = 0;
		}
		else
		{
			printf("\n");
		}
		wait(4);
		screenReset();
	}
	else if (m == 2) // Authorisation as Admin
	{
		count = 0;
		printf("\nAUTHORISATION AS ADMIN:");
		if (adminCount == 1)
		{
			while (count < 3 && isAdmin != 1)
			{
				printf("\nEnter Admin Key = ");

				fflush(stdin);
				fgets(admKey, 6, stdin);

				count++;
				if (strcmp(admKey, admin0[0].adminKey) == 0)
				{
					isAdmin = 1;
					printf("\nLOGGED IN AS ADMIN");
				}
				else
				{
					printf("\nINCORRECT ADMIN KEY ENTERED!");
					printf("\n%d CHANCES LEFT!", (maxLoginCount - count));
				}
			}
		}
		else
		{
			printf("\nNO ADMINS FOUND!\nDIRECTING TO ADD ADMIN RECORDS...");
			wait(1);
			addAdmin();
		}
	}
	else
	{
		printf("\nInvalid Input!");
	}
}

void import()
{
	// importing from PatientRecords1024.txt
	FILE *fp = fopen("PatientRecords1024.txt", "r");
	if (fp == NULL)
	{
		printf("\nPatients' Backup Not Found!");
		fp = fopen("PatientRecords1024.txt", "w");
		printf("\nNew Patient's Backup File has been created.");
		fclose(fp);
	}
	patCount = fread(x, sizeof(struct Patient), 100, fp);
	printf("\nPatient data imported successfully.");
	fclose(fp);

	// importing from User1024.txt
	FILE *fp2 = fopen("User1024.txt", "r");
	if (fp2 == NULL)
	{
		printf("\nUser Backup Not Found!");
		fp2 = fopen("User1024.txt", "w");
		printf("\nNew User Backup File has been created.");
		fclose(fp2);
	}
	userCount = fread(y, sizeof(struct User), 5, fp2);
	printf("\nUser data imported successfully.");
	fclose(fp2);

	// importing from AdminDetails1024.txt
	FILE *fp3 = fopen("AdminDetails1024.txt", "r");
	if (fp3 == NULL)
	{
		printf("\nAdmin Details' Backup Not Found!");
		fp3 = fopen("AdminDetails1024.txt", "w");
		printf("\nNew Admin Detail's Backup File has been created.");
		fclose(fp3);
	}
	adminCount = fread(admin0, sizeof(struct Admin), 1, fp3);
	printf("\nAdmin Records imported successfully.");
	fclose(fp3);

	// Decrypting all data
	for (int i = 0; i < patCount; i++)
	{
		decrypt(x[i].name);
		decrypt(x[i].disease);
		decrypt(x[i].address);
		x[i].age = decryptInt(x[i].age);
		x[i].cabin = decryptInt(x[i].cabin);
		decrypt(x[i].phone);
	}

	for (int i = 0; i < userCount; i++)
	{
		decrypt(y[i].password);
		decrypt(y[i].userName);
	}

	for (int i = 0; i < adminCount; i++)
	{
		decrypt(admin0[i].adminKey);
		decrypt(admin0[i].hospAdrs);
		decrypt(admin0[i].hospName);
		decrypt(admin0[i].hospContact);
	}
	// DECRYPTION COMPLETED
}

void backup()
{
	// Encrypting all data
	for (int i = 0; i < patCount; i++)
	{
		encrypt(x[i].name);
		encrypt(x[i].disease);
		encrypt(x[i].address);
		x[i].age = encryptInt(x[i].age);
		x[i].cabin = encryptInt(x[i].cabin);
		encrypt(x[i].phone);
	}

	for (int i = 0; i < userCount; i++)
	{
		encrypt(y[i].password);
		encrypt(y[i].userName);
	}

	for (int i = 0; i < adminCount; i++)
	{
		encrypt(admin0[i].adminKey);
		encrypt(admin0[i].hospAdrs);
		encrypt(admin0[i].hospName);
		encrypt(admin0[i].hospContact);
	}
	// ENCRYPTION COMPLETED

	// updating PatientRecords1024.txt
	FILE *fp = fopen("PatientRecords1024.txt", "w");
	if (fp == NULL)
	{
		printf("/nPatient Records Backup File is empty!");
		exit(1);
	}
	fwrite(x, sizeof(struct Patient), patCount, fp);
	printf("\nPatient Records Backup File updated successfully.");
	fclose(fp);

	// updating User1024.txt
	FILE *fp2 = fopen("User1024.txt", "w");
	if (fp2 == NULL)
	{
		printf("/nUser Backup File is empty!");
		exit(1);
	}
	fwrite(y, sizeof(struct User), userCount, fp2);
	printf("\nUser Backup File updated successfully.");
	fclose(fp2);

	// updating AdminDetails1024.txt
	FILE *fp3 = fopen("AdminDetails1024.txt", "w");
	if (fp3 == NULL)
	{
		printf("/nAdmin Details Backup File is empty!");
		exit(1);
	}
	fwrite(admin0, sizeof(struct Admin), adminCount, fp3);
	printf("\nAdmin Details Backup File updated successfully.");
	fclose(fp3);
}

void wait(int noSec)
{
	int f = 0;
	clock_t start_wait;
	clock_t end_wait;

	start_wait = clock();
	end_wait = clock() + noSec * CLOCKS_PER_SEC;

	printf("\nLoading.");

	while (clock() < end_wait)
	{
		if ((clock() - start_wait) % 400 == 0)
		{
			if (f != (clock() - start_wait))
				printf(".");
			f = (clock() - start_wait);
		}
	}
}

void screenReset()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif

	printf("\n--------------------------------------------------------");

	mytime = time(NULL);
	puts(ctime(&mytime));
	printf("\n\t\t\t***Welcome to %s***\n", admin0[0].hospName);

	if (activeUser != -1 && isUser == 1)
		printf("\nLogged in as : %s", y[activeUser].userName);
	else if (isAdmin == 1)
		printf("\nLogged in as : ADMIN");
	else
		printf("\nNot logged in!");

	printf("\n--------------------------------------------------------------------------------");
}

void encrypt(char *S)
{
	/*
		Logic for encryption

		Basic rules applied, but effective enough

		FOR STRING
		if alphabet, first, case is changed then, considering the alphabets forming a circle, the opposite letter is chosen
		if digit, again, opposite digit is chosen, for ex, 0 replaced by 9, 1 replaced by 8
		Other symbols kept as it is
		For Decryption, just reverse the processes
	*/
	int l = strlen(S);
	for (int i = 0; i < l; i++)
	{
		if (S[i] >= 65 && S[i] <= 90) // UPPER CASE LETTERS
		{
			S[i] += 32;
			S[i] = 122 - (S[i] - 97);
		}
		else if (S[i] >= 97 && S[i] <= 122) // LOWER CASE LETTERS
		{
			S[i] -= 32;
			S[i] = 90 - (S[i] - 65);
		}
		else if (S[i] >= 48 && S[i] <= 57) // DIGITS
		{
			S[i] = 57 - (S[i] - 48);
		}
	}
}

void decrypt(char *S)
{
	int l = strlen(S);
	for (int i = 0; i < l; i++)
	{
		if (S[i] >= 65 && S[i] <= 90) // UPPER CASE LETTERS
		{
			S[i] += 32;
			S[i] = 122 - (S[i] - 97);
		}
		else if (S[i] >= 97 && S[i] <= 122) // LOWER CASE LETTERS
		{
			S[i] -= 32;
			S[i] = 90 - (S[i] - 65);
		}
		else if (S[i] >= 48 && S[i] <= 57) // DIGITS
		{
			S[i] = 57 - (S[i] - 48);
		}
	}
}

int encryptInt(int a)
{
	int b = 0;

	while (a != 0)
	{
		b = b * 10 + (9 - a % 10);
		a /= 10;
	}

	a = 0; // for confirmation

	while (b != 0)
	{
		a = a * 10 + b % 10;
		b /= 10;
	}

	return a;
}

int decryptInt(int a)
{
	int b = 0;

	while (a != 0)
	{
		b = b * 10 + (9 - a % 10);
		a /= 10;
	}

	a = 0; // for confirmation

	while (b != 0)
	{
		a = a * 10 + b % 10;
		b /= 10;
	}

	return a;
}

////////////////////////////////////////////////////////////////////////////////
// USER FUNCTIONS
void add()
{
	wait(1);
	screenReset();
	printf("\nPATIENT ADDITION:");

	printf("\nNo of Patients already in the database = %d\n\n",
		   patCount); // how many inputs
	printf("How many entries to make? = ");

	fflush(stdin);
	scanf("%d", &in1);

	if (in1 < 1)
		in1 = 1; // Crash Prevention Measure

	sum = in1 + patCount;

	int zz = patCount; // FOR PRINTING PATIENT NO. BEING ADDED

	for (i = patCount, j = 0; i < sum; i++)
	{
		printf("\n");
		printf("\nPATIENT %d OF %d:", (i - zz + 1), in1);
		printf("\nEnter patient's Name = ");

		fflush(stdin);
		fgets(x[i].name, 30, stdin);

		printf("\nEnter patient's Address =");

		fflush(stdin);
		fgets(x[i].address, 30, stdin);

		printf("\nEnter disease = ");

		fflush(stdin);
		fgets(x[i].disease, 30, stdin);

		printf("\nEnter the age = ");

		fflush(stdin);
		scanf("%d", &x[i].age);

		printf("\nEnter cabin no = ");

		fflush(stdin);
		scanf("%d", &x[i].cabin);

		printf("\nEnter phone number = ");

		fflush(stdin);
		scanf("%s", x[i].phone);

		printf("\n");
		j++;
		a++;
		patCount++;
	}
}

void view()
{
	wait(1);
	screenReset();
	printf("\nPATIENT LIST:");

	if (patCount > 0)
	{
		for (i = 0; i < patCount; i++)
		{
			printf("\n");
			printf("Serial Number :\t%d\n", i);
			printf("Name :\t\t");
			puts(x[i].name);
			printf("Address :\t");
			puts(x[i].address);
			printf("Disease :\t");
			puts(x[i].disease);
			printf("Cabin no :\t%d\nPhone number :\t%s\nAge :\t\t%d", x[i].cabin, x[i].phone,
				   x[i].age);
			printf("\n");
		}
	}
	else
	{
		printf("\nNO PATIENT DETAILS FOUND!");
	}
	printf("\nEnter any no to continue = ");
	int useless;

	fflush(stdin);
	scanf("%d", &useless);
}

void edit()
{
	wait(1);
	screenReset();

	printf("\nPATIENT RECORD EDIT:");
	printf("\nWhat do you want to edit ?\n");
	printf("1.Name\n2.Address\n3.Disease\n4.Age\n5.Cabin\n6.Phone no.\n");
	printf("Enter your choice = ");

	fflush(stdin);
	scanf("%d", &j); // option input

	if (j <= 6)
	{
		printf("Enter the serial no of that patient= (0 - %d)=", patCount - 1);

		fflush(stdin);
		scanf("%d", &i); // serial number

		if (i < patCount)
		{
			if (j == 1)
			{
				printf("Enter the new name=");

				fflush(stdin);
				fgets(x[i].name, 30, stdin);
			}
			else if (j == 2)
			{
				printf("Enter the new address=");

				fflush(stdin);
				fgets(x[i].address, 30, stdin);
			}
			else if (j == 3)
			{
				printf("Enter the new Disease=");

				fflush(stdin);
				fgets(x[i].disease, 30, stdin);
			}
			else if (j == 4)
			{
				printf("Enter the new Age=");

				fflush(stdin);
				scanf("%d", &x[i].age);
			}

			else if (j == 5)
			{
				printf("Enter the new Cabin no=");

				fflush(stdin);
				scanf("%d", &x[i].cabin);
			}

			else if (j == 6)
			{
				printf("Enter the new Phone no =");

				fflush(stdin);
				scanf("%s", x[i].phone);
			}
		}
		else
		{
			printf("\n\nInvalid Serial \nTry Again !!\n\n");
		}
	}
	else
	{
		printf("\n\nInvalid option\nTry Again!!\n\n");
	}
}

void search()
{
	wait(1);
	screenReset();
	printf("\nPATIENT SEARCH:");

	int f;
	char u[100];

	printf("\nBy what do you want to search ?\n");
	printf("1.Serial no.\n2.Name\n3.Addres\n4.Disease\n5.Cabin no.\n6.Phone no.\n7.Age\n0. Go back\n\nOption = ");

	fflush(stdin);
	scanf("%d", &j);

	if (j == 1)
	{
		printf("Enter Serial number of the patient=");

		fflush(stdin);
		scanf("%d", &i);

		if (i < patCount)
		{
			printf("\n");
			printf("Serial Number=%d\n", i);
			printf("Name = ");
			puts(x[i].name);
			printf("Address = ");
			puts(x[i].address);
			printf("Disease = ");
			puts(x[i].disease);
			printf("Cabin no = %d\nPhone number = %s\nAge = %d", x[i].cabin, x[i].phone,
				   x[i].age);
			printf("\n\n");
		}
		else
			printf("\n\nNot Found\n\n");
	}

	else if (j == 2)
	{
		f = 1;
		printf("Enter your name=");

		fflush(stdin);
		fgets(u, 30, stdin);

		for (g = 0; g < patCount; g++)
		{
			if (strcmp(u, x[g].name) == 0)
			{
				printf("\n");
				printf("Serial Number=%d\n", g);
				printf("Name = ");
				puts(x[g].name);
				printf("Address = ");
				puts(x[i].address);
				printf("Disease = ");
				puts(x[g].disease);
				printf("Cabin no = %d\nPhone number = %s\nAge = %d", x[g].cabin, x[g].phone,
					   x[g].age);
				printf("\n\n");
				f = 0;
			}
		}
		if (f == 1)
			printf("\nNot Found\n");
	}
	else if (j == 3)
	{
		printf("Enter Address of the patient=");

		fflush(stdin);
		fgets(u, 30, stdin);

		if (strcmp(u, x[g].address) == 0)
		{
			printf("\n");
			printf("Serial Number=%d\n", i);
			printf("Name = ");
			puts(x[i].name);
			printf("Disease = ");
			puts(x[i].disease);
			printf("Cabin no = %d\nPhone number = %s\nAge = %d", x[i].cabin, x[i].phone,
				   x[i].age);
			printf("\n\n");
		}
		else
			printf("\n\nNot Found\n\n");
	}
	else if (j == 4)
	{
		f = 1;
		printf("Enter Disease = ");

		fflush(stdin);
		fgets(u, 30, stdin);

		for (g = 0; g < patCount; g++)
		{
			if (strcmp(u, x[g].disease) == 0)
			{
				printf("\n");
				printf("Serial Number=%d\n", g);
				printf("Name = ");
				puts(x[g].name);
				printf("Address = ");
				puts(x[i].address);
				printf("Disease = ");
				puts(x[g].disease);
				printf("Cabin no = %d\nPhone number = %s\nAge = %d", x[g].cabin, x[g].phone,
					   x[g].age);
				printf("\n\n");
				f = 0;
			}
		}
		if (f == 1)
			printf("\nNot Found\n");
	}
	else if (j == 5)
	{
		f = 1;
		printf("Enter Cabin number = ");

		fflush(stdin);
		scanf("%d", &f);

		for (g = 0; g < patCount; g++)
		{
			if (f == x[g].cabin)
			{
				printf("\n");
				printf("Serial Number=%d\n", g);
				printf("Name = ");
				puts(x[g].name);
				printf("Address =");
				puts(x[g].address);
				printf("Disease = ");
				puts(x[g].disease);
				printf("Cabin no = %d\nPhone number = %s\nAge = %d", x[g].cabin, x[g].phone,
					   x[g].age);
				printf("\n\n");
				f = 0;
			}
		}
		if (f == 1)
			printf("Not Found\n\n");
	}
	else if (j == 6)
	{
		f = 0;
		char in[15];
		printf("Enter Phone number = ");

		fflush(stdin);
		scanf("%s", in);

		for (g = 0; g < patCount; g++)
		{
			if (strcmp(x[g].phone, in) == 0)
			{
				printf("\n");
				printf("Serial Number=%d\n", g);
				printf("Name = ");
				puts(x[g].name);
				printf("Address =");
				puts(x[g].address);
				printf("Disease = ");
				puts(x[g].disease);
				printf("Cabin no = %d\nPhone number = %s\nAge = %d", x[g].cabin, x[g].phone,
					   x[g].age);
				printf("\n\n");
				f = 1;
			}
		}
		if (f == 0)
			printf("Not Found");
	}
	else if (j == 7)
	{
		f = 1;
		printf("Enter Age = ");

		fflush(stdin);
		scanf("%d", &f);

		for (g = 0; g < patCount; g++)
		{
			if (f == x[g].age)
			{
				printf("\n");
				printf("Serial Number=%d\n", g);
				printf("Name = ");
				puts(x[g].name);
				printf("Address=");
				puts(x[g].address);
				printf("Disease = ");
				puts(x[g].disease);
				printf("Cabin no = %d\nPhone number = %s\nAge = %d", x[g].cabin, x[g].phone,
					   x[g].age);
				printf("\n\n");
				f = 0;
			}
		}
		if (f == 1)
			printf("Not Found\n\n");
	}
	else if (j == 0)
	{
		printf("\n");
	}
	else
	{
		printf("\n\nInvalid input\n\n");
	}

	int useless;
	printf("\nEnter any no to continue = ");

	fflush(stdin);
	scanf("%d", &useless);
}

void del()
{
	wait(1);
	screenReset();
	printf("\nPATIENT RECORD DELETE:");

	printf("\nEnter the index number of the patient that you want to delete(SUGGSTED: -1 TO GO BACK) = ");

	fflush(stdin);
	scanf("%d", &i);

	if (i < patCount)
	{
		printf("What do you want ?\n");
		printf("1. Remove the whole record\n2. Remove Name\n3. Remove Address\n4. Remove Disease\n5. Remove age\n6. Remove Cabin\n7. Remove phone number\n0. GO BACK\nENTER YOUR CHOICE = ");

		fflush(stdin);
		scanf("%d", &j);

		if (j == 1)
		{
			while (i < patCount)
			{
				strcpy(x[i].name, x[i + 1].name);
				strcpy(x[i].disease, x[i + 1].disease);
				x[i].age = x[i + 1].age;
				x[i].cabin = x[i + 1].cabin;
				strcpy(x[i].phone, x[i + 1].phone);
				i++;
			}
			patCount--;
		}
		else if (j == 2)
		{
			strcpy(x[i].name, "Cleared");
		}
		else if (j == 3)
		{
			strcpy(x[i].address, "Cleared");
		}
		else if (j == 4)
		{
			strcpy(x[i].disease, "Cleared");
		}
		else if (j == 5)
		{
			x[i].age = 0;
		}
		else if (j == 6)
		{
			x[i].cabin = 0;
		}
		else if (j == 7)
		{
			strcpy(x[i].phone, "Cleared");
		}
		else
		{
			printf("\nINVALID INPUT!");
		}
	}
	else
		printf("\n\nInvalid Serial number\n");
}

void addUser()
{
	wait(1);
	screenReset();
	printf("\nADD USER:");

	int f1, f2; // f1= ANSWER TO account created?	f2=ANSWER TO username already exists?
	char uName[30], uPass[30];
	int count = 0; // counts no of attempts
	printf("\nNo of Users already in the database = %d", userCount);

	f1 = 0;
	while (f1 != 1 && count < 3)
	{
		f2 = 0;
		printf("\nEnter new username = ");

		fflush(stdin);
		fgets(uName, 30, stdin);

		printf("\nEnter new password =");

		fflush(stdin);
		fgets(uPass, 30, stdin);

		count++;

		for (i = 0; i < userCount; i++)
		{
			if (strcmp(y[i].userName, uName) == 0)
			{
				f2 = 1;
				break;
			}
		}
		if (f2 == 1 && count != 3)
		{
			printf("\nUsername already exists! Try a different username.");
		}
		else if (count != 3)
		{
			strcpy(y[userCount].userName, uName);
			strcpy(y[userCount].password, uPass);
			userCount++;
			f1 = 1;

			printf("\nUser added successfully.");
			printf("\nNo of Users now = %d", userCount);
			wait(3);
		}
	}

	if (f1 != 1)
	{
		printf("Too many unsuccessful attempts!\n");
		wait(2);
	}
}

void viewUsers()
{
	wait(1);
	screenReset();
	printf("\nVIEW USER LIST:");

	if (userCount != 0 && isAdmin == 1)
	{
		printf("\n--------------------");
		for (i = 0; i < userCount; i++)
		{
			printf("\n");
			printf("%d", i);
			printf("\t");
			puts(y[i].userName);
		}
		printf("--------------------");
		printf("\nEnter any no to continue = ");
		int useless;

		fflush(stdin);
		scanf("%d", &useless);
	}
	else if (isAdmin == 1)
	{
		printf("\nNo Users found!");
	}
	else
	{
		printf("\nUNAUTHORISED ACCESS DETECTED!");
		isAdmin = 0;
	}
}

void delUsers()
{

	char check[30];

	wait(1);
	screenReset();
	printf("\nREMOVE USERS:");

	int f = -1;
	if (userCount != 0 && isAdmin == 1)
	{
		while (f != 0)
		{
			printf("\nEnter Index No. of user to remove(-1 to GO BACK) = ");

			fflush(stdin);
			scanf("%d", &f);

			if (f >= 0)
			{

				i = f;
				strcpy(check, y[i].userName);

				while (i < userCount)
				{
					strcpy(y[i].userName, y[i + 1].userName);
					strcpy(y[i].password, y[i + 1].password);
					i++;
				}
				if (f - 1 < activeUser)
					activeUser--;
				userCount--;

				printf("\nUser No. %d(%s) removed successfully.", f, check);
				printf("\nNo of users now = %d", userCount);
			}
			else if (f == -1)
			{
				printf("\n");
				break;
			}
			else
			{
				printf("\nINVALID INPUT! TRY AGAIN!");
			}
		}
	}
	else if (isAdmin == 1)
	{
		system("cls");
		screenReset();
		printf("\n No Users found!");
	}
	else
	{
		printf("\nUNAUTHORISED ACCESS DETECTED");
		isAdmin = 0;
	}
}

void removeSelf()
{
	wait(1);
	screenReset();
	printf("\nREMOVE SELF(USER):");

	int f = 0;
	if (userCount != 0)
	{
		printf("\nYou are going to remove yourself.\nYou will no longer be able to access the application.\nAre you sure?(1 or 0) = ");

		fflush(stdin);
		scanf("%d", &f);

		if (f == 1)
		{

			i = activeUser;
			while (i < userCount)
			{
				strcpy(y[i].userName, y[i + 1].userName);
				strcpy(y[i].password, y[i + 1].password);
				i++;
			}
			userCount--;

			printf("\nUser removed successfully.");
			printf("\nNo of users now = %d", userCount);
			printf("\nMoving to Login Menu...");
			isUser = 0;
		}
	}
	else
	{
		system("cls");
		printf("\n No Users found!\nUnauthorized access detected...");
		isUser = 0;
	}
	wait(2);
}

void editSelf()
{
	wait(1);
	screenReset();
	if (isUser == 1)
	{
		printf("\nEDIT USERNAME AND PASSWORD:");

		int f1 = 0, f2 = 1;
		char check[30];

		printf("\nChange username?(1 or 0)");

		fflush(stdin);
		scanf("%d", &f1);

		if (f1 == 1)
		{
			printf("\nEnter new username = ");

			fflush(stdin);
			fgets(check, 30, stdin);

			// checking if username already exists
			for (i = 0; i < userCount; i++)
			{
				if (i != activeUser)
					if (strcmp(y[i].userName, check) == 0)
					{
						f2 = 1;
						break;
					}
			}
			if (f2 != 1)
				strcpy(y[activeUser].userName, check);
			else
				printf("\nUSERNAME ALREADY EXISTS!");
		}
		else
		{
			printf("\nUsername unchanged.");
		}

		f1 = 0;
		printf("\nChange password?(1 or 0)");

		fflush(stdin);
		scanf("%d", &f1);

		if (f1 == 1)
		{
			printf("\nOkay, but first enter your current password_");

			fflush(stdin);
			scanf("%s", check);

			if (strcmp(check, y[activeUser].password) == 0)
			{
				printf("\nEnter new password = ");

				fflush(stdin);
				fgets(check, 30, stdin);

				strcpy(y[activeUser].password, check);
			}
			else
			{
				printf("\nCURRENT PASSWORD ENTERED IS INCORRECT!");
			}
		}
		else
		{
			printf("\nPassword unchanged.");
		}
	}

	else
	{
		printf("UNAUTHORISED ACCESS DETECTED!");
		isUser = 0;
	}
}
////////////////////////////////////////////////////////////////////////////////
// ADMIN FUNCTIONS
void editAdmin()
{
	if (isAdmin == 1)
	{
		int f1 = 1, f2 = 1, f3 = 1, f9 = 0;
		char check[30];
		char check2[15];

		wait(1);
		screenReset();
		printf("\nEDIT HOSPITAL DETAILS(ADMIN):");

		if (adminCount != 1)
			f9 = 1;

		if (f9 == 0)
		{
			printf("\nChange Hospital Name?(1 or 0)");

			fflush(stdin);
			scanf("%d", &f1);
		}
		if (f1 == 1)
		{
			printf("\nEnter new hospital name = ");

			fflush(stdin);
			fgets(check, 30, stdin);

			strcpy(admin0[0].hospName, check);
		}
		else
		{
			printf("\nHospital Name unchanged.");
		}

		if (f9 == 0)
		{
			printf("\nChange Hospital Address?(1 or 0)");

			fflush(stdin);
			scanf("%d", &f2);
		}
		if (f2 == 1)
		{
			printf("\nEnter new hospital address = ");

			fflush(stdin);
			fgets(check, 30, stdin);

			strcpy(admin0[0].hospAdrs, check);
		}
		else
		{
			printf("\nHospital Address unchanged.");
		}

		if (f9 == 0)
		{
			printf("\nChange Hospital Contact?(1 or 0)");

			fflush(stdin);
			scanf("%d", &f3);
		}
		if (f3 == 1)
		{
			printf("\nEnter new hospital contact = ");

			fflush(stdin);
			fgets(check2, 15, stdin);

			strcpy(admin0[0].hospContact, check2);
		}
		else
		{
			printf("\nHospital Contact unchanged.");
		}
	}

	else
	{
		printf("UNAUTHORISED ACCESS DETECTED!");
		isAdmin = 0;
	}
}

void changeKey()
{
	if (isAdmin == 1)
	{
		char check[30];

		wait(1);
		screenReset();
		printf("\nCHANGE ADMIN KEY:");

		printf("\nFirst, lets verify if its really you, please enter your present key = ");

		fflush(stdin);
		fgets(check, 6, stdin);

		if (strcmp(check, admin0[0].adminKey) == 0)
		{
			printf("\nEnter new key = ");

			fflush(stdin);
			fgets(check, 6, stdin);

			strcpy(admin0[0].adminKey, check);
			printf("\nADMIN KEY UPDATED SUCCESSFULLY!");
		}
		else
		{
			printf("\nWRONG ADMIN KEY ENTERED!UNABLE TO CHANGE KEY!\nTRY A FEW MOMENTS LATER.");
		}
	}

	else
	{
		printf("\nUNATHORISED ACCESS DETECTED!");
		isAdmin = 0;
	}
	wait(3);
}

void viewAdmin()
{
	wait(1);
	screenReset();

	int checkN;

	if (isAdmin == 1)
	{
		printf("\nVIEW ADMIN DETAILS");
		printf("\nHospital Name : %s Hospital", admin0[0].hospName);
		printf("\nAddress : %s", admin0[0].hospAdrs);
		printf("\nContact : %s", admin0[0].hospContact);
		printf("\nEnter any no to continue = ");

		fflush(stdin);
		scanf("%d", &checkN);
	}
	else
	{
		printf("\nUNAUTHORISED ACCESS DETECTED!");
		isAdmin = 0;
	}
	printf("\n");
}

void addAdmin()
{
	char check[30];
	char check2[15];
	char keyIn[6];

	wait(1);
	screenReset();
	printf("\nEDIT HOSPITAL DETAILS(ADMIN):");

	printf("\nEnter Hospital Name = ");

	fflush(stdin);
	fgets(check, 30, stdin);

	strcpy(admin0[0].hospName, check);

	printf("\nEnter Hospital Address = ");

	fflush(stdin);
	fgets(check, 30, stdin);

	strcpy(admin0[0].hospAdrs, check);

	printf("\nEnter Contact No. = ");

	fflush(stdin);
	scanf("%s", check2);

	strcpy(admin0[0].hospContact, check2);
	printf("\nEnter Admin Key(exactly 6 lettered) = ");

	fflush(stdin);
	fgets(keyIn, 6, stdin);

	strcpy(admin0[0].adminKey, keyIn);

	isAdmin = 1;
	adminCount = 1;
	printf("\nADMIN DETAILS ADDED SUCCESSFULLY!");
}
// END OF PROGRAM