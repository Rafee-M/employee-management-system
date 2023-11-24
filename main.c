#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include <time.h>

void calculateSalary();
void showAll_info();
void showAll_tasks();
void modify_empInfo();
void assignTask();
void viewTasks(int userID);
void markTaskAsCompleted(int userID, FILE *ft);

void currenTime()
{
    //currrent time
    time_t current = time(NULL);

//putting the value of time into a structure

    struct tm local_time = *localtime(&current);

//printing

//determining weekday name

    char day[11];
    switch(local_time.tm_wday)
    {
    case 0:
        strcpy(day, "Sunday");
        break;
    case 1:
        strcpy(day, "Monday");
        break;
    case 2:
        strcpy(day, "Tuesday");
        break;
    case 3:
        strcpy(day, "Wednesday");
        break;
    case 4:
        strcpy(day, "Thursday");
        break;
    case 5:
        strcpy(day, "Friday");
        break;
    case 6:
        strcpy(day, "Saturday");
        break;
    }

    printf("Day and Date: %s, %d-%d-%d", day, local_time.tm_mday, local_time.tm_mon, 1900+local_time.tm_year);

}
struct emp
{
    int ID;
    char name[40];
    char position[20];
    int salary;
    char username[30];
    char password[30];
} e;


void adminLogin()
{
    char adminName[] = "ad";
    char adminPass[] = "ad";
    char input [2][30];
    char back [5] = "exit";
    printf("\n\n#### Admin Login Portal ####");
    printf("\n --(type exit to go back)--");

    while(1)
    {

        printf("\n\nEnter admin username: ");
        fgets(input[0], sizeof(input[0]), stdin);
        printf("\nEnter admin password: ");
        fgets(input[1], sizeof(input[1]), stdin);

        if(input[0][strlen(input[0])-1] == '\n')
        {
            input[0][strlen(input[0])-1] = '\0';
        }
        if(input[1][strlen(input[1])-1] == '\n')
        {
            input[1][strlen(input[1])-1] = '\0';
        }
        if (strcmp(back,input[0])==0 || strcmp(back, input[1])==0)
        {
            return;
        }

        if (strcmp(input[0],adminName)==0 && strcmp(input[1], adminPass)==0)
        {
            printf("Login successful");

            int response;
            while(1)
            {
                printf("\n\n### Menu ###:"); //admin menu printing
                printf("\n#Info: ");
                printf("\n1. View all employee info");
                printf("\n2. View all assigned tasks");
                printf("\n3. Calculate salary");

                printf("\n\n#Edit:");
                printf("\n4. Modify employee info");
                printf("\n5. Assign task");
                printf("\n6. Log out");

                printf("\n\nWhat would you like to do: ");
                scanf("%d", &response);
                getchar(); //to prevent new line from skipping

                switch (response) //admin menu actions
                {
                case 1:
                    showAll_info();
                    break;
                case 2:
                    showAll_tasks();
                    break;
                case 3:
                    calculateSalary();
                    break;
                case 4:
                    modify_empInfo();
                    break;
                case 5:
                    assignTask();
                    break;
                case 6:
                    return;
                default:
                    printf("Invalid input. Please choose between 1-6.");
                }
            }

        }
        else
        {
            printf("Invalid login credentials, try again");
        }
    }
}


void userLogin()
{
    char back[5] = "exit";
    char input[2][30];
    printf("\n\n#### User Login Portal ####");
    printf("\n --(type exit to go back)--");
    int response;
    int userID;
    FILE *fp, *ft;
    fp = fopen("info.txt", "r");

    if (fp == NULL)
    {
        printf("[MAJOR ERROR] File cannot be opened");
        exit(1);
    }

    while (1)
    {
        printf("\n\nEnter username: ");
        fgets(input[0], sizeof(input[0]), stdin);
        printf("\nEnter password: ");
        fgets(input[1], sizeof(input[1]), stdin);

        if (input[0][strlen(input[0]) - 1] == '\n')
        {
            input[0][strlen(input[0]) - 1] = '\0';
        }
        if (input[1][strlen(input[1]) - 1] == '\n')
        {
            input[1][strlen(input[1]) - 1] = '\0';
        }
        if (strcmp(back,input[0])==0 || strcmp(back, input[1])==0)
        {
            return;
        }

        fseek(fp, 0, SEEK_SET);

        while (fscanf(fp, "%d %s %s %d %s %s", &e.ID, e.name, e.position, &e.salary, e.username, e.password) != EOF)
        {
            if (strcmp(e.username, input[0]) == 0 && strcmp(e.password, input[1]) == 0)
            {
                printf("\nLogin successful");
                int userID = e.ID;
                printf("\nWelcome user ID %d", userID);

                while (1)
                {
                    printf("\n\nMenu:");
                    printf("\n1. View personal information");
                    printf("\n2. View tasks");
                    printf("\n3. Log out");

                    printf("\n\nWhat would you like to do: ");
                    scanf("%d", &response);

                    switch (response)
                    {
                    case 1:
                        printf("\nID: %d", e.ID);
                        printf("\nName: %s", e.name);
                        printf("\nPosition: %s", e.position);
                        printf("\nSalary: %d", e.salary);
                        printf("\nUsername: %s", e.username);
                        printf("\nPassword: %s", e.password);
                        printf("\n%d %s %s %d %s %s", e.ID, e.name, e.position, e.salary, e.username, e.password);
                        break;
                    case 2:
                        viewTasks(userID); // Call a separate function for viewing and marking tasks
                        break;
                    case 3:
                        fclose(fp); // Close the file before returning
                        return;
                    default:
                        printf("Invalid input. Please choose between 1-3");
                    }
                }
            }
        }
        printf("Invalid login credentials, try again");
    }
}

