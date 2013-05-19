#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <getopt.h>
#include "logic1.c"
        
#define PORT 9090
#define BUFSIZE 1024



struct node{
char value;
char child_arr[26];
char parent_arr[26];
struct node *next;
};

static struct node *head=NULL;

struct node *create(char z){
struct node *newnode;
int i=0;
newnode=malloc(sizeof(struct node));
newnode->value=z;
for(i=0;i<26;i++){
newnode->child_arr[i]='\0';
newnode->parent_arr[i]='\0';
}
newnode->next=NULL;
return newnode;
}


//query function 
int query(char h[2]) {
struct node *pointer;
int flag=0,flag1=0,flag2=0,option=0,i=0,flag3=0;
char a,b;
pointer=malloc(sizeof(struct node));
a=h[0];
b=h[1];
pointer=head;
flag=0;
flag1=0;
flag2=0;
flag3=0;
if(a==b) {
  option=7;
  return option;
}
while(pointer!=NULL) {
	if(pointer->value==a) {
           flag=1;	   
        }
	if(pointer->value==b) {
	   flag1=1;
	}
        pointer=pointer->next;
}
pointer=head;
if(flag==1 && flag1==1) {
      while(pointer!=NULL) {
          if(pointer->value==a) {
                for(i=0;pointer->child_arr[i]!='\0';i++) {
		    if(pointer->child_arr[i]==b) {
                           option=1;
                           return option;
                    }
                }
		for(i=0;pointer->parent_arr[i]!='\0';i++) {
		    if(pointer->parent_arr[i]==b) {
                           option=2;
                           return option;
                    }
                }
           }
           pointer=pointer->next;
      }
      option=3;
      return option;
}

else if(flag==1 && flag1==0) {
option=4;
return option;
}

else if(flag==0 && flag1==1) {
option=5;
return option;
}      

else 
option=6;
return option;
}


