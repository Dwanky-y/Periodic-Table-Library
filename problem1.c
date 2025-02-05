
#include <stdio.h>
#include <string.h>
#define MAXNAME 51

struct element
{
    // Components should include the atomic number (an
    // integer); the name, chemical symbol, and class (strings); a numeric field for
    // the atomic Weight; and a seven-element array of integers for the number of
    // electrons in each shell.

    int atomicNum;
    char name[MAXNAME]; // string
    char symbol[3];
    char class[MAXNAME]; // string

    float weight;
    int electrons[7]; // int
};
// you need to identify if struct
struct element createElement(int atomicNum, char name[], char symbol[], char class[], float weight, int electrons[])
{

    struct element createdElement;

    createdElement.atomicNum = atomicNum; // asigns int to atomicNum

    strncpy(createdElement.name, name, MAXNAME - 1); // strncpy is needed because you cant assign an array to a string otherwise
    createdElement.name[MAXNAME - 1] = '\0';         // Ensure null-termination

    strncpy(createdElement.symbol, symbol, 3);
    createdElement.symbol[2] = '\0'; // Ensure null-termination

    strncpy(createdElement.class, class, MAXNAME - 1);
    createdElement.class[MAXNAME - 1] = '\0'; // Ensure null-termination

    createdElement.weight = weight;

    for (int index = 0; index < 7; index++) // loops through 7
    {
        createdElement.electrons[index] = electrons[index]; // gets the electron at index, asigns it to struct electrons
    }

    return createdElement;
}

// Array to store elements of the periodic table
struct element periodicTable[120] = {
    // 1 Hydrogen H non_metal 1.01 1 0 0 0 0 0 0
    {1, "Hydrogen", "H", "non_metal", 1.01, {1, 0, 0, 0, 0, 0, 0}}}; // AtomicNum - 1 = index

struct element print_element(int atomicNum)
{ // get element by atomic num

    struct element foundElement = periodicTable[atomicNum - 1];
    // printf("Name of element: %s", foundElement.name);
    printf("Atomic num: %d, Name: %s, Symbol: %s, Class: %s, Weight: %f, electron: %d %d %d %d %d %d %d\n",
           foundElement.atomicNum, foundElement.name, foundElement.symbol, foundElement.class, foundElement.weight,
           foundElement.electrons[0], foundElement.electrons[1], foundElement.electrons[2], foundElement.electrons[3],
           foundElement.electrons[4], foundElement.electrons[5], foundElement.electrons[6]);

    return foundElement;
}