void viewTasks(int userID)
{
    FILE *ft;
    char line[1000];
    ft = fopen("tasks.txt", "r");

    if (ft == NULL)
    {
        printf("[MAJOR ERROR] File cannot be opened");
        exit(1);
    }

    int taskID;
    char response;

    while (1)
    {
        printf("\n\n1. List assigned tasks");
        printf("\n2. Mark a task as completed");
        printf("\n3. Back");

        printf("\n\nWhat would you like to do: ");
        scanf("%d", &response);

        switch (response)
        {
        case 1:
            fseek(ft, 0, SEEK_SET);
            printf("\nTasks assigned to ID %d: \n", userID);
            while (fgets(line, sizeof(line), ft) != NULL)
            {
                if (strstr(line, "[ID ") != NULL)
                {
                    int taskID;

                    if (sscanf(line, "[ID %d]", &taskID) == 1 && taskID == userID)
                    {
                        // Print the task
                        printf("%s", line);
                    }
                }
            }
            break;
        case 2:
            markTaskAsCompleted(userID, ft); // Pass the user ID and tasks file to the function
            break;
        case 3:
            fclose(ft); // Close the file before returning
            return;
        default:
            printf("Invalid input. Please choose between 1-3");
        }
    }
}


void markTaskAsCompleted(int userID, FILE *ft)
{
    char line[1000];
    char compTask[1000];
    printf("Enter task as completed in the format '[ID yourID] - task': ");

    getchar(); // consume the newline character
    fgets(compTask, sizeof(compTask), stdin);
    if (compTask[strlen(compTask) - 1] == '\n')
    {
        compTask[strlen(compTask) - 1] = '\0';
    }

    FILE *fp = fopen("tasks_temp.txt", "w");

    if (fp == NULL)
    {
        printf("[MAJOR ERROR] File cannot be opened");
        exit(1);
    }

    fseek(ft, 0, SEEK_SET);

    while (fgets(line, sizeof(line), ft) != NULL)
    {
        char *found = strstr(line, compTask);
        if (found != NULL)
        {
            // Append the [COMPLETED] status to the same line
            found[strlen(compTask)] = '\0'; // truncate the line at the found position
            fprintf(fp, "%s - [COMPLETED]\n", line);
            printf("Task marked as completed");
        }
        else
        {
            fprintf(fp, "%s", line);
        }
    }

    fclose(fp);
    fclose(ft);

    remove("tasks.txt");
    rename("tasks_temp.txt", "tasks.txt");
}




int main()
{

    printf("----Employee Login & Attendance System----\n    ");
    currenTime();
    printf("\n\n");




    int response;
    while(1)
    {
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit");
        printf("\n\nWhat would you like to do: ");
        scanf("%d", &response);
        getchar(); //to prevent new line from skipping

        switch (response)
        {
        case 1:
            adminLogin();
            break;
        case 2:
            userLogin();
            break;
        case 3:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid input. Please choose 1, 2 or 3");
        }
    }

}

void showAll_info()
{
    FILE *fp;
    fp = fopen("info.txt", "r+");

    if (fp == NULL)
    {

        printf("[MAJOR ERROR] File cannot be opened");
        exit (1);
    }
    printf("\n%-4s %-14s %-12s %-8s %-15s %-20s", "ID", "Name", "Position", "Salary", "Username", "Password");

    while (fscanf(fp, "%d %s %s %d %s %s", &e.ID, e.name, e.position, &e.salary, e.username, e.password) != EOF)
    {
        // Print data with formatting
        printf("\n%-4d %-14s %-12s %-8d %-15s %-20s", e.ID, e.name, e.position, e.salary, e.username, e.password);
    }
    fclose(fp);

}

void showAll_tasks()
{
    FILE *fp;
    char ch;
    fp = fopen("tasks.txt", "r");

    if (fp == NULL)
    {
        printf("[MAJOR ERROR] File cannot be opened");
        exit (1);
    }
    printf("\n## Assigned Tasks ##\n\n");
    while ((ch = fgetc(fp))!= EOF)
    {
        printf("%c", ch);
    }

}