//insert function
int insert(char elements[100],int l) {
int flag=0,flag1=0,flag2=0,pos=0,i=0,j=0,flag3=0,k=0,loop=0,len=0;
struct node *pointer;
char a,b,q[27];
pointer=malloc(sizeof(struct node));
for(k=0;k<l;k=k+2) {
a=elements[k];
b=elements[k+1];
if(head==NULL) {
     struct node *newnode=create(a);
     struct node *newnode1=create(b);
     head=newnode;
     newnode->next=newnode1;
     for(i=0;newnode->child_arr[i]!='\0';i++);
     newnode->child_arr[i]=b;
     for(i=0;newnode1->parent_arr[i]!='\0';i++);
     newnode1->parent_arr[i]=a;
}
    
else {
pointer=head;
flag=0;
flag1=0;
flag2=0;
flag3=0;
len=0;
while(pointer!=NULL) {
	if(pointer->value==a) {
           flag=1;	   
        }
	if(pointer->value==b) {
	   flag1=1;
	}
        pointer=pointer->next;
}
if(flag==1 && flag1==0) {
   flag2=0;
   pointer=head;
   while(pointer!=NULL) {
     for(i=0;pointer->child_arr[i]!='\0';i++) {
        if(pointer->child_arr[i]==a) {
           if(pointer->value!=b) {
	      q[len++]=pointer->value;
              for(j=i;pointer->child_arr[j]!='\0';j++);
              pointer->child_arr[j]=b;
           }
	   else {
	     flag2=1;
	     loop=1;
           }
           break;
        }
     }
     if(flag2==1) {
      break;
     }
     pointer=pointer->next;
   }
  if(flag2!=1) {
   pointer=head;
   while(pointer->value!=a) {
     pointer=pointer->next;
   }
   for(i=0;pointer->child_arr[i]!='\0';i++);
   pointer->child_arr[i]=b;
   pointer=head;
   while(pointer->next!=NULL) {
      pointer=pointer->next;
   }
   struct node *newnode;
   newnode=create(b);
   pointer->next=newnode;   
   for(i=0;newnode->parent_arr[i]!='\0';i++);
   newnode->parent_arr[i]=a;
   for(i=0;i<len;i++)
   newnode->parent_arr[i+1]=q[i];
  }
}


else if(flag==0 && flag1==0) {
   pointer=head;
   struct node *newnode;
   struct node *newnode1;
   newnode=create(a);
   newnode1=create(b);
   while(pointer->next!=NULL) {
      pointer=pointer->next;
   }
   pointer->next=newnode;
   newnode->next=newnode1;
   for(i=0;newnode->child_arr[i]!='\0';i++);
   newnode->child_arr[i]=b;
   for(i=0;newnode1->parent_arr[i]!='\0';i++);
   newnode1->parent_arr[i]=a;
}

else if(flag==0 && flag1==1) {
   pointer=head;
   while(pointer!=NULL) {
     for(i=0;pointer->parent_arr[i]!='\0';i++) {
        if(pointer->parent_arr[i]==b) {
           if(pointer->value!=a) {
	      q[len++]=pointer->value;
              for(j=i;pointer->parent_arr[j]!='\0';j++);
              pointer->parent_arr[j]=a;
           }
	   else {
             flag2=1;
	     loop=1;
           }
           break;
        }
     }
     if(flag2==1) {
      break;
     }
     pointer=pointer->next;
   }
   
  if(flag2!=1) {
   pointer=head;
   while(pointer->value!=b) {
     pointer=pointer->next;
   }
   for(i=0;pointer->parent_arr[i]!='\0';i++);
   pointer->parent_arr[i]=a;
   pointer=head;
   while(pointer->next!=NULL) {
      pointer=pointer->next;
   }
   struct node *newnode;
   newnode=create(a);
   pointer->next=newnode;   
   for(i=0;newnode->child_arr[i]!='\0';i++);
   newnode->child_arr[i]=b;
   for(i=0;i<len;i++)
   newnode->child_arr[i+1]=q[i];
  }
}

else {
   pointer=head;
   while(pointer!=NULL) {
       if(pointer->value==a) {
          for(i=0;pointer->parent_arr[i]!='\0';i++) {
              if(pointer->parent_arr[i]==b) {
                  loop=1;
		  break;
              }
          }
          for(i=0;pointer->child_arr[i]!='\0';i++) {
              if(pointer->child_arr[i]==a) {
                  flag2=1;
                  break;
              }
          }  
       }      
       if(loop==1 || flag2==1) {
            break;
       }
       pointer=pointer->next;
   }
   pointer=head;
   if(loop!=1 && flag2!=1) {
     while(pointer!=NULL) {
       if(pointer->value==a) {
          for(i=0;pointer->child_arr[i]!='\0';i++);
          pointer->child_arr[i]=b;
       }
       if(pointer->value==b) {
          for(i=0;pointer->parent_arr[i]!='\0';i++);
	  pointer->parent_arr[i]=a;
       }
       pointer=pointer->next;
     }
   }  
}
}
}
return loop;
}