int main()
{
    // 11 Sodium Na alkali_metal 22.9898 2 8 1 0 0 0 0
    //  printf("Enter element data as <AtomicNum> <Name> <Symbol> <class> <weight> <electrons (7)>");
    //  scanf("%d %s %s %s %s %f %d %d %d %d %d %d %d %d");
    print_element(1);
    // 11 Sodium Na alkali_metal 22.9898 2 8 1 0 0 0 0
    int sodiumElectrons[7] = {2, 8, 1, 0, 0, 0, 0};
    struct element sodium = createElement(11, "Sodium", "Na", "alkali_metal", 22.9898, sodiumElectrons);
    periodicTable[sodium.atomicNum - 1] = sodium;
    print_element(11);

    int running = 1;
    while (running)
    {

        int answer;
        printf("Add element (1) look up element (2) read from file (3) to write to output (4) end the program (-1) \n");
        scanf("%d", &answer);

        if (answer == 1) // Creating Element
        {
            int atomicNumber;
            printf("Enter Atomic Number: \n");
            scanf("%d", &atomicNumber);

            if (atomicNumber > 0 && atomicNumber <= 120 && periodicTable[atomicNumber - 1].atomicNum == atomicNumber)
            { // Check if atomic number is valid or it is in the array
                printf("Element already exist! or it is out of bounds!\n");
                continue;
            }

            printf("Creating Element! \n");

            // Gets atom info
            char name[MAXNAME];
            printf("Enter name: \n");
            scanf("%s", &name);
            // name[strcspn(name, "\n")] = '\0'; // removes newline character

            printf("Enter symbol: \n");
            char symbol[3];
            scanf("%s", symbol);

            printf("Enter class: \n");
            char class[MAXNAME];
            fgets(class, MAXNAME, stdin);
            scanf("%s", &class);

            printf("Enter weight: \n");
            float weight;
            scanf("%f", &weight);

            int electrons[7];

            for (int index = 0; index < 7; index++)
            {
                int electron;
                printf("Enter %d electron: ", index + 1);
                scanf("%d", &electron);
                electrons[index] = electron;
            }

            struct element newElement = createElement(atomicNumber, name, symbol, class, weight, electrons);
            periodicTable[newElement.atomicNum - 1] = newElement;
        }
        else if (answer == 2)
        {
            int atomicNumber;
            printf("Enter Atomic Number: \n");
            scanf("%d", &atomicNumber);

            if (atomicNumber > 0 && atomicNumber <= 120 && periodicTable[atomicNumber - 1].atomicNum != atomicNumber)
            { // Check if atomic number is valid or it is in the array
                printf("Element does not exist! or it is out of bounds!\n");
                continue;
            }
            print_element(atomicNumber);
        }

        else if (answer == 3)
        { // Reading from file
            FILE *fileOfElements = fopen("elements.txt", "r");

            if (fileOfElements != NULL)
            {
                int atomicNum;
                char name[MAXNAME];
                char symbol[3];
                char class[MAXNAME];
                float weight;
                int electrons[7];

                while (fscanf(fileOfElements, "%d %50s %2s %50s %f %d %d %d %d %d %d %d", // gets input from file, '%50s' only allows for 50 char
                              &atomicNum, name, symbol, class, &weight,
                              &electrons[0], &electrons[1], &electrons[2], &electrons[3], &electrons[4], &electrons[5], &electrons[6]) == 12) // '== 12' expects 12 elements
                {
                    struct element newElement = createElement(atomicNum, name, symbol, class, weight, electrons);
                    periodicTable[newElement.atomicNum - 1] = newElement;
                    printf("Atomic Number is: %d\n", newElement.atomicNum);
                }
                printf("Done reading file!\n");
            }

            else
            { // File does not exist for some reason
                printf("File does not exist!!!!!\n");
            }
        }

        else if (answer == 4)
        { // writing into file
            printf("Saving periodic table to file!\n");
            FILE *output = fopen("output.txt", "w");

            for (int index = 0; index < 120; index++)
            { // loops through 120 (length of periodic table)
                struct element foundElement = periodicTable[index];

                if (foundElement.atomicNum != 0)
                { // if the element is added
                    printf("Atomic Number: %d\n", periodicTable[index].atomicNum);
                    // %d %50s %2s %50s %f %d %d %d %d %d %d %d
                    //<AtomicNum> <Name> <Symbol> <class> <weight> <electrons (7)>
                    // fprintf(output, "testing\n");
                    fprintf(output, "%d %50s %2s %50s %f %d %d %d %d %d %d %d\n",
                            foundElement.atomicNum, foundElement.name, foundElement.symbol, foundElement.class, foundElement.weight,
                            foundElement.electrons[0], foundElement.electrons[1], foundElement.electrons[2], foundElement.electrons[3],
                            foundElement.electrons[4], foundElement.electrons[5], foundElement.electrons[6]);
                }
            }

            printf("Done writing to file!\n");
            fclose(output); // Closes the file, MANDATORY!!! it will not work otherwise
            // fprintf(output, )
        }
        else if (answer == -1)
        { // User ends program
            printf("Ending program! \n");
            running = 0;
            break;
        }

        else
        { // User inputted something not valid, ex 9
            printf("Error: Not a valid input!");
        }
    }

    return 0;
}