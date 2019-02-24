#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

char * ins_academy()
{  char * query;
   char k;
   char aca_num[100],aca_name[100];
   char s[200];
   printf("Enter academy number:");
   scanf("%s",aca_num);
   //k=getchar();
   printf("Enter academy name:");
   scanf("%s",aca_name);
   int len=sprintf(s,"insert into academy values(\"%s\",\"%s\");",aca_num,aca_name);
   query=(char *)malloc(len+1);
   snprintf(query,len+1,"%s",s);
   return query;
}
char* ins_stuInfo()
{  
   char * query;
   char stu_ID[50],stu_name[50],stu_academyno[50],state[50];
   char s[200];
   printf("Enter stu_ID:");
   scanf("%s",stu_ID);
   printf("Enter stu_name:");
   scanf("%s",stu_name);
   printf("Enter stu_academyno:");
   scanf("%s",stu_academyno);
   printf("Enter stu_note:");
   scanf("%s",state);
   int len=sprintf(s,"insert into stuInfo values(\"%s\",\"%s\",\"%s\",\"%s\");",stu_ID,stu_name,stu_academyno,state);
   query=(char*)malloc(len+1);
   snprintf(query,len+1,"%s",s);
   return query;
}
char* ins_stuScore()
{  char * query;
   char stu_ID[50],subject[50],note[50];
   char s[200];
   float score;
   printf("Enter stu_ID:");
   scanf("%s",stu_ID);
   printf("Enter subject:");
   scanf("%s",subject);
   printf("Enter score:");
   scanf("%f",&score);
   printf("Enter note:");
   scanf("%s",note);
   int len = sprintf(s,"insert into stuScore values(\"%s\",\"%s\",%f,\"%s\");",stu_ID,subject,score,note);
   query=(char*)malloc(len+1);
   snprintf(query,len+1,"%s",s);
   return query;
}
void add()
{
    MYSQL mysql;  
    MYSQL_RES *res;  
    MYSQL_ROW row;  
    char *query;  
    int flag, t;
    //初始化数据库
    mysql_init(&mysql);  
    if(!mysql_real_connect(&mysql, "localhost", "root", "112358", "ManStu", 0, NULL, 0)) {  
        printf("Failed to connect to Mysql!\n");  
        return;  
    }else {  
        printf("Connected to Mysql successfully!\n");  
    }  



    char temp;
    char k;
    while(1){
	     printf("--------------------------------------------------------------------------\n");
    	     printf("Which files do you want to add(1--academy,2--stu_info,3--stu_score,4--quit)?");
    	     scanf("%c",&temp);
    	     k=getchar();
	     switch(temp)
    	     {
     	     case '1':
     	     query=ins_academy();
     	     break;
     	     case '2':
	     query=ins_stuInfo();
	     break;
	     case '3':
	     query=ins_stuScore();
	     break;
	     case '4':
	     break;
	     default:
	     printf("can't recognize your input!");
	     }
	     if(temp=='4'){
		break;
	     }
	    /*插入，成功则返回0*/ 
	    //printf("start select %s\n",query); 
	    flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));  
	    if(flag) {  
		printf("insert data failure!\n");  
		return;  
	    }else {  
		printf("insert data success!\n");  
	    } 
	    k=getchar();  
	    free(query);
   }

    //关闭数据库
    mysql_close(&mysql); 
    return;
}
void show()
{ 
    MYSQL mysql;  
    MYSQL_RES *res;  
    MYSQL_ROW row;  
    char *query;  
    int flag, t;  
    mysql_init(&mysql);  
    if(!mysql_real_connect(&mysql, "localhost", "root", "112358", "ManStu", 0, NULL, 0)) {  
        printf("Failed to connect to Mysql!\n");  
        return;  
    }else {  
        printf("Connected to Mysql successfully!\n");  
    }

    char temp;
    char k;
    while(1){
	    printf("---------------------------------------------------------------------------\n");
	    printf("Which files do you want to see(1--academy,2--stu_info,3--stu_score,4--quit)?");
	    scanf("%c",&temp);
	    k=getchar();
	    switch(temp)
	    {
	     case '1':
	     query="select * from academy;";
	     break;
	     case '2':
	     query="select * from stuInfo;";
	     break;
	     case '3':
	     query="select *from stuScore;";
	     break;
	     case '4':
	     break;
	     default:
	     printf("Can't recognize your input!\n");
	     }
	     if(temp=='4'){
		break;
	     }
	     /*查询，成功则返回0*/  
	    flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));  
	    if(flag) {  
		printf("Query failed!\n");  
		return;  
	    }else {  
		printf("[%s] made...\n", query);  
	    }  
	  
	  
	    /*mysql_store_result讲所有的查询结果读取到client*/  
	    res = mysql_store_result(&mysql);  
	    /*mysql_fetch_row检索结果集的下一行*/  
	    while(row = mysql_fetch_row(res)) {  
		/*mysql_num_fields返回结果集中的字段数目*/  
		for(t=0; t<mysql_num_fields(res); t++)  
		{  
		    printf("%s\t", row[t]);  
		}  
		printf("\n");  
	    }  
  
    }  
  
    mysql_close(&mysql);  	
    return;
}


