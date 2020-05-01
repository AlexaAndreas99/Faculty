


create table Tables(
TableID Int Primary key,
Name varchar(50))

create table Tests(
TestID int Primary key,
Name varchar(50))

create table Views(
ViewID int primary key,
Name varchar(50))

create table TestRuns(
TestRunID int primary key identity,
Description varchar(100),
StartAt datetime,
EndAt datetime)

drop table TestRuns
drop table TestRunTables
drop table TestRunViews

create table TestTables(
TableID int foreign key references Tables(TableID),
TestID int foreign key references Tests(TestID),
NoOfRows int,
Position int
constraint pk_TestTables primary key(TableID,TestID)
)

create table TestViews(
ViewID int foreign key references Views(ViewID),
TestID int foreign key references Tests(TestID),
constraint pk_TestViews primary key(ViewID,TestID)
)

create table TestRunViews(
ViewID int foreign key references Views(ViewID),
TestRunID int foreign key references TestRuns(TestRunID),
StartAt datetime,
EndAt datetime,
constraint pk_TestRunViews primary key(ViewID,TestRunID)
)

create table TestRunTables(
TableID int foreign key references Tables(TableID),
TestRunID int foreign key references TestRuns(TestRunID),
StartAt datetime,
EndAt datetime,
constraint pk_TestRunTables primary key(TableID,TestRunID)
)

insert into dbo.Tables values (1,'Groups'),(2,'Members'),(3,'GT');
insert into Views values (1,'v_1'),(2,'v_2'),(3,'v_3')
insert into Tests values(1,'insert_Groups_100'),(2,'delete_Groups_100'),(3,'select_v_1'),
						(4,'insert_Members_100'),(5,'delete_Members_100'),(6,'select_v_2'),
						(7,'insert_GT_100'),(8,'delete_GT_100'),(9,'select_v_3')

insert into TestViews values(1,3),(2,6),(3,9)
insert into TestTables (TableId,TestId,NoOfRows,Position)values (1,1,100,1),(2,4,100,2),(3,7,100,3),(1,2,100,3),(2,5,100,2),(3,8,100,1)

select * from TestTables


create procedure insert_groups
@i int 
as begin
	declare @NoOfRows int
	declare @n int 
	declare @t varchar(30)
	select top 1 @NoOfRows = NoOfRows from dbo.TestTables where TestTables.TableID=1 and @i=TestTables.NoOfRows
	set @n=1

	while @n<@NoOfRows
	begin
		--set @t='Group '+CONVERT(varchar(5),@n)
		insert into Groups(Gid,NoofM)values(@n,20)
		set @n=@n+1
	end
end

create procedure insert_members
@i int
as begin
	declare @fk int
	declare @NoOfRows int
	declare @n int 
	declare @t varchar(30)
	select top 1 @NoOfRows = NoOfRows from dbo.TestTables where TestTables.TableID=2 and @i=TestTables.NoOfRows
	select top 1 @fk=Gid from Groups
	set @n=1

	while @n<@NoOfRows
	begin
		set @t='Name '+CONVERT(varchar(5),@n)
		insert into Members(Mid,Name,Gid)values(@n,@t,@fk+@n-1)
		set @n=@n+1
	end
end

create procedure insert_GT
as begin
	insert into GT(Gid,Tid) 
	select top 100 Gid,Tid from Groups cross join Trainers
end


drop procedure insert_groups
exec insert_groups 100
exec insert_members 100
exec insert_GT

create procedure main4 as begin
	declare @start datetime
	declare @end datetime
	declare @view datetime
	declare @testRunID int

	set @start =getdate()
	print '1'
	delete from GT
	delete from Members
	delete from Groups
	print '1'
	exec insert_groups 100
	exec insert_members 100
	exec insert_GT
	
	set @end=GETDATE()
	
	select * from v_1
	select * from v_2
	select * from v_3
	
	set @view=GETDATE()
	
	print '1'
	insert into  TestRuns(Description,StartAt,EndAt) values('Delete gt+members+groups, Insert groups+members+gt, View v_1+v_2+v3',@start,@view)
	set @testRunID=(select max(TestRunID) from TestRuns)
	print @testRunID
	insert into TestRunTables(TableID,TestRunID,StartAt,EndAt) values(1,@testRunID,@start,@end)
	insert into TestRunViews(ViewID,TestRunID,StartAt,EndAt) values(1,@testRunID,@end,@view)
end

delete from Groups
select * from Groups
delete from Members
select * from Members
select * from GT
delete from GT
select * from  TestRuns
exec main4
drop procedure main4

select * from TestRuns
select * from TestRunTables
select * from TestRunViews