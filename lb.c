#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct book 
{
    int id;
    char title[50];
    int copies; 
} bk;

struct student
{
    int rollno;
    char name[30];
} st;
// Function declarations
int avlBookId(int id);
void insert();
void display();
void search();
void deleteBook();
void update();
void sort();
void studentName();
void purchases();
void booksAvailable();
int empty();
// Function to insert book records
void insert() 
{
    FILE *fp1;
    fp1 = fopen("Library","a");
    printf("Enter Book ID:");
    scanf("%d", &bk.id);
    printf("Enter Title:");
    scanf("%s", bk.title);
    printf("Enter Copies:");
    scanf("%d", &bk.copies);
    fwrite(&bk, sizeof(bk), 1, fp1);
    fclose(fp1);
}
// Function to display all books
void display() 
{
    FILE *fp2;
    fp2 = fopen("Library", "r");
    printf("\nBook ID\tTitle\t\tCopies\n\n");
    while (fread(&bk, sizeof(bk), 1, fp2))
    printf("%d\t %s \t  %d\n", bk.id, bk.title, bk.copies);
    fclose(fp2);
}
// Function to search a book by ID
void search() 
{
    FILE *fp3;
    int r, s, avl;
    printf("\nEnter Book ID to search: ");
    scanf("%d", &r);
    avl = avlBookId(r);
    if (avl == 0)
        printf("Book ID %d is not available in the file\n", r);
    else 
	{
        fp3 = fopen("Library", "r");
        while (fread(&bk, sizeof(bk), 1, fp3)) {
            s = bk.id;
            if (s == r) 
			{
                printf("\nBook ID= %d", bk.id);
                printf("\nTitle= %s", bk.title);
                printf("\nCopies= %d\n", bk.copies);
            }
        }
        fclose(fp3);
    }
}
//Function to delete a book record
void deleteBook()
{
	FILE *fpo, *fpt;
	int r,s;
	printf("Enter book ID to delete:");
	scanf("%d",&r);
	if (avlBookId(r)==0)
	printf("Book ID %d is not available\n"),r;
	else
	fpo = fopen("Library", "r");
    fpt = fopen("TempFile", "w");
    while (fread(&bk, sizeof(bk), 1, fpo))
	{
		s=bk.id;
        if (s != r)
        fwrite(&bk, sizeof(bk), 1, fpt);
    }
        fclose(fpo);
        fclose(fpt);
        fpo = fopen("Library", "w");
        fpt = fopen("TempFile", "r");
        while (fread(&bk, sizeof(bk), 1, fpt))
        fwrite(&bk, sizeof(bk), 1, fpo);
        fclose(fpo);
        fclose(fpt);
        printf("\nRECORD DELETED\n");
}
//Function to update a book
void update() 
{
    int avl, r, s, ch;
    FILE *fpo, *fpt;
    printf("Enter Book ID to update: ");
    scanf("%d", &r);
    avl = avlBookId(r);
    if (avl == 0) 
	{
    printf("Book ID %d is not available in the file\n", r);
    } else 
	{
        fpo = fopen("Library", "r");
        fpt = fopen("TempFile", "w");
        while (fread(&bk, sizeof(bk), 1, fpo)) {
        s = bk.id;
        if (s != r)
        fwrite(&bk, sizeof(bk), 1, fpt);
        else 
		{
            printf("\n1. Update Title");
            printf("\n2. Update Copies");
            printf("\n3. Update Both");
            printf("\nEnter your choice: ");
            scanf("%d", &ch);
            switch (ch) 
			{
                case 1:
                printf("Enter New Title: ");
                scanf("%s", bk.title);
                break;
                case 2:
                printf("Enter New Copies: ");
                scanf("%d", &bk.copies);
                break;
                case 3:
                printf("Enter New Title: ");
                scanf("%s", bk.title);
                printf("Enter New Copies: ");
                scanf("%d", &bk.copies);
                break;
                default:
                printf("Invalid choice");
                break;
                }
               
            }
        }
//        fclose(fpo);
//        fclose(fpt);
//        fpo = fopen("Library", "w");
//        fpt = fopen("TempFile", "r");
//        while (fread(&bk, sizeof(bk), 1, fpt))
//        fwrite(&bk, sizeof(bk), 1, fpo);
//        fclose(fpo);
//        fclose(fpt);
//        printf("\nRECORD UPDATED\n");
    }
}
// Function to sort books by ID
void sort() 
{
    int a[50], count = 0, i, j, t, c;
    FILE *fp;
    fp = fopen("Library", "r");
    while (fread(&bk, sizeof(bk), 1, fp))
	{
        a[count] = bk.id;
        count++;
    }
    c = count;
    for (i = 0; i < count - 1; i++) 
	{
        for (j = i + 1; j < count; j++) 
		{
            if (a[i] > a[j]) 
			{
                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
    printf("Book ID\tTitle\t\tCopies\n\n");
    count = c;
    for (i = 0; i < count; i++) 
	{
        rewind(fp);
        while (fread(&bk, sizeof(bk), 1, fp)) 
		{
            if (a[i] == bk.id)
            printf("%d\t%s\t\t%d\n", bk.id, bk.title, bk.copies);
        }
    }
    fclose(fp);
}
// Function to add/display student names
void studentName() 
{
    FILE *fp;
    int kids;
    printf("\n1. Add Student\n2. Display Students\nEnter kids:");
    scanf("%d", &kids);
    if (kids == 1) 
	{
        fp = fopen("Students", "a");
        printf("Enter Roll No: ");
        scanf("%d", &st.rollno);
        printf("Enter Name: ");
        scanf("%s", st.name);
        fwrite(&st, sizeof(st), 1, fp);
        fclose(fp);
    }
	else
	{
        fp = fopen("Students", "r");
        printf("\nRoll No\tName\n\n");
        while (fread(&st, sizeof(st), 1, fp))
        printf("%d\t%s\n", st.rollno, st.name);
        fclose(fp);
    }
}
//Functions to record purchase of books
void purchases()
{
	int r, s, buy;
	FILE *fpo, *fpt;
	printf("Enter the Book ID:");
	scanf("%d",&r);
	if (avlBookId(r)==0)
	{
		printf("Book ID %d for purchase:");
		scanf("%d",&r);
	}
	else
	{
	   printf("Enter number of copies to purchase:");
       scanf("%d", &buy);
       fpo = fopen("Library", "r");
       fpt = fopen("TempFile", "w");
	   
	   while(fread(&bk,sizeof(bk),1,fpo))
	   {
	   	if(s==r)//to check the book id matches BookID
	   	{
	   		if (bk.copies >=buy)//number of copies available
	   		{
	   			bk.copies -= buy;//subtract num of copies
				printf("\nPurchase successful %d",buy);    
			}
			else
			{
				printf("\nNot enough copies for purchase %d", bk.copies);
			}
		}
		
		}	
	} fclose(fpo);//close original libraray file
	  fclose(fpt);//temp file,write mode
	  fpo = fopen("Library", "w");//reopen to update
      fpt = fopen("TempFile", "r");//reopen to read (for checking)

        while 
		(fread(&bk, sizeof(bk), 1, fpt))//copy all record
        fwrite(&bk, sizeof(bk), 1, fpo);//making changes permanent 

        fclose(fpo);//final closing
        fclose(fpt);
}
//Function to show only availabe books
void booksAvailable()
{
	FILE *fp;
	fp = fopen("Library","r");//opens library in read mode
	printf("\nAvailable Books:\n");
    printf("Book ID\tTitle\t\tCopies\n\n");//shows bookId,title,copies
    while (fread(&bk, sizeof(bk), 1, fp)) //reading one record(book) at a time from file
	{
        if (bk.copies > 0)//how many copy
        printf("%d\t%s\t\t%d\n", bk.id, bk.title, bk.copies);//if yes the print details
    }
    fclose(fp);//end of loop
}
//Function to chcek if a book is availabe 
int avlBookId(int id)
{
	FILE *fp;
	fp = fopen("Library", "r");
    while (fread(&bk, sizeof(bk), 1, fp)) 
	{
        if (id == bk.id) 
		{
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
// Function to check if file is empty
int empty() 
{
    FILE *fp;
    int c = 0;
    fp = fopen("Library", "r");
    while (fread(&bk, sizeof(bk), 1, fp))
    c = 1;
    fclose(fp);
}
//Main program
int main()
{
	int choice, emp;
	do
	{
	 printf("\n--- Library Management System ---\n");
        printf("1. Insert Book\n2. Display Books\n3. Search Book\n");
        printf("4. Delete Book\n5. Update Book\n6. Sort Books\n");
        printf("7. Student Name\n8. Purchases\n9. Books Available\n10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
		{
            case 1:
			insert();
			break;
            case 2: 
			display();
			break;
            case 3: 
			search(); 
			break;
            case 4: 
			deleteBook(); 
			break;
            case 5: 
			update(); 
			break;
            case 6: 
			sort(); 
			break;
            case 7: 
			studentName(); 
			break;
            case 8: 
			purchases(); 
			break;
            case 9: 
			booksAvailable(); 
			break;
            case 10: 
			exit(0);
            default: 
			printf("\nInvalid choice! Try again...\n"); 
			break;
        }
    } while (choice != 10);
    return 0;	
}