void usage()
{
  printf("dec_server [−h] [-p port-number] [−i file]\n");
  printf("-h  			print usage summary and exit\n");
  printf("-p portno.		port number. Default is 9090  \n");
  printf("-i input file 	log all request to a given file. Default is stdout\n");   
  exit(1);
}


                
void send_recv(int i, fd_set *master, int sockfd, int fdmax,FILE *fp,int option_file)
{
        int nbytes_recvd;
        char recv_buf[BUFSIZE], buf[BUFSIZE];	
        if ((nbytes_recvd = recv(i, recv_buf, BUFSIZ, 0)) <= 0) {
                if (nbytes_recvd == 0) {
                        printf("socket %d hung up\n", i);
                }else {
                        perror("recv");
                }
                close(i);
                FD_CLR(i, master);
        }else { 
	      fflush(stdout);
	      char *ptr=NULL,final[2000];
	      final[0]='\0';	      
              ptr=recv_buf;
	      printf("\ndec_server: Request received : %s",ptr);
	             while(*ptr!='\0') 
       			{
			       int j=0,k=0,len=0;char elements[100],q[2],option=0;
       			       if((*ptr=='i' || *ptr=='I') && (*(ptr+1)=='n')) {
			         	ptr=ptr+3;
				        while(*ptr!=';') {
                                           if(isupper(*ptr))
                                            {elements[j++]=*ptr;}
                                              ptr++;
                                        }
                                        len=j;                                            
                                        if(main_logic(elements,len)==0) {
                                            if(insert(elements,len)==0) {
					        printf("\ndec_server$ INSERT DONE\n");
						strcat(final,"INSERT DONE\n");  					        
						if(option_file==1) {
						     fputs("dec_server$ INSERT DONE\n", fp);
						}
                                                      
             			            }
             		                    else {
	        		                printf("\ndec_server$ LOOP DETECTED CANNOT INSERT\n");
						strcat(final,"LOOP DETECTED CANNOT INSERT\n");  		       		             
					        if(option_file==1) {
						     fputs("dec_server$ LOOP DETECTED CANNOT INSERT\n", fp);
						}
             		                    }    
       			                }
                                        else { 
         				    printf("\ndec_server$ LOOP DETECTED CANNOT INSERT\n");				            
					    strcat(final,"LOOP DETECTED CANNOT INSERT\n");
					    if(option_file==1) {
						     fputs("dec_server$ LOOP DETECTED CANNOT INSERT\n", fp);
						}
                                        } 
                                }
			        j=0;k=0,len=0;
			        if((*ptr=='q' || *ptr=='Q') && (*(ptr+1)=='u')) {
                                        ptr=ptr+3;
                                        while(*ptr!=';') {
                                             if(isupper(*ptr))
                                                {q[j++]=*ptr;}
                                             ptr++;
                                        }                                        
                                       option=query(q);
                                       char s[500]="Event ";
                       		       if(option==1) {
                                                printf("\ndec_server$ Event %c happened before Event %c \n",q[0],q[1]);
                                	        s[strlen(s)]=q[0];
                     		                strcat(s," happened before Event ");
                    		                s[strlen(s)]=q[1];
						strcat(s,"\n");
						strcat(final,s);						
						if(option_file==1) {
						     fputs(s, fp);
						}
                              	       }
		                       else if(option==2) {
	                                        printf("\ndec_server$ Event %c happened before Event %c \n",q[1],q[0]);
		    				s[strlen(s)]=q[1];
			 		        strcat(s," happened before Event ");
		    				s[strlen(s)]=q[0];
						strcat(s,"\n");
						strcat(final,s);		   
                                                if(option_file==1) {
						     fputs(s, fp);
						}
				       }
				       else if(option==3) {
			      	                printf("\ndec_server$ Event %c and Event %c are concurrent\n",q[0],q[1]);
		    				s[strlen(s)]=q[0];
		    				strcat(s," and Event ");
		    				s[strlen(s)]=q[1];
		    				strcat(s," are Concurrent");
		    				//send(i,s,500,0);	
						strcat(s,"\n");
						strcat(final,s);
						if(option_file==1) {
						     fputs(s, fp);
						} 
				       }
				       else if(option==4) {
		    				printf("\ndec_server$ Event %c not found\n",q[1]);
		    				s[strlen(s)]=q[1];
		    				strcat(s," not found");
		    				//send(i,s,500,0);
						strcat(s,"\n");
						strcat(final,s);
						if(option_file==1) {
						     fputs(s, fp);
						}	    
				       }
				       else if(option==5) {
		    				printf("\ndec_server$ Event %c not found\n",q[0]);
                    				s[strlen(s)]=q[0];
		    				strcat(s," not found");
		    				//send(i,s,500,0);
						strcat(s,"\n");
						strcat(final,s);
						if(option_file==1) {
						     fputs(s, fp);
						}
				       }
				       else if(option==6) {
		    				printf("\ndec_server$ Event %c and Event %c not found\n",q[0],q[1]);
                    				s[strlen(s)]=q[0];
		    				strcat(s," and Event ");
		    				s[strlen(s)]=q[1];
		    				strcat(s," not found");
		    				//send(i,s,500,0); 
						strcat(s,"\n");
						strcat(final,s);
						if(option_file==1) {
						     fputs(s, fp);
						}
				      }
				      else {
		    				printf("\ndec_server$ Event %c and Event %c are same\n",q[0],q[1]);
                    				s[strlen(s)]=q[0];
		    				strcat(s," and Event ");
		    				s[strlen(s)]=q[1];
		    				strcat(s," are same");
		    				//send(i,s,500,0); 
						strcat(s,"\n");
						strcat(final,s);
						if(option_file==1) {
						     fputs(s, fp);
						}
				      }
                             }
         		     if((*ptr=='r' || *ptr=='R') && (*(ptr+1)=='e')) {
				   while(*ptr!=';') {
                     		   ptr++;
                                   }
			  	   head=NULL;
		                   printf("\ndec_server$ RESET DONE\n");
				   //send(i,"RESET DONE",200,0);
				   strcat(final,"RESET DONE\n");					   
				   if(option_file==1) {
				          fputs("dec_server$RESET DONE\n", fp);
				   }
	   		    }
                            ptr++;
              }
	      send(i,final,2000,0);
      }       
}
                