void delete()
{   
    MYSQL mysql;  
    MYSQL_RES *res;  
    MYSQL_ROW row;  
    char *query;  
    int flag, t;  
    mysql_init(&mysql);  
    if(!mysql_real_connect(&mysql, "localhost", "root", "112358", "ManStu", 0, NULL, 0)) {  
        printf("Failed to connect to Mysql!\n");  
        return;  
    }else {  
        printf("Connected to Mysql successfully!\n");  
    }  
     	
    char k;
    char temp;
    char s[10];
    char s2[10];
    while(1){
    printf("-----------------------------------------------------------------------------\n");
    printf("Which files do you want to delete(1--academy,2--stu_info,3--stu_score,4--quit)?");
    scanf("%c",&temp);
    k=getchar();
    
    switch(temp)
    {
	     case '1':
             query=(char*)malloc(100);
	     printf("enter you academyNum:");
             scanf("%s",s);
	     sprintf(query,"delete from academy where acaNum=\"%s\"",s);
	     k=getchar();
	     break;
	     case '2':
	     query=(char*)malloc(100);
	     printf("enter you stuNum:");
             scanf("%s",s);
	     sprintf(query,"delete from stuInfo where stuNum=\"%s\"",s);
	     k=getchar();
	     break;
	     case '3':
	     query=(char*)malloc(100);
	     printf("enter you stuNum:");
	     scanf("%s",s);
	     printf("enter you subject:");
             scanf("%s",s2);
	     sprintf(query,"delete from stuScore where stuNum=\"%s\" and subject=\"%s\"",s,s2);
	     k=getchar();
	     break;
	     case '4':
	     break;
	     default:
	     printf("Can't recognize your input!\n");
    }
    if(temp=='4'){
        break;
    }
    /*删除，成功则返回0*/  
    flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));  
    if(flag) {  
        printf("Delete data failure!\n");  
        return;  
    }else {  
        printf("Delete data success!\n");  
    }
    free(query);
  }
    mysql_close(&mysql);  
    return; 
}

void update()
{
    MYSQL mysql;  
    MYSQL_RES *res;  
    MYSQL_ROW row;  
    char *query;  
    int flag, t;  
    mysql_init(&mysql);  
    if(!mysql_real_connect(&mysql, "localhost", "root", "112358", "ManStu", 0, NULL, 0)) {  
        printf("Failed to connect to Mysql!\n");  
        return;  
    }else {  
        printf("Connected to Mysql successfully!\n");  
    }  	
    
    char stu_ID[50],stu_name[50],stu_academyno[50],state[50];
    char k;
    char con;
    char s[200];
    query = s;
    while(1){
	printf("----------------------------------\n");
    	printf("update stuInfo,enter your stuNum");
	scanf("%s",stu_ID);
	printf("update stuName:");
	scanf("%s",stu_name);
	printf("update stuAcademyno:");
        scanf("%s",stu_academyno);
	printf("update state:");
	scanf("%s",state);
	sprintf(query,"update stuInfo set stuName=\"%s\",acaNum=\"%s\",state=\"%s\" where stuNum=\"%s\"",stu_name,stu_academyno,state,stu_ID);
        /*删除，成功则返回0*/  
        flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));  
        if(flag) {  
            printf("update data failure!\n");  
            return;  
          }else {  
            printf("update data success!\n");  
         } 
	k=getchar();
	printf("update continue(y/n):");
        con=getchar();
	k=getchar();
	if(con=='n')
	{break;}
    }

    
  
    mysql_close(&mysql);  
    return;  
}

void rank()
{
    MYSQL mysql;  
    MYSQL_RES *res;  
    MYSQL_ROW row;  
    char *query;  
    int flag, t;  
    mysql_init(&mysql);  
    if(!mysql_real_connect(&mysql, "localhost", "root", "112358", "ManStu", 0, NULL, 0)) {  
        printf("Failed to connect to Mysql!\n");  
        return;  
    }else {  
        printf("Connected to Mysql successfully!\n");  
    }  
    char * s[] = {"select stuNum,sum(score) from stuScore group by stuNum;","select * from stuScore sc1 where (select count(1) from stuScore sc2 where sc1.subject=sc2.subject and sc2.score>=sc1.score)<=3 order by subject,score desc;","select stuNum,sum(score) from stuScore group by stuNum LIMIT 5;"} ;
    char * prompt[]={"total score:\n","subject Top3:\n","total score Top5:\n"};           
    printf("-------------------------------------------------------\n");
    for(int i=0; i<3; i++){
	    printf("%s",prompt[i]);
	    query=s[i];
	    
	    flag = mysql_real_query(&mysql, query, (unsigned int)strlen(query));
            if(flag) {
                printf("Query failed!\n");
                return;
            }else {
                printf("[%s] made...\n", query);
            }


            /*mysql_store_result讲所有的查询结果读取到client*/
            res = mysql_store_result(&mysql);
            /*mysql_fetch_row检索结果集的下一行*/
            while(row = mysql_fetch_row(res)) {
                /*mysql_num_fields返回结果集中的字段数目*/
                for(t=0; t<mysql_num_fields(res); t++)
                {
                    printf("%s\t", row[t]);
                }
                printf("\n");
            }
    }
  
    mysql_close(&mysql);  
    return;  
}
void manage_loop()
{ char temp;
  char k;
  while(1){
    printf("**************************************************************************************\n");
    printf("Which operator do you want to do(1--insert,2--update,3--read,4--delete,5--rank,6--quit)?");
    scanf("%c",&temp);
    k=getchar();
    switch(temp)
    {
     case '1':
     	add(); break;
     
     case '2':
     	update(); break;
     
     case '3':
     	show(); break;
     
     case '4':
     	delete();
	       	break;
     
     case '5':
     	rank(); break;
     
     case '6': break;
     
     default:
     	printf("Can't recognize your input!\n");
    }
     
    if(temp=='6') break; 
  }
  return;
}

int main()
{
	MYSQL mysql;
	mysql_init(&mysql);
	if(!mysql_real_connect(&mysql,"localhost","root","112358","ManStu",0,NULL,0))
		printf("Error connecting to MySql!\n");
	//else
	//	printf("Connect MySql successful!\n");
	
	manage_loop();
	
	mysql_close(&mysql);
	return 0;
}
