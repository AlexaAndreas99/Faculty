CREATE DATABASE Gym
GO
USE Gym
GO

CREATE TABLE Groups(
Gid INT PRIMARY KEY,
NoofM INT NOT NULL)

CREATE TABLE Members(
Mid INT PRIMARY KEY,
Name VARCHAR(50) NOT NULL,
Gid INT FOREIGN KEY REFERENCES Groups(Gid))

select * from Members


CREATE TABLE Memberships(
MSid INT FOREIGN KEY REFERENCES Members(Mid),
EmissionD DATE,
ExpirationD DATE,
Constraint pk_MS PRIMARY KEY(MSid))

CREATE TABLE Trainers(
Tid INT PRIMARY KEY IDENTITY,
Name VARCHAR(50),
Domain VARCHAR(50)DEFAULT'Fitness',)




CREATE TABLE Sponsors(
Sid INT PRIMARY KEY,
Name VARCHAR(50))

CREATE TABLE Sponsorship(
Sid INT FOREIGN KEY REFERENCES Sponsors(Sid),
Tid INT FOREIGN KEY REFERENCES Trainers(Tid),
Value INT,
CONSTRAINT pk_SS PRIMARY KEY(Sid,Tid))

CREATE TABLE Providers(
Pid INT PRIMARY KEY,
Name VARCHAR(50))

CREATE TABLE Rooms(
Rid INT PRIMARY KEY,
Rnb INT)

CREATE TABLE Equipment(
Rid INT FOREIGN KEY REFERENCES Rooms(Rid),
Pid INT FOREIGN KEY REFERENCES Providers(Pid),
Value INT,
CONSTRAINT pk_eq PRIMARY KEY(Rid,Pid))

CREATE TABLE GT(
Gid INT FOREIGN KEY REFERENCES Groups(Gid),
Tid INT FOREIGN KEY REFERENCES Trainers(Tid),
Name VARCHAR(50),
Date DATE,
Time TIME,
Rid Int,
constraint fk_Rid  FOREIGN KEY(Rid) REFERENCES Rooms(Rid),
CONSTRAINT pk_GT PRIMARY KEY(Gid,Tid))

Drop Table GT
drop Table Memberships
drop table Members
--drop table Groups

--insert
INSERT INTO Groups(Gid,NoofM) VALUES(5,200),(4,20),(1,20),(2,20),(3,21)
INSERT INTO Groups(Gid,NoofM) VALUES(1,24)
DElete from Groups
delete from Members

INSERT INTO Members(Mid,Name,Gid) VALUES (123,'asd',4),(9,'Andrei',4),(1,'Andreas',1),(2,'Alex',1)
INSERT INTO Members VALUES(8,'Catalin',1),(5,'Marius',2),(6,'Monica',3),(7,'Ender',3)
INSERT INTO Memberships(MSid,EmissionD,ExpirationD) VALUES(1,'2012-12-02','2013-12-02'),(2,'2012-12-02','2013-12-02')



INSERT INTO Trainers(Name,Domain) VALUES ('Rock','HW'),('Paper','Fitness'),('Spock','Running'),('Scissors','Pilates')
delete from Trainers

INSERT INTO Sponsors(Sid,Name) VALUES (1,'NIKE'),(2,'UNDER ARMOUR')
INSERT INTO Sponsorship(Sid,Tid,Value) VALUES(1,1,1200),(2,2,1000)
delete from Sponsors
delete from Sponsorship


INSERT INTO Rooms(Rid,Rnb) VALUES(100,100),(101,101),(102,102)
INSERT INTO GT(Gid,Tid,Name,Date,Time,Rid) VALUES (3,3,'RUING','2012-12-02','19:00',102),(3,3,'RUNNING','2012-12-02','17:00',101),(1,2,'Fitness','2012-12-02','15:00',101),(2,1,'HW','2012-12-02','15:00',100)
delete from Rooms
delete from GT

--update
UPDATE Members SET Gid = 1 WHERE Mid = 9;
UPDATE Groups SET NoofM = 25 WHERE Gid = 5;
UPDATE GT SET Name = 'RUNNING' WHERE Tid = 3 and Gid=3;
--delete
DELETE FROM GT Where Gid=3 and Tid=3
DELETE FROM Members Where Mid=123

delete from Members
delete from Memberships
delete from Groups
delete from GT

SELECT * FROM GT
SELECT * FROM Trainers
SELECT * FROM Groups,Members WHERE Groups.Gid=Members.Gid
SELECT * FROM Groups
SELECT * FROM Members