void connection_accept(fd_set *master, int *fdmax, int sockfd, struct sockaddr_in *client_addr)
{
        socklen_t addrlen;
        int newsockfd;
        
        addrlen = sizeof(struct sockaddr_in);
        if((newsockfd = accept(sockfd, (struct sockaddr *)client_addr, &addrlen)) == -1) {
                perror("accept");
                exit(1);
        }else {
                FD_SET(newsockfd, master);
                if(newsockfd > *fdmax){
                        *fdmax = newsockfd;
                }
                printf("New connection from %s on port %d \n",inet_ntoa(client_addr->sin_addr), ntohs(client_addr->sin_port));
        }
}
        
void connect_request(int *sockfd, struct sockaddr_in *my_addr,char *port)
{
        int yes = 1;
                
        if ((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
                perror("Socket");
                exit(1);
        }
                
        my_addr->sin_family = AF_INET;
        my_addr->sin_port = htons(atoi(port));
        my_addr->sin_addr.s_addr = INADDR_ANY;
        memset(my_addr->sin_zero, '\0', sizeof my_addr->sin_zero);
                
        if (setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                perror("setsockopt");
                exit(1);
        }
                
        if (bind(*sockfd, (struct sockaddr *)my_addr, sizeof(struct sockaddr)) == -1) {
                perror("Unable to bind");
                exit(1);
        }
        if (listen(*sockfd, 10) == -1) {
                perror("listen");
                exit(1);
        }
        printf("\ndec_server Waiting for client\n");
        fflush(stdout);
}



int main(int argc,char *argv[])
{
        fd_set master;
        fd_set read_fds;
        int fdmax, i,prev_ind,option_file=0;
        int sockfd= 0;
	char *port="9090",*f,c;
        struct sockaddr_in my_addr, client_addr;
	FILE *fp;
	while(prev_ind = optind, (c =  getopt(argc, argv, ":h:p:i:")) != EOF) {
             if ( optind == prev_ind + 2 && *optarg == '-' ) {
                  c = ':';
                  -- optind;
             }
             switch (c) {
                    case 'h':
		      usage();
                      break;

		    case 'p':
                      port=optarg;
                      break;

		    case 'i':
                      option_file=1;
                      f=optarg;
		      break;

                    case ':':
                      printf("Missing option.\n");
                      exit(1);
                      break;
            }
        }
        
        if(option_file==1) {
	    fp=fopen(f,"w+");
        }
        FD_ZERO(&master);
        FD_ZERO(&read_fds);
        connect_request(&sockfd, &my_addr,port);
        FD_SET(sockfd, &master);
        
        fdmax = sockfd;
        while(1){
                read_fds = master;
                if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
                        perror("select");
                        exit(4);
                }
                
                for (i = 0; i <= fdmax; i++){
                        if (FD_ISSET(i, &read_fds)){
                                if (i == sockfd)
                                        connection_accept(&master, &fdmax, sockfd, &client_addr);
                                else
                                        send_recv(i, &master, sockfd, fdmax,fp,option_file);
                        }
                }
        }
        return 0;
}
