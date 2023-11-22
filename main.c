#include<stdio.h>
#include <string.h>

void showAll_info();

void adminLogin()
{
    char adminName[] = "ad";
    char adminPass[] = "ad";
    char input [2][30];
    printf("\n\n#### Admin Login Portal ####");

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

        if (strcmp(input[0],adminName)==0 && strcmp(input[1], adminPass)==0)
        {
            printf("Login successful");

            int response;
            while(1)
            {
                printf("\n\nMenu:"); //admin menu printing
                printf("\n#Info: ");
                printf("\n1. View all employee info");
                printf("\n2. View all assigned tasks");
                printf("\n3. View employee info and tasks");

                printf("\n\nEdit:");
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
                    show_empInfo();
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

}

int main()
{
    printf("Employee Login & Attendance System\n");


    int response;
    while(1)
    {
        printf("1. Admin Login\n");
        printf("2. User Login\n");
        printf("3. Exit\n");
        printf("What would you like to do: ");
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

}

void showAll_tasks()
{

}

void show_empInfo()
{

}

void modify_empInfo()
{

}

void assignTask()
{

}