void calculateSalary()
{
    FILE *fp;
    fp = fopen("info.txt", "r");
    int userID, days, salary;

    if (fp == NULL)
    {
        printf("[MAJOR ERROR] File cannot be opened");
        exit(1);
    }

    printf("Enter target employee ID: ");
    scanf("%d", &userID);
    printf("Enter number of days: ");
    scanf("%d", &days);

    while (fscanf(fp, "%d %s %s %d %s %s", &e.ID, e.name, e.position, &e.salary, e.username, e.password) != EOF)
    {
        if (userID == e.ID)
        {
            salary = days * e.salary;
            printf("The salary for %d day(s) at %d/day for employee ID %d is: %d\n", days, e.salary, userID, salary);
            break;
        }
        printf("ID not found, try again");
    }

    fclose(fp);
}

void modify_empInfo()
{
    FILE *fp, *ft;
    fp = fopen("info.txt", "a+");
    if (fp == NULL)
    {
        printf("[MAJOR ERROR] File cannot be opened");
        exit (1);
    }
    int response;
    while (1)
    {

        int tempID;
        printf("\n\n1. Create new entry");
        printf("\n2. Edit existing entry");
        printf("\n3. Back");
        printf("\n\nWhat would you like to do: ");
        scanf("%d", &response);
        getchar();

        switch (response)
        {
        case 1:
        {
            char another = 'y';
            while (another == 'y')
            {
                printf("Enter ID: ");
                scanf("%d", &tempID);
                getchar();
                int idExists = 1; // Flag to check if the ID already exists

                // Check if the ID already exists in the file
                while (fscanf(fp, "%d %s %s %d %s %s", &e.ID, e.name, e.position, &e.salary, e.username, e.password) != EOF)
                {
                    if (tempID == e.ID)
                    {
                        printf("This ID already exists. Enter a new ID: ");
                        scanf("%d", &tempID);
                        getchar();
                        rewind(fp);
                        idExists = 1;

                    }
                }

                // If the ID doesn't exist, proceed with data entry


                e.ID = tempID;
                printf("\nEnter name(single name): ");
                gets(e.name);
                printf("Enter position: ");
                gets(e.position);
                printf("Enter salary(per day): ");
                scanf("%d", &e.salary);
                getchar();
                printf("Enter username: ");
                gets(e.username);
                fflush(stdin);
                printf("Enter password: ");
                gets(e.password);
                fflush(stdin);

                fprintf(fp, "%d %s %s %d %s %s\n", e.ID, e.name, e.position, e.salary, e.username, e.password);

                printf("Would you like to add another entry? (y/n)");
                scanf("%c", &another);

            }
            fclose(fp);

        }
        break;
        case 2:
        {
            int searchID;
            char another = 'y';
            while (another == 'y')
            {
                fseek(fp, 0, SEEK_SET);
                printf("Enter the employee ID you wish to edit: ");
                scanf("%d", &searchID);
                getchar();

                ft = fopen("temp.txt", "w");

                while(fscanf(fp, "%d %s %s %d %s %s", &e.ID, e.name, e.position, &e.salary, e.username, e.password) != EOF)
                {
                    if (searchID == e.ID)
                    {
                        printf("Enter new name (single name) for ID %d: ", searchID);
                        gets(e.name);
                        printf("Enter new position for ID %d: ", searchID);
                        gets(e.position);
                        printf("Enter new salary(per day) for ID %d: ", searchID);
                        scanf("%d", &e.salary);
                        getchar();
                        printf("Enter new username for ID %d: ", searchID);
                        gets(e.username);
                        printf("Enter new password for ID %d: ", searchID);
                        gets(e.password);
                    }
                    fprintf(ft, "%d %s %s %d %s %s\n", e.ID, e.name, e.position, e.salary, e.username, e.password);
                }
                fclose(fp);
                fclose(ft);
                remove("info.txt");
                rename("temp.txt", "info.txt");
                fp = fopen("info.txt", "a+");
                fflush(stdin);

                printf("Modify another entry? (y/n): ");
                scanf("%c", &another);
            }
            break;

        }
        case 3:
            return;
        default:
            printf("Invalid selection. Please choose between 1-3");

        }

    }
}



void assignTask()
{
    FILE *fp, *ft;
    fp = fopen("tasks.txt", "a+");
    ft = fopen("info.txt", "r");

    if (fp == NULL || ft == NULL)
    {
        printf("[MAJOR ERROR] File cannot be opened");
        exit(1);
    }

    int taskID;
    char task[1000];
    char response;

    while(1)
    {
        printf("Enter the ID of the employee you want to assign a task to: ");
        scanf("%d", &taskID);
        getchar();
        // Check if both ID and salary are read successfully
        while (fscanf(ft, "%d %s %s %d %s %s", &e.ID, e.name, e.position, &e.salary, e.username, e.password) != EOF)
        {
            if (taskID == e.ID)
            {
                printf("Type the task you would like to assign: ");
                gets(task);
                fprintf(fp, "[ID %d] - %s\n", taskID, task);

                printf("Task assigned successfully.\n");
                fflush(stdin);


                // Reset the file pointer to the beginning of the file
                fseek(ft, 0, SEEK_SET);
                break;
            }

        }
        printf("Assign more tasks? (y/n): ");
        scanf(" %c", &response);
        if (response != 'y')
        {
            break;
        }
    }
    fclose(ft);
    fclose(fp);
}

