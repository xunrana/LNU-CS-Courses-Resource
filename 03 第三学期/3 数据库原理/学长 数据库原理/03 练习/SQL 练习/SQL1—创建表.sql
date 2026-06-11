CREATE TABLE Department
( dno char(9) primary key,
  dname char(9) unique,
  phone char(11) unique
);

CREATE TABLE Employee
( eno char(9) primary key,
  ename char(5) unique,
  birthday date,
  salary int,
  deptno char(9),
  phone char(11) unique,
  adress char(20),
  foreign key (deptno) references Department(dno)
);
 