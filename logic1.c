#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

struct node1{
char value1;
char child_arr1[26];
char parent_arr1[26];
struct node1 *next1;
};

struct node1 *create1(char z){
struct node1 *newnode;
int i=0;
newnode=malloc(sizeof(struct node1));
newnode->value1=z;
for(i=0;i<26;i++){
newnode->child_arr1[i]='\0';
newnode->parent_arr1[i]='\0';
}
newnode->next1=NULL;
return newnode;
}


int main_logic(char elements[100],int l)
{
int flag=0,flag1=0,flag2=0,pos=0,i=0,j=0,flag3=0,k=0,loop=0,len=0;
struct node1 *head1,*pointer;
char a,b,q[27];
head1=malloc(sizeof(struct node1));
pointer=malloc(sizeof(struct node1));
head1=NULL;
for(k=0;k<l;k=k+2) {

a=elements[k];
b=elements[k+1];
if(head1==NULL) {
if(a==b) {
   loop=2;
   return loop;
}
struct node1 *newnode=create1(a);
struct node1 *newnode1=create1(b);
head1=newnode;
newnode->next1=newnode1;
for(i=0;newnode->child_arr1[i]!='\0';i++);
newnode->child_arr1[i]=b;
for(i=0;newnode1->parent_arr1[i]!='\0';i++);
newnode1->parent_arr1[i]=a;
//printf("\nInsert done\n");
}
    
else {
if(a==b) {
   loop=2;
   return loop;
}
pointer=head1;
flag=0;
flag1=0;
flag2=0;
flag3=0;
len=0;
pointer=head1;
while(pointer!=NULL) {
	if(pointer->value1==a) {
           flag=1;	   
        }
	if(pointer->value1==b) {
	   flag1=1;
	}
        pointer=pointer->next1;
}
if(flag==1 && flag1==0) {
   flag2=0;
   pointer=head1;
   while(pointer!=NULL) {
     for(i=0;pointer->child_arr1[i]!='\0';i++) {
        if(pointer->child_arr1[i]==a) {
           if(pointer->value1!=b) {
              q[len++]=pointer->value1;
              for(j=i;pointer->child_arr1[j]!='\0';j++);
              pointer->child_arr1[j]=b;
	      //printf("\ninsert done flag=1,flag1=0\n");
           }
	   else {
             //printf("\nloop detected...insert failed\n");
	     flag2=1;
	     loop=1;
           }
           break;
        }
     }
     if(flag2==1) {
      break;
     }
     pointer=pointer->next1;
   }
  if(flag2!=1) {
   pointer=head1;
   while(pointer->value1!=a) {
     pointer=pointer->next1;
   }
   for(i=0;pointer->child_arr1[i]!='\0';i++);
   pointer->child_arr1[i]=b;
   pointer=head1;
   while(pointer->next1!=NULL) {
      pointer=pointer->next1;
   }
   struct node1 *newnode;
   newnode=create1(b);
   pointer->next1=newnode;   
   for(i=0;newnode->parent_arr1[i]!='\0';i++);
   newnode->parent_arr1[i]=a;
   for(i=0;i<len;i++)
   newnode->parent_arr1[i+1]=q[i];
   //printf("\ninsert done flag=1,flag1=0\n");
  }
}


else if(flag==0 && flag1==0) {
   pointer=head1;
   struct node1 *newnode;
   struct node1 *newnode1;
   newnode=create1(a);
   newnode1=create1(b);
   while(pointer->next1!=NULL) {
      pointer=pointer->next1;
   }
   pointer->next1=newnode;
   newnode->next1=newnode1;
   for(i=0;newnode->child_arr1[i]!='\0';i++);
   newnode->child_arr1[i]=b;
   for(i=0;newnode1->parent_arr1[i]!='\0';i++);
   newnode1->parent_arr1[i]=a;
   //printf("\ninsert done flag=0,flag1=0\n");
}

else if(flag==0 && flag1==1) {
   pointer=head1;
   while(pointer!=NULL) {
     for(i=0;pointer->parent_arr1[i]!='\0';i++) {
        if(pointer->parent_arr1[i]==b) {
           if(pointer->value1!=a) {
              q[len++]=pointer->value1;
              for(j=i;pointer->parent_arr1[j]!='\0';j++);
              pointer->parent_arr1[j]=a;
              //printf("\ninsert done flag=0,flag1=1\n");
           }
	   else {
             //printf("\nloop detected...insert failed\n");
             flag2=1;
	     loop=1;
           }
           break;
        }
     }
     if(flag2==1) {
      break;
     }
     pointer=pointer->next1;
   }
   
  if(flag2!=1) {
   pointer=head1;
   while(pointer->value1!=b) {
     pointer=pointer->next1;
   }
   for(i=0;pointer->parent_arr1[i]!='\0';i++);
   pointer->parent_arr1[i]=a;
   pointer=head1;
   while(pointer->next1!=NULL) {
      pointer=pointer->next1;
   }
   struct node1 *newnode;
   newnode=create1(a);
   pointer->next1=newnode;   
   for(i=0;newnode->child_arr1[i]!='\0';i++);
   newnode->child_arr1[i]=b;
   for(i=0;i<len;i++)
   newnode->child_arr1[i+1]=q[i];
   //printf("\ninsert done flag=0,flag1=1\n");
  }
}

else {
   pointer=head1;
   while(pointer!=NULL) {
       if(pointer->value1==a) {
          for(i=0;pointer->parent_arr1[i]!='\0';i++) {
              if(pointer->parent_arr1[i]==b) {
                  loop=1;
		  break;
              }
          }
          for(i=0;pointer->child_arr1[i]!='\0';i++) {
              if(pointer->child_arr1[i]==a) {
                  flag2=1;
                  break;
              }
          }
       }
       if(loop==1 || flag2==1) {
            break;
       }
       pointer=pointer->next1;
   }
   pointer=head1;
   if(loop!=1 && flag2!=1) {
     while(pointer!=NULL) {
       if(pointer->value1==a) {
          for(i=0;pointer->child_arr1[i]!='\0';i++);
          pointer->child_arr1[i]=b;
       }
       if(pointer->value1==b) {
          for(i=0;pointer->parent_arr1[i]!='\0';i++);
	  pointer->parent_arr1[i]=a;
       }
       pointer=pointer->next1;
     }
   }  
}
}
}
return loop;
}



