#include<iostream>
#include<string>
#include<cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
using namespace std;
void readfile(string f){
   int len,fd,length;
   char *file = (char *) f.data(); 
   fd=open(file,O_RDWR);
	 length=lseek(fd,0,SEEK_END);
   close(fd);
	 fd=open(file,O_RDWR);
	 char *b=new char[length];
   if(fd>0)
   {
     len=read(fd,b,length);
     b[len]='\0';
     cout<<b;
     close(fd);
   }
   else{
     cout<<"no file attain!";
   }
}

void show_records()
{
  char temp;
  while(true){
    cout<<"Which files do you want to see(1--academy,2--stuInfo,3--stuScore,4--quit)?";
    cin>>temp;
    switch(temp)
    {
     case '1':
     readfile("academy.txt");
     break;
     case '2':
     readfile("stuInfo.txt");
     break;
     case '3':
     readfile("stuScore.txt");
     break;
     case '4':
     break;
     default:
     cout<<"Can't recognize your input!"<<endl;
     }
     if(temp=='4'){
        break;
     }  
  }
}
void writefile(string file, char** s,int len){
   int fd;

   fd=open((char *)file.data(),O_CREAT|O_RDWR|O_APPEND,0777);
   if(fd>0)
   { 
     for(int i=0; i<len; i++)
     {
	write(fd,s[i],strlen(s[i]));
        write(fd,",",strlen(","));
     }
     write(fd,"\n",strlen("\n"));
     close(fd);
   }
   else{
     cout<<"no file attain!";
   }
}

