USE Gym
GO




v1
v2
v3
v4
v5
v6
v7

rv1
rv2
rv3
rv4
rv5
rv6
rv7







--drop procedure rv2

v1
--create procedure v1
--as begin
--	ALTER TABLE Equipment
--	ALTER COLUMN Value bigint
--	Print 'Value from Table Equipment changed from int to big int'
--end
rv1
--create procedure rv1
--as begin
--
--	ALTER TABLE Equipment
--	ALTER COLUMN Value int
--	Print 'Value from Table Equipment changed from big int to int'
--	end
v2
--create procedure v2
--as begin
--
--	ALTER TABLE Members
--	ADD Email varchar(50)
--	print 'Email added to the table Members'
--end
rv2
--create procedure rv2
--as begin

--	ALTER TABLE Members
--	DROP COLUMN Email 
--	print 'Email dropped from the table Members'
--end
v3
--create procedure v3
--as begin

--	alter table Sponsorship
--	add constraint df_100 default 100 for Value
--	print 'Default constraint added for Value in table Sponsorship'
--	end
rv3
--create procedure rv3
--as begin

--	Alter Table Sponsorship
--	drop constraint df_100
--	print 'Default constraint droped for Value in table Sponsorship'
	
--	end
v4
--create procedure v4
--as begin

--	alter table Equipment
--	Drop constraint pk_eq
--	Print 'Constraint pk_eq dropped from table Equipment'
--	end
rv4
--create procedure rv4
--as begin

--	alter table Equipment
--	ADD constraint pk_eq PRIMARY KEY(Rid,Pid)
--	Print 'Constraint pk_eq added to table Equipment'
--	end
v5
--alter table Trainers
--add CNP varchar(20)


alter table Members
drop CNP 

--create procedure v5
--as begin
--	alter table Trainers
--	add constraint ck_T unique(Cnp)
--	print 'constraint ck_M added to table Trainers'
--end

rv5

--create procedure rv5
--as begin
--	alter table Trainers
--	drop constraint ck_T 
--	print 'constraint ck_M dropped from table Trainers'
--end

v6
--create procedure v6
--as begin

--	Alter table GT
--	drop constraint fk_Rid
--	Print 'Constraint fk_Rid dropped from table GT'
--end
rv6
--create procedure rv6
--as begin

	--alter table GT
	--ADD constraint fk_Rid FOREIGN KEY(Rid) REFERENCES Rooms(Rid)
	--Print 'Constraint fk_Rid added to table Equipment'
	
--end
v7
--create procedure v7
--as begin
	--create table Sauna(
	--Sid int primary key,
	--Number int,
	--Type varchar(50));
	--print 'Table Sauna created'
--end
rv7
--create procedure rv7
--as begin
--	drop table Sauna
--	print 'Table Sauna droped'
--end


create table Version(
ver int);
insert into Version values(0);
Select * from Version

create procedure main
@vers int
as
begin
declare @t INT
declare @i INT
DECLARE @a varchar(50)
set @t=(select v.ver from Version v)
if @vers>7 or @vers<0
begin
	Print 'Invalid Version!'
	return
end

if @vers=@t
begin
	print 'This version is already!'
end

set @i=@t
while @i<@vers
begin
	set @i=@i+1
	set @a='v'+convert(varchar, @i)

	exec @a
end

while @i>@vers
begin
	set @a='rv'+convert(varchar, @i)
	exec @a
	set @i=@i-1
end

delete from Version
insert into Version values(@vers)
end

exec main @vers=0

select * from Version 

drop procedure main

delete from Version
insert into Version values(0)