--a
SELECT * FROM Members WHERE Name LIKE 'A_%' UNION SELECT * FROM Members WHERE Name LIKE 'M_%' --all members which name starts with A or M
SELECT * FROM Members WHERE Gid=1 OR Gid=3--all members from groups 1 or 3
--b
SELECT * FROM Members  WHERE Name like 'A_%' INTERSECT SELECT * FROM Members  WHERE Gid=1--members from group 1 which name starts with A
SELECT Top(2) Gid,Name FROM Members WHERE Gid IN (1,2);--top 2 members from groups 1 and 2
--c
SELECT * FROM Members WHERE Name LIKE 'A_%' EXCEPT SELECT * FROM Members WHERE Gid=1--all members wich name starts with A but are not in group 1
SELECT Gid,Name FROM Members WHERE Gid NOT IN (3,4,5);--all members that are not in groups 3,4,5
--d
select * FROM Groups g INNER JOIN Members m ON g.Gid=m.Gid INNER JOIN GT gt ON gt.Gid=g.Gid ORDER BY g.Gid--JOINS members and groups and GT
select m.Name as Member,gt.Name as Training,t.Name as Trainer,s.Name as ASD FROM Members m inner join Groups g on m.Gid=g.Gid inner join GT gt on gt.Gid=g.Gid INNER JOIN Trainers t ON gt.Tid=t.Tid inner join Sponsorship sp on sp.Tid=t.Tid inner join Sponsors s on s.Sid=sp.Sid

select g.Gid,Mid,Name from Groups g LEFT OUTER JOIN Members m ON g.Gid=m.Gid--joins groups and members
select g.Gid,Mid,Name from Groups g RIGHT OUTER JOIN Members m ON g.Gid=m.Gid
select * from Sponsorship s FULL OUTER JOIN GT g ON g.Tid=s.Tid
--e
SELECT Name FROM Members WHERE Gid IN(SELECT Gid FROM Groups WHERE NoofM<21)--the name of the members that are in a group with less than 21 people
SELECT * FROM Members Where Gid IN(SELECT Gid FROM Groups WHERE Gid IN(SELECT Gid FROM GT WHERE Date='2012-12-02') AND NoofM<21)--the name of the people that are in groups that have less than 21 members and have GT in 2012-12-02
--f
SELECT s.Gid, s.Name FROM Members s WHERE s.Name LIKE 'M_%' AND s.Gid<3 and EXISTS (SELECT * FROM Groups g  WHERE g.Gid=s.Gid) --the names that start with M in the groups that have the id smaller than 3 
SELECT * from Trainers t WHERE EXISTS(SELECT * FROM GT g Where g.Tid=t.Tid and g.Time='15:00')--the trainers that have training from 15:00
--g
SELECT * FROM (SELECT * FROM Members WHERE Name LIKE 'A_%' UNION SELECT * FROM Members WHERE Name LIKE 'M_%')A--THE NAMES OF THE MEMBERS THAT START WITH A OR M
SELECT * FROM (SELECT * FROM GT WHERE Rid=101)B--the GT that are held in room 101
--h
SELECT Name FROM Members GROUP BY Name HAVING Name IN(SELECT Name FROM Members Where Gid IN(SELECT Gid FROM GT WHERE Date='2012-12-02'))--the name of the members that are having GT in 2012-12-02
SELECT Name From Trainers t Group BY Name Having Name IN(SELECT Name From Trainers Where Tid IN(SELECT Tid FROM GT))--the name of the trainers that are assigned to a training program
SELECT Gid FROM Groups Group by Gid having MAX(NoofM)<21 --the Gid of the groups having less than 21 members
SELECT Gid,COUNT(Gid) From Members group by Gid--the number of members in each group 
--i
SELECT DISTINCT s.Name From Sponsors s,Sponsorship s1 WHERE s1.Value > All	(	SELECT s2.Value  FROM Sponsorship s2 WHERE s2.Value>1200	)
SELECT DISTINCT s.Name From Sponsors s,Sponsorship s1 WHERE s1.Value >= 	(	SELECT MAX(s2.Value)  FROM Sponsorship s2 WHERE s2.Sid=s1.Sid 	)
SELECT DISTINCT s.Name From Sponsors s,Sponsorship s1 WHERE s1.Value IN	(	SELECT s2.Value  FROM Sponsorship s2 WHERE s2.Value>100	)
SELECT DISTINCT s.Name From Sponsors s,Sponsorship s1 WHERE s1.Value NOT IN	(	SELECT s2.Value  FROM Sponsorship s2 WHERE s2.Value>1200	)


SELECT DISTINCT s.Name From Sponsors s,Sponsorship s1 WHERE s1.Value <ANY	(	SELECT s2.Value  FROM Sponsorship s2 WHERE s2.Value>1100	)
SELECT DISTINCT s.Name From Sponsors s,Sponsorship s1 WHERE s1.Value <	(	SELECT MIN(s2.Value)  FROM Sponsorship s2 WHERE s2.Value>1100	)

SELECT * from Sponsors
SELECT * from Sponsorship

EXEC v1