void insert1()
{
   string aca_num,aca_name;
   cout<<"Enter academy number:";
   cin>>aca_num;
   cout<<"Enter academy name:";
   cin>>aca_name;
   char **p = new char*[2];
   p[0]=(char*)aca_num.data();
   p[1]=(char*)aca_name.data();
   //把内容写进文件
   writefile("./academy.txt",p,2);
   delete []p;
}
void insert2()
{
   string stu_ID,stu_name,stu_academyno,stu_note;
   cout<<"Enter stu_ID:";
   cin>>stu_ID;
   cout<<"Enter stu_name:";
   cin>>stu_name;
   cout<<"Enter stu_academyno:";
   cin>>stu_academyno;
   cout<<"Enter stu_note:";
   cin>>stu_note;
   char **p = new char*[4];
   p[0]=(char*)stu_ID.data();
   p[1]=(char*)stu_name.data();
   p[2]=(char*)stu_academyno.data();
   p[3]=(char*)stu_note.data();
   writefile("./stuInfo.txt",p,4);
   delete []p;
}
void insert3()
{
   string stu_ID,stu_name,subject,note,score;
   cout<<"Enter stu_ID:";
   cin>>stu_ID;
   cout<<"Enter stu_name:";
   cin>>stu_name;
   cout<<"Enter subject:";
   cin>>subject;
   cout<<"Enter score:";
   cin>>score;
   cout<<"Enter note:";
   cin>>note;
   char **p=new char*[5];
   p[0]=(char*)stu_ID.data();
   p[1]=(char*)stu_name.data();
   p[2]=(char*)subject.data();
   p[3]=(char*)score.data();
   p[4]=(char*)note.data();
   writefile("./stuScore.txt",p,5);
   delete []p;
}
void add_records()
{
  char temp;
  while(true){
    cout<<"Which files do you want to add(1--academy,2--stu_info,3--stu_score,4--quit)?";
    cin>>temp;
    switch(temp)
    {
     case '1':
     insert1();
     break;
     case '2':
     insert2();
     break;
     case '3':
     insert3();
     break;
     case '4':
     break;
     default:
     cout<<"Can't recognize your input!"<<endl;
     }
     if(temp=='4'){
        break;
     }  
  }
}
void remove1()
{
   int num;
   cout<<"Enter you want to delete(input academy's number):";
   cin>>num;
   int len,fd,length,i;
   fd=open("./academy.txt",O_RDWR);
	 length=lseek(fd,0,SEEK_END);
   close(fd);
   
   fd=open("./academy.txt",O_RDWR);
   char *b=new char[length];
   char *p=new char[length];
   int flag=0,j=0;
   if(fd>0) {
     len=read(fd,b,length);
     b[len]='\0';
     close(fd);
     for(i=0;i<length;i++)
     {
       if(b[i]=='\n') {
         int m=(int)b[i+1]-'0';
         if(m==num) {
            flag=1;
         } 
         else {
            flag=0;
         }
       }
       if(flag==0) {
         if(j==i) {
           p[j]=b[i];
	   j++;
	 }
	 else {
	   p[j]=b[i];
           j++;
	 }
       }
     }
     p[j]='\0';
   }
   else {
     cout<<"no file attain!";
   }
   
   if(i==j) {
      cout<<"no records have been found!"<<endl;
   }
   else {
     fd=open("./academy.txt",O_CREAT|O_RDWR|O_TRUNC,0777);
     if(fd>0) {
       write(fd,p,strlen(p));
       close(fd);
     }
     else {
       cout<<"no file attain!";
     }
   }
}
void remove2()
{
   int num;
   cout<<"Enter you want to delete(input student's number):";
   cin>>num;
   int len,fd,length,i;
   fd=open("./stuInfo.txt",O_RDWR);
	 length=lseek(fd,0,SEEK_END);
   close(fd);
	 fd=open("./stuInfo.txt",O_RDWR);
	 char *b=new char[length];
   char *p=new char[length];
   int flag=0,j=0;
   if(fd>0)
   {
     len=read(fd,b,length);
     b[len]='\0';
     close(fd);
	   for(i=0;i<length;i++)
	 	 {
			 if(b[i]=='\n')
       {
					int m=(int)b[i+1]-'0';
          if(m==num)
          {
            flag=1;
					}else{
						flag=0;
					}
			 }
			 if(flag==0)
			 {
					if(j==i)
					{
						p[j]=b[i];
						j++;
					}
					else
					{
						p[j]=b[i];
            j++;
					}
			 }
		 }
		 p[j]='\0';
   }
   else{
     cout<<"no file attain!";
   }
 	 if(i==j)
	 {
		cout<<"no records have been found!"<<endl;
	 }
	 else
	 {
     fd=open("./stuInfo.txt",O_CREAT|O_RDWR|O_TRUNC,0777);
     if(fd>0)
		 {
		   write(fd,p,strlen(p));
		   close(fd);
		 }
		 else{
		   cout<<"no file attain!";
		 }
	 }
}
void remove3()
{
   int num;
   string sub,temp;
   cout<<"Enter you want to delete(input student's number and student's subject):";
   cin>>num>>sub;
   int len,fd,length,i;
   fd=open("./stu_score.txt",O_RDWR);
	 length=lseek(fd,0,SEEK_END);
   close(fd);
	 fd=open("./stu_score.txt",O_RDWR);
	 char *b=new char[length];
   char *p=new char[length];
   int flag=0,j=0,m=0,n;
   if(fd>0)
   {
     len=read(fd,b,length);
     b[len]='\0';
     close(fd);
	   for(i=0;i<length;i++)
	 	 {
			 if(b[i]=='\n')
       {
					int m=(int)b[i+1]-'0';
          if(m==num)
          {
            n=i;
						while(m!=3)
						{
						  if(b[n]==' ')
              {
                m++;
              }
              n++;
            }
            while(b[n]!=' ')
						{
						  temp+=b[n];
              n++;
            }
            if(temp==sub)
            {
              flag=1;
            }
            else
            {
              flag=0;
            }
					}else{
						flag=0;
					}
			 }
			 if(flag==0)
			 {
					if(j==i)
					{
						p[j]=b[i];
						j++;
					}
					else
					{
						p[j]=b[i];
            j++;
					}
			 }
		 }
		 p[j]='\0';
   }
   else{
     cout<<"no file attain!";
   }
 	 if(i==j)
	 {
		cout<<"no records have been found!"<<endl;
	 }
	 else
	 {
     fd=open("./stu_score.txt",O_CREAT|O_RDWR|O_TRUNC,0777);
     if(fd>0)
		 {
		   write(fd,p,strlen(p));
		   close(fd);
		 }
		 else{
		   cout<<"no file attain!";
		 }
	 }
}
void delete_records()
{
  char temp;
  while(true){
    cout<<"Which files do you want to delete(1--academy,2--stu_info,3--stu_score,4--quit)?";
    cin>>temp;
    switch(temp)
    {
     case '1':
     remove1();
     break;
     case '2':
     remove2();
     break;
     case '3':
     remove3();
     break;
     case '4':
     break;
     default:
     cout<<"Can't recognize your input!"<<endl;
     }
     if(temp=='4'){
        break;
     }  
  }
}
void update1()
{
   int num;
   cout<<"Enter you want to update(input academy's number):";
   cin>>num;
   string numb,name;
   cout<<"Enter new academy number:";
   cin>>numb;
   cout<<"Enter new academy name:";
   cin>>name;
   string sum="\n"+numb+" "+name;
   int len,fd,length,i;
   fd=open("./academy.txt",O_RDWR);
	 length=lseek(fd,0,SEEK_END);
   close(fd);
   length+=sum.length();

	 fd=open("./academy.txt",O_RDWR);
	 char *b=new char[length];
   char *p=new char[length];
   int flag=0,j=0,m=0;
   if(fd>0)
   {
     len=read(fd,b,length);

     close(fd);
	   for(i=0;i<length;i++)
	 	 {
			 if(b[i]=='\n')
       {
					int m=(int)b[i+1]-'0';
          if(m==num)
          {
						p[i]=b[i];
            flag=1;
					}else{
						flag=0;
					}
			 }
			 if(flag==0)
			 {
					p[i]=b[i];
          j++;
			 }
       else
       {
          if(sum[m]!='\0')
          {
				  p[i]=sum[m];
          m++;
			    }else
          {
          p[i]=' ';
          }
			 }
		 }
		 p[i]='\0';
   }
   else{
     cout<<"no file attain!";
   }
 	 if(i==j)
	 {
		cout<<"no records have been found!"<<endl;
	 }
	 else
	 {
     fd=open("./academy.txt",O_CREAT|O_RDWR|O_TRUNC,0777);
     if(fd>0)
		 {
		   write(fd,p,strlen(p));
		   close(fd);
		 }
		 else{
		   cout<<"no file attain!";
		 }
	 }
}
void update2()
{
   int num;
   cout<<"Enter you want to update(input student's number):";
   cin>>num;
   string stu_ID,stu_name,stu_academyno,stu_note;
   cout<<"Enter stu_ID:";
   cin>>stu_ID;
   cout<<"Enter stu_name:";
   cin>>stu_name;
   cout<<"Enter stu_academyno:";
   cin>>stu_academyno;
   cout<<"Enter stu_note:";
   cin>>stu_note;
   string sum="\n"+stu_ID+" "+stu_name+" "+stu_academyno+" "+stu_note;
   int len,fd,length,i;
   fd=open("./stu_info.txt",O_RDWR);
	 length=lseek(fd,0,SEEK_END);
   close(fd);
   length+=sum.length();

	 fd=open("./stu_info.txt",O_RDWR);
	 char *b=new char[length];
   char *p=new char[length];
   int flag=0,j=0,m=0;
   if(fd>0)
   {
     len=read(fd,b,length);

     close(fd);
	   for(i=0;i<length;i++)
	 	 {
			 if(b[i]=='\n')
       {
					int m=(int)b[i+1]-'0';
          if(m==num)
          {
						p[i]=b[i];
            flag=1;
					}else{
						flag=0;
					}
			 }
			 if(flag==0)
			 {
					p[i]=b[i];
          j++;
			 }
       else
       {
          if(sum[m]!='\0')
          {
				  p[i]=sum[m];
          m++;
			    }else
          {
          p[i]=' ';
          }
			 }
		 }
		 p[i]='\0';
   }
   else{
     cout<<"no file attain!";
   }
 	 if(i==j)
	 {
		cout<<"no records have been found!"<<endl;
	 }
	 else
	 {
     fd=open("./stu_info.txt",O_CREAT|O_RDWR|O_TRUNC,0777);
     if(fd>0)
		 {
		   write(fd,p,strlen(p));
		   close(fd);
		 }
		 else{
		   cout<<"no file attain!";
		 }
	 }
}
void update3()
{
   int num;
   string sub,temp;
   cout<<"Enter you want to delete(input student's number and student's subject):";
   cin>>num>>sub;
   string stu_ID,stu_name,subject,note,score;
   cout<<"Enter stu_ID:";
   cin>>stu_ID;
   cout<<"Enter stu_name:";
   cin>>stu_name;
   cout<<"Enter subject:";
   cin>>subject;
   cout<<"Enter score:";
   cin>>score;
   cout<<"Enter note:";
   cin>>note;
   string sum="\n"+stu_ID+" "+stu_name+" "+subject+" "+score+" "+note;
   int len,fd,length,i;
   fd=open("./stu_score.txt",O_RDWR);
	 length=lseek(fd,0,SEEK_END);
   close(fd);
   length+=sum.length();

	 fd=open("./stu_score.txt",O_RDWR);
	 char *b=new char[length];
   char *p=new char[length];
   int flag=0,j=0,m=0,n;
   if(fd>0)
   {
     len=read(fd,b,length);
     close(fd);
	   for(i=0;i<length;i++)
	 	 {
			 if(b[i]=='\n')
       {
					int m=(int)b[i+1]-'0';
          if(m==num)
          {
            n=i;
						while(m!=3)
						{
						  if(b[n]==' ')
              {
                m++;
              }
              n++;
            }
            while(b[n]!=' ')
						{
						  temp+=b[n];
              n++;
            }
            if(temp==sub)
            {
              flag=1;
            }
            else
            {
              flag=0;
            }
					}else{
						flag=0;
					}
		 		}
       if(flag==0)
			 {
					p[i]=b[i];
          j++;
			 }
       else
       {
          if(sum[m]!='\0')
          {
				  p[i]=sum[m];
          m++;
			    }else
          {
          p[i]=' ';
          }
			 }
      }
		 p[i]='\0';
   }
   else{
     cout<<"no file attain!";
   }
 	 if(i==j)
	 {
		cout<<"no records have been found!"<<endl;
	 }
	 else
	 {
     fd=open("./stu_score.txt",O_CREAT|O_RDWR|O_TRUNC,0777);
     if(fd>0)
		 {
		   write(fd,p,strlen(p));
		   close(fd);
		 }
		 else{
		   cout<<"no file attain!";
		 }
	 }
}
void update_records()
{
  char temp;
  while(true){
    cout<<"Which files do you want to update(1--academy,2--stu_info,3--stu_score,4--quit)?";
    cin>>temp;
    switch(temp)
    {
     case '1':
     update1();
     break;
     case '2':
     update2();
     break;
     case '3':
     update3();
     break;
     case '4':
     break;
     default:
     cout<<"Can't recognize your input!"<<endl;
     }
     if(temp=='4'){
        break;
     }  
  }
}
void sort(int src[],int n)
{
    //从大到小排序
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(src[j]<src[j+1])    //如果前一个元素小于后一个元素
            {
                int temp;        //临时变量
                temp = src[j];
                src[j] = src[j+1]; //大的元素到前一个位置
                src[j+1] = temp;   //小的元素到后一个位置
            }
        }
    }
}
void cal_single()
{
   int len,fd,length;
   fd=open("./stu_score.txt",O_RDWR);
	 length=lseek(fd,0,SEEK_END);
   close(fd);
	 fd=open("./stu_score.txt",O_RDWR);
	 char *b=new char[length];
   if(fd>0)
   {
     len=read(fd,b,length);
     b[len]='\0';
     close(fd);
   }
   else{
     cout<<"no file attain!";
   }
   string info=b;
   string t[1000],d[100][100];
   int s=0,i,j,m=0;
   for(i=0;i<info.length();i++)
   {
      if(info[i]=='\n'){
         s++;
         continue;
      }
      t[s]+=info[i];
   }
   for(i=1;i<s;i++){
      for(j=0;j<t[i].length();j++)
      {
        if(t[i][j]==' '){
         m++;
         continue;
      }
      d[i][m]+=t[i][j];
     
      }
      m=0;
   }
   char temp;
   int *total=new int[10];
   int a=0;
   string sub;
   cout<<"Which subject do you want to see?(1--math,2--Chinese,3--English):";
   cin>>temp;
   switch(temp)
    {
     case '1':
     sub="math";
     break;
     case '2':
     sub="Chinese";
     break;
     case '3':
     sub="English";
     break;
     default:
     cout<<"Can't recognize your input!"<<endl;
     }
     for(i=1;i<s;i++)
     {
        if(d[i][2]==sub)
        {
           total[a]=atoi(d[i][3].c_str());
           a++;
        }
     }
     sort(total,a);
     for(i=0;i<a;i++)
     {
        for(j=1;j<s;j++)
        {
          if(d[j][2]==sub&&total[i]==atoi(d[j][3].c_str()))
          {
            cout<<t[j]<<endl;
          }
        }
     }
        
}
void cal_sum()
{
   int len,fd,length;
   fd=open("./stu_score.txt",O_RDWR);
	 length=lseek(fd,0,SEEK_END);
   close(fd);
	 fd=open("./stu_score.txt",O_RDWR);
	 char *b=new char[length];
   if(fd>0)
   {
     len=read(fd,b,length);
     b[len]='\0';
     close(fd);
   }
   else{
     cout<<"no file attain!";
   }
   string info=b;
   string t[1000],d[100][100];
   int s=0,i,j,m=0;
   for(i=0;i<info.length();i++)
   {
      if(info[i]=='\n'){
         s++;
         continue;
      }
      t[s]+=info[i];
   }
   for(i=1;i<s;i++){
      for(j=0;j<t[i].length();j++)
      {
        if(t[i][j]==' '){
         m++;
         continue;
      }
      d[i][m]+=t[i][j];
     
      }
      m=0;
   }
   char temp;
   int *total=new int[10];
   int a=0;
   for(i=1;i<s;)
   {
      total[a]=atoi(d[i][3].c_str())+atoi(d[i+1][3].c_str())+atoi(d[i+2][3].c_str());
      a++;
      i+=3;
   }
    sort(total,a);
    for(i=0;i<a;i++)
    {
      for(j=1;j<s;)
      {
        if(total[i]==atoi(d[j][3].c_str())+atoi(d[j+1][3].c_str())+atoi(d[j+2][3].c_str()))
        {
          cout<<d[j][0]<<" "<<d[j][1]<<" "<<total[i]<<endl;
        }
        j+=3;
       }
     }
        
}
void rank_records()
{
  char temp;
  while(true){
    cout<<"Which operator do you want to do(1--rank single,2--rank sum,3--quit)?";
    cin>>temp;
    switch(temp)
    {
     case '1':
     cal_single();
     break;
     case '2':
     cal_sum();
     break;
     case '3':
     break;
     default:
     cout<<"Can't recognize your input!"<<endl;
     }
     if(temp=='3'){
        break;
     }  
  }
}
int main(){
  char temp;
  while(true){
    cout<<"***************************************************************************************"<<endl;
    cout<<"Which operator do you want to do(1--insert,2--update,3--read,4--delete,5--rank,6--quit)?";
    cin>>temp;
    switch(temp)
    {
     case '1':
     add_records();
     break;
     case '2':
     update_records();
     break;
     case '3':
     show_records();
     break;
     case '4':
     delete_records();
     break;
     case '5':
     rank_records();
     break;
     case '6':
     break;
     default:
     cout<<"Can't recognize your input!"<<endl;
     }
     if(temp=='6'){
        break;
     }  
  }
}
