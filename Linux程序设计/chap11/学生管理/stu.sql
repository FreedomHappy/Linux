create database ManStu;
create table academy(acaNum varchar(10) primary key,acaName varchar(10));
create table stuInfo(stuNum varchar(10) primary key,stuName varchar(10),acaNum varchar(10),state varchar(10),foreign key(acaNum) references academy(acaNum));
create table stuScore(stuNum varchar(10),subject varchar(10),score decimal(10,2),state varchar(10),primary key(stuNum,subject),foreign key(stuNum) references stuInfo(stuNum));

insert into academy values('001','Software'),
		   	 ('002','Education'),
			('003','Music');

insert into stuInfo values('0001','lin','001','none'),
			('0002','wang','002','none'),
			('0003','beta','002','none'),
			('0004','alpha','001','none'),
			('0005','kkk','003','none'),
			('0006','ddd','002','none');

insert into stuScore values('0001','English',89,'final'),
			('0002','English',90,'final'),
			('0003','English',70,'final'),
			('0004','English',80,'final'),
			('0005','English',60,'final'),
			('0006','English',50,'final'),
			('0001','math',90,'final'),
			('0001','linux',90,'final');
--查询各科前三名
select * from stuScore sc1 where (select count(1) from stuScore sc2 where sc1.subject=sc2.subject and sc2.score>=sc1.score)<=3 order by subject,score desc;
