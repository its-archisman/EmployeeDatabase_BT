#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// The following is a employee in the organisation, it has the pointer to two more employees a subordinate_1 and a subordinate_2
struct Employee {
    int emp_id; // emp_ids will be unique
    char* emp_name;
    int emp_salary;
    struct Employee* subordinate_1;
    struct Employee* subordinate_2;
};

// The following function creates a employee and returns its pointer
struct Employee* create_employee(int id, char* name, int salary) {
    struct Employee* ptr = (struct Employee*) malloc(sizeof(struct Employee));
    ptr->emp_id = id;
    ptr->emp_salary = salary;
    ptr->emp_name = strdup(name);
    // strdup() creates a copy of the string or char pointer and stores it in the new char pointer of the employee
    ptr->subordinate_1 = NULL;
    ptr->subordinate_2 = NULL;
    return ptr;
}

// The following code creates a organisation from scanning the input file
struct Employee* create_company() {
    int id, salary;
    char name[100];
    scanf("%d", &id);
    if(id == -1) return NULL; // -1 is used when there is a NULL pointer ie when no value is present

    scanf("%s %d", name, &salary);
    struct Employee* par = create_employee(id, name, salary);

    par->subordinate_1 = create_company();
    par->subordinate_2 = create_company();
    
    return par;
}

// The following function 
void print_company_helper(struct Employee* ceo) {
    // take input
    if(!ceo) {
        printf("%d ", -1);
        return;
    }
    printf("%d %s %d ", ceo->emp_id, ceo->emp_name, ceo->emp_salary);
    print_company_helper(ceo->subordinate_1);
    print_company_helper(ceo->subordinate_2);
    return;
}

void print_company(struct Employee* ceo) {
    print_company_helper(ceo);
    printf("\n");
    return;
} 


// --------------------------------------------------- YOU CAN EDIT BELOW THIS LINE -----------------------------------

struct Node
{
    int data;
    struct Node* next;
};

// create a node with data as x
struct Node* create_node(int x) {
    struct Node* ptr = malloc(sizeof(struct Node));
    ptr->next = NULL;
    ptr->data = x;
    return ptr;
}
struct Node* PythonListHead = NULL;


