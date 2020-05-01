use PracticalExamRe
go

create table A(

P int ,
D int check (D>P)
)


create table Species(
Sid int primary key,
Name varchar(50) unique,
Description varchar(50))

create table Islands(
Iid int primary key,
Name varchar(50),
Area int)

create table Users(
Uid int primary key,
Name varchar(50) unique)

create table Dinosaurs(
Did int primary key,
Nickname varchar(50),
Age int,
Weight int,
Height int,
Happiness int default 1,
Sid int foreign key references Species(Sid),
Iid int foreign key references Islands(Iid))

create table DU(
Uid int foreign key references Users(Uid),
Did int foreign key references Dinosaurs(Did),
StartDate date,
EndDate date,
CONSTRAINT pk_du PRIMARY KEY(Uid,Did))

--drop table DU

insert into Species values (1,'name1','desc1'),(2,'name2','desc2'),(3,'name3','desc3')
insert into Islands values (1,'Island1',100),(2,'Island2',100),(3,'Island3',100)
insert into Dinosaurs values (1,'Dinosaur1',1,1,1,1,1,1),(2,'Dinosaur2',1,1,1,1,2,1),(3,'Dinosaur3',1,1,1,1,2,1),(4,'Dinosaur4',1,1,1,1,3,3)
insert into Users values (1,'user1'),(2,'user2')
insert into DU(Uid,Did,StartDate,EndDate) values (1,2,2020-10-11,2020-10-12),(1,3,2020-11-11,2020-11-11),(2,2,2020-12-11,2020-12-13)

select * from Species
select * from Islands
select * from Dinosaurs
select * from DU

select * from Species s inner join Dinosaurs d on s.Sid=d.Sid group by s.Sid having count(*)>2

create procedure del @name varchar(50)
as
	declare @id int;
	set @id=0;
	select @id=Sid from Species s where s.Name=@name
	delete from Dinosaurs  where Dinosaurs.Sid=@id
	delete from Species where Name=@name
go

exec del 'name1'

create view vd as
	select Name 
	from Islands i inner join Dinosaurs d on i.Iid=d.Iid
	group by Name
	having count(*)+1=(select count(*) from Dinosaurs ds )
go

drop view vd

select * from vd

create function fd(@n int) returns table as return

select Name
	from Users u inner join DU d on u.Uid=d.Uid
	group by Name
	having count(*)>=@n

go

drop function fd

select * from fd(1)

