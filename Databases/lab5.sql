create database IndexedDB
go
use IndexedDB
go

select * from asd s1 left join asd s2 on s1.fk1=s2.E
select * from asd s1 inner join asd s2 on s1.fk1=s2.E
select fk2,fk1,count(distinct B) from asd group by fk2,fk1 having fk1=0
select fk2,fk1,count(C) from asd group by fk2,fk1 having max(E)<0


create table fwProducts(
Name varchar(50),
FWID int primary key,
TID int foreign key references fwTypes(Tid)
)

create table fwTypes(


create table asd(
fk1 int,
fk2 int,
A varchar(5),
B varchar(5),
C varchar(5),
D int,
E int,
CONSTRAINT pk_asd PRIMARY KEY(fk1,fk2))

insert into asd values (1,1,'a1','b1','c1',7,2),(1,2,'a2','b3','c1',5,2),(1,3,'a2','b1','c2',Null,2),(2,1,'a3','b3','c2',Null,100),(2,2,'a3','b3','c3',Null,100)

select * from asd
Name varchar(50),
TID int primary key,
)

create table Suppliers(
Name varchar(50),
Price int,
SID int primary key,
FWID int foreign key references fwProducts(FWID))

create table Eventss(
Name varchar(50),
EID int primary key)

create table FPE(
Description varchar(50),
FWID int foreign key references fwProducts(FWID),
EID int foreign key references Eventss(EID),
CONSTRAINT pk_FPE PRIMARY KEY(FWID,EID)
)


Create table Donuts(
Did int primary key identity,
Name varchar(50) unique,
Weight float default 50
)

drop table Donuts

create table Toppings(
Tid int primary key identity,
Name varchar(50))

drop table Toppings

create table TD(
TDid int primary key identity,
Did int foreign key references Donuts(Did),
Tid int foreign key references Toppings(Tid),
Price int default 5
)
drop table TD

insert into Donuts(Name) values('Simple'),('Filled with chocolate'),('Filled with caramel'),('Filled with vanilla')
insert into Toppings(Name) values('Cream'),('Cinnamon'),('Sprinkles'),('Chocolate')
insert into TD(Did,Tid) values(1,2),(2,2),(1,3),(2,1)
--a
select * from Donuts ; --clustered index scan
select * from Donuts where Did=2--clustered index seek
select Name from Donuts--nonclustered index scan 
select Name from Donuts where Name='Simple' --nonclustered index seek
select * from Donuts where Name='Simple'--key lookup
--b
select * from Toppings where Name='Cream'
--select * from Toppings where Tid=2 order by Name
--c 
select * from Donuts d inner join TD t on d.Did=t.Did 
					   inner join Toppings tp on t.Tid=tp.Tid	
					   where d.Weight>49

IF EXISTS (SELECT name FROM sys.indexes WHERE name = N'NonClusteredIndexToppings')
 DROP INDEX NonClusteredIndexToppings ON Toppings;
GO
CREATE NONCLUSTERED INDEX NonClusteredIndexToppings ON Toppings(Name);
GO


--all the events that involves all the firework products

create procedure add_s @sid int, @fwid int,@price int 
as
	declare @no int;
	set @no=0;
	select @no=count(*) from Suppliers s where s.FWID=@fwid and s.SID=@sid

	if(@no<>0)begin
			update Suppliers
			set Price=@price
			where FWID=@fwid and SID=@sid
	end
	else begin
		insert into Suppliers values ('asd',@price,@sid,@fwid)
	end
go

select * from Eventss e1 where e1.EID in( select EID from FPE fpe1 inner join fwProducts fwp1 on fpe1.FWID=fwp1.FWID where e1.EID=fpe1.EID   )
select count(FWID) from fwProducts;

select Name from Eventss e inner join FPE fp on e.EID=fp.EID
					having count(*)=(select count(FWID) from fwProducts)

create function f1() returns table as return
	select Name
	from Suppliers
go