// prints the list in space seperated format
void print_list(struct Node* head) {
    struct Node* cur = head;
    while(cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}


// Add an item to the end of the list
void append(int x) 
{
    struct Node* s;
    s=PythonListHead;
    if(PythonListHead==NULL)
    {
        PythonListHead=create_node(x);
        return;
    }
    else
    {   while(s->next!=NULL)
        {
            s=s->next;
        }
        s->next=create_node(x);
    }
}
int len()
{   struct Node* p=PythonListHead;
    int a=0;
    while(p!=NULL)
    {   a+=1;
        p=p->next;
    }
    return a;
}

struct Employee* getnode(struct Employee* ceo,int id)
{   if(ceo==NULL) return NULL;

    if(ceo->emp_id==id)
    return ceo;

    struct Employee* p=getnode(ceo->subordinate_1,id);
    if(p!=NULL)
    return p;
    p=getnode(ceo->subordinate_2,id);
    if(p!=NULL)
    return p;

    return NULL;

}
struct Employee* CEO = NULL;
// CEO is a global pointer that points to the CEO of the company
int Boss_helper(struct Employee* id,int e)
{   if(!id)
    return -1;

    if(id->subordinate_1!=NULL)
    if(id->subordinate_1->emp_id==e)
        return id->emp_id;

    if(id->subordinate_2!=NULL)
    if(id->subordinate_2->emp_id==e)
        return id->emp_id;
    
    
    int k=Boss_helper(id->subordinate_1,e);
    if(k!=-1)
    return k;

    k=Boss_helper(id->subordinate_2,e);
    if(k!=-1)
    return k;

    return -1;
}
int Boss(int emp_id) {
    return Boss_helper(CEO,emp_id);

}
int get_first_common_boss(int emp_id1,int emp_id2){
    
    int p1=emp_id1;
    int flag=0;
    while(p1!=-1)
    {
        int p2=emp_id2;
        while(p2!=-1)
        {
            if(p1==p2)
            {
                flag=1;
                break;
            }
            p2=Boss(p2);
        }
        if(flag==1)
        break;
        p1=Boss(p1);
    }
    return p1;
    
}

int helper_level(struct Employee* e,int n,int search)
{
    if(e==NULL)
    return -101;
    if(e->emp_id==search)
    return n;
    int k=helper_level(e->subordinate_1,n+1,search);
    if(k!=-101) return k;
    return helper_level(e->subordinate_2,n+1,search);

}
int Level(int emp_id) {
    // Note that ceo has level 0
    return helper_level(CEO,0,emp_id);
}
void get_all_bosses(int emp_id){
    if(emp_id==-1) return;
    int n=Level(emp_id);
    if(n==0) {printf("%d ",-1);return;}
    int a[n];
    for(int i=0;i<n;i++)
    a[i]=0;
    int k=Boss(emp_id);
    int i=n-1;
    while(k!=-1)
    {
        a[i]=k;
        i--;
        k=Boss(k);
    }
    for(int j=0;j<n;j++)
    printf("%d ",a[j]);
}


int salary_help(struct Employee* ceo)
{   if(ceo==NULL)
    return 0;
    return ceo->emp_salary+salary_help(ceo->subordinate_1)+salary_help(ceo->subordinate_2);
}
int get_size(struct Employee* ceo)
{
    if(ceo==NULL)
    return 0;
    return 1+get_size(ceo->subordinate_1)+get_size(ceo->subordinate_2);
}
double get_average_salary(int emp_id){
    struct Employee* mynode=getnode(CEO,emp_id);
    int s=salary_help(mynode);
    int n=get_size(mynode);
    double average_a=(double)s/(double)n;
    return average_a;
}
void same_last_names_help(struct Employee* ceo,struct Employee* ref)
{
    if(ceo==NULL)
    return;
    if(strcmp(ref->emp_name,ceo->emp_name)==0)
    append(ceo->emp_id);
    same_last_names_help(ceo->subordinate_1,ref);
    same_last_names_help(ceo->subordinate_2,ref);
}
int getitem(int position)
{   position++;
    if(position>len()||position<1) return -1;
    if(position==1)
    {
        return PythonListHead->data;
    }
    int i=2;
    struct Node* p=PythonListHead;
    while(i<position)
    {
        p=p->next;
        i++;
    }
    return p->next->data;
}
void same_last_names(int emp_id)
{   
    same_last_names_help(CEO,getnode(CEO,emp_id));
    int n=len();
    int a[n];
    for(int i=0;i<n;i++)
    a[i]=getitem(i);

    for(int i=0;i<n;i++)  
    {
        for(int j=i;j<n;j++)
        if(Level(a[i])>Level(a[j]))
        {
            int g=a[i];
            a[i]=a[j];
            a[j]=g;
        }
    }  
    
    for(int i=0;i<n;i++)
    printf("%d ",a[i]);
    PythonListHead=NULL;
}

// --------------------------------------------------- YOU CAN EDIT ABOVE THIS LINE -----------------------------------

/* The following driver code creates a organisation for you and based on the input file
it will call all the functions that are necessary, your job is to edit the functions
above the line. Their descriptions are in the pdf and in the comments in the code. */

int main(int argc, char const *argv[])
{
    CEO = create_company();
    print_company(CEO);

    int T; 
    scanf("%d", &T);

    char operation_type[100];

    while(T--) {
        scanf("%s", operation_type);

        if(strcmp(operation_type, "get_first_common_boss") == 0) {
            int x,y;
            scanf("%d %d", &x, &y);
            int ans = get_first_common_boss(x,y);
            printf("%d\n", ans);
        } 
        else if(strcmp(operation_type, "same_last_names") == 0) {
            int x;
            scanf("%d", &x);
            same_last_names(x);
            printf("\n");
        } 
        else if(strcmp(operation_type, "get_all_bosses") == 0) {
            int x;
            scanf("%d", &x);
            get_all_bosses(x);
            printf("\n");
        } 
        else if(strcmp(operation_type, "get_average_salary") == 0) {
            int x;
            scanf("%d", &x);
            double ans = get_average_salary(x);
            printf("%.2f\n", ans);
        } 

    }

    return 0;
}
